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
    print "Writing %s" % output_file
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

