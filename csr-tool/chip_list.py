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
import re

#
# The following list defines all chips processed by this script. Each entry
# is a chip name, chip pass, and a yaml file
#
CAVIUM_CHIPS = [
    # Chip name, chip pass, yaml file
    ["CN70XX",  1.0, "yaml/o70_pass_1.0.yaml"],
    ["CN73XX",  1.0, "yaml/o73_pass_1.0.yaml"],
    ["CNF75XX", 1.0, "yaml/o75_pass_1.0.yaml"],
    ["CN78XX",  1.0, "yaml/o78_pass_1.0.yaml"],
    ["CN78XX",  2.0, "yaml/o78_pass_2.0.yaml"],
    ["CN81XX",  1.0, "yaml/t81_pass_1.0.yaml"],
    ["CN83XX",  1.0, "yaml/t83_pass_1.0.yaml"],
    ["CN88XX",  1.0, "yaml/t88_pass_1.0.yaml"],
    ["CN88XX",  1.1, "yaml/t88_pass_1.1.yaml"],
    ["CN88XX",  2.0, "yaml/t88_pass_2.0.yaml"],
    ["CN93XX",  1.0, "yaml/t93_pass_1.0.yaml"],
]

#
# Additional diffs to show in HTML output above the usual
# chip pass differences
#
DIFFS = [
    ("CN70XXP1_0", "CN78XXP1_0"),
    ("CN78XXP1_0", "CN73XXP1_0"),
    ("CN73XXP1_0", "CNF75XXP1_0"),
    ("CNF75XXP1_0", "CN78XXP2_0"),
    ("CN78XXP1_0", "CN88XXP1_0"),
    ("CN88XXP2_0", "CN81XXP1_0"),
    ("CN88XXP2_0", "CN83XXP1_0"),
    ("CN81XXP1_0", "CN83XXP1_0"),
    ("CN83XXP1_0", "CN93XXP1_0"),
]

#
# This is a list of the possible register bus types
#
VALID_BUSSES = [
    "BPHY_RSL",         # RSL registers for Fusion
    "DAB",              # ARM debug port
    "DAB32b",           # ARM debug port 32bit
    "MDSB",             # t98: ?
    "NCB",              # Non coherent bus - Fast CSR
    "NCB32b",           # Non coherent bus 32bit - Fast CSR
    "PCCBR",            # PCIe bridge register
    "PCCPF",            # PCIe physical function
    "PCCVF",            # PCIe virtual function
    "PCICONFIGEP",      # PCIe config space in EP mode
    "PCICONFIGEP_SHADOW", # PCIe config space in EP mode, shadow regsiter? (Added for t93)
    "PCICONFIGEPVF",    # PCIe config space in EP mode, virtual function (Added for t93)
    "PCICONFIGRC",      # PCIe config space in RC mode
    "PEXP",             # PCIe BAR 0 address only
    "PEXP_NCB",         # NCB-direct and PCIe BAR0 address
    "PEXPV_NCB",        # Virtual NCB-direct and PCIe BAR0 address
    "RSL",              # Slow CSR
    "RSL32b",           # Slow CSR, 32bit
    "RVU_PF_BAR0",      # Offset into a RVU Physical function BAR (Added for t93)
    "RVU_PF_BAR2",      # Offset into a RVU Physical function BAR (Added for t93)
    "RVU_PFVF_BAR2",    # Offset into a RVU PF or VF BAR (Added for t93)
    "RVU_VF_BAR2",      # Offset into a RVU VF BAR (Added for t93)
    "SRIOMAINT",        # SRIO registers
    "SYSREG",           # ARM64 core system registers
]

#
# This is a list of the possible register field access types
#
VALID_ACCESS = [
    "RAZ",     # Read as zero
    "R/W",     # Read / Write
    "R/W1C",   # Read, write ones to clear
    "R/W1S",   # Read, write ones to set
    "R/W0C",   # Read, write zeros to clear
    "RO",      # Read only
    "RC/W",    # Read to clear, write
    "RC",      # Read clear
    "WO",      # Write only
    "R/W1",    # Read, write one
    "SR/W",    # Secure Read / Write
    "SR/W1C",  # Secure Read, write ones to clear
    "SR/W1S",  # Secure Read, write ones to set
    "SRO",     # Secure Read only
    "SWO",     # Secure Write only
    "WR0",     # Write, read zero
    "RO/WRSL", # Read only, cna be written through RSL
    "WORSL",   # Write through RSL
]

#
# Maximum pass ranges. Passes are encoded using 5 bits
# Bits[4:3] = Major pass, add one for display
# Bits[2:0] = Minor pass, starts at zero
#
MAX_MAJOR_PASS = 4 # Allow 1-4
MAX_MINOR_PASS = 7 # Allow 0-7
MAX_PASS = MAX_MAJOR_PASS + MAX_MINOR_PASS / 10.0 # As a float

#
# Return a list of all chips
#
def getChips():
    return _chips

#
# Return a list of all yaml files
#
def getYamlFiles():
    files = []
    for chip in CAVIUM_CHIPS:
        files.append(chip[2])
    return files

#
# Given a chip name, return the yaml file it used
#
def getYamlFile(chip):
    chip_family, chip_model, chip_pass = getChipNameParts(chip)
    for c in CAVIUM_CHIPS:
        if (chip_model == c[0]) and (chip_pass == c[1]):
            return c[2]
    raise Exception("Unable to find yaml file for \"%s\"" % chip)

#
# Given a chip, return a tuple containing the family, model, and pass
# Family is "CN7", "CNF7", "CN8"
# Model is "CN73XX", "CNF75XX", "CN88XX", etc
# Pass is a float between 1.0 and 4.7
#
def getChipNameParts(chip):
    return _chipNameParts[chip]

#
# Internal functions, don't call
#

# Create the list of all possible chips
def _fillChips():
    all_chips = []
    for chip in CAVIUM_CHIPS:
        chip_name = chip[0]
        chip_pass = chip[1]
        fullname = "%sP%.1f" % (chip_name, chip_pass)
        fullname = fullname.replace(".", "_")
        all_chips.append(fullname)
    all_chips.sort()
    return all_chips

# Create a dictionary mapping chips to their (family, model, pass) tuple
def _fillChipNameParts():
    result = {}
    for chip in getChips():
        match = re.match("^(CNF?[0-9])([0-9]XX)P([0-9]_[0-9])$", chip)
        if not match:
            raise Exception("Illegal chip name format \"%s\"" % chip)
        family = match.group(1)
        # Special case, change CNF (fusion) to CN so we treat fusion the
        # same as other chips for that architecture
        if family.startswith("CNF"):
            family = "CN" + family[3:]
        model = match.group(1) + match.group(2)
        pass_num = float(match.group(3).replace("_", "."))
        assert (pass_num >= 1) and (pass_num <= MAX_PASS)
        result[chip] = (family, model, pass_num)
    return result

#
# Private variables
#

# List of all possible chips
_chips = _fillChips()
# Dictionary mapping chips to their (family, model, pass) tuple
_chipNameParts = _fillChipNameParts()

