# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import re
from types import IntType, StringType
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

def generateRangeIter(ranges):
    if len(ranges) == 0:
        yield ranges
    else:
        for r in ranges[0]:
            first, last = r
            for i in [first, last]:
                for rest in generateRangeIter(ranges[1:]):
                    y = [i]
                    y.extend(rest)
                    yield y

def isAddressWrong(yaml, name, ranges, address_info, address_str):
    assert len(ranges) + 1 == len(address_info), "Number of ranges doesn't match the length of the equation"
    locals = {}
    for r in generateRangeIter(ranges):
        eq_answer = address_info[0]
        for i in range(len(r)):
            local_name = chr(ord('a') + i)
            locals[local_name] = r[i]
            eq_answer += address_info[i+1] * r[i]
        str_answer = eval(address_str, {}, locals)
        assert isinstance(str_answer, IntType), address_str
        #assert str_answer == eq_answer, address_str
        if str_answer != eq_answer:
            #print "%s[%s]: %s" % (yaml["name"], name, address_str)
            return True
    return False

#
# Parse the string from YAML into the numbers we need
#
def parseAddress(yaml, name, ranges):
    str_eq = getChild(yaml, name).lower()
    num_args = len(ranges)
    locals = {}
    for i in range(num_args):
        locals[chr(ord('a') + i)] = 0
    address_base = eval(str_eq, {}, locals)
    if not isinstance(address_base, IntType):
        raiseException(yaml, "Invalid equation for %s \"%s\"" % (name, str_eq))
    address_info = [long(address_base)]
    for i in range(num_args):
        locals[chr(ord('a') + i)] = 1
        tmp = eval(str_eq, {}, locals)
        if not isinstance(tmp, IntType):
            raiseException(yaml, "Invalid equation for %s \"%s\"" % (name, str_eq))
        locals[chr(ord('a') + i)] = 0
        tmp -= address_base
        address_info.append(tmp)
    if isAddressWrong(yaml, name, ranges, address_info, str_eq):
        return str_eq
    else:
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
    work_reg["address"][chip] = parseAddress(yaml,"address", ranges)
    work_reg["ranges"][chip] = ranges
    work_reg["bus"][chip] = _parseBus(yaml)
    work_reg["bar"][chip] = getChild(yaml,"bar", True)
    if attributes:
        work_reg["attributes"][chip] = attributes
    # CN9XXX special check for PCIe config space. The hardware team removed
    # the PEM index from the PCIe config registers, which was exceedingly
    # useful for software. Since logical arguments to make software compatible
    # fail to move the hardware team, hack the registers as we load them.
    # Modify the address equation to contain the PEM number
    if (("CN9" in chip) or ("CNF9" in chip)) and (work_reg["bus"][chip] in ["PCICONFIGEP", "PCICONFIGEP_SHADOW", "PCICONFIGEPVF", "PCICONFIGRC"]):
        if work_reg["address"][chip][1] == 0:
            work_reg["address"][chip][1] = 0x100000000
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
    # Limit to MAX_CSR_PARAMS parameters as a sanity check. This can be raised
    # bu editing the C database code
    if num_params > chip_list.MAX_CSR_PARAMS:
        raiseException(reg, "Reg: Too many params, name \"%s\"" % name)
    # Make sure the address equation agrees on the number of params
    for chip in reg["address"]:
        eq = reg["address"][chip]
        if isinstance(eq, StringType):
            continue
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
            reg["bar"][chip] = "RVU_" + reg["bar"][chip]
            reg["bar_size"][chip] = shift
            if len(block_addr) > 1:
                if name.startswith(rvu_block.lower() + "#_"):
                    del root[name]
                    name = name.replace(rvu_block.lower() + "#_", rvu_block.lower() + "_")
                else:
                    assert name.startswith(rvu_block.lower() + "_")
                    del root[name]
                name = rvu_block.lower() + "#" + name[len(rvu_block.lower()):]
                reg["name"] = name
                reg["address"][chip].insert(1, block_addr[1] << shift)
                reg["ranges"][chip].insert(0, block_range[0])
                root[name] = reg

#
# For registers in a PCIe BAR, build the bar offset and store the bar size
#
def _buildBarOffsets(root, name, enums):
    reg = root[name]
    # We do every chip independently because BAR data may change per chip
    for chip in reg["bar"]:
        if reg["bar"][chip] == None:
            # This register isn't tied to a BAR, set all data to None
            reg["bar_size"][chip] = None
            reg["bar_offset"][chip] = None
            reg["bar_ranges"][chip] = None
        else:
            # Create a list of possible BAR names. RVU BARs are special in that
            # they apply to a chip but aren't listed in the enums
            bar_info = {}
            bar_info["RVU_BAR0"] = enums["rvu_bar_e"]["values"]["RVU_PF#_BAR0"]
            bar_info["RVU_BAR2"] = enums["rvu_bar_e"]["values"]["RVU_PF#_FUNC#_BAR2"]
            # Special handling of RVU BAR sizes. The yaml specifies the sizes
            # For BAR0 as 33 bit and BAR2 as 25 bits. These sizes include the
            # block and function info that the ECAMs consider outside the BAR.
            # Change the BAR0 to be 28 bits and BAR2 to 20 bits. These sizes
            # See http://mawiki.caveonetworks.com/wiki/93xx/RVU
            bar_info["RVU_BAR0"]["bar_size"][chip] = 28
            bar_info["RVU_BAR2"]["bar_size"][chip] = 20
            # Build the enum name that contains BAR enumerations
            block = reg["block"]
            bar_enum_name = block.lower() + "_bar_e"
            # If we find the enum, add its values to the possible BAR names
            if bar_enum_name in enums:
                for name in enums[bar_enum_name]["values"]:
                    e = enums[bar_enum_name]["values"][name]
                    # Skip if it doesn't apply to this chip. This happens when
                    # tha name of the BAR varies slightly between chips
                    if not chip in e["value"]:
                        continue
                    assert "_BAR" in name, name
                    # All BARs are numbered BAR0, BAR2, or BAR4
                    for bar_num in [0, 2, 4]:
                        if not name.endswith("_BAR%d" % bar_num):
                            continue
                        if "VF" in name:
                            bar_info["VF_BAR%d" % bar_num] = e
                        elif "PF" in name:
                            bar_info["PF_BAR%d" % bar_num] = e
                        else: # Hardware team didn't specify PF or VF on chips without VF
                            bar_info["PF_BAR%d" % bar_num] = e
            # Get the BAR name specified in the register
            bar = reg["bar"][chip]
            if bar.startswith("BAR"):
                # Hardware team didn't specify PF or VF on chips without VF
                bar = "PF_" + bar
            assert bar in bar_info, bar
            # Get the BAR size and equation data
            bar_size = bar_info[bar]["bar_size"][chip]
            bar_eq = bar_info[bar]["value"][chip]
            assert bar_size
            assert bar_eq
            # Get the register address and see if its in the BAR
            reg_eq = reg["address"][chip]
            if not "RVU" in bar:
                # Skip registers not in bar
                low = bar_eq[0]
                high = low + (1 << bar_size)
                if (reg_eq[0] < low) or (reg_eq[0] >= high):
                    #print "\tSkip %s for %s:%s(0x%x), outside(0x%x - 0x%x)" % (bar, chip, reg["name"], reg_eq[0], low, high)
                    reg["bar_size"][chip] = None
                    reg["bar_offset"][chip] = None
                    reg["bar_ranges"][chip] = None
                    continue
            # Use the BAR equations to simplify the register equation
            assert len(reg["address"][chip]) == len(reg["ranges"][chip]) + 1
            bar_offset = []
            bar_ranges = []
            offset = reg["address"][chip][0] - bar_eq[0]
            offset &= (1 << bar_size) - 1
            bar_offset.append(offset)
            for i in range(1, len(reg["address"][chip])):
                if reg["address"][chip][i] < (1 << bar_size):
                    bar_offset.append(reg["address"][chip][i])
                    bar_ranges.append(reg["ranges"][chip][i-1])
            reg["bar_size"][chip] = bar_size
            reg["bar_offset"][chip] = bar_offset
            reg["bar_ranges"][chip] = bar_ranges
        # End of BAR use check
    # End of chip loop
    return

#
# Process all registers
#
def process(yaml_all, enums):
    # This will return all the registers when we're done
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
    for r in root.keys():
        _buildBarOffsets(root, r, enums)
    return root
