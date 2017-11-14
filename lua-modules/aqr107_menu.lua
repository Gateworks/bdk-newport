-- ***********************license start***********************************
-- Copyright (c) 2003-2016  Cavium Inc. (support@cavium.com). All rights
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

-- BDK USB menu.
-- Displays the GUI interface for configuring and accessing USB.
require("strict")
require("utils")
require("menu")
require("fileio")
local bit64 = require("bit64")

local mdio_bus = 1
local mdio_phy = 0
local doHardReset = 0
local image_file_name = "aqr107_image.cld"
local FS_PREFIX = "/fatfs/boot:"

-- look for valid images and set default name to the first found
local have_images = cavium.aqr107.list(FS_PREFIX)
if have_images then
    image_file_name = have_images[0]
end

( function()
        -- find aquantia device and set mdio_bus and phy addresses
        for bgx =0,1 do
            for port = 0,3 do
                if 0 ~= cavium.c.bdk_config_get_int(cavium.CONFIG_AQUANTIA_PHY,menu.node,bgx,port) then
                    local phyaddr = cavium.c.bdk_config_get_int(cavium.CONFIG_PHY_ADDRESS, menu.node,bgx,port)
                    mdio_bus = bit64.bextract(phyaddr,8,15)
                    mdio_phy =  bit64.bextract(phyaddr,0,7)
                    return
                end
            end
        end
end)()

local function select_file()
    local image_file = menu.prompt_string("Image name", image_file_name)
    local cldhandle = assert(io.open( FS_PREFIX .. image_file,"rb"))
    image_file_name = image_file
    local binimg =  cldhandle:read("*all")
    cldhandle:close()
    return binimg
end

local function cable_diag()
    printf("Initiating cable diagnostics, may take some time...\n")
    if 0 == cavium.c.bdk_aqr_cablediag(menu.node, mdio_bus, mdio_phy) then
        cavium.c.bdk_aqr_cablediag_result(menu.node, mdio_bus, mdio_phy)
    end
end

repeat
    local m = menu.new("AQR-107 Menu")
    m:item_node() -- Adds option to choose the node number

    m:item("port", string.format("Select ARQ-107 device MDIO address (Currently bus %d, phy %d)" , mdio_bus, mdio_phy),
           function()
               mdio_bus = menu.prompt_number("mdio_bus", mdio_bus, 0, 1)
               mdio_phy = menu.prompt_number("mdio_phy", mdio_phy, 0, 31)
    end)

    m:item("info", "Display AQR-107 running image status",
           function()
               cavium.c.bdk_aqr_get_status(menu.node, mdio_bus, mdio_phy)
    end)

    m:item("finfo", "Display AQR-107 flash information",
           function()
               cavium.c.bdk_aqr_flashinfo(menu.node, mdio_bus, mdio_phy)
    end)

    m:item("conn", "Display AQR-107 interface connection status",
           function()
               cavium.c.bdk_aqr_connstat(menu.node, mdio_bus, mdio_phy)
    end)

    m:item("cable", "Cable diagnostics", cable_diag)

    m:item("dump", "AQR-107 register dump",
            function()
                 cavium.c.bdk_aqr_debug_regs(menu.node, mdio_bus, mdio_phy)
    end)

    m:item("trace", "AQR-107 trace",
            function()
                 cavium.c.bdk_aqr_debug_trace(menu.node, mdio_bus, mdio_phy)
    end)

    m:item("rst", "Reset AQR-107 phy",
            function()
                 doHardReset = menu.prompt_number("Reset type 0:soft 1:hard",doHardReset,0,1)
                 cavium.c.bdk_aqr_reset(menu.node, mdio_bus, mdio_phy,doHardReset)
    end)

    m:item("list", "List available phy images",
           function()
               if have_images then
                   for _,imgname in pairs(have_images) do
                       printf("\t%s\n", imgname)
                   end
               else
                   printf("No images...\n")
               end
    end)

    m:item("load", "Load AQR-107 image into phy",
           function()
               local binimg = assert(select_file())
               cavium.aqr107.load(menu.node, mdio_bus, mdio_phy, binimg, #binimg)
    end)

    m:item("write", "Update and verify AQR-107 flash image",
           function()
               local binimg = assert(select_file())
               cavium.aqr107.flash(menu.node, mdio_bus, mdio_phy, binimg, #binimg)
    end)

    m:item("verify", "Verify AQR-107 flash image",
           function()
               local binimg = assert(select_file())
               cavium.aqr107.verify(menu.node, mdio_bus, mdio_phy, binimg, #binimg)
    end)

    m:item("quit", "Main menu")
until m:show() == "quit"

