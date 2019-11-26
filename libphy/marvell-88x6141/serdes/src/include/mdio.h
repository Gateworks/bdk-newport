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

/* AAPL (ASIC and ASSP Programming Layer) MDIO-related functions defined in
 * mdio.cpp.
 */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for MDIO bus functions.
 **/

#ifndef AVAGO_MDIO_H_
#define AVAGO_MDIO_H_

#if AAPL_ALLOW_MDIO || AAPL_ALLOW_GPIO_MDIO

#define AVSP_DEVAD 8

#define AVAGO_MDIO_REG_STATUS      32777
#define AVAGO_MDIO_REG_STAT_MISC1  32787
#define AVAGO_MDIO_REG_RESET       32784
#define AVAGO_MDIO_REG_CONTROL     0
#define AVAGO_MDIO_REG_CONTROL2    7

EXT uint avago_mdio(     Aapl_t *aapl, Avago_mdio_cmd_t mdio_cmd, uint port_addr, uint dev_addr, uint data);
EXT uint avago_mdio_rd(  Aapl_t *aapl, uint port_addr, uint dev_addr, uint reg_addr);
EXT uint avago_mdio_wr(  Aapl_t *aapl, uint port_addr, uint dev_addr, uint reg_addr, uint data);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

#if AAPL_ALLOW_AACS
EXT uint avago_aacs_mdio_fn(Aapl_t *aapl, Avago_mdio_cmd_t mdio_cmd, uint port_addr, uint dev_addr, uint reg_addr, uint data);
#endif
EXT uint avago_mdio_sbus_fn(Aapl_t *aapl, uint sbus_addr, unsigned char reg_addr, unsigned char command, uint *sbus_data);

#endif

#endif

#endif



