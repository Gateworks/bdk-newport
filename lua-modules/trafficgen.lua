-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

require("strict")
require("utils")
local readline = require("readline")

local GOTO_TOP      = "\27[1;1H"   -- ESC[1;1H begins output at the top of the terminal (line 1)
local GOTO_BOTTOM   = "\27[100;1H" -- ESC[1;1H begins output at the bottom of the terminal (actually line 100)
local GOTO_BOL      = "\27[100D"   -- Go to beginning of line
local ERASE_EOL     = "\27[0K"     -- Erase to end of line
local ERASE_EOS     = "\27[0J"     -- Erase to end screen
local ERASE_WIN     = "\27[2J"     -- Erase the window
local REVERSE       = "\27[7m"     -- Reverse the display
local NORMAL        = "\27[0m"     -- Normal display
local NONZEROHI     = "\27[33m"    -- Yellow used for non zero rows
local ZEROHI        = "\27[32m"    -- Green used for zero rows
local SCROLL_FULL   = "\27[1;r"    -- Normal full-screen scrolling for statistics region
local CURSOR_ON     = "\27[?25h"   -- Turn on cursor
local CURSOR_OFF    = "\27[?25l"   -- Turn off cursor

local ALIASES = {
    ["F1"]="help",
    ["F9"]="validate all on",
    ["F10"]="stop all",
    ["F11"]="start default",
    ["F12"]="stop default",
    ["PageUp"]="clear all",
    ["PageDown"]="clear default",
}

local TrafficGen = {}
function TrafficGen.new()
    octeontx.c.bdk_init_nodes(0, 0)
    local self = {}
    --
    -- Private variables
    --
    local DISPLAY_INTERVAL = 1000000 -- 1 second
    if octeontx.is_platform(octeontx.PLATFORM_EMULATOR) then
        DISPLAY_INTERVAL = 1000 -- 1ms
    end
    local visible_ports = {}
    local default_ports = {}
    local is_default_port = {}
    local is_running = true
    local use_readline = true
    local last_display = octeontx.time_us()
    local transmit_start = 0
    local transmit_time = 0
    local l2_stats_table = {}
    local show_l2_stats = false
    local ccpi_stats = {[0] = {{0,0,0}, {0,0,0}, {0,0,0}}, [1] = {{0,0,0}, {0,0,0}, {0,0,0}}}

    --
    -- Public variables
    --

    --
    -- Private Methods
    --
    local function get_known_ports()
        return octeontx.trafficgen.get_port_names()
    end

    -- Parse a port list string
    local function parse_port_list(str)
        local ports = {}
        local index = 1
        local start_name = nil
        str = str:upper()
        while index <= #str do
            local name, sep = str:match("^([A-Za-z0-9.]+)([*,-]?)", index)
            -- printf("name='%s', sep='%s', index=%d\n", name, sep, index);
            if not name then
                if str:sub(index,index) == "*" then
                    name = ""
                    sep = "*"
                elseif str:sub(index,index) == "," then
                    name = ","
                    sep = ""
                else
                    -- printf("no name found in %s\n", str:sub(index))
                    return nil
                end
                start_name = nil
            end
            index = index + #name + #sep
            -- printf("name='%s', sep='%s', index=%d\n",name,sep,index)
            if sep == "-" then
                start_name = name
            elseif sep == "*" then
                local prefix = name
                local suffix = str:match("^([A-Za-z0-9.]*)", index)
                index = index + #suffix
                for _,port in ipairs(get_known_ports()) do
                    -- printf("%s[1,%d]='%s' vs '%s', %s[%d,-1] = '%s' vs '%s'",
                    --     port, #prefix, port:sub(1,#prefix), prefix, port, -#suffix, port:sub(-#suffix,-1), suffix)

                    if port:sub(1,#prefix) == prefix and (#suffix == 0 or port:sub(-#suffix,-1) == suffix) then
                        table.insert(ports, port)
                        -- printf(" -- match")
                    end
                    -- printf("\n")
                end
                start_name = nil
            elseif not (name == ",") then
                local stop_name = name
                if not start_name then
                    start_name = stop_name
                end
                local in_range = false
                for _,port in ipairs(get_known_ports()) do
                    -- printf("port = '%s', start_name='%s'\n", port, start_name);
                    if port == start_name then
                        in_range = true
                    end
                    if in_range then
                        table.insert(ports, port)
                    end
                    if port == stop_name then
                        in_range = false
                    end
                end
                start_name = nil
            end
        end
        if #ports == 0 then
            -- printf("no ports found\n");
            return nil
        else
            return ports
        end
    end

    -- Build a mapping from stuff in range to true
    local function make_is_entry(range)
        local result = {}
        for _,entry in ipairs(range) do
           result[entry] = true
        end
        return result
    end

    -- Add stuff in range to list unless it is already there
    local function add_entries(list, range)
        local is_entry = make_is_entry(list)
        for _,entry in ipairs(range) do
           if not is_entry[entry] then
               table.insert(list, entry)
           end
        end
        return list
    end

    -- Build a new list with everything in the old list but not in range
    local function remove_entries(list, range)
        local is_entry = make_is_entry(range)
        local result = {}
        for _,entry in ipairs(list) do
           if not is_entry[entry] then
               table.insert(result, entry)
           end
        end
        return result
    end

    local function do_update(zero_stats)
        local stats = octeontx.trafficgen.update(zero_stats)
        local labels = stats.labels
        stats.labels = nil
        local result = {}
        for p,s in pairs(stats) do
            result[p] = {}
            for i=1, #labels do
                result[p][labels[i]] = s[i]
            end
        end
        return result
    end

    -- Get current "up" (link speed != 0) ports (ignoring FAKE ports)
    local function get_up_port_list()
        local ports = {}
        local stats = do_update(false)
        for _,port in ipairs(get_known_ports()) do
            if not port:find("FAKE") and not port:find("LBK") then
                 -- printf("stats[%s].link_speed = %d\n", port, stats[port].link_speed);
                 if stats[port].link_speed > 0 then
                    table.insert(ports, port)
                end
            end
        end
        if #ports == 0 then
            return nil
        else
            return ports
        end
    end

    -- Parse a command line into a command, a port range, and arguments
    local function parse_command(str)
        local SPECIAL_WORDS = {["true"]=true, ["false"]=false, ["on"]=true, ["off"]=false}
        local command
        local range
        local args = {}
        local word_num = 0
        for word in str:gmatch("[^ ]+") do
            word_num = word_num + 1
            if word_num == 1 then
                -- replace '.' in command with '_' for compatibility with old traffic-gen
                -- note: also in readline for tab completion, but here in case readline is off
                word:gsub(".", "_")
                for _,prefix in ipairs({"cmdp_", "cmd_"}) do
                    command = prefix .. word
                    if type(self[command]) == "function" then
                        break;
                    end
                end
            elseif word_num == 2 then
                if command:sub(1,5) == "cmdp_" then
                    if word == "all" then
                        range = get_known_ports()
                    elseif word == "up" then
                        range = get_up_port_list()
                    elseif word == "default" then
                        range = default_ports
                    else
                        range = parse_port_list(word)
                        if range == nil then
                            if SPECIAL_WORDS[word] ~= nil then
                                table.insert(args, SPECIAL_WORDS[word])
                            else
                                table.insert(args, word)
                            end
                        end
                    end
                elseif SPECIAL_WORDS[word] ~= nil then
                    table.insert(args, SPECIAL_WORDS[word])
                else
                    table.insert(args, word)
                end
            elseif SPECIAL_WORDS[word] ~= nil then
                table.insert(args, SPECIAL_WORDS[word])
            else
                table.insert(args, word)
            end
        end
        if range == nil then
            if command:sub(1,5) == "cmdp_" then
                range = default_ports
            end
        end
        return command, range, args
    end

    local zero_hide = {
        rx_backpressure=-5,
        rx_dropped_octets=-5,
        rx_dropped_packets=-5,
        rx_errors=-5,
        rx_validation_errors=-5,
        rx_rsfec_corrected=-5,
        rx_rsfec_uncorrected=-5,
        rx_rsfec_symbol=-5,
        rx_fec_corrected=-5,
        rx_fec_uncorrected=-5,
    }
    -- Display a single statistic line
    local function display_stat(stat_name, stats)
        local ZERO_HIDE_TIME = 5000000 -- 5 seconds
        if octeontx.is_platform(octeontx.PLATFORM_EMULATOR) then
            ZERO_HIDE_TIME = 5000 -- 5 ms
        end
        local current_time = octeontx.time_us()
        local totals = 0
        for _,p in ipairs(visible_ports) do
            totals = totals + stats[p][stat_name]
        end
        local color = NORMAL
        if zero_hide[stat_name] then
            if totals == 0 then
                if zero_hide[stat_name] + ZERO_HIDE_TIME < current_time then
                    return 0
                end
                color = ZEROHI
            else
                zero_hide[stat_name] = current_time
                color = NONZEROHI
            end
        end
        local COL_SEP = ZEROHI .. "|" .. color
        local is_bits = stat_name:sub(-5,-1) == "_bits"
        if is_bits then
            printf(color .. "%-20s", stat_name:sub(1,-6) .. " Mbps")
        else
            printf(color .. "%-20s", stat_name:gsub("_", " "))
        end
        for _,p in ipairs(visible_ports) do
            local v = stats[p][stat_name]
            if is_bits then
                v = (v + 500000) / 1000000
            end
            printf("%s%12s", COL_SEP, v)
        end
        if is_bits then
            totals = (totals + 500000) / 1000000
        end
        printf("%s%12d%s%s\n", COL_SEP, totals, NORMAL, ERASE_EOL)
        return 1
    end

    -- Create commands for getting and setting each value in the port config
    -- structure.
    local function create_config_commands()
        local known_ports = get_known_ports()
        local config = octeontx.trafficgen.get_config(known_ports[1])
        -- Add in sorted order
        for _,field_name in ipairs(table.sorted_keys(config)) do
            self["cmdp_" .. field_name] = function (self, port_range, args)
                for _, port in pairs(port_range) do
                    if #args == 1 then
                        octeontx.trafficgen.set_config(port, {[field_name]=args[1]})
                    else
                        local config = octeontx.trafficgen.get_config(port)
                        printf("Port %s: %s = %s\n", port, field_name, tostring(config[field_name]))
                    end
                end
            end
        end
    end
    create_config_commands()

    -- Create commands for getting each value in the port statistics.
    local function create_stats_commands()
        local stats = do_update(false)
        local known_ports = get_known_ports()
        local stat_names = stats[known_ports[1]]
        -- Add in sorted order
        for _,field_name in ipairs(table.sorted_keys(stat_names)) do
            self["cmdp_" .. field_name] = function (self, port_range, args)
                local stats = do_update(false)
                for _, port in pairs(port_range) do
                    printf("Port %s: %s = %s\n", port, field_name, tostring(stats[port][field_name]))
                end
            end
        end
    end
    create_stats_commands()

    --
    -- Public Methods
    --

    -- Print a list of all commands
    function self:cmd_help(port_range, args)
        local commands = {}
        for k in pairs(ALIASES) do
            table.insert(commands, "<" .. k .. ">=\"" .. ALIASES[k] .. "\"")
        end
        for k in pairs(self) do
            if k:sub(1,4) == "cmd_" then
                table.insert(commands, k:sub(5))
            end
            if k:sub(1,5) == "cmdp_" then
                table.insert(commands, k:sub(6))
            end
        end
        table.sort(commands)
        local clm = (#commands+2)/3
        for i=1,clm do
            if commands[i] then
                printf("%-27s ", commands[i])
            end
            if commands[i+clm] then
                printf("%-27s ", commands[i+clm])
            end
            if commands[i+clm*2] then
                printf("%-27s ", commands[i+clm*2])
            end
            printf("\n")
        end
        print()
        print("Most commands take an optional port range.  The port range is")
        print("specified as a series of names separated by commas or dashes.")
        print("Dashes include all ports between the named ports.  No spaces")
        print("are allowed in a port range. One '*' is allowed as a wildcard")
        print("in the port name. Some example port ranges are \"SGMII*\",")
        print("\"SGMII0.0-SGMII0.3\", \"XAUI0,XAUI1\", and \"40GKR0-40GKR1\".")
        print("When not specified, the port range is taken from the range")
        print("given in the last \"default\" command.  For a full list of the")
        print("supported port names, type the command \"default all\".")
    end

    -- Select which ports to used by default
    function self:cmdp_default(port_range, args)
        assert (#args == 0, "No arguments expected")

        default_ports = port_range

        is_default_port = {}

        printf("Default ports:")
        for _,port in ipairs(default_ports) do
            printf(" %s", port)
            is_default_port[port] = true
        end
        printf("\n")
        return default_ports
    end

    -- Quit the main run() loop
    function self:cmd_quit(port_range, args)
        assert (#args == 0, "No arguments expected")
        is_running = false
    end

    -- Enable/disable readline so scripting can be easier
    function self:cmd_readline(port_range, args)
        assert (#args == 1, "One argument expected (on/off)")
        use_readline = args[1]
    end

    function self:cmdp_start(port_range, args)
        assert (#args == 0, "Problem parsing port range or have an unexpected argument")
        octeontx.trafficgen.start(port_range)
    end

    function self:cmdp_stop(port_range, args)
        assert (#args == 0, "Problem parsing port range or have an unexpected argument")
        octeontx.trafficgen.stop(port_range)
    end

    function self:cmdp_show(port_range, args)
        assert (#args == 0, "Problem parsing port range or have an unexpected argument")
        visible_ports = add_entries(visible_ports, port_range)
    end

    function self:cmdp_hide(port_range, args)
        assert (#args == 0, "Problem parsing port range or have an unexpected argument")
        visible_ports = remove_entries(visible_ports, port_range)
        if #visible_ports == 0 then
            printf(SCROLL_FULL .. GOTO_BOTTOM)
        end
    end

    function self:cmdp_clear(port_range, args)
        assert (#args == 0, "Problem parsing port range or have an unexpected argument")
        octeontx.trafficgen.clear(port_range)
    end

    function self:cmdp_reset(port_range, args)
        assert (#args == 0, "No arguments expected")
        octeontx.trafficgen.reset(port_range)
    end

    function self:cmdp_unplug(port_range, args)
        assert (#args == 0, "No arguments expected")
        octeontx.trafficgen.unplug(port_range)
    end

    function self:cmdp_plug(port_range, args)
        assert (#args == 1, "One argument expected")
        octeontx.trafficgen.plug(port_range, args[1])
    end

    function self:cmdp_loopback(port_range, args)
        assert (#args == 1, "Argument expected, either INTERNAL, EXTERNAL, INTERNAL+EXTERNAL, or NONE")
        for _,port in pairs(port_range) do
            octeontx.trafficgen.set_loopback(port, args[1])
        end
    end

    function self:cmdp_tx_percent(port_range, args)
        for _,port in pairs(port_range) do
            if #args == 1 then
                octeontx.trafficgen.set_config(port, {output_rate_is_mbps = true, output_rate = args[1] * 10})
            else
                local config = octeontx.trafficgen.get_config(port)
                if config.output_rate_is_mbps then
                    printf("Port %s: %d Mbps\n", port, config.output_rate)
                else
                    printf("Port %s: %d packets/s\n", port, config.output_rate)
                end
            end
        end
    end

    function self:cmdp_tx_rate(port_range, args)
        for _,port in pairs(port_range) do
            if #args == 1 then
                octeontx.trafficgen.set_config(port, {output_rate_is_mbps = false, output_rate = args[1]})
            else
                local config = octeontx.trafficgen.get_config(port)
                if config.output_rate_is_mbps then
                    printf("Port %s: %d Mbps\n", port, config.output_rate)
                else
                    printf("Port %s: %d packets/s\n", port, config.output_rate)
                end
            end
        end
    end

    -- CSR access command only needed if we have a CSR database
    if octeontx.csr then
        function self:cmd_csr(port_range, args)
            assert(args[1], "CSR name[.field] expected with optional value for write")
            local value = args[2]
            local dot = args[1]:find(".", 2, true)
            if dot then
                local name = args[1]:sub(1,dot-1):upper()
                local field = args[1]:sub(dot+1):upper()
                if value then
                    octeontx.csr[name][field] = value
                else
                    local v = octeontx.csr[name][field]
                    printf("%s.%s = %d (0x%x)\n", name, field, v, v)
                end
            else
                local name = args[1]:upper()
                if value then
                    octeontx.csr.lookup(name).write(value)
                else
                    octeontx.csr.lookup(name).display()
                end
            end
        end

        function self:cmd_csra(port_range, args)
            assert(args[1], "CSRA name and value expected for atomic load and add")
            assert(args[2], "CSRA name and value expected for atomic load and add")
            local value = args[2]
            local name = args[1]:upper()
            value = octeontx.csr.lookup(name).load_add(value)
            octeontx.csr.lookup(name).display(value)
        end

        -- Command to dump all CSRs with a given prefix
        function self:cmd_dump_csr(port_range, args)
            assert(args[1], "CSR prefix expected")
            local prefix = args[1]:upper()
            local nozero = args[2]
            local len = #prefix
            printf("Searching CSRs for prefix \"%s\". This is slow...\n", prefix)
            for name in octeontx.csr(prefix) do
                local s = name:sub(1,len)
                if name:find("PKO_VFX_DQX_MP_STATEX", 1, true) or
                    name:find("PKO_VFX_DQX_PD_STATEX", 1, true) or
                    name:find("PKO_VFX_DQX_OP_", 1, true) then
                    -- Skip, crashes core on CN83XX
                elseif s == prefix then
                    local c = octeontx.csr.lookup(name)
                    if nozero then
                        local v = c.read()
                        if v ~= 0 then
                            c.display(v)
                        end
                    else
                        c.display()
                    end
                elseif s > prefix then
                    return
                end
            end
        end

        -- Command to show all CSRs with a given prefix and suffix
        function self:cmd_show_csrs(port_range, args)
            assert(args[1], "CSR prefix expected")
            assert(args[2], "CSR suffix expected")
            local prefix = args[1]:upper()
            local suffix = args[2]
            local lenp = #prefix
            local lens = #suffix
            printf("Searching CSRs for prefix \"%s\" and suffix \"%s\". This is slow...\n", prefix, suffix)
            for name in octeontx.csr(prefix) do
                local p = name:sub(1,lenp)
                local s = name:sub(-lens,-1)
                if p == prefix and s == suffix then
                    local c = octeontx.csr.lookup(name)
		    c.display()
                elseif p > prefix then
                    return
                end
            end
        end
    end

    function self:cmd_threads(port_range, args)
        octeontx.c.bdk_thread_show_stats()
    end

    function self:cmd_cls(port_range, args)
        assert (#args == 0, "No arguments expected")
        printf(ERASE_WIN .. GOTO_BOTTOM);
    end

    function self:cmd_reboot(port_range, args)
        assert (#args == 0, "No arguments expected")
        printf(SCROLL_FULL .. GOTO_BOTTOM)
        io.flush()
        octeontx.c.bdk_reset_chip(octeontx.MASTER_NODE)
    end

    function self:cmd_l2_stats(port_range, args)
        assert (#args == 1, "One argument expected, on or off")
        show_l2_stats = args[1]
    end

    function self:cmd_sleep(port_range, args)
        assert (#args == 1, "One argument expected, how long to sleep in seconds")
        printf("Sleeping for %d seconds\n", args[1])
        local timeout = octeontx.time_us() + args[1] * 1000000
        while octeontx.time_us() < timeout do
            self:display(false)
        end
    end

    function self:cmd_wait_links(port_range, args)
        local timeout = 30 -- Seconds
        if args[1] then
            timeout = args[1]
        end
        timeout = timeout * 1000000
        local status = octeontx.c.bdk_if_link_wait_all(timeout);
        if status ~= 0 then
            printf("Timeout before all links are up\n")
        end
    end

    function self:cmdp_scan_sizes(port_range, args)
        -- Optional arguments
        --  args[1] = packet count, defaults to 100
        --  args[2] = min packet size, defaults to 60
        --  args[3] = max packet size, default is calculated
        --  args[4] = increment, defaults to 1
        --  args[5] = scan loop count, defaults to 1
        -- Get the size of one buffer
        local buf_size = octeontx.c.bdk_config_get_int(octeontx.CONFIG_PACKET_BUFFER_SIZE)
        -- BGX/NIC on CN8XXX only allows a max of 9212 bytes (9216 with FCS added)
        local max_packet = 9212
        -- Get our setup params
        local output_count = args[1] or 100
        local size_start = args[2] or 60
        local size_stop = args[3] or max_packet
        local size_incr = args[4] or 1
        local scan_loop_stop = args[5] or 1
        -- Tell the user what we are doing
        printf("Scan sizes on ports:")
        for _,port in ipairs(port_range) do
            printf(" %s", port)
        end
        printf("\n")
        printf("Send %d packets, min size %d, max size %d, increment %d, loops %d\n",
            output_count, size_start, size_stop, size_incr, scan_loop_stop)
        -- Get the latest statistics
        local all_stats = self:display(true)
        -- Start with current counts
        local expected_packets = 0
        local expected_octets = 0
        local expected_rx_errors = 0
        local expected_validation_errors = 0
        for _,port in ipairs(port_range) do
            expected_packets = expected_packets + all_stats[port].rx_packets_total
            expected_octets = expected_octets + all_stats[port].rx_octets_total
            expected_rx_errors = expected_rx_errors + all_stats[port].rx_errors
            expected_validation_errors = expected_validation_errors + all_stats[port].rx_validation_errors
        end

        -- Loop through the sizes
        local new_config = {output_count = output_count}
        for _,port in ipairs(port_range) do
            octeontx.trafficgen.set_config(port, new_config)
        end
        new_config.output_count=nil
	for scan_loop=1,scan_loop_stop,1 do
	    local validation_errors
            for size=size_start,size_stop,size_incr do
	        if scan_loop_stop == 1 then
                    printf("Size %d\n", size)
                else
                    printf("Loop %d: Size %d\n", scan_loop, size)
		end
                new_config.size = size;
                -- Setup TX and count how many packets we expect
                for _,port in ipairs(port_range) do
                    octeontx.trafficgen.set_config(port, new_config)
                    expected_packets = expected_packets + output_count
                    if port:find("LBK") or port:find("FAKE") then
                        -- Loop doesn't have the 4 bytes of ethernet CRC
                        expected_octets = expected_octets + output_count * size
                    else
                        -- Account for the extra 4 bytes of ethernet CRC
                        expected_octets = expected_octets + output_count * (size+4)
                    end
                end
                -- Limit to five seconds per size
                local timeout = octeontx.time_us() + 5000000
                if octeontx.is_platform(octeontx.PLATFORM_EMULATOR) then
                    timeout = octeontx.time_us() + 5000 -- 5 ms
                end
                -- Do the TX
                octeontx.trafficgen.start(port_range)
                while octeontx.trafficgen.is_transmitting(port_range) and (octeontx.time_us() < timeout) do
                    if octeontx.global == nil then
                        -- Waiting for TX to be done
                        octeontx.c.bdk_thread_yield();
                    end
                    -- Get the latest statistics
                    self:display(false)
                end
                local rx_packets
                local rx_octets
                local rx_errors
                repeat
                    if octeontx.global == nil then
                        octeontx.c.bdk_thread_yield();
                    end
                    -- Get the latest statistics
                    all_stats = self:display(true)
                    -- Count the amount of data received
                    rx_packets = 0
                    rx_octets = 0
                    rx_errors = 0
                    validation_errors = 0
                    for _,port in ipairs(port_range) do
                        rx_packets = rx_packets + all_stats[port].rx_packets_total
                        rx_octets = rx_octets + all_stats[port].rx_octets_total
                        rx_errors = rx_errors + all_stats[port].rx_errors
                        validation_errors = validation_errors + all_stats[port].rx_validation_errors
                    end
                until ((rx_packets >= expected_packets) and (rx_octets >= expected_octets)) or (octeontx.time_us() >= timeout)
                -- Make sure we got the right amount of data
                if (rx_packets ~= expected_packets) or (rx_octets ~= expected_octets) then
                    if octeontx.time_us() >= timeout then
                        printf("Scan timeout\n")
                    else
                        printf("Scan failed\n")
                    end
                    printf("RX packets %d, octets %d\n", rx_packets, rx_octets)
                    printf("Expected packets %d, octets %d\n", expected_packets, expected_octets)
                    printf("Delta packets %d, octets %d\n", expected_packets - rx_packets, expected_octets - rx_octets)
                    break
                end
                if (rx_errors ~= expected_rx_errors) then
                    printf("Scan failed due to RX errors\n")
                    break
                end
                if (validation_errors ~= expected_validation_errors) then
                    printf("Scan failed due to validation errors\n")
                    break
                end
            end
        end
    end

    function self:cmdp_perf_test(port_range, args)
        local validation_on = (args[1] == "val")
        local USEC = 1000000
        if octeontx.is_platform(octeontx.PLATFORM_EMULATOR) then
            USEC = 1000 -- Speed up test 1000x on the emulator
        end
        -- Tell the user what we are doing
        printf("Performance test on ports:")
        for _,port in ipairs(port_range) do
            printf(" %s", port)
        end
        printf("\n")
        -- These are the packet sizes we're try
        local PACKET_SIZES = {60, 128, 256, 512, 1024, 2048, 4096, 8192, 9212}
        -- Stop all traffic before starting the test
        octeontx.trafficgen.stop(get_known_ports())
        printf("Turning validation %s\n", validation_on and "on" or "off")
        for _,port in ipairs(get_known_ports()) do
            octeontx.trafficgen.set_config(port, {validate = validation_on})
        end
        printf("Starting performance test\n")
        local new_config = {
            output_count = 0,
            output_rate_is_mbps = true,
            output_rate = 110000}
        for _,size in ipairs(PACKET_SIZES) do
            -- Get the latest statistics, don't zero reference
            local stats = do_update(false)
            -- Start with current counts
            local expected_rx_errors = {}
            local expected_validation_errors = {}
            for _,port in ipairs(port_range) do
                expected_rx_errors[port] = stats[port].rx_errors
                expected_validation_errors[port] = stats[port].rx_validation_errors
            end
            new_config.size = size;
            for _,port in ipairs(port_range) do
                octeontx.trafficgen.set_config(port, new_config)
            end
            -- Do the TX
            octeontx.trafficgen.start(port_range)
            -- Let the traffic stabalize before starting measurement
            octeontx.c.bdk_wait_usec(1 * USEC)
            -- Update stats, signalling measurement start
            do_update(true)
            -- Duration the measurement is over
            octeontx.c.bdk_wait_usec(3 * USEC)
            -- Stop the measurement
            stats = do_update(false)
            -- Stop the traffic
            octeontx.trafficgen.stop(port_range)
            -- Calculate the receive rate
            local tx_mbps = 0
            local rx_mbps = 0
            local tx_pps = 0
            local rx_pps = 0
            for port,stat in pairs(stats) do
                tx_mbps = tx_mbps + (stat.tx_bits + 500000) / 1000000
                rx_mbps = rx_mbps + (stat.rx_bits + 500000) / 1000000
                tx_pps = tx_pps + stat.tx_packets
                rx_pps = rx_pps + stat.rx_packets
            end
            printf("Size %4d: TX %5d Mbps (%8d pps), RX %5d Mbps (%8d pps)\n", size, tx_mbps, tx_pps, rx_mbps, rx_pps)
            -- Check error stats
            for _,port in ipairs(port_range) do
                local errors = stats[port].rx_errors - expected_rx_errors[port]
                if errors ~= 0 then
                    printf("%s: %d RX errors during perf_test\n", port, errors)
                end
                errors = stats[port].rx_validation_errors - expected_validation_errors[port]
                if errors ~= 0 then
                    printf("%s: %d Validation errors during perf_test\n", port, errors)
                end
            end
        end
        -- Let the traffic drain before turning on validation
        octeontx.c.bdk_wait_usec(1 * USEC)
        if not validation_on then
            printf("Perf test complete, turning validation on\n")
            for _,port in ipairs(get_known_ports()) do
                octeontx.trafficgen.set_config(port, {validate = true})
            end
        end
    end

    function self:cmdp_margin_rx(port_range, args)
        if not octeontx.is_model(octeontx.CN8XXX) then
            printf("Margining not support on this chip\n")
            return
        end
        local MARGIN_PASS = 6 -- To pass, max-min must be greater than equal to this
        local USEC = 1000000
        local function do_test(port, vert)
            local stats = do_update(true)
            local start_errors = stats[port].rx_errors
            octeontx.c.bdk_wait_usec(1 * USEC)
            local stats = do_update(false)
            local errors = stats[port].rx_errors - start_errors
            -- printf("    %d - %s\n", vert, (errors > 0) and "FAIL" or "PASS")
            return errors
        end
        for _,port in ipairs(port_range) do
            local config = octeontx.trafficgen.get_config(port)
            if #config.serdes_map == 0 then
                printf("%s: Doesn't use SERDES, skipping\n", port)
                goto skip_port
            end
            -- Update stats, signalling measurement start
            do_update(true)
            -- Measure 1 second to make sure we are receiving packets
            octeontx.c.bdk_wait_usec(1 * USEC)
            -- Stop the measurement
            local stats = do_update(false)
            if stats[port].rx_packets == 0 then
                printf("%s: No RX packets, skipping\n", port)
                goto skip_port
            end
            printf("%s: Measuring Eye Height\n", port)
            for i = 1,#config.serdes_map,2 do
                local node = config.node
                local qlm = config.serdes_map[i]
                local qlm_lane = config.serdes_map[i+1]
                local avg_eye_height = 0
                local avg_count = 3
                for avg_repeat=1,avg_count do
                    local vert_center = octeontx.c.bdk_qlm_margin_rx_get(node, qlm, qlm_lane, octeontx.QLM_MARGIN_VERTICAL);
                    local vert_min = octeontx.c.bdk_qlm_margin_rx_get_min(node, qlm, qlm_lane, octeontx.QLM_MARGIN_VERTICAL);
                    local vert_max = octeontx.c.bdk_qlm_margin_rx_get_max(node, qlm, qlm_lane, octeontx.QLM_MARGIN_VERTICAL);

                    for vert = vert_center,vert_max do
                        octeontx.c.bdk_qlm_margin_rx_set(node, qlm, qlm_lane, octeontx.QLM_MARGIN_VERTICAL, vert);
                        if do_test(port, vert) > 0 then
                            vert_max = vert - 1
                            break
                        end
                    end

                    for vert = vert_center,vert_min,-1 do
                        octeontx.c.bdk_qlm_margin_rx_set(node, qlm, qlm_lane, octeontx.QLM_MARGIN_VERTICAL, vert);
                        if do_test(port, vert) > 0 then
                            vert_min = vert + 1
                            break
                        end
                    end
                    octeontx.c.bdk_qlm_margin_rx_restore(node, qlm, qlm_lane, octeontx.QLM_MARGIN_VERTICAL, vert_center);
                    -- printf("%s QLM%d Lane %d: Min=%d, Middle=%d, Max=%d\n", port, qlm, qlm_lane, vert_min, vert_center, vert_max)
                    local eye_height = (vert_max - vert_min) + 1
                    avg_eye_height = avg_eye_height + eye_height
                end
                local eye_height = avg_eye_height / avg_count
                local status = (eye_height >= MARGIN_PASS) and "PASS" or "FAIL"
                printf("%s QLM%d Lane %d: Eye Height %2d - %s\n", port, qlm, qlm_lane, eye_height, status)
            end
::skip_port::
        end
    end

    -- Short aliases for common commands
    self.cmdp_count = self.cmdp_output_count
    -- These commands are kept around for backwards compatibility
    self.cmdp_output_packet_size = self.cmdp_size
    self.cmdp_tx_size = self.cmdp_size
    self.cmdp_tx_count = self.cmdp_output_count

    -- Delete commands that were created based on fields that aren't useful
    self.cmdp_do_checksum = nil
    self.cmdp_output_enable = nil
    self.cmdp_output_rate = nil
    self.cmdp_output_rate_is_mbps = nil
    self.cmdp_ip_tos = nil

    -- Issue a traffic gen command line
    function self:command(command_line)
        local command, port_range, args = parse_command(command_line)
        if type(self[command]) ~= "function" then
            printf("Invalid command \"%s\"\n", command)
        else
            local status, result = pcall(self[command], self, port_range, args)
            if status then
                return result
            else
                printf("ERROR: %s\n", result)
                return nil
            end
            return result
        end
    end

    function self:display(need_stats)
        local display_cycle = octeontx.time_us()
        if last_display + DISPLAY_INTERVAL > display_cycle then
            if need_stats then
                -- Make sure the stats are updated
                return do_update(false)
            else
                return
            end
        end
        last_display = display_cycle
        local all_stats = do_update(true)

        if #visible_ports == 0 then
            return all_stats
        end

        local num_rows = 0
        printf(CURSOR_OFF .. GOTO_TOP)

        if octeontx.trafficgen.is_transmitting(get_known_ports()) then
            transmit_time = (display_cycle - transmit_start) / 1000000
            printf(NONZEROHI)
        else
            transmit_start = display_cycle
            printf(ZEROHI)
        end
        printf("%4d:%02d:%02d", transmit_time/3600, transmit_time/60%60, transmit_time%60)

        printf(ZEROHI .. "%10s", "Port")
        for _,port in ipairs(visible_ports) do
            local star_or_space = is_default_port[port] and "*" or " "
            printf("|%12s", star_or_space .. port)
        end
        printf("|%12s%s\n%s", "Totals", ERASE_EOL, NORMAL);
        local known_ports = get_known_ports()
        local stat_names = table.sorted_keys(all_stats[known_ports[1]])
        for _,stat_name in ipairs(stat_names) do
            num_rows = num_rows + display_stat(stat_name, all_stats)
        end
        local COL_SEP = ZEROHI .. "|" .. NORMAL
        -- Create a row reporting Lua mem, and C mem
        printf("Lua mem %dKB, C mem %dKB%s\n",
            collectgarbage("count"),
            octeontx.c.get_sbrk() / 1024,
            ERASE_EOL);
        num_rows = num_rows + 1
        if show_l2_stats then
            l2_stats_table = octeontx.perf.get_l2(l2_stats_table)
            -- Function for displaying a 2d array of stats
            local function show_stat_table(group, member0)
                local data = l2_stats_table[group]
                local members = table.sorted_keys(data)
                local names = table.sorted_keys(data[member0])
                printf("%s%-20s", ZEROHI, group)
                for _,member in ipairs(members) do
                    printf("|%10s", member)
                end
                printf("%s%s\n", NORMAL, ERASE_EOL)
                for _,name in ipairs(names) do
                    printf("%-20s", name)
                    for _,member in ipairs(members) do
                        local d = data[member][name] or ""
                        printf("%s%10s", COL_SEP, tostring(d))
                    end
                    printf("%s\n", ERASE_EOL)
                    num_rows = num_rows + 1
                end
            end
            show_stat_table("cmb", "cmb0") -- Show CMB bus data
            show_stat_table("io", "io0") -- Show IO bus data
            show_stat_table("tad", "tad0") -- Show TAD data
        end

        print(ZEROHI .. "-------" .. NORMAL .. ERASE_EOL)
        printf(ERASE_EOL .. "\n");

        -- Confine scrolling region
        printf("\27[%d;r" .. GOTO_BOTTOM .. CURSOR_ON, num_rows + 3)
        if need_stats then
            return all_stats
        else
            return
        end
    end

    function self:build_tab()
        local tab = {}
        for n,v in pairs(self) do
            if n:sub(1,5) == "cmdp_" then
                tab[n:sub(6)] = get_known_ports()
            elseif n:sub(1,4) == "cmd_" then
                local cmd = n:sub(5)
                tab[#tab+1] = cmd
            end
        end
        return tab
    end

    function self:get_stats(zero_stats)
        local stats = do_update(zero_stats)
        local result = {}
        for _,port in ipairs(default_ports) do
            result[port] = stats[port]
        end
        return result
    end

    -- Run traffic gen interactively
    function self:run()
        printf(SCROLL_FULL .. GOTO_BOTTOM)
        printf("\n\nBDK Traffic Generator\n\n")
        printf("Type \"help\" for a list of commands\n")
        -- Allow the user to do some trafficgen specific customization. First argument
        -- is trafficgen, so the script can add/remove commands or modify trafficgen.
        utils.run("autorun-trafficgen", self)
        local tab = self:build_tab()
        is_running = true
        while is_running do
            self:display(false)
            local cmd
            if use_readline then
                -- We only need second updates if stats are shown
                local timeout = (#visible_ports == 0) and 0 or DISPLAY_INTERVAL
                -- NOTE: "readline_flags=0x1;" turns on '.' to '_' conversion and is stripped from the prompt
                cmd = readline.readline("readline_flags=0x1;Command> ", tab, timeout)
            else
                printf("Command> ")
                io.flush()
                cmd = io.read("*l")
                print(cmd)
            end
            if ALIASES[cmd] then
                cmd = ALIASES[cmd]
                printf("<%s>\n", cmd)
            end
            if cmd and (cmd ~= "") then
                local status, result = pcall(self.command, self, cmd)
                if not status then
                    printf(GOTO_BOTTOM .. CURSOR_ON .. "ERROR: %s\n", result)
                end
            end
        end
        printf(SCROLL_FULL .. GOTO_BOTTOM)
    end

    return self
end

return TrafficGen
