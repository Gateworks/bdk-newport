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

import optparse
import base64
import binascii
import hashlib
import os
import struct
import subprocess
import sys
import ecdsa
from elftools.elf.elffile import ELFFile

BDK_ROOT = os.getenv("BDK_ROOT", './') # defaults to current dir when BDK_ROOT is not set

#
# Read the public key from a private key file
#
def read_pub_key(private_key):
    inf = open(private_key, "rb")
    pem = inf.read()
    inf.close()
    priv_key = ecdsa.SigningKey.from_pem(pem)
    pub = priv_key.get_verifying_key().to_string()
    assert len(pub) == 64, "Public key must be two 256 bits numbers, 64 bytes"
    r = pub[0:32] # R in big endian format
    s = pub[32:64] # S in big endian format
    # Return R followed by S, both in little endian format. This is the format
    # that Thunder's CSIB expects
    return r[::-1] + s[::-1]

#
# Argument parser
#
def do_arg_parse():
    parser = optparse.OptionParser(
        usage=
            "%prog --key KEY --nv VALUE out_file\n",
        description=
            "Build a public key for use by the BDK that can be signed to extend\n"
            "the chain of trust\n")
    parser.add_option("--key", action="store", type="string", dest="key",
                      nargs=1, default="bdk-sign-private.pem",
                      help="Input Private Key file to extract public key from")
    parser.add_option("--nv", action="store", type="int", dest="nv",
                      nargs=1, default=0, help="Non volatile counter for key lifetime (0-31).")
    options, args = parser.parse_args()
    need_usage = False
    if (len(args) != 1):
        need_usage = True
    if need_usage:
        parser.print_help()
        sys.exit(1)
    class Args:
        def __init__(self, options, args):
            self.files = args[0:]
            self.key = options.key
            self.nv = options.nv
    return Args(options, args)

#
# Main entry point
#
def main():
    args = do_arg_parse()
    if args == None:
        return 1
    # Read the Public key
    pubk = read_pub_key(args.key)
    # Create the public key file
    outf = open(args.files[0], "wb")
    outf.write(os.urandom(8 * 7))
    # Write Non-volatile counter in little endian format
    outf.write(struct.pack("<Q", args.nv))
    # Write the public key in little endian format, same as
    # used for Thunder's CSIB
    outf.write(pubk)
    outf.close()

# Call main
sys.exit(main())
