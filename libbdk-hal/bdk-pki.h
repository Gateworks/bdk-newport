/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the SSO.
 *
 * @addtogroup hal
 * @{
 */

/**
 * One time init of global Packet Input
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_pki_global_init(bdk_node_t node);

/**
 * Configure packet input for a specific port. This is called for each
 * port on every interface that is connected to packet input.
 *
 * @param handle Handle for port to config
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_pki_port_init(bdk_if_handle_t handle);

/**
 * Enable PKI after all setup is complete
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_pki_enable(bdk_node_t node);

/**
 * Query PKI and fill in the receive stats for the supplied interface handle. The
 * interface must use PKI for RX.
 *
 * @param handle Port handle
 *
 * @return
 */
extern void bdk_pki_fill_rx_stats(bdk_if_handle_t handle);

/** @} */
