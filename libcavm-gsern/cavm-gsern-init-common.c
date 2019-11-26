
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "cavm-gsern-api.h"
#include "cavm-gsern-settings.h"
#include "cavm-gsern-init.h"

/* Some fields in GSERN must be based on the VDD supplied to VDDA_GSER. This
   global contains the BDK's guess as what the voltage currently is in
   millivolts */
int cavm_gsern_voltage = 900; /* HRM recomendation, increase to 1000 for 25G */

/**
 * Wait for GSERNX_COMMON_INIT_BSTS[rst_sm_complete]
 *
 * @param node
 * @param qlm
 *
 * @return
 */
int cavm_gsern_init_wait_for_sm_complete(bdk_node_t node, int qlm)
{
    const int TIMEOUT = 10000; /* Timeout for wait loops in microsec */

    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 0;

    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_COMMON_INIT_BSTS(qlm), rst_sm_complete, ==, 1, TIMEOUT))
    {
        bdk_error("N%d.QLM%d: Timeout waiting for GSERNX_COMMON_INIT_BSTS[rst_sm_complete]\n", node, qlm);
        return -1;
    }
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_COMMON_INIT_BSTS(qlm), rst_sm_ready, ==, 1, TIMEOUT))
    {
        bdk_error("N%d.QLM%d: Timeout waiting for GSERNX_COMMON_INIT_BSTS[rst_sm_ready]\n", node, qlm);
        return -1;
    }
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_COMMON_INIT_BSTS(qlm), cal_ready, ==, 1, TIMEOUT))
    {
        bdk_error("N%d.QLM%d: Timeout waiting for GSERNX_COMMON_INIT_BSTS[cal_ready]\n", node, qlm);
        return -1;
    }
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_COMMON_INIT_BSTS(qlm), cal_fail, ==, 0, TIMEOUT))
    {
        bdk_error("N%d.QLM%d: Timeout waiting for GSERNX_COMMON_INIT_BSTS[cal_fail=0]\n", node, qlm);
        return -1;
    }
    return 0;
}

/**
 * Wait for GSERNX_LANEX_INIT_BSTS[rst_sm_ready]
 *
 * @param node
 * @param qlm
 * @param qlm_lane
 *
 * @return
 */
int cavm_gsern_init_wait_for_sm_ready(bdk_node_t node, int qlm, int qlm_lane)
{
    const int TIMEOUT = 10000; /* Timeout for wait loops in microsec */
    int num_lanes = bdk_qlm_get_lanes(node, qlm);

    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 0;

    for (int lane = 0; lane < num_lanes; lane++)
    {
       /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;

        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), rst_sm_complete, ==, 1, TIMEOUT))
        {
            bdk_error("N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[rst_sm_complete]\n", node, qlm, lane);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), rst_sm_ready, ==, 1, TIMEOUT))
        {
            bdk_error("N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[rst_sm_ready]\n", node, qlm, lane);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), cal_ready, ==, 1, TIMEOUT))
        {
            bdk_error("N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[cal_ready]\n", node, qlm, lane);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), cal_fail, ==, 0, TIMEOUT))
        {
            bdk_error("N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[cal_fail=0]\n", node, qlm, lane);
            return -1;
        }
    }
    return 0;
}

/**
 * Wait for GSERNX_LANEX_INIT_BSTS[rx_ready, rx_rst_sm_complete]
 *
 * @param node
 * @param qlm
 * @param qlm_lane
 *
 * @return
 */
int cavm_gsern_init_wait_for_rx_ready(bdk_node_t node, int qlm, int qlm_lane)
{
    const int TIMEOUT = 10000; /* Timeout for wait loops in microsec */
    int num_lanes = bdk_qlm_get_lanes(node, qlm);

    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 0;

    for (int lane = 0; lane < num_lanes; lane++)
    {
       /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;

        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), rx_ready, ==, 1, TIMEOUT))
        {
            BDK_TRACE(QLM, "N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[rx_ready]\n", node, qlm, lane);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), rx_rst_sm_complete, ==, 1, TIMEOUT))
        {
            BDK_TRACE(QLM, "N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[rx_rst_sm_complete]\n", node, qlm, lane);
            return -1;
        }
    }
    return 0;
}

/**
 * Wait for GSERNX_LANEX_INIT_BSTS[tx_ready, tx_rst_sm_complete]
 *
 * @param node
 * @param qlm
 * @param qlm_lane
 *
 * @return
 */
int cavm_gsern_init_wait_for_tx_ready(bdk_node_t node, int qlm, int qlm_lane)
{
    const int TIMEOUT = 10000; /* Timeout for wait loops in microsec */
    int num_lanes = bdk_qlm_get_lanes(node, qlm);

    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 0;

    for (int lane = 0; lane < num_lanes; lane++)
    {
       /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;

        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), tx_ready, ==, 1, TIMEOUT))
        {
            bdk_error("N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[tx_ready]\n", node, qlm, lane);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), tx_rst_sm_complete, ==, 1, TIMEOUT))
        {
            bdk_error("N%d.QLM%d.Lane%d: Timeout waiting for GSERNX_LANEX_INIT_BSTS[tx_rst_sm_complete]\n", node, qlm, lane);
            return -1;
        }
    }
    return 0;
}

