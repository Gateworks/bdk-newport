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
#include <malloc.h>

static bdk_spinlock_t free_list_lock;
static void *free_list;

static int segment_init(void)
{
    bdk_spinlock_init(&free_list_lock);

    const int num_bufs = bdk_config_get_int(BDK_CONFIG_NUM_PACKET_BUFFERS);
    const int buf_size = bdk_config_get_int(BDK_CONFIG_PACKET_BUFFER_SIZE);

    bdk_spinlock_lock(&free_list_lock);

    /* Allocate a list of buffers */
    free_list = memalign(BDK_CACHE_LINE_SIZE, num_bufs * buf_size);
    if (!free_list)
    {
        bdk_spinlock_unlock(&free_list_lock);
        bdk_error("Unable to allocate packet buffers\n");
        return -1;
    }

    /* Create a linked list of segments where each segment points to the next */
    void *ptr = free_list;
    for (int i = 0; i < num_bufs-1; i++)
    {
        *(void **)ptr = ptr + buf_size;
        ptr += buf_size;
    }
    *(void **)ptr = NULL;

    bdk_spinlock_unlock(&free_list_lock);
    return 0;
}

static uint64_t segment_alloc(int length)
{
    uint64_t result;
    bdk_spinlock_lock(&free_list_lock);
    if (free_list)
    {
        result = bdk_ptr_to_phys(free_list);
        free_list = *(void **)free_list;
    }
    else
        result = 0;
    bdk_spinlock_unlock(&free_list_lock);
    return result;
}

static void segment_free(uint64_t address, int length)
{
    void *ptr = bdk_phys_to_ptr(address);
    bdk_spinlock_lock(&free_list_lock);
    *(void **)ptr = free_list;
    free_list = ptr;
    bdk_spinlock_unlock(&free_list_lock);
}

const __bdk_if_global_ops_t __bdk_if_global_ops_cn8xxx = {
    .init = segment_init,
    .alloc = segment_alloc,
    .free = segment_free,
};

