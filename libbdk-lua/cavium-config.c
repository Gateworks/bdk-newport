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
#include <unistd.h>

/**
 * Called to register the cavium module
 *
 * @param L
 *
 * @return
 */
void register_cavium_config(lua_State* L)
{
    #define push_bdk_enum(enum)             \
        do                                  \
        {                                   \
            lua_pushnumber(L, enum);        \
            lua_setfield(L, -2, #enum + 4); \
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

    /* Board wiring of network ports and PHYs */
    push_bdk_enum(BDK_CONFIG_PHY_ADDRESS);
    push_bdk_enum(BDK_CONFIG_BGX_ENABLE);

    /* BDK Configuration params */
    push_bdk_enum(BDK_CONFIG_NUM_PACKET_BUFFERS);
    push_bdk_enum(BDK_CONFIG_PACKET_BUFFER_SIZE);
    push_bdk_enum(BDK_CONFIG_SHOW_LINK_STATUS);
    push_bdk_enum(BDK_CONFIG_COREMASK);

    /* Chip feature items */
    push_bdk_enum(BDK_CONFIG_MULTI_NODE);

    /* QLM related config */
    push_bdk_enum(BDK_CONFIG_QLM_AUTO_CONFIG);
    /* SFF8104 related QLM config */
    push_bdk_enum(BDK_CONFIG_QLM_DIP_AUTO_CONFIG);
    push_bdk_enum(BDK_CONFIG_AQUANTIA_PHY);
    push_bdk_enum(BDK_CONFIG_QLM_MODE);
    push_bdk_enum(BDK_CONFIG_QLM_FREQ);
    push_bdk_enum(BDK_CONFIG_QLM_CLK);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_SWING);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_PREMPTAP);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_GAIN);
    push_bdk_enum(BDK_CONFIG_QLM_TUNING_TX_VBOOST);

    /* High level DRAM options */
    push_bdk_enum(BDK_CONFIG_DDR_SPEED);
    push_bdk_enum(BDK_CONFIG_DDR_ALT_REFCLK);
    push_bdk_enum(BDK_CONFIG_DRAM_VERBOSE);
    push_bdk_enum(BDK_CONFIG_DRAM_BOOT_TEST);

    /* USB */
    push_bdk_enum(BDK_CONFIG_USB_PWR_GPIO);
    push_bdk_enum(BDK_CONFIG_USB_PWR_GPIO_POLARITY);

    /* How EYE diagrams are captured from a QLM */
    push_bdk_enum(BDK_CONFIG_EYE_ZEROS);
    push_bdk_enum(BDK_CONFIG_EYE_SAMPLE_TIME);
    push_bdk_enum(BDK_CONFIG_EYE_SETTLE_TIME);

    /* SGPIO configuration */
    push_bdk_enum(BDK_CONFIG_SGPIO_SCLOCK_FREQ);
    push_bdk_enum(BDK_CONFIG_SGPIO_PIN_POWER);
    push_bdk_enum(BDK_CONFIG_SGPIO_PIN_SCLOCK);
    push_bdk_enum(BDK_CONFIG_SGPIO_PIN_SLOAD);
    push_bdk_enum(BDK_CONFIG_SGPIO_PIN_SDATAOUT);

    /* VRM temperature throttling */
    push_bdk_enum(BDK_CONFIG_VRM_TEMP_TRIP);
    push_bdk_enum(BDK_CONFIG_VRM_TEMP_HIGH);
    push_bdk_enum(BDK_CONFIG_VRM_TEMP_LOW);
    push_bdk_enum(BDK_CONFIG_VRM_THROTTLE_NORMAL);
    push_bdk_enum(BDK_CONFIG_VRM_THROTTLE_THERM);
}

