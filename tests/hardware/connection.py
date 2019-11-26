#!/usr/bin/env python2
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import re
import sys
import os
import select
import subprocess
import time
import telnetlib

#
# Log file implementation
#
class Log:
    def __init__(self, filename):
        self.filename = filename + time.strftime("-%Y-%m-%d-%H:%M:%S") + ".log"
        self.file = open(self.filename, "w")
        print "Log file: %s" % self.filename
        self.outputbuf = ""
        self.saw_cr = False

    def close(self):
        self.flush()
        self.file.close()
        print "Closed log file: %s" % self.filename

    def flush(self):
        if self.outputbuf:
            if self.outputbuf[-1] != "\n":
                self.outputbuf += "\n"
            for l in self.outputbuf[0:-1].split("\n"):
                self.file.write(">>> " + l + "\n")
                print ">>> " + l
            self.outputbuf = ""
        self.file.flush();

    def _write(self, data):
        self.flush()
        self.file.write(data)

    def logInput(self, data):
        self._write("<<< " + data + "\n")
        print "<<< " + data

    def logOutput(self, data):
        if data == "\n":
            # Flush after a NL
            self.flush()
            self.saw_cr = False
            return
        elif self.saw_cr:
            # Flush after a CR without a NL
            self.flush()
        # Remember CR s owe know to flush later
        self.saw_cr = (data == "\r")
        if not self.saw_cr:
            self.outputbuf += data

    def logInfo(self, data):
        self._write("*** " + data + "\n")
        print "*** " + data

    def logDebug(self, data):
        return
        self._write("DBG " + data + "\n")
        print "DBG " + data

#
# Implements a serial port connection. Used by GenericPort
#
class SerialPort:
    def __init__(self, connect_str):
        parts = connect_str.split(":")
        self.device = parts[0]
        if len(parts) == 2:
            baudrate = int(parts[1])
        else:
            baudrate = 115200
        if os.system("stty --file=%s %d raw clocal -crtscts -echo" % (self.device, baudrate)):
            raise Exception("stty failed")
        self.fd = os.open(self.device, os.O_RDWR | os.O_SYNC | os.O_NDELAY)
        self.poll = select.poll()
        self.poll.register(self.fd, select.POLLIN)

    def close(self):
        os.close(self.fd)

    def write(self, data):
        os.write(self.fd, data)

    def readChar(self, timeout):
        ready = self.poll.poll(timeout * 1000)
        if ready:
            return os.read(self.fd, 1)
        else:
            raise Exception("Timeout")

#
# Implements a telnet connection. Used by GenericPort
#
class TelnetPort:
    def __init__(self, connect_str):
        parts = connect_str.split(":")
        assert len(parts) == 2, "Expected 'host:port'"
        self.host = parts[0]
        self.port = int(parts[1])
        self.telnet = telnetlib.Telnet(self.host, self.port)
        self.telnet.read_until("JUNK", timeout=1)
        self.data = ""

    def close(self):
        self.telnet.close()

    def write(self, data):
        self.data += self.telnet.read_eager()
        if len(self.data) > 256:
            self.data = self.data[-256:]
        self.telnet.write(data)

    def readChar(self, timeout):
        start_time = time.time()
        while not self.data:
            if time.time() - start_time > timeout:
                raise Exception("Timeout")
            self.data += self.telnet.read_eager()
            if not self.data:
                time.sleep(0.01) # 10ms
        result = self.data[0]
        self.data = self.data[1:]
        return result

#
# Implements a Serial Over Lan connection. Used by GenericPort
#
class SerialOverLan:
    def __init__(self, connect_str):
        parts = connect_str.split(":")
        assert len(parts) == 2, "Expected 'sol:host'"
        self.host = parts[1]
        ipmitool = ["ipmitool", "-H", self.host, "-I", "lanplus", "-U", "admin", "-P", "admin", "sol"]
        ipmi_len = len(ipmitool)
        ipmitool.append("deactivate")
        subprocess.call(ipmitool)
        ipmitool = ipmitool[0:ipmi_len]
        ipmitool.extend(["set", "character-send-threshold", "1"])
        subprocess.call(ipmitool)
        ipmitool = ipmitool[0:ipmi_len]
        ipmitool.append("info")
        subprocess.call(ipmitool)
        ipmitool = ipmitool[0:ipmi_len]
        ipmitool.append("activate")
        self.ipmitool = subprocess.Popen(ipmitool, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        self.poll = select.poll()
        self.poll.register(self.ipmitool.stdout, select.POLLIN)

    def close(self):
        self.ipmitool.terminate()

    def write(self, data):
        self.ipmitool.stdin.write(data)

    def readChar(self, timeout):
        ready = self.poll.poll(timeout * 1000)
        if ready:
            return self.ipmitool.stdout.read(1)
        else:
            raise Exception("Timeout")

#
# Implements an ASIM connection. Used by GenericPort
#
class AsimConnect:
    def __init__(self, connect_str):
        pipe_r, pipe_w = os.pipe()
        self.pipe_r = pipe_r
        self.pipe_w = pipe_w
        self.data = ""
        self.sim = None # Filled in later

    def close(self):
        #os.close(self.pipe_w)
        #os.close(self.pipe_r)
        pass

    def write(self, data):
        assert self.sim
        assert self.sim.command("control n0.uaa0 input \"%s\"" % data)

    def readChar(self, timeout):
        start_time = time.time()
        while not self.data:
            if time.time() - start_time > timeout:
                raise Exception("Timeout")
            self.data += os.read(self.pipe_r, 1)
            if not self.data:
                time.sleep(0.01) # 10ms
        result = self.data[0]
        self.data = self.data[1:]
        return result

#
# Port connection for scripting
#
class GenericPort:
    def __init__(self, connect_str, logObject):
        self.connect_str = connect_str
        if "/" in connect_str:
            self.port = SerialPort(connect_str)
        elif connect_str.startswith("sol:"):
            self.port = SerialOverLan(connect_str)
        elif connect_str == "asim":
            self.port = AsimConnect(connect_str)
        else:
            self.port = TelnetPort(connect_str)
        self.log = logObject
        self.log.logInfo("Connected to %s" % connect_str)
        self.dataBuffer = ""

    def close(self):
        self.port.close()
        self.log.logInfo("Connection %s closed" % self.connect_str)

    def write(self, data):
        self.log.logInput(data)
        self.port.write(data)

    def unget(self, data):
        self.dataBuffer += data

    def readChar(self, timeout):
        if self.dataBuffer:
            data = self.dataBuffer[0]
            self.dataBuffer = self.dataBuffer[1:]
            return data
        data = self.port.readChar(timeout)
        if data == "\033":
            data = "<ESC>"
        self.log.logOutput(data)
        return data

    def send(self,str):
        self.write(str + "\r")

    def sendEcho(self,str):
        self.log.logInfo("Send echo: " + str)
        for c in str:
            self.port.write(c)
            r = self.readChar(1)
            while (c != r):
                r = self.readChar(1)
            if c != r:
                try:
                    self.waitfor("JUNK", timeout=1)
                except (KeyboardInterrupt, SystemExit):
                    raise
                except:
                    pass
                raise Exception("Send wasn't echoed properly. Sent '%s', received '%s'" % (c, r))
        self.port.write("\r")

    def delay(self, timeout):
        try:
            self.waitfor("ANY PENDING DATA", timeout)
        except (KeyboardInterrupt, SystemExit):
            raise
        except:
            pass

    def waitfor(self, str, timeout=1):
        self.log.logDebug("WaitFor: %s" % str)
        complete = ""
        current = ""
        start_time = time.time()
        while not str in current:
            current += self.readChar(timeout)
            if len(current) > 512:
                complete += current[0:256]
                current = current[256:]
            if time.time() - start_time > timeout:
                raise Exception("Timeout")
        self.log.logDebug("WaitFor done: %s" % str)
        return complete + current

    def waitforRE(self, str, timeout=1):
        self.log.logDebug("WaitForRE: %s" % str)
        complete = ""
        current = ""
        regex = re.compile(str)
        start_time = time.time()
        while not regex.search(current):
            current += self.readChar(timeout)
            if len(current) > 512:
                complete += current[0:256]
                current = current[256:]
            if time.time() - start_time > timeout:
                raise Exception("Timeout")
        self.log.logDebug("WaitForRE done: %s" % str)
        return complete + current

    def match(self, correct, timeout=1):
        self.log.logDebug("Match: %s" % correct)
        correct = correct.strip()
        r = self.readChar(timeout)
        while r in " \r\n\b":
            r = self.readChar(timeout)
        current = r
        for c in correct:
            if r != c:
                self.unget(current)
                raise Exception("Match failed\nCorrect: \"" + correct + "\"\nRead: \"" + current + "\"\n")
            try:
                r = self.readChar(timeout)
                current += r
            except:
                self.unget(current)
                raise
        self.log.logDebug("Match done: %s" % correct)

    def matchRE(self, correct, timeout=1):
        self.log.logDebug("MatchRE: %s" % correct)
        r = self.readChar(timeout)
        while r in " \r\n\b":
            r = self.readChar(timeout)
        current = r
        regex = re.compile(correct)
        start_time = time.time()
        match = regex.match(current)
        while not match:
            try:
                current += self.readChar(timeout)
            except:
                self.unget(current)
                raise
            if time.time() - start_time > timeout:
                break
            match = regex.match(current)
            if "\n" in current: # Don't allow line span
                break
        if match:
            self.log.logDebug("MatchRE done: %s" % correct)
            return match
        self.unget(current)
        if current:
            raise Exception("RE match failed \"%s\", got \"%s\"" % (correct, current))
        else:
            raise Exception("Timeout matching RE \"%s\"" % correct)

