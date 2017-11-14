/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>

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
    int mbytes = bdk_dram_config(node, override_for_speed);
    if (mbytes < 0)
    {
        bdk_error("N%d: Failed DRAM init\n", node);
        /* Reset on failure if we're using the watchdog */
        if (bdk_watchdog_is_running())
            bdk_boot_status(BDK_BOOT_STATUS_REQUEST_POWER_CYCLE);
        return;
    }

    /* Poke the watchdog */
    bdk_watchdog_poke();

    /* Report DRAM status */
    printf("Node %d: DRAM:%s\n", node, bdk_dram_get_info_string(node));

    /* See if we should test this node's DRAM during boot */
    int test_dram = bdk_config_get_int(BDK_CONFIG_DRAM_BOOT_TEST, node);
    if (test_dram)
    {
        /* Wake up one core on the other node */
        if (node != bdk_numa_master())
            bdk_init_cores(node, 1);
        /* Run the address test to make sure DRAM works */
        if (bdk_dram_test(13, 0, 0x10000000000ull, BDK_DRAM_TEST_NO_STATS | (1<<node)))
            bdk_boot_status(BDK_BOOT_STATUS_REQUEST_POWER_CYCLE);
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

    /* Unlock L2 now that DRAM works */
    if (node == bdk_numa_master())
    {
        uint64_t l2_size = bdk_l2c_get_cache_size_bytes(node);
        BDK_TRACE(INIT, "Unlocking L2\n");
        bdk_l2c_unlock_mem_region(node, 0, l2_size);
        bdk_watchdog_poke();
    }
}
