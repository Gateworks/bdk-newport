/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_PWM_ISL6813X);

/* Note this driver assumes both pages of the ISL6813X are in use. Page 0
   controls VDD_CORE and page 1 controls VDD_SYS */

static const uint64_t ID_68134 = 0x001fd249; /* ID is returned LSB */
static const uint64_t ID_68137 = 0x0027d249; /* ID is returned LSB */
static const int PAGE_VDD_CORE = 0;
static const int PAGE_VDD_SYS = 1;

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.gpio.device = bdk_driver_extract_device(config_str, "twsi");
    device->priv.gpio.address = bdk_driver_extract_int(config_str, "addr", 0, 127);
    BDK_TRACE(DEVICE, "%s: ISL6813X on TWSI=%s, ADDR=%d\n",
        device->name, device->priv.gpio.device->name, device->priv.gpio.address);
}

static int write_verify(bdk_device_t *device, int reg, int val)
{
    bdk_device_twsi_write_ia(device->priv.gpio.device,
        device->priv.gpio.address, reg, 1, 1, val);
    int64_t data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, reg, 1, 1);
    if (data != val)
    {
        bdk_error("%s: Write of reg 0x%02x failed. Expected 0x%02x, got 0x%02lx\n", device->name, reg, val, data);
        return -1;
    }
    return 0;
}

/**
 * Initialize the device, nothing needed
 *
 * @param device to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    /* Read IC_DEVICE_ID, 0xad. The ISL actually requires a 5 byte read as the
       length preceeds the data. We only support 4 bytes at most, so we don't
       check one ID byte */
    int64_t data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 0xad, 4, 1);
    int64_t len = bdk_extract(data, 24, 8);
    if (len != 4)
    {
        bdk_error("%s: Reports incorrect ID length of %ld, expected 4\n", device->name, len);
        goto fail;
    }
    data = bdk_extract(data, 0, 24);
    if ((data != (ID_68134 >> 8)) && (data != (ID_68137 >> 8)))
    {
        bdk_error("%s: Reports incorrect ID of 0x%06lx##, expected 0x%08lx or 0x%08lx\n",
            device->name, data, ID_68134, ID_68137);
        goto fail;
    }

    BDK_TRACE(DEVICE, "%s: ID is correct (0x%06lx##), enabling AVS for VDD_CORE\n", device->name, data);
    /* Set PAGE, 0x00, to zero, selecting page 0 */
    if (write_verify(device, 0x00, PAGE_VDD_CORE))
        goto fail;
    /* Set OPERATION, 0x01, to 0x30. AVSBus target rail voltage */
    if (write_verify(device, 0x01, 0x30))
        goto fail;
    BDK_TRACE(DEVICE, "%s: Enabling AVS for VDD_SYS\n", device->name);
    /* Set PAGE, 0x00, to one, selecting page 1 */
    if (write_verify(device, 0x00, PAGE_VDD_SYS))
        goto fail;
    /* Set OPERATION, 0x01, to 0x30. AVSBus target rail voltage */
    if (write_verify(device, 0x01, 0x30))
        goto fail;
    /* Set PAGE, 0x00, to zero, selecting page 0 */
    if (write_verify(device, 0x00, PAGE_VDD_CORE))
        goto fail;
    return 0;

fail:
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        bdk_error("%s: VRM problem detected - check AVS bus enable\n", device->name);
        switch (bdk_config_get_int(BDK_CONFIG_SCP_FAIL_ACTION, device->node))
        {
            case 1: /* Reboot the system */
                printf("Rebooting per SCP fail action\n");
                bdk_reset_chip(device->node);
                break;
            case 2: /* Halt forever*/
                printf("Hanging per SCP fail action\n");
                __bdk_die();
                break;
            default: /* Continue */
                printf("Continuing per SCP fail action\n");
                break;
        }
    }
    return -1;
}

bdk_driver_t __bdk_driver_pwm_isl6813x = {
    .name = "PWM-ISL6813X",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_NONE,
};
