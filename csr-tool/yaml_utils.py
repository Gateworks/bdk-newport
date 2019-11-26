# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
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


