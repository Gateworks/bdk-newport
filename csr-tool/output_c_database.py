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
import csr_utils
import chip_list
from output_c_header import PREFIX
from output_c_header import FILE_PREFIX
from output_c_header import writeCopyrightBanner

#
# Given a dictionary, return its keys sorted by the values they point to. This
# assumes that all values are unique
#
def getKeysSorted(dict):
    swapped = {}
    for k in dict:
        swapped[dict[k]] = k
    keys = swapped.keys()
    keys.sort()
    result = []
    for k in keys:
        result.append(swapped[k])
    return result

#
# Store a string into a global table and return its index. The index
# is half the actual value, requiring string to be a even length. Odd
# length strings will have an added zero when written.
#
def getStringTable(str):
    global globalStringTable
    global globalStringTableLookup
    global globalStringTableLen
    str = str.upper()   # Force all strings to upper case
    if not str in globalStringTableLookup:
        for k in globalStringTable:
            if k.endswith(str):
                position = globalStringTable[k] + len(k) - len(str)
                if position & 1 == 0:
                    globalStringTableLookup[str] = position/2
                    return globalStringTableLookup[str]
        globalStringTable[str] = globalStringTableLen
        globalStringTableLookup[str] = globalStringTableLen/2
        globalStringTableLen += len(str) + 1
        if globalStringTableLen & 1 == 1:
            globalStringTableLen += 1
    return globalStringTableLookup[str]

#
# Store a number into a global table and return its index
#
def getNumberTable(n):
    global globalNumberTable
    global globalNumberTableLen
    if not n in globalNumberTable:
        globalNumberTable[n] = globalNumberTableLen
        globalNumberTableLen += 1
    return globalNumberTable[n]

#
# Store a CSR field into a global table and return its index
#
def getFieldTable(field, chip):
    global globalFieldTable
    global globalFieldTableLen
    name_index = getStringTable(field["name"])
    key = "{%d,%d,%d}" % (name_index, field["bits"][chip][0], field["bits"][chip][1])
    if not key in globalFieldTable:
        globalFieldTable[key] = globalFieldTableLen
        globalFieldTableLen += 1
    return globalFieldTable[key]

#
# Store a CSR field list into a global table and return its index
#
def getFieldListTable(reg, chip):
    global globalFieldListTable
    global globalFieldListTableLen
    field_list = {}
    for name in reg["fields"]:
        field = reg["fields"][name]
        if chip in field["bits"]:
            field_list[field["bits"][chip][0]] = field
    bit_list =field_list.keys()
    bit_list.sort()
    fieldList = "%d" % len(bit_list)
    for bit in bit_list:
        fieldList += ",%d" % getFieldTable(field_list[bit], chip)
    if not fieldList in globalFieldListTable:
        globalFieldListTable[fieldList] = globalFieldListTableLen
        globalFieldListTableLen += len(bit_list) + 1
    return globalFieldListTable[fieldList]

#
# Store a range into a global table and return its index
#
def getRangeTable(range_info):
    global globalRangeTable
    global globalRangeTableLen
    key = "%d" % (len(range_info) * 2)
    for r in range_info:
        key += ",%d,%d" % r
    if not key in globalRangeTable:
        globalRangeTable[key] = globalRangeTableLen
        globalRangeTableLen += len(range_info)*2 + 1
    return globalRangeTable[key]

#
# Store a CSR into a global table and return its index
#
def getCsrTable(csr_str):
    global globalCsrTable
    global globalCsrTableLen
    key = csr_str
    if not key in globalCsrTable:
        globalCsrTable[key] = globalCsrTableLen
        globalCsrTableLen += 1
    return globalCsrTable[key]

def writeDB(arch, regs):
    global globalStringTable
    global globalStringTableLookup
    global globalStringTableLen
    global globalNumberTable
    global globalNumberTableLen
    global globalFieldTable
    global globalFieldTableLen
    global globalFieldListTable
    global globalFieldListTableLen
    global globalRangeTable
    global globalRangeTableLen
    global globalCsrTable
    global globalCsrTableLen
    globalStringTable = {}
    globalStringTableLookup = {}
    globalStringTableLen = 0
    globalNumberTable = {}
    globalNumberTableLen = 0
    globalFieldTable = {}
    globalFieldTableLen = 0
    globalFieldListTable = {}
    globalFieldListTableLen = 0
    globalRangeTable = {}
    globalRangeTableLen = 0
    globalCsrTable = {}
    globalCsrTableLen = 0

    filename = "output/%s/%s.c" % (arch, FILE_PREFIX)
    out = open(filename, "w")
    writeCopyrightBanner(out)
    out.write('#include <bdk.h>\n')
    out.write("\n")
    empty_range = getRangeTable([(-1,-1)])

    #
    # Write the per chip CSR tables
    #
    null_csr = getCsrTable("{0, 0, 0, BDK_CSR_TYPE_NCB, 0, 0, {0,0,0,0}, {0,0,0,0}}")
    for chip in chip_list.getChips():
        if not csr_utils.isChipArch(arch, chip):
            continue
        # Skip minor passes as they are basically the same as the major pass
        if not chip.endswith("_0"):
            continue
        out.write("static const int16_t __bdk_csr_db_%s[] = {\n" % chip)
        names = regs.keys()
        names.sort()
        for name in names:
            reg = regs[name]
            if not chip in reg["description"]:
                continue
            range_len = len(reg["ranges"][chip])
            assert range_len <= 4, "Only support four params for now"
            range_list = [empty_range, empty_range, empty_range, empty_range]
            param_inc = [0, 0, 0, 0]
            for i in range(range_len):
                range_list[i] = getRangeTable(reg["ranges"][chip][i])
                param_inc[i] = getNumberTable(reg["address"][chip][i+1])
            csr_str = "{%5d, %4d, %d, BDK_CSR_TYPE_%s,%d,%3d,{%2d,%2d,%2d,%2d},{%2d,%2d,%2d,%2d}}" % (
                        getStringTable(name.replace("#", "X")), # Name index
                        getNumberTable(reg["address"][chip][0]), # Base index
                        0, # Unused
                        reg["bus"][chip], # Bus Type
                        csr_utils.getSizeBits(reg, 32) / 8, # Width in bytes
                        getFieldListTable(reg, chip), # Field index
                        range_list[0], range_list[1], range_list[2], range_list[3],
                        param_inc[0], param_inc[1], param_inc[2], param_inc[3])
            csr_index = getCsrTable(csr_str)
            out.write("    %d, /* %s */\n" % (csr_index, name))

        out.write("    %s\n" % null_csr)
        out.write("};\n\n")
    #
    # Write the global CSR table
    #
    out.write("const __bdk_csr_db_type_t __bdk_csr_db_csr[] = {\n")
    keys = getKeysSorted(globalCsrTable)
    for key in keys:
        out.write("    %s, /* %d */\n" % (key, globalCsrTable[key]))
    out.write("};\n\n")
    #
    # Write the CSR fieldList table
    #
    out.write("const uint16_t __bdk_csr_db_fieldList[] = {\n")
    keys = getKeysSorted(globalFieldListTable)
    for key in keys:
        out.write("    %s, /* %d */\n" % (key, globalFieldListTable[key]))
    out.write("};\n\n")
    #
    # Write the CSR field table
    #
    out.write("const __bdk_csr_db_field_t __bdk_csr_db_field[] = {\n")
    keys = getKeysSorted(globalFieldTable)
    for key in keys:
        out.write("    %s, /* %d */\n" % (key, globalFieldTable[key]))
    out.write("};\n\n")
    #
    # Write the CSR range table
    #
    out.write("const int __bdk_csr_db_range[] = {\n")
    keys = getKeysSorted(globalRangeTable)
    for key in keys:
        out.write("    %s, /* %d */\n" % (key, globalRangeTable[key]))
    out.write("};\n\n")
    #
    # Write the CSR string table
    #
    out.write("const char __bdk_csr_db_string[] = ")
    keys = getKeysSorted(globalStringTable)
    for key in keys:
        if len(key) &1 == 0:
            out.write("\n    \"%s\\0\\0\" /* %s/2 */" % (key, globalStringTable[key]))
        else:
            out.write("\n    \"%s\\0\" /* %s/2 */" % (key, globalStringTable[key]))
    out.write("\n    \"\";\n\n")
    #
    # Write the CSR number table
    #
    out.write("const uint64_t __bdk_csr_db_number[] = {\n")
    keys = getKeysSorted(globalNumberTable)
    for key in keys:
        out.write("    0x%016xull, /* %s */\n" % (key, globalNumberTable[key]))
    out.write("};\n\n")
    #
    # Write the chip id to CSR table map
    #
    if arch == "octeon":
        model_prefex = "OCTEON_"
    else:
        model_prefex = "CAVIUM_"
    out.write("const __bdk_csr_db_map_t __bdk_csr_db[] = {\n")
    for chip in chip_list.getChips():
        if not csr_utils.isChipArch(arch, chip):
            continue
        # Skip minor passes as they are basically the same as the major pass
        if not chip.endswith("_0"):
            continue
        # Change the model check to match any minor pass
        model_check = model_prefex + chip.replace("P", "_PASS")
        model_check = model_check[0:-2] + "_X"
        out.write("    {%s, __bdk_csr_db_%s},\n" % (model_check, chip))
    out.write("    {0, NULL}\n")
    out.write("};\n\n")
    out.close()

#
# Create C database
#
def process(enums, structs, regs):
    for arch in ["octeon", "thunder", "thunder2"]:
        writeDB(arch, regs)

