/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Boot services for XMODEM transfers
 *
 * @addtogroup boot
 * @{
 */

/**
 * Receive a file through Xmodem and write it to an internal file.
 *
 * @param dest_file File to write to
 * @param offset    Offset into the file to write
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_xmodem_upload(const char *dest_file, uint64_t offset);

/** @} */
