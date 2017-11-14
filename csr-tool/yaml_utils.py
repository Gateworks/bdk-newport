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
import pprint

#
# Signals an error to the user. It displays any yaml file and line
# information that is available. If the error is a specific yaml line,
# then the error with have the exact file and line. If it might be from
# multiple yaml files, the associated files and lines are displayed.
#
def raiseException(yaml, message):
    y = pprint.pformat(yaml, depth=2)
    f = yaml["__FILE__"]
    l = yaml["__LINE__"]
    c = yaml["__COLUMN__"]
    raise Exception("\n******\n%s\n***\n%s:%s:%s: %s\n******\n" % (y,f,l,c,message))

#
# Lookup the child element of a yaml node. Although meant for yaml,
# it works on and dictionary type of data. If the element can't be found,
# the function can optionally raise an exception with file and line
# location info
#
def getChild(yaml, name, allowMissing = False):
    if name in yaml:
        return yaml[name]
    if allowMissing:
        return None
    raiseException(yaml, "Missing field \"%s\" in YAML" % name)

#
# Make sure all child tags of a yaml node are listed in the valid tag list.
# If not an exception is raised. Note that tags beginning with "__" are
# ignored as these represent debug location information.
#
def checkChildren(yaml, valid_list):
    for k in yaml:
        if not k in valid_list:
            if k.startswith("__"):
                continue
            raiseException(yaml, "Unexpected YAML field \"%s\"" % k)


