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
import datetime
import StringIO
import csr_utils
import chip_list

# All generated identifiers will have this prefix. The case
# will be changed to lowercase for types
PREFIX = "BDK_"
FILE_PREFIX = "bdk-csrs"

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
        args = "(%s)" % ",".join(args)
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
        major = "%sP%d" % (model, int(chip_pass))
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
            if not csr_utils.isChipArch(arch, chip):
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
            output = "%s (%s)" % (args, eq)
            enum_lines[chip] = full_name, output, sz
        # Consolidate all chips
        if enum_lines:
            consolidateChips(enum_lines)
        # Print lines after consolidation
        for chip in enum_lines:
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
        line = ("        " + c_type + " " + field["name"]).ljust(38) + " : " + str(bit_width) + ";"
        description = formatDescription(field["description"].get(chip, ""), 66)
        access = field.get("access", None)
        if access:
            access = "(%s)" % access[chip]
        else:
            access = ""
        if not csr_utils.isReserved(field["name"]):
            description = description.replace("<", "\<")
            description = description.replace(">", "\>")
            l = line.ljust(45) + "/**< [%3d:%3d]%s %s */" % (field["bits"][chip][1], field["bits"][chip][0], access, description)
            line = ""
            for l in l.split("\n"):
                line += l.rstrip() + "\n";
        else:
            line += "\n";
        out.write(line)
    fields = struct["fields"]
    out = StringIO.StringIO()
    total_size = csr_utils.getSizeBits(struct, multipleOf=32)
    if total_size % 64 == 0:
        c_type = "uint64_t"
        word_size = 64
    else:
        c_type = "uint32_t"
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
        bits.reverse()
        out.write("#if __BYTE_ORDER == __BIG_ENDIAN /* Word %d - Big Endian */\n" % word)
        for bit in bits:
            writeField(out, word_fields[bit])
        # Write the bits in big endian order
        out.write("#else /* Word %d - Little Endian */\n" % word)
        # Write the bits in little endian order
        bits.reverse()
        for bit in bits:
            writeField(out, word_fields[bit])
        out.write("#endif /* Word %d - End */\n" % word)
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
        for l in description.split("\n"):
            l = l.rstrip();
            if l:
                out.write(" * %s\n" % l)
            else:
                out.write(" *\n")
    out.write(" */\n")
    struct_name = (PREFIX + struct["name"]).replace("#", "X").lower()
    out.write("union %s\n" % struct_name)
    out.write("{\n")
    width = csr_utils.getSizeBits(struct, multipleOf=32)
    if width % 64 == 0:
        if width > 64:
            out.write("    uint64_t u[%d];\n" % (width / 64))
        else:
            out.write("    uint64_t u;\n")
    else:
        if width % 32 != 0:
            csr_utils.raiseException(struct, "Struct: Size expected to be a multiple of 32")
        if width > 32:
            out.write("    uint32_t u[%d];\n" % (width / 32))
        else:
            out.write("    uint32_t u;\n")
    # Create a dictionary of all per chip structures
    struct_items = {}
    for chip in struct["description"]:
        if not csr_utils.isChipArch(arch, chip):
            continue
        struct_items[chip] = buildStructMembers(chip, struct)
    # Consolidate all chips
    consolidateChips(struct_items)
    # Start writing structures with subset first
    written_structs = {}
    out.write("    struct %s_s\n" % struct_name)
    out.write("    {\n")
    subset = csr_utils.createSubset(arch, struct)
    struct_chip = buildStructMembers("s", subset)
    written_structs[struct_chip] = struct_name + "_s"
    out.write(struct_chip)
    out.write("    } s;\n")
    for chip in struct_items:
        struct_chip = struct_items[chip]
        if struct_chip in written_structs:
            # Chip duplicates one we have already written
            out.write("    /* struct %s %s; */\n" % (written_structs[struct_chip], chip.lower()))
        else:
            # New structure
            name = "%s_%s" % (struct_name, chip.lower())
            written_structs[struct_chip] = name
            out.write("    struct %s\n" % name)
            out.write("    {\n")
            out.write(struct_chip)
            out.write("    } %s;\n" % chip.lower())
    out.write("};\n")
    if title.startswith("Reg"):
        out.write("typedef union %s %s_t;\n" % (struct_name, struct_name))

#
# Write a single Register out to a header
#
def writeReg(out, arch, reg):
    # Reuse the structure writer to write the register
    writeStruct(out, arch, reg, title="Register (%s)" % getAnyField(reg, "bus", arch))
    out.write("\n")
    # Get common stuff need for register code
    base_name = reg["name"].replace("#", "X").upper()
    typedef_base = (PREFIX + base_name).lower()
    macro_name = typedef_base.upper()
    reg_range = getAnyField(reg, "ranges", arch)
    # Function to return address
    prototype = "static inline uint64_t %s" % macro_name
    if reg_range:
        params_paren = "(unsigned long a"
        for p in range(1, len(reg_range)):
            params_paren += ", unsigned long %s" % chr(ord('a') + p)
        prototype += params_paren + ")"
    else:
        prototype += "_FUNC(void)"
        out.write("#define %s %s_FUNC()\n" % (macro_name, macro_name))
    out.write("%s __attribute__ ((pure, always_inline));\n" % prototype)
    out.write("%s\n" % prototype)
    out.write("{\n")
    address_items = {}
    for chip in reg["address"]:
        if not csr_utils.isChipArch(arch, chip):
            continue
        # Build the parameter check boolean logic
        check_all = []
        for i,r in enumerate(reg["ranges"][chip]):
            param = chr(ord('a') + i)
            check_param = []
            for pair in r:
                if pair[0] == pair[1]:
                    check = "%s==%d" % (param, pair[0])
                elif pair[0] == 0:
                    check = "%s<=%d" % (param, pair[1])
                else:
                    check = "(%s>=%d)&&(%s<=%d)" % (param, pair[0], param, pair[1])
                check_param.append(check)
            if len(check_param) > 1:
                check = "(%s)" % (") || (".join(check_param))
            else:
                check = check_param[0]
            check_all.append(check)
        if len(check_all) > 1:
            check = "(%s)" % (") && (".join(check_all))
        elif len(check_all) == 1:
            check = check_all[0]
        else:
            check = None
        # Save the check and the equation. Both must be the same for
        # conssolidation
        address_items[chip] = check, csr_utils.addressToString(reg["address"][chip], reg["ranges"][chip], addSuffix=True)
    consolidateChips(address_items, useArch=arch)
    # Build the call for fatal failures if the CSR was accessed with the
    # incorrect parameter or on the wrong chip
    num_args = len(reg_range)
    fatal_line = "    __bdk_csr_fatal(\"%s\", %d" % (base_name, num_args)
    for i in range(4):
        if i < num_args:
            fatal_line += ", %s" % chr(ord('a') + i)
        else:
            fatal_line += ", 0"
    fatal_line += ");\n"
    # Check if all chips are the same
    chips = address_items.keys()
    if "CN" in chips:
        # All chips are same, simplify the address function to a single return
        assert len(chips) == 1, chips
        if address_items["CN"][0] == None: # No param check
            out.write("    return %s;\n" % address_items["CN"][1])
        else: # Need param check
            out.write("    if (%s)\n" % address_items["CN"][0])
            out.write("        return %s;\n" % address_items["CN"][1])
            out.write(fatal_line)
    else: # Need model checks
        chips.sort()
        for chip in chips:
            if "_" in chip: # A specific major and minor
                chip_name = "CAVIUM_" + chip.replace("P", "_PASS")
            elif "P" in chip: # A specific major, any minor
                chip_name = "CAVIUM_" + chip.replace("P", "_PASS") + "_X"
            elif not "X" in chip: # An entire family (CN9, CN8, CN7)
                assert len(chip) == 3, chip
                chip_name = "CAVIUM_" + chip +"XXX"
            else: # A model, and pass
                chip_name = "CAVIUM_" + chip
            if address_items[chip][0] == None: # No param check
                out.write("    if (CAVIUM_IS_MODEL(%s))\n" % chip_name)
            else: # Need param check
                out.write("    if (CAVIUM_IS_MODEL(%s) && (%s))\n" % (chip_name, address_items[chip][0]))
            out.write("        return %s;\n" % address_items[chip][1])
        out.write(fatal_line)
    out.write("}\n")
    out.write("\n")
    # Macros to support CSR modify macros
    macro_args = createDefineArgs(reg_range)
    macro = macro_name + macro_args
    out.write("#define typedef_%s %s_t\n" % (macro, typedef_base))
    out.write("#define bustype_%s %sCSR_TYPE_%s\n" % (macro, PREFIX, getAnyField(reg, "bus", arch)))
    out.write("#define basename_%s \"%s\"\n" % (macro, base_name))
    if reg["bar"]:
        bar = getAnyField(reg, "bar", arch)
        if bar == None:
            pass
        elif bar.endswith("BAR0"):
            bar_index = 0;
        elif bar.endswith("BAR2"):
            bar_index = 2;
        elif bar.endswith("BAR4"):
            bar_index = 4;
        else:
            assert False, "Invalid bar register %s for %s" % (bar, reg["name"])
        if bar != None:
            out.write("#define device_bar_%s 0x%x /* %s */\n" % (macro, bar_index, bar))
    if macro_args:
        params_paren = "(a)"
        for p in range(1, len(reg_range)):
            params_paren += ",(%s)" % chr(ord('a') + p)
        # params_paren must always have 4 arguments
        for p in range(len(reg_range), 4):
            params_paren += ",-1"
        out.write("#define busnum_%s (a)\n" % (macro))
        out.write("#define arguments_%s %s\n" % (macro, params_paren))
    else:
        out.write("#define busnum_%s 0\n" % macro)
        out.write("#define arguments_%s -1,-1,-1,-1\n" % macro)

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
    out.write("/***********************license start***************\n")
    out.write(" * Copyright (c) 2003-%d  Cavium Inc. (support@cavium.com). All rights\n" % year)
    out.write(" * reserved.\n")
    out.write(" *\n")
    out.write(" *\n")
    out.write(" * Redistribution and use in source and binary forms, with or without\n")
    out.write(" * modification, are permitted provided that the following conditions are\n")
    out.write(" * met:\n")
    out.write(" *\n")
    out.write(" *   * Redistributions of source code must retain the above copyright\n")
    out.write(" *     notice, this list of conditions and the following disclaimer.\n")
    out.write(" *\n")
    out.write(" *   * Redistributions in binary form must reproduce the above\n")
    out.write(" *     copyright notice, this list of conditions and the following\n")
    out.write(" *     disclaimer in the documentation and/or other materials provided\n")
    out.write(" *     with the distribution.\n")
    out.write("\n")
    out.write(" *   * Neither the name of Cavium Inc. nor the names of\n")
    out.write(" *     its contributors may be used to endorse or promote products\n")
    out.write(" *     derived from this software without specific prior written\n")
    out.write(" *     permission.\n")
    out.write("\n")
    out.write(" * This Software, including technical data, may be subject to U.S. export  control\n")
    out.write(" * laws, including the U.S. Export Administration Act and its  associated\n")
    out.write(" * regulations, and may be subject to export or import  regulations in other\n")
    out.write(" * countries.\n")
    out.write("\n")
    out.write(" * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED \"AS IS\"\n")
    out.write(" * AND WITH ALL FAULTS AND CAVIUM  NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR\n")
    out.write(" * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO\n")
    out.write(" * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR\n")
    out.write(" * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM\n")
    out.write(" * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,\n")
    out.write(" * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF\n")
    out.write(" * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR\n")
    out.write(" * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR\n")
    out.write(" * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.\n")
    out.write(" ***********************license end**************************************/\n")
    out.write("\n")
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
    out.write("/* This file is auto-generated. Do not edit */\n")
    out.write("\n")
    writeCopyrightBanner(out)
    out.write("/**\n")
    out.write(" * @file\n")
    out.write(" *\n")
    out.write(" * Configuration and status register (CSR) address and type definitions for\n")
    out.write(" * Cavium %s.\n" % block)
    out.write(" *\n")
    out.write(" * This file is auto generated. Do not edit.\n")
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
    out.write("extern void __bdk_csr_fatal(const char *name, int num_args, unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4) __attribute__ ((noreturn));\n")
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
    for arch in ["octeon", "thunder", "thunder2"]:
        blocks = getBlockList(arch, enums, structs, regs)
        for block in blocks:
            writeBlock(arch, block, enums, structs, regs)
        #writeMain(arch, blocks)

