#!/usr/bin/env python2
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
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
# Class for controlling EBB, SLT, and EVB boards with MCUs that control power cycling
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
        result = self.mcu.waitforRE("(EBB)?(SLT)?[0-9]{4} MCU Command>", timeout=15)
        self.mcu_prompt = result.split("\n")[-1]
        self.log("MCU's prompt is \"" + self.mcu_prompt + "\"")
        if "EBB80" in result:
            self.chip_model = "CN81XX"
        elif "EBB81" in result:
            self.chip_model = "CN81XX"
        elif "EBB83" in result:
            self.chip_model = "CN83XX"
        elif "EBB96" in result:
            self.chip_model = "CN96XX"
        elif "EBB93" in result:
            self.chip_model = "CN96XX"
        elif "SLT96" in result:
            self.chip_model = "CN96XX"
        elif "SLT95" in result:
            self.chip_model = "CNF95XX"
        elif "EBB95" in result:
            self.chip_model = "CNF95XX"
        else:
            assert False, "Unknown board, update boards.py"
        self.board = self.mcu_prompt.split(" ")[0]
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
            self.mcu2.waitfor(self.mcu_prompt, timeout=15)
        else:
            self.mcu2 = None
            self.multinode = False

    def close(self):
        if self.turn_off_when_done:
            self.mcu.sendEcho("echo mcu_responded")
            self.mcu.match("mcu_responded")
            self.mcu.waitfor(self.mcu_prompt)
            self.mcu.sendEcho("P -f")
            self.mcu.waitfor("Board is off!!!!")
            if self.mcu2:
                self.mcu2.sendEcho("echo mcu_responded")
                self.mcu2.match("mcu_responded")
                self.mcu2.waitfor(self.mcu_prompt)
                self.mcu2.sendEcho("P -f")
                self.mcu2.waitfor("Board is off!!!!")
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
            m.waitfor(self.mcu_prompt)
            m.sendEcho("P -f -r")
            self.delay(1) # Eat any stray output before the board powered off
        for m in mcu_list:
            m.waitfor(self.mcu_prompt, timeout=15)

    def resetCycle(self):
        self.log("Reset cycle board")
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
            m.waitfor(self.mcu_prompt)
            m.sendEcho("O -f")
            m.waitforRE("was reset!")
            m.match(self.mcu_prompt)

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
            result = m.waitfor(self.mcu_prompt, 5)
            if self.chip_model.startswith("CN8"):
                m.sendEcho("thunder_update -f -n %s -t %s" % (tftp_name, tftp_server))
            else:
                m.sendEcho("spi_update -f -n %s -t %s" % (tftp_name, tftp_server))
            m.match("Using \"%s\" as the filename" % tftp_name)
            m.match("Erased Sector 0x0 (address 0x0)")
        for m in mcu_list:
            m.waitfor("Starting File transfer for programming", timeout=60)
            m.waitfor("Starting File transfer for verification", timeout=60)
            m.waitfor(self.mcu_prompt, timeout=60)
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

    def resetCycle(self):
        self.log("Reset cycle board")
        ipmi = "ipmitool -H %s -U %s -P %s" % (self.bmc, self.bmc_user, self.bmc_pass)
        os.system(ipmi + " power reset") # Untested

    def flashUpdate(self, filename):
        self.log("Update flash on board")
        assert False, "Flash update not implemented for BMC based boards"

#
# Class for controlling ASIM
#
class Board_ASIM(Board):
    def __init__(self, args, logObject):
        assert args.bmc == "asim", "BMC must be specified as 'asim'"
        assert not args.mcu, "MCU can't be specified with BMC"
        BDK_ROOT = os.environ["BDK_ROOT"]
        ASIM = os.environ["ASIM"]
        try:
            import dl
            sys.setdlopenflags(dl.RTLD_NOW|dl.RTLD_GLOBAL)
        except:
            sys.setdlopenflags(0x00002|0x00100)
        if os.path.isdir(ASIM + "/shim/python"):
            sys.path.append(ASIM + "/shim/python")
        else:
            sys.path.append(ASIM + "/bin/python")
        os.environ["ASIM_LIBRARY_PATH"] = ASIM + "/lib"
        os.environ["BIN_IMAGE"] = BDK_ROOT + "/target-bin/bdk.bin"
        os.environ["SYMBOL_IMAGE"] = BDK_ROOT + "/apps/diagnostics/app"
        if not "ASIM_CHIP" in os.environ:
            os.environ["ASIM_CHIP"] = "CN88XX:1.0"
        Board.__init__(self, args, logObject)
        self.chip_model = os.environ["ASIM_CHIP"].split(":")[0]
        self.multinode = False
        self.asim = None

    def start_asim(self):
        if self.asim:
            self.asim.destroy()
        import asim
        self.sim = asim.Simulator(None)
        assert self.sim
        self.console.port.sim = self.sim
        # Setup UART connections
        os.environ["UART0PORT"] = str(self.console.port.pipe_w)
        os.environ["UART1PORT"] = "1"
        os.environ["UART2PORT"] = "1"
        assert self.sim.command("@%s/%s.asim" % (os.environ["BDK_ROOT"], self.chip_model))
        time.sleep(1) # Needed to make sure core threads get changes
        if self.chip_model.startswith("CN8"):
            assert self.sim.command("start 0")
        else:
            assert self.sim.command("start scp noap")

    def close(self):
        assert self.sim.command("stop")
        if not self.chip_model.startswith("CN8"):
            assert self.sim.command("stop scp mcp")
        time.sleep(1) # Needed to make sure cores are stopped before we die
        Board.close(self)
        if self.asim:
            self.asim.destroy()
            self.asim = None

    def powerCycle(self):
        self.log("Power cycle board")
        self.start_asim()

    def resetCycle(self):
        self.log("Reset cycle board")
        self.start_asim()

    def flashUpdate(self, filename):
        self.log("Update flash on board")
        assert False, "Flash update not implemented for ASIM based boards"

#
# Class for controlling the CN96XX-FIO
#
class Board_CN96XX_FIO(Board):
    def __init__(self, args, logObject):
        assert args.bmc, "BMC IP or name must be specified"
        assert not args.mcu, "MCU can't be specified with BMC"
        Board.__init__(self, args, logObject)
        self.turn_off_when_done = True
        self.chip_model = "CN96XX"
        self.bmc = args.bmc
        if args.bmc_user != "admin":
            self.bmc_user = args.bmc_user
            self.bmc_pass = args.bmc_pass
        else:
            self.bmc_user = "root"
            self.bmc_pass = "0penBmc"
        self.multinode = False
        self.ssh = "sshpass -p %s ssh %s@%s" % (self.bmc_pass, self.bmc_user, self.bmc)

    def close(self):
        if self.turn_off_when_done:
            os.system(self.ssh + " /usr/sbin/powerctl poweroff")
        Board.close(self)

    def powerCycle(self):
        self.log("Power cycle board")
        cmd = self.ssh + " /usr/sbin/powerctl poweroff"
        self.log(cmd)
        os.system(cmd)
        time.sleep(5)
        cmd = self.ssh + " /usr/sbin/powerctl poweron"
        self.log(cmd)
        os.system(cmd)
        #time.sleep(2)
        #cmd = self.ssh + " /usr/sbin/powerctl reset"
        #self.log(cmd)
        #os.system(cmd)

    def resetCycle(self):
        self.log("Reset cycle board")
        cmd = self.ssh + " /usr/sbin/powerctl reset"
        self.log(cmd)
        os.system(cmd)

    def flashUpdate(self, filename):
        self.log("Update flash on board")
        assert False, "Flash update not implemented for CN96XX-FIO based boards"

