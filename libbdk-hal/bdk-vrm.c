/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-vrm.h"

/**
 * Initialize the VRM
 *
 * @return Zero on success, negative on failure
 */
int bdk_vrm_initialize(bdk_node_t node)
{
    /* Skip throttle setup on Asim */
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    const int NUM_VRM = 1;
    /* Set the temperature for thermal trip */
    int temp_trip = bdk_config_get_int(BDK_CONFIG_VRM_TEMP_TRIP, node);
    if (temp_trip)
    {
        for (int i = 0; i < NUM_VRM; i++)
            BDK_CSR_MODIFY(c, node, BDK_VRMX_TRIP(i),
                c.s.trip_level = temp_trip);
    }

    /* The poll below will override this default */
    const int THROTTLE_NORMAL = bdk_config_get_int(BDK_CONFIG_VRM_THROTTLE_NORMAL, node);
    bdk_power_throttle(node, THROTTLE_NORMAL);

    /* Poll VRM status after setup */
    return bdk_vrm_poll(node);
}

/**
 * The VRM may be reporting temperature or other issues with the system. Poll the
 * VRM and handle any throttling or other actions needed.
 *
 * @param node   Node to poll
 *
 * @return Zero on success, negative on failure
 */
int bdk_vrm_poll(bdk_node_t node)
{
    const int NUM_VRM = 1;
    /* VRMX_TS_TEMP_CONV_RESULT[temp_corrected] has the lower two bits as a
       fractional part for better accuracy. FRACTIONAL represents the scale
       factor required to convert Celsius to the temp_corrected format */
    const int FRACTIONAL = 4;

    /* Check if temperature based throttling is configured */
    const int THROTTLE_THERM = bdk_config_get_int(BDK_CONFIG_VRM_THROTTLE_THERM, node);
    if (THROTTLE_THERM < 100)
    {
        /* Determine the max temperature based on all VRMs */
        int current_temp = -100 * FRACTIONAL;
        for (int vrm = 0; vrm < NUM_VRM; vrm++)
        {
            BDK_CSR_INIT(vrmx_misc_info, node, BDK_VRMX_MISC_INFO(vrm));
            /* Don't use the temperature result unless it is calibrated with
               thermal fuses */
            if (vrmx_misc_info.s.ts_fuse_sts)
            {
                BDK_CSR_INIT(conv_result, node, BDK_VRMX_TS_TEMP_CONV_RESULT(vrm));
                /* temp_corrected is 11 bit two's complement */
                int temp = bdk_extracts(conv_result.s.temp_corrected, 0, 11);
                if (temp > current_temp)
                    current_temp = temp;
            }
        }

        /* Only update throttling if we could read a valid temperature */
        if (current_temp > -100 * FRACTIONAL)
        {
            const int THROTTLE_NORMAL = bdk_config_get_int(BDK_CONFIG_VRM_THROTTLE_NORMAL, node);
            const int TEMP_HIGH = bdk_config_get_int(BDK_CONFIG_VRM_TEMP_HIGH, node) * FRACTIONAL;
            const int TEMP_LOW = bdk_config_get_int(BDK_CONFIG_VRM_TEMP_LOW, node) * FRACTIONAL;
            int desired_throttle;
            if (current_temp >= TEMP_HIGH) /* Check for overheat */
                desired_throttle = THROTTLE_THERM;
            else if (current_temp <= TEMP_LOW) /* Check for min temperature, max performance */
                desired_throttle = THROTTLE_NORMAL;
            else /* Scale between LOW and HIGH */
                desired_throttle = THROTTLE_NORMAL + (THROTTLE_THERM - THROTTLE_NORMAL) * (current_temp - TEMP_LOW) / (TEMP_HIGH - TEMP_LOW);
            /* Double check that we are in the throttle range */
            if (desired_throttle > THROTTLE_NORMAL)
                desired_throttle = THROTTLE_NORMAL;
            if (desired_throttle < THROTTLE_THERM)
                desired_throttle = THROTTLE_THERM;
            /* Apply the new throttle level */
            bdk_power_throttle(node, desired_throttle);
        }
    }
    return 0;
}

