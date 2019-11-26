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
 ** @brief SBus Master / Controller functions.
 **/

#include "aapl.h"

/** @brief   Gets the SBus clock divider value.
 ** @details The SBus clock frequency is set to the ref clock frequency
 **          divided by the sbus clock divider.
 **          Normally, a power of two is used, but this is not required.
 ** @return  On success, returns the SBus clock divider value.
 **          On error, decrements aapl->return_code and returns -1.
 **/
int avago_sbm_get_sbus_clock_divider(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address, only chip & ring parts used. */
{
    int return_code = aapl->return_code;
    int divider = (int)avago_sbus_rd(aapl, addr = avago_make_sbus_controller_addr(addr), 0x0a);

    if( divider & (1 << 7) )
    {
        divider = avago_sbus_rd(aapl, addr, 0x0b);
        divider++;
    }
    else
    {
        divider = (divider >= 12) ? 4096 : (1 << divider);
    }
    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, divider %u\n",aapl_addr_to_str(addr),divider);
    return return_code == aapl->return_code ? divider : -1;
}

/** @brief   Sets the SBus clock divider.
 ** @details The SBus clock frequency is the ref clock frequency
 **          divided by the sbus clock divider.
 **          Normally, a power of two is used, but this is not required.
 **          Valid divider range is [1..4096].
 ** @return  On success, returns 0.
 **          On error, decrements aapl->return_code and returns -1.
 **/
int avago_sbm_set_sbus_clock_divider(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address, only chip & ring parts used. */
    uint divider)       /**< [in] New sbus divider value in range [1-4096]. */
{
    int return_code = aapl->return_code;
    uint exponent;
    addr = avago_make_sbus_controller_addr(addr);

    if( divider == 0 || divider > 4096 )
        return aapl_fail(aapl,__func__,__LINE__,"SBus %s, divider %u is out of valid range [1-4096].\n",aapl_addr_to_str(addr),divider);

    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, divider %u\n",aapl_addr_to_str(addr),divider);

    for( exponent = 1; (divider >> exponent) != 0; exponent++ )
        continue;
    if( (divider & (divider - 1)) == 0 )
    {
        exponent--;
        avago_sbus_wr(aapl, addr, 0x0a, exponent);
    }
    else
    {
        avago_sbus_wr(aapl, addr, 0x0a, exponent);
        avago_sbus_wr(aapl, addr, 0x0b, divider - 1);
        avago_sbus_wr(aapl, addr, 0x0a, exponent | 0x0080);
    }
    return return_code == aapl->return_code ? 0 : -1;
}

