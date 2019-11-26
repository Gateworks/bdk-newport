/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Boot services for DRAM
 *
 * @addtogroup boot
 * @{
 */

/**
 * Configure DRAM on a specific node
 *
 * @param node   Node to configure
 * @param override_for_speed
 *               If non-zero, the DRAM init code will use this for the
 *               DRAM clock speed. This is used for SLT and should not
 *               be used otherwise.
 */
extern void bdk_boot_dram(bdk_node_t node, int override_for_speed);

/** @} */
