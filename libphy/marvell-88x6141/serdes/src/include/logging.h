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

/* Logging and core type conversion functions
 */

/** Doxygen File Header
 ** @file
 ** @brief Logging and core type conversion functions.
 **/

#ifndef AAPL_LOGGING_H_
#define AAPL_LOGGING_H_

#define aapl_log_get              MYD_aapl_log_get
#define aapl_log_clear            MYD_aapl_log_clear
#define aapl_start_file_logging   MYD_aapl_start_file_logging
#define aapl_stop_file_logging    MYD_aapl_stop_file_logging
#define aapl_buf_add              MYD_aapl_buf_add
#define name_to_index             MYD_name_to_index
#define value_to_index            MYD_value_to_index
#define aapl_comm_method_to_str   MYD_aapl_comm_method_to_str
#define aapl_str_to_comm_method   MYD_aapl_str_to_comm_method
#define aapl_log_type_to_str      MYD_aapl_log_type_to_str
#define aapl_spico_clk_to_str     MYD_aapl_spico_clk_to_str
#define aapl_str_to_spico_clk     MYD_aapl_str_to_spico_clk
#define aapl_pll_clk_to_str       MYD_aapl_pll_clk_to_str
#define aapl_str_to_pll_clk       MYD_aapl_str_to_pll_clk
#define aapl_process_id_to_str    MYD_aapl_process_id_to_str
#define aapl_mem_type_to_str      MYD_aapl_mem_type_to_str
#define aapl_str_to_mem_type      MYD_aapl_str_to_mem_type
#define aapl_bigint_to_str        MYD_aapl_bigint_to_str
#define aapl_bool_to_str          MYD_aapl_bool_to_str
#define aapl_onoff_to_str         MYD_aapl_onoff_to_str
#define aapl_enable_to_str        MYD_aapl_enable_to_str
#define aapl_data_sel_to_str      MYD_aapl_data_sel_to_str
#define aapl_str_to_data_sel      MYD_aapl_str_to_data_sel
#define aapl_cmp_data_to_str      MYD_aapl_cmp_data_to_str
#define aapl_str_to_cmp_data      MYD_aapl_str_to_cmp_data
#define aapl_cmp_mode_to_str      MYD_aapl_cmp_mode_to_str
#define aapl_str_to_cmp_mode      MYD_aapl_str_to_cmp_mode
#define aapl_term_to_str          MYD_aapl_term_to_str
#define aapl_str_to_term          MYD_aapl_str_to_term
#define aapl_line_encoding_to_str MYD_aapl_line_encoding_to_str
#define aapl_str_to_line_encoding MYD_aapl_str_to_line_encoding
#define aapl_dfe_tune_mode_to_str MYD_aapl_dfe_tune_mode_to_str
#define aapl_str_to_dfe_tune_mode MYD_aapl_str_to_dfe_tune_mode
#define aapl_ip_type_to_str       MYD_aapl_ip_type_to_str
#define aapl_str_to_ip_type       MYD_aapl_str_to_ip_type
#define aapl_addr_to_str          MYD_aapl_addr_to_str
#define aapl_str_to_addr          MYD_aapl_str_to_addr
#define aapl_log_add              MYD_aapl_log_add
#define aapl_fail                 MYD_aapl_fail

/*//////////////////////////////////////////////////////////////////////
 * AAPL LOGGING functions:
 */

/** @defgroup Logging Logging Functions and Types
 ** @{
 **/

EXT int  aapl_fail(      Aapl_t *aapl, const char *caller, int line, const char *fmt, ...);

#ifdef MYD_DEBUG
EXT void aapl_log_printf(Aapl_t *aapl, Aapl_log_type_t log_sel, const char *caller, int line, const char * fmt, ...);
#else
#define aapl_log_printf(...) 
#endif

EXT void aapl_log_add(   Aapl_t *aapl, Aapl_log_type_t log_sel, const char *string, const char *caller, int line);

/* Printf append to a dynamically growing buffer: */
EXT void aapl_buf_add(Aapl_t *aapl, char **buf, char **buf_end, int *size, const char *fmt, ...);

EXT const char *aapl_log_get(Aapl_t *aapl);
EXT void        aapl_log_clear(Aapl_t *aapl);

EXT void aapl_start_file_logging(Aapl_t *aapl, const char* filepath);
EXT void aapl_stop_file_logging(Aapl_t *aapl);

# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
/** @cond INTERNAL */
    EXT void aapl_built_in_logging_fn(Aapl_t *aapl, Aapl_log_type_t log_sel, const char * buf, size_t new_item_length);
/** @endcond */
# endif

EXT void aapl_register_logging_fn(Aapl_t *aapl,
    void (* log_fn)(Aapl_t *, Aapl_log_type_t log_sel, const char * buf, size_t new_item_length),
    int  (* log_open_fn)(Aapl_t *),
    int  (* log_close_fn)(Aapl_t *)
);
/** @} */


/*//////////////////////////////////////////////////////////////////////
 * Functions to convert types to strings, and strings to types.
 * Allows for human readable output of these enums during logging.
 */

# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
/** @cond INTERNAL */
    typedef struct
    {
        const char *const name;
        int value;
    } Aapl_conv_table_t;

    EXT int name_to_index(Aapl_conv_table_t tbl[], const char *name, uint skip_prefix);
    EXT int value_to_index(Aapl_conv_table_t tbl[], int value);
/** @endcond */
# endif

EXT const char *aapl_addr_to_str          (uint                          val);
EXT const char *aapl_bigint_to_str        (bigint                        val);
EXT const char *aapl_bool_to_str          (int                           val);
EXT const char *aapl_comm_method_to_str   (Aapl_comm_method_t            val);
EXT const char *aapl_cmp_data_to_str      (Avago_serdes_rx_cmp_data_t    val);
EXT const char *aapl_cmp_mode_to_str      (Avago_serdes_rx_cmp_mode_t    val);
EXT const char *aapl_data_sel_to_str      (Avago_serdes_tx_data_sel_t    val);
EXT const char *aapl_dfe_status_to_str    (uint                          val);
EXT const char *aapl_dfe_tune_mode_to_str (Avago_serdes_dfe_tune_mode_t  val);
EXT const char *aapl_enable_to_str        (int                           val);
EXT const char *aapl_line_encoding_to_str (Avago_serdes_line_encoding_t  val);
EXT const char *aapl_ip_type_to_str       (Avago_ip_type_t               val);
EXT const char *aapl_log_type_to_str      (Aapl_log_type_t               val);
EXT const char *aapl_mem_type_to_str      (Avago_serdes_mem_type_t       val);
EXT const char *aapl_onoff_to_str         (int                           val);
EXT const char *aapl_pll_clk_to_str       (Avago_serdes_tx_pll_clk_t     val);
EXT const char *aapl_process_id_to_str    (Avago_process_id_t            val);
EXT const char *aapl_rx_clock_cdc_to_str  (Avago_serdes_rx_clock_cdc_t   val);
EXT const char *aapl_rx_clock_to_str      (Avago_serdes_rx_clock_t       val);
EXT const char *aapl_term_to_str          (Avago_serdes_rx_term_t        val);
EXT const char *aapl_spico_clk_to_str     (Avago_serdes_spico_clk_t      val);

EXT BOOL aapl_str_to_addr         (const char *name, char **endptr, uint *addr);
EXT BOOL aapl_str_to_cmp_data     (const char *name, Avago_serdes_rx_cmp_data_t *out);
EXT BOOL aapl_str_to_cmp_mode     (const char *name, Avago_serdes_rx_cmp_mode_t *out);
EXT BOOL aapl_str_to_comm_method  (const char *name, Aapl_comm_method_t *out);
EXT BOOL aapl_str_to_data_sel     (const char *name, Avago_serdes_tx_data_sel_t *out);
EXT BOOL aapl_str_to_dfe_tune_mode(const char *name, Avago_serdes_dfe_tune_mode_t *out);
EXT BOOL aapl_str_to_line_encoding(const char *name, Avago_serdes_line_encoding_t *out);
EXT BOOL aapl_str_to_ip_type      (const char *name, Avago_ip_type_t *out);
EXT BOOL aapl_str_to_mem_type     (const char *name, Avago_serdes_mem_type_t *out);
EXT BOOL aapl_str_to_pll_clk      (const char *name, Avago_serdes_tx_pll_clk_t *out);
EXT BOOL aapl_str_to_rx_clock     (const char *name, Avago_serdes_rx_clock_t *out);
EXT BOOL aapl_str_to_rx_clock_cdc (const char *name, Avago_serdes_rx_clock_cdc_t *out);
EXT BOOL aapl_str_to_term         (const char *name, Avago_serdes_rx_term_t *out);
EXT BOOL aapl_str_to_spico_clk    (const char *name, Avago_serdes_spico_clk_t *out);

#endif
