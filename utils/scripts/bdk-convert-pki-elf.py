#!/usr/bin/env python2
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import sys
import elftools.elf.elffile

def write_microcode(input_file, output_file):
    inf = open(input_file, "r")
    elf = elftools.elf.elffile.ELFFile(inf)

    segment = elf.get_segment(0)
    #print segment.header
    #print "Start address 0x%x" % segment.header.p_vaddr
    data = segment.data()
    inf.close()

    data_len = len(data)
    #print "Length %d bytes" % data_len
    assert data_len & 7 == 0
    #print "Writing %s" % output_file
    outf = open(output_file, "w")
    outf.write("#include <stdint.h>\n")
    outf.write("/* This file is autgenerated from %s */\n" % input_file)
    outf.write("const int __BDK_PKI_MICROCODE_CN8XXX_LENGTH = %d;\n" % (data_len/8))
    outf.write("const uint64_t __BDK_PKI_MICROCODE_CN8XXX[] = {\n")
    outf.write("    0x")
    for count in range(data_len):
        # Swap endinness
        loc = (count>>3)<<3
        loc += 7-(count&7)
        if count and ((count&7) == 0):
            outf.write("ull,\n    0x%02x" % ord(data[loc]))
        else:
            outf.write("%02x" % ord(data[loc]))
    outf.write("ull\n")
    outf.write("};\n")
    outf.close()
    return 0

if len(sys.argv) == 3:
    sys.exit(write_microcode(sys.argv[1], sys.argv[2]))
else:
    print
    print "Convert an ELF file into C for microcode loading"
    print
    print "    %s input.elf output.c" % sys.argv[0]
    print
    sys.exit(1)

