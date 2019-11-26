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

#define avago_spico_running              MYD_avago_spico_running
#define avago_spico_get_pc               MYD_avago_spico_get_pc
#define avago_spico_get_state            MYD_avago_spico_get_state
#define avago_spico_status               MYD_avago_spico_status
#define avago_serdes_spico_int_sbus_fn   MYD_avago_serdes_spico_int_sbus_fn
#define avago_spico_int                  MYD_avago_spico_int
#define avago_spico_int_array            MYD_avago_spico_int_array
#define avago_spico_int_check            MYD_avago_spico_int_check
#define avago_spico_broadcast_int        MYD_avago_spico_broadcast_int
#define avago_spico_broadcast_int_w_mask MYD_avago_spico_broadcast_int_w_mask
#define aapl_crc_one_byte                MYD_aapl_crc_one_byte
#define aapl_crc_rom                     MYD_aapl_crc_rom
#define avago_spico_ram_bist             MYD_avago_spico_ram_bist
#define avago_firmware_get_rev           MYD_avago_firmware_get_rev
#define avago_spico_upload_swap_image    MYD_avago_spico_upload_swap_image
#define avago_firmware_get_build_id      MYD_avago_firmware_get_build_id
#define avago_spico_crc                  MYD_avago_spico_crc
#define avago_spico_upload               MYD_avago_spico_upload
#define avago_spico_reset                MYD_avago_spico_reset
#define avago_load_rom_from_file         MYD_avago_load_rom_from_file
#define avago_find_swap_file             MYD_avago_find_swap_file
#define avago_spico_upload_file          MYD_avago_spico_upload_file
#define avago_twi_wait_for_complete      MYD_avago_twi_wait_for_complete
#define avago_spico_wait_for_upload      MYD_avago_spico_wait_for_upload
#define avago_spico_halt                 MYD_avago_spico_halt
#define avago_spico_resume               MYD_avago_spico_resume

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
EXT int avago_parallel_spico_upload(Aapl_t *aapl, Avago_addr_t *addr_list, BOOL ram_bist, int words, const int rom[]);
#endif

EXT void avago_spico_wait_for_upload(Aapl_t *aapl, uint sbus_addr);
EXT void avago_twi_wait_for_complete(Aapl_t *aapl, uint sbus_addr);

#if AAPL_ENABLE_FILE_IO
EXT int avago_load_rom_from_file(Aapl_t *aapl, const char *filename, int *rom_size, int **rom);
EXT char *avago_find_swap_file(Aapl_t *aapl, const char *filename);
EXT int avago_spico_upload_file(Aapl_t *aapl, uint sbus_addr, BOOL ram_bist, const char *filename);
EXT int avago_parallel_spico_upload_file(Aapl_t *aapl, Avago_addr_t *addr_list, BOOL ram_bist, const char *filename);
#endif

/* executes a serdes interrupt */
EXT uint avago_spico_int(Aapl_t *aapl, uint sbus_addr, int int_num, int int_data);
EXT BOOL avago_spico_int_check(Aapl_t *aapl, const char *caller, int line, uint addr, int int_num, int param);
EXT  int avago_parallel_serdes_int(Aapl_t *aapl, Avago_addr_t *addr_list, int int_num, int int_data);
EXT BOOL avago_parallel_serdes_int_check(Aapl_t *aapl, const char *caller, int line, Avago_addr_t *addr_list, int int_num, int param);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

EXT uint avago_serdes_spico_int_sbus_fn(Aapl_t *aapl, uint sbus_addr, int int_num, int int_data);
EXT  int avago_parallel_serdes_int_sbus_fn(Aapl_t *aapl, Avago_addr_t *addr_list, int int_num, int int_data);
EXT  int avago_parallel_core_serdes_int_sbus_fn(Aapl_t *aapl, Avago_addr_t *addr_list, int int_num, int int_data);

#endif

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

EXT uint avago_firmware_get_engineering_id( Aapl_t *aapl, uint sbus_addr);
EXT uint avago_firmware_get_rev(            Aapl_t *aapl, uint sbus_addr);
EXT uint avago_firmware_get_build_id(       Aapl_t *aapl, uint sbus_addr);
EXT BOOL avago_spico_crc(                   Aapl_t *aapl, uint sbus_addr);
EXT BOOL avago_parallel_serdes_crc(         Aapl_t *aapl, Avago_addr_t *addr_list);

/* TBD write code for sram_reset */
EXT int avago_spico_ram_bist( Aapl_t *aapl, uint sbus_addr);

# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
    EXT void aapl_crc_one_byte(int *crc_ptr, int value);
    EXT int aapl_crc_rom(int *memory, int length);

    EXT int avago_spico_halt(Aapl_t *aapl, uint addr);
    EXT int avago_spico_resume(Aapl_t *aapl, uint addr, int spico_run_state);
# endif

#endif
