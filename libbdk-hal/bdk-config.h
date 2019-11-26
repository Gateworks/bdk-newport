/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for controlling the system configuration.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

#define BDK_CONFIG_MANUFACTURING_ADDRESS 0xff0000 /* 16MB - 64KB */
#define BDK_DEVICE_TREE_ROOT "cavium,bdk"

typedef enum
{
    /* Board manufacturing data */
    BDK_CONFIG_BOARD_MODEL,         /* No parameters */
    BDK_CONFIG_BOARD_REVISION,      /* No parameters */
    BDK_CONFIG_BOARD_SERIAL,        /* No parameters */
    BDK_CONFIG_MAC_ADDRESS,         /* No parameters */
    BDK_CONFIG_MAC_ADDRESS_NUM,     /* No parameters */
    BDK_CONFIG_MAC_ADDRESS_NUM_OVERRIDE, /* No parameters */

    /* Board generic */
    BDK_CONFIG_BMC_TWSI,            /* No parameters */
    BDK_CONFIG_WATCHDOG_TIMEOUT,    /* No parameters */
    BDK_CONFIG_TWSI_WRITE,          /* Parameters: Write number */
    BDK_CONFIG_MDIO_WRITE,          /* Parameters: Write number */
    BDK_CONFIG_DEVICES,             /* No parameters */

    /* Board wiring of network ports and PHYs */
    BDK_CONFIG_PHY_ADDRESS,         /* Parameters: Node, Interface, Port */
    BDK_CONFIG_BGX_ENABLE,          /* Parameters: Node, BGX, Port */
    BDK_CONFIG_NETWORK_LED_LINK_SLOW,   /* Parameters: Node, CGX, Port */
    BDK_CONFIG_NETWORK_LED_LINK_FAST,   /* Parameters: Node, CGX, Port */
    BDK_CONFIG_NETWORK_LED_ACTIVITY,    /* Parameters: Node, CGX, Port */
    BDK_CONFIG_NETWORK_LED_ID,          /* Parameters: Node, CGX, Port */
    BDK_CONFIG_NETWORK_PORT,            /* Parameters: Node, CGX, Port */
    BDK_CONFIG_NETWORK_FLAGS,           /* Parameters: Node, CGX, Port */
    BDK_CONFIG_NETWORK_LANE_ORDER,      /* Parameters: Node, CGX */

    /* BDK Configuration params */
    BDK_CONFIG_VERSION,
    BDK_CONFIG_NUM_PACKET_BUFFERS,
    BDK_CONFIG_PACKET_BUFFER_SIZE,
    BDK_CONFIG_SHOW_LINK_STATUS,
    BDK_CONFIG_COREMASK,
    BDK_CONFIG_BOOT_MENU_TIMEOUT,
    BDK_CONFIG_BOOT_PATH_OPTION,
    BDK_CONFIG_BOOT_NEXT_STAGE,
    BDK_CONFIG_BOOT_DEVICE,         /* Parameters: Node */
    BDK_CONFIG_TRACE,

    /* Chip feature items */
    BDK_CONFIG_PCIE_EA,             /* No parameters */
    BDK_CONFIG_PCIE_ORDERING,       /* No parameters */
    BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR, /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_GEN2_DEEMPHASIS, /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_WIDTH,          /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_TX_PRESET_OVERRIDE_VECTOR,  /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_ENDPOINT_TX_PRESET_OVERRIDE,  /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_IDLE_REFSET_VALUE,    /* Parameters: Node, QLM */
    BDK_CONFIG_PCIE_RC_OVERRIDE_DETECT,  /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_PHYSICAL_SLOT,  /* Parameters: Node, Port */
    BDK_CONFIG_PCIE_FLASH,          /* Parameters: Node, Port */
    BDK_CONFIG_CHIP_SKU,            /* Parameter: Node */
    BDK_CONFIG_CHIP_SERIAL,         /* Parameter: Node */
    BDK_CONFIG_CHIP_UNIQUE_ID,      /* Parameter: Node */

    /* Options for CN9XXX PCIe EP config space */
    BDK_CONFIG_PCIE_EP_NUM_PFS,     /* Parameters: Node, Port, see PCIEEPX_HIDE_PF */
    BDK_CONFIG_PCIE_EP_ID,          /* Parameters: Node, Port, see PCIEEPX_ID */
    BDK_CONFIG_PCIE_EP_REV,         /* Parameters: Node, Port, see PCIEEPX_REV */
    BDK_CONFIG_PCIE_EP_SUBSYS,      /* Parameters: Node, Port, see PCIEEPX_SUBSYS */
    BDK_CONFIG_PCIE_EP_BAR_SIZE,    /* Parameters: BAR(0,2,4), Node, Port, see PCIEEPX_BAR* */
    BDK_CONFIG_PCIE_EP_ROM_SIZE,    /* Parameters: Node, Port, see PCIEEPX_EROM_MASK */
    BDK_CONFIG_PCIE_EP_NUM_VFS,     /* Parameters: Node, Port, see PCIEEPX_SRIOV_FO */
    BDK_CONFIG_PCIE_EP_SRIOV_DEV,   /* Parameters: Node, Port, see PCIEEPX_SRIOV_DEV */
    BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, /* Parameters: BAR(0,2,4), Node, Port, see PCIEEPX_SRIOV_BAR */

    /* QLM related config */
    BDK_CONFIG_QLM_AUTO_CONFIG,     /* Parameters: Node */
    BDK_CONFIG_QLM_VOLTAGE,         /* Parameters: Node */
    BDK_CONFIG_QLM_MODE,            /* Parameters: Node, QLM, Lane */
    BDK_CONFIG_QLM_FREQ,            /* Parameters: Node, QLM, Lane */
    BDK_CONFIG_QLM_CLK,             /* Parameters: Node, QLM */
    BDK_CONFIG_QLM_CLK_TERM,        /* Parameters: Node, QLM */
    BDK_CONFIG_QLM_TUNING_TX_SWING, /* Parameters: Node, QLM, Lane (CN8XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_PREMPTAP, /* Parameters: Node, QLM, Lane (CN8XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_GAIN,  /* Parameters: Node, QLM, Lane (CN8XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_VBOOST, /* Parameters: Node, QLM, Lane (CN8XXX only) */
    BDK_CONFIG_QLM_CHANNEL_LOSS,    /* Parameters: Node, QLM (CN8XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_MAIN,  /* Parameters: QLM mode, QLM speed, Node, QLM, Lane (CN9XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_PRE,   /* Parameters: QLM mode, QLM speed, Node, QLM, Lane (CN9XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_POST,  /* Parameters: QLM mode, QLM speed, Node, QLM, Lane (CN9XXX only) */
    BDK_CONFIG_QLM_TUNING_TX_BS,    /* Parameters: QLM mode, QLM speed, Node, QLM, Lane (CN9XXX only) */
    BDK_CONFIG_QLM_TUNING_RX_PREVGA_GN_ADAPT, /* Parameters: Node, QLM, Lane */
    BDK_CONFIG_QLM_TUNING_RX_PREVGA_GN_OVRD, /* Parameters: Node, QLM, Lane */
    BDK_CONFIG_QLM_LANE_RX_POLARITY, /* Parameters: Node, QLM, Lane */
    BDK_CONFIG_QLM_LANE_TX_POLARITY, /* Parameters: Node, QLM, Lane */
    BDK_CONFIG_QLM_RX_ADAPTATION,    /* Parameters: Node, QLM */

    /* DRAM configuration options */
    BDK_CONFIG_DDR_SPEED,                                           /* Parameters: Node */
    BDK_CONFIG_DDR_ALT_REFCLK,                                      /* Parameters: Node */
    BDK_CONFIG_DDR_SPD_ADDR,                                        /* Parameters: DIMM, LMC, Node */
    BDK_CONFIG_DDR_SPD_DATA,                                        /* Parameters: DIMM, LMC, Node */
    BDK_CONFIG_DDR_RANKS_DQX_CTL,                                   /* Parameters: Num Ranks, Num DIMMs, LMC, Node */
    BDK_CONFIG_DDR_RANKS_WODT_MASK,                                 /* Parameters: Num Ranks, Num DIMMs, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_PASR,                                /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_ASR,                                 /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_SRT,                                 /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_RTT_WR,                              /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_DIC,                                 /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_RTT_NOM,                             /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE1_DB_OUTPUT_IMPEDANCE,                 /* Parameters: Num Ranks, Num DIMMs, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE2_RTT_PARK,                            /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE2_VREF_VALUE,                          /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE2_VREF_RANGE,                          /* Parameters: Num Ranks, Num DIMMs, Rank, LMC, Node */
    BDK_CONFIG_DDR_RANKS_MODE2_VREFDQ_TRAIN_EN,                     /* Parameters: Num Ranks, Num DIMMs, LMC, Node */
    BDK_CONFIG_DDR_RANKS_RODT_CTL,                                  /* Parameters: Num Ranks, Num DIMMs, LMC, Node */
    BDK_CONFIG_DDR_RANKS_RODT_MASK,                                 /* Parameters: Num Ranks, Num DIMMs, LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MIN_RTT_NOM_IDX,                          /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MAX_RTT_NOM_IDX,                          /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MIN_RODT_CTL,                             /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MAX_RODT_CTL,                             /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_CK_CTL,                                   /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_CMD_CTL,                                  /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_CTL_CTL,                                  /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MIN_CAS_LATENCY,                          /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_OFFSET_EN,                                /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_OFFSET,                                   /* Parameters: Type(UDIMM,RDIMM), LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMPUTE,                           /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMP_OFFSET,                       /* Parameters: Type(UDIMM,RDIMM), LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DDR2T,                                    /* Parameters: Type(UDIMM,RDIMM), LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DISABLE_SEQUENTIAL_DELAY_CHECK,           /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MAXIMUM_ADJACENT_RLEVEL_DELAY_INCREMENT,  /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_PARITY,                                   /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_FPRCH2,                                   /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MODE32B,                                  /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_MEASURED_VREF,                            /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DRAM_CONNECTION,                          /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DBI_MODE,                                 /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_PARITY_MODE,                              /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DATA_INVERT,                              /* Parameters: LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DLL_WRITE_OFFSET,                         /* Parameters: Byte, LMC, Node */
    BDK_CONFIG_DDR_CUSTOM_DLL_READ_OFFSET,                          /* Parameters: Byte, LMC, Node */

    /* High level DRAM options */
    BDK_CONFIG_DRAM_VERBOSE,        /* Parameters: Node */
    BDK_CONFIG_DRAM_BOOT_TEST,      /* Parameters: Node */
    BDK_CONFIG_DRAM_CONFIG_GPIO,    /* No parameters */
    BDK_CONFIG_DRAM_SCRAMBLE,       /* No parameters */

    /* USB */
    BDK_CONFIG_USB_PWR_GPIO,        /* Parameters: Node, Port */
    BDK_CONFIG_USB_PWR_GPIO_POLARITY, /* Parameters: Node, Port */
    BDK_CONFIG_USB_REFCLK_SRC, /* Parameters: Node, Port */

    /* VRM temperature throttling */
    BDK_CONFIG_VRM_TEMP_TRIP,       /* Parameters: Node */
    BDK_CONFIG_VRM_TEMP_HIGH,       /* Parameters: Node */
    BDK_CONFIG_VRM_TEMP_LOW,        /* Parameters: Node */
    BDK_CONFIG_VRM_THROTTLE_NORMAL, /* Parameters: Node */
    BDK_CONFIG_VRM_THROTTLE_THERM,  /* Parameters: Node */

    /* Clock configuration options, new for CN9XXX */
    BDK_CONFIG_RCLK_FREQ_MAX,       /* Parameters: Node */
    BDK_CONFIG_RCLK_FREQ_MIN,       /* Parameters: Node */
    BDK_CONFIG_SCLK_FREQ,           /* Parameters: Node */
    BDK_CONFIG_CPTCLK_FREQ,         /* Parameters: Node */
    BDK_CONFIG_BCLK_FREQ_MAX,       /* Parameters: Node */
    BDK_CONFIG_BCLK_FREQ_MIN,       /* Parameters: Node */
    BDK_CONFIG_DSPCLK_FREQ_MAX,     /* Parameters: Node */
    BDK_CONFIG_DSPCLK_FREQ_MIN,     /* Parameters: Node */

    /* Voltage configuration options, new for CN9XXX */
    BDK_CONFIG_VDD_CORE_TOLERANCE,  /* Parameters: Node */
    BDK_CONFIG_VDD_CORE_RIPPLE,     /* Parameters: Node */
    BDK_CONFIG_VDD_CORE_COMPENSATION, /* Parameters: Node */
    BDK_CONFIG_VDD_SYS_TOLERANCE,   /* Parameters: Node */
    BDK_CONFIG_VDD_SYS_RIPPLE,      /* Parameters: Node */
    BDK_CONFIG_VDD_SYS_COMPENSATION, /* Parameters: Node */

    /* DVFS Power Control configuration options, new for CN9XXX */
    BDK_CONFIG_DVFS_POWER_BUDGET,   /* Parameters: Node */
    BDK_CONFIG_DVFS_POWER_CONTROL_MODE, /* Parameters: Node */
    BDK_CONFIG_DVFS_THERMAL_HOT,    /* Parameters: Node */
    BDK_CONFIG_DVFS_THERMAL_HOT_BACKOFF, /* Parameters: Node */

    /* SCP Config option */
    BDK_CONFIG_SCP_FAILSAFE_TIMEOUT,/* Parameters: Node */
    BDK_CONFIG_SCP_UART_NUM,        /* Parameters: Node */
    BDK_CONFIG_SCP_MCP_DISABLE,     /* Parameters: Node */
    BDK_CONFIG_SCP_FORCE_SECONDARY_BOOT, /* Parameters: Node */
    BDK_CONFIG_SCP_WAKEUP_MODE, /* Parameters: Node */
    BDK_CONFIG_SCP_ACTIVE_THRESHOLD, /* Parameters: Node */
    BDK_CONFIG_SCP_FAIL_TIMEOUT,    /* Parameters: Node */
    BDK_CONFIG_SCP_FAIL_ACTION,     /* Parameters: Node */

    /* Generic GPIO, unrelated to a specific block */
    BDK_CONFIG_GPIO_PIN_SELECT,     /* Parameters: GPIO, Node */
    BDK_CONFIG_GPIO_POLARITY,       /* Parameters: GPIO, Node */

    /* PBUS */
    BDK_CONFIG_PBUS_CFG,            /* Parameters: Region, Node */
    BDK_CONFIG_PBUS_TIM,            /* Parameters: Region, Node */

    /* Trusted boot information */
    BDK_CONFIG_TRUST_CSIB,          /* No parameters */
    BDK_CONFIG_TRUST_ROT_ADDR,      /* No parameters */
    BDK_CONFIG_TRUST_BSSK_ADDR,     /* No parameters */

    /* Software Attestation information */
    BDK_CONFIG_ATTESTATION_IMAGE_LIST, /* No parameters */

    __BDK_CONFIG_END
} bdk_config_t;

/**
 * Internal BDK function to initialize the config system. Must be called before
 * any configuration functions are called
 */
extern void __bdk_config_init(void);

/**
 * Return a help string for the given configuration parameter
 *
 * @param cfg_item Configuration parameter to get help for
 *
 * @return Help string for the user
 */
extern const char *bdk_config_get_help(bdk_config_t cfg_item);

/**
 * Get an integer configuration item
 *
 * @param cfg_item  Config item to get. If the item takes parameters (see bdk_config_t), then the
 *                  parameters are listed following cfg_item.
 *
 * @return The value of the configuration item, or def_value if the item is not set
 */
extern int64_t bdk_config_get_int(bdk_config_t cfg_item, ...);

/**
 * Get a string configuration item
 *
 * @param cfg_item Config item to get. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 * @param args     Variable arguments
 *
 * @return The value of the configuration item, or def_value if the item is not set
 */
extern const char* bdk_config_get_str_va(bdk_config_t cfg_item, va_list args);

/**
 * Get a string configuration item
 *
 * @param cfg_item  Config item to get. If the item takes parameters (see bdk_config_t), then the
 *                  parameters are listed following cfg_item.
 *
 * @return The value of the configuration item, or def_value if the item is not set
 */
extern const char *bdk_config_get_str(bdk_config_t cfg_item, ...);

/**
 * Get a binary blob
 *
 * @param blob_size Integer to receive the size of the blob
 * @param cfg_item  Config item to get. If the item takes parameters (see bdk_config_t), then the
 *                  parameters are listed following cfg_item.
 *
 * @return The value of the configuration item, or def_value if the item is not set
 */
extern const void *bdk_config_get_blob(int *blob_size, bdk_config_t cfg_item, ...);

/**
 * Set an integer configuration item. Note this only sets the item in memory,
 * persistent storage is not updated. The optional parameters for the setting are
 * not supplied, meaning this function only changes the global default.
 *
 * @param value    Configuration item value
 * @param cfg_item Config item to set. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 */
extern void bdk_config_set_int_no_param(int64_t value, bdk_config_t cfg_item);

/**
 * Set an integer configuration item. Note this only sets the item in memory,
 * persistent storage is not updated.
 *
 * @param value    Configuration item value
 * @param cfg_item Config item to set. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 */
extern void bdk_config_set_int(int64_t value, bdk_config_t cfg_item, ...);

/**
 * Set an integer configuration item. Note this only sets the item in memory,
 * persistent storage is not updated.
 *
 * @param value    Configuration item value
 * @param cfg_item Config item to set. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 */
extern void bdk_config_set_str(const char *value, bdk_config_t cfg_item, ...);

/**
 * Appends a string to a configuration item. Note this only sets the item in memory,
 * persistent storage is not updated.
 *
 * @param value    Configuration item value to append
 * @param cfg_item Config item to set. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 */
extern void bdk_config_append_str(const char *value, bdk_config_t cfg_item, ...);

/**
 * Set a blob configuration item. Note this only sets the
 * item in memory, persistent storage is not updated. The optional
 * parameters for the setting are not supplied, meaning this function
 * only changes the global default.
 *
 * @param size     Size of the item in bytes. A size of zero removes the device tree field
 * @param value    Configuration item value
 * @param cfg_item Config item to set. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 */
extern void bdk_config_set_blob_no_param(int size, const void *value, bdk_config_t cfg_item);

/**
 * Set a blob configuration item. Note this only sets the
 * item in memory, persistent storage is not updated.
 *
 * @param size     Size of the item in bytes. A size of zero removes the device tree field
 * @param value    Configuration item value
 * @param cfg_item Config item to set. If the item takes parameters (see bdk_config_t), then the
 *                 parameters are listed following cfg_item.
 */
extern void bdk_config_set_blob(int size, const void *value, bdk_config_t cfg_item, ...);

/**
 * Display the active configuration
 */
extern void bdk_config_show(void);

/**
 * Display a list of all possible config items with help text
 */
extern void bdk_config_help(void);

/**
 * Save the current configuration to flash
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_config_save(void);

/**
 * Takes the current live device tree and exports it to a memory address suitable
 * for passing to the next binary in register X1.
 *
 * @return Physical address of the device tree, or 0 on failure
 */
extern uint64_t __bdk_config_export_to_mem(void);

/**
 * Return a pointer to the device tree used for configuration
 *
 * @return FDT or NULL on failure
 */
extern void* bdk_config_get_fdt(void);

/**
 * Set the device tree used for configuration
 *
 * @param fdt    Device tree to use. Memory is assumed to be from malloc() and bdk_config takes
 *               over ownership on success
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_config_set_fdt(void *fdt);

/**
 * Write all default values to a FDT. Missing config items get defaults in the
 * BDK config, this function adds those defaults to the FDT. This way other code
 * gets the default value without needing special code.
 *
 * @param fdt    FDT structure to fill defaults into
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_config_expand_defaults(void *fdt);

/** @} */
