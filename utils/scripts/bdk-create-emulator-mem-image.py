#!/usr/bin/python2

import binascii
import os
import sys
import struct

def create_hex(out_filename, in_filename):
    data = open(in_filename, "rb").read()
    # Pad to 16 bytes
    l = len(data) & 15
    if l != 0:
        fill = struct.pack("<B", 0)
        data += fill * (16 - l)
    outf = open(out_filename, "w")
    addr = 0x280000
    while data:
        chunk = data[0:16]
        data = data[16:]
        chunk = chunk[-1::-1]
        h = binascii.hexlify(chunk)
        outf.write("@%x %s_%s\n" % (addr, h[0:16], h[16:32]))
        addr += 1
    outf.close()

if len(sys.argv) != 3:
    print
    print "Usage:"
    print "    %s output_hex input_binary" % sys.argv[0]
    print
    print "Convert an input binary file into a hex memory image for the emulator"
    print
    sys.exit(1)

out_filename = sys.argv[1]
in_filename = sys.argv[2]
create_hex(out_filename, in_filename)


