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

import os
import sys
import binascii
import struct
import time

# BDK image heade for Thunder is
#   Offset  Size    Description
#   0x00    4       Raw instruction for skipping header
#   0x04    4       Length of the image, includes header
#   0x08    8       Magic string "THUNDERX"
#   0x10    4       CRC32 of image + header. These bytes are zero when calculating the CRC
#   0x14    4       Zero, reserved for future use
#   0x18    64      ASCII Image name. Must always end in zero
#   0x58    32      ASCII Version. Must always end in zero
#   0x78    136     Zero, reserved for future use
#   0x100   -       Beginning of image. Header is always 256 bytes.

HEADER_MAGIC = "THUNDERX"
HEADER_SIZE = 0x100

def pack(width, data):
    if width == 1:
        return struct.pack("<B", data)
    elif width == 2:
        return struct.pack("<H", data)
    elif width == 4:
        return struct.pack("<I", data)
    elif width == 8:
        return struct.pack("<Q", data)
    else:
        raise Exception("Invalid width")


def load_file(filename):
    inf = open(filename, "rb")
    file = inf.read()
    inf.close()
    return file

def update_header(filename, image_name, image_version, data):
    # Save the 4 bytes at the front for the new header
    raw_instruction = data[0:4]
    # Remove the existing header
    data = data[HEADER_SIZE:]
    # Header begins with one raw instruction for 4 bytes
    header = raw_instruction
    # Total length
    header += pack(4, HEADER_SIZE + len(data))
    # Eight bytes of magic number
    header += HEADER_MAGIC
    # CRC - filled later
    header += pack(4, 0)
    # Reserved 4 bytes
    header += pack(4, 0)
    # 32 bytes of Name
    name = image_name[0:63] # Truncate to 63 bytes, room for \0
    header += name
    header += "\0" * (64 - len(name))
    # 16 bytes of Version
    v = image_version[0:31] # Truncate to 31 bytes, room for \0
    header += v
    header += "\0" * (32 - len(v))
    # Pad to header length
    header += "\0" * (HEADER_SIZE - len(header))
    # Make sure we're the right length
    assert(len(header) == HEADER_SIZE)

    # Combine the header and the data
    data = header + data
    # Fix the CRC
    crc32 = 0xffffffffL & binascii.crc32(data)
    data = data[0:16] + pack(4,crc32) + data[20:]
    # Write the new file
    fhandle = open(filename, "wb")
    # Write the header
    fhandle.write(data)
    # Close, we're done
    fhandle.close()

if len(sys.argv) < 3:
    print
    print "Usage:"
    print "    %s new_image old_image [rom files...]" % sys.argv[0]
    print
    print "Update the Uboot image header in a '*.bin' file and possibly"
    print "add files to the image for use in the '/rom' filesystem."
    print
    print "    new_image: File name to write new bin image to."
    print "    old_image: File name of base bin image."
    print "    rom files: Optional list of file names to add to the image"
    print "               for use by the '/rom' file system. For example,"
    print "               'rom/*' includes all files in the BDK rom directory."
    print
    sys.exit(1)


out_filename = sys.argv[1]
in_filename = sys.argv[2]
rom_filenames = sys.argv[3:]

image_file = load_file(in_filename)
# ROM files are stored sequencially after the end of the image, starting
# at the _end symbol. Each ROM file starts with six bytes "ROM-FS",
# a two byte filename length, a four byte file length, the bytes for
# the filename, and the file's data. The filename is not \0 terminated.
for rom in rom_filenames:
    if rom.endswith(".lua"):
        # Compile Lua files to save space
        os.system(os.getenv("BDK_ROOT") + "/bin/bdk-luac -s -o luac.out " + rom)
        rom_file = load_file("luac.out")
        os.system("rm luac.out")
    else:
        rom_file = load_file(rom)
    name = rom.split("/")[-1]
    tmp = "ROM-FS"
    tmp += pack(2, len(name))
    tmp += pack(4, len(rom_file))
    tmp += name
    tmp += rom_file
    image_file += tmp

image_name = os.path.basename(out_filename)
image_version = time.strftime("%Y-%m-%d %H:%M:%S")

update_header(out_filename, image_name, image_version, image_file)

