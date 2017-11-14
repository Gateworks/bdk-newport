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
            bdk_gpio_initialize(node, gpio, 1, state);
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
