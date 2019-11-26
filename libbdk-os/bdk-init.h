/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Core initialization functions
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup thread Threading library
 * @{
 */

/**
 * Call this function to take secondary cores out of reset and have
 * them start running threads
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param coremask Cores to start. Zero is a shortcut for all.
 *
 * @return Zero on success, negative on failure.
 */
extern int bdk_init_cores(bdk_node_t node, uint64_t coremask);

/**
 * Put cores back in reset and power them down
 *
 * @param node     Node to update
 * @param coremask Each bit will be a core put in reset. Cores already in reset are unaffected
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_reset_cores(bdk_node_t node, uint64_t coremask);

/**
 * Call this function to take secondary nodes and cores out of
 * reset and have them start running threads
 *
 * @param skip_cores If non-zero, cores are not started. Only the nodes are setup
 * @param ccpi_sw_gbaud
 *                   If CCPI is in software mode, this is the speed the CCPI QLMs will be configured
 *                   for
 *
 * @return Zero on success, negative on failure.
 */
extern int bdk_init_nodes(int skip_cores, int ccpi_sw_gbaud);


/**
 * This function is the first function run on all cores once the
 * threading system takes over.
 *
 * @param arg
 * @param arg1
 */
extern void __bdk_init_main(int arg, void *arg1);

/**
 * Perform one time initialization for a node. Called for each
 * node from the master node.
 */
extern void __bdk_init_node(bdk_node_t node);

/**
 * Set the baud rate on a UART
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param uart     uart to set
 * @param baudrate Baud rate (9600, 19200, 115200, etc)
 * @param use_flow_control
 *                 Non zero if hardware flow control should be enabled
 */
extern void bdk_set_baudrate(bdk_node_t node, int uart, int baudrate, int use_flow_control);

/**
 * Get the coremask of the cores actively running the BDK. Doesn't count cores
 * that aren't booted.
 *
 * @param node   Node to coremask the count for
 *
 * @return 64bit bitmask
 */
extern uint64_t bdk_get_running_coremask(bdk_node_t node);

/**
 * Return the number of cores actively running in the BDK for the given node
 *
 * @param node   Node to get the core count for
 *
 * @return Number of cores running. Doesn't count cores that aren't booted
 */
extern int bdk_get_num_running_cores(bdk_node_t node);

#ifndef BDK_SHOW_BOOT_BANNERS
#define BDK_SHOW_BOOT_BANNERS 1
#endif

#define BDK_UART_BAUDRATE 115200
//#define BDK_UART_BAUDRATE 921600

extern uint64_t __bdk_init_reg_x0; /* The contents of X0 when this image started */
extern uint64_t __bdk_init_reg_x1; /* The contents of X1 when this image started */

/** @}  */
