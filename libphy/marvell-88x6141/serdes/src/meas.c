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
 ** @brief Helper functions for eye measurements.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#define AAPL_LOG_PRINT5 if(aapl->debug >= 5) aapl_log_printf
#define AAPL_LOG_PRINT6 if(aapl->debug >= 6) aapl_log_printf

#if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT || AAPL_ENABLE_DIAG

#define INT_CMP_CONTROL 0x0003
#define INT_DFE_EYE     0x0025

#if AAPL_ENABLE_ESCOPE_MEASUREMENT || AAPL_ENABLE_PHASE_CALIBRATION
#if AAPL_ALLOW_THREAD_SUPPORT
static AAPL_THREAD_STORAGE int mem_lock_count = 0;
#endif
#endif

/** @cond INTERNAL */

int avago_serdes_get_dac_range(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr)              /**< [in] Device address number. */
{
    int sdrev = aapl_get_sdrev(aapl,addr);
    return sdrev == AAPL_SDREV_CM4 || sdrev == AAPL_SDREV_CM4_16 || sdrev == AAPL_SDREV_D6_07 ? 512 : 256;
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
    int reg;
    uint rc = 0;
    switch( aapl_get_sdrev(aapl,addr) )
    {
    case AAPL_SDREV_P1: rc = 1; break;
    default:
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16:
    case AAPL_SDREV_OM4:
    case AAPL_SDREV_16: reg = 0x086; break;
    case AAPL_SDREV_D6_07: reg = 0x406; break;
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_D6: reg = 0x004; break;
    case AAPL_SDREV_PON: {
        unsigned int mul_map[4] = {4,1,8,2};
        reg = 0x146;
        rc = mul_map[avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg) & 3] * 2;
        }
        break;
    }
    if( rc == 0 )
    {
        unsigned int mul_map[8] = {1,2,4,8,16,32,64,128};
        int bits = avago_serdes_mem_rd(aapl, addr, AVAGO_ESB, reg) & 7;
        rc   = (return_code != aapl->return_code) ? 0 : mul_map[bits];
    }

    AAPL_LOG_PRINT5(aapl, AVAGO_DEBUG5, __func__, __LINE__, "SBus %s, multiplier %d.\n", aapl_addr_to_str(addr), rc);
    return rc;
}


#endif

#if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT



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
        if( !avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0f, 0x100) )
            return -1;
        aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, phase interpolator powered down.\n", aapl_addr_to_str(addr));
    }
    else
        aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, OLD FIRMWARE, phase interpolator not powered down.\n", aapl_addr_to_str(addr));
    return 0;
}

/** @brief  Gets hardware info into string buffer.
 ** @return On success, an allocated buffer with hardware info is returned.
 **         The caller is responsible for calling aapl_free() on the returned value.
 ** @return On error, NULL is returned.
 **/
char *avago_hardware_info_format(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    const int buf_length = 250;
    char *buf = (char *)aapl_malloc(aapl, buf_length, __func__);
    char *ptr = buf;
    uint sbm_addr = avago_make_sbus_master_addr(addr);
    uint eng_release = avago_firmware_get_engineering_id(aapl, addr);
    char eng_buffer[10];
    sprintf(eng_buffer, "_%03X", eng_release);
    if( !buf ) return 0;
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
    ptr += snprintf(ptr,buf_length-(ptr-buf), "FW serdes.0x%04X_%04X%s.rom\n",
                aapl_get_firmware_rev(aapl,addr),
                aapl_get_firmware_build(aapl,addr),
                eng_release?eng_buffer:"");
    return buf;
}
#endif

#define AVAGO_DFE_ACTIVE           0x37
#define AVAGO_DFE_ADAPTIVE_ENABLED 0x40

/** @endcond */

/** @brief   Checks if signal is loss during dfe tuning.
 ** @return  Returns TRUE if dfe is LOS detected, FALSE otherwise.
 ** @see     avago_serdes_get_dfe_status().
 **/
BOOL avago_serdes_dfe_los(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int dfe_status = avago_serdes_get_dfe_status(aapl, addr);
    return (dfe_status & 0x200) != 0;
}

/** @brief   Checks if DFE is running.
 ** @return  Returns TRUE if dfe is running, FALSE otherwise.
 ** @see     avago_serdes_get_dfe_status().
 **/
BOOL avago_serdes_dfe_running(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int dfe_status = avago_serdes_get_dfe_status(aapl, addr);
    return (dfe_status & AVAGO_DFE_ACTIVE) != 0;
}

/** @brief   Waits until any running DFE completes.
 ** @details May return without any wait if DFE is paused because of loss of signal.
 **          Call avago_serdes_dfe_pause() rather than this function.
 ** @return  Returns 1 if dfe has stopped.
 ** @return  Returns 0 if dfe is still running (timeout).
 ** @return  Returns -1 and decrements aapl->return_code if dfe won't run because of no signal.
 ** @see     avago_serdes_dfe_tune(), avago_serdes_dfe_wait().
 **/
int avago_serdes_dfe_wait_timeout(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    int ms_timeout)     /**< [in] Maximum milliseconds to wait for dfe to complete. */
{
    int dfe_status = avago_serdes_interpret_dfe_status(aapl, addr);
    int ret_status;
    int loop_delay = 40;
    int loop_time = 0;
    Aapl_log_type_t log_level = AVAGO_DEBUG3;
    aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "SBus %s, dfe_status 0x%x, Waiting for tuning to stop.\n", aapl_addr_to_str(addr), dfe_status);
    while( dfe_status > 0 && loop_time < ms_timeout )
    {
        if( !(dfe_status & AVAGO_DFE_ADAPTIVE_ENABLED)
            && !aapl_check_firmware_rev(aapl, addr, __func__,__LINE__,FALSE,1, 0x1044)
            && ((dfe_status & 0x30) && !(dfe_status & 0x03)) )
        {
            avago_serdes_mem_rmw(aapl, addr, AVAGO_DMEM, 0x200, 0x40, 0x40);
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "SBus %s, Running DFE Workaround\n",aapl_addr_to_str(addr));
        }

        loop_time += loop_delay;
        ms_sleep(loop_delay);
        if( aapl->debug >= 4 && ((loop_time / loop_delay) % 100) == 0 )
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
        dfe_status = avago_serdes_interpret_dfe_status(aapl, addr);
    }
    ret_status = dfe_status == 0 ? 1 : dfe_status > 0 ? 0 : -1;
    if( ret_status < 0 ) aapl->return_code--;
    if( ret_status != 1 ) log_level = AVAGO_WARNING;
    aapl_log_printf(aapl, log_level, __func__, __LINE__, "SBus %s, dfe_status 0x%x, DFE tuning %s, loop_time=%d ms.\n",
                    aapl_addr_to_str(addr), avago_serdes_get_dfe_status(aapl, addr), ret_status == 0 ? "stop timed out" : ret_status == 1 ? "stopped" : "no signal", loop_time);
    return ret_status;
}

/** @brief   Wait until any running DFE completes.
 ** @details May return without any wait if DFE is paused because of loss of signal.
 ** @details Calls avago_serdes_dfe_pause() rather than this function.
 ** @return  Returns 1 if dfe has stopped.
 ** @return  Returns 0 if dfe is still running (timeout).
 ** @return  Returns -1 and decrements aapl->return_code if dfe won't run because of no signal.
 ** @see     avago_serdes_dfe_tune(), avago_serdes_dfe_wait_timeout().
 **/
int avago_serdes_dfe_wait(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr)          /**< [in] Device address number. */
{
    int ms_timeout = 20000;
    if( aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, FALSE, 1, 0x1054) )
        ms_timeout = 50000;
    if( aapl_get_ip_type(aapl, addr) == AVAGO_M4 )
        ms_timeout *= 4;
    return avago_serdes_dfe_wait_timeout(aapl, addr, ms_timeout);
}

/** @brief   Block new DFE actions from starting, and
 **          then wait on any in progress.
 ** @details Each SerDes may participate in round-robin (rr) pCal or continuous
 **          adaptive pCal, both of which can start DFE at any time. Since a
 **          running DFE interferes with eye and escope measurement,
 **          avago_serdes_dfe_pause() is provided to block any new pCal from
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
 **          If dfe_pause returns because of loss of signal, -1 is returned
 **          and aapl->return_code is decremented.
 ** @see     avago_serdes_dfe_resume(), avago_serdes_dfe_tune(), avago_serdes_tune().
 **/
int avago_serdes_dfe_pause(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    uint *rr_enabled)   /**< [out] Return if RR was enabled (0x1048 only). */
{
    if( rr_enabled )
        *rr_enabled = FALSE;

    if( aapl_get_ip_type(aapl, addr) == AVAGO_M4 )
    {

        if( avago_serdes_get_dfe_status(aapl, addr) & AVAGO_DFE_ADAPTIVE_ENABLED )
        {
            if( rr_enabled ) *rr_enabled = TRUE;
            avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x02);
        }
        return avago_serdes_dfe_wait(aapl, addr) == 1 ? 0 : -1;
    }

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

    if( avago_serdes_get_dfe_status(aapl, addr) & AVAGO_DFE_ADAPTIVE_ENABLED )
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
 ** @see     avago_serdes_dfe_pause(), avago_serdes_dfe_tune(), avago_serdes_tune().
 **/
int avago_serdes_dfe_resume(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint addr,          /**< [in] Device address number. */
    uint rr_enable)     /**< [in] Enable RR if TRUE (0x1048 release only). */
{
    if( aapl_get_ip_type(aapl, addr) == AVAGO_M4 )
    {

        if( rr_enable && !avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x06) )
            return -1;
        return 0;
    }

    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1049) )
    if( aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1049) )
    {
        return avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x0f) ? 0 : -1;
    }


    if( rr_enable && aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1048) )
        if( !avago_spico_int_check(aapl, __func__, __LINE__, addr, 0x0a, 0x0a) )
            return -1;

    return 0;
}

/** @cond INTERNAL */

