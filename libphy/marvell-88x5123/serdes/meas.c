/* AAPL CORE Revision: 2.3.0-alpha */

/* Copyright 2014-2015 Avago Technologies. All rights reserved.
 *
 * This file is part of the AAPL CORE library.
 *
 * AAPL CORE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AAPL CORE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with AAPL CORE.  If not, see http://www.gnu.org/licenses.
 */


/** Doxygen File Header
*  @file
*  @brief Helper functions for eye measurements.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT || AAPL_ENABLE_DIAG

#define INT_CMP_CONTROL 0x0003
#define INT_DFE_EYE     0x0025
#define AAPL_LOG_PRINT5 if(aapl->debug >= 5) aapl_log_printf
#define AAPL_LOG_PRINT6 if(aapl->debug >= 6) aapl_log_printf

/** @cond INTERNAL */

int avago_serdes_get_dac_range(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr)              /**< [in] Device address number. */
{
#ifndef MV_HWS_REDUCED_BUILD
    return aapl_get_sdrev(aapl,addr) == AAPL_SDREV_CM4 ? 512 : 256;
#else
    return 256;
#endif
}

/** @brief   Reads the SerDes phase multiplier value.
 ** @details The phase multiplier is the ratio between real (ASIC setting
 **          level) PI steps per UI and the steps per UI in full rate
 **          mode (which is 64).
 ** @details In reduced data rate mode, the hardware supports 2, 4 or
 **          more times the PI steps per UI than in full rate mode.
 **
 ** @details For example, if running in 1/4 rate mode,
 **          avago_serdes_get_phase_multiplier returns 4 to indicate that the
 **          hardware has 4 * 64 = 256 PI steps per UI.
 **
 ** @return  On success, returns the phase multiplier (>= 1).
 ** @return  On error, decrements aapl->return_code and returns 0.
 ** @see     avago_serdes_get_phase(), avago_serdes_step_phase().
 **/
uint avago_serdes_get_phase_multiplier(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr)              /**< [in] Device address number. */
{
    int return_code = aapl->return_code;
    int reg,bits;
    uint rc;
    unsigned int *temp_mul_map = NULL;
    unsigned int mul_map[] = {1,2,4,8,16,32,64,128};
#ifndef MV_HWS_REDUCED_BUILD
    unsigned int p1_mul_map[] = {2,1,4,1,8,1,6,1};

    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1: reg = 0x11c; temp_mul_map = p1_mul_map; break;
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_M4:
    case AAPL_SDREV_16: reg = 0x086; temp_mul_map = mul_map; break;
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_D6: reg = 0x004; temp_mul_map = mul_map; break;
    }
#else /*AAPL_SDREV_D6 */
    reg = 0x004; temp_mul_map = mul_map;
#endif
    bits = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg) & 7;

    rc   = (return_code != aapl->return_code) ? 0 : temp_mul_map[bits];

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, multiplier %d.\n", aapl_addr_to_str(addr), rc);
    return rc;
}

#endif

#if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT


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
    int rx_clock_divider = avago_serdes_get_rx_register_clock(aapl,addr);
    bigint dwell_words = MAX(1, dwell_bits / rx_clock_divider);
    int int_load_lo, int_load_hi;
#ifndef MV_HWS_REDUCED_BUILD
    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1: int_load_lo = 0x2003; int_load_hi = 0x2083; break;
    default:
    case AAPL_SDREV_16: int_load_lo = 0x0103; int_load_hi = 0x0203; break;
    }
#else
    int_load_lo = 0x0103; int_load_hi = 0x0203;
#endif
    avago_spico_int_check(aapl,__func__,__LINE__,addr, int_load_lo,  dwell_words        & 0xffff);
    avago_spico_int_check(aapl,__func__,__LINE__,addr, int_load_hi, (dwell_words >> 16) & 0x3fff);

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, dwell_bits = %s, dwell_words = %s, rx_clock_divider = %d.\n", aapl_addr_to_str(addr), aapl_bigint_to_str(dwell_bits), aapl_bigint_to_str(dwell_words), rx_clock_divider);

    return (return_code == aapl->return_code) ? 0 : -1;
}


/** @brief   Sets phase interpolator (PI) hardware to low/no power mode.
 ** @details The PI powers up automatically whenever interrupt 0x0f is invoked.
 **          However, since the firmware does not know when the user is finished
 **          with the PI, the PI user must explicitly
 **          power it down when it is no longer needed.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avago_serdes_power_down_phase_interpolator(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1045) )
    {
        uint build_id = avago_firmware_get_build_id(aapl, addr);
        if( build_id == 0x8025 || build_id == 0x0085 )
        {
            printf("%s(): FW SUPPORT NOT YET IMPLEMENTED for build_id 0x%04x\n",__func__,build_id);
        }
        else
        if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, 0x100)) return -1;
        aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, phase interpolator powered down.\n", aapl_addr_to_str(addr));
        return 0;
    }
    aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, OLD FIRMWARE, phase interpolator not powered down.\n", aapl_addr_to_str(addr));
    return 0;
}
#ifndef MV_HWS_REDUCED_BUILD
/** @brief   Write hardware info to buffer.
 **
 ** @return  A buffer allocated by aapl_malloc.  The caller is
 **          responsible for calling aapl_free on the returned value.
 **/

char *avago_hardware_info_format(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    const int buf_length = 250;
    char *buf = (char *)aapl_malloc(aapl, buf_length, __func__);
    char *ptr = buf;
    uint sbm_addr = avago_make_sbus_master_addr(addr);
    buf[0] = '\0';
    ptr += snprintf(ptr,buf_length-(ptr-buf),
            "SBus_address:   %s\n"
            "JTAG_ID:        %s rev %s (0x%08x)\n"
            "Process_ID:     %s (%d)\n"
            "SBus_master:    FW sbus_master.0x%04X_%04X.rom\n"
            "SerDes:         ",
        aapl_addr_to_str(addr),
        aapl_get_chip_name(aapl, addr),
            aapl_get_chip_rev_str(aapl, addr),
            aapl_get_jtag_idcode(aapl, addr),
        aapl_get_process_id_str(aapl, addr),
            aapl_get_process_id(aapl, addr),
        aapl_get_firmware_rev(aapl,sbm_addr),
            aapl_get_firmware_build(aapl,sbm_addr));
    ptr += snprintf(ptr,buf_length-(ptr-buf), "(0x%02x); LSB 0x%02x; ",
                aapl_get_ip_rev(aapl,addr),
                aapl_get_lsb_rev(aapl,addr));
    ptr += snprintf(ptr,buf_length-(ptr-buf), "FW serdes.0x%04X_%04X.rom\n",
                aapl_get_firmware_rev(aapl,addr),
                aapl_get_firmware_build(aapl,addr));
    return buf;
}
#endif
#endif


#define DFE_ROW_COL(row,col) ((row << 8) | (col << 12))

static int serdes_get_dfe_status(
    Aapl_t *aapl,
    uint addr)
{
    return avago_spico_int(aapl, addr, 0x126, DFE_ROW_COL(11, 0));
}

#define AVAGO_DFE_ACTIVE           0x37
#define AVAGO_DFE_ADAPTIVE_ENABLED 0x40
/** @endcond */


/** @brief   Check if DFE is running.
 ** @return  Return TRUE if dfe is running, FALSE otherwise.
 **/
BOOL avago_serdes_dfe_running(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int dfe_status = serdes_get_dfe_status(aapl, addr);
    return (dfe_status & AVAGO_DFE_ACTIVE) != 0;
}

/** @brief   Wait until any running DFE completes.
 ** @details Call avago_serdes_dfe_pause() rather than this function.
 ** @return  Return 1 if dfe has stopped, 0 if dfe is still running.
 **/
int avago_serdes_dfe_wait(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int dfe_status = serdes_get_dfe_status(aapl, addr);
    int loop_count = 0;
    int dfe_running = 0;
    int old_timeout = aapl->serdes_int_timeout;
 
    aapl_log_printf(aapl,AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, dfe_status 0x%x, Waiting for tuning to stop.\n", aapl_addr_to_str(addr), dfe_status);

    if( aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, FALSE, 1, 0x1054) )
        aapl->serdes_int_timeout = aapl->serdes_int_timeout * 5 / 2;

    while( (dfe_status & AVAGO_DFE_ACTIVE) && loop_count++ < aapl->serdes_int_timeout )
    {
        if( !(dfe_status & AVAGO_DFE_ADAPTIVE_ENABLED)
            && !aapl_check_firmware_rev(aapl, addr, __func__,__LINE__,FALSE,1, 0x1044)
            && ((dfe_status & 0x30) && !(dfe_status & 0x03)) )
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_DMEM, 0x200, 0x40, 0x40);
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "SBus %s, Running DFE Workaround\n",aapl_addr_to_str(addr));
        }
        ms_sleep(40);
        if( aapl->debug >= 4 && (loop_count % 100) == 0 )
        {
            char buf[60], *ptr = buf;
            int i;
            for( i = 0; ptr-buf < (int)(sizeof(buf))-10; i++ )
            {
                uint pc = avago_sbus_rd(aapl, addr, 0x25);
                ptr += sprintf(ptr, "%x, ", pc);
            }
            aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "SBus %s, dfe_status 0x%x, pc samples=%s\n", aapl_addr_to_str(addr), dfe_status, buf);
        }
        dfe_status = serdes_get_dfe_status(aapl, addr);
    }
    dfe_running = dfe_status & AVAGO_DFE_ACTIVE;
    aapl->serdes_int_timeout = old_timeout;
    if( dfe_running )
        aapl_log_printf(aapl,AVAGO_WARNING, __func__, __LINE__, "SBus %s, dfe_status 0x%x, DFE tuning %s, loops=%d.\n",
                    aapl_addr_to_str(addr), dfe_status, dfe_running ? "stop timed out" : "stopped", loop_count);
    else
        aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, dfe_status 0x%x, DFE tuning %s, loops=%d.\n",
                    aapl_addr_to_str(addr), dfe_status, dfe_running ? "stop timed out" : "stopped", loop_count);

    return !dfe_running;
}

/** @brief   Block new DFE actions from starting, and
 **          then wait on any in progress.
 ** @details Each SerDes may participate in round-robin (rr) pCal or continuous
 **          adaptive pCal, both of which can start DFE at any time. Since a
 **          running DFE interferes with eye and escope measurement,
 **          avago_serdes_pause_dfe() is provided to block any new pCal from
 **          starting and then wait for any in-progress tuning to finish.
 **          <br>
 **          Note on firmware support:
 **          0x1049 and newer: Pause and resume are fully supported, pause and
 **            resume are idempotent, and rr_enabled is unused and may be NULL.
 **          In pre-0x1049 releases, adaptive pCal is stopped and the user must
 **              restart it themselves.
 **          In release 0x1048, the rr_enabled field must be used to properly
 **              resume the rr state.  In pre-0x1048, rr is not supported.
 ** @return  On success, returns 0.
 **          On error, decrements aapl->return_code and returns -1.
 **          If the wait on in-progress DFE times out, a -1 is returned without
 **          aapl->return_code being decremented.  In this case, call
 **          avago_serdes_dfe_pause() again to wait an additional period of time
 **          for DFE to complete.
 **/
int avago_serdes_dfe_pause(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    uint *rr_enabled)   /**< [out] Return if RR was enabled (0x1048 only). */
{
    if( rr_enabled )
        *rr_enabled = FALSE;
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1049) )
    {
        if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x00)) return -1;
        return avago_serdes_dfe_wait(aapl, addr) == 1 ? 0 : -1;
    }


    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1048) )
    {
        if( rr_enabled )
            *rr_enabled = avago_spico_int(aapl, addr, 0x126, 0x5400);
        if( !rr_enabled || *rr_enabled )
            if (!avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x08)) return -1;
    }

    if( serdes_get_dfe_status(aapl, addr) & AVAGO_DFE_ADAPTIVE_ENABLED )
    {
        Avago_serdes_dfe_tune_t control;
        avago_serdes_tune_init(aapl, &control);
        control.tune_mode = AVAGO_DFE_STOP_ADAPTIVE;
        avago_serdes_tune(aapl, addr, &control);
    }
    return avago_serdes_dfe_wait(aapl, addr) == 1 ? 0 : -1;
}

/** @brief   Resumes the previously paused DFE run state.
 ** @details Resumes the DFE execution state most recently saved by the
 **          avago_serdes_dfe_pause operation. In particular,
 **          if DFE adaptive tuning was running, it resumes running. And if
 **          round robin pCal participation was enabled, it is re-enabled.
 **          Note that repeating a resume operation has no additional effect,
 **          but repeating a pause operation will clear the resume state.
 **          Note for 0x1048 firmware, RR participation is restored.
 **          For pre-0x1049 firmware, adaptive pCal must be restarted
 **          by the caller, if desired.
 ** @return  On success, returns 0.
 **          On error, decrements aapl->return_code and returns -1.
 **/
int avago_serdes_dfe_resume(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    uint rr_enable)     /**< [in] Enable RR if TRUE (0x1048 release only). */
{
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1049) )
    {
        return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x0f) ? 0 : -1;
    }


    if( rr_enable && aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1048) )
        if( !avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x0a) )
            return -1;

    return 0;
}


