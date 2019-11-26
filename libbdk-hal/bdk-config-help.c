/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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
            "should normally not be used.",
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
    [BDK_CONFIG_DEVICES] =
            "Specify devices external to the chip that can't be probed through\n"
            "PCIe or USB. Generally these are devices connect to TWSI or\n"
            "GPIOs. The format of this is list of strings where each string\n"
            "represents an external device. The format of each string varies\n"
            "based on the device. See the BDK manual for the details.",
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
            "ports are enabled.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    BGX#: Parameter can be different for BGX/CGX. Optional.\n"
            "    PORT#: Parameter can be different for each BGX/CGX port. Optional.",
    [BDK_CONFIG_NETWORK_LED_LINK_SLOW] =
            "Define a LED to light when the CGX port is up, but running at\n"
            "less than its maximum speed.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.\n"
            "    PORT#: Parameter can be different for each CGX port. Optional.",
    [BDK_CONFIG_NETWORK_LED_LINK_FAST] =
            "Define a LED to light when the CGX port is up and running at\n"
            "its maximum speed.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.\n"
            "    PORT#: Parameter can be different for each CGX port. Optional.",
    [BDK_CONFIG_NETWORK_LED_ACTIVITY] =
            "Define a LED to light when the CGX is active\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.\n"
            "    PORT#: Parameter can be different for each CGX port. Optional.",
    [BDK_CONFIG_NETWORK_LED_ID] =
            "Define a LED to light when the CGX request identification\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.\n"
            "    PORT#: Parameter can be different for each CGX port. Optional.",
    [BDK_CONFIG_NETWORK_PORT] =
            "Define a network port connected to the CGX\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.\n"
            "    PORT#: Parameter can be different for each CGX port. Optional.",
    [BDK_CONFIG_NETWORK_FLAGS] =
            "Optional mode flags for a network port. These can be ORed together\n"
            "to creates combinations:\n"
            "    0: No flags (Default)\n"
            "    1: Use FEC\n"
            "    2: Use RS-FEC\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.\n"
            "    PORT#: Parameter can be different for each CGX port. Optional.",
    [BDK_CONFIG_NETWORK_LANE_ORDER] =
            "Lane order of QLM/DLM lanes connected to a network port. Each of the 4\n"
            "digit (in hex) corresponds to a DLM/QLM lane. Lane 0 is the least\n"
            "significant digit, while lane 3 is the most significant digit. The\n"
            "default value of 0x3210 represents non-swizzled lanes. For network ports\n"
            "spanning two DLMs, the first DLM is lane 0 and 1, the second is lane\n"
            "2 and 3.\n"
            "Examples:\n"
            "    0x3210: Default connection, lanes in order\n"
            "    0x0123: All lanes are swizzled. 0->3, 1->2, 2->1, 3->0\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    CGX#: Parameter can be different for CGX. Optional.",
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
    [BDK_CONFIG_BOOT_DEVICE] =
            "Device used to boot, string representation of RST_BOOT_METHOD_E.\n"
            "This is filled by the BDK with the device used to boot",
    [BDK_CONFIG_TRACE] =
            "BDK trace level. This is a bitmask of the enumeration defined in\n"
            "bdk-warn.h. Each bit turns on tracing of a specific BDK\n"
            "component.",
    /* Chip feature items */
    [BDK_CONFIG_PCIE_EA] =
            "Determine if internal PCIe ECAMs support Enhanced Allocation(EA):\n"
            "    0 = Enhanced Allocation is not supported\n"
            "    1 = Enhanced Allocation is supported",
    [BDK_CONFIG_PCIE_ORDERING] =
            "Enforcing stronger PCIe ordering. Use this option if a PCIe card\n"
            "is having compatibility issues.\n"
            "    0 = Don't wait for commit, default for best performance.\n"
            "    1 = Wait for commit, use conservative ordering.",
    [BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR] =
            "Specifies the preset request vector (PCIERCX_GEN3_EQ_CTL/PCIERCX_CFG554[PRV]).\n"
            "Requesting of presets during the initial part of the EQ master phase.\n"
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
    [BDK_CONFIG_PCIE_GEN2_DEEMPHASIS] =
            "Specifies the level of deemphasis on the downstream device for PCIe Gen2 (5GT/s).\n"
            "    0 = -6 dB (default)\n"
            "    1 = -3.5 dB\n"
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
    [BDK_CONFIG_PCIE_TX_PRESET_OVERRIDE_VECTOR] =
            "PCIe Transmit Prefix Value to use only when tap override is used\n"
            "(ERRATA 36412). This is for GEN3 only and is a vector of transmit presets\n"
            "to used for transmit equalization.  Normally equalization sets the value, but that\n"
            "is disabled when EN_TX_DRV set. This is only for CN9XXX A0 parts.\n"
            "Select a vector such as 0x393. There are 11 possible presets, up to 0x7FF,\n"
            "but typically not all of the presets are used.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_ENDPOINT_TX_PRESET_OVERRIDE] =
            "PCIE Endpoint Mode Transmit Preset Value to Use ONLY when tap override\n"
            "is used (ERRATA 36412). This can be used for GEN2 selection and also\n"
            "GEN3 selection.  GEN1 is always fixed. GEN2 uses preset 0 for -6 db,\n"
            "and preset 1 for -3.5 db de-emphasis. GEN3 can be preset 0 thru 10.\n"
            "This preset is not a vector, but an integer from 0 to 10.\n"
            "    GEN1 - do nothing, this value ignored\n"
            "    GEN2 - set to 0 for -6 db\n"
            "    GEN2 - set to 1 for -3.5 db\n"
            "    GEN3 - set to 0 to 10\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_IDLE_REFSET_VALUE] =
            "Configure the electrical idle refset detect value.  This specifies the\n"
            "voltage swing at the input of the QLM receiver. A signal level less than this\n"
            "value is considered electrical idle.  Testing done in the lab showed that\n"
            "slower parts required an idle detect of 6. However, some other testing\n"
            "showed a value of 4 produced improved results. It depends on the channel\n"
            "loss obviously, since these values represent millivolts. This value should\n"
            "be used on platforms that will operate in EP/RC mode.\n"
            "   0 = 23.0 mV\n"
            "   1 = 27.4 mV\n"
            "   2 = 31.8 mV\n"
            "   3 = 36.2 mV\n"
            "   4 = 40.6 mV\n"
            "   5 = 45.0 mV\n"
            "   6 = 49.4 mV\n"
            "   7 = 53.8 mV\n"
            "   8 = 58.2 mV\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_RC_OVERRIDE_DETECT] =
            "Configure a forced rx detect for a given PCIe port. Setting this is for\n"
            "lab debug or boards that are not within PCIe compliance in the rx detect.\n"
            "Setting this field to '1' for a given port will select all lanes of that\n"
            "port to be valid so that the rx detect is ignored. This ultimately sets the\n"
            "register bits within the GSERNX_LANEX_TX_RXD_BCFG register.\n"
            "Parameters: \n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            " PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional. ",
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
            "SKU for the chip. This is determined by early code and\n"
            "passed to later software for display. This should not be set in\n"
            "the input device tree, it will be ignored.",
    [BDK_CONFIG_CHIP_SERIAL] =
            "Serial number for the chip. This is determined by early\n"
            "code and passed to later software for display. This should not be\n"
            "set in the input device tree, it will be ignored.",
    [BDK_CONFIG_CHIP_UNIQUE_ID] =
            "Unique ID for the chip. This is determined by early\n"
            "code and passed to later software for display. This should not be\n"
            "set in the input device tree, it will be ignored.",
    /* Options for CN9XXX PCIe EP config space */
    [BDK_CONFIG_PCIE_EP_NUM_PFS] =
            "Number of physical functions (PFs) to expose on a PCIe endpoint.\n"
            "Valid values are 1-16. Defaults to 1.\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_ID] =
            "PCIe device ID for endpoints.\n"
            "Defaults to 0xb200177d, see PCIEEPX_ID.\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_REV] =
            "PCIe device ID for endpoints.\n"
            "Defaults to 0x0b800000, see PCIEEPX_REV.\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_SUBSYS] =
            "PCIe subsystem for endpoints.\n"
            "Defaults to 0xb200177d, see PCIEEPX_SUBSYS.\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_BAR_SIZE] =
            "PCIe endpoint BAR size as a power of 2. A value of zero disables the BAR.\n"
            "BAR0 defaults to 23 bits, or 8MB\n"
            "BAR2 defaults to 28 bits, or 256MB\n"
            "BAR4 defaults to 26 bits, or 64MB\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    BAR#: Must be BAR0, BAR2, or BAR4.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_ROM_SIZE] =
            "PCIe endpoint expansion ROM size as a power of 2. A value of zero disables the ROM.\n"
            "Defaults to 0, disabled\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_NUM_VFS] =
            "Number of virtual functions (VFs) to expose on a PCIe endpoint.\n"
            "Valid values are 0-240. Defaults to 128.\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_SRIOV_DEV] =
            "PCIe SRIOV device ID for endpoints.\n"
            "Defaults to 0xb203, see PCIEEPX_SRIOV_DEV.\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    [BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE] =
            "PCIe endpoint VBAR size as a power of 2. A value of zero disables the BAR.\n"
            "BAR0 defaults to 20 bits, or 1MB\n"
            "BAR2 defaults to disabled, recommended\n"
            "BAR4 defaults to disabled, recommended\n"
            "Only applies to CN9XXX.\n"
            "Parameters:\n"
            "    BAR#: Must be BAR0, BAR2, or BAR4.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    PORT#: Parameter can be different for PCIe port. This specifies\n"
            "        which PCIe RC port the value is for. Optional.",
    /* QLM/DLM related config */
    [BDK_CONFIG_QLM_AUTO_CONFIG] =
            "For evaluation boards, query the MCU for QLM/DLM setup\n"
            "information. The MCU supplies a TWSI protocol for the SOC to\n"
            "query the modules plugged in and automatically set the QLMs or\n"
            "DLMs to the correct mode. This should only be enabled(1) on\n"
            "EBB8XXX boards. Other boards should have it disabled(0).",
    [BDK_CONFIG_QLM_VOLTAGE] =
            "The voltage, VDDA_GSER, supplied to the SERDES by the board in\n"
            "millivolts. Some SERDES tuning is based on the voltage supplyed\n"
            "to the chip. The default value matches the HRM recommended value.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_QLM_MODE] =
            "Set the mode of a QLM/DLM. The possible mode strings are:\n"
            "    DISABLED     # CN83XX: All             CN81XX: All         CN80XX: All         CN96XX: All\n"
            "    PCIE_X1      #                                             CN80XX: DLM0\n"
            "    PCIE_X2      # CN83XX: DLM4,5          CN81XX: DLM0,2,3    CN80XX: DLM0,2,3    CN96XX: DLM4,5\n"
            "    PCIE_X4      # CN83XX: QLM0-3,DLM5     CN81XX: DLM0,2      CN80XX: DLM2        CN96XX: QLM0,1,2,3,6,7, DLM4-5\n"
            "    PCIE_X8      # CN83XX: QLM0,2                                                  CN96XX: QLM0-1,6-7\n"
            "    PCIE_X16     #                                                                 CN96XX: QLM0-3\n"
            "    PCIE_X4-EP   #                                                                 CN96XX: QLM0,3,6\n"
            "    PCIE_X8-EP   #                                                                 CN96XX: QLM0-1,6-7\n"
            "    PCIE_X16-EP  #                                                                 CN96XX: QLM0-3\n"
            "    SATA         # CN83XX: DLM4,5          CN81XX: DLM3        CN80XX: DLM3\n"
            "    SGMII        # CN83XX: QLM2-6          CN81XX: DLM0-3      CN80XX: DLM0-3      CN96XX: QLM3-7\n"
            "    1G_X         # CN83XX: QLM2-6          CN81XX: DLM0-3      CN80XX: DLM0-3      CN96XX: QLM3-7\n"
            "    QSGMII       # CN83XX: QLM2-4,DLM4,5   CN81XX: DLM0-3      CN80XX: DLM0-3      CN96XX: QLM3,6,7,DLM4,5\n"
            "    XAUI         # CN83XX: QLM3,4          CN81XX: DLM0,2      CN80XX: DLM2        CN96XX: QLM3,6,7\n"
            "    RXAUI        # CN83XX: QLM3-6          CN81XX: DLM0-3      CN80XX: DLM2        CN96XX: QLM3-7\n"
            "    XFI          # CN83XX: QLM2-6          CN81XX: DLM0-3      CN80XX: DLM0-3      CN96XX: QLM3-7\n"
            "    SFI          #                                                                 CN96XX: QLM3-7\n"
            "    XLAUI        # CN83XX: QLM3,4          CN81XX: DLM0,2      CN80XX: DLM2        CN96XX: QLM3,6,7\n"
            "    XLAUI_C2M    #                                                                 CN96XX: QLM3,6,7\n"
            "    10G_KR       # CN83XX: QLM3-6          CN81XX: DLM0-3      CN80XX: DLM0-3      CN96XX: QLM3-7\n"
            "    40G_CR4      # CN83XX: QLM3,4,DLM5     CN81XX: DLM0,2      CN80XX: DLM2        CN96XX: QLM3,6,7\n"
            "    40G_KR4      # CN83XX: QLM3,4,DLM5     CN81XX: DLM0,2      CN80XX: DLM2        CN96XX: QLM3,6,7\n"
            "    20GAUI_C2C   #                                                                 CN96XX: QLM3-7\n"
            "    25GAUI_C2C   #                                                                 CN96XX: QLM3-7\n"
            "    25GAUI_C2M   #                                                                 CN96XX: QLM3-7\n"
            "    25G_CR       #                                                                 CN96XX: QLM3-7\n"
            "    25G_KR       #                                                                 CN96XX: QLM3-7\n"
            "    25GAUI_2_C2C #                                                                 CN96XX: QLM3-7\n"
            "    40GAUI_2_C2C #                                                                 CN96XX: QLM3-7\n"
            "    50GAUI_2_C2C #                                                                 CN96XX: QLM3-7\n"
            "    50GAUI_2_C2M #                                                                 CN96XX: QLM3-7\n"
            "    50G_CR2      #                                                                 CN96XX: QLM3-7\n"
            "    50G_KR2      #                                                                 CN96XX: QLM3-7\n"
            "    50GAUI_4_C2C #                                                                 CN96XX: QLM3,6,7\n"
            "    80GAUI_4_C2C #                                                                 CN96XX: QLM3,6,7\n"
            "    CAUI_4_C2C   #                                                                 CN96XX: QLM3,6,7\n"
            "    CAUI_4_C2M   #                                                                 CN96XX: QLM3,6,7\n"
            "    100G_CR4     #                                                                 CN96XX: QLM3-7\n"
            "    100G_KR4     #                                                                 CN96XX: QLM3-7\n"
            "    USXGMII_4X1  #                                                                 CN96XX: QLM3,6,7,DLM4,5\n"
            "    USXGMII_2X1  #                                                                 CN96XX: QLM3,6,7,DLM4,5\n"
            "    USXGMII_1X1  #                                                                 CN96XX: QLM3,6,7,DLM4,5\n"
            "Notes:\n"
            "    1) For protocols spanning multiple QLM/DLM, only specify the lowest\n"
            "        DLM/QLM. The other DLM/QLM will automatically be configured. This\n"
            "        note applies to QLM-FREQ QLM-CLK, and QLM-CLK-TERM also.\n"
            "    2) For CN8XXX, PCIe EP mode is specified by strapping. Don't add\n"
            "        entries for these QLM/DLM here.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_FREQ] =
            "Set the speed of a QLM/DLM in Mhz. The possible speeds are:\n"
            "    1250 # Networking SGMII,1G_X\n"
            "    1500 # SATA Gen1\n"
            "    2500 # PCIe Gen1, Networking SGMII\n"
            "    3000 # SATA Gen2\n"
            "    3125 # Networking XAUI\n"
            "    5000 # PCIe Gen2, Networking QSGMII\n"
            "    6000 # SATA Gen3\n"
            "    6250 # Networking XAUI,RXAUI\n"
            "    8000 # PCIe Gen3\n"
            "   10312 # Networking XFI,XLAUI,10G_KR,40G_CR4,40G_KR4\n"
            "   12890 # Networking 25GAUI_2, 50GAUI_4\n"
            "   16000 # PCIe Gen4 (CN9XXX)\n"
            "   20625 # Networking 20GAUI, 40GAUI_2, 80GAUI_4, USXGMII (CN9XXX)\n"
            "   25781 # Networking (CN9XXX)\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_CLK] =
            "Set the source of the QLM/DLM reference clock:\n"
            "    0 = Common clock 0 (CN9XXX 100 Mhz No SSC)\n"
            "    1 = Common clock 1 (CN9XXX 100 Mhz SSC)\n"
            "    2 = QLM/DLM external reference\n"
            "    3 = Common clock 2 (CN9XXX 156.25 Mhz)\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.",
    [BDK_CONFIG_QLM_CLK_TERM] =
            "Set the QLM/DLM reference clock termination, not used for CN8XXX:\n"
            "   -1 = No clock, powered down (default)\n"
            "    0 = No termination\n"
            "    1 = LVPECL termination\n"
            "    2 = Reserved\n"
            "    3 = HCSL termination\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_SWING] =
            "Setting of GSERX_LANEX_TX_CFG_0[CFG_TX_SWING] for the QLM/DLM. This\n"
            "should only be used for QLMs or DLMs used for BGX and CCPI not using KR\n"
            "training.\n"
            "NOTE: This setting only apply to CN8XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_PREMPTAP] =
            "Setting of GSERX_LANEX_TX_PRE_EMPHASIS[CFG_TX_PREMPTAP] for the\n"
            "QLM/DLM. This should only be used for QLMs or DLMs used for BGX and CCPI not\n"
            "using KR training. CFG_TX_PREMPTAP:\n"
            "    Bits[8:5] = Tx Post Tap; Bits[3:0] = Tx Pre Tap\n"
            "NOTE: This setting only apply to CN8XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_GAIN] =
            "Setting of GSERX_LANEX_TX_CFG_3[PCS_SDS_TX_GAIN] for the QLM/DLM. This\n"
            "should only be used for QLMs or DLMs used for BGX and CCPI not using KR\n"
            "training.\n"
            "NOTE: This setting only apply to CN8XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_VBOOST] =
            "Setting of GSERX_LANEX_TX_CFG_3[CFG_TX_VBOOST_EN] for the QLM/DLM. This\n"
            "should only be used for QLMs or DLMs used for BGX and CCPI not using KR\n"
            "training.\n"
            "NOTE: This setting only apply to CN8XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_CHANNEL_LOSS] =
            "The insertion loss at Nyquist rate (e.g. 5.125Ghz for XFI/XLAUI) in\n"
            "dB for the RX channel should be passed into the channel loss\n"
            "attribute. For CN8XXX, this attribute is used for XFI/10GBASE-KR,\n"
            "XLAUI/40GBASE-KR4, and CCPI. If no channel loss attribute is\n"
            "provided the default value assumes a loss of greater than 10dB\n"
            "for networking (long channel) and less than 10dB (short channel)\n"
            "for CCPI. This matches the most common usage.\n"
            "NOTE: This setting only apply to CN8XXX.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_MAIN] =
            "Transmitter Main (C0) equalizer tap coefficient value.  Programs\n"
            "the SerDes transmitter Main tap. Valid range is 24 to 48.\n"
            "This can only be used for QLMs or DLMs configured for Networking.\n"
            "NOTE: This setting only applies to CN9XXX.\n"
            "Parameters:\n"
            "    <MODE>: DLM/QLM mode string from QLM-MODE. Optional.\n"
            "    <FREQ>: DLM/QLM frequency from QLM-FREQ. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_PRE] =
            "Transmitter Pre (C-1) equalizer tap coefficient value.  Programs the\n"
            "SerDes transmitter Pre tap. Valid range is 0 to 16.\n"
            "This can only be used for QLMs or DLMs configured for Networking.\n"
            "NOTE: This setting only applies to CN9XXX.\n"
            "Parameters:\n"
            "    <MODE>: DLM/QLM mode string from QLM-MODE. Optional.\n"
            "    <FREQ>: DLM/QLM frequency from QLM-FREQ. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_POST] =
            "Transmitter Post (C+1) equalizer tap coefficient value.  Programs\n"
            "the SerDes transmitter Post tap. Valid range is 0 to 16.\n"
            "This can only be used for QLMs or DLMs configured for Networking.\n"
            "NOTE: This setting only applies to CN9XXX.\n"
            "Parameters:\n"
            "    <MODE>: DLM/QLM mode string from QLM-MODE. Optional.\n"
            "    <FREQ>: DLM/QLM frequency from QLM-FREQ. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_TX_BS] =
            "Tx bias/swing selection.  This can only be used for QLMs or DLMs\n"
            "configured in PCIe mode. Typical values would be:\n"
            "    52 = Nominal 1.2V p-p transmit amplitude\n"
            "    42 = Nominal 1.0V p-p transmit amplitude\n"
            "    22 = Nominal 0.6V p-p transmit amplitude\n"
            "NOTE: This setting only applies to CN9XXX.\n"
            "Parameters:\n"
            "    <MODE>: DLM/QLM mode string from QLM-MODE. Optional.\n"
            "    <FREQ>: DLM/QLM frequency from QLM-FREQ. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_RX_PREVGA_GN_ADAPT] =
            "Controls whether the GSERN preVGA gain is initially adapted.  This\n"
            "can only be used for QLMs or DLMs configured in 20.625Gb/s modes.\n"
            "NOTE: This setting only applies to CN9XXX A0 and B0.\n"
            "-1 - S/W default is selected. (default)\n"
            " 0 - PreVGA gain is NOT adapted. Pre-VGA gain override value used.\n"
            " 1 - PreVGA gain is initially adapted.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_TUNING_RX_PREVGA_GN_OVRD] =
            "Sets the GSERN prevga gain override value.  This can only be used\n"
            "for QLMs or DLMs configured in 20.625Gb/s modes.\n"
            "NOTE: This setting only applies to CN9XXX A0 and B0.\n"
            "    -1 - S/W default is selected. (default)\n"
            "    Valid Range: 0 to 7\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_LANE_RX_POLARITY] =
            "Set the GSER lane Rx polarity\n"
            "NOTE: This setting only applies to CN9XXX.\n"
            "0 - Normal polarity. Positive differential pair signal connected\n"
            "   to link partner's positive signal. (Default)\n"
            "1 - Inverted polarity. Positive differential pair signal connected\n"
            "   to link partner's negative signal.\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_LANE_TX_POLARITY] =
            "Set the GSER lane Tx polarity\n"
            "NOTE: This setting only applies to CN9XXX.\n"
            "0 - Normal polarity. Positive differential pair signal connected\n"
            "   to link partner's positive signal. (Default)\n"
            "1 - Inverted polarity. Positive differential pair signal connected\n"
            "   to link partner's negative signal\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    [BDK_CONFIG_QLM_RX_ADAPTATION] =
            "Perform (or do not perform) GSER RX adaptation\n"
            "NOTE: This setting only applies to CN9XXX DLM/QLM configured for Ethernet.\n"
            "0 - Do not perform RX adaptation.\n"
            "1 - Perform RX adaptation. (Default)\n"
            "Parameters:\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.\n"
            "    QLM#: Parameter can be different for each DLM/QLM. Optional.\n"
            "    LANE#: Parameter can be different for each DLM/QLM lane. Optional.",
    /* DRAM configuration options */
    [BDK_CONFIG_DDR_SPEED] =
            "Speed grade to use for DRAM in MT/s. Hardware may adjust this value\n"
            "slightly to improve DRAM stability, so scope measurements may not\n"
            "exactly match the frequency with MT/s. The supported speed\n"
            "grades are:\n"
            "    CN8XXX                                 CN9XXX\n"
            "       0 (auto-set from SPD contents)         0 (auto-set from SPD contents)\n"
            "     666 MT/s (DDR3 only)                  1600 MT/s\n"
            "     800 MT/s (DDR3 only)                  1866 MT/s\n"
            "    1066 MT/s (DDR3 only)                  2133 MT/s\n"
            "    1333 MT/s (DDR3 only)                  2400 MT/s\n"
            "    1600 MT/s                              2666 MT/s\n"
            "    1866 MT/s                              2933 MT/s\n"
            "    2133 MT/s (DDR4 only)                  3200 MT/s\n"
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
            "    CN8XXX                     CN9XXX\n"
            "    0x1 = 24 ohm.              0x1 = 20 ohm.\n"
            "    0x2 = 26.67 ohm.           0x2 = 22 ohm.\n"
            "    0x3 = 30 ohm.              0x3 = 25 ohm.\n"
            "    0x4 = 34.3 ohm.            0x4 = 29 ohm.\n"
            "    0x5 = 40 ohm.              0x5 = 34 ohm.\n"
            "    0x6 = 48 ohm.              0x6 = 40 ohm.\n"
            "    0x7 = 60 ohm.              0x7 = 50 ohm.\n"
            "    _ else = Reserved.         _ else = Reserved.\n"
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
            "   DDR3                DDR4\n"
            "   0x0 = ODT off.      0x0 = ODT off.\n"
            "   0x1 = 60 ohm.       0x1 = 120 ohm.\n"
            "   0x2 = 120 ohm.      0x2 = 240 ohm.\n"
            "   _ else = Reserved   0x3 = Hi-Z.\n"
            "                       0x4 = 80 ohm.\n"
            "                       _ else = Reserved\n"
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
            "    0x0 = 34 ohms.\n"
            "    0x1 = 48 ohms.\n"
            "    _ else = Reserved\n"
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
            "   DDR3                    DDR4\n"
            "   0x1 = 60 ohms.          0x1 = 60 ohms.\n"
            "   0x2 = 120 ohms.         0x2 = 120 ohms.\n"
            "   0x3 = 40 ohms.          0x3 = 40 ohms.\n"
            "   0x4 = 20 ohms.          0x4 = 240 ohms.\n"
            "   0x5 = 30 ohms.          0x5 = 48 ohms.\n"
            "   _ else = Reserved       0x6 = 80 ohms.\n"
            "                           0x7 = 34 ohms.\n"
            "                           _ else = Reserved\n"
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
            "   DDR3                    DDR4\n"
            "   0x1 = 60 ohms.          0x1 = 60 ohms.\n"
            "   0x2 = 120 ohms.         0x2 = 120 ohms.\n"
            "   0x3 = 40 ohms.          0x3 = 40 ohms.\n"
            "   0x4 = 20 ohms.          0x4 = 240 ohms.\n"
            "   0x5 = 30 ohms.          0x5 = 48 ohms.\n"
            "   _ else = Reserved       0x6 = 80 ohms.\n"
            "                           0x7 = 34 ohms.\n"
            "                           _ else = Reserved\n"
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
            "   CN8XXX DDR3         CN8XXX DDR4         CN9XXX\n"
            "   0x0 = No ODT.       0x0 = No ODT.       0x0 = No ODT.\n"
            "   0x1 = 20 ohm.       0x1 = 40 ohm.       0x1 = 34 ohm.\n"
            "   0x2 = 30 ohm.       0x2 = 60 ohm.       0x2 = 40 ohm.\n"
            "   0x3 = 40 ohm.       0x3 = 80 ohm.       0x3 = 50 ohm.\n"
            "   0x4 = 60 ohm.       0x4 = 120 ohm.      0x4 = 67 ohm.\n"
            "   0x5 = 120 ohm.      0x5 = 240 ohm.      0x5 = 100 ohm.\n"
            "   _ else = Reserved.  0x6 = 34 ohm.       _ else = Reserved.\n"
            "                       0x7 = 48 ohm.\n"
            "                       _ else = Reserved.\n"
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
            "   DDR3                    DDR4\n"
            "   0x1 = 60 ohms.          0x1 = 60 ohms.\n"
            "   0x2 = 120 ohms.         0x2 = 120 ohms.\n"
            "   0x3 = 40 ohms.          0x3 = 40 ohms.\n"
            "   0x4 = 20 ohms.          0x4 = 240 ohms.\n"
            "   0x5 = 30 ohms.          0x5 = 48 ohms.\n"
            "   _ else = Reserved       0x6 = 80 ohms.\n"
            "                           0x7 = 34 ohms.\n"
            "                           _ else = Reserved\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MAX_RTT_NOM_IDX] =
            "   DDR3                    DDR4\n"
            "   0x1 = 60 ohms.          0x1 = 60 ohms.\n"
            "   0x2 = 120 ohms.         0x2 = 120 ohms.\n"
            "   0x3 = 40 ohms.          0x3 = 40 ohms.\n"
            "   0x4 = 20 ohms.          0x4 = 240 ohms.\n"
            "   0x5 = 30 ohms.          0x5 = 48 ohms.\n"
            "   _ else = Reserved       0x6 = 80 ohms.\n"
            "                           0x7 = 34 ohms.\n"
            "                           _ else = Reserved\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MIN_RODT_CTL] =
            "   CN8XXX DDR3         CN8XXX DDR4         CN9XXX\n"
            "   0x0 = No ODT.       0x0 = No ODT.       0x0 = No ODT.\n"
            "   0x1 = 20 ohm.       0x1 = 40 ohm.       0x1 = 34 ohm.\n"
            "   0x2 = 30 ohm.       0x2 = 60 ohm.       0x2 = 40 ohm.\n"
            "   0x3 = 40 ohm.       0x3 = 80 ohm.       0x3 = 50 ohm.\n"
            "   0x4 = 60 ohm.       0x4 = 120 ohm.      0x4 = 67 ohm.\n"
            "   0x5 = 120 ohm.      0x5 = 240 ohm.      0x5 = 100 ohm.\n"
            "   _ else = Reserved.  0x6 = 34 ohm.       _ else = Reserved.\n"
            "                       0x7 = 48 ohm.\n"
            "                       _ else = Reserved.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_MAX_RODT_CTL] =
            "   CN8XXX DDR3         CN8XXX DDR4         CN9XXX\n"
            "   0x0 = No ODT.       0x0 = No ODT.       0x0 = No ODT.\n"
            "   0x1 = 20 ohm.       0x1 = 40 ohm.       0x1 = 34 ohm.\n"
            "   0x2 = 30 ohm.       0x2 = 60 ohm.       0x2 = 40 ohm.\n"
            "   0x3 = 40 ohm.       0x3 = 80 ohm.       0x3 = 50 ohm.\n"
            "   0x4 = 60 ohm.       0x4 = 120 ohm.      0x4 = 67 ohm.\n"
            "   0x5 = 120 ohm.      0x5 = 240 ohm.      0x5 = 100 ohm.\n"
            "   _ else = Reserved.  0x6 = 34 ohm.       _ else = Reserved.\n"
            "                       0x7 = 48 ohm.\n"
            "                       _ else = Reserved.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_CK_CTL] =
            "Drive strength control for DDR_CK_X_P, DDR_DIMMX_CSX_L,\n"
            "   DDR3 CN8XXX         DDR4 CN8XXX         DDR4 CN9XXX\n"
            "    0x1 = 24 ohm.      0x1 = Reserved.     0x1 = 21 ohm.\n"
            "    0x2 = 26.67 ohm.   0x2 = 26 ohm.       0x2 = 24 ohm.\n"
            "    0x3 = 30 ohm.      0x3 = 30 ohm.       0x3 = 27 ohm.\n"
            "    0x4 = 34.3 ohm.    0x4 = 34 ohm.       0x4 = 30 ohm.\n"
            "    0x5 = 40 ohm.      0x5 = 40 ohm.       0x5 = 36 ohm.\n"
            "    0x6 = 48 ohm.      0x6 = 48 ohm.       0x6 = 44 ohm.\n"
            "    0x7 = 60 ohm.      else = Reserved.    else = Reserved.\n"
            "    else = Reserved.\n"
            "DDR_DIMMX_ODT_X drivers.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_CMD_CTL] =
            "Drive strength control for CMD/A/RESET_L/CKEX drivers.\n"
            "   DDR3 CN8XXX         DDR4 CN8XXX         DDR4 CN9XXX\n"
            "    0x1 = 24 ohm.      0x1 = Reserved.     0x1 = 21 ohm.\n"
            "    0x2 = 26.67 ohm.   0x2 = 26 ohm.       0x2 = 24 ohm.\n"
            "    0x3 = 30 ohm.      0x3 = 30 ohm.       0x3 = 27 ohm.\n"
            "    0x4 = 34.3 ohm.    0x4 = 34 ohm.       0x4 = 30 ohm.\n"
            "    0x5 = 40 ohm.      0x5 = 40 ohm.       0x5 = 36 ohm.\n"
            "    0x6 = 48 ohm.      0x6 = 48 ohm.       0x6 = 44 ohm.\n"
            "    0x7 = 60 ohm.      else = Reserved.    else = Reserved.\n"
            "    else = Reserved.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_CTL_CTL] =
            "Drive strength control for ODT, etc. drivers.\n"
            "   DDR3 CN8XXX         DDR4 CN8XXX         DDR4 CN9XXX\n"
            "    0x1 = 24 ohm.      0x1 = Reserved.     0x1 = 21 ohm.\n"
            "    0x2 = 26.67 ohm.   0x2 = 26 ohm.       0x2 = 24 ohm.\n"
            "    0x3 = 30 ohm.      0x3 = 30 ohm.       0x3 = 27 ohm.\n"
            "    0x4 = 34.3 ohm.    0x4 = 34 ohm.       0x4 = 30 ohm.\n"
            "    0x5 = 40 ohm.      0x5 = 40 ohm.       0x5 = 36 ohm.\n"
            "    0x6 = 48 ohm.      0x6 = 48 ohm.       0x6 = 44 ohm.\n"
            "    0x7 = 60 ohm.      else = Reserved.    else = Reserved.\n"
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
            "Set to 2 unless instructed differently by support.\n"
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
            "    3 = 3 CKs (CN9XXX)\n"
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
    [BDK_CONFIG_DDR_CUSTOM_DRAM_CONNECTION] =
            "DRAM connection type to motherboard\n"
            "    0 = DIMM(s) via slot(s)\n"
            "    1 = discrete soldered DRAMs\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_DBI_MODE] =
            "Enable DBI mode\n"
            "   Set to 1 to enable DBI mode operation.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_PARITY_MODE] =
            "Enable DRAM Parity mode\n"
            "   Set to 1 to enable parity mode operation.\n"
            "Parameters:\n"
            "    LMC#: Parameter can be different for memory controller. This\n"
            "        specifies which LMC the value is for. LMC must be\n"
            "        0-3. Optional.\n"
            "    N#: Parameter can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DDR_CUSTOM_DATA_INVERT] =
            "Enable DRAM data invert to cause all data to be inverted\n"
            "before writing to or reading from DRAM. May be useful if data\n"
            "inversion will result in lower power.\n"
            "   Defaults to enabled (1) on CN9xxx, disabled (0) on CN8xxx.\n"
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
            "Note that DRAM memory test accuracy may be affected by scrambling.\n"
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
    /* VRM temperature throttling */
    [BDK_CONFIG_VRM_TEMP_TRIP] =
            "Temperature where THERMAL_TRIP_N is asserted. When the chip reaches\n"
            "this temperature THERMAL_TRIP_N will assert, signalling the board\n"
            "to emergency power off. The default value is the recommended\n"
            "maximum temperature of the chip. Values between 0 and 140 degrees\n"
            "Celsius.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VRM_TEMP_HIGH] =
            "Temperature where maximum throttling is applied to the chip. Chip\n"
            "performance will be greatly reduced to keep the temperature below\n"
            "thermal trip (VRM-TEMP-TRIP). The default value is the\n"
            "recommended maximum operating temperature of the chip. Values\n"
            "between 0 and 140 degrees Celsius.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VRM_TEMP_LOW] =
            "Temperature where minimum throttling is applied to the chip. Chip\n"
            "performance will be maximized at or below this temperature. The\n"
            "throttling level will be set to VRM-THROTTLE-NORMAL. The default\n"
            "value is the recommended operating temperature of the chip.\n"
            "Values between 0 and 140 degrees Celsius. This only applies to\n"
            "CN8XXX chips, not CN9XXX.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VRM_THROTTLE_NORMAL] =
            "Throttle level of the chip when operating normally. Temperatures\n"
            "at or below VRM-TEMP-LOW will use this throttling level. The default\n"
            "level (70%), allows good performance while still reducing power under\n"
            "heavy loads. Value is a percentage between 1 and 100. This only\n"
            "applies to CN8XXX chips, not CN9XXX.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VRM_THROTTLE_THERM] =
            "Throttle level of the chip is overheating. Temperatures at or\n"
            "above VRM-TEMP-HIGH will use this throttling level. The default\n"
            "level (5%), allows for forward progress while still reducing power.\n"
            "Value is a percentage between 1 and 100. Setting a value of 100\n"
            "disables dynamic throttling (not recommended). This only applies to\n"
            "CN8XXX chips, not CN9XXX.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* Clock configuration options, new for CN9XXX */
    [BDK_CONFIG_RCLK_FREQ_MAX] =
            "Maximum Core clock (RCLK) frequency in MHz. DVFS control will vary the\n"
            "actual RCLK frequency depending on Tj, power budget, and system load;\n"
            "this sets an upper bound.  If fuses indicate the part supports a lower\n"
            "frequency, the fuse value is used.  Valid range is 500MHz-3300MHz. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_RCLK_FREQ_MIN] =
            "Minimum Core clock (RCLK) frequency in MHz. DVFS control will vary the\n"
            "actual RCLK frequency depending on Tj, power budget, and system load;\n"
            "this sets the lower bound.  Default value 500MHz.  WARNING- setting\n"
            "this above 500MHz may result in excess power consumption and sudden\n"
            "thermal shutdown. Valid range is 500MHz-3300MHz. Doesn't apply to\n"
            "CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCLK_FREQ] =
            "Coprocessor clock (SCLK) frequency in MHz. Valid range is\n"
            "500MHz-1200MHz. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_CPTCLK_FREQ] =
            "Cryptographic accelerator clock (CPTCLK) frequency in MHz. If fuses\n"
            "indicate the part supports a lower frequency, the fuse value is used.\n"
            "Valid range 200MHz-1600MHz. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_BCLK_FREQ_MAX] =
            "Maximum bphy clock (BCLK) frequency in MHz. SCP firmware will vary\n"
            "the actual BCLK frequency between min and max based on SCMI messages\n"
            "from the AP. F95* only; ignored in other chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_BCLK_FREQ_MIN] =
            "Minimum bphy clock (BCLK) frequency in MHz. SCP firmware will vary\n"
            "the actual BCLK frequency between min and max based on SCMI messages\n"
            "from the AP. F95* only; ignored in other chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DSPCLK_FREQ_MAX] =
            "Maximum dsp clock (DSPCLK) frequency in MHz. SCP firmware will vary\n"
            "the actual DSPCLK frequency between min and max based on SCMI messages\n"
            "from the AP. F95* only; ignored in other chips."
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DSPCLK_FREQ_MIN] =
            "Maximum dsp clock (DSPCLK) frequency in MHz. SCP firmware will vary\n"
            "the actual DSPCLK frequency between min and max based on SCMI messages\n"
            "from the AP. F95* only; ignored in other chips."
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* Voltage configuration options, new for CN9XXX */
    [BDK_CONFIG_VDD_CORE_TOLERANCE] =
            "The +/- control tolerance of the vdd_core supply as measured at\n"
            "the Chip in mV. Default is +/-8mV. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VDD_CORE_RIPPLE] =
            "The +/- ripple of the vdd_core supply as measured at the Chip in\n"
            "mV. Default is +/-21mV. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VDD_CORE_COMPENSATION] =
            "The compensation factor in percentage for the vdd_core supply.\n"
            "This can be used to adjust the voltage programmed by firmware to\n"
            "account for customer-specific VRM design requirements.  An example\n"
            "usage is below.\n"
            "    VDDC required voltage = 800mV\n"
            "    Compensation percentage = 95%\n"
            "    VDDC actual programmed voltage = 760mV\n"
            "This should be set to 100% for most designs.  Default is 100.\n"
            "Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VDD_SYS_TOLERANCE] =
            "The +/- control tolerance of the vdd_sys supply as measured at\n"
            "the Chip in mV. Default is +/-8mV. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VDD_SYS_RIPPLE] =
            "The +/- ripple of the vdd_sys supply as measured at the Chip in\n"
            "mV. Default is +/-21mV. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_VDD_SYS_COMPENSATION] =
            "The compensation factor in percentage for the vdd_sys supply.\n"
            "This can be used to adjust the voltage programmed by firmware to\n"
            "account for customer-specific VRM design requirements.  An example\n"
            "usage is below.\n"
            "    VDD_SYS required voltage = 800mV\n"
            "    Compensation percentage = 95%\n"
            "    VDD_SYS actual programmed voltage = 760mV\n"
            "This should be set to 100% for most designs.  Default is 100.\n"
            "Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* DVFS Power Control configuration options, new for CN9XXX */
    [BDK_CONFIG_DVFS_POWER_BUDGET] =
            "The total chip power budget in Watts, used in POWER_CAPPED_USING_ACTIVITY\n"
            "and EFFICIENT_OPERATION modes, DVFS control makes a best-effort\n"
            "attempt to keep power at or below this level. Values between 0 and\n"
            "150 Watts.  Default is 100W. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DVFS_POWER_CONTROL_MODE] =
            "The operating mode of the DVFS (Dynamic Frequency Voltage Scaling)\n"
            "power control code.  Encoding:\n"
            "    1 - POWER_CAPPED: Caps power consumption at or below\n"
            "        DVFS_POWER_BUDGET.\n"
            "    2 - THERMAL_BUDGET: Gives best performance within thermal budget.\n"
            "    3 - EFFICIENT_OPERATION: Sets performance level based on OSPM messages.\n"
            "    4 - MANUAL_CONTROL: Set voltage and frequencies manually.\n"
            "    5 - DVFS_OFF: Operate only at RCLK_FREQ_MAX (default).\n"
            "Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DVFS_THERMAL_HOT] =
            "DVFS control will assert the THERMAL_HOT_L pin when the highest\n"
            "observed temperature on the chip is at or above this value. This\n"
            "value is recommended to be 10 degrees Celsius below BDK_CONFIG_DVFS_MAX_TJ.\n"
            "The default value is the recommended maximum temperature of\n"
            "the chip minus 10. Values between 0 and 140 degrees Celsius. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_DVFS_THERMAL_HOT_BACKOFF] =
            "The percentage that the DVFS control should attempt to reduce the chip\n"
            "power when the board asserts THERMAL_HOT.  A value of 30 means reduce\n"
            "power 30%, etc.  Allowed values 0 to 100.  Default is 50. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    /* SCP Config option */
    [BDK_CONFIG_SCP_FAILSAFE_TIMEOUT] =
            "This timeout detects boot failures in when booting from the primary\n"
            "boot device, and causes a reboot from secondary. In seconds. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_UART_NUM] =
            "Selects which uart SCP will use for the SCP CLI and logging.\n"
            "0xf selects no logging. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_MCP_DISABLE] =
            "Instructs SCP firmware to not start the MCP. Doesn't apply to\n"
            "CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_FORCE_SECONDARY_BOOT] =
            "Force the next reboot to use the secondary boot device. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_WAKEUP_MODE] =
            "Enumerated by CPC_WAKEUP_MODE_E. Default FAST_WAKE_SLOW_SLEEP. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "    0 = FAST_WAKE_OFF: When AP activity detected, ramp from min_rclk\n"
            "        to max_rclk over ~10ms.\n"
            "    1 = FAST_WAKE_SLOW_SLEEP: When AP activity detected, ramp from\n"
            "        min_rclk to max_rclk in 1ms. When activity ceases, ramp from\n"
            "        max_rclk to min_rclk over ~10ms.\n"
            "    2 = FAST_WAKE_FAST_SLEEP: When AP activity detected, ramp from\n"
            "        min_rclk to max_rclk in 1ms. When activity ceases, ramp from\n"
            "        max_rclk to min_rclk IN 1ms.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_ACTIVE_THRESHOLD] =
            "The percentage of maximum IPC at which a core is considered active.\n"
            "Encoded as percent * 1000. Range 0.001% to 32.7%. Default 1%. Doesn't\n"
            "apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_FAIL_TIMEOUT] =
            "Timeout in seconds for SCP to configure clocks and signal complete to\n"
            "the BDK. Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
    [BDK_CONFIG_SCP_FAIL_ACTION] =
            "Action to take if the SCP fail timeout expires:\n"
            "    0: Continue to boot (Default)\n"
            "    1: Reboot the system\n"
            "    2: Halt forever\n"
            "Doesn't apply to CN8XXX chips.\n"
            "Parameters:\n"
            "    N#: Setting can be different for each node. This specifies\n"
            "        which node the value is for. Node must be 0-3. Optional.",
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
            "was non-trusted, this parameter will not be in the device tree.",
    [BDK_CONFIG_TRUST_ROT_ADDR] =
            "Address of the Root of Trust public key (ROT). This will be zero for\n"
            "non-trusted boot, or an address in secure space when trusted boot.\n"
            "This public key is copied from the trusted CSIB, so it is a coordinate\n"
            "pair (Qx,Qy) of 256-bit integers in little-endian format.",
    [BDK_CONFIG_TRUST_BSSK_ADDR] =
            "If boot was trusted and FUSF_HUK is non-zero, this contains the\n"
            "address in secure space for the BSSK. The BSSK is derived from the\n"
            "HUK and bytes 32- 47 of the CSIB.",
    /* Software Attestation information */
    [BDK_CONFIG_ATTESTATION_IMAGE_LIST] =
            "List of loaded image names and their hash ID values in the form:\n"
            "    <IMG_NAME>[@<OFFSET>]:<IMG_HASH>\n"
            "where:\n"
            "    <IMG_NAME> is filename that was loaded.\n"
            "    @<OFFSET> is location offset loaded from. Only present for\n"
            "        direct flash acceses, 8 hex digits.\n"
            "    <IMG_HASH> is a [SHA256] ASCII hash in hex if available. If\n"
            "        the file wasn't signed, a '0' will be stored.",
    };
    return help[cfg_item];
}

