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
#include "libbdk-arch/bdk-csrs-uaa.h"

static int uart_read(__bdk_fs_dev_t *handle, void *buffer, int length)
{
    int count = 0;
    int id = handle->dev_index;
    bdk_node_t node = handle->dev_node;

    BDK_CSR_INIT(fr, node, BDK_UAAX_FR(id));
    while (!fr.s.rxfe && length)
    {
        BDK_CSR_INIT(dr, node, BDK_UAAX_DR(id));
        int has_error = dr.s.fe;
        *(uint8_t*)buffer = dr.s.data;
        fr.u = BDK_CSR_READ(node, BDK_UAAX_FR(id));
        /* Character has an error, so skip it */
        if (has_error)
            continue;
        buffer++;
        count++;
        length--;
    }
    return count;
}

static void uart_write_byte(bdk_node_t node, int id, uint8_t byte)
{
    static bdk_spinlock_t tx_lock;
    BDK_CSR_INIT(fr, node, BDK_UAAX_FR(id));

    /* Spin until there is room */
    while (1)
    {
        bdk_spinlock_lock(&tx_lock);
        fr.u = BDK_CSR_READ(node, BDK_UAAX_FR(id));
        if (!fr.s.txff) /* Are we not full? */
        {
            /* Write the byte */
            BDK_CSR_WRITE(node, BDK_UAAX_DR(id), byte);
            bdk_spinlock_unlock(&tx_lock);
            break;
        }
        bdk_spinlock_unlock(&tx_lock);
        do
        {
            bdk_thread_yield();
            fr.u = BDK_CSR_READ(node, BDK_UAAX_FR(id));
        } while (fr.s.txff); /* Spin while full */
    }
}

static int uart_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    int l = length;
    int id = handle->dev_index;
    bdk_node_t node = handle->dev_node;
    const char *p = buffer;

    while (l--)
        uart_write_byte(node, id, *p++);
    return length;
}

const __bdk_fs_dev_ops_t bdk_fs_uart_ops =
{
    .open = NULL,
    .close = NULL,
    .read = uart_read,
    .write = uart_write,
};

