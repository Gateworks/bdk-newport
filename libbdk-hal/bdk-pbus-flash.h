/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * This file provides bootbus flash operations
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

typedef struct
{
    int start_offset;
    int block_size;
    int num_blocks;
} bdk_pbus_flash_region_t;

/**
 * Initialize the flash access library
 */
void bdk_pbus_flash_initialize(bdk_node_t node);

/**
 * Return a pointer to the flash chip
 *
 * @param chip_id Chip ID to return
 * @return Zero if the chip doesn't exist
 */
uint64_t bdk_pbus_flash_get_base(int chip_id);

/**
 * Return the number of erasable regions on the chip
 *
 * @param chip_id Chip to return info for
 * @return Number of regions
 */
int bdk_pbus_flash_get_num_regions(int chip_id);

/**
 * Return information about a flash chips region
 *
 * @param chip_id Chip to get info for
 * @param region  Region to get info for
 * @return Region information
 */
const bdk_pbus_flash_region_t *bdk_pbus_flash_get_region_info(int chip_id, int region);

/**
 * Erase a block on the flash chip
 *
 * @param chip_id Chip to erase a block on
 * @param region  Region to erase a block in
 * @param block   Block number to erase
 * @return Zero on success. Negative on failure
 */
int bdk_pbus_flash_erase_block(int chip_id, int region, int block);

/**
 * Write data to flash. The block must have already been erased. You can call
 * this multiple times on the same block to piecemeal write it.
 *
 * @param chip_id Which flash to write
 * @param offset  Offset into device to start write
 * @param data    Data to write
 * @param len     Length of the data
 *
 * @return Zero on success. Negative on failure
 */
int bdk_pbus_flash_write(int chip_id, int offset, const void *data, int len);

/** @} */
