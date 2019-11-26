-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
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
            assert(octeontx.c.bdk_fuse_field_soft_blow(node, start_fuse + fuse) == 0, "Failed to program fuse")
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
        assert(octeontx.c.bdk_fuse_field_hard_blow(menu.node, start_fuse + 64 * i,
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
-- The Non-secure NV counter is encodes as a 96bit mask in FUSF_SW0[63:32],
-- FUSF_SW1[63:0]. When prompting for this value, convert it to 0-96 instead
-- of a raw bitmask. We also prompt for bits 31:0 of FUSF_SW0 as a number.
-- This function returns two numbers, one representing FUSF_SW0[63:0], and
-- the second representing FUSF_SW1[63:0]
--
local function prompt_for_non_secure_nv_counter(sw0, sw1)
    local sw0_low_bits = bit64.band(sw0, 0xffffffff)
    local nv_counter = 0
    for i=32,63 do
        if bit64.btest(sw0, bit64.lshift(1, i)) then
            nv_counter = i-31
        end
    end
    for i=0,63 do
        if bit64.btest(sw1, bit64.lshift(1, i)) then
            nv_counter = i+33
        end
    end
    sw0_low_bits = menu.prompt_number("FUSF_SW(0)[31:0]", sw0_low_bits, 0, 0xffffffff)
    nv_counter = menu.prompt_number("FUSF_SW(0-1)[Non-secure NV counter]", nv_counter, 0, 96)
    if nv_counter >= 32 then
        sw0 = bit64.lshift(0xffffffff, 32) + sw0_low_bits
        if nv_counter == 96 then
            sw1 = -1
        else
            sw1 = bit64.lshift(1, nv_counter - 32) - 1
        end
    else
        sw0 = bit64.lshift(bit64.lshift(1, nv_counter) - 1, 32) + sw0_low_bits
        sw1 = 0
    end
    return sw0, sw1
end

--
-- Hard blow fuse menu
--
local function hard_blow_menu()
    repeat
        if octeontx.csr[menu.node].FUSF_CTL.FUSF_LCK == 1 then
            return
        end
        local m = menu.new("FUSF Fuse Blow Menu")
        m:item_node() -- Adds option to choose the node number
        -- ROT_LCK locks ROTK, HUK, and EK
        if octeontx.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
            m:item("hb-rotk", "Hard blow SHA256 of the Root-of-Trust Public Key (ROTK)",
                hard_blow_prompt, "FUSF_ROTK(%d)", 4, 0x300)
        end

        if octeontx.csr[menu.node].FUSF_CTL.SSK_LCK == 0 then
            m:item("hb-ssk", "Hard blow Secret Symmetric Key (SSK)",
                hard_blow_prompt, "FUSF_SSK(%d)", 2, 0x400)
        end

        -- ROT_LCK locks ROTK, HUK, and EK
        if octeontx.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
            m:item("hb-huk", "Hard blow Hardware Unique Key (HUK)",
                hard_blow_prompt, "FUSF_HUK(%d)", 2, 0x480)
            m:item("hb-ek", "Hard blow ECC Private Endorsement Key (EK)",
                hard_blow_prompt, "FUSF_EK(%d)", 4, 0x500)
        end

        if octeontx.csr[menu.node].FUSF_CTL.SW_LCK == 0 then
            m:item("hb-sw", "Hard blow Software Fuses (SW)", function()
                local data = {}
                data[0] = octeontx.csr[menu.node].FUSF_SWX(0).read()
                data[1] = octeontx.csr[menu.node].FUSF_SWX(1).read()
                data[0], data[1] = prompt_for_non_secure_nv_counter(data[0], data[1])
                for i=2,7 do
                    data[i] = menu.prompt_number("FUSF_SW(%d)" % i)
                end
                for i=0,7,2 do
                    assert(octeontx.c.bdk_fuse_field_hard_blow(menu.node, 0x600 + 64 * i,
                        data[i], data[i+1]) == 0, "Failed to program fuse")
                end
            end)
        end

        m:item("hb-ctl", "Hard blow Control Fuses (CTL)", function()
            local ctl = octeontx.csr[menu.node].FUSF_CTL.decode()
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
            ctl = octeontx.csr[menu.node].FUSF_CTL.encode(ctl)
            assert(octeontx.c.bdk_fuse_field_hard_blow(menu.node, 0, ctl, 0) == 0, "Failed to program fuse")
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
        local k0 = octeontx.csr[menu.node].FUSF_ROTPKX(0).read()
        local k1 = octeontx.csr[menu.node].FUSF_ROTPKX(1).read()
        local k2 = octeontx.csr[menu.node].FUSF_ROTPKX(2).read()
        local k3 = octeontx.csr[menu.node].FUSF_ROTPKX(3).read()
        printf("FUSF_ROTK = %016x %016x %016x %016x\n", k0, k1, k2, k3)
    end)

    m:item("r-ssk", "Display Secret Symmetric Key (SSK)", function()
        local k0 = octeontx.csr[menu.node].FUSF_SSKX(0).read()
        local k1 = octeontx.csr[menu.node].FUSF_SSKX(1).read()
        printf("FUSF_SSK = %016x %016x\n", k0, k1)
        if octeontx.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_SSK can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-huk", "Display Hardware Unique Key (HUK)", function()
        local k0 = octeontx.csr[menu.node].FUSF_HUKX(0).read()
        local k1 = octeontx.csr[menu.node].FUSF_HUKX(1).read()
        printf("FUSF_HUK = %016x %016x\n", k0, k1)
        if octeontx.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_HUK can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-ek", "Display ECC Private Endorsement Key (EK)", function()
        local k0 = octeontx.csr[menu.node].FUSF_EKX(0).read()
        local k1 = octeontx.csr[menu.node].FUSF_EKX(1).read()
        local k2 = octeontx.csr[menu.node].FUSF_EKX(2).read()
        local k3 = octeontx.csr[menu.node].FUSF_EKX(3).read()
        printf("FUSF_EK = %016x %016x %016x %016x\n", k0, k1, k2, k3)
        if octeontx.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_EK can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-sw", "Display Software Fuses (SW)", function()
        local k0 = octeontx.csr[menu.node].FUSF_SWX(0).read()
        local k1 = octeontx.csr[menu.node].FUSF_SWX(1).read()
        local k2 = octeontx.csr[menu.node].FUSF_SWX(2).read()
        local k3 = octeontx.csr[menu.node].FUSF_SWX(3).read()
        local k4 = octeontx.csr[menu.node].FUSF_SWX(4).read()
        local k5 = octeontx.csr[menu.node].FUSF_SWX(5).read()
        local k6 = octeontx.csr[menu.node].FUSF_SWX(6).read()
        local k7 = octeontx.csr[menu.node].FUSF_SWX(7).read()
        printf("FUSF_SW = %016x %016x %016x %016x\n", k0, k1, k2, k3)
        printf("          %016x %016x %016x %016x\n", k4, k5, k6, k7)
        if octeontx.csr[menu.node].RST_BOOT.DIS_HUK == 1 then
            printf("WARNING: FUSF_SW can't be read due to RST_BOOT[DIS_HUK]=1\n")
        end
    end)

    m:item("r-ctl", "Display Control Fuses (CTL)", function()
        octeontx.csr[menu.node].FUSF_CTL.display()
    end)

    -- Only show Soft blow options if fuses aren't locked
    if octeontx.csr[menu.node].FUSF_CTL.FUSF_LCK == 0 then
        -- ROT_LCK locks ROTK, HUK, and EK
        if octeontx.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
            m:item("sb-rotk", "Soft blow SHA256 of the Root-of-Trust Public Key (ROTK)", function()
                for i=0,3 do
                    local k = menu.prompt_number("FUSF_ROTK(%d)" % i)
                    soft_blow(menu.node, 0x300 + i * 64, 64, k)
                end
            end)
        end

        if octeontx.csr[menu.node].FUSF_CTL.SSK_LCK == 0 then
            m:item("sb-ssk", "Soft blow Secret Symmetric Key (SSK)", function()
                for i=0,1 do
                    local k = menu.prompt_number("FUSF_SSK(%d)" % i)
                    soft_blow(menu.node, 0x400 + i * 64, 64, k)
                end
            end)
        end

        -- ROT_LCK locks ROTK, HUK, and EK
        if octeontx.csr[menu.node].FUSF_CTL.ROT_LCK == 0 then
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

        if octeontx.csr[menu.node].FUSF_CTL.SW_LCK == 0 then
            m:item("sb-sw", "Soft blow Software Fuses (SW)", function()
                local sw0 = octeontx.csr[menu.node].FUSF_SWX(0).read()
                local sw1 = octeontx.csr[menu.node].FUSF_SWX(1).read()
                sw0, sw1 = prompt_for_non_secure_nv_counter(sw0, sw1)
                soft_blow(menu.node, 0x600 + 0 * 64, 64, sw0)
                soft_blow(menu.node, 0x600 + 1 * 64, 64, sw1)
                for i=2,7 do
                    local k = menu.prompt_number("FUSF_SW(%d)" % i)
                    soft_blow(menu.node, 0x600 + i * 64, 64, k)
                end
            end)
        end

        m:item("sb-ctl", "Soft blow Control Fuses (CTL)", function()
            local ctl = octeontx.csr[menu.node].FUSF_CTL.decode()
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
            ctl = octeontx.csr[menu.node].FUSF_CTL.encode(ctl)
            soft_blow(menu.node, 0, 64, ctl)
        end)
        m:item("hb", "Hard blow fuses", hard_blow_menu)
    end
    m:item("quit", "Main menu")
until m:show() == "quit"

