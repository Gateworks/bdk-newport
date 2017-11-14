#!/usr/bin/python
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
import argparse
import traceback
import sys
import boards
import connection
import test_boot
import test_dram
import test_sata
import test_trafficgen

SUPPORTED_BOARDS = {
    "crb-1s": {
        "cnx": boards.Board_IPMI,
        "info": {
            "sata": [4, 5, 6, 7],
        }
    },
    "crb-2s": {
        "cnx": boards.Board_IPMI,
        "info": {
            "sata": [4, 5, 6, 7],
        }
    },
    "ebb8800": {
        "cnx": boards.Board_EVB,
        "info": {
            "sata": [8, 9, 10, 11],
        }
    },
    "ebb8804": {
        "cnx": boards.Board_EVB,
        "info": {
            "sata": [],
        }
    },
    "ebb8004": {
        "cnx": boards.Board_EVB,
        "info": {
            "sata": [0, 1],
        }
    },
    "ebb8104": {
        "cnx": boards.Board_EVB,
        "info": {
            "sata": [0, 1],
        }
    },
    "ebb8304": {
        "cnx": boards.Board_EVB,
        "info": {
            "sata": [0, 1, 2, 3, 4, 5],
        }
    },
}

#
# The normal boot stuff boots to the diagnostics menu. This "fake"
# test adds an option to just do the boot without any further tests
# for fast boot testing
#
def test_boot_diags(cnx, board_info):
    return True

#
#
#
SUPPORTED_TESTS = {
    "boot-diags":   test_boot_diags,
    "short-dram":   test_dram.dram_short,
    "full-dram":    test_dram.dram_all,
    "ccpi":         test_dram.dram_ccpi,
    "sata":         test_sata.sata_detect,
    "network":      test_trafficgen.check_all_links,
}

#
# Parse command line arguments, returning an "args" object with all values
#
def parse_args():
    board_list = SUPPORTED_BOARDS.keys()
    test_list = SUPPORTED_TESTS.keys()
    parser = argparse.ArgumentParser(
        usage='%(prog)s [-h] [--help] [options] test [test ...]',
        description='Run one or more test scripts on a ThunderX board.')
    parser.add_argument('-c', '--count', action='store', type=int, default=1,
        help='Number of times to run the test. (Default 1)')
    parser.add_argument('-s', '--stop', action='store_const', default=False, const=True,
        help='Stop on failure')
    parser.add_argument('-b', '--board', action='store', type=str, required=True,
        help='Board type to run on. (Required)', choices=board_list)
    parser.add_argument('--bmc-user', action='store', type=str, default="admin",
        help='Username for BMC ipmi commands. Only used with ' +
            'boards supporting IPMI. (Default admin)')
    parser.add_argument('--bmc-pass', action='store', type=str, default="admin",
        help='Password for BMC ipmi commands. Only used with '+
            'boards supporting IPMI. (Default admin)')
    parser.add_argument('--console', action='store', type=str,
        help='Console connection to the board. This can be a ' +
            'serial port (/dev/ttyUSB0), a TCP/IP connection (IP:PORT), or ' +
            'the keyword "sol" for Serial Over LAN. If not specified for ' +
            'Cavium evaluation boards, the default is TCP/IP to the MCU. ' +
            'For boards using IPMI, the default is "sol". (Optional)')
    parser.add_argument('--flash', action='store', type=str,
        help='Flash image to update board too (Optional)')
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--bmc', action='store', type=str,
        help='BMC to use for control. Only used with boards supporting IPMI. ' +
        'Either this option, or "--mcu" must be specified.')
    group.add_argument('--mcu', action='store', type=str,
        help='MCU to use for control. Only used with Cavium evaluation ' +
            'boards. Either this option, or "--bmc" must be specified.')
    parser.add_argument('--mcu2', action='store', type=str,
        help='MCU to use for second node control. Only used with a dual node ' +
            'Cavium evaluation board setup.')
    parser.add_argument('test', metavar='test', type=str, nargs='+',
        help='One or more test to run. The possible tests are: {%s}' % ", ".join(test_list),
        choices=test_list)
    args = parser.parse_args()
    return args

#
# Create a connection to the board based on the supplied parameters
#
def create_connection(args):
    log_board_name = args.board
    if args.console == None:
        if args.mcu:
            log_board_name = args.mcu
            args.console = args.mcu + ":9761"
        else:
            assert args.bmc, "Serial over LAN requires BMC"
            log_board_name = args.bmc
            args.console = "sol:" + args.bmc
    elif args.console == "sol":
        assert args.bmc, "Serial over LAN requires BMC"
        log_board_name = args.bmc
        args.console = "sol:" + args.bmc
    if args.mcu and not ":" in args.mcu:
        args.mcu = args.mcu + ":9760"
    if args.mcu2 and not ":" in args.mcu2:
        args.mcu2 = args.mcu2 + ":9760"

    print "Console connection:     %s" % args.console
    if args.mcu:
        print "MCU/control connection: %s" % args.mcu
        print "Second MCU connection:  %s" % args.mcu2
    else:
        print "BMC/control connection: %s" % args.bmc

    logname = "log-%s-%s" % (log_board_name, "+".join(args.test))
    log = connection.Log(logname)
    cnx = SUPPORTED_BOARDS[args.board]["cnx"](args, log)
    return cnx

#
# Either power cycle, or soft reset a board. Soft reset only
# works if the board is already sitting at the BDK main menu.
#
# Returns True on success, False on failure
#
def do_cycle(cnx, powerCycle):
    try:
        if powerCycle:
            cnx.powerCycle()
        else:
            cnx.sendEcho("rbt")
        return True # passed
    except (KeyboardInterrupt, SystemExit):
        cnx.log("Abort forced")
        raise
    except:
        ex_str = traceback.format_exc()
        try:
            cnx.waitfor("JUNK", timeout=1)
        except:
            pass
        cnx.log("FAIL: Exception: %s" % ex_str)
        return False # failed

#
# Check booting of BDK
#
# Returns True on success, False on failure
#
def do_boot(cnx):
    try:
        test_boot.boot_normal(cnx, powerCycle=False)
        return True # passed
    except (KeyboardInterrupt, SystemExit):
        cnx.log("Abort forced")
        raise
    except:
        ex_str = traceback.format_exc()
        try:
            cnx.waitfor("JUNK", timeout=1)
        except:
            pass
        cnx.log("FAIL: Exception: %s" % ex_str)
        return False # failed

#
# Run a specific test on a board. The board is assumed to already
# be sitting at the BDK main menu, waiting for cnx to send a command.
#
# Returns True on success, False on failure
#
def do_test(cnx, args, test, board_info):
    try:
        test_func = SUPPORTED_TESTS[test]
        cnx.log("************************************************")
        cnx.log("Starting test \"%s\"" % test)
        test_func(cnx, board_info)
        return True # Return passed
    except (KeyboardInterrupt, SystemExit):
        cnx.log("Abort forced")
        raise
    except:
        ex_str = traceback.format_exc()
        try:
            cnx.waitfor("JUNK", timeout=1)
        except:
            pass
        cnx.log("FAIL: Exception: %s" % ex_str)
        return False # Return failed

#
# Run a list of tests on the board
#
# Returns True on success, False on failure
#
def run_tests(cnx, args):
    if args.flash:
        cnx.flashUpdate(args.flash)
    # Initialize loop counters
    count = 0
    fail_in_row = 0
    # Results are stored in a dictionary per test. One dict for pass and
    # one for fail
    test_pass = {}
    test_fail = {}
    test_pass["power-cycle"] = 0
    test_fail["power-cycle"] = 0
    test_pass["reset-cycle"] = 0
    test_fail["reset-cycle"] = 0
    test_pass["bdk-boot"] = 0
    test_fail["bdk-boot"] = 0
    for test in args.test:
        test_pass[test] = 0
        test_fail[test] = 0
    try:
        # Loop running tests for the given count
        while count < args.count:
            count += 1
            cnx.log("Starting loop %d of %d:" % (count, args.count))
            # Each loop runs the tests three times
            # 1) Power cycle before test
            # 2) Soft reset before test
            # 3) Soft reset before test
            # We've found that hardware performs differently depending on power
            # cycle or soft reboot
            for power in [True, False, False]:
                # Power or reset cycle
                if True:
                    test = "power-cycle" if power else "reset-cycle"
                    cnx.log("************************************************")
                    cnx.log("Starting test \"%s\"" % test)
                    passed = do_cycle(cnx, power)
                    if passed:
                        test_pass[test] += 1
                # Check BDK boot
                if passed:
                    test = "bdk-boot"
                    cnx.log("************************************************")
                    cnx.log("Starting test \"%s\"" % test)
                    passed = do_boot(cnx)
                    if passed:
                        test_pass[test] += 1
                # Run test list
                if passed:
                    for test in args.test:
                        passed = do_test(cnx, args, test, SUPPORTED_BOARDS[args.board]["info"])
                        if passed:
                            test_pass[test] += 1
                            fail_in_row = 0
                        else:
                            break # Skip next test
                if not passed:
                    # Failed, this loop is done
                    test_fail[test] += 1
                    fail_in_row += 1
                    cnx.log("Abort next test due to fail")
                    break # Skip next power loop and goto next repeat loop
            # Print summary after each repeat loop
            cnx.log("************************************************")
            cnx.log("After loop %d of %d:" % (count, args.count))
            for test in test_fail:
                cnx.log("    %-20s Pass: %5d Fail: %5d" % (test, test_pass[test], test_fail[test]))
            cnx.log("************************************************")
            # Exit if we got 10 failures in a row. Something probably went bad
            # in the setup and needs operator intervention
            if (args.stop and (fail_in_row >= 1)) or (fail_in_row >= 10):
                cnx.log("Failed %d in a row, stopping script" % (fail_in_row))
                break
    except (KeyboardInterrupt, SystemExit):
        cnx.log("************************************************")
        cnx.log("Cancelled during loop %d of %d:" % (count, args.count))
        for test in test_fail:
            cnx.log("    %-20s Pass: %5d Fail: %5d" % (test, test_pass[test], test_fail[test]))
        cnx.log("************************************************")
    total_fails = 0
    for test in test_fail:
        total_fails += test_fail[test]
    return (total_fails == 0)

#
# Main entry point of run script
#
def main():
    args = parse_args()
    cnx = create_connection(args)
    passed = run_tests(cnx, args)
    cnx.close()
    if passed:
        sys.exit(0)
    else:
        sys.exit(1)

#
# Execute main
#
main()
