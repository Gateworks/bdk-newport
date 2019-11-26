/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

/**
 * Configure TWSI on all nodes as part of booting
 */
void bdk_boot_twsi(void)
{
    int blob_length = 0;
    const char *blob = bdk_config_get_blob(&blob_length, BDK_CONFIG_TWSI_WRITE);
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
                bdk_error("Parsing TWSI sleep failed: %s\n", str);
                break;
            }
            BDK_TRACE(INIT, "BOOT-TWSI: Sleep %dms\n", delay);
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
                bdk_error("Parsing TWSI gpio failed: %s\n", str);
                break;
            }
            BDK_TRACE(INIT, "BOOT-TWSI: Set N%d.GPIO%d=%d\n", node, gpio, state);
            bdk_device_t *device = bdk_device_gpio_lookup(NULL, -1);
            bdk_device_gpio_setup(device, gpio, true, state, false, false);
        }
        else
        {
            /* Read the parameters from the write */
            int node = 0;
            int twsi_id = 0;
            int dev_addr = 0;
            int internal_addr = 0;
            int num_bytes = 0;
            int ia_width_bytes = 0;
            uint64_t data = 0;
            int count = sscanf(str, "%i,%i,%i,%i,%i,%i,%li", &node, &twsi_id, &dev_addr, &internal_addr, &num_bytes, &ia_width_bytes, &data);
            if (count != 7)
            {
                bdk_error("Parsing TWSI write failed: %s\n", str);
                break;
            }
            if (node == -1)
                node = bdk_numa_local();
            BDK_TRACE(INIT, "BOOT-TWSI: Write N%d.TWSI%d dev=0x%x, ia=0x%x, ia_width=%d, bytes=%d, data=0x%lx\n",
                node, twsi_id, dev_addr, internal_addr, ia_width_bytes, num_bytes, data);
            /* Perform the write */
            bdk_device_t *twsi_device = bdk_device_lookup(node, BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), twsi_id);
            if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr, num_bytes, ia_width_bytes, data))
            {
                bdk_error("TWSI write failed: %s\n", str);
                break;
            }
        }

        /* Move to the next string */
        str += strlen(str) + 1;
    }
}
