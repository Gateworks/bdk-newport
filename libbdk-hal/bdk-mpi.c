/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
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
 * @param clock_rate_hz
 *               Clock rate in Hz (1-16M)
 * @param flags  Setup flags ORed together
 *
 * @return Zero on success, negative on failure
 */
int bdk_mpi_initialize(bdk_node_t node, int clock_rate_hz, bdk_mpi_flags_t flags)
{
    if (clock_rate_hz < 1)
        return -1;

    uint64_t divider = bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / 2 / clock_rate_hz;

    BDK_CSR_DEFINE(mpi_cfg, BDK_MPIX_CFG(0));
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        mpi_cfg.u = BDK_CSR_READ(bdk_numa_master(), BDK_MPI_CFG);
    else
        mpi_cfg.u = BDK_CSR_READ(bdk_numa_master(), BDK_MPIX_CFG(0));
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        BDK_CSR_WRITE(node, BDK_MPI_CFG, mpi_cfg.u);
    else
        BDK_CSR_WRITE(node, BDK_MPIX_CFG(0), mpi_cfg.u);
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
uint64_t bdk_mpi_transfer(bdk_node_t node, int chip_select,
    int leave_cs_enabled, int tx_count, uint64_t tx_data, int rx_count)
{
    const int TIMEOUT = 1000000; /* 1sec */
    const int MAX_PER_TRANSER = 9; /* There are 9 MPI_DAT registers */
    if (tx_count + rx_count > MAX_PER_TRANSER)
    {
        bdk_error("MPI/SPI: TX count plus RX count must not exceed 9\n");
        return -1;
    }
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
    {
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
    else
    {
        BDK_CSR_INIT(mpi_cfg, node, BDK_MPIX_CFG(0));
        if (mpi_cfg.s.lsbfirst)
            BDK_CSR_WRITE(node, BDK_MPIX_WIDE_DAT(0), tx_data);
        else
            BDK_CSR_WRITE(node, BDK_MPIX_WIDE_DAT(0), bdk_swap64(tx_data) >> ((8 - tx_count) * 8));

        /* Do the operation */
        BDK_CSR_DEFINE(mpi_tx, BDK_MPIX_TX(0));
        mpi_tx.u = 0;
        mpi_tx.s.csid = chip_select;
        mpi_tx.s.leavecs = leave_cs_enabled;
        mpi_tx.s.txnum = tx_count;
        mpi_tx.s.totnum = tx_count + rx_count;
        BDK_CSR_WRITE(node, BDK_MPIX_TX(0), mpi_tx.u);

        /* Wait for completion */
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MPIX_STS(0), busy, ==, 0, TIMEOUT))
        {
            bdk_error("MPI/SPI: Timeout waiting for transaction to complete\n");
            return -1;
        }

        /* Read out the shift data */
        uint64_t result = bdk_cpu_to_be64(BDK_CSR_READ(node, BDK_MPIX_WIDE_DAT(0)));
        result >>= (8 - tx_count - rx_count) * 8;
        result &= bdk_build_mask(rx_count * 8);
        return result;
    }
}

