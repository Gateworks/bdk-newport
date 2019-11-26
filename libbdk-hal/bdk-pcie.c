/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pcierc.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(PCIE);

extern const __bdk_pcie_ops_t pcie_ops_cn8xxx;
extern const __bdk_pcie_ops_t pcie_ops_cn9xxx;

static const __bdk_pcie_ops_t* get_ops()
{
    static const __bdk_pcie_ops_t *ops = NULL;
    if (ops == NULL)
    {
        if (bdk_is_model(OCTEONTX_CN8XXX))
            ops = &pcie_ops_cn8xxx;
        else
            ops = &pcie_ops_cn9xxx;
    }
    return ops;
}

/**
 * Return the number of possible PCIe ports on a node. The actual number
 * of configured ports may be less and may also be disjoint.
 *
 * @param node   Node to query
 *
 * @return Number of PCIe ports that are possible
 */
int bdk_pcie_get_num_ports(bdk_node_t node)
{
    return get_ops()->get_num_ports(node);
}

/**
 * Return the Core physical base address for PCIe MEM access. Memory is
 * read/written as an offset from this address.
 *
 * @param node      Node to use in a Numa setup
 * @param pcie_port PCIe port the memory is on
 * @param mem_type  Type of memory
 *
 * @return 64bit physical address for read/write
 */
uint64_t bdk_pcie_get_base_address(bdk_node_t node, int pcie_port, bdk_pcie_mem_t mem_type)
{
    return get_ops()->get_base_address(node, pcie_port, mem_type);
}

/**
 * Size of the Mem address region returned at address
 * bdk_pcie_get_base_address()
 *
 * @param node      Node to use in a Numa setup
 * @param pcie_port PCIe port the IO is for
 * @param mem_type  Type of memory
 *
 * @return Size of the Mem window
 */
uint64_t bdk_pcie_get_base_size(bdk_node_t node, int pcie_port, bdk_pcie_mem_t mem_type)
{
    return get_ops()->get_base_size(node, pcie_port, mem_type);
}

/**
 * Check if the PCIe port is already initialized and up for use in host(RC) mode.
 *
 * @param node      Node to use in a Numa setup. Can be an exact ID or a special
 *                  value.
 * @param pcie_port PCIe port to initialize
 *
 * @return Zero if not initialized, negative if not available, positive is the width of
 *         the link
 */
int64_t bdk_pcie_is_rc_initialized(bdk_node_t node, int pcie_port)
{
    /* Find which QLM/DLM is associated with this PCIe port */
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    if (qlm < 0)
    {
        bdk_error("N%d.PCIe%d: Disabled, not connected to a QLM/DLM\n", node, pcie_port);
        return -1;
    }
    return get_ops()->is_rc_initialized(node, pcie_port);
}

/**
 * Initialize a PCIe port for use in host(RC) mode. It doesn't
 * enumerate the bus.
 *
 * @param pcie_port PCIe port to initialize
 *
 * @return Zero on success
 */
int bdk_pcie_rc_initialize(bdk_node_t node, int pcie_port)
{
    /* Find which QLM/DLM is associated with this PCIe port */
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    if (qlm < 0)
    {
        bdk_error("N%d.PCIe%d: Disabled, not connected to a QLM/DLM\n", node, pcie_port);
        return -1;
    }
    return get_ops()->rc_initialize(node, pcie_port);
}

/**
 * Shutdown a PCIe port and put it in reset
 *
 * @param pcie_port PCIe port to shutdown
 *
 * @return Zero on success
 */
int bdk_pcie_rc_shutdown(bdk_node_t node, int pcie_port)
{
    return get_ops()->rc_shutdown(node, pcie_port);
}

/**
 * Read 8bits from a Device's config space
 *
 * @param pcie_port PCIe port the device is on
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 *
 * @return Result of the read
 */
uint8_t bdk_pcie_config_read8(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg)
{
    uint64_t address = get_ops()->build_config_addr(node, pcie_port, bus, dev, fn, reg);
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d: Config Read8(bus=%d, dev=%d, fn=%d, reg=0x%x, internal=0x%lx)\n",
        node, pcie_port, bus, dev, fn, reg, address);
    uint8_t result;
    if (address)
        result = bdk_read64_uint8(address);
    else
        result = 0xff;
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d:     Result=0x%02x\n", node, pcie_port, result);
    return result;
}


/**
 * Read 16bits from a Device's config space
 *
 * @param pcie_port PCIe port the device is on
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 *
 * @return Result of the read
 */
uint16_t bdk_pcie_config_read16(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg)
{
    uint64_t address = get_ops()->build_config_addr(node, pcie_port, bus, dev, fn, reg);
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d: Config Read16(bus=%d, dev=%d, fn=%d, reg=0x%x, internal=0x%lx)\n",
        node, pcie_port, bus, dev, fn, reg, address);
    uint16_t result;
    if (address)
        result = bdk_le16_to_cpu(bdk_read64_uint16(address));
    else
        result = 0xffff;
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d:     Result=0x%04x\n", node, pcie_port, result);
    return result;
}


/**
 * Read 32bits from a Device's config space
 *
 * @param pcie_port PCIe port the device is on
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 *
 * @return Result of the read
 */
uint32_t bdk_pcie_config_read32(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg)
{
    uint64_t address = get_ops()->build_config_addr(node, pcie_port, bus, dev, fn, reg);
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d: Config Read32(bus=%d, dev=%d, fn=%d, reg=0x%x, internal=0x%lx)\n",
        node, pcie_port, bus, dev, fn, reg, address);
    uint32_t result;
    if (address)
        result = bdk_le32_to_cpu(bdk_read64_uint32(address));
    else
        result = 0xffffffff;
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d:     Result=0x%08x\n", node, pcie_port, result);

    return result;
}

/**
 * Workarounf Errata 36335, PCIe config space write enables
 *
 * @param node      Node for PCIe
 * @param pcie_port The PCIe port
 * @param reg       Address of register being written
 * @param width_bytes
 *                  Width of the access in bytes
 */
static void pcie_config_write_cn96xx_a0(bdk_node_t node, int pcie_port, int reg, int width_bytes)
{
    if (pcie_port >= 100)
        return;

    /* Step 1: Ensure that PCIERC_RASDP_DE_ME.ERR_MODE is set to 0 */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RASDP_DE_ME(pcie_port),
        c.s.err_mode_en = 0);

    /* Step 2: When we want to do a Cfg Op, set up the following PCIERC
        registers in the PEM that wishes to do the OP
        PCIERC_RAS_EINJ_EN.EINJ0_EN.set(0);
        PCIERC_RAS_EINJ_EN.EINJ1_EN.set(0);
        PCIERC_RAS_EINJ_EN.EINJ2_EN.set(0);
        PCIERC_RAS_EINJ_EN.EINJ3_EN.set(0);
        PCIERC_RAS_EINJ_EN.EINJ4_EN.set(0);
        PCIERC_RAS_EINJ_EN.EINJ5_EN.set(0);
        PCIERC_RAS_EINJ_EN.EINJ6_EN.set(1); */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RAS_EINJ_EN(pcie_port),
        c.s.einj0_en = 0;
        c.s.einj1_en = 0;
        c.s.einj2_en = 0;
        c.s.einj3_en = 0;
        c.s.einj4_en = 0;
        c.s.einj5_en = 0;
        c.s.einj6_en = 1);

    /* Set up error injection count to 1 and set type to TLP and INV_CNTRL
        must be 0
        PCIERC_RAS_EINJ_CTL6PE.EINJ6_PKT_TYP.set(0);
        PCIERC_RAS_EINJ_CTL6PE.EINJ6_INV_CNTRL.set(0);
        PCIERC_RAS_EINJ_CTL6PE.EINJ6_CNT.set(1); */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RAS_EINJ_CTL6PE(pcie_port),
        c.s.einj6_pkt_typ = 0;
        c.s.einj6_inv_cntrl = 0;
        c.s.einj6_cnt = 1);

    /* Set up compare point to compare Fmt/Type field in TLP Header word 0
        Where bits[31:0] = tlp_dw[7:0], tlp_dw[15:18], tlp_dw[23:16], tlp_dw[31:24]
        PCIERC_RAS_EINJ_CTL6CMPP0.EINJ6_COM_PT_H0.set(32'hfe00_0000); */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RAS_EINJ_CTL6CMPP0(pcie_port),
        c.s.einj6_com_pt_h0 = 0xfe000000);

    /* Set up the value to compare against, look for Fmt/Type to indicate
        CfgRd/CfWr - both type 0 or 1
        Where bits[31:0] = tlp_dw[7:0], tlp_dw[15:18], tlp_dw[23:16], tlp_dw[31:24]
        PCIERC_RAS_EINJ_CTL6CMPV0.EINJ6_COM_VAL_H0.set(32'h4400_0000); */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RAS_EINJ_CTL6CMPV0(pcie_port),
        c.s.einj6_com_val_h0 = 0x44000000);

    /* Set up the bit position in TLP Header word 1 to replace (LBE is bits
        7:4, FBE is bits 3:0)
        Where bits[31:0] = tlp_dw[7:0], tlp_dw[15:18], tlp_dw[23:16], tlp_dw[31:24]
        PCIERC_RAS_EINJ_CTL6CHGP1.set(32'h0000_00ff);
        * Note, we could probably just get away with using 32'h0000_000f but
            simulated with 'ff */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RAS_EINJ_CTL6CHGP1(pcie_port),
        c.s.einj6_chg_pt_h1 = 0xff);

    /* Set up the value you'd like to use for FBE (Cfg ops must have LBE==0)
        Where bits[31:0] = tlp_dw[7:0], tlp_dw[15:18], tlp_dw[23:16], tlp_dw[31:24]
        PCIERC_RAS_EINJ_CTL6CHGV1.set(32'h0000_000f); */
    int be;
    switch (width_bytes)
    {
        case 1:
            be = 1 << (reg & 3);
            break;
        case 2:
            be = 3 << (reg & 2);
            break;
        default:
            be = 0xf;
            break;
    }
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RAS_EINJ_CTL6CHGV1(pcie_port),
        c.s.einj6_chg_val_h1 = be);

    /* Please adding the following to disable parity correction at all
        transmit layers of the PCIe core:
        Set PCIERC_RASDP_EP_CTL.EP_DIS_TX to 1  */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_RASDP_EP_CTL(pcie_port),
        c.s.ep_dis_tx = 1);

    /* Make sure all writes are complete */
    BDK_CSR_READ(node, BDK_PCIERCX_RASDP_EP_CTL(pcie_port));
}

/**
 * Write 8bits to a Device's config space
 *
 * @param pcie_port PCIe port the device is on
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 * @param val       Value to write
 */
void bdk_pcie_config_write8(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg, uint8_t val)
{
    uint64_t address = get_ops()->build_config_addr(node, pcie_port, bus, dev, fn, reg);
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d: Config Write8(bus=%d, dev=%d, fn=%d, reg=0x%x, val=0x%02x, internal=0x%lx)\n",
        node, pcie_port, bus, dev, fn, reg, val, address);
    if (address)
    {
        /* Errata 36335: outbound configuration writes have incorrect BEs   */
        if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
            pcie_config_write_cn96xx_a0(node, pcie_port, reg, 1);
        bdk_write64_uint8(address, val);
    }
}


/**
 * Write 16bits to a Device's config space
 *
 * @param pcie_port PCIe port the device is on
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 * @param val       Value to write
 */
void bdk_pcie_config_write16(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg, uint16_t val)
{
    uint64_t address = get_ops()->build_config_addr(node, pcie_port, bus, dev, fn, reg);
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d: Config Write16(bus=%d, dev=%d, fn=%d, reg=0x%x, val=0x%04x, internal=0x%lx)\n",
        node, pcie_port, bus, dev, fn, reg, val, address);
    if (address)
    {
        /* Errata 36335: outbound configuration writes have incorrect BEs   */
        if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
            pcie_config_write_cn96xx_a0(node, pcie_port, reg, 2);
        bdk_write64_uint16(address, bdk_cpu_to_le16(val));
    }
}


/**
 * Write 32bits to a Device's config space
 *
 * @param pcie_port PCIe port the device is on
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 * @param val       Value to write
 */
void bdk_pcie_config_write32(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg, uint32_t val)
{
    uint64_t address = get_ops()->build_config_addr(node, pcie_port, bus, dev, fn, reg);
    BDK_TRACE(PCIE_CONFIG, "N%d.PCIe%d: Config Write32(bus=%d, dev=%d, fn=%d, reg=0x%x, val=0x%08x, internal=0x%lx)\n",
        node, pcie_port, bus, dev, fn, reg, val, address);
    if (address)
    {
        /* Errata 36335: outbound configuration writes have incorrect BEs   */
        if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
            pcie_config_write_cn96xx_a0(node, pcie_port, reg, 4);
        bdk_write64_uint32(address, bdk_cpu_to_le32(val));
    }
}

/**
 * Read 32bits from PCIe using a memory transaction
 *
 * @param node      Node to read from
 * @param pcie_port PCIe port to read
 * @param address   PCIe address to read
 *
 * @return Result of the read
 */
uint32_t bdk_pcie_mem_read32(bdk_node_t node, int pcie_port, uint64_t address)
{
    uint64_t base_address = get_ops()->get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    return bdk_read64_uint32(base_address + address);
}

/**
 * Read 64bits from PCIe using a memory transaction
 *
 * @param node      Node to read from
 * @param pcie_port PCIe port to read
 * @param address   PCIe address to read
 *
 * @return Result of the read
 */
uint64_t bdk_pcie_mem_read64(bdk_node_t node, int pcie_port, uint64_t address)
{
    uint64_t base_address = get_ops()->get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    return bdk_read64_uint64(base_address + address);
}

/**
 * Write 32bits to PCIe memory
 *
 * @param node      Node to write to
 * @param pcie_port PCIe port to use
 * @param address   Address to write
 * @param data      Data to write
 */
void bdk_pcie_mem_write32(bdk_node_t node, int pcie_port, uint64_t address, uint64_t data)
{
    uint64_t base_address = get_ops()->get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    bdk_write64_uint32(base_address + address, data);
}

/**
 * Write 64bits to PCIe memory
 *
 * @param node      Node to write to
 * @param pcie_port PCIe port to use
 * @param address   Address to write
 * @param data      Data to write
 */
void bdk_pcie_mem_write64(bdk_node_t node, int pcie_port, uint64_t address, uint64_t data)
{
    uint64_t base_address = get_ops()->get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    bdk_write64_uint64(base_address + address, data);
}

