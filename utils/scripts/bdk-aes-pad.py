#!/usr/bin/env python2
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import sys
import struct
import binascii

#
# Main entry point
#
def main():
    if len(sys.argv) < 2:
        print "Usage: %s file ..." % sys.argv[0]
        print "    Add AES padding to a file making it a multiple of 16 bytes"
        return 1
    for f in sys.argv[1:]:
        inf = open(f, "rb")
        data = inf.read()
        inf.close()
        need_padding = 16 - (len(data) & 15)
        if need_padding == 16:
            continue
        pad = struct.pack("<B", need_padding) * need_padding
        if need_padding >= 4:
            crc32 = 0xffffffffL & binascii.crc32(data)
            pad = struct.pack(">I", crc32) + pad[4:]
        if f.endswith(".lzma"):
            pad = struct.pack("<B", 0) * need_padding
        data += pad
        out = open(f, "wb")
        out.write(data)
        out.close()
    return 0

# Call main
sys.exit(main())
