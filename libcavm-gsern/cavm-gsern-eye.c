/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "cavm-gsern-api.h"

/* GSERN requires a short hold time between most changes to time or
   voltage. Theser are defined as 1.6us, but the BDK uses integers,
   so round up to 2us */
#define SETTLE_TIME 2

/**
 * Move the eye sample location. The hardware may lose lock if we move
 * the sampler in large steps. This code reads the current location and
 * moves the sampler one step at a time.
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 * @param t      Location along the X axis (time) (0-63)
 * @param v      Location along Y axis (voltage) (0-31)
 */
static void eye_move_location(bdk_node_t node, int qlm, int lane, int t, int v)
{
    /* Move along the X axis (time) */
    BDK_CSR_INIT(cdrfsm_bcfg, node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, lane));
    while (cdrfsm_bcfg.s.eoffs != t)
    {
        if (cdrfsm_bcfg.s.eoffs > t)
            cdrfsm_bcfg.s.eoffs--;
        else
            cdrfsm_bcfg.s.eoffs++;
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, lane), cdrfsm_bcfg.u);
        bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_QAC_BCFG(qlm, lane),
            c.s.cdr_qac_sele = 0);
        bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
    }

    /* Move along the Y axis (voltage) */
    BDK_CSR_INIT(rx_os_5_bcfg, node, BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, lane));
    while (rx_os_5_bcfg.s.c1_e_adjust != v)
    {
        if (rx_os_5_bcfg.s.c1_e_adjust > v)
            rx_os_5_bcfg.s.c1_e_adjust--;
        else
            rx_os_5_bcfg.s.c1_e_adjust++;
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, lane), rx_os_5_bcfg.u);
        bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
    }
}

/**
 * Measure the number of errors over a number of GSERN cycles
 *
 * @param node   Node to measure
 * @param qlm    DLM/QLM to measure
 * @param lane   Lane in QLM/DLM
 * @param cycles Cycles to measure over
 *
 * @return Number of errors, max uint64 if failure
 */
static uint64_t eye_measure_errors(bdk_node_t node, int qlm, int lane, uint64_t cycles)
{
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL(qlm, lane),
        c.s.rst_n = 0);
    /* Load Cycle Count */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL(qlm, lane),
        c.s.cycle_cnt_en = 1;
        c.s.cycle_cnt = cycles);
    /* Start Eye Measurement */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL(qlm, lane),
        c.s.eye_en = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL(qlm, lane),
        c.s.rst_n = 1);
    /* Wait for eye measurement done */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_EYE_DAT(qlm, lane), cycle_cnt_done, ==, 1, 10000000))
    {
        bdk_warn("Timeout waiting for cycle to complete, aborting eye\n");
        return UINT64_MAX;
    }
    /* Stop the eye */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL(qlm, lane),
        c.s.eye_en = 0);
    /* Read Error count */
    BDK_CSR_INIT(eye_dat, node, BDK_GSERNX_LANEX_EYE_DAT(qlm, lane));
    if (eye_dat.s.err_cnt_ovf || (eye_dat.s.err_cnt > UINT32_MAX))
        return UINT32_MAX;
    else
        return eye_dat.s.err_cnt;
}

/**
 * Capture an eye diagram for the given QLM lane. The output data is written
 * to "eye".
 *
 * @param node      Node to use in numa setup
 * @param qlm       QLM to use
 * @param qlm_lane  Which lane
 * @param show_data Set to non-zero to have the eye capture dump the raw eye data as
 *                  it is captured
 * @param eye       Output eye data
 *
 * @return Zero on success, negative on failure
 */
int cavm_gsern_eye_capture(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data)
{
    const int TIMEOUT = 10000; /* 10ms */
    int return_status = 0;

    BDK_CSR_INIT(cdrfsm_bcfg_original, node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, lane));

    /* Disable DFE Periodic Offset update */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_24_BCFG(qlm, lane),
        c.s.dfe_oscomp_timer_en = 0);

    /* Power-up the eye monitor */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
        c.s.rst_eye_rst_sm = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
        c.s.ln_reset_use_eye = 1);

    /* Poll for eye monitor ready */
    if (BDK_CSR_WAIT_FOR_FIELD(node,BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), eye_ready, ==, 1, TIMEOUT))
    {
        bdk_error("N%d.QLM%d.Lane%d: Eye monitor not ready\n", node, qlm, lane);
        return -1;
    }

    /* Calculate the number of cycles to sample over */
    const int BER = 6;
    uint64_t cycles = 1;
    for (int b = 0; b < BER; b++) /* Loop avoids math library for power */
        cycles *= 10;

    int v_height = 32;
    eye_data->width = 0x3b;
    eye_data->height = v_height * 2 - 1;

    /* Determine if we're in 20 bit or 40 bit mode */
    BDK_CSR_INIT(bcfg, node, BDK_GSERNX_LANEX_PCS_802P3_BCFG(qlm, lane));
    int bus_width = bcfg.s.rx_wpk_20b40b ? 20 : 40;

    if (show_data)
    {
        printf("# Extensive 1D Rx Eye on GSER%d Lane %d\n", qlm, lane);
        printf("# Start Time Offset: 0; End Time Offset: %d\n", eye_data->width - 1);
        printf("# eyemon %d %d %d %d %d %d %d %d %d %d %s %s\n",
            qlm, lane,
            0 /* vmin */, eye_data->height-1 /* vmax */, 1 /* vstep */,
            0 /* tmin */, eye_data->width-1 /* tmax */, 1 /* tstep */,
            BER /* BER */, 0 /* OffsetOverrideEn */, "DOUTQ" /* PTYPE */, "NO_SHIFT" /* SHIFT */);
        printf("# cycle count = %lu, bus width = %d\n", cycles, bus_width);
        printf("V  T  %-20s %-20s %-20s %-20s\n", "TRANS_ONE_ECNT",
            "NON_TRANS_ONE_ECNT", "TRANS_ZEROS_ECNT", "NON_TRANS_ZEROS_ECNT");
    }
    else
        printf("Capturing eye...\n");

    /* Initialize eyeEoffs from eyeQacEoffs */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_QAC_BCFG(qlm, lane),
        c.s.en_qac_e = 0);
    bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
    BDK_CSR_INIT(rx_qac_bsts, node, BDK_GSERNX_LANEX_RX_QAC_BSTS(qlm, lane));
    int eye_eoffs = rx_qac_bsts.s.qac_eoffs;
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, lane),
        c.s.eoffs = eye_eoffs);
    int delta_eye = eye_eoffs - 0x20;
    if (delta_eye < 0)
        delta_eye = 0;

    /* Scan the eye monitor across the area */
    for (int t = 0; t < eye_data->width; t++)
    {
        for (int v = 0; v < v_height; v++)
        {
            eye_move_location(node, qlm, lane, t + delta_eye, v);

            /* Configure Eye Monitor to capture Non-Transitions Ones */
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL_2(qlm, lane),
                c.s.capture_ones_en = 1;
                c.s.capture_ones = 1;
                c.s.capture_edgemode = 0;
                c.s.capture_trans = 0;
                c.s.eye_adapt_en = 1);
            bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
            uint64_t errors_nt_ones = eye_measure_errors(node, qlm, lane, cycles);
            if (errors_nt_ones == UINT64_MAX)
            {
                return_status = -1;
                goto fail;
            }
            /* Configure Eye Monitor to Capture Transitions Ones */
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL_2(qlm, lane),
                c.s.capture_ones_en = 1;
                c.s.capture_ones = 1;
                c.s.capture_edgemode = 1;
                c.s.capture_trans = 1;
                c.s.eye_adapt_en = 1);
            bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
            uint64_t errors_tr_ones = eye_measure_errors(node, qlm, lane, cycles);
            if (errors_tr_ones == UINT64_MAX)
            {
                return_status = -1;
                goto fail;
            }
            /* Configure Eye Monitor to capture Non-Transitions Zeros */
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL_2(qlm, lane),
                c.s.capture_ones_en = 0;
                c.s.capture_ones = 0;
                c.s.capture_edgemode = 0;
                c.s.capture_trans = 0;
                c.s.eye_adapt_en = 1);
            bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
            uint64_t errors_nt_zeros = eye_measure_errors(node, qlm, lane, cycles);
            if (errors_nt_zeros == UINT64_MAX)
            {
                return_status = -1;
                goto fail;
            }
            /* Configure Eye Monitor to capture Transitions Zeros */
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL_2(qlm, lane),
                c.s.capture_ones_en = 0;
                c.s.capture_ones = 0;
                c.s.capture_edgemode = 1;
                c.s.capture_trans = 1;
                c.s.eye_adapt_en = 1);
            bdk_wait_usec(SETTLE_TIME); /* 1.6 us */
            uint64_t errors_tr_zeros = eye_measure_errors(node, qlm, lane, cycles);
            if (errors_tr_zeros == UINT64_MAX)
            {
                return_status = -1;
                goto fail;
            }
            if (show_data)
            {
                printf("%02x %02x %020lx %020lx %020lx %020lx\n",
                    v, t, errors_tr_ones, errors_nt_ones,
                    errors_tr_zeros, errors_nt_zeros);
            }
            uint64_t total_ones = errors_nt_ones + errors_tr_ones;
            if (total_ones > UINT32_MAX)
                total_ones = UINT32_MAX;
            uint64_t total_zeros = errors_nt_zeros + errors_tr_zeros;
            if (total_zeros > UINT32_MAX)
                total_zeros = UINT32_MAX;
            eye_data->data[v_height - v - 1][t] = total_ones;
            eye_data->data[v_height + v - 1][t] = total_zeros;
        }
    }
fail:
    /* Power-down the eye monitor */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
        c.s.ln_reset_use_eye = 0);

    /* Re-Enable DFE Periodic Offset update */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_24_BCFG(qlm, lane),
        c.s.dfe_oscomp_timer_en = 1);

    /* Reset the eye monitor  */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, lane),
        c.s.eoffs = cdrfsm_bcfg_original.s.eoffs);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_QAC_BCFG(qlm, lane),
        c.s.en_qac_e = 1;
        c.s.en_qac_q = 1;
        c.s.cdr_qac_sele = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL_2(qlm, lane),
        c.s.capture_edgemode = 0;
        c.s.capture_trans = 0;
        c.s.eye_adapt_en = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_EYE_CTL(qlm, lane),
        c.s.cycle_cnt_en = 0;
        c.s.rst_n = 0);
    return return_status;
}
