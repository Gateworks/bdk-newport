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

/** Doxygen File Header
 ** @file
 ** @brief Declarations for measurement functions.
 **/

#ifndef AVAGO_SERDES_MEAS_H_
#define AVAGO_SERDES_MEAS_H_


EXT BOOL avago_serdes_dfe_los(Aapl_t *aapl, uint sbus_addr);
EXT BOOL avago_serdes_dfe_running(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_dfe_pause( Aapl_t *aapl, uint sbus_addr, uint *rr_enabled);
EXT int  avago_serdes_dfe_wait(  Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_dfe_wait_timeout(  Aapl_t *aapl, uint sbus_addr, int timeout);
EXT int  avago_serdes_dfe_resume(Aapl_t *aapl, uint sbus_addr, uint rr_enable);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
EXT int  avago_serdes_get_dac_range(Aapl_t *aapl, uint sbus_addr);
EXT uint avago_serdes_get_phase_multiplier(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_power_down_phase_interpolator(Aapl_t *aapl, uint sbus_addr);
#endif

#endif
