/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-nix.h"

/**
 * Process a CQ receive entry or WQE
 *
 * @param node      Node containing the CQ
 * @param cq_header CQ header to process
 * @param cq_header_le
 *
 * @return Returns the amount the RBDR doorbell needs to increment
 */
void __bdk_nix_process_complete_rx(bdk_if_handle_t handle, const union bdk_nix_rx_parse_s *rx_parse)
{
    const union bdk_nix_rx_sg_s *rx_sg_ptr = (const union bdk_nix_rx_sg_s *)(rx_parse + 1);
    BDK_TRACE(NIC, "    Receive RX_PARSE[%p - %p]\n", rx_parse, rx_parse+1);

#if __BYTE_ORDER == __BIG_ENDIAN
    union bdk_nix_rx_parse_s rx_parse_be;
    for (int i = 0; i < (int)sizeof(union bdk_nix_rx_parse_s) / 8; i++)
        rx_parse_be.u[i] = bdk_le64_to_cpu(rx_parse->u[i]);
    rx_parse = &rx_parse_be;
#endif

    bdk_if_packet_t packet;
    packet.length = rx_parse->s.pkt_lenm1 + 1;
    packet.if_handle = handle;
    /* Combine the errlev and errop into a single 11 bit number. Errop
       is 8 bits, so errlev will be in the top byte */
    packet.rx_error = rx_parse->s.errlev;
    packet.rx_error <<= 8;
    packet.rx_error |= rx_parse->s.errcode;

    int segments = 0;
    int segment_length = 0;
    int qwords = rx_parse->s.desc_sizem1 + 1;
    while (qwords > 0)
    {
        union bdk_nix_rx_sg_s rx_sg;
        rx_sg.u = bdk_le64_to_cpu(rx_sg_ptr->u);
        BDK_TRACE(NIC, "    Receive RX_SQ subdc=%d segs=%d ([%p] = 0x%lx)\n", rx_sg.s.subdc, rx_sg.s.segs, rx_sg_ptr, rx_sg.u);
        int num_seg = rx_sg.s.segs;

        uint64_t addr = bdk_le64_to_cpu(rx_sg_ptr[1].u);
        BDK_PREFETCH(bdk_phys_to_ptr(addr), 0);
        packet.packet[segments].u = addr;
        packet.packet[segments].s.size = rx_sg.s.seg1_size;
        segment_length += packet.packet[segments].s.size;
        BDK_TRACE(NIC, "    Receive segment1 size %d address 0x%lx\n", packet.packet[segments].s.size, addr);
        segments++;
        if (num_seg < 2)
            break;
        addr = bdk_le64_to_cpu(rx_sg_ptr[2].u);
        BDK_PREFETCH(bdk_phys_to_ptr(addr), 0);
        packet.packet[segments].u = addr;
        packet.packet[segments].s.size = rx_sg.s.seg2_size;
        segment_length += packet.packet[segments].s.size;
        BDK_TRACE(NIC, "    Receive segment2 size %d address 0x%lx\n", packet.packet[segments].s.size, addr);
        segments++;
        if (num_seg < 3)
            break;
        addr = bdk_le64_to_cpu(rx_sg_ptr[3].u);
        BDK_PREFETCH(bdk_phys_to_ptr(addr), 0);
        packet.packet[segments].u = addr;
        packet.packet[segments].s.size = rx_sg.s.seg3_size;
        segment_length += packet.packet[segments].s.size;
        BDK_TRACE(NIC, "    Receive segment3 size %d address 0x%lx\n", packet.packet[segments].s.size, addr);
        segments++;
        rx_sg_ptr = rx_sg_ptr + 4;
        qwords -= 2;
    }
    packet.segments = segments;
    /* If we ran out of buffer the packet could be truncated */
    if (segment_length < packet.length)
        packet.length = segment_length;

    /* Do RX stats in software as it is fast and I don't really trust
       the hardware. The hardware tends to count packets that are received
       and dropped in some weird way. Hopefully the hardware counters
       looking for drops can find these. It is important that they
       aren't counted as good */
    int len = packet.length;
    if (packet.if_handle->flags & BDK_IF_FLAGS_HAS_FCS)
        len += 4;
    bdk_atomic_add64_nosync((int64_t*)&packet.if_handle->stats.rx.packets, 1);
    bdk_atomic_add64_nosync((int64_t*)&packet.if_handle->stats.rx.octets, len);
    if (packet.rx_error)
        bdk_atomic_add64_nosync((int64_t*)&packet.if_handle->stats.rx.errors, 1);
    bdk_if_dispatch_packet(&packet);
    /* Free the packet data to the NPA */
    for (int s = 0; s < packet.segments; s++)
        __bdk_fpa_raw_free(handle->node, packet.packet[s].s.address & (0xffffffffffffffffULL ^ BDK_CACHE_LINE_MASK), rx_parse->s.pb_aura, 0);
}

