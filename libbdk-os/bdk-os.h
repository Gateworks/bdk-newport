/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Master include file for operating system support. Use bdk.h instead of
 * including this file directly.
 *
 * <hr>$Revision: 49448 $<hr>
 */

#ifndef BDK_BUILD_HOST
#include "bdk-dbg.h"
#include "bdk-rlock.h"
#include "bdk-thread.h"
#include "bdk-fs.h"
#include "bdk-init.h"
#include "bdk-env.h"
#endif
#include "bdk-menu.h"
#include "bdk-readline.h"

