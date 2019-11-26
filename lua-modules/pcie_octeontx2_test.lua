-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK PCIe tests for an Octeon(CN73XX), OcteonTX(CN83XX), or
-- OcteonTx2(CN96XX) plugged into a PCIe slot

local ID_CN73XX = 0x9700177d -- This card hasn't been tested
local ID_CN83XX = 0xa300177d
local ID_CN96XX = 0xb200177d

require("strict")
require("utils")
local bit64 = require("bit64")
local testmodule = {}

local function setup_octeon_card(pcie_root)
    local function read64(address)
        printf("    PCIe read  PEM%d, address 0x%x, ", pcie_root.port, address)
        local data = octeontx.c.bdk_pcie_mem_read64(pcie_root.node, pcie_root.port, address)
        printf("data 0x%016x\n", data)
        return data
    end
    local function write64(address, data)
        printf("    PCIe write PEM%d, address 0x%x, data 0x%016x\n", pcie_root.port, address, data)
        octeontx.c.bdk_pcie_mem_write64(pcie_root.node, pcie_root.port, address, data)
    end
    -- Get the first PCIe device. There should only be one, a CN73XX or a CN96XX
    local devices = pcie_root:get_devices()
    local device = devices[1]
    assert(device, "Test device not found")
    local id = device:read32(0)
    printf("Device ID: 0x%x\n", id)
    assert((id == ID_CN73XX) or (id == ID_CN83XX) or (id == ID_CN96XX), "Incorrect device found")
    -- Get the location of Octeon's BARs
    -- OcteonTX2's BARs
    local bar_reg -- Register access
    local bar_mem -- Indexed memory access
    local bar_big -- Big direct memory access
    local SLI_WIN_RD_ADDR
    local SLI_WIN_RD_DATA
    local SLI_WIN_WR_ADDR
    local SLI_WIN_WR_DATA
    local SLI_WIN_WR_MASK
    if id == ID_CN73XX then -- Octeon
        printf("    Octeon device\n")
        bar_reg = device:read32(0x10) -- BAR0
        bar_reg = bar_reg + bit64.lshift(device:read32(0x14), 32)
        bar_reg = bit64.band(bar_reg, -16)
        bar_mem = device:read32(0x18) -- BAR1
        bar_mem = bar_mem + bit64.lshift(device:read32(0x1c), 32)
        bar_mem = bit64.band(bar_mem, -16)
        bar_big = device:read32(0x20) -- BAR2
        bar_big = bar_big + bit64.lshift(device:read32(0x24), 32)
        bar_big = bit64.band(bar_big, -16)
        SLI_WIN_RD_ADDR = bar_reg + 0x20010
        SLI_WIN_RD_DATA = bar_reg + 0x20040
        SLI_WIN_WR_ADDR = bar_reg + 0x20000
        SLI_WIN_WR_DATA = bar_reg + 0x20020
        SLI_WIN_WR_MASK = bar_reg + 0x20030
    elseif id == ID_CN83XX then -- OcteonTX
        printf("    OcteonTX device\n")
        bar_reg = device:read32(0x10) -- BAR0
        bar_reg = bar_reg + bit64.lshift(device:read32(0x14), 32)
        bar_reg = bit64.band(bar_reg, -16)
        bar_mem = device:read32(0x18) -- BAR1
        bar_mem = bar_mem + bit64.lshift(device:read32(0x1c), 32)
        bar_mem = bit64.band(bar_mem, -16)
        bar_big = device:read32(0x20) -- BAR2
        bar_big = bar_big + bit64.lshift(device:read32(0x24), 32)
        bar_big = bit64.band(bar_big, -16)
        SLI_WIN_RD_ADDR = bar_reg + 0x2c010
        SLI_WIN_RD_DATA = bar_reg + 0x2c040
        SLI_WIN_WR_ADDR = bar_reg + 0x2c000
        SLI_WIN_WR_DATA = bar_reg + 0x2c020
        SLI_WIN_WR_MASK = bar_reg + 0x2c030
    else -- OcteonTX2
        printf("    OcteonTX2 device\n")
        bar_reg = device:read32(0x10) -- BAR0
        bar_reg = bar_reg + bit64.lshift(device:read32(0x14), 32)
        bar_reg = bit64.band(bar_reg, -16)
        bar_mem = device:read32(0x20) -- BAR4
        bar_mem = bar_mem + bit64.lshift(device:read32(0x24), 32)
        bar_mem = bit64.band(bar_mem, -16)
        bar_big = device:read32(0x18) -- BAR2
        bar_big = bar_big + bit64.lshift(device:read32(0x1c), 32)
        bar_big = bit64.band(bar_big, -16)
        SLI_WIN_RD_ADDR = bar_reg + 0x20010
        SLI_WIN_RD_DATA = bar_reg + 0x20040
        SLI_WIN_WR_ADDR = bar_reg + 0x20000
        SLI_WIN_WR_DATA = bar_reg + 0x20020
        SLI_WIN_WR_MASK = bar_reg + 0x20030
    end
    local function octeon_csr_read(address)
        address = address + bit64.lshift(1, 63) -- Secure enable
        address = address + bit64.lshift(3, 53) -- Load 8 bytes
        write64(SLI_WIN_RD_ADDR, address)
        assert(read64(SLI_WIN_RD_ADDR) == address, "RD_ADDR failed")
        return read64(SLI_WIN_RD_DATA)
    end
    local function octeon_csr_write(address, data)
        write64(SLI_WIN_WR_MASK, 0xff)
        assert(read64(SLI_WIN_WR_MASK) == 0xff, "WR_MASK failed")
        write64(SLI_WIN_WR_ADDR, address)
        assert(read64(SLI_WIN_WR_ADDR) == address, "WR_ADDR failed")
        write64(SLI_WIN_WR_DATA, data)
        read64(SLI_WIN_WR_DATA)
    end
    -- Setup memory bar region to allow access
    local card_pem
    if id == ID_CN73XX then -- Octeon
        card_pem = 0
        octeon_csr_write(0x11800c0000100, 0x1) -- SPEMX_BAR1_INDEXX(0,0) = 1
        printf("Octeon BAR0=0x%x, BAR1=0x%x, BAR2=%d, PEM=%d\n", bar_reg, bar_mem, bar_big, card_pem)
    elseif id == ID_CN83XX then -- OcteonTX
        local SLIX_MAC_NUMBERX = bar_reg + 0x2c050
        card_pem = octeontx.c.bdk_pcie_mem_read64(menu.node, pcie_root.port, SLIX_MAC_NUMBERX)
        octeon_csr_write(0x87e0c0000100 + 0x1000000 * card_pem, 0x1) -- PEMX_BAR1_INDEXX(pem,0) = 1
        -- Enable BAR2 with a size of 1MB, BAR1 is 64MB
        octeon_csr_write(0x87e0c00000a8 + 0x1000000 * card_pem, 0x18) -- PEMX_BAR_CTL(pem) = 1
        printf("OcteonTX BAR0=0x%x, BAR1=0x%x, BAR2=0x%x, PEM=%d\n", bar_reg, bar_mem, bar_big, card_pem)
    else -- OcteonTX2
        local SDPX_MAC_NUMBER = bar_reg + 0x2c100
        card_pem = octeontx.c.bdk_pcie_mem_read64(menu.node, pcie_root.port, SDPX_MAC_NUMBER)
        card_pem = bit64.band(card_pem, 0xff)
        octeon_csr_write(0x8e0000000700 + 0x1000000000 * card_pem, 0x1) -- PEMX_BAR4_INDEXX(pem,0) = 1
        printf("OcteonTX2 BAR0=0x%x, BAR2=0x%x, BAR4=0x%x, PEM=%d\n", bar_reg, bar_big, bar_mem, card_pem)
    end
    printf("Testing index memory\n")
    -- Write a test pattern to the card
    write64(bar_mem,    0x0123456789abcdef)
    write64(bar_mem+8,  0xfedcba9876543210)
    write64(bar_mem+16, 0x0123456789abcdef)
    write64(bar_mem+24, 0xfedcba9876543210)
    -- Make sure pattern was written
    local d1 = read64(bar_mem)
    local d2 = read64(bar_mem+8)
    local d3 = read64(bar_mem+16)
    local d4 = read64(bar_mem+24)
    assert(d1 == 0x0123456789abcdef, "Memory write corrupted, expect 0x%x, got 0x%x" % {0x0123456789abcdef, d1})
    assert(d2 == 0xfedcba9876543210, "Memory write corrupted, expect 0x%x, got 0x%x" % {0xfedcba9876543210, d2})
    assert(d3 == 0x0123456789abcdef, "Memory write corrupted, expect 0x%x, got 0x%x" % {0x0123456789abcdef, d3})
    assert(d4 == 0xfedcba9876543210, "Memory write corrupted, expect 0x%x, got 0x%x" % {0xfedcba9876543210, d4})
    printf("Index memory test passed\n")
    -- Big bar access
    printf("Testing big memory\n")
    local d1 = read64(bar_big)
    local d2 = read64(bar_big+8)
    local d3 = read64(bar_big+16)
    local d4 = read64(bar_big+24)
    assert(d1 == 0x0123456789abcdef, "Memory write corrupted, expect 0x%x, got 0x%x" % {0x0123456789abcdef, d1})
    assert(d2 == 0xfedcba9876543210, "Memory write corrupted, expect 0x%x, got 0x%x" % {0xfedcba9876543210, d2})
    assert(d3 == 0x0123456789abcdef, "Memory write corrupted, expect 0x%x, got 0x%x" % {0x0123456789abcdef, d3})
    assert(d4 == 0xfedcba9876543210, "Memory write corrupted, expect 0x%x, got 0x%x" % {0xfedcba9876543210, d4})
    write64(bar_big,    0xfedcba9876543210)
    write64(bar_big+8,  0x0123456789abcdef)
    write64(bar_big+16, 0xfedcba9876543210)
    write64(bar_big+24, 0x0123456789abcdef)
    local d1 = read64(bar_big)
    local d2 = read64(bar_big+8)
    local d3 = read64(bar_big+16)
    local d4 = read64(bar_big+24)
    assert(d1 == 0xfedcba9876543210, "Memory write corrupted, expect 0x%x, got 0x%x" % {0xfedcba9876543210, d1})
    assert(d2 == 0x0123456789abcdef, "Memory write corrupted, expect 0x%x, got 0x%x" % {0x0123456789abcdef, d2})
    assert(d3 == 0xfedcba9876543210, "Memory write corrupted, expect 0x%x, got 0x%x" % {0xfedcba9876543210, d3})
    assert(d4 == 0x0123456789abcdef, "Memory write corrupted, expect 0x%x, got 0x%x" % {0x0123456789abcdef, d4})
    printf("Big memory test passed\n")
end

function testmodule.test(pcie_root, pcie_port)
    printf("Starting test\n")
    setup_octeon_card(pcie_root[pcie_port])
    return 0
end

return testmodule

