/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/
/*******************************************************************************
 Copyright (c) 2014-2016 Avago Technologies. All rights reserved.

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
#ifndef MXD_SERDES_H
#define MXD_SERDES_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#include "aapl.h"

/* Data structure definition */
#define _MXD_SER_DEV Aapl_t
typedef _MXD_SER_DEV *MXD_SER_DEV_PTR;
typedef _MXD_SER_DEV MXD_SER_DEV;

#define MXD_SER_EYE_CONFIG_TYPE Avago_serdes_eye_config_t
#define MXD_SER_EYE_DATA_TYPE Avago_serdes_eye_data_t

#define MXD_SER_INIT_CONFIG_TYPE Avago_serdes_init_config_t

#define MXD_SER_INIT_DFE_TUNE_TYPE Avago_serdes_dfe_tune_t

#define MXD_SER_ADDR_TYPE Avago_addr_t
#define MXD_SER_TX_EQ_TYPE Avago_serdes_tx_eq_t

#define MXD_SER_RX_DFE_TYPE Avago_serdes_dfe_state_t

#define MXD_SER_PMD_CONFIG_TYPE Avago_serdes_pmd_config_t
#define MXD_SER_PMD_DEBUG_TYPE Avago_serdes_pmd_debug_t

#define MXD_SER_LOG_ERROR   AVAGO_ERR
#define MXD_SER_LOG_WARNING AVAGO_WARNING
#define MXD_SER_LOG_INFO    AVAGO_INFO
#define MXD_SER_LOG_OFF     AVAGO_DEBUG0

#define MXD_SER_INIT_ONLY   AVAGO_INIT_ONLY

/* Wrapper function definitions */
/* initialization */
#define mxdWrapperAllocDevStruct aapl_construct  
#define mxdWrapperFreeDevStruct  aapl_destruct
#define mxdWrapperSBusComm       aapl_is_sbus_communication_method
#define mxdWrapperRegisterSBusFn aapl_register_sbus_fn
#define mxdWrapperConnect        aapl_connect
#define mxdWrapperGetIpInfo      aapl_get_ip_info
#define mxdWrapperGetCDRLock     avago_serdes_get_frequency_lock
#define mxdWrapperResetSerdes    avago_spico_reset
#define mxdWrapperSerdesInt      avago_spico_int
#define mxdWrapperSerdesQuickInit avago_serdes_init_quick
#define mxdWrapperSerdesInit      avago_serdes_init
#define mxdWrapperAllocInitConfig avago_serdes_init_config_construct
#define mxdWrapperFreeInitConfig  avago_serdes_init_config_destruct

/* Eye */
#define mxdWrapperEyeAllocConfig  avago_serdes_eye_config_construct
#define mxdWrapperEyeFreeConfig   avago_serdes_eye_config_destruct
#define mxdWrapperGetEye          avago_serdes_eye_get
#define mxdWrapperEyeAllocDataSt  avago_serdes_eye_data_construct
#define mxdWrapperEyeFreeDataSt   avago_serdes_eye_data_destruct
#define mxdWrapperEyePlotWrite    avago_serdes_eye_plot_write
#define mxdWrapperEyeWriteToFile  avago_serdes_eye_data_write_file

/* Revision */
#define mxdWrapperBusMasterAddr   avago_make_sbus_master_addr
#define mxdWrapperGetSerdesRev    avago_firmware_get_rev
#define mxdWrapperGetSerdesBuild  aapl_get_firmware_build
#define mxdWrapperAddrToStruct    avago_addr_to_struct
#define mxdWrapperStructToAddr    avago_struct_to_addr

/* Diagnostic */
#define mxdWrapperGetTemperature  avago_sensor_get_temperature
#define mxdWrapperGetVoltage      avago_sensor_get_voltage

/*  Tuning */
#define mxdWrapperGetTxFFE        avago_serdes_get_tx_eq
#define mxdWrapperSetTxFFE        avago_serdes_set_tx_eq
#define mxdWrapperGetRxDFE        avago_serdes_get_dfe_state
#define mxdWrapperGetRxDFEStatus  avago_serdes_get_dfe_status
#define mxdWrapperSerDesTune      avago_serdes_tune

/* Inverter polarity */
#define mxdWrapperGetTxPolarity   avago_serdes_get_tx_invert
#define mxdWrapperSetTxPolarity   avago_serdes_set_tx_invert
#define mxdWrapperGetRxPolarity   avago_serdes_get_rx_invert
#define mxdWrapperSetRxPolarity   avago_serdes_set_rx_invert

/* PMD Training */
#define mxdWrapperPMDAllocConfig  avago_serdes_pmd_config_construct
#define mxdWrapperPMDFreeConfig   avago_serdes_pmd_config_destruct
#define mxdWrapperPMDTraining     avago_serdes_pmd_train
#define mxdWrapperPMDStatus       avago_serdes_pmd_status
#define mxdWrapperPMDAllocDebugStruct avago_serdes_pmd_debug_construct
#define mxdWrapperPMDFreeDebugStruct  avago_serdes_pmd_debug_destruct
#define mxdWrapperPMDDebug        avago_serdes_pmd_debug
#define mxdWrapperPMDDebugPrint   avago_serdes_pmd_debug_print

/* Error Injection */
#define mxdWrapperTxInjectError   avago_serdes_tx_inject_error
#define mxdWrapperRxInjectError   avago_serdes_rx_inject_error
#define mxdWrapperSetRxCmpMode    avago_serdes_set_rx_cmp_mode
#define mxdWrapperGetRxCmpMode    avago_serdes_get_rx_cmp_mode

/* PRBS Generator */
#define mxdWrapperSetTxPRBS      avago_serdes_set_tx_data_sel
#define mxdWrapperGetTxPRBS      avago_serdes_get_tx_data_sel

#define mxdWrapperSetTxOutputEnable avago_serdes_set_tx_output_enable
#define mxdWrapperGetTxOutputEnable avago_serdes_get_tx_output_enable

#define mxdWrapperSetTxRxEnable  avago_serdes_set_tx_rx_enable
#define mxdWrapperGetTxRxReady   avago_serdes_get_tx_rx_ready

#define mxdWrapperSetTxUserData  avago_serdes_set_tx_user_data
#define mxdWrapperGetTxUserData  avago_serdes_get_tx_user_data
#define mxdWrapperSetRxCmpData   avago_serdes_set_rx_cmp_data
#define mxdWrapperGetRxCmpData   avago_serdes_get_rx_cmp_data
#define mxdWrapperGetErrCounter  avago_serdes_get_errors

/* SerDes Loopback */
#define mxdWrapperSetRxLoopback     avago_serdes_set_rx_input_loopback
#define mxdWrapperGetRxLoopbackInfo avago_serdes_get_rx_input_loopback

/* Tap request & response tracking struct */
typedef struct 
{
    MXD_UINT inc;   /* Number of inc requests */
    MXD_UINT dec;   /* Number of dec requests */
    MXD_UINT max;   /* Number of max responses */
    MXD_UINT min;   /* Number of min responses */
} MXD_TRAINING_REQUEST;

/* Statistics for a given transmitter (local or remote) */
typedef struct 
{
    MXD_UINT preset;             /* Number of preset requests */
    MXD_UINT initialize;         /* Number of initialize requests */
    MXD_TRAINING_REQUEST tap[3]; /* Stats for taps (pre,cursor,post) */
} MXD_TRAINING_STATS;

/* Link Training Debug Information */
typedef struct 
{
    MXD_BOOL reset;  /* Query statistics and then clear them (Note: also done when training is started) */

    MXD_UINT rx_metric;          /* RxEq metric */

    MXD_TRAINING_STATS local;    /* Stats for change requests done by local training code */
    MXD_TRAINING_STATS remote;   /* Stats for change requests done by remote */

    MXD_UINT last_remote_request[8];     /* Last 8 requests sent by remote partner */
    MXD_UINT last_local_request;         /* Last request made by local training logic */
} MXD_TRAINING_INFO, *PMXD_TRAINING_INFO;


/* Tx input data selections. */
typedef enum
{
    MXD_SERDES_TX_DATA_SEL_PRBS7    = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    MXD_SERDES_TX_DATA_SEL_PRBS9    = 1, /**< PRBS9 (x^9+x^7+1). */
    MXD_SERDES_TX_DATA_SEL_PRBS11   = 2, /**< PRBS11 (x^11+x^9+1). */
    MXD_SERDES_TX_DATA_SEL_PRBS15   = 3, /**< PRBS15 (x^15+x^14+1). */
    MXD_SERDES_TX_DATA_SEL_PRBS23   = 4, /**< PRBS23 (x^23+x^18+1). */
    MXD_SERDES_TX_DATA_SEL_PRBS31   = 5, /**< PRBS31 (x^31+x^28+1). */
    MXD_SERDES_TX_DATA_SEL_USER     = 7, /**< User pattern generator. */
    MXD_SERDES_TX_DATA_SEL_CORE     = 8, /**< External data. */
    MXD_SERDES_TX_DATA_SEL_LOOPBACK = 9  /**< Parallel loopback from receiver. */
} MXD_SERDES_TX_DATA_TYPE;

/* Specify the pattern to use in validating the received data. */
typedef enum
{
    MXD_SERDES_RX_CMP_DATA_PRBS7     = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    MXD_SERDES_RX_CMP_DATA_PRBS9     = 1, /**< PRBS9 (x^9+x^7+1). */
    MXD_SERDES_RX_CMP_DATA_PRBS11    = 2, /**< PRBS11 (x^11+x^9+1). */
    MXD_SERDES_RX_CMP_DATA_PRBS15    = 3, /**< PRBS15 (x^15+x^14+1). */
    MXD_SERDES_RX_CMP_DATA_PRBS23    = 4, /**< PRBS23 (x^23+x^18+1). */
    MXD_SERDES_RX_CMP_DATA_PRBS31    = 5, /**< PRBS31 (x^31+x^28+1). */
    MXD_SERDES_RX_CMP_DATA_SELF_SEED = 7, /**< Auto-seed to received 40 bit repeating pattern. */
                                          /**< NOTE: This is USER mode in firmware. */
    MXD_SERDES_RX_CMP_DATA_OFF       = 8  /**< Disable cmp data generator */
} MXD_SERDES_RX_CMP_TYPE;


/* Specify the receiver data comparison mode. */
typedef enum
{
    MXD_SERDES_RX_CMP_MODE_OFF         = 0x0000, /**< Turn Off */
    MXD_SERDES_RX_CMP_MODE_XOR         = 0x0100, /**< Test^Mission */
    MXD_SERDES_RX_CMP_MODE_TEST_PATGEN = 0x0120, /**< Test^PatGen. */
    MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN = 0x0200  /**< Mission^PatGen */
} MXD_SERDES_RX_CMP_MODE_TYPE;


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MXD_SERDES_H */

