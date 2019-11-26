/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the ECAMs.
 *
 * @addtogroup hal
 * @{
 */

/**
 * Read from an ECAM
 *
 * @param device Device to read from
 * @param reg    Register to read
 *
 * @return Result of the read of -1 on failure
 */
extern uint32_t bdk_ecam_read32(const bdk_device_t *device, int reg);

/**
 * Write to an ECAM register
 *
 * @param device Device to write to
 * @param reg    Register to write
 * @param value  Value to write
 */
extern void bdk_ecam_write32(const bdk_device_t *device, int reg, uint32_t value);

/**
 * Build an ECAM config space request address for a device
 *
 * @param device Device being accessed
 * @param reg    Register to access
 *
 * @return 64bit IO address
 */
extern uint64_t __bdk_ecam_build_address(const bdk_device_t *device, int reg);

/**
 * Return the number of internal ECAMS on a node.
 *
 * @param node   Node to query
 *
 * @return Number of ECAMs available
 */
extern int bdk_ecam_get_num(bdk_node_t node);

/**
 * Scan all ECAMs for devices and add them to bdk-device
 *
 * @param node   Node to scan
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_ecam_scan_all(bdk_node_t node) BDK_WEAK;

/** @} */

