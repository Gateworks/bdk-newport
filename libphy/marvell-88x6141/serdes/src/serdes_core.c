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
 ** @file serdes_core.c
 ** @brief Functions for SerDes devices.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS

#include "aapl.h"

#define AAPL_LOG_PRINT5 if(aapl->debug >= 5) aapl_log_printf
#define AAPL_LOG_PRINT6 if(aapl->debug >= 6) aapl_log_printf


#if AAPL_ALLOW_THREAD_SUPPORT
static AAPL_THREAD_STORAGE int mem_lock_count = 0;
#endif

/** @defgroup SerDes Generic SerDes API
 ** @{
 **/

/** @brief   Gets the SerDes LSB revision.
 ** @details Reads the revision of SerDes LSB using an AVAGO_LSB_DIRECT read.
 ** @return  Revision of the LSB (>= 0), or -1 on error.
 ** @see avago_firmware_get_rev(), avago_firmware_get_build_id().
 **/
int avago_serdes_get_lsb_rev(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int rc = -1;

    if( aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1))
    {
        if (aapl_check_process(aapl, addr, __func__, __LINE__, FALSE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F))
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

/** @brief   Reads a memory location from a list of SerDes devices.
 **
 ** @return  Non-negative value on success, -1 on failure and aapl->return_code is set to negative value.
 ** @return  The addr_list results field returns read result on success.
 **/
int avago_parallel_serdes_mem_rd(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list,        /**< [in,out] List of addresses and results. */
    Avago_serdes_mem_type_t type,   /**< [in] The memory access type. */
    uint mem_addr)                  /**< [in] Memory address to access */
{
    int ret = -1;
    int sdrev = aapl_get_sdrev(aapl,avago_struct_to_addr(addr_list));

    switch( sdrev )
    {
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
        break;
    default:
        switch( type )
        {
        case AVAGO_DMEM:
        case AVAGO_ESB:        type = AVAGO_LSB;        break;
        case AVAGO_DMEM_PREHALTED:
        case AVAGO_ESB_DIRECT: type = AVAGO_LSB_DIRECT; break;
        default:;
        }
    }

    AAPL_SERDES_MEM_LOCK;
    switch( type )
    {
    case AVAGO_BIG_REG_16:
        ret  = avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x18, mem_addr);
        ret |= avago_parallel_serdes_int(aapl, addr_list, 0x1a, 0);
        break;
    case AVAGO_BIG_REG_32: {
        int *temp, list_len;
        Avago_addr_t *a;

        for( list_len = 0, a = addr_list; a; a = a->next )
            list_len++;

        temp = (int *)aapl_malloc(aapl, list_len * sizeof(*temp), __func__);
        if( temp )
        {
            int i;
            ret  = avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x18, mem_addr);
            ret |= avago_parallel_serdes_int(aapl, addr_list, 0x1a, 0);
            for( i = 0, a = addr_list; a; a = a->next )
                temp[i++] = a->results;

            ret |= avago_parallel_serdes_int(aapl, addr_list, 0x1a, 0);

            for( i = 0, a = addr_list; a; a = a->next )
                a->results = a->results << 16 | temp[i++];
            aapl_free(aapl, temp, __func__);
        }
        break;
        }
    case AVAGO_LSB:
        ret = avago_parallel_serdes_int(aapl, addr_list, (1 << 14) | (mem_addr & 0x0fff), 0x00);
        break;
    case AVAGO_ESB:
        ret  = avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x18, 0x4000 | (mem_addr & 0x3fff));
        ret |= avago_parallel_serdes_int(aapl, addr_list, 0x1a, 0x00);
        break;
    default:
        aapl_fail(aapl, __func__, __LINE__, "SBus group, Invalid DMA type (%d).\n", type);
        break;
    }
    AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"SBus %s, Read  group 0x%04x -> 0x%x\n",
        aapl_mem_type_to_str(type), mem_addr, ret);
    AAPL_SERDES_MEM_UNLOCK;
    return ret;
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

    AAPL_SERDES_MEM_LOCK;

    switch( sdrev )
    {
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
        break;
    default:
        switch( type )
        {
        case AVAGO_DMEM:
        case AVAGO_ESB:        type = AVAGO_LSB;        break;
        case AVAGO_DMEM_PREHALTED:
        case AVAGO_ESB_DIRECT: type = AVAGO_LSB_DIRECT; break;
        default:;
        }
    }

    switch( type )
    {
    case AVAGO_BIG_REG_16:
    case AVAGO_BIG_REG_32:
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, mem_addr);
        ret = avago_spico_int(aapl, addr, 0x1a, 0);
        if (type == AVAGO_BIG_REG_32)
            ret |= avago_spico_int(aapl, addr, 0x1a, 0) << 16;
        break;
    }
    case AVAGO_LSB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            ret = avago_spico_int(aapl, addr, (1 << 14) | (mem_addr & 0x0fff), 0x00);
            break;
        }

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
            avago_sbus_wr(aapl, addr, 0x01, (1<<30) | (mem_addr & 0x0fff));
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
            avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, 0x4000 | (mem_addr & 0x3fff));
            ret = avago_spico_int(aapl, addr, 0x1a, 0x00);
            break;
        }

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
        ret = (avago_sbus_rd(aapl, addr, 0x00) >> 16 ) & 0xfff;
        avago_sbus_wr(aapl, addr, 0x00, 0x00);
        if (type == AVAGO_IMEM) avago_spico_resume(aapl, addr, spico_run_state);
        break;
    }

    default:
        aapl_fail(aapl, __func__, __LINE__, "SBus %s, Invalid DMA type (%d).\n", aapl_addr_to_str(addr), type);
        AAPL_SERDES_MEM_UNLOCK;
        return 0;
    }
    AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"SBus %s, Read  %s 0x%04x -> 0x%x\n",
        aapl_addr_to_str(addr), aapl_mem_type_to_str(type), mem_addr, ret);
    AAPL_SERDES_MEM_UNLOCK;
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

    AAPL_SERDES_MEM_LOCK;

    AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"SBus %s, Write %s 0x%04x <- 0x%x\n",
        aapl_addr_to_str(addr), aapl_mem_type_to_str(type), mem_addr, data);

    switch( sdrev )
    {
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
        break;
    default:
        switch( type )
        {
        case AVAGO_DMEM:
        case AVAGO_ESB:        type = AVAGO_LSB;        break;
        case AVAGO_DMEM_PREHALTED:
        case AVAGO_ESB_DIRECT: type = AVAGO_LSB_DIRECT; break;
        default:;
        }
    }

    switch( type )
    {
    case AVAGO_BIG_REG_16:
    case AVAGO_BIG_REG_32:
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, mem_addr);
        avago_spico_int(aapl, addr, 0x19, data & 0xffff);
        if( type == AVAGO_BIG_REG_32 )
            avago_spico_int(aapl, addr, 0x19, (data >> 16) & 0xffff);
        break;
    }
    case AVAGO_LSB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            avago_spico_int(aapl, addr, (2 << 14) | (mem_addr & 0x0fff), data);
            break;
        }

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
            avago_sbus_wr(aapl, addr, 0x01, (1<<31) | ((data & 0xffff) << 12) | (mem_addr & 0x0fff));
        else
        {
            if(aapl_get_lsb_rev(aapl,addr) >= 3)
            {
                avago_sbus_wr(aapl, addr, 0x02, (0<<31) | ((mem_addr & 0x1ff) << 16) | (data & 0xffff));
            }
            avago_sbus_wr(    aapl, addr, 0x02, (1<<31) | ((mem_addr & 0x1ff) << 16) | (data & 0xffff));
        }
        break;

    case AVAGO_ESB:
        if( aapl_get_spico_running_flag(aapl,addr) ||
            aapl_set_spico_running_flag(aapl,addr, avago_spico_running(aapl, addr)) )
        {
            avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x18, 0x4000 | (mem_addr & 0x3fff));
            avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x19, data);
            break;
        }

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
        break;
    }

    case AVAGO_DMEM:
    {
        if( sdrev == AAPL_SDREV_HVD6 )
        {
            avago_sbus_wr(aapl, addr, 0x01, (1<<29) | (1<<31) | ((data & 0xffff) << 12) | (mem_addr & 0x03ff));
        }
        else
        {
            int spico_run_state = avago_spico_halt(aapl, addr);
            int initial_value_0x01 = avago_sbus_rd(aapl, addr,  0x01);
                                     avago_sbus_wr(aapl, addr,  0x01, 0x40000000 | (mem_addr & 0xfff) | ((data & 0xffff) << 12));
                                     avago_sbus_wr(aapl, addr,  0x01, 0xc0000000 | (mem_addr & 0xfff) | ((data & 0xffff) << 12));
                                     avago_sbus_wr(aapl, addr,  0x01, initial_value_0x01);
            avago_spico_resume(aapl, addr, spico_run_state);
        }
        break;
    }

    case AVAGO_IMEM:
    {
        int spico_run_state = avago_spico_halt(aapl, addr);
        int initial_value_0x00 = avago_sbus_rd(aapl, addr,  0x00);
                                 avago_sbus_wr(aapl, addr,  0x00, 0x40000000 | (mem_addr & 0xffff) | ((data & 0x03ff) << 16));
                                 avago_sbus_wr(aapl, addr,  0x00, 0xc0000000 | (mem_addr & 0xffff) | ((data & 0x03ff) << 16));
                                 avago_sbus_wr(aapl, addr,  0x00, initial_value_0x00);
        avago_spico_resume(aapl, addr, spico_run_state);
        break;
    }

    default:
        aapl_fail(aapl, __func__, __LINE__, "SBus %s, Invalid DMA type (%d).\n", aapl_addr_to_str(addr), type);
        break;
    }
    AAPL_SERDES_MEM_UNLOCK;
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
    int spico_run_state;
    AAPL_SERDES_MEM_LOCK;
    spico_run_state = avago_spico_halt(aapl, addr);

    if(      type == AVAGO_LSB ) type = AVAGO_LSB_DIRECT;
    else if( type == AVAGO_ESB ) type = AVAGO_ESB_DIRECT;

    initial_value = avago_serdes_mem_rd(aapl, addr, type, mem_addr);
    avago_serdes_mem_wr(aapl, addr, type, mem_addr, (data & mask) | (initial_value & ~mask));

    avago_spico_resume(aapl, addr, spico_run_state);
    AAPL_SERDES_MEM_UNLOCK;
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
    case AAPL_SDREV_PON:
    case AAPL_SDREV_16:   reg_serdes_rdy = 0x26; reg_accel_misc_ctl =  0xdf; bit = 0; break;
    case AAPL_SDREV_D6_07:reg_serdes_rdy = 0x26; reg_accel_misc_ctl = 0x43e; bit = 0; break;
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
 ** @details If enabling TX or RX, waits for all devices to become ready.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @return  On timeout, returns -1 and does not decrement aapl->return_code.
 ** @see     avago_serdes_get_tx_output_enable(), avago_serdes_get_tx_rx_ready(), avago_serdes_set_tx_output_enable().
 **/
int avago_parallel_serdes_set_tx_rx_enable(
    Aapl_t *aapl,            /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list, /**< [in] Device address number. */
    BOOL tx,                 /**< [in] New TX state. */
    BOOL rx,                 /**< [in] New RX state. */
    BOOL tx_output,          /**< [in] New TX output state. */
    uint extra)              /**< [in] Extra options for interrupt */
{
    int return_code = aapl->return_code;
    int loops = 0;
    int mask = extra;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"tx_en=%s, rx_en=%s,tx_output_en=%s\n",
                aapl_bool_to_str(tx),aapl_bool_to_str(rx),aapl_bool_to_str(tx_output));

    if( tx        ) mask |= 0x01;
    if( rx        ) mask |= 0x02;
    if( tx_output ) mask |= 0x04;

    if( 1 != avago_parallel_serdes_int(aapl, addr_list, 0x01, mask) || (addr_list->results & 0xff) != 1 )
    {
        aapl->return_code--;
        return -1;
    }

    mask &= 0x03;
    for( loops = 0; loops <= AAPL_SERDES_INIT_RDY_TIMEOUT; loops++ )
    {
        Avago_addr_t *a;
        int not_ok = 0;
        if( loops > 0 )
            ms_sleep(1);

        for( a = addr_list; mask && a; a = a->next )
        {
            uint lane_addr = avago_struct_to_addr(a);

            if( (serdes_get_int01_bits(aapl, lane_addr, mask) & mask) != mask )
                not_ok++;
        }

        if( not_ok == 0 )
        {
            if( loops > 0 )
                AAPL_LOG_PRINT6(aapl,AVAGO_DEBUG6,__func__,__LINE__,"Int 0x01 loops: %d\n", loops);
            return return_code == aapl->return_code ? 0 : -1;
        }
    }
    aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,"TX/RX RDY check timed out after %d loops. mask: 0x%x\n", loops, mask);
    return -1;
}

/** @brief   Sets TX & RX enable states, and TX output value.
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
    Avago_addr_t addr_list;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_en=%s, rx_en=%s,tx_output_en=%s\n",
                aapl_addr_to_str(addr),aapl_bool_to_str(tx),aapl_bool_to_str(rx),aapl_bool_to_str(tx_output));

    avago_addr_to_struct(addr, &addr_list);
    if( 0 == avago_parallel_serdes_set_tx_rx_enable(aapl, &addr_list, tx, rx, tx_output, 0) )
        return 0;

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
    uint reg_tx_data, reg_pmd_control, reg_lb_data, lb_bit, reg_tx_prbs_control = 0x29;
    Avago_serdes_mem_type_t reg_type;
    int data;

    int sdrev = aapl_get_sdrev(aapl,addr);
    switch( sdrev )
    {
    default:
    case AAPL_SDREV_16:   reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xdf; lb_bit = 1<<2; reg_type = AVAGO_ESB;
                          reg_pmd_control = 0x52; break;
    case AAPL_SDREV_PON:  reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xf0; lb_bit = 1<<2; reg_type = AVAGO_ESB;
                          reg_pmd_control = 0x52; break;
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:  reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xf1; lb_bit = 1<<0; reg_type = AVAGO_ESB;
                          reg_pmd_control = 0x52; break;
    case AAPL_SDREV_D6_07:reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0x463; lb_bit = 1<<6; reg_type = AVAGO_ESB;
                          reg_pmd_control = 0x52; break;
    case AAPL_SDREV_HVD6: reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0xde; lb_bit = 1<<2; reg_type = AVAGO_ESB;
                          reg_pmd_control = 0x52; break;
    case AAPL_SDREV_D6:   reg_tx_data = 0x21; reg_tx_prbs_control = 0x29; reg_lb_data = 0x21; lb_bit = 1<<5; reg_type = AVAGO_LSB;
                          reg_pmd_control = 0x52; break;
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
        else if( sdrev != AAPL_SDREV_P1 )
        {
            int protocol_data;
            protocol_data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_pmd_control);
            if( protocol_data & 0x01 ) ret = AVAGO_SERDES_TX_DATA_SEL_PMD;
            else if( protocol_data & 0x10 ) ret = AVAGO_SERDES_TX_DATA_SEL_AN;
        }
    }
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, data_sel=%s\n",aapl_addr_to_str(addr),aapl_data_sel_to_str(ret));
    return ret;
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
    case AVAGO_SERDES_TX_DATA_SEL_PRBS13:
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
    case AVAGO_SERDES_TX_DATA_SEL_PMD:
    case AVAGO_SERDES_TX_DATA_SEL_AN:
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
    case AAPL_SDREV_D6_07:
    case AAPL_SDREV_D6:
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_PON:
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

    AAPL_SERDES_MEM_LOCK;
    if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0018, 0x0000))
    {
        AAPL_SERDES_MEM_UNLOCK;
        return -1;
    }

    for( i = 0; i < 4; i++ )
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0019,  user_data[i] & 0x03ff);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0019, (user_data[i] >> 10) & 0x03ff);
    }
    AAPL_SERDES_MEM_UNLOCK;
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
    int reg_preinv = 0, preinv_bit = 0;
    int sdrev = aapl_get_sdrev(aapl,addr);
    if( (sdrev == AAPL_SDREV_CM4) && !aapl_check_firmware_rev(aapl,addr,0,0, FALSE, 1, 0x105F) )
        sdrev = AAPL_SDREV_16;

    switch( sdrev )
    {
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16: reg_invert =  0x29; invert_bit = 1<<6;
                            reg_preinv =  0x21; preinv_bit = 1<<1; break;
    case AAPL_SDREV_P1:   reg_invert = 0x15e; invert_bit = 1<<5;
                          if( aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B )
                          {
                              reg_invert = 0x162; invert_bit = 7<<7;
                          }
                          break;
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_PON:
    case AAPL_SDREV_16:   reg_invert =  0xdf; invert_bit = 1<<5; break;
    case AAPL_SDREV_D6_07:reg_invert = 0x43e; invert_bit = 1<<5; break;
    case AAPL_SDREV_HVD6: reg_invert =  0xde; invert_bit = 1<<5; break;
    case AAPL_SDREV_D6:   reg_invert = 0x211; invert_bit = 1<<3; break;
    }
    ret = !!(avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_invert) & invert_bit);
    if( reg_preinv ) ret |= !!(avago_serdes_mem_rd(aapl,addr,AVAGO_ESB,reg_preinv) & preinv_bit);
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

/** @brief   Configures the data path encoding modes for Rx.
 ** @return  For each Avago_addr_t, the results field is set to 0 on success, -1 on failure.
 ** @return  Returns 0 if all datapath actions succeed.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_datapath().
 ** @see     avago_serdes_set_tx_datapath().
 **/
int avago_parallel_serdes_set_rx_datapath(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list,            /**< [in] Device address list. */
    Avago_serdes_datapath_t *datapath)  /**< [in] New set of values of datapath configurations */
{
    int return_code = aapl->return_code;
    uint addr = avago_struct_to_addr(addr_list);
    BOOL status = TRUE;

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s; Set Rx datapath encoding: mask: 0x%x; invert: %d; gray: %d; precode: %d; swizzle: %d.\n",
                          aapl_addr_to_str(addr), datapath->mask, datapath->polarity_invert, datapath->gray_enable,
                          datapath->precode_enable, datapath->swizzle_enable);

    if( datapath->mask != 0 )
    {
        uint data = 0;
        Avago_addr_t *addr_struct;
        if( datapath->mask & 0x01 )
            data |= (1<<9) | (datapath->polarity_invert ? (1<<4) : 0);

        if( (datapath->mask & 0x0e) && avago_serdes_get_rx_line_encoding(aapl, addr) )
        {
            Avago_serdes_datapath_t get_datapath;
            data |= (1 << 11);
            if( (datapath->mask & 0x0e) != 0x0e )
                avago_serdes_get_rx_datapath(aapl, addr, &get_datapath);
            if( datapath->mask & 0x02 ) data |= datapath->gray_enable       ? (1<<5) : 0;
            else                        data |= get_datapath.gray_enable    ? (1<<5) : 0;
            if( datapath->mask & 0x04 ) data |= datapath->precode_enable    ? (1<<6) : 0;
            else                        data |= get_datapath.precode_enable ? (1<<6) : 0;
            if( datapath->mask & 0x08 ) data |= datapath->swizzle_enable    ? (1<<7) : 0;
            else                        data |= get_datapath.swizzle_enable ? (1<<7) : 0;
        }
        status = avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x13, data);

        for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
            addr_struct->results = addr_struct->results == 0x13 ? 0 : -1;
    }
    return (return_code == aapl->return_code && status) ? 0 : -1;
}

/** @brief   Configures the data path encoding modes for Rx.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_datapath().
 ** @see     avago_serdes_set_tx_datapath().
 **/
int avago_serdes_set_rx_datapath(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_datapath_t *datapath)  /**< [in] New set of values of datapath configurations */
{
    Avago_addr_t addr_list;
    avago_addr_to_struct(addr, &addr_list);
    return avago_parallel_serdes_set_rx_datapath(aapl, &addr_list, datapath);
}

/** @brief   Configures the data path encoding modes for Tx.
 ** @return  For each Avago_addr_t, the results field is set to 0 on success, -1 on failure.
 ** @return  Returns 0 if all datapath actions succeed.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_parallel_serdes_set_rx_datapath().
 ** @see     avago_serdes_get_tx_datapath().
 ** @see     avago_serdes_set_rx_datapath().
 **/
int avago_parallel_serdes_set_tx_datapath(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list,            /**< [in] Device address list. */
    Avago_serdes_datapath_t *datapath)  /**< [in] New set of values of datapath configurations */
{
    int return_code = aapl->return_code;
    uint addr = avago_struct_to_addr(addr_list);
    BOOL status = TRUE;

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s; Set Tx datapath decoding: mask: 0x%x; invert: %d; gray: %d; precode: %d; swizzle: %d.\n",
                          aapl_addr_to_str(addr), datapath->mask, datapath->polarity_invert, datapath->gray_enable,
                          datapath->precode_enable, datapath->swizzle_enable);

    if( datapath->mask != 0 )
    {
        uint data = 0;
        Avago_addr_t *addr_struct;
        if( datapath->mask & 0x01 )
            data |= (1<<8) | (datapath->polarity_invert ? (1<<0) : 0);

        if( (datapath->mask & 0x0e) && avago_serdes_get_tx_line_encoding(aapl, addr) )
        {
            Avago_serdes_datapath_t get_datapath;
            data |= (1<<10);
            if( (datapath->mask & 0x0e) != 0x0e )
                avago_serdes_get_tx_datapath(aapl, addr, &get_datapath);
            if( datapath->mask & 0x02 ) data |= datapath->gray_enable       ? (1<<1) : 0;
            else                        data |= get_datapath.gray_enable    ? (1<<1) : 0;
            if( datapath->mask & 0x04 ) data |= datapath->precode_enable    ? (1<<2) : 0;
            else                        data |= get_datapath.precode_enable ? (1<<2) : 0;
            if( datapath->mask & 0x08 ) data |= datapath->swizzle_enable    ? (1<<3) : 0;
            else                        data |= get_datapath.swizzle_enable ? (1<<3) : 0;
        }
        status = 1 == avago_parallel_serdes_int(aapl, addr_list, 0x13, data) && (addr_list->results & 0xff) == 0x13;

        for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
            addr_struct->results = addr_struct->results == 0x13 ? 0 : -1;
    }
    return (return_code == aapl->return_code && status) ? 0 : -1;
}

/** @brief   Configures the data path encoding modes for Tx.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_datapath().
 ** @see     avago_serdes_set_rx_datapath().
 **/
int avago_serdes_set_tx_datapath(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_datapath_t *datapath)  /**< [in] New set of values of datapath configurations */
{
    Avago_addr_t addr_list;
    avago_addr_to_struct(addr, &addr_list);
    return avago_parallel_serdes_set_tx_datapath(aapl, &addr_list, datapath);
}

/** @brief   Retrieves the Rx data path configuration values
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_datapath().
 ** @see     avago_serdes_set_rx_datapath().
 **/
int avago_serdes_get_rx_datapath(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_datapath_t *datapath)  /**< [in] Address of structure to populate with current datapath configurations */
{
    int return_code = aapl->return_code;
    datapath->polarity_invert = avago_serdes_get_rx_invert(aapl, addr);
    datapath->mask = 0;

    if( avago_serdes_get_rx_line_encoding(aapl, addr) )
    {
        int data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x2b);
        datapath->gray_enable = 0 != (data & (1<<3));

        data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x25);
        datapath->precode_enable = 0 != (data & (1<<4));

        data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x6d);
        datapath->swizzle_enable = 0 != (data & (1<<14));
    }
    else
        datapath->gray_enable = datapath->precode_enable = datapath->swizzle_enable = FALSE;

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, Get Rx datapath coding: invert: %d, gray: %d, precode: %d, "
                          "swizzle: %d.\n", aapl_addr_to_str(addr), datapath->polarity_invert, datapath->gray_enable,
                          datapath->precode_enable, datapath->swizzle_enable);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrieves the Tx data path configuration values
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_rx_datapath().
 ** @see     avago_serdes_set_tx_datapath().
 **/
int avago_serdes_get_tx_datapath(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_datapath_t *datapath)  /**< [in] Address of structure to populate with current datapath configurations */
{
    int return_code = aapl->return_code;
    datapath->polarity_invert = avago_serdes_get_tx_invert(aapl, addr);
    datapath->mask = 0;

    if( avago_serdes_get_tx_line_encoding(aapl, addr) )
    {
        int data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x29);
        datapath->gray_enable = 0 != (data & (1<<7));

        data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x21);
        datapath->precode_enable = 0 != (data & (1<<9));

        data = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x6d);
        datapath->swizzle_enable = 0 != (data & (1<<12));
    }
    else
        datapath->gray_enable = datapath->precode_enable = datapath->swizzle_enable = FALSE;

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, Get Tx datapath coding: invert: %d, gray: %d, precode: %d, "
                          "swizzle: %d.\n", aapl_addr_to_str(addr), datapath->polarity_invert, datapath->gray_enable,
                          datapath->precode_enable, datapath->swizzle_enable);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrieves the Tx data path configuration values
 ** @return  On success, returns 0.
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
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__,__LINE__,"gray_encode = %s, precode = %s.\n", aapl_bool_to_str(*gray_encode), aapl_bool_to_str(*precode));
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

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__,__LINE__,"gray_encode = %s, precode = %s.\n", aapl_bool_to_str(gray_encode), aapl_bool_to_str(precode));
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
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__,__LINE__,"gray_decode = %s, predecode = %s.\n", aapl_bool_to_str(*gray_decode), aapl_bool_to_str(*predecode));
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

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__,__LINE__,"gray_decode = %s, predecode = %s.\n", aapl_bool_to_str(gray_decode), aapl_bool_to_str(predecode));
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
    case AAPL_SDREV_PON:
    case AAPL_SDREV_16:
    case AAPL_SDREV_D6_07:
    case AAPL_SDREV_HVD6: reg_width =  0x22; reg_type = AVAGO_LSB; tx_shift = 8, rx_shift = 12; break;
    case AAPL_SDREV_P1:   reg_width =  0xea; reg_type = AVAGO_LSB; tx_shift = 8; rx_shift = 12; break;
    case AAPL_SDREV_D6:   reg_width = 0x301; reg_type = AVAGO_ESB; tx_shift = 0; rx_shift =  3; break;
    }

    data = avago_serdes_mem_rd(aapl, addr, reg_type, reg_width);

    tx_bits = (data >> tx_shift) & 0x7;
    rx_bits = (data >> rx_shift) & 0x7;

    if( sdrev == AAPL_SDREV_D6 ) { tx_bits &= 6; rx_bits &= 6; }
    if( sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_HVD6 || sdrev == AAPL_SDREV_D6_07 )
        tx_mul += ((avago_serdes_mem_rd(aapl,addr,AVAGO_LSB,0x21) >> 3) & 0x1);
    *tx = avago_serdes_bits_to_width(tx_bits) * tx_mul;

    if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_CM4_16 && sdrev != AAPL_SDREV_P1 )
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
 ** @return  On success on all devices, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_rx_width().
 **/
int avago_parallel_serdes_set_tx_rx_width_pam(
    Aapl_t *aapl,            /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list, /**< [in] Device address list. */
    int tx,                  /**< [in] New TX width. */
    int rx,                  /**< [in] New RX width. */
    Avago_serdes_line_encoding_t tx_encoding, /**< [in] Transmit serial line encoding */
    Avago_serdes_line_encoding_t rx_encoding  /**< [in] Receive serial line encoding */
    )
{
    int return_code = aapl->return_code;
    uint addr = avago_struct_to_addr(addr_list);
    int build_id = aapl_get_firmware_build(aapl, addr);
    int sdrev = aapl_get_sdrev(aapl,addr);
    int bits = avago_serdes_width_to_bits(tx) | (avago_serdes_width_to_bits(rx) << 4);
    if( bits < 0 )
        return aapl_fail(aapl, __func__, __LINE__, "ERROR: SBus %s, invalid width(s) %d/%d requested.\n",aapl_addr_to_str(addr),tx,rx);

    if( (build_id & (1<<1)) == 0 )
        if( (build_id & (1<<2)) != 0 )
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
    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x14, bits);
    return return_code == aapl->return_code ? 0 : -1;
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
    int rc;
    Avago_addr_t addr_struct;
    avago_addr_to_struct(addr,&addr_struct);
    rc = avago_parallel_serdes_set_tx_rx_width_pam(aapl, &addr_struct, tx, rx, tx_encoding, rx_encoding);
    if( rc != 0 )
        aapl_log_printf(aapl,AVAGO_ERR,__func__,__LINE__,"SBus %s\n", aapl_addr_to_str(addr));
    return rc;
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
        tx_eq->pre   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x0 << 12));
        tx_eq->atten = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x4 << 12));
        tx_eq->post  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x8 << 12));
        switch( sdrev )
        {
        case AAPL_SDREV_CM4:
        case AAPL_SDREV_CM4_16:
            tx_eq->pre3      = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x3 << 12));
#if 1
            tx_eq->pre2      = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xc << 12));
#else
            tx_eq->pre_lsb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x1 << 12));
            tx_eq->pre_msb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x2 << 12));
            tx_eq->atten_lsb = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x5 << 12));
            tx_eq->atten_msb = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x6 << 12));
            tx_eq->post_lsb  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x9 << 12));
            tx_eq->post_msb  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xa << 12));
            tx_eq->pre2_lsb  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xd << 12));
            tx_eq->pre2_msb  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xe << 12));
#endif
            break;
        case AAPL_SDREV_OM4:
            tx_eq->pre_lsb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x1 << 12));
            tx_eq->pre_msb   = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x2 << 12));
            tx_eq->atten_lsb = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x5 << 12));
            tx_eq->atten_msb = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x6 << 12));
            tx_eq->post_lsb  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0x9 << 12));
            tx_eq->post_msb  = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xa << 12));
            tx_eq->vert      = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (0xc << 12));
            tx_eq->t2        = (short) ( (avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xdd) & 0x0800) ? 1 : 0 );
            break;
        case AAPL_SDREV_HVD6:
            tx_eq->amp       = (short) avago_spico_int(aapl, addr, 0x15, (1 << 8) | (7 << 12));
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
    case AAPL_SDREV_PON:
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
    uint t2_mode;


    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_eq=%d,%d,%d\n",
                    aapl_addr_to_str(addr),tx_eq->pre,tx_eq->atten,tx_eq->post);
    switch( sdrev )
    {
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:

        rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xc<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x8<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x4<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x0<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x3<<12) | 0));

#if 1

        rc = (0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x0<<12) | (tx_eq->pre   & 0xFF)))) && rc;
        rc = (0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x4<<12) | (tx_eq->atten & 0xFF)))) && rc;
        rc = (0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x8<<12) | (tx_eq->post  & 0xFF)))) && rc;
        rc = (0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xc<<12) | (tx_eq->pre2  & 0xFF)))) && rc;
        rc = (0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0x3<<12) | (tx_eq->pre3  & 0xFF)))) && rc;

#else

        rc = rc && ( ( tx_eq->pre_lsb == tx_eq->pre_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<12)  | (tx_eq->pre_lsb & 0xFF))) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<12)  | (tx_eq->pre_lsb & 0xFF))) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<12)  | (tx_eq->pre_msb & 0xFF))) ) );

        rc = rc && ( ( tx_eq->pre2_lsb == tx_eq->pre2_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xc<<12)| (tx_eq->pre2_lsb & 0xFF))) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xd<<12)| (tx_eq->pre2_lsb & 0xFF))) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xe<<12)| (tx_eq->pre2_msb & 0xFF))) ) );

        rc = rc && ( ( tx_eq->atten_lsb == tx_eq->atten_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (4<<12)  | (tx_eq->atten_lsb & 0xFF))) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (5<<12)  | (tx_eq->atten_lsb & 0xFF))) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (6<<12)  | (tx_eq->atten_msb & 0xFF))) ) );

        rc = rc && ( ( tx_eq->post_lsb == tx_eq->post_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (8<<12)  | (tx_eq->post_lsb & 0xFF))) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (9<<12)  | (tx_eq->post_lsb & 0xFF))) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xA<<12)| (tx_eq->post_msb & 0xFF))) ) );
#endif

        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Incorrect return value of Interrupt 0x15 for: pre1_lsb=%d, pre1_msb=%d, pre2_lsb=%d, pre2_msb=%d, pre3=%d, atten_lsb=%d, atten_msb=%d, post_lsb=%d, post_msb=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre_lsb, tx_eq->pre_msb, tx_eq->pre2_lsb, tx_eq->pre2_msb, tx_eq->pre3, tx_eq->atten_lsb, tx_eq->atten_msb, tx_eq->post_lsb, tx_eq->post_msb);
        break;
    case AAPL_SDREV_OM4:

        t2_mode = ( tx_eq->t2 == 1 ) ? 0x0200 : 0;

        rc =         (0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<14)   | (tx_eq->vert    & 0xFF) | t2_mode)));

        rc = rc && ( ( tx_eq->pre_lsb == tx_eq->pre_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<12)  | (tx_eq->pre_lsb & 0xFF) | t2_mode)) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<12)  | (tx_eq->pre_lsb & 0xFF) | t2_mode)) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<12)  | (tx_eq->pre_msb & 0xFF) | t2_mode)) ) );

        rc = rc && ( ( tx_eq->atten_lsb == tx_eq->atten_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (4<<12)  | (tx_eq->atten_lsb & 0xFF) | t2_mode)) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (5<<12)  | (tx_eq->atten_lsb & 0xFF) | t2_mode)) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (6<<12)  | (tx_eq->atten_msb & 0xFF) | t2_mode)) ) );

        rc = rc && ( ( tx_eq->post_lsb == tx_eq->post_msb )
                   ? ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (8<<12)  | (tx_eq->post_lsb & 0xFF) | t2_mode)) )
                   : ( 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (9<<12)  | (tx_eq->post_lsb & 0xFF) | t2_mode)) &&
                       0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xA<<12)| (tx_eq->post_msb & 0xFF) | t2_mode)) ) );

        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Incorrect return value of Interrupt 0x15 for: pre_lsb=%d, pre_msb=%d, atten_lsb=%d, atten_msb=%d, post_lsb=%d, post_msb=%d, vert=%d, t2=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre_lsb, tx_eq->pre_msb, tx_eq->atten_lsb, tx_eq->atten_msb, tx_eq->post_lsb, tx_eq->post_msb, tx_eq->vert, tx_eq->t2);
        break;
    case AAPL_SDREV_HVD6:
        rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0xf<<12) | 0))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14) | (tx_eq->post  & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14) | (tx_eq->atten & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<14) | (tx_eq->pre   & 0xFF)))
            && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (7<<12) | (tx_eq->amp   & 0xFF)));
        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Incorrect return value of Interrupt 0x15 for: pre=%d, atten=%d, post=%d, amp=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre, tx_eq->atten, tx_eq->post, tx_eq->amp);
        break;

    default:
        if( tx_eq->atten == tx_eq->pre && tx_eq->atten == tx_eq->post )
            rc = 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3 << 14) | (tx_eq->atten & 0xFF)));
        else
        {
            rc =   0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (3<<14) | 0))
                && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (2<<14) | (tx_eq->post  & 0xFF)))
                && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (1<<14) | (tx_eq->atten & 0xFF)))
                && 0x15 == (0xff & avago_spico_int(aapl, addr, 0x15, (0<<14) | (tx_eq->pre   & 0xFF)));
        }
        if( !rc )
            aapl_fail(aapl, __func__,__LINE__,
                    "SBus %s, Incorrect return value of Interrupt 0x15 for: pre=%d, atten=%d, post=%d.\n",
                    aapl_addr_to_str(addr), tx_eq->pre, tx_eq->atten, tx_eq->post);
        break;
    }
    if( rc )
    {
        int reg_slew = 0;
        switch( sdrev )
        {
        case AAPL_SDREV_PON:
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
                aapl_fail(aapl,__func__,__LINE__, "SBus %s, Incorrect return value of Interrupt 0x15 for: slew = %d\n", aapl_addr_to_str(addr), tx_eq->slew);
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
    case AAPL_SDREV_PON:
    case AAPL_SDREV_16:   reg_float = 0x0c7; float_bit = 1<< 6; reg_type = AVAGO_ESB; reg_term = 0x0c7; term_bit = 1<< 5; break;
    case AAPL_SDREV_D6_07:reg_float = 0x41f; float_bit = 1<< 6; reg_type = AVAGO_ESB; reg_term = 0x41f; term_bit = 1<< 5; break;
    case AAPL_SDREV_P1:   reg_float = 0x0ec; float_bit = 1<<14; reg_type = AVAGO_ESB; reg_term = 0x0a0; term_bit = 1<< 5; break;
    case AAPL_SDREV_HVD6: reg_float = 0x023; float_bit = 1<<11; reg_type = AVAGO_LSB; reg_term = 0x020; term_bit = 1<<10; break;
    case AAPL_SDREV_D6:   reg_float = 0x024; float_bit = 1<<10; reg_type = AVAGO_LSB; reg_term = 0x020; term_bit = 1<<10; break;
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
    if( aapl_get_lsb_rev(aapl,addr) >= 3 || aapl_get_process_id(aapl,addr) == AVAGO_PROCESS_E )
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

/** @brief   Reads 80 bits from the RX data stream.
 ** @details The data is captured using the Rx compare circuitry, with the
 **          side-effect that rx_cmp_data is temporarily set to OFF.
 ** @return  On success, returns 0;
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_tx_user_data().
 **/
int avago_serdes_get_rx_data(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    long data[4])       /**< [out] 80-bit data (4 x 20). data[0] bit 0 is first bit. */
{
    int return_code = aapl->return_code;
    Avago_serdes_rx_cmp_data_t cmp_data = avago_serdes_get_rx_cmp_data(aapl, addr);
#if 1

    Avago_spico_int_t ints[] =
    {
        {0x001c, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x0018, 0x0004,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL},
        {0x001a, 0x0000,  0, AVAGO_SPICO_INT_ALL}
    };

    AAPL_SERDES_MEM_LOCK;
    if( avago_spico_int_array(aapl, addr, AAPL_ARRAY_LENGTH(ints), ints) == 0 )
    {
        int i;
        for( i = 0; i < 4; i++ )
        {
            data[i]  =  ints[i*2+2].ret & 0x03ff;
            data[i] |= (ints[i*2+3].ret & 0x03ff) << 10;
        }
    }

#else
    int i;
    AAPL_SERDES_MEM_LOCK;
    avago_spico_int_check(aapl, __func__,__LINE__, addr, 0x001c, 0x0000);
    avago_spico_int_check(aapl, __func__,__LINE__, addr, 0x0018, 0x0004);

    for( i = 0; i < 4; i++ )
    {
        data[i]  =  avago_spico_int(aapl, addr, 0x001a, 0x0000) & 0x3ff;
        data[i] |= (avago_spico_int(aapl, addr, 0x001a, 0x0000) & 0x3ff) << 10;
    }
#endif
    AAPL_SERDES_MEM_UNLOCK;
    avago_serdes_set_rx_cmp_data(aapl, addr, cmp_data);
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
    if( aapl_get_lsb_rev(aapl,addr) < 3 && aapl_get_process_id(aapl, addr) != AVAGO_PROCESS_E )
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
    else if( sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_P1 || sdrev == AAPL_SDREV_PON || sdrev == AAPL_SDREV_D6_07 )
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
    if( (mode & 0x0170) == 0x0150 ) mode = AVAGO_SERDES_RX_CMP_MODE_XOR;
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

#if 1
    if( aapl_get_ip_type(aapl,addr) == AVAGO_M4 )
    {
        if( mode == AVAGO_SERDES_RX_CMP_MODE_XOR )
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x6d, 1<<11, 1<<11);
            new_mode |= 0x0150;
        }
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x6d, 0<<11, 1<<11);
    }
#endif

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
    int reg_preinv = 0, preinv_bit = 0;
    Avago_serdes_mem_type_t mem_type = AVAGO_LSB;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    default:
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_D6_07:
    case AAPL_SDREV_PON:
    case AAPL_SDREV_16:  reg_invert = 0x24; invert_bit = 1<<0; break;
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_CM4: reg_invert = 0x2b; invert_bit = 1<<2;
                         reg_preinv = 0x25; preinv_bit = 1<<5; break;
    case AAPL_SDREV_P1:  reg_invert = 0xec; invert_bit = 1<<0; break;
    case AAPL_SDREV_D6:  reg_invert = 0x60; invert_bit = 1<<3; mem_type = AVAGO_ESB; break;
    }

    invert = !!(avago_serdes_mem_rd(aapl,addr,mem_type,reg_invert) & invert_bit);
    if( reg_preinv ) invert |= !!(avago_serdes_mem_rd(aapl,addr,mem_type,reg_preinv) & preinv_bit);
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
    case AAPL_SDREV_D6_07: reg_addr =0x43e; reg_bit = 1<<1; break;
    case AAPL_SDREV_PON:
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
    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x08, int_data) ? 0 : -1;
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
        case AAPL_SDREV_PON:
        case AAPL_SDREV_16:   reg_clk_misc =  0xf0; clk_shift = 3; reg_pll_misc =  0xd1; break;
        case AAPL_SDREV_D6_07:reg_clk_misc = 0x462; clk_shift = 3; reg_pll_misc = 0x42b; break;
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
        int reg_rxdiv, pcsdiv_shift, mode66_bit, rev = 1;
        switch( sdrev )
        {
        default:
        case AAPL_SDREV_OM4:    reg_rxdiv = 0xc0; rev = 3; break;
        case AAPL_SDREV_D6_07:  reg_rxdiv =0x418; rev = 2; break;
        case AAPL_SDREV_CM4_16:
            if( aapl_get_ip_rev(aapl, addr) >= 0x22 )
                              { reg_rxdiv = 0xfb; rev = 2; }
            else
                              { reg_rxdiv = 0xc1; rev = 2; }
            break;
        case AAPL_SDREV_CM4:
        case AAPL_SDREV_P1:   return bits;
        case AAPL_SDREV_HVD6: return bits;
        case AAPL_SDREV_PON:
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

/** @cond INTERNAL */

int aapl_get_pcs_architecture(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl,addr) )
    {
    case AVAGO_P1: return 0;
    case AVAGO_SERDES:
    {
        int ip_rev;
        Avago_process_id_t process = aapl_get_process_id(aapl, addr);
        if( process == AVAGO_PROCESS_F )
        {
            ip_rev = aapl_get_sdrev(aapl,addr);
            if( ip_rev != AAPL_SDREV_HVD6) return 1;
        }
        if( process == AVAGO_PROCESS_B )
        {
            ip_rev = aapl_get_ip_rev(aapl,addr);
            if( ip_rev <= 0x16 || ip_rev == 0x19 || ip_rev == 0x1a ) return 1;
        }
        if( process == AVAGO_PROCESS_E )
            return 2;
        break;
    }
    case AVAGO_M4:
    default: break;
    }
    return 2;
}

/** @endcond */


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
    int pcs_architecture, read_mask, write_mask;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, spico_clk=%s\n",aapl_addr_to_str(addr),aapl_spico_clk_to_str(src));

    if( aapl_get_ip_type(aapl,addr) == AVAGO_P1 )
        addr = avago_make_sbus_lane_addr(addr, AVAGO_ADDR_QUAD_ALL);

    pcs_architecture = aapl_get_pcs_architecture(aapl,addr);
    read_mask  = pcs_architecture == 2 ? 0x00f0 : 0x0ff0;
    write_mask = aapl_serdes_get_int30_bits(aapl, addr, read_mask) | (src & 7);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x30, write_mask);
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
    int pcs_architecture = aapl_get_pcs_architecture(aapl,addr);
    int read_mask = pcs_architecture == 2 ? 0x000f : ~0x00f0;
    int write_mask = aapl_serdes_get_int30_bits(aapl, addr, read_mask) | src | 0x0008;
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, tx_pll_clk=%s\n",aapl_addr_to_str(addr),aapl_pll_clk_to_str(src));

    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x30, write_mask);
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

    if( !aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1046) )
        return ret;

    if( sdrev == AAPL_SDREV_P1 )
    {
        ret = !((avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xa0) >> 7) & 1);
        if( ret )
        {
            int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xa1);
            ret = (val & 2) == 2;
        }
    }
    else if( sdrev == AAPL_SDREV_D6_07 )
    {
        int eid_pd = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x496);
        if( (eid_pd & 0xf) == 0 )
        {
            int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x426);
            ret = ((val>>9) & 0x01) == 0x01;
        }
    }
    else if( sdrev != AAPL_SDREV_D6 && sdrev != AAPL_SDREV_HVD6 )
    {
        int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xc4);
        ret = ((val>>8) & 0x03) == 0x02;
    }
    else
    {
        int val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x80);
        ret = (val & 0x03) == 0x02;
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
        int sdrev = aapl_get_sdrev(aapl,addr);
        switch( sdrev )
        {
        default:
        case AAPL_SDREV_HVD6:
        case AAPL_SDREV_D6:   reg = 0x80; shift = 2; mask = 0x0f;
                              if( sdrev == AAPL_SDREV_HVD6 && aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B ) mask = 0x1f;
                              break;
        case AAPL_SDREV_CM4:  reg = 0xff; shift = 2; mask = 0x0f; break;
        case AAPL_SDREV_D6_07:reg = 0x426; shift = 0; mask = 0x1ff; break;
        case AAPL_SDREV_PON:
        case AAPL_SDREV_CM4_16:
        case AAPL_SDREV_16:   reg = 0xc4; shift = 0; mask = 0xff; break;
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
 **          Resets the detector if reset is enabled and signal loss was
 **          detected so can tell if a signal is once again present.
 ** @return  Returns TRUE if no signal loss was detected on any SerDes.
 ** @return  Returns FALSE if signal loss was detected since last check.
 **          Examine the results fields for individual SerDes status.
 ** @see     avago_serdes_initialize_signal_ok().
 **/
BOOL avago_parallel_serdes_get_signal_ok(
    Aapl_t *aapl,            /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list, /**< [in] Device address number. */
    BOOL reset)              /**< [in] Clear signal loss sticky bit if set. */
{
    Avago_addr_t *addr_struct;
    uint addr = avago_struct_to_addr(addr_list);
    int reg_serdes_rdy = (aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1) ? 0xee : 0x26;
    BOOL combined_sig_ok = TRUE;

    avago_parallel_serdes_mem_rd(aapl, addr_list, AVAGO_LSB, reg_serdes_rdy);

    for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
    {
        uint addr = avago_struct_to_addr(addr_struct);
        BOOL sig_ok = (addr_struct->results & 0x0010) ? 0 : 1;
        combined_sig_ok &= sig_ok;
        if( reset && !sig_ok )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, reg_serdes_rdy, 0, 0x0010);
        addr_struct->results = sig_ok;
        AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, sig_ok=%s, reset=%d\n", aapl_addr_to_str(addr), aapl_bool_to_str(sig_ok), reset);
    }
    return combined_sig_ok;
}

/** @brief   Reads and resets the signal_ok_deasserted signal.
 ** @details Reads a sticky signal lost detector and returns whether any
 **          loss was detected since the last call to this function.
 **          Resets the detector if reset is enabled and signal loss was
 **          detected so can tell if a signal is once again present.
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

/** @brief   Enables or disables the RX Idle Detector to aide detecting signal loss.
 ** @details Call this function once to initialize the idle detector.
 **          Then call avago_serdes_get_signal_ok() to check if signal loss is detected.
 **          Functional for firmware 0x1046 and newer.  No-op on older versions.
 **          Call with a threshold of -1 to disable the EI detector.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_get_signal_ok(), avago_serdes_get_signal_ok_threshold().
 **/
int avago_parallel_serdes_initialize_signal_ok(
    Aapl_t *aapl,            /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_list, /**< [in] Device address number. */
    int threshold)           /**< [in] Threshold for signal OK (0-15). */
{
    int return_code = aapl->return_code;
    uint addr = avago_struct_to_addr(addr_list);
    int ip_rev = aapl_get_ip_rev(aapl, addr);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, threshold %d\n", aapl_addr_to_str(addr), threshold);

    if( threshold == -1)
        avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x20, 0x0);
    else if( ((ip_rev >= 0x0a && ip_rev <= 0x0c) || ip_rev == 0x1a) && aapl_get_ip_type(aapl,addr) == AVAGO_SERDES && aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B )
        ;
    else if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1046) )
    {
        int sdrev = aapl_get_sdrev(aapl, addr);
        int mask = ((sdrev == AAPL_SDREV_HVD6) && (aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_B) ) ? 0x1f :
                    (sdrev == AAPL_SDREV_PON)                                                          ? 0xff : 0xf;
        avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x20, 0x20);
        avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x20, 0x40 | ((threshold & mask)<<8));
    }
    avago_parallel_serdes_get_signal_ok(aapl, addr_list, TRUE);
    return return_code == aapl->return_code ? 0 : -1;
}


/** @brief Return electrical idle (EI) limits for SerDes. */
void avago_serdes_get_ei_limits(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    int *ei_min,    /** [out] EI minimum */
    int *ei_max)    /** [out] EI maximum */
{
    int fwbld  = aapl_get_firmware_build(aapl, addr);
    Avago_process_id_t process = aapl_get_process_id(aapl, addr);
    *ei_min = 0x00;
    *ei_max = 0x0f;
    if( process == AVAGO_PROCESS_B )
    {
        *ei_max = 0xff;
        if(      fwbld == 0x2147 ) *ei_max = 0x01f;
        else if( fwbld == 0x204D ) *ei_max = 0x00f;
        else if( aapl_get_ip_type(aapl, addr) == AVAGO_M4 )
            *ei_max = 0xf;
        else
        {
            int sdrev = aapl_get_sdrev(aapl, addr);
            if( sdrev == AAPL_SDREV_HVD6 ) *ei_max = 0x1f;
        }
    }
    else if( process == AVAGO_PROCESS_E )
    {
        *ei_min = 11;
        *ei_max = 57;
    }
}

/** @brief   Enables or disables the RX Idle Detector to aide detecting signal loss.
 ** @details Call this function once to initialize the idle detector.
 **          Then call avago_serdes_get_signal_ok() to check if signal loss is detected.
 **          Functional for firmware 0x1046 and newer.  No-op on older versions.
 **          Call with a threshold of -1 to disable the EI detector.
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
    Avago_process_id_t process_id = aapl_get_process_id(aapl, addr);
    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, threshold %d\n", aapl_addr_to_str(addr), threshold);

    if( threshold == -1)
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x0);
    else if( process_id == AVAGO_PROCESS_E )
    {
        int min, max;
        avago_serdes_get_ei_limits(aapl, addr, &min, &max);
        if(      threshold > max ) threshold = max;
        else if( threshold < min ) threshold = min;
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x20);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x40 | (threshold<<7));
    }
    else if( ((ip_rev >= 0x0a && ip_rev <= 0x0c) || ip_rev == 0x1a) && aapl_get_ip_type(aapl,addr) == AVAGO_SERDES && process_id == AVAGO_PROCESS_B )
        ;
    else if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1046) )
    {
        int min  = 0x00;
        int mask = 0x0f;
        avago_serdes_get_ei_limits(aapl, addr, &min, &mask);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x20);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, 0x40 | ((threshold & mask)<<8));
    }
    avago_serdes_get_signal_ok(aapl, addr, TRUE);
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrives Electrical Idle calibration status.
 ** @details Elecrical idle calibration is supported for PON and 7nm D6 SerDes.
 ** @return  On success, returns status.
 ** @return  On failure, returns -1.
 ** @see     avago_serdes_launch_ei_calibration().
 **/
int avago_serdes_get_ei_calibration_status(
    Aapl_t *aapl,    /**< [in] Pointer to Aapl_t structure. */
    uint addr)       /**< [in] Device address number. */
{
    int return_code = aapl->return_code;
    int rc = 0;
    int sdrev = aapl_get_sdrev(aapl, addr);
    if( sdrev == AAPL_SDREV_PON || sdrev == AAPL_SDREV_D6_07 )
    {
        rc = avago_spico_int(aapl, addr, 0x20, ((1<<6) | (1<<14) | (1<<15)));
        aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, Electrical Idle calibration status: %X.\n",
                        aapl_addr_to_str(addr), rc);
    }

    return return_code == aapl->return_code ? rc : -1;
}

/** @brief   Writes Electrical Idle calibration threshold value to ESB register.
 ** @details Elecrical idle calibration is supported for PON and 7nm D6 SerDes.
 ** @return  On success, returns 0.
 ** @return  On failure, returns -1.
 ** @see     avago_serdes_get_ei_calibration_threshold().
 **/
int avago_serdes_set_ei_calibration_threshold(
    Aapl_t *aapl,    /**< [in] Pointer to Aapl_t structure. */
    uint addr,       /**< [in] Device address number. */
    int threshold)   /**< [in] New EI calibration threshold value to set */
{
    int return_code = aapl->return_code;
    int reg_eidet_ctl2, bits;

    switch( aapl_get_sdrev(aapl, addr) )
    {
    case AAPL_SDREV_D6_07: reg_eidet_ctl2 = 0x427; bits = 0xff; break;
    case AAPL_SDREV_PON:   reg_eidet_ctl2 = 0xc1; bits = 0xff; break;
    default:               reg_eidet_ctl2 = 0; return 0;
    }

    avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, reg_eidet_ctl2, (threshold & bits), bits);
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, Set Electrical idle calibration threshold value: %d.\n",
                    aapl_addr_to_str(addr), threshold);

    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrives Electrical Idle calibration threshold value from ESB register.
 ** @details Elecrical idle calibration is supported for PON and 7nm D6 SerDes.
 ** @return  On success, returns threshold.
 ** @return  On failure, returns -1.
 ** @see     avago_serdes_set_ei_calibration_threshold().
 **/
int avago_serdes_get_ei_calibration_threshold(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    int return_code = aapl->return_code;
    int threshold = 0;
    int reg_eidet_ctl2, bits;

    switch( aapl_get_sdrev(aapl, addr) )
    {
    case AAPL_SDREV_D6_07: reg_eidet_ctl2 = 0x427; bits = 0xff; break;
    case AAPL_SDREV_PON:   reg_eidet_ctl2 = 0xc1; bits = 0xff; break;
    default:               reg_eidet_ctl2 = 0; return 0;
    }

    threshold = (avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg_eidet_ctl2)) & bits;
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, Configured Electrical idle calibration threshold value: %d.\n",
                    aapl_addr_to_str(addr), threshold);

    return return_code == aapl->return_code ? threshold : -1;
}

/** @brief   Launches Electrical Idle calibration.
 ** @details Elecrical idle calibration is supported for PON and 7nm D6 SerDes.
 ** @return  On success, returns 0.
 ** @return  On failure, returns -1.
 ** @see     avago_serdes_get_ei_calibration_status().
 **/
int avago_serdes_launch_ei_calibration(
    Aapl_t *aapl,     /**< [in] Pointer to Aapl_t structure. */
    uint addr,        /**< [in] Device address number. */
    BOOL ei_cal)      /**< [in] New EI calibration state */
{
    int return_code = aapl->return_code;
    int sdrev = aapl_get_sdrev(aapl, addr);
    if( sdrev == AAPL_SDREV_PON || sdrev == AAPL_SDREV_D6_07 )
    {
        uint data = 0;
        if( ei_cal ) data |= (1<<6) | (1<<13) | (1<<14);
        else         data |= (1<<6) | (1<<14);
        aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, Set Electrical idle calibration: %s.\n",
                        aapl_addr_to_str(addr), aapl_bool_to_str(ei_cal));
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x20, data);
    }

    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Retrieves selected rate for Rx.
 ** @details Rate selection is only supprted for PON SerDes.
 **          Function reports failure for other SerDes.
 ** @return On success, returns rate selection value(0 = Quarter rate, 1 = Full rate, 2 = Eighth rate, 3 = Half rate).
 ** @return On failure, decrements aapl->return_code and returns -1.
 **/
int avago_serdes_pon_get_rate_select(
    Aapl_t *aapl,  /**< [in] Pointer to Aapl_t structure. */
    uint addr)     /**< [in] Device address number. */
{
    if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_PON )
    {
        uint rate_sel = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x146) & 0x3;
        aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, configured rate selection: %d.\n",
                              aapl_addr_to_str(addr), rate_sel);
        return rate_sel;
    }
    else
        return aapl_fail(aapl, __func__, __LINE__, "Rate selection is only supported for PON SerDes.\n");
}

/** @brief   Selects rate for Rx.
 ** @details Rate selection is only supported for PON SerDes.
 **          Function reports failure for other SerDes.
 ** @return On success, returns 0.
 ** @return On failure, decrements aapl->return_code and returns -1.
 **/
int avago_serdes_pon_set_rate_select(
    Aapl_t *aapl,    /**< [in] Pointer to Aapl_t structure. */
    uint addr,       /**< [in] Device address number. */
    uint rate_sel)   /**< [in] New rate selection value. */
{
    int return_code = aapl->return_code;

    if( aapl_get_sdrev(aapl, addr) != AAPL_SDREV_PON )
        return aapl_fail(aapl, __func__, __LINE__, "Rate selection is supported only for PON SerDes.\n");

    avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x146, rate_sel & 0x03, 0x03);

    return aapl->return_code == return_code ? 0 : -1;
}

/** @brief   Checks whether burst mode is enabled or not.
 ** @details Burst mode is only supported for PON SerDes.
 ** @return  Returns TRUE if burst mode is enabled.
 ** @return  Returns FALSE if burst mode is disabled or not applicable.
 **/
BOOL avago_serdes_get_burst_mode(
    Aapl_t *aapl,    /**< [in] Pointer to Aapl_t structure. */
    uint addr)       /**< [in] Device address number. */
{
    if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_PON )
    {
        BOOL burst_mode = (avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x146) & 0x08 ) >> 3;
        AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, burst_mode = %s\n", aapl_addr_to_str(addr), aapl_bool_to_str(burst_mode));
        return burst_mode;
    }
    return FALSE;
}

/** @brief   Reads frequency lock time of Rx PLL from ESB register.
 ** @return  Returns lock time.
 **/
uint avago_serdes_get_frequency_lock_time(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    uint lock_time = 0;
    if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_PON )
        lock_time = (avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x149) & 0x7ffe);

    AAPL_LOG_PRINT5(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, lock_time = %d\n", aapl_addr_to_str(addr), lock_time);
    return lock_time;
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

    err_count = avago_serdes_mem_rd(aapl, addr, AVAGO_BIG_REG_32, 3);

    if( reset )
        avago_serdes_error_reset(aapl, addr);

    rc = return_code == aapl->return_code ? err_count : ~0U;
    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, reset=%d, errors = %u.\n", aapl_addr_to_str(addr), reset, rc);
    return rc;
}

/** @brief   Sets the SerDes SPICO error timer to a specified value.
 ** @details Range is 20 * (1..2^30).  Values too low or high are
 **          silently clipped to the edge of the range.
 **          Note that the real time elapsed depends on RX rate.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_serdes_set_error_timer(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    bigint dwell_bits)  /**< [in] Number of RX bits for which to count errors. */
{
    int return_code = aapl->return_code;
    int bits_per_ui = avago_serdes_get_rx_line_encoding(aapl, addr) ? 2 : 1;
    int rx_clock_divider = avago_serdes_get_rx_register_clock(aapl,addr);
    bigint dwell_words = dwell_bits / rx_clock_divider / bits_per_ui;
    int int_load_lo, int_load_hi;
    const bigint dwell_limit = (bigint)0x3fffffff * rx_clock_divider * bits_per_ui;

    if( dwell_bits > dwell_limit )
        return aapl_fail(aapl, __func__, __LINE__, "Requested dwell bits exceeds hardware capability: requested = %s, max = %s\n", aapl_bigint_to_str(dwell_bits), aapl_bigint_to_str(dwell_limit));

    if( dwell_words == 0 && dwell_bits > 0 ) dwell_words = 1;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1: int_load_lo = 0x2003; int_load_hi = 0x2083; break;
    default:
    case AAPL_SDREV_16: int_load_lo = 0x0103; int_load_hi = 0x0203; break;
    }

    avago_spico_int_check(aapl,__func__,__LINE__,addr, int_load_lo,  dwell_words        & 0xffff);
    avago_spico_int_check(aapl,__func__,__LINE__,addr, int_load_hi, (dwell_words >> 16) & 0x3fff);

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, dwell_bits = %s, dwell_words = %s, rx_clock_divider = %d, register = %d.\n",
        aapl_addr_to_str(addr), aapl_bigint_to_str(dwell_bits), aapl_bigint_to_str(dwell_words), rx_clock_divider,
        avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x13) | avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x14) << 16);

    return (return_code == aapl->return_code) ? 0 : -1;
}

/** @brief   Starts a comparison of the Rx data stream with the Rx comparator selection.
 ** @details Starts counting errors for the given number of bits.
 ** @details Note: dwell_bits will be truncated to a multiple of the Rx
 **          register clock value. See avago_serdes_get_rx_register_clock().
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 ** @see     avago_serdes_count_errors().
 **/
BOOL avago_serdes_count_errors_start(
    Aapl_t *aapl,      /**< [in] Pointer to Aapl_t structure. */
    uint addr,         /**< [in] Device address number. */
    bigint dwell_bits) /**< [in] Number of bits over which to count errors. */
{
    int select_msb_lsb;
    int ret = 0 == avago_serdes_set_error_timer(aapl, addr, dwell_bits);
    Avago_ip_type_t ip_type = aapl_get_ip_type(aapl, addr);
    uint reg_error_count = (ip_type == AVAGO_P1) ? 0xd7 : 0x0d;
    uint reg_error_timer = (ip_type == AVAGO_P1) ? 0xdc : 0x12;

    if( !ret )
        return FALSE;

    if( dwell_bits == 0 )
        return aapl_fail(aapl, __func__, __LINE__,"Invalid dwell_bits value (%s); positive value required.\n", aapl_bigint_to_str(dwell_bits)), FALSE;

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, reg_error_timer, 2);

    select_msb_lsb = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_error_count) & 0x3008;
    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, reg_error_count, select_msb_lsb | 0x0301);
    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, reg_error_count, select_msb_lsb | 0x0300);

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, reg_error_timer, 1);

    return ret;
}

/** @brief   Gets error count after error comparison completes.
 ** @details Waits for the comparison to complete.
 ** @return  On success, returns the error count.
 ** @return  On failure, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_count_errors().
 **/
int avago_serdes_count_errors_wait(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int return_code = aapl->return_code;

    if( avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x1d, 0) )
    {
        uint errors = avago_serdes_get_errors(aapl, addr, AVAGO_LSB, FALSE);

        avago_serdes_set_error_timer(aapl, addr, 0);

        if( return_code == aapl->return_code )
            return errors;
    }
    return -1;
}

/** @brief   Performs a comparison of the Rx data stream with the Rx comparator selection
 **          on all SerDes in the address list in parallel.
 ** @details Counts errors for the given number of bits on each of the addressed SerDes.
 ** @details Note: the error counter is left running after this call returns.
 ** @details Note: dwell_bits will be truncated to a multiple of the Rx
 **          register clock value. See avago_serdes_get_rx_register_clock().
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 ** @return  Individual error counts are stored into the bigint_results field of the address list,
 **          which is a 32 bit unsigned value.  For large dwells with lots of errors, the
 **          resulting BER can be misleading.
 ** @see     avago_serdes_count_errors().
 **/
BOOL avago_serdes_parallel_count_errors(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *list, /**< [in] Device address list. */
    bigint dwell_bits)  /**< [in] Number of bits over which to count errors. */
{
    int return_code = aapl->return_code;
    int bits_per_ui = 4;
    int register_clock = 40;
    bigint max_dwell = (0xffffffffU / 160) * 160;
    bigint this_dwell = MIN(dwell_bits, max_dwell);
    bigint dwell_limit;
    Avago_addr_t *ptr;

    int original_timeout = aapl->serdes_int_timeout;
    aapl->serdes_int_timeout *= register_clock;

    for( ptr = list; ptr != NULL; ptr = ptr->next )
    {
        uint addr = avago_struct_to_addr(ptr);
        ptr->bigint_results = 0;
        if( !avago_serdes_count_errors_start(aapl, addr, this_dwell) )
            break;
        if( bits_per_ui == 2 || !avago_serdes_get_rx_line_encoding(aapl, addr) )
            bits_per_ui = 2;
        if( register_clock > avago_serdes_get_rx_register_clock(aapl, addr) )
            register_clock = avago_serdes_get_rx_register_clock(aapl, addr);
    }
    dwell_bits -= this_dwell;

    dwell_limit = (bigint)0x3fffffff * register_clock * bits_per_ui;

    while( dwell_bits > 0 )
    {
        int errors = 0;
        int max_error_count = 0;
        this_dwell = MIN(dwell_bits, 2000000000);

        for( ptr = list; ptr != NULL; ptr = ptr->next )
        {
            uint addr = avago_struct_to_addr(ptr);
            errors = avago_serdes_count_errors_wait(aapl, addr);
            if( errors > max_error_count )
                max_error_count = errors;
            else if( errors < 0 )
                break;
            avago_serdes_count_errors_start(aapl, addr, this_dwell);
            ptr->bigint_results += errors;
        }

        if( errors < 0 )
            break;

        dwell_bits -= this_dwell;

        while( max_dwell < dwell_limit && max_error_count < 1000000000 )
        {
            max_dwell *= 2;
            errors *= 2;
            if( max_dwell > dwell_limit )
                max_dwell = dwell_limit;
        }
    }

    for( ptr = list; ptr != NULL; ptr = ptr->next )
    {
        uint addr = avago_struct_to_addr(ptr);
        int errors = avago_serdes_count_errors_wait(aapl, addr);
        if( errors < 0 )
            break;
        ptr->bigint_results += errors;
    }

    aapl->serdes_int_timeout = original_timeout;
    return return_code == aapl->return_code;
}

/** @brief   Performs a comparison of the Rx data stream with the Rx comparator selection.
 ** @details Counts errors for the given number of bits.
 ** @details Note: the error counter is left running after this call returns.
 ** @details Note: dwell_bits will be truncated to a multiple of the Rx
 **          register clock value. See avago_serdes_get_rx_register_clock().
 ** @return  On success, returns the error count.
 ** @return  On failure, decrements aapl->return_code and returns -1.
 ** @see     avago_serdes_parallel_count_errors(), avago_serdes_count_errors_start(), avago_serdes_count_errors_wait().
 **/
bigint avago_serdes_count_errors(
    Aapl_t *aapl,      /**< [in] Pointer to Aapl_t structure. */
    uint addr,         /**< [in] Device address number. */
    bigint dwell_bits) /**< [in] Number of bits over which to count errors. */
{
    Avago_addr_t addr_struct;
    avago_addr_to_struct(addr,&addr_struct);
    if( avago_serdes_parallel_count_errors(aapl, &addr_struct, dwell_bits) )
        return addr_struct.bigint_results;
    return -1;
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

/** @brief   Starts the auxiliary PRBS error counter counting from zero.
 ** @details This action configures and starts the error counter from zero.
 ** @see     avago_serdes_aux_counter_disable(), avago_serdes_aux_counter_read().
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_aux_counter_start(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    int return_code = aapl->return_code;

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x41, 0x8540);

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x40, 0x0580);

    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x18, 0x20, 0x23);

    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x0c, 0x23, 0x23);

    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x2a, 0x0010, 0x0010);
    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x2a, 0x0000, 0x0010);

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x41, 0x8541);
    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x41, 0x8540);

    return return_code == aapl->return_code;
}

/** @brief   Reads the auxiliary PRBS error counter.
 ** @details The error counter is read asynchronously to avoid missing any
 **          errors, but done in a way that the values returned are guaranteed
 **          to be monotonically non-decreasing and all values under 2^16 are
 **          guaranteed to be precise.  The error counter is 32 bits total.
 ** @see     avago_serdes_aux_counter_disable(), avago_serdes_aux_counter_start().
 ** @return  On success, returns the error count.
 ** @return  On failure, returns ~0 and decrements aapl->return_code.
 **/
uint avago_serdes_aux_counter_read(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    int return_code = aapl->return_code;
    int count_hi_before = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x47);
    int count_lo        = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x46);
    int count_hi_after  = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, 0x47);

    if( return_code != aapl->return_code )
        return ~0;

    if( count_hi_before != count_hi_after )
        count_lo = 0;

    return count_hi_after << 16 | count_lo;
}

/** @brief   Disables the auxiliary PRBS error counter and puts it into a low
 **          power state.
 ** @details While in this state, the unchanging error count can be read.
 ** @see     avago_serdes_aux_counter_read(), avago_serdes_aux_counter_start().
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_aux_counter_disable(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    int return_code = aapl->return_code;

    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x0c, 0x00, 0x20);

    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x18, 0x00, 0x20);

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x40, 0x0700);

    avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x41, 0x0700);

    avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x2a, 0x0010, 0x0010);

    return return_code == aapl->return_code;
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
    config->burst_mode   = FALSE;
    config->rate_sel     = 1; /**< 0 = Quarter rate, 1 = Full rate, 2 = Eighth rate, 3 = Half rate */

    config->init_tx      = TRUE;
    config->tx_divider   = 10;
    config->tx_width     = 0;
    config->tx_encoding  = AVAGO_SERDES_PAM4;
    config->tx_phase_cal = FALSE;
    config->refclk_sync_master = TRUE;
    config->tx_output_en = TRUE;
    config->tx_datapath.mask |= 0x0f;
    config->tx_datapath.polarity_invert = FALSE;
    config->tx_datapath.gray_enable = TRUE;
    config->tx_datapath.precode_enable = FALSE;
    config->tx_datapath.swizzle_enable = TRUE;

    config->init_rx      = TRUE;
    config->rx_divider   = 10;
    config->rx_width     = 0;
    config->rx_encoding  = AVAGO_SERDES_PAM4;
    config->signal_ok_en = TRUE;
    config->signal_ok_threshold = 0x0;
    config->rx_datapath.mask |= 0x0f;
    config->rx_datapath.polarity_invert = FALSE;
    config->rx_datapath.gray_enable = TRUE;
    config->rx_datapath.precode_enable = FALSE;
    config->rx_datapath.swizzle_enable = TRUE;

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
    else if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_PON )
        width = 16;
    return width;
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
    int errors = -1;
    Avago_serdes_init_config_t *config = avago_serdes_init_config_construct(aapl);
    if( config )
    {
        config->tx_divider = divider;
        config->rx_divider = divider;
        errors = avago_serdes_init(aapl, addr, config);
        avago_serdes_init_config_destruct(aapl, config);
    }
    return errors;
}

static uint pon_rate_sel_to_mask(uint rate_sel)
{
    uint mask_table[4] = {0x0200, 0x0000, 0x0300, 0x0100 };
    return mask_table[rate_sel&3];
}

/** @brief   Configures and calibrates a SerDes.
 ** @details Call this to initialize a SerDes.
 ** @return  0 on success, aapl->return_code (< 0) on error.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init_config_destruct(), avago_serdes_init_quick(), avago_parallel_serdes_init().
 **/
int avago_serdes_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    Avago_addr_t addr_struct;
    BOOL tx_en = FALSE, rx_en = FALSE, tx_output_en = FALSE;
    uint errors;
    int sdrev = aapl_get_sdrev(aapl, addr);
    uint rate_sel = 0;
    uint extra = 0;

    avago_addr_to_struct(addr, &addr_struct);

    if (aapl_check_broadcast_address(aapl, addr, __func__, __LINE__, TRUE)) return -1;
    if( !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) ||
        !aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F) )
        return -1;

    if( sdrev == AAPL_SDREV_PON )
    {
        if( config->rate_sel > 3 )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: Invalid rate_sel value: %u.  Valid range [0..3].\n", aapl_addr_to_str(addr), config->rate_sel);
        rate_sel = pon_rate_sel_to_mask(config->rate_sel);
        if( config->burst_mode )
            extra = 1<<8;
    }

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s\n",aapl_addr_to_str(addr));
    config->fail_code = 0;
    if( config->sbus_reset  ) avago_sbus_reset(aapl, addr, 0);
    if( config->spico_reset ) avago_spico_reset(aapl, addr);

    if( sdrev == AAPL_SDREV_P1 )
    {
        if( addr_struct.lane < 8 )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes P1 requires quad or chip level initialization.\n", aapl_addr_to_str(addr));

        if( config->tx_divider != config->rx_divider )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes P1 requires Tx and Rx dividers to match.\n", aapl_addr_to_str(addr));

        if( addr_struct.lane == AVAGO_ADDR_QUAD_ALL && !aapl_is_octal_p1(aapl, addr) )
        {
            addr = avago_make_sbus_lane_addr(addr, AVAGO_ADDR_QUAD_LOW);
            addr_struct.lane = AVAGO_ADDR_QUAD_LOW;
        }
    }

    aapl_set_spico_running_flag(aapl, addr, 1);

    if( !config->skip_crc && !avago_spico_crc(aapl, addr) )
        return aapl_fail(aapl, __func__, __LINE__, "SerDes %s failed CRC check.\n", aapl_addr_to_str(addr));

    if( !config->sbus_reset )
    {
        avago_serdes_get_tx_rx_ready(aapl, addr, &tx_en, &rx_en);
        tx_output_en = avago_serdes_get_tx_output_enable(aapl, addr);
    }

    avago_serdes_set_tx_rx_enable(aapl, addr, FALSE, FALSE, FALSE);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x11, 0x00);

    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0b, config->tx_phase_cal ? 1 : 0);

    if( config->tx_divider == config->rx_divider && rate_sel == 0 )
    {
        int div_val = (config->tx_divider & 0xff) | (1 << 15);
        if (config->refclk_sync_master) div_val |= 1<<12;
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x05, div_val);
    }
    else
    {
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x05, (config->tx_divider & 0xff) | (config->refclk_sync_master ? 1<<12 : 0));
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x06, rate_sel | (config->rx_divider & 0xff));
    }

    if( config->tx_width == 0 ) config->tx_width = avago_serdes_get_default_width(aapl, addr);
    if( config->rx_width == 0 ) config->rx_width = avago_serdes_get_default_width(aapl, addr);
    avago_serdes_set_tx_rx_width_pam(aapl, addr, config->tx_width, config->rx_width, config->tx_encoding, config->rx_encoding);

    if( -1 == avago_parallel_serdes_set_tx_rx_enable(aapl, &addr_struct, config->init_tx | tx_en, config->init_rx | rx_en, config->tx_output_en | tx_output_en, extra) )
        config->fail_code |= 0x4;

    if( config->signal_ok_en && sdrev != AAPL_SDREV_P1 )
        avago_serdes_initialize_signal_ok(aapl,addr,config->signal_ok_threshold);

    if( config->init_mode == AVAGO_INIT_ONLY )
    {
        avago_serdes_set_tx_datapath(aapl, addr, &(config->tx_datapath));
        avago_serdes_set_rx_datapath(aapl, addr, &(config->rx_datapath));

        aapl_log_printf(aapl, AVAGO_DEBUG1, 0, 0, "\n");
        return 0;
    }
    avago_serdes_set_rx_input_loopback(aapl, addr, TRUE);
    if( config->init_tx )
        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_PRBS31);
    if( config->init_rx )
    {
        if( config->init_tx && sdrev == AAPL_SDREV_OM4 && aapl_get_jtag_idcode(aapl, 0) == 0x0973957f )
            avago_serdes_set_tx_invert(aapl, addr, TRUE);
        if( config->init_tx && (sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 || (sdrev == AAPL_SDREV_OM4 && config->rx_encoding == AVAGO_SERDES_PAM4)) )
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

    avago_serdes_set_tx_datapath(aapl, addr, &(config->tx_datapath));
    avago_serdes_set_rx_datapath(aapl, addr, &(config->rx_datapath));

    if( config->init_mode == AVAGO_PRBS31_ELB    || config->init_mode == AVAGO_CORE_DATA_ELB )
    {
        avago_serdes_set_rx_input_loopback(aapl, addr, FALSE);
    }
    if( config->init_mode == AVAGO_CORE_DATA_ILB || config->init_mode == AVAGO_CORE_DATA_ELB )
    {
        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_CORE);
        avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_OFF);
    }
    avago_serdes_error_reset(aapl, addr);

    aapl_log_printf(aapl, AVAGO_DEBUG1, 0, 0, " Errors in ILB: %u.\n", errors);

    if( errors )
    {
        aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,
            "%u PRBS errors detected during ILB check of SerDes %s during serdes_init to div %d. Use this SerDes with caution.\n", errors, aapl_addr_to_str(addr), config->tx_divider);
        config->fail_code |= 0x8;
    }
    return (int)errors;
}

#if 0
/** @brief   Configures and calibrates a SerDes.
 ** @details Call this to initialize a SerDes.
 ** @return  0 on success, aapl->return_code (< 0) on error.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_base_init(), avago_serdes_tx_init(), avago_serdes_rx_init().
 **/
int avago_serdes_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    int errors;

    avago_serdes_base_init(aapl, addr, config);
    errors = avago_serdes_loopback_test(aapl, addr, config);
    avago_serdes_tx_init(aapl, addr, config);
    avago_serdes_rx_init(aapl, addr, config);

    return errors;
}
#endif

/** @brief   Initializes a SerDes as a whole after Download.
 ** @details Performs SBus reset, SPICO reset and a CRC check.
 **          Must call this once after upload and before any call to
 **          avago_serdes_rx_init() or avago_serdes_tx_init().
 ** @return  0 on success, -1 and decrements aapl->return_code on error.
 ** @see     avago_serdes_init(), avago_serdes_rx_init(), avago_serdes_tx_init().
 **/
int avago_serdes_base_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    Avago_addr_t addr_struct;
    if( avago_addr_to_struct(addr, &addr_struct) )
        return avago_parallel_serdes_base_init(aapl, &addr_struct, config->skip_crc);
    return -1;
}

/** @brief   Initializes Tx of SerDes without disturbing Rx.
 ** @details Configures divider, width, line encoding, data selection and datapath encoding of Tx.
 **          Must call avago_serdes_base_init() before first use.
 ** @return  0 on success, aapl->return_code (< 0) on error.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init(), avago_serdes_rx_init().
 **/
int avago_serdes_tx_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    int return_code = aapl->return_code;
    int tx_width = 0;
    int rx_width = 0;
    Avago_serdes_line_encoding_t rx_encoding = AVAGO_SERDES_NRZ;
    int div_val = 0;
    BOOL tx_en = FALSE, rx_en = FALSE;
    int sdrev = aapl_get_sdrev(aapl, addr);

    avago_serdes_get_tx_rx_ready(aapl, addr, &tx_en, &rx_en);
    avago_serdes_set_tx_rx_enable(aapl, addr, FALSE, rx_en, FALSE);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0b, config->tx_phase_cal ? 1 : 0);

    div_val = config->tx_divider & 0xff ;
    if( config->refclk_sync_master )
        div_val |= 1<<12;

    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x05, div_val);

    avago_serdes_get_tx_rx_width(aapl, addr, &tx_width, &rx_width);
    if( sdrev == AAPL_SDREV_P1 )
    {
        if( config->rx_width == 0 ) rx_width = avago_serdes_get_default_width(aapl, addr);
        else                        rx_width = config->rx_width;
    }

    if( config->tx_width == 0 ) config->tx_width = avago_serdes_get_default_width(aapl, addr);

    if( avago_serdes_get_rx_line_encoding(aapl, addr) ) rx_encoding = AVAGO_SERDES_PAM4;

    avago_serdes_set_tx_rx_width_pam(aapl, addr, config->tx_width, rx_width, config->tx_encoding, rx_encoding);

    if( avago_serdes_set_tx_rx_enable(aapl, addr, config->init_tx, rx_en, config->tx_output_en) == -1 ) config->fail_code |= 0x4;

    if( config->init_mode == AVAGO_INIT_ONLY )
    {
        avago_serdes_set_tx_datapath(aapl, addr, &(config->tx_datapath));
        aapl_log_printf(aapl, AVAGO_DEBUG1, 0, 0, "\n");
        return 0;
    }

    avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_PRBS31);

    if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_HVD6 )
    {
        avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x21, 0x80, 0x80);

        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_PRBS31);
    }

    avago_serdes_set_tx_datapath(aapl, addr, &(config->tx_datapath));
    if( config->init_mode == AVAGO_CORE_DATA_ILB || config->init_mode == AVAGO_CORE_DATA_ELB )
        avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_CORE);


    return aapl->return_code == return_code ? 0 : aapl->return_code;
}

/** @brief   Initializes Rx of SerDes without disturbing Tx.
 ** @details Configures divider, width, line encoding, data selection and datapath encoding of Rx.
 **          Must call avago_serdes_base_init() before first use.
 ** @return  0 on success, aapl->return_code (< 0) on error.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init(), avago_serdes_tx_init().
 **/
int avago_serdes_rx_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    Avago_addr_t addr_struct;
    int return_code = aapl->return_code;
    int rx_width = 0;
    int tx_width = 0;
    Avago_serdes_line_encoding_t tx_encoding = AVAGO_SERDES_NRZ;
    int sdrev = aapl_get_sdrev(aapl, addr);
    BOOL tx_en, rx_en, tx_output_en;
    uint rate_sel = 0;
    uint extra = 0;

    avago_addr_to_struct(addr, &addr_struct);

    if( sdrev == AAPL_SDREV_PON )
    {
        if( config->rate_sel > 3 )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: Invalid rate_sel value: %u.  Valid range [0..3].\n", aapl_addr_to_str(addr), config->rate_sel);
        rate_sel = pon_rate_sel_to_mask(config->rate_sel);
        if( config->burst_mode )
            extra = 1<<8;
    }

    tx_output_en = avago_serdes_get_tx_output_enable(aapl, addr);
    avago_serdes_get_tx_rx_ready(aapl, addr, &tx_en, &rx_en);

    avago_serdes_set_tx_rx_enable(aapl, addr, tx_en, FALSE, tx_output_en);
    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x11, 0x0);

    avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x06, rate_sel | (config->rx_divider & 0xff));

    avago_serdes_get_tx_rx_width(aapl, addr, &tx_width, &rx_width);

    if( config->rx_width == 0 ) config->rx_width = avago_serdes_get_default_width(aapl, addr);
    if( sdrev == AAPL_SDREV_P1 )
    {
        if( config->tx_width == 0 ) tx_width = avago_serdes_get_default_width(aapl, addr);
        else                        tx_width = config->tx_width;
    }

    if( avago_serdes_get_tx_line_encoding(aapl, addr) ) tx_encoding = AVAGO_SERDES_PAM4;

    avago_parallel_serdes_set_tx_rx_width_pam(aapl, &addr_struct, tx_width, config->rx_width, tx_encoding, config->rx_encoding);

    if( -1 == avago_parallel_serdes_set_tx_rx_enable(aapl, &addr_struct, tx_en, config->init_rx, tx_output_en, extra) )
        config->fail_code |= 0x4;

    if( config->signal_ok_en && sdrev != AAPL_SDREV_P1 )
        avago_serdes_initialize_signal_ok(aapl,addr,config->signal_ok_threshold);

    if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_HVD6 )
    {
        avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x1f, 0x1604);
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0, 0, 0x800);
    }

    avago_serdes_set_rx_datapath(aapl, addr, &(config->rx_datapath));

    if( config->init_mode == AVAGO_CORE_DATA_ILB || config->init_mode == AVAGO_CORE_DATA_ELB )
        avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_OFF);
    else
    {
        avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_PRBS31);
        avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x03, AVAGO_SERDES_RX_CMP_MODE_MAIN_PATGEN | 0x0003);
    }

    if( config->init_mode == AVAGO_CORE_DATA_ILB || config->init_mode == AVAGO_PRBS31_ILB )
        avago_serdes_set_rx_input_loopback(aapl, addr, TRUE);
    else
        avago_serdes_set_rx_input_loopback(aapl, addr, FALSE);

    avago_serdes_error_reset(aapl, addr);

    return aapl->return_code == return_code ? 0 : aapl->return_code;
}

int avago_serdes_loopback_test(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    int errors;

    if( config->init_tx && config->init_rx )
    {
        avago_serdes_error_reset(aapl, addr);
        errors = avago_serdes_get_errors(aapl, addr, AVAGO_LSB, 1);
    }
    else errors = 0;

    if( errors )
    {
        aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,
            "%u PRBS errors detected during ILB check of SerDes %s during serdes_init to div %d. Use this SerDes with caution.\n", errors, aapl_addr_to_str(addr), config->tx_divider);
        config->fail_code |= 0x8;
    }
    return errors;
}

/** @brief Verifies that all addresses in the list are SerDes suitable for parallel action.
 ** @details Broadcast addresses, non-SerDes addresses and references to multiple SerDes classes cause failure.
 ** @return Returns TRUE if all addresses refer to a consistent type of SerDes suitable for parallel action.
 ** @return Returns FALSE, logs a message and decrements aapl->return_code if the check fails.
 **/
BOOL avago_parallel_verify_addr_list(
    Aapl_t *aapl,                       /**< [in] Pointer to AAPL structure. */
    Avago_addr_t *addr_list)            /**< [in,out] List of addresses and results. */
{
    uint first_addr = avago_struct_to_addr(addr_list);
    Avago_ip_type_t first_ip_type = aapl_get_ip_type(aapl, first_addr);
    Avago_addr_t *addr_struct;

    if( !aapl_check_ip_type(aapl, first_addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) ||
        !aapl_check_process(aapl, first_addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_B, AVAGO_PROCESS_E, AVAGO_PROCESS_F) )
        return FALSE;

    for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
    {
        uint addr = avago_struct_to_addr(addr_struct);
        Avago_ip_type_t ip_type = aapl_get_ip_type(aapl, addr);

        if( first_ip_type != ip_type )
            return aapl_fail(aapl, __func__, __LINE__, "Inconsistent types in list: both %s and %s found.\n", aapl_ip_type_to_str(first_ip_type), aapl_ip_type_to_str(ip_type)),FALSE;

        if( aapl_check_broadcast_address(aapl, addr, __func__, __LINE__, TRUE) )
            return FALSE;

        if( addr_list->next )
            aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "%s (%s).\n", aapl_addr_to_str(addr), aapl_addr_to_str(addr_struct->group_addr));
    }
    return TRUE;
}

/** @brief   Performs base initialization of multiple SerDes of the same type.
 ** @details Base initialization is required of each SerDes after firmware upload and before any other SerDes configuration.
 ** @details The initialization is done in parallel on all listed SerDes, as much as possible.
 ** @details Resets all parts of a SerDes (Tx, Rx and shared).
 ** @details LIMITATION: All SerDes must be of the same basic type.
 ** @details SIDE EFFECT: Configures a group broadcast for addr_list.
 ** @return  Individual success/failure values are saved into the results field in addr_list.
 ** @return  Returns 0 if all initializations complete successfully.
 ** @return  Returns -1 and decrements aapl->return_code if any failure.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init_config_destruct(), avago_serdes_init(), avago_serdes_init_quick().
 **/
int avago_parallel_serdes_base_init(
    Aapl_t *aapl,                       /**< [in] Pointer to AAPL structure. */
    Avago_addr_t *addr_list,            /**< [in,out] List of addresses and results. */
    BOOL skip_crc)                      /**< [in] Set to skip crc checking (upload does crc also) */
{
    int return_code = aapl->return_code;
    Avago_addr_t *addr_struct;

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Starting parallel SerDes base initialization.\n");

    if( !avago_parallel_verify_addr_list(aapl, addr_list) )
        return -1;

    if( AVAGO_P1 == aapl_get_ip_type(aapl, avago_struct_to_addr(addr_list)) )
    {
        for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
        {
            uint addr = avago_struct_to_addr(addr_struct);
            if( addr_struct->lane < 8 )
                return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes initialization of P1 requires quad or chip level address.\n", aapl_addr_to_str(addr));

            if( addr_struct->lane == AVAGO_ADDR_QUAD_ALL && !aapl_is_octal_p1(aapl, addr) )
                addr_struct->lane = AVAGO_ADDR_QUAD_LOW;
        }
    }

    for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
    {
        uint addr = avago_struct_to_addr(addr_struct);
        avago_sbus_reset(aapl, addr, 0);
        avago_spico_reset(aapl, addr);

        aapl_set_spico_running_flag(aapl, addr, 1);
        addr_struct->results = 0;
    }

    avago_group_clear(aapl, addr_list);
    avago_group_setup(aapl, addr_list);

    if( !skip_crc && !avago_parallel_serdes_crc(aapl, addr_list) )
        return -1;

    avago_parallel_serdes_set_tx_rx_enable(aapl, addr_list, FALSE, FALSE, FALSE, 0);
    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x11, 0x00);

#if 0
    if( aapl_get_ip_type(aapl, avago_struct_to_addr(addr_list)) == AVAGO_M4
        )
    {
        avago_parallel_serdes_set_tx_rx_width_pam(aapl, addr_list, 80, 80, AVAGO_SERDES_PAM2, AVAGO_SERDES_PAM2);
        avago_parallel_serdes_set_tx_rx_enable(aapl, addr_list, FALSE, TRUE, FALSE, 0);
        avago_parallel_serdes_set_tx_rx_enable(aapl, addr_list, FALSE, FALSE, FALSE, 0);
    }
#endif

    return aapl->return_code == return_code ? 0 : -1;
}

/** @brief   Configures and calibrates multiple SerDes of the same type.
 ** @details The initialization is done in parallel on all listed SerDes at once, as much as possible.
 ** @details Since the purpose of this function is performance, some configuration options are not supported.
 **          If any of these are selected, a message will be logged and an error will be returned.
 ** @details LIMITATION: All SerDes must be of the same basic type.
 ** @details LIMITATION: Both Tx and Rx must be enabled.
 ** @details LIMITATION: SBus reset must be enabled.
 ** @return  Individual success/failure values are saved into the results field in addr_list.
 ** @return  Returns 0 if all initializations successfully return with non-identical values.
 ** @return  Returns -1 and decrements aapl->return_code if any failure.
 ** @see     avago_serdes_init_config_construct(), avago_serdes_init_config_destruct(), avago_serdes_init(), avago_serdes_init_quick().
 **/
int avago_parallel_serdes_init(
    Aapl_t *aapl,                       /**< [in] Pointer to AAPL structure. */
    Avago_addr_t *addr_list,            /**< [in,out] List of addresses and results. */
    Avago_serdes_init_config_t *config) /**< [in] Desired SerDes configuration. */
{
    uint first_addr = avago_struct_to_addr(addr_list);
    int sdrev = aapl_get_sdrev(aapl, first_addr);
    Avago_addr_t *addr_struct;
    int errors = 0;
    uint extra = 0;
    uint rate_sel = 0;

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Starting parallel serdes initialization.\n");

    config->fail_code = -1;

    if( !aapl_check_process(aapl, first_addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F) )
        return -1;

    if( !config->init_tx || !config->init_rx )
        return aapl_fail(aapl, __func__, __LINE__, "init_tx and init_rx must be enabled to use this function.\n");

    if( !config->sbus_reset )
        return aapl_fail(aapl, __func__, __LINE__, "sbus_reset must be enabled to use this function.\n");

    if( !config->spico_reset )
        return aapl_fail(aapl, __func__, __LINE__, "spico_reset must be enabled to use this function.\n");

    if( sdrev == AAPL_SDREV_P1 )
    {
        if( config->tx_divider != config->rx_divider )
            return aapl_fail(aapl, __func__, __LINE__, "SBus %s: SerDes P1 requires Tx and Rx dividers to match.\n", aapl_addr_to_str(first_addr));
    }

    if( sdrev == AAPL_SDREV_PON )
    {
        if( config->rate_sel > 3 )
            return aapl_fail(aapl, __func__, __LINE__, "Invalid rate_sel value: %u.  Valid range [0..3].\n", config->rate_sel);
        rate_sel = pon_rate_sel_to_mask(config->rate_sel);
        if( config->burst_mode )
            extra = 1<<8;
    }

    config->fail_code = 0;

    if( avago_parallel_serdes_base_init(aapl, addr_list, config->skip_crc) < 0 )
    {
        avago_group_clear(aapl, addr_list);
        return -1;
    }

    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x0b, config->tx_phase_cal ? 1 : 0);

    {
        uint tx_width = config->tx_width ? config->tx_width : avago_serdes_get_default_width(aapl, first_addr);
        uint rx_width = config->rx_width ? config->rx_width : avago_serdes_get_default_width(aapl, first_addr);

        int tx_div_value = (config->tx_divider & 0xff) |  (config->refclk_sync_master ? 1<<12 : 0);
        if( config->tx_divider == config->rx_divider && rate_sel == 0 )
        {
            avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x05, (1 << 15) | tx_div_value);
        }
        else
        {
            avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x05, tx_div_value);
            avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x06, rate_sel | (config->rx_divider & 0xff));
        }

        avago_parallel_serdes_set_tx_rx_width_pam(aapl, addr_list, tx_width, rx_width, config->tx_encoding, config->rx_encoding);
    }

    if( -1 == avago_parallel_serdes_set_tx_rx_enable(aapl, addr_list, TRUE, TRUE, config->tx_output_en, extra) )
        config->fail_code |= 0x4;

    if( config->signal_ok_en && sdrev != AAPL_SDREV_P1 )
        avago_parallel_serdes_initialize_signal_ok(aapl,addr_list,config->signal_ok_threshold);

    if( config->init_mode == AVAGO_INIT_ONLY )
    {
        avago_parallel_serdes_set_tx_datapath(aapl, addr_list, &(config->tx_datapath));
        avago_parallel_serdes_set_rx_datapath(aapl, addr_list, &(config->rx_datapath));
        aapl_log_printf(aapl, AVAGO_DEBUG1, 0, 0, "\n");
        avago_group_clear(aapl, addr_list);
        return 0;
    }


    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x08, 0x0101);
    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x02, 0x0125);
    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x02, 0x0235);

    if( sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 || (sdrev == AAPL_SDREV_OM4 && config->rx_encoding == AVAGO_SERDES_PAM4) )
    {
        if( aapl->capabilities & AACS_SERVER_NO_CRC )
            avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x0a, 0x20);
        else
            avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x0a, 1);

        for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
        {
            uint addr = avago_struct_to_addr(addr_struct);
            avago_serdes_dfe_wait(aapl, addr);
        }
    }

    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x03, AVAGO_SERDES_RX_CMP_MODE_MAIN_PATGEN | 0x0003);

    if( sdrev == AAPL_SDREV_HVD6 )
    {
        for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
        {
            uint addr = avago_struct_to_addr(addr_struct);
            avago_serdes_mem_rmw(aapl, addr, AVAGO_LSB, 0x21, 0x80, 0x80);
            avago_serdes_mem_wr(aapl, addr, AVAGO_LSB, 0x1f, 0x1604);
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0, 0, 0x800);
            avago_serdes_set_tx_data_sel(aapl, addr, AVAGO_SERDES_TX_DATA_SEL_PRBS31);
            avago_serdes_set_rx_cmp_data(aapl, addr, AVAGO_SERDES_RX_CMP_DATA_PRBS31);
        }
    }

    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x17, 0);

    avago_parallel_serdes_mem_rd(aapl, addr_list, AVAGO_BIG_REG_32, 3);

    if( aapl->debug >= AVAGO_DEBUG1 )
        for( addr_struct = addr_list; addr_struct; addr_struct = addr_struct->next )
        {
            uint addr = avago_struct_to_addr(addr_struct);
            int errs = addr_struct->results;
            if( errs == 0 ) continue;
            aapl_log_printf(aapl, AVAGO_DEBUG1, 0, 0, "%s has errors in ILB: %u.\n", aapl_addr_to_str(addr), errs);
            errors += errs;
        }

    avago_parallel_serdes_set_tx_datapath(aapl, addr_list, &(config->tx_datapath));
    avago_parallel_serdes_set_rx_datapath(aapl, addr_list, &(config->rx_datapath));

    if( config->init_mode == AVAGO_PRBS31_ELB || config->init_mode == AVAGO_CORE_DATA_ELB )
        avago_parallel_serdes_int(aapl, addr_list, 0x08, 0x100);

    if( config->init_mode == AVAGO_CORE_DATA_ILB || config->init_mode == AVAGO_CORE_DATA_ELB )
        avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x02, 0x3ff);

    avago_parallel_serdes_int_check(aapl, __func__, __LINE__, addr_list, 0x17, 0);


    if( errors )
    {
        aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,
            "%u PRBS errors detected during ILB check of SerDes %s during serdes_init to div %d. Use this SerDes with caution.\n", errors, "unknown", config->tx_divider);
        config->fail_code |= 0x8;
    }

    avago_group_clear(aapl, addr_list);
    return (int)errors;
}


/** @brief Initialize struct with default values */
void avago_serdes_tune_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_dfe_tune_t *control)   /**< [in] Tune options structure to initialize. */
{
    (void)aapl;
    memset(control,0,sizeof(*control));
    control->fixed[0] =
    control->fixed[1] =
    control->fixed[2] =
    control->fixed[3] = -1;

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

    if( !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) ||
        !aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F) ||
        !aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, TRUE, 1, 0x1046) )
        return FALSE;

    if( sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 )
    {
        int fixed_flags = 0;
        int unfixed_flags = 0;
        int i;
        for( i = 0; i < 4; i++ )
        {
            if( control->fixed[i] == 1 )
            {
                int hal_index = i <= 2 ? 2-i : i;
                avago_serdes_hal_set(aapl, addr, AVAGO_HAL_RXEQ_CTLE, hal_index, control->value[i]);
                fixed_flags |= 1 << i;
            }
            else if( control->fixed[i] == 0 )
                unfixed_flags |= 1 << i;
        }
        if( fixed_flags || unfixed_flags )
        {
            if( (fixed_flags | unfixed_flags) != 0xf )
                fixed_flags |= avago_serdes_hal_get(aapl, addr, AVAGO_HAL_GLOBAL_TUNE_PARAMS, 8);
            fixed_flags &= ~unfixed_flags;
            avago_serdes_hal_set(aapl, addr, AVAGO_HAL_GLOBAL_TUNE_PARAMS, 8, fixed_flags);
        }
    }
    else
    {
        uint column = (AAPL_SDREV_P1 == sdrev) ? 3 : 2;

        if( sdrev != AAPL_SDREV_P1 )
            if (control->dfe_disable){ int_data |= 0x0040; }

        if( control->fixed[0] == 1 ) { int_data |= 0x0080; avago_spico_int(aapl, addr, 0x26, (column << 12) | (2 << 8) | (control->value[0] & 0xff)); }
        if( control->fixed[1] == 1 ) { int_data |= 0x0100; avago_spico_int(aapl, addr, 0x26, (column << 12) | (1 << 8) | (control->value[1] & 0xff)); }
        if( control->fixed[2] == 1 ) { int_data |= 0x0200; avago_spico_int(aapl, addr, 0x26, (column << 12) | (0 << 8) | (control->value[2] & 0xff)); }

        if( aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, FALSE, 1, 0x104D) && control->fixed[3] == 1 )
        {
            int_data |= 0x0400;
            avago_spico_int(aapl, addr, 0x26, (column << 12) | (3 << 8) | (control->value[3] & 0xff));
        }
    }

    if( sdrev != AAPL_SDREV_CM4 && sdrev != AAPL_SDREV_P1 )
    {
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
 **       which is also the number of UI per heartbeat.
 **@details In PAM4 operation, the number of bits is twice the number of UI.
 **/
int avago_serdes_get_rx_register_clock(Aapl_t *aapl, uint addr)
{
    int tx_width, rx_width;

    if( aapl_get_process_id(aapl,addr) == AVAGO_PROCESS_F && aapl_get_ip_type(aapl,addr) == AVAGO_SERDES )
        return 20;

    avago_serdes_get_tx_rx_width(aapl, addr, &tx_width, &rx_width);
    if( rx_width >= 64 || avago_serdes_get_rx_line_encoding(aapl,addr) )
        rx_width /= 2;
    return rx_width;
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


/** @defgroup Clocking Rx Clocking API
 ** @{
 **/

/** @brief  Sets DATA clock source.
 ** @return On success, returns TRUE.
 ** @return On failure, returns FALSE.
 ** @see    avago_serdes_rx_clock_apply().
 **/
BOOL avago_serdes_set_rx_data_clock(
    Aapl_t *aapl,                     /**< [in] Pointer to Aapl_t structure. */
    uint addr,                        /**< [in] Device address number. */
    Avago_serdes_rx_clock_t data)     /**< [in] Clock to set for DATA clock source */
{
    int sdrev = aapl_get_sdrev(aapl, addr);
    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Sbus %s, Setting DATA clock source to %s.\n",
                          aapl_addr_to_str(addr), aapl_rx_clock_to_str(data));

    if( (data == AVAGO_SERDES_RX_CLOCK_R || data == AVAGO_SERDES_RX_CLOCK_OFF) && (sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_PON) )
    {
        int dly = data == AVAGO_SERDES_RX_CLOCK_R ? 0x0008 : 0x0001;
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xb7,    dly, 0x000f);
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x93, 0x0002, 0x000f);
        return TRUE;
    }

    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, (data<<4) | 0x00);
}

/** @brief  Sets DFE clock source.
 ** @return On success, returns TRUE.
 ** @return On failure, returns FALSE.
 ** @see    avago_serdes_rx_clock_apply().
 **/
BOOL avago_serdes_set_rx_dfe_clock(
    Aapl_t *aapl,                    /**< [in] Pointer to Aapl_t structure. */
    uint addr,                       /**< [in] Device address number. */
    Avago_serdes_rx_clock_t dfe)     /**< [in] Clock to set for DFE clock source */
{
    int sdrev = aapl_get_sdrev(aapl, addr);
    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Sbus %s, Setting DFE clock source to %s.\n",
                          aapl_addr_to_str(addr), aapl_rx_clock_to_str(dfe));

    if( sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_PON )
    {
        int dly = dfe == AVAGO_SERDES_RX_CLOCK_R ? 0x8000 : 0x1000;
        int val = dfe == AVAGO_SERDES_RX_CLOCK_I ? 0x8000 :
                  dfe == AVAGO_SERDES_RX_CLOCK_Q ? 0x4000 : 0x2000;
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xb7, dly, 0xf000);
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x93, val, 0xf000);
        return TRUE;
    }

    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, (dfe <<4) | 0x01);
}

/** @brief  Sets CDC clock source.
 ** @return On success, returns TRUE.
 ** @return On failure, returns FALSE.
 ** @see    avago_serdes_rx_clock_apply().
 **/
BOOL avago_serdes_set_rx_cdc_clock(
    Aapl_t *aapl,                      /**< [in] Pointer to Aapl_t structure. */
    uint addr,                         /**< [in] Device address number. */
    Avago_serdes_rx_clock_cdc_t cdc)   /**< [in] Clock to set for CDC clock source */
{
    int inv = 0;
    int sdrev = aapl_get_sdrev(aapl, addr);
    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Sbus %s, Setting CDC clock source to %s.\n",
                          aapl_addr_to_str(addr), aapl_rx_clock_cdc_to_str(cdc));

    if( sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_PON )
    {
        int return_code = aapl->return_code;
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x94, (cdc & 3) << 9, 3 << 9);
        return aapl->return_code == return_code;
    }
    if( sdrev == AAPL_SDREV_D6_07 )
    {
        if(      cdc == AVAGO_SERDES_RX_CDC_DATA     ) cdc = AVAGO_SERDES_RX_CDC_ICLK;
        else if( cdc == AVAGO_SERDES_RX_CDC_EDGE     ) cdc = AVAGO_SERDES_RX_CDC_QCLK;
        else if( cdc == AVAGO_SERDES_RX_CDC_INV_DATA ) cdc = AVAGO_SERDES_RX_CDC_INV_ICLK;
        else if( cdc == AVAGO_SERDES_RX_CDC_INV_EDGE ) cdc = AVAGO_SERDES_RX_CDC_INV_QCLK;

        if( cdc >= AVAGO_SERDES_RX_CDC_INV_ICLK )
            inv = 0x40;
    }

    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, inv | (3 & cdc) << 4 | 0x02);
}


/** @brief  Sets EDGE clock source.
 ** @return On success, returns TRUE.
 ** @return On failure, returns FALSE.
 ** @see    avago_serdes_rx_clock_apply().
 **/
BOOL avago_serdes_set_rx_edge_clock(
    Aapl_t *aapl,                     /**< [in] Pointer to Aapl_t structure. */
    uint addr,                        /**< [in] Device address number. */
    Avago_serdes_rx_clock_t edge)     /**< [in] Clock to set for EDGE clock source */
{
    int sdrev = aapl_get_sdrev(aapl, addr);
    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Sbus %s, Setting EDGE clock source to %s.\n",
                          aapl_addr_to_str(addr), aapl_rx_clock_to_str(edge));

    if( (edge == AVAGO_SERDES_RX_CLOCK_R || edge == AVAGO_SERDES_RX_CLOCK_OFF) && (sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_PON) )
    {
        int dly = edge == AVAGO_SERDES_RX_CLOCK_R ? 0x0080 : 0x0010;
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xb7,    dly, 0x00f0);
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x93, 0x0020, 0x00f0);
        return TRUE;
    }

    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, (edge<<4) | 0x03);
}

/** @brief  Sets TEST clock source.
 ** @return On success, returns TRUE.
 ** @return On failure, returns FALSE.
 ** @see    avago_serdes_rx_clock_apply().
 **/
BOOL avago_serdes_set_rx_test_clock(
    Aapl_t *aapl,                      /**< [in] Pointer to Aapl_t structure. */
    uint addr,                         /**< [in] Device address number. */
    Avago_serdes_rx_clock_t test)      /**< [in] Clock to set for TEST clock source */
{
    int sdrev = aapl_get_sdrev(aapl, addr);
    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Sbus %s, Setting TEST clock source to %s.\n",
                          aapl_addr_to_str(addr), aapl_rx_clock_to_str(test));

    if( (test == AVAGO_SERDES_RX_CLOCK_Q || test == AVAGO_SERDES_RX_CLOCK_OFF) && (sdrev == AAPL_SDREV_16 || sdrev == AAPL_SDREV_PON) )
    {
        int dly = test == AVAGO_SERDES_RX_CLOCK_Q ? 0x0400 : 0x0100;
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xb7,    dly, 0x0f00);
        avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x93, 0x0200, 0x0f00);
        return TRUE;
    }

    return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, (test<<4) | 0x04);
}

static char *one_line(char *buf)
{
    register char *to = buf;
    register char *from = buf;
    for( from = buf; *from; from++ )
    {
        if( *from == '\n' )
        {
            if( from != buf )
                *to++ = ',';
        }
        else if( *from != ' ' )
            *to++ = *from;
        else
        {
            *to++ = ' ';
            while( from[1] == ' ' )
                from++;
        }
    }
    *to = '\0';
    return buf;
}

/** @brief  Prints selected fields of the rx_clocks structure to a buffer.
 ** @return On success, returns a pointer to a string which should be freed using aapl_free().
 ** @return On failure, returns NULL.
 ** @see    avago_serdes_rx_clock_read().
 **/
char *avago_serdes_rx_clock_print(
    Aapl_t *aapl,                     /**< [in] Pointer to Aapl_t structure. */
    uint addr,                        /**< [in] Device address number. */
    uint mask,                        /**< [in] Mask that defines which parameters to update. */
    Avago_serdes_rx_clocks_t *params) /**< [in] Structure to print. */
{
    char *buf = 0, *buf_end = 0;
    int size = 0;
    (void)addr;

    if( mask & 0x01 ) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n    Data : %s", aapl_rx_clock_to_str(params->data));
    if( mask & 0x02 ) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n    Edge : %s", aapl_rx_clock_to_str(params->edge));
    if( mask & 0x04 ) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n    Test : %s", aapl_rx_clock_to_str(params->test));
    if( mask & 0x08 ) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n    DFE  : %s", aapl_rx_clock_to_str(params->dfe));
    if( mask & 0x10 ) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n    CDC  : %s", aapl_rx_clock_cdc_to_str(params->cdc));

    return buf;
}

/** @brief  Applies selected clock to respective clock source.
 ** @return On success, returns 0.
 ** @return On failure, returns -1.
 ** @see    avago_serdes_rx_clock_read().
 **/
int avago_serdes_rx_clock_apply(
    Aapl_t *aapl,                     /**< [in] Pointer to Aapl_t structure. */
    uint addr,                        /**< [in] Device address number. */
    uint mask,                        /**< [in] Mask that defines which parameters to update. */
    Avago_serdes_rx_clocks_t *params) /**< [in] Clock source whose clock to set. */
{
    int return_code = aapl->return_code;

    if( mask & 0x01 ) avago_serdes_set_rx_data_clock(aapl, addr, params->data);
    if( mask & 0x02 ) avago_serdes_set_rx_edge_clock(aapl, addr, params->edge);
    if( mask & 0x04 ) avago_serdes_set_rx_test_clock(aapl, addr, params->test);
    if( mask & 0x08 ) avago_serdes_set_rx_dfe_clock(aapl,  addr, params->dfe );
    if( mask & 0x10 ) avago_serdes_set_rx_cdc_clock(aapl,  addr, params->cdc );

    return (aapl->return_code == return_code) ? 0 : -1;
}

/** @brief  Writes selected clock to respective clock source.
 ** @return On success, returns 0.
 ** @return On failure, returns -1.
 ** @see    avago_serdes_rx_clock_apply(), avago_serdes_rx_clock_read().
 **/
int avago_serdes_rx_clock_write(
    Aapl_t *aapl,
    uint addr,
    Avago_serdes_rx_clocks_t *rx_clock)
{
    int return_code = aapl->return_code;

    avago_serdes_rx_clock_apply(aapl, addr, ~0, rx_clock);

    return (aapl->return_code == return_code) ? 0 : -1;
}

/** @brief  Reads Rx clock value and populates structure.
 ** @return On success, returns 0.
 ** @return On failure, returns -1.
 ** @see    avago_serdes_rx_clock_apply().
 **/
int avago_serdes_rx_clock_read(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint addr,                          /**< [in] Device address number. */
    Avago_serdes_rx_clocks_t *rx_clock) /**< [in] Addr of structure to update. */
{
    int return_code = aapl->return_code;
    int val = 0;
    int cdc_val = 0;
    uint sdrev = aapl_get_sdrev(aapl, addr);

    switch(sdrev)
    {
        uint data_val, dfe_val, edge_val, test_val, dly;
        case AAPL_SDREV_CM4_16:
            val     = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x93);
            cdc_val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xb5);
            data_val = ((val >> 1)  & 0x7);
            dfe_val  = ((val >> 13) & 0x7);
            edge_val = ((val >> 7)  & 0x7);
            test_val = ((val >> 10) & 0x7);
            rx_clock->data = (data_val == 0x01) ? AVAGO_SERDES_RX_CLOCK_R :
                             (data_val == 0x02) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (data_val == 0x04) ? AVAGO_SERDES_RX_CLOCK_I :
                                                  AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->dfe  = (dfe_val == 0x01)  ? AVAGO_SERDES_RX_CLOCK_R :
                             (dfe_val == 0x02)  ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dfe_val == 0x04)  ? AVAGO_SERDES_RX_CLOCK_I :
                                                  AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->edge = (edge_val == 0x01) ? AVAGO_SERDES_RX_CLOCK_R :
                             (edge_val == 0x02) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (edge_val == 0x04) ? AVAGO_SERDES_RX_CLOCK_I :
                                                  AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->test = (test_val == 0x01) ? AVAGO_SERDES_RX_CLOCK_R :
                             (test_val == 0x02) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (test_val == 0x04) ? AVAGO_SERDES_RX_CLOCK_I :
                                                  AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->cdc = (Avago_serdes_rx_clock_cdc_t) ((cdc_val >> 10) & 0x3);
            break;
        case AAPL_SDREV_HVD6:
        case AAPL_SDREV_D6:
            val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x30);
            rx_clock->data = (Avago_serdes_rx_clock_t) ( val       & 0x03);
            rx_clock->dfe  = (Avago_serdes_rx_clock_t) ((val >> 6) & 0x03);
            rx_clock->edge = (Avago_serdes_rx_clock_t) ((val >> 2) & 0x03);
            rx_clock->test = (Avago_serdes_rx_clock_t) ((val >> 4) & 0x03);
            rx_clock->cdc  = (Avago_serdes_rx_clock_cdc_t) ((val >> 9) & 0x03);
            break;
        case AAPL_SDREV_OM4:
            val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x93);
            cdc_val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x94);
            data_val = ((val >>  0) & 0x3);
            dfe_val  = ((val >> 12) & 0x3);
            edge_val = ((val >>  4) & 0x3);
            test_val = ((val >>  8) & 0x3);
            rx_clock->data = (Avago_serdes_rx_clock_t)(data_val + 1);
            rx_clock->dfe  = (Avago_serdes_rx_clock_t)(dfe_val  + 1);
            rx_clock->edge = (Avago_serdes_rx_clock_t)(edge_val + 1);
            rx_clock->test = (Avago_serdes_rx_clock_t)(test_val + 1);
            rx_clock->cdc  = (Avago_serdes_rx_clock_cdc_t) ((val >> 9) & 0x03);
            break;
        case AAPL_SDREV_D6_07: {
            Avago_serdes_rx_clock_t table[4] = { AVAGO_SERDES_RX_CLOCK_Q, AVAGO_SERDES_RX_CLOCK_I, AVAGO_SERDES_RX_CLOCK_R, AVAGO_SERDES_RX_CLOCK_OFF};
            val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x5d0);
            rx_clock->data = table[(val >>  4) & 0x03];
            rx_clock->dfe  = table[(val >>  0) & 0x03];
            rx_clock->edge = table[(val >>  8) & 0x03];
            rx_clock->test = table[(val >> 10) & 0x03];
            {
                Avago_serdes_rx_clock_cdc_t table[8] = {
                        AVAGO_SERDES_RX_CDC_QCLK,     AVAGO_SERDES_RX_CDC_ICLK,     AVAGO_SERDES_RX_CDC_RCLK,     AVAGO_SERDES_RX_CDC_OFF,
                        AVAGO_SERDES_RX_CDC_INV_QCLK, AVAGO_SERDES_RX_CDC_INV_ICLK, AVAGO_SERDES_RX_CDC_INV_RCLK, AVAGO_SERDES_RX_CDC_OFF };
                int cdc_index = (val >> 2) & 3;
                cdc_val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x580);
                if( cdc_val & (1<<10) )
                    cdc_index += 4;
                rx_clock->cdc  = table[cdc_index];
            }
            break;
            }
        case AAPL_SDREV_PON:
        case AAPL_SDREV_16:
            val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x93);
            dly = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xb7);
            cdc_val = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x94);

            rx_clock->data = (val & 0x0008) ? AVAGO_SERDES_RX_CLOCK_I :
                             (val & 0x0004) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dly & 0x0008) ? AVAGO_SERDES_RX_CLOCK_R :
                             (dly & 0x0004) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dly & 0x0002) ? AVAGO_SERDES_RX_CLOCK_I :
                             AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->dfe  = (val & 0x8000) ? AVAGO_SERDES_RX_CLOCK_I :
                             (val & 0x4000) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dly & 0x8000) ? AVAGO_SERDES_RX_CLOCK_R :
                             (dly & 0x4000) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dly & 0x2000) ? AVAGO_SERDES_RX_CLOCK_I :
                             AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->edge = (val & 0x0080) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (val & 0x0040) ? AVAGO_SERDES_RX_CLOCK_I :
                             (dly & 0x0080) ? AVAGO_SERDES_RX_CLOCK_R :
                             (dly & 0x0040) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dly & 0x0020) ? AVAGO_SERDES_RX_CLOCK_I :
                             AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->test = (val & 0x0800) ? AVAGO_SERDES_RX_CLOCK_I :
                             (val & 0x0400) ? AVAGO_SERDES_RX_CLOCK_R :
                             (dly & 0x0800) ? AVAGO_SERDES_RX_CLOCK_R :
                             (dly & 0x0400) ? AVAGO_SERDES_RX_CLOCK_Q :
                             (dly & 0x0200) ? AVAGO_SERDES_RX_CLOCK_I :
                             AVAGO_SERDES_RX_CLOCK_OFF;
            rx_clock->cdc  = (Avago_serdes_rx_clock_cdc_t) ((cdc_val >> 9) & 0x0003);
            break;
        default:
            rx_clock->data = AVAGO_SERDES_RX_CLOCK_I;
            rx_clock->dfe  = AVAGO_SERDES_RX_CLOCK_I;
            rx_clock->edge = AVAGO_SERDES_RX_CLOCK_Q;
            rx_clock->test = AVAGO_SERDES_RX_CLOCK_R;
            rx_clock->cdc  = AVAGO_SERDES_RX_CDC_DATA;
            break;
    }

    if( aapl->debug > 0 )
    {
        char *buf = avago_serdes_rx_clock_print(aapl, addr, ~0, rx_clock);
        if( buf )
        {
            aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "SBus %s, Read Rx clocks structure: {%s }\n", aapl_addr_to_str(addr), one_line(buf));
            aapl_free(aapl, buf, __func__);
        }
    }
    return (aapl->return_code == return_code) ? 0 : -1;
}

/** @brief   Enables or disables the PCS FIFO clock.
 ** @details If the o_rx_pcs_fifo_clk output is not used, you can save
 **          some power by disabling the PCS FIFO clock.
 ** @return  On success, returns TRUE.
 ** @return  On failure, returns FALSE and decrements aapl->return_code.
 **/
BOOL avago_serdes_enable_pcs_fifo_clock(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    BOOL enable)    /**< [in] Powers up/down the PCS FIFO CLOCK. */
{
    int return_code = aapl->return_code;
    int bits = enable ? 0x0000 : 0x000f;

    avago_serdes_mem_wr(aapl, addr, AVAGO_ESB, 0x0c2, bits);
    return return_code == aapl->return_code;
}

/** @brief   Powers up/down SerDes circuits which are not needed for normal traffic.
 ** @details The expectation is that low power mode will be enabled after
 **          the SerDes is configured and begins passing data, and disabled
 **          before any SerDes reconfiguration is performed.
 ** @details In low power mode, data traffic and ical/pcal tuning will function.
 **          Other actions may not function as expected.
 ** @details Currently implemented on 16nm D6 and CM4 SerDes only.
 ** @return  Returns TRUE to indicate was previously in low power mode.
 ** @return  Returns FALSE to indicate was not previously in low power mode.
 ** @return  Returns FALSE for unsupported SerDes.
 ** @return  Returns FALSE and decrements aapl->return_code on failure.
 **/
BOOL avago_serdes_enable_low_power_mode(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    uint addr,                  /**< [in] Device address number. */
    BOOL enable_low_power_mode) /**< [in] TRUE=enter low power mode, FALSE=exit low power mode */
{
    int return_code = aapl->return_code;
    int sdrev = aapl_get_sdrev(aapl, addr);
    BOOL in_low_power_mode = FALSE;

    if( !aapl_check_process(aapl, addr, __func__, __LINE__, FALSE, 1, AVAGO_PROCESS_B) ||
        !aapl_check_ip_type(aapl, addr, __func__, __LINE__, FALSE, 2, AVAGO_SERDES, AVAGO_M4) )
        return FALSE;


    switch( sdrev )
    {
    case AAPL_SDREV_CM4_16:
        in_low_power_mode = 0x70 == (avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x0f8) & 0x70);



        if( enable_low_power_mode )
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x08a, 0x0000, 0x0600);

            avago_serdes_mem_wr (aapl, addr, AVAGO_ESB, 0x08b, 0xffff        );

            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x090, 0x0000, 0x07f0);
        }
        else
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x08a, 0x0600, 0x0600);
            avago_serdes_mem_wr( aapl, addr, AVAGO_ESB, 0x08b, 0x5555        );
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x090, 0x0260, 0x07f0);
        }


#if 0
        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x093, 0x0000, 0x1c00);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x093, 0x1000, 0x1c00);

        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0be, 0x000f, 0x000f);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0be, 0x000f, 0x000d);
#endif



        if( enable_low_power_mode && !avago_serdes_get_rx_line_encoding(aapl, addr) )
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x093, 0x0000, 0x0070);
        }
        else
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x093, 0x0040, 0x0070);
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0be, 0xffd0, 0xfff0);
        }


        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x09f, 0x0000, 0xc000);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x09f, 0xc000, 0xc000);


        if( enable_low_power_mode )
            avago_serdes_mem_wr (aapl, addr, AVAGO_ESB, 0x0ba, 0x000f        );
        else
            avago_serdes_mem_wr (aapl, addr, AVAGO_ESB, 0x0ba, 0x0005        );


        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0f8, 0x0070, 0x0070);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0f8, 0x0000, 0x0070);


        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x13e, 0x00f0, 0x00f0);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x13e, 0x0000, 0x00f0);


        if( enable_low_power_mode )
        {
            if( (0x8000 & avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xd8)) != 0 )
                avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0f6, 0x000f, 0x00ff);
            else
                avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0f6, 0x00f0, 0x00ff);
        }
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0f6, 0x0000, 0x00ff);


        if( enable_low_power_mode )
        {
            if( (0x8000 & avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0xca)) != 0 )
                avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0cc, 0x000f, 0x00ff);
            else
                avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0cc, 0x00f0, 0x00ff);
        }
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x0cc, 0x0000, 0x00ff);

        break;

    case AAPL_SDREV_16:
        in_low_power_mode = 0x0400 == (avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, 0x093) & 0x0f00);
        if( enable_low_power_mode )
        {
            avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, 0x100);

            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x090, 0x0000, 0x07f0);
        }
        else
        {

            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x090, 0x0260, 0x07f0);
        }

        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x93, 0x0400, 0x0f00);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0x93, 0x0000, 0x0f00);

        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xbe, 0x0f0f, 0x0f0f);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xbe, 0x5555, 0x0f0f);

        if( enable_low_power_mode )
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xb9, 0xf000, 0xf000);
        else
            avago_serdes_mem_rmw(aapl, addr, AVAGO_ESB, 0xb9, 0x5000, 0xf000);
        break;

    default: return FALSE;
    }
    return return_code == aapl->return_code && in_low_power_mode;
}

/** @} */
