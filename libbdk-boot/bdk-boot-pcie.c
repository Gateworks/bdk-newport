/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-pcieep.h"

/* Errat 36827 Calibration For EP mode only T96 A0 and A1   */
void bdk_pcie_ep_9xxx_cal_ready_errata_36827(bdk_node_t node, int pcie_port);

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
                    if (bdk_is_model(OCTEONTX_CN9XXX))
                    {
                        BDK_CSR_INIT(pemx_cfg, n, BDK_PEMX_CFG(p));
                        if (pemx_cfg.cn9.hostmd)
                        {
                            BDK_TRACE(INIT, "Initializing PCIe%d on Node %d\n", p, n);
                            bdk_pcie_rc_initialize(n, p);
                        }
                        else
                        {
                            int sriov_bar0_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, 0, BDK_NODE_0, p);
                            if (sriov_bar0_bits == -1)
                                sriov_bar0_bits = 20; /* 1MB */
                            int sriov_bar2_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, 2, BDK_NODE_0, p);
                            if (sriov_bar2_bits == -1)
                                sriov_bar2_bits = 0; /* Disabled */
                            int sriov_bar4_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, 4, BDK_NODE_0, p);
                            if (sriov_bar4_bits == -1)
                                sriov_bar4_bits = 0; /* Disabled */
                            int pf_bar0_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_BAR_SIZE, 0, BDK_NODE_0, p);
                            if (pf_bar0_bits == -1)
                                pf_bar0_bits = 23; /* 8MB */
                            int pf_bar2_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_BAR_SIZE, 2, BDK_NODE_0, p);
                            if (pf_bar2_bits == -1)
                                pf_bar2_bits = 28; /* 256MB */
                            int pf_bar4_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_BAR_SIZE, 4, BDK_NODE_0, p);
                            if (pf_bar4_bits == -1)
                                pf_bar4_bits = 26; /* 64MB */
                            /* Setup remote access from BAR0, BAR2, and BAR4 */
                            BDK_CSR_MODIFY(c, n, BDK_PEMX_BAR_CTL(p),
                                c.cn9.vf_bar4_enb = (sriov_bar4_bits > 0);
                                c.cn9.vf_bar2_enb = (sriov_bar2_bits > 0);
                                c.cn9.vf_bar0_enb = (sriov_bar0_bits > 0);
                                c.cn9.bar4_enb =  (pf_bar4_bits > 0);
                                c.cn9.bar0_siz = pf_bar0_bits - 15; /* 1 = 64KB */
                                c.cn9.bar0_enb = (pf_bar0_bits > 0);
                                c.cn9.bar2_cbit = 0; /* PF BAR2 CAX disabled */
                                c.cn9.bar2_siz = pf_bar2_bits - 20; /* 1 = 1MB */
                                c.cn9.bar4_siz = pf_bar4_bits - 25; /* 1 = 64MB */
                                c.cn9.bar2_enb = (pf_bar2_bits > 0);
                                c.cn9.bar2_cax = 0); /* PF BAR2 Cache in L2 */
                            BDK_CSR_WRITE(n, BDK_PEMX_BAR2_MASK(p),
                                bdk_build_mask(pf_bar2_bits));

                            /* EP ports start out disabled, fix that */
                            BDK_CSR_WRITE(n, BDK_PEMX_DIS_PORT(p), 1);

                           /* Reference Errata: 36827 for 96XX A0, B0 parts (non-rambus)
                            * Impact: Primarily LIO3 boards that operate in EP mode. */
                            if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1))
                                bdk_pcie_ep_9xxx_cal_ready_errata_36827(n, p);
                        }
                    }
                    else
                    {
                        BDK_TRACE(INIT, "Initializing PCIe%d on Node %d\n", p, n);
                        bdk_pcie_rc_initialize(n, p);
                    }
                }
            }
        }
    }

    /* Initialize PCIe SPI flash */
    if (bdk_is_model(OCTEONTX_CN83XX))
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
