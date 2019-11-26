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

/* AAPL (ASIC and ASSP Programming Layer) generic handling of SerDes
 * (Serializer/Deserializer) slices on ASIC SBus rings; all functions exported
 * from this directory.
 */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for SerDes PMD/KR functions.
 **/

#ifndef AVAGO_SERDES_PMD_H_
#define AVAGO_SERDES_PMD_H_

/*//////////////////////////////////////////////////////////////////////////////
 * START: KR functions and structs
 */

/**@brief Controls which Rx DFE settings are updated. */
typedef enum
{
    AVAGO_PMD_RESTART,        /**< Reset the PMD training */
    AVAGO_PMD_BYPASS,         /**< Set Tx Eq to Initialize and start sending core data */
    AVAGO_PMD_TRAIN           /**< Run full PMD training */
} Avago_serdes_pmd_train_mode_t;

/**@brief Controls which Rx DFE settings are updated. */
typedef enum
{
    AVAGO_PMD_FC16G,         /**< PRBS11 - x^11 + x^9 + 1 */
    AVAGO_PMD_CL72,          /**< PRBS11 - x^11 + x^9 + 1 */
    AVAGO_PMD_CL84,          /**< PRBS11 - x^11 + x^9 + 1 */
    AVAGO_PMD_CL92           /**< PRBS11 - sequence based on lane config */
} Avago_serdes_pmd_clause_t;

/**@brief Link Training Configuration struct. */
typedef struct
{
  Avago_serdes_pmd_train_mode_t train_mode;/**< Select pmd link training mode to execute by serdes_pmd_train */

  uint sbus_addr;        /**< SBus Rx Address of SerDes to run training on */

  BOOL disable_timeout;  /**< Disables the timeout timer */

  Avago_serdes_pmd_clause_t clause; /**< CL72,CL84,CL92 */
  uint                        lane; /**< When clause is set to CL92, defines which PMD lane this SerDes is */
  uint                   prbs_seed; /**< When non-zero overrides the default PRBS seed value */

  BOOL  TT_FECreq;      /**< Set to transmit FEC request in TT training frames. */
  BOOL  TT_FECcap;      /**< Set to transmit FEC capability in TT training frames. */
  BOOL  TT_TF;          /**< Set to transmit Fixed TxEq in TT training frames. */

} Avago_serdes_pmd_config_t;

EXT Avago_serdes_pmd_config_t *avago_serdes_pmd_config_construct(Aapl_t *aapl);
EXT void avago_serdes_pmd_config_destruct( Aapl_t *aapl, Avago_serdes_pmd_config_t *pmd_config);
EXT void avago_serdes_pmd_train(Aapl_t *aapl, Avago_serdes_pmd_config_t *mode_control);
EXT int  avago_serdes_pmd_status(Aapl_t *aapl, uint addr);

/**@brief Tap request & response tracking struct */
typedef struct
{
    uint inc; /**< Number of inc requests */
    uint dec; /**< Number of dec requests */
    uint max; /**< Number of max responses */
    uint min; /**< Number of min responses */
} Avago_serdes_pmd_request_t;

/**@brief Statistics for a given transmitter (local or remote) */
typedef struct
{
    uint  preset;                 /**< Number of preset requests */
    uint  initialize;             /**< Number of initialize requests */
    Avago_serdes_pmd_request_t *tap[3]; /**< Stats for taps (pre,cursor,post) */
} Avago_serdes_pmd_tap_stats_t;

/**@brief Link Training Debug Information */
typedef struct
{
    BOOL reset; /**< Query statistics and then clear them (Note: also done when training is started) */

    uint rx_metric;              /**< RxEq metric */

    Avago_serdes_pmd_tap_stats_t *lcl;    /**< Stats for change requests done by local training code */
    Avago_serdes_pmd_tap_stats_t *remote; /**< Stats for change requests done by remote */

    uint last_remote_request[8]; /**< Last 8 requests sent by remote partner */
    uint last_local_request;     /**< Last request made by local training logic */

} Avago_serdes_pmd_debug_t;

EXT Avago_serdes_pmd_debug_t *avago_serdes_pmd_debug_construct(Aapl_t *aapl);
EXT void avago_serdes_pmd_debug_destruct( Aapl_t *aapl, Avago_serdes_pmd_debug_t *pmd_debug);

/* Run/Halt PMD link training  on a serdes based on tune_mode */
EXT void avago_serdes_pmd_debug(Aapl_t *aapl, uint sbus_addr, Avago_serdes_pmd_debug_t *pmd_debug);
EXT void avago_serdes_pmd_debug_print(Aapl_t *aapl, Avago_serdes_pmd_debug_t *pmd_debug);
EXT void avago_serdes_pmd_debug_print_repeat(Aapl_t *aapl, Avago_serdes_pmd_debug_t * pmd_debug);

EXT const char *aapl_pmd_clause_to_str    (Avago_serdes_pmd_clause_t     val);
EXT const char *aapl_pmd_train_mode_to_str(Avago_serdes_pmd_train_mode_t val);
EXT BOOL aapl_str_to_pmd_clause(    const char *name, Avago_serdes_pmd_clause_t     *out);
EXT BOOL aapl_str_to_pmd_train_mode(const char *name, Avago_serdes_pmd_train_mode_t *out);

#endif
