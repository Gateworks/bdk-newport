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
 ** @brief Functions common to ASSPs.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_AVSP
#define EQS(str1,str2) (0==strcmp(str1,str2))

/** @defgroup Avsp Avsp Functions
 ** @{
 **/

static void avsp_set_refclk_halve(Aapl_t *aapl, uint prtad, BOOL refclk_halve)
{
    uint addr = avago_make_addr3(prtad,0,0);
    uint sbc_addr = avago_make_sbus_controller_addr(addr);

    avago_sbus_reset(aapl, sbc_addr, 0);

    if( refclk_halve )
    {
        const char *avsp_name = aapl_get_chip_name(aapl, addr);
        if( EQS(avsp_name,"AVSP-1104") )
            avago_sbus_rmw(aapl, sbc_addr, 0x0080, 0x0002, 0x0002);
        else if( EQS(avsp_name,"AVSP-8812") )
            avago_sbus_rmw(aapl, sbc_addr, 0x0080, 0x000c, 0x000c);
        else if( EQS(avsp_name,"AVSP-5410") )
            avago_sbus_rmw(aapl, sbc_addr, 0x0080, 0x0008, 0x0008);
        else
            avago_sbus_rmw(aapl, sbc_addr, 0x0080, 0x0004, 0x0004);


        ms_sleep(1);
    }
}

/** @brief  Returns REFCLK divider.
 ** @details The REFCLK can be divided in half before passing to the SerDes.
 **          Note: This setting does not divide REFCLK for AN.
 ** @return Returns 1 if the REFCLK DIV2 divider is not enabled.
 ** @return Returns 2 if the REFCLK DIV2 divider is enabled.
 ** @return On error, decrements aapl->return_code and returns -1.
 **/
int avsp_get_refclk_divisor(
    Aapl_t *aapl,   /**< Pointer to Aapl_t structure. */
    uint    prtad)  /**< Port address of the targeted device. */
{
    int return_code = aapl->return_code;
    uint addr = avago_make_addr3(prtad,0,0);
    uint sbc_addr = avago_make_sbus_controller_addr(addr);
    const char *avsp_name = aapl_get_chip_name(aapl,addr);
    uint addr_80 = avago_sbus_rd(aapl, sbc_addr, 0x80);
    int ret = 1;
    if(    (EQS(avsp_name,"AVSP-1104")      &&  (addr_80 & 0x02))
        || (EQS(avsp_name,"AVSP-4412/8801") &&  (addr_80 & 0x04))
        || (EQS(avsp_name,"AVSP-5410")      &&  (addr_80 & 0x08))
        || (EQS(avsp_name,"AVSP-8812")      && ((addr_80 & 0x18) == 0x08 || (addr_80 & 0x14) == 0x14))
        || (EQS(avsp_name,"AVSP-9104")      &&  (addr_80 & 0x04)) )
        ret = 2;
    return (return_code == aapl->return_code) ? ret : -1;
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

/** @brief   Puts the AVSP device into a known good state and uploads firmware.
 ** @details Makes the device ready for additional configuration by performing
 **          soft resets, adjusting the refclk pad frequency if requested, and
 **          uploading firmware.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avsp_upload_firmware(
    Aapl_t    *aapl,            /**< Pointer to Aapl_t structure. */
    uint       prtad,           /**< Port address of the targeted device. */
    BOOL       refclk_halve,    /**< Cut REFCLK frequency in half within the clock pad. */
    int        serdes_rom_size, /**< Size of SerDes ROM image. */
    const int *serdes_rom,      /**< Pointer to SerDes ROM image. */
    int        sbm_rom_size,    /**< Size of SBM ROM image. */
    const int *sbm_rom,         /**< Pointer to SBM ROM image. */
    int        swap_rom_size,   /**< Size of SDI(swap) ROM image. */
    const int *swap_rom)        /**< Pointer to SDI(swap) ROM image. */
{
    int return_code = aapl->return_code;
    uint addr = avago_make_addr3(prtad,0,0);
    uint broadcast_addr = avago_make_serdes_broadcast_addr(addr);

    avsp_set_refclk_halve(aapl, prtad, refclk_halve);
    avago_firmware_upload(aapl, broadcast_addr, serdes_rom_size, serdes_rom,
                          sbm_rom_size, sbm_rom, swap_rom_size, swap_rom);

    return (return_code == aapl->return_code) ? 0 : -1;
}

#if AAPL_ENABLE_FILE_IO

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
            {
                BOOL st;
                Avago_addr_t addr_struct, start, stop, next;
                avago_addr_to_struct(addr, &addr_struct);
                for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE); st;
                     st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
                {
                    aapl->firmware_file[next.chip][next.ring][next.sbus] = (char *)aapl_malloc(aapl, strlen(serdes_rom_file)+1, __func__);
                    if (aapl->firmware_file[next.chip][next.ring][next.sbus])
                        strncpy(aapl->firmware_file[next.chip][next.ring][next.sbus], serdes_rom_file, strlen(serdes_rom_file)+1);
                    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Uploaded firmware to %s from file: %s.\n", aapl_addr_to_str(avago_struct_to_addr(&next)), serdes_rom_file);
                }
            }

            if( swap_file ) aapl_free(aapl, swap_file, __func__);
            if( swap_rom ) aapl_free(aapl, swap_rom, __func__);
            if( sdi_rom ) aapl_free(aapl, sdi_rom, __func__);
            if( sbm_rom ) aapl_free(aapl, sbm_rom, __func__);
        }
        if( serdes_rom ) aapl_free(aapl, serdes_rom, __func__);
    }
    return status;
}

/** @brief   Puts the AVSP device into a known good state and uploads firmware.
 ** @details Makes the device ready for additional configuration by performing
 **          soft resets, adjusting the refclk pad frequency if requested, and
 **          uploading firmware.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avsp_upload_firmware_file(
    Aapl_t *aapl,               /**< Pointer to Aapl_t structure. */
    uint prtad,                 /**< Port address of the targeted device. */
    BOOL refclk_halve,          /**< Cut REFCLK frequency in half within the clock pad. */
    const char *serdes_filepath,/**< Full path to a valid Avago-supplied SerDes ROM image */
    const char *sbm_filepath)   /**< Full path to a valid Avago-supplied sbus master ROM image */
{
    int return_code = aapl->return_code;
    uint addr = avago_make_addr3(prtad,0,0);
    uint broadcast_addr = avago_make_serdes_broadcast_addr(addr);

    avsp_set_refclk_halve(aapl, prtad, refclk_halve);
    avago_firmware_upload_file(aapl, broadcast_addr, serdes_filepath, sbm_filepath, NULL);

    return (return_code == aapl->return_code) ? 0 : -1;
}
#endif

static void avsp_edit_addrs(Aapl_t *aapl, uint prtad, size_t len, uint *addrs)
{
    size_t i;
    (void)aapl;
    for( i = 0; i < len; i++ )
    {
        Avago_addr_t addr_struct;
        avago_addr_to_struct(addrs[i],&addr_struct);
        addr_struct.chip = prtad;
        addrs[i] = avago_struct_to_addr(&addr_struct);
    }
}

#if AAPL_ENABLE_AVSP_5410
static uint a5410_host_addrs[] = { AVSP_5410_HOST_LIST };
static uint a5410_mod_addrs[]  = { AVSP_5410_MOD_LIST };
static uint a5410_addrs[]      = { AVSP_5410_LIST };
static const char *a5410_names[] = { 0, 0, 0, 0, 0, "M25G0", "H10G3", "H10G2", "H10G1", "H10G0", 0, "0", "1" };
#endif

/** @} */


#define AVSP_ARRAY_INIT(var,len,list) ((*var = list), (*len = AAPL_ARRAY_LENGTH(list)))

/** @brief  Get SerDes addresses for an AVSP device.
 ** @details The #type field specifies whether to get all SerDes address, or
 **           just the host or mod addresses.  Note that host/mod distinctions
 **           do not make sense for all AVSP devices, and AVSP_ALL should be
 **           passed in those cases.
 ** @return TRUE if known device and updates addrs and len, FALSE otherwise.
 **/
BOOL aapl_get_addr_list(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint prtad,             /**< [in] Port address of the targeted device. */
    const char *avsp_name,  /**< [in] Name of AVSP device, if known. */
    Avsp_addr_list_t list,  /**< [in] AVSP_ALL, AVSP_HOST, AVSP_MOD, ... */
    uint *len,              /**< [out] Number of addresses in returned #addrs. */
    uint **addrs)           /**< [out] Addresses of requested SerDes. */
{
    if( !avsp_name )
        avsp_name = aapl_get_chip_name(aapl, avago_make_addr3(prtad,0,0));

#if AAPL_ENABLE_AVSP_5410
    if( 0 == strcmp(avsp_name, "AVSP-5410") )
    {
        if(      list == AVSP_HOST ) AVSP_ARRAY_INIT(addrs,len,a5410_host_addrs);
        else if( list == AVSP_MOD  ) AVSP_ARRAY_INIT(addrs,len,a5410_mod_addrs);
        else                         AVSP_ARRAY_INIT(addrs,len,a5410_addrs);
    }
    else
#endif
    {
        (void)avsp_name;
        *len = 0;
        *addrs = 0;
        return FALSE;
    }

    avsp_edit_addrs(aapl, prtad, *len, *addrs);
    return TRUE;
}

BOOL avsp_get_name_list(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint prtad,             /**< [in] Port address of the targeted device. */
    const char *avsp_name,  /**< [in] Name of AVSP device, if known. */
    uint *len,              /**< [out] Number of addresses in returned #addrs. */
    const char ***names)    /**< [out] Names of devices */
{
    if( !avsp_name )
        avsp_name = aapl_get_chip_name(aapl, avago_make_addr3(prtad,0,0));

#if AAPL_ENABLE_AVSP_5410
    if( 0 == strcmp(avsp_name, "AVSP-5410") )
        AVSP_ARRAY_INIT(names, len, a5410_names);
    else
#endif
    {
        (void)avsp_name;
        *len = 0;
        *names = 0;
        return FALSE;
    }
    return TRUE;
}



/** @defgroup Supervisor Avsp Supervisor Functions
 ** @{
 **/

/** @brief   Enables supervisor monitoring of the SerDes for failure conditions.
 ** @details When failure is recognized, the hardware interr_io pin
 **          and/or self-healing functionality is activated.
 ** @return  0 on success, -1 on failure.
 **/
int avsp_supervisor_enable(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint chip,          /**< [in] Chip on which to enable monitoring. */
    BOOL enable)        /**< [in] Enable or disable monitoring. */
{
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(chip,0,0));
    uint data = enable ? 0x4400 : 0x4500;
    uint val;
    int i;
    BOOL enabled = !enable;

    avago_spico_int(aapl, addr, 0x0026, data);
    for( i = 0; i <= 30; i++ )
    {
        val = avsp_supervisor_status(aapl, chip, &enabled);
        if( val != 0  || enabled == enable ) break;
        ms_sleep(10);
    }
    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"Chip %d, loop=%d, enable=%s, status=0x%x\n", chip, i, aapl_bool_to_str(enable), val);

    if (enabled != enable || val != 0) return -1;
    return 0;
}

/** @brief   Retrieves whether the supervisor is enabled.
 ** @return  0 on success, -1 on failure.
 **/
int avsp_supervisor_status(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint chip,          /**< [in] Chip on which to enable monitoring. */
    BOOL *enabled)      /**< [out] *enabled returns TRUE if monitor is running. */
{
    int return_code = aapl->return_code;
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(chip,0,0));
    uint data = 0x3400;
    uint val  = avago_spico_int(aapl, addr, 0x0026, data);
    *enabled = 0 != (val & 0x1000);
    aapl_log_printf(aapl,AVAGO_DEBUG6,__func__,__LINE__,"Chip %d, enabled=%s, status=0x%x\n", chip, aapl_bool_to_str(*enabled), val);
    return (return_code == aapl->return_code) ? 0 : -1;
}

/** @brief    Clears the interr_io (interr_l) supervisor flag.
 ** @details  If the conditions for activating this flag continue to exist, and
 **           monitoring is enabled, the pin will be immediately re-activated.
 ** @details  Note: The interr_io supervisor flag propagates to the hardware
 **           pin via the core port and mdio state machine polling.  Core
 **           port interrupts must be enabled for this propagation to occur.
 ** @return   0 on success, -1 on failure.
 **/
int avsp_supervisor_clear_interr_io(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint    chip)   /**< [in] Chip upon which to operate. */
{
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(chip,0,0));
    uint data = 0x4700;
    uint val  = avago_spico_int(aapl, addr, 0x0026, data);
    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"SBus %s, val=0x%x\n", aapl_addr_to_str(addr), val);
    return (val & 0x10) ? -1 : 0;
}

/** @brief    Reads the hardware interr_io (interr_l) supervisor flag.
 ** @return   0 on success, -1 on failure.
 **/
int avsp_supervisor_get_interr_io(
    Aapl_t *aapl,   /**< [in] Pointer to Aapl_t structure. */
    uint    chip,   /**< [in] Chip upon which to operate. */
    BOOL   *active) /**< [out] State of interr_io pin. */
{
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(chip,0,0));
    int return_code = aapl->return_code;
    int val = avago_spico_int(aapl, addr, 0x0026, 0x3700);
    *active = val & 1;
    return (return_code == aapl->return_code) ? 0 : -1;
}

static int avsp_get_serdes_count(Aapl_t *aapl, uint chip)
{
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(chip,0,0));
    const char *avsp_name = aapl_get_chip_name(aapl, addr);
    int serdes_count;
    if( EQS(avsp_name,"AVSP-1104") || EQS(avsp_name,"AVSP-9104") )
        serdes_count = 20;
    else if( EQS(avsp_name,"AVSP-8812") )
        serdes_count = 16;
    else
        serdes_count = 8;

    return serdes_count;
}



/** @brief   Initializes an AVSP supervisor structure to the given settings.
 ** @details Provides configuration options for how to initialize self-healing
 **          features, including options for what to do on initial link bring
 **          up, what to do on future link down events, and some independent
 **          options.
 ** @return TRUE if mode is a valid value, FALSE otherwise.
 **/
BOOL avsp_supervisor_config_init(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avsp_supervisor_mode_t mode,        /**< [in] Select a configuration mode. */
    BOOL squelch_tx,                    /**< [in] Squelch tx while rx data is bad. */
    BOOL reuse_ical,                    /**< [in] Reuse initial iCal values during signal recovery. */
    BOOL adaptive,                      /**< [in] Run continuous adaptive tuning during normal operation. */
    Avsp_supervisor_config_t *config)   /**< [out] Configuration to initialize. */
{
    memset(config,0,sizeof(*config));

    switch( mode )
    {
    case AVSP_SUPERVISOR_MODE_TUNE_IF_SIGNAL:
        config->assp_control_0 = 0x02;
        break;
    case AVSP_SUPERVISOR_MODE_TUNE_IF_LOCKED_SIGNAL:
        config->assp_control_0 = 0x00;
        break;
    case AVSP_SUPERVISOR_MODE_NO_TUNE:
        config->assp_control_0 = 0x20;
        break;
    default:
        aapl_fail(aapl, __func__,__LINE__,"Invalid mode value: %d\n",mode);
        return FALSE;
    }
    if( squelch_tx )
        config->assp_control_0 |= 0x04;
    if( reuse_ical )
        config->assp_control_0 |= 0x10;
    if( adaptive )
        config->assp_control_0 |= 0x40;

    config->assp_control_1 = 0x24;
    config->assp_control_2 = 0x00;
    config->assp_control_3 = 0x00;

    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"control = %x, %x, %x, %x\n",
        config->assp_control_0, config->assp_control_1,
        config->assp_control_2, config->assp_control_3);
    return TRUE;
}

/** @brief   Constructs an AVSP supervisor structure with the given settings.
 ** @details Provides configuration options for how to initialize self-healing
 **          features, including options for what to do on initial link bring
 **          up, what to do on future link down events, and some independent
 **          options.
 **
 ** @return  Allocated structure.  Call avago_supervisor_config_destruct() to free it.
 ** @see     avsp_supervisor_config_destruct(), avsp_supervisor_config_init().
 **/
Avsp_supervisor_config_t *avsp_supervisor_config_construct(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    Avsp_supervisor_mode_t mode,    /**< [in] Select a configuration mode. */
    BOOL squelch_tx,                /**< [in] Squelch tx while rx data is bad. */
    BOOL reuse_ical,                /**< [in] Reuse initial iCal values during signal recovery. */
    BOOL adaptive)                  /**< [in] Run continuous adaptive tuning during normal operation. */
{
    size_t bytes = sizeof(Avsp_supervisor_config_t);
    Avsp_supervisor_config_t *config = (Avsp_supervisor_config_t *) aapl_malloc(aapl, bytes, __func__);

    if( config == 0 )
        return NULL;

    aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "Construct supervisor state %d\n",mode);

    if( avsp_supervisor_config_init(aapl, mode, squelch_tx, reuse_ical, adaptive, config) )
        return config;

    avsp_supervisor_config_destruct(aapl, config);
    return NULL;
}

/** @brief   Releases the resources associated with #config.
 ** @see     avsp_supervisor_config_construct().
 **/
void avsp_supervisor_config_destruct(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avsp_supervisor_config_t *config)   /**< [in] Supervisor struct to destroy. */
{
    aapl_free(aapl, config, __func__);
}


/** @brief   Sets the supervisor configuration.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
int avsp_supervisor_set_config(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    uint prtad,                         /**< [in] Port address of the device. */
    Avsp_supervisor_config_t *config)   /**< [in] Values to write to device. */
{
    int return_code = aapl->return_code;
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(prtad,0,0));

    config->serdes_count = avsp_get_serdes_count(aapl, prtad);

    avsp_supervisor_enable(aapl, prtad, FALSE);
    avago_spico_int(aapl, addr, 0x26, 0x6200 | (config->assp_control_0 & 0xff));
    avago_spico_int(aapl, addr, 0x26, 0x6300 | (config->assp_control_1 & 0xff));
    avago_spico_int(aapl, addr, 0x26, 0x7200 | (config->assp_control_2 & 0xff));
    avago_spico_int(aapl, addr, 0x26, 0x7300 | (config->assp_control_3 & 0xff));

    if( (config->assp_control_0 & 1) == 0 )
        avsp_supervisor_enable(aapl, prtad, TRUE);

    aapl_log_printf(aapl,AVAGO_DEBUG5,__func__,__LINE__,"Chip %d, Config = (0x%02x, 0x%02x, 0x%02x, 0x%02x)\n",
        prtad, config->assp_control_0, config->assp_control_1, config->assp_control_2, config->assp_control_3);
    return (return_code == aapl->return_code) ? 0 : -1;
}

/** @} */


/** @brief   Tells the user is self healing is enabled.
 ** @return  TRUE if it is running, FALSE otherwise
 **/
BOOL avsp_get_self_healing(Aapl_t *aapl, uint prtad)
{
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(prtad,0,0));
    if (avago_spico_int(aapl, addr, 0x26, 0x3500) & 0x1fff) return TRUE;
    return FALSE;
}

/** @brief   Allows the user to enable/disable self healing */
void avsp_set_self_healing(Aapl_t *aapl, uint prtad, BOOL self_heal_enable)
{
    uint addr = avago_make_sbus_master_addr(avago_make_addr3(prtad,0,0));
    if (self_heal_enable) avago_spico_int(aapl, addr, 0x26, 0x4400);
    else                  avago_spico_int(aapl, addr, 0x26, 0x4500);
}

#endif

