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

import sys
import os
import cPickle
import pprint
import chip_list
import yaml_loader
import enum_handler
import struct_handler
import reg_handler
import output_html
import output_c_header
import output_c_database

#
# Misc constants
#
PICKLE_FILE = "yaml.pickle"
pp = pprint.PrettyPrinter(indent=4, width=132)

#
# Main code start
#

# Create a list of all possible chips
print "Processing Chips:"
all_chips = chip_list.getChips()
for chip in all_chips:
    print "\t%s" % chip

# Load all the yaml
try:
    inf = open(PICKLE_FILE, "r")
    print "Loading %s" % PICKLE_FILE
    yaml_all = cPickle.load(inf)
    inf.close()
except:
    print "Reading YAML files"
    # Read YAML for all chips
    yaml_all = yaml_loader.read_files(chip_list.getYamlFiles())
    # Pickle it to disk for faster repeats
    print "Saving %s" % PICKLE_FILE
    out = open(PICKLE_FILE, "w")
    cPickle.dump(yaml_all, out)
    out.close()

# Process the different parts of the yaml
print "Processing Enums"
enums = enum_handler.process(yaml_all)
#pp.pprint(enums)
print "Processing Structs"
structs = struct_handler.process(yaml_all)
#pp.pprint(structs)
print "Processing Registers"
regs = reg_handler.process(yaml_all, enums)
#pp.pprint(regs)

# Generate the output files
print "Writing HTML"
output_html.process(enums, structs, regs)
print "Writing C headers"
output_c_header.process(enums, structs, regs)
print "Writing C databases"
output_c_database.process(enums, structs, regs)

