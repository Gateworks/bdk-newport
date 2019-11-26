/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_MMC);

static int mmc_open(__bdk_fs_dev_t *handle, int flags)
{
    uint64_t size = bdk_mmc_initialize(handle->dev_node, handle->dev_index);
    if (size == 0)
        return -1;
    return 0;
}

static int mmc_read(__bdk_fs_dev_t *handle, void *buffer, int length)
{
    /* Make sure we're working with complete sectors */
    if ((length & 511) || (handle->location & 511))
    {
        bdk_error("N%d.MMC%d: File IO must be in multiples of 512 bytes\n", handle->dev_node, handle->dev_index);
        return -1;
    }
    int status = bdk_mmc_read(handle->dev_node, handle->dev_index, handle->location, buffer, length);
    if (status)
        return -1;
    else
        return length;
}

static int mmc_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    /* Make sure we're working with complete sectors */
    if ((length & 511) || (handle->location & 511))
    {
        bdk_error("N%d.MMC%d: File IO must be in multiples of 512 bytes\n", handle->dev_node, handle->dev_index);
        return -1;
    }

    if (bdk_mmc_write(handle->dev_node, handle->dev_index, handle->location, buffer, length))
        return 0;
    else
        return length;
}

static const __bdk_fs_dev_ops_t bdk_fs_mmc_ops =
{
    .open = mmc_open,
    .close = NULL,
    .read = mmc_read,
    .write = mmc_write,
    .block_size = 512,
};

int __bdk_fs_mmc_init(void)
{
    for (int cs = 0; cs < 4; cs++)
    {
        if (bdk_fs_register_dev("mmc", cs, &bdk_fs_mmc_ops))
            return -1;
    }
    return 0;
}
