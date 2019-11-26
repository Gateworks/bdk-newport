/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gser.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(QLM_EYE);

/* Overview
    The eye capture hardware provides a window that "rotates" to find the eye.
    The time axis (X) ranges from 0-127.  When the X axis location changes
    from 127 to 0, the windows is rotated to the next position.  There are a
    total of 20 rotations before we repeat.  The voltage axis (Y) ranges from
    -31 to 31, where the eye should be centered at 0.  According to the very
    meager documentation, moving the eye sample location should be done one
    location at a time to prevent loss of sync.  We scan the eye out by
    traversing time (X) while sweeping the full voltage range (Y).  First we
    sweep min Y to max Y, then we step X one, and scan max Y to min Y.  This
    requires the least movements.  Before any of this scanning can be done, we
    have to find the right window rotation by search at Y=0 for a sequence of
    zero errors.  */

#define MAX_ROTATIONS   20  /* Number of "rotations" available in the hardware */
#define MAX_X           128 /* Maximum X location (time axis) */
#define MIN_Y           -31 /* Minimum Y location (voltage axis) */
#define MAX_Y           31  /* Maximum Y location (voltage axis) */

/**
 * Get the error counter for the current sample location
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 *
 * @return Number of errors
 */
static uint32_t GetErrorCount(bdk_node_t node, int qlm, int lane)
{
    uint32_t  ErrorCount = 0;  // Resulting Error Counts
    uint32_t  E[4];            // catch the 16 bit results

    for (int x = 0; x < 4; x++)
    {
        //
        // Set in register BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0[21:20] to select the RT-Eyemon bit counter
        //
        uint64_t reg =  BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0(qlm, lane));
        reg &=   ~(0x03 << 4);   // clear the bit field   (bit 20 - bit 16 = bit 4)
        reg |=    (x   << 4);   //  mask in the register Index;
        BDK_CSR_WRITE(node, BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0(qlm, lane), reg);
        BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0(qlm, lane));
        // read the status register
        E[x] =  BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CDR_STATUS_1(qlm, lane));
        ErrorCount |=  (((E[x] >> 7) & 0xff) << (x * 8));
    } // end x
    return ErrorCount;
}

/**
 * Enable or disable the eye error counter
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 * @param enable 1=Enable error counter, 0=disable
 */
static void ErrorCounterEnable(bdk_node_t node, int qlm, int lane, int enable)
{
    // Set in register BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0 [7] to enable
    const uint64_t EYE_MONITOR_COUNTER_ENABLE = 0x01 << 7;
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0(qlm, lane),
        if (enable)
            c.u |= EYE_MONITOR_COUNTER_ENABLE;
        else
            c.u &= ~EYE_MONITOR_COUNTER_ENABLE);
}

/**
 * Enable or disable the eye monitor
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 * @param enable 1=enable, 0=disable
 */
static void RTEnable(bdk_node_t node, int qlm, int lane, int enable)
{
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CFG_0(qlm, lane),
        c.s.pcs_sds_rx_eyemon_en = enable);
}

/**
 * Enable or disable the eye shadow PIV
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 * @param enable 1=enable, 0=disable
 */
static void ShadowPIVEnable(bdk_node_t node, int qlm, int lane, int enable)
{
    // Set in register BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0[6] to enable the Shadow PI Clock
    const uint64_t EYE_MONITOR_SHADOW_PI_CONTROL_ENABLE = 0x01 << 6;
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CDR_MISC_CTRL_0(qlm, lane),
        if (enable)
            c.u |= EYE_MONITOR_SHADOW_PI_CONTROL_ENABLE;
        else
            c.u &= ~EYE_MONITOR_SHADOW_PI_CONTROL_ENABLE);
}

/**
 * Move the eye sample location. The hardware may lose lock if we move the shadow
 * sampler in large steps. This code reads the current location and moves the
 * sampler one step at a time. Note that if told to move to 128 (MAX_X), we will
 * move up to 127 and then jump to 0, causing a rotation.
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 * @param x      Location along the X axis (time) (0-127, or 128)
 * @param y      Location along Y axis (-31,31)
 */
static void eye_move_location(bdk_node_t node, int qlm, int lane, int x, int y)
{
    /* Time (us) to settle between location movements (Default 50us) */
    const int SETTLE_TIME = 50;

    /* Extract the current Y location from DWC_RX_CFG_4[13:8] */
    uint64_t reg = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CFG_4(qlm, lane));
    int current_y = bdk_extract(reg, 8, 6);
    if (current_y & 0x20)
    {
        /* Convert negative */
        current_y &= 0x1f;
        current_y = -current_y;
    }

    /* Calculate step direction. The hardware may lose sync if we step by more
       than one */
    int step_y = (y > current_y) ? 1 : -1;

    while (current_y != y)
    {
        current_y += step_y;
        int tmp_y = current_y;
        /* Convert negative */
        if (current_y < 0)
            tmp_y = -current_y | 0x20;
        uint64_t reg = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CFG_4(qlm, lane));
        reg = bdk_insert(reg, tmp_y, 8, 6);
        BDK_CSR_WRITE(node, BDK_GSERX_LANEX_RX_CFG_4(qlm, lane), reg);
        bdk_wait_usec(SETTLE_TIME);
    }

    /* Extract the current X location */
    reg = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CDR_CTRL_2(qlm, lane));
    int current_x = bdk_extract(reg, 8, 7);

    /* Calculate step direction. The hardware may lose sync if we step by more
       than one */
    int step_x = (x > current_x) ? 1 : -1;

    while (current_x != x)
    {
        current_x += step_x;
        reg = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CDR_CTRL_2(qlm, lane));
        reg = bdk_insert(reg, current_x, 8, 7);
        BDK_CSR_WRITE(node, BDK_GSERX_LANEX_RX_CDR_CTRL_2(qlm, lane), reg);
        bdk_wait_usec(SETTLE_TIME);
    }
}

/**
 * Move the eye sample location and measure the errors at that location. See
 * eye_move_location() for more detail about the moving of the sample location as
 * this function wraps eye_move_location().
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param lane   Lane to access
 * @param x      Location along the X axis (time) (0-127, or 128)
 * @param y      Location along Y axis (-31,31)
 *
 * @return Number of errors
 */
static uint32_t eye_measure_errors(bdk_node_t node, int qlm, int lane, int x, int y)
{
    /* Time (us) to count errors at each location (default 400us) */
    const int SAMPLE_TIME = 400;

    eye_move_location(node, qlm, lane, x, y);
    ErrorCounterEnable(node, qlm, lane, 1);

    bdk_wait_usec(SAMPLE_TIME);

    uint32_t errors = GetErrorCount(node, qlm, lane);
    ErrorCounterEnable(node, qlm, lane, 0);
    return errors;
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
int __bdk_qlm_eye_capture_cn8xxx(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data)
{
    //  this errata removes the read timeout.
    //   BUG BUG  CN78 1.0 SILICON -> DISABLE READ TIMEOUT
    BDK_CSR_MODIFY(c, node, BDK_GSERX_SCRATCH(qlm),
        c.u |=  0x01 << 15);

    /* Freeze the rx equalization */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PWR_CTRL(qlm, lane),
        c.u |= 0x40);
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_LOOP_CTRL(qlm, lane),
        c.u |= 0x01);

    /* Save the Voltage Slicer.  It needs to be restored at the end. Else,
       calibration and other functions will fail */
    const uint64_t Q_QB_ERR = 0x3f << 8;
    uint64_t Q_QB_ES_Original = Q_QB_ERR &  BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_CFG_4(qlm, lane));

    /* Assert Shadow PI power enable bit:
       DWC_RX_MISC_CTRL.pcs_sds_rx_misc_ctrl[0] = 1'b1 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_MISC_CTRL(qlm, lane),
        c.u = bdk_insert(c.u, 1, 0, 1));

    /* Set Shadow PI phase to the middle of first UI:
       DWC_RX_CDR_CTRL_2.cfg_rx_cdr_ctrl_ovrrd_val_15_0[14:8] = 7'd32 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CDR_CTRL_2(qlm, lane),
        c.u = bdk_insert(c.u, 32, 8, 7));

    /* Enable the shadow relative mode PI phase control by setting the following field:
       DWC_RX_CDR_CTRL_2.cfg_rx_cdr_ctrl_ovrrd_val_15_0[15] = 1'b0
       Note: A bit value of 1 is the absolute mode and 0 is the relative mode. */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CDR_CTRL_2(qlm, lane),
        c.u = bdk_insert(c.u, 0, 15, 1));

    /* Turn on the RT-eye monitor test circuit by setting the following field
       to one:
       DWC_RX_CFG_0.pcs_sds_rx_eyemon_en = 1'b1 */
    RTEnable(node, qlm, lane, 1);

    /* Enable the shadow PI clock and error sampler by setting bit 22 of the
       23:16 range. That is, modify bit 6 of the 8 bits in the following
       register as shown below:
       DWC_RX_CDR_MISC_CTRL_0.pcs_sds_rx_cdr_misc_ctrl_23_16[6] = 1'b1 */
    ShadowPIVEnable(node, qlm, lane, 1);

    printf("Searching for eye...\n");
    /* Number of consecutive zeros that signals an eye (default 2) */
    const int NUM_ZEROS = 2;

    int zero_location = -1; /* Location of the eye */
    /* Step through all rotations looking for the eye */
    for (int rotation = 0; rotation < MAX_ROTATIONS; rotation++)
    {
        int zero_count = 0;
        for (int x = 0; x < MAX_X; x++)
        {
            uint32_t errors = eye_measure_errors(node, qlm, lane, x, 0);
            if (errors == 0)
            {
                zero_count++;
                if (zero_count >= NUM_ZEROS)
                {
                    /* We have enough zeros, mark the eye as found */
                    zero_location = x - (zero_count - 1);
                    break;
                }
            }
            else
                zero_count = 0;
        }
        /* Don't rotate the window if we found the eye */
        if (zero_location != -1)
            break;
        /* rotate the window */
        eye_move_location(node, qlm, lane, MAX_X, 0);
    }

    /* Warn the user if we were unable to find the eye */
    if (zero_location == -1)
        bdk_warn("N%d.QLM%d: Unable to find eye on lane %d\n", node, qlm, lane);

    printf("Capturing eye...\n");
    /* Loop through time with a step of two. See comment below about why it is
       two */
    for (int x = 0; x < MAX_X; x += 2)
    {
        /* We need to sweep through all Y locations. Since it takes time to
           move the sample point, we first scan up, then down. This way we
           only ever move one spot at a time. X must increment by two
           because of this */
        for (int y = MIN_Y; y <= MAX_Y; y++)
            eye_data->data[y - MIN_Y][x] = eye_measure_errors(node, qlm, lane, x, y);
        for (int y = MAX_Y; y >= MIN_Y; y--)
            eye_data->data[y - MIN_Y][x + 1] = eye_measure_errors(node, qlm, lane, x + 1, y);
    }

    /* Save the overall size */
    eye_data->width = MAX_X;
    eye_data->height = MAX_Y - MIN_Y + 1;

    /* Move back to the middle Y position. This covers this step from the docs:
       Set Shadow PI phase to middle of UI. Walk the value back to 7'd32 in
       steps of 2 or 1 until:
       DWC_RX_CDR_CTRL_2.cfg_rx_cdr_ctrl_ovrrd_val_15_0[14:8] = 7'd32 */
    eye_move_location(node, qlm, lane, MAX_X - 1, 0);

    /* Disable the shadow PI clock and Error Sampler by setting bit 22 of the
       23:16 range. That is, modify bit 6 of the 8 bits in the following
       register as shown below:
       DWC_RX_CDR_MISC_CTRL_0[6] = 0 */
    ShadowPIVEnable(node, qlm, lane, 0);

    /* Turn off the RT-eye monitor test circuit by setting the following field
       to one:
       DIG.DWC_RX_CFG_0.PCS_SDS_RX_EYEMON_EN = 0 */
    RTEnable(node, qlm, lane, 0);

    /* De-assert Shadow PI power enable bit:
       pcs_sds_rx_misc_ctrl[0] = 1'b0 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_MISC_CTRL(qlm, lane),
        c.u = bdk_insert(c.u, 0, 0, 1));

    /* Restore the Voltage Slicer */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CFG_4(qlm, lane),
        c.u &= ~Q_QB_ERR;         // clear the bit field
        c.u |= Q_QB_ES_Original);   // mask in the Starting Value;

    /* Un-freeze the rx equalization */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PWR_CTRL(qlm, lane),
        c.u &= ~0x40);
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_LOOP_CTRL(qlm, lane),
        c.u &= ~0x01);

    /* Reset Lane RX circuitry */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PWR_CTRL(qlm, lane),
        c.u |= 0x100);
    bdk_wait_usec(10);
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PWR_CTRL(qlm, lane),
        c.u &= ~0x100);

    /* Per Joe V. request, add a delay so reset completes */
    bdk_wait_usec(1000); /* 1ms */
    return 0;
}
