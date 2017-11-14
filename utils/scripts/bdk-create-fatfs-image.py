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

FIXED_SIZE = 0x180000 # 1.5MB of Fixed data, see flash_create()
FATFS_SIZE = 0x280000 # 2.5MB of FAT filesystem data, see fatfs_create()
BDK_ROOT = os.getenv("BDK_ROOT", './') # defaults to current dir when BDK_ROOT is not set
ROTPK = "" # Root of trust public key bytes. These fields are to be interpreted as
           # a coordinate pair (Qx,Qy) of 256-bit integers in little-endian format.
BSSK = "" # BSSK calculated from HUK

#
# Determine where fdisk is
#
def fdisk_get_path():
    try:
        return subprocess.check_output(["which", "fdisk"]).trim()
    except:
        if os.path.exists("/sbin/fdisk"):
            return "/sbin/fdisk"
        if os.path.exists("/usr/sbin/fdisk"):
            return "/usr/sbin/fdisk"
        else:
            raise Exception("Unable to find 'fdisk'. Please add it to your PATH")

#
# Create flash fiendly padding of 0xff. We use 0xff to be more
# friendly toward the flash devices the image gets stored in. This
# avoids needless bit flips in unused areas.
#
def padding(num_bytes):
    fill = struct.pack("<B", 0xff)
    return fill * num_bytes

#
# Create the FatFS area
#
def fatfs_create(args):
    global BSSK
    aes_key = None
    if args.ssk:
        aes_key = args.ssk
    if args.huk:
        aes_key = BSSK
    # Create a FATFS_SIZE file filled with 0xff
    outf = open(args.out, "wb")
    outf.write(padding(FATFS_SIZE))
    outf.close()
    # Create FAT filesystem in then file
    fatfs_tool = BDK_ROOT + "/bin/fatfs-tool"
    subprocess.check_call([fatfs_tool, "-q", "-i", args.out, "mkfs"])
    # Copy files into FAT filesystem
    for f in args.files:
        if aes_key:
            subprocess.check_call([fatfs_tool, "-q", "-i", args.out, "-e", aes_key, "cp", f, "/"])
        else:
            subprocess.check_call([fatfs_tool, "-q", "-i", args.out, "cp", f, "/"])
    inf = open(args.out, "rb")
    fatfs = inf.read()
    inf.close()
    assert len(fatfs) == FATFS_SIZE
    return fatfs

#
# Read a file and make sure it is less than or equal to a max length.
# Optionally pad the data to the max length
#
def read_file(filename, max_length, pad):
    inf = open(filename, "rb")
    data = inf.read()
    inf.close()
    assert len(data) <= max_length
    if pad:
        data += padding(max_length - len(data))
        assert len(data) == max_length
    return data

#
# Read a ELF file and generate a binary image from it
#
def read_elf(filename, max_length, pad, vma_start):
    vma_end = vma_start + max_length
    max_used = 0
    image = padding(max_length)
    image = struct.pack("<B", 0) * 256 + padding(max_length - 256)
    inf = open(filename, "rb")
    elffile = ELFFile(inf)
    for seg in elffile.iter_segments():
        if seg['p_type'] != "PT_LOAD":
            continue
        if seg['p_memsz'] == 0:
            continue
        if (seg['p_memsz'] % 4) != 0:
            raise Exception("segment size is not bit32 aligned")
        if seg['p_paddr'] >= vma_start and seg['p_paddr'] < vma_end:
            img_start = seg['p_paddr'] - vma_start
            img_end = img_start + seg['p_filesz']
            if img_end > max_length:
                raise Exception("EFL file %s has a segment that is too big for the requested size: %0d" % (filename, max_length))
            else:
                image = image[0:img_start] + seg.data() + image[img_end:]
                max_used = img_end
    inf.close()
    assert len(image) == max_length
    if not pad:
        # Image must be a multiple of 16KB
        max_used = (max_used + 0x3fff) & -16384
        image = image[0:max_used]
    return image

#
# Create a THUNDER/X flash image. This will contain everything except for
# the partition table
#
def flash_create(args):
    # Fill the fixed size part with 0xff
    flash = padding(FIXED_SIZE)
    # Update the AP non-trusted, CLIB=0x10000, CSIB=0x10100, Image=0x20000
    # Must be exactly 192KB for CN8XXX compatability, not encrypted
    ap_bl1 = read_file(args.ap_bl1, 0x30000, True)
    flash = update_image(flash, ap_bl1, False, 0x10000, 0x10100, 0x20000, args)
    # Update the AP trusted, CLIB=0x10200, CSIB=0x10300, Image=0x50000
    # Must be exactly 192KB for CN8XXX compatability, encrypted
    flash = update_image(flash, ap_bl1, True, 0x10200, 0x10300, 0x50000, args)
    # Update the SCP BL1 non-trusted, CLIB=0x10400, CSIB=0x10500, Image=0x80000
    # Must be 240KB or less. 256KB minus 16KB for stack, not encrypted
    scp_bl1 = read_elf(args.scp_bl1, 0x3c000, False, 0x80004000)
    flash = update_image(flash, scp_bl1, False, 0x10400, 0x10500, 0x80000, args)
    # Update the SCP BL1 trusted, CLIB=0x10600, CSIB=0x10700, Image=0xc0000
    # Must be 240KB or less. 256KB minus 16KB for stack, encrypted
    flash = update_image(flash, scp_bl1, True, 0x10600, 0x10700, 0xc0000, args)
    # Update the MCP BL1 non-trusted, CLIB=0x10800, CSIB=0x10900, Image=0x100000
    # Must be 240KB or less. 256KB minus 16KB for stack, not encrypted
    mcp_bl1 = read_elf(args.mcp_bl1, 0x3c000, False, 0x80004000)
    flash = update_image(flash, mcp_bl1, False, 0x10800, 0x10900, 0x100000, args)
    # Update the MCP BL1 trusted, CLIB=0x10a00, CSIB=0x10b00, Image=0x140000
    # Must be 240KB or less. 256KB minus 16KB for stack, encrypted
    flash = update_image(flash, mcp_bl1, True, 0x10a00, 0x10b00, 0x140000, args)
    # Add the FAT filesystem to it
    flash += fatfs_create(args)
    assert len(flash) == FIXED_SIZE + FATFS_SIZE
    return flash

#
# Setup the flash partition table information
#
def flash_fdisk(filename):
    fdisk = fdisk_get_path()
    start_sector = FIXED_SIZE / 512
    # Create a partition table in the file
    # Note that FatFS currently only looks at the first partition
    # Partition 1: FAT12 covering 1.5MB to 4MB
    inp = "n\n"     #    n          New partition
    inp += "p\n"    #    p          Primary
    inp += "1\n"    #    1          Primary 1
    inp += "%d\n" % start_sector #  Start at sector 3072, 1.5MB
    inp += "8191\n" #    8191       End at sector 8191, 4MB
    inp += "t\n"    #    t          Change type
    inp += "1\n"    #    1          FAT12
    inp += "w\n"    #    w          Write changes
    p = subprocess.Popen([fdisk, "-u", "-C", "1", filename], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.communicate(inp)
    assert p.returncode == 0, "fdisk command failed"

#
# Generate a Thunder ROM_CSIB_S structure
#
def generate_csib(crypt_type, image, nv):
    global ROTPK
    # Word 0
    csib = struct.pack("<Q", 0x424953435f4d5643) # Magic
    assert len(csib) == 8
    # Word 1
    csib_expose = 1
    csib_bkpt = 0
    csib_siden = 0
    csib_flags = (csib_expose << 7) | (csib_bkpt << 6) | (csib_siden << 4) | crypt_type
    csib += struct.pack("<B", csib_flags) # Above Flags
    csib += struct.pack("<B", 0) * 5 # 5 unused bytes
    csib += struct.pack("<B", nv) # NV count
    csib += struct.pack("<B", 0) # Version
    # Word 2
    csib += struct.pack("<Q", 0) # Reserved
    # Word 3
    csib += struct.pack("<Q", len(image)) # Size
    # Word 4-7
    csib += hashlib.sha256(image).digest()
    # Word 8-15
    assert len(ROTPK) == 64, "Public key must be two 256 bits numbers, 64 bytes"
    csib += ROTPK
    # Word 16-25
    csib += struct.pack("<Q", 0) * 10 # Reserved for software
    # Word 26-27
    csib += struct.pack("<Q", 0) * 2 # Sofware name / UUID
    # Word 28-31
    csib += os.urandom(8) # Random Nonce
    csib += os.urandom(8) # Random Nonce
    csib += os.urandom(8) # Random Nonce
    csib += os.urandom(8) # Random Nonce
    assert len(csib) == 256, "CSIB should be 256 bytes"
    return csib

#
# Generate a Thunder ROM_CLIB_S structure
#
def generate_clib(csib, offset, size, private_key):
    # Word 0
    clib = struct.pack("<Q", 0x42494c435f4d5643) # Magic
    # Word 1
    clib += struct.pack("<Q", 0) # Version and reserved
    # Word 2
    clib += struct.pack("<Q", offset) # Offset
    # Word 3
    clib += struct.pack("<Q", size) # Size
    # Word 4-7
    clib += struct.pack("<Q", 0) * 4 # Reserved
    # Word 8-15
    clib += sign_blob(csib, private_key)
    # Word 16-31
    clib += struct.pack("<Q", 0) * 16 # Reserved
    assert len(clib) == 256, "CLIB should be 256 bytes"
    return clib

#
# Sign a CSIB blob with the given private key file
# Result is 64 bytes
#
def sign_blob(blob, private_key):
    priv_key = ecdsa.SigningKey.from_pem(open(private_key).read())
    assert priv_key
    sign = priv_key.sign_deterministic(blob, hashfunc=hashlib.sha256)
    assert len(sign) == 64
    # Break into the R and S number
    r = sign[0:32]
    s = sign[32:64]
    # Results is R followed by S in little endian format
    return r[::-1] + s[::-1]

#
# Encrypt an image (binary string) with AES using key (hex string)
#
def encrypt_image(image, key):
    # The IV is hard coded as zero
    iv = "00000000000000000000000000000000"
    assert len(key) == 32, "AES key must be 32 hex chars, 128 bits"
    p = subprocess.Popen(["openssl", "enc", "-aes-128-cbc", "-e", "-K", key, "-iv", iv, "-nopad"],
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    out, err = p.communicate(image)
    assert p.returncode == 0, "openssl command failed"
    assert len(out) == len(image)
    return out

#
# AES Decrypt an image (binary string) with AES using key (hex string)
#
def aes128_decrypt(image, key):
    # The IV is hard coded as zero
    iv = "00000000000000000000000000000000"
    assert len(key) == 32, "AES key must be 32 hex chars, 128 bits"
    p = subprocess.Popen(["openssl", "enc", "-aes128", "-d", "-K", key, "-iv", iv, "-nopad"],
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    out, err = p.communicate(image)
    assert p.returncode == 0, "openssl command failed"
    assert len(out) == len(image)
    return out

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
# Embed an image into the middle of the flash image, updating the data, CLIB
# and CSIB as needed. Signing and encryption are done as the image is inserted
#
def update_image(flash, image, encrypt, clib_loc, csib_loc, image_loc, args):
    global BSSK
    flash_len = len(flash)
    crypt_type = 0 # Sign only
    if encrypt and args.huk:
        crypt_type = 2 # Sign and encrypt with HUK
    elif encrypt and args.ssk:
        crypt_type = 1 # Sign and encrypt with SSK
    csib = generate_csib(crypt_type, image, args.nv)
    clib = generate_clib(csib, image_loc, len(image), args.key)
    flash = flash[0:clib_loc] + clib + flash[clib_loc + 0x100:]
    flash = flash[0:csib_loc] + csib + flash[csib_loc + 0x100:]
    # Encrypt the image if necessary
    if encrypt and args.huk:
        bssk = csib[32:48]
        bssk = aes128_decrypt(bssk, args.huk)
        bssk = binascii.hexlify(bssk)
        assert len(bssk) == 32, "BSSK must be 32 hex digits"
        image = encrypt_image(image, bssk)
        if image_loc == 0x50000:
            BSSK = bssk
    elif encrypt and args.ssk:
        image = encrypt_image(image, args.ssk)
    flash = flash[0:image_loc] + image + flash[image_loc+len(image):]
    # Make sure the file size didn't change
    assert len(flash) == flash_len, "Images corrupted, length changed"
    return flash

#
# Argument parser
#
def do_arg_parse():
    parser = optparse.OptionParser(
        usage=
            "%prog <command>\n"
            "\n"
            "<command> is either:\n"
            "    genkey key_file            Generate a new Root of Trust signing key\n"
            "    create [options] files ... Create a flash image and sign it",
        description=
            "Build, sign, and optionally encrypt a THUNDER/X flash image\n"
            "\n"
            "Create a new signing key in file \"signing-key.private\":\n"
            "    %prog genkey signing-key.private\n"
            "\n"
            "Create a flash iamge and sign it:\n"
            "    %prog create --out=target-bin/bdk.bin --ap_bl1=apps/boot/boot.bin \\\n"
            "        --scp_bl1=target-bin/scp_bl1.exe --mcp_bl1=target-bin/mcp_bl1.exe \\\n"
            "        --key=signing-key.private apps/init/init.bin\n")
    group = optparse.OptionGroup(parser, "Create Options", "Options used with the create command.")
    group.add_option("--out", action="store", type="string", dest="out",
                      nargs=1, default="target-bin/bdk.bin",
                      help="Create a flash image of the specified name (target-bin/bdk.bin)")
    group.add_option("--ap_bl1", action="store", type="string", dest="ap_bl1",
                      nargs=1, default="apps/boot/boot.bin",
                      help="Input ARM boot code (apps/boot/boot.bin)")
    group.add_option("--scp_bl1", action="store", type="string", dest="scp_bl1",
                      nargs=1, default="target-bin/scp_bl1.bin",
                      help="Input SCP boot ELF, level 1 (target-bin/scp_bl1.exe)")
    group.add_option("--mcp_bl1", action="store", type="string", dest="mcp_bl1",
                      nargs=1, default="target-bin/mcp_bl1.bin", help="Input MCP boot ELF, level 1 (target-bin/mcp_bl1.exe)")
    group.add_option("--key", action="store", type="string", dest="key",
                      nargs=1, default="signing-key.private",
                      help="Input Key file to use for signing")
    group.add_option("--ssk", action="store", type="string", dest="ssk",
                      nargs=1, help="Encrypt the trusted boot stub with AES128 key (SSK HEX string, "
                      "32 digits). Set to \"random\" to generate a new key every signing for non-production testing.")
    group.add_option("--huk", action="store", type="string", dest="huk",
                      nargs=1, help="Encrypt the trusted boot stub with AES128 key (HUK HEX string, "
                      "32 digits). Set to \"random\" to generate a new key every signing for non-production testing.")
    parser.add_option("--nv", action="store", type="int", dest="nv",
                      nargs=1, default=0, help="Non volatile counter for key lifetime (0-31).")
    group.add_option("-v", "--verbose", action="store_true", dest="verbose",
                      default=False, help="Display verbose information.")
    parser.add_option_group(group)
    options, args = parser.parse_args()
    need_usage = False
    if (len(args) < 1):
        need_usage = True
    elif args[0] == "genkey":
        need_usage = (len(args) != 2)
    elif args[0] == "create":
        need_usage = (len(args) < 2)
    else:
        need_usage = True
    if need_usage:
        parser.print_help()
        sys.exit(1)
    class Args:
        def __init__(self, options, args):
            self.command = args[0]
            self.files = args[1:]
            self.out = options.out
            self.ap_bl1 = options.ap_bl1
            self.scp_bl1 = options.scp_bl1
            self.mcp_bl1 = options.mcp_bl1
            self.key = options.key
            self.ssk = options.ssk
            self.huk = options.huk
            self.verbose = options.verbose
            self.nv = options.nv
            # For testing purposes it can be useful to have the encryption
            # keys randomly generated. This is normally only useful with asim
            if self.ssk == "random":
                self.ssk = binascii.hexlify(os.urandom(16))
            if self.huk == "random":
                self.huk = binascii.hexlify(os.urandom(16))
    return Args(options, args)

#
# Command: Generate a new private key
#
def cmd_genkey(args):
    private_key = ecdsa.SigningKey.generate(curve=ecdsa.NIST256p)
    outf = open(args.files[0], "wb")
    outf.write(private_key.to_pem())
    outf.close()
    return 0

def show_fuses(args):
    global ROTPK
    global BSSK
    print "Root of Trust Public Key: "
    Qx = ROTPK[0:32] # First number, little endian
    Qy = ROTPK[32:64] # Second number, little endian
    Qx = Qx[::-1] # Convert to big endian
    Qy = Qy[::-1] # Convert to big endian
    # Show the key in numeric (big endian) format
    print "    Qx:            " + binascii.hexlify(Qx)
    print "    Qy:            " + binascii.hexlify(Qy)
    # Show the key in CSIB (little endian) format
    print "    CSIB ROTPK:    " + binascii.hexlify(ROTPK)
    # Show the key hash in FUSF_ROTPK format
    rotpk_sha = hashlib.sha256(ROTPK).digest()
    fusf_rotpkx = [rotpk_sha[0:8], rotpk_sha[8:16], rotpk_sha[16:24], rotpk_sha[24:32]]
    fusf_rotpkx = [x[::-1] for x in fusf_rotpkx]
    fusf_rotpkx = [binascii.hexlify(x) for x in fusf_rotpkx]
    for i in range(4):
        print "    FUSF_ROTPK[%d]: 0x%s" % (i, fusf_rotpkx[i])
    if args.ssk or args.huk:
        print "Secret Symmetric Keys:"
    if args.ssk:
        key0 = long(args.ssk[0:16], 16)
        key1 = long(args.ssk[16:32], 16)
        key0 = struct.pack("<Q", key0)
        key1 = struct.pack("<Q", key1)
        print "    SSK:           " + args.ssk
        print "    FUSF_SSK[0]:   0x" + binascii.hexlify(key0)
        print "    FUSF_SSK[1]:   0x" + binascii.hexlify(key1)
    if args.huk:
        key0 = long(args.huk[0:16], 16)
        key1 = long(args.huk[16:32], 16)
        key0 = struct.pack("<Q", key0)
        key1 = struct.pack("<Q", key1)
        print "    HUK:           " + args.huk
        print "    FUSF_HUK[0]:   0x" + binascii.hexlify(key0)
        print "    FUSF_HUK[1]:   0x" + binascii.hexlify(key1)
    if BSSK:
        print "    BSSK:          " + BSSK
    print "Field Fuses:"
    print "    0x3ff:0x300 (ROTPK SHA256) " + binascii.hexlify(rotpk_sha[::-1])
    if args.ssk:
        print "    0x47f:0x400 (SSK) " + args.ssk
    if args.huk:
        print "    0x4ff:0x480 (HUK) " + args.huk

def asim_fuses(args):
    global ROTPK
    rotpk_sha = hashlib.sha256(ROTPK).digest()
    fusf_rotpkx = [rotpk_sha[0:8], rotpk_sha[8:16], rotpk_sha[16:24], rotpk_sha[24:32]]
    outf = open(BDK_ROOT + "/signing-key.asim", "w")
    outf.write("control n0.gpio0 set strap 0x405\n")
    outf.write("mm8 0x87e004000060 = 0x%s secure external\n" % binascii.hexlify(fusf_rotpkx[0][::-1]))
    outf.write("mm8 0x87e004000068 = 0x%s secure external\n" % binascii.hexlify(fusf_rotpkx[1][::-1]))
    outf.write("mm8 0x87e004000070 = 0x%s secure external\n" % binascii.hexlify(fusf_rotpkx[2][::-1]))
    outf.write("mm8 0x87e004000078 = 0x%s secure external\n" % binascii.hexlify(fusf_rotpkx[3][::-1]))
    if args.ssk:
        key0 = long(args.ssk[0:16], 16)
        key1 = long(args.ssk[16:32], 16)
        key0 = struct.pack("<Q", key0)
        key1 = struct.pack("<Q", key1)
        outf.write("mm8 0x87e004000080 = 0x%s secure external\n" % binascii.hexlify(key0))
        outf.write("mm8 0x87e004000088 = 0x%s secure external\n" % binascii.hexlify(key1))
    if args.huk:
        key0 = long(args.huk[0:16], 16)
        key1 = long(args.huk[16:32], 16)
        key0 = struct.pack("<Q", key0)
        key1 = struct.pack("<Q", key1)
        outf.write("mm8 0x87e004000090 = 0x%s secure external\n" % binascii.hexlify(key0))
        outf.write("mm8 0x87e004000098 = 0x%s secure external\n" % binascii.hexlify(key1))

#
# Main entry point
#
def main():
    global ROTPK
    args = do_arg_parse()
    if args == None:
        return 1
    elif args.command == "genkey":
        return cmd_genkey(args)
    elif args.command == "create":
        # Read the Root of Trust key, little endian format
        ROTPK = read_pub_key(args.key)
        # Create the flash image
        flash = flash_create(args)
        outf = open(args.out, "wb")
        outf.write(flash)
        outf.close()
        # Write the partition table
        flash_fdisk(args.out)
        asim_fuses(args)
        if args.verbose:
            show_fuses(args)

# Call main
sys.exit(main())
