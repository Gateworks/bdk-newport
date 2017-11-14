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
import string
import getopt

import boards
import connection

####################################
# board-related settings
DEFAULT_BOARD = "ebb8804"
TIMER_MIN = 150   # long enough for 88xx
MEM_TEST_LEN = 5 * 256 * 1024 * 1024 # 5 blocks of 256MB
####################################

def maybe_image_number(cnx):
    try:
        cnx.waitfor("One image found, automatically loading", timeout=1)
    except:
        cnx.sendEcho("1")

def wait_for_bdkstub_messages(cnx):
    #cnx.powerCycle()
    cnx.waitfor("Cavium SOC", timeout=20)
    cnx.waitfor("BDK Stage1 Boot")
    cnx.waitfor("Boot Menu")
    cnx.waitfor("(INS)Menu choice:")
    cnx.sendEcho("3")

# this is needed for a BDK that asks for an image number
    maybe_image_number(cnx)
#
    cnx.waitfor("Cavium SOC")
    cnx.waitfor("Main Menu")
    cnx.waitfor("(INS)Menu choice []:")
    cnx.sendEcho("keys")
    cnx.match("Invalid choice. Choose a number from 1 to")
    cnx.waitfor("(INS)Menu choice []:")

def wait_for_test_menu(cnx):
    #cnx.waitforRE("DRAM Test Menu - [ ]*[0-9]+ MB, [0-9]+ MHz, DDR[34] [UR]DIMM")
    cnx.waitfor("DRAM Test Menu")
    cnx.waitfor("(INS)Menu choice []:")

def wait_for_dram_menu(cnx):
    cnx.waitfor("DRAM Menu")
    cnx.waitfor("(INS)Menu choice []:")

def dram_set_envvar(cnx, name, value):
    cnx.sendEcho("setenv")
    cnx.match("(INS)Name:")
    cnx.sendEcho(name)
    cnx.match("(INS)Value []:")
    cnx.sendEcho(value)
    wait_for_dram_menu(cnx)

def send_main_cmd(cnx, cmd):
    cnx.sendEcho(cmd)
    wait_for_dram_menu(cnx)

def send_dram_cmd(cnx, cmd):
    cnx.sendEcho(cmd)
    wait_for_dram_menu(cnx)

def send_test_cmd(cnx, cmd):
    cnx.sendEcho(cmd)
    wait_for_test_menu(cnx)

def dram_init(cnx, speed):
    global memsize
    global board

    cnx.sendEcho(board)
    cnx.waitforRE("\(INS\)DRAM clock Hertz, return for default \[[1-9][0-9]+\]:")
    cnx.sendEcho(speed)
#
    next = cnx.waitforRE("(BDK DRAM:|INFO:|WARNING:)", timeout=150)
    if next.find("INFO:") != -1:
        return False
    if next.find("WARNING:") != -1:
        return False

    megs = cnx.waitforRE(" [0-9]* ")
    try:
        memsize = int(megs) * 1024 * 1024
        #cnx.log("FOUND: megs='%s' memsize=0x%x" % (megs, memsize))
    except:
        cnx.log("ERROR: megs='%s', using memsize of 8GB" % megs)
        memsize = 8 * 1024 * 1024 * 1024
            
    #cnx.matchRE("MB, [0-9]+ MHz, DDR[34] [RU]DIMM", timeout=10)
    cnx.matchRE("MB, [0-9]+ MHz", timeout=10)
    wait_for_dram_menu(cnx)
    return True

def set_repeat_count(cnx, repeats):
    cnx.sendEcho("repeat")
    cnx.waitforRE("\(INS\)Number of times to repeat the test, or -1 for infinite \[(-|)[0-9]*\]:")
    cnx.sendEcho(repeats)
    wait_for_test_menu(cnx)

def set_start_address(cnx, start):
    cnx.sendEcho("start")
    cnx.waitforRE("\(INS\)Physical byte address to start memory test at \[[0-9]*\]:")
    cnx.sendEcho(start)
    wait_for_test_menu(cnx)

def set_test_length(cnx, length):
    cnx.sendEcho("length")
    cnx.waitforRE("\(INS\)Length of region in bytes, or -1 for all of memory \[(-|)[0-9]*\]:")
    cnx.sendEcho(length)
    wait_for_test_menu(cnx)

def setup_dram_test(cnx):
    send_test_cmd(cnx, cmd="cores")
    if errabort == False:
        send_test_cmd(cnx, cmd="abort") # this defaults to ON
    send_test_cmd(cnx, cmd="batch")
    #set_repeat_count(cnx, repeats="2")
    
def start_special_dram_test(cnx):
    cnx.sendEcho("spec")
    cnx.matchRE("Pass 1 of [0-9]+")

def wait_for_end_special_dram_test(cnx):
    if fullmem == True:
        timer = 14400 # 4-hour long timeout
    else:
        timer = TIMER_MIN
    try:
        cnx.waitforRE("(All tests passed |Tests reported [0-9]+ errors)", timeout=timer)
        return True
    except:
        return False

def boot_bdk_to_dram(cnx):
    wait_for_bdkstub_messages(cnx)
    # transition to the DRAM Menu
    cnx.sendEcho("ddr")
    wait_for_dram_menu(cnx)

def parse3Args(args):
    try:
        assert len(args) >= 2
        if ("/" in args[0]) or (":" in args[0]):
            # Using either serial ports, or telnet with port number specified
            # Need at least three arguments (console, mcu/control, logname)
            assert len(args) >= 3
            console = args[0]
            mcu = args[1]
            logname = args[2]
        elif args[0] == "sol":
            # Use Serial Over Lan. The second argument must be a BMC name or IP
            assert len(args) >= 3
            console = "sol:%s" % args[1]
            mcu = args[1]
            logname = args[2]
        else:
            # Using telnet with a hostname. Assume it is the name of an MCU
            # and the ports are 9761 and 9760
            console = args[0] + ":9761"
            mcu = args[0] + ":9760"
            logname = args[1]

        print "Console connection:     %s" % console
        print "MCU/control connection: %s" % mcu
        print "Log name: %s" % logname
        return (console, mcu, logname)
    except:
        print
        print "Test script for controlling boards remotely"
        print
        print "Usage: see docs for parseArgs in board.py"
        print
        sys.exit(2)

def do_help():
    print "Usage: one-test [OPTION]... [CONSOLE] [MCU] [LOGNAME] [OPTION]..."
    print """Performs a DRAM init and memory test via connections to console and MCU.
Mandatory arguments to long options are mandatory for short options too.
  -a, --abort      set BDK abort_on_error to false
  -b, --board=     name of the board to use for DRAM config
  -c, --cycles=    number of power cycles
  -d, --daily      log to the daily directory (~/LOGS/<date>)
      --dic=       DIC override
  -f, --full       test full memory
  -h, -?, --help   display this help and exit
  -l, --logdir     set the log directory
  -n, --nom=       RTTNOM override
  -p, --park=      RTTPARK override
      --range3     test 3 small memory ranges
  -r, --rodt=      RODT override
  -s, --speed=     speed in Hz
  -q, --quiet      print minimal DRAM init messages to stdout
  -v, --verbose    print verbose DRAM init messages to stdout
  -w, --wr=        RTTWR override
      --100mhz     enable 100MHz refclk
[CONSOLE] and [MCU] are in the form: <hostname>:<port> or <device>
eg. ce-console-02:10001 would use telnet
eg. /dev/ttyS3 would use the serial port
[LOGNAME] is the base log name used for all logs produced during the run;
options like --rodt 3 would be appended to the base name as -RODT3  
"""


# log runs with a given set of params
def log_a_set():

    logstr = logname

    print "rttnom: %s" % rttnom
    print "rttpark: %s" % rttpark
    print "rodtctl: %s" % rodtctl

    # if we modified any base params with args, add them to the log name
    if rodtctl != None:
        logstr += ("-RODT%s" % rodtctl)
    if rttnom != None:
        logstr += ("-NOM%s" % rttnom)
    if rttpark != None:
        logstr += ("-PARK%s" % rttpark)
    if rttwr != None:
        logstr += ("-WR%s" % rttwr)
    if dic != None:
        logstr += ("-DIC%s" % dic)

    # now add a date string for the logname
    logstr += time.strftime("-%Y%m%d-%H%M%S")
    logstr += "-log.txt"

    print "Log file: %s" % logstr
    print

    logfile = "%s/%s" % (logdir, logstr)
    print "Logging to: %s" % logfile
 
    # open the log and make the connection
    log = connection.Log(logfile)
    cnx = boards.Board_EVB(console=console, mcu=mcu, mcu2=None, logObject=log)

    # now loop for the cycle_count
    count = 0
    for count in range(cycle_count):

        # cycle power
        cnx.powerCycle()

        # dram_init may fail with training issue; handle...
        result = False
        fails = 0
        while result == False:

            # get through all the boot msgs and transition to the DRAM menu
            boot_bdk_to_dram(cnx)
            # now in the DRAM Menu for initialization...

            # set the envvars here if any params were specified...
            if rodtctl != None:
                dram_set_envvar(cnx, name="ddr_rodt_ctl", value=rodtctl)

            if rttnom != None:
                dram_set_envvar(cnx, name="ddr_rtt_nom", value=rttnom)

            if rttpark != None:
                dram_set_envvar(cnx, name="ddr_rtt_park", value=rttpark)

            if rttwr != None:
                dram_set_envvar(cnx, name="ddr_rtt_wr", value=rttwr)

            if dic != None:
                dram_set_envvar(cnx, name="ddr_dic", value=dic)

            # set any additional envvars here...

            # make it a verbose log
            if verbose == True:
                send_dram_cmd(cnx, cmd="verbose")

            # run at 100 MHz
            if do_100mhz == True:
                dram_set_envvar(cnx, name="ddr_100mhz_refclk", value="1")

            # run with ECC disabled
            if do_noecc == True:
                dram_set_envvar(cnx, name="ddr_use_ecc", value="0")

            # make any DLLRO adjustments for DIMMs
            if dllro_list != None:
                do_dllro_setup(cnx) # maybe more args

            # now do the init, leave us in the DRAM menu
            result = dram_init(cnx, speed=speed)
            if result == False:
                fails += 1
            if fails > 4:
                return

        # we get here when dram_init was successful

        # now go to the TEST Menu for running tests
        cnx.sendEcho("test")
        wait_for_test_menu(cnx)
        setup_dram_test(cnx)

        for i in range(num_test_ranges):

            if fullmem == False:
                # calculate test addresses and ranges
                start_addr = ((memsize * (i + 1)) / (num_test_ranges + 1)) - (MEM_TEST_LEN / 2)
                #cnx.log("CALC: start=0x%x len=0x%x" % (start_addr, test_len))
                set_start_address(cnx, start=("0x%x" % start_addr))
                set_test_length(cnx, length=("0x%x" % test_len))

            # run the special tests
            start_special_dram_test(cnx)
            ret = wait_for_end_special_dram_test(cnx) # wait for the end 
            if ret == False:
                break
            wait_for_test_menu(cnx)
            # end of range loop

        # end of the count loop

    cnx.close()

    print "Closing log file: %s" % logstr

def do_dllro_setup(cnx):
    # set DLL read offsets via envvars
    dram_set_envvar(cnx, name="ddr_dll_read_offset", value="1")
    for lmc in range(4):
        for (byte,value) in dllro_list[lmc]:
            namestr="ddr%d_dll_read_offset_byte%d" % (lmc,byte)
            dram_set_envvar(cnx, name=namestr, value=str(value))

# DIMM 122 adjustments
# mod L0 from [2,10]
L0_122_list=[(2,05),(3,15),(4,10),(5,10)]
L1_122_list=[(2,-5)]
L2_122_list=[(1,20),(2,10),(4,-10),(5,10),(8,-20)]
L3_122_list=[(3,15),(7,5)]
Lx_122_list=[L0_122_list,L1_122_list,L2_122_list,L3_122_list]

#dram_set_envvar(cnx, name="ddr0_dll_read_offset_byte3", value="15")
#dram_set_envvar(cnx, name="ddr0_dll_read_offset_byte5", value="10")
#dram_set_envvar(cnx, name="ddr1_dll_read_offset_byte2", value="-5")
#dram_set_envvar(cnx, name="ddr2_dll_read_offset_byte1", value="20")
#dram_set_envvar(cnx, name="ddr2_dll_read_offset_byte4", value="-10")
#dram_set_envvar(cnx, name="ddr2_dll_read_offset_byte5", value="10")
#dram_set_envvar(cnx, name="ddr2_dll_read_offset_byte8", value="-15")
#dram_set_envvar(cnx, name="ddr3_dll_read_offset_byte3", value="10")
#dram_set_envvar(cnx, name="ddr3_dll_read_offset_byte7", value="5")

# DIMM 124 adjustments
# Orig LMC0 (0,15)
# Orig LMC1 (0,0)
# Orig LMC2 (0,0)
L0_124_list=[(0,20), (7,10)]
L1_124_list=[(0,15), (1,10), (4,-10), (8,12)]
L2_124_list=[(0,15)]
L3_124_list=[]
Lx_124_list=[L0_124_list, L1_124_list, L2_124_list, L3_124_list]

#dram_set_envvar(cnx, name="ddr_dll_read_offset", value="1")
#dram_set_envvar(cnx, name="ddr0_dll_read_offset_byte0", value="15")
#dram_set_envvar(cnx, name="ddr0_dll_read_offset_byte7", value="5")
#dram_set_envvar(cnx, name="ddr1_dll_read_offset_byte1", value="10")
#dram_set_envvar(cnx, name="ddr1_dll_read_offset_byte4", value="-5")
#dram_set_envvar(cnx, name="ddr1_dll_read_offset_byte8", value="12")


########## mainline starts here

#hertz   = "933333333"
#hertz   = "1066666666"
#hertz   = "940000000"

start_addr = 0x7d8000000 #"0x7d8000000" # just under halfway of 64GB
test_len = 0x50000000    #"0x50000000"  # just 1.25 GB
memsize = 0

rodtctl = None
rttnom = None
rttpark = None
dic = None
rttwr = None

rodtctl_list = []
rttnom_list = []
rttpark_list = []
rttwr_list = []

speed = ""

cycle_count = 100

verbose = True
fullmem = False
errabort = True
do_100mhz = False
dllro_list = None
num_test_ranges = 1
board = DEFAULT_BOARD
do_daily = False
logdir = None
do_noecc = False

####################################
# mainline
short_opts = "?ab:c:defhl:n:p:r:s:qvw:"
long_opts = ["abort", "board=", "cycles=", "daily", "dic=", "full", "help", "logdir=", "noecc", "nom=", "park=", "range3", "rodt=", "speed=", "quiet", "verbose", "wr=", "100mhz", "122", "124" ]
try:
    opts, args = getopt.gnu_getopt(sys.argv[1:], short_opts, long_opts)
except getopt.GetoptError, err:
    # print help information and exit:
    print str(err) # will print something like "option -a not recognized"
    do_help()
    sys.exit(2)

for option, argument in opts:
    if option in ("-a", "--abort"):
        errabort = False
    elif option in ("-b", "--board"):
        board = argument
    elif option in ("-c", "--cycles"):
        cycle_count = int(argument)
    elif option in ("--dic",):
        dic = argument
    elif option in ("-d", "--daily"):
        logdir = None
        do_daily = True
    elif option in ("-e", "--noecc"):
        do_noecc = True
    elif option in ("-f", "--full"):
        fullmem = True
        num_test_ranges = 1
    elif option in ("-?", "-h", "--help"):
        do_help()
    elif option in ("-l", "--logdir"):
        do_daily = False
        logdir = argument
    elif option in ("-n", "--nom"):
        rttnom_list.append(argument)
    elif option in ("-p", "--park"):
        rttpark_list.append(argument)
    elif option in ("-q", "--quiet"):
        verbose = False
    elif option in ("-r", "--rodt"):
        rodtctl_list.append(argument)
    elif option in ("--range3",):
        fullmem = False
        num_test_ranges = 3
    elif option in ("-s", "--speed"):
        speed = argument
    elif option in ("-v", "--verbose"):
        verbose = True
    elif option in ("-w", "--wr"):
        rttwr_list.append(argument)
    elif option in ("--100mhz",):
        do_100mhz = True
    elif option in ("--122",):
        dllro_list = Lx_122_list
    elif option in ("--124",):
        dllro_list = Lx_124_list
    else:
        assert False, "unhandled option"


# of the remainder we must have 3 left: console MCU logname
console, mcu, logname = parse3Args(args)

# now handle a log directory specification
if do_daily == True:
    # make sure daily directory exists, and make it if not
    daystr = time.strftime("%Y%m%d")
    logdir = "%s/LOGS/%s" % (os.path.expanduser("~"), daystr)
    if os.path.isdir(logdir) != True:
        # make the directory
        print "INFO: Log directory '%s' does not exist - creating..." % logdir
        os.mkdir(logdir)
    else:
        print "INFO: Log directory '%s' exists..." % logdir

elif logdir != None:
    # make sure directory exists, but do NOT make it if not
    if os.path.isdir(logdir) != True:
        print "ERROR: Log directory '%s' does not exist - exiting" % logdir
        sys.exit(3)
    else:
        print "INFO: Log directory '%s' exists..." % logdir
else:
    logdir = "./"

# add the board name to the logname
logname += "-%s" % board

# if running at 100 MHz, add to log name
if do_100mhz == True:
    logname += "-100mhz"

# if speed passed as arg, add it to the log name
# but just the MHz value
if len(speed) == 9:
    logname += "-%s" % speed[:3]    
elif len(speed) == 10:
    logname += "-%s" % speed[:4]

print "cycles: %s" % cycle_count
print "speed: %s" % speed
print "verbose: %s" % verbose
print "base logname: %s" % logname

if len(rodtctl_list) == 0:
    rodtctl_list.append(None)
if len(rttnom_list) == 0:
    rttnom_list.append(None)
if len(rttpark_list) == 0:
    rttpark_list.append(None)
if len(rttwr_list) == 0:
    rttwr_list.append(None)


for rodtctl in rodtctl_list: # RODT should be [ 0-7 ]
    for rttnom in rttnom_list: # RTT_NOM should be [ 0-7 ]
        for rttpark in rttpark_list: # RTT_PARK should be [ 0-7 ]
            for rttwr in rttwr_list: # RTT_WR should be [ 0-7 ]

                log_a_set()
                #print "settings=%s:%s:%s:%s:" % (rodtctl, rttnom, rttpark, rttwr)

print "Done."
print

