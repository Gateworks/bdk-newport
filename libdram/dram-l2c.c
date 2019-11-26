/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "dram-internal.h"

int limit_l2_ways(bdk_node_t node, int ways, int verbose)
{
    int ways_max;
    int ways_min = 0;
    int errors = 0;

    // FIXME: ignore on T9X for now
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        if (verbose)
            ddr_print("N%d: CN9XXX: Unable to limit L2 to %d ways\n", node, ways);
        return 0;
    }

    ways_max = bdk_l2c_get_num_assoc(node);
    if (ways >= ways_min && ways <= ways_max)
    {
        uint32_t valid_mask = (0x1 << ways_max) - 1;
        uint32_t mask = (valid_mask << ways) & valid_mask;
        if (verbose)
            ddr_print("N%d: Limiting L2 to %d ways\n", node, ways);
        for (int i = 0; i < (int)bdk_get_num_cores(node); i++)
            errors += bdk_l2c_set_core_way_partition(node, i, mask);
        errors += bdk_l2c_set_hw_way_partition(node, mask);
    }
    else
    {
        errors++;
        printf("ERROR: invalid limit_l2_ways %d, must be between %d and %d\n",
               ways, ways_min, ways_max);
    }
    if (errors)
        puts("ERROR limiting L2 cache ways\n");

    return errors;
}

