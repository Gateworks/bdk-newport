/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>

/**
 * Called to register the octeontx module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_constants(lua_State* L)
{
    #define push_bdk_enum(enum)             \
        do                                  \
        {                                   \
            lua_pushnumber(L, enum);        \
            lua_setfield(L, -2, ((const char *)#enum) + 4); \
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
    push_bdk_enum(BDK_QLM_MODE_PCIE_X1);
    push_bdk_enum(BDK_QLM_MODE_PCIE_X2);
    push_bdk_enum(BDK_QLM_MODE_PCIE_X4);
    push_bdk_enum(BDK_QLM_MODE_PCIE_X8);
    push_bdk_enum(BDK_QLM_MODE_PCIE_X16);
    push_bdk_enum(BDK_QLM_MODE_SATA);
    push_bdk_enum(BDK_QLM_MODE_SGMII);
    push_bdk_enum(BDK_QLM_MODE_1G_X);
    push_bdk_enum(BDK_QLM_MODE_QSGMII);
    push_bdk_enum(BDK_QLM_MODE_XAUI);
    push_bdk_enum(BDK_QLM_MODE_RXAUI);
    push_bdk_enum(BDK_QLM_MODE_XFI);
    push_bdk_enum(BDK_QLM_MODE_SFI);
    push_bdk_enum(BDK_QLM_MODE_XLAUI);
    push_bdk_enum(BDK_QLM_MODE_XLAUI_C2M);
    push_bdk_enum(BDK_QLM_MODE_10G_KR);
    push_bdk_enum(BDK_QLM_MODE_40G_KR4);
    push_bdk_enum(BDK_QLM_MODE_20GAUI_C2C);
    push_bdk_enum(BDK_QLM_MODE_25GAUI_C2C);
    push_bdk_enum(BDK_QLM_MODE_25GAUI_C2M);
    push_bdk_enum(BDK_QLM_MODE_25GAUI_2_C2C);
    push_bdk_enum(BDK_QLM_MODE_40GAUI_2_C2C);
    push_bdk_enum(BDK_QLM_MODE_50GAUI_2_C2C);
    push_bdk_enum(BDK_QLM_MODE_50GAUI_2_C2M);
    push_bdk_enum(BDK_QLM_MODE_50GAUI_4_C2C);
    push_bdk_enum(BDK_QLM_MODE_80GAUI_4_C2C);
    push_bdk_enum(BDK_QLM_MODE_CAUI_4_C2C);
    push_bdk_enum(BDK_QLM_MODE_CAUI_4_C2M);
    push_bdk_enum(BDK_QLM_MODE_USXGMII_4X1);
    push_bdk_enum(BDK_QLM_MODE_USXGMII_2X1);
    push_bdk_enum(BDK_QLM_MODE_USXGMII_1X1);

    push_bdk_enum(BDK_QLM_CLK_COMMON_0);
    push_bdk_enum(BDK_QLM_CLK_COMMON_1);
    push_bdk_enum(BDK_QLM_CLK_COMMON_2);
    push_bdk_enum(BDK_QLM_CLK_EXTERNAL);

    push_bdk_enum(BDK_QLM_MODE_FLAG_ENDPOINT);

    push_bdk_enum(BDK_QLM_LOOP_DISABLED);
    push_bdk_enum(BDK_QLM_LOOP_SHALLOW);
    push_bdk_enum(BDK_QLM_LOOP_NEAR_END);
    push_bdk_enum(BDK_QLM_LOOP_CORE);

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
    push_bdk_enum(BDK_POWER_BURN_WFE);

    lua_pushnumber(L, bdk_numa_master());
    lua_setfield(L, -2, "MASTER_NODE");
#endif
}

