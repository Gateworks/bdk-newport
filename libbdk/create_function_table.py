#!/usr/bin/env python2
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import os
import sys

def read_functions(elf, func_list):
    file = os.popen("${BDK_GCC_PREFIX}-readelf --wide -s %s | grep -v LOCAL | grep FUNC" % elf)
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

