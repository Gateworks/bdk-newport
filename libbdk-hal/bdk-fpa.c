/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/* Global variables for FPA / NPA */

__bdk_fpa_state_t __bdk_fpa_node_state[BDK_NUMA_MAX_NODES];

void* (*bdk_fpa_alloc)(bdk_node_t node, int aura);
void (*__bdk_fpa_raw_free)(bdk_node_t node, uint64_t address, int aura, int num_cache_lines);
int (*bdk_fpa_fill_pool)(bdk_node_t node, bdk_fpa_pool_t pool, int num_blocks);
int (*bdk_fpa_init_aura)(bdk_node_t node, int aura, bdk_fpa_pool_t pool, int num_blocks, uint64_t fc_addr);

/**
 * Global FPA initialization
 *
 * @return Zero on success, negative on failure
 */
int bdk_fpa_init(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
    {
        extern int __bdk_fpa_init(bdk_node_t node);
        return __bdk_fpa_init(node);
    }
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        extern int __bdk_npa_init(bdk_node_t node);
        return __bdk_npa_init(node);
    }
    /* No FPA or NPA */
    return 0;
}

