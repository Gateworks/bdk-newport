#ifndef __BDK_ARCH_H__
#define __BDK_ARCH_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Master include file for architecture support. Use bdk.h
 * instead of including this file directly.
 *
 * <hr>$Revision: 49448 $<hr>
 */

#ifndef __BYTE_ORDER
    #if !defined(__ORDER_BIG_ENDIAN__) || !defined(__ORDER_LITTLE_ENDIAN__) || !defined(__BYTE_ORDER__)
        #error Unable to determine Endian mode
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define __BYTE_ORDER __ORDER_BIG_ENDIAN__
        #define BDK_LITTLE_ENDIAN_STRUCT __attribute__ ((scalar_storage_order("little-endian")))
    #elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define __BYTE_ORDER __ORDER_LITTLE_ENDIAN__
        #define BDK_LITTLE_ENDIAN_STRUCT
    #else
        #error Unable to determine Endian mode
    #endif
    #define __BIG_ENDIAN    __ORDER_BIG_ENDIAN__
    #define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#endif

#include "bdk-require.h"
#include "bdk-swap.h"
#ifndef BDK_BUILD_HOST
#include "bdk-asm.h"
#endif
#include "bdk-model.h"
#include "bdk-numa.h"
#include "bdk-csr.h"
#ifndef BDK_BUILD_HOST
#include "bdk-lmt.h"
#endif
#include "bdk-warn.h"
#include "bdk-version.h"
#ifndef BDK_BUILD_HOST
#include "bdk-fuse.h"
#include "bdk-platform.h"
#endif

#endif
