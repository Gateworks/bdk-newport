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

-- BDK power burn menu.
require("strict")
require("utils")
require("menu")
local bit64 = require("bit64")

--
-- Soft blow a sequence of fuses
--
local function soft_blow(node, start_fuse, num_fuses, value)
    -- Blow MSB to LSB. This way FUSF_LCK is blown last when working
    -- with FUSF_CTL
    for fuse = num_fuses - 1,0,-1 do
        local f = bit64.bextract(value, fuse)
        if f == 1 then
            assert(cavium.c.bdk_fuse_field_soft_blow(node, start_fuse + fuse, f) == 0, "Failed to program fuse")
        end
    end
end

--
-- Prompt for a sequence of FUSF fuses to hard blow
--
local function hard_blow_prompt(prompt_format, num_regs, start_fuse)
    local data = {}
    for i=0,num_regs-1 do
        data[i] = menu.prompt_number(prompt_format % i)
    end
    for i=0,num_regs-1,2 do
        assert(cavium.c.bdk_fuse_field_hard_blow(menu.node, start_fuse + 64 * i,
            data[i], data[i+1]) == 0, "Failed to program fuse")
    end
end

--
-- The NV counter is encodes as a 32bit mask in FUSF_CTL[ROM_T_CNT]. When
-- prompting for this value, convert it to 0-32 instead of a raw bitmask.
--
local function prompt_for_nv_counter(rom_t_cnt)
    -- FUSF_CTL[ROM_T_CNT] is a bitmask representing 0-32 for the secure
    -- NV counter. Prompt for the 0-32 value, not the raw ROM_T_CNT mask
    local nv_counter = 0
    for i=0,31 do
        if bit64.btest(rom_t_cnt, bit64.lshift(1, i)) then
            nv_counter = i+1
        end
    end
    nv_counter = menu.prompt_number("FUSF_CTL[Secure NV counter]", nv_counter, 0, 32)
    return bit64.lshift(1, nv_counter) - 1
end

--
-- Hard blow fuse menu
--
local function hard_blow_menu()
    repeat
        if cavium.csr[menu.node].FUSF_CTL.FUSF_LCK == 1 then
            return
        end
        local m = menu.new("FUSF Fuse Blow Menu")
        m:item_node() -- Adds option to choose the node number
        -- ROT_LCK locks ROTK, HUK, and EK
        if cavium.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
            m:item("hb-rotk", "Hard blow SHA256 of the Root-of-Trust Public Key (ROTK)",
                hard_blow_prompt, "FUSF_ROTK(%d)", 4, 0x300)
        end

        if cavium.csr[menu.node].FUSF_CTL.SSK_LCK == 0 then
            m:item("hb-ssk", "Hard blow Secret Symmetric Key (SSK)",
                hard_blow_prompt, "FUSF_SSK(%d)", 2, 0x400)
        end

        -- ROT_LCK locks ROTK, HUK, and EK
        if cavium.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
            m:item("hb-huk", "Hard blow Hardware Unique Key (HUK)",
                hard_blow_prompt, "FUSF_HUK(%d)", 2, 0x480)
            m:item("hb-ek", "Hard blow ECC Private Endorsement Key (EK)",
                hard_blow_prompt, "FUSF_EK(%d)", 4, 0x500)
        end

        if cavium.csr[menu.node].FUSF_CTL.SW_LCK == 0 then
            m:item("hb-sw", "Hard blow Software Fuses (SW)",
                hard_blow_prompt, "FUSF_SW(%d)", 8, 0x600)
        end

        m:item("hb-ctl", "Hard blow Control Fuses (CTL)", function()
            local ctl = cavium.csr[menu.node].FUSF_CTL.decode()
            ctl.FUSF_LCK =      menu.prompt_number("FUSF_CTL[FUSF_LCK]",        ctl.FUSF_LCK, 0, 1)
            ctl.SSK_LCK =       menu.prompt_number("FUSF_CTL[SSK_LCK]",         ctl.SSK_LCK, 0, 1)
            ctl.ROT_LCK =       menu.prompt_number("FUSF_CTL[ROT_LCK]",         ctl.ROT_LCK, 0, 1)
            ctl.SW_LCK =        menu.prompt_number("FUSF_CTL[SW_LCK]",          ctl.SW_LCK, 0, 1)
            ctl.TZ_FORCE2 =     menu.prompt_number("FUSF_CTL[TZ_FORCE2]",       ctl.TZ_FORCE2, 0, 1)
            ctl.FJ_DIS =        menu.prompt_number("FUSF_CTL[FJ_DIS]",          ctl.FJ_DIS, 0, 1)
            ctl.FJ_TIMEOUT =    menu.prompt_number("FUSF_CTL[FJ_TIMEOUT]",      ctl.FJ_TIMEOUT, 0, 3)
            ctl.FJ_CORE0 =      menu.prompt_number("FUSF_CTL[FJ_CORE0]",        ctl.FJ_CORE0, 0, 1)
            ctl.FJ_DIS_HUK =    menu.prompt_number("FUSF_CTL[FJ_DIS_HUK]",      ctl.FJ_DIS_HUK, 0, 1)
            ctl.CRYPT_NO_DIS =  menu.prompt_number("FUSF_CTL[CRYPT_NO_DIS]",    ctl.CRYPT_NO_DIS, 0, 1)
            ctl.CRYPT_SSK_DIS = menu.prompt_number("FUSF_CTL[CRYPT_SSK_DIS]",   ctl.CRYPT_SSK_DIS, 0, 1)
            ctl.ROM_T_CNT =     prompt_for_nv_counter(ctl.ROM_T_CNT)
            ctl = cavium.csr[menu.node].FUSF_CTL.encode(ctl)
            assert(cavium.c.bdk_fuse_field_hard_blow(menu.node, 0, ctl, 0) == 0, "Failed to program fuse")
        end)
        m:item("quit", "Main menu")
    until m:show() == "quit"
end

--
-- Trusted boot menu
--
repeat
    local m = menu.new("Trusted Boot Menu")
    m:item_node() -- Adds option to choose the node number

    m:item("r-rotk", "Display SHA256 of the Root-of-Trust Public Key (ROTK)", function()
        local k0 = cavium.csr[menu.node].FUSF_ROTPKX(0).read()
        local k1 = cavium.csr[menu.node].FUSF_ROTPKX(1).read()
        local k2 = cavium.csr[menu.node].FUSF_ROTPKX(2).read()
        local k3 = cavium.csr[menu.node].FUSF_ROTPKX(3).read()
        printf("FUSF_ROTK = %016x %016x %016x %016x\n", k0, k1, k2, k3)
    end)

    m:item("r-ssk", "Display Secret Symmetric Key (SSK)", function()
        local k0 = cavium.csr[menu.node].FUSF_SSKX(0).read()
        local k1 = cavium.csr[menu.node].FUSF_SSKX(1).read()
        printf("FUSF_SSK = %016x %016x\n", k0, k1)
        if cavium.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_SSK can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-huk", "Display Hardware Unique Key (HUK)", function()
        local k0 = cavium.csr[menu.node].FUSF_HUKX(0).read()
        local k1 = cavium.csr[menu.node].FUSF_HUKX(1).read()
        printf("FUSF_HUK = %016x %016x\n", k0, k1)
        if cavium.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_HUK can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-ek", "Display ECC Private Endorsement Key (EK)", function()
        local k0 = cavium.csr[menu.node].FUSF_EKX(0).read()
        local k1 = cavium.csr[menu.node].FUSF_EKX(1).read()
        local k2 = cavium.csr[menu.node].FUSF_EKX(2).read()
        local k3 = cavium.csr[menu.node].FUSF_EKX(3).read()
        printf("FUSF_EK = %016x %016x %016x %016x\n", k0, k1, k2, k3)
        if cavium.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_EK can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-sw", "Display Software Fuses (SW)", function()
        local k0 = cavium.csr[menu.node].FUSF_SWX(0).read()
        local k1 = cavium.csr[menu.node].FUSF_SWX(1).read()
        local k2 = cavium.csr[menu.node].FUSF_SWX(2).read()
        local k3 = cavium.csr[menu.node].FUSF_SWX(3).read()
        local k4 = cavium.csr[menu.node].FUSF_SWX(4).read()
        local k5 = cavium.csr[menu.node].FUSF_SWX(5).read()
        local k6 = cavium.csr[menu.node].FUSF_SWX(6).read()
        local k7 = cavium.csr[menu.node].FUSF_SWX(7).read()
        printf("FUSF_SW = %016x %016x %016x %016x\n", k0, k1, k2, k3)
        printf("          %016x %016x %016x %016x\n", k4, k5, k6, k7)
        if cavium.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_SW can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-ctl", "Display Control Fuses (CTL)", function()
        cavium.csr[menu.node].FUSF_CTL.display()
    end)

    -- Only show Soft blow options if fuses aren't locked
    if cavium.csr[menu.node].FUSF_CTL.FUSF_LCK == 0 then
        -- ROT_LCK locks ROTK, HUK, and EK
        if cavium.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
            m:item("sb-rotk", "Soft blow SHA256 of the Root-of-Trust Public Key (ROTK)", function()
                for i=0,3 do
                    local k = menu.prompt_number("FUSF_ROTK(%d)" % i)
                    soft_blow(menu.node, 0x300 + i * 64, 64, k)
                end
            end)
        end

        if cavium.csr[menu.node].FUSF_CTL.SSK_LCK == 0 then
            m:item("sb-ssk", "Soft blow Secret Symmetric Key (SSK)", function()
                for i=0,1 do
                    local k = menu.prompt_number("FUSF_SSK(%d)" % i)
                    soft_blow(menu.node, 0x400 + i * 64, 64, k)
                end
            end)
        end

        -- ROT_LCK locks ROTK, HUK, and EK
        if cavium.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
        m:item("sb-huk", "Soft blow Hardware Unique Key (HUK)", function()
                for i=0,1 do
                    local k = menu.prompt_number("FUSF_HUK(%d)" % i)
                    soft_blow(menu.node, 0x480 + i * 64, 64, k)
                end
            end)

            m:item("sb-ek", "Soft blow ECC Private Endorsement Key (EK)", function()
                for i=0,3 do
                    local k = menu.prompt_number("FUSF_EK(%d)" % i)
                    soft_blow(menu.node, 0x500 + i * 64, 64, k)
                end
            end)
        end

        if cavium.csr[menu.node].FUSF_CTL.SW_LCK == 0 then
            m:item("sb-sw", "Soft blow Software Fuses (SW)", function()
                for i=0,7 do
                    local k = menu.prompt_number("FUSF_SW(%d)" % i)
                    soft_blow(menu.node, 0x600 + i * 64, 64, k)
                end
            end)
        end

        m:item("sb-ctl", "Soft blow Control Fuses (CTL)", function()
            local ctl = cavium.csr[menu.node].FUSF_CTL.decode()
            ctl.FUSF_LCK =      menu.prompt_number("FUSF_CTL[FUSF_LCK]",        ctl.FUSF_LCK, 0, 1)
            ctl.SSK_LCK =       menu.prompt_number("FUSF_CTL[SSK_LCK]",         ctl.SSK_LCK, 0, 1)
            ctl.ROT_LCK =       menu.prompt_number("FUSF_CTL[ROT_LCK]",         ctl.ROT_LCK, 0, 1)
            ctl.SW_LCK =        menu.prompt_number("FUSF_CTL[SW_LCK]",          ctl.SW_LCK, 0, 1)
            ctl.TZ_FORCE2 =     menu.prompt_number("FUSF_CTL[TZ_FORCE2]",       ctl.TZ_FORCE2, 0, 1)
            ctl.FJ_DIS =        menu.prompt_number("FUSF_CTL[FJ_DIS]",          ctl.FJ_DIS, 0, 1)
            ctl.FJ_TIMEOUT =    menu.prompt_number("FUSF_CTL[FJ_TIMEOUT]",      ctl.FJ_TIMEOUT, 0, 3)
            ctl.FJ_CORE0 =      menu.prompt_number("FUSF_CTL[FJ_CORE0]",        ctl.FJ_CORE0, 0, 1)
            ctl.FJ_DIS_HUK =    menu.prompt_number("FUSF_CTL[FJ_DIS_HUK]",      ctl.FJ_DIS_HUK, 0, 1)
            ctl.CRYPT_NO_DIS =  menu.prompt_number("FUSF_CTL[CRYPT_NO_DIS]",    ctl.CRYPT_NO_DIS, 0, 1)
            ctl.CRYPT_SSK_DIS = menu.prompt_number("FUSF_CTL[CRYPT_SSK_DIS]",   ctl.CRYPT_SSK_DIS, 0, 1)
            ctl.ROM_T_CNT =     prompt_for_nv_counter(ctl.ROM_T_CNT)
            ctl = cavium.csr[menu.node].FUSF_CTL.encode(ctl)
            soft_blow(menu.node, 0, 64, ctl)
        end)
        m:item("hb", "Hard blow fuses", hard_blow_menu)
    end
    m:item("quit", "Main menu")
until m:show() == "quit"

