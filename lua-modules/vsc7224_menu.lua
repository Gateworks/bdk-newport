-- BDK VSC7224 Menu
-- Displays the interface for accessing VSC7224

require("strict")
require("utils")
require("menu")

local xfi = {}

xfi.unit = 0		-- Active 

local function vsc7224_set_unit(twsi_bus, unit)
    -- correct would be to show the inbound/outbound messages depending on board type
    -- and maybe select by twsi_bus as well, but not needed for now
    local board = cavium.c.bdk_config_get_str(cavium.CONFIG_BOARD_MODEL)
    local extrastr = ""

    if board == "sff8304" then
	extrastr = " (0 = outbound SFP+, 1 = inbound SFP+, 2 = outbound QSFP+, 3 = inbound QSFP+)"
    end

    unit = menu.prompt_number("VSC7224 Unit%s" % extrastr, unit, 0, 7)
    xfi.unit = unit
    return unit
end

local function vsc7224_page_dump(twsi_bus, unit)
    --local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    --local ia_width = menu.prompt_number("Internal address width", nil, 0, 2)
    local dev_addr = 0x10 + unit
    local ia_width = 1
    local ia_address = 0x80
    --if ia_width > 0 then
    --    ia_address = menu.prompt_number("Internal address")
    --end

    local num_bytes = 2
    local page_addr = 0x7F
    printf("TWSI addr: %d , addrwidth:%d , regaddr:%2X page_addr:%02X\n", dev_addr, ia_width, ia_address, page_addr)

    local page = menu.prompt_number("Page Number")
    local result = cavium.c.bdk_twsix_write_ia(menu.node, twsi_bus, dev_addr, page_addr, num_bytes, ia_width, page)
    assert(result ~= -1, "TWSI write failed")

    --num_bytes = menu.prompt_number("Number of bytes to read", nil, 1, 4)
    local data = {} 
    for reg_addr = 0x80,255,1 do
	data[reg_addr] = cavium.c.bdk_twsix_read_ia(menu.node, twsi_bus, dev_addr, reg_addr, num_bytes, ia_width)
	assert(data[reg_addr] ~= -1, "TWSI write failed")
    end

    for reg_addr = 0x80,255,1 do
	if (reg_addr % 8) == 0 then
		printf(" %02X: ", reg_addr)
	end
	printf(" %04X", data[reg_addr])
	if ((reg_addr + 1) % 8) == 0 then
		printf("\n")
	end
    end
    printf("\n")
end

local function vsc7224_mode_dump(twsi_bus, unit)
    --local mode = menu.prompt_number("Device XFI Mode PageReg Dump", nil, 0, 1)
    local mode = 0
    local result = cavium.c.bdk_xfi_vsc7224_dump(twsi_bus, unit, mode)
    assert(result ~= -1, "VSC7224 Mode Reg Dump failed")
end

local function vsc7224_modeset(twsi_bus, unit)
    local mode = menu.prompt_number("Device XFI Mode Set: 0-Retimer , 1-Redriver", nil, 0, 1)
    local result = cavium.c.bdk_vsc7224_modeset(twsi_bus, unit, mode)
    assert(result ~= -1, "VSC7224 Mode Set write failed")
end

local function vsc7224_regmap_modeget(twsi_bus, unit)
    --local mode = menu.prompt_number("Device XFI Mode get", nil, 0, 1)
    local result = cavium.c.bdk_vsc7224_regmap_modeget(twsi_bus, unit)
    assert(result ~= -1, "VSC7224 Mode Get Read failed")
end

local function vsc7224_wp_regs(twsi_bus, unit)
    local wp_xfi = menu.prompt_number("XFI Write Protect Regs on/off", nil, 0, 1)
    local result = cavium.c.bdk_vsc7224_wp_regs(twsi_bus, unit, wp_xfi)
    assert(result ~= -1, "VSC7224 XFI Write protect Failed")
end


local function vsc7224_debug()
    local debug = menu.prompt_number("XFI debug on/off", nil, 0, 1)
    local result = cavium.c.bdk_vsc7224_debug(debug)
    assert(result ~= -1, "VSC7224 XFI DEBUG Failed")
end

local function vsc7224_set_reg(twsi_bus, unit)
    local page = menu.prompt_number("VSC7224 Page")
    local reg = menu.prompt_number("Register")
    local val = menu.prompt_number("Value")
    local result = cavium.c.bdk_vsc7224_set_reg(twsi_bus, unit,page,reg,val)
    assert(result ~= -1, "VSC7224 XFI Unit Select Failed")
end


--local function vsc7224_submenu(twsi_bus)
repeat
    local m = menu.new("VSC7224 Menu")
    m:item_node() -- Adds option to choose the node number
    local twsi_bus = 0;
    m:item("xfiunitsel", "VSC7224 Unit (currently %s)" % xfi.unit, vsc7224_set_unit, twsi_bus, xfi.unit)
    m:item("xfiregdump", "VSC7224 Page Reg Dump", vsc7224_page_dump, twsi_bus, xfi.unit)
    m:item("xfiregcdump", "VSC7224 Page Reg C Struct Dump", vsc7224_mode_dump, twsi_bus, xfi.unit)
    m:item("xfimodeset", "VSC7224 Mode Set", vsc7224_modeset, twsi_bus, xfi.unit)
    m:item("xfimodeget", "VSC7224 Mode Get", vsc7224_regmap_modeget, twsi_bus, xfi.unit)
    m:item("xfiwp", "VSC7224 Write Protect", vsc7224_wp_regs, twsi_bus, xfi.unit)
    m:item("xfisetreg", "VSC7224 Set Register", vsc7224_set_reg, twsi_bus, xfi.unit)
    m:item("xfidebug", "VSC7224 Debug En/Dis", vsc7224_debug)
    m:item("quit", "Main menu")
until m:show() == "quit"
