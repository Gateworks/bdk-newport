/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>

int __bdk_numa_master_node = -1;    /* Which node is the master */
static int __bdk_numa_exists_mask = 0;     /* Bitmask of nodes that exist */
static bdk_spinlock_t __bdk_numa_lock;

/**
 * Get a bitmask of the nodes that exist
 *
 * @return bitmask
 */
uint64_t bdk_numa_get_exists_mask(void)
{
    return __bdk_numa_exists_mask;
}

/**
 * Add a node to the exists mask
 *
 * @param node   Node to add
 */
void bdk_numa_set_exists(bdk_node_t node)
{
    bdk_spinlock_lock(&__bdk_numa_lock);
    __bdk_numa_exists_mask |= 1 << node;
    if (__bdk_numa_master_node == -1)
        __bdk_numa_master_node = node;
    bdk_spinlock_unlock(&__bdk_numa_lock);
}

/**
 * Return true if a node exists
 *
 * @param node   Node to check
 *
 * @return Non zero if the node exists
 */
int bdk_numa_exists(bdk_node_t node)
{
    return __bdk_numa_exists_mask & (1 << node);
}

/**
 * Return true if there is only one node
 *
 * @return
 */
extern int bdk_numa_is_only_one()
{
    return __bdk_numa_exists_mask == 1;
}

