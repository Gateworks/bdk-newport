/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the MMC, eMMC, or SD
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/**
 * Initialize a MMC for read/write
 *
 * @author creese (10/14/2013)
 * @param chip_sel Chip select to use
 *
 * @return Size of the SD card, zero on failure
 */
extern int64_t bdk_mmc_initialize(bdk_node_t node, int chip_sel);

/**
 * Read blocks from a MMC card
 *
 * @author creese (10/14/2013)
 * @param node     Node to access
 * @param chip_sel Chip select to use
 * @param address  Offset into the card in bytes. Must be a multiple of 512
 * @param buffer   Buffer to read into
 * @param length   Length to read in bytes. Must be a multiple of 512
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_mmc_read(bdk_node_t node, int chip_sel, uint64_t address, void *buffer, int length);

/**
 * Write blocks to a MMC card
 *
 * @author creese (10/14/2013)
 * @param node     Node to access
 * @param chip_sel Chip select to use
 * @param address  Offset into the card in bytes. Must be a multiple of 512
 * @param buffer   Buffer to write
 * @param length   Length to write in bytes. Must be a multiple of 512
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_mmc_write(bdk_node_t node, int chip_sel, uint64_t address, const void *buffer, int length);

extern bool bdk_mmc_card_is_sd(bdk_node_t node, int chip_sel);

/** @} */
