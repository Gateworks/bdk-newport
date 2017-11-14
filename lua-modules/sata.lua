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

-- BDK SATA menu.
-- Displays the GUI interface for accessing SATA.
require("strict")
require("utils")
require("fileio")
require("menu")
local readline = require("readline")
local bit64 = require("bit64")

local option = ""
local sata = 0

--
-- A number of palces below need to ask the user for an area to work on and
-- open a file at that location. This function consolidates this
--
local function get_file_data(file_mode)
    local filename = utils.devfile("sata", sata)
    local offset = menu.prompt_number("Starting sector")
    local length = menu.prompt_number("Number of sectors", 1)

    local handle = assert(cavium.devopen(filename, file_mode))
    local loc = handle:seek("set", offset * 512)
    if not loc then
        handle:close()
        error('Seek failed in file "' .. filename ..'"')
    end

    return handle, offset, length
end

--
-- Write a fixed pattern to SATA
--
local function write_pattern(pattern)
    local handle, offset, length = get_file_data("w")
    handle:write(fileio.get_pattern(pattern, length))
    handle:close()
end

--
-- Read SATA and verify the data matches the pattern
--
local function read_pattern(pattern)
    local handle, offset, length = get_file_data("r")
    local correct = fileio.get_pattern(pattern, length)
    local data = handle:read(length * 512)
    handle:close()
    assert(#data == length * 512, "SATA read failed")
    assert(correct == data, "SATA data doesn't match pattern")
end

local function run_auto()
    local filename = utils.devfile("sata", sata)
    return fileio.pattern_test(filename, 512, 128, 0)
end

--
-- Check margin range for SATA channel
--
local function margin_rx()
    local MARGIN_PASS = 6 -- To pass, max-min must be greater than equal to this
    local filename = utils.devfile("sata", sata)
    local handle = assert(cavium.devopen(filename, "r+"))
    local function do_data()
        cavium.csr[menu.node].SATAX_UAHC_P0_IS(sata).write(-1)
        cavium.csr[menu.node].SATAX_UAHC_P0_SERR(sata).write(-1)
        cavium.csr[menu.node].SATAX_UAHC_P0_SERR(sata).read()
        local errors = 0
        local length = 128
        local correct = fileio.get_pattern(0x55, length)
        assert(handle:seek("set", 0), "Write seek failed")
        handle:write(correct)
        for rep = 1,64 do
            assert(handle:seek("set", 0), "Read seek failed")
            local data = handle:read(length * 512)
            if correct ~= data then
                errors = errors + 1
                break
            end
            if cavium.csr[menu.node].SATAX_UAHC_P0_SERR(sata).read() ~= 0 then
                errors = errors + 1
                break
            end
            if cavium.csr[menu.node].SATAX_UAHC_P0_IS(sata).INFS ~= 0 then
                errors = errors + 1
                break
            end
            if cavium.csr[menu.node].SATAX_UAHC_P0_IS(sata).IFS ~= 0 then
                errors = errors + 1
                break
            end
        end
        return errors
    end
    local qlm = (sata >= 8) and (6 + (sata - 8) / 4) or (2 + sata / 4) -- FIXME: Only CN88XX
    local qlm_lane = bit64.band(sata, 3)
    printf("N%d.SATA%d: Measuring Eye Height\n", menu.node, sata)
    local avg_eye_height = 0
    local avg_count = 3
    for avg_repeat=1,avg_count do
        local vert_center = cavium.c.bdk_qlm_margin_rx_get(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
        local vert_min = cavium.c.bdk_qlm_margin_rx_get_min(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
        local vert_max = cavium.c.bdk_qlm_margin_rx_get_max(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
        for vert = vert_center,vert_max do
            cavium.c.bdk_qlm_margin_rx_set(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert);
            local errors = do_data() -- Send data
            --printf("    %d - %s\n", vert, (errors > 0) and "FAIL" or "PASS")
            if errors > 0 then
                vert_max = vert - 1
                break
            end
        end
        cavium.c.bdk_qlm_margin_rx_restore(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert_center);
        handle:close()
        -- Open causes another SATA init
        handle = assert(cavium.devopen(filename, "r+"))
        for vert = vert_center,vert_min,-1 do
            cavium.c.bdk_qlm_margin_rx_set(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert);
            local errors = do_data() -- Send data
            --printf("    %d - %s\n", vert, (errors > 0) and "FAIL" or "PASS")
            if errors > 0 then
                vert_min = vert + 1
                break
            end
        end
        cavium.c.bdk_qlm_margin_rx_restore(menu.node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert_center);
        --printf("N%d.SATA%d: Min=%d, Middle=%d, Max=%d\n", menu.node, sata, vert_min, vert_center, vert_max)
        local eye_height = (vert_max - vert_min) + 1
        avg_eye_height = avg_eye_height + eye_height
    end
    local eye_height = avg_eye_height / avg_count
    local status = (eye_height >= MARGIN_PASS) and "PASS" or "FAIL"
    printf("N%d.SATA%d: Eye Height %2d - %s\n", menu.node, sata, eye_height, status)
    handle:close()
end

--
-- Put the menu on the screen
--
while (option ~= "quit") do
    local m = menu.new("SATA Menu")
    m:item_node() -- Adds option to choose the node number

    m:item("port", "Select SATA port (Currently %d)" % sata, function()
        local num_sata = cavium.c.bdk_sata_get_controllers(menu.node)
        sata = menu.prompt_number("SATA port to use", sata, 0, num_sata - 1)
    end)

    m:item("id", "Perform an identify disk", function()
        local size = cavium.c.bdk_sata_identify(menu.node, sata, 0)
    end)

    m:item("sw-retimed", "Enter Local-end Retimed Loopback", function()
        printf("Entering Local-end Retimed Loopback\n")
        cavium.c.bdk_sata_bist_fis(menu.node, sata, 0, cavium.SATA_BIST_SW_RETIMED)
    end)

    local function add_tx_only(test, descr)
        m:item("sw-tx%d" % test, "Enter Local-end Transmit Only, %s" % descr, function()
            printf("Entering %s\n" % descr)
            cavium.c.bdk_sata_bist_fis(menu.node, sata, 0, test)
        end)
    end
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_SSOP, "Simultaneous switching outputs pattern (SSOP)")
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_HTDP, "High transition density pattern (HTDP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_LTDP, "Low transition density pattern (LTDP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_LFSCP,"Low frequency spectral component pattern (LFSCP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_COMP, "Composite pattern (COMP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_LBP,  "Lone bit pattern (LBP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_MFTP, "Mid frequency test pattern (MFTP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_HFTP, "High frequency test pattern (HFTP)");
    add_tx_only(cavium.SATA_BIST_SW_TX_ONLY_LFTP, "Low frequency test pattern (LFTP)");

    m:item("reset", "Reset the controller", function()
        printf("Resetting the controller\n")
        local status = cavium.c.bdk_sata_shutdown(menu.node, sata)
    end)

    m:item("hex", "Hex display", function()
        local offset = menu.prompt_number("Starting sector")
        local length = menu.prompt_number("Number of sectors", 1)
        local filename = utils.devfile("sata", sata)
        fileio.hexdump(filename, offset * 512, length * 512)
    end)

    for i,p in ipairs(fileio.PATTERNS) do
        m:item("w" .. tostring(p), "Write pattern 0x%02x" % p, write_pattern, p)
        m:item("r" .. tostring(p), "Read  pattern 0x%02x" % p, read_pattern, p)
    end

    m:item("auto", "Run automated pattern test", run_auto)
    m:item("margin", "Run margining tool", margin_rx)

    m:item("quit", "Main menu")
    option = m:show()
end

