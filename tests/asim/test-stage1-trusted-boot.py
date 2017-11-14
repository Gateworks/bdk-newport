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

#
# Instruct python to make all symbols global when loading asim (required
# so that simulator external symbols referenced from device models will
# resolve correctly).
#
import sys
import os
import signal

if "ASIM_TIMING" in os.environ:
    signal.alarm(2 * 60 * 60) # 2 hour limit
else:
    signal.alarm(10 * 60) # 10 min limit

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

pipe_r, pipe_w = os.pipe()
UART0PORT = str(pipe_w)
UART1PORT = "1"
os.environ["UART0PORT"] = UART0PORT
os.environ["UART1PORT"] = UART1PORT
os.environ["BIN_IMAGE"] = BDK_ROOT + "/target-bin/bdk.bin"
os.environ["SYMBOL_IMAGE"] = BDK_ROOT + "/apps/diagnostics/app"
if not "ASIM_CHIP" in os.environ:
    os.environ["ASIM_CHIP"] = "CN88XX:1.0"

#
# Load the simulator
#
import asim

#
# Create a shim object, send all log output to stdout.
#
sim = asim.Simulator(None)
assert sim

def send(str):
    assert sim.command("control n0.uaa0 input \"%s\\n\"" % str)

def wait_for(wait_str):
    buffer = ""
    while True:
        data = os.read(pipe_r, 1)
        sys.stdout.write(data)
        sys.stdout.flush()
        buffer += data
        buffer = buffer[-200:]
        if buffer.endswith(wait_str):
            break;


#
# Load the common config
#
assert sim.command("@%s/%s.asim" % (BDK_ROOT, os.environ["ASIM_CHIP"].split(":")[0]))
# Check for timing
if "ASIM_TIMING" in os.environ:
    assert sim.command("activecores 1")
    # ASIM_TIMING is any asim command to start the timing model. Examples:
    # ASIM_TIMING="stm2 simple"
    # ASIM_TIMING="stm2 exec_at_fetch"
    # ASIM_TIMING="stm"
    assert sim.command(os.environ["ASIM_TIMING"])
    # Timing model is very slow, so show current instruction every 1M cycles
    assert sim.command("trace cpu0 tick 1000000")
    # Use CPU cycles instead of wall time
    assert sim.command("timer 0")
assert sim.command("@%s/signing-key.asim" % BDK_ROOT)
if os.environ["ASIM_CHIP"].startswith("CN9"):
    assert sim.command("control n0.gpio0 set strap 0x3402")
assert sim.command("start 0")

wait_for("Cavium SOC")
wait_for("PASS: CRC32 verification")
wait_for("================")
wait_for("Cavium Boot Stub")
wait_for("================")
wait_for("Version:")
if os.environ["ASIM_CHIP"].startswith("CN88XX"):
    wait_for("Node:  0")
if os.environ["ASIM_CHIP"].startswith("CN8"):
    wait_for("Chip:  0xa")
    wait_for("SKU:   CN8")
    wait_for("L2:")
    wait_for("RCLK:  2500 Mhz")
    wait_for("SCLK:  800 Mhz")
    wait_for("Boot:  SPI24")
    wait_for("VRM:   Enabled")
    wait_for("Trust: Enabled, Secure Boot")
else:
    wait_for("Chip:  0xb")
    wait_for("SKU:   CN9")
    wait_for("L2:")
    wait_for("RCLK:  2500 Mhz")
    wait_for("SCLK:  800 Mhz")
    wait_for("Boot:  SPI0-CS0,SPI0-CS0")
    wait_for("AVS:   Enabled")
    wait_for("Trust: Enabled, Secure Boot")
wait_for("Press 'B' within 10 seconds for boot menu")
send("b")

wait_for("============")
wait_for("Boot Options")
wait_for("============")
wait_for("N) Boot Normally")
wait_for("S) Enter Setup")
wait_for("D) Enter Diagnostics")
if not os.environ["ASIM_CHIP"].startswith("CN81XX"):
    wait_for("E) Enter Diagnostics, skipping Setup")
wait_for("W) Burn boot flash using Xmodem")
wait_for("U) Change baud rate and flow control")
wait_for("R) Reboot")
wait_for("Choice:")

send("d")
wait_for("Loading image file '/fatfs/diagnostics.bin.lzma'")
wait_for("---")
wait_for("Cavium SOC")
wait_for("PASS: CRC32 verification")
wait_for("Lua 5.2.0  Copyright (C) 1994-2011 Lua.org, PUC-Rio")

wait_for("Cavium Diagnostic")
wait_for("Copyright (C) 2010-2017 Cavium Inc.")
wait_for("Version")

wait_for("=================================")
wait_for("Main Menu")
wait_for("=================================")
wait_for("(INS)Menu choice []:")

assert sim.command("stop")
assert sim.command("statistics")

print "***********"
print "Test Passed"
print "***********"

