/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ap.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(POWER_BURN);

static bdk_power_burn_type_t global_burn_type[BDK_NUMA_MAX_NODES] = {
    BDK_POWER_BURN_NONE,};

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
            case BDK_POWER_BURN_WFE: /* Loop a sequence of WFEs to lower core power */
                /* Idle BDK automatically stalls the core */
                return;
        }
        if (result != 0)
            bdk_error("N%d.CPU%d: Power burn self check failed\n", node, bdk_get_core_num());
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
        BDK_WMB;
        return 0;
    }

    int need_cores = (global_burn_type[node] == BDK_POWER_BURN_NONE) ||
        (global_burn_type[node] == BDK_POWER_BURN_WFE);
    global_burn_type[node] = burn_type;
    BDK_WMB;
    if (!need_cores)
        return 0;

    if (bdk_init_cores(node, 0))
    {
        global_burn_type[node] = BDK_POWER_BURN_NONE;
        BDK_WMB;
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
            /* Percentage is based on the Max power field */
            power.s.powlim = throttle_percent * power.s.maxpow / 100;
            bdk_sysreg_write(node, core, BDK_AP_CVM_POWER_EL1, power.u);
        }
    }
}

/**
 * Start coremark on the requested coremask
 *
 * @param node     Node to start
 * @param coremask cores to start
 *
 * @return Zero on success, negative on failure
 */
int bdk_power_coremark(bdk_node_t node, uint64_t coremask)
{
    extern uint32_t default_num_contexts;
    extern uint64_t coremark_coremask;
    extern void coremark_main(void);

    if (bdk_init_cores(node, coremask))
    {
        bdk_error("N%d: Not starting coremark as node's cores didn't start\n", node);
        return -1;
    }
    if (coremask == 0)
        coremask = -1;
    coremask &= bdk_get_running_coremask(node);
    coremark_coremask = coremask;
    default_num_contexts = bdk_dpop(coremask);
    BDK_WMB;
    printf("RCLK:  %lu Mhz\n"
        "SCLK:  %lu Mhz\n",
        bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000,
        bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / 1000000);
    coremark_main();
    return 0;
}

