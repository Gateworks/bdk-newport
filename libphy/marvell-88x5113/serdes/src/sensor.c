/* AAPL CORE Revision: 2.4.0
 *
 * Copyright (c) 2014-2016 Avago Technologies. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/** @file   sensor.c
 ** @brief  Functions for accessing Avago sensors (for temperature, voltage, etc.).
 ** @defgroup Sensor Sensor API for Measuring Temperature and Voltage
 ** @{
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#define AAPL_LOG_PRINT5 if(aapl->debug >= 5) aapl_log_printf

/** @brief Prepare sensor for measurement */
static void initialize_sensor(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address. */
    uint frequency) /**< [in] Sensor clock input frequency in Hertz. */
                    /**<      If non-zero, configures the sensor, */
                    /**<      which only need be done once. */
{
    avago_sbus_wr(aapl, addr, 0x00, 0x01);
    if( frequency > 0 )
    {
        uint divider = (frequency + 1000000) / 2000000;
        avago_sbus_wr(aapl, addr, 0x01, divider & 0x03FF);
    }
    if (aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B)
    {
        avago_sbus_wr(aapl, addr, 0x06, 0x4fe4);
        avago_sbus_wr(aapl, addr, 0x07, 0xb5dd);
        avago_sbus_wr(aapl, addr, 0x08, 0x1e);
        avago_sbus_wr(aapl, addr, 0x0b, 0x07);
        avago_sbus_wr(aapl, addr, 0x0c, 0x5e70);
        avago_sbus_wr(aapl, addr, 0x0e, 0x2a);
        avago_sbus_wr(aapl, addr, 0x10, 0x5);
        /*//avago_sbus_wr(aapl, addr, 0x13, 0x0); */
        /*//avago_sbus_wr(aapl, addr, 0x14, 0x5); */
    }
}

/** @brief   Starts a temperature measurement.
 ** @details Use this function to start measurements on multiple devices.
 ** @details Note that each device (sensor sbus address) can perform only
 **          one measurement (voltage or temperature) at a time.
 ** @see avago_sensor_wait_temperature(), avago_sensor_get_temperature().
 **/
void avago_sensor_start_temperature(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address.  Chip/ring broadcast OK. */
    int sensor,     /**< [in] Which sensor to access. A value of 0 selects */
                    /**<      the main sensor. Values of 1 through 8 */
                    /**<      select remote sensors 0 through 7. */
    uint frequency) /**< [in] Sensor clock input frequency in Hertz. */
                    /**<      If non-zero, configures the sensor, */
                    /**<      which only need be done once. */
{
    initialize_sensor(aapl, addr, frequency);
    if( sensor > 8 ) sensor = 0;
    avago_sbus_wr(aapl, addr, 0x03, 0x01 << sensor );
    avago_sbus_wr(aapl, addr, 0x00, 0x02);
}

/** @brief   Performs a blocking read on a temperature sensor, which is
 **          assumed to be properly initialized.
 ** @return  On success, returns the temperature in milli-degrees C.
 ** @return  On error, decrements aapl->return_code and returns -1000000.
 ** @see avago_sensor_start_temperature(), avago_sensor_get_temperature().
 **/
int avago_sensor_wait_temperature(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address. */
    int sensor)     /**< [in] Which sensor to access. A value of 0 selects */
                    /**<      the main sensor. Values of 1 through 8 */
                    /**<      select remote sensors 0 through 7. */
{
    int i;
    for( i = 0; i < 16; i++ )
    {
        int data;
        if( i > 0 ) ms_sleep(5);
        data = avago_sbus_rd(aapl, addr, 65 + sensor);
        if( data & 0x8000 )
        {
            int temp;
            if( data & 0x800 )
                temp = data | ~0x7ff;
            else
                temp = data & 0x7ff;
            temp *= 125;
            AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Temp = %7d mC (data=0x%x, %d reads)\n", temp, data, i+1);
            return temp;
        }
    }

    aapl_fail(aapl, __func__, __LINE__, "SBus 0x%02x, Temperature conversion failed, returning -1000000 after %d reads.\n",addr, i);
    return -1000000;
}


/** @brief   Performs a temperature measurement.
 ** @details Combines the start and wait functions into one blocking operation.
 ** @return  On success, returns the temperature in milli-degrees C.
 ** @return  On error, decrements aapl->return_code and returns -1000000.
 ** @see     avago_sensor_start_temperature(), avago_sensor_wait_temperature().
 ** @see     avago_sensor_get_voltage().
 **/
int avago_sensor_get_temperature(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address. */
    int sensor,     /**< [in] Which sensor to access. A value of 0 selects */
                    /**<      the main sensor. Values of 1 through 8 */
                    /**<      select remote sensors 0 through 7. */
    uint frequency) /**< [in] Sensor clock input frequency in Hertz. */
                    /**<      If non-zero, configures the sensor, */
                    /**<      which only need be done once. */
{
    avago_sensor_start_temperature(aapl, addr, sensor, frequency);
    return avago_sensor_wait_temperature(aapl, addr, sensor);
}


/** @brief   Starts a voltage measurement.
 ** @details Use this function to start measurements on multiple devices.
 ** @details Note that each device (sensor sbus address) can perform only
 **          one measurement (voltage or temperature) at a time.
 ** @see     avago_sensor_wait_voltage(), avago_sensor_get_voltage().
 **/
void avago_sensor_start_voltage(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address.  Chip/ring broadcast OK. */
    int sensor,     /**< [in] Which sensor to access.  A value of 0 selects */
                    /**<      the VDD voltage, 1 selects CORE_VDD_VIN, and */
                    /**<      values [2..7] select SENSOR_A2D_VIN[0..5] */
    uint frequency) /**< [in] Sensor clock input frequency in Hertz. */
                    /**<      If non-zero, configures the sensor, */
                    /**<      which only need be done once. */
{
    if( sensor > 7 ) sensor = 0;
    initialize_sensor(aapl, addr, frequency);
    avago_sbus_wr(aapl, addr, 0x03, 0x200 << sensor );
    avago_sbus_wr(aapl, addr, 0x00, 0x02);
}

/** @brief   Performs a blocking read on a voltage sensor, which is
 **          assumed to be properly initialized.
 ** @return  On success, returns the voltage in mV.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_sensor_start_voltage(), avago_sensor_get_voltage().
 **/
int avago_sensor_wait_voltage(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address. */
    int sensor)     /**< [in] Which sensor to access.  A value of 0 selects */
                    /**<      the VDD voltage, 1 selects CORE_VDD_VIN, and */
                    /**<      values [2..7] select SENSOR_A2D_VIN[0..5] */
{
    int i;
    for( i = 0; i < 8; i++ )
    {
        uint data;
        if( i > 0 ) ms_sleep(4);
        data = avago_sbus_rd(aapl, addr, 74 + sensor);
        if( data & 0x8000 )
        {
            uint avdd = (data & 0xfff) / 2;
            AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Voltage = %4d mV (data=0x%x, %d reads)\n",avdd,data,i+1);
            return avdd;
        }
    }
    return aapl_fail(aapl, __func__, __LINE__, "Voltage conversion failed, returning -1 after %d reads.\n",i);
}

/** @brief   Performs a voltage measurement.
 ** @details Combines the start and wait functions into one blocking operation.
 ** @return  On success, returns the voltage in mV.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_sensor_start_voltage(), avago_sensor_wait_voltage().
 ** @see     avago_sensor_get_temperature().
 **/
int avago_sensor_get_voltage(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address. */
    int sensor,     /**< [in] Which sensor to access.  A value of 0 selects */
                    /**<      the VDD voltage, 1 selects CORE_VDD_VIN, and */
                    /**<      values [2..7] select SENSOR_A2D_VIN[0..5] */
    uint frequency) /**< [in] Sensor clock input frequency in Hertz. */
                    /**<      If non-zero, configures the sensor, */
                    /**<      which only need be done once. */
{
    avago_sensor_start_voltage(aapl, addr, sensor, frequency);
    return avago_sensor_wait_voltage(aapl, addr, sensor);
}


/** @} */

