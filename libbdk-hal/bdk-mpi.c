/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-mpi.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(MPI);

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
static int mpi_initialize_cn8xxx(bdk_node_t node, int mpi, int clock_rate_hz, bdk_mpi_flags_t flags)
{
    if (clock_rate_hz < 1)
        return -1;
    if (mpi != 0)
    {
        bdk_error("MPI/SPI: Invalid MPI block number %d\n", mpi);
        return -1;
    }

    uint64_t divider = bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / 2 / clock_rate_hz;
    BDK_CSR_DEFINE(mpi_cfg, BDK_MPIX_CFG(mpi));
    mpi_cfg.u = BDK_CSR_READ(bdk_numa_master(), BDK_MPI_CFG);
    mpi_cfg.s.clkdiv = divider;
    mpi_cfg.s.csena3 = (flags & BDK_MPI_FLAGS_ENABLE_CS3) != 0;
    mpi_cfg.s.csena2 = (flags & BDK_MPI_FLAGS_ENABLE_CS2) != 0;
    mpi_cfg.s.csena1 = (flags & BDK_MPI_FLAGS_ENABLE_CS1) != 0;
    mpi_cfg.s.csena0 = (flags & BDK_MPI_FLAGS_ENABLE_CS0) != 0;
    /* mpi_cfg.s.cslate is unchanged */
    mpi_cfg.s.idleclks = (flags & BDK_MPI_FLAGS_IDLE_CLOCKS) != 0;
    mpi_cfg.s.cshi = (flags & BDK_MPI_FLAGS_CS_ACTIVE_HI) != 0;
    mpi_cfg.s.lsbfirst = (flags & BDK_MPI_FLAGS_LSB_FIRST) != 0;
    mpi_cfg.s.wireor = (flags & BDK_MPI_FLAGS_ONE_WIRE) != 0;
    mpi_cfg.s.tritx = mpi_cfg.s.wireor;
    mpi_cfg.s.clk_cont = mpi_cfg.s.idleclks;
    mpi_cfg.s.idlelo = (flags & BDK_MPI_FLAGS_IDLE_LOW) != 0;
    mpi_cfg.s.enable = 1;
    BDK_CSR_WRITE(node, BDK_MPI_CFG, mpi_cfg.u);
    return 0;
}

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
static uint64_t mpi_transfer_cn8xxx(bdk_node_t node, int mpi, int chip_select,
    int leave_cs_enabled, int tx_count, uint64_t tx_data, int rx_count)
{
    const int TIMEOUT = 1000000; /* 1sec */
    const int MAX_PER_TRANSER = 9; /* There are 9 MPI_DAT registers */

    if (tx_count + rx_count > MAX_PER_TRANSER)
    {
        bdk_error("MPI/SPI: TX count plus RX count must not exceed 9\n");
        return -1;
    }

    if (mpi != 0)
    {
        bdk_error("MPI/SPI: Invalid MPI block number %d\n", mpi);
        return -1;
    }

    BDK_CSR_INIT(mpi_cfg, node, BDK_MPI_CFG);
    if (mpi_cfg.s.lsbfirst)
        BDK_CSR_WRITE(node, BDK_MPI_WIDE_DAT, tx_data);
    else
        BDK_CSR_WRITE(node, BDK_MPI_WIDE_DAT, bdk_swap64(tx_data) >> ((8 - tx_count) * 8));

    /* Do the operation */
    BDK_CSR_DEFINE(mpi_tx, BDK_MPI_TX);
    mpi_tx.u = 0;
    mpi_tx.s.csid = chip_select;
    mpi_tx.s.leavecs = leave_cs_enabled;
    mpi_tx.s.txnum = tx_count;
    mpi_tx.s.totnum = tx_count + rx_count;
    BDK_CSR_WRITE(node, BDK_MPI_TX, mpi_tx.u);

    /* Wait for completion */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MPI_STS, busy, ==, 0, TIMEOUT))
    {
        bdk_error("MPI/SPI: Timeout waiting for transaction to complete\n");
        return -1;
    }

    /* Read out the shift data */
    uint64_t result = bdk_cpu_to_be64(BDK_CSR_READ(node, BDK_MPI_WIDE_DAT));
    result >>= (8 - tx_count - rx_count) * 8;
    result &= bdk_build_mask(rx_count * 8);
    return result;
}


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
static int mpi_initialize_cn9xxx(bdk_node_t node, int mpi, int clock_rate_hz, bdk_mpi_flags_t flags)
{
    if (clock_rate_hz < 1)
        return -1;

    uint64_t divider = bdk_clock_get_rate(node, BDK_CLOCK_MAIN_REF) / 2 / clock_rate_hz;
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        divider = 4;

    BDK_CSR_INIT(mpi_cfg, bdk_numa_master(), BDK_MPIX_CFG(mpi));
    mpi_cfg.s.tb100_en = 1; /* Use 100Mhz main reference */
    mpi_cfg.s.cs_espi_en = 0; /* Not using eSPI mode */
    mpi_cfg.s.iomode = BDK_MPI_IOMODE_E_X1_UNIDIR;
    mpi_cfg.s.legacy_dis = 1; /* We don't use legacy mode */
    mpi_cfg.s.clkdiv = divider;
    mpi_cfg.s.csena3 = 1;
    mpi_cfg.s.csena2 = 1;
    mpi_cfg.s.csena1 = 1;
    mpi_cfg.s.csena0 = 1;
    mpi_cfg.s.tritx = (flags & BDK_MPI_FLAGS_ONE_WIRE) != 0;
    mpi_cfg.s.idleclks = (flags & BDK_MPI_FLAGS_IDLE_CLOCKS) != 0;
    mpi_cfg.s.cshi = (flags & BDK_MPI_FLAGS_CS_ACTIVE_HI) != 0;
    mpi_cfg.s.cs_sticky = 1;
    mpi_cfg.s.lsbfirst = (flags & BDK_MPI_FLAGS_LSB_FIRST) != 0;
    mpi_cfg.s.wireor = (flags & BDK_MPI_FLAGS_ONE_WIRE) != 0;
    mpi_cfg.s.clk_cont = mpi_cfg.s.idleclks;
    mpi_cfg.s.idlelo = (flags & BDK_MPI_FLAGS_IDLE_LOW) != 0;
    mpi_cfg.s.enable = 1;
    BDK_CSR_WRITE(node, BDK_MPIX_CFG(mpi), mpi_cfg.u);
    return 0;
}

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
static uint64_t mpi_transfer_cn9xxx(bdk_node_t node, int mpi, int chip_select,
    int leave_cs_enabled, int tx_count, uint64_t tx_data, int rx_count)
{
    const int TIMEOUT = 1000000; /* 1sec */
    const int MAX_PER_TRANSER = 9; /* There are 9 MPI_DAT registers */
    if (tx_count + rx_count > MAX_PER_TRANSER)
    {
        bdk_error("MPI/SPI: TX count plus RX count must not exceed 9\n");
        return -1;
    }
    BDK_CSR_INIT(mpi_cfg, node, BDK_MPIX_CFG(mpi));
    if (mpi_cfg.s.lsbfirst)
        BDK_CSR_WRITE(node, BDK_MPIX_WIDE_BUFX(mpi, 0), tx_data);
    else
        BDK_CSR_WRITE(node, BDK_MPIX_WIDE_BUFX(mpi, 0), bdk_swap64(tx_data) >> ((8 - tx_count) * 8));

    /* Do the operation */
    BDK_CSR_DEFINE(mpi_tx, BDK_MPIX_XMIT(mpi));
    mpi_tx.u = 0;
    mpi_tx.s.csid = chip_select;
    mpi_tx.s.leavecs = leave_cs_enabled;
    mpi_tx.s.txnum = tx_count;
    mpi_tx.s.totnum = tx_count + rx_count;
    BDK_CSR_WRITE(node, BDK_MPIX_XMIT(mpi), mpi_tx.u);

    /* Wait for completion */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MPIX_STS(mpi), busy, ==, 0, TIMEOUT))
    {
        bdk_error("MPI/SPI: Timeout waiting for transaction to complete\n");
        return -1;
    }

    /* Read out the shift data */
    uint64_t result = bdk_cpu_to_be64(BDK_CSR_READ(node, BDK_MPIX_WIDE_BUFX(mpi, 0)));
    result >>= (8 - tx_count - rx_count) * 8;
    result &= bdk_build_mask(rx_count * 8);
    return result;
}

/**
 * Return the number of MPI/SPI controllers
 *
 * @param node   Node to query
 *
 * @return Number of controllers
 */
int bdk_mpi_get_controllers(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 1;
    else if (bdk_is_model(OCTEONTX_CN96XX))
        return 2;
    else if (bdk_is_model(OCTEONTX_CNF95XX))
        return 2;
    else if (bdk_is_model(OCTEONTX_LOKI))
        return 2;
    else if (bdk_is_model(OCTEONTX_CN98XX))
        return 2;
    else
    {
        bdk_error("MPI: Update bdk_mpi_get_controllers() for this chip\n");
        return 0;
    }
}

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
int bdk_mpi_initialize(bdk_node_t node, int mpi, int clock_rate_hz, bdk_mpi_flags_t flags)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return mpi_initialize_cn8xxx(node, mpi, clock_rate_hz, flags);
    else
        return mpi_initialize_cn9xxx(node, mpi, clock_rate_hz, flags);
}

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
uint64_t bdk_mpi_transfer(bdk_node_t node, int mpi, int chip_select,
    int leave_cs_enabled, int tx_count, uint64_t tx_data, int rx_count)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return mpi_transfer_cn8xxx(node, mpi, chip_select, leave_cs_enabled, tx_count, tx_data, rx_count);
    else
        return mpi_transfer_cn9xxx(node, mpi, chip_select, leave_cs_enabled, tx_count, tx_data, rx_count);
}

