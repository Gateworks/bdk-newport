/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for identifying BDK build version.
 *
 * <hr>$Revision$<hr>
 */


extern const char bdk_version_str[];

/**
 * Return BDK version string
 *
 * @return BDK version string
 */
static inline const char *bdk_version_string(void)
{
	return bdk_version_str;
}
