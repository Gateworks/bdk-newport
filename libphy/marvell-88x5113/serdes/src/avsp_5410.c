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
 ** @brief Functions specific to the AVSP-5410
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_AVSP_5410

/** @brief   Configure internal logic for the given mode.
 ** @return  On success, returns 0.
 ** @return  On failure, decrements aapl->return_code and returns -1.
 **/
int avsp_5410_set_mode(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint prtad,         /**< [in] Port address of the target device. */
    Avsp_mode_t mode)   /**< [in] New mode to set */
{
    uint addr = 0;
    switch( mode )
    {
    case AVSP_REPEATER_DUPLEX: {

        break;
    }
    case AVSP_GEARBOX_4_1: {
        addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr, 0xf9, 0x00);
          avago_sbus_wr(aapl, addr, 0x99, 0x0A05);


          addr = avago_make_addr3(prtad, 0, 0x0b);
          avago_sbus_wr(aapl, addr, 0x04, 0x0f);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr, 151, 0x03);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr, 0x00, 0x07);
          avago_sbus_wr(aapl, addr, 0x20, 0x07);
          avago_sbus_wr(aapl, addr, 0x40, 0x07);
          avago_sbus_wr(aapl, addr, 0x60, 0x07);



          addr = avago_make_addr3(prtad, 0, 0x0b);
          avago_sbus_wr(aapl, addr, 0x05, 0x28);
          addr = avago_make_addr3(prtad, 0, 0x0c);
          avago_sbus_wr(aapl, addr, 0x05, 0x28);

          addr = avago_make_addr3(prtad, 0, 0x0b);
          avago_sbus_wr(aapl, addr, 0x04, 0x0e);
          avago_sbus_wr(aapl, addr, 0x04, 0x0c);
          avago_sbus_wr(aapl, addr,10,0x8002);
          avago_sbus_wr(aapl, addr,12,1279);
          avago_sbus_wr(aapl, addr,6,0x02);
          avago_sbus_wr(aapl, addr,6,0x00);

          avago_sbus_wr(aapl, addr,10,0x7);
          avago_sbus_wr(aapl, addr,12,0x100);
          avago_sbus_wr(aapl, addr,6,0x10);
          avago_sbus_wr(aapl, addr,6,0x00);

          avago_sbus_wr(aapl, addr,4,0x00);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr,0x00,0x05);
          avago_sbus_wr(aapl, addr,0x20,0x05);
          avago_sbus_wr(aapl, addr,0x40,0x05);
          avago_sbus_wr(aapl, addr,0x60,0x05);



          avago_sbus_wr(aapl, addr,151,0x02);

          addr = avago_make_addr3(prtad, 0, 0xb);
          avago_sbus_wr(aapl, addr,0x04,0x00);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr,0x00,0x01);
          avago_sbus_wr(aapl, addr,0x20,0x01);
          avago_sbus_wr(aapl, addr,0x40,0x01);
          avago_sbus_wr(aapl, addr,0x60,0x01);



    }
    case AVSP_RS_FEC: {
          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr,0xf9,0x0f);

          avago_sbus_wr(aapl, addr,0xf9,0x00);
          avago_sbus_wr(aapl, addr,0x99,0x0A05);


          addr = avago_make_addr3(prtad, 0, 0x0b);
          avago_sbus_wr(aapl, addr,0x04,0x0f);
          addr = avago_make_addr3(prtad, 0, 0x0c);
          avago_sbus_wr(aapl, addr,0x04,0x0f);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl, addr,151,0x03);

          avago_sbus_wr(aapl, addr,0x00,0x07);
          avago_sbus_wr(aapl, addr,0x20,0x07);
          avago_sbus_wr(aapl, addr,0x40,0x07);
          avago_sbus_wr(aapl, addr,0x60,0x07);


          addr = avago_make_addr3(prtad, 0, 0x0b);
          avago_sbus_wr(aapl, addr,0x04,0x0e);
          avago_sbus_wr(aapl, addr,0x04,0x0c);

          avago_sbus_wr(aapl, addr,10,0x8002);
          avago_sbus_wr(aapl, addr,12,1279);
          avago_sbus_wr(aapl, addr,6,0x02);
          avago_sbus_wr(aapl, addr,6,0x00);

          avago_sbus_wr(aapl, addr,10,0x7);
          avago_sbus_wr(aapl, addr,12,0x100);
          avago_sbus_wr(aapl, addr,6,0x10);
          avago_sbus_wr(aapl, addr,6,0x00);
          avago_sbus_wr(aapl, addr,4,0x00);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl,addr,0x00,0x05);
          avago_sbus_wr(aapl,addr,0x20,0x05);
          avago_sbus_wr(aapl,addr,0x40,0x05);
          avago_sbus_wr(aapl,addr,0x60,0x05);



          avago_sbus_wr(aapl,addr,151,0x02);

          addr = avago_make_addr3(prtad, 0, 0xb);
          avago_sbus_wr(aapl,addr,0x04,0x00);

          addr = avago_make_addr3(prtad, 0, 0xec);
          avago_sbus_wr(aapl,addr,0x00,0x01);
          avago_sbus_wr(aapl,addr,0x20,0x01);
          avago_sbus_wr(aapl,addr,0x40,0x01);
          avago_sbus_wr(aapl,addr,0x60,0x01);
    }
    default:
    break;
    }
    return 0;
}

/** @brief  Retrieves the mode into which the core logic is configured.
 ** @return Returns the core logic configuration mode.
 **/
Avsp_mode_t avsp_5410_get_mode(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint prtad)     /**< [in] Port address of the target device. */
{
    uint addr = avago_make_addr3(prtad, 0, 0xfd);
    int val = avago_spico_int(aapl,addr,0x26,0x3800) & 0x0f;
    Avsp_mode_t mode = val == 0x001 ? AVSP_REPEATER_DUPLEX :
                       val == 0x002 ? AVSP_GEARBOX_4_1 :
                       val == 0x003 ? AVSP_RS_FEC : AVSP_ADHOC;
    return mode;
}


/** @brief   Directly resets the core logic.
 ** @return  On success, returns 0.
 ** @return  On failure, decrements aapl->return_code and returns -1.
 **/
BOOL avsp_5410_control_logic_reset_direct(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint prtad,        /**< [in] Port address of the targeted device. */
    const char * direction) /**< [in] direction from host to mod or mod to host */
{
    uint addr;
    addr = avago_make_addr3(prtad, 0, 0xa);

    if( strcmp( direction, "host_to_mod") == 0 || strcmp( direction, "both") == 0){
        aapl_log_printf(aapl,AVAGO_INFO,0,0,"Resetting control logic from host to mod direction \n");
        avago_sbus_wr(aapl, addr, 0, 0x0002);
        avago_sbus_wr(aapl, addr, 20, 0x0002);

        avago_sbus_wr(aapl, addr, 0, 0);
        avago_sbus_wr(aapl, addr, 20, 0);
    }
    if( strcmp( direction, "mod_to_host") == 0 || strcmp( direction, "both") == 0){
        aapl_log_printf(aapl,AVAGO_INFO,0,0,"Resetting control logic from mod to host direction \n");
        avago_sbus_wr(aapl, addr, 0, 0x0001);
        avago_sbus_wr(aapl, addr, 20, 0x0001);

        avago_sbus_wr(aapl, addr, 0, 0);
        avago_sbus_wr(aapl, addr, 20, 0);

        avago_sbus_wr(aapl, addr, 151, 0x0003);
        avago_sbus_wr(aapl, addr, 151, 0x0002);
    }
    return 0;
}
#endif
