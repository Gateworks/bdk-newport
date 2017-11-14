/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>

/**
 * Called to register the cavium module
 *
 * @param L
 *
 * @return
 */
void register_cavium_constants(lua_State* L)
{
    #define push_bdk_enum(enum)             \
        do                                  \
        {                                   \
            lua_pushnumber(L, enum);        \
            lua_setfield(L, -2, #enum + 4); \
        } while (0)
    /* These need to be upeprcase for the lua host code to work */
    const int BDK_CSR_TYPE_DAB32B = BDK_CSR_TYPE_DAB32b;
    const int BDK_CSR_TYPE_NCB32B = BDK_CSR_TYPE_NCB32b;
    const int BDK_CSR_TYPE_RSL32B = BDK_CSR_TYPE_RSL32b;

    push_bdk_enum(BDK_CSR_TYPE_DAB);
    push_bdk_enum(BDK_CSR_TYPE_DAB32B);
    push_bdk_enum(BDK_CSR_TYPE_NCB);
    push_bdk_enum(BDK_CSR_TYPE_NCB32B);
    push_bdk_enum(BDK_CSR_TYPE_PCCBR);
    push_bdk_enum(BDK_CSR_TYPE_PCCPF);
    push_bdk_enum(BDK_CSR_TYPE_PCCVF);
    push_bdk_enum(BDK_CSR_TYPE_PCICONFIGRC);
    push_bdk_enum(BDK_CSR_TYPE_PCICONFIGEP);
    push_bdk_enum(BDK_CSR_TYPE_PEXP);
    push_bdk_enum(BDK_CSR_TYPE_PEXP_NCB);
    push_bdk_enum(BDK_CSR_TYPE_RSL);
    push_bdk_enum(BDK_CSR_TYPE_RSL32B);
    push_bdk_enum(BDK_CSR_TYPE_SYSREG);
#ifndef BDK_BUILD_HOST
    push_bdk_enum(BDK_MPI_FLAGS_ENABLE_CS0);
    push_bdk_enum(BDK_MPI_FLAGS_ENABLE_CS1);
    push_bdk_enum(BDK_MPI_FLAGS_ENABLE_CS2);
    push_bdk_enum(BDK_MPI_FLAGS_ENABLE_CS3);
    push_bdk_enum(BDK_MPI_FLAGS_CS_ACTIVE_HI);
    push_bdk_enum(BDK_MPI_FLAGS_ONE_WIRE);
    push_bdk_enum(BDK_MPI_FLAGS_IDLE_CLOCKS);
    push_bdk_enum(BDK_MPI_FLAGS_IDLE_LOW);
    push_bdk_enum(BDK_MPI_FLAGS_LSB_FIRST);

    push_bdk_enum(BDK_IF_BGX);
    push_bdk_enum(BDK_IF_PCIE);

    push_bdk_enum(BDK_QLM_MODE_DISABLED);
    push_bdk_enum(BDK_QLM_MODE_PCIE_1X1);
    push_bdk_enum(BDK_QLM_MODE_PCIE_2X1);
    push_bdk_enum(BDK_QLM_MODE_PCIE_1X2);
    push_bdk_enum(BDK_QLM_MODE_PCIE_1X4);
    push_bdk_enum(BDK_QLM_MODE_PCIE_1X8);
    push_bdk_enum(BDK_QLM_MODE_SATA_4X1);
    push_bdk_enum(BDK_QLM_MODE_SATA_2X1);
    push_bdk_enum(BDK_QLM_MODE_ILK);
    push_bdk_enum(BDK_QLM_MODE_SGMII_4X1);
    push_bdk_enum(BDK_QLM_MODE_SGMII_2X1);
    push_bdk_enum(BDK_QLM_MODE_SGMII_1X1);
    push_bdk_enum(BDK_QLM_MODE_XAUI_1X4);
    push_bdk_enum(BDK_QLM_MODE_RXAUI_2X2);
    push_bdk_enum(BDK_QLM_MODE_RXAUI_1X2);
    push_bdk_enum(BDK_QLM_MODE_OCI);
    push_bdk_enum(BDK_QLM_MODE_XFI_4X1);
    push_bdk_enum(BDK_QLM_MODE_XFI_2X1);
    push_bdk_enum(BDK_QLM_MODE_XFI_1X1);
    push_bdk_enum(BDK_QLM_MODE_XLAUI_1X4);
    push_bdk_enum(BDK_QLM_MODE_10G_KR_4X1);
    push_bdk_enum(BDK_QLM_MODE_10G_KR_2X1);
    push_bdk_enum(BDK_QLM_MODE_10G_KR_1X1);
    push_bdk_enum(BDK_QLM_MODE_40G_KR4_1X4);
    push_bdk_enum(BDK_QLM_MODE_QSGMII_4X1);

    push_bdk_enum(BDK_QLM_CLK_COMMON_0);
    push_bdk_enum(BDK_QLM_CLK_COMMON_1);
    push_bdk_enum(BDK_QLM_CLK_COMMON_2);
    push_bdk_enum(BDK_QLM_CLK_EXTERNAL);

    push_bdk_enum(BDK_QLM_MODE_FLAG_ENDPOINT);

    push_bdk_enum(BDK_QLM_LOOP_DISABLED);

    push_bdk_enum(BDK_QLM_DIRECTION_TX);
    push_bdk_enum(BDK_QLM_DIRECTION_RX);
    push_bdk_enum(BDK_QLM_DIRECTION_BOTH);

    push_bdk_enum(BDK_QLM_MARGIN_VERTICAL);
    push_bdk_enum(BDK_QLM_MARGIN_HORIZONTAL);

    push_bdk_enum(BDK_PCIE_MEM_NORMAL);
    push_bdk_enum(BDK_PCIE_MEM_PREFETCH);
    push_bdk_enum(BDK_PCIE_MEM_IO);

    /* SATA test constants */
    push_bdk_enum(BDK_SATA_BIST_FIS_RETIMED);
    push_bdk_enum(BDK_SATA_BIST_FIS_ANALOG);
    push_bdk_enum(BDK_SATA_BIST_FIS_TX_ONLY);
    push_bdk_enum(BDK_SATA_BIST_SW_RETIMED);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_SSOP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_HTDP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_LTDP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_LFSCP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_COMP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_LBP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_MFTP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_HFTP);
    push_bdk_enum(BDK_SATA_BIST_SW_TX_ONLY_LFTP);

    /* DRAM testing flags */
    push_bdk_enum(BDK_DRAM_TEST_NO_STOP_ERROR);
    push_bdk_enum(BDK_DRAM_TEST_NO_PROGRESS);
    push_bdk_enum(BDK_DRAM_TEST_NO_STATS);
    push_bdk_enum(BDK_DRAM_TEST_NO_BANNERS);
    push_bdk_enum(BDK_DRAM_TEST_USE_CCPI);

    /* Power burn constants */
    push_bdk_enum(BDK_POWER_BURN_NONE);
    push_bdk_enum(BDK_POWER_BURN_FULL);
    push_bdk_enum(BDK_POWER_BURN_CYCLE_10MS);
    push_bdk_enum(BDK_POWER_BURN_CYCLE_1S);
    push_bdk_enum(BDK_POWER_BURN_CYCLE_5S);
    push_bdk_enum(BDK_POWER_BURN_CYCLE_1M);
    push_bdk_enum(BDK_POWER_BURN_CYCLE_5M);

    push_bdk_enum(BDK_SGPIO_LED_ACT);
    push_bdk_enum(BDK_SGPIO_LED_ERR);
    push_bdk_enum(BDK_SGPIO_LED_LOC);
    push_bdk_enum(BDK_SGPIO_STATIC_ON);
    push_bdk_enum(BDK_SGPIO_STATIC_OFF);
    push_bdk_enum(BDK_SGPIO_BLINK);

    lua_pushnumber(L, bdk_numa_master());
    lua_setfield(L, -2, "MASTER_NODE");
#endif
}

