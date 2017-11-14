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
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"

#include "bdk-driver-sgpio.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(SGPIO);

/* To maintain backwards compatibility for the old MDIO API we need
   to lookup the MDIO device on the ECAM bus by ID. This defines
   the ID */
#define SGPIO_DEVID (0xa000177d | (BDK_PCC_DEV_IDL_E_SGP << 16))

#define BDK_SGPIO_SCLOCK_FREQ_MIN   128
#define BDK_SGPIO_SCLOCK_FREQ_MAX   100000

static void bdk_sgpio_set_hold(const bdk_device_t *device, int hold)
{
    BDK_BAR_MODIFY(c, device, BDK_SGP_IMP_CTL, c.s.hold = !!hold);
}

/**
 * Get the SGPIO controller state
 *
 * @param node      CPU node number
 *
 * @return          1 == Controller is enabled, 0 == Controller is disabled
 */
int bdk_sgpio_is_enabled(bdk_node_t node)
{
    const bdk_device_t *device = bdk_device_lookup(node, SGPIO_DEVID, 0);

    BDK_BAR_INIT(c, device, BDK_SGP_CFG0);
    return c.s.ena;
}

/**
 * Set the mode for a specific LED.
 *
 * @param node      CPU node number
 * @param drive     Drive number of LED (0-15)
 * @param led       LED type:
 *                       BDK_SGPIO_LED_ACT
 *                       BDK_SGPIO_LED_LOC
 *                       BDK_SGPIO_LED_ERR
 * @param state     LED state:
 *                      BDK_SGPIO_STATIC_ON
 *                      BDK_SGPIO_STATIC_OFF
 *                      BDK_SGPIO_BLINK
 *
 * @return
 */
void bdk_sgpio_set_led_state(bdk_node_t node, int drive, int led, int state)
{
    const bdk_device_t *device = bdk_device_lookup(node, SGPIO_DEVID, 0);

    if (drive >= 16)
    {
        bdk_warn("SGPIO: Invalid drive number %d\n", drive);
        return;
    }

    if (led > BDK_SGPIO_LED_ERR)
    {
        bdk_warn("SGPIO: Invalid LED type %d\n", led);
        return;
    }

    int reg = (drive >> 2) & 0x03;
    BDK_BAR_INIT(sgp_tx, device, BDK_SGP_TXX(reg));

    switch (drive & 0x03)
    {
        case 0:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: sgp_tx.s.d0_act = state; break;
                case BDK_SGPIO_LED_LOC: sgp_tx.s.d0_loc = state; break;
                case BDK_SGPIO_LED_ERR: sgp_tx.s.d0_err = state; break;
            }
            break;
        case 1:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: sgp_tx.s.d1_act = state; break;
                case BDK_SGPIO_LED_LOC: sgp_tx.s.d1_loc = state; break;
                case BDK_SGPIO_LED_ERR: sgp_tx.s.d1_err = state; break;
            }
            break;
        case 2:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: sgp_tx.s.d2_act = state; break;
                case BDK_SGPIO_LED_LOC: sgp_tx.s.d2_loc = state; break;
                case BDK_SGPIO_LED_ERR: sgp_tx.s.d2_err = state; break;
            }
            break;
        case 3:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: sgp_tx.s.d3_act = state; break;
                case BDK_SGPIO_LED_LOC: sgp_tx.s.d3_loc = state; break;
                case BDK_SGPIO_LED_ERR: sgp_tx.s.d3_err = state; break;
            }
            break;
    }
    BDK_BAR_WRITE(device, BDK_SGP_TXX(reg), sgp_tx.u);
}

/**
 * Get the mode for a specific LED.
 *
 * @param node      CPU node number
 * @param drive     Drive number of LED (0-15)
 * @param led       LED type:
 *                       BDK_SGPIO_LED_ACT
 *                       BDK_SGPIO_LED_LOC
 *                       BDK_SGPIO_LED_ERR
 *
 * @return          LED state:
 *                      BDK_SGPIO_STATIC_ON
 *                      BDK_SGPIO_STATIC_OFF
 *                      BDK_SGPIO_BLINK
 */
int bdk_sgpio_get_led_state(bdk_node_t node, int drive, int led)
{
    const bdk_device_t *device = bdk_device_lookup(node, SGPIO_DEVID, 0);
    int state = -1;
    int reg = (drive >> 2) & 0x03;
    BDK_BAR_INIT(sgp_tx, device, BDK_SGP_TXX(reg));

    switch (drive & 0x03)
    {
        case 0:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: state = sgp_tx.s.d0_act; break;
                case BDK_SGPIO_LED_LOC: state = sgp_tx.s.d0_loc; break;
                case BDK_SGPIO_LED_ERR: state = sgp_tx.s.d0_err; break;
            }
            break;
        case 1:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: state = sgp_tx.s.d1_act; break;
                case BDK_SGPIO_LED_LOC: state = sgp_tx.s.d1_loc; break;
                case BDK_SGPIO_LED_ERR: state = sgp_tx.s.d1_err; break;
            }
            break;
        case 2:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: state = sgp_tx.s.d2_act; break;
                case BDK_SGPIO_LED_LOC: state = sgp_tx.s.d2_loc; break;
                case BDK_SGPIO_LED_ERR: state = sgp_tx.s.d2_err; break;
            }
            break;
        case 3:
            switch (led)
            {
                case BDK_SGPIO_LED_ACT: state = sgp_tx.s.d3_act; break;
                case BDK_SGPIO_LED_LOC: state = sgp_tx.s.d3_loc; break;
                case BDK_SGPIO_LED_ERR: state = sgp_tx.s.d3_err; break;
            }
            break;
    }
    return state;
}

/**
 * Enable / disable controller
 *
 * @param node      CPU node number
 * @param ena       zero = disable, non-zero = enable
 *
 * @return
 */
void bdk_sgpio_enable_controller(bdk_node_t node, int ena)
{
    const bdk_device_t *device = bdk_device_lookup(node, SGPIO_DEVID, 0);

    if (ena)
    {
        BDK_BAR_MODIFY(c, device, BDK_SGP_CFG0, c.s.ena = 1);
        bdk_sgpio_set_hold(device, 0);
    }
    else
    {
        bdk_sgpio_set_hold(device, 1);
        BDK_BAR_MODIFY(c, device, BDK_SGP_CFG0, c.s.ena = 0);

        /* Wait for BUSY flag to clear */
        int rc = BDK_BAR_WAIT_FOR_FIELD(device, BDK_SGP_IMP_CTL, busy, ==, 0, 100000);
        if (-1 == rc)
        {
            bdk_warn("SGPIO: Timeout waiting for controller disable.\n");
        }
    }
}

/**
 * Set the controller's SCLOCK frequency
 *
 * @param node      CPU node number
 * @param freq      Frequency to set
 *
 * @return Zero on success, negative on failure
 */
int bdk_sgpio_set_sclock(bdk_node_t node, int freq)
{
    const bdk_device_t *device = bdk_device_lookup(node, SGPIO_DEVID, 0);

    if ((freq < BDK_SGPIO_SCLOCK_FREQ_MIN) || (freq > BDK_SGPIO_SCLOCK_FREQ_MAX))
    {
        bdk_warn("SGPIO: Invalid SCLOCK frequency (%d Hz) requested. Ignoring.", freq);
        return -1;
    }

    /* Clock divider can only be set if controller is disabled. */
    int was_enabled = bdk_sgpio_is_enabled(node);
    if (was_enabled)
    {
        bdk_sgpio_enable_controller(node, 0);
    }

    /* Set up SCLOCK */
    int clk = bdk_clock_get_rate(device->node, BDK_CLOCK_SCLK);
    int div = clk / freq;
    BDK_BAR_MODIFY(c, device, BDK_SGP_IMP_CLK, c.s.div = div);

    /* Set up Seconds clock */
    int div_sec = freq / 64;
    BDK_BAR_MODIFY(c, device, BDK_SGP_IMP_SEC_CLK, c.s.div = div_sec);

    if (was_enabled)
    {
        bdk_sgpio_enable_controller(node, 1);
    }
    return 0;
}

/**
 * Set up SGPIO pin muxing based on environment.
 *
 * @param node      CPU node number
 *
 * @return Zero on success, negative on failure
 */
int bdk_sgpio_setup_gpio_pins(const bdk_node_t node)
{
    const bdk_device_t *device = bdk_device_lookup(node, SGPIO_DEVID, 0);

    /* Set up SGPIO pin muxing */
    int power[BDK_NUMA_MAX_NODES];
    int sdataout[4], sclock, sload;

    /* Power control is optional, not failing if not configured. */
    power[device->node] = bdk_config_get_int(BDK_CONFIG_SGPIO_PIN_POWER, device->node);
    sclock = bdk_config_get_int(BDK_CONFIG_SGPIO_PIN_SCLOCK, device->node);
    sload  = bdk_config_get_int(BDK_CONFIG_SGPIO_PIN_SLOAD, device->node);
    for (int i = 0; i < 4; i++)
        sdataout[i] = bdk_config_get_int(BDK_CONFIG_SGPIO_PIN_SDATAOUT, device->node, i);

    if ((-1 == sclock) || (-1 == sload) ||
        ((-1 == sdataout[0]) && (-1 == sdataout[1]) && (-1 == sdataout[2]) && (-1 == sdataout[3])))
    {
        return -1;
    }

    /* Mux SDATAOUT lines */
    for (int i = 0; i < 4; i++)
    {
        if (sdataout[i] != -1)
        {
            if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
                bdk_gpio_select_pin(device->node, sdataout[i],
                                    BDK_GPIO_PIN_SEL_E_SGPIO_SDATAOUTX_CN88XX(i));
            else if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
                bdk_gpio_select_pin(device->node, sdataout[i],
                                    BDK_GPIO_PIN_SEL_E_SGPIO_SDATAOUTX_CN83XX(i));
            else if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
                bdk_gpio_select_pin(device->node, sdataout[i],
                                    BDK_GPIO_PIN_SEL_E_SGPIO_SDATAOUTX_CN81XX(i));
            else
                bdk_fatal("Update SDATAOUTX in %s()\n", __FUNCTION__);
        }
    }

    /* Mux SCLOCK and SLOAD lines */
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
    {
        bdk_gpio_select_pin(device->node, sclock, BDK_GPIO_PIN_SEL_E_SGPIO_SCLOCK_CN88XX);
        bdk_gpio_select_pin(device->node, sload, BDK_GPIO_PIN_SEL_E_SGPIO_SLOAD_CN88XX);
    }
    else if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
    {
        bdk_gpio_select_pin(device->node, sclock, BDK_GPIO_PIN_SEL_E_SGPIO_SCLOCK_CN83XX);
        bdk_gpio_select_pin(device->node, sload, BDK_GPIO_PIN_SEL_E_SGPIO_SLOAD_CN83XX);
    }
    else if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
    {
        bdk_gpio_select_pin(device->node, sclock, BDK_GPIO_PIN_SEL_E_SGPIO_SCLOCK_CN81XX);
        bdk_gpio_select_pin(device->node, sload, BDK_GPIO_PIN_SEL_E_SGPIO_SLOAD_CN81XX);
    }
    else
        bdk_fatal("Update SCLOCK/SLOAD in %s()\n", __FUNCTION__);

    /* Enable power, if configured */
    if (-1 != power[device->node])
        bdk_gpio_initialize(device->node, power[device->node], 1, 1);

    return 0;
}

/**
 * The SGPIO probe function
 *
 * @param device SGPIO to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.SGPIO", device->node);
    return 0;
}

/**
 * Initialize the SGPIO controller.
 *  - Set up the SGPIO pin muxing as per configuration environment.
 *  - Turn all LEDs off
 *  - Set the blink rate to 1/2 second
 *  - Enable the controller
 *
 * @param device SGPIO to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    bdk_node_t node = device->node;

    /* Set up SGPIO pin muxing from environment. */
    if (-1 == bdk_sgpio_setup_gpio_pins(node))
    {
        /* No valid configuration found -> Skip configuration. */
        return 0;
    }

    /* Configure all activity LEDs to be controlled by the SATA controller, LOC
     * and ERR are off. */
    for (int drv = 0 ; drv < 16; drv++)
    {
        /* Set mode */
        bdk_sgpio_set_led_state(node, drv, BDK_SGPIO_LED_ACT, BDK_SGP_TX_ACT_E_STATIC_OFF);
        bdk_sgpio_set_led_state(node, drv, BDK_SGPIO_LED_LOC, BDK_SGP_TX_ACT_E_STATIC_OFF);
        bdk_sgpio_set_led_state(node, drv, BDK_SGPIO_LED_ERR, BDK_SGP_TX_ACT_E_STATIC_OFF);

        /* Map the drive index, enable presence detect. */
        BDK_BAR_MODIFY(c, device, BDK_SGP_IMP_DRIVEX(drv), c.s.pres_det = 1; c.s.ctrlr = drv);
    }

    /* Set blink rate A to 1/2 seconds (4/8) */
    BDK_BAR_MODIFY(c, device, BDK_SGP_CFG1, c.s.blink_a = 4);

    /* Set SCLOCK */
    int sclock_freq = bdk_config_get_int(BDK_CONFIG_SGPIO_SCLOCK_FREQ, device->node);
    bdk_sgpio_set_sclock(node, sclock_freq);

    /* Enable controller */
    bdk_sgpio_enable_controller(node, 1);
    return 0;
}

bdk_driver_t __bdk_driver_sgpio = {
    .id = SGPIO_DEVID,
    .probe = probe,
    .init = init,
};
