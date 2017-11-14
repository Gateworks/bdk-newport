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
#include <fcntl.h>

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_SATA);

/**
 * Open a SATA disk for read/write. The SATA device is treated as raw block
 * storage without any filesystem. All reads and writes must be in 512 byte
 * chunks, aligned on 512 byte boundaries. SATA read / writes complete sectors
 * at a time.
 *
 * @param handle Device handle
 * @param flags  Standard open flags
 *
 * @return Zero on success, negative on failure
 */
static int sata_open(__bdk_fs_dev_t *handle, int flags)
{
    bdk_node_t node = handle->dev_node;
    int sata = handle->dev_index;

    /* Determine how many SATA ports are connected to the controller */
    int num_ports = bdk_sata_get_ports(node, sata);

    /* If no ports are connected, call initialize to restart the controller */
    if (num_ports == 0)
    {
        if (bdk_sata_initialize(node, sata))
        {
            bdk_error("N%d.SATA%d: Initialization failed\n", node, sata);
            return -1;
        }
        num_ports = bdk_sata_get_ports(node, sata);
    }

    /* We should have one port, If we don't then the QLMs aren't configured for
        SATA */
    if (num_ports == 0)
    {
        bdk_error("N%d.SATA%d: Controller not connected to any ports\n", node, sata);
        return -1;
    }

    return 0;
}

/**
 * Read from a SATA device
 *
 * @param handle FS handle
 * @param buffer Buffer to fill
 * @param length Length to fill, must be a multiple of 512
 *
 * @return Number of bytes read, or negative on error
 */
static int sata_read(__bdk_fs_dev_t *handle, void *buffer, int length)
{
    /* Extract the controller and node */
    int sata = handle->dev_index;
    bdk_node_t node = handle->dev_node;

    /* Make sure we're working with complete sectors */
    if ((length & 511) || (handle->location & 511))
    {
        bdk_error("N%d.SATA%d: File IO must be in multiples of 512 bytes\n", node, sata);
        return -1;
    }

    /* Do the read */
    if (bdk_sata_read(node, sata, 0, handle->location >> 9, length >> 9, buffer))
    {
        //bdk_error("N%d.SATA%d: Read error\n", node, sata);
        return 0;
    }
    else
        return length;
}

/**
 * Write to a SATA device
 *
 * @param handle FS handle
 * @param buffer Buffer to write
 * @param length Length to buffer, must be a multiple of 512
 *
 * @return Number of bytes written, or negative on error
 */
static int sata_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    /* Extract the controller and node */
    int sata = handle->dev_index;
    bdk_node_t node = handle->dev_node;

    /* Make sure we're working with complete sectors */
    if ((length & 511) || (handle->location & 511))
    {
        bdk_error("N%d.SATA%d: File IO must be in multiples of 512 bytes\n", node, sata);
        return -1;
    }

    /* Do the write */
    if (bdk_sata_write(node, sata, 0, handle->location >> 9, length >> 9, buffer))
    {
        bdk_error("N%d.SATA%d: Write error\n", node, sata);
        return 0;
    }
    else
        return length;
}

static const __bdk_fs_dev_ops_t bdk_fs_sata_ops =
{
    .open = sata_open,
    .close = NULL,
    .read = sata_read,
    .write = sata_write,
};

int __bdk_fs_sata_init(void)
{
    int num_sata = bdk_sata_get_controllers(bdk_numa_master());
    for (int sata = 0; sata < num_sata; sata++)
    {
        if (bdk_fs_register_dev("sata", sata, &bdk_fs_sata_ops))
            return -1;
    }
    return 0;
}
