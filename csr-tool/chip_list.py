# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import re
import os

#
# Blocks marked proprietary_for are normally suppressed to protect NDAs. If
# the environment variable PROPRIETARY is set, it is interpreted as a comma
# separated list of allowed proprietary types.
#
ALLOWED_PROPRIETARY = []
if "PROPRIETARY" in os.environ:
    ALLOWED_PROPRIETARY = os.environ["PROPRIETARY"].split(",")

#
# The following list defines all chips processed by this script. Each entry
# is a chip name, chip pass, and a yaml file
#
OCTEONTX_CHIPS = [
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
    ["CN96XX",  1.0, "yaml/t96_pass_1.0.yaml"],
    ["CN96XX",  1.1, "yaml/t96_pass_1.1.yaml"],
    ["CN96XX",  3.0, "yaml/t96_pass_3.0.yaml"],
    ["CNF95XX", 1.0, "yaml/t95_pass_1.0.yaml"],
    ["CNF95XX", 2.0, "yaml/t95_pass_2.0.yaml"],
    ["LOKI",    1.0, "yaml/loki_pass_1.0.yaml"],
    ["CN98XX",  1.0, "yaml/t98_pass_1.0.yaml"],
]

#
# Additional diffs to show in HTML output above the usual
# chip pass differences
#
DIFFS = [
    ("CN70XX_P1_0", "CN78XX_P1_0"),
    ("CN78XX_P1_0", "CN73XX_P1_0"),
    ("CN73XX_P1_0", "CNF75XX_P1_0"),
    ("CNF75XX_P1_0", "CN78XX_P2_0"),
    ("CN78XX_P1_0", "CN88XX_P1_0"),
    ("CN88XX_P2_0", "CN81XX_P1_0"),
    ("CN88XX_P2_0", "CN83XX_P1_0"),
    ("CN81XX_P1_0", "CN83XX_P1_0"),
    ("CN83XX_P1_0", "CN96XX_P1_0"),
    ("CN96XX_P1_0", "CNF95XX_P1_0"),
    ("CNF95XX_P2_0", "LOKI_P1_0"),
    ("CN96XX_P3_0", "CN98XX_P1_0"),
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
    "PCICONFIGEP_SHADOW", # PCIe config space in EP mode, shadow register? (Added for t96)
    "PCICONFIGEPVF",    # PCIe config space in EP mode, virtual function (Added for t96)
    "PCICONFIGRC",      # PCIe config space in RC mode
    "PEXP",             # PCIe BAR 0 address only
    "PEXP_NCB",         # NCB-direct and PCIe BAR0 address
    "PEXPV_NCB",        # Virtual NCB-direct and PCIe BAR0 address
    "RSL",              # Slow CSR
    "RSL32b",           # Slow CSR, 32bit
    "RVU_PF_BAR0",      # Offset into a RVU Physical function BAR (Added for t96)
    "RVU_PF_BAR2",      # Offset into a RVU Physical function BAR (Added for t96)
    "RVU_PFVF_BAR2",    # Offset into a RVU PF or VF BAR (Added for t96)
    "RVU_VF_BAR2",      # Offset into a RVU VF BAR (Added for t96)
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
    "RO/WRSL", # Read only, can be written through RSL
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
MAX_CSR_PARAMS = 6

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
    for chip in OCTEONTX_CHIPS:
        files.append(chip[2])
    return files

#
# Given a chip name, return the yaml file it used
#
def getYamlFile(chip):
    chip_family, chip_model, chip_pass = getChipNameParts(chip)
    for c in OCTEONTX_CHIPS:
        if (chip_model == c[0]) and (chip_pass == c[1]):
            return c[2]
    raise Exception("Unable to find yaml file for \"%s\"" % chip)

#
# Given a chip, return a tuple containing the family, model, and pass
# Family is "CN7", "CNF7", "CN8", "CN9"
# Model is "CN73XX", "CNF75XX", "CN88XX", "CN96XX", etc
# Pass is a float between 1.0 and 4.7
#
def getChipNameParts(chip):
    return _chipNameParts[chip]

# Given a chip name, convert it into a model define as used in the BDK
# A chip name can be any name listed in OCTEONTX_CHIPS. Optionally the
# name may be followed by major pass information, then possibly minor
# pass information. In addition, the following special chip names are
# allowed:
# CN7: All Octeon chips and passes
# CN8: All OcteonTX chips and passes
# CN9: All OcteonTX2 chips and passes
# CN: All chips and passes
#
# Example pass info:
# CN83XX_P1     => OCTEONTX_CN83XX_PASS1_X
# CN83XX_P1_0   => OCTEONTX_CN83XX_PASS1_0
# LOKI_P1_0     => OCTEONTX_LOKI_PASS1_0
def chipToModelDefine(chip):
    PREFIX = "OCTEONTX_"
    assert not "XXP" in chip, chip
    parts = chip.split("_")
    assert len(parts) <= 3, chip
    if parts[0] in ["CN7", "CN8", "CN9"]:
        parts[0] += "XXX"
    if len(parts) >= 2:
        assert len(parts[1]) == 2, chip
        assert parts[1][0] == "P", chip
        major = int(parts[1][1])
        assert major >= 1, chip
        assert major <= MAX_MAJOR_PASS, chip
    if len(parts) == 3:
        assert len(parts[2]) == 1, chip
        minor = int(parts[2][0])
        assert minor >= 0, chip
        assert minor <= MAX_MINOR_PASS, chip

    model_define = PREFIX + parts[0]
    if len(parts) >= 2:
        model_define += "_PASS%d" % major
        if len(parts) == 3:
            model_define += "_%d" % minor
        else:
            model_define += "_X"
    return model_define

# Given a chip name, convert it into a C structure nameas used in the BDK
# A chip name can be any name listed in OCTEONTX_CHIPS. Optionally the
# name may be followed by major pass information, then possibly minor
# pass information. In addition, the following special chip names are
# allowed:
# CN7: All Octeon chips and passes
# CN8: All OcteonTX chips and passes
# CN9: All OcteonTX2 chips and passes
# CN: All chips and passes
#
# Example pass info:
# CN83XX_P1     => cn83xxp1
# CN83XX_P1_0   => cn83xxp1_0
# LOKI_P1_0     => loki_p1_0
def chipToStructName(chip):
    assert not "XXP" in chip, chip
    # Previous to using project names, all chips ended with XX and we didn't
    # have a underscore before the pass. Rename in these cases so old code
    # doesn't have to change
    if "XX_P" in chip:
        chip = chip.replace("XX_P", "XXP")
    return chip.lower()

#
# Internal functions, don't call
#

# Create the list of all possible chips
def _fillChips():
    all_chips = []
    for chip in OCTEONTX_CHIPS:
        chip_name = chip[0]
        chip_pass = chip[1]
        fullname = "%s_P%.1f" % (chip_name, chip_pass)
        fullname = fullname.replace(".", "_")
        all_chips.append(fullname)
    all_chips.sort()
    return all_chips

# Create a dictionary mapping chips to their (family, model, pass) tuple
def _fillChipNameParts():
    result = {}
    for chip in getChips():
        if chip.startswith("CN"):
            match = re.match("^(CNF?P?[0-9])([0-9X]XX)_P([0-9]_[0-9])$", chip)
            if not match:
                raise Exception("Illegal chip name format \"%s\"" % chip)
            family = match.group(1)
            # Special case, change CNF (fusion) to CN so we treat fusion the
            # same as other chips for that architecture
            if family.startswith("CNF"):
                family = "CN" + family[3:]
            model = match.group(1) + match.group(2)
            pass_num = float(match.group(3).replace("_", "."))
        else: # Project names, LOKI, TITAN, ...
            match = re.match("^([A-Z]+)_P([0-9]_[0-9])$", chip)
            if not match:
                raise Exception("Illegal chip name format \"%s\"" % chip)
            family = "CN9"
            model = match.group(1)
            pass_num = float(match.group(2).replace("_", "."))
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

