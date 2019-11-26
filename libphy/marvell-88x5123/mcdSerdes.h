/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************
This file is a placeholder of AVAGO defined file.
********************************************************************/

#ifndef MCD_SERDES_H
#define MCD_SERDES_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#ifndef MCD_RUN_WITH_CPSS
#include <aapl.h>
#include <aapl_library.h>
#else
#include <serdes/avago/aapl/include/aapl.h>
#include <serdes/avago/aapl/include/aapl_library.h>
#endif
/* Data structure definition */
#define _MCD_SER_DEV Aapl_t
typedef _MCD_SER_DEV *MCD_SER_DEV_PTR;
typedef _MCD_SER_DEV MCD_SER_DEV;

#define MCD_SER_EYE_CONFIG_TYPE Avago_serdes_eye_config_t
#define MCD_SER_EYE_DATA_TYPE Avago_serdes_eye_data_t

#define MCD_SER_ADDR_TYPE Avago_addr_t
#define MCD_SER_TX_EQ_TYPE Avago_serdes_tx_eq_t

#define MCD_SER_RX_CMP_DATA_TYPE Avago_serdes_rx_cmp_data_t
#define MCD_SER_TX_DATA_SEL_TYPE Avago_serdes_tx_data_sel_t

#define MCD_SER_PMD_CONFIG_TYPE Avago_serdes_pmd_config_t
#define MCD_SER_PMD_DEBUG_TYPE Avago_serdes_pmd_debug_t

#define MCD_SER_DFE_TUNE_TYPE Avago_serdes_dfe_tune_t

#define MCD_SER_LOG_ERROR   AVAGO_ERR
#define MCD_SER_LOG_WARNING AVAGO_WARNING
#define MCD_SER_LOG_INFO    AVAGO_INFO
#define MCD_SER_LOG_OFF     AVAGO_DEBUG0

/* Wrapper function definitions */
/* initialization and download*/
#define mcdWrapperAllocDevStruct            aapl_construct
#define mcdWrapperFreeDevStruct             aapl_destruct
#define mcdWrapperInitDevStruct             aapl_init
#define mcdWrapperSBusComm                  aapl_is_sbus_communication_method
#define mcdWrapperRegisterSBusFn            aapl_register_sbus_fn
#define mcdWrapperConnect                   aapl_connect
#define mcdWrapperGetIpInfo                 aapl_get_ip_info
#define mcdWrapperGetReturnCode             aapl_get_return_code
#define mcdWrapperSerdesInit                avago_serdes_init
#define mcdWrapperSerdesInitConfig          avago_serdes_init_config
#define mcdWrapperGetCDRLock                avago_serdes_get_frequency_lock
#define mcdWrapperResetSerdes               avago_spico_reset
#define mcdWrapperSerdesInt                 avago_spico_int
#define mcdWrapperSerdesUpload              avago_spico_upload
#define mcdWrapperSerdesUploadSwapImage     avago_spico_upload_swap_image
#define mcdWrapperSerdesAacsServer          avago_aacs_server
#define mcdWrapperSerdesTXenableSet         avago_serdes_set_tx_output_enable
#define mcdWrapperSerdesTXenableGet         avago_serdes_get_tx_output_enable

#define mcdWrapperSerdesTxRxEnableSet       avago_serdes_set_tx_rx_enable

/* Eye */
#define mcdWrapperEyeAllocConfig        avago_serdes_eye_config_construct
#define mcdWrapperEyeFreeConfig         avago_serdes_eye_config_destruct
#define mcdWrapperGetEye                avago_serdes_eye_get
#define mcdWrapperEyeAllocDataSt        avago_serdes_eye_data_construct
#define mcdWrapperEyeFreeDataSt         avago_serdes_eye_data_destruct
#define mcdWrapperEyePlotWrite          avago_serdes_eye_plot_write
#define mcdWrapperEyeWriteToFile        avago_serdes_eye_data_write_file
#define mcdWrapperEyeGetSimpleMetric    avago_serdes_eye_get_simple_metric
#define mcdWrapperEyePlotFormat         avago_serdes_eye_plot_format
#define mcdWrapperEyeVbtcFormat         avago_serdes_eye_vbtc_format
#define mcdWrapperEyeHbtcFormat         avago_serdes_eye_hbtc_format

/* Revision */
#define mcdWrapperBusMasterAddr   avago_make_sbus_master_addr
#define mcdWrapperGetSerdesRev    avago_firmware_get_rev
#define mcdWrapperGetSerdesBuild  aapl_get_firmware_build
#define mcdWrapperAddrToStruct    avago_addr_to_struct
#define mcdWrapperStructToAddr    avago_struct_to_addr
#define mcdWrapperBusCntrrAddr    avago_make_sbus_controller_addr
#define mcdWrapperMemRead         avago_serdes_mem_rd

/* Diagnostic */
#define mcdWrapperGetTemperature  avago_sensor_get_temperature
#define mcdWrapperGetVoltage      avago_sensor_get_voltage
#define mcdWrapperSbusTest        avago_diag_sbus_rw_test

/*  Tuning */

#define mcdWrapperTuneInit        avago_serdes_tune_init
#define mcdWrapperTune            avago_serdes_tune
#define mcdWrapperGetTxFFE        avago_serdes_get_tx_eq
#define mcdWrapperSetTxFFE        avago_serdes_set_tx_eq


/* Inverter polarity */
#define mcdWrapperGetTxPolarity   avago_serdes_get_tx_invert
#define mcdWrapperSetTxPolarity   avago_serdes_set_tx_invert
#define mcdWrapperGetRxPolarity   avago_serdes_get_rx_invert
#define mcdWrapperSetRxPolarity   avago_serdes_set_rx_invert

/* PMD Training */
#define mcdWrapperPMDAllocConfig        avago_serdes_pmd_config_construct
#define mcdWrapperPMDFreeConfig         avago_serdes_pmd_config_destruct
#define mcdWrapperPMDInit               avago_serdes_pmd_init
#define mcdWrapperPMDTraining           avago_serdes_pmd_train
#define mcdWrapperPMDStatus             avago_serdes_pmd_status
#define mcdWrapperPMDAllocDebugStruct   avago_serdes_pmd_debug_construct
#define mcdWrapperPMDFreeDebugStruct    avago_serdes_pmd_debug_destruct
#define mcdWrapperPMDDebug              avago_serdes_pmd_debug
#define mcdWrapperPMDDebugPrint         avago_serdes_pmd_debug_print

#define mcdWrapperInitSignalOk          avago_serdes_initialize_signal_ok
#define mcdWrapperGetSignalOk           avago_serdes_get_signal_ok_threshold
#define mcdWrapperGetSignalOkLive       avago_serdes_get_signal_ok_live

/* Error Injection */
#define mcdWrapperTxInjectError         avago_serdes_tx_inject_error
#define mcdWrapperRxInjectError         avago_serdes_rx_inject_error

/* PRBS Generator */
#define mcdWrapperSetTxPRBS      avago_serdes_set_tx_data_sel
#define mcdWrapperGetTxPRBS      avago_serdes_get_tx_data_sel
#define mcdWrapperSetTxUserData  avago_serdes_set_tx_user_data
#define mcdWrapperGetTxUserData  avago_serdes_get_tx_user_data
#define mcdWrapperSetRxCmpData   avago_serdes_set_rx_cmp_data
#define mcdWrapperGetRxCmpData   avago_serdes_get_rx_cmp_data
#define mcdWrapperGetErrCounter  avago_serdes_get_errors
#define mcdWrapperSetTxRxWidth   avago_serdes_set_tx_rx_width
#define mcdWrapperErrorReset     avago_serdes_error_reset

/* SerDes Loopback */
#define mcdWrapperSetRxLoopback     avago_serdes_set_rx_input_loopback
#define mcdWrapperGetRxLoopbackInfo avago_serdes_get_rx_input_loopback

#ifndef ASIC_SIMULATION
/* misc */
#define  mcdWrapperMsSleep(x)          ms_sleep(x)
#else
#define  mcdWrapperMsSleep(x)
#endif
/* Struct for holding the horizontal bathtub calculation results. */
typedef struct
{
    MCD_UINT left_index;        /* Inner most left index of points used in extrapolation. */
    MCD_UINT right_index;       /* Inner most right index of points used in extrapolation. */
    MCD_UINT points;            /* Number of points (on each side) used to do the extrapolation.  Will be zero if not enough points. */

    MCD_UINT data_row;          /* Data row index. */
    MCD_UINT total_rows;        /* Total rows in eye data. Used to id center. */
    MCD_UINT data_millivolts;   /* mV of data row, from eye center. */

    float trans_density;        /* Copied from input request. */

    float dj;                   /* Estimated DJpp in mUI (milliUI). */
    float snr;                  /* Estimated signal noise ratio. */
    float left_rj;              /* Left estimated random jitter in mUI (rms). */
    float left_slope;           /* Left slope in Q/UI. */
    float left_intercept;       /* Left y-intercept in Q. */
    float left_R_squared;       /* Left R-squared confidence. */

    float right_rj;             /* Right estimated random jitter in mUI (rms). */
    float right_slope;          /* Right slope in Q/UI. */
    float right_intercept;      /* Right y-intercept in Q. */
    float right_R_squared;      /* Right R-squared confidence. */

    MCD_INT horz_eye_1e03;      /* Eye width at 1e-03 in mUI. */
    MCD_INT horz_eye_1e04;      /* Eye width at 1e-04 in mUI. */
    MCD_INT horz_eye_1e05;      /* Eye width at 1e-05 in mUI. */
    MCD_INT horz_eye_1e06;      /* Eye width at 1e-06 in mUI. */
    MCD_INT horz_eye_1e10;      /* Eye width at 1e-10 in mUI. */
    MCD_INT horz_eye_1e12;      /* Eye width at 1e-12 in mUI. */
    MCD_INT horz_eye_1e15;      /* Eye width at 1e-15 in mUI. */
    MCD_INT horz_eye_1e17;      /* Eye width at 1e-17 in mUI. */

    float width_0mUI;           /* Q value for horz_ber_0mUI. */
    float width_100mUI;         /* Q value for horz_ber_100mUI. */
    double horz_ber_0mUI;       /* Extrapolated BER at 0 mUI eye opening. */
    double horz_ber_100mUI;     /* Extrapolated BER at 100 mUI eye opening. */

} MCD_SERDES_EYE_HBTC;


/* Struct for holding vertical bathtub calculation results. */
typedef struct
{
    MCD_UINT top_index;         /* Inner most top index of points used in extrapolation. */
    MCD_UINT bottom_index;      /* Inner most bottom index of points used in extrapolation. */
    MCD_UINT points;            /* Number of points (on each edge) used to do the extrapolation.  Will be zero if not enough points. */

    MCD_INT data_column;        /* Data column index.  Is negative if mission data. */
    MCD_INT total_columns;      /* Total columns in eye data.  Used to id center. */

    float dc_balance;           /* Default is 0.5. */

    float snr;                  /* Estimated signal noise ratio. */
    float top_rj;               /* Top estimated random jitter in mV (rms). */
    float top_slope;            /* Top slope in mV/Q. */
    float top_intercept;        /* Top x-intercept in Q. */
    float top_R_squared;        /* Top R-squared confidence. */

    float bottom_rj;            /* Bottom estimated random jitter in mV (rms). */
    float bottom_slope;         /* Bottom slope in mV/Q. */
    float bottom_intercept;     /* Bottom x-intercept in Q. */
    float bottom_R_squared;     /* Bottom R-squared confidence. */

    double vert_ber_0mV;        /* Extrapolated BER at 0 mV eye opening. */
    double vert_ber_25mV;       /* Extrapolated BER at 25 mV eye opening. */
    float height_0mV;           /* Q value for vert_ber_0mV. */
    float height_25mV;          /* Q value for vert_ber_25mV. */

    MCD_INT Vmean;              /* Eye height at Q==0, in mV. */
    MCD_INT vert_eye_1e03;      /* Eye height at 1e-03 in mV. */
    MCD_INT vert_eye_1e04;      /* Eye height at 1e-04 in mV. */
    MCD_INT vert_eye_1e05;      /* Eye height at 1e-05 in mV. */
    MCD_INT vert_eye_1e06;      /* Eye height at 1e-06 in mV. */
    MCD_INT vert_eye_1e10;      /* Eye height at 1e-10 in mV. */
    MCD_INT vert_eye_1e12;      /* Eye height at 1e-12 in mV. */
    MCD_INT vert_eye_1e15;      /* Eye height at 1e-15 in mV. */
    MCD_INT vert_eye_1e17;      /* Eye height at 1e-17 in mV. */

} MCD_SERDES_EYE_VBTC;


/* Struct for holding SerDes eye measurement calculation results. */
typedef struct
{
    MCD_UINT  ed_width;             /* Eye width (in real PI steps). */
    MCD_UINT  ed_height;            /* Eye height (in DAC steps). */

    MCD_UINT  ed_width_mUI;         /* Eye width (in mUI). */
    MCD_UINT  ed_height_mV;         /* Eye height (in mV). */

    MCD_UINT  ed_x_UI;              /* Number of UI gathered. */
    MCD_UINT  ed_x_points;          /* Width dimension of packed output arrays. */
    MCD_UINT  ed_x_step;            /* Separation between x coordinates with data. */
    MCD_UINT  ed_x_resolution;      /* Pixels per UI; always a power of 2. Available resolution is ed_x_step times this. */
    MCD_INT   ed_x_min;             /* Min PI coordinate (corresponds to data column 0). */
    MCD_UINT  ed_x_max;             /* Max PI coordinate. */

    MCD_UINT  ed_y_points;          /* Height dimension of packed output arrays. */
    MCD_UINT  ed_y_step;            /* Separation between y coordinates with data. */
    MCD_UINT  ed_y_min;             /* Min y (dac) coordinate with data. */
    MCD_UINT  ed_y_resolution;      /* Maximum vertical range is [0..y_resolution-1]. */
    MCD_UINT  ed_y_center_point;    /* DAC value around which ed_y_points is gathered. */
                                    /* = ed_y_min + (ed_y_points/2) * ed_y_step */

    MCD_UINT  ed_y_mission_points;  /* Points in mission arrays. */
    MCD_UINT  ed_y_mission_step;    /* DAC steps between values in mission arrays. */
    MCD_UINT  ed_y_mission_min;     /* DAC value for index 0 in mission arrays. */

    float ed_dc_balance;            /* Default is 0.5 */
    float ed_trans_density;         /* Default is 0.5 */
    MCD_U16  ed_error_threshold;    /* error threshold use by BTC calcs. */

    MCD_64 ed_min_dwell_bits;       /* Minimum samples measured. */
    MCD_64 ed_max_dwell_bits;       /* Maximum samples for measurement. */
    MCD_U16   ed_fast_dynamic;      /* Type of dwell performed. */

    MCD_SERDES_EYE_HBTC hbtcData;   /* Struct for horizontal bathtub results */
    MCD_SERDES_EYE_VBTC vbtcData;   /* Struct for vertical bathtub results */

} MCD_EYE_DATA, *PMCD_EYE_DATA;
/* Tap request & response tracking struct */
typedef struct
{
    MCD_UINT inc;   /* Number of inc requests */
    MCD_UINT dec;   /* Number of dec requests */
    MCD_UINT max;   /* Number of max responses */
    MCD_UINT min;   /* Number of min responses */
} MCD_TRAINING_REQUEST;

/* Statistics for a given transmitter (local or remote) */
typedef struct
{
    MCD_UINT preset;             /* Number of preset requests */
    MCD_UINT initialize;         /* Number of initialize requests */
    MCD_TRAINING_REQUEST tap[3]; /* Stats for taps (pre,cursor,post) */
} MCD_TRAINING_STATS;

/* Link Training Debug Information */
typedef struct
{
    MCD_BOOL reset;  /* Query statistics and then clear them (Note: also done when training is started) */

    MCD_UINT rx_metric;          /* RxEq metric */

    MCD_TRAINING_STATS local;    /* Stats for change requests done by local training code */
    MCD_TRAINING_STATS remote;   /* Stats for change requests done by remote */

    MCD_UINT last_remote_request[8];     /* Last 8 requests sent by remote partner */
    MCD_UINT last_local_request;         /* Last request made by local training logic */
} MCD_TRAINING_INFO, *PMCD_TRAINING_INFO;

/* Tx input data selections. */
typedef enum
{
    MCD_SERDES_TX_DATA_SEL_PRBS7    = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    MCD_SERDES_TX_DATA_SEL_PRBS9    = 1, /**< PRBS9 (x^9+x^7+1). */
    MCD_SERDES_TX_DATA_SEL_PRBS11   = 2, /**< PRBS11 (x^11+x^9+1). */
    MCD_SERDES_TX_DATA_SEL_PRBS15   = 3, /**< PRBS15 (x^15+x^14+1). */
    MCD_SERDES_TX_DATA_SEL_PRBS23   = 4, /**< PRBS23 (x^23+x^18+1). */
    MCD_SERDES_TX_DATA_SEL_PRBS31   = 5, /**< PRBS31 (x^31+x^28+1). */
    MCD_SERDES_TX_DATA_SEL_USER     = 7, /**< User pattern generator. */
    MCD_SERDES_TX_DATA_SEL_CORE     = 8, /**< External data. */
    MCD_SERDES_TX_DATA_SEL_LOOPBACK = 9  /**< Parallel loopback from receiver. */
} MCD_SERDES_TX_DATA_TYPE;

/* Specify the pattern to use in validating the received data. */
typedef enum
{
    MCD_SERDES_RX_CMP_DATA_PRBS7     = 0, /**< PRBS7 (x^7+x^6+1) generator. */
    MCD_SERDES_RX_CMP_DATA_PRBS9     = 1, /**< PRBS9 (x^9+x^7+1). */
    MCD_SERDES_RX_CMP_DATA_PRBS11    = 2, /**< PRBS11 (x^11+x^9+1). */
    MCD_SERDES_RX_CMP_DATA_PRBS15    = 3, /**< PRBS15 (x^15+x^14+1). */
    MCD_SERDES_RX_CMP_DATA_PRBS23    = 4, /**< PRBS23 (x^23+x^18+1). */
    MCD_SERDES_RX_CMP_DATA_PRBS31    = 5, /**< PRBS31 (x^31+x^28+1). */
    MCD_SERDES_RX_CMP_DATA_SELF_SEED = 7, /**< Auto-seed to received 40 bit repeating pattern. */
                                          /**< NOTE: This is USER mode in firmware. */
    MCD_SERDES_RX_CMP_DATA_OFF       = 8  /**< Disable cmp data generator */
} MCD_SERDES_RX_CMP_TYPE;

typedef enum
{
  MCD_SERDES_LP_DISABLE,
  MCD_SERDES_LP_AN_TX_RX,
  MCD_SERDES_LP_DIG_TX_RX,
  MCD_SERDES_LP_DIG_RX_TX

}MCD_SERDES_LB;

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCD_SERDES_H */


