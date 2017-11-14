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

-- BDK CCPI menu.
-- Displays the GUI interface for CCPI testing
require("strict")
require("utils")
require("menu")
require("fileio")
local bit64 = require("bit64")

--
-- Used on a single node to test the internal CCPI logic
--
local function do_loopback_test()
    assert(cavium.c.bdk_numa_is_only_one() == 1, "Loopback test can't run in a multinode setup")
    cavium.c.bdk_ccpi_test_loopback()
end

--
-- Called to test CCPI with a memory test
--
local function do_margin_check(node, lane)
    -- Define the range of memory to check for CCPI loading
    local mem_address = 0x4000000
    local mem_length = 0x1000000
    local test_flags = cavium.DRAM_TEST_NO_STOP_ERROR + cavium.DRAM_TEST_NO_PROGRESS +
        cavium.DRAM_TEST_NO_BANNERS + cavium.DRAM_TEST_USE_CCPI + cavium.DRAM_TEST_NO_STATS
    -- Clear lane errors
    cavium.csr[node].OCX_LNEX_INT(lane).write(-1)
    -- Run the mem test
    local errors = cavium.c.bdk_dram_test(11, mem_address, mem_length, test_flags)
    -- Read the lane error bits
    local err_bits = cavium.csr[node].OCX_LNEX_INT(lane).read()
    -- Fail if there were any errors other than counter overflow (bit 7)
    if (err_bits ~= 0) and (err_bits ~= 0x80) then
        errors = errors + 1
    end
    cavium.csr[node].OCX_LNEX_INT(lane).write(-1)
    cavium.csr[node].OCX_COM_LINKX_INT(0).write(-1)
    cavium.csr[node].OCX_COM_LINKX_INT(1).write(-1)
    cavium.csr[node].OCX_COM_LINKX_INT(2).write(-1)
    return errors
end

--
-- Measure the vertical eye for a CCPI lane
--
local function measure_vert_eye(node, qlm, qlm_lane, avg_count)
    local avg_eye_height = 0
    for avg_repeat=1,avg_count do
        local ccpi_lane = (qlm - 8) * 4 + qlm_lane
        local vert_center = cavium.c.bdk_qlm_margin_rx_get(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
        local vert_min = cavium.c.bdk_qlm_margin_rx_get_min(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
        local vert_max = cavium.c.bdk_qlm_margin_rx_get_max(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
        for vert = vert_center,vert_max do
            cavium.c.bdk_qlm_margin_rx_set(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert);
            local have_error = do_margin_check(node, ccpi_lane) > 0
            --printf("    %d - %s\n", vert, have_error and "FAIL" or "PASS")
            if have_error then
                vert_max = vert - 1
                break
            end
        end

        for vert = vert_center,vert_min,-1 do
            cavium.c.bdk_qlm_margin_rx_set(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert);
            local have_error = do_margin_check(node, ccpi_lane) > 0
            --printf("    %d - %s\n", vert, have_error and "FAIL" or "PASS")
            if have_error then
                vert_min = vert + 1
                break
            end
        end
        cavium.c.bdk_qlm_margin_rx_restore(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert_center);
        --printf("N%d.CCPI QLM%d Lane %d: Min=%d, Middle=%d, Max=%d\n", node, qlm, qlm_lane, vert_min, vert_center, vert_max)
        local eye_height = (vert_max - vert_min) + 1
        avg_eye_height = avg_eye_height + eye_height
    end
    local eye_height = avg_eye_height / avg_count
    return eye_height
end

--
-- Perform a margin sweep on all CCPI lanes
--
local function do_margin_rx()
    local MARGIN_PASS = 7 -- To pass, max-min must be greater than equal to this
    assert(cavium.c.bdk_numa_is_only_one() == 0, "Margin test can't run in a single node setup")
    assert(not cavium.is_model(cavium.CN88XXP1), "Margin test can't run on CN88XX pass 1.x")
    assert(cavium.c.bdk_init_nodes(0,0) == 0, "Failed to start all cores on all nodes")

    for node=0,1 do
        printf("N%d.CCPI: Measuring Eye Height for each lane\n", node)
        for qlm=8,13 do
            for qlm_lane=0,3 do
                local eye_height = measure_vert_eye(node, qlm, qlm_lane, 3)
                local status = (eye_height >= MARGIN_PASS) and "PASS" or "FAIL"
                printf("N%d.CCPI QLM%d Lane %d: Eye Height %2d - %s\n", node, qlm, qlm_lane, eye_height, status)
            end
        end
    end
end

--
-- Given a CCPI lane, determine the remote lane that connects to it
--
local function get_remote_lane(rx_node, rx_qlm, rx_qlm_lane)
    -- Figure out which CCPI lane on the other node is connected to the one
    -- we are tuning. Lanes may be reversed
    local tx_ccpi_lane = (rx_qlm - 8) * 4 + rx_qlm_lane
    if cavium.csr.OCX_QLMX_CFG(0).ser_lane_rev == 1 then
        tx_ccpi_lane = 23 - tx_ccpi_lane
    end
    local tx_node = bit64.bxor(rx_node, 1)
    local tx_qlm = tx_ccpi_lane / 4 + 8
    local tx_qlm_lane = bit64.band(tx_ccpi_lane, 3)
    return tx_node, tx_qlm, tx_qlm_lane
end

--
-- Auto tune a CCPI lane
--
local function do_auto_tune_lane(rx_node, rx_qlm, rx_qlm_lane)
    -- Determine the TX lane connected to this one
    local tx_node, tx_qlm, tx_qlm_lane = get_remote_lane(rx_node, rx_qlm, rx_qlm_lane)
    -- Get the current TX tuning parameters
    local tx_swing = cavium.csr[tx_node].GSERX_LANEX_SDS_PIN_MON_1(tx_qlm, tx_qlm_lane).pcs_sds_tx_swing
    local tx_premptap = cavium.csr[tx_node].GSERX_LANEX_SDS_PIN_MON_2(tx_qlm, tx_qlm_lane).pcs_sds_premptap
    local tx_pre = bit64.band(tx_premptap, 0xf)
    local tx_post = bit64.rshift(tx_premptap, 4)
    local best_eye = 0
    local best_swing = tx_swing
    -- Display the starting lane parameters for both TX and RX
    printf("\n----\n")
    printf("TX\n")
    cavium.c.bdk_qlm_display_settings(tx_node, tx_qlm, tx_qlm_lane, 1, 1)
    printf("RX\n")
    cavium.c.bdk_qlm_display_settings(rx_node, rx_qlm, rx_qlm_lane, 1, 1)
    printf("N%d.QLM%d.Lane%d: Start: TX Swing %d, Pre %d, Post %d\n",
           tx_node, tx_qlm, tx_qlm_lane, tx_swing, tx_pre, tx_post)
    -- Sweep TX swing, lowering amplitude
    for swing=tx_swing,25 do
        if cavium.c.bdk_qlm_tune_lane_tx(tx_node, tx_qlm, tx_qlm_lane, swing, tx_pre, tx_post, -1, -1) ~= 0 then
            break
        end
        local eye_height = measure_vert_eye(rx_node, rx_qlm, rx_qlm_lane, 1)
        if eye_height > best_eye then
            best_eye = eye_height
            best_swing = swing
        end
        printf("N%d.CCPI QLM%d Lane %d: Tx Swing %2d Eye Height %2d\n", rx_node, rx_qlm, rx_qlm_lane, swing, eye_height)
        if eye_height <= 5 then
            break
        end
    end
    -- Sweep TX swing, raising amplitude
    for swing=tx_swing,0,-1 do
    if cavium.c.bdk_qlm_tune_lane_tx(tx_node, tx_qlm, tx_qlm_lane, swing, tx_pre, tx_post, -1, -1) ~= 0 then
            break
        end
        local eye_height = measure_vert_eye(rx_node, rx_qlm, rx_qlm_lane, 1)
        if eye_height > best_eye then
            best_eye = eye_height
            best_swing = swing
        end
        printf("N%d.CCPI QLM%d Lane %d: Tx Swing %2d Eye Height %2d\n", rx_node, rx_qlm, rx_qlm_lane, swing, eye_height)
        if eye_height <= 5 then
            break
        end
    end
    -- Restore tuning to starting position
    cavium.c.bdk_qlm_tune_lane_tx(tx_node, tx_qlm, tx_qlm_lane, tx_swing, tx_pre, tx_post, -1, -1)
    -- Return results
    printf("N%d.CCPI QLM%d Lane %d: Best Eye Height %d with TX Swing %d\n", rx_node, rx_qlm, rx_qlm_lane, best_eye, best_swing)
    return best_swing, best_eye
end

--
-- Autotune CCPI and display settings
--
local function do_auto_tune()
    assert(cavium.c.bdk_numa_is_only_one() == 0, "Margin test can't run in a single node setup")
    assert(not cavium.is_model(cavium.CN88XXP1), "Margin test can't run on CN88XX pass 1.x")
    assert(cavium.c.bdk_init_nodes(0,0) == 0, "Failed to start all cores on all nodes")
    -- Find best swing tuning, storing results in:
    -- best_settings[rx_node][rx_qlm][rx_qlm_lane] = {1: tx_swing, 2: rx_eye}
    local best_settings = {}
    for rx_node=0,1 do
        best_settings[rx_node] = {}
        for rx_qlm=8,13 do
            best_settings[rx_node][rx_qlm] = {}
            for rx_qlm_lane=0,3 do
                local best_swing, best_eye = do_auto_tune_lane(rx_node, rx_qlm, rx_qlm_lane)
                best_settings[rx_node][rx_qlm][rx_qlm_lane] = {best_swing, best_eye}
            end
        end
    end
    -- Flush IO and wait a little for any errors to be reported
    io.flush()
    cavium.c.bdk_wait_usec(100000)
    -- Display the results
    printf("\n// CCPI TX Autotune Settings\n")
    for rx_node=0,1 do
        local average = 0
        local average_node
        for rx_qlm=8,13 do
            for rx_qlm_lane=0,3 do
                local tx_node, tx_qlm, tx_qlm_lane = get_remote_lane(rx_node, rx_qlm, rx_qlm_lane)
                average_node = tx_node
                average = average + best_settings[rx_node][rx_qlm][rx_qlm_lane][1]
                printf("    QLM-TUNING-TX-SWING.N%d.QLM%d.LANE%d = \"%d\"; // Eye Height %d\n",
                       tx_node, tx_qlm, tx_qlm_lane,
                       best_settings[rx_node][rx_qlm][rx_qlm_lane][1],
                       best_settings[rx_node][rx_qlm][rx_qlm_lane][2])
            end
        end
        average = (average + 12) / 24
        printf("    QLM-TUNING-TX-SWING.N%d = \"%d\"; // Average across lanes\n",
               average_node, average)
    end
    io.flush()
end

--
-- CCPI main menu
--

local m = menu.new("CCPI Menu")
m:item("ccpi",  "Test CCPI using internal loopback", do_loopback_test)
m:item("margin",  "Run CCPI margining tool", do_margin_rx)
m:item("autotune",  "Run CCPI auto tune tool", do_auto_tune)
m:item("quit", "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end
