/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the on chip key memory. Key memory is
 * 8k on chip that is inaccessible from off chip. It can
 * also be cleared using an external hardware pin.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

#define BDK_KEY_MEM_SIZE 8192  /* Size in bytes */

/**
 * Read from KEY memory
 *
 * @param node    Which node to use
 * @param address Address (byte) in key memory to read
 *                0 <= address < BDK_KEY_MEM_SIZE
 * @return Value from key memory
 */
extern uint64_t bdk_key_read(bdk_node_t node, uint64_t address);

/**
 * Write to KEY memory
 *
 * @param node    Which node to use
 * @param address Address (byte) in key memory to write
 *                0 <= address < BDK_KEY_MEM_SIZE
 * @param value   Value to write to key memory
 */
extern void bdk_key_write(bdk_node_t node, uint64_t address, uint64_t value);

/**
 * Allocate an area in key memory for storing data. Return a pointer to the
 * memory on success.
 *
 * @param node       Node to allocate on
 * @param size_bytes Number of bytes to allocate
 *
 * @return Pointer to key memory, or NULL on failure
 */
extern void* bdk_key_alloc(bdk_node_t node, int size_bytes);

/** @} */
