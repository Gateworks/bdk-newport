# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import re
import chip_list
import csr_data
import csr_utils
from yaml_utils import *

#
# Parse the bit description out of a structure field. The value
# is in the format "w#(#)" or (w#(#..#)", or "#", or "#..#"
#
def _parseBits(yaml):
    bits_str = getChild(yaml, "bits")
    if bits_str[0] != 'w':
        word = 0
        bits = bits_str.split("..")
    else:
        bits = bits_str.split("(")
        if len(bits) != 2:
            raiseException(yaml, "Unexpected bit format \"%s\"" % bits_str)
        word = int(bits[0][1:])
        if bits[1][-1] != ")":
            raiseException(yaml, "Unexpected bit format \"%s\"" % bits_str)
        bits = bits[1][0:-1].split("..")
    if len(bits) == 1:
        start_bit = int(bits[0])
        stop_bit = start_bit
    elif len(bits) != 2:
        raiseException(yaml, "Unexpected bit format \"%s\"" % bits_str)
    else:
        stop_bit = int(bits[0])
        start_bit = int(bits[1])
    if (word >= 64) or (start_bit < 0) or (start_bit >=64) or (stop_bit < start_bit) or (stop_bit >= 64):
        raiseException(yaml, "Unexpected bit format \"%s\"" % bits_str)
    start_bit = start_bit + word*64
    stop_bit = stop_bit + word*64
    # These will always be ordered with the smallest first
    return start_bit, stop_bit

#
# Parse an individual structure
#
def _parseStruct(root, yaml, chip, block):
    # Check that yaml doesn't have any unexpected tags
    checkChildren(yaml, [
        "name",          # Name of the structure (text)
        "title",         # Short description (text)
        "description",   # Optional description (text)
        "fields",        # Structure fields (sub tree)
        "internal",      # Optional internal (text)
        "attributes"])   # Optional attributes (sub tree)
    # Make the type name is lower case
    name = getChild(yaml,"name").lower()
    attributes = getChild(yaml, "attributes", allowMissing = True)
    if attributes:
        align = getChild(attributes, "struct_alignment_size", allowMissing = True)
        if align == "0":
            #print "\t%s: Skipping %s due to mis-alignment" % (chip, name)
            return
    if name in root:
        work_struct = root[name]
    else:
        work_struct = csr_data.Struct(name)
    # Add this chip and YAML
    work_struct.addChip(chip, yaml)
    work_struct["block"] = block
    root[name] = work_struct
    # Iterate all yaml fields
    fields = getChild(yaml, "fields")
    for f in fields:
        # Check that yaml doesn't have any unexpected tags
        checkChildren(f, [
            "name",          # Field name (text)
            "description",   # Optional description (text)
            "bits",          # w#(#) or w#(#..#)
            "internal",      # Optional internal (text)
            "attributes"])   # Optional attributes (sub tree)
        name = getChild(f, "name").lower()
        bits = _parseBits(f)
        if csr_utils.isReserved(name):
            name = csr_utils.getReservedName(bits)
        if not name in work_struct["fields"]:
            work_struct["fields"][name] = csr_data.StructField(name)
        item = work_struct["fields"][name]
        item.addChip(chip, f)
        item["bits"][chip] = bits

#
# Check for errors
#
def _validateStruct(root, name):
    struct = root[name]
    # Validate the type name
    if not re.match("^[a-z][a-z0-9_]*$", name):
        raiseException(struct, "Struct: Illegal name \"%s\"" % name)
    for n in struct["fields"]:
        if not re.match("^[a-z][a-z0-9_]*$", n):
            raiseException(struct, "Struct: Illegal field name \"%s\"" % n)
    # Find any missing bits
    chip_holes = csr_utils.findBitHoles(struct, multipleOf=32)
    # Create reserved fields for bits
    for chip in chip_holes:
        if ((getChild(struct["attributes"][chip], "allow_missing_bits", allowMissing=True) == "True") or
            (getChild(struct["attributes"][chip], "struct_not_64b_multiple", allowMissing=True) == "True")):
            for hole in chip_holes[chip]:
                n = csr_utils.getReservedName(hole)
                if not n in struct["fields"]:
                    struct["fields"][n] = csr_data.StructField(n)
                assert not chip in struct["fields"][n]["bits"]
                struct["fields"][n]["bits"][chip] = hole
        else:
            raiseException(struct, "Struct: Missing bits for chip %s %s" % (chip, chip_holes[chip]))
    # Sanity check the size. These can be changed without issue
    size = csr_utils.getSizeBits(struct, multipleOf=0)
    if (size < 32):
        raiseException(struct, "Struct: Size smaller than 32 bits")
    if (size > 32) and (size % 64 != 0):
        raiseException(struct, "Struct: Must be multiple of 64 bits")
    if (size > 512 * 8):
        raiseException(struct, "Struct: Size smaller than 512 bytes")

#
# Process all structures
#
def process(yaml_all):
    # This will return all the structures when we're done
    root = {}
    # Loop through all chips
    for chip in chip_list.getChips():
        # Get the YAML corresponding to this chip
        file = chip_list.getYamlFile(chip)
        yaml_root = yaml_all[file]
        # Loop through all blocks
        for block in yaml_root:
            # Trickbox doesn't exist in the chip as in only useful to Asim
            if block == "TRICKBOX":
                continue
            yaml_block = yaml_root[block]
            # Skip proprietary_for blocks
            attributes = getChild(yaml_block, "attributes", True)
            if attributes:
                p = getChild(attributes, "proprietary_for", True)
                if p and (not p in chip_list.ALLOWED_PROPRIETARY):
                    continue
            # Find the yaml structs section
            yaml_structs = getChild(yaml_block, "structs", True)
            if not yaml_structs:
                continue
            # Process each structure for this chip
            for struct in yaml_structs:
                _parseStruct(root, struct, chip, block)
    for s in root:
        _validateStruct(root, s)
    return root
