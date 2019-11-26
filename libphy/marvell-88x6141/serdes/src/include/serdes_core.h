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

/* Core SerDes types and functions.
 */

/** Doxygen File Header
 ** @file
 ** @brief Core SerDes types and functions.
 **/

#ifndef AAPL_SERDES_CORE_H_
#define AAPL_SERDES_CORE_H_

#define avago_serdes_mem_wr                   MYD_avago_serdes_mem_wr
#define avago_serdes_mem_rd                   MYD_avago_serdes_mem_rd
#define avago_serdes_get_lsb_rev              MYD_avago_serdes_get_lsb_rev
#define avago_serdes_mem_rmw                  MYD_avago_serdes_mem_rmw
#define avago_serdes_get_tx_rx_ready          MYD_avago_serdes_get_tx_rx_ready
#define avago_serdes_set_tx_rx_enable         MYD_avago_serdes_set_tx_rx_enable
#define avago_serdes_get_tx_output_enable     MYD_avago_serdes_get_tx_output_enable
#define avago_serdes_set_tx_output_enable     MYD_avago_serdes_set_tx_output_enable
#define avago_serdes_get_tx_data_sel          MYD_avago_serdes_get_tx_data_sel
#define avago_serdes_set_tx_data_sel          MYD_avago_serdes_set_tx_data_sel
#define avago_serdes_get_tx_user_data         MYD_avago_serdes_get_tx_user_data
#define avago_serdes_set_tx_user_data         MYD_avago_serdes_set_tx_user_data
#define avago_serdes_get_tx_invert            MYD_avago_serdes_get_tx_invert
#define avago_serdes_set_tx_invert            MYD_avago_serdes_set_tx_invert
#define avago_serdes_bits_to_width            MYD_avago_serdes_bits_to_width
#define avago_serdes_width_to_bits            MYD_avago_serdes_width_to_bits
#define avago_serdes_get_tx_rx_width          MYD_avago_serdes_get_tx_rx_width
#define avago_serdes_set_tx_rx_width_pam      MYD_avago_serdes_set_tx_rx_width_pam
#define avago_serdes_set_tx_rx_width          MYD_avago_serdes_set_tx_rx_width
#define avago_serdes_get_tx_rx_line_encoding  MYD_avago_serdes_get_tx_rx_line_encoding
#define avago_serdes_get_tx_line_encoding     MYD_avago_serdes_get_tx_line_encoding
#define avago_serdes_get_tx_datapath_encoding MYD_avago_serdes_get_tx_datapath_encoding
#define avago_serdes_set_tx_datapath_encoding MYD_avago_serdes_set_tx_datapath_encoding
#define avago_serdes_get_rx_line_encoding     MYD_avago_serdes_get_rx_line_encoding
#define avago_serdes_get_rx_datapath_encoding MYD_avago_serdes_get_rx_datapath_encoding
#define avago_serdes_set_rx_datapath_encoding MYD_avago_serdes_set_rx_datapath_encoding
#define avago_serdes_tx_eq_init               MYD_avago_serdes_tx_eq_init
#define avago_serdes_get_tx_eq                MYD_avago_serdes_get_tx_eq
#define avago_serdes_set_tx_eq                MYD_avago_serdes_set_tx_eq
#define avago_serdes_get_rx_cmp_data          MYD_avago_serdes_get_rx_cmp_data
#define avago_serdes_set_rx_cmp_data          MYD_avago_serdes_set_rx_cmp_data
#define avago_serdes_get_rx_term              MYD_avago_serdes_get_rx_term
#define avago_serdes_set_rx_term              MYD_avago_serdes_set_rx_term
#define avago_serdes_get_rx_live_data         MYD_avago_serdes_get_rx_live_data
#define avago_serdes_rx_inject_error          MYD_avago_serdes_rx_inject_error
#define avago_serdes_tx_inject_error          MYD_avago_serdes_tx_inject_error
#define avago_serdes_get_rx_cmp_mode          MYD_avago_serdes_get_rx_cmp_mode
#define avago_serdes_set_rx_cmp_mode          MYD_avago_serdes_set_rx_cmp_mode
#define avago_serdes_get_rx_invert            MYD_avago_serdes_get_rx_invert
#define avago_serdes_set_rx_invert            MYD_avago_serdes_set_rx_invert
#define avago_serdes_get_rx_input_loopback    MYD_avago_serdes_get_rx_input_loopback
#define avago_serdes_set_rx_input_loopback    MYD_avago_serdes_set_rx_input_loopback
#define aapl_serdes_get_int30_bits            MYD_aapl_serdes_get_int30_bits
#define avago_serdes_get_spico_clk_src        MYD_avago_serdes_get_spico_clk_src
#define avago_serdes_set_spico_clk_src        MYD_avago_serdes_set_spico_clk_src
#define avago_serdes_get_tx_pll_clk_src       MYD_avago_serdes_get_tx_pll_clk_src
#define avago_serdes_set_tx_pll_clk_src       MYD_avago_serdes_set_tx_pll_clk_src
#define avago_serdes_get_signal_ok_enable     MYD_avago_serdes_get_signal_ok_enable
#define avago_serdes_get_electrical_idle      MYD_avago_serdes_get_electrical_idle
#define avago_serdes_get_signal_ok_threshold  MYD_avago_serdes_get_signal_ok_threshold
#define avago_serdes_get_signal_ok            MYD_avago_serdes_get_signal_ok
#define avago_serdes_get_signal_ok_live       MYD_avago_serdes_get_signal_ok_live
#define avago_serdes_initialize_signal_ok     MYD_avago_serdes_initialize_signal_ok
#define avago_serdes_get_frequency_lock       MYD_avago_serdes_get_frequency_lock
#define avago_serdes_error_flag_reset         MYD_avago_serdes_error_flag_reset
#define avago_serdes_get_error_flag           MYD_avago_serdes_get_error_flag
#define avago_serdes_error_reset              MYD_avago_serdes_error_reset
#define avago_serdes_get_errors               MYD_avago_serdes_get_errors
#define avago_serdes_enable_core_to_cntl      MYD_avago_serdes_enable_core_to_cntl
#define avago_serdes_slip_bits                MYD_avago_serdes_slip_bits
#define avago_serdes_slip_rx_phase            MYD_avago_serdes_slip_rx_phase
#define avago_serdes_slip_tx_phase            MYD_avago_serdes_slip_tx_phase
#define avago_serdes_enable_core_bit_slip     MYD_avago_serdes_enable_core_bit_slip
#define avago_serdes_init_config_construct    MYD_avago_serdes_init_config_construct
#define avago_serdes_init_config_destruct     MYD_avago_serdes_init_config_destruct
#define avago_serdes_init                     MYD_avago_serdes_init
#define avago_serdes_init_quick               MYD_avago_serdes_init_quick
#define avago_serdes_tune_init                MYD_avago_serdes_tune_init
#define avago_serdes_eye_get_simple_metric    MYD_avago_serdes_eye_get_simple_metric
#define avago_serdes_get_rx_register_clock    MYD_avago_serdes_get_rx_register_clock
#define avago_serdes_set_error_timer          MYD_avago_serdes_set_error_timer
#define avago_serdes_hal_get                  MYD_avago_serdes_hal_get
#define avago_serdes_hal_set                  MYD_avago_serdes_hal_set
#define avago_serdes_tune                     MYD_avago_serdes_tune
#define avago_serdes_hal_func                 MYD_avago_serdes_hal_func

EXT int avago_serdes_get_lsb_rev(Aapl_t *aapl, uint sbus_addr);

/*//////////////////////////////////////////////////////////////////////
 * Memory access functions:
 */

/** @brief   Selects memory access type.
 ** @details AVAGO_LSB_DIRECT uses SBus transactions to read/write data,
 **          which avoids interrupting the processor, and also works if the
 **          SPICO processor is not running.
 ** @details AVAGO_ESB_DIRECT also works if the processor is not running,
 **          though it is much slower than AVAGO_ESB.
 ** @details The *_PREHALTED versions assume the caller invokes
 **          avago_spico_halt() and avago_spico_resume()
 **          appropriately, and are used to avoid the overhead of halting
 **          and restarting the processor for multiple successive reads.
 **/
typedef enum
{
    AVAGO_ESB,            /**< Electrical Sub-Block access. */
    AVAGO_ESB_DIRECT,     /**< ESB access using SBus instead of an interrupt. */
    AVAGO_LSB,            /**< Logical Sub-Block access. */
    AVAGO_LSB_DIRECT,     /**< LSB access using SBus instead of an interrupt. */
    AVAGO_DMEM,           /**< Data memory access. */
    AVAGO_DMEM_PREHALTED, /**< Data memory access, processor already halted. */
    AVAGO_IMEM,           /**< Instruction memory access. */
    AVAGO_IMEM_PREHALTED, /**< Instruction memory access, processor already halted. */
    AVAGO_BIG_REG_16,     /**< Access 16 bit big register reads/writes */
    AVAGO_BIG_REG_32      /**< Access 32 bit big register reads/writes */
} Avago_serdes_mem_type_t;

EXT int  avago_serdes_mem_rd(Aapl_t *aapl, uint sbus_addr,
                             Avago_serdes_mem_type_t type, uint addr);
EXT void avago_serdes_mem_wr(Aapl_t *aapl, uint sbus_addr,
                             Avago_serdes_mem_type_t type, uint addr, uint data);
EXT int avago_serdes_mem_rmw(Aapl_t *aapl, uint sbus_addr,
                             Avago_serdes_mem_type_t type, uint addr, uint data, uint mask);


# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
    EXT int aapl_get_pcs_architecture(Aapl_t *aapl, uint addr);
    EXT int avago_serdes_width_to_bits(int width);
    EXT int avago_serdes_bits_to_width(uint bits);
    EXT int avago_serdes_get_rx_register_clock(Aapl_t *aapl, uint addr);
    EXT int aapl_serdes_get_int30_bits(Aapl_t *aapl, uint addr, uint mask);
    EXT void avago_serdes_get_ei_limits(Aapl_t *aapl, uint addr, int *ei_min, int *ei_max);
# endif


/**< @brief The TX input data selections. */
typedef enum
{
    AVAGO_SERDES_TX_DATA_SEL_PRBS7    = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    AVAGO_SERDES_TX_DATA_SEL_PRBS9    = 1, /**< PRBS9 (x^9+x^5+1). */
    AVAGO_SERDES_TX_DATA_SEL_PRBS11   = 2, /**< PRBS11 (x^11+x^9+1). */
    AVAGO_SERDES_TX_DATA_SEL_PRBS15   = 3, /**< PRBS15 (x^15+x^14+1). */
    AVAGO_SERDES_TX_DATA_SEL_PRBS23   = 4, /**< PRBS23 (x^23+x^18+1). */
    AVAGO_SERDES_TX_DATA_SEL_PRBS31   = 5, /**< PRBS31 (x^31+x^28+1). */
    AVAGO_SERDES_TX_DATA_SEL_PRBS13   = 6, /**< PRBS13 (x^13+x^12+x^2+x^1+1) */
    AVAGO_SERDES_TX_DATA_SEL_USER     = 7, /**< User pattern generator. */
    AVAGO_SERDES_TX_DATA_SEL_CORE     = 8, /**< External data. */
    AVAGO_SERDES_TX_DATA_SEL_LOOPBACK = 9, /**< Parallel loopback from receiver. */
    AVAGO_SERDES_TX_DATA_SEL_PMD      = 10,/**< PMD training data. */
    AVAGO_SERDES_TX_DATA_SEL_AN       = 11 /**< Auto-negotiation data. */
} Avago_serdes_tx_data_sel_t;

EXT Avago_serdes_tx_data_sel_t avago_serdes_get_tx_data_sel(Aapl_t *aapl, uint sbus_addr);
EXT int                        avago_serdes_set_tx_data_sel(Aapl_t *aapl, uint sbus_addr,
                                                            Avago_serdes_tx_data_sel_t input);

EXT int  avago_serdes_get_tx_user_data(Aapl_t *aapl, uint sbus_addr, long data[4]);
EXT int  avago_serdes_set_tx_user_data(Aapl_t *aapl, uint sbus_addr, long data[4]);

EXT int  avago_serdes_get_tx_rx_ready(Aapl_t *aapl, uint sbus_addr, BOOL *tx, BOOL *rx);
EXT int  avago_serdes_set_tx_rx_enable(Aapl_t *aapl, uint sbus_addr, BOOL tx, BOOL rx, BOOL tx_output);
EXT BOOL avago_serdes_get_burst_mode(Aapl_t *aapl, uint addr);

EXT BOOL avago_serdes_get_tx_output_enable(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_set_tx_output_enable(Aapl_t *aapl, uint sbus_addr, BOOL enable);

EXT BOOL avago_serdes_get_tx_invert(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_set_tx_invert(Aapl_t *aapl, uint sbus_addr, BOOL invert);

EXT int avago_serdes_set_tx_datapath_encoding(Aapl_t *aapl, uint addr, BOOL gray_encode, BOOL precode);
EXT int avago_serdes_get_tx_datapath_encoding(Aapl_t *aapl, uint addr, BOOL *gray_encode, BOOL *precode);

EXT int  avago_serdes_tx_inject_error(Aapl_t *aapl, uint sbus_addr, uint num_bits);
EXT int  avago_serdes_rx_inject_error(Aapl_t *aapl, uint sbus_addr, uint num_bits);

/**< @brief The width mode and line encoding selections */
typedef enum
{
    AVAGO_SERDES_NRZ  = 0,    /**< Transmit using 2 levels of encoding */
    AVAGO_SERDES_PAM2 = 0,    /**< Transmit using 2 levels of encoding */
    AVAGO_SERDES_PAM4 = 1     /**< Transmit using 4 levels of encoding */
} Avago_serdes_line_encoding_t;
typedef Avago_serdes_line_encoding_t Avago_serdes_encoding_mode_t;

EXT int  avago_serdes_get_tx_rx_width(Aapl_t *aapl, uint sbus_addr, int *tx_width, int *rx_width);
EXT int  avago_serdes_set_tx_rx_width(Aapl_t *aapl, uint sbus_addr, int tx_width, int rx_width);
EXT BOOL avago_serdes_get_tx_line_encoding(Aapl_t *aapl, uint addr);
EXT BOOL avago_serdes_get_rx_line_encoding(Aapl_t *aapl, uint addr);
EXT int  avago_serdes_get_tx_rx_line_encoding(Aapl_t *aapl, uint addr, Avago_serdes_line_encoding_t *tx, Avago_serdes_line_encoding_t *rx);
EXT int  avago_serdes_set_tx_rx_width_pam(Aapl_t *aapl, uint sbus_addr, int tx_width, int rx_width, Avago_serdes_line_encoding_t tx_encoding, Avago_serdes_line_encoding_t rx_encoding);


/**< @brief The TX equalization settings. */
typedef struct
{
    short pre;            /**< Pre-cursor setting */
    short atten;          /**< Attenuator setting */
    short post;           /**< Post-cursor setting */
    short slew;           /**< Slew rate setting [0..3], 0 is fastest */
    short pre2;           /**< Pre-cursor setting */
    short pre3;           /**< Pre-cursor setting */
    short vert;           /**< vert skew setting - valid only for OM4 */
    short pre_lsb;        /**< Pre-cursor LSB setting - valid only for CM4/OM4 */
    short pre_msb;        /**< Pre-cursor MSB setting - valid only for CM4/OM4 */
    short atten_lsb;      /**< Attenuator LSB setting - valid only for CM4/OM4 */
    short atten_msb;      /**< Attenuator MSB setting - valid only for CM4/OM4 */
    short post_lsb;       /**< Post-cursor LSB setting - valid only for CM4/OM4 */
    short post_msb;       /**< Post-cursor MSB setting - valid only for CM4/OM4 */
    short pre2_lsb;       /**< Pre-cursor LSB setting - valid only for CM4 */
    short pre2_msb;       /**< Pre-cursor MSB setting - valid only for CM4 */
    short amp;            /**< AMP setting valid only for HVD6 */
    short t2;             /**< T2 setting - valid only for OM4 */
} Avago_serdes_tx_eq_t;

EXT void avago_serdes_tx_eq_init(Avago_serdes_tx_eq_t *ptr);
EXT int avago_serdes_get_tx_eq(Aapl_t *aapl, uint sbus_addr, Avago_serdes_tx_eq_t *tx_eq);
EXT int avago_serdes_set_tx_eq(Aapl_t *aapl, uint sbus_addr, Avago_serdes_tx_eq_t *tx_eq);



/** @brief Specify the pattern to use in validating the received data. */
typedef enum
{
    AVAGO_SERDES_RX_CMP_DATA_PRBS7    = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    AVAGO_SERDES_RX_CMP_DATA_PRBS9    = 1, /**< PRBS9 (x^9+x^5+1). */
    AVAGO_SERDES_RX_CMP_DATA_PRBS11   = 2, /**< PRBS11 (x^11+x^9+1). */
    AVAGO_SERDES_RX_CMP_DATA_PRBS15   = 3, /**< PRBS15 (x^15+x^14+1). */
    AVAGO_SERDES_RX_CMP_DATA_PRBS23   = 4, /**< PRBS23 (x^23+x^18+1). */
    AVAGO_SERDES_RX_CMP_DATA_PRBS31   = 5, /**< PRBS31 (x^31+x^28+1). */
    AVAGO_SERDES_RX_CMP_DATA_PRBS13   = 6, /**< PRBS13 (x^13+x^12+x^2+x^1+1) */
    AVAGO_SERDES_RX_CMP_DATA_SELF_SEED= 7, /**< Auto-seed to received 40 bit repeating pattern. */
                                           /**< NOTE: This is USER mode in firmware. */
    AVAGO_SERDES_RX_CMP_DATA_OFF      = 8  /**< Disable cmp data generator */
} Avago_serdes_rx_cmp_data_t;

EXT Avago_serdes_rx_cmp_data_t avago_serdes_get_rx_cmp_data(Aapl_t *aapl, uint sbus_addr);
EXT int                        avago_serdes_set_rx_cmp_data(Aapl_t *aapl, uint sbus_addr,
                                                            Avago_serdes_rx_cmp_data_t cmp_data);

EXT BOOL avago_serdes_get_rx_input_loopback(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_set_rx_input_loopback(Aapl_t *aapl, uint sbus_addr, BOOL select_internal);

EXT BOOL avago_serdes_get_rx_invert(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_set_rx_invert(Aapl_t *aapl, uint sbus_addr, BOOL invert);

/** @brief Datapath configurations. */
typedef struct
{
    uint mask;             /**< Select which value to update */
                           /**< 0x01 = polarity_invert, 0x02 = gray_enable */
                           /**< 0x04 = precode_enable, 0x08 = swizzle_enable */
    BOOL polarity_invert;  /**< Polarity inversion */
    BOOL gray_enable;      /**< Gray coding */
    BOOL precode_enable;   /**< Pre-coding */
    BOOL swizzle_enable;   /**< Swizzle coding */
}Avago_serdes_datapath_t;

EXT int avago_serdes_get_rx_datapath(Aapl_t *aapl, uint addr, Avago_serdes_datapath_t *datapath);
EXT int avago_serdes_set_rx_datapath(Aapl_t *aapl, uint addr, Avago_serdes_datapath_t *datapath);
EXT int avago_serdes_get_tx_datapath(Aapl_t *aapl, uint addr, Avago_serdes_datapath_t *datapath);
EXT int avago_serdes_set_tx_datapath(Aapl_t *aapl, uint addr, Avago_serdes_datapath_t *datapath);

EXT int avago_serdes_set_rx_datapath_encoding(Aapl_t *aapl, uint addr, BOOL gray_decode, BOOL predecode);
EXT int avago_serdes_get_rx_datapath_encoding(Aapl_t *aapl, uint addr, BOOL *gray_decode, BOOL *predecode);

EXT int avago_serdes_get_rx_data(Aapl_t *aapl, uint sbus_addr, long data[4]);
EXT int avago_serdes_get_rx_live_data(Aapl_t *aapl, uint sbus_addr);


/** @brief Receiver data comparison mode. */
typedef enum
{
    AVAGO_SERDES_RX_CMP_MODE_OFF         = 0x0000, /**< Turn Off */
    AVAGO_SERDES_RX_CMP_MODE_XOR         = 0x0100, /**< Test^Mission */
    AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN = 0x0120, /**< Test^PatGen. */
    AVAGO_SERDES_RX_CMP_MODE_MAIN_PATGEN = 0x0200  /**< Mission^PatGen */
} Avago_serdes_rx_cmp_mode_t;

EXT Avago_serdes_rx_cmp_mode_t avago_serdes_get_rx_cmp_mode(Aapl_t *aapl, uint sbus);
EXT int                        avago_serdes_set_rx_cmp_mode(Aapl_t *aapl, uint sbus,
                                                            Avago_serdes_rx_cmp_mode_t mode);


/** @brief Specify the RX termination value. */
typedef enum
{
    AVAGO_SERDES_RX_TERM_AGND = 0,    /**< Resistor to ground */
    AVAGO_SERDES_RX_TERM_AVDD = 1,    /**< Resistor to AVDD */
    AVAGO_SERDES_RX_TERM_FLOAT = 2    /**< No resistor. */
} Avago_serdes_rx_term_t;

EXT Avago_serdes_rx_term_t avago_serdes_get_rx_term(Aapl_t *aapl, uint sbus_addr);
EXT int                    avago_serdes_set_rx_term(Aapl_t *aapl, uint sbus_addr,
                                                    Avago_serdes_rx_term_t term);

/** @brief Select the SPICO clock source. */
typedef enum
{
    AVAGO_SERDES_SPICO_REFCLK                = 0, /**< default */
    AVAGO_SERDES_SPICO_PCIE_CORE_CLK         = 1,
    AVAGO_SERDES_SPICO_TX_F10_CLK_FIXED      = 2,
    AVAGO_SERDES_SPICO_TX_FN_CLK             = 2,   /**< M4 and newest D6 slices (datapath clock) */
    AVAGO_SERDES_SPICO_TX_F40_CLK_FIXED      = 3,   /**< Most D6 slices */
    AVAGO_SERDES_SPICO_REFCLK1               = 3,   /**< M4 and newest D6 slices */
    AVAGO_SERDES_SPICO_REFCLK_DIV2           = 4,
    AVAGO_SERDES_SPICO_PCIE_CORE_CLK_DIV2    = 5,
    AVAGO_SERDES_SPICO_TX_F10_CLK_FIXED_DIV2 = 6,
    AVAGO_SERDES_SPICO_TX_FN_CLK_DIV2        = 6,   /**< M4 and newest D6 slices (datapath clock) */
    AVAGO_SERDES_SPICO_TX_F40_CLK_FIXED_DIV2 = 7,   /**< Most D6 slices */
    AVAGO_SERDES_SPICO_REFCLK1_DIV2          = 7,   /**< M4 and newest D6 slices */
    AVAGO_SERDES_SPICO_TX_DATA_CLK           = 2,   /**< P1 only */
    AVAGO_SERDES_SPICO_TX_DATA_CLK_DIV2      = 6,   /**< P1 only */
    AVAGO_SERDES_SPICO_TX_F20_CLK_FIXED      = 0xe,
    AVAGO_SERDES_SPICO_TX_F80_CLK_FIXED      = 0xf
} Avago_serdes_spico_clk_t;

EXT Avago_serdes_spico_clk_t avago_serdes_get_spico_clk_src(Aapl_t *aapl, uint sbus_addr);
EXT int                      avago_serdes_set_spico_clk_src(Aapl_t *aapl, uint sbus_addr,
                                                            Avago_serdes_spico_clk_t src);

/** @brief Select the Tx PLL clock source. */
typedef enum
{
    AVAGO_SERDES_TX_PLL_REFCLK             = 0x00,    /**< Use REF clock; default. */
    AVAGO_SERDES_TX_PLL_RX_DIVX            = 0x10,    /**< Use the recovered clock. */
    AVAGO_SERDES_TX_PLL_OFF                = 0x30,    /**< Use no clock. */
    AVAGO_SERDES_TX_PLL_PCIE_CORE_CLK      = 0x70,    /**< Use core clock. */
    AVAGO_SERDES_TX_PLL_PCIE_CORE_CLK_DIV2 = 0xf0     /**< Use core clock / 2. */
} Avago_serdes_tx_pll_clk_t;

EXT Avago_serdes_tx_pll_clk_t avago_serdes_get_tx_pll_clk_src(Aapl_t *aapl, uint sbus_addr);
EXT int                       avago_serdes_set_tx_pll_clk_src(Aapl_t *aapl, uint sbus_addr,
                                                              Avago_serdes_tx_pll_clk_t src);

EXT BOOL avago_serdes_get_electrical_idle(Aapl_t *aapl, uint sbus_addr);
EXT BOOL avago_serdes_get_signal_ok_enable(Aapl_t *aapl, uint sbus_addr);
EXT int  avago_serdes_get_signal_ok_threshold(Aapl_t *aapl, uint sbus_addr);

EXT BOOL avago_serdes_get_signal_ok(Aapl_t *aapl, uint sbus_addr, BOOL reset);
EXT int avago_serdes_initialize_signal_ok(Aapl_t *aapl, uint sbus_addr, int threshold);

EXT int avago_serdes_launch_ei_calibration(Aapl_t *aapl, uint addr, BOOL ei_cal);
EXT int avago_serdes_get_ei_calibration_status(Aapl_t *aapl, uint addr);
EXT int avago_serdes_get_ei_calibration_threshold(Aapl_t *aapl, uint addr);
EXT int avago_serdes_set_ei_calibration_threshold(Aapl_t *aapl, uint addr, int threshold);

EXT BOOL avago_serdes_get_frequency_lock(Aapl_t *aapl, uint sbus_addr);
EXT uint avago_serdes_get_frequency_lock_time(Aapl_t *aapl, uint addr);
EXT BOOL avago_serdes_get_signal_ok_live(Aapl_t *aapl, uint sbus_addr);

EXT uint avago_serdes_get_errors(Aapl_t *aapl, uint addr, Avago_serdes_mem_type_t type, BOOL reset_count_after_get);
EXT BOOL avago_serdes_error_reset(Aapl_t *aapl, uint addr);
EXT BOOL   avago_serdes_count_errors_start(Aapl_t *aapl, uint addr, bigint bits);
EXT int    avago_serdes_count_errors_wait(Aapl_t *aapl, uint addr);
EXT bigint avago_serdes_count_errors(Aapl_t *aapl, uint addr, bigint bits);
EXT BOOL avago_serdes_parallel_count_errors(Aapl_t *aapl, Avago_addr_t *list, bigint bits);
EXT int  avago_serdes_set_error_timer(Aapl_t *aapl, uint addr, bigint dwell_bits);

EXT BOOL avago_serdes_get_error_flag(Aapl_t *aapl, uint addr, BOOL reset);
EXT void avago_serdes_error_flag_reset(Aapl_t *aapl, uint addr);

EXT BOOL avago_serdes_aux_counter_disable(Aapl_t *aapl, uint addr);
EXT uint avago_serdes_aux_counter_read(Aapl_t *aapl, uint addr);
EXT BOOL avago_serdes_aux_counter_start(Aapl_t *aapl, uint addr);

EXT BOOL avago_serdes_enable_core_to_cntl(Aapl_t *aapl, uint addr, BOOL enable_tx_rx_en, BOOL enable_low_power);
EXT BOOL avago_serdes_slip_bits(Aapl_t *aapl, uint sbus_addr, uint bits);
EXT BOOL avago_serdes_slip_rx_phase(Aapl_t *aapl, uint sbus_addr, uint bits, BOOL apply_at_init);
EXT BOOL avago_serdes_slip_tx_phase(Aapl_t *aapl, uint sbus_addr, uint bits, BOOL apply_at_init);
EXT BOOL avago_serdes_enable_core_bit_slip(Aapl_t *aapl, uint addr, BOOL enable_core, BOOL enable_pcs_fifo_clk_auto_slip);

EXT BOOL avago_serdes_enable_low_power_mode(Aapl_t *aapl, uint addr, BOOL enable);
EXT BOOL avago_serdes_enable_pcs_fifo_clock(Aapl_t *aapl, uint addr, BOOL enable);

/** @brief Initialize a SerDes slice. */
typedef enum
{
    AVAGO_PRBS31_ILB,    /**< Run a PRBS check in ILB; leave SerDes in ILB running PRBS 31 data. */
    AVAGO_PRBS31_ELB,    /**< Run a PRBS check in ILB; leave SerDes in ELB running PRBS 31 data. */
    AVAGO_CORE_DATA_ILB, /**< Run a PRBS check in ILB; leave SerDes in ILB sending data from the ASIC core. */
    AVAGO_CORE_DATA_ELB, /**< Run a PRBS check in ILB; leave SerDes in ELB sending data from the ASIC core. */
    AVAGO_INIT_ONLY      /**< Don't check any errors during init, just init the serdes. */
                         /**< SerDes will be left in ELB mode sending data from the ASIC core. */
} Avago_serdes_init_mode_t;

typedef struct
{
    BOOL sbus_reset;
    BOOL spico_reset;
    BOOL init_tx;
    BOOL init_rx;
    BOOL burst_mode;    /**< Only valid for PON SerDes */
    Avago_serdes_init_mode_t init_mode;
    BOOL skip_crc;

    uint tx_divider;
    Avago_serdes_line_encoding_t tx_encoding;
    Avago_serdes_datapath_t tx_datapath;
    BOOL tx_output_en;
    uint tx_width;      /**< TX width mode: 10, 20, 40, 80, 16, 32, or 64.  Valid values are SerDes dependent. */
    BOOL tx_phase_cal;
    BOOL refclk_sync_master;

    uint rx_divider;
    uint rate_sel;      /**< Rx rate selector. Only valid for PON SerDes */
                        /**< 0 = Quarter rate, 1 = Full rate, 2 = Eighth rate, 3 = Half rate */
    Avago_serdes_line_encoding_t rx_encoding;
    Avago_serdes_datapath_t rx_datapath;
    uint rx_width;      /**< RX width mode: 10, 20, 40, 80, 16, 32, or 64.  Valid values are SerDes dependent. */
    BOOL signal_ok_en;
    int  signal_ok_threshold;   /**< [0-15] */

    int fail_code;
} Avago_serdes_init_config_t;

EXT Avago_serdes_init_config_t *avago_serdes_init_config_construct(Aapl_t *aapl);
EXT void avago_serdes_init_config_destruct(Aapl_t *aapl, Avago_serdes_init_config_t *config);
EXT int avago_serdes_init(Aapl_t *aapl, uint sbus_addr, Avago_serdes_init_config_t *config);
EXT int avago_serdes_base_init(Aapl_t *aapl, uint sbus_addr, Avago_serdes_init_config_t *config);
EXT int avago_serdes_tx_init(Aapl_t *aapl, uint sbus_addr, Avago_serdes_init_config_t *config);
EXT int avago_serdes_rx_init(Aapl_t *aapl, uint sbus_addr, Avago_serdes_init_config_t *config);
EXT int avago_serdes_loopback_test(Aapl_t *aapl, uint sbus_addr, Avago_serdes_init_config_t *config);

EXT int  avago_parallel_serdes_base_init(           Aapl_t *aapl, Avago_addr_t *addr_list, BOOL skip_crc);
EXT BOOL avago_parallel_serdes_get_signal_ok(       Aapl_t *aapl, Avago_addr_t *addr_list, BOOL reset);
EXT int  avago_parallel_serdes_init(                Aapl_t *aapl, Avago_addr_t *addr_list, Avago_serdes_init_config_t *config);
EXT int  avago_parallel_serdes_initialize_signal_ok(Aapl_t *aapl, Avago_addr_t *addr_list, int threshold);
EXT int  avago_parallel_serdes_mem_rd(              Aapl_t *aapl, Avago_addr_t *addr_list, Avago_serdes_mem_type_t type, uint addr);
EXT int  avago_parallel_serdes_set_rx_datapath(     Aapl_t *aapl, Avago_addr_t *addr_list, Avago_serdes_datapath_t *datapath);
EXT int  avago_parallel_serdes_set_tx_datapath(     Aapl_t *aapl, Avago_addr_t *addr_list, Avago_serdes_datapath_t *datapath);
EXT int  avago_parallel_serdes_set_tx_rx_enable(    Aapl_t *aapl, Avago_addr_t *addr_list, BOOL tx, BOOL rx, BOOL tx_output, uint extra);
EXT int  avago_parallel_serdes_set_tx_rx_width_pam( Aapl_t *aapl, Avago_addr_t *addr_list, int tx, int rx, Avago_serdes_line_encoding_t tx_encoding, Avago_serdes_line_encoding_t rx_encoding);
EXT BOOL avago_parallel_verify_addr_list(           Aapl_t *aapl, Avago_addr_t *addr_list);

EXT int avago_serdes_pon_set_rate_select(Aapl_t *aapl, uint addr, uint rate_sel);
EXT int avago_serdes_pon_get_rate_select(Aapl_t *aapl, uint addr);
EXT int avago_serdes_init_quick(Aapl_t *aapl, uint sbus_addr, uint divider);

/**@brief Controls what type of tuning to execute. */
typedef enum
{
    AVAGO_DFE_ICAL,          /**< Initial calibration, coarse+fine tuning. (Default) */
    AVAGO_DFE_PCAL,          /**< Periodic calibration, fine tuning, no LF,HF adjustments */
    AVAGO_DFE_ICAL_ONLY,     /**< Initial calibration, coarse tuning without PCAL. */
    AVAGO_DFE_START_ADAPTIVE,/**< Launch continous pCAL */
    AVAGO_DFE_STOP_ADAPTIVE, /**< Stop continous pCAL */
    AVAGO_DFE_ENABLE_RR,     /**< Enable SerDes to participate in Round-Robin pCal */
    AVAGO_DFE_DISABLE_RR     /**< Disable SerDes from participation in Round-Robin pCal */
} Avago_serdes_dfe_tune_mode_t;


/** @brief   Specify tuning options.
 ** @details The order of fixed and value array elements is DC, LF, HF and BW.
 ** @details If fixed[n] is 0, then fixed tuning for that value will be disabled.
 ** @details If fixed[n] is 1, then fixed tuning using value[n] will be enabled.
 ** @details If fixed[n] is -1, then the fixed tuning state for that value will be left unchanged.
 ** @details All fixed setting changes are applied before tuning begins.
 **/
typedef struct
{
    int  fixed[4];  /**< Set to 0 to disable fixed state, 1 to set fixed value and -1 to make no change.  Initialized to -1 by avago_serdes_tune_init(). */
    int  value[4];  /**< Fixed value to set if corresponding fixed flag is 1. */

    uint dfe_disable; /**< When set, skip tuning of dfeTaps. */

    Avago_serdes_dfe_tune_mode_t tune_mode; /**< Select tuning mode to execute. */

} Avago_serdes_dfe_tune_t;
EXT void avago_serdes_tune_init(Aapl_t *aapl, Avago_serdes_dfe_tune_t *control);
EXT BOOL avago_serdes_tune(Aapl_t *aapl, uint sbus_addr, Avago_serdes_dfe_tune_t *control);

EXT uint avago_serdes_eye_get_simple_metric(Aapl_t *aapl, uint addr);


typedef enum
{
    AVAGO_SERDES_RX_CLOCK_OFF = 0,
    AVAGO_SERDES_RX_CLOCK_I,
    AVAGO_SERDES_RX_CLOCK_Q,
    AVAGO_SERDES_RX_CLOCK_R
} Avago_serdes_rx_clock_t;
typedef enum
{
    AVAGO_SERDES_RX_CDC_DATA = 0,
    AVAGO_SERDES_RX_CDC_EDGE,
    AVAGO_SERDES_RX_CDC_INV_DATA,
    AVAGO_SERDES_RX_CDC_INV_EDGE,
    AVAGO_SERDES_RX_CDC_OFF = 4,
    AVAGO_SERDES_RX_CDC_ICLK,
    AVAGO_SERDES_RX_CDC_QCLK,
    AVAGO_SERDES_RX_CDC_RCLK,
    AVAGO_SERDES_RX_CDC_INV_ICLK = 9,
    AVAGO_SERDES_RX_CDC_INV_QCLK,
    AVAGO_SERDES_RX_CDC_INV_RCLK
} Avago_serdes_rx_clock_cdc_t;

typedef struct
{
    Avago_serdes_rx_clock_t data;
    Avago_serdes_rx_clock_t edge;
    Avago_serdes_rx_clock_t test;
    Avago_serdes_rx_clock_t dfe;
    Avago_serdes_rx_clock_cdc_t cdc;
} Avago_serdes_rx_clocks_t;

EXT BOOL avago_serdes_set_rx_data_clock(Aapl_t *aapl, uint addr, Avago_serdes_rx_clock_t data);
EXT BOOL avago_serdes_set_rx_dfe_clock( Aapl_t *aapl, uint addr, Avago_serdes_rx_clock_t dfe );
EXT BOOL avago_serdes_set_rx_edge_clock(Aapl_t *aapl, uint addr, Avago_serdes_rx_clock_t edge);
EXT BOOL avago_serdes_set_rx_test_clock(Aapl_t *aapl, uint addr, Avago_serdes_rx_clock_t test);
EXT BOOL avago_serdes_set_rx_cdc_clock( Aapl_t *aapl, uint addr, Avago_serdes_rx_clock_cdc_t cdc);

EXT int   avago_serdes_rx_clock_apply(Aapl_t *aapl, uint addr, uint mask, Avago_serdes_rx_clocks_t *rx_clock);
EXT char *avago_serdes_rx_clock_print(Aapl_t *aapl, uint addr, uint mask, Avago_serdes_rx_clocks_t *rx_clock);
EXT int   avago_serdes_rx_clock_read( Aapl_t *aapl, uint addr,            Avago_serdes_rx_clocks_t *rx_clock);
EXT int   avago_serdes_rx_clock_write(Aapl_t *aapl, uint addr,            Avago_serdes_rx_clocks_t *rx_clock);


#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

EXT BOOL avago_serdes_get_fine_frequency_lock(Aapl_t *aapl, uint addr);
EXT int  avago_serdes_set_fine_frequency_lock(Aapl_t *aapl, uint addr, BOOL enable);

/** @brief SerDes HAL function enumerations */
typedef enum
{
    AVAGO_HAL_RXCLK_VERNIER_APPLY = 0x03, /**< Load Clock vernier settings into HW */
    AVAGO_HAL_TXEQ_FFE_APPLY      = 0x07, /**< Load Tx Eq settings into HW */
    AVAGO_HAL_DATA_CHANNEL_APPLY  = 0x0a, /**< Load Data channel VOS settings into HW */
    AVAGO_HAL_TEST_CHANNEL_APPLY  = 0x0d, /**< Load Test channel VOS settings into HW */
    AVAGO_HAL_RXEQ_FFE_APPLY      = 0x12, /**< Load RxFFE settings into HW */
    AVAGO_HAL_RXEQ_CTLE_APPLY     = 0x15, /**< Load CTLE  settings into HW */
    AVAGO_HAL_RXEQ_DFE_APPLY      = 0x18  /**< Load DFE   settings into HW */
} Avago_serdes_hal_func_type_t;

/** @brief SerDes HAL struct enumerations */
typedef enum
{
    AVAGO_HAL_GLOBAL_TUNE_PARAMS     = 0x01, /**< Load Clock vernier settings into HW */
    AVAGO_HAL_M4_TUNE_PARAMS         = 0x02, /**< Read/set M4 Tune Parameters */
    AVAGO_HAL_RXCLK_SELECT           = 0x03, /**< Read/set vernier settings */
    AVAGO_HAL_TXEQ_FFE               = 0x07, /**< Read/set Tx Eq settings */
    AVAGO_HAL_RXEQ_CTLE              = 0x09, /**< Read/set Rx CTLE settings */
    AVAGO_HAL_RXEQ_DFE               = 0x0b, /**< Read/set Rx DFE settings */
    AVAGO_HAL_RXEQ_FFE               = 0x0d, /**< Read/set Rx FFE settings */
    AVAGO_HAL_DATA_CHANNEL_INPUTS    = 0x0f, /**< Read/set data DAC offset from mid point */
    AVAGO_HAL_DATA_CHANNEL_OFFSET    = 0x0f, /**< */
    AVAGO_HAL_DATA_CHANNEL_CAL       = 0x11, /**< Read/set data VOS calibrated mid point */
    AVAGO_HAL_TEST_CHANNEL_INPUTS    = 0x12, /**< Read/set test DAC offset from mid point */
    AVAGO_HAL_TEST_CHANNEL_OFFSET    = 0x12, /**< */
    AVAGO_HAL_TEST_CHANNEL_CAL       = 0x14, /**< Read/set test VOS calibrated mid point */
    AVAGO_HAL_PAM4_EYE               = 0x17, /**< Read PAM4 eye parameters */
    AVAGO_HAL_PAM4_LEVELS            = 0x1f, /**< Read PAM4 eye middles */
    AVAGO_HAL_GRADIENT_INPUTS        = 0x20, /**< Read gradient inputs */
    AVAGO_HAL_DATA_CHANNEL_CAL_DELTA = 0x2c, /**< Read deltas between data and test channels */
    AVAGO_HAL_CLK_VERNIER_CAL        = 0x2f  /**< Read Rx clock vernier cals */
} Avago_serdes_hal_type_t;

EXT int  avago_serdes_hal_get (Aapl_t *aapl, uint addr, Avago_serdes_hal_type_t hal, uint member);
EXT int  avago_serdes_hal_set (Aapl_t *aapl, uint addr, Avago_serdes_hal_type_t hal, uint member, int value);
EXT void avago_serdes_hal_func(Aapl_t *aapl, uint addr, Avago_serdes_hal_func_type_t hal_func);

#endif

#endif
