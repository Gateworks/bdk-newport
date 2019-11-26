#!/usr/bin/env python2
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
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
import output_c_header_uboot
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
print "Writing C headers for Uboot"
output_c_header_uboot.process(enums, structs, regs)
print "Writing C databases"
output_c_database.process(enums, structs, regs)

