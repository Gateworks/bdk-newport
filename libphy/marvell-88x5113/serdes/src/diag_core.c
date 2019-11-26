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
 ** @file
 ** @brief Functions for SerDes diagnostics.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_DIAG

/** @brief   Prints a formatted dump of all SBus registers with non-zero values.
 ** @details Dumps all SBus registers for a given sbus_addr.
 **          Only registers with non-zero values are written.  All output
 **          is written using AVAGO_INFO logging via aapl_log_printf().
 ** @return  void
 **/
void avago_diag_sbus_dump(Aapl_t *aapl, uint sbus_addr, BOOL bin_enable)
{
    int mem_addr;
    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "SBus dump for SBus address %s\n", aapl_addr_to_str(sbus_addr));

    for( mem_addr=0; mem_addr <= 0xff; mem_addr++ )
    {
        uint data;
        if (aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_PMRO) && (mem_addr<0xf8))
            continue;
        data = avago_sbus_rd(aapl, sbus_addr, mem_addr);
        if( data != 0 || aapl->verbose)
        {
            if( bin_enable )
                aapl_hex_2_bin(aapl->data_char, data, 1, 32);
            else
                aapl->data_char[0] = 0x00;

            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%s 0x%02x: 0x%08x  %s\n", aapl_addr_to_str(sbus_addr), mem_addr, data, aapl->data_char);
        }
    }
}


static void search_table_file(char *tablefile, uint mem_addr, char *str)
{
    (void)tablefile;
    (void)mem_addr;
    str[0] = 0;

}



static void serdes_dmem_imem_dump(Aapl_t *aapl, uint sbus_addr, int columns, BOOL dmem_dump)
{
    int stop_addr;
    int start_addr=0;
    int buf_len;
    int mem_addr;
    int spico_run_state = 0;
    int page_width = 16;
    char * buf;
    char * tablefile = 0;

    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");
    aapl_log_printf(aapl, AVAGO_INFO, __func__, 0, "SerDes %cMEM dump for SBus address %s.\n", dmem_dump?'D':'I',aapl_addr_to_str(sbus_addr));

    if (dmem_dump)
    {
        stop_addr = 0x3ff;
        if ( (aapl_get_lsb_rev(aapl,sbus_addr) < 5) &&
             (aapl_get_process_id(aapl,sbus_addr) == AVAGO_PROCESS_F)  )
            start_addr = 0x200;
    }
    else
    {
        if      (aapl_get_lsb_rev(aapl, sbus_addr) <= 2) stop_addr = 8  * 1024 - 1;
        else if (aapl_get_lsb_rev(aapl, sbus_addr) <= 5) stop_addr = 12 * 1024 - 1;
        else                                             stop_addr = 24 * 1024 - 1;
    }

    if (! (dmem_dump && (aapl_get_lsb_rev(aapl,sbus_addr) > 4) ))
      spico_run_state = avago_spico_halt(aapl, sbus_addr);

    {
        buf = (char *) aapl_malloc(aapl, page_width * 5 * 1  + 20, __func__);
        if (page_width == 16)
        {
            buf_len = sprintf(buf, "        ");
            for(mem_addr = 0; mem_addr < page_width; mem_addr++)
                buf_len += sprintf(buf+buf_len, "0x%02x ", mem_addr);
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%s\n", buf);
        }
    }

    buf_len = sprintf(buf, "0x%04x: ", start_addr);
    for (mem_addr = start_addr; mem_addr<=stop_addr; mem_addr++)
    {
        uint data;
        char str[1024];
        search_table_file(tablefile, mem_addr, str);
        if (columns == 0 || (((mem_addr-start_addr) % page_width) == 0 && (mem_addr != start_addr)) )
        {
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%s\n", buf);
            buf_len = sprintf(buf,"0x%04x: ", mem_addr);
        }
        if (dmem_dump) data = avago_serdes_mem_rd(aapl, sbus_addr, AVAGO_DMEM_PREHALTED, mem_addr);
        else           data = avago_serdes_mem_rd(aapl, sbus_addr, AVAGO_IMEM_PREHALTED, mem_addr);
        if (tablefile) buf_len += sprintf(buf+buf_len, "%04x %16.16s ", data, str);
        else           buf_len += sprintf(buf+buf_len, "%04x ", data);
    }
    if (!dmem_dump)
        avago_sbus_wr(aapl, sbus_addr, 0x00, 0x00);
    if (! (dmem_dump && (aapl_get_lsb_rev(aapl,sbus_addr) > 4) ))
        avago_spico_resume(aapl, sbus_addr, spico_run_state);
    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%s\n", buf);
    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");

    if (tablefile) aapl_free(aapl, tablefile, __func__);
    if (buf)       aapl_free(aapl, buf, __func__);
}


#define MAX_LINES 0x350
/** @brief  Formats and displays the memory contents of the given SerDes.
 ** @return void
 **/
void avago_serdes_mem_dump(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,     /**< [in] SBus address to SerDes. */
    BOOL bin_enable,    /**< [in] Also display binary value. */
    BOOL columns,       /**< [in] Enable multi-column output. */
    BOOL dma_dump,      /**< [in] Dump SerDes register values. */
    BOOL dmem_dump,     /**< [in] Dump data memory. */
    BOOL imem_dump)     /**< [in] Dump instruction memory. */
{
    int stop_addr = 0;
    Avago_serdes_mem_type_t dma_type = AVAGO_LSB;

    int subtype = 0;
    int *data = 0;
    int *data_addr = 0;
    int index[2];
    int type;
    char * tablefile = 0;

    if (imem_dump) serdes_dmem_imem_dump(aapl, sbus_addr, /* columns */ TRUE, FALSE);

    if ( (aapl_get_lsb_rev(aapl,sbus_addr) > 4 ) ||
         (aapl_get_process_id(aapl, sbus_addr) == AVAGO_PROCESS_B) ){
        serdes_dmem_imem_dump(aapl, sbus_addr, columns, TRUE);
        if (aapl_get_lsb_rev(aapl,sbus_addr) != 8) return;
        columns = TRUE;
    }

    if (dmem_dump) serdes_dmem_imem_dump(aapl, sbus_addr, /* columns */ TRUE, TRUE);

    if (!dma_dump) return;

    if (columns)
    {
        data = (int *) aapl_malloc(aapl, 2 * MAX_LINES * sizeof(int), "mem_dump data");
        data_addr = (int *) aapl_malloc(aapl, 2 * MAX_LINES * sizeof(int), "mem_dump data");
        memset(index, 0, sizeof(index));
        memset(data, 0, 2 * MAX_LINES * sizeof(int));
        memset(data_addr, 0, 2 * MAX_LINES * sizeof(int));
    }


    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");
    aapl_log_printf(aapl, AVAGO_INFO, __func__, 0, "SerDes LSB/ESB DMA dump for SBus address %s.\n", aapl_addr_to_str(sbus_addr));
    for (type = 0; type <= 3; type ++)
    {
        int mem_addr;
        if (type == 0)
        {
            if (aapl_get_lsb_rev(aapl,sbus_addr) == 8) continue;
            dma_type = AVAGO_LSB_DIRECT;
            stop_addr = 0x60;
            subtype = 0;
            if (!columns) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "LSB DMA dump:\n");
        }
        else if (type == 1)
        {
            dma_type = AVAGO_ESB;
            stop_addr = 0xff;
            subtype = 0x000;
            if (!columns && aapl_get_lsb_rev(aapl,sbus_addr) != 8) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "RX ESB DMA dump:\n");
            else if (!columns) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "ESB DMA dump:\n");
        }
        else if (type == 2)
        {
            if (aapl_get_lsb_rev(aapl,sbus_addr) == 8) continue;
            dma_type = AVAGO_ESB;
            stop_addr = 0xff;
            subtype = 0x200;
            if (!columns) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "TX ESB DMA dump:\n");
        }
        else if (type == 3)
        {
            dma_type = AVAGO_ESB;
            stop_addr = 0x05;
            subtype = 0x300;
            if (!columns) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "CLK ESB DMA dump:\n");
        }

        if (!columns)
        {
            for (mem_addr = 0; mem_addr <= stop_addr; mem_addr++)
            {
                uint read = avago_serdes_mem_rd(aapl, sbus_addr, dma_type, subtype | mem_addr);
                if (read || aapl->verbose)
                {
                    char str[1024];
                    str[0] = 0;
                    if (dma_type != AVAGO_ESB) search_table_file(tablefile, mem_addr, str);
                    if (bin_enable) aapl_hex_2_bin(aapl->data_char, read, 1, 16);
                    else {aapl->data_char[0] = 0x00;}
                    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "0x%03x 0x%04x %s %16.16s\n", subtype | mem_addr, read, aapl->data_char, str);
                }
            }
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");
        }
        else
        {
            for (mem_addr = 0; mem_addr <= stop_addr; mem_addr++)
            {
                int col_num;
                uint read = avago_serdes_mem_rd(aapl, sbus_addr, dma_type, subtype | mem_addr);
                if      (type == 0) col_num = 0;
                else col_num = 1;

                if (!read && !aapl->verbose) continue;

                data[col_num * MAX_LINES + index[col_num]] = read;
                data_addr[col_num * MAX_LINES + index[col_num]] = subtype | mem_addr;
                index[col_num]++;
            }
        }
    }

    if (columns)
    {
        int x;
        if (bin_enable)
        {
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "                    LSB DMA                                           ESB DMA           \n");
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, " Addr   Data                                       Addr   Data                  \n");
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "----- ------ ----------------------------------   ----- ------ ----------------------------------\n");
        }
        else
        {
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "   LSB DMA         ESB DMA  \n");
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, " Addr   Data     Addr   Data\n");
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "------------    ------------\n");
        }

        for (x = 0; x<=MAX_LINES; x++)
        {
            char buf[255];

            int buf_len = 0;
            int have_data = 0;
            int col;
            for (col = 0; col <= 1; col++)
            {
                char str[1024];
                str[0] = 0;
                if (bin_enable) aapl_hex_2_bin(aapl->data_char, data[col * MAX_LINES + x], 1, 16);
                if (col == 0) search_table_file(tablefile, data_addr[col * MAX_LINES + x], str);

                if      ((aapl->verbose && data_addr[col * MAX_LINES + x]) || (data[col * MAX_LINES + x] && bin_enable))
                                        buf_len += sprintf(buf+buf_len, "0x%03x 0x%04x %16s %16.16s   ",  data_addr[col * MAX_LINES + x], data[col * MAX_LINES + x], aapl->data_char, str);
                else if ((aapl->verbose && data_addr[col * MAX_LINES + x]) || data[col * MAX_LINES + x])
                                        buf_len += sprintf(buf+buf_len, "0x%03x 0x%04x %16.16s    ",       data_addr[col * MAX_LINES + x], data[col * MAX_LINES + x], str);
                else if (bin_enable)    buf_len += sprintf(buf+buf_len, "  %3.3s   %4.4s %16s %16.16s    ", "","", "", "");
                else                    buf_len += sprintf(buf+buf_len, "%16.16s %16.16s", "", "");

                if (x == 0 || data_addr[col * MAX_LINES + x]) have_data = 1;
            }
            if (!have_data) break;
            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%s\n", buf);
        }
    }
    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");
    if (tablefile) aapl_free(aapl, tablefile, __func__);
    if (data) aapl_free(aapl, data, __func__);
    if (data_addr) aapl_free(aapl, data_addr, __func__);
}

static char *avago_serdes_get_rx_state_str(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr)              /**< [in] SBus address to SerDes. */
{
    char *buf = (char *)aapl_malloc(aapl, 1200, __func__);
    if( buf )
    {
        char *ptr = buf;
        int row;
        ptr += sprintf(ptr,"Rx State Dump for %s\n",aapl_addr_to_str(addr));
        ptr += sprintf(ptr,"         0      1      2      3      4      5      6      7\n");
        ptr += sprintf(ptr,"--- ------ ------ ------ ------ ------ ------ ------ ------\n");
        for( row = 0; row < 16; row++ )
        {
            int col;
            ptr += sprintf(ptr,"%2d:",row);
            for( col = 0; col < 8; col++ )
            {
                int int_data = row << 8 | col << 12;
                int val = avago_spico_int(aapl, addr, 0x126, int_data);
                ptr += sprintf(ptr," 0x%04x", val);
            }
            ptr += sprintf(ptr,"\n");
        }
        ptr += sprintf(ptr,"\n");
    }
    return buf;
}

#endif

/** @brief   Gathers detailed data from a SerDes.
 ** @details Gathers a user defined table of TX, RX, DFE, and other information for a single SerDes.
 **          Verbose == 1: Print regardless if CRC passes, and print some extra details.
 **          Verbose == 2: Print eye data as part of RX info
 ** @return  A pointer to the string containing the data requested.
 **/
char *avago_serdes_get_state_dump(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint addr,              /**< [in] SBus address to SerDes. */
    uint disable_features,  /**< [in] Bitmask of features to disable. */
    BOOL ignore_errors)     /**< [in] Continue in face of errors. */
{
    uint features       = ~disable_features;
    uint header         = features & 0x00000001;
    uint tx             = features & 0x00000002;
    uint rx             = features & 0x00000004;
    uint clk            = features & 0x00000010;
#if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT
    uint rx_data        = features & 0x00000020;
#endif

    uint details        = features & 0x10000000;
    uint column_header  = features & 0x80000000;

    char *buf = 0;
    char *buf_end = 0;
    int size = 0;
    int crc = 0;
    uint fw_rev, fw_build_id;
    int failed = 0;
    int spico_running;

    if( !aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 4, AVAGO_PROCESS_C, AVAGO_PROCESS_B, AVAGO_PROCESS_F, AVAGO_PROCESS_A) ||
        !aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) )
        return 0;

    AAPL_SUPPRESS_ERRORS_PUSH(aapl);
    spico_running = avago_spico_running(aapl, addr);
    crc = avago_spico_crc(aapl, addr);
    fw_rev      = avago_firmware_get_rev(aapl, addr);
    fw_build_id = avago_firmware_get_build_id(aapl, addr);
    AAPL_SUPPRESS_ERRORS_POP(aapl);

    if ((!crc || !spico_running) & !ignore_errors) failed = 1;

    if (header)
    {
        int lsb_rev     = avago_serdes_get_lsb_rev(aapl, addr);
        char rev_id_name[30];
        sprintf(rev_id_name, "SerDes_0x%x", aapl_get_ip_rev(aapl, addr));
        aapl_buf_add(aapl, &buf, &buf_end, &size, "########## %s %s %s\n", "SerDes state dump for SBus address", aapl_addr_to_str(addr), " ##############################");
        aapl_buf_add(aapl, &buf, &buf_end, &size, "%s LSB rev %d. Firmware: 0x%04X_%04X.\n\n", rev_id_name, lsb_rev, fw_rev, fw_build_id);
    }

    {
        const char *sep = "---------------";
        BOOL tx_en = FALSE, rx_en = FALSE;
        int  tx_width = 0, rx_width = 0;
        Avago_serdes_tx_data_sel_t tx_data_sel = AVAGO_SERDES_TX_DATA_SEL_PRBS7;
        if( tx || details )
            tx_data_sel = avago_serdes_get_tx_data_sel(aapl, addr);
        if( tx || rx )
        {
            avago_serdes_get_tx_rx_ready(aapl, addr, &tx_en, &rx_en);
            avago_serdes_get_tx_rx_width(aapl, addr, &tx_width, &rx_width);
        }

        /*////// Display TX info: */
        if (tx && column_header)
        {
            const char *fmt = "%8.8s %.2s %.5s %.3s %8.8s %.3s %.3s %.3s %.3s %.3s %.3s %.3s %.3s %.3s %.3s %.4s %.3s %.3s %.3s %.3s %.3s \n";
            aapl_buf_add(aapl, &buf, &buf_end, &size, fmt, "Addr", "TX", "Width", "Inv", "Data", "Out", "Pre", "lsb", "msb", "Pre2", "lsb", "msb", "Pre3", "Att", "lsb", "msb", "Post", "lsb", "msb", "Vert", "Amp", "Slew");
            aapl_buf_add(aapl, &buf, &buf_end, &size, fmt, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep);
        }
        if (tx && failed) aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s No data collected. CRC: %d, spico_running: %d\n", aapl_addr_to_str(addr), crc, spico_running);
        else if (tx )
        {
            BOOL                 tx_out    = avago_serdes_get_tx_output_enable(aapl, addr);
            int                  tx_invert = avago_serdes_get_tx_invert(aapl, addr);
            BOOL                 tx_encoding  = avago_serdes_get_tx_line_encoding(aapl, addr);
            BOOL                 tx_gray, tx_precode;
            const char *         datapath_tx_status;
            Avago_serdes_tx_eq_t tx_eq;
            avago_serdes_get_tx_eq(aapl, addr, &tx_eq);
            avago_serdes_get_tx_datapath_encoding(aapl, addr, &tx_gray, &tx_precode);

            if ( tx_gray && tx_precode )
                datapath_tx_status = "gp";
            else if ( tx_gray )
                datapath_tx_status = "g ";
            else if ( tx_precode )
                datapath_tx_status = "p ";
            else
                datapath_tx_status = "  ";

            aapl_buf_add(aapl, &buf, &buf_end, &size, "%8s %2d %s%2d%s %3s ",
                aapl_addr_to_str(addr), tx_en, tx_encoding?"P":" ", tx_width, datapath_tx_status, aapl_onoff_to_str(tx_invert));

            aapl_buf_add(aapl, &buf, &buf_end, &size, "%8s %3d %3d %3d %3d %4d %3d %3d %4d %3d %3d %3d %4d %3d %3d %4d %3d %4d \n",
                aapl_data_sel_to_str(tx_data_sel), tx_out, tx_eq.pre, tx_eq.pre_lsb, tx_eq.pre_msb, tx_eq.pre2, tx_eq.pre2_lsb, tx_eq.pre2_msb, tx_eq.pre3, tx_eq.atten, tx_eq.atten_lsb, tx_eq.atten_msb, tx_eq.post, tx_eq.post_lsb, tx_eq.post_msb, tx_eq.vert, tx_eq.amp, tx_eq.slew);
        }
        if (tx && header) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n");

        /*////// Display RX info: */
        if (rx && column_header)
        {
            const char *fmt = "%8.8s %.2s %.5s %.3s %9.9s %12.12s %3.3s %.2s %.2s %.2s %5.5s %5.5s %1.1s %10.10s\n";
            aapl_buf_add(aapl, &buf, &buf_end, &size, fmt,
                "Addr", "RX", "Width", "Inv", "Data", "Cmp_Mode", "EI", "OK", "LK", "LB", "Term", "Phase", "E", "Errors");
            aapl_buf_add(aapl, &buf, &buf_end, &size, fmt, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep, sep);
        }
        if      (rx && failed) aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s No data collected. CRC: %d, spico_running: %d\n", aapl_addr_to_str(addr), crc, spico_running);
        else if (rx)
        {
            int                         rx_invert    = avago_serdes_get_rx_invert(aapl, addr);
            int                         rx_input_sel = avago_serdes_get_rx_input_loopback(aapl,addr);
            Avago_serdes_rx_term_t      rx_term      = avago_serdes_get_rx_term(aapl, addr);
            Avago_serdes_rx_cmp_mode_t  rx_cmp_mode  = avago_serdes_get_rx_cmp_mode(aapl, addr);
            Avago_serdes_rx_cmp_data_t  rx_cmp_data  = avago_serdes_get_rx_cmp_data(aapl, addr);
            uint                        error_count  = avago_serdes_get_errors(aapl, addr, AVAGO_LSB, FALSE);
            BOOL                        error_flag   = avago_serdes_get_error_flag(aapl, addr, FALSE);
            BOOL                        signal_ok1   = avago_serdes_get_signal_ok(aapl, addr, TRUE);
            BOOL                        signal_ok2   = avago_serdes_get_signal_ok(aapl, addr, TRUE);
            BOOL                        freq_lock    = avago_serdes_get_frequency_lock(aapl, addr);
            BOOL                        rx_encoding  = avago_serdes_get_rx_line_encoding(aapl, addr);
            BOOL                        rx_gray, rx_precode;
            const char *                datapath_rx_status;
            uint                        phase        = 0;
            char                        elec_idle_buf[16];
            char                        error_cnt_buf[16] = "-";

            if (!avago_serdes_get_signal_ok_enable(aapl, addr))    snprintf(elec_idle_buf, sizeof(elec_idle_buf), "Dis");
            else if (avago_serdes_get_electrical_idle(aapl, addr)) snprintf(elec_idle_buf, sizeof(elec_idle_buf), "1");
            else                                                   snprintf(elec_idle_buf, sizeof(elec_idle_buf), "0");

            if(aapl->debug || (rx_cmp_mode != AVAGO_SERDES_RX_CMP_MODE_OFF && rx_cmp_mode != AVAGO_SERDES_RX_CMP_MODE_XOR))
                snprintf(error_cnt_buf, sizeof(error_cnt_buf), "%u", error_count);


            avago_serdes_get_rx_datapath_encoding(aapl, addr, &rx_gray, &rx_precode);

            if ( rx_gray && rx_precode )
                datapath_rx_status = "gp";
            else if ( rx_gray )
                datapath_rx_status = "g ";
            else if ( rx_precode )
                datapath_rx_status = "p ";
            else
                datapath_rx_status = "  ";

            aapl_buf_add(aapl, &buf, &buf_end, &size,  "%8s %2d %s%2d%s %3s",
                aapl_addr_to_str(addr), rx_en, rx_encoding?"P":" ", rx_width, datapath_rx_status, aapl_onoff_to_str(rx_invert));


            aapl_buf_add(aapl, &buf, &buf_end, &size, " %9s", aapl_cmp_data_to_str(rx_cmp_data));


            aapl_buf_add(aapl, &buf, &buf_end, &size,  " %12s %3s %d%d %2d %2d %5s 0x%03x %1d %10s\n",
                aapl_cmp_mode_to_str(rx_cmp_mode),
                elec_idle_buf, signal_ok1, signal_ok2, freq_lock, rx_input_sel, aapl_term_to_str(rx_term), phase, error_flag, error_cnt_buf);
        }
        if (rx && header) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n");

        /*////// Display extra details */
        if (details && !failed)
        {
            int  threshold   = avago_serdes_get_signal_ok_threshold(aapl, addr);
            if( tx_data_sel == AVAGO_SERDES_TX_DATA_SEL_USER )
            {
                long tx_user[4];
                avago_serdes_get_tx_user_data(aapl, addr, tx_user);
                aapl_log_printf(aapl, AVAGO_INFO, 0, 0, " (0x%05lx)", tx_user[0]);
            }
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");


            aapl_buf_add(aapl, &buf, &buf_end, &size,  "RX: EI threshold = %d\n", threshold);
        }
        if (details && header) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n");

        /*////// Display RX info: */
#       if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT
        if (rx_data && aapl->verbose > 1)
        {
            if (column_header)
            {
                aapl_buf_add(aapl, &buf, &buf_end, &size,  "%6s %s\n" , "Addr", "RX Data");
                aapl_buf_add(aapl, &buf, &buf_end, &size,  "%6s %7s\n" , "------", "-------");
            }
            if      (failed) aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s No data collected. CRC: %d, spico_running: %d\n", aapl_addr_to_str(addr), crc, spico_running);
            else
            {
                int i;
                int data = avago_serdes_get_rx_live_data(aapl, addr);
                char pattern[17];
                for( i = 0; i < 16; i++ )
                    pattern[i] = (data & (1 << i)) ? '1' : '0';
                pattern[16] = '\0';
                aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s %s\n", aapl_addr_to_str(addr), pattern);
            }
            if (header) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n");
        }
#       endif

        /*////// Display CLK info: */
        if (clk && column_header)
        {
            aapl_buf_add(aapl, &buf, &buf_end, &size,  "    Addr         SPICO             TX PLL\n");
            aapl_buf_add(aapl, &buf, &buf_end, &size,  "-------- ------------- ------------------\n");
        }
        if      (clk && failed) aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s No data collected. CRC: %d, spico_running: %d\n", aapl_addr_to_str(addr), crc, spico_running);
        else if (clk)
        {
            Avago_serdes_spico_clk_t spico_clk       = avago_serdes_get_spico_clk_src(aapl, addr);
            Avago_serdes_tx_pll_clk_t tx_pll_clk     = avago_serdes_get_tx_pll_clk_src(aapl, addr);
            aapl_buf_add(aapl, &buf, &buf_end, &size,  "%8.8s %13.13s %18.18s\n",
                aapl_addr_to_str(addr), aapl_spico_clk_to_str(spico_clk), aapl_pll_clk_to_str(tx_pll_clk));
        }
        if (clk && header) aapl_buf_add(aapl, &buf, &buf_end, &size, "\n");

        /*////// Display DFE info */
        if( features & 0x00000008 )
        {
            char *buf2 = 0;

            Avago_serdes_dfe_state_t dfe;
            memset(&dfe,0,sizeof(dfe));
            if (!failed)
            {
                avago_serdes_get_dfe_state(aapl, addr, &dfe);
                buf2 = avago_serdes_dfe_state_to_str(aapl, addr, &dfe, 0, column_header);
            }
            else if (column_header && failed) buf2 = avago_serdes_dfe_state_to_str(aapl, 0, &dfe, 0, column_header);

            if (failed) aapl_buf_add(aapl, &buf, &buf_end, &size, "%6s No data collected. CRC: %d, spico_running: %d\n", aapl_addr_to_str(addr), crc, spico_running);

            if (buf2)
            {
                aapl_buf_add(aapl, &buf, &buf_end, &size, "%s", buf2);
                aapl_free(aapl, buf2, __func__);
            }

            buf2 = avago_serdes_get_rx_state_str(aapl, addr);
            if (buf2)
            {
                aapl_buf_add(aapl, &buf, &buf_end, &size, "%s", buf2);
                aapl_free(aapl, buf2, __func__);
            }
        }
    }
    return buf;
}

/** @brief   Prints detailed information from a SerDes.
 ** @details Prints a predefined table of TX, RX, DFE, and other information for a single SerDes.
 **/
void avago_serdes_state_dump(Aapl_t *aapl, uint addr)
{
    char *buf = avago_serdes_get_state_dump(aapl, addr, 0, TRUE);
    if (buf)
    {
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%s\n", buf);
        aapl_free(aapl, buf, __func__);
    }
}

/** @brief   Prints detailed information for a SerDes.
 ** @details Prints a table of TX, RX, DFE, and other information for the given SerDes. This function is broadcast safe.
 **/
void avago_serdes_print_state_table_options(Aapl_t *aapl, Avago_addr_t *addr_struct, Avago_state_table_options_t *options)
{
    uint loop = 0;
    for (loop = 0; loop <= 4; loop++)
    {
        uint header = 0;
        Avago_addr_t start, stop, next;
        BOOL st;

        if (options)
        {
            if (options->disable_tx && loop == 0) continue;
            if (options->disable_rx && loop == 1) continue;
            if (options->disable_dfe && loop == 2) continue;
            if (options->disable_clk && loop == 3) continue;
        }

        for( st = aapl_broadcast_first(aapl, addr_struct, &start, &stop, &next, AAPL_BROADCAST_LANE);
             st;
             st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_LANE) )
        {
            char * buf = 0;
            uint sbus_addr = avago_struct_to_addr(&next);
            if( !aapl_check_ip_type(aapl, sbus_addr, 0, 0, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) )
                continue;

            if (options && options->type_filter && options->type_filter != aapl_get_ip_type(aapl, sbus_addr)) continue;

            if (!header++)  buf = avago_serdes_get_state_dump(aapl, sbus_addr, ~(1 << (loop +1)) & ~0x80000000, FALSE);
            else            buf = avago_serdes_get_state_dump(aapl, sbus_addr, ~(1 << (loop + 1)), FALSE);

            if (buf)
            {
                aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%s", buf);
                aapl_free(aapl, buf, __func__);
            }
        }
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");
    }
}

/** @brief Print information on the device(s) AAPL is connected to using the AVAGO_INFO log type (which is typically STDOUT).
 ** @details The addr field selects the device to print info on.
 **          As aapl->verbose levels increase, more information is printed
 **          The type input will print info only for the IP type specified.
 **          Provides additional options as compared with avago_device_info.\n
 ** @return void
 **/
void avago_device_info_options(
    Aapl_t *aapl,
    Avago_addr_t *addr_struct,
    Avago_ip_type_t type,
    Avago_state_table_options_t *options)
{
    char buf[640];
    char *ptr = buf;
    BOOL st;
    Avago_addr_t start, stop, next;
    uint prev_chip = ~0;
    uint name_len = 0;
    const char **name_list = 0;
    Avago_addr_t addr2_struct = *addr_struct;

    aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "Avago Device Info:\n");

    aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  Communication method:      %s\n", aapl_comm_method_to_str(aapl->communication_method));
    if(aapl_is_aacs_communication_method(aapl))
    {
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  Connected to:              %s:%d\n", aapl->aacs_server, aapl->tcp_port);
        if( aapl->capabilities != 0 )
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  Remote AACS capabilities:  %x\n", aapl->capabilities);
    }
    if( aapl->verbose >= 2 )
    {
        uint c;
        ptr += sprintf(ptr, "  Number of devices:         %d (", aapl->chips);
        for (c = 0; c < aapl->chips; c++)
            ptr += sprintf(ptr, c == 0 ? "%s" : ", %s", aapl->chip_name[c]);
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "%s)\n", buf);

        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  debug:                     %x\n", aapl->debug);
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  enable_debug_logging:      %x\n", aapl->enable_debug_logging);
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  enable_stream_logging:     %x\n", aapl->enable_stream_logging);
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  enable_stream_err_logging: %x\n", aapl->enable_stream_err_logging);

        aapl_log_printf(aapl, AVAGO_INFO, 0, 0,  "  log size / data_char size: %d of %d / %d of %d\n",
            (aapl->data_char_end - aapl->data_char), aapl->data_char_size, (aapl->log_end - aapl->log), aapl->log_size);
    }

    for( st = aapl_broadcast_first(aapl, &addr2_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st && (!options || !options->disable_info);
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        if( next.chip != prev_chip )
        {
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0,   "\nInformation for chip %d:\n", next.chip);
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "  JTAG ID: 0x%08x", aapl->jtag_idcode[next.chip]);
            if (*aapl->chip_name[next.chip])
                aapl_log_printf(aapl, AVAGO_INFO, 0, 0, ";  %s rev %s", aapl->chip_name[next.chip], aapl->chip_rev[next.chip]);
            else
                aapl_log_printf(aapl, AVAGO_INFO, 0, 0, " (%s)", aapl_hex_2_bin(aapl->data_char, aapl->jtag_idcode[next.chip], 0, 32));
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, ";  %s\n", aapl_process_id_to_str(aapl->process_id[next.chip]));

            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");
            if( aapl->debug >= 4 ) aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "IP-ID ");
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "  Addr              IP Type  Rev  LSB Firmware    On Miscellaneous Info\n");
            if( aapl->debug >= 4 ) aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "----- ");
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "------ -------------------- ---- ---- ----------- -- ----------------------\n");

            name_len = 0;
            name_list = 0;
#if AAPL_ENABLE_AVSP
            if( 0 == strncmp(aapl->chip_name[next.chip], "AVSP-", 5) )
                avsp_get_name_list(aapl, next.chip, aapl->chip_name[next.chip], &name_len, &name_list);
#endif
        }
        prev_chip = next.chip;

        if( 0 == aapl->max_sbus_addr[next.chip][next.ring] ) continue;

        if ((int) next.sbus <= aapl->max_sbus_addr[next.chip][next.ring] + 2 || next.sbus == 0xfd || next.sbus == 0xfe )
        {
            Avago_addr_t addr_struct2;
            uint sbus_addr;
            Avago_ip_type_t ip_type;
            int ip_rev;
            ptr = buf;

            avago_addr_init(&addr_struct2);
            addr_struct2.chip = next.chip;
            addr_struct2.ring = next.ring;
            addr_struct2.sbus = next.sbus;
            addr_struct2.lane = next.lane;
            if ((int)next.sbus == aapl->max_sbus_addr[next.chip][next.ring] + 1) addr_struct2.sbus = 0xfd;
            if ((int)next.sbus == aapl->max_sbus_addr[next.chip][next.ring] + 2) addr_struct2.sbus = 0xfe;
            sbus_addr = avago_struct_to_addr(&addr_struct2);

            ip_type = aapl_get_ip_type(aapl, sbus_addr);
            if (type && type != ip_type) continue;

            ip_rev = aapl_get_ip_rev(aapl, sbus_addr);

            if( aapl->debug >= 4 )
                ptr += sprintf(ptr,"0x%02x: ", avago_sbus_rd(aapl, sbus_addr, 0xff));
            if( next.sbus < name_len && name_list && name_list[next.sbus] )
            {
                char ip_type_buf[100];
                sprintf(ip_type_buf, "%s %s", aapl_ip_type_to_str(ip_type), name_list[next.sbus]);
                ptr += sprintf(ptr, "%6s %20s", aapl_addr_to_str(sbus_addr), ip_type_buf);
            }
            else
                ptr += sprintf(ptr, "%6s %20s", aapl_addr_to_str(sbus_addr), aapl_ip_type_to_str(ip_type));

            if (ip_type == AVAGO_THERMAL_SENSOR)
            {
            }
            else
            {
                int firm_rev   = aapl_get_firmware_rev(aapl, sbus_addr);
                int firm_build = aapl_get_firmware_build(aapl, sbus_addr);
                int lsb_rev    = aapl_get_lsb_rev(aapl, sbus_addr);
                int swap = 0;

                if (ip_rev != 0xffff) ptr += sprintf(ptr, " 0x%02x", ip_rev);
                else                  ptr += sprintf(ptr, " %4s","    ");

                if (lsb_rev != 0xff)  ptr += sprintf(ptr, " 0x%02x", lsb_rev);
                else                  ptr += sprintf(ptr, " %4s","    ");

                if( firm_build == 0x0045 && ip_type == AVAGO_SERDES )
                    swap = avago_serdes_mem_rd(aapl, sbus_addr, AVAGO_DMEM, 0x201) & 0x3;

                if (firm_rev != 0xffff) ptr += sprintf(ptr, " 0x%04X_%04X%c %d", firm_rev, firm_build, " cp "[swap], aapl_get_spico_running_flag(aapl, sbus_addr));
                else                    ptr += sprintf(ptr, " %11s   ", "");


                while( ptr[-1] == ' ' ) *--ptr = '\0';
            }
                aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%-s\n", buf);
        }
    }

    if (aapl->verbose >= 1 )
    {
        Avago_state_table_options_t options_local;
        if( !options )
        {
            memset(&options_local, 0, sizeof(options_local));
            options = &options_local;
        }

        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");

        options->type_filter = type;
        avago_serdes_print_state_table_options(aapl, addr_struct, options);
    }

    if (aapl->verbose >= 3 )
    {
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "  Aapl_t buffers:\n");
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "  --------- data_char:       ---------\n%s\n", aapl->data_char);
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "  --------- end of data_char ---------\n");
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "  --------- log:             ---------\n");
#       ifdef AAPL_STREAM
        fwrite(aapl->log, 1, aapl->log_end - aapl->log, AAPL_STREAM);
#       endif
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "  --------- end of log       ---------\n");
        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");
    }
}

#if AAPL_ENABLE_DIAG

/** @brief   Allocates and initializes a default Avago_diag_config_t object.
 ** @return  On success, returns a pointer to the initialized structure, which
 **          should be freed by calling avago_diag_config_destruct() after use.
 ** @return  On failure, returns NULL.
 ** @see     avago_serdes_diag(), avago_diag_config_destruct().
 **/
Avago_diag_config_t *avago_diag_config_construct(Aapl_t *aapl)
{
    int dividers[] = {10, 20, 30, 40, 50, 60, 66, 70, 80, 90, 100, 110, 120, 165, -1};
    Avago_diag_config_t *config;
    size_t bytes = sizeof(Avago_diag_config_t);

    if (! (config = (Avago_diag_config_t *) aapl_malloc(aapl, bytes, __func__))) return(NULL);
    memset(config, 0, sizeof(*config));

    config->binary           = TRUE;
    config->columns          = FALSE;
    config->serdes_init_only = FALSE;
    config->state_dump       = TRUE;
    config->sbus_dump        = TRUE;
    config->dma_dump         = TRUE;
    config->dmem_dump        = TRUE;
    config->imem_dump        = FALSE;
    config->cycles           = 20;

    config->dividers = (int *)aapl_malloc(aapl, sizeof(dividers), __func__);
    if( !config->dividers ) { aapl_free(aapl, config, __func__); return NULL; }

    memcpy(config->dividers, dividers, sizeof(dividers));
    return config;
}

/** @brief   Releases an Avago_diag_config_t struct.
 ** @return  None.
 ** @see     avago_diag_config_construct(), avago_serdes_diag().
 **/
void avago_diag_config_destruct(
    Aapl_t *aapl,
    Avago_diag_config_t *config)
{
    aapl_free(aapl, config->dividers, __func__);
    aapl_free(aapl, config, __func__);
}

/** @brief   Run diagnostics and memory dumps on SerDes.
 ** @details See the config struct for more info.
 **
 ** @return Return 0 on success, negative on error.
 **/
int avago_serdes_diag(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr_in,              /**< [in] SBus address to SerDes. */
    Avago_diag_config_t *config)    /**< [in] Options for the function. */
{
    BOOL st;
#if AAPL_ENABLE_AVSP
    BOOL self_healing = FALSE;
#endif
    Avago_addr_t addr_struct, start, stop, next;

    if (!aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_A, AVAGO_PROCESS_B, AVAGO_PROCESS_F)) return 0;
    if (!aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 5, AVAGO_SPICO, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_M4, AVAGO_P1)) return 0;

    avago_addr_to_struct(sbus_addr_in, &addr_struct);
    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, 0);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, 0) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1) )
            continue;

        avago_diag_sbus_rw_test(aapl, sbus_addr, 2);

        if(config->sbus_dump)
            avago_diag_sbus_dump(aapl, sbus_addr, config->binary);

        if (!aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, FALSE, 2, AVAGO_PROCESS_B, AVAGO_PROCESS_F)) return 0;

#if AAPL_ENABLE_AVSP
        if (avsp_get_self_healing(aapl, next.chip))
        {
            self_healing = TRUE;
            avsp_set_self_healing(aapl, next.chip, FALSE);
        }
#endif

        if(config->dma_dump || config->imem_dump || config->dmem_dump)
            avago_serdes_mem_dump(aapl, sbus_addr, config->binary, config->columns, config->dma_dump, config->dmem_dump, config->imem_dump);
        if (config->cycles)
            avago_spico_diag(aapl, sbus_addr, config->cycles);
        if(config->state_dump)
            avago_serdes_state_dump(aapl, sbus_addr);
        if(config->pmd_debug)
        {
            Avago_serdes_pmd_debug_t * pmd = avago_serdes_pmd_debug_construct(aapl);
            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "########## %s %s %s\n", "SerDes PMD debug for SBus address", aapl_addr_to_str(sbus_addr), " ##############################");
            avago_serdes_pmd_debug(aapl, sbus_addr, pmd);
            avago_serdes_pmd_debug_print(aapl, pmd);
            avago_serdes_pmd_debug_destruct(aapl, pmd);
        }

        if( config->destructive )
        {
            int divider = 0;
            int div_loop = -1;
            while (config->dividers[++div_loop] != -1 && !(config->use_existing_divider && div_loop !=0))
            {
                int ilb, errors;
                    divider = config->dividers[div_loop];

                {
                    Avago_serdes_init_config_t *config = avago_serdes_init_config_construct(aapl);
                    int log_en = aapl->enable_stream_err_logging;
                    aapl->enable_stream_err_logging = 0;

                    config->init_tx = TRUE;
                    config->init_rx = TRUE;
                    config->sbus_reset = TRUE;
                    config->init_mode = AVAGO_PRBS31_ILB;
                    config->tx_divider = divider;
                    config->rx_divider = divider;
                    errors = avago_serdes_init(aapl, sbus_addr, config);
                    avago_serdes_init_config_destruct(aapl, config);

                    aapl->enable_stream_err_logging = log_en;
                }
                aapl_get_return_code(aapl);


                for (ilb = 1; ilb >= 0; ilb--)
                {
                    int data_sel_loop;
                    char test_name[256];
                    avago_serdes_set_rx_input_loopback(aapl, sbus_addr, ilb);
                    if (ilb) snprintf(test_name, 256, "ILB");
                    else     snprintf(test_name, 256, "ELB");

                    if      (ilb)
                    {
                        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%10s %7s %2s %10s\n",      "Mode",       "Data",    "", "Non-invert");
                        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%10s %7s %2s %10s\n",      "----------", "-------", "",   "----------");
                    }
                    else if (!ilb)
                    {
                        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%10s %7s %2s %10s %10s\n", "Mode",       "Data",    "OK", "Non-invert", "Inverted");
                        aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%10s %7s %2s %10s %10s\n", "----------", "-------", "--", "----------", "--------");
                    }
                    for (data_sel_loop = AVAGO_SERDES_TX_DATA_SEL_PRBS7; data_sel_loop <= AVAGO_SERDES_TX_DATA_SEL_USER; data_sel_loop ++)
                    {
                        Avago_serdes_tx_data_sel_t data_sel = (Avago_serdes_tx_data_sel_t) data_sel_loop;
                        Avago_serdes_rx_cmp_data_t cmp_data = (Avago_serdes_rx_cmp_data_t) data_sel_loop;
                        if( data_sel_loop == AVAGO_SERDES_TX_DATA_SEL_PRBS31+1 ) continue;

                        avago_serdes_set_tx_data_sel(aapl, sbus_addr, data_sel);
                        avago_serdes_set_rx_cmp_data(aapl, sbus_addr, cmp_data);

                        if (!ilb) avago_serdes_initialize_signal_ok(aapl, sbus_addr, 0);
                                 avago_serdes_get_errors(aapl, sbus_addr, AVAGO_LSB, /*reset=*/ 1);
                        errors = avago_serdes_get_errors(aapl, sbus_addr, AVAGO_LSB, /*reset=*/ 0);
                        if (ilb) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%10s %7s %2s %10d\n", test_name, aapl_data_sel_to_str(data_sel), "", errors);
                        else
                        {
#ifdef MXD_DEBUG
                            uint signal_ok = avago_serdes_get_signal_ok(aapl, sbus_addr, TRUE);
#endif
                            aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "%10s %7s %2d %10d ", test_name, aapl_data_sel_to_str(data_sel), signal_ok, errors);
                            avago_serdes_set_rx_invert(aapl, sbus_addr, 1);
                                     avago_serdes_get_errors(aapl, sbus_addr, AVAGO_LSB, /*reset=*/ 1);
                            errors = avago_serdes_get_errors(aapl, sbus_addr, AVAGO_LSB, /*reset=*/ 0);
                            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "%10d", errors);
                            avago_serdes_set_rx_invert(aapl, sbus_addr, 0);

                            avago_serdes_set_rx_cmp_mode(aapl, sbus_addr, AVAGO_SERDES_RX_CMP_MODE_XOR);
                                     avago_serdes_get_errors(aapl, sbus_addr, AVAGO_LSB, /*reset=*/ 1);
                            errors = avago_serdes_get_errors(aapl, sbus_addr, AVAGO_LSB, /*reset=*/ 0);
                            aapl_log_printf(aapl, AVAGO_INFO, 0, 0, " %10d\n", errors);
                            avago_serdes_set_rx_cmp_mode(aapl, sbus_addr, AVAGO_SERDES_RX_CMP_MODE_MAIN_PATGEN);
                        }
                    }
                    if (ilb) aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "\n");
                }
            }
        }
#if AAPL_ENABLE_AVSP
        if (self_healing) avsp_set_self_healing(aapl, next.chip, TRUE);
#endif
    }
    return aapl->return_code;
}

/**=============================================================================
 ** Diag
 ** Run diagnostics on various IP. See the Avago_diag_config_t struct for more info.
 **
 ** @brief  Display diagnostics for the given address, which may be a
 ** @return On success, returns 0.  Otherwise decrements aapl->return_code and returns -1;
 ** @return On failure, decrements aapl->return_code and returns -1;
 **/
int avago_diag(Aapl_t *aapl, uint sbus_addr_in, Avago_diag_config_t *config)
{
    int return_code = aapl->return_code;
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "AAPL diag started. AAPL version: " AAPL_VERSION ";  " AAPL_COPYRIGHT "\n");
    aapl_log_printf(aapl, AVAGO_INFO, 0, 1, "aapl->return_code: %d\n", aapl->return_code);

    if (aapl->capabilities & AACS_SERVER_DIAG)
    {
        uint index;
        char cmd_buffer[320];
        char * cmd_buffer_end = cmd_buffer;

        cmd_buffer_end += snprintf(cmd_buffer_end, 319, "diag %s ", aapl_addr_to_str(sbus_addr_in));

        for (index = 0; index < sizeof(Avago_diag_config_t) - 8; index++)
            cmd_buffer_end += snprintf(cmd_buffer_end, cmd_buffer_end - cmd_buffer - 319, "0x%x ", *((char *)config + index));

        aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "Executing AACS direct diag cmd: %s\n", cmd_buffer);
        AAPL_SUPPRESS_ERRORS_PUSH(aapl);
        avago_aacs_send_command_options(aapl, cmd_buffer, /* recv_data_back */ 1, /* strtol */ 0);
        AAPL_SUPPRESS_ERRORS_POP(aapl);
        aapl_log_add(aapl, AVAGO_INFO, aapl->data_char, __func__, __LINE__);

        return return_code == aapl->return_code ? 0 : -1;
    }

    {
        int prev_verbose = aapl->verbose;
        Avago_addr_t addr_struct;
        avago_addr_to_struct(sbus_addr_in, &addr_struct);
        aapl->verbose = 0;
        avago_device_info_options(aapl, &addr_struct, (Avago_ip_type_t) 0, 0);
        aapl->verbose = prev_verbose;
    }

    avago_addr_to_struct(sbus_addr_in, &addr_struct);
    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, 0);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, 0) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        if (aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_UNKNOWN_IP)) continue;
        if (!aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_A, AVAGO_PROCESS_B, AVAGO_PROCESS_F)) return 0;
        if (aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1))
        {
            avago_serdes_diag(aapl, sbus_addr, config);
            continue;
        }

        if (config->sbus_dump ) avago_diag_sbus_dump(aapl, sbus_addr, config->binary);

    }
    return return_code == aapl->return_code ? 0 : -1;
}

#endif
