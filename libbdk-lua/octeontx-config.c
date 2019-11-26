/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>

/**
 * Called to register the octeontx module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_config(lua_State* L)
{
    #define push_bdk_enum(enum)             \
        do                                  \
        {                                   \
            lua_pushnumber(L, enum);        \
            lua_setfield(L, -2, ((const char *)#enum) + 4); \
        } while (0)

    /* Board manufacturing data */
    push_bdk_enum(BDK_CONFIG_BOARD_MODEL);
    push_bdk_enum(BDK_CONFIG_BOARD_REVISION);
    push_bdk_enum(BDK_CONFIG_BOARD_SERIAL);
    push_bdk_enum(BDK_CONFIG_MAC_ADDRESS);
    push_bdk_enum(BDK_CONFIG_MAC_ADDRESS_NUM);
    push_bdk_enum(BDK_CONFIG_MAC_ADDRESS_NUM_OVERRIDE);

    /* Board generic */
    push_bdk_enum(BDK_CONFIG_BMC_TWSI);
    push_bdk_enum(BDK_CONFIG_WATCHDOG_TIMEOUT);
    push_bdk_enum(BDK_CONFIG_TWSI_WRITE);
    push_bdk_enum(BDK_CONFIG_MDIO_WRITE);
    push_bdk_enum(BDK_CONFIG_DEVICES);

    /* Board wiring of network ports and PHYs */
    push_bdk_enum(BDK_CONFIG_PHY_ADDRESS);
    push_bdk_enum(BDK_CONFIG_BGX_ENABLE);
    push_bdk_enum(BDK_CONFIG_NETWORK_LED_LINK_SLOW);
    push_bdk_enum(BDK_CONFIG_NETWORK_LED_LINK_FAST);
    push_bdk_enum(BDK_CONFIG_NETWORK_LED_ACTIVITY);
    push_bdk_enum(BDK_CONFIG_NETWORK_LED_ID);
    push_bdk_enum(BDK_CONFIG_NETWORK_PORT);
    push_bdk_enum(BDK_CONFIG_NETWORK_FLAGS);
    push_bdk_enum(BDK_CONFIG_NETWORK_LANE_ORDER);

    /* BDK Configuration params */
    push_bdk_enum(BDK_CONFIG_VERSION);
    push_bdk_enum(BDK_CONFIG_NUM_PACKET_BUFFERS);
    push_bdk_enum(BDK_CONFIG_PACKET_BUFFER_SIZE);
    push_bdk_enum(BDK_CONFIG_SHOW_LINK_STATUS);
    push_bdk_enum(BDK_CONFIG_COREMASK);
    push_bdk_enum(BDK_CONFIG_BOOT_MENU_TIMEOUT);
    push_bdk_enum(BDK_CONFIG_BOOT_PATH_OPTION);
    push_bdk_enum(BDK_CONFIG_BOOT_NEXT_STAGE);
    push_bdk_enum(BDK_CONFIG_BOOT_DEVICE);
    push_bdk_enum(BDK_CONFIG_TRACE);

    /* Chip feature items */
    push_bdk_enum(BDK_CONFIG_PCIE_EA);
    push_bdk_enum(BDK_CONFIG_PCIE_ORDERING);
    push_bdk_enum(BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR);
    push_bdk_enum(BDK_CONFIG_PCIE_GEN2_DEEMPHASIS);
    push_bdk_enum(BDK_CONFIG_PCIE_WIDTH);
    push_bdk_enum(BDK_CONFIG_PCIE_TX_PRESET_OVERRIDE_VECTOR);
    push_bdk_enum(BDK_CONFIG_PCIE_ENDPOINT_TX_PRESET_OVERRIDE);
    push_bdk_enum(BDK_CONFIG_PCIE_PHYSICAL_SLOT);
    push_bdk_enum(BDK_CONFIG_PCIE_FLASH);
    push_bdk_enum(BDK_CONFIG_CHIP_SKU);
    push_bdk_enum(BDK_CONFIG_CHIP_SERIAL);
    push_bdk_enum(BDK_CONFIG_CHIP_UNIQUE_ID);

    /* Options for CN9XXX PCIe EP config space */
    push_bdk_enum(BDK_CONFIG_PCIE_EP_NUM_PFS);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_ID);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_REV);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_SUBSYS);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_BAR_SIZE);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_ROM_SIZE);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_NUM_VFS);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_SRIOV_DEV);
    push_bdk_enum(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE);

    /* QLM related config */
    push_bdk_enum(BDK_CONFIG_QLM_AUTO_CONFIG);
    push_bdk_enum(BDK_CONFIG_QLM_VOLTAGE);
    push_bdk_enum(BDK_CONFIG_QLM_MODE);
    push_bdk_enum(BDK_CONFIG_QLM_FREQ);
    push_bdk_enum(BDK_CONFIG_QLM_CLK);
    push_bdk_enum(BDK_CONFIG_QLM_CLK_TERM);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_SWING);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_PREMPTAP);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_GAIN);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_VBOOST);
    push_bdk_enum(BDK_CONFIG_QLM_CHANNEL_LOSS);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_MAIN);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_PRE);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_POST);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_BS);
    push_bdk_enum(BDK_CONFIG_QLM_LANE_RX_POLARITY);
    push_bdk_enum(BDK_CONFIG_QLM_LANE_TX_POLARITY);
    push_bdk_enum(BDK_CONFIG_QLM_RX_ADAPTATION);

    /* High level DRAM options */
    push_bdk_enum(BDK_CONFIG_DDR_SPEED);
    push_bdk_enum(BDK_CONFIG_DDR_ALT_REFCLK);
    push_bdk_enum(BDK_CONFIG_DRAM_VERBOSE);
    push_bdk_enum(BDK_CONFIG_DRAM_BOOT_TEST);
    push_bdk_enum(BDK_CONFIG_DRAM_CONFIG_GPIO);
    push_bdk_enum(BDK_CONFIG_DRAM_SCRAMBLE);

    /* USB */
    push_bdk_enum(BDK_CONFIG_USB_PWR_GPIO);
    push_bdk_enum(BDK_CONFIG_USB_PWR_GPIO_POLARITY);
    push_bdk_enum(BDK_CONFIG_USB_REFCLK_SRC);

    /* VRM temperature throttling */
    push_bdk_enum(BDK_CONFIG_VRM_TEMP_TRIP);
    push_bdk_enum(BDK_CONFIG_VRM_TEMP_HIGH);
    push_bdk_enum(BDK_CONFIG_VRM_TEMP_LOW);
    push_bdk_enum(BDK_CONFIG_VRM_THROTTLE_NORMAL);
    push_bdk_enum(BDK_CONFIG_VRM_THROTTLE_THERM);

    /* Clock configuration options, new for CN9XXX */
    push_bdk_enum(BDK_CONFIG_RCLK_FREQ_MAX);
    push_bdk_enum(BDK_CONFIG_RCLK_FREQ_MIN);
    push_bdk_enum(BDK_CONFIG_SCLK_FREQ);
    push_bdk_enum(BDK_CONFIG_CPTCLK_FREQ);
    push_bdk_enum(BDK_CONFIG_BCLK_FREQ_MAX);
    push_bdk_enum(BDK_CONFIG_BCLK_FREQ_MIN);
    push_bdk_enum(BDK_CONFIG_DSPCLK_FREQ_MAX);
    push_bdk_enum(BDK_CONFIG_DSPCLK_FREQ_MIN);

    /* Voltage configuration options, new for CN9XXX */
    push_bdk_enum(BDK_CONFIG_VDD_CORE_TOLERANCE);
    push_bdk_enum(BDK_CONFIG_VDD_CORE_RIPPLE);
    push_bdk_enum(BDK_CONFIG_VDD_SYS_TOLERANCE);
    push_bdk_enum(BDK_CONFIG_VDD_SYS_RIPPLE);

    /* DVFS Power Control configuration options, new for CN9XXX */
    push_bdk_enum(BDK_CONFIG_DVFS_POWER_BUDGET);
    push_bdk_enum(BDK_CONFIG_DVFS_POWER_CONTROL_MODE);
    push_bdk_enum(BDK_CONFIG_DVFS_THERMAL_HOT);
    push_bdk_enum(BDK_CONFIG_DVFS_THERMAL_HOT_BACKOFF);

    /* SCP Config option */
    push_bdk_enum(BDK_CONFIG_SCP_FAILSAFE_TIMEOUT);
    push_bdk_enum(BDK_CONFIG_SCP_UART_NUM);
    push_bdk_enum(BDK_CONFIG_SCP_MCP_DISABLE);
    push_bdk_enum(BDK_CONFIG_SCP_FORCE_SECONDARY_BOOT);
    push_bdk_enum(BDK_CONFIG_SCP_WAKEUP_MODE);
    push_bdk_enum(BDK_CONFIG_SCP_ACTIVE_THRESHOLD);

    /* Generic GPIO, unrelated to a specific block */
    push_bdk_enum(BDK_CONFIG_GPIO_PIN_SELECT);
    push_bdk_enum(BDK_CONFIG_GPIO_POLARITY);

    /* PBUS */
    push_bdk_enum(BDK_CONFIG_PBUS_CFG);
    push_bdk_enum(BDK_CONFIG_PBUS_TIM);

    /* Trusted boot information */
    push_bdk_enum(BDK_CONFIG_TRUST_CSIB);
    push_bdk_enum(BDK_CONFIG_TRUST_ROT_ADDR);
    push_bdk_enum(BDK_CONFIG_TRUST_BSSK_ADDR);

    /* Software Attestation information */
    push_bdk_enum(BDK_CONFIG_ATTESTATION_IMAGE_LIST);
}

