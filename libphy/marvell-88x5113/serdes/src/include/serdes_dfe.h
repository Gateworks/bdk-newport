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

/* AAPL (ASIC and ASSP Programming Layer) generic handling of SerDes
 * (Serializer/Deserializer) slices on ASIC SBus rings.
 */

/** Doxygen File Header
 ** @file
 ** @brief Declarations and types for SerDes DFE functions.
 **/

#ifndef AVAGO_SERDES_DFE_H_
#define AVAGO_SERDES_DFE_H_

/**@brief Rx DFE Settings and Control functions for DFE tuning. */
typedef struct
{
    uint dc;         /**< DC-Restore value [0-255] */
    uint lf;         /**< CTLE Low-Frequency setting [0-15] */
    uint hf;         /**< CTLE High-Frequency setting [0-15] */
    uint bw;         /**< CTLE Band-width setting [0-15] */

    uint dfeGAIN;    /**< DFE Gain Tap strength setting [0-15] */
    uint dfeGAIN2;   /**< DFE Gain Tap 2 strength setting [0-15] */


} Avago_serdes_dfe_state_t;

EXT void  avago_serdes_get_dfe_state(   Aapl_t *aapl, uint sbus_addr, Avago_serdes_dfe_state_t *dfe_state);
EXT void  avago_serdes_print_dfe(       Aapl_t *aapl, uint sbus_addr, Avago_serdes_dfe_state_t *dfe_state, BOOL single_line);
EXT char *avago_serdes_dfe_state_to_str(Aapl_t *aapl, uint sbus_addr, Avago_serdes_dfe_state_t *dfe_state, BOOL single_line, BOOL header);
EXT int avago_serdes_get_dfe_status(Aapl_t* aapl, uint sbus_addr);
#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
EXT int avago_serdes_interpret_dfe_status(Aapl_t *aapl, uint sbus_addr);
#endif




#endif




