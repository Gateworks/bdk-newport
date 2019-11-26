/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-gpio.h"

/**
 * Return non-zero if the die is in an alternate package. The
 * normal is_model() checks will treat alternate package parts
 * as all the same, where this function can be used to detect
 * them. The return value is the upper two bits of
 * MIO_FUS_DAT2[chip_id]. Most alternate packages use bit 6,
 * which will return 1 here. Parts with a second alternative
 * will use bit 7, which will return 2.
 *
 * @param arg_model One of the OCTEONTX_* constants for chip models and
 *                  passes
 *
 * @return Non-zero if an alternate package
 *         0 = Normal package
 *         1 = Alternate package 1 (CN86XX, CN80XX with 555 balls)
 *         2 = Alternate package 2 (CN80XX with 676 balls)
 *         3 = Alternate package 3 (Currently unused)
 */
int bdk_is_altpkg(uint32_t arg_model)
{
    if (bdk_is_model(arg_model))
    {
        if (bdk_is_model(OCTEONTX_CN9XXX))
        {
            /* Alternate package bits moved to GPIO_PKG_VER */
            BDK_CSR_INIT(gpio_pkg_ver, bdk_numa_local(), BDK_GPIO_PKG_VER);
            /* 96XX pass C0 and above have extended package codes */
            if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X))
                return 8 + gpio_pkg_ver.s.pkg_ver;
            else
                return gpio_pkg_ver.s.pkg_ver;
        }
        BDK_CSR_INIT(mio_fus_dat2, bdk_numa_local(), BDK_MIO_FUS_DAT2);
        /* Bits 7:6 are used for alternate packages. Return the exact
           number so multiple alternate packages can be detected
           (CN80XX is an example) */
        int altpkg = mio_fus_dat2.s.chip_id >> 6;
        if (altpkg)
            return altpkg;
        /* Due to a documentation mixup, some CN80XX parts do not have chip_id
           bit 7 set. As a backup, use lmc_mode32 to find these parts. Both
           bits are suppose to be fused, but some parts only have lmc_mode32 */
        if (bdk_is_model(OCTEONTX_CN81XX) && mio_fus_dat2.s.lmc_mode32)
            return 2;
        return 0;
    }
    else
        return 0;
}

/**
 * Return the SKU string for a chip
 *
 * @param node   Node to get SKU for
 *
 * @return Chip's SKU
 */
const char* bdk_model_get_sku(int node)
{
    extern void __bdk_model_get_sku_cn8xxx(int node, char *chip_sku);
    extern void __bdk_model_get_sku_cn9xxx(int node, char *chip_sku);

    /* Storage for SKU is per node. Static variable stores the value
       so we don't decode on every call */
    static char chip_sku[BDK_NUMA_MAX_NODES][BDK_MODEL_MAX_SKU] = { { 0, }, };

    if (!chip_sku[node][0])
    {
        if (bdk_is_model(OCTEONTX_CN8XXX))
            __bdk_model_get_sku_cn8xxx(node, chip_sku[node]);
        else
            __bdk_model_get_sku_cn9xxx(node, chip_sku[node]);
    }

    return chip_sku[node];
}
