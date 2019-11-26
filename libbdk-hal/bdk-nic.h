/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the NIC.
 *
 * @addtogroup hal
 * @{
 */

typedef enum
{
    BDK_NIC_TYPE_BGX,           /* All chips */
    BDK_NIC_TYPE_TNS,           /* Only allowed on CN88XX */
    BDK_NIC_TYPE_LBK,           /* CN81XX and CN83XX */
    BDK_NIC_TYPE_RGMII,         /* CN83XX */
} bdk_nic_type_t;

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
extern int bdk_nic_port_init(bdk_if_handle_t handle, bdk_nic_type_t ntype, int lmac_credits);

/**
 * Get the current TX queue depth. Note that this operation may be slow
 * and adversly affect packet IO performance.
 *
 * @param handle Port to check
 *
 * @return Depth of the queue in packets
 */
extern int bdk_nic_get_queue_depth(bdk_if_handle_t handle);

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
extern int bdk_nic_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet, int repeat_count);

/**
 * Query NIC and fill in the transmit stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
extern void bdk_nic_fill_tx_stats(bdk_if_handle_t handle);

/**
 * Query NIC and fill in the receive stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
extern void bdk_nic_fill_rx_stats(bdk_if_handle_t handle);

/** @} */
