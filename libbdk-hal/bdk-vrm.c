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

    const int NUM_VRM = CAVIUM_IS_MODEL(CAVIUM_CN88XX) ? 2 : 1;
    /* Set the temperature for thermal trip */
    int temp_trip = bdk_config_get_int(BDK_CONFIG_VRM_TEMP_TRIP, node);
    if (temp_trip)
    {
        for (int i = 0; i < NUM_VRM; i++)
            BDK_CSR_MODIFY(c, node, BDK_VRMX_TRIP(i),
                c.s.trip_level = temp_trip);
    }

    /* Don't perform polling on CN88XX pass 1.x. The throttling uses DAP
       core acceses that have an errata on pass 1.x (DAP-24000) */
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        return 0;

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
    /* Don't perform polling on CN88XX pass 1.x. The throttling uses DAP
       core acceses that have an errata on pass 1.x (DAP-24000) */
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        return 0;

    const int NUM_VRM = CAVIUM_IS_MODEL(CAVIUM_CN88XX) ? 2 : 1;
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

