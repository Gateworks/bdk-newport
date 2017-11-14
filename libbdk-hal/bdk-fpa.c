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

/* Global variables for FPA / NPA */

__bdk_fpa_state_t __bdk_fpa_node_state[BDK_NUMA_MAX_NODES];

void* (*bdk_fpa_alloc)(bdk_node_t node, int aura);
void (*__bdk_fpa_raw_free)(bdk_node_t node, uint64_t address, int aura, int num_cache_lines);
int (*bdk_fpa_fill_pool)(bdk_node_t node, bdk_fpa_pool_t pool, int num_blocks);
int (*bdk_fpa_init_aura)(bdk_node_t node, int aura, bdk_fpa_pool_t pool, int num_blocks);

/**
 * Global FPA initialization
 *
 * @return Zero on success, negative on failure
 */
int bdk_fpa_init(bdk_node_t node)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
    {
        extern int __bdk_fpa_init(bdk_node_t node);
        return __bdk_fpa_init(node);
    }
    if (CAVIUM_IS_MODEL(CAVIUM_CN93XX))
    {
        extern int __bdk_npa_init(bdk_node_t node);
        return __bdk_npa_init(node);
    }
    /* No FPA or NPA */
    return 0;
}

