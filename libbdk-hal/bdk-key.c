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
#include "libbdk-arch/bdk-csrs-key.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(KEY_MEMORY);

static int bdk_key_allocated[BDK_NUMA_MAX_NODES];

/**
 * Read from KEY memory
 *
 * @param node    Which node to use
 * @param address Address (byte) in key memory to read
 *                0 <= address < BDK_KEY_MEM_SIZE
 * @return Value from key memory
 */
uint64_t bdk_key_read(bdk_node_t node, uint64_t address)
{
    return BDK_CSR_READ(node, BDK_KEY_MEMX(address >> 3));
}


/**
 * Write to KEY memory
 *
 * @param node    Which node to use
 * @param address Address (byte) in key memory to write
 *                0 <= address < BDK_KEY_MEM_SIZE
 * @param value   Value to write to key memory
 */
void bdk_key_write(bdk_node_t node, uint64_t address, uint64_t value)
{
    return BDK_CSR_WRITE(node, BDK_KEY_MEMX(address >> 3), value);
}

/**
 * Allocate an area in key memory for storing data. Return a pointer to the
 * memory on success.
 *
 * @param node       Node to allocate on
 * @param size_bytes Number of bytes to allocate
 *
 * @return Pointer to key memory, or NULL on failure
 */
void* bdk_key_alloc(bdk_node_t node, int size_bytes)
{
    if (bdk_key_allocated[node] + size_bytes <= BDK_KEY_MEM_SIZE)
    {
        uint64_t addr = BDK_KEY_MEMX(0) + bdk_key_allocated[node];
        bdk_key_allocated[node] += size_bytes;
        return bdk_phys_to_ptr(bdk_numa_get_address(node, addr));
    }
    else
        return NULL;
}

