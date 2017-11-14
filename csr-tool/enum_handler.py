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
import re
import chip_list
import csr_data
import csr_utils
import reg_handler
from yaml_utils import *

#
# Parse a single enumeration for one chip
#
def _parseEnum(root, yaml, chip, block):
    # Check that yaml doesn't have any unexpected tags
    checkChildren(yaml, [
        "name",          # Name of the enum (text)
        "title",         # Short description (text)
        "attributes",    # Optional attributes (sub tree)
        "description",   # Optional description (text)
        "internal",      # Optional internal (text)
        "values"])       # Enum values (sub tree)
    # Make the type name is lower case
    name = getChild(yaml,"name").lower()
    if name in root:
        work_enum = root[name]
    else:
        work_enum = csr_data.Enum(name)
    # Add this chip and YAML
    work_enum.addChip(chip, yaml)
    work_enum["block"] = block
    attributes = getChild(yaml, "attributes")
    work_enum["width"][chip] = int(getChild(attributes, "width"))
    root[name] = work_enum
    # Iterate all yaml values
    values = getChild(yaml, "values")
    for v in values:
        # Check that yaml doesn't have any unexpected tags
        checkChildren(v, [
            "name",          # Value name (text)
            "value",         # Value (number or equation)
            "attributes",    # Optional attributes (sub tree)
            "internal",      # Optional internal (text)
            "description"])  # Optional description (text)
        # Enum values are upper case
        name = getChild(v, "name").upper()
        name, ranges = csr_utils.parseNameForRanges(name, v)
        if not name in work_enum["values"]:
            work_enum["values"][name] = csr_data.EnumValue(name)
        item = work_enum["values"][name]
        item.addChip(chip, v)
        item["value"][chip] = reg_handler.parseAddress(v, "value")
        item["ranges"][chip] = ranges
        attributes = getChild(v, "attributes", True)
        if attributes:
            s = getChild(attributes, "pcc_bar_size_bits", True)
            if s:
                item["bar_size"][chip] = int(s)

#
# Check for errors
#
def _validateEnum(root, name):
    enum = root[name]
    # Validate the type name
    if not re.match("^[a-z][a-z0-9_]*$", name):
        raiseException(enum, "Enum: Illegal name \"%s\"" % name)
    # Check enum width
    for chip in enum["width"]:
        if (enum["width"][chip] < 1) or (enum["width"][chip] > 52):
            raiseException(enum, "Enum: Illegal width \"%s\" for chip %s" % (enum["width"][chip], chip))
    for n in enum["values"]:
        v = enum["values"][n]
        # Validate the specific value name. These can contain
        # parameters
        if not re.match("^[A-Z][A-Z0-9#_]*$", n):
            raiseException(v, "Enum: Illegal name \"%s\"" % n)
        # Validate bar sizes
        for chip in v["bar_size"]:
            if (v["bar_size"][chip] < 16) or (v["bar_size"][chip] > 40):
                raiseException(v, "Enum: Unexpected bar size \"%s\"" % v["bar_size"][chip])
        # Count the number of parameters
        num_params = n.count("#")
        # Limit to 3 parameters as a sanity check. This can be raised without
        # issue
        if num_params > 3:
            raiseException(v, "Enum: Too many params, name \"%s\"" % n)
        # Loop through values for each chip
        for chip in v["value"]:
            eq = v["value"][chip]
            if len(eq) != num_params + 1:
                raiseException(v, "Enum: Unexpected equation length for %s" % chip)
            if len(v["ranges"][chip]) != num_params :
                raiseException(v, "Enum: Unexpected range length for %s" % chip)
            # Make sure all enums fit inside 48 bits.
            for num in eq:
                if num >= (1L<<48):
                    raiseException(v, "Enum: Out of range for %s %s" % (chip, eq))

#
# Process all enums for all chips
#
def process(yaml_all):
    # This will return all the enums when we're done
    root = {}
    # Loop for every chip
    for chip in chip_list.getChips():
        # Get the YAML coresponding to this chip
        file = chip_list.getYamlFile(chip)
        # Loop through all blocks
        yaml_root = yaml_all[file]
        for block in yaml_root:
            # Trickbox doesn't exist in the chip as in only useful to Asim
            if block == "TRICKBOX":
                continue
            yaml_block = yaml_root[block]
            # Find the yaml enums section
            yaml_enums = getChild(yaml_block, "enums", True)
            if not yaml_enums:
                continue
            # Process each enum for this chip
            for enum in yaml_enums:
                _parseEnum(root, enum, chip, block)
    for e in root:
        _validateEnum(root, e)
    return root
