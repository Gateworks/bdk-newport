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

/* AAPL (ASIC and ASSP Programming Layer) support for AVSP */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for ASSP functions.
 **/

#ifndef AVSP_H_
#define AVSP_H_

#if AAPL_ENABLE_AVSP

#ifndef SWIG

/* defines for AVSP-5410 product */
#define AVSP_5410_BROD_A     AVAGO_SERDES_BROADCAST_ADDRESS
#define AVSP_5410_SBM_A      0xfd
#define AVSP_5410_SD0        0x009
#define AVSP_5410_SD1        0x008
#define AVSP_5410_SD2        0x007
#define AVSP_5410_SD3        0x006
#define AVSP_5410_SD4        0x005
/*#define AVSP_5410_SD5        0x004 */
#define AVSP_5410_HOST_LIST AVSP_5410_SD0, AVSP_5410_SD1, AVSP_5410_SD2, AVSP_5410_SD3
#define AVSP_5410_MOD_LIST  AVSP_5410_SD4
#define AVSP_5410_LIST      AVSP_5410_HOST_LIST, AVSP_5410_MOD_LIST

#endif

#define AVSP_MAX_SLICE_COUNT 20

/** @brief The AVSP operating mode. */
typedef enum
{
    AVSP_PMA                 = 0, /**< Select the AVSP-1104 10:4  operating mode. */
    AVSP_GEARBOX_10_4        = 0, /**< Select the AVSP-1104 10:4  operating mode. */
    AVSP_RPT                 = 1, /**< Select the AVSP-1104 10:10 operating mode. */
    AVSP_REPEATER_DUPLEX     = 1, /**< Select the AVSP-1104 10:10 and AVSP-4412 operating mode. */
    AVSP_GEARBOX_10_4_RS_FEC = 2,
    AVSP_GEARBOX_10_4_MLG    = 3,
    AVSP_REPEATER_SIMPLEX    = 4, /**< Select the AVSP-8801 mode. */
    AVSP_GEARBOX_4_1         = 5,
    AVSP_ADHOC               = 6,
    AVSP_GEARBOX_2_1         = 7, /**<Select AVSP-8812 Gearbox 2:1 mode */
    AVSP_GEARBOX_2_1_MOD_HOST= 8, /**<Select AVSP-8812 Gearbox 1:2 mode */
    AVSP_RS_FEC_4x4          = 9, /**<Select AVSP-8812 FEC mode */
    AVSP_RS_FEC_528          = 10,/**<Select AVSP-7412 FEC mode */
    AVSP_RS_FEC_544          = 11,/**<Select AVSP-7412 FEC mode */
    AVSP_RS_FEC              = 12 /**<Select AVSP-5410 FEC mode */
} Avsp_mode_t;



EXT int avsp_supervisor_enable(Aapl_t *aapl, uint chip, BOOL enable);
EXT int avsp_supervisor_status(Aapl_t *aapl, uint chip, BOOL *enabled);
EXT int avsp_supervisor_clear_interr_io(Aapl_t *aapl, uint chip);
EXT int avsp_supervisor_get_interr_io(Aapl_t *aapl, uint chip, BOOL *active);

/** @brief */
typedef enum
{
    AVSP_SUPERVISOR_MODE_TUNE_IF_SIGNAL,        /**< Start tuning when signal is detected without waiting for frequency lock. */
    AVSP_SUPERVISOR_MODE_TUNE_IF_LOCKED_SIGNAL, /**< Start tuning only after signal is detected and frequency is locked. */
    AVSP_SUPERVISOR_MODE_NO_TUNE                /**< */
} Avsp_supervisor_mode_t;

/** @brief Structure for retrieving supervisor status, and for controlling
 **        supervisor operation.
 **/
typedef struct
{
    short assp_control_0;               /**< Control flags.  Change only if you know what you are doing. */
    short assp_control_1;
    short assp_control_2;
    short assp_control_3;
    int  serdes_count;                  /**< Informational */
    BOOL enabled;                       /**< Supervisor run status. */
    BOOL interr_io;                     /**< interr_io pin status. */
    int status[AVSP_MAX_SLICE_COUNT];   /**< Per slice status bits. */
} Avsp_supervisor_config_t;

EXT BOOL avsp_supervisor_config_init(Aapl_t *aapl, Avsp_supervisor_mode_t mode,
        BOOL squelch_tx, BOOL reuse_ical, BOOL adaptive, Avsp_supervisor_config_t *config);
EXT Avsp_supervisor_config_t *avsp_supervisor_config_construct(Aapl_t *aapl,
        Avsp_supervisor_mode_t mode, BOOL squelch_tx, BOOL reuse_ical, BOOL adaptive);
EXT void avsp_supervisor_config_destruct(Aapl_t *aapl, Avsp_supervisor_config_t *config);
EXT int avsp_supervisor_set_config(Aapl_t *aapl, uint chip, Avsp_supervisor_config_t *config);


typedef enum { AVSP_ALL, AVSP_HOST, AVSP_MOD, AVSP_HOST_MOD4, AVSP_MOD_HOST4, AVSP_MOD4, AVSP_MODX, AVSP_GB01_HOST_MOD, AVSP_GB23_HOST_MOD, AVSP_GB01_MOD_HOST, AVSP_GB23_MOD_HOST, AVSP_HALF0, AVSP_HALF1, AVSP_MOD6 = AVSP_MODX } Avsp_addr_list_t;

EXT BOOL aapl_get_addr_list(Aapl_t *aapl, uint prtad, const char *avsp_name, Avsp_addr_list_t list, uint *len, uint **addrs);
EXT BOOL avsp_get_name_list(Aapl_t *aapl, uint prtad, const char *avsp_name, uint *len, const char ***names);

EXT int avago_firmware_upload(Aapl_t *aapl, uint addr,
                              int serdes_rom_size, const int *serdes_rom,
                              int sbm_rom_size,    const int *sbm_rom,
                              int sdi_rom_size,    const int *sdi_rom);

/* General AVSP functions: */
EXT int avsp_upload_firmware(Aapl_t *aapl, uint prtad, BOOL refclk_halve,
                             int serdes_rom_size, const int *serdes_rom,
                             int sbm_rom_size, const int *sbm_rom,
                             int swap_rom_size, const int *swap_rom);

#if AAPL_ENABLE_FILE_IO
EXT int avago_firmware_upload_file(Aapl_t *aapl, uint addr,
                              const char *serdes_rom_file,
                              const char *sbm_rom_file,
                              const char *sdi_rom_file);
EXT int avsp_upload_firmware_file(Aapl_t *aapl, uint prtad, BOOL refclk_halve,
                                  const char *serdes_filename, const char *sbm_filename);
#endif

EXT BOOL avsp_get_self_healing(Aapl_t *aapl, uint prtad);
EXT void avsp_set_self_healing(Aapl_t *aapl, uint prtad, BOOL self_heal_enable);


#if AAPL_ENABLE_AVSP_5410
EXT Avsp_mode_t avsp_5410_get_mode(Aapl_t *aapl, uint prtad);
EXT int avsp_5410_set_mode(Aapl_t *aapl, uint prtad, Avsp_mode_t mode);
EXT BOOL avsp_5410_control_logic_reset_direct(Aapl_t *aapl, uint prtad, const char * direction);
#endif


#endif

#endif

