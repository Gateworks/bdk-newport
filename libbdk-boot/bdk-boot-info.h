/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for displaying and retrieving infomration about the
 * boot environment
 *
 * @addtogroup boot
 * @{
 */


/**
 * Display information about strapping and other hard configuration items for
 * the specified node
 *
 * @param node   Node to display
 */
void bdk_boot_info_strapping(bdk_node_t node);

/**
 * Return a string containing information about the chip's manufacture wafer
 *
 * @param node   Node to query
 *
 * @return Static string, reused on each call
 */
const char* bdk_boot_info_wafer(bdk_node_t node);

/**
 * Return a string containing the chip's unique serial number
 *
 * @param node   Node to query
 *
 * @return Static string, reused on each call
 */
const char* bdk_boot_info_serial(bdk_node_t node);

/**
 * Return a string containing the chip's unique ID
 *
 * @param node   Node to query
 *
 * @return Static string, reused on each call
 */
const char* bdk_boot_info_unique_id(bdk_node_t node);

/** @} */
