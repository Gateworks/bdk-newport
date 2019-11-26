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
 ** @brief Functions for SerDes diagnostics.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_DIAG

/** @cond INTERNAL */

#if AAPL_ENABLE_FILE_IO
/** @brief   Searches for a diagnostic file that matches the SerDes firmware
 **          running on the SPICO at addr, and if found, reads the file into
 **          memory.
 ** @return  On success, returns an allocated buffer with contents of file.
 **          Call aapl_free() to release the buffer after use.
 ** @return  Returns NULL if a file is not found.
 **/
char *read_spico_file(Aapl_t *aapl, uint addr, const char *suffix)
{
    char *file = 0;
    (void)aapl;
    (void)addr;
    (void)suffix;
    return file;
}
#endif

static int spico_label_lookup(char *file, const char *label)
{
    if( file && label )
    {
    }
    return 0;
}

static void spico_imem_lookup(char *file, char *str, int pc)
{
    (void)pc;
    str[0] = 0;
    if (file)
    {
    }
}

/** @brief   Returns the SPICO status byte from the processor.
 ** @return  SPICO's status byte
 ** @see     avago_spico_status
 **/
static uint avago_spico_get_status(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: return avago_sbus_rd(aapl, addr, 0x27);
    case AVAGO_SPICO:  return avago_sbus_rd(aapl, addr, 0x0c)
                            | avago_sbus_rd(aapl, addr, 0x0e);
    default:           return 0;
    }
}

static uint avago_spico_get_operands(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: return avago_sbus_rd(aapl, addr, 0x28);
    case AVAGO_SPICO:  return avago_sbus_rd(aapl, addr, 0x0d);
    default:           return 0;
    }
}

static uint avago_spico_get_result(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: return avago_sbus_rd(aapl, addr, 0x29);
    case AVAGO_SPICO:  return avago_sbus_rd(aapl, addr, 0x10);
    default:           return 0;
    }
}

static uint avago_spico_get_ab_reg(Aapl_t *aapl, uint addr)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: return avago_sbus_rd(aapl, addr, 0x2b);
    case AVAGO_SPICO:  return avago_sbus_rd(aapl, addr, 0x11);
    default:           return 0;
    }
}

/** @brief  Single step the addressed SPICO processor.
 ** @return void
 **/
void avago_spico_single_step(Aapl_t *aapl, uint addr, uint state)
{
    switch( aapl_get_ip_type(aapl, addr) )
    {
    case AVAGO_P1:
    case AVAGO_M4:
    case AVAGO_SERDES: avago_sbus_wr(aapl, addr, 0x20, state | 0x3);
                       break;
    case AVAGO_SPICO:  avago_sbus_wr(aapl, addr, 0x5, state | 0x1);
                       avago_sbus_wr(aapl, addr, 0x5, state | 0x3);
    default:           return;
    }
}

/** @brief  Print spico trace header
 ** @return void
 **/
static void avago_spico_diag_header(Aapl_t *aapl)
{
    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%4s %4s %2s %5s %3s %4s %4s %8s %2s %4s %4s\n", "PC", "SP", "ER", "SCNOZ", "INS", "OP1", "OP2", "RESULT", "ST", "A", "B");
}

/** @brief  Print spico trace line
 ** @return void
 **/
void avago_spico_diag_line(Aapl_t *aapl, uint addr, char *hexfile, char *str, int cycle)
{
    int status, operands, result, state, ab_reg;
    int pc = avago_spico_get_pc(aapl, addr);

    if ((cycle % 100) == 0) avago_spico_diag_header(aapl);

    str[0] = 0;

    spico_imem_lookup(hexfile, str, pc);
    status = avago_spico_get_status(aapl, addr);
    operands = avago_spico_get_operands(aapl, addr);
    result = avago_spico_get_result(aapl, addr);
    state = avago_spico_get_state(aapl, addr);
    ab_reg = avago_spico_get_ab_reg(aapl, addr);
    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%04x %04x %02x %x%x%x%x%x %03x %04x %04x %08x %02x %04x %04x  %s\n",
        pc & 0xffff,
        pc >> 16,
        status >> 27,
        (status >> 24) & 1,
        (status >> 19) & 1,
        (status >> 18) & 1,
        (status >> 17) & 1,
        (status >> 16) & 1,
        status & 0x3ff,
        operands & 0xffff,
        (operands >> 16) & 0xffff,
        result,
        state,
        ab_reg & 0xFFFF,
        (ab_reg >> 16) & 0xFFFF,
        str);
}

/** @endcond */

/** @brief  Run diagnostics on SPICO
 ** @return Returns 0 on success, < 0 on failure.
 **/
int avago_spico_diag(Aapl_t *aapl, uint addr, int cycles)
{
    int cycle = 0;
    int initial_state;
    char * hexfile = 0;
    char * tablefile = 0;
    char str[1024];

    if (!aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F)) return 0;
    if (!aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 4, AVAGO_SPICO, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)) return 0;

#if AAPL_ENABLE_FILE_IO
    hexfile = read_spico_file(aapl, addr, ".hex");
    tablefile = read_spico_file(aapl, addr, ".table");
#endif
    initial_state = avago_spico_halt(aapl, addr);

    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n########## Printing %d subsequent values of SPICO's PC for SBus address %s ##########\n", cycles, aapl_addr_to_str(addr)) ;
    for (cycle = 0; cycle < cycles; cycle++)
    {
        avago_spico_diag_line(aapl, addr, hexfile, str, cycle);
        avago_spico_single_step(aapl, addr, initial_state);
    }

    if (aapl_check_ip_type(aapl, addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1))
    {
        int int_number;
        int table_start   = spico_label_lookup(tablefile, "interrupt_debug_xdmem_data");
        int debug_pointer = spico_label_lookup(tablefile, "interrupt_debug_pointer");
        if (table_start)
        {
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Interrupt debug from XDMEM pointer @ 0x%x\n", table_start);
            table_start = avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, table_start);
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Interrupt debug from XDMEM data @ 0x%x\n", table_start);
        }
        else
        {
            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Interrupt debug from DMEM @ 0x202\n");
            debug_pointer = spico_label_lookup(tablefile, "interrupt_debug_pointer");
            if (!debug_pointer) debug_pointer = 0x202;
            table_start = debug_pointer + 1;
        }

        debug_pointer = avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, debug_pointer);
        debug_pointer += table_start;

        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n########## Last 8 interrupts received for SBus address %s. ##########\n", aapl_addr_to_str(addr)) ;
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%7s   %9s %8s   %8s  (%12s)\n", "", "Interrupt", "Data", "Source", "DMEM address");
        for (int_number = 0; int_number <= 7; int_number ++)
        {
            uint source;
            if (debug_pointer == table_start) debug_pointer = table_start + 24;
            debug_pointer -= 3;
            source = ~avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, debug_pointer+2) & 0xffff;
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%7s      0x%04x   0x%04x   %8s  (0x%04x)\n",
                int_number == 0 ? "Newest" : int_number == 7 ? "Oldest" : "",
                avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, debug_pointer+0),
                avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, debug_pointer+1),
                (source & 0x8000) ? "SBM" : (source & 0x4000) ? "SBus" :  "Core",
                debug_pointer+0);
        }
    }

    if (aapl_check_ip_type(aapl, addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1))
    {
        int sp;
        int pc = avago_spico_get_pc(aapl, addr);
        int m4 = aapl_check_ip_type(aapl, addr, __func__, __LINE__, FALSE, 1, AVAGO_M4);
        int d6_07 = aapl_get_sdrev(aapl, addr) == AAPL_SDREV_D6_07;
        int sp_max = m4 ? 0x5ff : d6_07 ? 0x0fff : 0x3ff;
        sp = pc >> 16;
        pc &= 0xffff;

        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n########## Stack dump for SBus address %s. ##########\n", aapl_addr_to_str(addr)) ;
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "PC: 0x%04x  SP: 0x%04x\n", pc, sp);
        if (!sp) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "NOTE: Stack pointer either 0 or not available on this hardware revision.\n");
        else aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%6s (%4s %4s %4s %4s) %6s %6s\n", "SP", "sp+0", "sp+1", "sp+2", "sp+3", "Ret1", "Ret2");
        while (sp <= sp_max && sp != 0)
        {
            int a, b, c, d, ret1, ret2;
            a = avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, sp);
            b = avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, sp+1);
            c = avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, sp+2);
            d = avago_serdes_mem_rd(aapl, addr, AVAGO_DMEM, sp+3);

            ret1 = (a & 0x3f) << 10 | b;
            ret2 = (c & 0x3f) << 10 | d;

            str[0] = 0;
            spico_imem_lookup(hexfile, str, ret1);
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "0x%04x (%4x %4x %4x %4x) 0x%04x 0x%04x ## %s\n", sp, a, b, c, d, ret1, ret2, str);
            sp += m4 ? 1 : 2;
        }
    }

    avago_spico_resume(aapl, addr, initial_state);

    if (hexfile) aapl_free(aapl, hexfile, __FILE__);
    if (tablefile) aapl_free(aapl, tablefile, __FILE__);

    return aapl->return_code;
}

void avago_spico_dmi_dump(Aapl_t *aapl, uint addr)
{
    int num_bytes, imem_addr;
    int count = 0;
    int x;

    if (1)
    {
        int spico_run_state = avago_spico_halt(aapl, addr);
        for (x=0x7fff; x>= 0; x--)
        {
            int mem = avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM_PREHALTED, x);
            if (mem == 0x4e && avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM_PREHALTED, x-1) == 0x45) break;
        }
        avago_spico_resume(aapl, addr, spico_run_state);
        imem_addr = x - 7;
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "### 0x%4d: ", imem_addr);
    }
    imem_addr += 15;

    num_bytes =     avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM, imem_addr+1);
    count =         avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM, imem_addr+2);
    count +=        avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM, imem_addr+3) * 256;

    if (count > 10000) count = 0;

    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "### Total number of points: %d (%x)\n", count, count);
    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "### 0x%4x: ", imem_addr);
    for (x=0; x<num_bytes; x++)
    {
        int data = avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM, imem_addr++);
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%04x ", data);
    }
    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n\n");

    while (1)
    {
        int new_line = 0;
        int prev = 0;
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "## Loop: %4d  ", count);

        for (x=0; x<num_bytes; x++)
        {
            int data = avago_serdes_mem_rd(aapl, addr, AVAGO_IMEM, imem_addr++);

            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%04x ", data);
            if (!(prev >= 0xe0 && prev <= 0xf9))
                aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "(%4d)   ", (data & 0x200) ? data | (int) 0xfffffc00 : data);
        }
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");
        if (new_line) aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");

        if (!count--) break;
        if (imem_addr+num_bytes >= 0x8000) break;
    }
    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "Last addr: %04x\n", imem_addr);
}

#endif

