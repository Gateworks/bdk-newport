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
import time
import os
import difflib
import chip_list
import csr_data
import csr_utils

BG_RESERVED = "lightgray"

BEGIN_TABLE_SORT = "<span title=\"Sortable table, click on headers\"><table class=\"sortable\">\n"

#
# Creating tables, we use TD tags with extra options a lot. This
# function creates them
#
def TD(s, rowspan=1, colspan=1, bgcolor=None, tag="td"):
    result = "<%s" % tag
    if not "</" in s:
        s = s.replace("<", "&lt;")
        s = s.replace(">", "&gt;")
        s = s.replace("\n", "<br>\n")
    if bgcolor:
        result += " bgcolor=" + bgcolor
    if rowspan > 1:
        result += " rowspan=" + str(rowspan)
    if colspan > 1:
        result += " colspan=" + str(colspan)
    result += ">" + s + "</%s>" % tag
    return result

def TH(s, rowspan=1, colspan=1, bgcolor=None):
    return TD(s, rowspan, colspan, bgcolor, tag="th")

#
# All HTML files start with this header
#
def writePageHeader(out, title):
    out.write("<html>\n")
    out.write("<head>\n")
    out.write("<title>%s</title>\n" % title)
    out.write("<meta http-equiv=\"Cache-Control\" content=\"no-cache, no-store, must-revalidate\"/>\n")
    out.write("<meta http-equiv=\"Pragma\" content=\"no-cache\"/>\n")
    out.write("<meta http-equiv=\"Expires\" content=\"0\"/>\n")
    out.write("<script src=\"sorttable.js\"></script>\n")
    out.write("<link href=\"csr.css\" rel=\"stylesheet\" type=\"text/css\">\n")
    out.write("</head>\n")
    out.write("<body>\n")

#
# All HTML files end with this footer
#
def writePageFooter(out):
    out.write("</body>\n")
    out.write("</html>\n")

#
# Format two strings for output. If same, just show one. If different, show
# html diff
#
def formatDiff(chip1, str1, chip2, str2, allowDiff=False):
    if str1 == str2:
        return str1
    if allowDiff and str1 and str2:
        l1 = str(str1).split("\n")
        l2 = str(str2).split("\n")
        return difflib.HtmlDiff(wrapcolumn=60).make_table(l1, l2, chip1, chip2)
    result = ""
    if str1 != "":
        result += "<font class=diff_sub>%s:%s</font>" % (chip1, str1)
    if str2 != "":
        if result:
            result += "<br>"
        result += "<font class=diff_add>%s:%s</font>" % (chip2, str2)
    return result

#
# Write a single Enumeration to html for a specific chip
#
def writeEnum(out, chip, enum):
    out.write("<table>\n")
    display_name = enum["name"].upper()
    out.write("<tr>" + TH("Name") + TD(display_name) + "</tr>\n")
    out.write("<tr>" + TH("Block") + TD(enum["block"]) + "</tr>\n")
    out.write("<tr>" + TH("Width") + TD(str(enum["width"][chip])) + "</tr>\n")
    description = enum["description"][chip]
    out.write("<tr>" + TH("Description") + TD(description) + "</tr>\n")
    out.write("</table>\n")
    out.write("<br><br>\n")
    out.write(BEGIN_TABLE_SORT)
    out.write("<tr>")
    out.write(TH("Name"))
    out.write(TH("Range"))
    out.write(TH("Decimal"))
    out.write(TH("Hex"))
    out.write(TH("Size"))
    out.write(TH("Description"))
    out.write("</tr>\n")
    names = enum["values"].keys()
    names.sort()
    for name in names:
        v = enum["values"][name]
        if not chip in v["value"]:
            continue
        out.write("<tr>")
        out.write(TD(name))
        ranges = csr_utils.rangeToString(v["ranges"][chip])
        out.write(TD(ranges))
        value_eq = csr_utils.addressToString(v["value"][chip], None, smartHex=False)
        out.write(TD(value_eq))
        value_eq = csr_utils.addressToString(v["value"][chip], None, smartHex=True)
        out.write(TD(value_eq))
        out.write(TD(str(v["bar_size"].get(chip, ""))))
        out.write(TD(v["description"][chip]))
        out.write("</tr>\n")
    out.write("</table></span>\n")

#
# Write a single Structure to html for a specific chip
#
def writeStruct(out, chip, struct):
    out.write("<table>\n")
    display_name = struct["name"].upper()
    out.write("<tr>" + TH("Name") + TD(display_name) + "</tr>\n")
    out.write("<tr>" + TH("Block") + TD(struct["block"]) + "</tr>\n")
    description = struct["description"][chip]
    out.write("<tr>" + TH("Description") + TD(description) + "</tr>\n")
    out.write("</table>\n")
    out.write("<br><br>\n")
    out.write("<table>\n")
    out.write("<tr>")
    out.write(TH("Bits"))
    out.write(TH("Name"))
    out.write(TH("Description"))
    out.write("</tr>\n")
    start_bits = {}
    for name in struct["fields"]:
        f = struct["fields"][name]
        if not chip in f["bits"]:
            continue
        start_bits[f["bits"][chip][0]] = f
    bits = sorted(start_bits, reverse=False)
    for bit in bits:
        f = start_bits[bit]
        if csr_utils.isReserved(f["name"]):
            color = BG_RESERVED
        else:
            color = None
        out.write("<tr>")
        bits = f["bits"][chip]
        if bits[0] == bits[1]:
            out.write(TD(str(bits[0]), bgcolor=color))
        else:
            out.write(TD("%d:%d" % (bits[1], bits[0]), bgcolor=color))
        out.write(TD(f["name"], bgcolor=color))
        if chip in f["description"]:
            description = f["description"][chip]
        else:
            description = ""
        out.write(TD(description, bgcolor=color))
        out.write("</tr>\n")
    out.write("</table>\n")

#
# Write a single Register to html for a specific chip
#
def writeReg(out, chip, reg):
    out.write("<table>\n")
    display_name = reg["name"].replace("#", "x").upper()
    range = csr_utils.rangeToString(reg["ranges"][chip])
    out.write("<tr>" + TH("Name") + TD(display_name + range) + "</tr>\n")
    out.write("<tr>" + TH("Block") + TD(reg["block"]) + "</tr>\n")
    description = reg["description"][chip]
    out.write("<tr>" + TH("Description") + TD(description) + "</tr>\n")
    address_eq = csr_utils.addressToString(reg["address"][chip], reg["ranges"][chip])
    out.write("<tr>" + TH("Address") + TD(address_eq) + "</tr>\n")
    out.write("<tr>" + TH("Bus") + TD(reg["bus"][chip]) + "</tr>\n")
    rvu_block_id = reg["rvu_block_id"][chip]
    if rvu_block_id == None:
        rvu_block_id = ""
    out.write("<tr>" + TH("RVU Block") + TD(rvu_block_id) + "</tr>\n")
    bar = reg["bar"][chip]
    if bar == None:
        bar = ""
    out.write("<tr>" + TH("Bar") + TD(bar) + "</tr>\n")
    out.write("<tr>" + TH("Reset") + TD("0x%x" % csr_utils.getResetValue(chip, reg)) + "</tr>\n")
    out.write("</table>\n")
    out.write("<br><br>\n")
    out.write("<table>\n")
    out.write("<tr>")
    out.write(TH("Bits"))
    out.write(TH("Name"))
    out.write(TH("Access"))
    out.write(TH("Reset"))
    out.write(TH("Typical"))
    out.write(TH("Description"))
    out.write("</tr>\n")
    start_bits = {}
    for name in reg["fields"]:
        f = reg["fields"][name]
        if not chip in f["bits"]:
            continue
        start_bits[f["bits"][chip][0]] = f
    bits = sorted(start_bits, reverse=True)
    for bit in bits:
        f = start_bits[bit]
        if csr_utils.isReserved(f["name"]):
            color = BG_RESERVED
        else:
            color = None
        out.write("<tr>")
        bits = f["bits"][chip]
        if bits[0] == bits[1]:
            out.write(TD(str(bits[0]), bgcolor=color))
        else:
            out.write(TD("%d:%d" % (bits[1], bits[0]), bgcolor=color))
        out.write(TD(f["name"], bgcolor=color))
        out.write(TD(f["access"][chip], bgcolor=color))
        out.write(TD(str(f["reset"][chip]), bgcolor=color))
        out.write(TD(str(f["typical"][chip]), bgcolor=color))
        if chip in f["description"]:
            description = f["description"][chip]
        else:
            description = ""
        out.write(TD(description, bgcolor=color))
        out.write("</tr>\n")
    out.write("</table>\n")

#
# Write a single object (Enumeration, Structure, or Register) to html for a
# specific chip
#
def writeObject(chip, name, obj):
    display_name = name.replace("#", "x").upper()
    out = open("html/%s-%s.html" % (chip, display_name), "w")
    title = "%s - %s" % (chip, display_name)
    writePageHeader(out, title)
    out.write("<font size=+3>%s</font><br>\n" % title)
    if isinstance(obj, csr_data.Enum):
        writeEnum(out, chip, obj)
    elif isinstance(obj, csr_data.Struct):
        writeStruct(out, chip, obj)
    elif isinstance(obj, csr_data.Register):
        writeReg(out, chip, obj)
    else:
        assert False, "Invalid type"
    writePageFooter(out)
    out.close()

#
# For each section in html page (Enums, Structs, Regs), this function
# writes links all items in a per block table. For each link created,
# this also calls the function to write the linked file.
#
def writeBlocksTable(out, chip, enums, structs, regs):
    data = {}
    for n in enums:
        assert not n in data
        data[n] = enums[n]
    for n in structs:
        assert not n in data
        data[n] = structs[n]
    for n in regs:
        assert not n in data
        data[n] = regs[n]
    blocks = {}
    for name in data:
        if not chip in data[name]["description"]:
            continue
        block = data[name]["block"]
        if not block in blocks:
            blocks[block] = {}
        blocks[block][name] = data[name]
    block_list = blocks.keys()
    block_list.sort()
    # Write block link table
    count = 0
    out.write("<table class=\"links_table\">")
    out.write("<tr>\n")
    for b in block_list:
        if count >= 10:
            count = 0
            out.write("\n</tr><tr>\n")
        link = "<a href=\"#%s\">%s</a>" % (b,b)
        out.write(TH(link))
        count+=1
    out.write("</tr>\n")
    out.write("</table>")
    # Write block data
    out.write("<br><font size=+2>Per Block Data</font><br>\n")
    out.write("<table class=\"blocks_table\">")
    out.write("<tr>\n")
    columns = 0
    for b in block_list:
        columns = columns + 1
        if columns > 3:
            out.write("</tr>\n")
            out.write("<tr>\n")
            columns = 1
        block = blocks[b]
        out.write("  <td><table class=\"block_table\">")
        out.write("    <tr>")
        anchor = "<a name=\"%s\">%s</a>" % (b,b)
        out.write(TH(anchor))
        out.write("</tr>\n")
        out.write("    <tr><td>\n")
        names = block.keys()
        names.sort()
        out.write("        Enumerations<br>\n")
        for name in names:
            if not isinstance(block[name], csr_data.Enum):
                continue
            display_name = name.replace("#", "x").upper()
            link = "<a href=%s-%s.html>%s</a>" % (chip, display_name, display_name)
            out.write("        %s<br>\n" % link)
        out.write("        Structures<br>\n")
        for name in names:
            if not isinstance(block[name], csr_data.Struct):
                continue
            display_name = name.replace("#", "x").upper()
            link = "<a href=%s-%s.html>%s</a>" % (chip, display_name, display_name)
            out.write("        %s<br>\n" % link)
        out.write("        Registers<br>\n")
        for name in names:
            if not isinstance(block[name], csr_data.Register):
                continue
            display_name = name.replace("#", "x").upper()
            link = "<a href=%s-%s.html>%s</a>" % (chip, display_name, display_name)
            out.write("        %s<br>\n" % link)
        out.write("    </td></tr>\n")
        out.write("  </table></td>\n")
    out.write("</tr>\n")
    out.write("</table>\n")
    for b in block_list:
        block = blocks[b]
        for name in block:
            writeObject(chip, name, data[name])

#
# For a given chip, write an html page of all its enumerations, structures,
# and registers
#
def writeChip(chip, enums, structs, regs):
    out = open("html/%s.html" % chip, "w")
    writePageHeader(out, chip)
    out.write("<font size=+3>%s</font><br>\n" % chip)
    writeBlocksTable(out, chip, enums, structs, regs)
    writePageFooter(out)
    out.close()

#
# Write the difference between two chips for a single Enumeration
#
def diffEnum(out, chip1, chip2, name, enum):
    def formatBoth(str1, str2):
        return formatDiff(chip1, str1, chip2, str2)
    out.write("<table>\n")
    display_name = enum["name"].upper()
    out.write("<tr>" + TH("Name") + TD(display_name) + "</tr>\n")
    out.write("<tr>" + TH("Block") + TD(enum["block"]) + "</tr>\n")
    width1 = str(enum["width"].get(chip1, ""))
    width2 = str(enum["width"].get(chip1, ""))
    width = formatBoth(width1, width2)
    out.write("<tr>" + TH("Width") + TD(width) + "</tr>\n")
    description1 = enum["description"].get(chip1, "")
    description2 = enum["description"].get(chip2, "")
    description = formatDiff(chip1, description1, chip2, description2, allowDiff=True)
    out.write("<tr>" + TH("Description") + TD(description) + "</tr>\n")
    out.write("</table>\n")
    out.write("<br><br>\n")
    out.write(BEGIN_TABLE_SORT)
    out.write("<tr>")
    out.write(TH("Name"))
    out.write(TH("Range"))
    out.write(TH("Value"))
    out.write(TH("Size"))
    out.write(TH("Description"))
    out.write("</tr>\n")
    names = enum["values"].keys()
    names.sort()
    for name in names:
        v = enum["values"][name]
        if (not chip1 in v["value"]) and  (not chip2 in v["value"]):
            continue
        out.write("<tr>")
        out.write(TD(name))
        ranges1 = csr_utils.rangeToString(v["ranges"].get(chip1, []))
        ranges2 = csr_utils.rangeToString(v["ranges"].get(chip2, []))
        ranges = formatBoth(ranges1, ranges2)
        out.write(TD(ranges))
        value_eq1 = csr_utils.addressToString(v["value"].get(chip1, []), None)
        value_eq2 = csr_utils.addressToString(v["value"].get(chip2, []), None)
        value_eq = formatBoth(value_eq1, value_eq2)
        out.write(TD(value_eq))
        bar_size1 = str(v["bar_size"].get(chip1, ""))
        bar_size2 = str(v["bar_size"].get(chip2, ""))
        bar_size = formatBoth(bar_size1, bar_size2)
        out.write(TD(bar_size))
        description1 = v["description"].get(chip1, "")
        description2 = v["description"].get(chip2, "")
        description = formatBoth(description1, description2)
        out.write(TD(description))
        out.write("</tr>\n")
    out.write("</table></span>\n")

#
# Write the difference between two chips for a single Structure
#
def diffStruct(out, chip1, chip2, name, struct):
    def formatBoth(str1, str2):
        return formatDiff(chip1, str1, chip2, str2)
    out.write("<table>\n")
    display_name = struct["name"].upper()
    out.write("<tr>" + TH("Name") + TD(display_name) + "</tr>\n")
    out.write("<tr>" + TH("Block") + TD(struct["block"]) + "</tr>\n")
    description1 = struct["description"].get(chip1, "")
    description2 = struct["description"].get(chip2, "")
    description = formatDiff(chip1, description1, chip2, description2, allowDiff=True)
    out.write("<tr>" + TH("Description") + TD(description) + "</tr>\n")
    out.write("</table>\n")
    out.write("<br><br>\n")
    out.write("<table>\n")
    out.write("<tr>")
    out.write(TH("Bits"))
    out.write(TH("Name"))
    out.write(TH("Description"))
    out.write("</tr>\n")
    start_bits = {}
    filler = {"name": "", "bits": {}, "description": {}}
    for name in struct["fields"]:
        f = struct["fields"][name]
        if chip1 in f["bits"]:
            sb = f["bits"][chip1][0]
            if sb in start_bits:
                start_bits[sb] = (f, start_bits[sb][1])
            else:
                start_bits[sb] = (f, filler)
        if chip2 in f["bits"]:
            sb = f["bits"][chip2][0]
            if sb in start_bits:
                start_bits[sb] = (start_bits[sb][0], f)
            else:
                start_bits[sb] = (filler, f)
    bits = sorted(start_bits, reverse=False)
    for bit in bits:
        f1, f2 = start_bits[bit]
        if (csr_utils.isReserved(f1["name"]) or (f1["name"] == "")) and (csr_utils.isReserved(f2["name"]) or (f2["name"] == "")):
            color = BG_RESERVED
        else:
            color = None
        out.write("<tr>")
        bits1 = f1["bits"].get(chip1, (bit,bit))
        bits2 = f2["bits"].get(chip2, (bit,bit))
        if bits1[0] == bits1[1]:
            bits1 = "%d" % bits1[0]
        else:
            bits1 = "%d:%d" % (bits1[1], bits1[0])
        if bits2[0] == bits2[1]:
            bits2 = "%d" % bits2[0]
        else:
            bits2 = "%d:%d" % (bits2[1], bits2[0])
        bits = formatBoth(bits1, bits2)
        out.write(TD(bits, bgcolor=color))
        s = formatBoth(f1["name"], f2["name"])
        out.write(TD(s, bgcolor=color))
        description1 = f1["description"].get(chip1, "")
        description2 = f2["description"].get(chip2, "")
        description = formatDiff(chip1, description1, chip2, description2, allowDiff=True)
        out.write(TD(description, bgcolor=color))
        out.write("</tr>\n")
    out.write("</table>\n")

#
# Write the difference between two chips for a single Register
#
def diffReg(out, chip1, chip2, name, reg):
    def formatBoth(str1, str2):
        return formatDiff(chip1, str1, chip2, str2)
    out.write("<table>\n")
    display_name = reg["name"].replace("#", "x").upper()
    range1 = csr_utils.rangeToString(reg["ranges"].get(chip1, []))
    range2 = csr_utils.rangeToString(reg["ranges"].get(chip2, []))
    range = formatDiff(chip1, range1, chip2, range2, allowDiff=True)
    out.write("<tr>" + TH("Name") + TD(display_name + range) + "</tr>\n")
    out.write("<tr>" + TH("Block") + TD(reg["block"]) + "</tr>\n")
    description1 = reg["description"].get(chip1, "")
    description2 = reg["description"].get(chip2, "")
    description = formatDiff(chip1, description1, chip2, description2, allowDiff=True)
    out.write("<tr>" + TH("Description") + TD(description) + "</tr>\n")
    address_eq1 = csr_utils.addressToString(reg["address"].get(chip1, []), reg["ranges"].get(chip1, []))
    address_eq2 = csr_utils.addressToString(reg["address"].get(chip2, []), reg["ranges"].get(chip2, []))
    address_eq = formatDiff(chip1, address_eq1, chip2, address_eq2, allowDiff=True)
    out.write("<tr>" + TH("Address") + TD(address_eq) + "</tr>\n")
    bus1 = reg["bus"].get(chip1, "")
    bus2 = reg["bus"].get(chip2, "")
    bus = formatBoth(bus1, bus2)
    out.write("<tr>" + TH("Bus") + TD(bus) + "</tr>\n")
    bar1 = reg["bar"].get(chip1, "")
    if bar1 == None:
        bar1 = ""
    bar2 = reg["bar"].get(chip2, "")
    if bar2 == None:
        bar2 = ""
    bar = formatBoth(bar1, bar2)
    out.write("<tr>" + TH("Bar") + TD(bar) + "</tr>\n")
    out.write("</table>\n")
    out.write("<br><br>\n")
    out.write("<table>\n")
    out.write("<tr>")
    out.write(TH("Bits"))
    out.write(TH("Name"))
    out.write(TH("Access"))
    out.write(TH("Reset"))
    out.write(TH("Typical"))
    out.write(TH("Description"))
    out.write("</tr>\n")
    start_bits = {}
    filler = {"name": "", "bits": {}, "access": {}, "reset": {}, "typical": {}, "description": {}}
    for name in reg["fields"]:
        f = reg["fields"][name]
        if chip1 in f["bits"]:
            sb = f["bits"][chip1][0]
            if sb in start_bits:
                start_bits[sb] = (f, start_bits[sb][1])
            else:
                start_bits[sb] = (f, filler)
        if chip2 in f["bits"]:
            sb = f["bits"][chip2][0]
            if sb in start_bits:
                start_bits[sb] = (start_bits[sb][0], f)
            else:
                start_bits[sb] = (filler, f)
    bits = sorted(start_bits, reverse=True)
    for bit in bits:
        f1,f2 = start_bits[bit]
        if (csr_utils.isReserved(f1["name"]) or (f1["name"] == "")) and (csr_utils.isReserved(f2["name"]) or (f2["name"] == "")):
            color = BG_RESERVED
        else:
            color = None
        out.write("<tr>")
        bits1 = f1["bits"].get(chip1, None)
        bits2 = f2["bits"].get(chip2, None)
        if bits1 == None:
            bits1 = ""
        elif bits1[0] == bits1[1]:
            bits1 = "%d" % bits1[0]
        else:
            bits1 = "%d:%d" % (bits1[1], bits1[0])
        if bits2 == None:
            bits2 = ""
        elif bits2[0] == bits2[1]:
            bits2 = "%d" % bits2[0]
        else:
            bits2 = "%d:%d" % (bits2[1], bits2[0])
        bits = formatBoth(bits1, bits2)
        out.write(TD(bits, bgcolor=color))
        s = formatBoth(f1["name"], f2["name"])
        out.write(TD(s, bgcolor=color))
        s = formatBoth(f1["access"].get(chip1, ""), f2["access"].get(chip2, ""))
        out.write(TD(s, bgcolor=color))
        s = formatBoth(f1["reset"].get(chip1, ""), f2["reset"].get(chip2, ""))
        out.write(TD(str(s), bgcolor=color))
        s = formatBoth(f1["typical"].get(chip1, ""), f2["typical"].get(chip2, ""))
        out.write(TD(str(s), bgcolor=color))
        description1 = f1["description"].get(chip1, "")
        description2 = f2["description"].get(chip2, "")
        description = formatDiff(chip1, description1, chip2, description2, allowDiff=True)
        out.write(TD(description, bgcolor=color))
        out.write("</tr>\n")
    out.write("</table>\n")

#
# Write a single object (Enumeration, Structure, or Register) to html for a
# for the differences between two chips
#
def diffObject(chip1, chip2, name, obj):
    display_name = name.replace("#", "x").upper()
    out = open("html/%s-%s-%s.html" % (chip1, chip2, display_name), "w")
    title = "%s vs %s - %s" % (chip1, chip2, display_name)
    writePageHeader(out, title)
    out.write("<font size=+3>%s</font><br>\n" % title)
    if isinstance(obj, csr_data.Enum):
        diffEnum(out, chip1, chip2, name, obj)
    elif isinstance(obj, csr_data.Struct):
        diffStruct(out, chip1, chip2, name, obj)
    elif isinstance(obj, csr_data.Register):
        diffReg(out, chip1, chip2, name, obj)
    else:
        assert False, "Invalid type"
    writePageFooter(out)
    out.close()

#
# For each section in html page (Enums, Structs, Regs), this function
# writes links all items in a per block table. For each link created,
# this also calls the function to write the linked file.
#
def diffBlocksTable(out, chip1, chip2, enums, structs, regs):
    data = {}
    for n in enums:
        assert not n in data
        data[n] = enums[n]
    for n in structs:
        assert not n in data
        data[n] = structs[n]
    for n in regs:
        assert not n in data
        data[n] = regs[n]
    blocks = {}
    for name in data:
        chip1_exists = chip1 in data[name]["description"]
        chip2_exists = chip2 in data[name]["description"]
        if not chip1_exists and not chip2_exists:
            continue
        block = data[name]["block"]
        if not block in blocks:
            blocks[block] = {}
        blocks[block][name] = data[name]
    block_list = blocks.keys()
    block_list.sort()
    # Write block link table
    count = 0
    out.write("<table class=\"links_table\">")
    out.write("<tr>\n")
    for b in block_list:
        if count >= 10:
            count = 0
            out.write("\n</tr><tr>\n")
        link = "<a href=\"#%s\">%s</a>" % (b,b)
        out.write(TH(link))
        count+=1
    out.write("</tr>\n")
    out.write("</table>")
    # Write block data
    out.write("<br><font size=+2>Per Block Data</font><br>\n")
    out.write("<table class=\"blocks_table\">")
    out.write("<tr>\n")
    columns = 0
    for b in block_list:
        columns = columns + 1
        if columns > 3:
            out.write("</tr>\n")
            out.write("<tr>\n")
            columns = 1
        block = blocks[b]
        out.write("  <td><table class=\"block_table\">")
        out.write("    <tr>")
        anchor = "<a name=\"%s\">%s</a>" % (b,b)
        out.write(TH(anchor))
        out.write("</tr>\n")
        out.write("    <tr><td>\n")
        names = block.keys()
        names.sort()
        def do_objects(obj_type):
            for name in names:
                if not isinstance(block[name], obj_type):
                    continue
                display_name = name.replace("#", "x").upper()
                chip1_exists = chip1 in block[name]["description"]
                chip2_exists = chip2 in block[name]["description"]
                if not chip1_exists and not chip2_exists:
                    # Not valid on either chip
                    assert False
                elif chip1_exists and not chip2_exists:
                    # Deleted from chip2
                    link = "<a class=diff_sub href=%s-%s.html>%s(Removed)</a>" % (chip1, display_name, display_name)
                elif not chip1_exists and chip2_exists:
                    # Added to chip2
                    link = "<a class=diff_add href=%s-%s.html>%s(Added)</a>" % (chip2, display_name, display_name)
                elif csr_utils.isDifferent(chip1, chip2, block[name]):
                    # Different between the chips
                    link = "<a href=%s-%s-%s.html>%s(Changed)</a>" % (chip1, chip2, display_name, display_name)
                    diffObject(chip1, chip2, name, data[name])
                else:
                    # Same on both chips
                    continue
                out.write("        %s<br>\n" % link)
        out.write("        Enumerations<br>\n")
        do_objects(csr_data.Enum)
        out.write("        Structures<br>\n")
        do_objects(csr_data.Struct)
        out.write("        Registers<br>\n")
        do_objects(csr_data.Register)
        out.write("    </td></tr>\n")
        out.write("  </table></td>\n")
    out.write("</tr>\n")
    out.write("</table>\n")

#
# For two chips, write an html page of differences between all its
# enumerations, structures, and registers
#
def diffChip(chip1, chip2, enums, structs, regs):
    filename = "%s-%s.html" % (chip1, chip2)
    out = open("html/%s" % filename, "w")
    title = "%s versus %s" % (chip1, chip2)
    writePageHeader(out, title)
    out.write("<font size=+3>%s</font><br>\n" % title)
    diffBlocksTable(out, chip1, chip2, enums, structs, regs)
    writePageFooter(out)
    out.close()
    return chip1, chip2, filename

#
# Write the master index page index.html
#
def writeMainIndex(enums, structs, regs):
    diff_list = []
    out = open("html/index.html", "w")
    writePageHeader(out, "Cavium Chip Information")
    out.write("<table class=\"layout_table\">\n")
    out.write("<tr><td>\n")
    out.write("<font size=-1>Updated: %s</font><br><br>\n" % time.asctime())
    out.write("<font size=+2>Chips</font><br>\n")
    out.write("<table class=\"chips_table\">\n")
    out.write("<tr>")
    out.write(TH("Chip"))
    out.write(TH("Pass", colspan=4))
    out.write("</tr>")
    by_model = {}
    for chip in chip_list.getChips():
        family, model, pass_num = chip_list.getChipNameParts(chip)
        if not model in by_model:
            by_model[model] = []
        by_model[model].append((chip, pass_num))
    models = by_model.keys()
    models.sort()
    for model in models:
        out.write("<tr>")
        out.write(TD(model))
        last_chip = None
        for chip, p in by_model[model]:
            link = "<a href=%s.html target=\"frame\">%.1f</a>" % (chip, p)
            out.write(TD(link))
            if last_chip:
                diff_list.append(diffChip(last_chip, chip, enums, structs, regs))
            last_chip = chip
        out.write("</tr>\n")
    out.write("</table>\n")
    out.write("<font size=+2>Differences</font><br>\n")
    for diff in chip_list.DIFFS:
        diff_list.append(diffChip(diff[0], diff[1], enums, structs, regs))
    out.write("<table class=\"chips_table\">\n")
    out.write("<tr>")
    out.write(TH("Chip1"))
    out.write(TH("Chip2"))
    out.write(TH("Diff"))
    out.write("</tr>\n")
    for diff in diff_list:
        out.write("<tr>")
        out.write(TD(diff[0].replace("P", "&nbsp;").replace("_", ".")))
        out.write(TD(diff[1].replace("P", "&nbsp;").replace("_", ".")))
        link = "<a href=%s target=\"frame\">diff</a>" % diff[2]
        out.write(TD(link))
        out.write("</tr>\n")
    out.write("</table>\n")
    out.write("</td>\n")
    out.write("<td width=100%>")
    out.write("<iframe name=\"frame\" width=100%></iframe>\n")
    out.write("</td></tr>\n")
    out.write("</table>\n")
    writePageFooter(out)
    out.close()

#
# Create html pages for all chips
#
def process(enums, structs, regs):
    for chip in chip_list.getChips():
        writeChip(chip, enums, structs, regs)
    writeMainIndex(enums, structs, regs)

