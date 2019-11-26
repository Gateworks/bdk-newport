# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import sys
import os
import signal
import time

BDK_ROOT = os.environ["BDK_ROOT"]
ASIM = os.environ["ASIM"]

#
# Setup path to find Asim libraries
#
def setup_asim_libs():
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

#
# Class for controlling asim
#
class AsimHelper:
    def __init__(self):
        self.chip = os.environ["ASIM_CHIP"].split(":")[0]
        self.sim = None
        self.pipe_r = None
        self.pipe_w = None
        assert "ASIM_CHIP" in os.environ

    def setup_asim_env(self, extra_env):
        self.pipe_r, self.pipe_w = os.pipe()
        UART0PORT = str(self.pipe_w)
        UART1PORT = "1"
        os.environ["UART0PORT"] = UART0PORT
        os.environ["UART1PORT"] = UART1PORT
        os.environ["UART2PORT"] = UART1PORT # Same as uart1
        os.environ["BIN_IMAGE"] = BDK_ROOT + "/target-bin/bdk.bin"
        os.environ["SYMBOL_IMAGE"] = BDK_ROOT + "/apps/diagnostics/app"
        for name in extra_env:
            os.environ[name] = extra_env[name]

    def command(self, str):
        assert self.sim.command(str)

    def start(self, timeout_sec, extra_commands = [], extra_env = {}, no_start = False):
        signal.alarm(timeout_sec)
        self.setup_asim_env(extra_env)
        self.sim = asim.Simulator(None)
        assert self.sim
        # Load the common config
        self.command("@%s/%s.asim" % (BDK_ROOT, self.chip))
        for cmd in extra_commands:
            self.command(cmd)
        if no_start:
            return
        time.sleep(1) # Needed to make sure core threads get changes
        if self.chip.startswith("CN8"):
            self.command("start 0")
        else:
            self.command("start scp noap")

    def stop(self):
        self.command("stop")
        if not self.chip.startswith("CN8"):
            self.command("stop scp mcp")
        time.sleep(1) # Needed to make sure cores are stopped before we die
        self.command("statistics")
        print "Closing ASIM"
        signal.alarm(2)
        self.sim.destroy()
        signal.alarm(0)
        print "ASIM Closed"
        self.sim = None
        self.pipe_r = None
        self.pipe_w = None

    def send(self, str):
        self.command("control n0.uaa0 input \"%s\\n\"" % str)

    def wait_for(self, wait_str):
        buffer = ""
        while True:
            data = os.read(self.pipe_r, 1)
            if data == "\033":
                data = "<ESC>"
            sys.stdout.write(data)
            sys.stdout.flush()
            buffer = buffer[-199:] + data
            if buffer.endswith(wait_str):
                break;


setup_asim_libs()
# Load the simulator
import asim

