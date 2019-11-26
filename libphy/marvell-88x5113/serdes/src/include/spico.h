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

/* AAPL (ASIC and ASSP Programming Layer) support for talking with SPICO
 * processors in SBus master and SerDes slices.
 */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for SPICO processor functions.
 **/

#ifndef AVAGO_SPICO_H_
#define AVAGO_SPICO_H_

#define AVAGO_SPICO_HALT 2

typedef enum
{
    AVAGO_SPICO_RESET=0,
    AVAGO_SPICO_RUNNING=1,
    AVAGO_SPICO_PAUSE=2,
    AVAGO_SPICO_ERROR=3
} Avago_spico_state_t;

/**@brief SPICO processor status values */
typedef struct
{
    uint enabled;                 /**< Indicates if processor is enabled and runnning */
    uint pc;                      /**< Program Counter value */
    uint revision;                /**< Revision of firmware */
    uint build;                   /**< Build ID of firmware */
    Avago_serdes_spico_clk_t clk; /**< Clock Processor is running on */
    Avago_spico_state_t state;    /**< State the Processor is in */
} Avago_spico_status_t;

EXT int  avago_spico_status( Aapl_t *aapl, uint sbus_addr, BOOL no_cache, Avago_spico_status_t *st);
EXT uint avago_spico_running(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_spico_reset(  Aapl_t *aapl, uint sbus_addr);
EXT uint avago_spico_get_pc(Aapl_t *aapl, uint addr);
EXT uint avago_spico_get_state(Aapl_t *aapl, uint addr);


/* uploads SPICO machine code. Returns number of words uploaded */
#ifndef SWIG
/* disabling this routine from SWIG access to avoid supporting an unbounded array argument */
EXT int avago_spico_upload_swap_image(Aapl_t *aapl, uint sbus_addr, int words, const int rom[]);
EXT int avago_spico_upload(Aapl_t *aapl, uint sbus_addr, BOOL ram_bist, int words, const int rom[]);
EXT int avago_firmware_upload(Aapl_t *aapl, uint addr,
                              int serdes_rom_size, const int *serdes_rom,
                              int sbm_rom_size,    const int *sbm_rom,
                              int sdi_rom_size,    const int *sdi_rom);
#endif

EXT void avago_spico_wait_for_upload(Aapl_t *aapl, uint sbus_addr);
EXT void avago_twi_wait_for_complete(Aapl_t *aapl, uint sbus_addr);

#if AAPL_ENABLE_FILE_IO
EXT int avago_load_rom_from_file(Aapl_t *aapl, const char *filename, int *rom_size, int **rom);
EXT int avago_firmware_upload_file(Aapl_t *aapl, uint addr,
                              const char *serdes_rom_file,
                              const char *sbm_rom_file,
                              const char *sdi_rom_file);
EXT char *avago_find_swap_file(Aapl_t *aapl, const char *filename);
EXT int avago_spico_upload_file(Aapl_t *aapl, uint sbus_addr, BOOL ram_bist, const char *filename);
#endif

/* executes a serdes interrupt */
EXT uint avago_spico_int(Aapl_t *aapl, uint sbus_addr, int int_num, int param);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

EXT uint avago_serdes_spico_int_sbus_fn(Aapl_t *aapl, uint sbus_addr, int int_num, int param);

#endif

EXT BOOL avago_spico_int_check(Aapl_t *aapl, const char *caller, int line, uint addr, int int_num, int param);
EXT uint avago_spico_broadcast_int(Aapl_t *aapl, int int_num, int param, int args, ...);
EXT uint avago_spico_broadcast_int_w_mask(Aapl_t *aapl, uint addr_mask, int int_num, int param, int args, ...);

typedef enum
{
    AVAGO_SPICO_INT_ALL=0,
    AVAGO_SPICO_INT_FIRST=1,
    AVAGO_SPICO_INT_NOT_FIRST=2
} Avago_spico_int_flags_t;
typedef struct
{
    int                     interrupt;
    int                     param;
    int                     ret;
    Avago_spico_int_flags_t flags;
} Avago_spico_int_t;
EXT int  avago_spico_int_array(Aapl_t *aapl, uint sbus_addr, int num_elements, Avago_spico_int_t *interrupts);

EXT uint avago_firmware_get_rev(     Aapl_t *aapl, uint sbus_addr);
EXT uint avago_firmware_get_build_id(Aapl_t *aapl, uint sbus_addr);
EXT uint avago_spico_crc(            Aapl_t *aapl, uint sbus_addr);

/* TBD write code for sram_reset */
EXT int avago_spico_ram_bist( Aapl_t *aapl, uint sbus_addr);

# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
    EXT void aapl_crc_one_byte(int *crc_ptr, int value);
    EXT int aapl_crc_rom(int *memory, int length);

    EXT int avago_spico_halt(Aapl_t *aapl, uint addr);
    EXT int avago_spico_resume(Aapl_t *aapl, uint addr, int spico_run_state);
# endif

#endif
