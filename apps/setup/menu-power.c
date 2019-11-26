/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "menu-common.h"

void menu_power(bdk_menu_t *parent, char key, void *arg)
{
    bdk_menu_t menu;
    const struct menu_add_info info_8x[] =
    {
        { .key = 'T', .name = "Thermal Trip Temperature", .config = BDK_CONFIG_VRM_TEMP_TRIP,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'H', .name = "Maximum Operating Temperature", .config = BDK_CONFIG_VRM_TEMP_HIGH,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'L', .name = "Normal Operating Temperature", .config = BDK_CONFIG_VRM_TEMP_LOW,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'M', .name = "Maximum Operating Throttle", .config = BDK_CONFIG_VRM_THROTTLE_THERM,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },
        { .key = 'N', .name = "Normal Operating Throttle", .config = BDK_CONFIG_VRM_THROTTLE_NORMAL,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },
        { .key = 0, },
    };
    const struct menu_add_info info_9x[] =
    {
        /* VRM temperature throttling */
        { .key = 'H', .name = "Maximum Operating Temperature", .config = BDK_CONFIG_VRM_TEMP_HIGH,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'T', .name = "Temperature where THERMAL_TRIP_N is asserted", .config = BDK_CONFIG_VRM_TEMP_TRIP,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },

        /* Clock configuration options, new for CN9XXX */
        { .key = 'R', .name = "Maximum Core clock (RCLK) frequency", .config = BDK_CONFIG_RCLK_FREQ_MAX,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = 'E', .name = "Minimum Core clock (RCLK) frequency", .config = BDK_CONFIG_RCLK_FREQ_MIN,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = 'S', .name = "Coprocessor clock (SCLK) frequency", .config = BDK_CONFIG_SCLK_FREQ,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = 'C', .name = "Cryptographic accelerator clock (CPTCLK) frequency", .config = BDK_CONFIG_CPTCLK_FREQ,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = '1', .name = "Maximum BPHY clock (BCLK) frequency", .config = BDK_CONFIG_BCLK_FREQ_MAX,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = '2', .name = "Minimum BPHY clock (BCLK) frequency", .config = BDK_CONFIG_BCLK_FREQ_MIN,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = '3', .name = "Maximum DSP clock (DSPCLK) frequency", .config = BDK_CONFIG_DSPCLK_FREQ_MAX,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },
        { .key = '4', .name = "Minimum DSP clock (DSPCLK) frequency", .config = BDK_CONFIG_DSPCLK_FREQ_MIN,
            .input = MENU_INPUT_DEC, .units = "MHz", .param = MENU_PARAM_NODE },

        /* Voltage configuration options, new for CN9XXX */
        {.key = '5', .name = "+/-mV control tolerance of the vdd_core supply", .config = BDK_CONFIG_VDD_CORE_TOLERANCE,
            .input = MENU_INPUT_DEC, .units = "mV", .param = MENU_PARAM_NODE },
        {.key = '6', .name = "+/-mV control ripple of the vdd_core supply", .config = BDK_CONFIG_VDD_CORE_RIPPLE,
            .input = MENU_INPUT_DEC, .units = "mV", .param = MENU_PARAM_NODE },
        {.key = '7', .name = "Compensation of the vdd_core supply", .config = BDK_CONFIG_VDD_CORE_COMPENSATION,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },
        {.key = '8', .name = "+/-mV control tolerance of the vdd_sys supply", .config = BDK_CONFIG_VDD_SYS_TOLERANCE,
            .input = MENU_INPUT_DEC, .units = "mV", .param = MENU_PARAM_NODE },
        {.key = '9', .name = "+/-mV control ripple of the vdd_sys supply", .config = BDK_CONFIG_VDD_SYS_RIPPLE,
            .input = MENU_INPUT_DEC, .units = "mV", .param = MENU_PARAM_NODE },
        {.key = '0', .name = "Compensation of the vdd_sys supply", .config = BDK_CONFIG_VDD_SYS_COMPENSATION,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },

        /* DVFS Power Control configuration options, new for CN9XXX */
        { .key = 'P', .name = "The total chip power budget", .config = BDK_CONFIG_DVFS_POWER_BUDGET,
            .input = MENU_INPUT_DEC, .units = "W", .param = MENU_PARAM_NODE },
        { .key = 'M', .name = "The operating mode of the DVFS", .config = BDK_CONFIG_DVFS_POWER_CONTROL_MODE,
            .input = MENU_INPUT_DEC, .param = MENU_PARAM_NODE },
        { .key = 'L', .name = "DVFS control will assert the THERMAL_HOT_L", .config = BDK_CONFIG_DVFS_THERMAL_HOT,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'B', .name = "THERMAL_HOT backoff", .config = BDK_CONFIG_DVFS_THERMAL_HOT_BACKOFF,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },

        /* SCP Config option */
        { .key = 'F', .name = "Failsafe boot timeout", .config = BDK_CONFIG_SCP_FAILSAFE_TIMEOUT,
            .input = MENU_INPUT_DEC, .units = "S", .param = MENU_PARAM_NODE },
        { .key = 'U', .name = "SCP log uart", .config = BDK_CONFIG_SCP_UART_NUM,
            .input = MENU_INPUT_DEC, .units = "Uart", .param = MENU_PARAM_NODE },
        { .key = 'W', .name = "MCP disable", .config = BDK_CONFIG_SCP_MCP_DISABLE,
            .input = MENU_INPUT_DEC, .param = MENU_PARAM_NODE },
        { .key = 'X', .name = "Force secondary boot", .config = BDK_CONFIG_SCP_FORCE_SECONDARY_BOOT,
            .input = MENU_INPUT_DEC, .param = MENU_PARAM_NODE },
        {.key = 'A', .name = "Active threshold", .config = BDK_CONFIG_SCP_ACTIVE_THRESHOLD,
            .input = MENU_INPUT_DEC, .units = "%*1000", .param = MENU_PARAM_NODE },
        { .key = 0, },
    };

    do
    {
        bdk_menu_init(&menu, "Setup - Power");
        int i = 0;
        const struct menu_add_info *info = bdk_is_model(OCTEONTX_CN8XXX) ? info_8x : info_9x;
        while (info[i].key)
        {
            menu_add_config(&menu, &info[i]);
            i++;
        }
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}
