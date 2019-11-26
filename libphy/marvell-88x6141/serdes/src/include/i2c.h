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

/* i2c.h - Defines i2c related functions and constants */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for i2c bus functions.
 **/

#ifndef AVAGO_I2C_H_
#define AVAGO_I2C_H_

#if AAPL_ALLOW_I2C || AAPL_ALLOW_SYSTEM_I2C

EXT int avago_i2c_write(Aapl_t *aapl, uint dev_addr, uint length, unsigned char *buffer);
EXT int avago_i2c_read(Aapl_t *aapl, uint dev_addr, uint length, unsigned char *buffer);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

EXT uint avago_i2c_sbus_fn(Aapl_t *aapl, uint sbus_addr, unsigned char reg_addr, unsigned char command, uint *sbus_data);

#if AAPL_ALLOW_AACS
EXT int avago_aacs_i2c_write_fn(Aapl_t *aapl, uint dev_addr, uint length, unsigned char *buffer);
EXT int avago_aacs_i2c_read_fn(Aapl_t *aapl, uint dev_addr, uint length, unsigned char *buffer);
#endif

#if AAPL_ALLOW_SYSTEM_I2C
EXT int avago_system_i2c_open_fn(Aapl_t *aapl);
EXT int avago_system_i2c_close_fn(Aapl_t *aapl);
EXT int avago_system_i2c_write_fn(Aapl_t *aapl, uint dev_addr, uint length, unsigned char *buffer);
EXT int avago_system_i2c_read_fn(Aapl_t *aapl, uint dev_addr, uint length, unsigned char *buffer);
#endif

#endif

#endif

#endif
