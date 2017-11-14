# ***********************license start***********************************
# Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
# reserved.
#
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#
#   * Neither the name of Cavium Inc. nor the names of
#     its contributors may be used to endorse or promote products
#     derived from this software without specific prior written
#     permission.
#
# This Software, including technical data, may be subject to U.S. export
# control laws, including the U.S. Export Administration Act and its
# associated regulations, and may be subject to export or import
# regulations in other countries.
#
# TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
# AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
# WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
# TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
# REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
# DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
# OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
# PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
# QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
# ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
# **********************license end**************************************
import time
import test_boot

#
# Start traffic-gen, assuming we are already sitting at the main menu
#
def start_trafficgen(cnx):
    cnx.sendEcho("tg")
    cnx.waitfor("BDK Traffic Generator")
    cnx.match("Type \"help\" for a list of commands")
    cnx.match("(INS)Command> ")
    cnx.write("wait_links\r")
    cnx.waitfor("(INS)Command> ")
    cnx.write("\r")
    cnx.match("(INS)Command> ")

#
# Get a list of known ports in traffic-gen
#
def get_port_list(cnx):
    cnx.sendEcho("default all")
    cnx.match("Default ports:")
    port_str = cnx.matchRE(".+\n").group(0)
    cnx.match("(INS)Command> ")
    port_list = port_str.strip().split()
    # CN83XX LBK and FAKE devices overflow the max length of a traffic-gen
    # command. Don't include them in the test to avoid this
    if cnx.chip_model == "CN83XX":
        port_list = [x for x in port_list if not ("LBK" in x or "FAKE" in x)]
    return port_list

#
# Get a port stat
#
def get_stat(cnx, stat_name, port_list):
    port_str = ",".join(port_list)
    cnx.sendEcho("%s %s" % (stat_name, port_str))
    results = {}
    for port in port_list:
        cnx.match("Port %s: %s =" % (port, stat_name))
        v = cnx.matchRE("[0-9]+\s").group(0)
        v = int(v)
        results[port] = v
    cnx.match("(INS)Command> ")
    return results

#
# Check if a list of ports are up
#
def check_links_up(cnx, port_list):
    results = get_stat(cnx, "link_speed", port_list)
    for port in port_list:
        assert results[port] != 0, "Port %s is down" % port
    return results

#
# Scan all possible packet sizes across the given ports
#
def run_scan_size(cnx, port_list):
    port_str = ",".join(port_list)
    cnx.sendEcho("scan_sizes %s" % port_str)
    for s in range(60, 9213):
        cnx.match("Size %s" % s)
    cnx.match("(INS)Command> ")

#
# Run a performance test across supplied ports
#
def run_perf_test(cnx, port_list):
    port_str = ",".join(port_list)
    cnx.sendEcho("perf_test %s" % port_str)
    cnx.match("Turning validation off")
    cnx.match("Starting performance test")
    results = {}
    for s in [60, 128, 256, 512, 1024, 2048, 4096, 8192, 9212]:
        cnx.match("Size %4d: TX" % s)
        tx_mbps = cnx.matchRE("[0-9]+\s").group(0)
        cnx.match("Mbps, RX")
        rx_mbps = cnx.matchRE("[0-9]+\s").group(0)
        cnx.match("Mbps")
        results[s] = [int(tx_mbps), int(rx_mbps)]
    cnx.match("Perf test complete, turning validation on")
    cnx.match("(INS)Command> ")
    return results

#
# Simple test checks for link up, does scan sizes, then perf_test
#
def check_all_links(cnx, board_info):
    start_trafficgen(cnx)
    port_list = get_port_list(cnx)
    check_links_up(cnx, port_list)
    run_scan_size(cnx, port_list)
    run_perf_test(cnx, port_list)
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

