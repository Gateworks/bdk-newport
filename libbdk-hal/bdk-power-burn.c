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
#include "libbdk-arch/bdk-csrs-ap.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(POWER_BURN);

static bdk_power_burn_type_t global_burn_type[BDK_NUMA_MAX_NODES] = {
    BDK_POWER_BURN_NONE, BDK_POWER_BURN_NONE, BDK_POWER_BURN_NONE, BDK_POWER_BURN_NONE};

static void power_thread(int unused1, void *unused2)
{
    extern int __bdk_power_burn(void);
    bdk_node_t node = bdk_numa_local();
    BDK_TRACE(INIT, "N%d.%d: Thread burning power\n", node, bdk_get_core_num());
    bdk_wait_usec(100000);
    uint64_t second = bdk_clock_get_rate(node, BDK_CLOCK_TIME);
    while (1)
    {
        uint64_t result = 0;
        bdk_power_burn_type_t burn_type = (volatile bdk_power_burn_type_t)global_burn_type[node];
        switch (burn_type)
        {
            case BDK_POWER_BURN_NONE:        /* Disable power burn */
                return;
            case BDK_POWER_BURN_FULL:        /* Continuously burn power */
                result = __bdk_power_burn();
                break;
            case BDK_POWER_BURN_CYCLE_10MS:  /* Cycle: Burn for 10ms, idle for 10ms */
            {
                uint64_t wall = bdk_clock_get_count(BDK_CLOCK_TIME);
                wall /= second / 100;
                if (wall & 1)
                    result = __bdk_power_burn();
                break;
            }
            case BDK_POWER_BURN_CYCLE_1S:    /* Cycle: Burn for 1s, idle for 1s */
            {
                uint64_t wall = bdk_clock_get_count(BDK_CLOCK_TIME);
                wall /= second;
                if (wall & 1)
                    result = __bdk_power_burn();
                break;
            }
            case BDK_POWER_BURN_CYCLE_5S:    /* Cycle: Burn for 5s, idle for 5s */
            {
                uint64_t wall = bdk_clock_get_count(BDK_CLOCK_TIME);
                wall /= second * 5;
                if (wall & 1)
                    result = __bdk_power_burn();
                break;
            }
            case BDK_POWER_BURN_CYCLE_1M:    /* Cycle: Burn for 1m, idle for 1m */
            {
                uint64_t wall = bdk_clock_get_count(BDK_CLOCK_TIME);
                wall /= second * 60;
                if (wall & 1)
                    result = __bdk_power_burn();
                break;
            }
            case BDK_POWER_BURN_CYCLE_5M:    /* Cycle: Burn for 5m, idle for 5m */
            {
                uint64_t wall = bdk_clock_get_count(BDK_CLOCK_TIME);
                wall /= second * 300;
                if (wall & 1)
                    result = __bdk_power_burn();
                break;
            }
        }
        if (result != 0)
            bdk_fatal("N%d.CPU%d: Power burn self check failed\n", node, bdk_get_core_num());
        bdk_thread_yield();
    }
}

/**
 * Set the current power burn mode for a node
 *
 * @param node      Node to control power burn for
 * @param burn_type Mode of power burn
 *
 * @return Zero on success, negative on failure
 */
int bdk_power_burn(bdk_node_t node, bdk_power_burn_type_t burn_type)
{
    if (burn_type == BDK_POWER_BURN_NONE)
    {
        global_burn_type[node] = burn_type;
        BDK_MB;
        return 0;
    }

    int need_cores = (global_burn_type[node] == BDK_POWER_BURN_NONE);
    global_burn_type[node] = burn_type;
    BDK_MB;
    if (!need_cores)
        return 0;

    if (bdk_init_cores(node, 0))
    {
        global_burn_type[node] = BDK_POWER_BURN_NONE;
        BDK_MB;
        bdk_error("N%d: Not starting power burn as node's cores didn't start\n", node);
        return -1;
    }

    printf("N%d: Starting power burn threads\n", node);

    const int num_cores = bdk_get_num_cores(node);
    for (int core = 0; core < num_cores; core++)
    {
        if (bdk_thread_create(node, 1ull << core, power_thread, 0, NULL, 16384))
            bdk_error("Failed to create thread %d for power burn on node %d\n", core, node);
    }
    return 0;
}

/**
 * Set the throttle level percent for an entire chip
 *
 * @param node     Node to set
 * @param throttle Percent of Throttle level (0-100)
 */
void bdk_power_throttle(bdk_node_t node, int throttle_percent)
{
    const int num_cores = bdk_get_num_cores(node);
    uint64_t running = bdk_get_running_coremask(node);
    for (int core = 0; core < num_cores; core++)
    {
        if (running & (1ull << core))
        {
            BDK_CSR_DEFINE(power, BDK_AP_CVM_POWER_EL1);
            power.u = bdk_sysreg_read(node, core, BDK_AP_CVM_POWER_EL1);
            /* Max power was set incorrectly for CN88XX pass 1.x */
            if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
                power.s.maxpow = 165;
            /* Percentage is based on the Max power field */
            power.s.powlim = throttle_percent * power.s.maxpow / 100;
            bdk_sysreg_write(node, core, BDK_AP_CVM_POWER_EL1, power.u);
        }
    }
}

