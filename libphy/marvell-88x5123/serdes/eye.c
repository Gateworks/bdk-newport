/* AAPL CORE Revision: 2.3.0-alpha */

/* Copyright 2014-2015 Avago Technologies. All rights reserved.
 *
 * This file is part of the AAPL CORE library.
 *
 * AAPL CORE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AAPL CORE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with AAPL CORE.  If not, see http://www.gnu.org/licenses.
 */


/** @file
*  @brief  Functions for eye capture.
*  @defgroup Eye Eye Capture Functions
*  @{
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"
#include "eye.h"
#define FAST 1

#if AAPL_ENABLE_EYE_MEASUREMENT

#define EQS(str1,str2) (0==strcmp(str1,str2))
#define AAPL_LOG_PRINT3 if(esp->aapl->debug >= 3) aapl_log_printf
#define AAPL_LOG_PRINT2 if(esp->aapl->debug >= 2) aapl_log_printf


static Aapl_conv_table_t eye_type_table[] =
{
    { "EYE_SIZE",       AVAGO_EYE_SIZE },
    { "EYE_CROSS",      AVAGO_EYE_SIZE },
    { "EYE_HEIGHT",     AVAGO_EYE_HEIGHT },
    { "EYE_WIDTH",      AVAGO_EYE_WIDTH },
    { "EYE_FULL",       AVAGO_EYE_FULL },
    { "EYE_VDUAL",      AVAGO_EYE_SIZE_VDUAL },
    { "EYE_DVOS",       AVAGO_EYE_HEIGHT_DVOS },
    { 0,                0 }
};
const char *aapl_eye_type_to_str(Avago_serdes_eye_type_t value)
{
    Aapl_conv_table_t *table = eye_type_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
BOOL aapl_str_to_eye_type(const char *name, Avago_serdes_eye_type_t *out)
{
    Aapl_conv_table_t *table = eye_type_table;
    int index = name_to_index(table,name,4);
    if( index >= 0 )
        *out = (Avago_serdes_eye_type_t)table[index].value;
    return index >= 0;
}

/** @cond INTERNAL */

int allocate_eye_arrays(Aapl_t *aapl, Avago_serdes_eye_data_t *datap)
{
    size_t bigint_bytes = datap->ed_x_points * datap->ed_y_points * sizeof(bigint);
    size_t float_bytes  = datap->ed_x_points * datap->ed_y_points * sizeof(float);

    bigint * errorsp = datap->ed_errorsp;
    float  * gradp   = datap->ed_gradp;
    float  * qvalp   = datap->ed_qvalp;
    bigint * bitsp   = datap->ed_bitsp;

    errorsp = (bigint *) aapl_realloc(aapl, errorsp, bigint_bytes, "Avago_serdes_eye_data_t.ed_errorsp array");
    gradp   = (float  *) aapl_realloc(aapl, gradp,    float_bytes, "Avago_serdes_eye_data_t.ed_gradp array");
    qvalp   = (float  *) aapl_realloc(aapl, qvalp,    float_bytes, "Avago_serdes_eye_data_t.ed_qvalp array");
    bitsp   = (bigint *) aapl_realloc(aapl, bitsp,   bigint_bytes, "Avago_serdes_eye_data_t.ed_bitsp array");
    if( !bitsp || !qvalp || !gradp || !errorsp )
    {
        if( bitsp   ) aapl_free(aapl, bitsp,   "bits");
        if( qvalp   ) aapl_free(aapl, qvalp,   "qvalp");
        if( gradp   ) aapl_free(aapl, gradp,   "gradp");
        if( errorsp ) aapl_free(aapl, errorsp, "errorsp");
        bitsp = errorsp = 0;
        gradp = qvalp = 0;
        return -1;
    }

    memset((void *) errorsp, 0, bigint_bytes);
    memset((void *) gradp,   0,  float_bytes);
    memset((void *) qvalp,   0,  float_bytes);
    memset((void *) bitsp,   0, bigint_bytes);

    datap->ed_errorsp  = errorsp;
    datap->ed_gradp    = gradp;
    datap->ed_qvalp    = qvalp;
    datap->ed_bitsp    = bitsp;

    return 0;
}

/** @brief   Allocates and initializes an Avago_serdes_eye_config_t struct.
 ** @details Provides default values for capturing an eye.
 ** @return  Pointer to resulting struct.
 ** @return  On error, decrements aapl->return_code and returns NULL.
 **/
Avago_serdes_eye_config_t *avago_serdes_eye_config_construct(Aapl_t *aapl)
{
    size_t bytes = sizeof(Avago_serdes_eye_config_t);
    Avago_serdes_eye_config_t *configp = (Avago_serdes_eye_config_t *) aapl_malloc(aapl, bytes, __func__);

    if( 0 == configp)
        return NULL;


    configp->ec_eye_type         = AVAGO_EYE_FULL;
    configp->ec_cmp_mode         = AVAGO_SERDES_RX_CMP_MODE_XOR;
    configp->ec_max_dwell_bits   = AVAGO_EYE_DEF_MAX_DWELL_BITS;
    configp->ec_min_dwell_bits   = AVAGO_EYE_DEF_DWELL_BITS;
    configp->ec_fast_dynamic     = 2;
    configp->ec_error_threshold  = 30;
    configp->ec_x_UI             = 1;
    configp->ec_x_resolution     = 64;
    configp->ec_y_center_point   = 0;
    configp->ec_y_step_size      = 1;
    configp->ec_y_points         = 129;
    configp->ec_dc_balance       = 0.5;
    configp->ec_trans_density    = 0.5;
    configp->ec_x_auto_scale     = TRUE;
    configp->ec_y_auto_scale     = TRUE;


    return configp;
}

/** @brief   Deallocates an Avago_serdes_eye_config_t struct.
 ** @return  void
 **/
void avago_serdes_eye_config_destruct(
    Aapl_t *aapl,                   /**< [in] */
    Avago_serdes_eye_config_t *configpp)    /**< [in] Object to destroy. */
{
    aapl_free(aapl, configpp, __func__);
}

/** @brief   Allocates and initializes an Avago_serdes_eye_data_t struct.
 ** @return  Pointer to resulting struct.
 ** @return  On error, decrements aapl->return_code and returns NULL.
 **/
Avago_serdes_eye_data_t *avago_serdes_eye_data_construct(Aapl_t * aapl)
{
    size_t bytes = sizeof(Avago_serdes_eye_data_t);
    Avago_serdes_eye_data_t *datap = (Avago_serdes_eye_data_t *) aapl_malloc(aapl, bytes, __func__);

    if( 0 == datap )
        return NULL;

    memset(datap, 0, bytes);
    datap->ed_vbtc2.data_column = -2;
    datap->ed_vbtc3.data_column = -3;
    datap->ed_hbtc3.data_row = ~0;
    datap->ed_hbtc2.data_row = ~0;
    datap->ed_hbtc .data_row = ~0;
    return datap;
}

/** @brief   Deallocates an Avago_serdes_eye_data_t structure.
 ** @details Frees any allocated members as well as itself.
 ** @return  void
 **/
void avago_serdes_eye_data_destruct(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_eye_data_t *datap) /**< [in] Object to destroy. */
{
    if( datap->ed_errorsp     ) aapl_free(aapl,datap->ed_errorsp,"ed_errorsp");
    if( datap->ed_gradp       ) aapl_free(aapl,datap->ed_gradp  ,"ed_gradp");
    if( datap->ed_qvalp       ) aapl_free(aapl,datap->ed_qvalp  ,"ed_qvalp");
    if( datap->ed_bitsp       ) aapl_free(aapl,datap->ed_bitsp  ,"ed_bitsp");
    if( datap->ed_hardware_log) aapl_free(aapl,datap->ed_hardware_log,"ed_hw_log");
    if( datap->ed_comment )
        aapl_free(aapl,datap->ed_comment,"ed_comment");

    aapl_free(aapl,datap,__func__);
}







/** EYE state info, used like the data members of a C++ class.
 **  Stuff it's nice to have available when gathering eye data.
 **  Used internally by serdes_eye_get.
 **/

typedef struct
{
    Aapl_t                          *aapl;
    uint                             addr;
    const Avago_serdes_eye_config_t *configp;
    Avago_serdes_eye_data_t         *datap;
    int                              curr_clock_is_test;
    Avago_serdes_rx_cmp_mode_t       cmp_mode;
    BOOL                             sbm_eye_gather;
    uint                             phase_mult;
    int                              threshold;
    int                              dwell_scale;
    bigint                           real_dwell;
    bigint                           curr_dwell;
    bigint                           min_dwell;
    bigint                           max_dwell;
} Eye_state_t;

/** @endcond */


static BOOL init_eye_state(
    Eye_state_t *esp,
    Aapl_t *aapl,
    uint addr,
    const Avago_serdes_eye_config_t *configp,
    Avago_serdes_eye_data_t *datap)
{
    memset(esp, 0, sizeof(Eye_state_t));
    esp->aapl      = aapl;
    esp->addr      = addr;
    esp->configp   = configp;
    esp->datap     = datap;

    esp->sbm_eye_gather = TRUE;

    esp->curr_clock_is_test = ~0;
    esp->threshold  = configp->ec_error_threshold;
    esp->real_dwell = 0;
    esp->curr_dwell = 0;
    esp->min_dwell  = MAX(AVAGO_EYE_MIN_DWELL_BITS, configp->ec_min_dwell_bits);
    esp->min_dwell = ((esp->min_dwell + 19) / 20) * 20;
    esp->max_dwell  = MAX(esp->min_dwell, configp->ec_max_dwell_bits);
    esp->max_dwell = ((esp->max_dwell + 19) / 20) * 20;
    esp->phase_mult = 1;
    esp->dwell_scale = 1;

    esp->cmp_mode  = avago_serdes_get_rx_cmp_mode(aapl, addr);
    if( aapl->return_code < 0 )
        return FALSE;


    if( configp->ec_eye_type == AVAGO_EYE_HEIGHT )
        return TRUE;


    if( (esp->phase_mult = avago_serdes_get_phase_multiplier(aapl, addr)) <= 0 )
        return FALSE;

    return TRUE;
}

/** @brief   Validates & returns valid eye gathering values.
 ** @details May modify *resolution and *numUIp to valid values.
 **          Valid resolution is power of 2.  Valid numUIp is [1..8].
 ** @see check_range_y().
 **/
static void check_range_x(
    uint max_resolution,/**< [in] hardware resolution */
    uint *resolution,   /**< [in,out] requested/actual resolution */
    uint *numUIp,       /**< [in,out] requested/actual UI to gather */
    uint *pointsp,      /**< [out] x phase points to gather */
    uint *stepp)        /**< [out] x phase step size */
{
#   define MIN_RESOLUTION 8
    uint res = max_resolution;
    if( res < 64 ) res = 64;
    while( *resolution < res && res > MIN_RESOLUTION )
        res /= 2;
    *resolution = res;

    if( *numUIp > 8 )
        *numUIp = 8;
    else if( *numUIp < 1 )
        *numUIp = 1;

    *pointsp = *resolution * *numUIp + 1;

    *stepp = max_resolution / res;
}


/** @brief   Validates & returns valid eye gathering values.
 ** @details May modify *y_points and *y_dac_center to valid values.
 ** @see check_range_x().
 **/
static void check_range_y(
    Eye_state_t *esp,
    uint *y_step,       /**< [in]     vertical step size */
    uint *y_points,     /**< [in,out] vertical points to collect, 0..255 */
    uint *y_dac_center, /**< [in,out] center point */
    uint *y_min)        /**< [out]    min dac value for start of range, scaled */
{
    uint top_points, bot_points;
    if( *y_step == 0) *y_step = 1;

    *y_dac_center  = MIN(esp->datap->ed_y_resolution-1, *y_dac_center);
    if( *y_dac_center == 0 ) *y_dac_center = 128;

    bot_points = *y_dac_center / *y_step;
    top_points = (esp->datap->ed_y_resolution - 1 - *y_dac_center) / *y_step;
    while( bot_points + top_points + 1 > *y_points )
    {
        if( bot_points > top_points )
            bot_points --;
        else
            top_points--;
    }

    *y_points = top_points + bot_points + 1;
    *y_min    = *y_dac_center - bot_points * *y_step;
}

static const bigint *get_bits_column(const Avago_serdes_eye_data_t *datap, int column)
{
    switch( column )
    {
    case -1: return datap->ed_mission_bits;
    case -2: return datap->ed_mission2_bits;
    case -3: return datap->ed_mission3_bits;
    default: 

        return &AVAGO_EYE_BITS_GET(*datap, column, 0);
    }
}
static const bigint *get_errs_column(const Avago_serdes_eye_data_t *datap, int column)
{
    switch( column )
    {
    case -1: return datap->ed_mission_errors;
    case -2: return datap->ed_mission2_errors;
    case -3: return datap->ed_mission3_errors;
    default: return &AVAGO_EYE_ERRORS_GET(*datap, column, 0);
    }
}

/** @brief Calculates the gradient for a point which has
 **        valid self, south and west data.
 **        Skip points which are out of range or don't yet have data.
 **/
static void calc_gradient_bit(Avago_serdes_eye_data_t *datap, uint x, uint y)
{
    if( x > 0 && y > 0 && x < datap->ed_x_points && y < datap->ed_y_points )
    {
        bigint bits     = AVAGO_EYE_BITS_GET(*datap, x,   y  );
        bigint bits_s   = AVAGO_EYE_BITS_GET(*datap, x,   y-1);
        bigint bits_w   = AVAGO_EYE_BITS_GET(*datap, x-1, y  );
        if( bits > 0 && bits_s > 0 && bits_w > 0 )
        {
            bigint errors   = AVAGO_EYE_ERRORS_GET(*datap, x,   y  );
            bigint errors_s = AVAGO_EYE_ERRORS_GET(*datap, x,   y-1);
            bigint errors_w = AVAGO_EYE_ERRORS_GET(*datap, x-1, y  );
            float grad;
            bigint en, ew;
            if( bits == bits_s && bits == bits_w )
            {
                en = errors - errors_s;
                ew = errors - errors_w;
            }
            else
            {
                en = (errors * bits_s - errors_s * bits) / bits_s;
                ew = (errors * bits_w - errors_w * bits) / bits_w;
            }
            grad = 2 * sqrt(en*en + ew*ew) / bits;
            AVAGO_EYE_GRAD_SET(*datap, x, y, grad);
        }
    }
    return;
}

/** @brief Update the gradient array from the current eye data. */
static void serdes_eye_calc_gradient(
    Avago_serdes_eye_data_t *datap) /**< [in,out] Eye data to act upon. */
{
    size_t bytes;
    uint x, y;

    bytes = datap->ed_x_points * datap->ed_y_points * sizeof(datap->ed_gradp[0]);
    memset((void *) datap->ed_gradp, 0, bytes);

    for( x = 1; x < datap->ed_x_points; x++ )
        for( y = 1; y < datap->ed_y_points; y++ )
            calc_gradient_bit(datap, x, y);
}

static void calc_qval_bit(Avago_serdes_eye_data_t *datap, uint x, uint y)
{
    if( x < datap->ed_x_points && y < datap->ed_y_points )
    {
        float qinv = 0;
        bigint bits = AVAGO_EYE_BITS_GET(*datap, x, y);
        if( bits > 0 )
        {
            bigint errs = AVAGO_EYE_ERRORS_GET(*datap, x, y);
            double BER = avago_calc_BER(errs, bits, 0.5);
            qinv = avago_qfuncinv(BER);
        }
        AVAGO_EYE_QVAL_SET(*datap, x, y, qinv);
    }
}

static void serdes_eye_calc_qval(
    Avago_serdes_eye_data_t *datap) /**< [in,out] Eye data to act upon. */
{
    uint x, y;
    for( x = 0; x < datap->ed_x_points; x++ )
        for( y = 0; y < datap->ed_y_points; y++ )
            calc_qval_bit(datap, x, y);
}

/** @brief   Sets the error timer and updates the internal state accordingly.
 ** @details If the internal state already matches the request, does nothing.
 **/
static int eye_set_error_timer(Eye_state_t *esp, bigint new_dwell)
{
    int ret;
    bigint real_dwell = new_dwell * esp->dwell_scale;


    if( real_dwell == esp->real_dwell )
        return 0;

    ret = avago_serdes_set_error_timer(esp->aapl, esp->addr, real_dwell);
    if( ret >= 0 )
    {
        esp->real_dwell = real_dwell;
        esp->curr_dwell = new_dwell;
    }
    return ret;
}

/** @brief   Updates the bits to dwell for a given eye point.
 ** @details Want to dwell enough to push errors above threshold without
 **          wasting time getting it much above it.
 **          Also caps total dwell at max_dwell bits.
 **/
static BOOL update_dwell(Eye_state_t *esp, uint x, uint y)
{
    bigint bits   = get_bits_column(esp->datap, x)[y];
    bigint errors = get_errs_column(esp->datap, x)[y];

    bigint new_dwell = esp->curr_dwell;
    if( new_dwell > bits )
        new_dwell = bits;
    if( errors <= esp->threshold / 10 )
        new_dwell *= 10;
    else if( errors <= esp->threshold / 4 )
        new_dwell *= 4;
    else if( errors <= esp->threshold / 3 )
        new_dwell *= 2;
    else if( errors <= esp->threshold * 2 / 3 )
        new_dwell +=  (new_dwell / 40000) * 20000;

    new_dwell = MAX(new_dwell, esp->min_dwell);
    new_dwell = MIN(new_dwell, esp->max_dwell - bits);
    new_dwell = ((new_dwell+19) / 20) * 20;


    new_dwell = MIN(new_dwell,    10000000);

    if( eye_set_error_timer(esp, new_dwell) < 0 )
        return FALSE;
    aapl_log_printf(esp->aapl, AVAGO_DEBUG3, __func__, __LINE__, "update_dwell: x,y = %2u,%3u, errors,bits = %s,%s, new dwell = %s\n",
        x,y,
        aapl_bigint_to_str(errors),
        aapl_bigint_to_str(bits),
        aapl_bigint_to_str(esp->curr_dwell));
    return TRUE;
}



#define SBM_INT             0x2F
#define EYE_READ_VERSION    0x0000
#define EYE_READ_ADDR       0x0001
#define EYE_READ_START      0x0002
#define EYE_READ_POINTS     0x0003
#define EYE_READ_STEP       0x0004
#define EYE_READ_OFFSET     0x0005
#define EYE_READ_RESOLUTION 0x0006
#define EYE_READ_OPTIONS    0x0007
#define EYE_READ_LOCATION   0x000a
#define EYE_SET_ADDR        0x1000
#define EYE_SET_START       0x2000
#define EYE_SET_POINTS      0x3000
#define EYE_SET_STEP        0x4000
#define EYE_SET_OFFSET      0x5000
#define EYE_SET_RESOLUTION  0x6000
#define EYE_SET_OPTIONS     0x7000
#define EYE_GATHER_ROW      0xa000
#define EYE_GATHER_COLUMN   0xb000
#define EYE_GATHER_MISSION  0xc000


/** @brief   Performs once-per-eye device configuration.
 ** @details Configures values that need be set only once per eye gather.
 ** @return  Returns TRUE on success.
 **/
static BOOL sbm_eye_setup_serdes(Eye_state_t *esp)
{
    Aapl_t *aapl = esp->aapl;
    uint addr = esp->addr;
    uint sbm_addr = avago_make_sbus_master_addr(addr);
    int return_code = aapl->return_code;
    int options = 0;
    uint fw_build = aapl_get_firmware_build(aapl, addr);

    AAPL_LOG_PRINT2(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SerDes FW: 0x%04X_%04X  SBM FW: 0x%04X_%04X\n",
        aapl_get_firmware_rev(aapl,addr),
        fw_build,
        aapl_get_firmware_rev(aapl,sbm_addr),
        aapl_get_firmware_build(aapl,sbm_addr));
    if( aapl_get_ip_type(aapl, addr) == AVAGO_SERDES )
    {
        options = (esp->cmp_mode == AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN) ? 1 : 0;
    }

    if( fw_build == 0x2085 || fw_build == 0x0085 )
        options |= 0x0010;

    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_ADDR       | (0x0ff & addr));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_OFFSET     |  0);
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_RESOLUTION | (0x7ff & avago_serdes_get_phase_multiplier(aapl, addr)));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_OPTIONS    | (0x7ff & options));
    return return_code == aapl->return_code;
}

/** @brief   Configures SBM for a column eye gather.
 ** @details The column parameter says the type of column.
 **          - column < 0 means setup for mission data column
 **          - column >= 0 means setup for test channel column
 **/
static BOOL sbm_eye_setup_column(Eye_state_t *esp, int column)
{
    Aapl_t *aapl = esp->aapl;
    int return_code = aapl->return_code;
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);

    uint y_points, y_step;
    int  y_start;

    if( column < 0 )
    {
        y_points  = esp->datap->ed_y_mission_points;
        y_step  = esp->datap->ed_y_mission_step;
    }
    else
    {
        y_points  = esp->datap->ed_y_points;
        y_step  = esp->datap->ed_y_step;
    }
    y_start = (0 - y_points / 2) * y_step;
    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Points = %u; Column = %d\n", y_points, column);
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_START  | (y_start  & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | (y_points & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP   | (y_step   & 0x7ff));
    return return_code == aapl->return_code;
}

/** @brief Configures SBM for a row eye gather. */
static BOOL sbm_eye_setup_row(Eye_state_t *esp)
{
    Aapl_t *aapl = esp->aapl;
    int return_code = aapl->return_code;
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);

    uint x_points  = esp->datap->ed_x_points;
    uint x_step  = esp->datap->ed_x_step;
    int  x_start = (0 - x_points / 2) * x_step;

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "\n", "\n");

    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_START  | (x_start  & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | (x_points & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP   | (x_step   & 0x7ff));
    return return_code == aapl->return_code;
}

/** @brief Configures SBM for a row eye gather. */
static BOOL sbm_eye_setup_point(Eye_state_t *esp)
{
    Aapl_t *aapl = esp->aapl;
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);
    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "\n", "\n");
    return avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | 1);
}

/** @brief Converts FW floating point error count into integer. */
static uint error_float_to_int(uint e)
{
    if( e & 0xe000 )
        e = (0x1000 | (e & 0x0fff)) << (((e >> 12) & 0x0f) - 1);
    else
        e &= 0x1fff;
    return e;
}

static BOOL sbm_eye_gather_data(
    Eye_state_t *esp,   /**< [in] Eye state info */
    uint int_data,      /**< [in] Tell SBM type of eye gather */
    bigint *bits,       /**< [in] First location for saving bit counts */
    bigint *errors,     /**< [in] First location for saving error results */
    uint   step,        /**< [in] Offset for saving next result */
    uint   points)      /**< [in] Number of points to read */
{
    Aapl_t *aapl = esp->aapl;
    int return_code = aapl->return_code;
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);
    uint sbc_addr = avago_make_sbus_controller_addr(esp->addr);
    uint index, stop_index = points * step, read_index = 1;

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Points = %u\n", points);

    avago_sbus_wr(aapl, sbc_addr, 0x11, read_index);
    avago_sbus_wr(aapl, sbc_addr, 0x12, 0);
    avago_spico_int(aapl, sbm_addr, SBM_INT, int_data);

    for( index = 0; index < stop_index;     )
    {
        unsigned char reg_addrs[] = { 0x12, 0x13, 0x16 };
        uint avail = 0, err_reg[3];
        uint loop_count = 0;

        avago_sbus_wr(aapl, sbc_addr, 0x11, read_index);
        while( loop_count++ < 500 )
        {
            avago_sbus_rd_array(aapl, sbc_addr, 3, reg_addrs, err_reg);
            avail = err_reg[0];
            if( avail >= read_index )
                break;
            if( loop_count >= 400 )
                ms_sleep(1);
        }

        bits[index] += esp->curr_dwell;
        errors[index] += error_float_to_int(err_reg[1] >> 16);
        index += step;
        if( index < stop_index )
        {
            bits[index] += esp->curr_dwell;
            errors[index] += error_float_to_int(err_reg[1]);
            index += step;
            if( index < stop_index )
            {
                bits[index] += esp->curr_dwell;
                errors[index] += error_float_to_int(err_reg[2] >> 16);
                index += step;
                if( index < stop_index )
                {
                    bits[index] += esp->curr_dwell;
                    errors[index] += error_float_to_int(err_reg[2]);
                    index += step;
                }
            }
        }

        while( avail*4*step > index && index < stop_index )
        {
            bits[index] += esp->curr_dwell;
            errors[index] += errors[index-4*step];
            index += step;
        }

        read_index = avail + 1;
    }
    return return_code == aapl->return_code;
}

/** @brief  Setup and gather a single row */
static BOOL sbm_eye_gather_row(
    Eye_state_t *esp,
    int y_row)
{
    int dac = (y_row - esp->datap->ed_y_points / 2) * esp->datap->ed_y_step;
    int int_data   = EYE_GATHER_ROW | (dac & 0x7ff);
    bigint *bits   = &AVAGO_EYE_BITS_GET(  *esp->datap,0,y_row);
    bigint *errors = &AVAGO_EYE_ERRORS_GET(*esp->datap,0,y_row);
    uint    step   = esp->datap->ed_y_points;
    return sbm_eye_gather_data(esp, int_data, bits, errors, step, esp->datap->ed_x_points);
}

static BOOL sbm_eye_gather_column(
    Eye_state_t *esp,
    int x_point,
    uint begin_y,
    uint end_y)
{
    uint int_data;
    bigint *bits   = (bigint *)get_bits_column(esp->datap, x_point) + begin_y;
    bigint *errors = (bigint *)get_errs_column(esp->datap, x_point) + begin_y;

    if( x_point < 0 )
    {
        int_data = EYE_GATHER_MISSION;
    }
    else
    {
        int phase = (x_point - (esp->datap->ed_x_points / 2)) * esp->datap->ed_x_step;
        int_data = EYE_GATHER_COLUMN | (phase & 0x7ff);
    }
    return sbm_eye_gather_data(esp, int_data, bits, errors, 1, end_y - begin_y);
}

static BOOL sbm_eye_gather_column_nrz(Eye_state_t *esp, int column)
{
    uint points = (column < 0) ? esp->datap->ed_y_mission_points : esp->datap->ed_y_points;
    return sbm_eye_setup_column(esp, column)
        && sbm_eye_gather_column(esp, column, 0, points);
}

static BOOL sbm_eye_gather_mission_nrz(Eye_state_t *esp)
{
    return sbm_eye_gather_column_nrz(esp, -1);
}

static BOOL sbm_eye_gather_nrz(Eye_state_t *esp)
{
    BOOL status = sbm_eye_setup_column(esp, 0);
    uint i;

    for( i = 0; i < esp->datap->ed_x_points; i++ )
        status &= sbm_eye_gather_column(esp, i, 0, esp->datap->ed_y_points);

    return status;
}

static BOOL sbm_eye_get_one_pixel(Eye_state_t *esp, int x_point, uint y_point)
{
    Aapl_t *aapl = esp->aapl;
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);
    int dac = (y_point - esp->datap->ed_y_points / 2) * esp->datap->ed_y_step;

    return avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_START | (dac & 0x7ff) ) &&
            sbm_eye_gather_column(esp, x_point, y_point, y_point + 1);
}


static BOOL eye_dynamic_get(Eye_state_t *esp, int x, uint y)
{
    BOOL return_value = TRUE;
    const bigint *bits = &get_bits_column(esp->datap, x)[y];
    const bigint *errs = &get_errs_column(esp->datap, x)[y];
    int threshold = esp->threshold;

    if( *bits <= 0 )
        return TRUE;

    if( esp->configp->ec_fast_dynamic == 2 ) esp->threshold *= 30;
    while( *errs <= esp->threshold &&
           *errs >= 0 &&
           *bits < esp->max_dwell )
    {
        if( ! update_dwell(esp, x, y) )
            { return_value = FALSE; break; }


        if( !sbm_eye_get_one_pixel(esp, x, y) )
            { return_value = FALSE; break; }
    }
    esp->threshold = threshold;

    aapl_log_printf(esp->aapl, AVAGO_DEBUG3, __func__, __LINE__, "Eye vals: x,y = %2d,%3u; errors,bits = %s,%s\n",
        x, y,
        aapl_bigint_to_str(*errs),
        aapl_bigint_to_str(*bits));

    return return_value;
}



static BOOL skip_eye_dynamic_dwell(Eye_state_t *esp, const char *func, int line)
{
    if( esp->max_dwell == esp->min_dwell )
    {
        aapl_log_printf(esp->aapl, AVAGO_DEBUG2, func, line,
            "skipping dynamic dwell as min_dwell == max_dwell == %s\n",
            aapl_bigint_to_str(esp->max_dwell));
        return TRUE;
    }

    return FALSE;
}


static BOOL eye_dynamic_dwell_width(Eye_state_t *esp, uint row)
{
    uint x;
    uint x_points = esp->datap->ed_x_points;
    uint x_mid = x_points / 2;
    uint x_left = MAX(0, (int)(x_mid - esp->datap->ed_x_resolution));
    uint x_right = MIN(x_points - 1, x_mid + esp->datap->ed_x_resolution);
    int neighbor_threshold = esp->configp->ec_fast_dynamic ? esp->threshold : 0;

    if( skip_eye_dynamic_dwell(esp,__func__,__LINE__) )
        return TRUE;

    for( x = x_left; x <= x_right; x++ )
        if( x==0 || AVAGO_EYE_ERRORS_GET(*esp->datap, x-1, row) > neighbor_threshold )
            if( ! eye_dynamic_get(esp, x, row) )
                return FALSE;

    for( x = x_right; x > x_left; x-- )
        if( x == x_right || AVAGO_EYE_ERRORS_GET(*esp->datap, x+1, row) > neighbor_threshold )
            if( ! eye_dynamic_get(esp, x, row) )
                return FALSE;

    return TRUE;
}

static BOOL eye_dynamic_dwell_height(Eye_state_t *esp, int column)
{
    uint y;
    uint y_points = column < 0 ? esp->datap->ed_y_mission_points : esp->datap->ed_y_points;
    const bigint *errs = get_errs_column(esp->datap, column);
    int neighbor_threshold = esp->configp->ec_fast_dynamic ? esp->threshold : 0;

    if( skip_eye_dynamic_dwell(esp,__func__,__LINE__) )
        return TRUE;

    for( y = 0; y < y_points; y++ )
    {
        if( y == 0 || errs[y-1] > neighbor_threshold )
            if( ! eye_dynamic_get(esp, column, y) )
                return FALSE;
    }

    for( y = y_points - 1; y > 0; y-- )
        if( y == (y_points - 1) || errs[y+1] > neighbor_threshold )
            if( ! eye_dynamic_get(esp, column, y) )
                return FALSE;

    return TRUE;
}

static BOOL eye_dynamic_dwell_all(Eye_state_t *esp)
{
    int neighbor_threshold = esp->configp->ec_fast_dynamic ? esp->threshold : 0;
    uint x, y;

    if( skip_eye_dynamic_dwell(esp,__func__,__LINE__) )
        return TRUE;

    aapl_log_printf(esp->aapl, AVAGO_DEBUG2, __func__, __LINE__, "dynamic_mode = %d\n", esp->configp->ec_fast_dynamic);
    if( esp->configp->ec_fast_dynamic == 2 )
    {
        uint x_mid = esp->datap->ed_x_points / 2;
        uint y_mid = esp->datap->ed_y_points / 2;
        if(    eye_dynamic_dwell_width(esp, y_mid)
            && eye_dynamic_dwell_height(esp, x_mid)
            && eye_dynamic_dwell_height(esp, -1) )
            return TRUE;
    }

    for( x = 0; x < esp->datap->ed_x_points; x++ )
    {
        for( y = 0; y < esp->datap->ed_y_points; y++ )
        {
            if( (x != 0 && AVAGO_EYE_ERRORS_GET(*esp->datap, x-1, y) > neighbor_threshold) ||
                (y != 0 && AVAGO_EYE_ERRORS_GET(*esp->datap, x, y-1) > neighbor_threshold) )
            {
                if( ! eye_dynamic_get(esp, x, y) )
                    return FALSE;
            }
        }
    }
    for( x = esp->datap->ed_x_points; x > 0;    )
    {
        BOOL right_edge = (x == esp->datap->ed_x_points);
        x--;
        for( y = esp->datap->ed_y_points; y > 0;     )
        {
            BOOL bottom_edge = (y == esp->datap->ed_y_points);
            y--;
            if( (!right_edge  && AVAGO_EYE_ERRORS_GET(*esp->datap, x+1, y) > neighbor_threshold) ||
                (!bottom_edge && AVAGO_EYE_ERRORS_GET(*esp->datap, x, y+1) > neighbor_threshold) )
            {
                if( ! eye_dynamic_get(esp, x, y) )
                    return FALSE;
            }
        }
    }
    if( !eye_dynamic_dwell_height(esp, -1) )
        return FALSE;

    return TRUE;
}




/** @brief Converts x coordinate into milliUI.
 ** @return Returns milli-UI offset of x relative to the eye center.
 **/
static double mui_from_index(const Avago_serdes_eye_data_t *datap, int x)
{
    int x_resolution = datap->ed_x_resolution;
    int x_mid = datap->ed_x_points / 2;
    int val = (x - x_mid) * 1000;
#if 0
    int half_point = x_resolution / 2;
    val += (val > 0 ? half_point : -half_point);
    return val / x_resolution;
#else
    return (double) val / x_resolution;
#endif
}

/** @brief Converts y coordinate into milliVolts.
 ** @return Returns milliVolt offset of y relative to the eye center.
 **/
static double mv_from_index(
    uint dac_range,     /**< total dac range */
    uint y_points,      /**< array size, used only for finding the midpoint. */
    uint step,          /**< maps array spacing to dac range. */
    int y)              /**< coordinate to convert to mV. */
{
    int y_mid = y_points / 2;
    int val = (y - y_mid) * step * 1000;
#if 0
    int half = val > 0 ? dac_range/2 : -dac_range/2;
    return (val + half) / dac_range;
#else
    return (double) val / dac_range;
#endif
}

static double get_BER(const Avago_serdes_eye_data_t *datap, int x, int y, float density)
{
    return avago_calc_BER(AVAGO_EYE_ERRORS_GET(*datap,x,y),AVAGO_EYE_BITS_GET(*datap,x,y), density);
}

/** @brief  Calculates the RJ (random jitter) from the slope.
 ** @return The calculated RJ value.
 **/
static double calc_rj(const Avago_least_sqr_results *data)
{
    double ret;
    if( data->slope == 0.0 )
        return 1000.0;
    ret = 1.0 / data->slope;
    return ret > 0.0 ? ret : -ret;
}


/** @brief   Calculates the DJ (deterministic jitter).
 ** @details Assumes the dataset is already adjusted for transition density.
 ** @return  The calculated DJ value in the same units as passed in.
 **/
static double calc_dj(const Avago_least_sqr_results *left, const Avago_least_sqr_results *right)
{
    double x_intercept_left = 0;
    double x_intercept_right = 0;

    if( left->slope != 0.0 )
        x_intercept_left = -left->y_intercept / left->slope;
    if( right->slope != 0.0 )
        x_intercept_right = -right->y_intercept / right->slope;

    return fabs(1000 - (x_intercept_right - x_intercept_left));
}

/** @cond INTERNAL */

const double q03 = 3.0902;
const double q04 = 3.7190;
const double q05 = 4.2649;
const double q06 = 4.74;
const double q10 = 6.36;
const double q12 = 7.03;
const double q15 = 7.94;
const double q17 = 8.49;

#define FIT (3)
/** @endcond */

/** @brief Find best R-squared fit.
 ** @return Shift count, 0 if no shift.
 **/
static uint find_best_fit(Avago_least_sqr_point *points, uint pointCount)
{
    Avago_least_sqr_results lsr_prev, lsr;
    uint i;
    int best_r_squared_loc = 0;
    memset(&lsr_prev,0,sizeof(lsr_prev));
    for( i = 0; i < 8; i++ )
    {
        if( pointCount < FIT+i ) break;
        avago_least_sqr(points+i, FIT, &lsr);
        if( i == 0 ) lsr_prev = lsr;
        if( lsr.Rsqr > lsr_prev.Rsqr )
        {
            best_r_squared_loc = i;
            if( lsr.Rsqr > 0.995 ) break;
            lsr_prev = lsr;
        }
    }
    if( best_r_squared_loc != 0 )
    {
        memmove(points,points+best_r_squared_loc,FIT*sizeof(points[0]));
    }
    return best_r_squared_loc;
}

/** @brief   Calculates best-fit extrapolation for the HBTC (horizontal bathtub curve).
 ** @details Uses the selected row of eye data, as well as datap->ed_trans_density,
 **          to perform a standard set of error rate extrapolations.
 ** @return  Saves relevant results into the Avago_serdes_eye_hbtc_t structure.
 **/
void avago_serdes_eye_hbtc_extrapolate(
    const Avago_serdes_eye_data_t *datap,   /**< [in] Populated eye data. */
    uint data_row,                          /**< [in] Row index in eye data to analyze. */
    Avago_serdes_eye_hbtc_t *results)       /**< [out] Where results are written. */
{
    int threshold = datap->ed_error_threshold;
    int x_mid = datap->ed_x_points / 2;

    memset(results,0,sizeof(*results));

    if( data_row >= datap->ed_y_points )
        return;

    results->data_row = data_row;
    results->total_rows = datap->ed_y_points;
    results->trans_density = datap->ed_trans_density;
    results->data_millivolts = mv_from_index(datap->ed_y_resolution, datap->ed_y_points, datap->ed_y_step, data_row) + 0.5;



    {
        uint x;
        uint min_x = x_mid;
        float max_qval = AVAGO_EYE_QVAL_GET(*datap,min_x,data_row);
        for( x = 0; x < datap->ed_x_points; x++ )
        {
            float qval = AVAGO_EYE_QVAL_GET(*datap,x,data_row);

            if( AVAGO_EYE_BITS_GET(*datap,x,data_row) <= 0 )
                continue;

            if( qval > max_qval )
            {
                max_qval = qval;
                x_mid = x;
            }
        }
    }

    {
    #define LSPTS (5*FIT)
    Avago_least_sqr_point leftPoints[LSPTS], rightPoints[LSPTS];

    int x, leftPointCount = 0, rightPointCount = 0;
    for( x = x_mid - 1; x >= 0; x-- )
    {
        if( AVAGO_EYE_BITS_GET(*datap,x,data_row) < 0 )
            continue;

        if( AVAGO_EYE_ERRORS_GET(*datap,x,data_row) <= threshold && leftPointCount < FIT )
            leftPointCount = 0;
        else
        {
            leftPoints[leftPointCount].x = mui_from_index(datap,x);
            leftPoints[leftPointCount].y = avago_qfuncinv(get_BER(datap,x,data_row,results->trans_density));
            if( leftPointCount++ == 0 ) results->left_index = x;
            if( leftPointCount >= LSPTS )
                break;
        }
    }

    for( x = x_mid + 1; x < (int)datap->ed_x_points; x++ )
    {
        if( AVAGO_EYE_BITS_GET(*datap,x,data_row) < 0 )
            continue;

        if( AVAGO_EYE_ERRORS_GET(*datap,x,data_row) <= threshold && rightPointCount < FIT )
            rightPointCount = 0;
        else
        {
            rightPoints[rightPointCount].x = mui_from_index(datap,x);
            rightPoints[rightPointCount].y = avago_qfuncinv(get_BER(datap,x,data_row,results->trans_density));
            if( rightPointCount++ == 0 ) results->right_index = x;
            if( rightPointCount >= LSPTS )
                break;
        }
    }

#if 0
    printf("Row = %u\n",data_row);
    printf("Left edge points: ");
    for( int i = 0; i < leftPointCount && i < FIT+1; i++ )
        printf(" (%.3f,%f)",leftPoints[i].x,leftPoints[i].y);
    printf("\n");
    printf("Right edge points: ");
    for( int i = 0; i < rightPointCount && i < FIT+1; i++ )
        printf(" (%.3f,%f)",rightPoints[i].x,rightPoints[i].y);
    printf("\n");
#endif

    if( leftPointCount < FIT || rightPointCount < FIT )
        return;

    results->points = FIT;

    {
    Avago_least_sqr_results left, right;

    results->left_index -= find_best_fit(leftPoints,leftPointCount);
    results->right_index += find_best_fit(rightPoints,rightPointCount);

    avago_least_sqr(leftPoints, FIT, &left);
    avago_least_sqr(rightPoints, FIT, &right);

    results->left_slope      = left.slope * 1000;
    results->left_intercept  = left.y_intercept;
    results->left_R_squared  = left.Rsqr;
    results->left_rj         = calc_rj(&left);

    results->right_slope     = right.slope * 1000;
    results->right_intercept = right.y_intercept;
    results->right_R_squared = right.Rsqr;
    results->right_rj        = calc_rj(&right);
    results->dj              = calc_dj(&left,&right);


    {
    double y_int_diff = right.y_intercept - left.y_intercept;
    double slope_diff = left.slope - right.slope;
    double x_0mUI = y_int_diff / slope_diff * left.slope + left.y_intercept;
    double x_100mUI = (y_int_diff + (100 * right.slope)) / slope_diff * left.slope + left.y_intercept;
    if( x_0mUI > AVAGO_Q_CEILING )
        x_0mUI = AVAGO_Q_CEILING;
    if( x_100mUI > AVAGO_Q_CEILING )
        x_100mUI = AVAGO_Q_CEILING;
    results->horz_ber_0mUI = avago_qfunc(x_0mUI);
    results->horz_ber_100mUI = avago_qfunc(x_100mUI);
    results->width_0mUI = x_0mUI;
    results->width_100mUI = x_100mUI;
    }


    results->horz_eye_1e03 = (int)((left.y_intercept - q03) / left.slope - (right.y_intercept - q03) / right.slope);
    results->horz_eye_1e04 = (int)((left.y_intercept - q04) / left.slope - (right.y_intercept - q04) / right.slope);
    results->horz_eye_1e05 = (int)((left.y_intercept - q05) / left.slope - (right.y_intercept - q05) / right.slope);
    results->horz_eye_1e06 = (int)((left.y_intercept - q06) / left.slope - (right.y_intercept - q06) / right.slope);
    results->horz_eye_1e10 = (int)((left.y_intercept - q10) / left.slope - (right.y_intercept - q10) / right.slope);
    results->horz_eye_1e12 = (int)((left.y_intercept - q12) / left.slope - (right.y_intercept - q12) / right.slope);
    results->horz_eye_1e15 = (int)((left.y_intercept - q15) / left.slope - (right.y_intercept - q15) / right.slope);
    results->horz_eye_1e17 = (int)((left.y_intercept - q17) / left.slope - (right.y_intercept - q17) / right.slope);
    } }
}

/** @brief Write the HBTC data to a string.
 ** @return A character string containing the formatted HBTC results.
 **         The caller should AAPL_FREE the returned string.
 **/

char *avago_serdes_eye_hbtc_format(const Avago_serdes_eye_hbtc_t *hbtcp) /**< Populated Avago_serdes_eye_hbtc_t pointer. */
{
    size_t buf_len = 750;
    char *buf = (char *)AAPL_MALLOC(buf_len);
    char *end = buf + buf_len;
    char *ptr = buf;
    double td = hbtcp->trans_density;
    if( buf == NULL )
        return buf;

    ptr += snprintf(ptr, end-ptr, "\n");
    if( hbtcp->data_row == hbtcp->total_rows/2 )
        ptr += snprintf(ptr, end-ptr, "# Horizontal Bathtub Curve for center eye:\n");
    else
        ptr += snprintf(ptr, end-ptr, "# Horizontal Bathtub Curve for eye at %+d mV (%+d rows) from center:\n", hbtcp->data_millivolts, hbtcp->data_row-hbtcp->total_rows/2);
    if( hbtcp->points == 0 )
    {
        if( hbtcp->data_row != ~0U )
            return strncat(ptr,"\nNOTE: Insufficient data to generate horizontal bathtub information.\n", end-ptr), buf;
        AAPL_FREE(buf);
        return NULL;
    }

    if( hbtcp->left_R_squared < 0.95 || hbtcp->right_R_squared < 0.95 ||
        hbtcp->left_slope <= 0.0 || hbtcp->right_slope >= 0.0 )
        ptr += snprintf(ptr, end-ptr, "#\n# WARNING: This projection is based on measurements with poor correlation.\n#\n");

    ptr += snprintf(ptr, end-ptr, "BER/%g = Q at eye width of   0 mUI: %4.2e, %5.2f\n", td, hbtcp->horz_ber_0mUI, hbtcp->width_0mUI);
    ptr += snprintf(ptr, end-ptr, "BER/%g = Q at eye width of 100 mUI: %4.2e, %5.2f\n", td, hbtcp->horz_ber_100mUI, hbtcp->width_100mUI);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-06 BER/%g = Q(%4.2f): %3d mUI\n", td, q06, hbtcp->horz_eye_1e06);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-10 BER/%g = Q(%4.2f): %3d mUI\n", td, q10, hbtcp->horz_eye_1e10);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-12 BER/%g = Q(%4.2f): %3d mUI\n", td, q12, hbtcp->horz_eye_1e12);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-15 BER/%g = Q(%4.2f): %3d mUI\n", td, q15, hbtcp->horz_eye_1e15);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-17 BER/%g = Q(%4.2f): %3d mUI\n", td, q17, hbtcp->horz_eye_1e17);
    ptr += snprintf(ptr, end-ptr, "Slope left/right:       %6.2f, %6.2f Q/UI\n", hbtcp->left_slope, hbtcp->right_slope);
    ptr += snprintf(ptr, end-ptr, "Y-intercept left/right: %6.2f, %6.2f    Q\n", hbtcp->left_intercept, hbtcp->right_intercept);
    ptr += snprintf(ptr, end-ptr, "Indexes left/right:     %6u, %6u\n",hbtcp->left_index,hbtcp->right_index);
    ptr += snprintf(ptr, end-ptr, "R-squared fit left/right:%5.2f, %6.2f\n", hbtcp->left_R_squared, hbtcp->right_R_squared);
    ptr += snprintf(ptr, end-ptr, "Est RJrms left/right:   %7.3f, %6.3f mUI\n",  hbtcp->left_rj, hbtcp->right_rj);
    ptr += snprintf(ptr, end-ptr, "Est DJpp:               %7.3f  mUI\n", hbtcp->dj);
    return buf;
}

/** @brief Write the formatted HBTC data to a file using the
 **        serdes_eye_hbtc_format() output.
 **/

#if AAPL_ENABLE_FILE_IO
void avago_serdes_eye_hbtc_write(FILE *file, const Avago_serdes_eye_hbtc_t *hbtcp)
{
    char *hbtc_string = avago_serdes_eye_hbtc_format(hbtcp);
    if( hbtc_string )
    {
        fputs("\n",file);
        fputs(hbtc_string,file);
        AAPL_FREE(hbtc_string);
    }
}
#endif

/** @brief Write the formatted HBTC data to the log using the
 **        serdes_eye_hbtc_format() output.
 **/

void avago_serdes_eye_hbtc_log_print(
    Aapl_t *aapl,           /**< [in] */
    Aapl_log_type_t level,         /**< [in] Specify logging type. */
    const char *caller,     /**< [in] Typically __func__, may be 0. */
    int line,               /**< [in] Typically __LINE__, may be 0. */
    const Avago_serdes_eye_hbtc_t *hbtcp)    /**< [in] Data to format and print. */
{
    char *hbtc_string = avago_serdes_eye_hbtc_format(hbtcp);
    if( hbtc_string )
    {
        aapl_log_add(aapl, level, hbtc_string, caller, line);
        AAPL_FREE(hbtc_string);
    }
}


/** @brief   Calculate best-fit extrapolation for the VBTC (vertical bathtub curve).
 ** @details Uses the selected row of eye data, as well as datap->ed_dc_balance,
 **          to perform a standard set of error rate extrapolations.
 ** @return  Saves relevant results into the Avago_serdes_eye_vbtc_t structure.
 **/

void avago_serdes_eye_vbtc_extrapolate(
    const Avago_serdes_eye_data_t *datap, /**< [in] Populated eye data. */
    int data_col,                         /**< [in] Column index in eye data to analyze. */
    Avago_serdes_eye_vbtc_t *results)     /**< [out] Where results are written. */
{
    const bigint *bits   = get_bits_column(datap, data_col);
    const bigint *errors = get_errs_column(datap, data_col);

    int points = data_col < 0 ? datap->ed_y_mission_points : datap->ed_y_points;
    int step   = data_col < 0 ? datap->ed_y_mission_step   : datap->ed_y_step;
    int threshold = datap->ed_error_threshold;

    int y_mid = -1;
    bigint error_min = 0x7fffffff;
    int y;
    for( y = 0; y < points; y++ )
    {
        if( bits[y] > 0 )
        {
            if( errors[y] < error_min )
                error_min = errors[y_mid = y];
        }
    }
    if( y_mid < 0 )
        y_mid = points / 2;


    memset(results,0,sizeof(*results));
    results->data_column = data_col;
    results->total_columns = datap->ed_x_points;
    results->dc_balance = datap->ed_dc_balance;




    {
    int y, dac_top = -1, dac_bottom = -1;
    Avago_least_sqr_point topPoints[AAPL_MAX_DAC_RANGE], bottomPoints[AAPL_MAX_DAC_RANGE];

    int topPointCount = 0, bottomPointCount = 0;
    for( y = y_mid; y < points; y++ )
    {
        if( bits[y] < 0 ) continue;
        if( bits[y] == 0 ) break;

        if( errors[y] <= threshold )
        {
            if( errors[y] == -1 )
                break;
            topPointCount = 0;
            results->top_index = 0;
        }
        else
        {
            topPoints[topPointCount].x = mv_from_index(datap->ed_y_resolution, points, step, y);
            topPoints[topPointCount].y = avago_qfuncinv(avago_calc_BER(errors[y],bits[y],results->dc_balance));
            if( results->top_index == 0 )
                results->top_index = y;

            if( topPointCount > 0
                && topPoints[topPointCount-1].y >= 0
                && topPoints[topPointCount].y < 0 )
            {
                dac_top = topPointCount;
            }
            topPointCount++;
        }
    }

    for( y = y_mid; y >= 0; y-- )
    {
        if( bits[y] < 0 ) continue;
        if( bits[y] == 0 ) break;

        if( errors[y] <= threshold )
        {
            if( errors[y] == -1 )
                break;
            bottomPointCount = 0;
            results->bottom_index = 0;
        }
        else
        {
            bottomPoints[bottomPointCount].x = mv_from_index(datap->ed_y_resolution, points, step, y);
            bottomPoints[bottomPointCount].y = avago_qfuncinv(avago_calc_BER(errors[y],bits[y],results->dc_balance));
            if( results->bottom_index == 0 )
                results->bottom_index = y;

            if( bottomPointCount > 0
                && bottomPoints[bottomPointCount-1].y >= 0
                && bottomPoints[bottomPointCount].y < 0 )
            {
                dac_bottom = bottomPointCount;
            }
            bottomPointCount++;
        }
    }

    if( dac_top >= 0 && dac_bottom >= 0 )
    {
        float top = avago_interpolate(&topPoints[dac_top-1],&topPoints[dac_top]);
        float bottom = avago_interpolate(&bottomPoints[dac_bottom-1],&bottomPoints[dac_bottom]);
        results->Vmean = (int)(top - bottom);
    }
    else
        results->Vmean = 0;

#if 0
    printf("Top edge points (column = %d): ", data_col);
    for( int i = 0; i < topPointCount; i++ )
        printf("(%f,%5.3f)",topPoints[i].x,topPoints[i].y);
    printf("\n");
    printf("Bottom edge points: ");
    for( int i = 0; i < bottomPointCount; i++ )
        printf("(%f,%5.3f)",bottomPoints[i].x,bottomPoints[i].y);
    printf("\n");
#endif

    if( topPointCount < FIT || bottomPointCount < FIT )
        return;

    results->points = FIT;

    {
    Avago_least_sqr_results top, bottom;

    results->top_index += find_best_fit(topPoints,topPointCount);
    results->bottom_index -= find_best_fit(bottomPoints,bottomPointCount);

    avago_least_sqr(topPoints, FIT, &top);
    avago_least_sqr(bottomPoints, FIT, &bottom);

    results->top_rj           = calc_rj(&top);
    results->top_slope        = 1.0 / top.slope;
    results->top_intercept    = top.y_intercept;
    results->top_R_squared    = top.Rsqr;
    results->bottom_rj        = calc_rj(&bottom);
    results->bottom_slope     = 1.0 / bottom.slope;
    results->bottom_intercept = bottom.y_intercept;
    results->bottom_R_squared = bottom.Rsqr;


    {

    double proj_diff = top.y_intercept * bottom.slope - bottom.y_intercept * top.slope;
    double slope_diff = top.slope - bottom.slope;
    int sign = slope_diff > 0 ? +1 : -1;
    double y_0mV = 0.0 - proj_diff / slope_diff;
    double y_25mV = 0.0 - (proj_diff - (sign * 25) * bottom.slope * top.slope) / slope_diff;
    if( y_0mV > AVAGO_Q_CEILING )
        y_0mV = AVAGO_Q_CEILING;
    if( y_25mV > AVAGO_Q_CEILING )
        y_25mV = AVAGO_Q_CEILING;
    results->vert_ber_0mV = avago_qfunc(y_0mV);
    results->vert_ber_25mV = avago_qfunc(y_25mV);
    results->height_0mV = y_0mV;
    results->height_25mV = y_25mV;


    results->vert_eye_1e03 = (int)(sign * ((top.y_intercept - q03) / top.slope - (bottom.y_intercept - q03) / bottom.slope));
    results->vert_eye_1e04 = (int)(sign * ((top.y_intercept - q04) / top.slope - (bottom.y_intercept - q04) / bottom.slope));
    results->vert_eye_1e05 = (int)(sign * ((top.y_intercept - q05) / top.slope - (bottom.y_intercept - q05) / bottom.slope));
    results->vert_eye_1e06 = (int)(sign * ((top.y_intercept - q06) / top.slope - (bottom.y_intercept - q06) / bottom.slope));
    results->vert_eye_1e10 = (int)(sign * ((top.y_intercept - q10) / top.slope - (bottom.y_intercept - q10) / bottom.slope));
    results->vert_eye_1e12 = (int)(sign * ((top.y_intercept - q12) / top.slope - (bottom.y_intercept - q12) / bottom.slope));
    results->vert_eye_1e15 = (int)(sign * ((top.y_intercept - q15) / top.slope - (bottom.y_intercept - q15) / bottom.slope));
    results->vert_eye_1e17 = (int)(sign * ((top.y_intercept - q17) / top.slope - (bottom.y_intercept - q17) / bottom.slope));
    } } }
}

/** @brief Perform a standard set of error rate calculations using the horizontal
 **         center row for each eye.
 **/
static void hbtc_extrapolate(Avago_serdes_eye_data_t *datap)
{
    avago_serdes_eye_hbtc_extrapolate(datap, datap->ed_y_points / 2, &datap->ed_hbtc);
}

/** @brief Perform a standard set of error rate calculations using the mission
 **         data column of the eye data.
 **/

static void vbtc_extrapolate_mission(Avago_serdes_eye_data_t *datap)
{
    avago_serdes_eye_vbtc_extrapolate(datap, -1, &datap->ed_vbtc);
}


/** @brief Write the VBTC data to a string.
 ** @return A character string containing the formatted VBTC results.
 **         The caller should AAPL_FREE the returned string.
 **/

char *avago_serdes_eye_vbtc_format(const Avago_serdes_eye_vbtc_t *vbtcp) /**< Populated VBTC structure pointer */
{
    size_t buf_len = 700;
    char *buf = (char *)AAPL_MALLOC(buf_len);
    char *end = buf + buf_len;
    char *ptr = buf;
    double db = vbtcp->dc_balance;
    if( buf == NULL )
        return buf;

    ptr += snprintf(ptr, end-ptr, "\n");
    if( vbtcp->data_column < 0 )
        ptr += snprintf(ptr, end-ptr, "# Vertical Bathtub Curve (mission data channel %d..%d eye):\n", -1-vbtcp->data_column, 0-vbtcp->data_column);
    else if( vbtcp->data_column == vbtcp->total_columns / 2 )
        ptr += snprintf(ptr, end-ptr, "# Vertical Bathtub Curve (calculated phase center):\n");
    else
        ptr += snprintf(ptr, end-ptr, "# Vertical Bathtub Curve (calculated phase center %+d):\n", vbtcp->data_column - vbtcp->total_columns / 2);
    if( vbtcp->points == 0 )
    {
        if( vbtcp->data_column >= -1 )
            return strncat(ptr,"\nNOTE: Insufficient data to generate vertical bathtub information.\n", end-ptr), buf;
        AAPL_FREE(buf);
        return NULL;
    }
    if( vbtcp->bottom_R_squared < 0.95 || vbtcp->top_R_squared < 0.95 ||
        vbtcp->bottom_slope <= 0.0 || vbtcp->top_slope >= 0.0 )
        ptr += snprintf(ptr, end-ptr, "#\n# WARNING: This projection is based on measurements with poor correlation.\n#\n");

    ptr += snprintf(ptr, end-ptr, "BER/%g = Q at eye height of  0 mV: %4.2e, %5.2f\n", db, vbtcp->vert_ber_0mV, vbtcp->height_0mV);
    ptr += snprintf(ptr, end-ptr, "BER/%g = Q at eye height of 25 mV: %4.2e, %5.2f\n", db, vbtcp->vert_ber_25mV, vbtcp->height_25mV);
    if( vbtcp->Vmean > 0 )
    ptr += snprintf(ptr, end-ptr, "Eye height (Vmean) at %g BER=Q(%4.2f): %3d mV\n",db,0.0,vbtcp->Vmean);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-06 BER/%g = Q(%4.2f): %3d mV\n",db,q06,vbtcp->vert_eye_1e06);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-10 BER/%g = Q(%4.2f): %3d mV\n",db,q10,vbtcp->vert_eye_1e10);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-12 BER/%g = Q(%4.2f): %3d mV\n",db,q12,vbtcp->vert_eye_1e12);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-15 BER/%g = Q(%4.2f): %3d mV\n",db,q15,vbtcp->vert_eye_1e15);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-17 BER/%g = Q(%4.2f): %3d mV\n",db,q17,vbtcp->vert_eye_1e17);
    ptr += snprintf(ptr, end-ptr, "Slope bottom/top:       %6.2f, %6.2f mV/Q\n", vbtcp->bottom_slope, vbtcp->top_slope);
    ptr += snprintf(ptr, end-ptr, "X-intercept bottom/top: %6.2f, %6.2f    Q\n", vbtcp->bottom_intercept, vbtcp->top_intercept);
    ptr += snprintf(ptr, end-ptr, "Indexes bottom/top:     %6u, %6u\n",vbtcp->bottom_index,vbtcp->top_index);
    ptr += snprintf(ptr, end-ptr, "R-squared fit bottom/top:%5.2f, %6.2f\n", vbtcp->bottom_R_squared, vbtcp->top_R_squared);
    ptr += snprintf(ptr, end-ptr, "Est RJrms bottom/top:   %7.3f, %6.3f  mV\n", vbtcp->bottom_rj, vbtcp->top_rj);
    return buf;
}

/** @brief Write the formatted VBTC data to a file using the
 **        serdes_eye_vbtc_format() output.
 **/

#if AAPL_ENABLE_FILE_IO
void avago_serdes_eye_vbtc_write(FILE *file, const Avago_serdes_eye_vbtc_t *vbtcp)
{
    char *vbtc_string = avago_serdes_eye_vbtc_format(vbtcp);
    if( vbtc_string )
    {
        fputs("\n",file);
        fputs(vbtc_string,file);
        AAPL_FREE(vbtc_string);
    }
}
#endif

/** @brief Write the formatted VBTC data to the log using the
 **        serdes_eye_vbtc_format() output.
 **/

void avago_serdes_eye_vbtc_log_print(
    Aapl_t *aapl,           /**< [in] */
    Aapl_log_type_t level,         /**< [in] Specify logging type. */
    const char *caller,     /**< [in] Typically __func__, may be 0. */
    int line,               /**< [in] Typically __LINE__, may be 0. */
    const Avago_serdes_eye_vbtc_t *vbtcp)    /**< [in] Data to format and print. */
{
    char *vbtc_string = avago_serdes_eye_vbtc_format(vbtcp);
    if( vbtc_string )
    {
        aapl_log_add(aapl, level, vbtc_string, caller, line);
        AAPL_FREE(vbtc_string);
    }
}

static void calc_height(Aapl_t *aapl, Avago_serdes_eye_data_t *datap, int column)
{
    int height = 0;
    const bigint *bits   = get_bits_column(datap, column);
    const bigint *errors = get_errs_column(datap, column);
    const int dac_resolution = datap->ed_y_resolution;
    uint y_point;
    for( y_point = 0; y_point < datap->ed_y_points; ++y_point )
    {
        bigint e = errors[y_point];
        if( e <= datap->ed_error_threshold && e >= 0 && bits[y_point] > 0 )
            height++;
    }
    datap->ed_height = height * datap->ed_y_step;

    datap->ed_height_mV = (1000 * datap->ed_height + dac_resolution/2) / dac_resolution;
    vbtc_extrapolate_mission(datap);

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__,"height = %u, height_mV = %u\n", datap->ed_height, datap->ed_height_mV);
    if( aapl->debug >= AVAGO_DEBUG1 )
        avago_serdes_eye_vbtc_log_print(aapl, AVAGO_DEBUG1, __func__, __LINE__, &datap->ed_vbtc);
}


static void calc_width(Aapl_t *aapl, Avago_serdes_eye_data_t *datap)
{
    int pi_resolution = datap->ed_x_resolution * datap->ed_x_step;
    int width = 0, w = 0, out = 0;
    uint x_point;
    for( x_point = 0; x_point < datap->ed_x_points; ++x_point )
    {
        bigint e = AVAGO_EYE_ERRORS_GET(*datap, x_point, datap->ed_y_points/2);
        if( e <= datap->ed_error_threshold && e >= 0 )
        {
            if( out >= 4 )
            {
                width = MAX(w,width);
                w = 0;
            }
            w++;
            out = 0;
        }
        else
            out++;
    }
    datap->ed_width = MAX(w,width) * datap->ed_x_step;
    datap->ed_width_mUI = (1000 * datap->ed_width + pi_resolution/2) / pi_resolution;
    hbtc_extrapolate(datap);

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__,"width = %u, width_mUI = %u\n", datap->ed_width, datap->ed_width_mUI);
    if( aapl->debug >= AVAGO_DEBUG1 )
        avago_serdes_eye_hbtc_log_print(aapl, AVAGO_DEBUG1, __func__, __LINE__, &datap->ed_hbtc);
}






static BOOL gather_eye_width(Eye_state_t *esp)
{

    return sbm_eye_setup_row(esp)
        && sbm_eye_gather_row(esp, esp->datap->ed_y_points / 2);
}

static BOOL gather_eye_height(Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int x_mid = datap->ed_x_points / 2;
    BOOL status;


    status = sbm_eye_gather_mission_nrz(esp);
    if( datap->ed_eye_type == AVAGO_EYE_SIZE_VDUAL && status )
    {
        status = sbm_eye_setup_column(esp, 0) && sbm_eye_gather_column(esp, x_mid, 0, datap->ed_y_points);
    }
    return status;
}

static BOOL gather_full_eye(Eye_state_t *esp)
{

    return sbm_eye_gather_mission_nrz(esp) && sbm_eye_gather_nrz(esp);

}

/** @brief      Gather eye diagram data (measurements) from a SerDes slice.
 ** @details    See serdes.h for explanations about configuration and return
 **             values.  In case of success or error, tries resetting key
 **             SerDes values to original states.  But leaves test channel
 **             clock source set to the test clock (rclk).
 ** @return Returns 0 on success, -1 and decrements aapl->return_code on error.
 **/

int avago_serdes_eye_get(
    Aapl_t *aapl,                             /**< [in] Pointer to Aapl_t structure. */
    uint addr,                                /**< [in] SBus slice address. */
    const Avago_serdes_eye_config_t *configp, /**< [in] Configuration parameters for how to gather the eye. */
    Avago_serdes_eye_data_t *datap)           /**< [out] Where to save the gathered eye data. */
{
    uint dfe_resume_status = 0;
    Eye_state_t es;
    Eye_state_t *esp = &es;

    int ret = aapl_get_return_code(aapl);
    if( ret < 0 )
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "found aapl->return_code negative (%d) implying a prior error; value cleared\n",ret);
    
    if( !(   aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 2, AVAGO_PROCESS_B, AVAGO_PROCESS_F)
          && aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)) )
    {
        return -1;
    }
    if( !aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, FALSE, 1, 0x1049) )
    {
        uint build_id = avago_firmware_get_build_id(aapl, addr);
        if( 0 == (build_id & 0x0040) )
            return aapl_fail(aapl, __func__, __LINE__,
                "SBus %s, Eye measurement requires a _xx4x build in pre-0x1049 firmware, current is 0x%04X_%04X\n",
                aapl_addr_to_str(addr), avago_firmware_get_rev(aapl, addr), build_id);
    }
     
#ifndef MV_HWS_REDUCED_BUILD
    if( datap->ed_hardware_log) aapl_free(aapl,datap->ed_hardware_log,"ed_hw_log");
    datap->ed_hardware_log = avago_hardware_info_format(aapl, addr);
#endif

    if( configp->ec_eye_type > AVAGO_EYE_FULL )
    {
        return aapl_fail(aapl, __func__, __LINE__,
            "Avago_serdes_eye_config_t->ec_eye_type value (%d) is out-of-range.\n",
            configp->ec_eye_type);
    }

    if( avago_serdes_dfe_pause(aapl, addr, &dfe_resume_status) == -1 &&
        avago_serdes_dfe_wait(aapl, addr) == 0 )
    {
        return aapl_fail(aapl,__func__,__LINE__,"EYE coordination with running DFE failed.\n", "\n");
    }

    datap->ed_y_resolution = avago_serdes_get_dac_range(aapl, addr);

    if( !init_eye_state(esp, aapl, addr, configp, datap) )
    {
        return aapl_fail(aapl, __func__, __LINE__, "Error initializing hardware: returning %d\n",aapl->return_code);
    }

    {
    uint x_UI          = configp->ec_x_UI;
    uint x_res         = configp->ec_x_resolution;
    uint x_step, x_points;
    uint x_min_offset;

    uint y_step         = configp->ec_y_step_size;
    uint y_points       = configp->ec_eye_type == AVAGO_EYE_WIDTH ? 1 : configp->ec_y_points;
    uint y_center_point = configp->ec_y_center_point;
    uint dac_min;
    if( y_center_point == 0 )
        y_center_point = datap->ed_y_resolution / 2;
    check_range_x(es.phase_mult * 64, &x_res, &x_UI, &x_points, &x_step);
    check_range_y(&es, &y_step, &y_points, &y_center_point, &dac_min);

    datap->ed_x_UI         = x_UI;
    datap->ed_x_points     = x_points;
    datap->ed_x_step       = x_step;
    datap->ed_x_resolution = (x_points - 1) / x_UI;
    x_min_offset           = (x_points / 2) * x_step;

    datap->ed_y_points     = y_points;
    datap->ed_y_step       = y_step;
    datap->ed_error_threshold = configp->ec_error_threshold;
    datap->ed_dc_balance      = configp->ec_dc_balance;
    datap->ed_trans_density   = configp->ec_trans_density;
    datap->ed_min_dwell_bits  = configp->ec_min_dwell_bits;
    datap->ed_max_dwell_bits  = configp->ec_max_dwell_bits;
    datap->ed_fast_dynamic    = configp->ec_fast_dynamic;
    datap->ed_eye_type        = configp->ec_eye_type;
    datap->ed_cmp_mode        = configp->ec_cmp_mode;


    {

    int phase_min;
    int do_height = 1;
    int do_width = 1;
    uint x_mid = x_points / 2;

    Avago_serdes_rx_cmp_mode_t   orig_cmp_mode  = es.cmp_mode;





    {
    int phase_center = 0;

    datap->ed_x_min = phase_center - x_min_offset;
    datap->ed_y_min = dac_min;

    {
        datap->ed_y_mission_points = datap->ed_y_points;
        datap->ed_y_mission_step = datap->ed_y_step;
        datap->ed_y_mission_min = datap->ed_y_min;
    }

 if( allocate_eye_arrays(aapl, datap) < 0 )
        return -1;

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus %s, x_UI=%u, x_points=%u, x_step=%u, x_offset=%u; y_points=%u, y_step=%u, y_min=%u.\n", aapl_addr_to_str(addr), x_UI, x_points, x_step, x_min_offset, datap->ed_y_points, datap->ed_y_step, datap->ed_y_min);




    phase_min = phase_center - x_min_offset;

    datap->ed_x_min    = phase_min;
    datap->ed_x_max    = phase_min + (x_points - 1) * x_step;
    }

    if( eye_set_error_timer(&es, es.min_dwell) < 0 )
        goto SEG_Reset;

    if( esp->sbm_eye_gather )
        sbm_eye_setup_serdes(esp);

    if( configp->ec_eye_type == AVAGO_EYE_FULL )
    {
        if( gather_full_eye(esp) < 0 )
        {
            goto SEG_Reset;
        }
    }
    else
    {
        if( configp->ec_eye_type == AVAGO_EYE_HEIGHT ) do_width = 0;
        if( configp->ec_eye_type == AVAGO_EYE_WIDTH  ) do_height = 0;


        if( do_width )
        {
            if( !gather_eye_width(esp) )
                goto SEG_Reset;
        }

        if( do_height )
        {
            if( !gather_eye_height(esp) )
                goto SEG_Reset;
        }
 
    }

    if( esp->sbm_eye_gather )
        sbm_eye_setup_point(esp);

    if( configp->ec_eye_type == AVAGO_EYE_FULL )
    {
            eye_dynamic_dwell_all(esp);
    }
    else
    {
        int x_mid = esp->datap->ed_x_points / 2;
        int y_mid = esp->datap->ed_y_points / 2;
        if( do_width )
            eye_dynamic_dwell_width(&es, y_mid);
        if( do_height && do_width )
            eye_dynamic_dwell_height(esp, x_mid);
        if( do_height && !eye_dynamic_dwell_height(esp, -1) )
            return -1;
    }
    if( configp->ec_eye_type == AVAGO_EYE_SIZE || configp->ec_eye_type == AVAGO_EYE_HEIGHT )
    {
        uint y;
        for( y = 0; y < datap->ed_y_points; y++ )
        {
            AVAGO_EYE_ERRORS_SET(*datap,x_mid,y,datap->ed_mission_errors[y]);
            AVAGO_EYE_BITS_SET(  *datap,x_mid,y,datap->ed_mission_bits  [y]);
        }
    }
    serdes_eye_calc_gradient(esp->datap);
    serdes_eye_calc_qval(esp->datap);

    if( do_width ) calc_width(esp->aapl, datap);
    if( do_height ) calc_height(esp->aapl, datap, -1);
 
    avago_serdes_eye_plot_log_print(aapl, AVAGO_DEBUG1, __func__, __LINE__, datap);
  

goto SEG_Exit;

SEG_Reset:
#ifndef MV_HWS_REDUCED_BUILD
    if( aapl_get_async_cancel_flag(aapl) )
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__,"SBus %s, Eye exit due to cancel request.\n", aapl_addr_to_str(addr));
    else
#endif
        aapl_fail(aapl, __func__, __LINE__,"SBus %s, Eye abnormal exit.\n",aapl_addr_to_str(addr));

SEG_Exit:


    avago_serdes_set_rx_cmp_mode(esp->aapl, esp->addr, orig_cmp_mode);
    avago_serdes_get_errors(aapl, addr, AVAGO_LSB, TRUE);

    avago_serdes_power_down_phase_interpolator(aapl, addr);
    } }

    avago_serdes_dfe_resume(aapl, addr, dfe_resume_status);

    return aapl->return_code;

}


/** @brief  Create a simple text eye.
 ** @return A string containing the eye.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_plot_format(
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to display */
{
    BOOL use_mission = (datap->ed_x_points == 1);
    char *buf = (char *)AAPL_MALLOC((datap->ed_x_points+6)*datap->ed_y_points + 80);
    char *ptr = buf + sprintf(buf,"Text eye plot %d x %d :\n",datap->ed_x_points, datap->ed_y_points);
    uint y = datap->ed_y_points;
    while( y-- > 0 )
    {
        uint x;
        ptr += sprintf(ptr,"%4d:", y * datap->ed_y_step + datap->ed_y_min - datap->ed_y_resolution/2);

        for (x = 0; x < datap->ed_x_points; x++) 
        {
            bigint bits = get_bits_column(datap, use_mission ? -1 : (int)x)[y];
            bigint errs = get_errs_column(datap, use_mission ? -1 : (int)x)[y];
            if( bits <= 0 )
                ptr[x] = '-';
            else if( errs == 0 )
            {
                if( datap->ed_x_points / 2 == x )
                    ptr[x] = '!';
                else if( datap->ed_hbtc.data_row == y )
                    ptr[x] = '-';
                else if( datap->ed_hbtc2.data_row == y )
                    ptr[x] = '-';
                else if( datap->ed_hbtc3.data_row == y )
                    ptr[x] = '-';
                else
                    ptr[x] = ' ';
            }
            else if( errs <= datap->ed_error_threshold )
                ptr[x] = '.';
            else if( errs <= datap->ed_error_threshold*10 )
                ptr[x] = '+';
            else if( errs <= datap->ed_error_threshold*100 )
                ptr[x] = '*';
            else if( datap->ed_x_points / 2 == x )
                ptr[x] = '|';
            else if( datap->ed_hbtc.data_row == y )
                ptr[x] = '=';
            else if( datap->ed_hbtc2.data_row == y )
                ptr[x] = '=';
            else if( datap->ed_hbtc3.data_row == y )
                ptr[x] = '=';
            else
                ptr[x] = '#';
        }
        ptr += datap->ed_x_points;
        *ptr++ = '\n';
    }
    *ptr = '\0';
    return buf;
}

/** @brief  Create a simple text gradient eye.
 ** @return A string containing the eye gradient.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_gradient_plot_format(
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to display */
{
    char *buf = (char *)AAPL_MALLOC((datap->ed_x_points+6)*datap->ed_y_points + 80);
    char *ptr = buf + sprintf(buf,"Text eye gradient plot %d x %d :\n",datap->ed_x_points, datap->ed_y_points-1);

    uint y = datap->ed_y_points;
    while( y-- > 1 )
    {
        uint x;
        ptr += sprintf(ptr,"%4d:", y * datap->ed_y_step + datap->ed_y_min - datap->ed_y_resolution/2);
        for( x = 0; x < datap->ed_x_points; x++ )
        {
            float grad = AVAGO_EYE_GRAD_GET(*datap,x,y);
            bigint bits = AVAGO_EYE_BITS_GET(*datap,x,y);

            if( bits <= 0 )
                ptr[x] = '-';
            else if( grad < 0.0001 )
            {
                if( datap->ed_x_points / 2 == x )
                    ptr[x] = '!';
                else if( datap->ed_hbtc.data_row == y )
                    ptr[x] = '-';
                else if( datap->ed_hbtc2.data_row == y )
                    ptr[x] = '-';
                else if( datap->ed_hbtc3.data_row == y )
                    ptr[x] = '-';
                else
                    ptr[x] = ' ';
            }
            else if( grad < 0.004 )
                ptr[x] = '.';
            else if( grad < 0.014 )
                ptr[x] = ':';
            else if( grad < 0.030 )
                ptr[x] = '+';
            else if( datap->ed_x_points / 2 == x )
                ptr[x] = '|';
            else if( datap->ed_hbtc2.data_row == y )
                ptr[x] = '=';
            else if( datap->ed_hbtc3.data_row == y )
                ptr[x] = '=';
            else if( datap->ed_hbtc.data_row == y )
                ptr[x] = '=';
            else if( datap->ed_y_points / 2 == y )
                ptr[x] = '=';
            else if( grad < 0.100 )
                ptr[x] = '*';
            else
                ptr[x] = '#';
        }
        ptr += datap->ed_x_points;
        *ptr++ = '\n';
    }
    *ptr = '\0';
    return buf;
}

/** @brief  Write a simple text eye to a log file. */
void avago_serdes_eye_plot_log_print(
    Aapl_t *aapl,                       /**< [in] */
    Aapl_log_type_t level,              /**< [in] Specify logging type. */
    const char *caller,                 /**< [in] Typically __func__, may be 0. */
    int line,                           /**< [in] Typically __LINE__, may be 0. */
    const Avago_serdes_eye_data_t *datap)   /**< [in] Data to format and print. */
{
    if(( aapl->debug >= (uint)level ) || (level >= AVAGO_MEM_LOG ))
    {
        char *eye_text = avago_serdes_eye_plot_format(datap);
        aapl_log_add(aapl, level, eye_text, caller, line);
        AAPL_FREE(eye_text);
    }
}

#if AAPL_ENABLE_FILE_IO

/** @brief Write a simple text eye to a file. */
void avago_serdes_eye_plot_write(
    FILE *file,                             /**< Where to print the eye */
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to print */
{
    char *eye_text = avago_serdes_eye_plot_format(datap);
    fputs(eye_text,file);
    AAPL_FREE(eye_text);
}

/** @brief Write a simple text gradient eye to a file. */
void avago_serdes_eye_gradient_plot_write(
    FILE *file,                             /**< Where to print the eye */
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to print */
{
    char *eye_text = avago_serdes_eye_gradient_plot_format(datap);
    fputs(eye_text,file);
    AAPL_FREE(eye_text);
}

#ifndef MV_HWS_REDUCED_BUILD
/** @brief Write eye data to a file. */
void avago_serdes_eye_data_write(
    FILE *file,                             /**< where to write the data */
    const Avago_serdes_eye_data_t *datap)   /**< data to write */
{
    char time_str[40];
    aapl_local_strftime(time_str,sizeof(time_str),"%Y-%m-%d %H:%M:%S");

    fprintf(file,"# EYE DIAGRAM DATA\n");
    fprintf(file,"\n");
    fprintf(file,"file_format:    7\n");
    fprintf(file,"capture_date:   %s\n", time_str);
    if( datap->ed_comment )
        fprintf(file,"user_comment:   %s\n",datap->ed_comment);
    fprintf(file,"\n");
    if( datap->ed_hardware_log )
        fprintf(file,"%s\n", datap->ed_hardware_log);

    fprintf(file,"eye_type:       %s\n", aapl_eye_type_to_str(datap->ed_eye_type));
    fprintf(file,"compare_mode:   %s\n", aapl_cmp_mode_to_str(datap->ed_cmp_mode));
    fprintf(file,"\n");

    fprintf(file,"x.UI:         %3d\n",datap->ed_x_UI);
    fprintf(file,"x.resolution: %3d\n",datap->ed_x_resolution);
    fprintf(file,"x.points:     %3d\n",datap->ed_x_points);
    fprintf(file,"x.min:        %3d\n",datap->ed_x_min);
    fprintf(file,"x.max:        %3d\n",datap->ed_x_max);
    fprintf(file,"x.step:       %3d\n",datap->ed_x_step);
    fprintf(file,"x.center:     %3d\n",(datap->ed_x_min + datap->ed_x_max) / 2);
    fprintf(file,"x.width:      %3d\n",datap->ed_width);
    fprintf(file,"x.width_mUI:  %3d\n",datap->ed_width_mUI);
    fprintf(file,"\n");

    fprintf(file,"y.resolution: %3d (DAC points)\n",datap->ed_y_resolution);
    fprintf(file,"y.points:     %3d\n",datap->ed_y_points);
    fprintf(file,"y.step:       %3d\n",datap->ed_y_step);
    fprintf(file,"y.min:        %3d (DAC for y=0)\n",datap->ed_y_min);
    fprintf(file,"y.mission_points: %3d\n",datap->ed_y_mission_points);
    fprintf(file,"y.mission_step:   %3d\n",datap->ed_y_mission_step);
    fprintf(file,"y.mission_min:    %3d (DAC for y=0)\n",datap->ed_y_mission_min);
    if( datap->ed_hbtc2.data_row > 0 )
    {
    fprintf(file,"y.center2-3:  %3d\n",datap->ed_hbtc3.data_row);
    fprintf(file,"y.center1-2:  %3d\n",datap->ed_hbtc2.data_row);
    fprintf(file,"y.center0-1:  %3d\n",datap->ed_hbtc .data_row);
    }
    fprintf(file,"y.center:     %3d (DAC middle)\n",datap->ed_y_min + datap->ed_y_points / 2 * datap->ed_y_step);
    fprintf(file,"y.height:     %3d\n",datap->ed_height);
    fprintf(file,"y.height_mV:  %3d\n",datap->ed_height_mV);
    fprintf(file,"\n");

    fprintf(file,"dc_balance:    %6.2g\n", datap->ed_dc_balance);
    fprintf(file,"trans_density: %6.2g\n", datap->ed_trans_density);
    fprintf(file,"error_threshold: %d\n",  datap->ed_error_threshold);
    fprintf(file,"min_dwell_bits:  %g\n",  datap->ed_min_dwell_bits*1.0);
    fprintf(file,"max_dwell_bits:  %g\n",  datap->ed_max_dwell_bits*1.0);
    fprintf(file,"fast_dynamic:    %d\n",  datap->ed_fast_dynamic);
    fprintf(file,"\n");
#if 1
    if( datap->ed_vbtc2.top_index > 0 )
    {
        fprintf(file,"vbtc3_top_index:     %3d\n", datap->ed_vbtc3.top_index);
        fprintf(file,"vbtc3_bottom_index:  %3d\n", datap->ed_vbtc3.bottom_index);
        fprintf(file,"vbtc2_top_index:     %3d\n", datap->ed_vbtc2.top_index);
        fprintf(file,"vbtc2_bottom_index:  %3d\n", datap->ed_vbtc2.bottom_index);
    }
    fprintf(file,"vbtc_top_index:     %3d\n", datap->ed_vbtc.top_index);
    fprintf(file,"vbtc_bottom_index:  %3d\n", datap->ed_vbtc.bottom_index);

    if( datap->ed_hbtc2.left_index > 0 )
    {
        fprintf(file,"hbtc3_left_index:   %3d\n", datap->ed_hbtc3.left_index);
        fprintf(file,"hbtc3_right_index:  %3d\n", datap->ed_hbtc3.right_index);
        fprintf(file,"hbtc2_left_index:   %3d\n", datap->ed_hbtc2.left_index);
        fprintf(file,"hbtc2_right_index:  %3d\n", datap->ed_hbtc2.right_index);
    }
    fprintf(file,"hbtc_left_index:    %3d\n", datap->ed_hbtc.left_index);
    fprintf(file,"hbtc_right_index:   %3d\n", datap->ed_hbtc.right_index);
    fprintf(file,"\n");
#endif

    fprintf(file,"# Phase index, DAC index, Errors, Bits\n");
    if( datap->ed_y_points > 1 )
    {
        int x;
        fprintf(file,"# Mission data:\n");
        for( x = -3; x < 0; x++ )
        {
            const bigint *errs = get_errs_column(datap, x);
            const bigint *bits = get_bits_column(datap, x);
            uint y;
            for( y = 0; y < datap->ed_y_resolution; y++ )
                if( bits[y] != 0 )
                {
                    fprintf(file,"%3d, %3u, %6s, %13s", x, y, aapl_bigint_to_str(errs[y]), aapl_bigint_to_str(bits[y]));
                    fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y));
                    if( y > 0 ) fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y-1) - avago_serdes_eye_qval_get(0,datap,x,y));
                    fprintf(file,"\n");
                }
        }
    }
    if( datap->ed_x_points > 1 )
    {
        uint x;
        fprintf(file,"# Test channel data:\n");
        for( x = 0; x < datap->ed_x_points; ++x )
        {
            const bigint *errs = get_errs_column(datap, x);
            const bigint *bits = get_bits_column(datap, x);
            uint y;
            for( y = 0; y < datap->ed_y_points; ++y )
                if( bits[y] != 0 )
                {
                    fprintf(file,"%3u, %3u, %6s, %13s", x, y, aapl_bigint_to_str(errs[y]), aapl_bigint_to_str(bits[y]));
                    fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y));
                    if( y > 0 ) fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y-1) - avago_serdes_eye_qval_get(0,datap,x,y));
                    if( x > 0 ) fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x-1,y) - avago_serdes_eye_qval_get(0,datap,x,y));
                    fprintf(file,"\n");
                }
        }
    }

    avago_serdes_eye_vbtc_write(file, &datap->ed_vbtc3);
    avago_serdes_eye_vbtc_write(file, &datap->ed_vbtc2);
    avago_serdes_eye_vbtc_write(file, &datap->ed_vbtc);
    avago_serdes_eye_hbtc_write(file, &datap->ed_hbtc3);
    avago_serdes_eye_hbtc_write(file, &datap->ed_hbtc2);
    avago_serdes_eye_hbtc_write(file, &datap->ed_hbtc);

#if 0
    {
    Avago_serdes_eye_vbtc_t vbtc_calc;
    avago_serdes_eye_vbtc_extrapolate(datap, datap->ed_x_points / 2, &vbtc_calc);
    avago_serdes_eye_vbtc_write(file, &vbtc_calc);
    fputs("\n", file);
    }
#endif
}

/** @brief Write the captured data and meta data to a file.
 **
 ** @return 0 on success, -1 on failure.
 **/
int avago_serdes_eye_data_write_file(
    const char *file_name,                  /**< Filename to write the data. */
    const Avago_serdes_eye_data_t *datap)   /**< Data to write. */
{
    FILE *fp = fopen(file_name,"w");
    if( fp )
    {
        avago_serdes_eye_data_write(fp, datap);
        return fclose(fp);
    }
    return -1;
}
#endif
#ifndef MV_HWS_REDUCED_BUILD
static int split(char *line, const char *delim, char *argv[])
{
    int argc = 0;
    char *tok_state;
    argv[argc] = aapl_strtok_r(line,delim,&tok_state);
    while( argv[argc] )
        argv[++argc] = aapl_strtok_r(NULL,delim,&tok_state);
    return argc;
}

static int getint(const char *str)
{
    return (int) strtol(str,0,0);
}

static bigint getbigint(const char *str)
{
    return (bigint) strtoll(str,0,0);
}

static void set_x_center(Aapl_t *aapl, Avago_serdes_eye_data_t *datap, int value)
{
    (void)aapl;
    datap->ed_x_min = value - 32 * datap->ed_x_step;
    datap->ed_x_max = value + 32 * datap->ed_x_step;
}

static void parse_mission_errors(Aapl_t *aapl, Avago_serdes_eye_data_t *datap, char *str_val)
{
    char *argv[260];
    int last = 0;
    int ypoints, i;
    (void)aapl;
    split(str_val, " ", argv);
    while( argv[last] )
        last++;
    ypoints = last;
    for( i = 0; i < ypoints; i++ )
    {
        bigint errs = getbigint(argv[i]);
        datap->ed_mission_errors[i] = errs;
        datap->ed_mission_bits[i]   = errs < 0 ? 0 : datap->ed_max_dwell_bits;
    }
}

static void parse_ebert_args(Aapl_t *aapl, Avago_serdes_eye_data_t *datap, char *str_val)
{
    char *argv[260];
    int i;
    char *hscale = 0, *vscale = 0, *timer = 0;
    split(str_val, " ", argv);
    for( i = 0; argv[i]; i++ )
    {
        if(      EQS(argv[i],"-horiz_scale") ) hscale = argv[i+1];
        else if( EQS(argv[i],"-scale"      ) ) vscale = argv[i+1];
        else if( EQS(argv[i],"-timer"      ) ) timer  = argv[i+1];
        else if( EQS(argv[i],"-full"       ) ) datap->ed_eye_type = AVAGO_EYE_FULL;
        else if( EQS(argv[i],"-cross"      ) ) datap->ed_eye_type = AVAGO_EYE_SIZE;
    }
    if( timer )
    {
        float dval;
        sscanf(timer,"%20g",&dval);
        datap->ed_min_dwell_bits = datap->ed_max_dwell_bits = (bigint)dval;
    }
    if( hscale && vscale )
    {
        int x_UI =
            0==strcmp(hscale,"1") ? 1 :
            0==strcmp(hscale,"0.5") ? 2 :
            0==strcmp(hscale,"0.25") ? 4 :
            0==strcmp(hscale,"0.125") ? 8 : 3;
        int y_step =
            0==strcmp(vscale,"1") ? 1 :
            0==strcmp(vscale,"0.5") ? 2 :
            0==strcmp(vscale,"0.25") ? 4 : 3;

        aapl_log_printf(aapl, AVAGO_DEBUG4,__func__,__LINE__,"x_UI = %d, y_step = %d\n",x_UI, y_step);

        datap->ed_x_UI = x_UI;
        datap->ed_x_points = 64;
        datap->ed_x_step = x_UI;
        datap->ed_x_resolution = 64 / x_UI;

        datap->ed_y_mission_step   = datap->ed_y_step   = y_step;
        datap->ed_y_mission_points = datap->ed_y_points = 64;
        datap->ed_y_mission_min    = datap->ed_y_min    = datap->ed_y_resolution / 2 - datap->ed_y_points / 2 * datap->ed_y_step;

        if( allocate_eye_arrays(aapl, datap) < 0 )
            return;
    }
}

/** @brief   Reads a name and value from buf.
 ** @details Buf contains a name value pair separated by white space
 **          and an equals sign.  Locate and nul terminate the name, and
 **          store the value into *value.
 **          Comments (starting with a '#') and extra fields are ignored.
 ** @return  The number of fields found: 0 for blank or comment lines, 1 for
 **          only a name, 2 for name and value.
 **/
static int get_name_value_pair(
    char *buf,              /**< [in] Line to parse. */
    char **name,            /**< [out] Pointer to name in buf. */
    char **value_string,    /**< [out] Pointer to value string in buf. */
    bigint *value)          /**< [out] Pointer to value. */
{
    const char *seps = ": \t\r\n=";
    char *ptr;
    *value = 0;
    buf += strspn(buf,seps);
    if( *buf == '\0' ) return 0;

    *name = buf;
    buf += strcspn(buf,seps);
    if( *buf == '\0' ) return 1;
    *buf++ = '\0';

    buf += strspn(buf,seps+1);
    if( *buf == '#' || *buf == '\0' ) return 1;

    *value_string = buf;
    *value = strtol(*value_string,&ptr,0);
    buf += strcspn(buf,"\r\n");
    *buf = '\0';

    if( **name == '#' ) return 0;
    return 2;
}

/** @brief   Loads eye data from a file.
 ** @details Does not require AAPL connection to any hardware.
 ** @return  Returns 0 on error, and logs specific problem.
 **/
int avago_serdes_eye_data_read_file(
    Aapl_t *aapl,                   /**< Pointer to Aapl_t structure. */
    const char *filename,           /**< name of file containing eye data */
    Avago_serdes_eye_data_t *datap) /**< eye data structure to fill in */
{
    char line[4096];
    int linenum = 0;
    FILE *file = fopen(filename,"r");
    BOOL in_header = TRUE;

    int file_format = 0;
    char *ptr = datap->ed_hardware_log = (char *)aapl_malloc(aapl,200,__func__);
    *ptr = '\0';

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "%s\n",filename);

    if( !file )
        return aapl_fail(aapl, __func__, __LINE__, "ERROR opening file %s\n",filename);

    datap->ed_error_threshold = 30;
    datap->ed_width = 0;
    datap->ed_height = 0;
    datap->ed_x_points = 64;
    datap->ed_y_points = 64;
    datap->ed_cmp_mode = AVAGO_SERDES_RX_CMP_MODE_XOR;
    datap->ed_y_resolution = 256;
    datap->ed_y_mission_points = 0;
    datap->ed_y_mission_step = 0;
    datap->ed_y_mission_min = 0;


    while( fgets(line, sizeof(line), file) )
    {
        linenum++;

        if( in_header )
        {
            char *name = 0, *str_val = 0;
            bigint value;
            int count = get_name_value_pair(line,&name,&str_val,&value);
            float dval;

            if( count > 1 || (name && (*name == '#')) )
            aapl_log_printf(aapl,AVAGO_DEBUG4,__func__,__LINE__,"count=%d, name=\"%s\", str_val=\"%s\", value=%ld\n",count,name,str_val,value);

            if( count == 0 && str_val && 0 == strncmp(str_val,"Phase index", 11) )
            {
                allocate_eye_arrays(aapl, datap);
                in_header = FALSE;
            }
            if( count != 2 ) continue;


            if(      EQS(name,"file_format"     ) ) file_format = value;

            else if( EQS(name,"x.width"         ) ) datap->ed_width = value;
            else if( EQS(name,"y.height"        ) ) datap->ed_height = value;

            else if( EQS(name,"x.width_mUI"     ) ) datap->ed_width_mUI = value;
            else if( EQS(name,"y.height_mV"     ) ) datap->ed_height_mV = value;

            else if( EQS(name,"x.UI"            ) ) datap->ed_x_UI = value;
            else if( EQS(name,"x.points"        ) ) datap->ed_x_points = value;
            else if( EQS(name,"x.step"          ) ) datap->ed_x_step = value;
            else if( EQS(name,"x.resolution"    ) ) datap->ed_x_resolution = value;

            else if( EQS(name,"x.min"           ) ) datap->ed_x_min = value;
            else if( EQS(name,"x.max"           ) ) datap->ed_x_max = value;

            else if( EQS(name,"y.resolution"    ) ) datap->ed_y_resolution = value;
            else if( EQS(name,"y.center2-3"     ) ) datap->ed_hbtc3.data_row = value;
            else if( EQS(name,"y.center1-2"     ) ) datap->ed_hbtc2.data_row = value;
            else if( EQS(name,"y.center0-1"     ) ) datap->ed_hbtc .data_row = value;
            else if( EQS(name,"y.points"        ) ) datap->ed_y_points = value;
            else if( EQS(name,"y.step"          ) ) datap->ed_y_step = value;
            else if( EQS(name,"y.min"           ) ) datap->ed_y_min = value;
            else if( EQS(name,"y.mission_points") ) datap->ed_y_mission_points = value;
            else if( EQS(name,"y.mission_step"  ) ) datap->ed_y_mission_step = value;
            else if( EQS(name,"y.mission_min"   ) ) datap->ed_y_mission_min = value;

            else if( EQS(name,"SBus_address"    ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"JTAG_ID"         ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"Process_ID"      ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"SerDes"          ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);

            else if( EQS(name,"user_comment"    ) ) datap->ed_comment          = aapl_strdup(str_val);

            else if( EQS(name,"eye_type"        ) ) aapl_str_to_eye_type (str_val,&datap->ed_eye_type);
            else if( EQS(name,"compare_mode"    ) ) aapl_str_to_cmp_mode (str_val,&datap->ed_cmp_mode);
            else if( EQS(name,"fast_dynamic"    ) ) datap->ed_fast_dynamic     = getint(str_val);
            else if( EQS(name,"error_threshold" ) ) datap->ed_error_threshold = value;

            else if( EQS(name,"dc_balance"      ) ) sscanf(str_val, "%20f",&datap->ed_dc_balance);
            else if( EQS(name,"trans_density"   ) ) sscanf(str_val, "%20f",&datap->ed_trans_density);
            else if( EQS(name,"min_dwell_bits"  ) ) sscanf(str_val, "%20g",&dval),datap->ed_min_dwell_bits = (bigint)dval;
            else if( EQS(name,"max_dwell_bits"  ) ) sscanf(str_val, "%20g",&dval),datap->ed_max_dwell_bits = (bigint)dval;



            else if( EQS(name,"file_format_version") ) file_format = value;
            else if( EQS(name,"process_id"         ) ) ptr += sprintf(ptr,"Process_ID:     %s\n",str_val);
            else if( EQS(name,"chip"               ) ) ptr += sprintf(ptr,"JTAG_ID:        %s",str_val);
            else if( EQS(name,"chip_rev"           ) ) ptr += sprintf(ptr," rev %s\n",str_val);
            else if( EQS(name,"errors_mission"     ) ) parse_mission_errors(aapl, datap, str_val);
            else if( EQS(name,"args"               ) ) parse_ebert_args(aapl, datap, str_val);
            else if( EQS(name,"phase_center"       ) ) set_x_center(aapl, datap, value);
            else if( EQS(name,"max_errors"         ) ) sscanf(str_val,"%20g",&dval), datap->ed_min_dwell_bits = datap->ed_max_dwell_bits = (bigint)dval;
            else if( file_format == 0 ) continue;

        }
        else
        {
            char *argv[20];
            int argc = split(line, " ,", argv);
            if( argv[0][0] == '#' && EQS(argv[1],"BATHTUB") )
                break;
            if( argv[0][0] == '#' && EQS(argv[1],"Horizontal") )
                break;
            if( argv[0][0] == '#' && EQS(argv[1],"Vertical") )
                break;
            if( argc >= 3 && argv[0][0] != '#' )
            {
                 int x = getint(argv[0]);
                uint y = getint(argv[1]);
                bigint *errorsp = (bigint *)&get_errs_column(datap, x)[y];
                bigint *bitsp   = (bigint *)&get_bits_column(datap, x)[y];
                bigint errs = getbigint(argv[2]);
                bigint bits;

                if( errs < 0 )       bits = 0;
                else if( argc >= 4 ) bits = getbigint(argv[3]);
                else                 bits = datap->ed_max_dwell_bits;

                if( x >= -3 && x < (int)datap->ed_x_points && ((x >= 0 && y < datap->ed_y_points) || y < datap->ed_y_resolution) )
                {
                    *errorsp = errs;
                    *bitsp   = bits;

                    calc_qval_bit(datap, x, y);
                }
                else
                {
                    printf("Warning: Data index out of range at [%d,%u]\n",x,y);
                }
            }
        }
    }
    if( datap->ed_y_mission_points == 0 ) datap->ed_y_mission_points = datap->ed_y_points;
    if( datap->ed_y_mission_step   == 0 ) datap->ed_y_mission_step   = datap->ed_y_step;
    if( datap->ed_y_mission_points == 0 ) datap->ed_y_mission_min    = datap->ed_y_min;

    serdes_eye_calc_gradient(datap);
    vbtc_extrapolate_mission(datap);
    hbtc_extrapolate(datap);

    fclose(file);
    return aapl->return_code;
}
#endif
#endif



static int serdes_eye_range_check(Aapl_t *aapl, const Avago_serdes_eye_data_t *datap,
        uint x_point, uint y_point, const char *field)
{
    if( y_point >= datap->ed_y_points )
    {
        aapl_fail(aapl, __func__, __LINE__,
            "Y coordinate (%u) beyond number of points in %u (%u).", field, y_point, datap->ed_y_points);
        return 0;
    }
    if( x_point >= datap->ed_x_points )
    {
        aapl_fail(aapl, __func__, __LINE__,
            "X coordinate (%u) beyond number of points in %u (%u).", field, x_point, datap->ed_x_points);
        return 0;
    }
    return 1;
}

/** @brief    Accessor function to retrieve one error count from
 **           Avago_serdes_eye_data_t, which must contain non-null ed_errorsp field.
 ** @details  (If linking from C, use AVAGO_EYE_ERRORS_GET() macro instead for
 **           possibly better performance.)
 ** @return   Error count at this coordinate; -2 means X/Y error.
 ** @see      avago_serdes_eye_bits_get(), avago_serdes_eye_grad_get(), avago_serdes_eye_qval_get().
 **/
bigint avago_serdes_eye_errors_get(
    Aapl_t *aapl,                           /**< Pointer to Aapl_t structure. */
    const Avago_serdes_eye_data_t *datap,   /**< Eye data pointer. */
    uint x_point,                           /**< X (phase) coordinate. */
    uint y_point)                           /**< Y (DAC) coordinate. */
{
    if( !serdes_eye_range_check(aapl,datap,x_point,y_point,"ed_errorsp") )
        return -2;
    return AVAGO_EYE_ERRORS_GET(*datap, x_point, y_point);
}

/** @brief    Accessor function to retrieve one bit (RX dwell) count from
 **           Avago_serdes_eye_data_t, which must contain non-null ed_bitsp.
 ** @details  If linking from C, use AVAGO_EYE_BITS_GET() macro instead for
 **           possibly better performance.
 ** @return   Bit (dwell) count at this coordinate; 0 means no data yet
 **           at this point; -2 means X/Y error.
 ** @see      avago_serdes_eye_errors_get().
 **/
bigint avago_serdes_eye_bits_get(
    Aapl_t *aapl,                           /**< Pointer to Aapl_t structure. */
    const Avago_serdes_eye_data_t *datap,   /**< Eye data pointer. */
    uint x_point,                           /**< X (phase) coordinate. */
    uint y_point)                           /**< Y (DAC) coordinate. */
{
    if( !serdes_eye_range_check(aapl,datap,x_point,y_point,"ed_bitsp") )
        return -2;
    return AVAGO_EYE_BITS_GET(*datap, x_point, y_point);
}

/** @brief    Accessor function to retrieve gradient for one bit from
 **           Avago_serdes_eye_data_t, which must contain non-null ed_gradp.
 **           Note also that the gradient is only calculated for x and y > 0.
 ** @details  If linking from C, use AVAGO_EYE_GRAD_GET() macro instead for
 **           possibly better performance.
 ** @return   Gradient value at this coordinate; -2 means X/Y range error.
 ** @see      avago_serdes_eye_errors_get(), avago_serdes_eye_bits_get().
 **/
float avago_serdes_eye_grad_get(
    Aapl_t *aapl,                           /**< Pointer to Aapl_t structure. */
    const Avago_serdes_eye_data_t *datap,   /**< Eye data pointer. */
    uint x_point,                           /**< X (phase) coordinate. */
    uint y_point)                           /**< Y (DAC) coordinate. */
{
    if( !serdes_eye_range_check(aapl,datap,x_point,y_point,"ed_gradp") )
        return -2;
    return AVAGO_EYE_GRAD_GET(*datap, x_point, y_point);
}

/** @brief    Accessor function to retrieve Q value for one bit from
 **           Avago_serdes_eye_data_t, which must contain non-null ed_qvalp.
 ** @details  If linking from C, use AVAGO_EYE_QVAL_GET() macro instead for
 **           possibly better performance.
 ** @return   Q value at this coordinate; -100 means X/Y range error.
 ** @see      avago_serdes_eye_errors_get(), avago_serdes_eye_bits_get().
 **/
float avago_serdes_eye_qval_get(
    Aapl_t *aapl,                           /**< Pointer to Aapl_t structure. */
    const Avago_serdes_eye_data_t *datap,   /**< Eye data pointer. */
     int x_point,                           /**< X (phase) coordinate. */
    uint y_point)                           /**< Y (DAC) coordinate. */
{
    if( x_point >= -3 && x_point < 0 && y_point < AAPL_ARRAY_LENGTH(datap->ed_mission_errors) )
    {
        bigint errors = get_errs_column(datap, x_point)[y_point];
        bigint bits   = get_bits_column(datap, x_point)[y_point];
        double BER = avago_calc_BER(errors, bits, 0.5);
        return avago_qfuncinv(BER);
    }

    if( aapl && !serdes_eye_range_check(aapl,datap,x_point,y_point,"ed_qvalp") )
        return -100;
    return AVAGO_EYE_QVAL_GET(*datap, x_point, y_point);
}

/** @} */

#endif
