/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdbool.h>
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-bgx.h"
#include "libbdk-arch/bdk-csrs-cgx.h"
#include "libbdk-arch/bdk-csrs-rgx.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(TRAFFIC_GEN);

static const int ETHERNET_CRC = 4;       /* Gigabit ethernet CRC in bytes */
static const int MAC_ADDR_LEN = 6;
static const int CYCLE_SHIFT = 12;

enum tx_pattern
{
    TX_PATTERN_RAND = 0,    /* Random bytes */
    TX_PATTERN_INC = 1,     /* Incrementing bytes, specifically the low 8 bits of the offset */
    TX_PATTERN_ONES = 2,    /* All ones, ie 0xff bytes */
    TX_PATTERN_ZEROS = 3,   /* All zeros, ie 0x00 bytes */
};

/**
 * Statistics for the port. Exposed to Lua
 */
typedef struct
{
    uint64_t    tx_packets;                 /* TX as packets/sec */
    uint64_t    tx_octets;                  /* TX as octests/sec (includes FCS) */
    uint64_t    tx_packets_total;           /* TX total packets */
    uint64_t    tx_octets_total;            /* TX total octets (includes FCS) */
    uint64_t    tx_bits;                    /* TX as bits/sec (includes preamble, IFG, and FCS) */

    uint64_t    rx_packets;                 /* RX as packets/sec */
    uint64_t    rx_octets;                  /* RX as octets/sec (includes FCS) */
    uint64_t    rx_packets_total;           /* RX total packets */
    uint64_t    rx_octets_total;            /* RX total octets (includes FCS) */
    uint64_t    rx_dropped_octets;          /* RX total dropped octets (includes FCS) */
    uint64_t    rx_dropped_packets;         /* RX total dropped packets */
    uint64_t    rx_errors;                  /* RX packets with some sort of error signalled by HW */
    uint64_t    rx_bits;                    /* RX as bits/sec (includes preamble, IFG, and FCS) */
    uint64_t    rx_backpressure;            /* Increments whenever we receive backpressure. Number is meaningless otherwise */
    uint64_t    rx_validation_errors;       /* RX packets with an incorrect CRC32 at the end */
    uint64_t    rx_rsfec_corrected_errors;  /* RS-FEC corrected errors */
    uint64_t    rx_rsfec_uncorrected_errors;/* RS-FEC uncorrected errors */
    uint64_t    rx_rsfec_symbol_errors;     /* RS-FEC symbols with errors */
    uint64_t    rx_fec_corrected_errors;    /* FEC corrected errors */
    uint64_t    rx_fec_uncorrected_errors;  /* FEC uncorrected errors */
} trafficgen_port_stats_t;

/**
 * Setup information for the port. Exposed to Lua
 */
typedef struct
{
    int                     output_rate;    /* The TX output rate in packets/s or Mbps */
    bool                    output_rate_is_mbps; /* True if output_rate is Mbps */
    bool                    output_enable;  /* True if TX is enabled */
    bool                    tcp;            /* True if packets should be TCP, false for UDP */
    enum tx_pattern         pattern;        /* What type of pattern to put in packets. See "enum tx_pattern" */
    int                     size;           /* TX packet size without FCS */
    uint64_t                output_count;   /* TX output count, or zero for infinite */
    uint64_t                src_mac;        /* MACs are stored so a printf in hex will show them */
    uint64_t                dest_mac;
    uint32_t                src_ip;         /* IPv4 addresses */
    uint32_t                dest_ip;
    uint32_t                ip_tos;         /* IPv4 TOS */
    uint16_t                src_port;       /* TCP/UDP port numbers */
    uint16_t                dest_port;
    bool                    display_packet; /* Display RX and TX packets */
    bool                    validate;       /* Add and check a CRC32 at the end of each packet */
    int                     mtu;            /* Max packet mtu after TSO. Zero disables TSO. This plus FCS is the L2 ethernet frame size */
} trafficgen_port_setup_t;

/**
 * This is structure contains the two struct above, everything that is exposed
 * to Lua.
 */
typedef struct
{
    trafficgen_port_setup_t setup;
    trafficgen_port_stats_t stats;
} trafficgen_port_info_t;

/**
 * Per port internal structure, not exposed to Lua
 */
typedef struct tg_port
{
    bdk_if_handle_t         handle;         /* Raw handle to the bdk-if device */
    bdk_if_stats_t          clear_stats;    /* HW counters are never zeroed. This is what we use as zero */
    bdk_if_stats_t          delta_stats;    /* These are the stats snapshot at the last update time */
    uint64_t                last_update;    /* Time of the last stats calculation */
    int                     tx_running;     /* Non-zero if this port has a running TX thread */
    int                     instance;       /* Instance of tg_port_t. Starts at zero and increments */
    trafficgen_port_info_t  pinfo;          /* Data exposed to Lua */
    struct tg_port *        next;           /* Ports are kept in a linked list */
} tg_port_t;

static tg_port_t *tg_port_head;
static tg_port_t *tg_port_tail;

static int is_packet_crc32c_wrong(tg_port_t *tg_port, bdk_if_packet_t *packet, int fix);
static int do_reset(lua_State* L, tg_port_t *tg_port);
static void tg_packet_receiver(const bdk_if_packet_t *packet, void *arg);

/**
 *
 * @param tg_port
 */
static void tg_init_port(tg_port_t *tg_port)
{
    bdk_if_register_for_packets(tg_port->handle, tg_packet_receiver, tg_port);
    if (!(tg_port->handle->flags & BDK_IF_FLAGS_HIDDEN))
        bdk_if_enable(tg_port->handle);
}

/**
 */
static void tg_init(void)
{
    for (bdk_if_handle_t handle = bdk_if_next_port(NULL); handle!=NULL; handle = bdk_if_next_port(handle))
    {
        tg_port_t *tg_port = calloc(1, sizeof(tg_port_t));
        if (tg_port)
        {
            static int instance = 0;
            tg_port->handle = handle;
            tg_port->instance = instance++;
            tg_port->next = NULL;
            if (tg_port_tail)
                tg_port_tail->next = tg_port;
            else
                tg_port_head = tg_port;
            tg_port_tail = tg_port;
            tg_init_port(tg_port);
            do_reset(NULL, tg_port);
        }
    }
}


/**
 *
 * @param pinfo
 *
 * @return
 */
static int get_size_wire_overhead(const tg_port_t *tg_port)
{
    return 12 /*INTERFRAME_GAP*/ + 8 /*MAC_PREAMBLE*/ + ETHERNET_CRC;
}

/**
 *
 * @param pinfo
 *
 * @return
 */
static int get_size_l2(const tg_port_t *tg_port)
{
    /* L2 header is two MAC addresses and a L2 size/type */
    return MAC_ADDR_LEN*2 + 2;
}

/**
 *
 * @param pinfo
 *
 * @return
 */
static int get_size_ip_header(const tg_port_t *tg_port)
{
    /* We don't support options, so the size of the IP header is fixed for
        IPv4 */
    return 20;
}

/**
 *
 * @param pinfo
 *
 * @return
 */
static int get_size_payload(const tg_port_t *tg_port)
{
    /* The payload area is whatever is left after the previous headers. Note
        that this does not include any UDP or TCP header */
    return tg_port->pinfo.setup.size - get_size_ip_header(tg_port) - get_size_l2(tg_port);
}

/**
 *
 * @return
 */
static int trafficgen_do_update(bool do_clear)
{
    uint64_t clock_rate = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);

    /* Get the statistics for displayed ports */
    for (tg_port_t *tg_port = tg_port_head; tg_port!=NULL; tg_port = tg_port->next)
    {
        uint64_t update_cycle = bdk_clock_get_count(BDK_CLOCK_TIME);
        const bdk_if_stats_t *stats = bdk_if_get_stats(tg_port->handle);

        /* TX stats */
        tg_port->pinfo.stats.tx_packets = stats->tx.packets - tg_port->delta_stats.tx.packets;
        tg_port->pinfo.stats.tx_octets = stats->tx.octets - tg_port->delta_stats.tx.octets;

        /* RX stats */
        tg_port->pinfo.stats.rx_octets = stats->rx.octets - tg_port->delta_stats.rx.octets;
        tg_port->pinfo.stats.rx_packets = stats->rx.packets - tg_port->delta_stats.rx.packets;

        /* Create totals */
        tg_port->pinfo.stats.tx_packets_total = stats->tx.packets - tg_port->clear_stats.tx.packets;
        tg_port->pinfo.stats.tx_octets_total = stats->tx.octets - tg_port->clear_stats.tx.octets;
        tg_port->pinfo.stats.rx_packets_total = stats->rx.packets - tg_port->clear_stats.rx.packets;
        tg_port->pinfo.stats.rx_octets_total = stats->rx.octets - tg_port->clear_stats.rx.octets;
        tg_port->pinfo.stats.rx_errors = stats->rx.errors - tg_port->clear_stats.rx.errors;
        tg_port->pinfo.stats.rx_dropped_octets = stats->rx.dropped_octets - tg_port->clear_stats.rx.dropped_octets;
        tg_port->pinfo.stats.rx_dropped_packets = stats->rx.dropped_packets - tg_port->clear_stats.rx.dropped_packets;

        /* Scale to account for update interval */
        if (update_cycle > tg_port->last_update)
        {
            const int scale_shift = 16;
            uint64_t scale = (1ull<<scale_shift) * clock_rate / (update_cycle - tg_port->last_update);
            tg_port->pinfo.stats.tx_packets = tg_port->pinfo.stats.tx_packets * scale >> scale_shift;
            tg_port->pinfo.stats.tx_octets = tg_port->pinfo.stats.tx_octets * scale >> scale_shift;

            tg_port->pinfo.stats.rx_octets = tg_port->pinfo.stats.rx_octets * scale >> scale_shift;
            tg_port->pinfo.stats.rx_packets = tg_port->pinfo.stats.rx_packets * scale >> scale_shift;
        }

        /* Calculate the RX bits. By convention this include all packet
            overhead on the wire. We've already accounted for ETHERNET_CRC but
            not the preamble and IFG */
        uint64_t bytes_off_per_packet;
        switch (bdk_if_get_type(tg_port->handle))
        {
            default:
                bytes_off_per_packet = get_size_wire_overhead(tg_port) - ETHERNET_CRC;
                break;
        }
        tg_port->pinfo.stats.rx_bits = (tg_port->pinfo.stats.rx_packets * bytes_off_per_packet + tg_port->pinfo.stats.rx_octets) * 8;

        /* Calculate the TX bits */
        tg_port->pinfo.stats.tx_bits = (tg_port->pinfo.stats.tx_packets * bytes_off_per_packet + tg_port->pinfo.stats.tx_octets) * 8;

        /* Update RS-FEC counters */
        tg_port->pinfo.stats.rx_rsfec_corrected_errors = stats->rsfec_corrected_errors - tg_port->clear_stats.rsfec_corrected_errors;
        tg_port->pinfo.stats.rx_rsfec_uncorrected_errors = stats->rsfec_uncorrected_errors - tg_port->clear_stats.rsfec_uncorrected_errors;
        tg_port->pinfo.stats.rx_rsfec_symbol_errors = stats->rsfec_symbol_errors - tg_port->clear_stats.rsfec_symbol_errors;

        /* Update FEC counters */
        tg_port->pinfo.stats.rx_fec_corrected_errors = stats->fec_corrected_errors - tg_port->clear_stats.fec_corrected_errors;
        tg_port->pinfo.stats.rx_fec_uncorrected_errors = stats->fec_uncorrected_errors - tg_port->clear_stats.fec_uncorrected_errors;

        /* Get the backpressure counters */
        switch (bdk_if_get_type(tg_port->handle))
        {
            case BDK_IF_BGX:
            {
                int port = tg_port->handle->index;
                BDK_CSR_INIT(rx_pause, tg_port->handle->node, BDK_BGXX_CMRX_RX_STAT2(tg_port->handle->interface, port));
                BDK_CSR_WRITE(tg_port->handle->node, BDK_BGXX_CMRX_RX_STAT2(tg_port->handle->interface, port), 0);
                tg_port->pinfo.stats.rx_backpressure += rx_pause.s.cnt;
                break;
            }
            case BDK_IF_CGX:
            {
                int port = tg_port->handle->index;
                BDK_CSR_INIT(rx_pause, tg_port->handle->node, BDK_CGXX_CMRX_RX_STAT2(tg_port->handle->interface, port));
                BDK_CSR_WRITE(tg_port->handle->node, BDK_CGXX_CMRX_RX_STAT2(tg_port->handle->interface, port), 0);
                tg_port->pinfo.stats.rx_backpressure += rx_pause.s.cnt;
                break;
            }
            case BDK_IF_RGX:
            {
                int port = tg_port->handle->index;
                BDK_CSR_INIT(rx_pause, tg_port->handle->node, BDK_RGXX_CMRX_RX_STAT2(tg_port->handle->interface, port));
                BDK_CSR_WRITE(tg_port->handle->node, BDK_RGXX_CMRX_RX_STAT2(tg_port->handle->interface, port), 0);
                tg_port->pinfo.stats.rx_backpressure += rx_pause.s.cnt;
                break;
            }
            case BDK_IF_PCIE:
            case BDK_IF_FAKE:
            case BDK_IF_LBK:
            case __BDK_IF_LAST:
                break;
        }
        if (do_clear)
        {
            tg_port->delta_stats = *stats;
            tg_port->last_update = update_cycle;
        }
    }
    return 0;
}



/*
 *      Fold a partial checksum without adding pseudo headers
 */
static unsigned short int csum_fold(unsigned int csum)
{
   unsigned int sum = csum;
   sum = (sum & 0xffff) + (sum >> 16);
   sum = (sum & 0xffff) + (sum >> 16);
   return ~sum;
}


/*
 *      This is a version of ip_compute_csum() optimized for IP headers,
 *      which always checksum on 4 octet boundaries.
 *
 *      By Jorge Cwik <jorge@laser.satlink.net>, adapted for linux by
 *      Arnt Gulbrandsen.
 */
static unsigned short ip_fast_csum(char *iph, unsigned int ihl)
{
        unsigned int *word = (unsigned int *) iph;
        unsigned int *stop = word + ihl;
        unsigned int csum;
        int carry;

        csum = bdk_cpu_to_be32(word[0]);
        csum += bdk_cpu_to_be32(word[1]);
        carry = (csum < bdk_cpu_to_be32(word[1]));
        csum += carry;

        csum += bdk_cpu_to_be32(word[2]);
        carry = (csum < bdk_cpu_to_be32(word[2]));
        csum += carry;

        csum += bdk_cpu_to_be32(word[3]);
        carry = (csum < bdk_cpu_to_be32(word[3]));
        csum += carry;

        word += 4;
        do {
                csum += bdk_cpu_to_be32(*word);
                carry = (csum < bdk_cpu_to_be32(*word));
                csum += carry;
                word++;
        } while (word != stop);

        return csum_fold(csum);
}

static int write_packet(bdk_if_packet_t *packet, int loc, uint8_t data)
{
    if (loc < packet->length)
        bdk_if_packet_write(packet, loc, 1, &data);
    return loc + 1;
}

/**
 * Generate a valid TCP/UDP packet
 *
 * @param port   Output port to build for
 */
static int build_packet(tg_port_t *tg_port, bdk_if_packet_t *packet)
{
    if (tg_port->pinfo.setup.size < 1)
    {
        bdk_error("%s: Packet must be at least 1 byte\n", bdk_if_name(tg_port->handle));
        return -1;
    }

    if (tg_port->pinfo.setup.validate && (tg_port->pinfo.setup.size < 19))
    {
        /* Packets smaller than 19 bytes will skip validation. 14 bytes
            skipped for L2, 1 byte of data, and 4 bytes of CRC is the
            minimum for validation */
        bdk_warn("%s: Packets smaller than 19 bytes will not be validated\n", bdk_if_name(tg_port->handle));
    }

    int total_length = tg_port->pinfo.setup.size;

    /* Packet allocate needs to know the type of packet, otherwise will limit
       the size of TSO */
    if (tg_port->pinfo.setup.tcp)
    {
        packet->packet_type = BDK_IF_TYPE_TCP4;
        /* Require the TSO MTU to contain at least 6 bytes of TCP data,
           making a min size packet */
        if (tg_port->pinfo.setup.mtu >= 60)
            packet->mtu = tg_port->pinfo.setup.mtu; /* Needs to be TCP MTU for TSO */
        else
            packet->mtu = 0;
    }
    else
    {
        /* Asim doesn't handle UDP4 checksum insert right on CN83XX */
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
            packet->packet_type = BDK_IF_TYPE_UNKNOWN;
        else
            packet->packet_type = BDK_IF_TYPE_UDP4;
        packet->mtu = 0;
    }

    /* Allcoate a packet for transmit */
    if (bdk_if_alloc(packet, total_length))
    {
        bdk_error("%s: Failed to allocate TX packet\n", bdk_if_name(tg_port->handle));
        return -1;
    }
    int loc = 0;

    /* Ethernet dest address */
    for (int i=0; i<6; i++)
        loc = write_packet(packet, loc, tg_port->pinfo.setup.dest_mac>>(40-i*8));

    /* Ethernet source address */
    for (int i=0; i<6; i++)
        loc = write_packet(packet, loc, tg_port->pinfo.setup.src_mac>>(40-i*8));

    /* Ethernet Protocol */
    loc = write_packet(packet, loc, 0x08);
    loc = write_packet(packet, loc, 0x00);
    /* IP version, ihl */
    loc = write_packet(packet, loc, 0x45);
    /* IP TOS */
    loc = write_packet(packet, loc, tg_port->pinfo.setup.ip_tos);
    /* IP length */
    int ip_length = get_size_ip_header(tg_port) + get_size_payload(tg_port);
    loc = write_packet(packet, loc, ip_length>>8);
    loc = write_packet(packet, loc, ip_length&0xff);
    /* IP id */
    loc = write_packet(packet, loc, 0x00);
    loc = write_packet(packet, loc, 0x00);
    /* IP frag_off */
    loc = write_packet(packet, loc, 0x00);
    loc = write_packet(packet, loc, 0x00);
    /* IP ttl */
    loc = write_packet(packet, loc, 0x04);
    /* IP protocol, TCP=0x6, UDP=0x11 */
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.tcp) ? 0x06 : 0x11);
    /* IP check */
    int ip_checksum_loc = loc;    /* remember for later */
    loc = write_packet(packet, loc, 0x00);
    loc = write_packet(packet, loc, 0x00);
    /* IP saddr */
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.src_ip>>24) & 0xff);
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.src_ip>>16) & 0xff);
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.src_ip>>8) & 0xff);
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.src_ip>>0) & 0xff);
    /* IP daddr */
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.dest_ip>>24) & 0xff);
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.dest_ip>>16) & 0xff);
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.dest_ip>>8) & 0xff);
    loc = write_packet(packet, loc, (tg_port->pinfo.setup.dest_ip>>0) & 0xff);

    /* Fix the IP checksum */
    int begin_ip = get_size_l2(tg_port);
    char buffer[20];
    if (packet->length >= begin_ip + (int)sizeof(buffer))
    {
        bdk_if_packet_read(packet, begin_ip, sizeof(buffer), buffer);
        uint16_t ip_checksum = ip_fast_csum(buffer, sizeof(buffer)/4);
        write_packet(packet, ip_checksum_loc, ip_checksum >> 8);
        write_packet(packet, ip_checksum_loc+1, ip_checksum);
    }

    /* TCP/UDP source port */
    loc = write_packet(packet, loc, tg_port->pinfo.setup.src_port >> 8);
    loc = write_packet(packet, loc, tg_port->pinfo.setup.src_port & 0xff);
    /* TCP/UDP destination port */
    loc = write_packet(packet, loc, tg_port->pinfo.setup.dest_port >> 8);
    loc = write_packet(packet, loc, tg_port->pinfo.setup.dest_port & 0xff);

    if (tg_port->pinfo.setup.tcp)
    {
        /* TCP sequence number, hardcoded as 0x12345678 */
        loc = write_packet(packet, loc, 0x12);
        loc = write_packet(packet, loc, 0x34);
        loc = write_packet(packet, loc, 0x56);
        loc = write_packet(packet, loc, 0x78);
        /* TCP ACK number, hardcoded as 0 */
        loc = write_packet(packet, loc, 0x00);
        loc = write_packet(packet, loc, 0x00);
        loc = write_packet(packet, loc, 0x00);
        loc = write_packet(packet, loc, 0x00);
        /* TCP Header length (Five 32bit words) + 4 reserved bits */
        loc = write_packet(packet, loc, 0x50);
        /* TCP Flags, RST only */
        loc = write_packet(packet, loc, 0x04);
        /* TCP Window size, hardcoded as 0x8000 */
        loc = write_packet(packet, loc, 0x80);
        loc = write_packet(packet, loc, 0x00);
        /* TCP checksum, filled by hardware */
        loc = write_packet(packet, loc, 0x00);
        loc = write_packet(packet, loc, 0x00);
        /* TCP Urgent Pointer, zero for no urgent data */
        loc = write_packet(packet, loc, 0x00);
        loc = write_packet(packet, loc, 0x00);
    }
    else
    {
        /* UDP length */
        int udp_length = get_size_payload(tg_port);
        loc = write_packet(packet, loc, udp_length>>8);
        loc = write_packet(packet, loc, udp_length&0xff);
        /* UDP checksum, filled by hardware */
        loc = write_packet(packet, loc, 0x00);
        loc = write_packet(packet, loc, 0x00);
    }

    /* Fill the rest of the packet with pattern bytes */
    while (loc < total_length)
    {
        int data = 0;
        switch (tg_port->pinfo.setup.pattern)
        {
            case TX_PATTERN_RAND:
                data = rand();
                break;
            case TX_PATTERN_INC:
                data = loc & 0xff;
                break;
            case TX_PATTERN_ONES:
                data = 0xff;
                break;
            case TX_PATTERN_ZEROS:
                data = 0x00;
                break;
        }
        loc = write_packet(packet, loc, data);
    }

    if (tg_port->pinfo.setup.validate)
        is_packet_crc32c_wrong(tg_port, packet, 1);
    return 0;
}

static void dump_packet(tg_port_t *tg_port, const bdk_if_packet_t *packet)
{
    uint64_t        count;
    uint64_t        remaining_bytes;
    const bdk_packet_ptr_t *buffer_next;
    uint8_t *       data_address;
    uint8_t *       end_of_data;

    printf("\nPacket Length:   %u\n", packet->length);
    printf("    Port:        %s\n", bdk_if_name(tg_port->handle));
    printf("    Buffers:     %u\n", packet->segments);
    if (packet->rx_error)
        printf("    Error code:  %u\n", packet->rx_error);

    buffer_next = packet->packet;
    remaining_bytes = packet->length;

    while (remaining_bytes)
    {
        printf("    Address:     0x%llx\n", (unsigned long long)buffer_next->s.address);
        printf("                 ");
        data_address = (uint8_t *)bdk_phys_to_ptr(buffer_next->s.address);
        end_of_data = data_address + buffer_next->s.size;
        count = 0;
        while (data_address < end_of_data)
        {
            if (remaining_bytes == 0)
                break;
            else
                remaining_bytes--;
            printf("%02x", (unsigned int)*data_address);
            data_address++;
            if (remaining_bytes && (count == 31))
            {
                printf("\n                 ");
                count = 0;
            }
            else if (remaining_bytes && ((count&3) == 3))
            {
                printf(" ");
                count++;
            }
            else
                count++;
        }
        printf("\n");

        if (remaining_bytes)
            buffer_next++;
    }
    fflush(stdout);
}

/**
 * Transmitter loop for generic ports. PKO based ports
 * use the optimized version below. Currently this is
 * only used for MGGMT ports.
 *
 * @param tg_port Trafficgen port to transmit on
 * @param packet  Packet to send
 * @param output_cycle_gap
 *                Gap between each packet in core cycles shifted by CYCLE_SHIFT
 */
static void packet_transmitter_generic(tg_port_t *tg_port, bdk_if_packet_t *packet, uint64_t output_cycle_gap)
{
    const uint64_t BURST_SIZE = 32;
    trafficgen_port_setup_t *port_tx = &tg_port->pinfo.setup;
    uint64_t count = port_tx->output_count;
    uint64_t output_cycle = bdk_clock_get_count(BDK_CLOCK_TIME) << CYCLE_SHIFT;

    int sent_without_yield = 0;
    int sent;
    while (port_tx->output_enable)
    {
        uint64_t cycle = bdk_clock_get_count(BDK_CLOCK_TIME) << CYCLE_SHIFT;
        int do_tx = cycle >= output_cycle;
        sent = 0;
        if (bdk_likely(do_tx))
        {
            int repeat_count = 0;
            if ((count > BURST_SIZE) && (cycle >= output_cycle + output_cycle_gap * BURST_SIZE))
                repeat_count = BURST_SIZE - 1;

            sent = bdk_if_transmit(tg_port->handle, packet, repeat_count);

            output_cycle += output_cycle_gap * sent;
            count -= sent;
            sent_without_yield += sent;
            if (bdk_unlikely(count == 0))
                break;
        }

        if (!sent || (sent_without_yield >= 65536))
        {
            sent_without_yield = 0;
            bdk_thread_yield();
        }
    }
}


/**
 * Transmit loop for each port. This is started as an independent
 * thread.
 *
 * @param unused  Unused
 * @param tg_port Port to transmit on
 */
static void packet_transmitter(int unused, tg_port_t *tg_port)
{
    trafficgen_port_setup_t *port_tx = &tg_port->pinfo.setup;
    bdk_if_packet_t packet;

    packet.if_handle = tg_port->handle;
    if (build_packet(tg_port, &packet))
        goto out;

    if (bdk_unlikely(tg_port->pinfo.setup.display_packet))
    {
        printf("Transmit packet:\n");
        dump_packet(tg_port, &packet);
    }

    /* Figure out my TX rate */
    int packet_rate = port_tx->output_rate;
    if (port_tx->output_rate_is_mbps)
        packet_rate = packet_rate * 125000ull / (tg_port->pinfo.setup.size + get_size_wire_overhead(tg_port));
    if (packet_rate == 0)
        packet_rate = 1;
    uint64_t output_cycle_gap = (bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) << CYCLE_SHIFT) / packet_rate;

    packet_transmitter_generic(tg_port, &packet, output_cycle_gap);

    /* Wait for transmit to be idle before freeing the packet */
    uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    uint64_t queue_depth = bdk_if_get_queue_depth(tg_port->handle);
    while (queue_depth)
    {
        if (bdk_clock_get_count(BDK_CLOCK_TIME) > timeout)
            break;
        bdk_wait_usec(100);
        queue_depth = bdk_if_get_queue_depth(tg_port->handle);
    }
    if (queue_depth == 0)
        bdk_if_free(&packet);
    else
        bdk_error("%s: Transmit packet not freed as output queue still active\n", tg_port->handle->name);
out:
    port_tx->output_enable = 0;
    tg_port->tx_running = 0;
    BDK_WMB;
}


/**
 * Check the CRC on an incoming packet and return non zero if it
 * doesn't match the calculated value.
 *
 * @param work   Packet to process. We handle dynamic short.
 *
 * @return Non zero on CRC error
 */
static int is_packet_crc32c_wrong(tg_port_t *tg_port, bdk_if_packet_t *packet, int fix)
{
    uint32_t crc = 0xffffffff;
    bdk_packet_ptr_t *buffer_next = packet->packet;

    /* Get a pointer to the beginning of the packet */
    int buffer_bytes = buffer_next->s.size;
    void *ptr = bdk_phys_to_ptr(buffer_next->s.address);
    int remaining_bytes = packet->length;

    /* CRC the L2 and L3 header */
    /* Skip the L2 header in the CRC calculation */
    int l2l3_size = 14 + 20;
    if (remaining_bytes >= l2l3_size + 20)
    {
        /* Get the IPv4 packet type */
        uint8_t ipv4_type = *((uint8_t *)ptr + 14 + 9);
        crc = bdk_crc32(ptr,  l2l3_size,  crc);
        buffer_bytes -= l2l3_size;
        remaining_bytes -= l2l3_size;
        ptr += l2l3_size;
        if ((ipv4_type == 0x6) || ipv4_type == 0x11) /* TCP or UDP */
        {
            /* CRC header skipping checksum  */
            int size = (ipv4_type == 0x6) ? 16 : 6;
            int skip = 2; /* Size of checksum */
            crc = bdk_crc32(ptr,  size,  crc);
            buffer_bytes -= size + skip;
            remaining_bytes -= size + skip;
            ptr += size + skip;
        }
    }

    /* Reduce the length by 4, the length of the CRC at the end */
    remaining_bytes -= 4;

    while (remaining_bytes > 0)
    {
        if (bdk_likely(remaining_bytes <= buffer_bytes))
        {
            /* The rest of the crc data fits in this single buffer */
            crc = bdk_crc32(ptr,  remaining_bytes,  crc);
            buffer_bytes -= remaining_bytes;
            /* Most of the time the CRC fits right after the data in the
                buffer. If it doesn't we need the next buffer too */
            if (bdk_likely(buffer_bytes >= 4))
            {
                if (fix)
                {
                    //printf("write crc 0x%08x\n", crc);
                    *(uint32_t*)(ptr + remaining_bytes) = bdk_cpu_to_be32(crc);
                    return 0;
                }
                else
                {
                    uint32_t from_packet = *(uint32_t*)(ptr + remaining_bytes);
                    from_packet = bdk_be32_to_cpu(from_packet);
                    //printf("crc 0x%08x, correct 0x%08x\n", from_packet, crc);
                    return (crc != from_packet);
                }
            }
            else
            {
                if (bdk_likely(buffer_bytes))
                {
                    if (fix)
                    {
                        //printf("write crc 0x%08x\n", crc);
                        crc = bdk_cpu_to_be32(crc);
                        memcpy(ptr + remaining_bytes, &crc, buffer_bytes);
                        /* Get a pointer to the next buffer. The rest of the CRC should
                        be at the beginning */
                        buffer_next++;
                        ptr = bdk_phys_to_ptr(buffer_next->s.address);
                        memcpy(ptr, ((char*)&crc) + buffer_bytes, 4 - buffer_bytes);
                        return 0;
                    }
                    else
                    {
                        /* Read 4 bytes from right after the data */
                        uint32_t packet_crc1 = *(uint32_t*)(ptr + remaining_bytes);
                        /* AND off the lower bits that are actually in the next buffer */
#if __BYTE_ORDER == __BIG_ENDIAN
                        packet_crc1 &= ~bdk_build_mask(8*(4-buffer_bytes));
#else
                        packet_crc1 &= bdk_build_mask(8*buffer_bytes);
#endif
                        /* Get a pointer to the next buffer. The rest of the CRC should
                        be at the beginning */
                        buffer_next++;
                        ptr = bdk_phys_to_ptr(buffer_next->s.address);
                        /* Read the rest of the CRC */
                        uint32_t packet_crc2 = *(uint32_t*)ptr;
#if __BYTE_ORDER == __BIG_ENDIAN
                        /* Shift off extra bytes read since some bytes are stored in part 1*/
                        packet_crc2 >>= 32 - 8*(4-buffer_bytes);
#else
                        /* AND off extra bytes read since some bytes are stored in part 1*/
                        packet_crc2 &= bdk_build_mask(8*(4-buffer_bytes));
                        packet_crc2 <<= 8 * buffer_bytes;
#endif
                        /* Compare the final CRC with both parts put together */
                        uint32_t from_packet = packet_crc1|packet_crc2;
                        from_packet = bdk_be32_to_cpu(from_packet);
                        //printf("crc 0x%08x, correct 0x%08x\n", from_packet, crc);
                        return (crc != from_packet);
                    }
                }
                else
                {
                    /* Get a pointer to the next buffer. The CRC should be at the beginning */
                    buffer_next++;
                    ptr = bdk_phys_to_ptr(buffer_next->s.address);
                    if (fix)
                    {
                        //printf("write crc 0x%08x\n", crc);
                        /* Write the CRC */
                        *(uint32_t*)ptr = bdk_cpu_to_be32(crc);
                        return 0;
                    }
                    else
                    {
                        /* Read the CRC */
                        uint32_t from_packet = *(uint32_t*)ptr;
                        from_packet = bdk_be32_to_cpu(from_packet);
                        //printf("crc 0x%08x, correct 0x%08x\n", from_packet, crc);
                        return (crc != from_packet);
                    }
                }
            }
        }
        else
        {
            /* This buffer only contains part of our crc data */
            crc = bdk_crc32(ptr, buffer_bytes,  crc);
            remaining_bytes -= buffer_bytes;
            /* Get a pointer to the next buffer */
            buffer_next++;
            ptr = bdk_phys_to_ptr(buffer_next->s.address);
            buffer_bytes = buffer_next->s.size;
        }
    }
    return 0;
}

/**
 * Called by cores when they get work and need to process it.
 *
 * @param work   Work to be processed. Ideally it should already be prefetched
 *               into memory.
 */
static void tg_packet_receiver(const bdk_if_packet_t *packet, void *arg)
{
    tg_port_t *tg_port = arg;

    if (bdk_likely(tg_port->pinfo.setup.validate))
    {
        if (bdk_unlikely(is_packet_crc32c_wrong(tg_port, (bdk_if_packet_t *)packet, 0)))
            bdk_atomic_add64((int64_t*)&tg_port->pinfo.stats.rx_validation_errors, 1);
    }

    if (bdk_unlikely(tg_port->pinfo.setup.display_packet))
        dump_packet(tg_port, packet);
}


static tg_port_t *lookup_name(lua_State* L, const char *name)
{
    for (tg_port_t *tg_port = tg_port_head; tg_port!=NULL; tg_port = tg_port->next)
        if (strcasecmp(name, bdk_if_name(tg_port->handle)) == 0)
            return tg_port;
    luaL_error(L, "Invalid port name %s", name);
    return NULL;
}

static int for_each_port(lua_State* L, int (*func)(lua_State* L, tg_port_t *tg_port))
{
    luaL_checktype(L, 1, LUA_TTABLE);
    int result = 0;
    int length = luaL_len(L, 1);
    for (int count=1; count<=length; count++)
    {
        lua_pushinteger(L, count);
        lua_gettable(L, 1);
        tg_port_t *tg_port = lookup_name(L, luaL_checkstring(L, -1));
        lua_pop(L, 1);
        result |= func(L, tg_port);
    }
    return result;
}


/**
 *
 * @param range
 *
 * @return
 */
static int do_clear(lua_State* L, tg_port_t *tg_port)
{
    const bdk_if_stats_t *stats = bdk_if_get_stats(tg_port->handle);
    tg_port->clear_stats = *stats;
    tg_port->delta_stats = *stats;
    memset(&tg_port->pinfo.stats, 0, sizeof(tg_port->pinfo.stats));
    return 0;
}

/**
 *
 * @param range
 *
 * @return
 */
static int do_reset(lua_State* L, tg_port_t *tg_port)
{
    uint64_t mac_addr_base = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS);

    int port_offset = tg_port->instance;
    uint64_t src_mac = mac_addr_base + port_offset; /* Linear */
    uint64_t dest_mac = src_mac + ((port_offset & 1) ? -1 : 1); /* Dest is pair port */
    int src_inc = port_offset << 16;
    int dest_inc = port_offset << 16;
    const char *name = bdk_if_name(tg_port->handle);
    int default_speed;
    if (strstr(name, "GMII")) /* SGMII, RGMII */
        default_speed = 1000;
    else if (strstr(name, "1G"))
        default_speed = 1000;
    else if (strstr(name, "10G"))
        default_speed = 10000;
    else if (strstr(name, "20G"))
        default_speed = 20000;
    else if (strstr(name, "25G"))
        default_speed = 25000;
    else if (strstr(name, "40G"))
        default_speed = 40000;
    else if (strstr(name, "50G"))
        default_speed = 50000;
    else if (strstr(name, "80G"))
        default_speed = 80000;
    else if (strstr(name, "100G"))
        default_speed = 100000;
    else
        default_speed = 10000; /* LOOP, XAUI */

    tg_port->pinfo.setup.output_rate                = default_speed;
    tg_port->pinfo.setup.output_rate_is_mbps        = true;
    tg_port->pinfo.setup.output_enable              = 0;
    tg_port->pinfo.setup.output_count               = 0;
    tg_port->pinfo.setup.size                       = 64 - ETHERNET_CRC;
    tg_port->pinfo.setup.src_mac                    = src_mac;
    tg_port->pinfo.setup.dest_mac                   = dest_mac;
    tg_port->pinfo.setup.src_ip                     = 0x0a000063 | src_inc;        /* 10.port.0.99 */
    tg_port->pinfo.setup.dest_ip                    = 0x0a000063 | dest_inc;   /* 10.connect_to_port.0.99 */
    tg_port->pinfo.setup.src_port                   = 4096;
    tg_port->pinfo.setup.dest_port                  = 4097;
    tg_port->pinfo.setup.ip_tos                     = 0;
    tg_port->pinfo.setup.display_packet             = false;
    tg_port->pinfo.setup.validate                   = true;
    return do_clear(L, tg_port);
}

/**
 *
 * @param range
 *
 * @return
 */
static int do_start(lua_State* L, tg_port_t *tg_port)
{
    if (tg_port->handle->flags & BDK_IF_FLAGS_HIDDEN)
        return 0;

    if (tg_port->pinfo.setup.output_enable == 0)
    {
        /* Spin waiting for any old transmitters to stop */
        while (tg_port->tx_running)
            bdk_thread_yield();
        tg_port->pinfo.setup.output_enable = 1;
        tg_port->tx_running = 1;
        BDK_WMB;
        bdk_thread_create(tg_port->handle->node, 0, (bdk_thread_func_t)packet_transmitter, 0, tg_port, 0);
    }
    return 0;
}

/**
 *
 * @param range
 *
 * @return
 */
static int do_stop(lua_State* L, tg_port_t *tg_port)
{
    tg_port->pinfo.setup.output_enable = 0;
    BDK_WMB;
    return 0;
}

/**
 *
 * @param range
 *
 * @return
 */
static int do_is_transmitting(lua_State* L, tg_port_t *tg_port)
{
    return tg_port->pinfo.setup.output_enable;
}

/**
 *
 * @param range
 *
 * @return
 */
static int do_unplug(lua_State* L, tg_port_t *tg_port)
{
    if (tg_port->handle->netport)
        bdk_device_netport_unplug(tg_port->handle->netport);
    return 0;
}

/**
 *
 * @param range
 *
 * @return
 */
static int do_plug(lua_State* L, tg_port_t *tg_port)
{
    const char *param = luaL_checkstring(L, 2);
    if (tg_port->handle->netport)
        bdk_device_netport_plug(tg_port->handle->netport, param);
    return 0;
}

/**
 * Lua interface function
 * Get an array of all port names
 * Input: Nothing
 * Output: Array of port names
 *
 * @param L
 *
 * @return
 */
static int get_port_names(lua_State* L)
{
    if (!tg_port_head)
        tg_init();
    int count = 0;
    lua_newtable(L);
    for (tg_port_t *tg_port = tg_port_head; tg_port!=NULL; tg_port = tg_port->next)
    {
        if (!(tg_port->handle->flags & BDK_IF_FLAGS_HIDDEN))
        {
            lua_pushinteger(L, ++count);
            lua_pushstring(L, bdk_if_name(tg_port->handle));
            lua_settable(L, -3);
        }
    }
    return 1;
}


/**
 * Lua interface function
 * Get the configuration of a single port
 * Input: A single port name string
 * Output: Table of setup data
 *
 * @param L
 *
 * @return
 */
static int get_config(lua_State* L)
{
    tg_port_t *tg_port = lookup_name(L, luaL_checkstring(L, 1));
    #define pushfield(field, lua_type)                      \
        lua_push##lua_type(L, tg_port->pinfo.setup.field);  \
        lua_setfield (L, -2, #field);

    lua_newtable(L);
    pushfield(output_rate,          number);
    pushfield(output_rate_is_mbps,  boolean);
    pushfield(output_enable,        boolean);
    pushfield(tcp,                  boolean);
    pushfield(pattern,              number);
    pushfield(size,                 number);
    pushfield(output_count,         number);
    pushfield(src_mac,              number);
    pushfield(dest_mac,             number);
    pushfield(src_ip,               number);
    pushfield(dest_ip,              number);
    pushfield(ip_tos,               number);
    pushfield(src_port,             number);
    pushfield(dest_port,            number);
    pushfield(display_packet,       boolean);
    pushfield(validate,             boolean);
    pushfield(mtu,                  number);

    lua_pushinteger(L, tg_port->handle->node);
    lua_setfield (L, -2, "node");
    /* serdes_map is a array (table starting at 1) containing a list
       of all lanes used by this port. The format is "qlm,lane,qlm,lane,..." */
    lua_newtable(L);
    int qlm = bdk_if_get_qlm(tg_port->handle);
    if (qlm != -1)
    {
        uint64_t mask = bdk_if_get_lane_mask(tg_port->handle);
        int num_lanes = bdk_qlm_get_lanes(tg_port->handle->node, qlm);
        int lane = 0;
        int table_index = 1;
        /* Loop until we've used all lanes */
        while (mask)
        {
            if (mask & 1)
            {
                /* Add QLM and lane to serdes map */
                lua_pushinteger(L, table_index++);
                lua_pushinteger(L, qlm);
                lua_settable(L, -3);
                lua_pushinteger(L, table_index++);
                lua_pushinteger(L, lane);
                lua_settable(L, -3);
            }
            /* Move to next lane */
            mask >>= 1;
            lane++;
            /* Check if port spans multiple QLMs */
            if (lane >= num_lanes)
            {
                qlm++;
                num_lanes = bdk_qlm_get_lanes(tg_port->handle->node, qlm);
            }
        }
    }
    lua_setfield(L, -2, "serdes_map");
    return 1;
}


/**
 * Lua interface function
 * Set the configuration od a port. Only named parameters are changed.
 * Input: A single port name string
 * Input: Table of setup data
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int set_config(lua_State* L)
{
    tg_port_t *tg_port = lookup_name(L, luaL_checkstring(L, 1));

    #define getfield(field,  lua_type)                              \
        lua_getfield (L, 2, #field);                                \
        if (!lua_isnil(L, -1))                                      \
            tg_port->pinfo.setup.field = lua_to##lua_type(L, -1);   \
        lua_pop(L, 1);

    luaL_checktype(L, 2, LUA_TTABLE);
    getfield(output_rate,          number);
    getfield(output_rate_is_mbps,  boolean);
    getfield(output_enable,        boolean);
    getfield(tcp,                  boolean);
    getfield(pattern,              number);
    getfield(size,                 number);
    getfield(output_count,         number);
    getfield(src_mac,              number);
    getfield(dest_mac,             number);
    getfield(src_ip,               number);
    getfield(dest_ip,              number);
    getfield(ip_tos,               number);
    getfield(src_port,             number);
    getfield(dest_port,            number);
    getfield(display_packet,       boolean);
    getfield(validate,             boolean);
    getfield(mtu,                  number);
    BDK_WMB;
    return 0;
}

/**
 * Lua interface function
 * Set the loopback state of a port.
 * Input: A single port name string
 * Input: A string for loopback mode
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int set_loopback(lua_State* L)
{
    tg_port_t *tg_port = lookup_name(L, luaL_checkstring(L, 1));
    const char *loop_mode = luaL_checkstring(L, 2);

    if (strcasecmp(loop_mode, "none") == 0)
    {
        if (bdk_if_loopback(tg_port->handle, BDK_IF_LOOPBACK_NONE))
            return luaL_error(L, "Setting loopback failed");
    }
    else if (strcasecmp(loop_mode, "internal") == 0)
    {
        if (bdk_if_loopback(tg_port->handle, BDK_IF_LOOPBACK_INTERNAL))
            return luaL_error(L, "Setting loopback failed");
    }
    else if (strcasecmp(loop_mode, "external") == 0)
    {
        if (bdk_if_loopback(tg_port->handle, BDK_IF_LOOPBACK_EXTERNAL))
            return luaL_error(L, "Setting loopback failed");
    }
    else if (strcasecmp(loop_mode, "internal+external") == 0)
    {
        if (bdk_if_loopback(tg_port->handle, BDK_IF_LOOPBACK_INTERNAL_EXTERNAL))
            return luaL_error(L, "Setting loopback failed");
    }
    else
        return luaL_error(L, "Illegal loopback mode \"%s\", expect \"none\", \"internal\", \"external\", or \"internal+external\"", loop_mode);
    return 0;
}


/**
 * Lua interface function
 * Clear the statistics for a range of ports
 * Input: Array of port names
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int clear(lua_State* L)
{
    for_each_port(L, do_clear);
    return 0;
}


/**
 * Lua interface function
 * Reset and clear a range of ports
 * Input: Array of port names
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int reset(lua_State* L)
{
    for_each_port(L, do_reset);
    return 0;
}


/**
 * Lua interface function
 * Update the statistics of all port and returns them
 * Input: clear boolean
 * Output: Table index by port name of table of stats
 *
 * @param L
 *
 * @return
 */
static int update(lua_State* L)
{
    #define pushlabel(i, field)                         \
        lua_pushnumber(L, i);                           \
        lua_pushstring(L, #field);                      \
        lua_settable(L, -3);

    #define pushstat(i, field)                          \
        lua_pushnumber(L, i);                           \
        lua_pushnumber(L, tg_port->pinfo.stats.field);  \
        lua_settable(L, -3);

    trafficgen_do_update(lua_toboolean(L, 1));

    /* This is the table that contains the entire response */
    lua_newtable(L);

    /* This table will contains the labels for the stats. It is named "labels" */
    lua_newtable(L);
    pushlabel(1, tx_packets);
    pushlabel(2, tx_octets);
    pushlabel(3, tx_packets_total);
    pushlabel(4, tx_octets_total);
    pushlabel(5, tx_bits);
    pushlabel(6, rx_packets);
    pushlabel(7, rx_octets);
    pushlabel(8, rx_packets_total);
    pushlabel(9, rx_octets_total);
    pushlabel(10, rx_dropped_octets);
    pushlabel(11, rx_dropped_packets);
    pushlabel(12, rx_errors);
    pushlabel(13, rx_bits);
    pushlabel(14, rx_backpressure);
    pushlabel(15, rx_validation_errors);
    pushlabel(16, rx_rsfec_corrected);
    pushlabel(17, rx_rsfec_uncorrected);
    pushlabel(18, rx_rsfec_symbol);
    pushlabel(19, rx_fec_corrected);
    pushlabel(20, rx_fec_uncorrected);
    pushlabel(21, link_speed);
    lua_setfield(L, -2, "labels");

    /* Add stats for each interface */
    for (tg_port_t *tg_port = tg_port_head; tg_port!=NULL; tg_port = tg_port->next)
    {
        lua_newtable(L);
        pushstat(1, tx_packets);
        pushstat(2, tx_octets);
        pushstat(3, tx_packets_total);
        pushstat(4, tx_octets_total);
        pushstat(5, tx_bits);
        pushstat(6, rx_packets);
        pushstat(7, rx_octets);
        pushstat(8, rx_packets_total);
        pushstat(9, rx_octets_total);
        pushstat(10, rx_dropped_octets);
        pushstat(11, rx_dropped_packets);
        pushstat(12, rx_errors);
        pushstat(13, rx_bits);
        pushstat(14, rx_backpressure);
        pushstat(15, rx_validation_errors);
        pushstat(16, rx_rsfec_corrected_errors);
        pushstat(17, rx_rsfec_uncorrected_errors);
        pushstat(18, rx_rsfec_symbol_errors);
        pushstat(19, rx_rsfec_corrected_errors);
        pushstat(20, rx_rsfec_uncorrected_errors);
        /* Add link speed */
        lua_pushnumber(L, 21);
        lua_pushnumber(L, tg_port->handle->link_info.s.speed);
        lua_settable(L, -3);
        lua_setfield(L, -2, bdk_if_name(tg_port->handle));
    }
    return 1;
}


/**
 * Lua interface function
 * Stop the supplied ports from transmitting
 * Input: Array of port names
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int stop(lua_State* L)
{
    for_each_port(L, do_stop);
    return 0;
}


/**
 * Lua interface function
 * Start the supplied ports transmitting
 * Input: Array of port names
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int start(lua_State* L)
{
    for_each_port(L, do_start);
    return 0;
}


/**
 * Lua interface function
 * Return a boolean of true if any of the supplied ports are transmitting
 * Input: Array of port names
 * Output: Bool, true if any of ports are transmitting
 *
 * @param L
 *
 * @return
 */
static int is_transmitting(lua_State* L)
{
    lua_pushboolean(L, for_each_port(L, do_is_transmitting));
    return 1;
}

/**
 * Lua interface function
 * Call unplug on each port
 * Input: Array of port names
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int unplug(lua_State* L)
{
    for_each_port(L, do_unplug);
    return 0;
}

/**
 * Lua interface function
 * Call plug for each port
 * Input: Array of port names
 * Output: Nothing
 *
 * @param L
 *
 * @return
 */
static int plug(lua_State* L)
{
    for_each_port(L, do_plug);
    return 0;
}

/**
 * Initialize the trafficgen module
 *
 * @param L
 *
 * @return
 */
void register_trafficgen(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, get_port_names);
    lua_setfield(L, -2, "get_port_names");
    lua_pushcfunction(L, get_config);
    lua_setfield(L, -2, "get_config");
    lua_pushcfunction(L, set_config);
    lua_setfield(L, -2, "set_config");
    lua_pushcfunction(L, set_loopback);
    lua_setfield(L, -2, "set_loopback");
    lua_pushcfunction(L, clear);
    lua_setfield(L, -2, "clear");
    lua_pushcfunction(L, reset);
    lua_setfield(L, -2, "reset");
    lua_pushcfunction(L, update);
    lua_setfield(L, -2, "update");
    lua_pushcfunction(L, stop);
    lua_setfield(L, -2, "stop");
    lua_pushcfunction(L, start);
    lua_setfield(L, -2, "start");
    lua_pushcfunction(L, is_transmitting);
    lua_setfield(L, -2, "is_transmitting");
    lua_pushcfunction(L, unplug);
    lua_setfield(L, -2, "unplug");
    lua_pushcfunction(L, plug);
    lua_setfield(L, -2, "plug");
    lua_setfield(L, -2, "trafficgen");
}

