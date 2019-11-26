/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for dealing with multiple chips organized into a
 * NUMA cluster.
 *
 * <hr>$Revision: 49448 $<hr>
 */

/* None of the current chips support multi-node, so allow the
   optimizer to remove processing the node number */
#define BDK_SUPPORT_MULTINODE 0

typedef enum
{
    BDK_NODE_0 = 0,
#if BDK_SUPPORT_MULTINODE
    BDK_NODE_1 = 1,
    BDK_NODE_2 = 2,
    BDK_NODE_3 = 3,
    BDK_NUMA_MAX_NODES = 4
#else
    BDK_NUMA_MAX_NODES = 1
#endif
} bdk_node_t;

/**
 * Return the local node number
 *
 * @return Node number
 */
static inline bdk_node_t bdk_numa_local(void) __attribute__ ((always_inline, pure));
static inline bdk_node_t bdk_numa_local(void)
{
#ifndef BDK_BUILD_HOST
    /* None of the current chips support multi-node, so allow the
       optimizer to remove processing the node number */
    if (BDK_SUPPORT_MULTINODE)
    {
        int mpidr_el1;
        BDK_MRS_NV(MPIDR_EL1, mpidr_el1);
        int result;
        result = (mpidr_el1 >> 16) & 0xff;
        return BDK_NODE_0 + result;
    }
    else
        return BDK_NODE_0;
#else
    return BDK_NODE_0;
#endif
}

/**
 * Return the master node number
 *
 * @return Node number
 */
static inline bdk_node_t bdk_numa_master(void)
{
    /* None of the current chips support multi-node, so allow the
       optimizer to remove processing the node number */
    if (BDK_SUPPORT_MULTINODE)
    {
        extern int __bdk_numa_master_node;
        return __bdk_numa_master_node;
    }
    else
        return BDK_NODE_0;
}

/**
 * Get a bitmask of the nodes that exist
 *
 * @return bitmask
 */
extern uint64_t bdk_numa_get_exists_mask(void);

/**
 * Add a node to the exists mask
 *
 * @param node   Node to add
 */
extern void bdk_numa_set_exists(bdk_node_t node);

/**
 * Return true if a node exists
 *
 * @param node   Node to check
 *
 * @return Non zero if the node exists
 */
extern int bdk_numa_exists(bdk_node_t node);

/**
 * Return true if there is only one node
 *
 * @return
 */
extern int bdk_numa_is_only_one();

/**
 * Given a physical address without a node, return the proper physical address
 * for the given node.
 *
 * @param node   Node to create address for
 * @param pa     Base physical address
 *
 * @return Node specific address
 */
static inline uint64_t bdk_numa_get_address(bdk_node_t node, uint64_t pa) __attribute__((pure,always_inline));
static inline uint64_t bdk_numa_get_address(bdk_node_t node, uint64_t pa)
{
    /* None of the current chips support multi-node, so allow the
       optimizer to remove processing the node number */
    if (BDK_SUPPORT_MULTINODE)
    {
        if (pa & (1ull << 47))
            pa |= (uint64_t)(node&3) << 44;
        else if (bdk_is_model(OCTEONTX_CN8XXX))
            pa |= (uint64_t)(node & 3) << 40; /* CN8XXX uses bits [41:40] for nodes */
        else
            pa |= (uint64_t)(node & 3) << 44; /* CN9XXX uses bits [45:44] for nodes */
    }
    return pa;
}


