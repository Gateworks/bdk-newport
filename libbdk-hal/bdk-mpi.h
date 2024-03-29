/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the SPI / MPI bus
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

typedef enum
{
    BDK_MPI_FLAGS_ENABLE_CS0    = 1<<0, /**< Chip select 0 will be needed */
    BDK_MPI_FLAGS_ENABLE_CS1    = 1<<1, /**< Chip select 1 will be needed */
    BDK_MPI_FLAGS_ENABLE_CS2    = 1<<2, /**< Chip select 2 will be needed */
    BDK_MPI_FLAGS_ENABLE_CS3    = 1<<3, /**< Chip select 3 will be needed */
    BDK_MPI_FLAGS_CS_ACTIVE_HI  = 1<<4, /**< Chip select is active high, else active low */
    BDK_MPI_FLAGS_ONE_WIRE      = 1<<5, /**< Input and output are multiplexed over SPI_DO */
    BDK_MPI_FLAGS_IDLE_CLOCKS   = 1<<7, /**< Continue to clock between commands */
    BDK_MPI_FLAGS_IDLE_LOW      = 1<<8, /**< Clear the clock is idle high, Set the clock is idle low */
    BDK_MPI_FLAGS_LSB_FIRST     = 1<<9, /**< Set to shift the LSB first, otherwise MSB will shift first */
} bdk_mpi_flags_t;

/**
 * Return the number of MPI/SPI controllers
 *
 * @param node   Node to query
 *
 * @return Number of controllers
 */
extern int bdk_mpi_get_controllers(bdk_node_t node);

/**
 * Initialize MPI/SPI for use. The different configuration
 * options are encoded as bitmask inside the flags parameter.
 *
 * @param node   Numa node to use
 * @param mpi    Which MPI block to use. CN8XXX only supports one and requires this to be zero
 * @param clock_rate_hz
 *               Clock rate in Hz (1-16M)
 * @param flags  Setup flags ORed together
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_mpi_initialize(bdk_node_t node, int mpi, int clock_rate_hz, bdk_mpi_flags_t flags);

/**
 * Perform a SPI/MPI transfer. The transfer can contain tx_count
 * bytes that are transferred out, followed by rx_count bytes
 * that are read in. Both tx_count and rx_count may be zero if
 * no transfer is needed. Transmit data is sent most significant
 * byte first, unless BDK_MPI_FLAGS_LSB_FIRST is set. Receive data
 * is in the return value with the last byte in the least
 * signnificant byte.
 *
 * @param node     Numa node to use
 * @param mpi      Which MPI block to use. CN8XXX only supports one and requires this to be zero
 * @param chip_select
 *                 Which chip select to enable during the transfer
 * @param leave_cs_enabled
 *                 Leave the chip select assert after the transaction. Normally can
 *                 be zero. Set to non zero if you want to perform repeated
 *                 transactions.
 * @param tx_count Number of bytes to transfer before startng the rx/shift data.
 *                 Can be zero.
 * @param tx_data  Data to transmit. The low order bytes are used for the data. Order
 *                 of shift out is controlled by BDK_MPI_FLAGS_LSB_FIRST
 * @param rx_count Number of bytes to read. These bytes will be in the return value
 *                 least significant bytes
 *
 * @return Read data
 */
extern uint64_t bdk_mpi_transfer(bdk_node_t node, int mpi, int chip_select,
    int leave_cs_enabled, int tx_count, uint64_t tx_data, int rx_count);

/** @} */
