/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/
/*******************************************************************************
 Copyright (c) 2014-2017 Avago Technologies. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level SERDES API functions 
********************************************************************/
#ifndef MYD_SERDES_H
#define MYD_SERDES_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#include "aapl.h"

/* Data structure definition */
#define _MYD_SER_DEV Aapl_t
typedef _MYD_SER_DEV *MYD_SER_DEV_PTR;
typedef _MYD_SER_DEV MYD_SER_DEV;

#define MYD_SER_EYE_CONFIG_TYPE Avago_serdes_eye_config_t
#define MYD_SER_EYE_DATA_TYPE Avago_serdes_eye_data_t

#define MYD_SER_INIT_CONFIG_TYPE Avago_serdes_init_config_t

#define MYD_SER_INIT_DFE_TUNE_TYPE Avago_serdes_dfe_tune_t

#define MYD_SER_ADDR_TYPE Avago_addr_t
#define MYD_SER_TX_EQ_TYPE Avago_serdes_tx_eq_t

#define MYD_SER_RX_DFE_TYPE Avago_serdes_dfe_state_t

#define MYD_SER_PMD_CONFIG_TYPE Avago_serdes_pmd_config_t
#define MYD_SER_PMD_DEBUG_TYPE Avago_serdes_pmd_debug_t

#define MYD_SER_LOG_ERROR   AVAGO_ERR
#define MYD_SER_LOG_WARNING AVAGO_WARNING
#define MYD_SER_LOG_INFO    AVAGO_INFO
#define MYD_SER_LOG_OFF     AVAGO_DEBUG0

#define MYD_SER_INIT_ONLY   AVAGO_INIT_ONLY

/* Wrapper function definitions */
/* initialization */
#define mydWrapperAllocDevStruct aapl_construct  
#define mydWrapperFreeDevStruct  aapl_destruct
#define mydWrapperSBusComm       aapl_is_sbus_communication_method
#define mydWrapperRegisterSBusFn aapl_register_sbus_fn
#define mydWrapperConnect        aapl_connect
#define mydWrapperGetIpInfo      aapl_get_ip_info
#define mydWrapperGetCDRLock     avago_serdes_get_frequency_lock
#define mydWrapperResetSerdes    avago_spico_reset
#define mydWrapperSerdesInt      avago_spico_int
#define mydWrapperSerdesQuickInit avago_serdes_init_quick
#define mydWrapperSerdesInit      avago_serdes_init
#define mydWrapperAllocInitConfig avago_serdes_init_config_construct
#define mydWrapperFreeInitConfig  avago_serdes_init_config_destruct

/* Eye */
#define mydWrapperEyeAllocConfig  avago_serdes_eye_config_construct
#define mydWrapperEyeFreeConfig   avago_serdes_eye_config_destruct
#define mydWrapperGetEye          avago_serdes_eye_get
#define mydWrapperEyeAllocDataSt  avago_serdes_eye_data_construct
#define mydWrapperEyeFreeDataSt   avago_serdes_eye_data_destruct
#define mydWrapperEyePlotWrite    avago_serdes_eye_plot_write
#define mydWrapperEyeWriteToFile  avago_serdes_eye_data_write_file

/* Revision */
#define mydWrapperBusMasterAddr   avago_make_sbus_master_addr
#define mydWrapperGetSerdesRev    avago_firmware_get_rev
#define mydWrapperGetSerdesBuild  aapl_get_firmware_build
#define mydWrapperAddrToStruct    avago_addr_to_struct
#define mydWrapperStructToAddr    avago_struct_to_addr

/* Diagnostic */
#define mydWrapperGetTemperature  avago_sensor_get_temperature
#define mydWrapperGetVoltage      avago_sensor_get_voltage
#define mydWrapperGetStateDump    avago_serdes_get_state_dump

/*  Tuning */
#define mydWrapperGetTxFFE        avago_serdes_get_tx_eq
#define mydWrapperSetTxFFE        avago_serdes_set_tx_eq
#define mydWrapperGetRxDFE        avago_serdes_get_dfe_state
#define mydWrapperGetRxDFEStatus  avago_serdes_get_dfe_status
#define mydWrapperSerDesTuneInit  avago_serdes_tune_init
#define mydWrapperSerDesTune      avago_serdes_tune

/* Inverter polarity */
#define mydWrapperGetTxPolarity   avago_serdes_get_tx_invert
#define mydWrapperSetTxPolarity   avago_serdes_set_tx_invert
#define mydWrapperGetRxPolarity   avago_serdes_get_rx_invert
#define mydWrapperSetRxPolarity   avago_serdes_set_rx_invert

/* PMD Training */
#define mydWrapperPMDAllocConfig  avago_serdes_pmd_config_construct
#define mydWrapperPMDFreeConfig   avago_serdes_pmd_config_destruct
#define mydWrapperPMDTraining     avago_serdes_pmd_train
#define mydWrapperPMDStatus       avago_serdes_pmd_status
#define mydWrapperPMDAllocDebugStruct avago_serdes_pmd_debug_construct
#define mydWrapperPMDFreeDebugStruct  avago_serdes_pmd_debug_destruct
#define mydWrapperPMDDebug        avago_serdes_pmd_debug
#define mydWrapperPMDDebugPrint   avago_serdes_pmd_debug_print

/* Error Injection */
#define mydWrapperTxInjectError   avago_serdes_tx_inject_error
#define mydWrapperRxInjectError   avago_serdes_rx_inject_error
#define mydWrapperSetRxCmpMode    avago_serdes_set_rx_cmp_mode
#define mydWrapperGetRxCmpMode    avago_serdes_get_rx_cmp_mode

/* PRBS Generator */
#define mydWrapperSetTxPRBS      avago_serdes_set_tx_data_sel
#define mydWrapperGetTxPRBS      avago_serdes_get_tx_data_sel

#define mydWrapperSetTxOutputEnable avago_serdes_set_tx_output_enable
#define mydWrapperGetTxOutputEnable avago_serdes_get_tx_output_enable

#define mydWrapperSetTxRxEnable  avago_serdes_set_tx_rx_enable
#define mydWrapperGetTxRxReady   avago_serdes_get_tx_rx_ready

#define mydWrapperSetTxUserData  avago_serdes_set_tx_user_data
#define mydWrapperGetTxUserData  avago_serdes_get_tx_user_data
#define mydWrapperSetRxCmpData   avago_serdes_set_rx_cmp_data
#define mydWrapperGetRxCmpData   avago_serdes_get_rx_cmp_data
#define mydWrapperGetErrCounter  avago_serdes_get_errors

/* SerDes Loopback */
#define mydWrapperSetRxLoopback     avago_serdes_set_rx_input_loopback
#define mydWrapperGetRxLoopbackInfo avago_serdes_get_rx_input_loopback

/* Tap request & response tracking struct */
typedef struct 
{
    MYD_UINT inc;   /* Number of inc requests */
    MYD_UINT dec;   /* Number of dec requests */
    MYD_UINT max;   /* Number of max responses */
    MYD_UINT min;   /* Number of min responses */
} MYD_TRAINING_REQUEST;

/* Statistics for a given transmitter (local or remote) */
typedef struct 
{
    MYD_UINT preset;             /* Number of preset requests */
    MYD_UINT initialize;         /* Number of initialize requests */
    MYD_TRAINING_REQUEST tap[3]; /* Stats for taps (pre,cursor,post) */
} MYD_TRAINING_STATS;

/* Link Training Debug Information */
typedef struct 
{
    MYD_BOOL reset;  /* Query statistics and then clear them (Note: also done when training is started) */

    MYD_UINT rx_metric;          /* RxEq metric */

    MYD_TRAINING_STATS local;    /* Stats for change requests done by local training code */
    MYD_TRAINING_STATS remote;   /* Stats for change requests done by remote */

    MYD_UINT last_remote_request[8];     /* Last 8 requests sent by remote partner */
    MYD_UINT last_local_request;         /* Last request made by local training logic */
} MYD_TRAINING_INFO, *PMYD_TRAINING_INFO;


/* Tx input data selections. */
typedef enum
{
    MYD_SERDES_TX_DATA_SEL_PRBS7    = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    MYD_SERDES_TX_DATA_SEL_PRBS9    = 1, /**< PRBS9 (x^9+x^7+1). */
    MYD_SERDES_TX_DATA_SEL_PRBS11   = 2, /**< PRBS11 (x^11+x^9+1). */
    MYD_SERDES_TX_DATA_SEL_PRBS15   = 3, /**< PRBS15 (x^15+x^14+1). */
    MYD_SERDES_TX_DATA_SEL_PRBS23   = 4, /**< PRBS23 (x^23+x^18+1). */
    MYD_SERDES_TX_DATA_SEL_PRBS31   = 5, /**< PRBS31 (x^31+x^28+1). */
    MYD_SERDES_TX_DATA_SEL_USER     = 7, /**< User pattern generator. */
    MYD_SERDES_TX_DATA_SEL_CORE     = 8, /**< External data. */
    MYD_SERDES_TX_DATA_SEL_LOOPBACK = 9  /**< Parallel loopback from receiver. */
} MYD_SERDES_TX_DATA_TYPE;

/* Specify the pattern to use in validating the received data. */
typedef enum
{
    MYD_SERDES_RX_CMP_DATA_PRBS7     = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    MYD_SERDES_RX_CMP_DATA_PRBS9     = 1, /**< PRBS9 (x^9+x^7+1). */
    MYD_SERDES_RX_CMP_DATA_PRBS11    = 2, /**< PRBS11 (x^11+x^9+1). */
    MYD_SERDES_RX_CMP_DATA_PRBS15    = 3, /**< PRBS15 (x^15+x^14+1). */
    MYD_SERDES_RX_CMP_DATA_PRBS23    = 4, /**< PRBS23 (x^23+x^18+1). */
    MYD_SERDES_RX_CMP_DATA_PRBS31    = 5, /**< PRBS31 (x^31+x^28+1). */
    MYD_SERDES_RX_CMP_DATA_SELF_SEED = 7, /**< Auto-seed to received 40 bit repeating pattern. */
                                          /**< NOTE: This is USER mode in firmware. */
    MYD_SERDES_RX_CMP_DATA_OFF       = 8  /**< Disable cmp data generator */
} MYD_SERDES_RX_CMP_TYPE;


/* Specify the receiver data comparison mode. */
typedef enum
{
    MYD_SERDES_RX_CMP_MODE_OFF         = 0x0000, /**< Turn Off */
    MYD_SERDES_RX_CMP_MODE_XOR         = 0x0100, /**< Test^Mission */
    MYD_SERDES_RX_CMP_MODE_TEST_PATGEN = 0x0120, /**< Test^PatGen. */
    MYD_SERDES_RX_CMP_MODE_MAIN_PATGEN = 0x0200  /**< Mission^PatGen */
} MYD_SERDES_RX_CMP_MODE_TYPE;


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYD_SERDES_H */

