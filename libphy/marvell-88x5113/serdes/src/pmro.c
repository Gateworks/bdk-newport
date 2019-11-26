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

/** Doxygen File Header
 ** @file
 ** @brief PMRO device specific functions.
 **/

#include "aapl.h"

/** @brief   Measures process performance of the chip.
 ** @details The returned value is dependent on the reference clock frequency.
 **          As a result, values obtained with different reference clock
 **          frequencies cannot be meaningfully compared.
 ** @return  Returns a number indicating propagation delay through
 **          a set of gates and interconnects.
 **          A higher number indicates faster process performance.
 **/
uint avago_pmro_get_metric(
    Aapl_t *aapl,        /**< [in] Pointer to AAPL structure */
    uint addr)           /**< [in] SBus address of SerDes */
{
    if( !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 1, AVAGO_PMRO) )
        return 0;

    avago_sbus_reset(aapl, addr, 0);
    avago_sbus_wr(aapl, addr, 0, 1);
    return avago_sbus_rd(aapl, addr, 6);
}

