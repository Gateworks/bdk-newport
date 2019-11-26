/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * Functions for reporting DRAM init status through GPIOs.
 * Useful for triggering scopes and such. Internal use only.
 */

extern void pulse_gpio_pin(bdk_node_t node, int pin, int usecs);

