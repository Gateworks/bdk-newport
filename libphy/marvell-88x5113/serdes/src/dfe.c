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

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

/** Doxygen File Header
 ** @file
 ** @brief Functions related to the DFE.
 **/

/** @cond INTERNAL */

/** @brief   Reads and summarizes the DFE status flags.
 ** @return  Returns 0 if DFE is complete.
 ** @return  Returns -1 if loss of signal and dfe did not complete.
 ** @return  Returns >0 (dfe_status flags) if DFE is in progress.
 **/
int avago_serdes_interpret_dfe_status(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] SBus slice address. */
{
    int retval;
    int dfe_status = avago_serdes_get_dfe_status(aapl, addr);

    if( dfe_status & 0x37 )
        retval = dfe_status & 0x37;
    else
        retval = 0;

    if( dfe_status & 0x200 )
    {
        aapl_fail(aapl, __func__, __LINE__, "DFE Loss of Signal.\n");
        retval = -1;
    }

    return retval;
}

/** @endcond */

/** @brief  Reads the dfe status flags.
 ** DFE status bit meanings (as of 0x1048):
 **
 ** dfe_status[0] iCal in_prog
 ** dfe_status[1] pCal in_prog
 ** dfe_status[2] vos  in_prog
 ** dfe_status[4] run_ical
 ** dfe_status[5] run_pcal
 ** dfe_status[9] EI detected (loss of signal)
 **
 ** @return Returns the dfe status flags value.
 **/
int avago_serdes_get_dfe_status(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint addr)      /**< [in] SBus slice address. */
{
    uint interrupt_code;
    uint interrupt_data;

    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1:
        interrupt_code = 0x2026;
        interrupt_data = 0x2100;
        break;
    default:
        interrupt_code = 0x126;
        interrupt_data = 0x0b00;
    }
    return avago_spico_int(aapl, addr, interrupt_code, interrupt_data);
}


/**@cond INTERNAL */

/** @brief Write or read a HAL value. */
static void hal_update_uint_value(
    Aapl_t *aapl,                /**< [in] Pointer to Aapl_t structure. */
    uint addr,                   /**< [in] SBus slice address. */
    BOOL enable_write,           /**< [in] TRUE to write values to SerDes, else read from SerDes. */
    Avago_serdes_hal_type_t hal, /**< [in] HAL register set selector */
    uint member,                 /**< [in] HAL register selector */
    uint *value)                 /**< [in,out] Address of value to update */
{
    if( enable_write )
    {
        avago_serdes_hal_set(aapl, addr, hal, member, *value);
        return;
    }
    *value = avago_serdes_hal_get(aapl, addr, hal, member);
}
#if 0
static void hal_update_int_value(
    Aapl_t *aapl,                /**< [in] Pointer to Aapl_t structure. */
    uint addr,                   /**< [in] SBus slice address. */
    BOOL enable_write,           /**< [in] TRUE to write values to SerDes, else read from SerDes. */
    Avago_serdes_hal_type_t hal, /**< [in] HAL register set selector */
    uint member,                 /**< [in] HAL register selector */
    int *value)                  /**< [in,out] Address of value to update */
{
    if( enable_write )
    {
        avago_serdes_hal_set(aapl, addr, hal, member, *value);
        return;
    }
    *value = (short)avago_serdes_hal_get(aapl, addr, hal, member);
}
#endif

static void serdes_dfe_update_ctle_0x26(Aapl_t *aapl, uint addr, Avago_serdes_dfe_state_t *dfe_state, BOOL enable_write)
{
    uint int_code = enable_write ? 0x26 : 0x126;
    const uint column = (AAPL_SDREV_P1 == aapl_get_sdrev(aapl,addr)) ? 3 : 2;

    dfe_state->hf = avago_spico_int(aapl, addr, int_code, (column << 12) | (0 << 8) | (dfe_state->hf & 0xffff));
    dfe_state->lf = avago_spico_int(aapl, addr, int_code, (column << 12) | (1 << 8) | (dfe_state->lf & 0xffff));
    dfe_state->dc = avago_spico_int(aapl, addr, int_code, (column << 12) | (2 << 8) | (dfe_state->dc & 0xffff));
    dfe_state->bw = avago_spico_int(aapl, addr, int_code, (column << 12) | (3 << 8) | (dfe_state->bw & 0xffff));
}
static void serdes_dfe_update_ctle_hal(Aapl_t *aapl, uint addr, Avago_serdes_dfe_state_t *dfe_state, BOOL enable_write)
{
    uint fixed = 0;

    hal_update_uint_value(aapl, addr, enable_write && !!(fixed & 1), AVAGO_HAL_RXEQ_CTLE, 2, &dfe_state->dc);
    hal_update_uint_value(aapl, addr, enable_write && !!(fixed & 2), AVAGO_HAL_RXEQ_CTLE, 1, &dfe_state->lf);
    hal_update_uint_value(aapl, addr, enable_write && !!(fixed & 4), AVAGO_HAL_RXEQ_CTLE, 0, &dfe_state->hf);
    hal_update_uint_value(aapl, addr, enable_write && !!(fixed & 8), AVAGO_HAL_RXEQ_CTLE, 3, &dfe_state->bw);

    if( enable_write && fixed != 0 )
        avago_serdes_hal_func(aapl, addr, AVAGO_HAL_RXEQ_CTLE_APPLY);
}
/** @brief Update the ctle values of the provided DFE struct. */
static void serdes_dfe_update_ctle(Aapl_t *aapl, uint addr, Avago_serdes_dfe_state_t *dfe_state, int int_code)
{
    BOOL enable_write = int_code == 0x26;
    switch( aapl_get_sdrev(aapl, addr) )
    {
        case AAPL_SDREV_OM4    :
        case AAPL_SDREV_CM4    :
        case AAPL_SDREV_CM4_16 : serdes_dfe_update_ctle_hal(aapl, addr, dfe_state, enable_write);
                                 break;
        default                : serdes_dfe_update_ctle_0x26(aapl, addr, dfe_state, enable_write);
                                 break;
    }
}


static void serdes_dfe_update_gain_0x26(Aapl_t *aapl, uint addr, Avago_serdes_dfe_state_t *dfe_state, BOOL enable_write)
{
    int sdrev = aapl_get_sdrev(aapl,addr);

    if( sdrev != AAPL_SDREV_P1 )
    {
        uint int_code = enable_write ? 0x26 : 0x126;
        uint mask = 0x0F;
        uint int_data = dfe_state->dfeGAIN & mask;
        uint data = avago_spico_int(aapl,addr,int_code, 0x3000 | int_data);
        dfe_state->dfeGAIN = data & mask;
        dfe_state->dfeGAIN2 = 0;
    }
}
static void serdes_dfe_update_gain_hal(Aapl_t *aapl, uint addr, Avago_serdes_dfe_state_t *dfe_state, BOOL enable_write)
{
    hal_update_uint_value(aapl, addr, enable_write, AVAGO_HAL_RXEQ_DFE, 0, &dfe_state->dfeGAIN);
    hal_update_uint_value(aapl, addr, enable_write, AVAGO_HAL_RXEQ_DFE, 1, &dfe_state->dfeGAIN2);
    if( enable_write )
        avago_serdes_hal_func(aapl, addr, AVAGO_HAL_RXEQ_DFE_APPLY);
}
static void serdes_dfe_update_gain(Aapl_t *aapl, uint addr, Avago_serdes_dfe_state_t *dfe_state, BOOL enable_write)
{
    switch( aapl_get_sdrev(aapl, addr) )
    {
    case AAPL_SDREV_OM4   :
    case AAPL_SDREV_CM4   :
    case AAPL_SDREV_CM4_16: serdes_dfe_update_gain_hal(aapl, addr, dfe_state, enable_write); break;
    default               : serdes_dfe_update_gain_0x26(aapl, addr, dfe_state, enable_write); break;
    case AAPL_SDREV_P1    : break;
    }
}

/** @brief   Reads the DFE state from a SerDes device.
 ** @details To read less that all the state, see
 **          avago_serdes_get_dfe_state_ext().
 ** @return void.
 **/
void avago_serdes_get_dfe_state(
    Aapl_t *aapl,                        /**< [in] Pointer to Aapl_t structure. */
    uint addr,                           /**< [in] SBus slice address. */
    Avago_serdes_dfe_state_t *dfe_state) /**< [out] Where to write state. */
{
    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s\n", aapl_addr_to_str(addr));
    serdes_dfe_update_ctle(aapl, addr, dfe_state, 0x126);
    serdes_dfe_update_gain(aapl, addr, dfe_state, FALSE);
}



/** @brief Formats a DFE state structure as a string.
 ** @return A malloc'd string.  Call aapl_free() to release its memory.
 **/
char *avago_serdes_dfe_state_to_str(
    Aapl_t *aapl,                        /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,                      /**< [in] SBus slice address. */
    Avago_serdes_dfe_state_t *dfe_state,
    BOOL single_line,
    BOOL header)
{
    int sdrev = aapl_get_sdrev(aapl, sbus_addr);
    char *buf = 0;
    char *buf_end = 0;
    int size = 0;
    BOOL is_cm4 = sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16;
    BOOL is_m4  = is_cm4 || sdrev == AAPL_SDREV_OM4;
    BOOL is_p1  = sdrev == AAPL_SDREV_P1;

    if (single_line) {
        aapl_buf_add(aapl, &buf, &buf_end, &size,"DC: %d ",dfe_state->dc);
        aapl_buf_add(aapl, &buf, &buf_end, &size,"LF: %d ",dfe_state->lf);
        aapl_buf_add(aapl, &buf, &buf_end, &size,"HF: %d ",dfe_state->hf);
        aapl_buf_add(aapl, &buf, &buf_end, &size,"BW: %d ",dfe_state->bw);
        if (!is_p1)
          aapl_buf_add(aapl, &buf, &buf_end, &size,"DFEGAIN: %d ",dfe_state->dfeGAIN);
    } else {

        if( header )
        {
            aapl_buf_add(aapl, &buf, &buf_end, &size, "          CTLE     | DFE\n");
            aapl_buf_add(aapl, &buf, &buf_end, &size, "  Addr|DC LF HF BW |G1 G2\n");
            aapl_buf_add(aapl, &buf, &buf_end, &size, "------+------------+-----\n");
        }
        if( !sbus_addr ) return buf;
        aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s|%02x %02x %02x %02x |", aapl_addr_to_str(sbus_addr), dfe_state->dc,dfe_state->lf,dfe_state->hf,dfe_state->bw);
        if (is_m4)
            aapl_buf_add(aapl, &buf, &buf_end, &size, "%2x %2x",dfe_state->dfeGAIN,dfe_state->dfeGAIN2);
        else
            aapl_buf_add(aapl, &buf, &buf_end, &size, "%2x %2s",dfe_state->dfeGAIN,"");
        aapl_buf_add(aapl, &buf, &buf_end, &size, "\n\n");

    }
    return buf;
}

/** @brief Prints a sub-set of information from a Avago_serdes_dfe_state_t struct in a standard format.
 ** @return void
 **/
void avago_serdes_print_dfe(
    Aapl_t *aapl,                        /**< [in] Pointer to Aapl_t structure. */
    uint addr,                           /**< [in] SBus slice address. */
    Avago_serdes_dfe_state_t *dfe_state, /**< [in] Structure to print information from. */
    BOOL single_line)                    /**< [in] When true print as a PARAM: Value list rather then 2 lines */
                                         /**<      of header and values.  This mode also prints data out in */
                                         /**<      decimal values rather then hex. */
{
    char *buf = avago_serdes_dfe_state_to_str(aapl, addr, dfe_state, single_line, TRUE);
    if( buf )
    {
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%s\n", buf);
        aapl_free(aapl, buf, __func__);
    }
}

