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

import os
import sys

def read_functions(elf, func_list):
    file = os.popen("aarch64-thunderx-elf-readelf --wide -s %s | grep -v LOCAL | grep FUNC" % elf)
    for line in file:
        parts = line.split()
        func = parts[-1]
        if not func in func_list:
            func_list.append(func)
    file.close()
    return func_list

def filter(list, prefix):
    result = []
    for e in list:
        if e.startswith(prefix):
            result.append(e)
    return result

def write_function_table(out, table_name, functions):
    out.write("\n")
    for f in functions:
        out.write("extern void %s() __attribute__((weak));\n" % f)
    out.write("\n")
    out.write("const bdk_functions_t %s[] = {\n" % table_name)
    for f in functions:
        out.write("    {\"%s\", %s},\n" % (f, f))
    out.write("    {0, 0}\n")
    out.write("};\n")
    out.write("\n")



all_funcs = []
for elf in sys.argv[2:]:
    read_functions(elf, all_funcs)

bdk_funcs = filter(all_funcs, "bdk_")
bdk_funcs.sort()

out = open(sys.argv[1], "w")
out.write("/**\n");
out.write(" * DO NOT EDIT\n")
out.write(" * This is a mechanically generated file. All changes made here will be lost\n")
out.write(" * after the next file generation.\n")
out.write(" */\n\n")
out.write("#include \"bdk-functions.h\"\n")
write_function_table(out, "bdk_functions", bdk_funcs)
out.close()

