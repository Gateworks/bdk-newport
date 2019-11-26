#ifndef __BDK_BOOT_H__
#define __BDK_BOOT_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Master include file for functions related to boot images and
 * their operation. Any BDK based image booting on hardware has
 * a number of common tasks it needs to do. This header includes
 * the API functions in this category. Use bdk.h instead of
 * including this file directly.
 *
 * @defgroup boot Boot related support functions
 */

#include "bdk-boot-bgx.h"
#include "bdk-boot-board.h"
#include "bdk-boot-dram.h"
#include "bdk-boot-info.h"
#include "bdk-boot-mdio.h"
#include "bdk-boot-pcie.h"
#include "bdk-boot-qlm.h"
#include "bdk-boot-twsi.h"
#include "bdk-boot-usb.h"
#include "bdk-image.h"
#include "bdk-watchdog.h"
#include "bdk-xmodem.h"

#endif
