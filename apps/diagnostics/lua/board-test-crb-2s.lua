-- ***********************license start***********************************
-- Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
-- reserved.
--
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are
-- met:
--
--   * Redistributions of source code must retain the above copyright
--     notice, this list of conditions and the following disclaimer.
--
--   * Redistributions in binary form must reproduce the above
--     copyright notice, this list of conditions and the following
--     disclaimer in the documentation and/or other materials provided
--     with the distribution.
--
--   * Neither the name of Cavium Inc. nor the names of
--     its contributors may be used to endorse or promote products
--     derived from this software without specific prior written
--     permission.
--
-- This Software, including technical data, may be subject to U.S. export
-- control laws, including the U.S. Export Administration Act and its
-- associated regulations, and may be subject to export or import
-- regulations in other countries.
--
-- TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
-- AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
-- WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
-- TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
-- REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
-- DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
-- OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
-- PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
-- QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
-- ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
-- **********************license end**************************************
require("strict")
require("menu")
require("utils")
require("cavium")
require("trafficgen")
local bit64 = require("bit64")

local node = cavium.MASTER_NODE

local function check_ref_clock(qlm, expected_rate_hz)
    local measured = cavium.c.bdk_qlm_measure_clock(node, qlm)
    local range = expected_rate_hz / 1000 -- With 0.1%
    local min_hz = expected_rate_hz - range
    local max_hz = expected_rate_hz + range
    local good = (measured >= min_hz) and (measured <= max_hz)
    if good then
        printf("Ref clock QLM%d: PASS\n", qlm)
    else
        printf("Ref clock QLM%d: FAIL (%d Hz, expected %d Hz\n", qlm, measured, expected_rate_hz)
    end
    return good
end

local function check_pcie_rc(pem)
    local pcie = require("pcie")
    local status, rc = pcall(pcie.initialize, 0, pem)
    if status then
        rc:scan()
        rc:enumerate()
        --rc:display()
        print("PCIe%d: PASS" % pem)
        return true
    else
        print("PCIe%d: FAIL (No link)" % pem)
        return false
    end
end

local function check_sata(sata)
    local size = cavium.c.bdk_sata_identify(node, sata, 0)
    local good = (size > 0)
    if good then
        printf("SATA%d: PASS\n", sata)
    else
        printf("SATA%d: FAIL (Identify failed)\n", sata)
    end
    return good
end


local function tg_run(tg, ports, size, count, rate, to_secs)
    local test_ports = tg:command("default %s" % ports)
    if test_ports == nil then
        printf("Test %s, size %d, count %d: FAIL (No ports)\n", ports, size, count)
        return false
    end
    tg:command("clear all")
    tg:command("size %d" % size)
    tg:command("count %d" % count)
    tg:command("tx_percent %d" % rate)
    tg:command("start")
    cavium.c.bdk_wait_usec(to_secs * 1000000)
    local stats = tg:get_stats()
    local ports_pass = true
    local num_ports = 0
    for port,stat in pairs(stats) do
        num_ports = num_ports + 1
        local pass = true
        pass = pass and (stat.tx_packets_total == count)
        pass = pass and (stat.rx_packets_total == count)
        pass = pass and (stat.tx_octets_total == stat.rx_octets_total)
        pass = pass and (stat.rx_errors == 0)
        pass = pass and (stat.rx_validation_errors == 0)
        if not pass then
            pprint("FAIL", port, stat)
        end
        ports_pass = ports_pass and pass
    end
    if num_ports ~= #test_ports then
        printf("Test %s, size %d, count %d: FAIL (Stats missing ports)\n", ports, size, count)
        return false
    end
    if ports_pass then
        printf("Test %s, size %d, count %d: PASS\n", ports, size, count)
    else
        printf("Test %s, size %d, count %d: FAIL\n", ports, size, count)
    end
    return ports_pass
end

local function check_dram()
    local good = true
    local expected_mbytes = 32768

    local dram_mbytes = cavium.c.bdk_dram_get_size_mbytes(node)
    good = (dram_mbytes == expected_mbytes)
    if good then
        printf("DRAM Size: PASS\n")
    else
        printf("DRAM Size: FAIL (%d MB, expect %d MB)\n", dram_mbytes, expected_mbytes)
    end

    -- Run all tests, on 64-128MB
    local err_count = -1
    for test_number=0,100 do
        local name = cavium.c.bdk_dram_get_test_name(test_number);
        if not name then
            break
        end
        err_count = cavium.c.bdk_dram_test(test_number, 0x4000000, 0x4000000)
        if err_count ~= 0 then
            break
        end
    end
    good = (err_count == 0) and good
    if err_count == 0 then
        printf("DRAM Test 64MB-128MB: PASS\n")
    else
        printf("DRAM Test 64MB-128MB: FAIL\n")
    end
    return good
end

local function board_test()
    printf("\n")
    printf("Board test: CN88XX-CRB-2S\n")
    printf("BDK version: %s\n", cavium.c.bdk_version_string())

    local all_pass = true

    --
    -- Go multinode
    --
    local status = cavium.c.bdk_init_nodes(0, 10312)
    if (status == 0) then
        printf("Mult-core: PASS\n")
    else
        printf("Mult-core: FAIL\n")
    end
    all_pass = all_pass and (status == 0)

    --
    -- Measure reference clocks
    --
    node = cavium.MASTER_NODE
    all_pass = check_ref_clock(0, 156250000) and all_pass
    all_pass = check_ref_clock(1, 156250000) and all_pass
    all_pass = check_ref_clock(2, 100000000) and all_pass
    all_pass = check_ref_clock(3, 100000000) and all_pass
    all_pass = check_ref_clock(4, 100000000) and all_pass
    all_pass = check_ref_clock(5, 100000000) and all_pass
    all_pass = check_ref_clock(6, 100000000) and all_pass
    all_pass = check_ref_clock(7, 100000000) and all_pass
    node = 1
    all_pass = check_ref_clock(0, 156250000) and all_pass
    all_pass = check_ref_clock(3, 100000000) and all_pass

    --
    -- DRAM
    --
    node = cavium.MASTER_NODE
    all_pass = check_dram() and all_pass
    node = 1
    all_pass = check_dram() and all_pass

    --
    -- PCIe tests
    --
    node = cavium.MASTER_NODE
    all_pass = check_pcie_rc(0) and all_pass -- Internal to BMC
    all_pass = check_pcie_rc(2) and all_pass -- x24 riser
    all_pass = check_pcie_rc(4) and all_pass -- x8 slot

    --
    -- SATA tests
    --
    node = cavium.MASTER_NODE
    all_pass = check_sata(4) and all_pass -- QLM3, SATA port 0
    all_pass = check_sata(5) and all_pass -- QLM3, SATA port 1
    all_pass = check_sata(6) and all_pass -- QLM3, SATA port 2
    all_pass = check_sata(7) and all_pass -- QLM3, SATA port 3
    node = 1
    all_pass = check_sata(4) and all_pass -- QLM3, SATA port 0
    all_pass = check_sata(5) and all_pass -- QLM3, SATA port 1
    all_pass = check_sata(6) and all_pass -- QLM3, SATA port 2
    all_pass = check_sata(7) and all_pass -- QLM3, SATA port 3

    --
    -- Put networking in PHY internal loopback
    --

    --
    -- Network Traffic Tests
    --
    local tg_pass = true
    local trafficgen = require("trafficgen")
    local tg = trafficgen.new()
    cavium.c.bdk_if_link_wait_all(10 * 1000000) -- wait for links to come up.
    -- Do 100k packets, 60 bytes each, 50% of gigabit, timeout 5 secs
    all_pass = tg_run(tg, "N0.XLAUI1", 60, 100000, 50, 5) and all_pass
    -- Do 100k packets, 1499 bytes each, 50% of gigabit, timeout 7 secs
    all_pass = tg_run(tg, "N0.XLAUI1", 1499, 100000, 50, 7) and all_pass
    -- Do 100k packets, 9212 bytes each, 50% of gigabit, timeout 12 secs
    all_pass = tg_run(tg, "N0.XLAUI1", 9212, 10000, 10, 12) and all_pass
    -- Do 100k packets, 60 bytes each, 50% of gigabit, timeout 5 secs
    all_pass = tg_run(tg, "N0.XFI0.0", 60, 100000, 50, 5) and all_pass
    -- Do 100k packets, 1499 bytes each, 50% of gigabit, timeout 7 secs
    all_pass = tg_run(tg, "N0.XFI0.0", 1499, 100000, 50, 7) and all_pass
    -- Do 100k packets, 9212 bytes each, 50% of gigabit, timeout 12 secs
    all_pass = tg_run(tg, "N0.XFI0.0", 9212, 10000, 10, 12) and all_pass
    -- Do 100k packets, 60 bytes each, 50% of gigabit, timeout 5 secs
    all_pass = tg_run(tg, "N1.XFI0.0", 60, 100000, 50, 5) and all_pass
    -- Do 100k packets, 1499 bytes each, 50% of gigabit, timeout 7 secs
    all_pass = tg_run(tg, "N1.XFI0.0", 1499, 100000, 50, 7) and all_pass
    -- Do 100k packets, 9212 bytes each, 50% of gigabit, timeout 12 secs
    all_pass = tg_run(tg, "N1.XFI0.0", 9212, 10000, 10, 12) and all_pass

    --
    -- Summary
    --
    print("")
    if all_pass then
        print("All tested summary: PASS")
    else
        print("All tested summary: FAIL")
    end
    print("")
end

return board_test



