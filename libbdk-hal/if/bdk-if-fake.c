/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/* This file implements a fake ethernet device that loops to itself. It allows
   testing the BDK code without ties to real hardware */

/* This interface puts packets in a fixed size TX fifo, defined here. It is a
   circular list with a head and tail index. Transmit will fail if the fifo
   is full */
#define MAX_QUEUE 32
typedef struct
{
    int32_t next_rx; /* Atomic */
    int32_t tx_free; /* Atomic */
    bdk_if_packet_t queue[MAX_QUEUE];
} priv_t;

static void if_receive(int unused, void *hand);


static int if_num_interfaces(bdk_node_t node)
{
    return 4;
}

static int if_num_ports(bdk_node_t node, int interface)
{
    /* Only support one port per interface to make naming easier */
    return 1;
}

static int if_probe(bdk_if_handle_t handle)
{
    /* Change name to be something that might be meaningful to the user */
    const char *name_format;
    if (bdk_numa_is_only_one())
        name_format = "FAKE%d";
    else
        name_format = "N%d.FAKE%d";

    if (bdk_numa_is_only_one())
        snprintf(handle->name, sizeof(handle->name), name_format, handle->interface);
    else
        snprintf(handle->name, sizeof(handle->name), name_format, handle->node, handle->interface);
    handle->name[sizeof(handle->name)-1] = 0;
    return 0;
}

static int if_init(bdk_if_handle_t handle)
{
    priv_t *priv = (priv_t *)handle->priv;
    memset(priv, 0, sizeof(*priv));
    if (bdk_thread_create(handle->node, 0, if_receive, 0, handle, 0))
    {
        bdk_error("%s: Failed to allocate receive thread\n", handle->name);
        return -1;
    }
    return 0;
}

static bdk_if_link_t if_link_get(bdk_if_handle_t handle)
{
    /* Always report 10Gbps as a fake value */
    bdk_if_link_t result;
    result.u64 = 0;
    result.s.full_duplex = 1;
    result.s.lanes = 1;
    result.s.speed = 10000;
    result.s.up = 1;
    return result;
}

static int if_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet, int repeat_count)
{
    int sent = 0;
    priv_t *priv = (priv_t *)handle->priv;
    int32_t tx_free = bdk_atomic_get32(&priv->tx_free);
    int32_t next_tx_free;
    do
    {
        next_tx_free = tx_free + 1;
        if (next_tx_free >= MAX_QUEUE)
            next_tx_free = 0;
        int32_t rx_loc = bdk_atomic_get32(&priv->next_rx);
        if (next_tx_free == rx_loc)
        {
            /* Queue is full */
            next_tx_free = tx_free;
            break;
        }

        /* It is the callers responsibility to make sure the packet
           isn't freed until the TX queue is empty. For us the TX
           queue isn't empty until all packets have been received
           and processed. This means we can use the packet data without
           copying */
        priv->queue[tx_free].if_handle = handle;
        priv->queue[tx_free].rx_error = 0;
        priv->queue[tx_free].length = packet->length;
        priv->queue[tx_free].segments = packet->segments;
        for (int s = 0; s < packet->segments; s++)
            priv->queue[tx_free].packet[s] = packet->packet[s];
        tx_free = next_tx_free;
        sent++;
    } while (repeat_count--);
    if (!sent)
        return 0;

    handle->stats.tx.packets += sent;
    handle->stats.tx.octets += packet->length * sent;
    BDK_WMB;
    /* Move to the next free spot */
    bdk_atomic_set32(&priv->tx_free, next_tx_free);
    return sent;
}

static void if_receive(int unused, void *hand)
{
    bdk_if_handle_t handle = hand;
    priv_t *priv = (priv_t *)handle->priv;
    int rx_loc = bdk_atomic_get32(&priv->next_rx);

    while (1)
    {
        int tx_loc = bdk_atomic_get32(&priv->tx_free);
        /* check for empty */
        if (bdk_likely(rx_loc == tx_loc))
        {
            bdk_thread_yield();
            continue;
        }
        BDK_RMB;
        bdk_if_packet_t *packet = priv->queue + rx_loc;

        handle->stats.rx.packets++;
        handle->stats.rx.octets += packet->length;

        bdk_if_dispatch_packet(packet);
        /* No free needed as TX caller will do it when the queue is empty */

        /* Move to the next packet */
        rx_loc++;
        if (rx_loc >= MAX_QUEUE)
            rx_loc = 0;
        bdk_atomic_set32(&priv->next_rx, rx_loc);
    }
}

static int if_loopback(bdk_if_handle_t handle, bdk_if_loopback_t loopback)
{
    /* Always internal loopback */
    return 0;
}

static int if_get_queue_depth(bdk_if_handle_t handle)
{
    priv_t *priv = (priv_t *)handle->priv;

    /* Make sure gcc reads the variables once and in the correct order */
    int next_rx = bdk_atomic_get32(&priv->next_rx);
    int tx_free = bdk_atomic_get32(&priv->tx_free);

    if (next_rx > tx_free)
        return MAX_QUEUE - next_rx + tx_free;
    else
        return tx_free - next_rx;
}

/**
 * Get the interface RX and TX counters.
 *
 * @param handle Handle of port
 *
 * @return Statistics
 */
static const bdk_if_stats_t *if_get_stats(bdk_if_handle_t handle)
{
    return &handle->stats;
}

const __bdk_if_ops_t __bdk_if_ops_fake = {
    .priv_size = sizeof(priv_t),
    .if_num_interfaces = if_num_interfaces,
    .if_num_ports = if_num_ports,
    .if_probe = if_probe,
    .if_init = if_init,
    .if_link_get = if_link_get,
    .if_transmit = if_transmit,
    .if_loopback = if_loopback,
    .if_get_queue_depth = if_get_queue_depth,
    .if_get_stats = if_get_stats,
};

