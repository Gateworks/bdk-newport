/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for reading Cavium chip fuses.
 *
 * <hr>$Revision: 49448 $<hr>
 */


/**
 * Read a single fuse bit
 *
 * @param fuse   Fuse number (0-1024)
 *
 * @return fuse value: 0 or 1
 */
extern int bdk_fuse_read(bdk_node_t node, int fuse);

/**
 * Read a range of fuses
 *
 * @param node   Node to read from
 * @param fuse   Fuse number
 * @param width  Number of fuses to read, max of 64
 *
 * @return Fuse value
 */
extern uint64_t bdk_fuse_read_range(bdk_node_t node, int fuse, int width);

/**
 * Soft blow a fuse. Soft blown fuses keep there new value over soft resets, but
 * not power cycles.
 *
 * @param node   Node to blow
 * @param fuse   Fuse to blow
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_fuse_soft_blow(bdk_node_t node, int fuse);

/**
 * Read a single fuse bit from the field set (FUSF)
 *
 * @param fuse   Fuse number (0-1024)
 *
 * @return fuse value: 0 or 1
 */
extern int bdk_fuse_field_read(bdk_node_t node, int fuse);

/**
 * Soft blow a fuse in the field set (FUSF). Soft blown fuses
 * keep there new value over soft resets, but not power cycles.
 *
 * @param node   Node to blow
 * @param fuse   Fuse to blow
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_fuse_field_soft_blow(bdk_node_t node, int fuse);

/**
 * Hard blow fuses in the field set (FUSF). Up to 128 fuses in a bank
 * are blown at the same time
 *
 * @param node       Node to blow
 * @param start_fuse First fuses to blow. Must be on a 128 bit boundary.
 *                   This fuse is blown to match the LSB of fuse 0.
 * @param fuses0     First 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses0 maps to start_fuse. MSB of fuses0 maps to
 *                   (start_fuse + 63).
 * @param fuses1     Second 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses1 maps to (start_fuse + 64). MSB of fuses1
 *                   maps to (start_fuse + 127).
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_fuse_field_hard_blow(bdk_node_t node, int start_fuse, uint64_t fuses0, uint64_t fuses1);

