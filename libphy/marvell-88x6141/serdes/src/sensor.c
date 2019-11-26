/* AAPL CORE Revision: 2.6.2
 *
 * Copyright (c) 2014-2017 Avago Technologies. All rights reserved.
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


static void avago_apb_start_read(Aapl_t *aapl, uint addr, int reg)
{
    if( (reg & ~0xffff) == 0 )
        avago_sbus_wr(aapl, addr, 11, (reg & 0xffff) | (1<<16));
    else
    {
        avago_sbus_wr(aapl, addr, 10, reg);
        avago_sbus_wr(aapl, addr,  6, 1);
    }
}

static int avago_apb_read16(Aapl_t *aapl, uint addr, int reg)
{
    int i;
    avago_apb_start_read(aapl, addr, reg);

    for(i = 0; i < 10; i++ )
    {
        int data = avago_sbus_rd(aapl, addr, 21);
        if( (data & 7) == 0 )
            return data >> 16;
        ms_sleep(1);
    }
    return -1;
}

#if 0
int avago_apb_read32(Aapl_t *aapl, uint addr, int reg)
{
    avago_apb_start_read(aapl, addr, reg);

    for(;;)
    {
        int busy = avago_sbus_rd(aapl, addr, 2);
        if( (busy & 7) == 0 )
            return avago_sbus_rd(aapl, addr, 20);
        printf("busy = 0x%x\n", busy);
    }
}

int avago_apb_write(Aapl_t *aapl, uint addr, int reg, int data)
{
    int busy;
    avago_sbus_wr(aapl, addr, 12, data);
    if( (addr & ~0xffff) == 0 )
    {
        avago_sbus_wr(aapl, addr, 11, reg | (1<<17));
        while( ((busy = avago_sbus_rd(aapl, addr, 21)) & 7) != 0 )
            printf("busy = 0x%x\n", busy);
    }
    else
    {
        avago_sbus_wr(aapl, addr, 10, reg);
        avago_sbus_wr(aapl, addr,  6, 2);
        while( ((busy = avago_sbus_rd(aapl, addr,  2)) & 7) != 0 )
            printf("busy = 0x%x\n", busy);
    }
    return 0;
}
#endif

/** @brief Prepare sensor for measurement */
static void initialize_sensor(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Sensor sbus address. */
    uint frequency) /**< [in] Sensor clock input frequency in Hertz. */
                    /**<      If non-zero, configures the sensor, */
                    /**<      which only need be done once. */
                    /**< For the 7nm sensor, if non-zero, this should be the sbus clock input frequency before being divided. */
{
    if( aapl_get_ip_type(aapl, addr) == AVAGO_SBUS2APB )
    {
        Avago_addr_t addr_struct;
        avago_addr_to_struct(addr, &addr_struct);
        if( frequency > 0 )
        {
            int sbus_divider = avago_sbm_get_sbus_clock_divider(aapl, addr);
            uint adc_divider = (frequency / sbus_divider + 500000) / 1000000;
            uint pclk_divider = adc_divider / 20;

            if( pclk_divider == 0 ) pclk_divider = 1;
            if( adc_divider == 0 ) adc_divider = 1;

            avago_sbus_wr(aapl, addr, 30, adc_divider);
            avago_sbus_wr(aapl, addr, 31, pclk_divider);
            avago_sbus_wr(aapl, addr, 32, 0);
        }

        if( aapl->jtag_idcode[addr_struct.chip] == 0x1a08457f )
        {
            avago_sbus_wr(aapl, addr, 0, 0x0f);
            avago_sbus_wr(aapl, addr, 0, 0x10);
        }
        else
        {
            avago_sbus_wr(aapl, addr, 0, 0x1f);
            avago_sbus_wr(aapl, addr, 0, 0x00);
        }

        return;
    }

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
 ** @details Note that in 16 and 28 nm, each device (sensor sbus address) can perform only
 **          one measurement (voltage or temperature) at a time.
 **
 **          In 7nm, sensor measurements need be started and initialized only once.
 **          Thereafter, current values can be read at will.
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

    if( aapl_get_ip_type(aapl, addr) == AVAGO_SBUS2APB )
        return;

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
    int return_code = aapl->return_code;
    int temp = -1000000;
    int data;
    if( aapl_get_ip_type(aapl, addr) == AVAGO_SBUS2APB )
    {
        int sensor_reg = sensor == 0 ? 7 : sensor + 8;
        data = avago_apb_read16(aapl, addr, sensor_reg);
        temp = ((-2388 * (0x7ff & data) + (3657800 + 1250)) / 2500) * 250;
    }
    else
    {
        int i;
        for( i = 0; i < 16; i++ )
        {
            if( i > 0 ) ms_sleep(5);
            data = avago_sbus_rd(aapl, addr, 65 + sensor);
            if( data & 0x8000 )
            {
                if( data & 0x800 )
                    temp = data | ~0x7ff;
                else
                    temp = data & 0x7ff;
                temp *= 125;
                break;
            }
        }
    }

    if( temp < -40000 || temp > 125000 || aapl->return_code != return_code  )
    {
        aapl_fail(aapl, __func__, __LINE__, "SBus 0x%02x, Temperature conversion failed, returning -1000000.\n",addr);
        temp = -1000000;
    }
    else
        AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Temp = %7d mC (data=0x%x)\n", temp, data);

    return temp;
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
    int temp;
    AAPL_SENSOR_LOCK;
    avago_sensor_start_temperature(aapl, addr, sensor, frequency);
    temp = avago_sensor_wait_temperature(aapl, addr, sensor);
    AAPL_SENSOR_UNLOCK;
    return temp;
}


/** @brief   Starts a voltage measurement.
 ** @details Use this function to start measurements on multiple devices.
 ** @details Note that in 16 and 28 nm, each device (sensor sbus address) can perform only
 **          one measurement (voltage or temperature) at a time.
 **
 **          In 7nm, sensor measurements need be started and initialized only once.
 **          Thereafter, current values can be read at will.
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
    initialize_sensor(aapl, addr, frequency);

    if( aapl_get_ip_type(aapl, addr) == AVAGO_SBUS2APB )
        return;

    if( sensor > 7 ) sensor = 0;
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
                    /**< The 7nm block has remote sensors [0..7] without special designations. */
{
    int return_code = aapl->return_code;
    int data;
    int mV = -1;
    if( aapl_get_ip_type(aapl, addr) == AVAGO_SBUS2APB )
    {
        int A = (sensor == 7) ? 2 : (sensor == 8) ? 4 : 1;
        int sensor_reg = sensor + 0x11;
        data = avago_apb_read16(aapl, addr, sensor_reg);
        mV = A * 1020 * (data & 0x7ff) / 2048;
    }
    else
    {
        int i;
        for( i = 0; i < 8; i++ )
        {
            if( i > 0 ) ms_sleep(4);
            data = avago_sbus_rd(aapl, addr, 74 + sensor);
            if( data & 0x8000 )
            {
                mV = (data & 0xfff) / 2;
                break;
            }
        }
    }

    if( mV == -1 || aapl->return_code != return_code )
        return aapl_fail(aapl, __func__, __LINE__, "Voltage conversion failed, returning -1.\n");

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Voltage = %4d mV (data=0x%x)\n",mV,data);
    return mV;
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
    int volt;
    AAPL_SENSOR_LOCK;
    avago_sensor_start_voltage(aapl, addr, sensor, frequency);
    volt = avago_sensor_wait_voltage(aapl, addr, sensor);
    AAPL_SENSOR_UNLOCK;
    return volt;
}


/** @} */

