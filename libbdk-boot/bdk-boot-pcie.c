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

/**
 * Check if the PCIe SPI flash needs to be programmed
 *
 * @param node      Node to check
 * @param pcie_port PCIe port to check
 */
void bdk_boot_pcie_flash(bdk_node_t node, int pcie_port)
{
    int MAX_FLASH_ENTRIES = BDK_PCIE_FLASH_MAX_OFFSET/8 - 1;
    int entries = 0;
    bdk_pemx_spi_data_t spi_data[MAX_FLASH_ENTRIES];

    int blob_length = 0;
    const char *blob = bdk_config_get_blob(&blob_length, BDK_CONFIG_PCIE_FLASH, node, pcie_port);
    if (!blob)
        return;

    /* If the SPI flash isn't available it will likely be later. All
       we need is access to it once to program it */
    if (!bdk_pcie_flash_is_available(node, pcie_port))
        return;

    const char *done = blob + blob_length;
    const char *str = blob;
    while (str < done)
    {
        BDK_TRACE(INIT, "N%d.PCIe%d: Parsing %s\n", node, pcie_port, str);
        /* Check for the special case of erase */
        if (strcmp(str, "erase") == 0)
        {
            BDK_TRACE(INIT, "N%d.PCIe%d: Erasing SPI flash\n", node, pcie_port);
            bdk_pcie_flash_erase(node, pcie_port);
            return;
        }
        else
        {
            if (entries >= MAX_FLASH_ENTRIES)
            {
                bdk_error("Too many entries: %s\n", str);
                break;
            }
            /* Read the parameters from the write */
            int cs2 = 0;
            uint32_t address = 0;
            uint32_t data = 0;
            int count = sscanf(str, "%i,%i,%i", &cs2, &address, &data);
            if (count != 3)
            {
                bdk_error("Parsing PCIe flash write failed: %s\n", str);
                break;
            }

            /* Add the write */
            spi_data[entries].u = 0;
            spi_data[entries].s.preamble = BDK_PCIE_FLASH_PREAMBLE;
            spi_data[entries].s.cs2 = cs2;
            spi_data[entries].s.adr = address;
            spi_data[entries].s.data = data;
            entries++;
        }

        /* Move to the next string */
        str += strlen(str) + 1;
    }

    spi_data[entries].u = -1;
    spi_data[entries].s.preamble = BDK_PCIE_FLASH_END;
    entries++;
    BDK_TRACE(INIT, "N%d.PCIe%d: SPI flash should have %d entries\n",
        node, pcie_port, entries);

    bool need_flash = false;
    for (int i = 0; i < entries; i++)
    {
        uint64_t data = bdk_pcie_flash_read(node, pcie_port, i * 8);
        BDK_TRACE(INIT, "N%d.PCIe%d: SPI flash [0x%02x]0x%016lx, expected 0x%016lx\n",
            node, pcie_port, i * 8, data, spi_data[i].u);
        if (data != spi_data[i].u)
        {
            need_flash = true;
            BDK_TRACE(INIT, "N%d.PCIe%d: SPI flash needs update\n", node, pcie_port);
            break;
        }
    }

    if (need_flash)
    {
        BDK_TRACE(INIT, "N%d.PCIe%d: Erasing SPI flash\n", node, pcie_port);
        if (bdk_pcie_flash_erase(node, pcie_port))
            return;
        for (int i = 0; i < entries; i++)
        {
            BDK_TRACE(INIT, "N%d.PCIe%d: Write SPI flash [0x%02x]0x%016lx\n",
                node, pcie_port, i*8, spi_data[i].u);
            if (bdk_pcie_flash_write(node, pcie_port, i * 8, spi_data[i].u))
                return;
        }
        BDK_TRACE(INIT, "N%d.PCIe%d: SPI flash update complete\n", node, pcie_port);
    }
    else
        BDK_TRACE(INIT, "N%d.PCIe%d: SPI flash OK\n", node, pcie_port);
}

/**
 * Configure PCIe on all nodes as part of booting
 */
void bdk_boot_pcie(void)
{
    /* Initialize PCIe and bring up the link */
    for (bdk_node_t n = BDK_NODE_0; n < BDK_NUMA_MAX_NODES; n++)
    {
        if (bdk_numa_exists(n))
        {
            for (int p = 0; p < bdk_pcie_get_num_ports(n); p++)
            {
                /* Only init PCIe that are attached to QLMs */
                if (bdk_qlm_get(n, BDK_IF_PCIE, p, 0) != -1)
                {
                    BDK_TRACE(INIT, "Initializing PCIe%d on Node %d\n", p, n);
                    bdk_pcie_rc_initialize(n, p);
                }
            } 
        }
    }

    /* Initialize PCIe SPI flash */
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
    {
        for (bdk_node_t n = BDK_NODE_0; n < BDK_NUMA_MAX_NODES; n++)
        {
            if (bdk_numa_exists(n))
            {
                for (int p = 0; p < bdk_pcie_get_num_ports(n); p++)
                {
                    /* Only init PCIe that are attached to QLMs */
                    if (bdk_qlm_get(n, BDK_IF_PCIE, p, 0) != -1)
                    {
                        /* CN83XX Only support flash on PEM0 or PEM2 */
                        if ((p == 0) || (p == 2))
                            bdk_boot_pcie_flash(n, p);
                    }
                }
            }
        }
    }
}
