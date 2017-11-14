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

-- BDK QLM menu for CN88XX configuration.
require("strict")
require("utils")
require("menu")

-- This is an array indexed by QLM number. Each entry is a list of
-- QLM mode settings that the user can choose. Not all possibilites
-- are here, but this should cover most cases. Note that QLMs that
-- have the same list share the same lists, so take care making
-- modifications.
local qlm_display_order = {}
local qlm_modes = {}
local qlm_external_name = {}
if not cavium.is_altpkg(cavium.CN88XX) then
    -- CN88XX in a standard package
    for qlm=0,14 do
        qlm_display_order[qlm] = qlm
        qlm_external_name[qlm] = "QLM%d" % qlm
    end
    qlm_modes[0] = {
        {"sgmii", "SGMII   @  1 Gbps", cavium.QLM_MODE_SGMII_4X1, 1250, 0},
        {"xaui",  "XAUI    @ 10 Gbps", cavium.QLM_MODE_XAUI_1X4, 3125, 0},
        {"dxaui", "DXAUI   @ 20 Gbps", cavium.QLM_MODE_XAUI_1X4, 6250, 0},
        {"rxaui", "RXAUI   @ 10 Gbps", cavium.QLM_MODE_RXAUI_2X2, 6250, 0},
        {"xfi",   "XFI     @ 10 Gbps", cavium.QLM_MODE_XFI_4X1, 10312, 0},
        {"xlaui", "XLAUI   @ 40 Gbps", cavium.QLM_MODE_XLAUI_1X4, 10312, 0},
        {"10g",   "10G-KR  @ 10 Gbps", cavium.QLM_MODE_10G_KR_4X1, 10312, 0},
        {"40g",   "40G-KR4 @ 40 Gbps", cavium.QLM_MODE_40G_KR4_1X4, 10312, 0},
        {"dis",   "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_modes[1] = qlm_modes[0]
    qlm_modes[2] = {
        {"rc-x4-g1", "PCIe x4 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x4-g2", "PCIe x4 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x4-g3", "PCIe x4 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"rc-x8-g1", "PCIe x8 - GEN 1", cavium.QLM_MODE_PCIE_1X8, 2500, 0},
        {"rc-x8-g2", "PCIe x8 - GEN 2", cavium.QLM_MODE_PCIE_1X8, 5000, 0},
        {"rc-x8-g3", "PCIe x8 - GEN 3", cavium.QLM_MODE_PCIE_1X8, 8000, 0},
        {"sata1",    "SATA    @ 1.500 Gbps", cavium.QLM_MODE_SATA_4X1, 1500, 0},
        {"sata2",    "SATA    @ 3.000 Gbps", cavium.QLM_MODE_SATA_4X1, 3000, 0},
        {"sata3",    "SATA    @ 6.000 Gbps", cavium.QLM_MODE_SATA_4X1, 6000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_modes[3] = {
        {"rc-x4-g1", "PCIe x4 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x4-g2", "PCIe x4 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x4-g3", "PCIe x4 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"sata1",    "SATA    @ 1.500 Gbps", cavium.QLM_MODE_SATA_4X1, 1500, 0},
        {"sata2",    "SATA    @ 3.000 Gbps", cavium.QLM_MODE_SATA_4X1, 3000, 0},
        {"sata3",    "SATA    @ 6.000 Gbps", cavium.QLM_MODE_SATA_4X1, 6000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_modes[4] = {
        {"rc-x4-g1", "PCIe x4 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x4-g2", "PCIe x4 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x4-g3", "PCIe x4 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"rc-x8-g1", "PCIe x8 - GEN 1", cavium.QLM_MODE_PCIE_1X8, 2500, 0},
        {"rc-x8-g2", "PCIe x8 - GEN 2", cavium.QLM_MODE_PCIE_1X8, 5000, 0},
        {"rc-x8-g3", "PCIe x8 - GEN 3", cavium.QLM_MODE_PCIE_1X8, 8000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_modes[5] = {
        {"rc-x4-g1", "PCIe x4 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x4-g2", "PCIe x4 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x4-g3", "PCIe x4 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_modes[6] = qlm_modes[2]
    qlm_modes[7] = qlm_modes[3]
    -- GSER 8-13 are OCI only and are normally covered by pin straps
    qlm_modes[8] = {
        {"ccpi1",    "CCPI    @ 1.250 Gbps", cavium.QLM_MODE_OCI, 1250, 0},
        {"ccpi2",    "CCPI    @ 2.500 Gbps", cavium.QLM_MODE_OCI, 2500, 0},
        {"ccpi3",    "CCPI    @ 3.125 Gbps", cavium.QLM_MODE_OCI, 3125, 0},
        {"ccpi5",    "CCPI    @ 5.000 Gbps", cavium.QLM_MODE_OCI, 5000, 0},
        {"ccpi6",    "CCPI    @ 6.250 Gbps", cavium.QLM_MODE_OCI, 6250, 0},
        {"ccpi8",    "CCPI    @ 8.000 Gbps", cavium.QLM_MODE_OCI, 8000, 0},
        {"ccpi10",   "CCPI    @ 10.3125 Gbps", cavium.QLM_MODE_OCI, 10312, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_modes[9] = qlm_modes[8]
    qlm_modes[10] = qlm_modes[8]
    qlm_modes[11] = qlm_modes[8]
    qlm_modes[12] = qlm_modes[8]
    qlm_modes[13] = qlm_modes[8]
else
    -- CN86XX, CN88XX in a CN83XX compatible package
    qlm_display_order[0] = 4
    qlm_display_order[1] = 5
    qlm_display_order[2] = 0
    qlm_display_order[3] = 1
    qlm_display_order[4] = 2
    qlm_display_order[5] = 6
    qlm_display_order[6] = 7
    qlm_external_name[4] = "QLM0(Internal QLM4)"
    qlm_modes[4] = {
        {"rc-x4-g1", "PCIe x4 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x4-g2", "PCIe x4 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x4-g3", "PCIe x4 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"rc-x8-g1", "PCIe x8 - GEN 1", cavium.QLM_MODE_PCIE_1X8, 2500, 0},
        {"rc-x8-g2", "PCIe x8 - GEN 2", cavium.QLM_MODE_PCIE_1X8, 5000, 0},
        {"rc-x8-g3", "PCIe x8 - GEN 3", cavium.QLM_MODE_PCIE_1X8, 8000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_external_name[5] = "QLM1(Internal QLM5)"
    qlm_modes[5] = {
        {"rc-x4-g1", "PCIe x4 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x4-g2", "PCIe x4 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x4-g3", "PCIe x4 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_external_name[0] = "QLM2(Internal QLM0)"
    qlm_modes[0] = {
        {"sgmii", "SGMII   @  1 Gbps", cavium.QLM_MODE_SGMII_4X1, 1250, 0},
        {"xaui",  "XAUI    @ 10 Gbps", cavium.QLM_MODE_XAUI_1X4, 3125, 0},
        {"dxaui", "DXAUI   @ 20 Gbps", cavium.QLM_MODE_XAUI_1X4, 6250, 0},
        {"rxaui", "RXAUI   @ 10 Gbps", cavium.QLM_MODE_RXAUI_2X2, 6250, 0},
        {"xfi",   "XFI     @ 10 Gbps", cavium.QLM_MODE_XFI_4X1, 10312, 0},
        {"xlaui", "XLAUI   @ 40 Gbps", cavium.QLM_MODE_XLAUI_1X4, 10312, 0},
        {"10g",   "10G-KR  @ 10 Gbps", cavium.QLM_MODE_10G_KR_4X1, 10312, 0},
        {"40g",   "40G-KR4 @ 40 Gbps", cavium.QLM_MODE_40G_KR4_1X4, 10312, 0},
        {"dis",   "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_external_name[1] = "QLM3(Internal QLM1)"
    qlm_modes[1] = qlm_modes[0]

    qlm_external_name[2] = "DLM4(Internal QLM2)"
    qlm_modes[2] = {
        {"sata1",    "SATA    @ 1.500 Gbps", cavium.QLM_MODE_SATA_4X1, 1500, 0},
        {"sata2",    "SATA    @ 3.000 Gbps", cavium.QLM_MODE_SATA_4X1, 3000, 0},
        {"sata3",    "SATA    @ 6.000 Gbps", cavium.QLM_MODE_SATA_4X1, 6000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }
    qlm_external_name[6] = "DLM5(Internal QLM6)"
    qlm_modes[6] = {
        {"rc-x2-g1", "PCIe x2 - GEN 1", cavium.QLM_MODE_PCIE_1X4, 2500, 0},
        {"rc-x2-g2", "PCIe x2 - GEN 2", cavium.QLM_MODE_PCIE_1X4, 5000, 0},
        {"rc-x2-g3", "PCIe x2 - GEN 3", cavium.QLM_MODE_PCIE_1X4, 8000, 0},
        {"sata1",    "SATA    @ 1.500 Gbps", cavium.QLM_MODE_SATA_4X1, 1500, 0},
        {"sata2",    "SATA    @ 3.000 Gbps", cavium.QLM_MODE_SATA_4X1, 3000, 0},
        {"sata3",    "SATA    @ 6.000 Gbps", cavium.QLM_MODE_SATA_4X1, 6000, 0},
        {"dis",      "Disabled", cavium.QLM_MODE_DISABLED, 0, 0}
    }

    qlm_external_name[7] = "DLM6(Internal QLM7)"
    qlm_modes[7] = qlm_modes[6]
end

--
-- This is called when the user selects a QLM to change its config
--
local function do_setup(qlm)
    -- Only the first 8 QLMs can select different reference clocks
    -- CCPI QLMs 8-13 always use an external reference clock
    if qlm < 8 then
        local m = menu.new("Select a reference clock for %s" % qlm_external_name[qlm])
        m:item("ext", "External reference (QLM%d_REF_CLK)" % qlm)
        m:item("c0", "Common clock 0 (QLMC_REF_CLK0)")
        m:item("c1", "Common clock 1 (QLMC_REF_CLK1)")
        local index = m:show()
        -- Select the reference clock to use
        if index == "ext" then
            cavium.c.bdk_qlm_set_clock(menu.node, qlm, cavium.QLM_CLK_EXTERNAL)
        elseif index == "c0" then
            cavium.c.bdk_qlm_set_clock(menu.node, qlm, cavium.QLM_CLK_COMMON_0)
        else
            cavium.c.bdk_qlm_set_clock(menu.node, qlm, cavium.QLM_CLK_COMMON_1)
        end
        -- Reset the QLM after changing the reference clock
        cavium.c.bdk_qlm_reset(menu.node, qlm)
    end

    -- Select the mode to use
    local m = menu.new("Select a mode for %s" % qlm_external_name[qlm])
    for i=1,#qlm_modes[qlm] do
        m:item(qlm_modes[qlm][i][1], qlm_modes[qlm][i][2])
    end
    local index = m:show()
    local choice
    for i=1,#qlm_modes[qlm] do
        if qlm_modes[qlm][i][1] == index then
            choice = qlm_modes[qlm][i]
        end
    end
    assert(choice, "Invalid menu choice")
    local mode = choice[3]
    local baud_mhz = choice[4]
    local flags = choice[5]
    cavium.c.bdk_qlm_set_mode(menu.node, qlm, mode, baud_mhz, flags)
end

--
-- Chip specific configuration prompting for CN88XX
--
function qlm_setup_cn88xx()
    local qlm_max = 7
    if not cavium.is_altpkg(cavium.CN88XX) then
        -- Allow changing the CCPI QLMs if they are in software mode
        if cavium.csr.GSERX_SPD(8).SPD == 0xf then
            qlm_max = 13
        end
    else
        qlm_max = 6
    end
    local m = menu.new("Select a QLM to Configure")
    repeat
        for index = 0, qlm_max do
            local qlm_num = qlm_display_order[index]
            local mode = cavium.c.bdk_qlm_get_mode(menu.node, qlm_num)
            local config_mode = cavium.c.bdk_qlm_mode_tostring(mode)
            local config_speed = cavium.c.bdk_qlm_get_gbaud_mhz(menu.node, qlm_num)
            local num_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm_num)
            local name = qlm_external_name[qlm_num]
            local ref_clock = cavium.c.bdk_qlm_measure_clock(menu.node, qlm_num)
            local option
            if config_speed == 0 then
                option = "%s - Disabled" % name
            else
                option = "%s - %s @%2d.%03d GBaud, ref %3d.%03d Mhz" % {name, config_mode, config_speed / 1000, config_speed % 1000, ref_clock / 1000000, ref_clock / 1000 % 1000}
            end
            m:item(name, option, do_setup, qlm_num)
        end
        m:item("quit", "Exit menu")
    until (m:show() == "quit")
end

