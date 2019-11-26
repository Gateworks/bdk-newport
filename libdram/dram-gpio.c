/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

void pulse_gpio_pin(bdk_node_t node, int pin, int usecs)
{
    static uint64_t configured_pin = 0;
    static bdk_device_t *gpio_device = NULL;

    if (!gpio_device)
        gpio_device = bdk_device_gpio_lookup(NULL, -1);

    if (!(configured_pin & 1ull << pin))
    {
        configured_pin |= 1ull << pin;
        bdk_device_gpio_setup(gpio_device, pin, true, 0, false, false);
    }
    bdk_device_gpio_set0(gpio_device, pin >> 6, 1ull << (pin & 63));
    bdk_wait_usec(usecs);
    bdk_device_gpio_set1(gpio_device, pin >> 6, 1ull << (pin & 63));
}

