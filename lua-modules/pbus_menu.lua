-- BDK PBUS menu.
-- Displays the GUI interface for accessing PBUS.
require("strict")
require("utils")
require("fileio")
require("menu")

local option = ""
local node = cavium.MASTER_NODE

local function pbus_xmodem(filename)
    local offset = menu.prompt_number("Starting offset", 0)
    local baudrate = menu.prompt_number("Baudrate", 115200)
    printf("Changing baudrate to %d, no flow control\n", baudrate)
    cavium.c.bdk_wait_usec(500000);
    cavium.c.bdk_set_baudrate(cavium.MASTER_NODE, 0, baudrate, 0)
    cavium.c.bdk_wait_usec(500000);
    printf("\nBaudrate is now %d\n", baudrate)
    fileio.copy("/xmodem", nil, "/ram/upload", nil)
    cavium.c.bdk_wait_usec(500000);
    printf("\n\nFile uploaded to /ram/upload\n")
    local do_burn = menu.prompt_yes_no("Write to boot flash", true)
    if do_burn then
        printf("Writing to flash...")
        io.flush()
        fileio.copy("/ram/upload", nil, filename, offset)
        io.flush()
        printf("Done\n")
    end
end

while (option ~= "quit") do
    local m = menu.new("Flash Menu")
    m:item("init", "Query for NOR flash", function()
        cavium.c.bdk_pbus_flash_initialize(node)
    end)
    for chip=0,7 do
        if cavium.c.bdk_pbus_flash_get_base(chip) ~= 0 then
            local filename = utils.devfile("pbus-nor", chip)
            local cs = "(CS" .. tostring(chip) .. ")"

            m:item("view" .. cs, "View NOR flash " .. cs, function()
                local offset = menu.prompt_number("Starting offset")
                local length = menu.prompt_number("Bytes to display")
                fileio.hexdump(filename, offset, length)
            end)

            m:item("write" .. cs, "Write NOR flash " .. cs, function()
                local source = menu.prompt_filename("Enter source filename")
                local offset = menu.prompt_number("Flash offset")
                fileio.copy(source, nil, filename, offset)
            end)
            m:item("xmodem" .. cs, "Xmodem upload to NOR flash " .. cs, pbus_xmodem, filename)
        end
    end
    m:item("quit", "Main menu")
    option = m:show()
end

