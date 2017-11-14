/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>

/**
 * Return a help string for the given configuration parameter
 *
 * @param cfg_item Configuration parameter to get help for
 *
 * @return Help string for the user
 */
const char* bdk_config_get_help(bdk_config_t cfg_item)
{
    static const char *help[__BDK_CONFIG_END] = {
    /* Board manufacturing data */
    [BDK_CONFIG_BOARD_MODEL] =
            "Board model number. This is used to determine the name of the\n"
            "configuration file containing the boards default settings. This\n"
            "parameter is stored in a static board manufacturing area at the\n"
            "top of the boot flash.",
    [BDK_CONFIG_BOARD_REVISION] =
            "The board revision level. This parameter is stored in a static\n"
            "board manufacturing area at the top of the boot flash.",
    [BDK_CONFIG_BOARD_SERIAL] =
            "Unique string used as a serial number. This parameter is stored\n"
            "in a static board manufacturing area at the top of the boot flash.",
    [BDK_CONFIG_MAC_ADDRESS] =
            "The first MAC address assigned to the on-chip network ports. MAC\n"
            "addresses are in a contiguous block starting at this address and\n"
            "containing BOARD-MAC-ADDRESS-NUM number of addresses. The format\n"
            "of this parameter is 0xXXXXXXXXXXXX, 12 hex digits starting with\n"
            "'0x'.This parameter is stored in a static board manufacturing\n"
            "area at the top of the boot flash.",
    [BDK_CONFIG_MAC_ADDRESS_NUM] =
            "The number of MAC addresses assigned to the on-chip network\n"
            "ports. See BOARD-MAC-ADDRESS for the actual MAC address numeric\n"
            "value.This parameter is stored in a static board manufacturing\n"
            "area at the top of the boot flash.",
    [BDK_CONFIG_MAC_ADDRESS_NUM_OVERRIDE] =
            "Some boards shipped with BOARD-MAC-ADDRESS-NUM programmed\n"
            "incorrectly. This value overrides the setting in flash of\n"
            "BOARD-MAC-ADDRESS-NUM, allowing correction of the value. This\n"
            "should normally not be used.\n",
    /* Board generic */
    [BDK_CONFIG_BMC_TWSI] =
            "On-chip TWSI port connected to the BMC for IPMI traffic.\n"
            "-1 = No connection exists. 0+ is TWSI bus number.",
    [BDK_CONFIG_WATCHDOG_TIMEOUT] =
            "This specifies a watchdog timer should run during boot and reset\n"
            "the chip if boot hangs for some reason. The timeout is specified\n"
            "in milliseconds. Zero disables the watchdog.",
    [BDK_CONFIG_TWSI_WRITE] =
            "Allow a sequence of TWSI writes to be performed during boot. Each\n"
            "string in the list line is executed in sequence. The TWSI write\n"
            "format is:\n"
            "    node,twsi_id,dev_addr,internal_addr,num_bytes,ia_width_bytes,data\n"
            "    sleep,ms\n"
            "    gpio,node,gpio_num,state\n"
            "node           = Node ID the twsi bus is on. -1 means the local node\n"
            "twsi_id        = TWSI bus to use\n"
            "dev_addr       = TWSI bus address\n"
            "internal_addr  = TWSI internal address, zero if not used\n"
            "num_bytes      = Number of bytes to write (1-8)\n"
            "ia_width_bytes = Internal address width in bytes (0-2)\n"
            "data           = Data to write as a 64bit number\n"
            "sleep,ms       = This on a line delays for 'ms' milliseconds\n"
            "gpio,...       = This sets the state of a GPIO gpio_num to 0 or 1",
    [BDK_CONFIG_MDIO_WRITE] =
            "Allow a sequence of MDIO writes to be performed during boot. Each\n"
            "string in the list line is executed in sequence. The MDIO write\n"
            "format is:\n"
            "    clause,node,bus_id,phy_id,device,location,val\n"
            "    sleep,ms\n"
            "    gpio,node,gpio_num,state\n"
            "clause   = MDIO clause for the write (22 or 45)\n"
            "node     = Node the MDIO bus is connected, -1 for local\n"
            "bus_id   = MDIO bus to use\n"
            "phy_id   = MDIO address\n"
            "device   = Clause 45 internal device address, zero for clause 22\n"
            "location = MDIO register\n"
            "val      = Value to write\n"
            "sleep,ms = This on a line delays for 'ms' milliseconds\n"
            "gpio,... = This sets the state of a GPIO gpio_num to 0 or 1",
    /* Board wiring of network ports and PHYs */
    [BDK_CONFIG_PHY_ADDRESS] =
            "PHY address encoding:\n"
            "    Bits[31:24]: Node ID, 0xff for node the ethernet device is on\n"
            "    Bits[23:16]: Only used for TWSI\n"
            "    Bits[15:12]: PHY connection type (0=MDIO, 1=Fixed, 2=TWSI)\n"
            "For MDIO:\n"
            "    Bits[31:24]: Node ID, 0xff for node the ethernet device is on\n"
            "    Bits[23:16]: 0\n"
            "    Bits[15:12]: 0=MDIO\n"
            "    Bits[11:8]: MDIO bus number\n"
            "    Bits[7:0]: MDIO address\n"
            "For Fixed:\n"
            "    Bits[31:24]: 0\n"
            "    Bits[23:16]: Zero\n"
            "    Bits[15:12]: 1=Fixed\n"
            "    Bits[11:0]:  0 = 1Gb, 1 = 100Mb\n"
            "For TWSI:\n"
            "    Bits[31:24]: Node ID, 0xff for node the ethernet device is on\n"
            "    Bits[23:16]: TWSI internal address width in bytes (0-2)\n"
            "    Bits[15:12]: 2=TWSI\n"
            "    Bits[11:8]: TWSI bus number\n"
            "    Bits[7:0]: TWSI address",
    [BDK_CONFIG_BGX_ENABLE] =
            "Independent enables for each on-chip BGX port. Use this to\n"
            "disable ports that are not wired on a board. Default is that all\n"
            "ports are enabled.",
    /* Non-EBB specific SFF8104 board and alike */
    [BDK_CONFIG_AQUANTIA_PHY] = 
            "Set for ports which have aquantia phy attached\n"
            "Encoding:\n"
            "When phy is not attached:"
            "     Bits[15:0] 0 - no aquantia phy\n"
	    "When aquantia phy is attached:\n"
            "    Bits[15:8]: SERDES lane number to use, 0xff use normal QLM/DLM mapping\n"
            "                used when mapping depends on dip switches\n"
            "    Bits[7:0]: 1 - aquantia phy attached",
    /* BDK Configuration params */
    [BDK_CONFIG_VERSION] =
            "BDK Version information.",
    [BDK_CONFIG_NUM_PACKET_BUFFERS] =
            "Number of packet buffers in the BDK.",
    [BDK_CONFIG_PACKET_BUFFER_SIZE] =
            "The size of each packet buffer in the BDK.",
    [BDK_CONFIG_SHOW_LINK_STATUS] =
            "Controls whether the BDK displays link status messages.",
    [BDK_CONFIG_COREMASK] =
            "Controls the cores used by the BDK. Zero means all cores.",
    [BDK_CONFIG_BOOT_MENU_TIMEOUT] =
            "Timeout for the boot menu in seconds.",
    [BDK_CONFIG_BOOT_PATH_OPTION] =
            "This is used by the boot menu to control which boot path the init\n"
            "code chooses. The supported options are\n"
            "    0 = Normal boot path\n"
            "    1 = Diagnostics boot path",
    [BDK_CONFIG_BOOT_NEXT_STAGE] =
            "This is used by the boot apps to determine the next boot stage.\n"
            "    e.g.:\n"
            "      BDK-CONFIG-BOOT-NEXT-STAGE-INIT=/fatfs/cortina-app.bin",
    [BDK_CONFIG_TRACE] =
            "BDK trace level. This is a bitmask of the enumeration defined in\n"
            "bdk-warn.h. Each bit turns on tracing of a specific BDK\n"
            "component.",
    /* Chip feature items */
    [BDK_CONFIG_MULTI_NODE] =
            "Determine how multi-node is supported for this system:\n"
            "    0 = Multi-node is not supported\n"
            "    1 = Multi-node is supported and booting requires two nodes\n"
            "    2 = Multi-node is auto detected. Two nodes are used if\n"
            "        if available, otherwise fall back to single node.",
    [BDK_CONFIG_PCIE_EA] =
            "Determine if internal PCIe ECAMs support Enhanced Allocation(EA):\n"
            "    0 = Enhanced Allocation is not supported\n"
            "    1 = Enhanced Allocation is supported\n"
            "Note EA is not supported on CN88XX pass 1.x, and is always\n"
            "disabled.",
    [BDK_CONFIG_PCIE_ORDERING] =
            "Enforcing stronger PCIe ordering. Use this option if a PCIe card\n"
            "is having compatibility issues.\n"
            "    0 = Don't wait for commit, default for best performance.\n"
            "    1 = Wait for commit, use conservative ordering.",
    [BDK_CONFIG_CCPI_LANE_REVERSE] =
            "Force CCPI lane reversal. This should be set for boards which\n"
            "reverse the CCPI lanes between nodes. If lane 0 connects to lane\n"
            "23, this option is needed. CN88XX pass 2.0 and higher automatically\n"
            "detect lane reversal, so setting this is optional.\n"
            "    0 = Automatically detect lane reversal, no lane reversal on\n"
            "        CN88XX pass 1.x.\n"
            "    1 = Force lane reversal, required on CN88XX pass 1.0 with CCPI\n"
            "        lanes reversed.",
    [BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR] =
            "Specifies the preset request vector (PCIERCX_CFG554[PRV]). Requesting\n"
            "of presets during the initial part of the EQ master phase.\n"
            "Encoding scheme as follows:\n"
            "    Bit [15:0] = 0x0: No preset is requested and evaluated in the EQ master phase.\n"
            "    Bit [i] = 1: Preset=i is requested and evaluated in the EQ master phase.\n"
            "    0000000000000000: No preset req/evaluated in EQ master phase\n"
            "    00000xxxxxxxxxx1: Preset 0 req/evaluated in EQ master phase\n"
            "    00000xxxxxxxxx1x: Preset 1 req/evaluated in EQ master phase\n"
            "    00000xxxxxxxx1xx: Preset 2 req/evaluated in EQ master phase\n"
            "    00000xxxxxxx1xxx: Preset 3 req/evaluated in EQ master phase\n"
            "    00000xxxxxx1xxxx: Preset 4 req/evaluated in EQ master phase\n"
            "    00000xxxxx1xxxxx: Preset 5 req/evaluated in EQ master phase\n"
            "    00000xxxx1xxxxxx: Preset 6 req/evaluated in EQ master phase\n"
            "    00000xxx1xxxxxxx: Preset 7 req/evaluated in EQ master phase\n"
            "    00000xx1xxxxxxxx: Preset 8 req/evaluated in EQ master phase\n"
            "    00000x1xxxxxxxxx: Preset 9 req/evaluated in EQ master phase\n"
            "    000001xxxxxxxxxx: Preset 10 req/evaluated in EQ master phase\n"
            "    All other encodings: Reserved\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_WIDTH] =
	    "Override the auto detected width of a PCIe port. The width of a PCIe\n"
	    "port is normally auto detected. Some boards do not wire all PCIe lanes,\n"
	    "which causes the port assume more lanes than are actually possible. Use\n"
	    "this value to limit the maximum lanes the port can support. The default\n"
	    "value of -1 lets the hardware decide.\n"
	    "Parameters:\n"
	    "    N#: Parameter can be different for each node. This specifies\n"
	    "        which node the value is for. Node must be 0-3. Optional.\n"
	    "    PORT#: Parameter can be different for PCIe port. This specifies\n"
	    "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_PHYSICAL_SLOT] =
	    "Configure the physical slot number for a PCIe port. This is used by error\n"
	    "reporting to narrow down failures to a board PCIe slot number. The\n"
	    "default value of -1 doesn't set the slot number.\n"
	    "Parameters:\n"
	    "    N#: Parameter can be different for each node. This specifies\n"
	    "        which node the value is for. Node must be 0-3. Optional.\n"
	    "    PORT#: Parameter can be different for PCIe port. This specifies\n"
	    "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_FLASH] =
            "Allow a sequence of PCIe config accesses during endpoint boot. Each\n"
            "string in the list is written to the PCIe SPI flash to configure\n"
            "the endpoint before link initialization. The string format is:\n"
            "    cl2,address,data\n"
            "    erase\n"
            "cl2      = 1 for writes to the mask, 0 for normal writes\n"
            "address  = PCIe config space address\n"
            "data     = Data to write\n"
            "erase    = Special case to erase the SPI flash without programming anything",
    [BDK_CONFIG_CHIP_SKU] =
            "Cavium SKU for the chip. This is determined by early code and\n"
            "passed to later software for display. This should not be set in\n"
            "the input device tree, it will be ignored.",
    [BDK_CONFIG_CHIP_SERIAL] =
            "Cavium serial number for the chip. This is determined by early\n"
            "code and passed to later software for display. This should not be\n"
            "set in the input device tree, it will be ignored.",
    [BDK_CONFIG_CHIP_UNIQUE_ID] =
            "Cavium unique ID for the chip. This is determined by early\n"
            "code and passed to later software for display. This should not be\n"
            "set in the input device tree, it will be ignored.",
    /* QLM/DLM related config */
    [BDK_CONFIG_QLM_AUTO_CONFIG] =
            "For Cavium evaluation boards, query the MCU for QLM/DLM setup\n"
            "information. The MCU supplies a TWSI protocol for the SOC to\n"
            "query the modules plugged in and automatically set the QLMs or\n"
            "DLMs to the correct mode. This should only be enabled(1) on Cavium\n"
            "EBB8XXX boards. Other boards should have it disabled(0).",
/* SFF8104 related QLM config */	    
    [BDK_CONFIG_QLM_DIP_AUTO_CONFIG] =
            "For Cavium SFF boards, query the DIP switches for QLM setup\n"
            "information. The DIP switches are on FTDI I2C GPIO expander.\n"
            "This should only be enabled(1) on Cavium SFF8XXX boards.\n"
	    "Other boards should have it disabled(0).",
	    
    [BDK_CONFIG_QLM_MODE] =
            "Set the mode of a QLM/DLM. The possible mode strings are:\n"
            "    DISABLED\n"
            "    PCIE_1X1\n"
            "    PCIE_2X1\n"
            "    PCIE_1X2\n"
            "    PCIE_1X4\n"
            "    PCIE_1X8\n"
            "    SATA_4X1\n"
            "    SATA_2X1\n"
            "    ILK\n"
            "    SGMII_4X1\n"
            "    SGMII_2X1\n"
            "    SGMII_1X1\n"
            "    XAUI_1X4\n"
            "    RXAUI_2X2\n"
            "    RXAUI_1X2\n"
            "    OCI\n"
            "    XFI_4X1\n"
            "    XFI_2X1\n"
            "    XFI_1X1\n"
            "    XLAUI_1X4\n"
            "    10G_KR_4X1\n"
            "    10G_KR_2X1\n"
            "    10G_KR_1X1\n"
            "    40G_KR4_1X4\n"
            "    QSGMII_4X1",
    [BDK_CONFIG_QLM_FREQ] =
            "Set the speed of a QLM/DLM in Mhz. The possible speeds are:\n"
            "    1250\n"
            "    1500\n"
            "    2500\n"
            "    3000\n"
            "    3125\n"
            "    5000\n"
            "    6000\n"
            "    6250\n"
            "    8000\n"
            "   10312",
    [BDK_CONFIG_QLM_CLK] =
            "Set the source of the QLM/DLM reference clock:\n"
            "    0 = Common clock 0\n"
            "    1 = Common clock 1\n"
            "    2 = QLM/DLM external reference\n"
            "    3 = Common clock 2\n",
    [BDK_CONFIG_QLM_TUNING_TX_SWING] =
            "Setting of GSERX_LANEX_TX_CFG_0[CFG_TX_SWING] for the QLM/DLM. This\n"
            "should only be used for QLMs or DLMs used for BGX and CCPI not using KR\n"
            "training.",
    [BDK_CONFIG_QLM_TUNING_TX_PREMPTAP] =
            "Setting of GSERX_LANEX_TX_PRE_EMPHASIS[CFG_TX_PREMPTAP] for the\n"
            "QLM/DLM. This should only be used for QLMs or DLMs used for BGX and CCPI not\n"
            "using KR training. CFG_TX_PREMPTAP:\n"
            "    Bits[8:5] = Tx Post Tap; Bits[3:0] = Tx Pre Tap",
    [BDK_CONFIG_QLM_TUNING_TX_GAIN] =
            "Setting of GSERX_LANEX_TX_CFG_3[PCS_SDS_TX_GAIN] for the QLM/DLM. This\n"
            "should only be used for QLMs or DLMs used for BGX and CCPI not using KR\n"
            "training.",
    [BDK_CONFIG_QLM_TUNING_TX_VBOOST] =
            "Setting of GSERX_LANEX_TX_CFG_3[CFG_TX_VBOOST_EN] for the QLM/DLM. This\n"
            "should only be used for QLMs or DLMs used for BGX and CCPI not using KR\n"
            "training.",
    [BDK_CONFIG_QLM_CHANNEL_LOSS] =
            "The insertion loss at Nyquist rate (e.g. 5.125Ghz for XFI/XLAUI) in\n"
            "dB for the RX channel should be passed into the channel loss\n"
            "attribute. For CN8XXX, this attribute is used for XFI/10GBASE-KR,\n"
            "XLAUI/40GBASE-KR4, and CCPI. If no channel loss attribute is\n"
            "provided the default value assumes a loss of greater than 10dB\n"
            "for networking (long channel) and less than 10dB (short channel)\n"
            "for CCPI. This matches the most common usage.",
    /* DRAM configuration options */
    [BDK_CONFIG_DDR_SPEED] =
            "Speed grade to use for DRAM in MT/s. Hardware may adjust this value\n"
            "slightly to improve DRAM stability, so scope measurements may not\n"
            "exactly match the frequency with MT/s. The Cavium supported speed\n"
            "grades are:\n"
            "       0 (auto-set from SPD contents)\n"
            "     666 MT/s (DDR3 only)\n"
            "     800 MT/s (DDR3 only)\n"
            "    1066 MT/s (DDR3 only)\n"
            "    1333 MT/s (DDR3 only)\n"
            "    1600 MT/s\n"
            "    1866 MT/s\n"
            "    2133 MT/s (DDR4 only)\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_ALT_REFCLK] =
            "Set to use a an alternate reference clock for DRAM than the usual\n"
            "50Mhz reference. The value of here specifies the frequency of the\n"
            "alternate clock in Mhz. Currently the only supported reference\n"
            "clock frequencies are 50Mhz and 100Mhz.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_SPD_ADDR] =
            "TWSI address of the DIMM SPD. The encoding of this address is\n:"
            "    [15:12]: TWSI bus the DIMM is connected to.\n"
            "     [11:7]: Reserved, set to zero.\n"
            "      [6:0]: TWSI address for the DIMM.\n"
            "A value of zero means the DIMMs are not accessible. Hard coded\n"
            "values will be read from DDR-CONFIG-SPD-DATA."
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_SPD_DATA] =
            "DIMM SPD data to be used if memory doesn't support the standard\n"
            "TWSI access to DIMM SPDs. The format of this is a binary blob\n"
            "stored in the device tree. An example would be:\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_DQX_CTL] =
            "Drive strength control for DDR_DQ* / DDR_DQS_*_P/N drivers.\n"
            "    0x1 = 24 ohm.\n"
            "    0x2 = 26.67 ohm.\n"
            "    0x3 = 30 ohm.\n"
            "    0x4 = 34.3 ohm.\n"
            "    0x5 = 40 ohm.\n"
            "    0x6 = 48 ohm.\n"
            "    0x7 = 60 ohm.\n"
            "    _ else = Reserved.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_WODT_MASK] =
            "LMC Write OnDieTermination Mask Register\n"
            "System designers may desire to terminate DQ/DQS lines for\n"
            "higher-frequency DDR operations, especially on a multirank system.\n"
            "DDR3 DQ/DQS I/Os have built-in termination resistors that can be\n"
            "turned on or off by the controller, after meeting TAOND and TAOF\n"
            "timing requirements. Each rank has its own ODT pin that fans out\n"
            "to all of the memory parts in that DIMM. System designers may\n"
            "prefer different combinations of ODT ONs for write operations into\n"
            "different ranks. CNXXXX supports full programmability by way of\n"
            "the mask register below. Each rank position has its own 8-bit\n"
            "programmable field. When the controller does a write to that rank,\n"
            "it sets the 4 ODT pins to the mask pins below. For example, when\n"
            "doing a write into Rank0, a system designer may desire to terminate\n"
            "the lines with the resistor on DIMM0/Rank1. The mask WODT_D0_R0\n"
            "would then be {00000010}.\n"
            "CNXXXX drives the appropriate mask values on the ODT pins by\n"
            "default. If this feature is not required, write 0x0 in this\n"
            "register. When a given RANK is selected, the WODT mask for that\n"
            "RANK is used.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_PASR] =
            "Partial array self-refresh per rank. LMC writes this value to\n"
            "MR2[PASR] in the rank (i.e. DIMM0_CS0) DDR3 parts when selected\n"
            "during power-up/init, write-leveling, and, if\n"
            "LMC()_CONFIG[SREF_WITH_DLL] is set, self-refresh entry and exit\n"
            "instruction sequences. See LMC()_SEQ_CTL[SEQ_SEL,INIT_START] and\n"
            "LMC()_CONFIG[RANKMASK] and LMC()_RESET_CTL[DDR3PWARM,DDR3PSOFT].\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_ASR] =
            "Auto self-refresh per rank. LMC writes this value to MR2[ASR] in\n"
            "the rank (i.e. DIMM0_CS0) DDR3 parts when selected during\n"
            "power-up/init, write-leveling, and, if LMC()_CONFIG[SREF_WITH_DLL]\n"
            "is set, self-refresh entry and exit instruction sequences. See\n"
            "LMC()_SEQ_CTL[SEQ_SEL,INIT_START] and LMC()_CONFIG[RANKMASK] and\n"
            "LMC()_RESET_CTL [DDR3PWARM,DDR3PSOFT].\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_SRT] =
            "Self-refresh temperature range per rank. LMC writes this value to\n"
            "MR2[SRT] in the rank (i.e. DIMM0_CS0) DDR3 parts when selected\n"
            "during power-up/init, write-leveling, and, if\n"
            "LMC()_CONFIG[SREF_WITH_DLL] is set, self-refresh entry and exit\n"
            "instruction sequences. See LMC()_SEQ_CTL[SEQ_SEL,INIT_START] and\n"
            "LMC()_CONFIG[RANKMASK] and LMC()_RESET_CTL[DDR3PWARM,DDR3PSOFT].\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_RTT_WR] =
            "RTT_WR per rank. LMC writes this value to MR2[RTT_WR] in the rank\n"
            "(i.e. DIMM0_CS0) DDR3 parts when selected during power-up/init,\n"
            "write-leveling, and, if LMC()_CONFIG[SREF_WITH_DLL] is set,\n"
            "self-refresh entry and exit instruction sequences. See\n"
            "LMC()_SEQ_CTL[SEQ_SEL,INIT_START] and LMC()_CONFIG[RANKMASK] and\n"
            "LMC()_RESET_CTL[DDR3PWARM, DDR3PSOFT].\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_DIC] =
            "Output driver impedance control per rank. LMC writes this value\n"
            "to MR1[D.I.C.] in the rank (i.e. DIMM0_CS0) DDR3 parts when\n"
            "selected during power-up/init, write-leveling, and, if\n"
            "LMC()_CONFIG[SREF_WITH_DLL] is set, self-refresh entry and exit\n"
            "instruction sequences. See LMC()_SEQ_CTL[SEQ_SEL,INIT_START] and\n"
            "LMC()_CONFIG[RANKMASK] and LMC()_RESET_CTL[DDR3PWARM,DDR3PSOFT].\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_RTT_NOM] =
            "RTT_NOM per rank. LMC writes this value to MR1[RTT_NOM] in the\n"
            "rank (i.e. DIMM0_CS0) DDR3 parts when selected during\n"
            "power-up/init, write-leveling, and, if LMC()_CONFIG[SREF_WITH_DLL]\n"
            "is set, self-refresh entry and exit instruction sequences. See\n"
            "LMC()_SEQ_CTL[SEQ_SEL,INIT_START] and LMC()_CONFIG[RANKMASK] and\n"
            "LMC()_RESET_CTL[DDR3PWARM, DDR3PSOFT]. Per JEDEC DDR3\n"
            "specifications, if RTT_NOM is used during write operations, only\n"
            "values MR1[RTT_NOM] = 1 (RZQ/4), 2 (RZQ/2), or 3 (RZQ/6) are\n"
            "allowed. Otherwise, values MR1[RTT_NOM] = 4 (RZQ/12) and 5 (RZQ/8)\n"
            "are also allowed.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE1_DB_OUTPUT_IMPEDANCE] =
            "Host Interface DQ/DQS Output Driver Impedance control for DIMM0's\n"
            "Data Buffer. This is the default value used during Host Interface\n"
            "Write Leveling in LRDIMM environment, i.e.,\n"
            "LMC()_CONFIG[LRDIMM_ENA] = 1, LMC()_SEQ_CTL[SEQ_SEL] = 0x6.\n"
            "    0x0 = RZQ/6 (40 ohm).\n"
            "    0x1 = RZQ/7 (34 ohm).\n"
            "    0x2 = RZQ/5 (48 ohm).\n"
            "    0x3-0x7 = Reserved.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE2_RTT_PARK] =
            "RTT park value per rank.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE2_VREF_VALUE] =
            "VREF value per rank.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE2_VREF_RANGE] =
            "VREF range per rank.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    RANK#: Parameter can be different for each rank of a DIMM. This\n"
            "        specifies which rank the value is for. Rank must be\n"
            "        0-3. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_MODE2_VREFDQ_TRAIN_EN] =
            "Vref training mode enable, used for all ranks.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_RODT_CTL] =
            "RODT NCTL impedance control bits. This field controls ODT values\n"
            "during a memory read.\n"
            "    0x0 = No ODT.\n"
            "    0x1 = 20 ohm.\n"
            "    0x2 = 30 ohm.\n"
            "    0x3 = 40 ohm.\n"
            "    0x4 = 60 ohm.\n"
            "    0x5 = 120 ohm.\n"
            "    _ else = Reserved.\n"
            "In DDR4 mode:\n"
            "    0x0 = No ODT.\n"
            "    0x1 = 40 ohm.\n"
            "    0x2 = 60 ohm.\n"
            "    0x3 = 80 ohm.\n"
            "    0x4 = 120 ohm.\n"
            "    0x5 = 240 ohm.\n"
            "    0x6 = 34 ohm.\n"
            "    0x7 = 48 ohm.\n"
            "    _ else = Reserved.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_RANKS_RODT_MASK] =
            "LMC Read OnDieTermination Mask Register\n"
            "System designers may desire to terminate DQ/DQS lines for higher\n"
            "frequency DDR operations, especially on a multirank system. DDR3\n"
            "DQ/DQS I/Os have built-in termination resistors that can be turned\n"
            "on or off by the controller, after meeting TAOND and TAOF timing\n"
            "requirements.\n"
            "Each rank has its own ODT pin that fans out to all the memory\n"
            "parts in that DIMM. System designers may prefer different\n"
            "combinations of ODT ONs for read operations into different ranks.\n"
            "CNXXXX supports full programmability by way of the mask register\n"
            "below. Each rank position has its own 4-bit programmable field.\n"
            "When the controller does a read to that rank, it sets the 4 ODT\n"
            "pins to the MASK pins below. For example, when doing a read from\n"
            "Rank0, a system designer may desire to terminate the lines with\n"
            "the resistor on DIMM0/Rank1. The mask RODT_D0_R0 would then be {0010}.\n"
            "CNXXXX drives the appropriate mask values on the ODT pins by\n"
            "default. If this feature is not required, write 0x0 in this\n"
            "register. Note that, as per the JEDEC DDR3 specifications, the ODT\n"
            "pin for the rank that is being read should always be 0x0. When a\n"
            "given RANK is selected, the RODT mask for that rank is used.\n"
            "Parameters:\n"
            "    RANKS#: Specifies that this parameter only applies to DIMMs\n"
            "        with the supplied number of ranks. Support ranks is 1, 2,\n"
            "        or 4. Optional.\n"
            "    DIMMS#: Specifies that this parameter only applies when the\n"
            "        DIMMs per memory controller matches. Support number of\n"
            "        DIMMs is 1 or 2. Optional.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MIN_RTT_NOM_IDX] =
            "1=120ohms, 2=60ohms, 3=40ohms, 4=30ohms, 5=20ohms\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MAX_RTT_NOM_IDX] =
            "1=120ohms, 2=60ohms, 3=40ohms, 4=30ohms, 5=20ohms\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MIN_RODT_CTL] =
            "1=20ohms, 2=30ohms, 3=40ohms, 4=60ohms, 5=120ohms\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MAX_RODT_CTL] =
            "1=20ohms, 2=30ohms, 3=40ohms, 4=60ohms, 5=120ohms\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_CK_CTL] =
            "Drive strength control for DDR_CK_X_P, DDR_DIMMX_CSX_L,\n"
            "DDR_DIMMX_ODT_X drivers.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_CMD_CTL] =
            "Drive strength control for CMD/A/RESET_L/CKEX drivers.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_CTL_CTL] =
            "Drive strength control for ODT, etc. drivers.\n"
            "In DDR3 mode:\n"
            "    0x1 = 24 ohm.\n"
            "    0x2 = 26.67 ohm.\n"
            "    0x3 = 30 ohm.\n"
            "    0x4 = 34.3 ohm.\n"
            "    0x5 = 40 ohm.\n"
            "    0x6 = 48 ohm.\n"
            "    0x7 = 60 ohm.\n"
            "    else = Reserved.\n"
            "In DDR4 mode:\n"
            "    0x0 = Reserved.\n"
            "    0x1 = Reserved.\n"
            "    0x2 = 26 ohm.\n"
            "    0x3 = 30 ohm.\n"
            "    0x4 = 34 ohm.\n"
            "    0x5 = 40 ohm.\n"
            "    0x6 = 48 ohm.\n"
            "    else = Reserved.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MIN_CAS_LATENCY] =
            "Minimum allowed CAS Latency\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_OFFSET_EN] =
            "When set, LMC attempts to select the read-leveling setting that is\n"
            "LMC()_RLEVEL_CTL[OFFSET] settings earlier than the last passing\n"
            "read-leveling setting in the largest contiguous sequence of\n"
            "passing settings. When clear, or if the setting selected by\n"
            "LMC()_RLEVEL_CTL[OFFSET] did not pass, LMC selects the middle\n"
            "setting in the largest contiguous sequence of passing settings,\n"
            "rounding earlier when necessary.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_OFFSET] =
            "The offset used when LMC()_RLEVEL_CTL[OFFSET] is set.\n"
            "Parameters:\n"
            "   %s: This setting can by specified by DRAM type (UDIMM or RDIMM)\n"
            "       Different settings can be used for each, or the type can be\n"
            "       omitted to use the same setting for both.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMPUTE] =
            "Enables software interpretation of per-byte read delays using the\n"
            "measurements collected by the chip rather than completely relying\n"
            "on the automatically to determine the delays. 1=software\n"
            "computation is recommended since a more complete analysis is\n"
            "implemented in software.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMP_OFFSET] =
            "Set to 2 unless instructed differently by Cavium.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_DDR2T] =
            "Turn on the DDR 2T mode. 2-cycle window for CMD and address. This\n"
            "mode helps relieve setup time pressure on the address and command\n"
            "bus. Please refer to Micron's tech note tn_47_01 titled DDR2-533\n"
            "Memory Design Guide for Two DIMM Unbuffered Systems for physical\n"
            "details.\n"
            "Parameters:\n"
            "   %s: This setting can by specified by DRAM type (UDIMM or RDIMM)\n"
            "       Different settings can be used for each, or the type can be\n"
            "       omitted to use the same setting for both.\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_DISABLE_SEQUENTIAL_DELAY_CHECK] =
            "As result of the flyby topology prescribed in the JEDEC\n"
            "specifications the byte delays should maintain a consistent\n"
            "increasing or decreasing trend across the bytes on standard DIMMs.\n"
            "This setting can be used disable that check for unusual\n"
            "circumstances where the check is not useful.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MAXIMUM_ADJACENT_RLEVEL_DELAY_INCREMENT] =
            "An additional sequential delay check for the delays that result\n"
            "from the flyby topology. This value specifies the maximum\n"
            "difference between the delays of adjacent bytes.  A value of 0\n"
            "disables this check.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_PARITY] =
            "The parity input signal PAR_IN on each DIMM must be strapped high\n"
            "or low on the board.  This bit is programmed into\n"
            "LMC0_DIMM_CTL[PARITY] and it must be set to match the board\n"
            "strapping.  This signal is typically strapped low.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_FPRCH2] =
            "Front Porch Enable: When set, the turn-off time for the default\n"
            "DDR_DQ/DQS drivers is FPRCH2 CKs earlier.\n"
            "    0 = 0 CKs\n"
            "    1 = 1 CKs\n"
            "    2 = 2 CKs\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MODE32B] =
            "Enable 32-bit datapath mode. Set to 1 if only 32 DQ pins are\n"
            "used.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MEASURED_VREF] =
            "Use Measured VREF\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_DLL_WRITE_OFFSET] =
            "Supply a custom DLL write offset\n"
            "Parameters:\n"
            "    BYTE#: Byte lane to apply the parameter to (0-8).\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_DLL_READ_OFFSET] =
            "Supply a custom DLL read offset\n"
            "Parameters:\n"
            "    BYTE#: Byte lane to apply the parameter to (0-8).\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* High level DRAM options */
    [BDK_CONFIG_DRAM_VERBOSE] =
            "Choose the debug logging level used during DRAM initialization.\n"
            "Zero disables debug logging. The possible debug levels are:\n"
            "    0: Off, no logging\n"
            "    1: Logging of DRAM initialization at a normal detail level\n"
            "    2: Logging of DRAM initialization at FAE detail level\n"
            "    3: Logging of DRAM initialization at TME detail level\n"
            "    4: Logging of DRAM initialization at DEV detail level\n"
            "    5: Logging of DRAM initialization at DEV2 detail level\n"
            "    6: Logging of DRAM initialization at DEV3 detail level\n"
            "    7: Logging of DRAM initialization at DEV4 detail level\n"
            "Add in the following for special trace features.\n"
            "   16: Trace specialized DRAM controller sequences.\n"
            "   32: Trace every DRAM controller register write.",
    [BDK_CONFIG_DRAM_BOOT_TEST] =
            "Run a short DRAM test after DRAM is initialized as quick check\n"
            "for functionality. This is normally not needed required. Boards\n"
            "with poor DRAM power supplies may use this to detect failures\n"
            "during boot. This should be used in combination with the watchdog\n"
            "timer.",
    [BDK_CONFIG_DRAM_CONFIG_GPIO] =
            "The DRAM initialization code has the ability to toggle a GPIO to\n"
            "signal when it is running. Boards may need to mux TWSI access\n"
            "between a BMC and the SOC so the BMC can monitor DIMM temperatures\n"
            "and health. This GPIO will be driven high when the SOC may read\n"
            "from the SPDs on the DIMMs. When driven low, another device (BMC)\n"
            "may takeover the TWSI connections to the DIMMS. The default value\n"
            "(-1) disables this feature.",
    [BDK_CONFIG_DRAM_SCRAMBLE] =
            "Scramble DRAM to prevent snooping. This options programs the DRAM\n"
            "controller to scramble addresses and data with random values.\n"
            "Supported values:\n"
            "    0: No scrambling\n"
            "    1: Always scramble\n"
            "    2: Scramble only when using trusted boot (Default)",
    /* USB */
    [BDK_CONFIG_USB_PWR_GPIO] =
            "Specify a on-chip GPIO used to control power for a USB port. When\n"
            "set, the USB host controller will toggle the GPIO automatically\n"
            "during USB reset events. The default value assumes the SOC has no\n"
            "control of the USB power and it is always on.",
    [BDK_CONFIG_USB_PWR_GPIO_POLARITY] =
            "Specify the polarity of a on-chip GPIO used to control power for\n"
            "a USB port. The GPIO used is specified by USB-PWR-GPIO. Setting this\n"
            "GPIO low. The default value drives the GPIO high.",
     [BDK_CONFIG_USB_REFCLK_SRC] =
    	     "Specify reference clock source for SuperSpeed and HighSpeed PLL.\n"
             "Possible sources:\n"
             " USB_REF_CLK pin\n"
             "Additional sources for CN81XX/CN80XX chips\n"
             " DLMC_REF_CLK0 pin\n"
             " DLMC_REF_CLK1 pin\n"
             " PLL_REF_CLK\n"
             "Clock used by usb needs to run at 100MHz frequency except PLL_REF_CLK\n"
             "which requires 50MHz frequency.\n"
             "Encoding:\n"
             "0 - SS(USB_REF_CLK)   HS(USB_REF_CLK)\n"
             "1 - SS(DLMC_REF_CLK0) HS(DLMC_REF_CLK0)\n"
             "2 - SS(DLMC_REF_CLK1) HS(DLMC_REF_CLK1)\n"
             "3 - SS(USB_REF_CLK)   HS(PLL_REF_CLK)\n"
             "4 - SS(DLMC_REF_CLK0) HS(PLL_REF_CLK)\n"
             "5 - SS(DLMC_REF_CLK1) HS(PLL_REF_CLK)\n"
             "The default is 0 : USB_REF_CLK.",
    /* Nitrox reset - For CN88XX SC and SNT part. High drives Nitrox DC_OK high */
    [BDK_CONFIG_NITROX_GPIO] =
            "CN88XX SC and SNT parts have an errata where a GPIO is used to\n"
            "toggle DC_OK. For boards with SC and SNT parts, a GPIO must be wired\n"
            "per errata description.",
    /* How EYE diagrams are captured from a QLM/DLM */
    [BDK_CONFIG_EYE_ZEROS] =
            "Number of reading with no errors to signal the start of an\n"
            "eye. The default value should be good for most cases.",
    [BDK_CONFIG_EYE_SAMPLE_TIME] =
            "Time to sample at each location in microseconds. The default\n"
            "value should be good for most cases.",
    [BDK_CONFIG_EYE_SETTLE_TIME] =
            "Time to settle after each movement in microseconds. The\n"
            "default value should be good for most cases.",
    /* SGPIO configuration */
    [BDK_CONFIG_SGPIO_SCLOCK_FREQ] =
            "Reference clock in Hz. CN88XX drives data on rising edges of this\n"
            "clock, and the target latches data on the falling edges of this\n"
            "clock. On reset CN88XX tristates SGPIO_SCLK. When not exchanging\n"
            "a bit stream CN88XX keeps SGPIO_SCLK low.\n"
            "  Min: 128 Hz\n"
            "  Max: 100 kHz",
    [BDK_CONFIG_SGPIO_PIN_POWER] =
            "Output pin number for SGPIO controller power control.",
    [BDK_CONFIG_SGPIO_PIN_SCLOCK] =
            "Output pin number for SGPIO SCLOCK signal.",
    [BDK_CONFIG_SGPIO_PIN_SLOAD] =
            "Output pin number for SGPIO SLOAD signal.",
    [BDK_CONFIG_SGPIO_PIN_SDATAOUT] =
            "Output pin number for SGPIO SDATAOUT[n] signal. n = 0..3.",
    /* VRM temperature throttling */
    [BDK_CONFIG_VRM_TEMP_TRIP] =
            "Temperature where THERMAL_TRIP_N is asserted. When the chip reaches\n"
            "this temperature THERMAL_TRIP_N will assert, signalling the board\n"
            "to emergency power off. The default value is the Cavium recommended\n"
            "maximum temperature of the chip. Values between 0 and 110 degrees\n"
            "Celsius.",
    [BDK_CONFIG_VRM_TEMP_HIGH] =
            "Temperature where maximum throttling is applied to the chip. Chip\n"
            "performance will be greatly reduced to keep the temperature below\n"
            "thermal trip (VRM-TEMP-TRIP). The default value is the Cavium\n"
            "recommended maximum operating temperature of the chip. Values\n"
            "between 0 and 110 degrees Celsius.",
    [BDK_CONFIG_VRM_TEMP_LOW] =
            "Temperature where minimum throttling is applied to the chip. Chip\n"
            "performance will be maximized at or below this temperature. The\n"
            "throttling level will be set to VRM-THROTTLE-NORMAL. The default\n"
            "value is the Cavium recommended operating temperature of the chip.\n"
            "Values between 0 and 110 degrees Celsius.",
    [BDK_CONFIG_VRM_THROTTLE_NORMAL] =
            "Throttle level of the chip when operating normally. Temperatures\n"
            "at or below VRM-TEMP-LOW will use this throttling level. The default\n"
            "level (70%), allows good performance while still reducing power under\n"
            "heavy loads. Value is a percentage between 1 and 100.",
    [BDK_CONFIG_VRM_THROTTLE_THERM] =
            "Throttle level of the chip is overheating. Temperatures at or\n"
            "above VRM-TEMP-HIGH will use this throttling level. The default\n"
            "level (5%), allows for forward progress while still reducing power.\n"
            "Value is a percentage between 1 and 100. Setting a value of 100\n"
            "disables dynamic throttling (not recommended).",
    /* Generic GPIO, unrelated to a specific block */
    [BDK_CONFIG_GPIO_PIN_SELECT] =
            "Internal source for GPIO pins. The enumeration GPIO_PIN_SEL_E\n"
            "details the possible internal sources for GPIO pins in the chip.\n"
            "The value of this setting is the numeric value from the GPIO_PIN_SEL_E\n"
            "enumeration. The default value(-1) leaves the pin at the hardware\n"
            "default, which is to connect the pin to the GPIO block for manual\n"
            "control.\n"
            "Parameters:\n"
            "    GPIO#: Which GPIO pin to configure.\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_GPIO_POLARITY] =
            "Set the polarity of GPIO pins. GPIO pins are normally high=1 and\n"
            "low=0. Setting this configuration item to '1' inverts this, so\n"
            "high=0 and low=1. The inversion applies to both input and output.\n"
            "The default value of '0' configures high=1 and low=0.\n"
            "Parameters:\n"
            "    GPIO#: Which GPIO pin to configure.\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* PBUS */
    [BDK_CONFIG_PBUS_CFG] =
            "Configure a PBUS region. The encoding of this value is the exact\n"
            "register contents of PBUS_REGX_CFG. Note that the base is\n"
            "overwritten by the BDK to fix addressing in the code.\n"
            "Parameters:\n"
            "    REGION#: Which PBUS region to configure.\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_PBUS_TIM] =
            "Configure a PBUS region timing. The encoding of this value is the\n"
            "exact register contents of PBUS_REGX_TIM.\n"
            "Parameters:\n"
            "    REGION#: Which PBUS region to configure.\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* Trusted boot information */
    [BDK_CONFIG_TRUST_CSIB] =
            "Binary blob containing the TBL1FW CSIB header use to boot. If boot\n"
            "was non-trusted, this parameter will not be in the device tree.\n",
    [BDK_CONFIG_TRUST_ROT_ADDR] =
            "Address of the Root of Trust public key (ROT). This will be zero for\n"
            "non-trusted boot, or an address in secure space when trusted boot.\n"
            "This public key is copied from the trusted CSIB, so it is a coordinate\n"
            "pair (Qx,Qy) of 256-bit integers in little-endian format.\n",
    [BDK_CONFIG_TRUST_BSSK_ADDR] =
            "If boot was trusted and FUSF_HUK is non-zero, this contains the\n"
            "address in secure space for the BSSK. The BSSK is derived from the\n"
            "HUK and bytes 32- 47 of the CSIB.\n"
    };
    return help[cfg_item];
}

