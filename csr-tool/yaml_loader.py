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
import yaml
import pprint
from multiprocessing import Pool

#
# Read a single YAML file. Nodes are annotated with the file name and
# line number they are from
#
def read_file(filename):
    # Read the entire YAML file
    inf = open(filename, "r")
    raw = inf.read()
    inf.close()
    # Connect a yaml loader to the data
    loader = yaml.Loader(raw)
    # These are callback to attach the file position data
    def compose_node(parent, index):
        # the line number where the previous token has ended (plus empty lines)
        line = loader.line
        column = loader.column
        node = yaml.composer.Composer.compose_node(loader, parent, index)
        node.__file__ = filename
        node.__line__ = line + 1
        node.__column__ = column + 1
        return node
    def construct_mapping(node, deep=False):
        mapping = yaml.constructor.Constructor.construct_mapping(loader, node, deep=deep)
        mapping['__FILE__'] = node.__file__
        mapping['__LINE__'] = node.__line__
        mapping['__COLUMN__'] = node.__column__
        return mapping
    # These two lines hook into node creation to add __FILE__ and __LINE__ to
    # all nodes with children. It doesn't add to items that have a simple
    # value
    loader.compose_node = compose_node
    loader.construct_mapping = construct_mapping
    # The following line stops YAML from converting strings to numbers or
    # true/false
    loader.yaml_implicit_resolvers = {}
    # This does the actual parsing
    y = {}
    while loader.check_data():
        tmp = loader.get_data()
        assert "name" in tmp, "YAML missing blcok name"
        block_name = tmp["name"]
        y[block_name] = tmp
    return y

#
# Read all CSR files in a list of directories and create one large python
# dictionary
#
def read_files(files_list):
    results = Pool().map(read_file, files_list)
    assert len(files_list) == len(results)
    y = {}
    for i,n in enumerate(files_list):
        y[n] = results[i]
    # Write text for debug
    if False:
        print "Writing YAML as yaml-all-chips.txt for debug"
        out = open("yaml-all-chips.txt", "w")
        pp = pprint.PrettyPrinter(indent=4, width=132, stream=out)
        pp.pprint(y)
        out.close()
    return y

