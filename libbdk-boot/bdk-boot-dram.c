/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-ap.h"

static int dram_emulator(bdk_node_t node, int override_for_speed)
{
    /* For emulation dram is just there
     * Fake minimal init to avoid nxm_wr errors.
     * 2 chip-selects, 1gb each, no ranking
     * Memory does not have ecc - no need to scrub
     */
    BDK_CSR_MODIFY(lmcx_ddr_pll_ctl, node, BDK_LMCX_DLL_CTL2(0),
                   lmcx_ddr_pll_ctl.s.dreset = 0);
    BDK_CSR_INIT(lmc0_cfg,node,BDK_LMCX_CONFIG(0));
    BDK_CSR_MODIFY(c,node,BDK_LMCX_NXM(0),
                   c.s.mem_msb_d1_r0 = lmc0_cfg.s.pbank_lsb + 2 - lmc0_cfg.s.rank_ena ;
                   c.s.mem_msb_d0_r0 = lmc0_cfg.s.pbank_lsb + 2 - lmc0_cfg.s.rank_ena ;
                   c.s.cs_mask = 0xc;);
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_CSR_MODIFY(lmcx_ddr_pll_ctl, node, BDK_LMCX_DDR_PLL_CTL(0),
                       lmcx_ddr_pll_ctl.cn83xx.reset_n = 1);
    }
    else
    {
        BDK_CSR_MODIFY(lmcx_ddr_pll_ctl, node, BDK_LMCX_DDR_PLL_CTL(0),
                       lmcx_ddr_pll_ctl.cn9.pd = 0;
                       lmcx_ddr_pll_ctl.cn9.pll_reset = 0);
    }
    return 4096;
}

/**
 * Configure DRAM on a specific node
 *
 * @param node   Node to configure
 * @param override_for_speed
 *               If non-zero, the DRAM init code will use this for the
 *               DRAM clock speed. This is used for SLT and should not
 *               be used otherwise.
 */
void bdk_boot_dram(bdk_node_t node, int override_for_speed)
{
    /* Don't run for nodes that don't exist */
    if (!bdk_numa_exists(node))
        return;

    BDK_TRACE(INIT, "Initializing DRAM on node %d\n", node);
    int mbytes;
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        mbytes = dram_emulator(node, override_for_speed);
    else
        mbytes = bdk_dram_config(node, override_for_speed);
    if (mbytes < 0)
    {
        bdk_error("N%d: Failed DRAM init\n", node);
        return;
    }

    /* Poke the watchdog */
    bdk_watchdog_poke();

    /* Report DRAM status */
#if 0 // NEWPORT
    printf("Node %d: DRAM:%s\n", node, bdk_dram_get_info_string(node));
#else
    printf("DRAM    :%s\n", bdk_dram_get_info_string(node));
#endif

    /* See if we should test this node's DRAM during boot */
    int test_dram = bdk_config_get_int(BDK_CONFIG_DRAM_BOOT_TEST, node);
    if (test_dram)
    {
        /* Wake up one core on the other node */
        if (node != bdk_numa_master())
            bdk_init_cores(node, 1);
        /* Run the address test to make sure DRAM works */
        bdk_dram_test(13, 0, 0x10000000000ull, BDK_DRAM_TEST_NO_STATS | (1 << node));
        bdk_watchdog_poke();
        /* Put other node core back in reset */
        if (node != bdk_numa_master())
            BDK_CSR_WRITE(node, BDK_RST_PP_RESET, -1);
        /* Clear DRAM */
        uint64_t skip = 0;
        if (node == bdk_numa_master())
            skip = bdk_dram_get_top_of_bdk();
        void *base = bdk_phys_to_ptr(bdk_numa_get_address(node, skip));
        bdk_zero_memory(base, ((uint64_t)mbytes << 20) - skip);
        bdk_watchdog_poke();
    }
}
