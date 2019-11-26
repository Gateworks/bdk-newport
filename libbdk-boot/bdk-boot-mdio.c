/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

/**
 * Configure MDIO on all nodes as part of booting
 */
void bdk_boot_mdio(void)
{
    int blob_length = 0;
    const char *blob = bdk_config_get_blob(&blob_length, BDK_CONFIG_MDIO_WRITE);
    if (!blob)
        return;
    const char *done = blob + blob_length;
    const char *str = blob;
    while (str < done)
    {
        /* Check for the special case of a sleep line specifying a delay (ms) */
        if (strncmp(str, "sleep,", 6) == 0)
        {
            int delay = 0;
            int count = sscanf(str, "sleep,%i", &delay);
            if (count != 1)
            {
                bdk_error("Parsing MDIO sleep failed: %s\n", str);
                break;
            }
            bdk_wait_usec(delay * 1000);
        }
        /* Check for the special case of a gpio line specifying a new
           gpio state */
        else if (strncmp(str, "gpio,", 5) == 0)
        {
            int node = 0;
            int gpio = 0;
            int state = 0;
            int count = sscanf(str, "gpio,%i,%i,%i", &node, &gpio, &state);
            if (count != 3)
            {
                bdk_error("Parsing MDIO gpio failed: %s\n", str);
                break;
            }
            bdk_device_t *device = bdk_device_gpio_lookup(NULL, -1);
            bdk_device_gpio_setup(device, gpio, true, state, false, false);
        }
        else
        {
            /* Read the parameters from the write */
            int clause = 0;
            int node = 0;
            int bus_id = 0;
            int phy_id = 0;
            int device = 0;
            int location = 0;
            int val = 0;
            int count = sscanf(str, "%i,%i,%i,%i,%i,%i,%i", &clause, &node, &bus_id, &phy_id, &device, &location, &val);
            if (count != 7)
            {
                bdk_error("Parsing MDIO write failed: %s\n", str);
                break;
            }
            if (node == -1)
                node = bdk_numa_local();

            /* Perform the write */
            int status;
            if (clause == 45)
                status = bdk_mdio_45_write(node, bus_id, phy_id, device, location, val);
            else if (clause == 22)
                status = bdk_mdio_write(node, bus_id, phy_id, location, val);
            else
            {
                bdk_error("MDIO write with unsupported clause: %s\n", str);
                break;
            }
            if (status)
            {
                bdk_error("MDIO write failed: %s\n", str);
                break;
            }
        }

        /* Move to the next string */
        str += strlen(str) + 1;
    }
}
