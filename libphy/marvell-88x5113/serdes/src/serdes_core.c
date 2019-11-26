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
 ** @file serdes_core.c
 ** @brief Functions for SerDes devices.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#define AAPL_LOG_PRINT5 if(aapl->debug >= 5) aapl_log_printf
#define AAPL_LOG_PRINT6 if(aapl->debug >= 6) aapl_log_printf



/** @defgroup SerDes Generic SerDes API
 ** @{
 **/

/** @brief   Gets the SerDes LSB revision.
 ** @details Reads the revision of SerDes LSB using an AVAGO_LSB_DIRECT read.
 ** @return  Revision of the LSB (> 0), or -1 on error.
 ** @see avago_firmware_get_rev(), avago_firmware_get_build_id().
 **/
int avago_serdes_get_lsb_rev(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int rc = -1;

    if( aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1))
    {
        if (aapl_check_process(aapl, addr, __func__, __LINE__, FALSE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F))
        {
            rc = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB_DIRECT, 0x026);
            rc = (rc >> 12) & 0xf;
        }
        else if (aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 1, AVAGO_PROCESS_A))
        {
            rc = (avago_sbus_rd(aapl, addr, 0x64) >> 28) & 0xf;
        }
    }

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, ret = %d.\n", aapl_addr_to_str(addr), rc);
    return rc;
}

static int get_mem_slice_sel(Aapl_t *aapl, uint addr)
{
    int slice = (addr >> 16) & 0xf;
    if( (slice < 8 && slice != 2) || aapl_get_ip_type(aapl,addr) != AVAGO_P1 )
        return 0;
    if( slice == 2 ) slice = 4;
    return slice & 7;
}

/** @brief   Reads a memory location from a SerDes device.
 **
 ** @return  Value read.  On error, aapl->return_code is set to negative value.
 ** @see     avago_serdes_mem_wr(), avago_serdes_mem_rmw().
 **/
int avago_serdes_mem_rd(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_mem_type_t type,   /**< [in] The memory access type. */
    uint mem_addr)                  /**< [in] Memory address to access */
{
    int ret = 0;
    int sdrev = aapl_get_sdrev(aapl,addr);

    switch( sdrev )
    {
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
        break;
    case AAPL_SDREV_D6_10:
        if( type == AVAGO_DMEM ) type = AVAGO_LSB;
        break;
    default:
        switch( type )
        {
        case AVAGO_DMEM:
        case AVAGO_ESB:        type = AVAGO_LSB;        break;
        case AVAGO_ESB_DIRECT: type = AVAGO_LSB_DIRECT; break;
        default:;
        }
    }

    switch( type )
    {
    case AVAGO_LSB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            ret = avago_spico_int(aapl, addr, (1 << 14) | (mem_addr & 0x07ff), 0x00);
            break;
        }
        /* Fall through */

    case AVAGO_LSB_DIRECT:
        if( sdrev == AAPL_SDREV_P1 )
        {
            int spico_run_state = avago_spico_halt(aapl, addr);

            int sel = get_mem_slice_sel(aapl,addr);
            if( mem_addr >= 128 && mem_addr < 384 )
                avago_sbus_wr(aapl, addr, 0x2d, sel);
            else if( mem_addr >= 384 && mem_addr < 448 )
                mem_addr += sel * 64 + 1024 - 384;

            avago_sbus_wr(aapl, addr, 0x01, (1<<30) | (mem_addr & 0x0fff));
            ret = (avago_sbus_rd(aapl, addr, 0x01) >> 12) & 0xFFFF;

            avago_spico_resume(aapl, addr, spico_run_state);
        }
        else if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_HVD6 )
        {
            avago_sbus_wr(aapl, addr, 0x01, (1<<30) | (mem_addr & 0x03ff));
            ret = (avago_sbus_rd(aapl, addr, 0x01) >> 12) & 0xFFFF;
        }
        else
        {
            avago_sbus_wr(aapl, addr, 0x02, ((mem_addr & 0x1ff) << 16));
            ret = avago_sbus_rd(aapl, addr, 0x40) & 0xFFFF;
        }
        break;

    case AVAGO_ESB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            if( sdrev == AAPL_SDREV_D6_10 )
            {
                uint int_data = ((mem_addr & 0x380) << 4) | (mem_addr & 0x7f) | 0x80;
                ret = avago_spico_int(aapl, addr, (1 << 14) | int_data, 0x00);
            }
            else
            {
                avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, 0x4000 | (mem_addr & 0x3fff));
                ret = avago_spico_int(aapl, addr, 0x1a, 0x00);
            }
            break;
        }
        /* Fall through */

    case AVAGO_ESB_DIRECT:
    {
        int lsb_esb_addr;
        int spico_run_state = avago_spico_halt(aapl, addr);

        int reset_status = avago_sbus_rd(aapl, addr, 0x07);
        if( reset_status & 0x01 )
            avago_sbus_wr(aapl, addr, 0x07, reset_status & ~1);

        lsb_esb_addr = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB_DIRECT, 0x030);

        if( lsb_esb_addr & 0x8000 )
            avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, lsb_esb_addr & 0x7fff);

        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, mem_addr);
        ret = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB_DIRECT, 0x032);

        if( lsb_esb_addr & 0x8000 )
            avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, lsb_esb_addr & 0x7fff);
        avago_serdes_mem_wr(    aapl, addr, AVAGO_LSB_DIRECT, 0x030, lsb_esb_addr);

        if( reset_status & 0x01 )
            avago_sbus_wr(aapl, addr, 0x07, reset_status);
        avago_spico_resume(aapl, addr, spico_run_state);
        break;
    }

    case AVAGO_DMEM:
    case AVAGO_DMEM_PREHALTED:
    {
        if( sdrev == AAPL_SDREV_HVD6 )
        {
            avago_sbus_wr(aapl, addr, 0x01, (1<<29) | (1<<30) | (mem_addr & 0x03ff));
            ret = (avago_sbus_rd(aapl, addr, 0x01) >> 12) & 0xFFFF;
            break;
        }
        else
        {
            int spico_run_state = 0, initial_value_0x01;
            if (type == AVAGO_DMEM)  spico_run_state = avago_spico_halt(aapl, addr);
            initial_value_0x01 =    avago_sbus_rmw(aapl, addr, 0x01, 0x40000000 | (mem_addr & 0xfff), 0x40000fff);
            ret =                  (avago_sbus_rd(aapl, addr, 0x01) >> 12) & 0xffff;
                                    avago_sbus_wr(aapl, addr, 0x01, initial_value_0x01);
            if (type == AVAGO_DMEM) avago_spico_resume(aapl, addr, spico_run_state);
            break;
        }
    }

    case AVAGO_IMEM:
    case AVAGO_IMEM_PREHALTED:
    {
        int spico_run_state = 0;
        if (type == AVAGO_IMEM) spico_run_state = avago_spico_halt(aapl, addr);
        avago_sbus_wr(aapl, addr, 0x00, (mem_addr & 0xffff) | 1 << 30);
        ret = (avago_sbus_rd(aapl, addr, 0x00) >> 16 ) & 0x3ff;
        avago_sbus_wr(aapl, addr, 0x00, 0x00);
        if (type == AVAGO_IMEM) avago_spico_resume(aapl, addr, spico_run_state);
        break;
    }

    default:
        aapl_fail(aapl, __func__, __LINE__, "SBus %s, Invalid DMA type (%d).\n", aapl_addr_to_str(addr), type);
        return 0;
    }
    AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"SBus %s, Read  %s 0x%04x -> 0x%x\n",
        aapl_addr_to_str(addr), aapl_mem_type_to_str(type), mem_addr, ret);
    return ret;
}

/** @brief   Writes data to a memory location.
 **
 ** @return  On error, decrements aapl->return_code.
 ** @see     avago_serdes_mem_rd(), avago_serdes_mem_rmw().
 **/
void avago_serdes_mem_wr(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_mem_type_t type,   /**< [in] The memory access type. */
    uint mem_addr,                  /**< [in] Memory address to access */
    uint data)                      /**< [in] Data to write into memory location addr. */
{
    int sdrev = aapl_get_sdrev(aapl,addr);
    AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"SBus %s, Write %s 0x%04x <- 0x%x\n",
        aapl_addr_to_str(addr), aapl_mem_type_to_str(type), mem_addr, data);

    switch( sdrev )
    {
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
        break;
    case AAPL_SDREV_D6_10:
        if( type == AVAGO_DMEM ) type = AVAGO_LSB;
        break;
    default:
        switch( type )
        {
        case AVAGO_DMEM:
        case AVAGO_ESB:        type = AVAGO_LSB;        break;
        case AVAGO_ESB_DIRECT: type = AVAGO_LSB_DIRECT; break;
        default:;
        }
    }

    switch( type )
    {
    case AVAGO_LSB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            avago_spico_int(aapl, addr, (2 << 14) | (mem_addr & 0x07ff), data);
            return;
        }
        /* Fall through */

    case AVAGO_LSB_DIRECT:
        if( sdrev == AAPL_SDREV_P1 )
        {
            int spico_run_state = avago_spico_halt(aapl, addr);
            int sel = get_mem_slice_sel(aapl,addr);
            int reset_status = avago_sbus_rd(aapl, addr, 0x07);
            if( (reset_status & 0x01) || !(reset_status & 0x10) )
                avago_sbus_wr(aapl, addr, 0x07, (reset_status & ~1) | 0x10);

            if( mem_addr >= 128 && mem_addr < 384 )
                avago_sbus_wr(aapl, addr, 0x2d, sel);
            else if( mem_addr >= 384 && mem_addr < 448 )
                mem_addr += sel * 64 + 1024 - 384;
            avago_sbus_wr(aapl, addr, 0x01, (1<<31) | ((data & 0xffff) << 12) | (mem_addr & 0x0fff));

            if( (reset_status & 0x01) || !(reset_status & 0x10) )
                avago_sbus_wr(aapl, addr, 0x07, reset_status);
            avago_spico_resume(aapl, addr, spico_run_state);
        }
        else if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_HVD6 )
            avago_sbus_wr(aapl, addr, 0x01, (1<<31) | ((data & 0xffff) << 12) | (mem_addr & 0x03ff));
        else
        {
            if(aapl_get_lsb_rev(aapl,addr) >= 3)
            {
                avago_sbus_wr(aapl, addr, 0x02, (0<<31) | ((mem_addr & 0x1ff) << 16) | (data & 0xffff));
            }
            avago_sbus_wr(    aapl, addr, 0x02, (1<<31) | ((mem_addr & 0x1ff) << 16) | (data & 0xffff));
        }
        return;

    case AVAGO_ESB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            if( sdrev == AAPL_SDREV_D6_10 )
            {
                uint int_data = ((mem_addr & 0x380) << 4) | (mem_addr & 0x7f) | 0x80;
                avago_spico_int(aapl, addr, (2 << 14) | int_data, data);
            }
            else
            {
                avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, 0x4000 | (mem_addr & 0x3fff));
                avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x19, data);
            }
            return;
        }
        /* Fall through */

    case AVAGO_ESB_DIRECT:
    {
        int lsb_esb_addr, lsb_esb_write_data;
        int spico_run_state = avago_spico_halt(aapl, addr);

        int reset_status = avago_sbus_rd(aapl, addr, 0x07);
        if( reset_status & 0x01 )
            avago_sbus_wr(aapl, addr, 0x07, reset_status & ~1);

        lsb_esb_write_data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB_DIRECT, 0x031);
        lsb_esb_addr = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB_DIRECT, 0x030);

        if( lsb_esb_addr & 0x8000 )
            avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, lsb_esb_addr & 0x7fff);

        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x031, data);
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, mem_addr);
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, mem_addr | 0x8000);
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, mem_addr);

        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x031, lsb_esb_write_data);
        if( lsb_esb_addr & 0x8000 )
            avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x030, lsb_esb_addr & 0x7fff);
        avago_serdes_mem_wr(    aapl, addr, AVAGO_LSB_DIRECT, 0x030, lsb_esb_addr);

        if( reset_status & 0x01 )
            avago_sbus_wr(aapl, addr, 0x07, reset_status);
        avago_spico_resume(aapl, addr, spico_run_state);
        return;
    }

    case AVAGO_DMEM:
    {
        if( sdrev == AAPL_SDREV_HVD6 )
        {
            avago_sbus_wr(aapl, addr, 0x01, (1<<29) | (1<<31) | ((data & 0xffff) << 12) | (mem_addr & 0x03ff));
            return;
        }
        else
        {
            int spico_run_state = avago_spico_halt(aapl, addr);
            int initial_value_0x01 = avago_sbus_rd(aapl, addr,  0x01);
                                     avago_sbus_wr(aapl, addr,  0x01, 0x40000000 | (mem_addr & 0xfff) | ((data & 0xffff) << 12));
                                     avago_sbus_wr(aapl, addr,  0x01, 0xc0000000 | (mem_addr & 0xfff) | ((data & 0xffff) << 12));
                                     avago_sbus_wr(aapl, addr,  0x01, initial_value_0x01);
            avago_spico_resume(aapl, addr, spico_run_state);
            return;
        }
    }

    case AVAGO_IMEM:
    {
        int spico_run_state = avago_spico_halt(aapl, addr);
        int initial_value_0x00 = avago_sbus_rd(aapl, addr,  0x00);
                                 avago_sbus_wr(aapl, addr,  0x00, 0x40000000 | (mem_addr & 0xffff) | ((data & 0x03ff) << 16));
                                 avago_sbus_wr(aapl, addr,  0x00, 0xc0000000 | (mem_addr & 0xffff) | ((data & 0x03ff) << 16));
                                 avago_sbus_wr(aapl, addr,  0x00, initial_value_0x00);
        avago_spico_resume(aapl, addr, spico_run_state);
        return;
    }

    default: ;
    }

    aapl_fail(aapl, __func__, __LINE__, "SBus %s, Invalid DMA type (%d).\n", aapl_addr_to_str(addr), type);
}

/** @brief   Performs a read-modify-write operation on SerDes memory location.
 **
 ** @return  Returns the value of the memory location before it was modified.
 ** @return  On error, decrements aapl->return_code.
 ** @see     avago_serdes_mem_rd(), avago_serdes_mem_wr().
 **/
int avago_serdes_mem_rmw(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_mem_type_t type,   /**< [in] The memory access type. */
    uint mem_addr,                  /**< [in] Memory address to access. */
    uint data,                      /**< [in] Data to write. */
    uint mask)                      /**< [in] Bits in existing data to modify. */
{
    int initial_value;
    int spico_run_state = avago_spico_halt(aapl, addr);

    if(      type == AVAGO_LSB ) type = AVAGO_LSB_DIRECT;
    else if( type == AVAGO_ESB ) type = AVAGO_ESB_DIRECT;

    initial_value = avago_serdes_mem_rd(aapl, addr, type, mem_addr);
    avago_serdes_mem_wr(aapl, addr, type, mem_addr, (data & mask) | (initial_value & ~mask));

    avago_spico_resume(aapl, addr, spico_run_state);
    return initial_value;
}



static int serdes_get_int01_bits(Aapl_t *aapl, uint addr, uint mask)
{
    int bits = 0;
    int reg_serdes_rdy, reg_accel_misc_ctl, bit;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_16:   reg_serdes_rdy = 0x26; reg_accel_misc_ctl =  0xdf; bit = 0; break;
    case AAPL_SDREV_D6_10:reg_serdes_rdy = 0x26; reg_accel_misc_ctl =  0x3e; bit = 0; break;
    case AAPL_SDREV_HVD6: reg_serdes_rdy = 0x26; reg_accel_misc_ctl =  0xde; bit = 0; break;
    case AAPL_SDREV_D6:   reg_serdes_rdy = 0x26; reg_accel_misc_ctl = 0x213; bit = 1; break;
    case AAPL_SDREV_P1:   reg_serdes_rdy = 0xee; reg_accel_misc_ctl = 0x15e; bit = 0;
                          if( aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B )
                              reg_accel_misc_ctl = 0x162;
                          break;
    }
    if( mask & 0x03 )
    {
        bits  |= 0x03 & avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_serdes_rdy);
    }
    if( mask & 0x04 )
    {
        int reg = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg_accel_misc_ctl) >> bit;
        bits |= (0x01 & reg) << 2;
    }
    if( mask & 0x08 )
        bits |= 0;
    if( mask & 0x10 )
        bits |= 0;
    if( mask & 0x20 )
        bits |= 0;
    if( mask & 0x40 )
        bits |= 0;
    if( mask & 0x80 )
        bits |= 0;
    return bits;
}

/** @brief   Gets the TX & RX ready states.
 ** @details Returns if the TX and RX devices are initialized and ready
 **          for operation.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_output_enable(), avago_serdes_set_tx_output_enable(), avago_serdes_set_tx_rx_enable().
 **/
int avago_serdes_get_tx_rx_ready(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    BOOL *tx,           /**< [out] Where to store TX state. */
    BOOL *rx)           /**< [out] Where to store RX state. */
{
    int return_code = aapl->return_code;
    int bits = serdes_get_int01_bits(aapl, addr, 0x03);
    *tx = (bits & 0x01) == 0x01;
    *rx = (bits & 0x02) == 0x02;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, TX %s, RX %s\n",
                aapl_addr_to_str(addr),aapl_enable_to_str(*tx),aapl_enable_to_str(*rx));
    return return_code == aapl->return_code ? 0 : -1;
}
/** @brief   Sets TX & RX enable states, and TX output values.
 ** @details If enabling TX or RX, waits for the device to become ready.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @return  On timeout, returns -1 and does not decrement aapl->return_code.
 ** @see     avago_serdes_get_tx_output_enable(), avago_serdes_get_tx_rx_ready(), avago_serdes_set_tx_output_enable().
 **/
int avago_serdes_set_tx_rx_enable(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    BOOL tx,            /**< [in] New TX state. */
    BOOL rx,            /**< [in] New RX state. */
    BOOL tx_output)     /**< [in] New TX output state. */
{
    Avago_addr_t addr_struct;
    int return_code = aapl->return_code;
    int loops = 0;
    int mask;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_en=%s, rx_en=%s,tx_output_en=%s\n",
                aapl_addr_to_str(addr),aapl_bool_to_str(tx),aapl_bool_to_str(rx),aapl_bool_to_str(tx_output));

    mask = serdes_get_int01_bits(aapl, addr, ~0x07);
    if( tx        ) mask |= 0x01;
    if( rx        ) mask |= 0x02;
    if( tx_output ) mask |= 0x04;

    if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x01, mask)) return -1;

    mask &= 0x03;
    avago_addr_to_struct(addr,&addr_struct);
    for( loops = 0; loops <= AAPL_SERDES_INIT_RDY_TIMEOUT; loops++ )
    {
        Avago_addr_t start, stop, next; BOOL st;
        int not_ok = 0;
        if( loops > 0 )
            ms_sleep(1);

        for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, 0);
             st;
             st = aapl_broadcast_next(aapl, &next, &start, &stop, 0) )
        {
            uint lane_addr = avago_struct_to_addr(&next);

            if( (serdes_get_int01_bits(aapl, lane_addr, mask) & mask) != mask )
                not_ok++;
        }
        if( not_ok == 0 )
        {
            if( loops > 0 )
                AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"SBus %s, Int 0x01 loops: %d\n",aapl_addr_to_str(addr), loops);
            return return_code == aapl->return_code ? 0 : -1;
        }
    }
    aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,"SBus %s, TX/RX RDY check timed out after %d loops. mask: 0x%x\n", aapl_addr_to_str(addr), loops, mask);
    /*// */
#if AAPL_ENABLE_DIAG
    if( aapl->diag_on_failure && !(aapl_get_jtag_idcode(aapl, 0) == 0x0991757f && (addr & 0xff) == 0x10) )
    {
        Avago_diag_config_t *config = avago_diag_config_construct(aapl);
        config->columns = 0;
        config->cycles  = 0;
        avago_diag(aapl, addr, config);
        avago_diag_config_destruct(aapl, config);
        aapl->diag_on_failure--;
    }
#endif
    /*// */
    return -1;
}

/** @brief   Gets the TX output enable state.
 ** @details
 ** @return  Returns TRUE if TX output is enabled, FALSE otherwise.
 ** @see     avago_serdes_get_tx_rx_ready(), avago_serdes_set_tx_output_enable(), avago_serdes_set_tx_rx_enable().
 **/
BOOL avago_serdes_get_tx_output_enable(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr)                  /**< [in] Device address number. */
{
    BOOL ret = serdes_get_int01_bits(aapl, addr, 0x04) == 0x04;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, TX output %s\n",aapl_addr_to_str(addr),aapl_enable_to_str(ret));
    return ret;
}
/** @brief   Sets the TX output enable state.
 ** @details Turns on TX if not already on.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_output_enable(), avago_serdes_get_tx_rx_ready(), avago_serdes_set_tx_rx_enable().
 **/
int avago_serdes_set_tx_output_enable(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL enable)                /**< [in] TRUE to enable output signal. */
{
    int return_code = aapl->return_code;
    int mask;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, TX output_en=%s\n",aapl_addr_to_str(addr),aapl_bool_to_str(enable));

    mask = serdes_get_int01_bits(aapl, addr, ~4) | (enable ? 4 : 0);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x01, mask);
    return return_code == aapl->return_code ? 0 : -1;
}


static int spico_int_02_retry(Aapl_t *aapl, uint addr, int data, int retry)
{
    int i;
    for( i = 0; i < retry; i++ )
    {
        if( 0x02 == (0xff & avago_spico_int(aapl, addr, 0x02, data)) )
            return 0;
        avago_sbus_rd(aapl, addr, 0x04);
    }
    return aapl_fail(aapl,__func__,__LINE__,"SBus %s, PRBS reconfigure timed out.\n",aapl_addr_to_str(addr));
}

/** @brief   Gets the selected TX data source.
 **
 ** @return  Returns the selected TX data source.
 ** @return  On error, aapl->return_code is set negative.
 ** @see     avago_serdes_set_tx_data_sel().
 **/
Avago_serdes_tx_data_sel_t avago_serdes_get_tx_data_sel(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    Avago_serdes_tx_data_sel_t ret = AVAGO_SERDES_TX_DATA_SEL_CORE;
    uint reg_tx_data, reg_lb_data, lb_bit, reg_tx_prbs_control = 0x29;
    Avago_serdes_mem_type_t reg_type;
    int data;

    int sdrev = aapl_get_sdrev(aapl,addr);
    switch( sdrev )
    {
    default:
    case AAPL_SDREV_16:   reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xdf; lb_bit = 1<<2; reg_type = AVAGO_ESB; break;
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:  reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xf1; lb_bit = 1<<0; reg_type = AVAGO_ESB; break;
    case AAPL_SDREV_D6_10:reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0x63; lb_bit = 1<<6; reg_type = AVAGO_ESB; break;
    case AAPL_SDREV_HVD6: reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xde; lb_bit = 1<<2; reg_type = AVAGO_ESB; break;
    case AAPL_SDREV_D6:   reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0x21; lb_bit = 1<<5; reg_type = AVAGO_LSB; break;
    case AAPL_SDREV_P1:   reg_tx_data = 0xe9; reg_tx_prbs_control = 0xf1; reg_lb_data = 0xc7; lb_bit = 1<<0; reg_type = AVAGO_ESB; break;
    }

    data = avago_serdes_mem_rd(aapl,addr,reg_type,reg_lb_data);
    if( data & lb_bit )
        ret = AVAGO_SERDES_TX_DATA_SEL_LOOPBACK;

    else
    {
        if( reg_lb_data != reg_tx_data )
            data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_tx_data);
        if( data & (1 << 4) )
        {
            data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_tx_prbs_control);
            ret = (Avago_serdes_tx_data_sel_t)(data & 0x07);
        }
    }
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, data_sel=%s\n",aapl_addr_to_str(addr),aapl_data_sel_to_str(ret));
    return ret;
}

/** @brief   Sets the TX data source.
 **
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_data_sel().
 **/
int avago_serdes_set_tx_data_sel(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_tx_data_sel_t source)  /**< [in] New TX data selection. */
{
    int return_code = aapl->return_code;
    int int_data;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, data_sel=%s\n",aapl_addr_to_str(addr),aapl_data_sel_to_str(source));

    int_data = source==AVAGO_SERDES_TX_DATA_SEL_LOOPBACK ? 0x0210 : 0x0200;
    if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x08, int_data)) return -1;

    switch( source )
    {
    case AVAGO_SERDES_TX_DATA_SEL_CORE:
        spico_int_02_retry(aapl, addr, 0x01ff, 8);
        break;

    case AVAGO_SERDES_TX_DATA_SEL_PRBS7:
    case AVAGO_SERDES_TX_DATA_SEL_PRBS9:
    case AVAGO_SERDES_TX_DATA_SEL_PRBS11:
    case AVAGO_SERDES_TX_DATA_SEL_PRBS15:
    case AVAGO_SERDES_TX_DATA_SEL_PRBS23:
    case AVAGO_SERDES_TX_DATA_SEL_PRBS31:
    case AVAGO_SERDES_TX_DATA_SEL_USER:
        int_data = 0x0100 | 0x0020 | (source & 0x0007);
        spico_int_02_retry(aapl, addr, int_data, 8);
        if( aapl_get_lsb_rev(aapl,addr) == 8 )
        {
            int_data = 0x0100 | 0x0000 | (source & 0x0007);
            spico_int_02_retry(aapl, addr, int_data, 8);
        }
        break;

    case AVAGO_SERDES_TX_DATA_SEL_LOOPBACK:
        break;
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrieves the 80-bit TX user data register.
 ** @details Note: Only the first 20 bits of the pattern are returned
 **          as that is all that is readily available from the SerDes.
 **          These bits are then duplicated into the other bits.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_set_tx_user_data().
 **/
int avago_serdes_get_tx_user_data(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    long user_data[4])          /**< [out] 80-bit user data (4 x 20). */
{
    int return_code = aapl->return_code;
    int value;
    int reg_prbs_seed_lo, reg_prbs_seed_hi;

    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1: reg_prbs_seed_lo = 0xf4; reg_prbs_seed_hi = 0xf5; break;
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_D6_10:
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_16: reg_prbs_seed_lo = 0x2c; reg_prbs_seed_hi = 0x2d; break;
    }

    value  =  avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_prbs_seed_lo);
    value |= (avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_prbs_seed_hi) & 0x0f) << 16;
    user_data[0] =
    user_data[1] =
    user_data[2] =
    user_data[3] = value & 0x000fffff;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, user_data=0x%05x\n",aapl_addr_to_str(addr),user_data[0]);
    return return_code == aapl->return_code ? 0 : -1;
}
/** @brief   Loads the 80-bit value into the TX user data register
 **          and select it as the TX input.
 ** @details The bit transmit order is from the least significant bit [0] of
 **          user_data[0] through bit [19] of user_data[3].
 **          Each word holds 20 significant bits.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_user_data().
 **/
int avago_serdes_set_tx_user_data(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    long user_data[4])          /**< [in] 80-bit user data (4 x 20). */
{
    int return_code = aapl->return_code;
    int i;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, user_data=0x%05x,%05x,%05x,%05x\n",
        aapl_addr_to_str(addr),user_data[0],user_data[1],user_data[2],user_data[3]);

    if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0018, 0x0000)) return -1;

    for( i = 0; i < 4; i++ )
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0019,  user_data[i] & 0x03ff);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0019, (user_data[i] >> 10) & 0x03ff);
    }
    if (aapl->return_code != return_code) return -1;
    return avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_USER);
}

/** @brief   Gets the TX inverter polarity.
 ** @return  Returns TRUE if inverter is enabled, FALSE if data is not being inverted.
 ** @return  On error, decrements aapl->return_code.
 ** @see     avago_serdes_get_rx_invert().
 ** @see     avago_serdes_set_tx_invert().
 **/
BOOL avago_serdes_get_tx_invert(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr)                  /**< [in] Device address number. */
{
    int ret;
    int reg_invert, invert_bit;
    int sdrev = aapl_get_sdrev(aapl,addr);
    if( (sdrev == AAPL_SDREV_CM4) && !aapl_check_firmware_rev(aapl,addr,0,0, FALSE, 1, 0x105F) )
        sdrev = AAPL_SDREV_16;

    switch( sdrev )
    {
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16: reg_invert =  0x29; invert_bit = 1<<6; break;
    case AAPL_SDREV_P1:   reg_invert = 0x15e; invert_bit = 1<<5;
                          if( aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B )
                          {
                              reg_invert = 0x162; invert_bit = 7<<7;
                          }
                          break;
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_16:   reg_invert =  0xdf; invert_bit = 1<<5; break;
    case AAPL_SDREV_D6_10:reg_invert =  0x3e; invert_bit = 1<<5; break;
    case AAPL_SDREV_HVD6: reg_invert =  0xde; invert_bit = 1<<5; break;
    case AAPL_SDREV_D6:   reg_invert = 0x211; invert_bit = 1<<3; break;
    }
    ret = !!(avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_invert) & invert_bit);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_invert=%s\n",aapl_addr_to_str(addr),aapl_onoff_to_str(ret));
    return ret;
}

/** @brief   Sets the TX inverter polarity.
 ** @details Set invert to TRUE to enable the inverter, FALSE to not invert the data.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_invert().
 ** @see     avago_serdes_set_rx_invert().
 **/
int avago_serdes_set_tx_invert(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL invert)                /**< [in] TRUE to invert output data. */
{
    uint data = invert ? 0x0101 : 0x0100;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_invert=%s\n",aapl_addr_to_str(addr),aapl_onoff_to_str(invert));
    if( !avago_spico_int_check(aapl, __func__, __LINE__, addr,0x13,data) ) return -1;
    return 0;
}

/** @brief   Retrieves the Tx data path configuration values
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see avago_serdes_get_rx_datapath_encoding().
 ** @see avago_serdes_set_tx_datapath_encoding().
 **/
int avago_serdes_get_tx_datapath_encoding(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL *gray_encode,          /**< [out] Returns TRUE if gray encoding is enabled. */
    BOOL *precode)              /**< [out] Returns TRUE if precode encoding is enabled. */
{
    int return_code = aapl->return_code;
    *gray_encode = *precode = FALSE;
    if( avago_serdes_get_tx_line_encoding(aapl,addr) )
    {
        int data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x29);
        *gray_encode = 0 != (data & (1<<7));

        data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x21);
        *precode = 0 != (data & (1<<9));
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Configures the data path encoding modes for the Tx.
 ** @details Does nothing unless device is an M4 SerDes in PAM4 mode.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see avago_serdes_get_tx_datapath_encoding().
 ** @see avago_serdes_set_rx_datapath_encoding().
 **/
int avago_serdes_set_tx_datapath_encoding(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL gray_encode,           /**< [in] TRUE to enable gray encoding (PAM4 only) */
    BOOL precode)               /**< [in] TRUE to enable precode encoding (PAM4 only). */
{
    int return_code = aapl->return_code;
    if( avago_serdes_get_tx_line_encoding(aapl,addr) )
    {
        int data = 0x400;
        data |= gray_encode ? 2 : 0;
        data |= precode ? 4 : 0;
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x13, data);
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrieves the Rx data path configuration values
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see avago_serdes_get_tx_datapath_encoding().
 ** @see avago_serdes_set_rx_datapath_encoding().
 **/
int avago_serdes_get_rx_datapath_encoding(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL *gray_decode,          /**< [out] Returns TRUE if gray decoding is enabled. */
    BOOL *predecode)            /**< [out] Returns TRUE if precode decoding is enabled. */
{
    int return_code = aapl->return_code;
    *gray_decode = *predecode = FALSE;
    if( avago_serdes_get_rx_line_encoding(aapl,addr) )
    {
        int data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x2b);
        *gray_decode = 0 != (data & (1<<3));

        data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x25);
        *predecode = 0 != (data & (1<<4));
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Configures the data path encoding modes for the Rx.
 ** @details Does nothing unless device is an M4 SerDes in PAM4 mode.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see avago_serdes_get_rx_datapath_encoding().
 ** @see avago_serdes_set_tx_datapath_encoding().
 **/
int avago_serdes_set_rx_datapath_encoding(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL gray_decode,           /**< [in] TRUE to enable gray decoding (PAM4 only). */
    BOOL predecode)             /**< [in] TRUE to enable precode decoding (PAM4 only). */
{
    int return_code = aapl->return_code;
    if( avago_serdes_get_rx_line_encoding(aapl,addr) )
    {
        int data = 0x800;
        data |= gray_decode ? 0x20 : 0;
        data |= predecode ? 0x40 : 0;
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x13, data);
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @cond INTERNAL */
static int width_tab[] = {10,16,20,32,40,64,80,80};
int avago_serdes_bits_to_width(uint bits)
{
    return width_tab[ bits & 7 ];
}
static int width_val[] = {0,4,2,5,3,6,7,7};
int avago_serdes_width_to_bits(int width)
{
    int i;
    for( i = 0; i < AAPL_ARRAY_LENGTH(width_tab); i++ )
        if( width_tab[i] == width )
            return width_val[i];
    return -1;
}
/** @endcond */

/** @brief   Gets the TX and RX data widths.
 ** @details Typically, these are set to the same value, but can be different
 **          for specialized situations.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_set_tx_rx_width().
 **/
int avago_serdes_get_tx_rx_width(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    int *tx,            /**< [out] Where to store TX width. */
    int *rx)            /**< [out] Where to store RX width. */
{
    int return_code = aapl->return_code;
    int data, sdrev = aapl_get_sdrev(aapl,addr);
    uint tx_bits, rx_bits, tx_mul = 1, rx_mul = 1;
    Avago_serdes_mem_type_t reg_type;
    int reg_width, tx_shift, rx_shift;
    switch( sdrev )
    {
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_16:
    case AAPL_SDREV_D6_10:
    case AAPL_SDREV_HVD6: reg_width =  0x22; reg_type = AVAGO_LSB; tx_shift = 8, rx_shift = 12; break;
    case AAPL_SDREV_P1:   reg_width =  0xea; reg_type = AVAGO_LSB; tx_shift = 8; rx_shift = 12; break;
    case AAPL_SDREV_D6:   reg_width = 0x301; reg_type = AVAGO_ESB; tx_shift = 0; rx_shift =  3; break;
    }

    data = avago_serdes_mem_rd(aapl, addr, reg_type, reg_width);

    tx_bits = (data >> tx_shift) & 0x7;
    rx_bits = (data >> rx_shift) & 0x7;

    if( sdrev == AAPL_SDREV_D6 ) { tx_bits &= 6; rx_bits &= 6; }
    if( sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_HVD6 || sdrev == AAPL_SDREV_D6_10 )
        tx_mul += ((avago_serdes_mem_rd(aapl,addr,AVAGO_LSB,0x21) >> 3) & 0x1);
    *tx = avago_serdes_bits_to_width(tx_bits) * tx_mul;

    if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_P1 )
        rx_mul += ((avago_serdes_mem_rd(aapl,addr,AVAGO_LSB,0x24) >> 3) & 0x1);
    *rx = avago_serdes_bits_to_width(rx_bits) * rx_mul;

    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx/rx width mode %d/%d bits\n",aapl_addr_to_str(addr),*tx,*rx);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Sets the TX and RX data width.
 ** @details Supported widths are hardware and rate dependent.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_rx_width().
 **/
int avago_serdes_set_tx_rx_width(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    int tx,             /**< [in] New TX width. */
    int rx)             /**< [in] New RX width. */
{
    return avago_serdes_set_tx_rx_width_pam(aapl, addr, tx, rx, AVAGO_SERDES_NRZ, AVAGO_SERDES_PAM2);
}

/** @brief   Sets the TX and RX data width.
 ** @details Supported widths are hardware and rate dependent.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_rx_width().
 **/
int avago_serdes_set_tx_rx_width_pam(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    int tx,             /**< [in] New TX width. */
    int rx,             /**< [in] New RX width. */
    Avago_serdes_line_encoding_t tx_encoding, /**< [in] Transmit serial line encoding */
    Avago_serdes_line_encoding_t rx_encoding  /**< [in] Receive serial line encoding */
    )
{
    int return_code = aapl->return_code;
    int build_id = avago_firmware_get_build_id(aapl, addr);
    int sdrev = aapl_get_sdrev(aapl,addr);
    int bits = avago_serdes_width_to_bits(tx) | (avago_serdes_width_to_bits(rx) << 4);
    if( bits < 0 )
        return aapl_fail(aapl, __func__, __LINE__, "ERROR: SBus %s, invalid width(s) %d/%d requested.\n",aapl_addr_to_str(addr),tx,rx);
    if( (build_id & 2) == 0 )
        bits |= 0x8800;
    if( sdrev == AAPL_SDREV_OM4 || sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 )
    {
        if (tx_encoding == AVAGO_SERDES_PAM4) bits |= 0x08;
        if (rx_encoding == AVAGO_SERDES_PAM4) bits |= 0x80;
    }
    else if( sdrev == AAPL_SDREV_P1 )
    {
        if( tx != rx )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes P1 requires Tx and Rx widths to match.\n", aapl_addr_to_str(addr));
    }
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx/rx width mode %d/%d bits, mask=0x%x\n",aapl_addr_to_str(addr),tx,rx,bits);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x14, bits);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrieves the Tx and Rx line encoding values.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_serdes_get_tx_rx_line_encoding(
    Aapl_t *aapl,                     /**< [in] Pointer to Aapl_t structure. */
    uint addr,                        /**< [in] Device address number. */
    Avago_serdes_line_encoding_t *tx, /**< [out] Transmit serial line encoding */
    Avago_serdes_line_encoding_t *rx) /**< [out] Receive serial line encoding */
{
    int return_code = aapl->return_code;
    if( aapl_get_ip_type(aapl,addr) == AVAGO_M4 )
    {
        int reg = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x22);
        *tx = (reg & 0x10) ? AVAGO_SERDES_PAM4 : AVAGO_SERDES_PAM2;
        *rx = (reg & 0x40) ? AVAGO_SERDES_PAM4 : AVAGO_SERDES_PAM2;
        AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, ip_type %d, return tx=%s, rx=%s\n", aapl_addr_to_str(addr), aapl_get_ip_type(aapl,addr), aapl_line_encoding_to_str(*tx), aapl_line_encoding_to_str(*rx));
    }
    else
        *tx = *rx = AVAGO_SERDES_PAM2;
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief This function is deprecated.
 ** @see   avago_serdes_get_tx_rx_line_encoding().
 **/
BOOL avago_serdes_get_tx_line_encoding(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    Avago_serdes_line_encoding_t tx, rx;
    return avago_serdes_get_tx_rx_line_encoding(aapl, addr, &tx, &rx) == 0 && tx == AVAGO_SERDES_PAM4;
}

/** @brief This function is deprecated.
 ** @see   avago_serdes_get_tx_rx_line_encoding().
 **/
BOOL avago_serdes_get_rx_line_encoding(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    Avago_serdes_line_encoding_t tx, rx;
    return avago_serdes_get_tx_rx_line_encoding(aapl, addr, &tx, &rx) == 0 && rx == AVAGO_SERDES_PAM4;
}

/** @brief  Initialize the structure to default values.
 ** @return void
 **/
void avago_serdes_tx_eq_init(
    Avago_serdes_tx_eq_t *ptr)  /**< Structure pointer to initialize */
{
    memset(ptr,0,sizeof(Avago_serdes_tx_eq_t));
}

/** @brief   Gets the TX equalization values.
 ** @details Retrieves all valid values, sets others to zero.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_set_tx_eq(), avago_serdes_get_tx_eq_limits().
 **/
int avago_serdes_get_tx_eq(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_tx_eq_t *tx_eq)    /**< [in] New TX equalization values. */
{
    int return_code = aapl->return_code;
    int reg_slew;
    int sdrev = aapl_get_sdrev(aapl,addr);
    avago_serdes_tx_eq_init(tx_eq);
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1043) )
    {
        tx_eq->pre   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0 << 14));
        tx_eq->atten = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (1 << 14));
        tx_eq->post  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (2 << 14));
        switch( sdrev )
        {
        case AAPL_SDREV_CM4:
        case AAPL_SDREV_CM4_16:
            tx_eq->pre_lsb     = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (1 << 12));
            tx_eq->pre_msb     = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (2 << 12));
            tx_eq->pre2        = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xc << 12));
            tx_eq->pre2_lsb    = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xd << 12));
            tx_eq->pre2_msb    = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xe << 12));
            tx_eq->pre3        = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (3 << 12));
            tx_eq->atten_lsb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (5 << 12));
            tx_eq->atten_msb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (6 << 12));
            tx_eq->post_lsb    = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (9 << 12));
            tx_eq->post_msb    = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xa << 12));
            break;
        case AAPL_SDREV_OM4:
            tx_eq->pre_lsb     = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (1 << 12));
            tx_eq->pre_msb     = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (2 << 12));
            tx_eq->atten_lsb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (5 << 12));
            tx_eq->atten_msb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (6 << 12));
            tx_eq->post_lsb    = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (9 << 12));
            tx_eq->post_msb    = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xa << 12));
            tx_eq->vert        = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (3 << 14));
            break;
        case AAPL_SDREV_HVD6:
            tx_eq->amp         = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (7 << 12));
            break;
        default:
            break;
        }
    }
    else
    {
        uint i = avago_spico_int(aapl, addr, 0x15, 1 << 8);
        tx_eq->pre   = (i >> 12) & 0x0F;
        tx_eq->atten = (i >> 5 ) & 0x1F;
        tx_eq->post  = (i >> 0 ) & 0x1F;
    }
    switch( sdrev )
    {
    case AAPL_SDREV_D6:    reg_slew = 0x240; break;
    case AAPL_SDREV_HVD6:  reg_slew = 0x040; break;
    case AAPL_SDREV_16:    reg_slew = 0x0e5; break;
    default:
    case AAPL_SDREV_P1:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:   reg_slew = 0; tx_eq->slew = 0; break;
    }
    if( reg_slew )
        tx_eq->slew = (short) avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg_slew) & 3;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_eq=%d,%d,%d,%d\n",
                    aapl_addr_to_str(addr),tx_eq->pre,tx_eq->atten,tx_eq->post,tx_eq->slew);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Sets the TX equalization values.
 ** @details Set all values, if applicable.
 **          Note: The slew rate is not adjustable on high speed SerDes and
 **                must be set to 0 in this case.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_eq(), avago_serdes_get_tx_eq_limits().
 **/
int avago_serdes_set_tx_eq(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_tx_eq_t *tx_eq)    /**< [in] New set of values. */
{
    int return_code = aapl->return_code;
    int rc;
    int sdrev = aapl_get_sdrev(aapl,addr);


    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_eq=%d,%d,%d\n",
                    aapl_addr_to_str(addr),tx_eq->pre,tx_eq->atten,tx_eq->post);
    switch( sdrev )
    {
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:

        tx_eq->pre_msb = tx_eq->pre;
        tx_eq->pre2_msb = tx_eq->pre2;
        tx_eq->post_msb = tx_eq->post;
        tx_eq->atten_msb = tx_eq->atten;

        rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xf<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<12)   | (tx_eq->pre        & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<12)   | (tx_eq->pre_lsb    & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<12)   | (tx_eq->pre_msb    & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<12)   | (tx_eq->pre3       & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (4<<12)   | (tx_eq->atten      & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (5<<12)   | (tx_eq->atten_lsb  & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (6<<12)   | (tx_eq->atten_msb  & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (8<<12)   | (tx_eq->post       & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (9<<12)   | (tx_eq->post_lsb   & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xA<<12) | (tx_eq->post_msb   & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xc<<12) | (tx_eq->pre2       & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xd<<12) | (tx_eq->pre2_lsb   & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xe<<12) | (tx_eq->pre2_msb   & 0xFF)));

        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Invalid TX equalization set: pre1=%d, pre1_lsb=%d, pre1_msb=%d, pre2=%d, pre2_lsb=%d, pre2_msb=%d, pre3=%d, atten=%d, atten_lsb=%d, atten_msb=%d, post=%d, post_lsb=%d, post_msb=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre, tx_eq->pre_lsb, tx_eq->pre_msb, tx_eq->pre2, tx_eq->pre2_lsb, tx_eq->pre2_msb, tx_eq->pre3, tx_eq->atten, tx_eq->atten_lsb, tx_eq->atten_msb, tx_eq->post, tx_eq->post_lsb, tx_eq->post_msb);
        break;
    case AAPL_SDREV_OM4:

        tx_eq->pre_msb = tx_eq->pre;
        tx_eq->post_msb = tx_eq->post;
        tx_eq->atten_msb = tx_eq->atten;

        rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<14) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xf<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<14)   | (tx_eq->vert       & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14)   | (tx_eq->post       & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14)   | (tx_eq->atten      & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (5<<12)   | (tx_eq->atten_lsb  & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (6<<12)   | (tx_eq->atten_msb  & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<12)   | (tx_eq->pre        & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<12)   | (tx_eq->pre_lsb    & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<12)   | (tx_eq->pre_msb    & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (9<<12)   | (tx_eq->post_lsb   & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xA<<12) | (tx_eq->post_msb   & 0xFF)));
        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Invalid TX equalization set: pre=%d, pre_lsb=%d, pre_msb=%d, atten=%d, atten_lsb=%d, atten_msb=%d, post=%d, post_lsb=%d, post_msb=%d, vert=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre, tx_eq->pre_lsb, tx_eq->pre_msb, tx_eq->atten, tx_eq->atten_lsb, tx_eq->atten_msb, tx_eq->post, tx_eq->post_lsb, tx_eq->post_msb, tx_eq->vert);
        break;
    case AAPL_SDREV_HVD6:
        rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xf<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14) | (tx_eq->post  & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14) | (tx_eq->atten & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<14) | (tx_eq->pre   & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (7<<12) | (tx_eq->amp   & 0xFF)));
        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Invalid TX equalization set: pre=%d, atten=%d, post=%d, amp=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre, tx_eq->atten, tx_eq->post, tx_eq->amp);
        break;

    default:
        if( tx_eq->atten == tx_eq->pre && tx_eq->atten == tx_eq->post )
            rc = 0xff & avago_spico_int(aapl, addr, 0x15, (3 << 14) | (tx_eq->atten & 0xFF));
        else
        {
            rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<14) | 0))
                && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14) | (tx_eq->post  & 0xFF)))
                && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14) | (tx_eq->atten & 0xFF)))
                && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<14) | (tx_eq->pre   & 0xFF)));
        }
        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Invalid TX equalization set: pre=%d, atten=%d, post=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre, tx_eq->atten, tx_eq->post);
        break;
    }
    if( rc )
    {
        int reg_slew = 0;
        switch( sdrev )
        {
        case AAPL_SDREV_16:   reg_slew = 0x0e5; break;
        case AAPL_SDREV_HVD6: reg_slew = 0x040; break;
        case AAPL_SDREV_D6:   reg_slew = 0x240; break;
        default:              reg_slew = 0;     break;
        }
        if( reg_slew )
        {
#if 0
            if( avago_get_ip_info(aapl,addr)->center_freq > 10000 )
            {
                if( tx_eq->slew != 0 )
                    aapl_fail(aapl,__func__,__LINE__,
                        "SBus %s, Invalid slew value: %d, high speed SerDes requires value of 0.\n", aapl_addr_to_str(addr), tx_eq->slew);
            }
            else
#endif
            if( tx_eq->slew > 3 || tx_eq->slew < 0 )
                aapl_fail(aapl,__func__,__LINE__, "SBus %s, Invalid slew value: %d, valid range [0..3].\n", aapl_addr_to_str(addr), tx_eq->slew);
            else
                avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, reg_slew, tx_eq->slew, 3);
        }
    }

    return return_code == aapl->return_code ? 0 : -1;
}


/** @brief   Gets the RX compare data configuration.
 **
 ** @return  Avago_serdes_rx_cmp_data_t value.
 **          On error, aapl->return_code is set negative.
 ** @see     avago_serdes_set_rx_cmp_data().
 **/
Avago_serdes_rx_cmp_data_t avago_serdes_get_rx_cmp_data(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr)              /**< [in] Device address number. */
{
    Avago_serdes_rx_cmp_data_t return_data;
    uint data;
    int reg_prbs_sel;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1: reg_prbs_sel = 0xf2; break;
    default:
    case AAPL_SDREV_D6: reg_prbs_sel = 0x2a; break;
    }
    data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_prbs_sel);
    return_data = (data & 0x8000) ? (Avago_serdes_rx_cmp_data_t)(data & 0x07) : AVAGO_SERDES_RX_CMP_DATA_OFF;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, cmp_data=%s\n", aapl_addr_to_str(addr), aapl_cmp_data_to_str(return_data));
    return return_data;
}

/** @brief   Sets the RX compare data configuration.
 ** @details Sets the PRBS pattern to compare incoming data against.
 **          If AVAGO_SERDES_RX_CMP_DATA_SELF_SEED is selected, the comparator
 **          automatically synchronizes to an incoming 80 bit pattern.
 **          The error counter then reports deviations from that pattern.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_cmp_data().
 **/
int avago_serdes_set_rx_cmp_data(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_rx_cmp_data_t data)    /**< [in] New RX compare data setting. */
{
    int int_data = 0x0200 | 0x0020 | 0x0010 | (data & 0x0007);
    if( data == AVAGO_SERDES_RX_CMP_DATA_OFF ) int_data = 0x2ff;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, cmp_data=%s\n", aapl_addr_to_str(addr), aapl_cmp_data_to_str(data));

    if( aapl_get_lsb_rev(aapl,addr) == 8 )
    {
        spico_int_02_retry(aapl, addr, int_data, 8);
        int_data = 0x0200 | 0x0000 | 0x0010 | (data & 0x0007);
        if( data == AVAGO_SERDES_RX_CMP_DATA_OFF ) int_data = 0x2ff;
        AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, cmp_data=%s\n", aapl_addr_to_str(addr), aapl_cmp_data_to_str(data));
    }
    return spico_int_02_retry(aapl, addr, int_data, 8);
}

/** @brief   Gets the RX termination.
 **
 ** @return  One of AVAGO_SERDES_RX_TERM_AGND, AVAGO_SERDES_RX_TERM_AVDD, or
 **          AVAGO_SERDES_RX_TERM_FLOAT.
 ** @return  On error, decrements aapl->return_code.
 ** @see     avago_serdes_set_rx_term().
 **/
Avago_serdes_rx_term_t avago_serdes_get_rx_term(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr)                  /**< [in] Device address number. */
{
    Avago_serdes_rx_term_t term = AVAGO_SERDES_RX_TERM_AGND;
    int reg_float, float_bit, reg_term, term_bit;
    Avago_serdes_mem_type_t reg_type;
    int data;

    switch( aapl_get_sdrev(aapl,addr) )
    {
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_16:   reg_float = 0xc7; float_bit = 1<< 6; reg_type = AVAGO_ESB; reg_term = 0xc7; term_bit = 1<< 5; break;
    case AAPL_SDREV_D6_10:reg_float = 0x1f; float_bit = 1<< 6; reg_type = AVAGO_ESB; reg_term = 0x1f; term_bit = 1<< 5; break;
    case AAPL_SDREV_P1:   reg_float = 0xec; float_bit = 1<<14; reg_type = AVAGO_ESB; reg_term = 0xa0; term_bit = 1<< 5; break;
    case AAPL_SDREV_HVD6: reg_float = 0x23; float_bit = 1<<11; reg_type = AVAGO_LSB; reg_term = 0x20; term_bit = 1<<10; break;
    case AAPL_SDREV_D6:   reg_float = 0x24; float_bit = 1<<10; reg_type = AVAGO_LSB; reg_term = 0x20; term_bit = 1<<10; break;
    }

    data = avago_serdes_mem_rd(aapl,addr,reg_type,reg_float);
    if( data & float_bit )
        term = AVAGO_SERDES_RX_TERM_FLOAT;
    else
    {
        if( reg_float != reg_term )
            data = avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_term);
        if( data & term_bit )
            term = AVAGO_SERDES_RX_TERM_AVDD;
    }
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, term=%s\n", aapl_addr_to_str(addr), aapl_term_to_str(term));
    return term;
}

/** @brief   Sets the RX termination.
 ** @details Term is AVAGO_SERDES_RX_TERM_AGND, AVAGO_SERDES_RX_TERM_AVDD, or
 **          AVAGO_SERDES_RX_TERM_FLOAT.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_term().
 **/
int avago_serdes_set_rx_term(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_rx_term_t term)    /**< [in] New termination value. */
{
    int return_code = aapl->return_code;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, term=%s\n", aapl_addr_to_str(addr), aapl_term_to_str(term));
    if( aapl_get_lsb_rev(aapl,addr) >= 3 )
    {
        int int_data = 0;
        switch( term )
        {
        case AVAGO_SERDES_RX_TERM_AGND : int_data = 0; break;
        case AVAGO_SERDES_RX_TERM_AVDD : int_data = 1; break;
        case AVAGO_SERDES_RX_TERM_FLOAT: int_data = 2; break;
        }
        if(!avago_spico_int_check(aapl, __func__, __LINE__, addr,0x2b,int_data) ) return -1;
    }
    else if( term == AVAGO_SERDES_RX_TERM_FLOAT )
    {
        avago_serdes_mem_rmw(aapl,addr,AVAGO_LSB,0x024,0x0400,0x0400);
    }
    else
    {
        int value = (term == AVAGO_SERDES_RX_TERM_AVDD) ? 0x0400 : 0x0000;
        avago_serdes_mem_rmw(aapl,addr,AVAGO_ESB,0x020,value,0x0400);
        avago_serdes_mem_rmw(aapl,addr,AVAGO_LSB,0x024,0x0000,0x0400);
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Reads 16 bits from the RX data stream.
 ** @details The data is read asynchronously from a live buffer, so is not
 **          guaranteed to be consistent.
 ** @details Note: If the Rx divider is a multiple of the bit width, then
 **          timing relationships may occur such that this call will always
 **          read while the data is being updated.  The result is the returned
 **          data will be consistently invalid.
 ** @return  On success, returns 16 bits of data (a positive value).
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_data().
 **/
int avago_serdes_get_rx_live_data(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int return_code = aapl->return_code;
    int rx_data_obs_lo_reg = aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1 ? 0xf6 : 0x2e;
    int results =  avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, rx_data_obs_lo_reg) & 0xffff;
    return return_code == aapl->return_code ? results : -1;
}

/** @brief   Injects errors into the RX data.
 ** @details RX error injection affects only the main data channel.
 **          Therefore, errors are only detected if the MAIN channel
 **          is one of the selected compare inputs.
 ** @details RX injected errors are detected in XOR and MAIN_PATGEN compare
 **          modes, but are not detected in TEST_PATGEN mode.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_tx_inject_error().
 **/
int avago_serdes_rx_inject_error(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    uint num_bits)              /**< [in] Number of error bits to inject. */
{
    int sdrev = aapl_get_sdrev(aapl,addr);
    int bits, orig, return_code = aapl->return_code;
    uint mem_addr = (aapl_get_ip_type(aapl, addr) == AVAGO_P1) ? 0xf3 : 0x2b;
    if( aapl_get_lsb_rev(aapl,addr) < 3 )
    {
        return aapl_fail(aapl, __func__, __LINE__,
            "ERROR: LSB revisions 01 & 02 don't support RX ERROR injection.\n");
    }

    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, injecting %u errors.\n", aapl_addr_to_str(addr), num_bits);

    orig = bits = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, mem_addr);

    if( sdrev == AAPL_SDREV_HVD6 )
    {
        bits &= ~0x07f0;
        bits |=  0x0130;
    }
    else if( sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_P1 || sdrev == AAPL_SDREV_D6_10 )
    {
        bits &= ~0x07f0;
        bits |=  0x0270;
    }
    else if( sdrev == AAPL_SDREV_CM4_16 || sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_OM4 )
    {
        bits &= ~0x07f0;
        if( avago_serdes_get_rx_line_encoding(aapl, addr) )
            bits |=  0x04f0;
        else
            bits |=  0x04e0;
    }
    for(         ; num_bits > 0; num_bits -- )
    {
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, mem_addr, bits & ~2);
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, mem_addr, bits |= 2);
    }
    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, mem_addr, orig & ~2);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Injects errors into the TX data.
 ** @details TX error injection affects the transmitted data stream. Therefore,
 **          errors are only detected when comparing with a known pattern.
 **          TX injected errors will be detected in RX TEST_PATGEN and MAIN_PATGEN modes.
 **          TX injected errors will not be detected in XOR mode.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_rx_inject_error().
 **/
int avago_serdes_tx_inject_error(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    uint num_bits)              /**< [in] Number of error bits to inject (max=65535). */
{
    uint int_data = MIN(num_bits,0x0ffff);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, injecting %u errors.\n",aapl_addr_to_str(addr),int_data);

    if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x1b, int_data)) return -1;
    return 0;
}

/** @brief  Gets the RX compare mode.
 **
 ** @return Returns the RX compare mode.
 ** @return On error, decrements aapl->return_code.
 ** @see     avago_serdes_set_rx_cmp_mode().
 **/
Avago_serdes_rx_cmp_mode_t avago_serdes_get_rx_cmp_mode(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int compare_reg = aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1 ? 0xe1 : 0x17;
    Avago_serdes_rx_cmp_mode_t mode = (Avago_serdes_rx_cmp_mode_t)(avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, compare_reg) & 0x0770);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, cmp_mode=%s\n", aapl_addr_to_str(addr), aapl_cmp_mode_to_str(mode));
    return mode;
}

/** @brief  Sets the RX compare mode.
 **
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_cmp_mode().
 **/
int avago_serdes_set_rx_cmp_mode(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_rx_cmp_mode_t mode)    /**< [in] New compare mode. */
{
    int new_mode = (0x0770 & mode) | 0x0003;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, cmp_mode=%s\n", aapl_addr_to_str(addr), aapl_cmp_mode_to_str(mode));
    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x03, new_mode) ? 0 : -1;
}

/** @brief   Gets the RX inverter polarity.
 ** @return  Returns TRUE if inverter is enabled, FALSE if data is not being inverted.
 ** @return  On error, decrements aapl->return_code.
 ** @see     avago_serdes_get_tx_invert().
 ** @see     avago_serdes_set_rx_invert().
 **/
BOOL avago_serdes_get_rx_invert(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr)                  /**< [in] Device address number. */
{
    BOOL invert;
    int reg_invert, invert_bit;
    Avago_serdes_mem_type_t mem_type = AVAGO_LSB;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    default:
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_D6_10:
    case AAPL_SDREV_16:  reg_invert = 0x24; invert_bit = 1<<0; break;
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_CM4: reg_invert = 0x2b; invert_bit = 1<<2; break;
    case AAPL_SDREV_P1:  reg_invert = 0xec; invert_bit = 1<<0; break;
    case AAPL_SDREV_D6:  reg_invert = 0x60; invert_bit = 1<<3; mem_type = AVAGO_ESB; break;
    }

    invert = !!(avago_serdes_mem_rd(aapl,addr,mem_type,reg_invert) & invert_bit);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, rx_invert=%s\n", aapl_addr_to_str(addr), aapl_onoff_to_str(invert));
    return invert;
}

/** @brief   Sets the RX inverter polarity.
 ** @details Set <b>invert</b> TRUE to enable the inverter, FALSE to not invert the data.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_invert().
 ** @see     avago_serdes_set_tx_invert().
 **/
int avago_serdes_set_rx_invert(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL invert)                /**< [in] TRUE to invert input data. */
{
    int data = invert ? 0x0210 : 0x0200;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, rx_invert=%s\n", aapl_addr_to_str(addr), aapl_onoff_to_str(invert));
    if( !avago_spico_int_check(aapl,__func__,__LINE__,addr,0x13,data) ) return -1;
    return 0;
}

/** @brief   Gets the RX signal input source.
 ** @return  Returns TRUE if internal loopback is enabled, FALSE if external signal.
 ** @return  On error, aapl->return_code becomes negative.
 ** @see     avago_serdes_set_rx_input_loopback().
 **/
BOOL avago_serdes_get_rx_input_loopback(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr)                  /**< [in] Device address number. */
{
    uint reg_addr, reg_bit;
    BOOL ret;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    default:
    case AAPL_SDREV_P1:    reg_addr = 0xec; reg_bit = 1<<1; break;
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_CM4:   reg_addr = 0xe8; reg_bit = 1<<3; break;
    case AAPL_SDREV_D6_10: reg_addr = 0x3e; reg_bit = 1<<1; break;
    case AAPL_SDREV_16:    reg_addr = 0xdf; reg_bit = 1<<1; break;
    case AAPL_SDREV_HVD6:  reg_addr = 0xde; reg_bit = 1<<1; break;
    case AAPL_SDREV_D6:    reg_addr =0x213; reg_bit = 1<<2; break;
    }
    ret = (avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_addr) & reg_bit) ? TRUE : FALSE;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, rx_input_loopback=%s\n",
        aapl_addr_to_str(addr), ret ? "internal" : "external");
    return ret;
}

/** @brief   Sets the RX signal input source.
 ** @details Set <b>internal_loopback</b> TRUE to select loopback from own TX output.
 ** @details Set to FALSE to select external signal.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_input_loopback().
 **/
int avago_serdes_set_rx_input_loopback(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL internal_loopback)     /**< [in] New loopback state. */
{
    int int_data = internal_loopback ? 0x0101 : 0x0100;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, loopback=%s\n",
        aapl_addr_to_str(addr), internal_loopback ? "internal" : "external");
    if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x08, int_data)) return -1;
    return 0;
}

int aapl_serdes_get_int30_bits(Aapl_t *aapl, uint addr, uint mask)
{
    int sdrev = aapl_get_sdrev(aapl,addr);
    int bits = 0;
    if( mask & 0x0007 )
    {
        int reg_spico_clk_sel = (sdrev == AAPL_SDREV_P1) ? 0xd6 : 0x0c;
        bits |= (avago_serdes_mem_rd(aapl,addr,AVAGO_LSB,reg_spico_clk_sel) >> 8) & 0x7;
    }
    if( mask & 0x00f0 )
    {
        int reg_pll_misc, reg_clk_misc, clk_shift;
        switch( sdrev )
        {
        default:
        case AAPL_SDREV_OM4:
        case AAPL_SDREV_CM4:
        case AAPL_SDREV_CM4_16:
        case AAPL_SDREV_16:   reg_clk_misc =  0xf0; clk_shift = 3; reg_pll_misc =  0xd1; break;
        case AAPL_SDREV_HVD6: reg_clk_misc = 0x300; clk_shift = 3; reg_pll_misc = 0x008; break;
        case AAPL_SDREV_D6:   reg_clk_misc = 0x300; clk_shift = 6; reg_pll_misc = 0x200; break;
        case AAPL_SDREV_P1:   break;
        }
        if( sdrev == AAPL_SDREV_P1 )
            bits |= AVAGO_SERDES_TX_PLL_REFCLK;
        else
        {
            bits |= (avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_clk_misc) >> clk_shift << 6) & 0xc0;
            bits |= (avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_pll_misc) >>        10 << 4) & 0x30;
        }
        if(      (bits & 0x10) == 0x00 ) bits &= 0xff0f;
        else if( (bits & 0x30) == 0x10 ) bits &= 0xff1f;
        else if( (bits & 0x70) == 0x30 ) bits &= 0xff3f;
    }
    if( mask & 0x0f00 )
    {
        int reg_rxdiv, pcsdiv_shift = 0, mode66_bit = 0, rev = 1;
        switch( sdrev )
        {
        default:
        case AAPL_SDREV_OM4:    reg_rxdiv = 0xc0; rev = 3; break;
        case AAPL_SDREV_CM4_16:
            if( aapl_get_ip_rev(aapl, addr) >= 0x22 )
                              { reg_rxdiv = 0xfb; rev = 2; }
            else
                              { reg_rxdiv = 0xc1; rev = 2; }
            break;
        case AAPL_SDREV_CM4:
        case AAPL_SDREV_P1:   return bits;
        case AAPL_SDREV_HVD6: return bits;
        case AAPL_SDREV_16:   reg_rxdiv = 0xc1; pcsdiv_shift = 8; mode66_bit = 1<<3; break;
        case AAPL_SDREV_D6:   reg_rxdiv = 0x73; pcsdiv_shift = 2; mode66_bit = 1<<0; break;
        }

        if( rev == 2 )
        {

            uint rxdiv = avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_rxdiv);
            uint values[] = { 0x08ed, 0x185b, 0x18eb, 0x105b, 0x38c7, 0x10ed, 0x10fd, 0x385b, 0x186b };
            int i;
            for( i = 0; i < AAPL_ARRAY_LENGTH(values); i++ )
            {
                if( rxdiv == values[i] )
                {
                    if( i < 8 )
                        bits |= (i << 8) | 0x0800;
                    break;
                }
            }
            if( i >= AAPL_ARRAY_LENGTH(values) )
                aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Unexpected value read from ESB register 0x%x: 0x%x\n", reg_rxdiv, rxdiv);
        }
        else if( rev == 3 )
        {
            uint rxdiv = avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_rxdiv);
            uint values[] = { 0x0c76, 0x1c2d, 0x1c75, 0x142d, 0x5c63, 0x1476, 0x147e, 0x5c2d, 0x1c35 };
            int i;
            for( i = 0; i < AAPL_ARRAY_LENGTH(values); i++ )
            {
                if( rxdiv == values[i] )
                {
                    if( i < 8 )
                        bits |= (i << 8) | 0x0800;
                    break;
                }
            }
            if( i >= AAPL_ARRAY_LENGTH(values) )
                aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Unexpected value read from ESB register 0x%x: 0x%x\n", reg_rxdiv, rxdiv);
        }
        else
        {
            uint pcs_read = avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_rxdiv);
            if( (pcs_read & mode66_bit) == 0 )
                bits |= ((pcs_read >> pcsdiv_shift << 8) & 0x0700) | 0x0800;
        }
    }
    return bits;
}

/** @brief   Gets the SerDes's SPICO clock source.
 ** @details
 ** @return  The SerDes's SPICO clock source.
 ** @return  On error, aapl->return_code is set negative.
 ** @see     avago_serdes_set_spico_clk_src(), avago_serdes_get_tx_pll_clk_src(), avago_serdes_get_pcs_fifo_clk_div().
 **/
Avago_serdes_spico_clk_t avago_serdes_get_spico_clk_src(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    Avago_serdes_spico_clk_t ret = (Avago_serdes_spico_clk_t)aapl_serdes_get_int30_bits(aapl, addr, 0x0007);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, spico_clk %s\n",aapl_addr_to_str(addr),aapl_spico_clk_to_str(ret));
    return ret;
}

/** @brief   Sets the SerDes's SPICO clock source.
 ** @details
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_spico_clk_src(), avago_serdes_set_tx_pll_clk_src(), avago_serdes_set_pcs_fifo_clk_div().
 **/
int avago_serdes_set_spico_clk_src(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_spico_clk_t src)   /**< [in] New clock source. */
{
    int return_code = aapl->return_code;
    int mask;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, spico_clk=%s\n",aapl_addr_to_str(addr),aapl_spico_clk_to_str(src));

    if( aapl_get_ip_type(aapl,addr) == AVAGO_P1 )
        addr = avago_make_sbus_lane_addr(addr, AVAGO_ADDR_QUAD_ALL);
    mask = aapl_serdes_get_int30_bits(aapl, addr, ~7) | (src & 7);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x30, mask);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Gets the TX PLL clock source.
 ** @details
 ** @return  Returns the TX PLL clock source.
 ** @return  On error, decrements aapl->return_code.
 ** @see     avago_serdes_set_tx_pll_clk_src(), avago_serdes_get_spico_clk_src(), avago_serdes_get_pcs_fifo_clk_div().
 **/
Avago_serdes_tx_pll_clk_t avago_serdes_get_tx_pll_clk_src(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    Avago_serdes_tx_pll_clk_t ret = (Avago_serdes_tx_pll_clk_t)aapl_serdes_get_int30_bits(aapl, addr, 0x00f0);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_pll_clk %s\n",aapl_addr_to_str(addr),aapl_pll_clk_to_str(ret));
    return ret;
}

/** @brief   Sets the SerDes's PLL Reference clock source.
 ** @details
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_pll_clk_src(), avago_serdes_set_spico_clk_src(), avago_serdes_set_pcs_fifo_clk_div().
 **/
int avago_serdes_set_tx_pll_clk_src(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] Device address number. */
    Avago_serdes_tx_pll_clk_t src)  /**< [in] New clock source. */
{
    int return_code = aapl->return_code;
    int mask;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_pll_clk=%s\n",aapl_addr_to_str(addr),aapl_pll_clk_to_str(src));

    mask = aapl_serdes_get_int30_bits(aapl, addr, ~0x00f0) | src;
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x30, mask);
    return return_code == aapl->return_code ? 0 : -1;
}


/** @brief   Reads whether or not signal OK has been initialized.
 ** @return  Returns TRUE if signal OK detection is enabled, FALSE if not.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 ** @see     avago_serdes_initialize_signal_ok().
 **/
BOOL avago_serdes_get_signal_ok_enable(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int sdrev = aapl_get_sdrev(aapl,addr);
    BOOL ret = FALSE;
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1046) )
    {
        if( sdrev == AAPL_SDREV_P1 )
        {
            ret = !((avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xa0) >> 7) & 1);
            if( ret )
            {
                int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xa1);
                ret = (val & 2) == 2;
            }
        }
        else if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_HVD6 )
        {
            int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xc4);
            ret = ((val>>8) & 0x03) == 0x02;
        } else {
            int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x080);
            ret = (val & 0x03) == 0x02;
        }
    }
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, signal_ok_enable=%s\n", aapl_addr_to_str(addr), aapl_bool_to_str(ret));
    return ret;
}

/** @brief   Checks for presence of electrical idle.
 ** @return  Returns TRUE if electrical idle is detected, FALSE if a signal is
 **          detected.
 **/
BOOL avago_serdes_get_electrical_idle(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int reg_rx_elec_idle = (aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1) ? 0xed : 0x25;
    int val = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_rx_elec_idle);
    BOOL ret = (val & 0x04) == 0x04;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, elec_idle=%s\n", aapl_addr_to_str(addr), aapl_bool_to_str(ret));
    return ret;
}

/** @brief   Reads the signal OK threshold value.
 ** @details Reads a sticky signal lost detector and returns whether any
 **          loss was detected since the last call to this function.
 **          Resets the detector if signal loss was detected so can tell
 **          if a signal is once again present.
 ** @return  On success, returns threshold value.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_initialize_signal_ok().
 **/
int avago_serdes_get_signal_ok_threshold(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int return_code = aapl->return_code;
    int threshold = 0;
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1046) )
    {
        int reg, shift, mask;
        switch( aapl_get_sdrev(aapl,addr) )
        {
        default:
        case AAPL_SDREV_HVD6:
        case AAPL_SDREV_D6:   reg = 0x80; shift = 2; mask = 0x0f; break;
        case AAPL_SDREV_CM4:  reg = 0xff; shift = 2; mask = 0x0f; break;
        case AAPL_SDREV_CM4_16:
        case AAPL_SDREV_16:   reg = 0xc4; shift = 0; mask = 0x1f; break;
        case AAPL_SDREV_P1:   reg = 0xa1; shift = 2; mask = 0x0f; break;
        case AAPL_SDREV_OM4:  reg = 0; return 0;
        }
        threshold = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg);
        threshold = (threshold >> shift) & mask;
    }
    if( return_code != aapl->return_code )
        threshold = -1;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, signal_ok_threshold=%d\n", aapl_addr_to_str(addr), threshold);
    return threshold;
}

/** @brief   Reads and resets the signal_ok_deasserted signal.
 ** @details Reads a sticky signal lost detector and returns whether any
 **          loss was detected since the last call to this function.
 **          Resets the detector if signal loss was detected so can tell
 **          if a signal is once again present.
 ** @return  Returns TRUE if no signal loss has been detected.
 ** @return  Returns FALSE if signal loss was detected since last check.
 ** @see     avago_serdes_initialize_signal_ok().
 **/
BOOL avago_serdes_get_signal_ok(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    BOOL reset)         /**< [in] Clear signal loss sticky bit if set. */
{
    int reg_serdes_rdy = (aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1) ? 0xee : 0x26;
    int bits = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_serdes_rdy);
    BOOL sig_ok = (bits & 0x0010) ? 0 : 1;
    if( reset && !sig_ok )
        avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, reg_serdes_rdy, 0, 0x0010);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, sig_ok=%s, reset=%d\n", aapl_addr_to_str(addr), aapl_bool_to_str(sig_ok), reset);
    return sig_ok;
}

/** @brief   Reads the live version of signal_ok
 ** @details Reads signal_ok from O_CORE_STATUS port
 ** @return  Returns TRUE if signal OK is true
 ** @return  Returns FALSE if signal OK is false
 ** @see     avago_serdes_initialize_signal_ok().
 **/
BOOL avago_serdes_get_signal_ok_live(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int reg_serdes_rdy = (aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1) ? 0xee : 0x26;
    int bits = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_serdes_rdy + 1);
    BOOL sig_ok = (bits & 0x0010) ? 1 : 0;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, sig_ok live=%s, reset=%d\n", aapl_addr_to_str(addr), aapl_bool_to_str(sig_ok));
    return sig_ok;
}

/** @brief   Enables the RX Idle Detector to aide detecting signal loss.
 ** @details Call this function once to initialize the idle detector.
 **          Then call avago_serdes_get_signal_ok() to check if signal loss is detected.
 **          Functional for firmware 0x1046 and newer.  No-op on older versions.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_signal_ok(), avago_serdes_get_signal_ok_threshold().
 **/
int avago_serdes_initialize_signal_ok(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    int threshold)      /**< [in] Threshold for signal OK (0-15). */
{
    int return_code = aapl->return_code;
    int ip_rev = aapl_get_ip_rev(aapl, addr);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, threshold %d\n", aapl_addr_to_str(addr), threshold);

    if( ip_rev >= 0x0a && ip_rev <= 0x0c && aapl_get_ip_type(aapl,addr) == AVAGO_SERDES && aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B )
        ;
    else
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1046) )
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x20);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x40 | ((threshold & 0xf)<<8));
    }
    avago_serdes_get_signal_ok(aapl, addr, TRUE);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Returns whether or not the RX PLL is frequency locked.
 ** @details NOTE: The PLL may be locked even when valid data is not
 **          present at the RX inputs. The user should generally rely
 **          on signal ok instead.
 ** @return  Returns TRUE if the PLL is locked
 ** @return  Returns FALSE if the PLL is not locked
 **/
BOOL avago_serdes_get_frequency_lock(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    BOOL flock = (avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x1c) & 0x8000) >> 15;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, freq lock=%d\n", aapl_addr_to_str(addr), flock);
    return flock;
}

/** @brief   Retrieves the value of the error counter.
 ** @details If reset is selected, resets the error counter after reading.
 ** @return  On success, returns the error count.
 ** @return  On error, decrements aapl->return_code and returns an all ones value.
 ** @see     avago_serdes_error_reset().
 **/
uint avago_serdes_get_errors(
    Aapl_t *aapl,                 /**< [in] Pointer to Aapl_t structure. */
    uint addr,                    /**< [in] Device address number. */
    Avago_serdes_mem_type_t type, /**< [in] Unused, set to AVAGO_LSB. */
    BOOL reset)                   /**< [in] Set to reset error count after read. */
{
    int return_code = aapl->return_code;
    uint rc, err_count;
    (void) type;

    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, 3);
    err_count  = avago_spico_int(aapl, addr, 0x1a, 0);
    err_count += avago_spico_int(aapl, addr, 0x1a, 0) << 16;

    if( reset )
        avago_serdes_error_reset(aapl, addr);

    rc = return_code == aapl->return_code ? err_count : ~0U;
    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, reset=%d, errors = %u.\n", aapl_addr_to_str(addr), reset, rc);
    return rc;
}

/** @brief   Retrieves the value of the simple error flag.
 ** @details If reset is selected, resets the error flag after reading.
 ** @return  On success, returns the whether or not the error flag has been set.
 ** @return  On error, decrements aapl->return_code and returns an all ones value.
 ** @see     avago_serdes_error_flag_reset().
 **/
BOOL avago_serdes_get_error_flag(
    Aapl_t *aapl,                 /**< [in] Pointer to Aapl_t structure. */
    uint addr,                    /**< [in] Device address number. */
    BOOL reset)                   /**< [in] Set to reset error flag after read. */
{
    BOOL error_flag = (avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x18) & 0x40) >> 6;
    if (reset) avago_serdes_error_flag_reset(aapl, addr);

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, reset=%d, errors = %u.\n", aapl_addr_to_str(addr), reset, error_flag);
    return error_flag;
}

/** @brief   Resets the error flag.
 ** @see     avago_serdes_get_errors().
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
void avago_serdes_error_flag_reset(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x18, 0x10, 0x10);
    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x18, 0x00, 0x10);
    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s\n", aapl_addr_to_str(addr));
}

/** @brief   Resets the error counter.
 ** @see     avago_serdes_get_errors().
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_error_reset(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    BOOL rc = avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x17, 0);
    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s; rc = %s.\n", aapl_addr_to_str(addr), aapl_bool_to_str(rc));
    return rc;
}

/** @brief   Configures core_to_cntl to enable tx/rx enable and/or 802.3AZ controls.
 ** @details Enables i_core_to_cntl control of certain functions.
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_enable_core_to_cntl(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr,              /**< [in] Device address number. */
    BOOL enable_tx_rx_en,   /**< [in] Enable i_core_to_cntl of Tx & Rx enable. */
    BOOL enable_low_power)  /**< [in] Enable i_core_to_cntl of Tx & Rx quiet, and lpi_disable. */
{
    BOOL rc;
    int data = 0;
    if( enable_tx_rx_en  ) data |= 1;
    if( enable_low_power ) data |= 2;
    rc = avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x27, data);
    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s; data = %x, rc = %s.\n", aapl_addr_to_str(addr), data, aapl_bool_to_str(rc));
    return rc;
}

/** @brief   Slips (drops) bits on the Rx.
 ** @details Slips up to 127 bits.
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_slip_bits(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    uint bits)      /**< [in] Number of bits to slip.  127 max. */
{
    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0c, bits & 0x7f);
}

/** @brief   Slips the Rx FIFO clock phase.
 ** @details Valid values are 1 to the word width.
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_slip_rx_phase(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    uint bits,      /**< [in] Number of bits to slip. 63 max. */
    BOOL remember)  /**< [in] If TRUE, applies slips every time the Rx is enabled. */
{
    int flags = remember ? 0x8000 : 0;
    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0e, ((bits & 0x3f) << 8) | flags);
}

/** @brief   Slips the Tx phase.
 ** @details Each slip slips the Tx load by 2 UI.  Up to 31 slips can be done.
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_slip_tx_phase(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    uint slips,     /**< [in] Number of slips (2UI each) to perform. */
    BOOL remember)  /**< [in] If TRUE, applies slips every time the Tx is enabled. */
{
    int flags = remember ? 0x8000 : 0;
    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0d, (slips & 0x1f) | flags);
}

/** @brief   Enables fast bit slip via the i_core_to_cntl interface.
 ** @details Note that pcs_fifo_clk_auto_slip applies only to original
 **          28nm D6 SerDes designs.
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_enable_core_bit_slip (
    Aapl_t *aapl,                /**< [in] Pointer to Aapl_t structure. */
    uint addr,                   /**< [in] Device address number. */
    BOOL enable_core,            /**< [in] Enables/disables core bit slip. */
    BOOL pcs_fifo_clk_auto_slip) /**< [in] Enables/disables PCS fifo clock auto slip. */
{
    int slip_cfg = enable_core ? (1 << 8) : 0;

    if( pcs_fifo_clk_auto_slip && aapl_get_sdrev(aapl, addr) == AAPL_SDREV_D6 )
        slip_cfg |= (1 << 9);

    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0c, slip_cfg);
}

/** @brief   Allocates and initializes a Avago_serdes_init_config_t struct.
 ** @details The return value should be released using
 **          avago_serdes_init_config_destruct() after use.
 ** @return  On success, returns a pointer to the initialized structure.
 ** @return  On failure, returns NULL.
 ** @see     avago_serdes_init_config_destruct(), avago_serdes_init().
 **/
Avago_serdes_init_config_t *avago_serdes_init_config_construct(
    Aapl_t *aapl)       /**< [in] Pointer to Aapl_t structure. */
{
    size_t bytes = sizeof(Avago_serdes_init_config_t);
    Avago_serdes_init_config_t *config;

    if( ! (config = (Avago_serdes_init_config_t *) aapl_malloc(aapl, bytes, "Avago_serdes_init_config_t struct")) )
        return NULL;
    memset(config, 0, sizeof(*config));

    config->sbus_reset   = TRUE;
    config->spico_reset  = TRUE;
    config->init_mode    = AVAGO_PRBS31_ILB;

    config->init_tx      = TRUE;
    config->tx_divider   = 10;
    config->tx_width     = 0;
    config->tx_encoding  = AVAGO_SERDES_PAM4;
    config->tx_phase_cal = FALSE;
    config->refclk_sync_master = TRUE;
    config->tx_output_en = TRUE;

    config->init_rx      = TRUE;
    config->rx_divider   = 10;
    config->rx_width     = 0;
    config->rx_encoding  = AVAGO_SERDES_PAM4;
    config->signal_ok_en = TRUE;
    config->signal_ok_threshold = 0x0;

    config->enable_tx_gray  = TRUE;
    config->enable_rx_gray  = TRUE;
    config->enable_tx_precode = FALSE;
    config->enable_rx_precode = FALSE;

    return config;
}

/** @brief   Releases a Avago_serdes_init_config_t struct.
 **
 ** @return  None.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init().
 **/
void avago_serdes_init_config_destruct(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_init_config_t *config) /**< [in] Pointer to struct to release. */
{
    aapl_free(aapl, config, "Avago_serdes_init_config_t struct");
}

/** @brief   Initializes a SerDes device to the given divider.
 **
 ** @return  0 on success,
 ** @return  > 0 if channel errors after initialization,
 ** @return  aapl->return_code (< 0) if errors during initialization.
 ** @see     avago_serdes_init().
 **/
int avago_serdes_init_quick(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    uint divider)   /**< [in] Desired divider to configure. */
{
    int errors;
    Avago_serdes_init_config_t *config = avago_serdes_init_config_construct(aapl);
    config->tx_divider = divider;
    config->rx_divider = divider;
    errors = avago_serdes_init(aapl, addr, config);
    avago_serdes_init_config_destruct(aapl, config);
    return errors;
}


/** @brief Provides a valid, device-specific width mode.
 **        Generally, wider widths are preferred.
 **/
static uint avago_serdes_get_default_width(
    Aapl_t *aapl, /**< [in] Pointer to Aapl_t structure. */
    uint addr)    /**< [in] Device address number. */
{
    uint width = 40;
    if( aapl_get_ip_type(aapl,addr) == AVAGO_M4 )
        width = 80;
    return width;
}

/** @brief   Configures and calibrates a SerDes.
 ** @details Call this to initialize a SerDes.
 ** @return  0 on success, aapl->return_code (< 0) on error.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init_config_destruct(), avago_serdes_init_quick().
 **/
int avago_serdes_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    BOOL tx_en = FALSE, rx_en = FALSE, tx_output_en = FALSE;

    uint errors;
    int sdrev = aapl_get_sdrev(aapl, addr);
    if (aapl_check_broadcast_address(aapl, addr, __func__, __LINE__, TRUE)) return -1;
    if( !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) ||
        !aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F) )
        return -1;

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s\n",aapl_addr_to_str(addr));
    config->fail_code = 0;
    if( config->sbus_reset  ) avago_sbus_reset(aapl, addr, 0);
    if( config->spico_reset ) avago_spico_reset(aapl, addr);

    if( sdrev == AAPL_SDREV_P1 )
    {
        Avago_addr_t addr_struct;
        avago_addr_to_struct(addr, &addr_struct);
        if( addr_struct.lane < 8 )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes P1 requires quad or chip level initialization.\n", aapl_addr_to_str(addr));

        if( config->tx_divider != config->rx_divider )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes P1 requires Tx and Rx dividers to match.\n", aapl_addr_to_str(addr));

        if( addr_struct.lane == AVAGO_ADDR_QUAD_ALL && !aapl_is_octal_p1(aapl, addr) )
            addr = avago_make_sbus_lane_addr(addr, AVAGO_ADDR_QUAD_LOW);
    }

    aapl_set_spico_running_flag(aapl, addr, 1);

    if( !avago_spico_crc(aapl, addr) )
        return aapl_fail(aapl, __func__, __LINE__, "SerDes %s failed CRC check.\n", aapl_addr_to_str(addr));

    if( !config->sbus_reset )
    {
        avago_serdes_get_tx_rx_ready(aapl, addr, &tx_en, &rx_en);
        tx_output_en = avago_serdes_get_tx_output_enable(aapl, addr);
    }

    avago_serdes_set_tx_rx_enable(aapl, addr, FALSE, FALSE, FALSE);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x11, 0x00);

    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0b, config->tx_phase_cal ? 1 : 0);

    if( config->tx_divider == config->rx_divider )
    {
        int div_val = (config->tx_divider & 0xff) | (1 << 15);
        if (config->refclk_sync_master) div_val |= 1<<12;
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x05, div_val);
    }
    else
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x05, (config->tx_divider & 0xff) | (config->refclk_sync_master ? 1<<12 : 0));
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x06, config->rx_divider & 0xff);
    }

    if( config->tx_width == 0 ) config->tx_width = avago_serdes_get_default_width(aapl, addr);
    if( config->rx_width == 0 ) config->rx_width = avago_serdes_get_default_width(aapl, addr);
    avago_serdes_set_tx_rx_width_pam(aapl, addr, config->tx_width, config->rx_width, config->tx_encoding, config->rx_encoding);

    if (avago_serdes_set_tx_rx_enable(aapl, addr, config->init_tx | tx_en, config->init_rx | rx_en, config->tx_output_en | tx_output_en) == -1) config->fail_code |= 0x4;

    if( config->signal_ok_en && sdrev != AAPL_SDREV_P1 )
        avago_serdes_initialize_signal_ok(aapl,addr,config->signal_ok_threshold);

    if( config->init_mode == AVAGO_INIT_ONLY )
    {
        avago_serdes_set_rx_input_loopback(aapl, addr, FALSE);
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "\n");
        return 0;
    }
    avago_serdes_set_rx_input_loopback(aapl, addr, TRUE);
    if( config->init_tx )
        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_PRBS31);
    if( config->init_rx )
    {
        if( config->init_tx && sdrev == AAPL_SDREV_OM4 && aapl_get_jtag_idcode(aapl, 0) == 0x0973957f )
            avago_serdes_set_tx_invert(aapl, addr, TRUE);
        if( config->init_tx && config->rx_encoding == AVAGO_SERDES_PAM4 && (sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 || sdrev == AAPL_SDREV_OM4) )
        {
            if( !(aapl->capabilities & AACS_SERVER_NO_CRC) )
            {
                avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 1);
                avago_serdes_dfe_wait(aapl, addr);
            }
            else
            {
                avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x20);
                avago_serdes_dfe_wait(aapl, addr);
            }
        }
        avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_PRBS31);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x03, AVAGO_SERDES_RX_CMP_MODE_MAIN_PATGEN | 0x0003);
    }

    if( sdrev == AAPL_SDREV_HVD6 )
    {
        avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x21, 0x80, 0x80);
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x1f, 0x1604);
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0, 0, 0x800);
        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_PRBS31);
        avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_PRBS31);
    }

    if (config->init_tx && config->init_rx)
    {
        avago_serdes_error_reset(aapl, addr);
        errors = avago_serdes_get_errors(aapl, addr, AVAGO_LSB, 1);
    }
    else errors = 0;

    if( config->init_mode == AVAGO_PRBS31_ELB    || config->init_mode == AVAGO_CORE_DATA_ELB )
    {
        if (config->tx_inversion) avago_serdes_set_tx_invert(aapl, addr, TRUE);
        if (config->rx_inversion) avago_serdes_set_rx_invert(aapl, addr, TRUE);
        avago_serdes_set_rx_input_loopback(aapl, addr, FALSE);
    }
    if( config->init_mode == AVAGO_CORE_DATA_ILB || config->init_mode == AVAGO_CORE_DATA_ELB )
    {
        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_CORE);
        avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_OFF);
    }

    avago_serdes_set_tx_datapath_encoding(aapl, addr, config->enable_tx_gray, config->enable_tx_precode );
    avago_serdes_set_rx_datapath_encoding(aapl, addr, config->enable_rx_gray, config->enable_rx_precode );

    aapl_log_printf(aapl,AVAGO_DEBUG1, "", 0, "Errors in ILB: %u.\n", errors);

    if( errors )
    {
        aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,
            "%u PRBS errors detected during ILB check of SerDes %s during serdes_init to div %d. Use this SerDes with caution.\n", errors, aapl_addr_to_str(addr), config->tx_divider);
        config->fail_code |= 0x8;
    }

    return (int)errors;
}


/** @brief Initialize struct with default values */
void avago_serdes_tune_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_dfe_tune_t *control)   /**< [in] Tune options structure to initialize. */
{
    (void)aapl;
    memset(control,0,sizeof(*control));

    control->tune_mode=AVAGO_DFE_ICAL;

    control->value[0] = 56;
    control->value[1] = 12;
    control->value[2] =  0;
    control->value[3] = 15;
}

/** @brief  Starts SerDes tuning with a few options.
 ** @note   Requires SerDes firmware revision 0x1046 or higher.
 ** @see    avago_serdes_dfe_pause(), avago_serdes_dfe_tune().
 **/
BOOL avago_serdes_tune(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_dfe_tune_t *control)   /**< [in] Tune options. */
{
    uint int_data = 0;
    uint int_data2 = 0;
    int sdrev = aapl_get_sdrev(aapl, addr);

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, tune_mode %s\n", aapl_addr_to_str(addr), aapl_dfe_tune_mode_to_str(control->tune_mode));

    if (!aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)) return FALSE;
    if (!aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F)) return FALSE;
    if (!aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, TRUE, 1, 0x1046)) return FALSE;

    if( sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 )
    {
        int fixed_flags = 0;
        int i;
        for( i = 0; i < 4; i++ )
        {
            if( control->fixed[i] )
            {
                int hal_index = i <= 2 ? 2-i : i;
                fixed_flags |= 1 << i;
                avago_spico_int(aapl, addr, 0x2C, 0x0900 | hal_index);
                avago_spico_int(aapl, addr, 0x6C, control->value[i]);
            }
        }
        avago_spico_int(aapl, addr, 0x2C, 0x0100 | 8);
        avago_spico_int(aapl, addr, 0x6C, fixed_flags);
    }
    else
    {
        uint column = (AAPL_SDREV_P1 == sdrev) ? 3 : 2;

        if( sdrev != AAPL_SDREV_P1 )
            if (control->dfe_disable){ int_data |= 0x0040; }

        if (control->fixed[0]) { int_data |= 0x0080; avago_spico_int(aapl, addr, 0x26, (column << 12) | (2 << 8) | (control->value[0] & 0xff)); }
        if (control->fixed[1]) { int_data |= 0x0100; avago_spico_int(aapl, addr, 0x26, (column << 12) | (1 << 8) | (control->value[1] & 0xff)); }
        if (control->fixed[2]) { int_data |= 0x0200; avago_spico_int(aapl, addr, 0x26, (column << 12) | (0 << 8) | (control->value[2] & 0xff)); }

        if (aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, FALSE, 1, 0x104D) &&
            control->fixed[3]) { int_data |= 0x0400; avago_spico_int(aapl, addr, 0x26, (column << 12) | (3 << 8) | (control->value[3] & 0xff)); }
    }

    if( sdrev != AAPL_SDREV_CM4 && sdrev != AAPL_SDREV_P1 ) {
      int_data2 = avago_spico_int(aapl, addr, 0x126, 0x5b00);
      int_data2 |= 0x5b00;
    }
    switch(control->tune_mode)
    {
    case AVAGO_DFE_ICAL           : { int_data |= 0x0001; int_data2 &= 0xFFFe; break; }
    case AVAGO_DFE_PCAL           : { int_data |= 0x0002; break; }
    case AVAGO_DFE_ICAL_ONLY      : { int_data |= 0x0001; int_data2 |= 0x0001; break; }
    case AVAGO_DFE_ENABLE_RR      : { int_data |= 0x000A; break; }
    case AVAGO_DFE_START_ADAPTIVE : { int_data |= 0x0006; break; }
    case AVAGO_DFE_STOP_ADAPTIVE  : { int_data  = 0x0002; break; }
    case AVAGO_DFE_DISABLE_RR     : { int_data  = 0x0008; break; }
    }

    if( sdrev != AAPL_SDREV_CM4 && sdrev != AAPL_SDREV_P1 )
      avago_spico_int(aapl, addr, 0x26, int_data2);
    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, int_data);
}

/** @brief   Returns a simple eye metric in range [0..1000].
 ** @details Value is derived from SerDes tuning, and returns 0 if tuning
 **          has not completed.
 **/
uint avago_serdes_eye_get_simple_metric(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr)                          /**< [in] Device address number. */
{
    int i, results = 1000;
    for( i = 0; i < 8; i += 2 )
    {
        short val1 = avago_spico_int(aapl,addr, 0x126, (4 << 12) | ((i+0) << 8));
        short val2 = avago_spico_int(aapl,addr, 0x126, (4 << 12) | ((i+1) << 8));
        int height = val2 - val1;
        if( height < results )
            results = height;
    }
    results = results * 1000 / 255;
    return results;
}

/** @} */

/**@brief Returns the register clock divider,
 **       which is also the number of symbols per heartbeat.
 **/
int avago_serdes_get_rx_register_clock(Aapl_t *aapl, uint addr)
{
    int sdrev = aapl_get_sdrev(aapl,addr);
    if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_HVD6 )
    {
        int tx_width, rx_width;
        avago_serdes_get_tx_rx_width(aapl, addr, &tx_width, &rx_width);
        if( rx_width >= 64 || avago_serdes_get_rx_line_encoding(aapl,addr) )
            rx_width /= 2;
        return rx_width;
    }
    return 20;
}

#define AVAGO_HAL_RD_MASK   (0x0 << 6)
#define AVAGO_HAL_WR_MASK   (0x1 << 6)
#define AVAGO_HAL_FUNC_MASK (0x3 << 6)

/** @brief   Retrieves the indicated HAL register value.
 ** @return  On success, returns value of register.
 ** @return  On failure, decrements aapl->return_code and returns -1.
 ** @see avago_serdes_hal_set(), avago_serdes_hal_func().
 **/
int avago_serdes_hal_get(
    Aapl_t *aapl,                /**< [in] Pointer to AAPL structure */
    uint addr,                   /**< [in] SBus address of SerDes */
    Avago_serdes_hal_type_t hal, /**< [in] HAL register set selector */
    uint member)                 /**< [in] HAL register selector */
{
    return avago_spico_int(aapl, addr, 0x2C | AVAGO_HAL_RD_MASK, ((hal & 0xff) <<8) | (member & 0xff));
}

/** @brief   Sets the indicated HAL register.
 ** @return  On success, returns previous value of register.
 ** @return  On failure, decrements aapl->return_code and returns -1.
 ** @see avago_serdes_hal_get(), avago_serdes_hal_func().
 **/
int avago_serdes_hal_set(
    Aapl_t *aapl,                /**< [in] Pointer to AAPL structure */
    uint addr,                   /**< [in] SBus address of SerDes */
    Avago_serdes_hal_type_t hal, /**< [in] HAL register set selector */
    uint member,                 /**< [in] HAL register selector */
    int value)                   /**< [in] Value to write into the register */
{
    int prev = avago_serdes_hal_get(aapl, addr, hal, member);
    int rc = avago_spico_int(aapl, addr, 0x2C | AVAGO_HAL_WR_MASK, value);
    if( rc != 0x2C )
        return aapl_fail(aapl, __func__, __LINE__, "avago_serdes_hal_set(%s,0x%x,0x%x,0x%x) interrupt returned 0x%x\n",aapl_addr_to_str(addr), (uint)hal, member, value, rc);
    return prev;
}

/** @brief   Invokes the indicated HAL function.
 ** @return  None.
 ** @see avago_serdes_hal_get(), avago_serdes_hal_set().
 **/
void avago_serdes_hal_func(
    Aapl_t *aapl,                           /**< [in] Pointer to AAPL structure */
    uint addr,                              /**< [in] SBus address of SerDes */
    Avago_serdes_hal_func_type_t hal_func)  /**< [in] HAL function selector */
{
    avago_spico_int(aapl, addr, 0x2C | AVAGO_HAL_FUNC_MASK, hal_func);
}

