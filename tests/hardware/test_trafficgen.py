# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import time
import test_boot

#
# Start traffic-gen, assuming we are already sitting at the main menu
#
def start_trafficgen(cnx):
    cnx.sendEcho("tg")
    cnx.waitfor("BDK Traffic Generator", 30) # Long wait for PHY init
    cnx.waitfor("Type \"help\" for a list of commands")
    cnx.waitfor("(INS)Command> ")
    cnx.write("wait_links 2\r")
    cnx.waitfor("(INS)Command> ", 20)
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
    # command. Don't include FAKE,LBK1,LBK2,LBK3 in the test to avoid this
    if cnx.chip_model == "CN83XX":
        port_list = [x for x in port_list if not (("LBK1" in x) or ("LBK2" in x) or ("LBK3" in x) or ("FAKE" in x))]
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
def run_scan_size(cnx, port_list, count=100):
    port_str = ",".join(port_list)
    cnx.sendEcho("scan_sizes %s %d" % (port_str, count))
    cnx.match("Scan sizes on ports: %s" % " ".join(port_list))
    cnx.match("Send %d packets, min size 60, max size 9212, increment 1, loops 1" % count)
    for s in range(60, 9213):
        cnx.match("Size %s" % s)
    cnx.match("(INS)Command> ")

#
# Run a performance test across supplied ports
#
def run_perf_test(cnx, port_list, use_validation = True):
    port_str = ",".join(port_list)
    if use_validation:
        cnx.sendEcho("perf_test %s val" % port_str)
    else:
        cnx.sendEcho("perf_test %s" % port_str)
    cnx.match("Performance test on ports: %s" % " ".join(port_list))
    if use_validation:
        cnx.match("Turning validation on")
    else:
        cnx.match("Turning validation off")
    cnx.match("Starting performance test")
    results = {}
    for s in [60, 128, 256, 512, 1024, 2048, 4096, 8192, 9212]:
        cnx.match("Size %4d: TX" % s)
        tx_mbps = cnx.matchRE("[0-9]+\s").group(0)
        cnx.match("Mbps (")
        tx_pps = cnx.matchRE("[0-9]+\s").group(0)
        cnx.match("pps), RX")
        rx_mbps = cnx.matchRE("[0-9]+\s").group(0)
        cnx.match("Mbps (")
        rx_pps = cnx.matchRE("[0-9]+\s").group(0)
        cnx.match("pps)")
        results[s] = [int(tx_mbps), int(rx_mbps)]
    if not use_validation:
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

#
# Simple test checks for LBK link up, does scan sizes, then perf_test
#
def check_lbk_links(cnx, board_info):
    start_trafficgen(cnx)
    all_port_list = get_port_list(cnx)
    port_list = []
    for p in all_port_list:
        if "LBK" in p:
            port_list.append(p)
    check_links_up(cnx, port_list)
    run_scan_size(cnx, port_list, 10)
    run_perf_test(cnx, port_list, True)
    run_perf_test(cnx, port_list, False)
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

