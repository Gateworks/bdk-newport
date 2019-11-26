/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to programming the PCIe SPI flash used for config overrides
 *
 * @addtogroup hal
 * @{
 */

#define BDK_PCIE_FLASH_PREAMBLE 0x9da1
#define BDK_PCIE_FLASH_END      0x6a5d
#define BDK_PCIE_FLASH_MAX_OFFSET 256

/**
 * Determine if access to the PCIe SPI flash is available
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 *
 * @return One if available, zero if not
 */
extern int bdk_pcie_flash_is_available(bdk_node_t node, int pcie_port);

/**
 * Read the specified offset in the PCIe SPI flash and returns its
 * value. In the case the EEPROM isn't there or can't be read -1
 * is returned.
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 * @param offset    Offset in bytes, Must be a multiple of 8
 *
 * @return Value read or -1 if the read failed
 */
extern uint64_t bdk_pcie_flash_read(bdk_node_t node, int pcie_port, int offset);

/**
 * Write a value to the PCIe SPI flash. The value should be of the
 * format bdk_pemx_spi_data_t.
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 * @param offset    Offset to write. Must be a multiple of 8 bytes.
 * @param value     Value to write
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_pcie_flash_write(bdk_node_t node, int pcie_port, int offset, uint64_t value);

/**
 * Erase the PCIe SPI Flash
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_pcie_flash_erase(bdk_node_t node, int pcie_port);

/**
 * Dump the PCIe SPI Flash
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_pcie_flash_dump(bdk_node_t node, int pcie_port);

/** @} */
