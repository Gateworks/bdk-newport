/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for information about the run platform.
 *
 * <hr>$Revision: 49448 $<hr>
 * @addtogroup hal
 * @{
 */

/**
 * This typedef defines the possible platforms for the BDK. The
 * numbers represent fuse setting in Fuses[197:195].
 */
typedef enum
{
    BDK_PLATFORM_HW = 0,
    BDK_PLATFORM_EMULATOR = 1,
    BDK_PLATFORM_RTL = 2,
    BDK_PLATFORM_ASIM = 3,
} bdk_platform_t;

/**
 * Check which platform we are currently running on. This allows a BDK binary to
 * run on various platforms without a recompile.
 *
 * @param platform Platform to check for
 *
 * @return Non zero if we are on the platform
 */
static inline int bdk_is_platform(bdk_platform_t platform) __attribute__ ((pure, always_inline));
static inline int bdk_is_platform(bdk_platform_t platform)
{
    extern bdk_platform_t __bdk_platform;
    return (__bdk_platform == platform);
}

/**
 * Call to initialize the platform state
 */
extern void __bdk_platform_init();

/** @} */
