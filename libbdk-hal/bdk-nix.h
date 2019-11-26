/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the NIX.
 *
 * @addtogroup hal
 * @{
 */

typedef enum
{
    BDK_NIX_TYPE_CGX,
    BDK_NIX_TYPE_LBK,
    BDK_NIX_TYPE_SDP,
} bdk_nix_type_t;

/**
 * Configure NIC for a specific port. This is called for each
 * port on every interface that connects to NIC.
 *
 * @param handle Handle for port to config
 * @param ntype  Type of LMAC this NIC connects to
 * @param lmac_credits
 *               Size of the LMAC buffer in bytes. Used to configure the number of credits to
 *               setup between the NIC and LMAC
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_nix_port_init(bdk_if_handle_t handle, bdk_nix_type_t ntype, int lmac_credits);

/**
 * Send a packet
 *
 * @param handle Handle of port to send on
 * @param packet Packet to send
 * @param repeat_count
 *               Number of times to repeat the packet. This is used to send a high
 *               speed burst. Set to zero for no repeats, only one packet will be sent
 *
 * @return Number of packets sent or zero on failure
 */
extern int bdk_nix_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet, int repeat_count);

/**
 * Get the current TX queue depth. Note that this operation may be slow
 * and adversly affect packet IO performance.
 *
 * @param handle Port to check
 *
 * @return Depth of the queue in packets
 */
extern int bdk_nix_get_queue_depth(bdk_if_handle_t handle);

/**
 * Query NIC and fill in the transmit stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
extern void bdk_nix_fill_tx_stats(bdk_if_handle_t handle);

/**
 * Query NIC and fill in the receive stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
extern void bdk_nix_fill_rx_stats(bdk_if_handle_t handle);

/**
 * Process a CQ receive entry or WQE
 *
 * @param node      Node containing the CQ
 * @param cq_header CQ header to process
 * @param cq_header_le
 *
 * @return Returns the amount the RBDR doorbell needs to increment
 */
union bdk_nix_rx_parse_s;
extern void __bdk_nix_process_complete_rx(bdk_if_handle_t handle, const union bdk_nix_rx_parse_s *rx_parse);

/** @} */
