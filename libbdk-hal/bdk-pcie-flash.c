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
#include "libbdk-arch/bdk-csrs-pem.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(PCIE_EEPROM);

#define STATUS_SRWD 0x80/* Bit 7 is Status Register Write Protect */
#define STATUS_BP2 0x10 /* Bit 4 is Block Protect 2 */
#define STATUS_BP1 0x08 /* Bit 3 is Block Protect 1 */
#define STATUS_BP0 0x04 /* Bit 2 is Block Protect 0 */
#define STATUS_WEL 0x02 /* Bit 1 is Write Enable Latch */
#define STATUS_WIP 0x01 /* Bit 0 is Write In Progress */

/**
 * Determine if access to the PCIe SPI flash is available
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 *
 * @return One if available, zero if not
 */
int bdk_pcie_flash_is_available(bdk_node_t node, int pcie_port)
{
    /* PEM needs to be on and out of reset */
    BDK_CSR_INIT(pemx_on, node, BDK_PEMX_ON(pcie_port));
    if (!pemx_on.s.pemon || !pemx_on.s.pemoor)
        return 0;
    /* PEM needs to be in EP mode */
    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(pcie_port));
    if (pemx_cfg.cn83xx.hostmd)
        return 0;
    /* For CN83XX, PEM0 must not be in EP mode for PEM1 to use flash */
    if (pcie_port != 0)
    {
        BDK_CSR_INIT(pem0_on, node, BDK_PEMX_ON(0));
        if (pem0_on.s.pemon && pem0_on.s.pemoor)
        {
            BDK_CSR_INIT(pemx_cfg0, node, BDK_PEMX_CFG(0));
            if (!pemx_cfg0.cn83xx.hostmd)
                return 0;
        }
    }
    return 1;
}

/**
 * Read the status register
 *
 * @param node      Node to read from
 * @param pcie_port PCIe port
 *
 * @return Status of the flash
 */
static int __bdk_pcie_flash_status(bdk_node_t node, int pcie_port)
{
    /* Make sure the interface is idle before we start */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash status: PEMX_SPI_CTL[start_busy] is stuck on\n", node, pcie_port);
        return -1;
    }

    /* Issue the read status */
    bdk_pemx_spi_ctl_t spi_ctl;
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x5; /* RDSR */
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 100ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 100000))
    {
        bdk_error("N%d.PCIe%d: Flash status: timeout\n", node, pcie_port);
        return -1;
    }

    /* Return the result */
    return BDK_CSR_READ(node, BDK_PEMX_SPI_DATA(pcie_port)) & 0xff;
}

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
uint64_t bdk_pcie_flash_read(bdk_node_t node, int pcie_port, int offset)
{
    if (!bdk_pcie_flash_is_available(node, pcie_port))
        return -1;

    /* Make sure the interface is idle before we start */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash read: PEMX_SPI_CTL[start_busy] is stuck on\n", node, pcie_port);
        return -1;
    }

    /* Make sure a write isn't in progress */
    int status = __bdk_pcie_flash_status(node, pcie_port);
    if (status & STATUS_WIP)
    {
        bdk_error("N%d.PCIe%d: Flash read: Write in Progress\n", node, pcie_port);
        return -1;
    }

    /* Issue the read */
    bdk_pemx_spi_ctl_t spi_ctl;
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x3; /* Read */
    spi_ctl.s.adr = offset;
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 100ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 100000))
    {
        bdk_error("N%d.PCIe%d: Flash read: timeout\n", node, pcie_port);
        return -1;
    }

    /* Return the result */
    return BDK_CSR_READ(node, BDK_PEMX_SPI_DATA(pcie_port));
}

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
int bdk_pcie_flash_write(bdk_node_t node, int pcie_port, int offset, uint64_t value)
{
    bdk_pemx_spi_ctl_t spi_ctl;

    if (!bdk_pcie_flash_is_available(node, pcie_port))
        return -1;

    /* Make sure the interface is idle before we start */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash write: PEMX_SPI_CTL[start_busy] is stuck on\n", node, pcie_port);
        return -1;
    }

    /* Make sure a write isn't in progress */
    int status = __bdk_pcie_flash_status(node, pcie_port);
    if (status & STATUS_WIP)
    {
        bdk_error("N%d.PCIe%d: Flash read: Write in Progress before call\n", node, pcie_port);
        return -1;
    }

    /* Enable writes to the EEPROM */
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x6; /* Write enable */
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 10ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash write: Timeout on write enable\n", node, pcie_port);
        return -1;
    }

    /* Make sure a Write Enable is latched */
    status = __bdk_pcie_flash_status(node, pcie_port);
    if ((status & STATUS_WEL) == 0)
    {
        bdk_error("N%d.PCIe%d: Flash write: Write Enable Latch failed\n", node, pcie_port);
        return -1;
    }

    /* Setup the data */
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_DATA(pcie_port), value);
    BDK_CSR_READ(node, BDK_PEMX_SPI_DATA(pcie_port));

    /* Perform the write */
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x2; /* Write */
    spi_ctl.s.adr = offset;
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 100ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 100000))
    {
        bdk_error("N%d.PCIe%d: Flash write: Timeout on write\n", node, pcie_port);
        return -1;
    }

    /* Wait for write to complete */
    status = __bdk_pcie_flash_status(node, pcie_port);
    while (status & STATUS_WIP)
    {
        bdk_wait_usec(1000);
        status = __bdk_pcie_flash_status(node, pcie_port);
    }

    /* Disable writes to the EEPROM */
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x4; /* Write disable */
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 10ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash write: Timeout on write disable\n", node, pcie_port);
        return -1;
    }

    /* All done */
    return 0;
}

/**
 * Erase the PCIe SPI Flash
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 *
 * @return Zero on success, negative on failure
 */
int bdk_pcie_flash_erase(bdk_node_t node, int pcie_port)
{
    bdk_pemx_spi_ctl_t spi_ctl;

    /* Make sure the interface is idle before we start */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash erase: PEMX_SPI_CTL[start_busy] is stuck on\n", node, pcie_port);
        return -1;
    }

    /* Make sure a write isn't in progress */
    int status = __bdk_pcie_flash_status(node, pcie_port);
    if (status & STATUS_WIP)
    {
        bdk_error("N%d.PCIe%d: Flash read: Write in Progress before call\n", node, pcie_port);
        return -1;
    }

    /* Enable writes to the EEPROM */
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x6; /* Write enable */
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 10ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash erase: Timeout on write enable\n", node, pcie_port);
        return -1;
    }

    /* Make sure a Write Enable is latched */
    status = __bdk_pcie_flash_status(node, pcie_port);
    if ((status & STATUS_WEL) == 0)
    {
        bdk_error("N%d.PCIe%d: Flash erase: Write Enable Latch failed\n", node, pcie_port);
        return -1;
    }

    /* Perform the erase */
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0xd8; /* Sector erase */
    spi_ctl.s.adr = 0;
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 100ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 100000))
    {
        bdk_error("N%d.PCIe%d: Flash erase: Timeout on write\n", node, pcie_port);
        return -1;
    }

    /* Wait for erase to complete */
    status = __bdk_pcie_flash_status(node, pcie_port);
    while (status & STATUS_WIP)
    {
        bdk_wait_usec(1000);
        status = __bdk_pcie_flash_status(node, pcie_port);
    }

    /* Disable writes to the EEPROM */
    spi_ctl.u = 0;
    spi_ctl.s.start_busy = 1;
    spi_ctl.s.cmd = 0x4; /* Write disable */
    BDK_CSR_WRITE(node, BDK_PEMX_SPI_CTL(pcie_port), spi_ctl.u);

    /* Wait for complete, up to 10ms */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_SPI_CTL(pcie_port), start_busy, ==, 0, 10000))
    {
        bdk_error("N%d.PCIe%d: Flash erase: Timeout on write disable\n", node, pcie_port);
        return -1;
    }

    /* All done */
    return 0;
}

/**
 * Dump the PCIe SPI Flash
 *
 * @param node      Numa node request is for
 * @param pcie_port PCIe port to access
 *
 * @return Zero on success, negative on failure
 */
int bdk_pcie_flash_dump(bdk_node_t node, int pcie_port)
{
    if (!bdk_pcie_flash_is_available(node, pcie_port))
    {
        bdk_error("N%d.PCIe%d: PEM not enabled\n", node, pcie_port);
        return -1;
    }

    for (int offset = 0; offset < BDK_PCIE_FLASH_MAX_OFFSET; offset+=8)
    {
        bdk_pemx_spi_data_t data;
        data.u = bdk_pcie_flash_read(node, pcie_port, offset);
        printf("%02x: Preamble: 0x%04x CS2: %d Address:0x%04x Data: 0x%08x (0x%016lx)\n",
            offset, data.s.preamble, data.s.cs2, data.s.adr, data.s.data, data.u);
        if (data.u == (uint64_t)-1)
            break;
    }
    return 0;
}

