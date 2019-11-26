/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ocla.h"
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"

bdk_platform_t __bdk_platform;

void __bdk_platform_init()
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_CSR_INIT(dat2, bdk_numa_master(), BDK_MIO_FUS_DAT2);
        __bdk_platform = dat2.s.run_platform;
        BDK_CSR_INIT(c, bdk_numa_master(), BDK_OCLAX_CONST(0));
        if ((__bdk_platform == BDK_PLATFORM_HW) && (c.u == 0))
            __bdk_platform = BDK_PLATFORM_ASIM;
    }
    else
    {
        __bdk_platform = bdk_fuse_read_range(bdk_numa_master(), BDK_FUS_FUSE_NUM_E_RUN_PLATFORMX(0), 3);
    }
}

