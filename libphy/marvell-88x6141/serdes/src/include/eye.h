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

#ifndef AVAGO_SERDES_EYE_H_
#define AVAGO_SERDES_EYE_H_

/** Doxygen File Header
 ** @file
 ** @brief   Functions and data structures for eye measurement.
 ** @details The general function call outline is:
 **
 **   Avago_serdes_eye_config_t *config = avago_serdes_eye_config_construct(aapl);
 **   Avago_serdes_eye_data_t *data = avago_serdes_eye_data_construct(aapl);
 **
 **
 **
 **   avago_serdes_eye_get(aapl, sbus_addr, config, data);
 **
 **
 **
 **   avago_serdes_eye_data_destruct(aapl, data);
 **   avago_serdes_eye_config_destruct(aapl, config);
 **/

#define AVAGO_EYE_MIN_DWELL_BITS     (bigint)1e4
#define AVAGO_EYE_ONE_DWELL_MAX_BITS (bigint)1e8
#define AVAGO_EYE_DEF_DWELL_BITS     (bigint)5e6
#define AVAGO_EYE_DEF_MAX_DWELL_BITS (bigint)2e8
#define AAPL_MAX_DAC_RANGE 512


/** @brief Type of eye measurement to perform: */

typedef enum {
    AVAGO_EYE_SIZE = 0,   /**< Do both AVAGO_EYE_HEIGHT and AVAGO_EYE_WIDTH measurements. */
    AVAGO_EYE_CROSS = 0,  /**< Deprecated alias for AVAGO_EYE_SIZE. */
    AVAGO_EYE_SIZE_VDUAL, /**< AVAGO_EYE_SIZE + height using test channel. */
    AVAGO_EYE_HEIGHT,     /**< Measure decimal eye height & VBTC using data channel. */
    AVAGO_EYE_WIDTH,      /**< Measure decimal eye width & HBTC using test channel. */
    AVAGO_EYE_FULL,       /**< Measure entire eye, including bathtub curve plots. */
    AVAGO_EYE_HEIGHT_DVOS /**< Retrieve DFE determined height and width only. */
} Avago_serdes_eye_type_t;

EXT BOOL aapl_str_to_eye_type(const char *name, Avago_serdes_eye_type_t *out);
EXT const char *aapl_eye_type_to_str(Avago_serdes_eye_type_t val);

/*#define AVAGO_Q_CEILING  9.262217
 *#define AVAGO_Q_CEILING 11.463900
 */
#define AVAGO_Q_CEILING 13.310803
/*#define AVAGO_Q_CEILING 14.933225
 *#define AVAGO_Q_CEILING 16.397172
 *#define AVAGO_Q_CEILING 17.741543
 *#define AVAGO_Q_CEILING 18.991540
 */


/** @brief Struct for configuring eye measurements, created and initialized by
 ** avago_serdes_eye_config_construct() and released by
 ** avago_serdes_eye_config_destruct().
 ** @details Eye gathering is performed based on the values specified here.
 ** In some cases, the specified values are adjusted.
 ** The actual values are reported in the output structure.
 **/
typedef struct
{
/** Specifies the type of gather to perform. */
    Avago_serdes_eye_type_t     ec_eye_type;  /**< Default = AVAGO_EYE_FULL.
 ** Specifies whether to compare the test channel with the data channel, or
 ** with the pattern generator.
 **/
    Avago_serdes_rx_cmp_mode_t  ec_cmp_mode;  /**< Default = AVAGO_SERDES_RX_CMP_MODE_XOR. */

/** The code internally uses some combination of setting dwell
 ** (sampling) times, and gathering multiple samples at each data point (eye
 ** pixels), to derive the return values, based on these settings:
 **
 ** Dwell time is the number of RX bits (amount of real time depends on RX bit
 **   rate) for which to count errors at each data point.  The actual RX bits
 **   for each data point is returned in ed_bitsp[] (see later).
 **
 ** - ec_min_dwell_bits is the lower limit on how long to sample at each data point.
 ** - ec_max_dwell_bits is the upper limit on how long to sample at each data point.
 **
 ** If the minimum useful dwell time internally (based on time between
 **   serdes_int() calls to start data gathering and read back results) exceeds
 **   either value, the code uses the internal practical minimum.
 **
 ** Otherwise ed_bitsp[] (see later) reported for each data point never exceeds
 **   ec_max_dwell_bits.
 **
 ** - If ec_max_dwell_bits == ec_min_dwell_bits, dynamic dwelling is disabled.
 ** - If ec_max_dwell_bits > ec_min_dwell_bits, dynamic dwelling is enabled.
 **   When dynamic dwelling is enabled, errors are accumulated at each point
 **   using ec_min_dwell_bits.  Then at key points, additional dwells are
 **   accumulated until the error count exceeds ec_error_threshold (see later),
 **   or the total bit accumulation is ec_max_dwell_bits.
 **/

/** Dynamic dwelling requires much less time to gather data, especially
 **   for large dwell times, than using a high dwell time on every bit: bits
 **   with lots of errors will dwell at ec_min_dwell_bits, so time is spent
 **   efficiently on just those bits on the edge of the eye.
 **/

    bigint ec_min_dwell_bits;   /**< Minimum samples to measure. Default = 5e5. */
                                /**< Library enforces a reasonable minimum. */
    bigint ec_max_dwell_bits;   /**< Maximum samples to measure. Default = 1e8. */
    uint   ec_fast_dynamic;     /**< If 0, dwell extra on points with neighbors with >0 errors. */
                                /**< If 1, dwell extra on points with neighbors with >ec_error_threshold errors. */
                                /**< If 2 (default), only do dynamic dwell on BTC projection points. */

/** Specifies the minimum errors above which we stop processing a bit
 **   in dynamic dwell mode.
 ** Processing always stops when ec_max_dwell_bits are sampled.
 **/

    uint   ec_error_threshold;  /**< Default is 30. */

    float  ec_dc_balance;       /**< Default is 0.0, which means use device specific defaults. */
    float  ec_trans_density;    /**< Default is 0.0, which means use device specific defaults. */
    float  ec_avdd;             /**< Default is 0.0, which means use device specific defaults. */

/** Number of unit intervals (UI) to gather.
 **     One UI is always the time required for one RX bit, no matter the clock
 **     frequency.  Values outside the range are forced into range silently.
 **/

    uint ec_x_UI;   /**< Number of UI to gather.  Default = 1.  Range: [1..8]. */

/** Number of X points to gather for each UI.
 **     The requested value will be rounded down to the next lower
 **     power of 2, with a minimum of 8 points per UI.
 **/

    uint ec_x_resolution;  /**< Number of points per UI to gather. Default = 64. */

    uint ec_y_center_point;  /**< Center around which ec_y_points is gathered. */

/** The number of points to gather.  Valid range is
 **        1 to whatever the hardware supports.
 **        Points will be gathered around the specified center point.
 **        Value is ignored if ec_y_auto_scale is true.
 **
 ** The total number of points returned will be adjusted to match the hardware
 **  capability and returned in the Avago_serdes_eye_data_t structure.
 **/

    uint ec_y_points;        /**< Number of vertical points to gather. */

    uint ec_y_step_size;     /**< Vertical step size.  Default = 1. */


/** Auto scale the x resolution to gather sufficient data for valid
 **   horizontal BTC calculations.  If true, the effective x resolution
 **   is at least ec_x_resolution, if valid.
 **/

    int ec_x_auto_scale;      /**< Default = 1. */

/** Auto scale the y points and y step size to gather
 **   sufficient data for valid vertical BTC calculations.
 **    If true, the actual y points gathered will be determined automatically,
 **    while the effective y step size will be no greater than ec_y_step_size.
 **/

    int ec_y_auto_scale;      /**< Default = 1. */

/** If ec_set_phase_center is true, add this amount to the center.
 ** If ec_set_phase_center is false, add this amount to the current phase.
 ** Then gather the eye normally.
 **/

    int ec_x_shift;  /**< PI steps to adjust the eye center before gathering. */

/** If ec_gather_mean is true, gather only the eye points that bracket the 50% error point. */
    BOOL ec_gather_mean;  /**< Default = false. */

/** If ec_gather_mean is given, use this value as the 50% error point, overriding calculation. */
    bigint ec_mean_threshold;   /**< Gather mean threshold of calculated 50% value. */

/** If ec_gather_mean is given, use this value to control direction. */
    uint ec_mean_direction;     /**< Gather mean scan direction. */

/** If ec_no_sbm is true then sbus master assist will not be used even if available. */
    BOOL ec_no_sbm;  /**< Default = false. */


} Avago_serdes_eye_config_t;


/** Struct for holding the horizontal bathtub calculation results. */

typedef struct
{
    uint left_index;    /**< Inner most left index of points used in extrapolation. */
    uint right_index;   /**< Inner most right index of points used in extrapolation. */
    uint left_points;   /**< Number of points used for the left side extrapolation. Zero if not enough. */
    uint right_points;  /**< Number of points used for the right side extrapolation. Zero if not enough. */
    uint points;        /**< Total horizontal points in row. Used, with left/right index to id even/odd. */

    uint data_row;          /**< Data row index. */
    uint total_rows;        /**< Total rows in eye data. Used to id center. */
    uint data_millivolts;   /**< mV of data row, from eye center. */

    float trans_density;    /**< Device and eye specific value. */

    float dj;               /**< Estimated DJpp in mUI (milliUI). */
    float snr;              /**< Estimated signal noise ratio. */
    float left_rj;          /**< Left estimated random jitter in mUI (rms). */
    float left_slope;       /**< Left slope in Q/UI. */
    float left_intercept;   /**< Left y-intercept in Q. */
    float left_R_squared;   /**< Left R-squared confidence. */

    float left_mean;        /**< Left edge mean in mUI. */
    float left_x_intercept; /**< Left x-intercept in mUI. */

    float right_mean;       /**< Right edge mean in mUI. */
    float right_x_intercept;/**< Right x-intercept in mUI. */

    float right_rj;         /**< Right estimated random jitter in mUI (rms). */
    float right_slope;      /**< Right slope in Q/UI. */
    float right_intercept;  /**< Right y-intercept in Q. */
    float right_R_squared;  /**< Right R-squared confidence. */

    int horz_eye_1e03;      /**< Eye width at 1e-03 in mUI. */
    int horz_eye_1e04;      /**< Eye width at 1e-04 in mUI. */
    int horz_eye_1e05;      /**< Eye width at 1e-05 in mUI. */
    int horz_eye_1e06;      /**< Eye width at 1e-06 in mUI. */
    int horz_eye_1e10;      /**< Eye width at 1e-10 in mUI. */
    int horz_eye_1e12;      /**< Eye width at 1e-12 in mUI. */
    int horz_eye_1e15;      /**< Eye width at 1e-15 in mUI. */
    int horz_eye_1e17;      /**< Eye width at 1e-17 in mUI. */

    float width_0mUI;       /**< Q value for horz_ber_0mUI. */
    float width_100mUI;     /**< Q value for horz_ber_100mUI. */
    double horz_ber_0mUI;   /**< Extrapolated BER at 0 mUI eye opening. */
    double horz_ber_100mUI; /**< Extrapolated BER at 100 mUI eye opening. */

} Avago_serdes_eye_hbtc_t;

/** Struct for holding vertical bathtub calculation results. */

typedef struct
{
    uint top_index;    /**< Inner most top index of points used in extrapolation. */
    uint bottom_index; /**< Inner most bottom index of points used in extrapolation. */
    uint top_points;   /**< Number of points used for the top side extrapolation. Zero if not enough. */
    uint bottom_points;/**< Number of points used for the bottom side extrapolation. Zero if not enough. */
    uint points;        /**< Smaller of bottom_points and top_points. Deprecated. */

    int data_column;        /**< Data column index.  Is negative if mission data. Is > total_columns for odd eye. */
    int total_columns;      /**< Total columns in eye data.  Used to id center. */
    int which;              /**< Which eye indicator. */
    int eye_count;          /**< Total eyes gathered.  Used during display to id current eye. */

    float dc_balance;       /**< Device specific value. */
    float avdd;             /**< Device voltage for which BTC is calculated. */

    float snr;              /**< Estimated signal noise ratio. */
    float top_rn;           /**< Top estimated random noise in mV (rms). */
    float top_slope;        /**< Top slope in mV/Q. */
    float top_intercept;    /**< Top x-intercept in Q. */
    float top_vsig;         /**< Top signal in mV. */
    float top_vmean;        /**< Top value at Q == 0 in mV. */
    float top_R_squared;    /**< Top R-squared confidence. */

    float bottom_rn;        /**< Bottom estimated random noise in mV (rms). */
    float bottom_slope;     /**< Bottom slope in mV/Q. */
    float bottom_intercept; /**< Bottom x-intercept in Q. */
    float bottom_vsig;      /**< Bottom signal in mV. */
    float bottom_vmean;     /**< Bottom value at Q == 0 in mV. */
    float bottom_R_squared; /**< Bottom R-squared confidence. */

    double vert_ber_0mV;    /**< Extrapolated BER at 0 mV eye opening. */
    double vert_ber_25mV;   /**< Extrapolated BER at 25 mV eye opening. */
    float height_0mV;       /**< Q value for vert_ber_0mV. */
    float height_25mV;      /**< Q value for vert_ber_25mV. */

    int Vmean;              /**< Eye height at Q==0, in mV. */
    int vert_eye_1e03;      /**< Eye height at 1e-03 in mV. */
    int vert_eye_1e04;      /**< Eye height at 1e-04 in mV. */
    int vert_eye_1e05;      /**< Eye height at 1e-05 in mV. */
    int vert_eye_1e06;      /**< Eye height at 1e-06 in mV. */
    int vert_eye_1e10;      /**< Eye height at 1e-10 in mV. */
    int vert_eye_1e12;      /**< Eye height at 1e-12 in mV. */
    int vert_eye_1e15;      /**< Eye height at 1e-15 in mV. */
    int vert_eye_1e17;      /**< Eye height at 1e-17 in mV. */

} Avago_serdes_eye_vbtc_t;


/** @brief Struct for returning eye measurement results, created and initialized by
 ** avago_serdes_eye_data_construct() and released by avago_serdes_eye_data_destruct().
 **
 ** @details Note for IPC (inter-process communication) using this structure as a
 ** form of shared memory between caller and data-gathering threads:
 **
 ** - The data engine guarantees to fill in ed_x_points and ed_y_points values,
 **   and zero the malloc()'d memory under ed_errorsp and ed_bitsp, before
 **   setting the pointers to non-null.
 **
 ** - The data engine guarantees to write the ed_bitsp value before the
 **   ed_errorsp for each new data sample.
 **
 ** Thus, a caller that wishes to "sniff" the data while it's being gathered,
 ** should follow this procedure:
 **
 ** - Allocate Avago_serdes_eye_data_t using avago_serdes_eye_data_construct().
 **
 ** - After passing the struct to avago_serdes_eye_get(), wait until (ed_errorsp &&
 **   ed_bitsp) before using the data; that is, the pointers are both non-null.
 **
 ** - When exploring the eye data under the pointers (in real time as it is
 **   revised), ignore any point where the bits value is 0 (no data yet).
 **
 ** - Be aware that a non-zero bits value is no assurance that the corresponding
 **   errors value is consistent.  It could lag behind (not updated yet) by one
 **   sample/gather in the worst-case timing scenario, leading to a zero or
 **   understated BER.  (The unimplemented alternative is to have mutex locking
 **   around all accesses to the combined errors + bits data, since there's no
 **   way to write both fields atomically.)
 **
 ** - After avago_serdes_eye_get() returns successfully, all errors and bits data
 **   should be valid and consistent.
 **/

#define AAPL_MAX_EYE_COUNT 6
typedef struct
{
    Avago_serdes_eye_type_t     ed_eye_type;    /**< Type of measurement */
    Avago_serdes_rx_cmp_mode_t  ed_cmp_mode;    /**< Compare mode */

    bigint ed_min_dwell_bits;   /**< Minimum samples measured. */
    bigint ed_max_dwell_bits;   /**< Maximum samples for measurement. */
    uint   ed_fast_dynamic;     /**< Type of dwell performed. */
    uint   ed_error_threshold;  /**< error threshold use by BTC calcs. */
    float  ed_dc_balance;       /**< Default is device specific. */
    float  ed_trans_density;    /**< Default is device specific. */
    float  ed_avdd;             /**< Voltage upon which vertical projections are based. */
    double ed_dac_scale;        /**< DAC step size in mV. */

    uint  ed_x_UI;          /**< Number of UI gathered. */
     int  ed_x_shift;       /**< PI steps to shift eye center. */
    uint  ed_x_resolution;  /**< Pixels per UI; always a power of 2. Available resolution is ed_x_step times this. */
    uint  ed_x_points;      /**< Width dimension of packed output arrays. */
    uint  ed_x_step;        /**< Separation between x coordinates with data. */
     int  ed_x_min;         /**< Min phase coordinate (corresponds to data column 0). */
     int  ed_x_max;         /**< Max phase coordinate. */
     int  ed_x_sbm_center;  /**< Phase at which SBM accelerator is centered. */
     int  ed_x_center[AAPL_MAX_EYE_COUNT]; /**< SerDes FW center phase for each of the eyes. */

    uint  ed_y_points;      /**< Height dimension of packed output arrays. */
    uint  ed_y_step;        /**< Separation between y coordinates with data. */
    uint  ed_y_min;         /**< Min y (dac) coordinate with data. */
    uint  ed_y_resolution;  /**< Maximum vertical range is [0..y_resolution-1]. */
    uint  ed_y_center_point;/**< DAC value around which ed_y_points is gathered. */
                            /**< = ed_y_min + (ed_y_points/2) * ed_y_step */

    uint  ed_y_mission_points;  /**< Points in mission arrays. */
    uint  ed_y_mission_step;    /**< DAC steps between values in mission arrays. */
    uint  ed_y_mission_min;     /**< DAC value for index 0 in mission arrays. */

    uint  ed_width;         /**< Eye width (in real PI steps). */
    uint  ed_height;        /**< Eye height (in DAC steps). */
    uint  ed_width_mUI;     /**< Eye width (in mUI). */
    uint  ed_height_mV;     /**< Eye height (in mV). */


/** Two-dimensional arrays of [ed_x_points][ed_y_points]:
 **
 ** Note:
 **
 ** - Basic (unadjusted) BER = bit error rate = (errors / bits).
 **
 ** - If any requested eye pixel (data point) would fall outside the DAC
 *    range, the error value is set to -1 and the bit value remains 0.
 **   The caller must recognize and ignore these data points.
 **
 ** - C programmers may use the AVAGO_EYE_*_GET(sed,x,y) macros to access the values
 **       in the arrays.
 **   Non-C programmers should use the accessor functions:
 **
 **     avago_serdes_eye_errors_get(data,x,y),
 **     avago_serdes_eye_bits_get(data,x,y),
 **     avago_serdes_eye_grad_get(data,x,y),
 **     avago_serdes_eye_qval_get(data,x,y)
 **/

    bigint * ed_errorsp;  /**< Number of errors at each data point (eye pixel). */
    bigint * ed_bitsp;    /**< Total RX bits sampled at each data point. */
    float  * ed_gradp;    /**< Gradient field for RX bits sampled at each data point. */
    float  * ed_qvalp;    /**< Qinv value at each data point */

    /** @brief See ed_y_mission_points, ed_y_mission_step and ed_y_mission_min */
    /**        to interpret the data in these arrays. */
    int eye_count;
    bigint ed_mission_errors[AAPL_MAX_EYE_COUNT][AAPL_MAX_DAC_RANGE];  /**< Num errors, mission channels */
    bigint ed_mission_bits  [AAPL_MAX_EYE_COUNT][AAPL_MAX_DAC_RANGE];  /**< Num bits,   mission channels */

/* Hide pointer math for accessing the previous pointers (to malloc()'d memory)
 * as 2D arrays; see also accessor functions for non-C linkages:
 */

/** @cond INTERNAL */
#define _2DELEM(sed,elem,x,y) ((sed).elem[(((x) * (sed).ed_y_points) + (y))])
#define AVAGO_EYE_ERRORS_SET(sed,x,y,value) _2DELEM(sed, ed_errorsp, x, y)  = (value)
#define AVAGO_EYE_ERRORS_ADD(sed,x,y,value) _2DELEM(sed, ed_errorsp, x, y) += (value)
#define AVAGO_EYE_BITS_SET(sed,x,y,value)   _2DELEM(sed, ed_bitsp,   x, y)  = (value)
#define AVAGO_EYE_BITS_ADD(sed,x,y,value)   _2DELEM(sed, ed_bitsp,   x, y) += (value)
#define AVAGO_EYE_GRAD_SET(sed,x,y,value)   _2DELEM(sed, ed_gradp,   x, y)  = (value)
#define AVAGO_EYE_GRAD_ADD(sed,x,y,value)   _2DELEM(sed, ed_gradp,   x, y) += (value)
#define AVAGO_EYE_QVAL_SET(sed,x,y,value)   _2DELEM(sed, ed_qvalp,   x, y)  = (value)
#define AVAGO_EYE_QVAL_ADD(sed,x,y,value)   _2DELEM(sed, ed_qvalp,   x, y) += (value)
/** @endcond */

#define AVAGO_EYE_ERRORS_GET(sed,x,y)       _2DELEM(sed, ed_errorsp, x, y)  /**< Macro version of avago_serdes_eye_errors_get(). */
#define AVAGO_EYE_BITS_GET(sed,x,y)         _2DELEM(sed, ed_bitsp,   x, y)  /**< Macro version of avago_serdes_eye_bits_get(). */
#define AVAGO_EYE_GRAD_GET(sed,x,y)         _2DELEM(sed, ed_gradp,   x, y)  /**< Macro version of avago_serdes_eye_grad_get(). */
#define AVAGO_EYE_QVAL_GET(sed,x,y)         _2DELEM(sed, ed_qvalp,   x, y)  /**< Macro version of avago_serdes_eye_qval_get(). */


    char *ed_hardware_log;      /**< Holds hardware info buffer. */
    char *ed_comment;           /**< Holds any user comment string. */
                                /**< This value is written to the output file */
                                /**< and may be set at any time.  It's value */
                                /**< must be malloc'd space as it will */
                                /**< be freed by the destruct function. */


    Avago_serdes_eye_hbtc_t ed_hbtc[AAPL_MAX_EYE_COUNT]; /**< Horizontal Bathtub Curve data (PAM4 order is le, lo, me, mo, ue, uo) */
    Avago_serdes_eye_vbtc_t ed_vbtc[AAPL_MAX_EYE_COUNT]; /**< Vertical BathTub Curve data (PAM4 order is le, lo, me, mo, ue, uo) */

    double      ed_combined_btc_ber;    /**< Eye center BER value. */
    double      ed_combined_lsb_ber;    /**< Eye center lsb BER value. */
    float       ed_combined_btc_qval;   /**< Eye center Q value. */
    float       ed_combined_lsb_qval;   /**< Eye center lsb Q value. */

    float level_dn    [2][4];           /**< Deterministic noise and */
    float level_vmean [2][4];           /**< Mean for each even/odd level, in mV. */
    float level03_comp[2];              /**< Even/odd values in dB. */

    char  *ed_phase_center_log;  /**< Holds any phase centering info. */
    float  ed_phase_center;      /**< Phase location of eye center */
    uint   ed_phase_table_len;   /**< Length of phase table */
    float *ed_phase_table;       /**< mUI position adjustment for each phase step location. */

    BOOL ed_gather_mean;      /**< Read/Write only eye points that bracket the 50% error point (only non-zero points). Default = false. */
    uint ed_mean_direction;   /**< Gather mean scan direction. */

    bigint ed_mean_threshold;   /**< Optional gather mean threshold of calculated 50% value. */

    short delay[8];
    short inputs[AAPL_MAX_EYE_COUNT];

} Avago_serdes_eye_data_t;

/* Allocator/constructor and destructor/deallocator functions: */
EXT Avago_serdes_eye_config_t *avago_serdes_eye_config_construct(Aapl_t *aapl);
EXT Avago_serdes_eye_data_t   *avago_serdes_eye_data_construct(Aapl_t *aapl);
EXT void avago_serdes_eye_config_destruct(Aapl_t *aapl, Avago_serdes_eye_config_t *configp);
EXT void avago_serdes_eye_data_destruct(  Aapl_t *aapl, Avago_serdes_eye_data_t   *datap);

/* Main function for eye gathering: */
EXT int avago_serdes_eye_get(Aapl_t *aapl, uint sbus_addr,
                             const Avago_serdes_eye_config_t *configp,
                             Avago_serdes_eye_data_t *datap);

/* Functions for saving/restoring data from a file. */
EXT int avago_serdes_eye_data_read_file(Aapl_t *aapl, const char *filename,
                                        Avago_serdes_eye_data_t *datap);
EXT int avago_serdes_eye_data_write_file(const char *filename,
                                         const Avago_serdes_eye_data_t *datap);

/* Functions to analyze any row/column of the data: */
EXT void avago_serdes_eye_hbtc_extrapolate(const Avago_serdes_eye_data_t *datap,
                                           BOOL odd,
                                           uint data_row,
                                           float trans_density,
                                           Avago_serdes_eye_hbtc_t *results);
EXT void avago_serdes_eye_vbtc_extrapolate(const Avago_serdes_eye_data_t *datap,
                                           int which,
                                           int data_col,
                                           Avago_serdes_eye_vbtc_t *results);

/* Function for obtaining serdes specific default values: */
EXT float avago_serdes_eye_get_default_avdd(Aapl_t *aapl, uint addr);

/* Read phase corrections for HBTC calculations: */
EXT int avago_serdes_eye_data_read_phase(Aapl_t *aapl, const char *filename, Avago_serdes_eye_data_t *datap);

/* Functions for writing formatted information to a file: */
#if AAPL_ENABLE_FILE_IO
EXT void avago_serdes_eye_plot_write(         FILE *file, const Avago_serdes_eye_data_t *datap);
EXT void avago_serdes_eye_gradient_plot_write(FILE *file, const Avago_serdes_eye_data_t *datap);
EXT void avago_serdes_eye_contour_plot_write( FILE *file, const Avago_serdes_eye_data_t *datap);
EXT void avago_serdes_eye_hbtc_write(FILE *file, const Avago_serdes_eye_hbtc_t *hbtcp);
EXT void avago_serdes_eye_vbtc_write(FILE *file, const Avago_serdes_eye_vbtc_t *vbtcp);
EXT void avago_serdes_eye_btc_write( FILE *file, const Avago_serdes_eye_data_t *datap);
EXT void avago_serdes_eye_data_write(FILE *file, const Avago_serdes_eye_data_t *datap);
#endif

/* Function for writing formatted info into the log: */
EXT void avago_serdes_eye_plot_log_print(Aapl_t *aapl, Aapl_log_type_t level,
                                         const char *func, int line,
                                         const Avago_serdes_eye_data_t *datap);
EXT void avago_serdes_eye_hbtc_log_print(Aapl_t *aapl, Aapl_log_type_t level,
                                         const char *func, int line,
                                         const Avago_serdes_eye_hbtc_t *hbtcp);
EXT void avago_serdes_eye_vbtc_log_print(Aapl_t *aapl, Aapl_log_type_t level,
                                         const char *func, int line,
                                         const Avago_serdes_eye_vbtc_t *vbtcp);
EXT void avago_serdes_eye_btc_log_print(Aapl_t *aapl, Aapl_log_type_t level,
                                         const char *func, int line,
                                         const Avago_serdes_eye_data_t *datap);

/* Low level functions for accessing eye data: */
EXT bigint avago_serdes_eye_errors_get(Aapl_t *aapl,
                                       const Avago_serdes_eye_data_t *datap,
                                       uint x_point, uint y_point);
EXT bigint avago_serdes_eye_bits_get(Aapl_t *aapl,
                                     const Avago_serdes_eye_data_t *datap,
                                     uint x_point, uint y_point);
EXT float  avago_serdes_eye_grad_get(Aapl_t *aapl,
                                     const Avago_serdes_eye_data_t *datap,
                                     uint x_point, uint y_point);
EXT float  avago_serdes_eye_qval_get(Aapl_t *aapl,
                                     const Avago_serdes_eye_data_t *datap,
                                     int x_point, uint y_point);

/* Functions for formatting eye data for display in a text window: */
EXT char *avago_serdes_eye_plot_format(const Avago_serdes_eye_data_t *datap);
EXT char *avago_serdes_eye_gradient_plot_format(const Avago_serdes_eye_data_t *datap);
EXT char *avago_serdes_eye_contour_plot_format(const Avago_serdes_eye_data_t *datap);
EXT char *avago_serdes_eye_hbtc_format(const Avago_serdes_eye_hbtc_t *hbtcp);
EXT char *avago_serdes_eye_vbtc_format(const Avago_serdes_eye_vbtc_t *vbtcp);
EXT char *avago_serdes_eye_btc_format( const Avago_serdes_eye_data_t *datap);
EXT char *avago_hardware_info_format(Aapl_t *aapl, uint sbus_addr);


# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
EXT int allocate_eye_arrays(Aapl_t *aapl, Avago_serdes_eye_data_t *datap);
EXT int sbm_eye_gather(Aapl_t *aapl, uint addr, bigint dwell, int eye_start, uint eye_points, uint eye_step, uint eye_gather, uint options);
# endif

#endif
