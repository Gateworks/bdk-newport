/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the VRM.
 *
 * @addtogroup hal
 * @{
 */

/**
 * Initialize the VRM
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_vrm_initialize(bdk_node_t node);

/**
 * The VRM may be reporting temperature or other issues with the system. Poll the
 * VRM and handle any throttling or other actions needed.
 *
 * @param node   Node to poll
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_vrm_poll(bdk_node_t node);

/** @} */
