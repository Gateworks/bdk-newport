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

import sys
import os
import time
import connection
import commands
import tempfile

#
# Generic connection for a board. Serves as a base class for specific boards
# below
#
class Board:
    def __init__(self, args, logObject):
        self.board = args.board
        self.logging = logObject
        self.console = connection.GenericPort(args.console, self.logging)
        # Info about the board, filled in later
        self.chip_model = None
        self.multinode = None

    def close(self):
        self.console.close()
        self.logging.close()

    def write(self, data):
        self.console.write(data)

    def log(self, data):
        self.logging.logInfo(data)

    def send(self,str):
        self.console.send(str)

    def sendEcho(self,str):
        self.console.sendEcho(str)

    def waitfor(self, str, timeout=5):
        return self.console.waitfor(str, timeout)

    def waitforRE(self, str, timeout=5):
        return self.console.waitforRE(str, timeout)

    def delay(self, timeout):
        return self.console.delay(timeout)

    def match(self, correct, timeout=5):
        return self.console.match(correct, timeout)

    def matchRE(self, correct, timeout=5):
        return self.console.matchRE(correct, timeout)

#
# Class for controlling EBB and EVB boards with MCUs that control power cycling
# and reset
#
class Board_EVB(Board):
    def __init__(self, args, logObject):
        assert args.mcu, "MCU IP or name must be specified"
        assert not args.bmc, "BMC can't be specified with MCU"
        Board.__init__(self, args, logObject)
        self.turn_off_when_done = False
        self.mcu = connection.GenericPort(args.mcu, logObject)
        try:
            self.mcu.sendEcho("echo mcu_responded")
            self.mcu.match("mcu_responded")
        except:
            self.mcu.write("\r\n")
            self.mcu.waitfor("Hit 'P' key or toggle the power switch to turn the board on.")
            self.mcu.write("P")
            self.turn_off_when_done = True
        result = self.mcu.waitforRE("EBB[0-9]{4} MCU Command>", timeout=15)
        if "EBB80" in result:
            self.chip_model = "CN81XX"
        elif "EBB81" in result:
            self.chip_model = "CN81XX"
        elif "EBB83" in result:
            self.chip_model = "CN83XX"
        else:
            self.chip_model = "CN88XX"
        if args.mcu2:
            self.mcu2 = connection.GenericPort(args.mcu2, logObject)
            self.multinode = True
            try:
                self.mcu2.sendEcho("echo mcu_responded")
                self.mcu2.match("mcu_responded")
            except:
                self.mcu2.write("\r\n")
                self.mcu2.waitfor("Hit 'P' key or toggle the power switch to turn the board on.")
                self.mcu2.write("P")
                self.turn_off_when_done = True
            self.mcu2.waitforRE("EBB[0-9]{4} MCU Command>", timeout=15)
        else:
            self.mcu2 = None
            self.multinode = False

    def close(self):
        if self.turn_off_when_done:
            self.mcu.sendEcho("echo mcu_responded")
            self.mcu.match("mcu_responded")
            self.mcu.waitforRE("EBB[0-9]{4} MCU Command>")
            self.mcu.sendEcho("P -f")
            self.mcu.match("Board is off!!!!")
            if self.mcu2:
                self.mcu2.sendEcho("echo mcu_responded")
                self.mcu2.match("mcu_responded")
                self.mcu2.waitforRE("EBB[0-9]{4} MCU Command>")
                self.mcu2.sendEcho("P -f")
                self.mcu2.match("Board is off!!!!")
        self.mcu.close()
        if self.mcu2:
            self.mcu2.close()
        Board.close(self)

    def powerCycle(self):
        self.log("Power cycle board")
        mcu_list = [self.mcu]
        if self.mcu2:
            mcu_list.append(self.mcu2)
        for m in mcu_list:
            try:
                self.mcu.waitfor("JUNK")
            except (KeyboardInterrupt, SystemExit):
                raise
            except:
                pass
        for m in mcu_list:
            m.sendEcho("echo mcu_responded")
            m.match("mcu_responded")
            m.waitforRE("EBB[0-9]{4} MCU Command>")
            m.sendEcho("P -f -r")
            self.delay(1) # Eat any stray output before the board powered off
        for m in mcu_list:
            m.waitforRE("EBB[0-9]{4} MCU Command>", timeout=15)

    def flashUpdate(self, filename):
        self.log("Update flash on board")
        inf = open(filename, "rb")
        data = inf.read()
        inf.close()
        outf = tempfile.NamedTemporaryFile(mode="wb", dir="/tftpboot")
        outf.write(data)
        outf.flush()
        commands.getoutput("chmod 666 %s" % outf.name)
        tftp_name = os.path.basename(outf.name)
        tftp_server = commands.getoutput("hostname -I")
        self.log("Using TFTP server on %s with filename %s" % (tftp_server, tftp_name))
        mcu_list = [self.mcu]
        if self.mcu2:
            mcu_list.append(self.mcu2)
        for m in mcu_list:
            try:
                self.mcu.waitfor("JUNK")
            except (KeyboardInterrupt, SystemExit):
                raise
            except:
                pass
        for m in mcu_list:
            m.sendEcho("echo mcu_responded")
            m.match("mcu_responded")
            result = m.waitforRE("EBB[0-9]{4} MCU Command>")
            m.sendEcho("thunder_update -f -n %s -t %s" % (tftp_name, tftp_server))
            m.match("Using \"%s\" as the filename" % tftp_name)
            m.match("Erased Sector 0x0 (address 0x0)")
        for m in mcu_list:
            m.waitfor("Starting File transfer for programming", timeout=60)
            m.waitfor("Starting File transfer for verification", timeout=60)
            m.waitforRE("EBB[0-9]{4} MCU Command>", timeout=60)
        outf.close()

#
# Class for controlling the CRB-1S
#
class Board_IPMI(Board):
    def __init__(self, args, logObject):
        assert args.bmc, "BMC IP or name must be specified"
        assert not args.mcu, "MCU can't be specified with BMC"
        Board.__init__(self, args, logObject)
        self.turn_off_when_done = True
        self.chip_model = "CN88XX"
        self.bmc = args.bmc
        self.bmc_user = args.bmc_user
        self.bmc_pass = args.bmc_pass
        self.multinode = (args.board != "crb-1s")

    def close(self):
        if self.turn_off_when_done:
            ipmi = "ipmitool -H %s -U %s -P %s" % (self.bmc, self.bmc_user, self.bmc_pass)
            os.system(ipmi + " power off")
        Board.close(self)

    def powerCycle(self):
        self.log("Power cycle board")
        ipmi = "ipmitool -H %s -U %s -P %s" % (self.bmc, self.bmc_user, self.bmc_pass)
        os.system(ipmi + " power off")
        time.sleep(7)
        os.system(ipmi + " power on")

    def flashUpdate(self, filename):
        self.log("Update flash on board")
        assert False, "Flash update not implemented for BMC based boards"

