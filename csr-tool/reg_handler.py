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
from types import IntType
import chip_list
import csr_data
import csr_utils
from yaml_utils import *

def _parseBus(yaml):
    bus = getChild(yaml,"bus")
    if not bus in chip_list.VALID_BUSSES:
        raiseException(yaml, "Unexpected bus \"%s\"" % bus)
    return bus

def _parseAccess(yaml):
    access = getChild(yaml,"access")
    # Strip off the hardware modified flag during checking
    if access.endswith("/H"):
        a = access[0:-2]
    else:
        a = access
    if not a in chip_list.VALID_ACCESS:
        raiseException(yaml, "Unexpected access \"%s\"" % access)
    return access

def _parseFieldValue(yaml, name):
    value = getChild(yaml, name).lower()
    if value in ["--", "ns", "x"]:
        value = "--"
    elif value in ["all-ones"]:
        value = long(-1)
    else:
        try:
            value = long(value, 0)
        except:
            raiseException(yaml, "Invalid value for %s \"%s\"" % (name, value))
    return value

#
# Parse the string from YAML into the numbers we need
#
def parseAddress(yaml, name):
    str_eq = getChild(yaml, name).lower()
    try:
        return [long(str_eq, 0)]
    except:
        pass
    # The address equation takes an unknown number of arguments. Keep adding
    # arguments until we can evaluate the equation. The max number of arguments
    # is arbitrary and can be increased in the future
    num_args = 0
    locals = {}
    for i in range(4):
        # Add another argument to the locals environment
        locals[chr(ord('a') + i)] = 0
        # Try and evaluate the equation
        try:
            tmp = eval(str_eq, {}, locals)
            # Success, record the number of args
            num_args = i + 1
            break
        except:
            pass # We probably need another argument
    if num_args == 0:
        raiseException(yaml, "Invalid equation for %s \"%s\"" % (name, str_eq))
    address_info = []
    address_base = eval(str_eq, {}, locals)
    if not isinstance(address_base, IntType):
        raiseException(yaml, "Invalid equation for %s \"%s\"" % (name, str_eq))
    address_info.append(address_base)
    for i in range(num_args):
        locals[chr(ord('a') + i)] = 1
        tmp = eval(str_eq, {}, locals)
        if not isinstance(tmp, IntType):
            raiseException(yaml, "Invalid equation for %s \"%s\"" % (name, str_eq))
        locals[chr(ord('a') + i)] = 0
        tmp -= address_base
        address_info.append(tmp)
    return address_info

#
# Parse the bit description out of a structure field. The value
# is in the format "#", or "#..#"
#
def _parseBits(yaml):
    bits_str = getChild(yaml, "bits")
    bits = bits_str.split("..")
    if len(bits) == 1:
        start_bit = int(bits[0])
        stop_bit = start_bit
    elif len(bits) != 2:
        raiseException(yaml, "Unexpected bit format \"%s\"" % bits_str)
    else:
        stop_bit = int(bits[0])
        start_bit = int(bits[1])
    if (start_bit < 0) or (start_bit >= 64) or (stop_bit < start_bit) or (stop_bit >= 64):
        raiseException(yaml, "Unexpected bit format \"%s\"" % bits_str)
    # These will always be ordered with the smallest first
    return start_bit, stop_bit

#
# Parse an individual register
#
def _parseReg(root, yaml, chip, yaml_root, block):
    # Skip deprecated registers
    attributes = getChild(yaml, "attributes", allowMissing = True)
    if attributes:
        deprecated = getChild(attributes, "deprecated", allowMissing = True)
        if deprecated:
            assert deprecated == "RAZ", "Deprecated is expected to be RAZ"
            return
    # Check that yaml doesn't have any unexpected tags
    checkChildren(yaml, [
        "name",          # CSR name (text with range info embedded)
        "fields",        # Fields of the register (sub tree)
        "description",   # Description of the register (text)
        "notes",         # Extra notes after description (text)
        "title",         # One line title/description (text)
        "address",       # Address equation for register (text equation)
        "bus",           # Type of the register (keyword)
        "attributes",    # Optional attributes (sub tree)
        "bar",           # Information about how to device the CSR space into PCIe BARs
        "internal"])     # Internal description (text)
    # Make the type name is lower case
    name = getChild(yaml,"name").lower()
    # "(s)" in the name represents secure, change it to a "s"
    name = name.replace("(s)", "s")
    name, ranges = csr_utils.parseNameForRanges(name, yaml)
    if name in root:
        work_reg = root[name]
    else:
        work_reg = csr_data.Register(name)
    # Add this chip and YAML
    work_reg.addChip(chip, yaml)
    root[name] = work_reg
    work_reg["block"] = block
    work_reg["address"][chip] = parseAddress(yaml,"address")
    work_reg["ranges"][chip] = ranges
    work_reg["bus"][chip] = _parseBus(yaml)
    work_reg["bar"][chip] = getChild(yaml,"bar", True)
    # CN9XXX special check for PCIe config space. The hardware team removed
    # the PEM index from the PCIe config registers, which was exceedingly
    # useful for software. Since logical arguments to make software compatible
    # fail to move the hardware team, hack the registers as we load them.
    # Modify the address equation to contain the PEM number
    if ("CN9" in chip) and (work_reg["bus"][chip] in ["PCICONFIGEP", "PCICONFIGEP_SHADOW", "PCICONFIGEPVF", "PCICONFIGRC"]):
        old = work_reg["address"][chip]
        work_reg["address"][chip] = [old[0]]
        work_reg["address"][chip].append(0x100000000)
        work_reg["address"][chip].extend(old[1:])
    # For RVU registers we need to determine the RVU_BLOCK_ID
    rvu_block_id = None
    if "RVU" in work_reg["bus"][chip]:
        attr = getChild(yaml, "attributes", allowMissing = True)
        if attr:
            rvu_block_id = getChild(attr, "rvu_block_id", allowMissing = True)
        if not rvu_block_id:
            attr = getChild(yaml_root[block], "attributes")
            rvu_block_id = getChild(attr, "rvu_block_id")
        rvu_block_id = rvu_block_id.split(":")[-1]
        assert work_reg["bar"][chip] == None
        if work_reg["bus"][chip] == "RVU_PF_BAR0":
            work_reg["bar"][chip] = "BAR0"
        else:
            assert "BAR2" in work_reg["bus"][chip]
            work_reg["bar"][chip] = "BAR2"
    work_reg["rvu_block_id"][chip] = rvu_block_id
    # Inherits should have been handled by csr3
    inherits = getChild(yaml, "inherits", True)
    if inherits:
        raiseException(yaml, "Unexpected inherit")
    # Iterate all yaml fields
    fields = getChild(yaml, "fields")
    for f in fields:
        # Check that yaml doesn't have any unexpected tags
        checkChildren(f, [
            "name",          # Name of the field (text name)
            "bits",          # Bits used. Either single number or "number..number"
            "access",        # Access mode (RO, RW, etc)
            "reset",         # Reset value of the fields
            "typical",       # Typical value
            "description",   # Description of the field (text)
            "internal",      # Hardware team internal only notes
            "attributes"])   # Optional attributes (sub tree)
        name = getChild(f, "name").lower()
        bits = _parseBits(f)
        if csr_utils.isReserved(name):
            name = csr_utils.getReservedName(bits)
        if not name in work_reg["fields"]:
            work_reg["fields"][name] = csr_data.RegisterField(name)
        item = work_reg["fields"][name]
        item.addChip(chip, f)
        item["bits"][chip] = bits
        item["access"][chip] = _parseAccess(f)
        item["reset"][chip] = _parseFieldValue(f, "reset")
        item["typical"][chip] = _parseFieldValue(f, "typical")

#
# Check for errors
#
def _validateReg(root, name):
    reg = root[name]
    # Validate the type name
    if not re.match("^[a-z][a-z0-9#_]*$", name):
        raiseException(reg, "Reg: Illegal name \"%s\"" % name)
    # Count the number of parameters
    num_params = name.count("#")
    # Limit to 4 parameters as a sanity check. This can be raised without
    # issue
    if num_params > 4:
        raiseException(reg, "Reg: Too many params, name \"%s\"" % name)
    # Make sure the address equation agrees on the number of params
    for chip in reg["address"]:
        eq = reg["address"][chip]
        if len(eq) != num_params + 1:
            raiseException(reg, "Reg: Unexpected equation length for %s %s" % (chip, eq))
        if len(reg["ranges"][chip]) != num_params :
            raiseException(reg, "Reg: Unexpected range length for %s %s" % (chip, reg["ranges"][chip]))
    # Check fields
    for n in reg["fields"]:
        if not re.match("^[a-z][a-z0-9_]*$", n):
            raiseException(reg, "Reg: Illegal field name \"%s\"" % n)
    # Find any missing bits
    chip_holes = csr_utils.findBitHoles(reg, multipleOf=32)
    # Create reserved fields for bits
    for chip in chip_holes:
        raiseException(reg, "Reg: Missing bits for chip %s %s" % (chip, chip_holes[chip]))
    # Sanity check the size. These can be changed without issue
    size = csr_utils.getSizeBits(reg, multipleOf=0)
    if (size != 32) and (size != 64):
        raiseException(struct, "Reg: Size not 32 or 64 bits")

def _fixAddressRVU(root, name, enums):
    addr_e = enums["rvu_block_addr_e"]["values"]
    rvu_bar_e_bar0 = enums["rvu_bar_e"]["values"]["RVU_PF#_BAR0"]["value"]
    rvu_bar_e_bar2 = enums["rvu_bar_e"]["values"]["RVU_PF#_FUNC#_BAR2"]["value"]
    reg = root[name]
    for chip in reg["rvu_block_id"]:
        rvu_block = reg["rvu_block_id"][chip]
        if rvu_block:
            if rvu_block in addr_e:
                block_addr = addr_e[rvu_block]["value"][chip]
                block_range = addr_e[rvu_block]["ranges"][chip]
            else:
                block_addr = addr_e[rvu_block + "#"]["value"][chip]
                block_range = addr_e[rvu_block + "#"]["ranges"][chip]
            assert len(block_addr) in [1,2], "Unexpected length for RVU_BLOCK_ADDR_E::" + rvu_block
            assert reg["bar"][chip] in ["BAR0", "BAR2"]
            if reg["bar"][chip] == "BAR0":
                assert reg["address"][chip][0] < (1<<28), "Out of BAR0"
                address = rvu_bar_e_bar0[chip][0]
                shift = 28
            else:
                assert reg["address"][chip][0] < (1<<20), "Out of BAR2"
                address = rvu_bar_e_bar2[chip][0]
                shift = 20
            reg["address"][chip][0] += address
            reg["address"][chip][0] += block_addr[0] << shift
            if len(block_addr) > 1:
                assert name.startswith(rvu_block.lower() + "_")
                del root[name]
                name = rvu_block.lower() + "#" + name[len(rvu_block.lower()):]
                reg["name"] = name
                reg["address"][chip].insert(1, block_addr[1] << shift)
                reg["ranges"][chip].insert(0, block_range[0])
                root[name] = reg

#
# Process all registers
#
def process(yaml_all, enums):
    # This will return all the registers when we're done
    root = {}
    # Loop through all chips
    for chip in chip_list.getChips():
        # Get the YAML coresponding to this chip
        file = chip_list.getYamlFile(chip)
        yaml_root = yaml_all[file]
        # Loop through all blocks
        for block in yaml_root:
            # Trickbox doesn't exist in the chip as in only useful to Asim
            if block == "TRICKBOX":
                continue
            yaml_block = yaml_root[block]
            # Find the yaml registers section
            yaml_regs = getChild(yaml_block, "registers", True)
            if not yaml_regs:
                continue
            # Process each register for this chip
            for reg in yaml_regs:
                _parseReg(root, reg, chip, yaml_root, block)
    for r in root.keys():
        _validateReg(root, r)
        _fixAddressRVU(root, r, enums)
    return root
