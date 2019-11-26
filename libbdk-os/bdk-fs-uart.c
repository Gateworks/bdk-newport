/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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

static int uart_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    static bdk_spinlock_t tx_lock;
    int l = length;
    int id = handle->dev_index;
    bdk_node_t node = handle->dev_node;
    const char *p = buffer;

    bdk_spinlock_lock(&tx_lock);
    while (l)
    {
        BDK_CSR_INIT(fr, node, BDK_UAAX_FR(id));
        if (!fr.s.txff) /* Are we not full? */
        {
            /* Write the byte */
            BDK_CSR_WRITE(node, BDK_UAAX_DR(id), *p++);
            l--;
        }
        else /* Spin while full */
        {
            bdk_spinlock_unlock(&tx_lock);
            do
            {
                bdk_thread_yield();
                fr.u = BDK_CSR_READ(node, BDK_UAAX_FR(id));
            } while (fr.s.txff);
            bdk_spinlock_lock(&tx_lock);
        }
    }
    bdk_spinlock_unlock(&tx_lock);
    return length;
}

const __bdk_fs_dev_ops_t bdk_fs_uart_ops =
{
    .open = NULL,
    .close = NULL,
    .read = uart_read,
    .write = uart_write,
};

