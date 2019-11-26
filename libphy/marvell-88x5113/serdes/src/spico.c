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
 ** @file spico.c
 ** @brief Functions for SPICO processors.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

/** @brief  Check the PC and possibly interrupt pending bits to see if the Processor
 **         is running or if it's possibly hung.
 **
 ** @return 0 - The spico is not running for this serdes slice
 **         1 - The spico is running for this serdes slice
 **/
uint avago_spico_running(
    Aapl_t *aapl,   /**< [in] Pointer to AAPL structure */
    uint sbus_addr) /**< [in] SBus address of SerDes */
{
    int running = 0;
    if( !aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F, AVAGO_PROCESS_A) ||
        aapl_check_broadcast_address(aapl, sbus_addr, __func__, __LINE__, TRUE) )
        return 0;

    switch( aapl_get_process_id(aapl, sbus_addr) )
    {
    case AVAGO_PROCESS_C:
    case AVAGO_PROCESS_B:
    case AVAGO_PROCESS_F:
        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_SERDES, AVAGO_SPICO, AVAGO_M4, AVAGO_P1) ) return 0;
        if( (aapl_get_ip_type(aapl, sbus_addr) == AVAGO_SERDES) || (aapl_get_ip_type(aapl, sbus_addr) == AVAGO_M4)
                                                                || (aapl_get_ip_type(aapl, sbus_addr) == AVAGO_P1) )
        {
            int pc = avago_sbus_rd(aapl, sbus_addr, 0x25);
            int interrupt = avago_sbus_rd(aapl, sbus_addr, 0x4);
            int mem_bist = avago_sbus_rd(aapl, sbus_addr, 0x9);
            int stepping = avago_sbus_rd(aapl, sbus_addr, 0x20);
            int enable = avago_sbus_rd(aapl, sbus_addr, 0x7);
            int error = avago_sbus_rd(aapl, sbus_addr, 0x2a);

            if(((enable & 0x2) == 0x2) && (pc != 0x2) && (pc != 0xffff) && ((interrupt >> 16 & 0x3) == 0x0) && ((mem_bist & 0x1) == 0x00) && ((stepping&1) == 0) && ((error & 0x1f) != 0x1f))
                running = 1;
            aapl_log_printf(aapl, AVAGO_DEBUG7, __func__, __LINE__,
                "Running: %d, SBus %s, 0x25: 0x%08x, 0x04: 0x%08x, 0x09: 0x%08x, 0x20: 0x%x, 0x07: 0x%08x 0x2a: 0x%02x\n",
                running, aapl_addr_to_str(sbus_addr), pc, interrupt, mem_bist, stepping, enable, error);
        }
        else
        {
            int pc = avago_sbus_rd(aapl, sbus_addr, 0xa);
            int stepping = avago_sbus_rd(aapl, sbus_addr, 0x05);
            int mem_bist = avago_sbus_rd(aapl, sbus_addr, 0x0);
            int enable = avago_sbus_rd(aapl, sbus_addr, 0x1);
            int error = avago_sbus_rd(aapl, sbus_addr, 0xf);

            if((pc != 0x2) && (pc != 0xffff) && ((stepping & 1) == 0) && ((mem_bist & 0x4) == 0x00) && ((enable & 0x100) == 0x100) && ((error & 0x1f) != 0x1f))
                running = 1;
            aapl_log_printf(aapl, AVAGO_DEBUG7, __func__, __LINE__,
                            "Running: %d, SBus: %s, 0x0a: 0x%x, 0x05: 0x%08x, 0x00: 0x%08x, 0x01: 0x%08x 0x0f: 0x%02x\n",
                            running, aapl_addr_to_str(sbus_addr), pc, stepping, mem_bist, enable, error);
        }
        break;

    case AVAGO_PROCESS_A:
        if( !aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO) ) return 0;
        if( avago_sbus_rd(aapl, sbus_addr, 0xa) != 0x2 ) running = 1;
        break;

    default:
        aapl_fail(aapl, __func__, __LINE__, "SBus %s, IP type 0x%x, in process %s, is not supported.\n",
                    aapl_addr_to_str(sbus_addr), aapl_get_ip_type(aapl, sbus_addr),
                    aapl_get_process_id_str(aapl, sbus_addr));
        break;
    }
    return running;
}

/** @brief   Internal function. Returns the value of SPICO's program counter.
 ** @return  The PC value
 ** @see     avago_spico_status
 **/
uint avago_spico_get_pc(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: return avago_sbus_rd(aapl, addr, 0x25);
    case AVAGO_SPICO:  return avago_sbus_rd(aapl, addr, 0x0a)
                          | ((avago_sbus_rd(aapl, addr, 0x0e) & 0x3FF) << 16);
    default:           return 0;
    }
}

/** @brief   Internal function. Returns the current state of the processor.
 ** @return  SPICO's state byte
 ** @see     avago_spico_status
 **/
uint avago_spico_get_state(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: return avago_sbus_rd(aapl, addr, 0x2a);
    case AVAGO_SPICO:  return avago_sbus_rd(aapl, addr, 0x0f) & 0x1f;
    default:           return 0;
    }
}


/**
 ** @brief    Gets the current state of the processor
 ** @return   aapl->return_code
 ** @details  Create a spico_status struct, if spico is not running or it's an invalid
 ** IP or Process the struct is returned with a default configuration (state = SPICO_RESET
 ** and PC=2, all other members = 0).  Otherwise the Avago_spico_status_t is updated with the
 ** current information for the processor.
 **/
int avago_spico_status(
    Aapl_t *aapl,                   /**< [in] Pointer to AAPL structure */
    uint sbus_addr,                 /**< [in] SBus address of SerDes */
    BOOL no_cache,                  /**< [in] Don't use AAPL cache for returning firmware rev and build information */
    Avago_spico_status_t *state)    /**< [out] Pointer to structure to fill in */
{
    if( aapl_get_spico_running_flag(aapl,sbus_addr) )
    {
        if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
            state->clk = AVAGO_SERDES_SPICO_REFCLK;
        else
            state->clk = avago_serdes_get_spico_clk_src(aapl, sbus_addr);

        if (no_cache)
        {
            Avago_addr_t addr_struct;
            avago_addr_to_struct(sbus_addr, &addr_struct);
            aapl->firm_rev[AAPL_3D_ARRAY_ADDR(addr_struct)] = 0;
            aapl->firm_build[AAPL_3D_ARRAY_ADDR(addr_struct)] = 0;
        }
        state->revision = aapl_get_firmware_rev(aapl,sbus_addr);
        state->build    = aapl_get_firmware_build(aapl,sbus_addr);
        state->pc       = avago_spico_get_pc(aapl, sbus_addr);
        state->enabled  = 1;
        switch( avago_spico_get_state(aapl,sbus_addr) )
        {
            case 0x00 : { state->state = AVAGO_SPICO_RESET; break;}
            case 0x12 : { state->state = AVAGO_SPICO_PAUSE; break;}
            case 0x1f : { state->state = AVAGO_SPICO_ERROR; break;}
            default   : { state->state = AVAGO_SPICO_RUNNING; break;}
        }
    }
    else
    {
        state->enabled  = 0;
        state->pc       = 2;
        state->revision = 0;
        state->build    = 0;
        state->state    = AVAGO_SPICO_RESET;
        state->clk      = AVAGO_SERDES_SPICO_REFCLK;
    }
    return aapl->return_code;
}

static int add_int_slice_sel(Aapl_t *aapl, uint addr, int int_num)
{

    char tab[16] = { 0, 0x08, 0x10, 0x18, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7 };
    int slice = tab[(addr >> 16) & 0xf];
    if( slice == 0 || aapl_get_ip_type(aapl,addr) != AVAGO_P1 )
        return 0;
    if( int_num & 0xc000 )
    {
        if( slice == 0x10 ) slice = 4;
        return (slice & 7) << 10;
    }
    return slice << 8;
}

/** @cond INTERNAL */


uint avago_serdes_spico_int_sbus_fn(
    Aapl_t *aapl,   /**< [in] Pointer to AAPL structure */
    uint sbus_addr, /**< [in] SBus address of SBus Master SPICO */
    int int_num,    /**< [in] Interrupt code */
    int param)      /**< [in] Interrupt data */
{
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;
    uint dev_count = 0;
    uint prev_data = 0;
    int loops = 0;
    uint data = 0;

    avago_sbus_wr(aapl, sbus_addr, 0x03, (int_num << 16) | param);
    avago_addr_to_struct(sbus_addr, &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);
        if (!aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)) continue;
        for (loops = 0; loops < aapl->serdes_int_timeout; loops++)
        {
            data = avago_sbus_rd(aapl, sbus_addr, 0x04);
            if ((data & 0x30000) == 0) break;
            if (aapl_get_spico_running_flag(aapl, sbus_addr) == AVAGO_SPICO_HALT)
            {
                aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__,
                    "SBus %s in halted state, so return value may not be valid for interrupt 0x%02x,0x%04x.\n", aapl_addr_to_str(sbus_addr), int_num, param);
                break;
            }
        }
        if (dev_count > 0 && prev_data != data)
        {
            aapl_fail(aapl, __func__, __LINE__, "Broadcast interrupt failed because not all SerDes responded with the same answer. Previous answers: %04x. Current answer from SBus address %s: %04x.\n", prev_data, aapl_addr_to_str(sbus_addr), data);
            return 0;
        }
        prev_data = data;
        dev_count ++;

        if (loops >= aapl->serdes_int_timeout)
        {
            uint bits = (data >> 16) & 3;
            const char *msg = bits == 3 ? "disabled & in_progress" : bits == 2 ? "disabled" : "in_progress";
            aapl_set_spico_running_flag(aapl,sbus_addr,0);
            aapl_fail(aapl, __func__, __LINE__, "Interrupt 0x%02x,0x%04x timed out after %d loops on SBus address %s -> 0x%x (%s).\n", int_num, param, aapl->serdes_int_timeout, aapl_addr_to_str(sbus_addr), data, msg);
            return data;
        }
    }

    if( aapl_get_lsb_rev(aapl, sbus_addr) <= 2 ) data = avago_sbus_rd(aapl, sbus_addr, 0x04);
    return data;
}

/** @endcond */

static uint avago_serdes_spico_int(
    Aapl_t *aapl,   /**< [in] Pointer to AAPL structure */
    uint sbus_addr, /**< [in] SBus address of SBus Master SPICO */
    int int_num,    /**< [in] Interrupt code */
    int param)      /**< [in] Interrupt data */
{
    uint data = 0;
    if (!aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, TRUE, 4,AVAGO_SERDES_BROADCAST,AVAGO_SERDES,AVAGO_M4,AVAGO_P1)) return 0;

    param &= 0xffff;
    int_num |= add_int_slice_sel(aapl, sbus_addr, int_num);
    sbus_addr &= 0xffff;

    if (aapl->serdes_int_fn)
        data = aapl->serdes_int_fn(aapl, sbus_addr, int_num, param);

    aapl_log_printf(aapl, AVAGO_DEBUG7, __func__, __LINE__, "SBus %s, int: 0x%02x 0x%04x -> 0x%04x.\n", aapl_addr_to_str(sbus_addr), int_num, param, data);
    return (data & 0xffff);
}

/** @return  On success, returns 0;
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
static int spico_int_array_nobatch(Aapl_t *aapl, uint sbus_addr, int num_elements, Avago_spico_int_t *ints)
{
    int i;
    int return_code = aapl->return_code;
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "num_elements = %d\n",num_elements);
    for( i = 0; i < num_elements; i++ )
    {
        Avago_spico_int_t *it = &ints[i];
        if( it->flags & AVAGO_SPICO_INT_NOT_FIRST )
        {
            it->ret = 0;
            continue;
        }
        it->ret = avago_spico_int(aapl, sbus_addr, it->interrupt, it->param);
        if( aapl->return_code != return_code )
            break;
    }
    return aapl->return_code == return_code ? 0 : -1;
}

/** @return  On success, returns 0;
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
static int spico_int_array_batch(Aapl_t *aapl, uint sbus_addr, int num_elements, Avago_spico_int_t *ints)
{
    int loops;
    int return_code = aapl->return_code;

    if( !aapl_is_aacs_communication_method(aapl) )
        return spico_int_array_nobatch(aapl, sbus_addr, num_elements, ints);

    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "num_elements = %d\n",num_elements);
    for( loops = 0; loops < aapl->serdes_int_timeout; loops++ )
    {
        BOOL timeout = FALSE;
        char *ptr;
        int i;
        for( i = 0; i < num_elements; i++ )
        {
            int int_num;
            int recv_data_back;
            Avago_spico_int_t *it = &ints[i];
            if( ((it->flags & AVAGO_SPICO_INT_FIRST) && loops != 0) ||
                ((it->flags & AVAGO_SPICO_INT_NOT_FIRST) && loops == 0) )
                continue;
            int_num = it->interrupt | add_int_slice_sel(aapl, sbus_addr, it->interrupt);
            avago_sbus_wr(aapl, sbus_addr, 0x03, (int_num << 16) | it->param);
            recv_data_back = (i == num_elements-1) ? 3 : 2;
            avago_sbus(aapl, sbus_addr, 0x04, 0x02, 0x00000000, recv_data_back);
        }
        ptr = aapl->data_char;
        for( i = 0; i < num_elements; i++ )
        {
            Avago_spico_int_t *it = &ints[i];
            if( ((it->flags & AVAGO_SPICO_INT_FIRST) && loops != 0) ||
                ((it->flags & AVAGO_SPICO_INT_NOT_FIRST) && loops == 0) )
            {
                it->ret = 0;
                continue;
            }
            ptr += strspn(ptr,";");
            it->ret = aapl_strtoul(ptr, &ptr, 2);
            if( it->ret & 0x30000 )
            {
                timeout = TRUE;
                break;
            }
        }
        if( !timeout )
            break;
        aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "Array operation timeout retry; count = %d\n",loops);
    }
    if( loops >= aapl->serdes_int_timeout )
    {
        aapl_set_spico_running_flag(aapl,sbus_addr,0);
        return aapl_fail(aapl, __func__, __LINE__, "SBus %s, Interrupt array action timed out after %d loops.\n", aapl_addr_to_str(sbus_addr), aapl->serdes_int_timeout);
    }

    return aapl->return_code == return_code ? 0 : -1;
}


/** @cond INTERNAL */

/** @return  On success, returns 0;
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_spico_int_array(Aapl_t *aapl, uint sbus_addr, int num_elements, Avago_spico_int_t *ints)
{
    int return_code = aapl->return_code;
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, num_elements = %d\n",aapl_addr_to_str(sbus_addr), num_elements);
    if (!aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F, AVAGO_PROCESS_A)) return -1;
    if (!aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_SPICO, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)) return -1;

    if (!aapl_get_spico_running_flag(aapl,sbus_addr))
        aapl_set_spico_running_flag(aapl,sbus_addr, avago_spico_running(aapl, sbus_addr));

    if (!aapl_get_spico_running_flag(aapl,sbus_addr))
    {
        return aapl_fail(aapl, __func__, __LINE__, "Interrupt array not executed because SPICO not running on SBus address %s.\n", aapl_addr_to_str(sbus_addr));
    }

    if( aapl->max_cmds_buffered >= num_elements && aapl_is_aacs_communication_method(aapl) )
        spico_int_array_batch(aapl,sbus_addr,num_elements,ints);
    else
        spico_int_array_nobatch(aapl,sbus_addr,num_elements,ints);

    return return_code == aapl->return_code ? 0 : -1;
}

/** @endcond */

/** @brief    Issue the provided interrupt to a SBM SPICO. */
static uint avago_sbm_spico_int(
    Aapl_t *aapl,   /**< [in] Pointer to AAPL structure */
    uint sbus_addr, /**< [in] SBus address of SBus Master SPICO */
    int int_num,    /**< [in] Interrupt code */
    int param)      /**< [in] Interrupt data */
{
    int loops;
    int int_data;
    uint data = 0;
    param &= 0xffff;

    if (!aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO)) return 0;

    avago_sbus_wr(aapl, sbus_addr, 0x02, (param << 16) | int_num);
    int_data = avago_sbus_rd(aapl, sbus_addr, 0x07);

    if (aapl_check_process(aapl,sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_PROCESS_A))
        int_data = int_data | 0x02;

    int_data = int_data | 0x01;
    avago_sbus_wr(aapl, sbus_addr, 0x07, int_data);
    int_data = int_data ^ 0x01;
    avago_sbus_wr(aapl, sbus_addr, 0x07, int_data);

    loops = 0;

    if (aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr)) <= 0xbd)
    {
        for (loops = 0; loops <= aapl->serdes_int_timeout; loops++)
        {
            if (avago_sbus_rd(aapl, sbus_addr, 0x08) & 0x3ff)
                break;
            if( loops > 10 )
                ms_sleep(1);
        }
    }
    else
    {
        for (loops = 0; loops <= aapl->serdes_int_timeout; loops++)
        {
            if ((avago_sbus_rd(aapl, sbus_addr, 0x08) & 0x8000)==0)
                break;
            if( loops > 10 )
                ms_sleep(1);
        }
    }

    if (loops >= aapl->serdes_int_timeout)
    {
        aapl_set_spico_running_flag(aapl,sbus_addr,0);
        aapl_fail(aapl, __func__, __LINE__, "Interrupt 0x%02x,0x%04x timed out after %d loops on SBus address %s -> 0x%x.\n", int_num, param, aapl->serdes_int_timeout, aapl_addr_to_str(sbus_addr), data);
        return 0;
    }

    data = avago_sbus_rd(aapl, sbus_addr, 0x08);

    aapl_log_printf(aapl, AVAGO_DEBUG7, __func__, __LINE__, "SBus %s, loops: %d, int: 0x%02x 0x%04x -> 0x%04x.\n", aapl_addr_to_str(sbus_addr), loops, int_num, param, (data >> 16) & 0xffff);
    if ((data & 0x7fff) == 1) return (data >> 16) & 0xffff;
    else                      return ((data >> 16) & 0xffff) | ((data & 0x7fff) << 16);
}


/** @brief  Issue the interrupt to the SPICO processor, and verifies that the
 **         return value matches the interrupt number.
 ** @return TRUE for pass
 ** @return FALSE for fail
 **/
BOOL avago_spico_int_check(
    Aapl_t *aapl,           /**< [in] Pointer to AAPL structure */
    const char *caller,     /**< Caller function, usually __func__ */
    int line,               /**< Caller line number, usually __LINE__ */
    uint addr,              /**< [in] SBus address of SerDes */
    int int_num,            /**< [in] Interrupt code */
    int param)              /**< [in] Interrupt data */
{
    int rc = avago_spico_int(aapl, addr, int_num, param);
    if( (rc & 0xff) != (int_num & 0xff) )
    {
        aapl_fail(aapl, caller, line, "spico_int returned incorrect value. SBus %s, spico_int(0x%x, 0x%x) returned 0x%x\n",aapl_addr_to_str(addr), int_num, param, rc);
        return FALSE;
    }
    return TRUE;
}


/** @brief  Issue the interrupt to the SPICO processor.
 ** @return The return value depends on the interrupt.
 **         For 28nm, it is often the same as the interrupt number.
 **         See the firmware documentation for details.
 **/
uint avago_spico_int(
    Aapl_t *aapl,   /**< [in] Pointer to AAPL structure */
    uint sbus_addr, /**< [in] SBus address of SerDes */
    int int_num,    /**< [in] Interrupt code */
    int param)      /**< [in] Interrupt data */
{
    BOOL st;
    int rc = 0;
    int return_code = aapl->return_code;

    Avago_addr_t addr_struct, start, stop, next;
    avago_addr_to_struct(sbus_addr, &addr_struct);
    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);
        if (aapl_get_ip_type(aapl, sbus_addr) != AVAGO_SERDES &&
            aapl_get_ip_type(aapl, sbus_addr) != AVAGO_M4 &&
            aapl_get_ip_type(aapl, sbus_addr) != AVAGO_P1 &&
            aapl_get_ip_type(aapl, sbus_addr) != AVAGO_SPICO ) continue;

        if( !aapl_get_spico_running_flag(aapl,sbus_addr) )
            aapl_set_spico_running_flag(aapl,sbus_addr,avago_spico_running(aapl, sbus_addr));

        if( !aapl_get_spico_running_flag(aapl,sbus_addr) )
        {
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__,
                "SBus %s, Interrupt 0x%02x,0x%04x not executed because SPICO not running.\n", aapl_addr_to_str(sbus_addr), int_num, param);
            return 0;
        }
    }

    if (aapl->capabilities & AACS_SERVER_SPICO_INT)
    {
        char spico_cmd_buffer[64];
        uint ret;
        if( aapl->capabilities & AACS_SERVER_NO_CRC )
        {
            uint addr = sbus_addr & 0xffff;
            int_num |= add_int_slice_sel(aapl, sbus_addr, int_num);
            snprintf(spico_cmd_buffer, 63, "spico_int 0x%02x 0x%04x 0x%04x", addr, int_num, param);
        }
        else
            snprintf(spico_cmd_buffer, 63, "spico_int %s 0x%04x 0x%04x", aapl_addr_to_str(sbus_addr), int_num, param);

        avago_aacs_send_command_options(aapl, spico_cmd_buffer, /* recv_data_back */ 1, /* strtol */ 16);
        ret = aapl->data;
        aapl_log_printf(aapl, AVAGO_DEBUG7, __func__, __LINE__, "%s -> 0x%04x\n", spico_cmd_buffer, ret);
        return ret;
    }

    switch( aapl_get_process_id(aapl, sbus_addr) )
    {
    case AVAGO_PROCESS_C:
    case AVAGO_PROCESS_B:
    case AVAGO_PROCESS_F:
        switch( aapl_get_ip_type(aapl, sbus_addr) )
        {
        case AVAGO_SERDES_BROADCAST:
        case AVAGO_P1:
        case AVAGO_M4:
        case AVAGO_SERDES: rc = avago_serdes_spico_int(aapl,sbus_addr,int_num,param); break;
        case AVAGO_SPICO:  rc = avago_sbm_spico_int(aapl,sbus_addr,int_num,param); break;
        default: break;
        }
        break;

    case AVAGO_PROCESS_A:
        if( aapl_get_ip_type(aapl, sbus_addr) == AVAGO_SPICO )
            rc = avago_sbm_spico_int(aapl,sbus_addr,int_num,param);
        break;

    default:
        aapl_fail(aapl, __func__, __LINE__, "SBus %s, IP type 0x%x, in process %s, is not supported.\n",
                    aapl_addr_to_str(sbus_addr), aapl_get_ip_type(aapl, sbus_addr),
                    aapl_get_process_id_str(aapl,sbus_addr));
        return 0;
        break;
    }





#if AAPL_ENABLE_MAIN && AAPL_ENABLE_DIAG
    if (aapl->diag_on_failure && return_code != aapl->return_code)
    {
        Avago_diag_config_t *config = avago_diag_config_construct(aapl);
        avago_diag(aapl, sbus_addr, config);
        avago_diag_config_destruct(aapl, config);
        aapl->diag_on_failure--;
    }
#else
    (void) return_code;
#endif

    return rc;
}


/**
 ** @brief TBD: Documentation to be completed
 ** @return TBD: Documentation to be completed
 **/
uint avago_spico_broadcast_int(Aapl_t *aapl, int int_num, int param, int args, ...)
{
    int i;
    va_list sbus_rx_list;
    va_start(sbus_rx_list, args);

    for( i=0; i<args; i++ )
        avago_spico_int(aapl, va_arg(sbus_rx_list, uint), int_num, param);

    va_end(sbus_rx_list);
    return aapl->return_code;
}


/**
 ** @brief TBD: Documentation to be completed
 ** @return TBD: Documentation to be completed
 **/
uint avago_spico_broadcast_int_w_mask(Aapl_t *aapl, uint addr_mask, int int_num, int param, int args, ...)
{
    int i;
    va_list sbus_rx_list;
    va_start(sbus_rx_list, args);

    for( i=0; i<args; i++ )
    {
        uint this_addr = va_arg(sbus_rx_list, uint);
        if( (addr_mask & (1U << i)) == (1U << i) )
        {
            avago_spico_int(aapl, this_addr, int_num, param);
        }
    }

    va_end(sbus_rx_list);
    return aapl->return_code;
}

#if AAPL_ALLOW_MDIO || AAPL_ALLOW_GPIO_MDIO
static void mdio_burst_upload(Aapl_t *aapl, Avago_addr_t addr_struct, int words, const int rom[])
{
    uint burst_word = 0x00000000;
    int word, burst_cnt = 0;

    if (addr_struct.sbus == 0xfd)
    {
        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, 32779, 0x14fd);
        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, 32778, 0x0001);
    }
    else
    {
        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, 32781, (0x0a00 | (0x00ff & addr_struct.sbus)));
        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, 32780, 0x0001);
    }
    avago_mdio(aapl, AVAGO_MDIO_ADDR, addr_struct.chip, AVSP_DEVAD, 32771);

    for(  word = 0; word < words; word++ )
    {
        burst_word = burst_word | (rom[word] << (10 * burst_cnt));
        if (burst_cnt == 2)
        {
            burst_word = burst_word | 0xc0000000;
            avago_mdio(aapl, AVAGO_MDIO_WRITE, addr_struct.chip, AVSP_DEVAD, (burst_word & 0x0000ffff));
            avago_mdio(aapl, AVAGO_MDIO_WRITE, addr_struct.chip, AVSP_DEVAD, ((burst_word & 0xffff0000) >> 16));
            burst_cnt = 0;
            burst_word = 0x00000000;
        }
        else burst_cnt++;
    }

    if (burst_cnt != 0)
    {
        burst_word = burst_word | (burst_cnt << 30);
        avago_mdio(aapl, AVAGO_MDIO_WRITE, addr_struct.chip, AVSP_DEVAD, (burst_word & 0x0000ffff));
        avago_mdio(aapl, AVAGO_MDIO_WRITE, addr_struct.chip, AVSP_DEVAD, ((burst_word & 0xffff0000) >> 16));
    }

    if (addr_struct.sbus == 0xfd) avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, 32778, 0x0000);
    else                          avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, 32780, 0x0000);
}
#endif

static void spico_burst_upload(Aapl_t *aapl, uint sbus, uint reg, uint rom_size, const int *rom)
{
    uint word;
    aapl_log_printf(aapl,AVAGO_DEBUG7,__func__,__LINE__,"sbus=0x%02x, reg=0x%x, rom_size=%u\n",sbus,reg,rom_size);
    for( word=0; word < rom_size-2; word += 3 )
        avago_sbus_wr(aapl, sbus, reg, 0xc0000000 | rom[word] | (rom[word+1] << 10) | (rom[word+2] << 20));
    if( rom_size - word == 2 )
        avago_sbus_wr(aapl, sbus, reg, 0x80000000 | rom[word] | (rom[word+1] << 10));
    else if( rom_size - word == 1 )
        avago_sbus_wr(aapl, sbus, reg, 0x40000000 | rom[word]);
}

/** @brief   Internal function that uploads the ROM blindly to the sbus_addr.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
static int spico_upload_image(Aapl_t *aapl, uint sbus_addr, int words, const int rom[])
{
    int return_code = aapl->return_code;

    if (aapl_check_process(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F))
    {
        Avago_addr_t addr_struct;
        avago_addr_to_struct(sbus_addr,&addr_struct);
        if( aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, FALSE, 6,
                AVAGO_SERDES, AVAGO_SERDES_D6_BROADCAST,
                AVAGO_M4, AVAGO_SERDES_M4_BROADCAST,
                AVAGO_P1, AVAGO_SERDES_P1_BROADCAST) )
        {
            avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000011);
            avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000010);
            avago_sbus_wr(aapl, sbus_addr, 0x08, 0x00000030);
            avago_sbus_wr(aapl, sbus_addr, 0x00, 0xc0000000);

#if AAPL_ALLOW_MDIO || AAPL_ALLOW_GPIO_MDIO
            if( aapl_is_mdio_communication_method(aapl) )
                mdio_burst_upload(aapl, addr_struct, words, rom);
            else
#endif
            {
                if( aapl_get_lsb_rev(aapl, sbus_addr) <= 2 )
                {
                    int word;
                    for (word=0; word < words; word++)
                        avago_sbus_wr(aapl, sbus_addr, 0x00, 0xc0000000 | (rom[word] << 16) | word);
                }
                else
                    spico_burst_upload(aapl, sbus_addr, 0x0a, words, rom);
            }

            avago_sbus_wr(aapl, sbus_addr, 0x00, 0x00000000);
            avago_sbus_wr(aapl, sbus_addr, 0x0b, 0x000c0000);
            avago_sbus_wr(aapl, sbus_addr, 0x0c, 0xc0000000);
            avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000002);
            avago_sbus_wr(aapl, sbus_addr, 0x08, 0x00000000);
        }
        else if (aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, TRUE, 2, AVAGO_SPICO, AVAGO_SPICO_BROADCAST))
        {
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x000000c0);
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000040);
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000240);

#if AAPL_ALLOW_MDIO || AAPL_ALLOW_GPIO_MDIO
            if( aapl_is_mdio_communication_method(aapl) )
                mdio_burst_upload(aapl, addr_struct, words, rom);
            else
#endif
            {
                int rev = aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr));
                if( rev >= 0xbe
                   || aapl_get_process_id(aapl, sbus_addr) == AVAGO_PROCESS_B )
                {
                    avago_sbus_wr(aapl, sbus_addr, 0x03, 0x00000000);
                    avago_sbus_wr(aapl, sbus_addr, 0x03, 0x80000000);
                    spico_burst_upload(aapl, sbus_addr, 0x14, words, rom);
                }
                else
                {
                    int word;
                    for( word=0; word < words; word++ )
                        avago_sbus_wr(aapl, sbus_addr, 0x03, 0x80000000 | (rom[word] << 16) | word);
                }
            }

            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000040);
            avago_sbus_wr(aapl, sbus_addr, 0x16, 0x000c0000);
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000140);
        }
    }
    else if (aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_PROCESS_A))
    {
        if (aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO))
        {
            int word;
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x000000c0);
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000040);
            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x40000000);

            for (word=0; word < words; word++)
                avago_sbus_wr(aapl, sbus_addr, 0x03, 0xc0000000 | (rom[word] << 16) | word);

            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x00000000);
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000140);
            avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000002);
        }
    }
    return aapl->return_code == return_code ? 0 : -1;
}


/** @cond INTERNAL */

/** @brief   Internal function that uploads SWAP image into SBM.
 ** @return  Returns 1 on success, 0 on failure.
 **/
int avago_spico_upload_swap_image(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint sbus_addr_in,  /**< [in] SBus address of SerDes */
    int words,          /**< [in] Number of elements in rom */
    const int *rom)     /**< [in] Swap image to upload */
{
    int crc = 0;
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    if( !aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 4, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_M4, AVAGO_P1) ||
        !aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 2, AVAGO_PROCESS_B, AVAGO_PROCESS_F) )
        return 0;

    avago_addr_to_struct(avago_make_sbus_master_addr(sbus_addr_in), &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
            continue;

        avago_firmware_get_rev(aapl, sbus_addr);
        if( !aapl_get_spico_running_flag(aapl,sbus_addr) )
        {
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Swap image can not be uploaded because the SPICO at address %s is not running.\n", aapl_addr_to_str(sbus_addr));
            continue;
        }

        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus %s, Uploading %d bytes of SerDes swap machine code.\n", aapl_addr_to_str(sbus_addr), words);

        avago_sbus_rmw(aapl, sbus_addr, 7, 0, 2);

        if( aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr)) >= 0x00be )
        {
            int base_addr = avago_spico_int(aapl, sbus_addr, 0x1c, 0);
            aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s, Loading Swap Image to production SBM, base_addr=0x%x \n",aapl_addr_to_str(sbus_addr), base_addr);

            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x01);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0200, 0x0200);
            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x00000000 | base_addr);
            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x80000000 | base_addr);

            spico_burst_upload(aapl, sbus_addr, 0x14, words, rom);

            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x00000000);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0000, 0x0200);
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x00);
            crc = avago_spico_int(aapl, sbus_addr, 0x1a, 0);
        }
        else
        {
            int base_addr = 0x400;
            int word;
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus %s, Loading Swap Image to test chip SBM, base_addr=0x%x \n",aapl_addr_to_str(sbus_addr), base_addr);
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x01);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0C00, 0x0C00);
            for( word=0; word < words; word++ )
                avago_sbus_wr(aapl, sbus_addr, 0x04, 0x8000 | (rom[word] << 16) | (base_addr+word));
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0000, 0x0C00);
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x00);
            crc = avago_spico_int(aapl, sbus_addr, 0x04, 0);
        }
        if( crc == 1 )
            aapl_log_printf(aapl, AVAGO_DEBUG2, __func__,__LINE__,"SBus %s, Swap CRC passed\n", aapl_addr_to_str(sbus_addr));
        else
        {
            aapl_fail(aapl, __func__, __LINE__, "SBus %s, Swap CRC failed, interrupt returned %d\n", aapl_addr_to_str(sbus_addr), crc);
            crc = 0;
        }
    }
    return crc;
}

void aapl_crc_one_byte(int *crc_ptr, int value)
{
    int crc = *crc_ptr;
    crc += value;
    crc ^= 0xd8;
    if( crc & 0x80000000 )
        crc = (crc << 1) + 229;
    else
        crc <<= 1;
    *crc_ptr = crc;
}

int aapl_crc_rom(int *memory, int length)
{
    int i, crc = 0;
    for (i = 0; i < length; i++)
        aapl_crc_one_byte(&crc, memory[i]);
    return crc ^ 0xdeadbeef;
}

/** @endcond */


/** @brief   Upload SPICO machine code and check CRC.
 **          Works for broadcast and individual addresses.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_spico_upload(
    Aapl_t *aapl,       /**< Pointer to Aapl_t structure */
    uint sbus_addr_in,  /**< Sbus address */
    BOOL ram_bist,      /**< If TRUE, perform spico_ram_bist prior to upload */
    int words,          /**< Length of ROM image */
    const int *rom)     /**< Avago-supplied ROM image */
{
    int return_code = aapl->return_code;
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    if( !aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 8, AVAGO_SPICO, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_SPICO_BROADCAST, AVAGO_M4, AVAGO_SERDES_M4_BROADCAST, AVAGO_P1, AVAGO_SERDES_P1_BROADCAST) ||
        !aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_A, AVAGO_PROCESS_F, AVAGO_PROCESS_B) )
        return 0;

    if (words <= 0)
    {
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "0 byte image specified. Skipping upload to %s.\n", aapl_addr_to_str(sbus_addr_in));
        return 0;
    }

    avago_addr_to_struct(sbus_addr_in, &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        BOOL ignore = FALSE;
        uint sbus_addr = avago_struct_to_addr(&next);

        if( !aapl_addr_selects_fw_device(aapl, &addr_struct, sbus_addr, &ignore) )
        {
            if( ignore )
                aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Skipping reset of SBus address %s because an upload was requested to %s and the ignore broadcast bit on this SerDes was set.\n", aapl_addr_to_str(sbus_addr), aapl_addr_to_str(sbus_addr_in));
            continue;
        }

        avago_sbus_reset(aapl, sbus_addr, 0);
        aapl_set_spico_running_flag(aapl,sbus_addr,0);
        if( ram_bist )
            avago_spico_ram_bist(aapl, sbus_addr);
    }

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Uploading %d bytes of SPICO machine code to SBus address %s.\n", words, aapl_addr_to_str(sbus_addr_in));
    spico_upload_image(aapl, sbus_addr_in, words, rom);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        BOOL ignore = FALSE;
        uint sbus_addr = avago_struct_to_addr(&next);

        if( !aapl_addr_selects_fw_device(aapl, &addr_struct, sbus_addr, &ignore) )
        {
            if( ignore )
                aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Skipping CRC check of SBus address %s because an upload was requested to %s and the ignore broadcast bit on this SerDes was set.\n", aapl_addr_to_str(sbus_addr), aapl_addr_to_str(sbus_addr_in));
            continue;
        }
        aapl_set_spico_running_flag(aapl, sbus_addr, 1);
        if( avago_spico_crc(aapl, sbus_addr) )
            aapl_set_ip_type(aapl, sbus_addr);
        if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
        {
            int end_addr = avago_spico_int(aapl, sbus_addr, 0x1c, 0);
            aapl_set_spico_running_flag(aapl, sbus_addr, 1);
            if( end_addr < words )
            {
                int crc = avago_spico_int(aapl, sbus_addr, 0x1a, 0);
                if( crc )
                    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s, SDI CRC passed.\n", aapl_addr_to_str(sbus_addr));
                else
                    aapl_fail(aapl, __func__, __LINE__, "SBus %s, SDI CRC failed. CRC interrupt returned 0x%04x\n", aapl_addr_to_str(sbus_addr), crc);
            }
        }
    }
    return return_code == aapl->return_code ? 0 : -1;
}


/** @brief   Resets and uploads all the Avago firmware for the device.
 ** @details Makes the device ready for additional configuration by performing
 **          soft resets and sequencing the uploads for correct operation.
 ** @details The SerDes ROM image is directly loaded to the SerDes on the
 **          addressed chip(s) and ring(s).  The SBM ROM image is directly
 **          uploaded to the SBus Master processor.  If specified, the SDI ROM
 **          image is appended to the SBus Master image in the target processor
 **          memory.  If the SBM ROM image already has an SDI (with swap and/or
 **          a state table) appended, or no SDI image is needed, the sbm_rom
 **          pointer should be NULL.
 **
 **          The SDI ROM contains SerDes swap images, an AVSP state table,
 **          or both.  Note that SerDes swap images are already in the SDI
 **          format.
 **
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_firmware_upload_file().
 **/
int avago_firmware_upload(
    Aapl_t    *aapl,            /**< Pointer to Aapl_t structure. */
    uint       addr,            /**< SerDes/chip/ring addresses targeted. */
    int        serdes_rom_size, /**< Size of SerDes ROM image. */
    const int *serdes_rom,      /**< Pointer to SerDes ROM image. */
    int        sbm_rom_size,    /**< Size of SBM ROM image. */
    const int *sbm_rom,         /**< Pointer to SBM ROM image. */
    int        sdi_rom_size,    /**< Size of sdi (swap) ROM image. */
    const int *sdi_rom)         /**< Pointer to sdi (swap) ROM image. */
{
    int return_code = aapl->return_code;
    uint sbm_addr = avago_make_sbus_master_addr(addr);

    avago_spico_upload(aapl, addr, TRUE, serdes_rom_size, serdes_rom);
    if( 0 == avago_spico_upload(aapl, sbm_addr, TRUE, sbm_rom_size, sbm_rom)
        && sdi_rom && sdi_rom_size > 0 )
    {
        if( aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(addr)) >= 0x00be )
        {
            int end_addr = avago_spico_int(aapl, sbm_addr, 0x1c, 0);
            if( end_addr == sbm_rom_size )
                avago_spico_upload_swap_image(aapl, addr, sdi_rom_size, sdi_rom);
            else
                aapl_log_printf(aapl, AVAGO_WARNING, __func__,__LINE__,
                    "Skipping swap/SDI ROM upload because SBus Master image already contains an SDI image.\n");
        }
        else
            avago_spico_upload_swap_image(aapl, addr, sdi_rom_size, sdi_rom);
    }

    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief   Runs RAM BIST on given SBus address.
 ** @details Works for broadcast and individual addresses.
 ** @return  On success, returns 0.
 **          On error, decrements aapl->return_code and returns -1.
 **/
int avago_spico_ram_bist(
    Aapl_t *aapl,           /**< Pointer to Aapl_t structure */
    uint sbus_addr_in)      /**< Sbus address */
{
    int return_code = aapl->return_code;
    int loops;
    uint data = 0;
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    if( !aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 8, AVAGO_SERDES, AVAGO_SPICO,
            AVAGO_SERDES_BROADCAST, AVAGO_SPICO_BROADCAST, AVAGO_M4, AVAGO_SERDES_M4_BROADCAST, AVAGO_P1, AVAGO_SERDES_P1_BROADCAST) ||
        !aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F, AVAGO_PROCESS_A) )
        return 0;

    avago_addr_to_struct(sbus_addr_in, &addr_struct);
    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        uint rambist_mask = 0;
        uint sbus_addr = avago_struct_to_addr(&next);

        if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
        {
            avago_sbus_wr(aapl, sbus_addr, 0x00, 0x03);
            aapl_set_spico_running_flag(aapl,sbus_addr,0);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x080, 0x180);
            avago_sbus_wr(aapl, sbus_addr, 0x00, 0x05);
            for( loops=0; loops<=aapl->serdes_int_timeout; loops++ )
            {
                data = avago_sbus_rd(aapl, sbus_addr, 0x00);
                if( data & 0x18 ) break;
            }

            if( loops >= aapl->serdes_int_timeout )
                aapl_fail(aapl, __func__, __LINE__, "SBus master SPICO RAM BIST timed out on SBus address %s -> 0x%x.\n", aapl_addr_to_str(sbus_addr), data);
            else if( (data & 0x18) == 0x08 )
                aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus master SPICO RAM BIST test on SBus address %s passed.\n", aapl_addr_to_str(sbus_addr));
            else
                aapl_fail(aapl, __func__, __LINE__, "SBus master SPICO RAM BIST on SBus %s failed -> 0x%x.\n", aapl_addr_to_str(sbus_addr), data);

            avago_sbus_wr(aapl, sbus_addr, 0x00, 0x01);
            continue;
        }

        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) )
            continue;

        if( start.sbus != stop.sbus && (avago_sbus_rd(aapl, sbus_addr, 0xfd) & 0x1) == 0x1 )
        {
            aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Skipping RAM BIST check of SBus address %s because a RAM BIST test was requested to %s and the ignore broadcast bit on this serdes was set.\n", aapl_addr_to_str(sbus_addr), aapl_addr_to_str(sbus_addr_in));
            continue;
        }

        if( (aapl_get_lsb_rev(aapl, sbus_addr) < 5) && (aapl_get_process_id(aapl,sbus_addr) == AVAGO_PROCESS_F) )
            rambist_mask = 8;

        avago_sbus_wr(aapl, sbus_addr, 0x09, 0x00 | rambist_mask);
        data = avago_sbus_rd(aapl, sbus_addr, 0x09);

        if ((data & 0x001f) != rambist_mask)
        {
            aapl_fail(aapl, __func__, __LINE__, "0x%02x, RAM BIST setup failed. Returned value: 0x%08x, expecting: 0x%08x.\n", sbus_addr, data, rambist_mask);
            avago_sbus_wr(aapl, sbus_addr, 0x09, rambist_mask);
            continue;
        }

        aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "Performing RAM BIST check of SBus address %s because a RAM BIST test was requested to %s.\n", aapl_addr_to_str(sbus_addr), aapl_addr_to_str(sbus_addr_in));
        aapl_set_spico_running_flag(aapl,sbus_addr,0);
        avago_sbus_wr(aapl, sbus_addr, 0x07, 0x11);
        avago_sbus_wr(aapl, sbus_addr, 0x09, 0x03 | rambist_mask);

        for( loops=0; loops<=aapl->serdes_int_timeout; loops++ )
        {
            data = avago_sbus_rd(aapl, sbus_addr, 0x09);
            if( data & 0x3f0060 )
                break;

            if( aapl_get_lsb_rev(aapl, sbus_addr) >= 3 && aapl_get_lsb_rev(aapl, sbus_addr) < 8 )
            {
                if( (data & 0x3f00) == 0x0300 )
                    break;
            }
        }

        if (loops >= aapl->serdes_int_timeout)
        {
            aapl_fail(aapl, __func__, __LINE__, "SBus %s, RAM BIST timed out -> 0x%x\n", aapl_addr_to_str(sbus_addr), data);
        }
        else if ((data & 0x3f0040) != 0x0)
            aapl_fail(aapl, __func__, __LINE__, "SBus %s, RAM BIST failed -> 0x%x.\n", aapl_addr_to_str(sbus_addr), data);
        else
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus %s, RAM BIST test passed.\n", aapl_addr_to_str(sbus_addr));

        avago_sbus_wr(aapl, sbus_addr, 0x09, rambist_mask);
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/** @brief  Gets the revision of the firmware loaded into the SPICO processor.
 ** @return  On success, returns the firmware revision.
 **          If SPICO is stopped, returns 0.
 ** @see avago_firmware_get_build_id().
 **/
uint avago_firmware_get_rev(
    Aapl_t *aapl,   /**< Pointer to Aapl_t structure */
    uint addr)      /**< Sbus address of the SPICO to check. */
{
    uint rc = 0;
    Avago_process_id_t process_id = aapl_get_process_id(aapl,addr);
    if( process_id == AVAGO_PROCESS_F || process_id == AVAGO_PROCESS_B || process_id == AVAGO_PROCESS_C )
    {
        if( aapl_check_ip_type(aapl,addr, __func__, __LINE__, TRUE, 4, AVAGO_SERDES, AVAGO_SPICO, AVAGO_M4, AVAGO_P1) )
            rc = avago_spico_int(aapl, addr, 0, 0);
    }
    else if( process_id == AVAGO_PROCESS_A )
    {
        if( aapl_check_ip_type(aapl,addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO) )
            rc = avago_spico_int(aapl, addr, 1, 0);
    }
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, fw_rev = 0x%04x.\n", aapl_addr_to_str(addr), rc);
    return rc;
}

/** @brief  Gets the build id of the firmware loaded into the SPICO processor.
 ** @return On success, returns the firmware build id.
 **         If SPICO is stopped, returns 0.
 ** @see    avago_firmware_get_rev().
 **/
uint avago_firmware_get_build_id(
    Aapl_t *aapl,   /**< Pointer to Aapl_t structure */
    uint addr)      /**< Sbus address of the SPICO to check. */
{
    uint rc = 0;
    Avago_process_id_t process_id = aapl_get_process_id(aapl,addr);
    if( process_id == AVAGO_PROCESS_F || process_id == AVAGO_PROCESS_B || process_id == AVAGO_PROCESS_C )
    {
        if( aapl_check_ip_type(aapl,addr, __func__, __LINE__, TRUE, 4, AVAGO_SERDES, AVAGO_SPICO, AVAGO_M4, AVAGO_P1) )
        {
            if( aapl_check_ip_type(aapl,addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) )
                rc = avago_spico_int(aapl, addr, 0x3f, 0);
            else
                rc = avago_spico_int(aapl, addr, 0x01, 0);
        }
    }
    else if( process_id == AVAGO_PROCESS_A )
    {
        if( aapl_check_ip_type(aapl,addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO) )
            rc = avago_spico_int(aapl, addr, 0x00, 0);
    }
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, fw_build_id = %04X.\n", aapl_addr_to_str(addr), rc);
    return rc;
}

/** @brief  Return the CRC checksum of the firmware image on sbus_addr.
 **
 ** @return 0 - CRC checksum failed
 ** @return 1 - CRC checksum passed
 **/
uint avago_spico_crc(
    Aapl_t *aapl,       /**< Pointer to Aapl_t structure */
    uint sbus_addr)     /**< Sbus address */
{
    int crc_status = 0;
    int crc = 1;
    int return_code = aapl->return_code;
    int running;

    if (!aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F, AVAGO_PROCESS_A)) return 0;
    if (aapl->capabilities & AACS_SERVER_NO_CRC)
    {
        aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s, CRC skipped due to aapl->capabilities AACS_SERVER_NO_CRC set. CRC passed.\n", aapl_addr_to_str(sbus_addr));
        return 1;
    }

    switch( aapl_get_process_id(aapl, sbus_addr) )
    {
    case AVAGO_PROCESS_C:
    case AVAGO_PROCESS_B:
    case AVAGO_PROCESS_F:
        if(!aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 7, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_SPICO, AVAGO_M4, AVAGO_SERDES_M4_BROADCAST, AVAGO_P1, AVAGO_SERDES_P1_BROADCAST)) return 0;
        if(aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 6, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_M4, AVAGO_SERDES_M4_BROADCAST, AVAGO_P1, AVAGO_SERDES_P1_BROADCAST))
        {
            crc = avago_spico_int(aapl, sbus_addr, 0x3c, 0);
            crc_status = crc == 0;
        }
        else if (aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO))
        {
            crc = avago_spico_int(aapl, sbus_addr, 0x2, 0);
            crc_status = crc == 1;
        }
        break;

    case AVAGO_PROCESS_A:
        if( !aapl_check_ip_type(aapl,sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO) ) return 0;
        crc = avago_spico_int(aapl, sbus_addr, 0x02, 0);
        crc_status = crc == 1;
        break;

    default: break;
    }

    running = aapl_get_spico_running_flag(aapl,sbus_addr);
    if( crc_status && return_code == aapl->return_code && running )
    {
        aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s, CRC passed.\n", aapl_addr_to_str(sbus_addr));
        return 1;
    }
    aapl_fail(aapl, __func__, __LINE__, "SBus %s, CRC failed. CRC interrupt returned 0x%04x. Running: %d.\n", aapl_addr_to_str(sbus_addr), crc, running);
    return 0;
}

/** @brief   Resets a SerDes SPICO processor.
 ** @details Supports broadcast addresses.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_spico_reset(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr)     /**< [in] SBus slice address. */
{
    int return_code = aapl->return_code;
    if (!aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F))
        return -1;
    if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) )
    {
        avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000011);
        avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000010);
        avago_sbus_wr(aapl, sbus_addr, 0x0b, 0x000c0000);
        avago_sbus_wr(aapl, sbus_addr, 0x0c, 0xc0000000);
        avago_sbus_wr(aapl, sbus_addr, 0x07, 0x00000002);
        avago_sbus_wr(aapl, sbus_addr, 0x08, 0x00000000);
    }
    else if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_SPICO) )
    {
        avago_sbus_wr(aapl, sbus_addr, 0x01, 0x000000c0);
        avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000040);
        avago_sbus_wr(aapl, sbus_addr, 0x16, 0x000c0000);
        avago_sbus_wr(aapl, sbus_addr, 0x01, 0x00000140);
    }
    return return_code == aapl->return_code ? 0 : -1;
}

#if AAPL_ENABLE_FILE_IO

/** @brief   Load a valid Avago-supplied ROM image into memory.
 ** @details Caller should call aapl_free(aapl, rom_ptr, __func__)
 **          when finished with the ROM image.
 **
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_load_rom_from_file(
    Aapl_t *aapl,           /**< Pointer to Aapl_t structure */
    const char *filename,   /**< Full path to a valid Avago-supplied ROM image */
    int *rom_size,          /**< [out] Address to receive length of image */
    int **rom_ptr)          /**< [out] Address to receive ROM image */
{
    int *rom, addr = 0;
    char mem_buffer[6];
    FILE *file = NULL;

    if( filename )
        file = fopen(filename, "r");

    *rom_ptr = 0;
    if( !file )
        return aapl_fail(aapl, __func__, __LINE__, "## ERROR opening file %s: %s\n",filename,strerror(errno));

    fseek(file, 0, SEEK_END);
    *rom_size = ftell(file) / 4;
    rewind(file);
    if( *rom_size < 50 )
    {
        fclose(file);
        return aapl_fail(aapl, __func__, __LINE__, "## ERROR: invalid file: %s\n",filename);
    }

    rom = (int*) aapl_malloc(aapl, sizeof(int) * (*rom_size + 2), filename);
    if( !rom )
    {
        fclose(file);
        return -1;
    }


    while( fgets(mem_buffer, 6, file) )
    {
        char *ptr;
        rom[addr] = aapl_strtol(mem_buffer, &ptr, 16);
        if( ptr != mem_buffer+3 && (ptr != mem_buffer+4 || mem_buffer[3] != '\r') )
        {
            fclose(file);
            free(rom);
            return aapl_fail(aapl, __func__, __LINE__, "## ERROR: %s has invalid file format\n",filename);
        }
        addr ++;
    }
    *rom_size = addr;

    rom[*rom_size+0] = 0;
    rom[*rom_size+1] = 0;

    fclose(file);
    *rom_ptr = rom;
    return 0;
}

/** @brief Search for existing swap file.
 ** @details The swap name is assumed to have the same path as the SerDes
 **          ROM file, but with the ".rom" suffix replaced with ".swap".
 ** @return Name of existing swap file, or NULL if no swap file.
 **         A non-NULL return value should be released using aapl_free().
 **/
char *avago_find_swap_file(
    Aapl_t *aapl,           /**< Pointer to Aapl_t structure */
    const char *filename)   /**< Path to a valid Avago-supplied SerDes ROM image */
{
    FILE *file;
    uint name_len = strlen(filename);
    char *swap_file = (char *)aapl_malloc(aapl, name_len + 8, __func__);
    strcpy(swap_file, filename);
    if( name_len >= 4 && 0 == strcmp(swap_file + name_len - 4,".rom") )
        name_len -= 4;
    strcpy(swap_file + name_len, ".swap");
    file = fopen(swap_file, "r");
    if( file )
    {
        fclose(file);
        return swap_file;
    }
    aapl_free(aapl, swap_file, __func__);
    return NULL;
}

/** @brief   Upload SPICO machine code and check CRC.
 ** @details Works for broadcast and individual addresses.
 **
 ** @return  On success, returns the number of 10 bit words in the ROM image.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_spico_upload_file(
    Aapl_t *aapl,           /**< Pointer to Aapl_t structure */
    uint sbus_addr,         /**< Sbus address of device to upload to */
    BOOL ram_bist,          /**< Perform spico_ram_bist prior to upload */
    const char *filename)   /**< Full path to a valid Avago-supplied ROM image */
{
    int return_code = aapl->return_code;
    int rom_size = -1, *rom;

    if( avago_load_rom_from_file(aapl, filename, &rom_size, &rom) == 0 )
    {
        aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Uploading SPICO machine code: %s\n", filename);
        if( avago_spico_upload(aapl, sbus_addr, ram_bist, rom_size, rom) == 0 )
        {
            char *swap_file = avago_find_swap_file(aapl, filename);
            if( swap_file )
            {
                int swap_size, *swap;
                if( avago_load_rom_from_file(aapl, swap_file, &swap_size, &swap) == 0 )
                {
                    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Uploading swap image: %s\n", swap_file);
                    if( avago_spico_upload_swap_image(aapl, sbus_addr, swap_size, swap) < 0 )
                        aapl_fail(aapl, __func__, __LINE__, "CRC of swap image failed (%s)\n.",swap_file);
                    aapl_free(aapl, swap, __func__);
                }
                aapl_free(aapl, swap_file, __func__);
            }
        }
        aapl_free(aapl, rom, __func__);
    }
    return return_code == aapl->return_code ? rom_size : -1;
}

/** @brief   Verifies the CRC on a single ROM image.
 ** @return  TRUE if the CRC is valid, FALSE if not valid.
 **/
static BOOL aapl_verify_rom_crc(int rom_size, int *rom)
{
    int crc = aapl_crc_rom(rom,rom_size-4);
    int *ptr = rom + rom_size - 5;
    return  ptr[0] == 0x4e
         && ptr[1] == ((crc >>  0) & 0xff)
         && ptr[2] == ((crc >>  8) & 0xff)
         && ptr[3] == ((crc >> 16) & 0xff)
         && ptr[4] == ((crc >> 24) & 0xff);
}

static BOOL aapl_sbm_rom_has_sdi(int sbm_rom_size, int *sbm_rom)
{
    return !aapl_verify_rom_crc(sbm_rom_size, sbm_rom);
}

/** @details NOTE: May modify sbm_rom and sdi_rom values on return.
 **
 ** @return 0 if there were no conflicts.
 ** @return -1 and decrement aapl->return_code if conflicting swap images or tables were given.
 **/
static int merge_sdi_files(
    Aapl_t *aapl,
    int *sbm_rom_size, int **sbm_rom,
    int *sdi_rom_size, int **sdi_rom,
    int *swap_rom_size, int **swap_rom)
{

    if( (*sdi_rom_size > 0 || *swap_rom_size > 0) && aapl_sbm_rom_has_sdi(*sbm_rom_size, *sbm_rom) )
    {
        if( *sbm_rom_size > *sdi_rom_size && *sdi_rom_size > 0 )
        {
            if( 0 == memcmp(*sbm_rom + *sbm_rom_size - *sdi_rom_size, *sdi_rom, *sdi_rom_size) )
            {
                aapl_free(aapl, *sdi_rom, __func__);
                *sdi_rom = 0;
                *sdi_rom_size = 0;
            }
            else
                return aapl_fail(aapl,__func__,__LINE__,"SDI ROM cannot be uploaded because SBM already has an appended SDI.\n");
        }

        if( *sbm_rom_size > *swap_rom_size && *swap_rom_size > 0 )
        {
            if( 0 == memcmp(*sbm_rom + *sbm_rom_size - *swap_rom_size, *swap_rom, *swap_rom_size) )
            {
                aapl_free(aapl, *swap_rom, __func__);
                *swap_rom = 0;
                *swap_rom_size = 0;
            }
            else
                return aapl_fail(aapl,__func__,__LINE__,"SWAP ROM cannot be uploaded because SBM already has an appended SDI.\n");
        }
    }

    if( *sdi_rom_size == *swap_rom_size
        && *sdi_rom_size > 0
        && 0 == memcmp(*sdi_rom,*swap_rom,*sdi_rom_size) )
    {
        aapl_free(aapl, *swap_rom, __func__);
        *swap_rom = 0;
        *swap_rom_size = 0;
    }
    else if( *swap_rom && !*sdi_rom )
    {
        *sdi_rom = *swap_rom;
        *swap_rom = 0;
        *sdi_rom_size = *swap_rom_size;
        *swap_rom_size = 0;
    }
    if( *swap_rom && *sdi_rom )
        return aapl_fail(aapl,__func__,__LINE__,"SWAP and SDI ROM cannot both be uploaded!\n");

    return 0;
}

/** @brief   Puts the Avago device into a known good state and uploads firmware.
 ** @details Makes the device ready for additional configuration by performing
 **          soft resets, and uploading firmware.
 ** @details The SerDes ROM image is directly loaded to the SerDes on the
 **          addressed chip(s) and ring(s).  The SBM ROM image is directly
 **          uploaded to the SBus Master processor.  The sdi_rom_file, if not
 **          NULL, or the SerDes swap image if any, is appended to the SBus
 **          Master image in the target processor memory.  If the user creates a custom SBM ROM image with the SDI
 **          image already appended, or if no SDI image is needed, the sbm_rom
 **          pointer should be NULL.
 **
 **          The SDI ROM contains SerDes swap images, an AVSP state table,
 **          or both.  Note that SerDes swap images are already in the SDI
 **          format.
 **
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 ** @see     avago_firmware_upload().
 **/
int avago_firmware_upload_file(
    Aapl_t *aapl,                   /**< Pointer to Aapl_t structure */
    uint addr,                      /**< Sbus address of device to upload to */
    const char *serdes_rom_file,    /**< Path name of SerDes .rom file. */
    const char *sbm_rom_file,       /**< Path name of SBus Master .rom file. */
    const char *sdi_rom_file)       /**< Path name of SDI file, or NULL. */
{
    int status = -1, serdes_rom_size = 0, *serdes_rom = 0;
    if( 0 == avago_load_rom_from_file(aapl, serdes_rom_file, &serdes_rom_size, &serdes_rom) )
    {
        int sbm_rom_size = 0, *sbm_rom = 0;
        if( sbm_rom_file && 0 == avago_load_rom_from_file(aapl, sbm_rom_file, &sbm_rom_size, &sbm_rom) )
        {
            char *swap_file = avago_find_swap_file(aapl, serdes_rom_file);
            int swap_rom_size = 0, *swap_rom = 0;
            int sdi_rom_size = 0, *sdi_rom = 0;

            if( (!sdi_rom_file || 0 == avago_load_rom_from_file(aapl, sdi_rom_file, &sdi_rom_size, &sdi_rom))
                && (!swap_file || 0 == avago_load_rom_from_file(aapl, swap_file, &swap_rom_size, &swap_rom)) )
            {
                if( 0 == merge_sdi_files(aapl, &sbm_rom_size, &sbm_rom, &sdi_rom_size, &sdi_rom, &swap_rom_size, &swap_rom) )
                {
                    status = avago_firmware_upload(aapl, addr, serdes_rom_size, serdes_rom, sbm_rom_size, sbm_rom, sdi_rom_size, sdi_rom);
                }
            }

            if( swap_file )
                aapl_free(aapl, swap_file, __func__);
            if( swap_rom && swap_rom_size > 0 )
                aapl_free(aapl, swap_rom, __func__);
            if( sdi_rom && sdi_rom_size > 0 )
                aapl_free(aapl, sdi_rom, __func__);
            if (sbm_rom)
                aapl_free(aapl, sbm_rom, __func__);
        }
        if (serdes_rom)
            aapl_free(aapl, serdes_rom, __func__);
    }
    return status;
}

#endif


/** @brief   Check to see if any uploads are in progress, and waits for them to complete
 **/
void avago_twi_wait_for_complete(
    Aapl_t *aapl,    /**< Pointer to Aapl_t structure */
    uint sbus_addr)  /**< Sbus address of device to check for current upload */
{
    if( !aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F, AVAGO_PROCESS_A) ||
         aapl_check_broadcast_address(aapl, sbus_addr, __func__, __LINE__, TRUE) ||
        !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 2, AVAGO_SBUS_CONTROLLER)  ) return;

    if (aapl_get_process_id(aapl, sbus_addr) == AVAGO_PROCESS_A) return;

    if (aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr) == 0xbf))
    {
        int initial = avago_sbus_rmw(aapl, sbus_addr, 0x40, 1<<13, 1<<13);
        int twi_status = avago_sbus_rd(aapl, sbus_addr, 0x81);
        aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "TWI status: 0x%08x.\n", twi_status);

        if (((twi_status >> 18) & 0x3) == 0x1)
        {
            int loops;
            aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SPICO upload in progress on %s. Waiting for completion (0x%08x).\n",  aapl_addr_to_str(sbus_addr), twi_status);
            for( loops = 0; loops <= AAPL_SPICO_UPLOAD_WAIT_TIMEOUT; loops++ )
            {
                ms_sleep(1);
                twi_status = avago_sbus_rd(aapl, sbus_addr, 0x81);
                if (((twi_status >> 18) & 0x3) != 0x1) break;
            }
            if (loops>= AAPL_SPICO_UPLOAD_WAIT_TIMEOUT)
                aapl_fail(aapl, __func__, __LINE__, "Timed out after %d loops while waiting for TWI upload to complete (0x%02x).\n", loops, twi_status);
            aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "Waited %d loops for pending upload to complete (0x%02x).\n" , loops, twi_status);
        }
        avago_sbus_wr(aapl, sbus_addr, 0x40, initial);
        if (((twi_status >> 18) & 0x3) == 0x2)
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "TWI status indicates failure: 0x%08x.\n", twi_status);
    }
}


/** @brief   Check to see if any uploads are in progress, and waits for them to complete
 **/
void avago_spico_wait_for_upload(
    Aapl_t *aapl,    /**< Pointer to Aapl_t structure */
    uint sbus_addr)  /**< Sbus address of device to check for current upload */
{
    uint imem_cntl = 0;
    uint loops;

    if( !aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F) ||
         aapl_check_broadcast_address(aapl, sbus_addr, __func__, __LINE__, TRUE) ||
        !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 4, AVAGO_SERDES, AVAGO_SPICO, AVAGO_M4, AVAGO_P1)  ) return;

    if (aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1))
    {
        imem_cntl = avago_sbus_rd(aapl, sbus_addr, 0x00);
        if (imem_cntl & 0x40000000)
        {
            aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SPICO upload in progress on %s. Waiting for completion (0x%08x).\n",  aapl_addr_to_str(sbus_addr), imem_cntl);
            for( loops = 0; loops <= AAPL_SPICO_UPLOAD_WAIT_TIMEOUT; loops++ )
            {
                ms_sleep(1);
                if ((avago_sbus_rd(aapl, sbus_addr, 0x07) & 0x02) || !(imem_cntl & 0x40000000))
                    break;
                imem_cntl = avago_sbus_rd(aapl, sbus_addr, 0x00);
            }
            if (loops>= AAPL_SPICO_UPLOAD_WAIT_TIMEOUT)
                aapl_fail(aapl, __func__, __LINE__, "Timed out after %d loops while waiting for SPICO upload to complete (0x%02x 0x%08x).\n",
                    loops, avago_sbus_rd(aapl, sbus_addr, 0x07), imem_cntl);
            aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "Waited %d loops for pending upload to complete (0x%02x 0x%08x).\n" ,
                loops, avago_sbus_rd(aapl, sbus_addr, 0x07), imem_cntl);
        }
    }
    else if (aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO))
    {
        imem_cntl = avago_sbus_rd(aapl, sbus_addr, 0x01);
        if (imem_cntl & 0x200)
        {
            aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SPICO upload in progress on %s. Waiting for completion (0x%08x).\n",  aapl_addr_to_str(sbus_addr), imem_cntl);
            for( loops = 0; loops <= AAPL_SPICO_UPLOAD_WAIT_TIMEOUT; loops++ )
            {
                ms_sleep(1);
                if ((imem_cntl & 0x100) || !(imem_cntl & 0x200))
                    break;
                imem_cntl = avago_sbus_rd(aapl, sbus_addr, 0x01);
            }
            if (loops>= AAPL_SPICO_UPLOAD_WAIT_TIMEOUT)
                aapl_fail(aapl, __func__, __LINE__, "Timed out after %d loops while waiting for SPICO upload to complete (0x%02x 0x%08x).\n",
                    loops, avago_sbus_rd(aapl, sbus_addr, 0x01), imem_cntl);
            aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "Waited %d loops for pending upload to complete (0x%02x 0x%08x).\n" ,
                loops, avago_sbus_rd(aapl, sbus_addr, 0x01), imem_cntl);
        }
    }
}

/** @cond INTERNAL */

static void serdes_spico_halt_fix(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr,      /**< [in] Device address number. */
    int initial_value_0x20)
{
    if ((aapl_get_lsb_rev(aapl, addr) < 5)
        && ((avago_sbus_rd(aapl, addr, 0x27) & 0x3ff) == 0x142))
    {
        avago_sbus_wr(aapl, addr, 0x20, initial_value_0x20 | 0x3);
        if ((avago_sbus_rd(aapl, addr, 0x27) & 0x3ff) == 0x047)
        {
            uint addr_0x00;
            aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Stepping processor and clearing HDW interrupt. %04x %08x %08x\n", avago_sbus_rd(aapl, addr, 0x25), avago_sbus_rd(aapl, addr, 0x27), avago_sbus_rd(aapl, addr, 0x28));
            avago_sbus_wr(aapl, addr, 0x20, initial_value_0x20 | 0x3);
            addr_0x00 = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB_DIRECT, 0x00);
            avago_serdes_mem_wr(aapl, addr, AVAGO_LSB_DIRECT, 0x00, addr_0x00 | 0x2);
        }
    }
}

/** @brief   Safely halts the SPICO processor.
 ** @details Checks that the processor did not halt on the clear interrupt
 **          command which is right before the rti. The two commands must be
 **          atomic.  If we stopped between them, we need to step the
 **          processor past the RTI and then clear the interrupts again so
 **          that any pending hardware interrupts will be seen.
 ** @details The halt/resume functions can be safely nested:
 **          It's safe to call halt when already halted, and resume will only
 **          resume if SPICO was running prior to the corresponding halt.
 ** @return  A SPICO run state variable to pass to avago_spico_resume().
 ** @see avago_spico_resume().
 **/
int avago_spico_halt(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] Device address number. */
{
    int initial_value = 0;
    int spico_running = aapl_get_spico_running_flag(aapl, addr);

    if( !aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F) ||
        !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 4, AVAGO_SPICO, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)  ) return 0;

    if ( (aapl_get_ip_type(aapl, addr) == AVAGO_SERDES) || (aapl_get_ip_type(aapl, addr) == AVAGO_M4)
                                                        || (aapl_get_ip_type(aapl, addr) == AVAGO_P1) )
    {
        initial_value = avago_sbus_rmw(aapl, addr, 0x20, 0x01, 0x01);
        if( 0 == (initial_value & 0x01))
            serdes_spico_halt_fix(aapl, addr, initial_value);

        if( aapl_get_ip_type(aapl, addr) == AVAGO_P1 )
        {
            int reset_status = avago_sbus_rd(aapl, addr, 0x07);
            if( (reset_status & 0x01) || !(reset_status & 0x10) )
                avago_sbus_wr(aapl, addr, 0x07, (reset_status & ~1) | 0x10);
            initial_value |= reset_status << 16;
        }
    }
    else if (aapl_get_ip_type(aapl, addr) == AVAGO_SPICO)
    {
        initial_value = avago_sbus_rmw(aapl, addr, 0x5, 0x01, 0x03);
    }
    aapl_set_spico_running_flag(aapl, addr, 0);
    return initial_value | (spico_running << 31);
}


/** @brief   Resume the SPICO run state after avago_spico_halt().
 ** @details The halt/resume functions can be safely nested:
 **          It's safe to call halt when already halted, and resume will only
 **          resume if SPICO was running prior to the corresponding halt.
 ** @return  0 on success, -1 on error.
 ** @see     avago_spico_halt().
 **/
int avago_spico_resume(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr,              /**< [in] Device address number. */
    int spico_run_state)    /**< [in] Value returned from halt function. */
{
    if( !aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F) ||
        !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 4, AVAGO_SPICO, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)  ) return 0;

    if( aapl_get_ip_type(aapl, addr) == AVAGO_P1 )
    {
        int reset_status = (spico_run_state >> 16) & 0x7fff;
        if( (reset_status & 0x01) || !(reset_status & 0x10) )
            avago_sbus_wr(aapl, addr, 0x07, reset_status);
    }

    if( 0 == (spico_run_state & 0x01) )
    {
        if ( (aapl_get_ip_type(aapl, addr) == AVAGO_SERDES) || (aapl_get_ip_type(aapl, addr) == AVAGO_M4)
                                                            || (aapl_get_ip_type(aapl, addr) == AVAGO_P1) )
        {
            serdes_spico_halt_fix(aapl, addr, spico_run_state);
            avago_sbus_wr(aapl, addr, 0x20, spico_run_state);
        }
        if (aapl_get_ip_type(aapl, addr) == AVAGO_SPICO)
        {
            avago_sbus_wr(aapl, addr, 0x05, spico_run_state);
        }
        if( spico_run_state & 0x80000000 ) aapl_set_spico_running_flag(aapl, addr, 1);
    }
    return 0;
}


/** @endcond */
