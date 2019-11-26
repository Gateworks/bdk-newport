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

/* AAPL (ASIC and ASSP Programming Layer) sensor functions */

/** Doxygen File Header
 ** @file
 ** @brief Function definitions for temperature and voltage sensor.
 **/

#ifndef AAPL_SENSOR_H_
#define AAPL_SENSOR_H_

/* Sensor functions: */
EXT void avago_sensor_start_temperature(Aapl_t *aapl, uint addr, int sensor, uint frequency);
EXT int  avago_sensor_wait_temperature(Aapl_t *aapl, uint addr, int sensor);
EXT int  avago_sensor_get_temperature(Aapl_t *aapl, uint addr, int sensor, uint frequency);
EXT void avago_sensor_start_voltage(Aapl_t *aapl, uint addr, int sensor, uint frequency);
EXT int  avago_sensor_wait_voltage(Aapl_t *aapl, uint addr, int sensor);
EXT int  avago_sensor_get_voltage(Aapl_t *aapl, uint addr, int sensor, uint frequency);

#endif
