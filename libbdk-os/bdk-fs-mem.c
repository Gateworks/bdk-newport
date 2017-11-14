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
BDK_REQUIRE_DEFINE(FS_MEM);

static int mem_read(__bdk_fs_dev_t *handle, void *buffer, int length)
{
    uint64_t address = bdk_numa_get_address(handle->dev_node, handle->location);
    /* Check location to avoid warning from bdk_phys_to_ptr */
    const void *ptr = (address) ? bdk_phys_to_ptr(address) : NULL;
    memcpy(buffer, ptr, length);
    return length;
}


static int mem_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    uint64_t address = bdk_numa_get_address(handle->dev_node, handle->location);
    /* Check location to avoid warning from bdk_phys_to_ptr */
    void *ptr = (address) ? bdk_phys_to_ptr(address) : NULL;
    memcpy(ptr, buffer, length);
    return length;
}

static const __bdk_fs_dev_ops_t bdk_fs_mem_ops =
{
    .open = NULL,
    .close = NULL,
    .read = mem_read,
    .write = mem_write,
};

int __bdk_fs_mem_init(void)
{
    return bdk_fs_register_dev("mem", 0, &bdk_fs_mem_ops);
}
