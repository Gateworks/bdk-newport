/* AAPL CORE Revision: 2.3.0-alpha */

/* Copyright 2014-2015 Avago Technologies. All rights reserved.
 *
 * This file is part of the AAPL CORE library.
 *
 * AAPL CORE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AAPL CORE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with AAPL CORE.  If not, see http://www.gnu.org/licenses.
 */

/** Doxygen File Header
*  @file
*  @brief Declarations for measurement functions.
 **/

#ifndef AVAGO_SERDES_MEAS_H_
#define AVAGO_SERDES_MEAS_H_


EXT BOOL avago_serdes_dfe_running(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_dfe_pause( Aapl_t *aapl, uint sbus_addr, uint *rr_enabled);
EXT int  avago_serdes_dfe_wait(  Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_dfe_resume(Aapl_t *aapl, uint sbus_addr, uint rr_enable);

EXT int  avago_serdes_get_dac_range(Aapl_t *aapl, uint sbus_addr);
EXT uint avago_serdes_get_phase_multiplier(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_power_down_phase_interpolator(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_set_error_timer(Aapl_t *aapl, uint sbus_addr, bigint dwell_bits);

#endif
