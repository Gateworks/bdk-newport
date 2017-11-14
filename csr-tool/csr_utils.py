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
import types
import re
import chip_list
import csr_data
from yaml_utils import raiseException

#
# The designers aren't always consistent about the name used for reserved
# fields. This function checks the name for some of the common choices
#
def isReserved(name):
    if name == "--":
        return True;
    if name.startswith("reserved"):
        return True;
    return False

#
# We name reserved fields with a standardized name based on the bit position.
# This function creates the standard names
#
def getReservedName(bits):
    assert len(bits) == 2
    if bits[0] == bits[1]:
        return "reserved_%d" % bits[0]
    else:
        return "reserved_%d_%d" % (bits[0], bits[1])

#
# Check if a chip applies to a specific architecture. The possible
# architectures are "octeon", "thunder", and "thunder2".
#
def isChipArch(arch, chip):
    assert arch in ["octeon", "thunder", "thunder2"], "Invalid architecture"
    if chip.startswith("CN9"):
        return (arch == "thunder")
    elif chip.startswith("CN8"):
        return (arch == "thunder")
    else:
        return (arch == "octeon")

#
# Check if a DataItem applies to a specific architecture. Each architecture
# gets its  own header files and data base files. Only HTML files handle
# multiple architectures
#
def isArch(arch, dataItem):
    for chip in dataItem["description"].keys():
        if isChipArch(arch, chip):
            return True
    return False

#
# This function returns a list of undefined bits inside a structure or
# register. The output is a dictionary of chips with each chip that has
# a hole.
#
def findBitHoles(struct, multipleOf):
    assert (multipleOf == 32) or (multipleOf == 64), "Unexpected size multiple of %d" % multipleOf
    chips = struct["description"].keys()
    result = {}
    for chip in chips:
        exists = []
        for f in struct["fields"]:
            bits = struct["fields"][f]["bits"]
            if chip in bits:
                exists.append(bits[chip])
        # Exists is empty if this structure doesn't exist on this chip
        if exists == []:
            continue
        exists.sort()
        next_bit = 0
        holes = []
        for bits in exists:
            start_bit = bits[0]
            stop_bit = bits[1]
            if start_bit < next_bit:
                raiseException(struct, "Overlap of bits around bit %d" % start_bit)
            elif start_bit == next_bit:
                # No hole
                next_bit = stop_bit + 1
            else:
                # Hole between next_bit and start_bit
                while next_bit != start_bit:
                    bit = (next_bit & -multipleOf) + multipleOf - 1
                    if bit > start_bit - 1:
                        bit = start_bit - 1
                    hole = (next_bit, bit)
                    holes.append(hole)
                    #print "Hole for %s on chip %s: %d..%d" % (struct["name"], chip, hole[0], hole[1])
                    next_bit = bit + 1
                # Resume after stop_bit now that we found the hole
                next_bit = stop_bit + 1
        # Make sure structs end on a multiple
        if next_bit % multipleOf != 0:
            stop_bit = (next_bit & -multipleOf) + multipleOf - 1
            hole = (next_bit, stop_bit)
            holes.append(hole)
            #print "Hole for %s on chip %s: %d..%d" % (struct["name"], chip, hole[0], hole[1])
        if holes:
            result[chip] = holes
    return result

#
# Parse the name of an object to extract the range parameters inside it.
# The pass object in "obj" is only used to display debug information
# on error. Ouput is a tuple. First is the name with ranges replaced with
# "#". The second is a list of ranges, where element 0 is the list of ranges
# for arg1, element 1 is the list of ranges for arg2, etc.
#
def parseNameForRanges(name, obj):
    ranges = []
    # Handle the simple case of no ranges at all
    if not "(" in name:
        return name, ranges
    # Create a list of broken up name pieces
    parts = []
    for p in name.split("("):
        p2 = p.split(")")
        parts.extend(p2)
    # Names must start with a letter, so the parts above will be broken
    # such that even pieces are name and odd pieces are ranges
    new_name = []
    for i in range(len(parts)):
        if i & 1 == 0:
            # Name piece
            if re.match("^[A-Za-z0-9_]*$", parts[i]):
                new_name.append(parts[i])
            else:
                raiseException(obj, "Illegal name \"%s\"" % name)
        else:
            # Range piece, will parse later
            ranges.append(parts[i])
    # Create the final name
    new_name = "#".join(new_name)
    # Each range can be:
    #   - A single number "X"
    #   - Two numbers "X..Y"
    #   - A sequence of the above two separated by commas "X..Y,Z"
    for i in range(len(ranges)):
        terms = ranges[i].split(",")
        for t in range(len(terms)):
            if re.match("^[0-9]+\.\.[0-9]+$", terms[t]):
                parts = terms[t].split("..")
                num1 = int(parts[0])
                num2 = int(parts[1])
                terms[t] = (num1, num2)
            elif re.match("^[0-9]+$", terms[t]):
                num = int(terms[t])
                terms[t] = (num, num)
            else:
                raiseException(obj, "Illegal name \"%s\"" % name)
        ranges[i] = terms
    return new_name, ranges

#
# Convert an address list into an equation string
#
def addressToString(address_list, range_list, addSuffix=False, smartHex=True):
    suffix = ""
    if addSuffix:
        for v in address_list:
            if v > (1<<31):
                suffix = "ll"
    eq = ""
    for i,v in enumerate(address_list):
        param = chr(ord('a') + i - 1)
        if (i > 0) and (range_list !=None):
            # Figure out the minimum number of bits to cover the entire range
            max_range = 0
            for rng in range_list[i-1]:
                for r in rng:
                    assert r >= 0, "Unexpected negative range value"
                    if r > max_range:
                        max_range = r
            power2 = 1
            while power2 <= max_range:
                power2 <<= 1
            # AND the parameter so the compile knows to do a bit insert
            param = "(%s) & 0x%x" % (param, power2-1)
        if i == 0:
            if (v < 10) or not smartHex:
                eq = "%d%s" % (v, suffix)
            else:
                eq = "0x%x%s" % (v, suffix)
        elif v == 1:
            eq += " + (%s)" % param
        elif (v < 10) or not smartHex:
            eq += " + %d%s * (%s)" % (v, suffix, param)
        else:
            eq += " + 0x%x%s * (%s)" % (v, suffix, param)
    return eq

#
# Convert a range list into a string
#
def rangeToString(range_list):
    result = []
    for arg_ranges in range_list:
        result.append("(")
        for rmin,rmax in arg_ranges:
            if result[-1] != "(":
                result.append(", ")
            result.append("%d" % rmin)
            if rmin != rmax:
                result.append("..%d" % rmax)
        result.append(")")
    return "".join(result)

#
# Compare an item for two differnet chips. When this is called the
# item is known to be valid on both chips
#
def isDifferent(chip1, chip2, data):
    assert isinstance(data, csr_data.DataItem)
    for key in data:
        # Allow differences in location info
        if key.startswith("_"):
            continue
        # Allow differences in attributes
        if key == "attributes":
            continue
        # Allow differences in ranges
        if key == "ranges":
            continue
        item = data[key]
        # If the item isn't a dictionary then it doesn't vary per chip
        if isinstance(item, types.StringType):
            continue
        assert isinstance(item, types.DictType)
        # Empty is the same on both chips
        if not item:
            continue
        first = item.keys()[0]
        if isinstance(item[first], csr_data.DataItem):
            # Indexed by names
            for n in item:
                if isDifferent(chip1, chip2, item[n]):
                    return True
        else:
            # Indexed by chip
            assert first.startswith("CN")
            if chip1 in item and chip2 in item:
                # Both exists
                child1 = item[chip1]
                child2 = item[chip2]
                if str(child1) != str(child2):
                    return True
            elif chip1 in item:
                # Only chip1 is valid
                return True
            elif chip2 in item:
                # Only chip2 is valid
                return True
            else:
                # Not in either
                continue
    return False

#
# Return the size of a structure or register in bits. We currently require
# this to be a multiple of multipleOf (if non-zero). This code doesn't care,
# but its a sanity check for yaml.
#
def getSizeBits(struct_reg, multipleOf):
    assert (multipleOf == 0) or (multipleOf == 32) or (multipleOf == 64), "Unexpected size multiple of %d" % multipleOf
    size_bits = 0
    fields = struct_reg["fields"]
    for name in fields:
        field = fields[name]
        for chip in field["bits"]:
            bits = field["bits"][chip]
            if bits[1] >= size_bits:
                size_bits = bits[1]+1
    if multipleOf and (size_bits % multipleOf != 0):
        raiseException(struct_reg, "Structures and registers are expected to be a multiple of %d bits" % multipleOf)
    return size_bits

#
# Given the fields of a structure or register, fill in the subset "s"
# of fields that can be used across all chips
#
def createSubset(arch, struct_reg):
    isReg = isinstance(struct_reg, csr_data.Register)
    bit_size = getSizeBits(struct_reg, multipleOf=0)
    if bit_size & 63:
        multipleOf = 32
    else:
        multipleOf = 64
    if isReg:
        subset = csr_data.Register(struct_reg["name"])
    else:
        subset = csr_data.Struct(struct_reg["name"])
    # Go through all the fields, skipping reserved bits
    subset["description"]["s"] = "Common subset"
    subset_fields = subset["fields"]
    for name in struct_reg["fields"]:
        if isReserved(name):
            continue
        start_bit_changed = False
        start_bit = None
        stop_bit = None
        description = ""
        access = ""
        f = struct_reg["fields"][name]
        # Go through all the chips for this field and expand it so that
        # start_bit and stop_bit encompass the largest version of the field.
        # Remember if the start_bit changed as we can't handle that in C code.
        for chip in f["bits"]:
            # Skip other architecture as we don't care about conflicts
            if not isChipArch(arch, chip):
                continue
            if start_bit == None:
                start_bit, stop_bit = f["bits"][chip]
                description = f["description"][chip]
                if isReg:
                    access = f["access"][chip]
            elif f["bits"][chip][0] < start_bit:
                start_bit = f["bits"][chip][0]
                start_bit_changed = True
            elif f["bits"][chip][0] > start_bit:
                start_bit_changed = True
            elif f["bits"][chip][1] > stop_bit:
                stop_bit = f["bits"][chip][1]
        if start_bit == None:
            continue
        # Add this field to the subset
        if isReg:
            subset_fields[name] = csr_data.RegisterField(name)
            subset_fields[name]["access"]["s"] = access
        else:
            subset_fields[name] = csr_data.StructField(name)
        subset_fields[name]["bits"]["s"] = (start_bit, stop_bit)
        subset_fields[name]["description"]["s"] = description
        # Remember if the start_bit changed, causing this field to be a conflict
        subset_fields[name]["conflict_bits"] = start_bit_changed
    # Loop through all the fields in the subset looking for overlaps
    for name in subset_fields:
        start_bit, stop_bit = subset_fields[name]["bits"]["s"]
        # Check against all fields except myself
        for n in subset_fields:
            if n == name:
                continue
            # Mark both fields as conflicts if they overlap
            if start_bit <= subset_fields[n]["bits"]["s"][1] and stop_bit >= subset_fields[n]["bits"]["s"][0]:
                subset_fields[name]["conflict_bits"] = True
                subset_fields[n]["conflict_bits"] = True
    # Loop through the subset fields deleting the ones we flagged as conflicts
    names = subset_fields.keys()
    for name in names:
        if subset_fields[name]["conflict_bits"]:
            # Delete the conflict
            del subset_fields[name]
        else:
            # Delete the false conflict marker
            del subset_fields[name]["conflict_bits"]
    # Fields should only be a valid subset. Now fill in the holes
    holes = findBitHoles(subset, multipleOf)
    subset_size = getSizeBits(subset, multipleOf=0)
    while subset_size < bit_size:
        start_bit = subset_size
        stop_bit = bit_size - 1
        max_step = (start_bit & -multipleOf) + multipleOf - 1
        if stop_bit > max_step:
            stop_bit = max_step
        subset_size = stop_bit + 1
        if not "s" in holes:
            holes["s"] = []
        if (len(holes["s"]) > 0) and holes["s"][-1][1] == stop_bit:
            pass # Already in holes list
        else:
            holes["s"].append((start_bit, stop_bit))
            #print "Padding for %s on subset: %d..%d" % (struct_reg["name"], start_bit, stop_bit)
    if holes:
        for hole in holes["s"]:
            n = getReservedName(hole)
            #print "Filling hole in %s for subset: %s" % (struct_reg["name"], n)
            assert not n in subset_fields
            if isReg:
                subset_fields[n] = csr_data.RegisterField(n)
            else:
                subset_fields[n] = csr_data.StructField(n)
            subset_fields[n]["bits"]["s"] = hole
    subset_size = getSizeBits(subset, multipleOf)
    assert subset_size == bit_size, "%s subset %d, original %d" % (struct_reg["name"], subset_size, bit_size)
    return subset

#
# Get the reset value for a Register
#
def getResetValue(chip, reg):
    reset = 0
    for name in reg["fields"]:
        f = reg["fields"][name]
        if chip in f["reset"]:
            r = f["reset"][chip]
            if r != "--":
                r &= (1 << (f["bits"][chip][1] - f["bits"][chip][0] + 1)) - 1
                r <<= f["bits"][chip][0]
                reset |= r
    return reset


