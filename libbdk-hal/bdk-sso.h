/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the SSO.
 *
 * @addtogroup hal
 * @{
 */

/**
 * Initialize the SSO
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_sso_init(bdk_node_t node);

/**
 * Register a bdk-if handle with the SSO code so the SSO can be used to receive
 * traffic from it.
 *
 * @param handle Handle to register
 */
extern void bdk_sso_register_handle(bdk_if_handle_t handle);

/**
 * Function called during bdk_thread_yield() to process work while we're idle
 */
extern void (*bdk_sso_process_work)(void);

/**
 * Channels is 12 bits in WQE. This contains pointers to 1024 element arrays
 * for each node. They are not allocated until a network interface is required
 * for the node to save space
 */
extern bdk_if_handle_t *bdk_sso_map[BDK_NUMA_MAX_NODES];

/** @} */
