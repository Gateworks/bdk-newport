/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_TWSI_PCA9548);

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.twsi.device = bdk_driver_extract_device(config_str, "twsi");
    device->priv.twsi.address = bdk_driver_extract_int(config_str, "addr", 0, 127);
    device->priv.twsi.channel = bdk_driver_extract_int(config_str, "chan", 0, 7);
    BDK_TRACE(DEVICE, "%s: PCA9548 on TWSI=%s, ADDR=%d, CHAN=%d\n",
        device->name, device->priv.twsi.device->name, device->priv.twsi.address,
        device->priv.twsi.channel);
}

static void do_update(bdk_device_t *device, int select)
{
    int reg = (select < 0) ? 0 : (1 << select);

    BDK_TRACE(DEVICE, "%s: Write 0x%x, selecting channel %d\n", device->name, reg, select);

    if (bdk_device_twsi_write_ia(device->priv.twsi.device,
            device->priv.twsi.address, 0, 1, 0, reg))
    {
        bdk_error("%s: Error updating state\n", device->name);
    }
}

/**
 * TWSI init() function
 *
 * @param device TWSI to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    do_update(device, -1);
    return 0;
}

/**
 * Do a twsi read from a 7 bit device address using an (optional)
 * internal address. Up to 4 bytes can be read at a time.
 *
 * @param device    Device to access
 * @param dev_addr  Device address (7 bit)
 * @param internal_addr
 *                  Internal address.  Can be 0, 1 or 2 bytes in width
 * @param num_bytes Number of data bytes to read (1-4)
 * @param ia_width_bytes
 *                  Internal address size in bytes (0, 1, or 2)
 *
 * @return Read data, or -1 on failure
 */
static int64_t read_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes)
{
    do_update(device, device->priv.twsi.channel);
    int64_t result = bdk_device_twsi_read_ia(device->priv.twsi.device, dev_addr, internal_addr, num_bytes, ia_width_bytes);
    do_update(device, -1);
    return result;
}

/**
 * Write 1-8 bytes to a TWSI device using an internal address.
 *
 * @param device    Device to access
 * @param dev_addr  TWSI device address (7 bit only)
 * @param internal_addr
 *                  TWSI internal address (0, 8, or 16 bits)
 * @param num_bytes Number of bytes to write (1-8)
 * @param ia_width_bytes
 *                  internal address width, in bytes (0, 1, 2)
 * @param data      Data to write.  Data is written MSB first on the twsi bus, and
 *                  only the lower num_bytes bytes of the argument are valid.  (If
 *                  a 2 byte write is done, only the low 2 bytes of the argument is
 *                  used.
 *
 * @return Zero on success, -1 on error
 */
static int write_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data)
{
    do_update(device, device->priv.twsi.channel);
    int result = bdk_device_twsi_write_ia(device->priv.twsi.device, dev_addr, internal_addr, num_bytes, ia_width_bytes, data);
    do_update(device, -1);
    return result;
}

bdk_driver_t __bdk_driver_twsi_pca9548 = {
    .api = BDK_DEVICE_API_TWSI,
    .name = "TWSI-PCA9548",
    .init = init,
    .add = add,
    .funcs.twsi.read_ia = read_ia,
    .funcs.twsi.write_ia = write_ia,
};
