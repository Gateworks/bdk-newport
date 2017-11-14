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
BDK_REQUIRE_DEFINE(FS_PCIE);

static int pcie_read(__bdk_fs_dev_t *handle, void *buffer, int length)
{
    int pcie_port = handle->dev_index;
    bdk_node_t node = handle->dev_node;

    uint64_t base_address = bdk_pcie_get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    uint64_t offset = handle->location;
    if (offset >= (2ull << 36)) /* This assume PREFETCH follows NORMAL */
    {
        bdk_error("PCIe address outside of SLI regions\n");
        return -1;
    }
    switch (length)
    {
        case 1:
            *(uint8_t *)buffer = bdk_read64_uint8(base_address + offset);
            break;
        case 2:
            *(uint16_t *)buffer = bdk_read64_uint16(base_address + offset);
            break;
        case 4:
            *(uint32_t *)buffer = bdk_read64_uint32(base_address + offset);
            break;
        case 8:
            *(uint64_t *)buffer = bdk_read64_uint64(base_address + offset);
            break;
        default:
        {
            const void *ptr = bdk_phys_to_ptr(base_address + offset);
            memcpy(buffer, ptr, length);
            break;
        }
    }
    return length;
}


static int pcie_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    int pcie_port = handle->dev_index;
    bdk_node_t node = handle->dev_node;

    uint64_t base_address = bdk_pcie_get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    uint64_t offset = handle->location;
    if (offset >= (2ull << 36)) /* This assume PREFETCH follows NORMAL */
    {
        bdk_error("PCIe address outside of SLI regions\n");
        return -1;
    }
    switch (length)
    {
        case 1:
            bdk_write64_uint8(base_address + offset, *(uint8_t*)buffer);
            break;
        case 2:
            bdk_write64_uint16(base_address + offset, *(uint16_t*)buffer);
            break;
        case 4:
            bdk_write64_uint32(base_address + offset, *(uint32_t*)buffer);
            break;
        case 8:
            bdk_write64_uint64(base_address + offset, *(uint64_t*)buffer);
            break;
        default:
        {
            void *ptr = bdk_phys_to_ptr(base_address + offset);
            memcpy(ptr, buffer, length);
            break;
        }
    }
    return length;
}

static const __bdk_fs_dev_ops_t bdk_fs_dev_pcie_ops =
{
    .open = NULL,
    .close = NULL,
    .read = pcie_read,
    .write = pcie_write,
};

int __bdk_fs_pcie_init(void)
{
    int num_pcie = bdk_pcie_get_num_ports(bdk_numa_master());
    for (int p = 0; p < num_pcie; p++)
    {
        if (bdk_fs_register_dev("pcie", p, &bdk_fs_dev_pcie_ops))
            return -1;
    }
    return 0;
}
