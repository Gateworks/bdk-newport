# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import datetime
import StringIO
import csr_utils
import chip_list
import csr_data
import textwrap

# All generated identifiers will have this prefix. The case
# will be changed to lowercase for types
PREFIX = "CAVM_"
FILE_PREFIX = "cavm-csrs"

#
# For the top level common fields, we don't know which chip to use
# the field for. As a guess, use the last of the sorted chip names
#
def getAnyField(data, field, arch):
    keys = data[field].keys()
    keys.sort()
    keys.reverse()
    for chip in keys:
        if csr_utils.isChipArch(arch, chip):
            return data[field][chip]
    return None

#
# Format a description for use at the end of a line. All but the first line
# is indented
#
def formatDescription(descr, indent):
    d = descr.split("\n")
    return "\n".ljust(indent).join(d).strip()

#
# Enumeration may take arguments. This creates the argument part of the
# define. For example "(a,b,c)".
#
def createDefineArgs(ranges):
    if ranges:
        args = range(len(ranges))
        args = [chr(ord("a") + x) for x in args]
        args = "(%s)" % ", ".join(args)
        return args
    else:
        return ""

#
# Given a dictionary of stuff, consolidate the keys assuming they are chip
# pass data. This eliminates the need to write each pass if all passes are the
# same. Consolidation does minor passes, major passes, models, families, and
# finally "CN" for everything.
#
def consolidateChips(by_chip, useArch=None):
    # Worker function to check that all "keys" are in "dict" and the same. If
    # they are, remove the keys and replace them with a single item "new_key".
    def check_all_same(keys, dict, new_key):
        ref = None
        ref_str = None
        for key in keys:
            if not key in by_chip:
                return False
            s = str(dict[key])
            if ref_str == None:
                ref = dict[key]
                ref_str = s
            elif s != ref_str:
                return False
        for key in keys:
            del dict[key]
        dict[new_key] = ref
        return True
    # If an architecture was supplied, all chips for said architecture must be
    # present for consolidation. Otherwise we just require the ones passed.
    if useArch:
        chips = []
        for chip in chip_list.getChips():
            if csr_utils.isChipArch(useArch, chip):
                chips.append(chip)
    else:
        chips = by_chip.keys()
    # Create a multi-level dictionary describing all the families, models,
    # major passes, and minor passes in use
    used_chips = {}
    for chip in chips:
        family, model, chip_pass = chip_list.getChipNameParts(chip)
        major = "%s_P%d" % (model, int(chip_pass))
        if not family in used_chips:
            used_chips[family] = {}
        if not model in used_chips[family]:
            used_chips[family][model] = {}
        if not major in used_chips[family][model]:
            used_chips[family][model][major] = []
        used_chips[family][model][major].append(chip)
    # Search for and consolidate duplicates
    family_all_same = True
    for family in used_chips:
        model_all_same = True
        for model in used_chips[family]:
            major_all_same = True
            for major in used_chips[family][model]:
                minor_all_same = check_all_same(used_chips[family][model][major], by_chip, major)
                major_all_same &= minor_all_same
            if major_all_same:
                major_all_same = check_all_same(used_chips[family][model].keys(), by_chip, model)
                model_all_same &= major_all_same
        if model_all_same:
            model_all_same = check_all_same(used_chips[family].keys(), by_chip, family)
            family_all_same &= model_all_same
    if family_all_same:
        check_all_same(used_chips.keys(), by_chip, "CN")

#
# Write a single Enumeration out to a header
#
def writeEnum(out, arch, enum):
    out.write("\n")
    out.write("/**\n")
    out.write(" * Enumeration %s\n" % enum["name"])
    description = getAnyField(enum, "description", arch)
    if description:
        out.write(" *\n")
        description = description.replace("<", "\<")
        description = description.replace(">", "\>")
        description = textwrap.dedent(description)
        description = textwrap.fill(description, 70)
        for l in description.split("\n"):
            l = l.rstrip();
            if l:
                out.write(" * %s\n" % l)
            else:
                out.write(" *\n")
    out.write(" */\n")
    keys = enum["values"].keys()
    keys.sort()
    for n in keys:
        enumValue = enum["values"][n]
        # Build output lines for all chips of this value
        enum_lines = {}
        for chip in enumValue["value"]:
            is_this_arch = csr_utils.isChipArch(arch, chip)
            if not is_this_arch:
                continue
            # Name is PREFIX+<enum_name>+_+<enum_value>
            full_name = "%s%s_%s" % (PREFIX, enum["name"].upper(), n)
            full_name = full_name.replace("#", "X")
            # Range info is used for arguments and comments
            r = enumValue["ranges"][chip]
            args = createDefineArgs(r)
            eq = csr_utils.addressToString(enumValue["value"][chip], None, addSuffix=True)
            if enumValue["bar_size"]:
                sz = "0x%xull" % (1 << enumValue["bar_size"][chip])
            else:
                sz = None
            #descr = formatDescription(enumValue["description"][chip], 40)
            if (len(full_name) + len(args) + len(eq) > 70):
                output = "%s\t\\\n\t(%s)" % (args, eq)
            else:
                output = "%s (%s)" % (args, eq)
            enum_lines[chip] = full_name, output, sz
        # Consolidate all chips
        if enum_lines:
            consolidateChips(enum_lines)
        # Print lines after consolidation
        for chip in csr_data.iterChipOrder(enum_lines):
            e = enum_lines[chip]
            if chip == "CN":
                out.write("#define %s%s\n" % (e[0], e[1]))
            else:
                out.write("#define %s_%s%s\n" % (e[0], chip, e[1]))
            if e[2]:
                # Print BAR sizes
                if chip == "CN":
                    out.write("#define %s_SIZE %s\n" % (e[0], e[2]))
                else:
                    out.write("#define %s_%s_SIZE %s\n" % (e[0], chip, e[2]))

#
# Build a string representing all the fields in a structure or register. The
# string is everything that should be inside the structure, including endian
# defines, bit members, and comments.
#
def buildStructMembers(chip, struct):
    # Write a single field
    def writeField(out, field):
        bit_width = field["bits"][chip][1] - field["bits"][chip][0] + 1
        line = ("\t\t" + c_type + " " + field["name"]).ljust(38) + " : " + str(bit_width) + ";"
        access = field.get("access", None)
        if access:
            access = "(%s)" % access[chip]
        else:
            access = ""
        line += "\n";
        out.write(line)
    fields = struct["fields"]
    out = StringIO.StringIO()
    total_size = csr_utils.getSizeBits(struct, multipleOf=32)
    if total_size % 64 == 0:
        c_type = "u64"
        word_size = 64
    else:
        c_type = "u32"
        word_size = 32
    num_words = total_size / word_size
    for word in range(num_words):
        # Create a list of all fields in this word
        min_bit = word * word_size
        max_bit = min_bit + word_size - 1
        word_fields = {}
        for name in fields:
            # Skip fields not in this chip
            if not chip in fields[name]["bits"]:
                continue
            # Add fields in this word to the word's field list
            bits = fields[name]["bits"][chip]
            if (bits[0] >= min_bit) and (bits[0] <= max_bit):
                if (bits[1] < min_bit) or (bits[1] > max_bit):
                    csr_utils.raiseException(fields[name], "Struct: Field spans a word")
                word_fields[bits[0]] = fields[name]
        # Sort the fields into big endian order
        bits = word_fields.keys()
        bits.sort()
        # Write the bits in little endian order
        for bit in bits:
            writeField(out, word_fields[bit])
    result = out.getvalue()
    out.close()
    return result

#
# Write a single Structure out to a header
#
def writeStruct(out, arch, struct, title="Structure"):
    out.write("\n")
    out.write("/**\n")
    out.write(" * %s %s\n" % (title, struct["name"]))
    description = getAnyField(struct, "description", arch)
    if description:
        out.write(" *\n")
        description = description.replace("<", "\<")
        description = description.replace(">", "\>")
        description = textwrap.dedent(description)
        description = textwrap.fill(description, 70)
        for l in description.split("\n"):
            l = l.rstrip();
            if l:
                out.write(" * %s\n" % l)
            else:
                out.write(" *\n")
    out.write(" */\n")
    struct_name = (PREFIX + struct["name"]).replace("#", "X").lower()
    out.write("union %s {\n" % struct_name)
    width = csr_utils.getSizeBits(struct, multipleOf=32)
    if width % 64 == 0:
        if width > 64:
            out.write("\tu64 u[%d];\n" % (width / 64))
        else:
            out.write("\tu64 u;\n")
    else:
        if width % 32 != 0:
            csr_utils.raiseException(struct, "Struct: Size expected to be a multiple of 32")
        if width > 32:
            out.write("\tu32 u[%d];\n" % (width / 32))
        else:
            out.write("\tu32 u;\n")
    # Create a dictionary of all per chip structures
    struct_items = {}
    for chip in struct["description"]:
        is_this_arch = csr_utils.isChipArch(arch, chip)
        if not is_this_arch:
            continue
        struct_items[chip] = buildStructMembers(chip, struct)
    # Consolidate all chips
    consolidateChips(struct_items)
    # Start writing structures with subset first
    written_structs = {}
    out.write("\tstruct %s_s {\n" % struct_name)
    subset = csr_utils.createSubset(arch, "s", struct)
    struct_chip = buildStructMembers("s", subset)
    written_structs[struct_chip] = struct_name + "_s"
    out.write(struct_chip)
    out.write("\t} s;\n")
    for chip in csr_data.iterChipOrder(struct_items):
        struct_chip = struct_items[chip]
        chip_member = chip_list.chipToStructName(chip)
        if struct_chip in written_structs:
            # Chip duplicates one we have already written
            out.write("\t/* struct %s %s; */\n" % (written_structs[struct_chip], chip_member))
        else:
            # New structure
            name = "%s_%s" % (struct_name, chip_member)
            written_structs[struct_chip] = name
            out.write("\tstruct %s {\n" % name)
            out.write(struct_chip)
            out.write("\t} %s;\n" % chip_member)
    out.write("};\n")

#
# Write a single Register out to a header
#
def writeReg(out, arch, reg):
    use_bar_offset = getAnyField(reg, "bar_size", arch)
    # Reuse the structure writer to write the register
    writeStruct(out, arch, reg, title="Register (%s)" % getAnyField(reg, "bus", arch))
    out.write("\n")
    # Get common stuff need for register code
    base_name = reg["name"].replace("#", "X").upper()
    typedef_base = (PREFIX + base_name).lower()
    macro_name = typedef_base.upper()
    if use_bar_offset:
        reg_range = getAnyField(reg, "bar_ranges", arch)
        address_data = reg["bar_offset"]
        address_range = reg["bar_ranges"]
    else:
        reg_range = getAnyField(reg, "ranges", arch)
        address_data = reg["address"]
        address_range = reg["ranges"]
    # Function to return address
    prototype = "static inline u64 %s" % macro_name
    if reg_range:
        params_paren = "(u64 a"
        for p in range(1, len(reg_range)):
            params_paren += ", u64 %s" % chr(ord('a') + p)
        prototype += params_paren + ")"
    else:
        prototype += "(void)"
    out.write("%s\n\t__attribute__ ((pure, always_inline));\n" % prototype)
    out.write("%s\n" % prototype)
    out.write("{\n")
    address_items = {}
    for chip in csr_data.iterChipOrder(address_data):
        if address_data[chip] == None:
            continue
        is_this_arch = csr_utils.isChipArch(arch, chip)
        if not is_this_arch:
            continue
        # Build the model check boolean logic. This doesn't have the parameter
        # checks normally in the BDK
        # Save the check and the equation. Both must be the same for
        # conssolidation
        address_items[chip] = None, csr_utils.addressToString(address_data[chip], address_range[chip], addSuffix=True, useMasks=False)
    consolidateChips(address_items)
    # Build the call for fatal failures if the CSR was accessed with the
    # incorrect parameter or on the wrong chip
    num_args = len(reg_range)
    fatal_line = "\treturn -1;\n"
    # Check if all chips are the same
    if "CN" in address_items:
        # All chips are same, simplify the address function to a single return
        assert len(address_items) == 1, address_items
        if address_items["CN"][0] == None: # No param check
            out.write("\treturn %s;\n" % address_items["CN"][1])
        else: # Need param check
            out.write("\tif (%s)\n" % address_items["CN"][0])
            out.write("\t\treturn %s;\n" % address_items["CN"][1])
            out.write(fatal_line)
    else: # Need model checks
        for chip in csr_data.iterChipOrder(address_items):
            chip_name = chip_list.chipToModelDefine(chip)
            if address_items[chip][0] == None: # No param check
                out.write("\tif (CAVIUM_IS_MODEL(%s))\n" % chip_name)
            else: # Need param check
                out.write("\tif (CAVIUM_IS_MODEL(%s) && (%s))\n" % (chip_name, address_items[chip][0]))
            out.write("\t\treturn %s;\n" % address_items[chip][1])
        out.write(fatal_line)
    out.write("}\n")

#
# Get a list of all possible blocks
#
def getBlockList(arch, enums, structs, regs):
    blocks = {}
    for data in enums, structs, regs:
        for n  in data:
            if not csr_utils.isArch(arch, data[n]):
                continue
            block = data[n]["block"]
            if not block in blocks:
                blocks[block] = {}
    block_list = blocks.keys()
    block_list.sort()
    return block_list

#
# Write the Copyright banner
#
def writeCopyrightBanner(out):
    year = datetime.date.today().year
    out.write("/***********************license start***********************************\n")
    out.write("* Copyright (C) %d Marvell International Ltd.\n" % year)
    out.write("* SPDX-License-Identifier: BSD-3-Clause\n")
    out.write("* https://spdx.org/licenses\n")
    out.write("***********************license end**************************************/\n")
    out.write("\n")

#
# Write the normal C header file banners and such
#
def writeBanner(out, block=None):
    if block:
        define_name = "__%sCSRS_%s_H__" % (PREFIX, block)
    else:
        define_name = "__%sCSRS_H__" % PREFIX
    out.write("#ifndef %s\n" % define_name)
    out.write("#define %s\n" % define_name)
    out.write("/* This file is auto-generated.  Do not edit */\n")
    out.write("\n")
    writeCopyrightBanner(out)
    out.write("/**\n")
    out.write(" * @file\n")
    out.write(" *\n")
    out.write(" * Configuration and status register (CSR) address and type definitions for\n")
    out.write(" * Cavium %s.\n" % block)
    out.write(" *\n")
    out.write(" * This file is auto generated.  Do not edit.\n")
    out.write(" *\n")
    out.write(" */\n")

#
# Write the normal C header file footer
#
def writeFooter(out, block=None):
    if block:
        define_name = "__%sCSRS_%s_H__" % (PREFIX, block)
    else:
        define_name = "__%sCSRS_H__" % PREFIX
    out.write("\n")
    out.write("#endif /* %s */\n" % define_name)
    out.close()

#
# Write all enumarations for a given block
#
def writeEnums(out, arch, block, enums):
    names = enums.keys()
    names.sort()
    for name in names:
        if block == enums[name]["block"] and csr_utils.isArch(arch, enums[name]):
            writeEnum(out, arch, enums[name])

#
# Write all structures for a given block
#
def writeStructs(out, arch, block, structs):
    names = structs.keys()
    names.sort()
    for name in names:
        if block == structs[name]["block"] and csr_utils.isArch(arch, structs[name]):
            writeStruct(out, arch, structs[name])

#
# Write all registers for a given block
#
def writeRegs(out, arch, block, regs):
    names = regs.keys()
    names.sort()
    for name in names:
        if block == regs[name]["block"] and csr_utils.isArch(arch, regs[name]):
            writeReg(out, arch, regs[name])

#
# Create C header for a single block
#
def writeBlock(arch, block, enums, structs, regs):
    filename = "output/%s/%s-%s.h" % (arch, FILE_PREFIX, block.lower())
    out = open(filename, "w")
    writeBanner(out, block)
    writeEnums(out, arch, block, enums)
    writeStructs(out, arch, block, structs)
    writeRegs(out, arch, block, regs)
    writeFooter(out, block)
    out.close()

#
# Create C header including all block headers
#
def writeMain(arch, blocks):
    filename = "output/%s/%s.h" % (arch, FILE_PREFIX)
    out = open(filename, "w")
    writeBanner(out)
    out.write("\n")
    out.write("/* Include all CSR files for easy access */\n")
    for block in blocks:
        out.write("#include \"%s-%s.h\"\n" % (FILE_PREFIX, block.lower()))
    writeFooter(out)
    out.close()

#
# Create all C headers
#
def process(enums, structs, regs):
    for arch in ["octeon", "thunder", "octeontx"]:
        blocks = getBlockList(arch, enums, structs, regs)
        for block in blocks:
            writeBlock(arch, block, enums, structs, regs)
        #writeMain(arch, blocks)

