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
    /* Read one block into a temp buffer in case the buffer we received
       doesn't have enough space */
    char tmp[512];
    /* Force the read to be 512 byte aligned and only one block */
    int status = bdk_mmc_read(handle->dev_node, handle->dev_index, handle->location & -512, tmp, 512);
    if (status != 0)
        return -1;
    /* The caller may not be aligned, so drop data that he doesn't want */
    int offset = handle->location & 511;
    /* Limit the return length to one block */
    if (length > 512 - offset)
        length = 512 - offset;
    memcpy(buffer, tmp + offset, length);
    /* Return length may be much smaller than they originally wanted */
    return length;
}

static int mmc_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    uint64_t loc = handle->location;
    int write_count = 0;
    while (length)
    {
        /* Do a partial write if the update doesn't start on a block
           boundary or the length is shorter than a block */
        int partial = (loc & 511) || (length < 512);
        int len;
        if (partial) /* Partial block, do a read/modify/write */
        {
            /* Align on a block boundary */
            int offset = loc & 511;
            char tmp[512];
            if (bdk_mmc_read(handle->dev_node, handle->dev_index, loc & -512, tmp, 512))
                break;
            len = 512 - offset;
            if (len > length)
                len = length;
            memcpy(tmp + offset, buffer, len);
            if (bdk_mmc_write(handle->dev_node, handle->dev_index, loc & -512, tmp, 512))
                break;
        }
        else
        {
            len = length & -512;
            if (bdk_mmc_write(handle->dev_node, handle->dev_index, loc, buffer, len))
                break;
        }
        buffer += len;
        length -= len;
        loc += len;
        write_count += len;
    }
    return write_count;
}

static const __bdk_fs_dev_ops_t bdk_fs_mmc_ops =
{
    .open = mmc_open,
    .close = NULL,
    .read = mmc_read,
    .write = mmc_write,
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
