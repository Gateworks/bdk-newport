/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"

/**
 * Return true if DRAM has been configured
 *
 * @return Boolean
 */
int __bdk_is_dram_enabled(bdk_node_t node)
{
    BDK_CSR_INIT(lmcx_ddr_pll_ctl, node, BDK_LMCX_DDR_PLL_CTL(0));
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return lmcx_ddr_pll_ctl.cn83xx.reset_n;
    else
        return !lmcx_ddr_pll_ctl.cn9.pd;
}
