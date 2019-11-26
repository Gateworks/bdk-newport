/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-cpc.h"
#include "libbdk-arch/bdk-csrs-key.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(KEY_MEMORY);

static int bdk_key_allocated[BDK_NUMA_MAX_NODES];

/**
 * Get a pointer to KEY memory
 *
 * @param node   Node to get memory for
 * @param key_address
 *               Offset into key memory in bytes
 *
 * @return Pointer to key memory
 */
static volatile uint64_t *get_key_ptr(bdk_node_t node, uint64_t key_address)
{
    if (key_address >= BDK_KEY_MEM_SIZE)
        bdk_error("N%d.KEY: Access invalid key memory offset 0x%lx", node, key_address);
    uint64_t pa;
    if (bdk_is_model(OCTEONTX_CN8XXX))
        pa = bdk_numa_get_address(node, BDK_KEY_MEMX(key_address >> 3));
    else /* 8KB at top of 192KB CPC secure memory */
        pa = bdk_numa_get_address(node, BDK_CPC_RAM_MEMX((0x30000 - 8192 + key_address) >> 3));
    return bdk_phys_to_ptr(pa);
}

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
    return *get_key_ptr(node, address);
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
    *get_key_ptr(node, address) = value;
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
        void *ptr = (void*)get_key_ptr(node, bdk_key_allocated[node]);
        bdk_key_allocated[node] += size_bytes;
        return ptr;
    }
    else
        return NULL;
}

