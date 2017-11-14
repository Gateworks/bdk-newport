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
require("pcie")
require("strict")
require("menu")
require("utils")
require("cavium")
require("trafficgen")
local bit64 = require("bit64")

local node = 0
local all_pass = true
local bist_failures = 0

local function tg_run(tg, ports, size, count, rate, to_secs)
    print("TESTINGS PORT "..ports.."\n");
    if not tg:command("default %s" % ports) then
        printf("Test %s, size %d, count %d: FAIL\n", ports, size, count)
        return false
    end

    tg:command("clear all")
    tg:command("size %d" % size)
    tg:command("count %d" % count)
    tg:command("tx_percent %d" % rate)
    tg:command("start")
    cavium.c.bdk_wait_usec(to_secs * 1000000)
    tg:command("rx_octets_total")
    local stats = tg:get_stats()
    local ports_pass = true
    for port,stat in pairs(stats) do
        local pass = true
        pass = pass and (stat.tx_packets_total == count)
        pass = pass and (stat.rx_packets_total == count)
        pass = pass and (stat.tx_octets_total == stat.rx_octets_total)
        pass = pass and (stat.rx_errors == 0)
        pass = pass and (stat.rx_validation_errors == 0)
        if not pass then
            pprint(port, stat)
        end
        ports_pass = ports_pass and pass
    end
    if ports_pass then
        printf("Test %s, size %d, count %d: PASS\n", ports, size, count)
    else
        printf("Test %s, size %d, count %d: FAIL\n", ports, size, count)
    end
    return ports_pass
end



local function pcie_rc(pem)
    --
    -- PCIe
    --
        print("test start: PCIe")
        local pcie = require("pcie")
        local status, rc = pcall(pcie.initialize, 0, pem)
        if status then
    --    t
    --    t
    --    w
            rc:scan()
            rc:enumerate()
            rc:display()
            print("PCIe%d init: PASS" % pem)
        else
            print("PCIe%d init: FAIL" % pem)
        end
        print("test end: PCIe")
end

local function mmc_test(device)
    --
    -- MMC Tests
    --
    local mmc_pass = false
    local capacity = cavium.c.bdk_mmc_initialize(node, device)
    if (capacity > 0) then
        mmc_pass = true
        printf("MMC%d Init test: PASS\n", device)
    else
        printf("MMC%d capacity:%d\n", device, capacity)
        printf("MMC%d Init test: FAIL\n",device)
        mmc_pass = false
    end
    return mmc_pass
end

--Ported the function from bist.c
local function check_bist_reg(reg_name, expected, mask)
    local masked_val
    
    local bist_val = cavium.c.bdk_csr_read_by_name(node, reg_name)

    printf("REG %s VALUE %x mask %x\n", reg_name, bist_val, mask);
    -- Log complete value for reference.... 
    mask = bit64.bxor(0xffffffffffffffff,mask)
    masked_val = bit64.bxor(bit64.band(bist_val, mask),expected)
    if (masked_val  ~= 0) then
        bist_failures = bist_failures+1
	    printf("BIST FAILURE: %s, error bits ((register & mask) ^ expected): 0x%016x\n", reg_name, masked_val);
    end
end

local function tns_bist_check()
    check_bist_reg("TNS_SE_AGE_MEM_BIST_STDN", 
                    0, 
                    (bit64.lshift(1, 4)-1)
                   )

    for i=0,7 do 
        check_bist_reg("TNS_SE_SRAM_PAIRX_BIST_STDN("..i..")", 
                        0, 
                        (bit64.lshift(1, 4)-1)
                       )
    end

    for i=0,7 do 
        check_bist_reg("TNS_SE_TCAM_DBX_BIST_STDN("..i..")", 
                        0, 
                        bit64.bor(
                            (bit64.lshift(1, 6)-1),--cam_bist_done
                            bit64.lshift((bit64.lshift(1,6)-1),12) --bist_done
                            )
                       )
    end

    for i=0,7 do 
        check_bist_reg("TNS_SE_TCAM_SRAMX_BIST_STDN("..i..")", 
                        0, 
                        (bit64.lshift(1, 2)-1)
                       )
    end


    check_bist_reg("TNS_TXQ_CNT_QAC_BIST_STDN", 
                    0, 
                    (bit64.lshift(1, 12)-1)
                   )
    check_bist_reg("TNS_TXQ_DQ_BIST_STDN", 
                    0, 
                    (bit64.lshift(1, 14)-1)
                   )
    check_bist_reg("TNS_TXQ_EQ_BIST_STDN", 
                    0, 
                    (bit64.lshift(1, 1)-1)
                   )
    check_bist_reg("TNS_TXQ_TBC_BIST_STDN", 
                    0, 
                    (bit64.lshift(1, 7)-1)
                   )

    if(bist_failures == 0) then
        print("TNS BIST PASS\n")
    else
        print("TNS BIST FAIL\n")
    end

end

local function check_ccpi(link)
    --
    -- MMC Tests
    --
    local ccpi_pass = true
    if ((cavium.csr.OCX_COM_LINKX_CTL(link).UP ~= 1) or
        (cavium.csr.OCX_COM_LINKX_CTL(link).VALID ~= 1)) then
        print ("oci0: FAIL (link status)")
        ccpi_pass = false
    end
    if ((cavium.csr.OCX_QLMX_CFG(2 * link + 0).SER_LANE_READY ~= 15) or
        (cavium.csr.OCX_QLMX_CFG(2 * link + 1).SER_LANE_READY ~= 15)) then
        print ("oci0: FAIL (missing lanes)")
        ccpi_pass = false
    end
    return ccpi_pass
end


-- Print out a banner
print("")
print("BDK version ".. cavium.c.bdk_version_string())
print("Cavium Chip Screen")
print("Copyright (C) 2010-2017 Cavium Inc.")

if utils.isglobal("BOARD_SETUP_DONE") then
    -- Board setup is already complete, don't do it again
elseif package.searchpath("board-setup", package.path) then
    menu.dofile("board-setup")
end
BOARD_SETUP_DONE = true

local board_name = menu.prompt_string("Board type: ", "ebb8800")
local coremask = menu.prompt_number("Coremask: ", 0xffffffffffff)
-- Config Number
-- 0 = Regular I/O testing (Chip SLT)
-- 1 = Board testing configuration for module testing (Board Mfg screen)
-- 2 = Board testing configuration for module testing (Board Mfg screen)
-- 3 = TNS BIST check
-- 4 = TNS test (Config 0 with TNS 
--
local config_num = menu.prompt_number("Config Number: ", 0)
local use_tns = 0


if (config_num == 4) then
-- config_num = 4 means the regular chip-testing (config=0) with TNS
    use_tns = 1
    config_num = 0
end

-- Go multicore, based on coremask provided by script.
printf("Using coremask: 0x%x\n", coremask)

if (config_num == 0) then

    -- OCI test - confirm all QLMs are up and valid.

    if (string.match(board_name, "ebb88")) then
        if (check_ccpi(0) and check_ccpi(1) and check_ccpi(2)) then
            print ("OCI Test: PASS")
        else
            all_pass = false
            print ("OCI Test: FAIL")
        end
    end


    local mmc_pass = true
    mmc_pass = mmc_test(0)
    mmc_pass = mmc_test(1) and mmc_pass
    all_pass = all_pass and mmc_pass

    -- PCIe tests.  All QLMs x8 RC
    if (string.match(board_name, "ebb88")) then
        pcie_rc(0)
    end
    pcie_rc(2)
    if (string.match(board_name, "ebb88")) then
        pcie_rc(4)
    end
end

--
-- Network Traffic Tests
--
print("Starting all requested cores");
cavium.c.bdk_init_cores(0, coremask)

if (config_num == 5) then
    if cavium.c.bdk_ccpi_test_loopback() ~= 0 then
        all_pass = 0
    end
    print("CCPI Loopback test done")
end

print("test start: traffic")
local tg_pass = true
local trafficgen = require("trafficgen")
local tg = trafficgen.new()
if (use_tns == 1) then
    tg:command("use_tns")
end
cavium.c.bdk_wait_usec(3 * 1000000) -- wait for links to come up.

if (config_num == 0) then
    tg_pass = tg_run(tg, "40GKR0-40GKR1", 60, 100000, 50, 5)
    tg_pass = tg_run(tg, "40GKR0-40GKR1", 1499, 100000, 50, 7) and tg_pass
    tg_pass = tg_run(tg, "40GKR0-40GKR1", 9111, 10000, 10, 12) and tg_pass
    all_pass = all_pass and tg_pass
elseif (config_num == 1) then
    tg_pass = tg_run(tg, "SGMII0.0-SGMII0.1", 60, 100000, 100, 2)
    tg_pass = tg_run(tg, "SGMII0.0-SGMII0.1", 1499, 1000, 100, 2) and tg_pass
    tg_pass = tg_run(tg, "SGMII0.2-SGMII0.3", 60, 100000, 100, 2) and tg_pass
    tg_pass = tg_run(tg, "SGMII0.2-SGMII0.3", 1499, 1000, 100, 2) and tg_pass
    tg_pass = tg_run(tg, "XAUI1", 60, 100000, 100, 2) and tg_pass
    tg_pass = tg_run(tg, "XAUI1", 1499, 1000, 100, 2) and tg_pass
    all_pass = all_pass and tg_pass
elseif (config_num == 2) then
    tg_pass = tg_run(tg, "XAUI0", 60, 100000, 100, 2)
    tg_pass = tg_run(tg, "XAUI0", 1499, 1000, 100, 2) and tg_pass
elseif (config_num == 3) then
    tns_bist_check();
end
if (use_tns == 1) then
    if (cavium.csr.TNS_SDE_PE_KPUX_KPU_DBG_W0(0).HIT == 1) then
        print("TNS HIT TEST: PASS\n")
    else
        all_pass = 0
        print("TNS HIT TEST: FAIL\n")
    end
end

  
--
-- Summary
--
print("")
if all_pass then
    print("All tested summary: PASS")
else
    print("All tested summary: FAIL")
end
print("BDK Chip Screen complete.")
print("")

