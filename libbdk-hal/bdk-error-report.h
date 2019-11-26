/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to hardware error reporting.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/**
 * Call this function to check if any error interrupts are
 * set in the chip.
 */
extern void (*bdk_error_check)(bdk_node_t node) BDK_WEAK;

/**
 * Call this function to setup error enables.
 */
extern void bdk_error_enable(bdk_node_t node) BDK_WEAK;

/** @} */
