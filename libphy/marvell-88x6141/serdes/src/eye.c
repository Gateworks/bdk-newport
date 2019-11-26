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


/** @file
 ** @brief  Functions for eye capture.
 ** @defgroup Eye Eye Capture Functions
 ** @{
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#define MEAN_EYE_FORCE_READ



#if AAPL_ENABLE_EYE_MEASUREMENT

#define ADJUST_CM4_PHASE_CENTER 1

#define SBM_INT             0x2F
#define EYE_READ_CAP        0x0000
#define EYE_READ_ADDR       0x0001
#define EYE_READ_START      0x0002
#define EYE_READ_POINTS     0x0003
#define EYE_READ_STEP       0x0004
#define EYE_READ_RESOLUTION 0x0006
#define EYE_READ_OPTIONS    0x0007
#define EYE_READ_CENTER     0x0008
#define EYE_READ_ROW_COL    0x000d
#define EYE_READ_PHASE      0x0026
#define EYE_SET_ADDR        0x1000
#define EYE_SET_START       0x2000
#define EYE_SET_POINTS      0x3000
#define EYE_SET_STEP        0x4000
#define EYE_SET_RESOLUTION  0x6000
#define EYE_SET_OPTIONS     0x7000
#define EYE_SET_THRESH      0x9000
#define EYE_GATHER_ROW      0xa000
#define EYE_GATHER_COLUMN   0xb000
#define EYE_GATHER_MISSION  0xc000

#define EQS(str1,str2) (0==strcmp(str1,str2))
#define AAPL_LOG_PRINT4 if((esp->aapl->debug & 0xf) >= AVAGO_DEBUG4) aapl_log_printf
#define AAPL_LOG_PRINT3 if((esp->aapl->debug & 0xf) >= AVAGO_DEBUG3) aapl_log_printf
#define AAPL_LOG_PRINT2 if((esp->aapl->debug & 0xf) >= AVAGO_DEBUG2) aapl_log_printf
#define AVAGO_EYE_SBM_DWELL_MAX_BITS (bigint)1e8

#define DEF_TRANS_DENSITY           (0.50000F)
#define DEF_DC_BALANCE              (0.50000F)

#define DEF_TRANS_DENSITY_M4        (0.09375F)
#define DEF_TRANS_DENSITY_M4_MSB    (DEF_TRANS_DENSITY_M4 * 4.0F / 3.0F)
#define DEF_DC_BALANCE_M4           (0.06250F)

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
/** @brief  Converts Avago_serdes_eye_type_t value into a display string.
 ** @return Returns the display string.
 **/
const char *aapl_eye_type_to_str(Avago_serdes_eye_type_t value)
{
    Aapl_conv_table_t *table = eye_type_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts name string to an Avago_serdes_eye_type_t variable.
 ** @return Returns TRUE on success, FALSE on error.
 **/
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

    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Size: %u x %u\n", datap->ed_x_points, datap->ed_y_points);

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

    memset((void *) datap->ed_mission_errors,  0, sizeof(datap->ed_mission_errors ));
    memset((void *) datap->ed_mission_bits,    0, sizeof(datap->ed_mission_bits   ));

    datap->ed_errorsp  = errorsp;
    datap->ed_gradp    = gradp;
    datap->ed_qvalp    = qvalp;
    datap->ed_bitsp    = bitsp;

    return 0;
}
/** @endcond */

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
    configp->ec_dc_balance       = 0.0;
    configp->ec_trans_density    = 0.0;
    configp->ec_avdd             = 0.0;
    configp->ec_x_auto_scale     = TRUE;
    configp->ec_y_auto_scale     = TRUE;
    configp->ec_x_shift          = 0;
    configp->ec_gather_mean      = FALSE;
    configp->ec_mean_threshold   = 0;
    configp->ec_no_sbm           = FALSE;


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
Avago_serdes_eye_data_t *avago_serdes_eye_data_construct(Aapl_t *aapl)
{
    int i;
    size_t bytes = sizeof(Avago_serdes_eye_data_t);
    Avago_serdes_eye_data_t *datap = (Avago_serdes_eye_data_t *) aapl_malloc(aapl, bytes, __func__);

    if( 0 == datap )
        return NULL;

    memset(datap, 0, bytes);
    for( i = 0; i < AAPL_ARRAY_LENGTH(datap->ed_hbtc); i++ )
        datap->ed_hbtc[i].data_row = AAPL_MAX_DAC_RANGE;
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
    if( datap->ed_phase_center_log )
        aapl_free(aapl,datap->ed_phase_center_log,"ed_phase_center_log");
    if( datap->ed_comment )
        aapl_free(aapl,datap->ed_comment,"ed_comment");

    aapl_free(aapl,datap,__func__);
}

static const bigint *get_bits_column(const Avago_serdes_eye_data_t *datap, int column)
{
    if( column < 0 && column >= -AAPL_ARRAY_LENGTH(datap->ed_mission_errors) )
        return datap->ed_mission_bits[-1-column];
    return &AVAGO_EYE_BITS_GET(*datap, column, 0);
}
static const bigint *get_errs_column(const Avago_serdes_eye_data_t *datap, int column)
{
    if( column < 0 && column >= -AAPL_ARRAY_LENGTH(datap->ed_mission_errors) )
        return datap->ed_mission_errors[-1-column];
    return &AVAGO_EYE_ERRORS_GET(*datap, column, 0);
}

/** @cond INTERNAL */

typedef struct
{
    Aapl_t                          *aapl;
    uint                             addr;
    const Avago_serdes_eye_config_t *configp;
    Avago_serdes_eye_data_t         *datap;
    uint                             phase_mult;

    int                              curr_clock_is_test;
    Avago_serdes_rx_cmp_mode_t       cmp_mode;
    int                              threshold;
    bigint                           real_dwell;
    bigint                           curr_dwell;
    int                              dwell_scale;
    BOOL                             sbm_eye_gather;
    BOOL                             enable_not_errors;
    BOOL                             default_gather;


    Avago_serdes_rx_cmp_mode_t       orig_cmp_mode;
    Avago_serdes_rx_cmp_data_t       orig_cmp_data;
    uint                             dfe_resume_status;
    uint                             timeout_count;
    Avago_serdes_rx_clock_t          data_clock;
    BOOL                             pd_pi;

    BOOL                             gather_reverse;
} Eye_state_t;

typedef struct
{
    int which;
    int entries;
    int eye[2];
    int v_offset[2];
    int h_index[2];
    int h_delay[2];
} Gather_info_t;

static void init_gather_info(Eye_state_t *esp, int which, Gather_info_t *gather_info)
{
    gather_info->entries = 1;
    gather_info->which = which;
    gather_info->v_offset[0] = 0;
    gather_info->h_index[0] = -1;
    gather_info->eye[0] = -1;

    if( !esp->default_gather )
        return;

    switch( aapl_get_ip_type(esp->aapl, esp->addr) )
    {
    case AVAGO_M4:
        if( avago_serdes_get_rx_line_encoding(esp->aapl, esp->addr) )
        {
            gather_info->h_delay[0] = esp->datap->delay[which];
            gather_info->h_index[0] = 12 - (which&1);
            gather_info->eye[0] = which;
        }
        else
        {
            gather_info->eye[0] = 6;
        }
        break;

    default:
    case AVAGO_SERDES:

        break;
    }
    AAPL_LOG_PRINT4(esp->aapl, AVAGO_DEBUG4, __func__, __LINE__, "which=%d; entries=%d; eye=%d,%d; v_offset=%d,%d; h_index=%d,%d; h_delay=%d,%d.\n",
                                gather_info->which, gather_info->entries,
                                gather_info->eye[0], gather_info->eye[1],
                                gather_info->v_offset[0], gather_info->v_offset[1],
                                gather_info->h_index[0], gather_info->h_index[1],
                                gather_info->h_delay[0], gather_info->h_delay[1]);
}

/** @endcond */

/** @brief   Determines the appropriate default AVDD value for this eye gather.
 ** @return  Returns the default AVDD in volts.
 **/
float avago_serdes_eye_get_default_avdd(Aapl_t *aapl, uint addr)
{
    float avdd = 1.0;
    int sdrev = aapl_get_sdrev(aapl, addr);
    switch( sdrev )
    {
    case AAPL_SDREV_OM4:    avdd = 1.2; break;
    case AAPL_SDREV_CM4:
    case AAPL_SDREV_CM4_16: avdd = 1.1; break;
    default:
    case AAPL_SDREV_HVD6:
    case AAPL_SDREV_D6:     avdd = 1.0; break;
    case AAPL_SDREV_16:     avdd = 0.9; break;
    case AAPL_SDREV_P1:
        if( aapl_get_process_id(aapl,addr) == AVAGO_PROCESS_F ) avdd = 0.9;
        else                                                  avdd = 0.8;
        break;
    }
    return avdd;
}
/** @brief  Calculates the DAC scaling.
 ** @return Returns milliVolts per DAC step.
 **/
static float eye_get_dac_scale(Eye_state_t *esp)
{
    if( aapl_get_ip_type(esp->aapl, esp->addr) == AVAGO_M4
        && aapl_get_process_id(esp->aapl, esp->addr) == AVAGO_PROCESS_B
        && aapl_get_ip_rev(esp->aapl, esp->addr) > 0x0a )
    {
        if( avago_serdes_mem_rd(esp->aapl, esp->addr, AVAGO_ESB, 0xb1) & 1 )
            return 1454.545454 * esp->datap->ed_avdd / esp->datap->ed_y_resolution;
        return  800 * esp->datap->ed_avdd / esp->datap->ed_y_resolution;
    }
    return 1000 * esp->datap->ed_avdd / esp->datap->ed_y_resolution;
}


/** @brief   Sets the error timer and updates the internal state accordingly.
 ** @details If the internal state already matches the request, does nothing.
 ** @return  On success, returns 0.
 ** @return  On error, decrements aapl->return_code and returns -1.
 **/
static int eye_set_error_timer(Eye_state_t *esp, bigint new_dwell)
{
    int ret;
    bigint real_dwell = new_dwell * esp->dwell_scale;


    if( real_dwell == esp->real_dwell )
        return 0;

    ret = avago_serdes_set_error_timer(esp->aapl, esp->addr, real_dwell);
    if( ret == 0 )
    {
        esp->real_dwell = real_dwell;
        esp->curr_dwell = new_dwell;
    }
    return ret;
}


static void eye_select(Eye_state_t *esp, int selection)
{
    if( selection >= 0 )
    {
        int compare_reg = aapl_get_ip_type(esp->aapl,esp->addr) == AVAGO_P1 ? 0xe1 : 0x17;
        int data = avago_serdes_mem_rd(esp->aapl, esp->addr, AVAGO_LSB, compare_reg) & 0x0770;
        switch( selection )
        {
        case 0: data |= 0x9803; break;
        case 1: data |= 0x5803; break;
        case 2: data |= 0x9003; break;
        case 3: data |= 0x5003; break;
        case 4: data |= 0x8803; break;
        case 5: data |= 0x4803; break;
        case 6: data |= 0x0003; break;
        case 7: data |= 0x2003; break;
        case 8: data |= 0x2803; break;
        default: return;
        }
        avago_spico_int(esp->aapl, esp->addr, 3, data);
    }
}



/** @brief   Sets the compare mode and updates the internal state to match.
 ** @details If the internal state already matches the request, does nothing.
 **/
static BOOL eye_set_compare_mode(Eye_state_t *esp, Avago_serdes_rx_cmp_mode_t cmp_mode)
{
    if( cmp_mode == esp->cmp_mode )
        return TRUE;

    if( esp->datap->ed_cmp_mode == AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN )
    {
        avago_serdes_set_rx_cmp_data(esp->aapl, esp->addr, esp->orig_cmp_data);
        avago_spico_int(esp->aapl, esp->addr, 0x02, 0x0220 | (esp->orig_cmp_data & 7));
    }
    if( 0 == avago_serdes_set_rx_cmp_mode(esp->aapl, esp->addr, cmp_mode) )
    {
        esp->cmp_mode = cmp_mode;
        return TRUE;
    }
    return FALSE;
}

static int sbm_eye_get_point(Eye_state_t *esp, BOOL mission, int x, int y);

static float find_edge(Eye_state_t *esp, int inner_dac, int outer_dac, int threshold)
{
    int inc = (outer_dac - inner_dac) / 2;
    int above_count = threshold, below_count = threshold;

    float interpolated_dac;
    while( inc != 0 && !aapl_get_async_cancel_flag(esp->aapl) )
    {
        int dac = inner_dac + inc;
        int errors;
            errors = sbm_eye_get_point(esp, TRUE, 0, dac - (esp->datap->ed_y_resolution-1) / 2);
        inc /= 2;
        if( errors > threshold )
        {
            above_count = errors;
            outer_dac = dac;
            dac -= inc;
        }
        else
        {
            below_count = errors;
            inner_dac = dac;
            dac += inc;
        }
    }
    interpolated_dac = inner_dac + (float)1.0 * (outer_dac - inner_dac) * (threshold - below_count) / (above_count - below_count);

    return interpolated_dac;
}


/** @brief   Sets ed_x_min, ed_x_max in datap for new center.
 ** datap inputs: ed_x_points, ed_x_step.
 **/
static void set_x_center(Avago_serdes_eye_data_t *datap, int center)
{
    int offset = datap->ed_x_UI * datap->ed_x_resolution / 2 * datap->ed_x_step;
    datap->ed_x_min = center - offset;
    datap->ed_x_max = center + offset;
    if( !datap->ed_phase_table )
        datap->ed_phase_center = center;
}

/** @brief    Updates x values for new resolution.
 ** @details Sets datap fields ed_x_resolution, ed_x_points, ed_x_step, ed_x_min, ed_x_max.
 ** Implicit inputs: esp->phase_mult, datap->ed_x_UI
 **/
static void set_x_resolution(Eye_state_t *esp, uint request_res)
{
#   define MIN_RESOLUTION 8
    Avago_serdes_eye_data_t *datap = esp->datap;
    uint full_res = 64 * esp->phase_mult;
    uint x_res = full_res;
    while( x_res > request_res && x_res > MIN_RESOLUTION )
        x_res /= 2;
    datap->ed_x_resolution = x_res;
    datap->ed_x_points     = x_res * datap->ed_x_UI + 1;
    datap->ed_x_step       = full_res / x_res;
    set_x_center(datap, (datap->ed_x_min + datap->ed_x_max) / 2);
}

static void set_y_points(Avago_serdes_eye_data_t *datap, uint y_points)
{
    datap->ed_y_points = y_points;
    datap->ed_y_min = datap->ed_y_center_point - (datap->ed_y_points - 1) / 2 * datap->ed_y_step;
}

static BOOL initialize_eye_data(Eye_state_t *esp)
{
    int aapl_return_code = esp->aapl->return_code;
    const Avago_serdes_eye_config_t *configp = esp->configp;
    Avago_serdes_eye_data_t *datap = esp->datap;
    Aapl_t *aapl = esp->aapl;
    uint addr = esp->addr;

    if( esp->phase_mult == 0 )
        esp->phase_mult = configp->ec_eye_type == AVAGO_EYE_HEIGHT ? 1 : avago_serdes_get_phase_multiplier(aapl, addr);

    if( datap->ed_y_resolution == 0 )
        datap->ed_y_resolution = avago_serdes_get_dac_range(aapl, addr);

    datap->ed_eye_type        = configp->ec_eye_type;
    datap->ed_cmp_mode        = configp->ec_cmp_mode;
    datap->ed_min_dwell_bits  = MAX(AVAGO_EYE_MIN_DWELL_BITS, configp->ec_min_dwell_bits);
    datap->ed_max_dwell_bits  = MAX(datap->ed_min_dwell_bits, configp->ec_max_dwell_bits);
    if( esp->sbm_eye_gather )
        datap->ed_min_dwell_bits  = MIN(datap->ed_min_dwell_bits, AVAGO_EYE_SBM_DWELL_MAX_BITS);
    else
        datap->ed_min_dwell_bits  = MIN(datap->ed_min_dwell_bits, AVAGO_EYE_ONE_DWELL_MAX_BITS);
    datap->ed_max_dwell_bits  = MAX(datap->ed_min_dwell_bits, datap->ed_max_dwell_bits);
    datap->ed_fast_dynamic    = configp->ec_fast_dynamic;
    datap->ed_error_threshold = configp->ec_error_threshold;
    datap->ed_mean_threshold  = configp->ec_mean_threshold;
    datap->ed_dc_balance      = configp->ec_dc_balance;
    datap->ed_trans_density   = configp->ec_trans_density;
    datap->ed_avdd            = configp->ec_avdd == 0.0 ? avago_serdes_eye_get_default_avdd(aapl, addr) : configp->ec_avdd;
    datap->ed_dac_scale       = eye_get_dac_scale(esp);

    datap->ed_x_shift         = configp->ec_x_shift;
    if( datap->ed_eye_type == AVAGO_EYE_HEIGHT )
    {
        datap->ed_x_resolution = 1;
        datap->ed_x_points     = 1;
        datap->ed_x_step       = 1;
        datap->ed_x_UI         = 1;
        set_x_center(datap, 0);
    }
    else
    {
        datap->ed_x_UI = configp->ec_x_UI <= 1 ? 1 : configp->ec_x_UI;
        set_x_resolution(esp, configp->ec_x_resolution);
    }

    if( esp->datap->ed_cmp_mode == AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN )
        esp->orig_cmp_data = avago_serdes_get_rx_cmp_data(aapl,addr);

    datap->ed_y_center_point = configp->ec_y_center_point == 0 || configp->ec_y_center_point >= datap->ed_y_resolution ? (datap->ed_y_resolution-1) / 2 : configp->ec_y_center_point;
    datap->ed_y_step         = configp->ec_y_step_size > 0 ? configp->ec_y_step_size : 1;

    if( datap->ed_eye_type == AVAGO_EYE_WIDTH )
    {
        if( avago_serdes_get_rx_line_encoding(aapl, addr) )
            set_y_points(esp->datap, datap->ed_y_resolution);
        else
            set_y_points(esp->datap, 1);
    }
    else
    {
        uint y_points = datap->ed_y_center_point / datap->ed_y_step + (datap->ed_y_resolution - datap->ed_y_center_point - 1) / datap->ed_y_step + 1;
        if( configp->ec_y_points < y_points )
            y_points = configp->ec_y_points;
        set_y_points(esp->datap, y_points);
    }


    datap->ed_y_mission_points = datap->ed_y_resolution;
    datap->ed_y_mission_step   = 1;
    datap->ed_y_mission_min    = 0;
    datap->eye_count = 1;

    if( datap->ed_hardware_log) aapl_free(aapl,datap->ed_hardware_log,"ed_hw_log");
    datap->ed_hardware_log = avago_hardware_info_format(aapl, addr);

    if( avago_serdes_get_rx_line_encoding(aapl, addr) )
    {
        uint index;
        for( index = 0; index < 6; index++ )
            datap->inputs[index] = (short) avago_serdes_hal_get(aapl, addr, 0xf, index);

        datap->delay[0] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT, 10);
        datap->delay[1] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT,  9);
        datap->delay[2] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT,  8);
        datap->delay[3] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT,  7);
        datap->delay[4] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT,  6);
        datap->delay[5] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT,  5);
        datap->delay[6] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT, 12);
        datap->delay[7] = (short) avago_serdes_hal_get(aapl, addr, AVAGO_HAL_RXCLK_SELECT, 11);
        datap->eye_count = 6;
    }
    else
        datap->eye_count = 1;


    return aapl->return_code == aapl_return_code;
}


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

    esp->curr_clock_is_test = TRUE;
    esp->orig_cmp_mode =
    esp->cmp_mode = avago_serdes_get_rx_cmp_mode(aapl, addr);
    esp->threshold  = configp->ec_error_threshold;
    esp->real_dwell = 0;
    esp->curr_dwell = 0;
    esp->default_gather = TRUE;

    {
        Avago_serdes_rx_clocks_t clocks;
        avago_serdes_rx_clock_read(aapl, addr, &clocks);
        esp->data_clock = clocks.data;
        esp->curr_clock_is_test = clocks.test == AVAGO_SERDES_RX_CLOCK_R;
        esp->pd_pi = TRUE;
        if( clocks.data == AVAGO_SERDES_RX_CLOCK_R || clocks.edge == AVAGO_SERDES_RX_CLOCK_R || clocks.dfe == AVAGO_SERDES_RX_CLOCK_R )
            esp->pd_pi = FALSE;
    }
    initialize_eye_data(esp);

    esp->pd_pi &= avago_serdes_enable_low_power_mode(aapl, addr, FALSE);

    esp->dwell_scale = 1;
    esp->sbm_eye_gather = TRUE;

    if( datap->ed_dc_balance == 0.0 )
        datap->ed_dc_balance = avago_serdes_get_rx_line_encoding(aapl, addr) ? DEF_DC_BALANCE_M4 : DEF_DC_BALANCE;

    if( datap->ed_trans_density == 0.0 )
        datap->ed_trans_density = avago_serdes_get_rx_line_encoding(aapl, addr) ? DEF_TRANS_DENSITY_M4 : DEF_TRANS_DENSITY;

    return TRUE;
}

static void restore_serdes_state(Eye_state_t *esp)
{
    Aapl_t *aapl = esp->aapl;
    uint    addr = esp->addr;


    if( esp->datap->ed_cmp_mode == AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN )
        avago_serdes_set_rx_cmp_data(aapl, addr, esp->orig_cmp_data);

    avago_serdes_set_rx_cmp_mode(aapl, addr, esp->orig_cmp_mode);
    avago_serdes_get_errors(aapl, addr, AVAGO_LSB, TRUE);

    if( esp->pd_pi )
        avago_serdes_enable_low_power_mode(aapl, addr, TRUE);
    avago_serdes_power_down_phase_interpolator(aapl, addr);

    avago_serdes_dfe_resume(aapl, addr, esp->dfe_resume_status);
}

static BOOL gather_separate_even_odd(const Avago_serdes_eye_data_t *datap)
{
    return datap->eye_count == 6;
}

/** @brief Returns middle of eye containing x_index.
 ** @details If separate even/odd gathering, then returns even or odd center.  Else overall center.
 **/
static int get_eye_middle_x_index(const Avago_serdes_eye_data_t *datap, BOOL odd_gather)
{
    return datap->ed_x_points * (gather_separate_even_odd(datap) ? odd_gather ? 3 : 1 : 2) / 4;
}

/** @brief Calculates the gradient for a point which has
 **        valid self, south and west data.
 **        Skip points which are out of range or don't yet have data.
 **/
static void calc_gradient_bit(Avago_serdes_eye_data_t *datap, uint x, uint y)
{
    uint x_points = gather_separate_even_odd(datap) ? datap->ed_x_points/2 : datap->ed_x_points;
    if( x > 0 && y > 0 && x < datap->ed_x_points && y < datap->ed_y_points && x != x_points )
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
            grad = (float)(2 * sqrt((double)(en*en + ew*ew)) / bits);
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
            double BER = avago_calc_BER(errs, bits, datap->ed_dc_balance);
            qinv = (float)avago_qfuncinv(BER);
        }
        AVAGO_EYE_QVAL_SET(*datap, x, y, qinv);
    }
}

static int mod(int val, uint mod)
{
    if( val >= 0 ) return val % mod;
    return mod - (-val % mod);
}

/** @brief Converts x coordinate into milliUI.
 ** @return Returns milli-UI offset of x relative to the eye center.
 **/
static double mui_from_index(const Avago_serdes_eye_data_t *datap, int x)
{
    int x_center_index = get_eye_middle_x_index(datap, x >= (int)datap->ed_x_points/2);
    int val = x - x_center_index;
    double mUI = (double) val * 1000.0 / datap->ed_x_resolution;
    uint x_full_res = datap->ed_x_step * datap->ed_x_resolution;

#if 1
    if( datap->ed_phase_table_len == 2 * x_full_res )
    {
        int phase = datap->ed_x_min + x * datap->ed_x_step + datap->ed_x_sbm_center;

        int data_center = mod(datap->ed_x_min + x_center_index * datap->ed_x_step + datap->ed_x_sbm_center, 2 * x_full_res);
        int align = mod((int)datap->ed_phase_center - data_center + 64, 2 * x_full_res) / 128 * 128;

        int mod_phase = mod(phase + align, 2 * x_full_res);
        int mod_center = mod(data_center + align, 2 * x_full_res);
        double mui_correction = datap->ed_phase_table[mod_phase];

        double center_shift = ((double)mod_center - datap->ed_phase_center) * 1000.0 / x_full_res;
        double adjusted_mUI = mUI + mui_correction + center_shift;

        mUI = adjusted_mUI;
    }
#endif
    return mUI;
}

/** @brief Converts y coordinate into milliVolts.
 ** @return Returns milliVolt offset of y relative to the eye center.
 **/
static double mv_from_index(
    const Avago_serdes_eye_data_t *datap, /**< [in] Eye data to act upon. */
    uint y_points,                        /**< [in] Array size, used only for finding the midpoint. */
    uint step,                            /**< [in] Array spacing in dac steps. */
    int y)                                /**< [in] Coordinate to convert to mV. */
{
    int y_mid = (y_points-1) / 2;
    double val = datap->ed_dac_scale * ((y - y_mid) * (int)step);
    return val;
}

static double get_BER(const Avago_serdes_eye_data_t *datap, int x, int y, float density)
{
    const bigint *bits = get_bits_column(datap, x);
    const bigint *errs = get_errs_column(datap, x);
    return avago_calc_BER(errs[y], bits[y], density);
}

static void find_center_ui_edges(
    const Avago_serdes_eye_data_t *datap, /**< [in,out] Eye data to act upon. */
    uint data_row,                        /**< [in] Row to analyze */
    BOOL odd_gather,                      /**< [in] Hint. */
    uint *left,                           /**< [out] */
    uint *right)                          /**< [out] Range: [left..right] */
{
    if( datap->ed_x_points == 1 ) { *left = *right = 0; return; }
    if( datap->ed_x_points == 2 ) { *left = *right = odd_gather ? 1 : 0; return; }

    *left = (datap->ed_x_UI-1) * datap->ed_x_resolution / 2;
    if( odd_gather && gather_separate_even_odd(datap) )
        *left += datap->ed_x_points / 2;
    *right = *left + datap->ed_x_resolution;
    if( AVAGO_EYE_BITS_GET(*datap,*left,data_row) <= 0 ||
        AVAGO_EYE_BITS_GET(*datap,*right,data_row) <= 0 )
    {
        *left = *right = datap->ed_x_points / 2;
    }
}

static void find_horizontal_extrapolation_points(
    const Avago_serdes_eye_data_t *datap, /**< [in,out] Eye data to act upon. */
    uint data_row,                        /**< [in] Which data row index to analyze */
    BOOL odd_gather,                      /**< [in] Which eye to act upon. */
    uint *left,                           /**< [out] */
    uint *innerLeft,                      /**< [out] Range: [left..innerLeft] */
    uint *innerRight,                     /**< [out] */
    uint *right)                          /**< [out] Range: [innerRight..right] */
{
    int x_mid = get_eye_middle_x_index(datap, odd_gather);
    int x;
    bigint min_errors;

    if( x_mid < 2 )
    {
        *left = *innerLeft = *innerRight = *right = x_mid;
        return;
    }
    find_center_ui_edges(datap, data_row, odd_gather, left, right);

    *innerLeft = *left+3;
    min_errors = 0x7fffffff;
    for( x = *left+3; x < x_mid; x++ )
    {
        if( AVAGO_EYE_BITS_GET(*datap,x,data_row) > 0 )
        {
            bigint errors = AVAGO_EYE_ERRORS_GET(*datap,x,data_row);
            if( errors > datap->ed_error_threshold )
                *innerLeft = x;
            else
                break;
        }
    }

    *innerRight = *right;
    min_errors = 0x7fffffff;
    for( x = *right-3; x > x_mid; x-- )
    {
        if( AVAGO_EYE_BITS_GET(*datap,x,data_row) > 0 )
        {
            bigint errors = AVAGO_EYE_ERRORS_GET(*datap,x,data_row);
            if( errors < min_errors )
            {
                min_errors = errors;
                if( errors > datap->ed_error_threshold )
                    *innerRight = x;
            }
        }
    }
}

static void find_vertical_extrapolation_points(
    const Avago_serdes_eye_data_t *datap, /**< [in,out] Eye data to act upon. */
    int column,                           /**< [in] Which data column index to analyze */
    int which,                            /**< [in] Which eye opening, 0=lower, 1=middle, 2=upper */
    uint *lower,                          /**< [out] */
    uint *innerLower,                     /**< [out] Range: [lower..innerLower] */
    uint *innerUpper,                     /**< [out] */
    uint *upper)                          /**< [out] Range: [innerUpper..upper] */
{
    uint y, y_mid;
    const bigint *bits = get_bits_column(datap, column);
    const bigint *errs = get_errs_column(datap, column);

    *lower = 0;
    *upper = (column < 0 ? datap->ed_y_mission_points : datap->ed_y_points) - 1;
    y_mid = (*upper + 1) / 2;

    if( column < 0 )
    {
        double ber_min = 1.0;
        for( y = *lower; y < *upper; y++ )
        {
            double ber;
            if( bits[y] <= 0 )
                continue;

            ber = 1.0 * errs[y] / bits[y];
            if( ber < ber_min )
            {
                y_mid = y + 1;
                ber_min = ber;
                if( errs[y] == 0 )
                    break;
            }
        }
    }
    else if( gather_separate_even_odd(datap) )
    {
        int odd = (column >= (int)datap->ed_x_points / 2) ? 1 : 0;
        if( which == 0 )
        {
            y_mid = datap->ed_hbtc[odd].data_row;
            *lower = 0;
            *upper = (y_mid + datap->ed_hbtc[2+odd].data_row) / 2;
        }
        else if( which == 1 )
        {
            y_mid = datap->ed_hbtc[2+odd].data_row;
            *lower = (y_mid + datap->ed_hbtc[0+odd].data_row) / 2;
            *upper = (y_mid + datap->ed_hbtc[4+odd].data_row) / 2;
        }
        else if( which == 2 )
        {
            y_mid = datap->ed_hbtc[4+odd].data_row;
            *lower = (y_mid + datap->ed_hbtc[2+odd].data_row) / 2;
            *upper = datap->ed_y_points-1;
        }
    }

    *innerLower = *lower;
    for( y = y_mid - 1; y_mid > 0 && y-- > *lower;         )
    {
        if( bits[y] > 0 && errs[y] > datap->ed_error_threshold )
        {
            *innerLower = y;
            break;
        }
    }

    *innerUpper = *upper;
    for( y = y_mid + 1; y_mid > 0 && y <= *upper; y++ )
    {
        if( bits[y] > 0 && errs[y] > datap->ed_error_threshold )
        {
            *innerUpper = y;
            break;
        }
    }
}

#define LSR_POINTS (64)

/** @brief   Calculates the left and right mean where Q == 0.
 ** @details Updates BTC values in results.
 **          Must call after get_horizontal_least_sqr(), which sets left and right index values.
 **/
static void get_horizontal_means(
    const Avago_serdes_eye_data_t *datap, /**< [in] Eye data to act upon. */
    uint data_row,                        /**< [in] Row in datap to act upon. */
    BOOL odd_gather,                      /**< [in] Which eye to act upon. */
    float trans_density,                  /**< [in] Transition density to use for the calculations. */
    Avago_serdes_eye_hbtc_t *results)     /**< [out] Where partial results are stored. */
{
    Avago_least_sqr_point point, prev = {0.0, 0.0};
    int x;
    int half_width = datap->ed_x_UI * datap->ed_x_resolution / 2;
    int center_index = get_eye_middle_x_index(datap, odd_gather);
    int left_edge_index = center_index - half_width;
    int right_edge_index = center_index + half_width;

    results->left_mean = mui_from_index(datap, center_index - datap->ed_x_resolution / 2);
    for( x = results->left_index; x >= left_edge_index; x-- )
    {
        point.x = mui_from_index(datap, x);
        point.y = avago_qfuncinv(get_BER(datap, x, data_row, trans_density));
        if( point.y < 0.0 )
        {
            results->left_mean = (float)avago_interpolate(&prev,&point);
            break;
        }
        prev.x = point.x;
        prev.y = point.y;
    }

    results->right_mean = mui_from_index(datap, center_index + datap->ed_x_resolution / 2);
    for( x = results->right_index; x <= right_edge_index; x++ )
    {
        point.x = mui_from_index(datap, x);
        point.y = avago_qfuncinv(get_BER(datap, x, data_row, trans_density));
        if( point.y < 0.0 )
        {
            results->right_mean = (float)avago_interpolate(&prev,&point);
            break;
        }
        prev.x = point.x;
        prev.y = point.y;
    }
}

/** @brief   Calculates least squares info for left and right sides of data row;
 **          stores left and right index and point values into results.
 ** @details Also sets data_row field of results.
 **          Does not update BTC info in results.
 **/
static void get_horizontal_least_sqr(
    const Avago_serdes_eye_data_t *datap, /**< [in] Eye data to act upon. */
    uint data_row,                        /**< [in] Row in datap to act upon. */
    BOOL odd_gather,                      /**< [in] Which eye to act upon. */
    float trans_density,                  /**< [in] Transition density to use for the calculations. */
    Avago_serdes_eye_hbtc_t *results,     /**< [out] Where partial results are stored. */
    Avago_least_sqr_results *left_lsr,    /**< [out] Left side least squares fit. */
    Avago_least_sqr_results *right_lsr)   /**< [out] Right side least squares fit. */
{
    uint i, x, left, innerLeft, innerRight, right;
    Avago_least_sqr_point leftPoints[LSR_POINTS];
    Avago_least_sqr_point rightPoints[LSR_POINTS];
    double best_Rsqr = 0.0;
    uint  best_count = 0;

    find_horizontal_extrapolation_points(datap, data_row, odd_gather, &left, &innerLeft, &innerRight, &right);
    for( i = 0, x = innerLeft+1; i < AAPL_ARRAY_LENGTH(leftPoints) && x-- > left;     )
    {
        leftPoints[i].x = mui_from_index(datap,x);
        leftPoints[i].y = avago_qfuncinv(get_BER(datap,x,data_row,trans_density));

        if( ++i >= 3 )
        {
            avago_least_sqr(leftPoints, i, left_lsr);
            if( left_lsr->Rsqr >= best_Rsqr - 0.005 )
            {
                best_count = i;
                if( left_lsr->Rsqr > best_Rsqr )
                    best_Rsqr = left_lsr->Rsqr;
            }
        }
    }
    avago_least_sqr(leftPoints, best_count, left_lsr);
    results->left_index = innerLeft;
    results->left_points = best_count;

    best_Rsqr = 0.0;
    best_count = 0;
    for( i = 0, x = innerRight; i < AAPL_ARRAY_LENGTH(rightPoints) && x <= right; x++ )
    {
        rightPoints[i].x = mui_from_index(datap,x);
        rightPoints[i].y = avago_qfuncinv(get_BER(datap,x,data_row,trans_density));

        if( ++i >= 3 )
        {
            avago_least_sqr(rightPoints, i, right_lsr);
            if( right_lsr->Rsqr >= best_Rsqr - 0.005 )
            {
                best_count = i;
                if( right_lsr->Rsqr >= best_Rsqr )
                    best_Rsqr = right_lsr->Rsqr;
            }
        }
    }
    avago_least_sqr(rightPoints, best_count, right_lsr);
    results->right_index = innerRight;
    results->right_points = best_count;
    results->data_row = data_row;

#if 0
    printf("h points(row=%u) = %u, %u, %u, %u\n", data_row, left, innerLeft, innerRight, right);
    printf("left  Q = %7fx + %7f\n", left_lsr->slope * 1000, left_lsr->y_intercept);
    printf("right Q = %7fx + %7f\n", right_lsr->slope * 1000, right_lsr->y_intercept);
#endif

#if 0
    printf("left_mUI,left_Q\n");
    for( uint i = 0; i < results->left_points; i++ )
        printf("%.3f,%f\n",leftPoints[i].x,leftPoints[i].y);
    printf("right_mUI,right_Q\n");
    for( uint i = 0; i < results->right_points; i++ )
        printf("%.3f,%f\n",rightPoints[i].x,rightPoints[i].y);
#endif
#if 0
    printf("Row = %u\n",data_row);
    printf("%u left edge points: ", results->left_points);
    for( uint i = 0; i < results->left_points; i++ )
        printf(" (%.3f,%f)",leftPoints[i].x,leftPoints[i].y);
    printf("\n");
    printf("%u right edge points: ", results->right_points);
    for( uint i = 0; i < results->right_points; i++ )
        printf(" (%.3f,%f)",rightPoints[i].x,rightPoints[i].y);
    printf("\n");
#endif
}

/** @brief   Calculates least squares info for bottom and top eye edges in column;
 **          stores top and bottom index and point values into results.
 ** @details Also sets data_column field of results.
 **          Does not update BTC info in results.
 **
 **  For each column, extracts top and bottom points above threshold and in bounds.
 **  Linear fits them to find the slope and intercept in Q space for both
 **  bottom and top.
 **/
static void get_vertical_least_sqr(
    const Avago_serdes_eye_data_t *datap, /**< [in] Eye data to act upon. */
    int which,                            /**< [in] Which PAM4 eye to analyze (0=lower, 1=middle, 2=upper) */
    int column,                           /**< [in] Column in datap to act upon. */
    Avago_serdes_eye_vbtc_t *results,     /**< [out] Where partial results are stored. */
    Avago_least_sqr_results *lower_lsr,   /**< [out] Bottom side least squares fit. */
    Avago_least_sqr_results *upper_lsr)   /**< [out] Top side least squares fit. */
{
    uint i, y, lower, inner_lower, inner_upper, upper;
    Avago_least_sqr_point lowerPoints[LSR_POINTS];
    Avago_least_sqr_point upperPoints[LSR_POINTS];
    int points = column < 0 ? datap->ed_y_mission_points : datap->ed_y_points;
    int step   = column < 0 ? datap->ed_y_mission_step   : datap->ed_y_step;
    double best_Rsqr = 0.0;
    uint  best_count = 0;

    find_vertical_extrapolation_points(datap, column, which, &lower, &inner_lower, &inner_upper, &upper);
    for( i = 0, y = inner_lower; i < AAPL_ARRAY_LENGTH(lowerPoints) && y > lower; y-- )
    {
        double BER = get_BER(datap, column, y, datap->ed_dc_balance);
        if( BER >= 0.16 ) break;

        lowerPoints[i].x = mv_from_index(datap, points, step, y);
        lowerPoints[i].y = avago_qfuncinv(BER);

        if( ++i >= 5 )
        {
            avago_least_sqr(lowerPoints, i, lower_lsr);
            if( lower_lsr->Rsqr >= best_Rsqr )
            {
                best_count = i;
                best_Rsqr = lower_lsr->Rsqr;
            }
        }
    }
    if( best_count == 0 )
        best_count = i;
    avago_least_sqr(lowerPoints, best_count, lower_lsr);
    results->bottom_index = inner_lower;
    results->bottom_points = best_count;

    best_Rsqr = 0.0;
    best_count = 0;

    for( i = 0, y = inner_upper; i < AAPL_ARRAY_LENGTH(upperPoints) && y <= upper; y++ )
    {
        double BER = get_BER(datap, column, y, datap->ed_dc_balance);
        if( BER >= 0.16 ) break;

        upperPoints[i].x = mv_from_index(datap, points, step, y);
        upperPoints[i].y = avago_qfuncinv(BER);

        if( ++i >= 5 )
        {
            avago_least_sqr(upperPoints, i, upper_lsr);
            if( upper_lsr->Rsqr >= best_Rsqr )
            {
                best_count = i;
                best_Rsqr = upper_lsr->Rsqr;
            }
        }
    }
    if( best_count == 0 )
        best_count = i;
    avago_least_sqr(upperPoints, best_count, upper_lsr);
    results->top_index = inner_upper;
    results->top_points = best_count;

#if 0
    printf("v points(col=%d) = %u, %u, %u, %u\n", column, lower, inner_lower, inner_upper, upper);
    printf("upperQ(%d) = %6.2fx + %6.2f mV/Q\n", column, 1.0 / upper_lsr->slope, upper_lsr->y_intercept);
    printf("lowerQ(%d) = %6.2fx + %6.2f mV/Q\n", column, 1.0 / lower_lsr->slope, lower_lsr->y_intercept);
    printf("column = %d, top/bottom_points = %u, %u\n", column, results->top_points, results->bottom_points);
#endif
#if 0
    printf("Top edge points (column = %d): ", column);
    for( i = 0; i < results->top_points; i++ )
        printf("(%f,%5.3f)",upperPoints[i].x,upperPoints[i].y);
    printf("\n");
    printf("Bottom edge points: ");
    for( i = 0; i < results->bottom_points; i++ )
        printf("(%f,%5.3f)",lowerPoints[i].x,lowerPoints[i].y);
    printf("\n");
#endif
}

static void extrapolate_horizontal_qvals(
    Avago_serdes_eye_data_t *datap) /**< [in,out] Eye data to act upon. */
{
    uint data_row;
    if( datap->ed_x_points < 8 ) return;
    for( data_row = 0; data_row < datap->ed_y_points; data_row++ )
    {
        uint x;
        Avago_least_sqr_results left_lsr, right_lsr;
        Avago_serdes_eye_hbtc_t results;
        float trans_density = datap->ed_trans_density;
        int odd_gather;

        if( datap->eye_count == 6 )
        {
            uint lower_center_index = datap->ed_hbtc[0].data_row;
            uint mid_center_index   = datap->ed_hbtc[2].data_row;
            uint upper_center_index = datap->ed_hbtc[4].data_row;
            uint upper_third = (mid_center_index + upper_center_index) / 2;
            uint lower_third = (mid_center_index + lower_center_index) / 2;
            if( data_row < upper_third && data_row > lower_third && fabsf(trans_density - DEF_TRANS_DENSITY_M4) < 0.01F )
                trans_density = DEF_TRANS_DENSITY_M4_MSB;
        }

        for( odd_gather = (gather_separate_even_odd(datap) ? 1 : 0); odd_gather >= 0; odd_gather-- )
        {
            get_horizontal_least_sqr(datap, data_row, odd_gather, trans_density, &results, &left_lsr, &right_lsr);
            for( x = results.left_index+1; x < results.right_index; x++ )
            {
                if( AVAGO_EYE_ERRORS_GET(*datap,x,data_row) == 0 )
                {
                    double x_val = mui_from_index(datap,x);
                    double qval_left  =  left_lsr.slope * x_val + left_lsr.y_intercept;
                    double qval_right = right_lsr.slope * x_val + right_lsr.y_intercept;
                    double qval       = MIN(qval_left, qval_right);
                    AVAGO_EYE_QVAL_SET(*datap, x, data_row, qval);
                }
            }
        }
    }
    #if 0
    for( data_row = 0; data_row < datap->ed_y_points; data_row++ )
    {
        uint x;
        for( x = 0; x < datap->ed_x_points; x++ )
             if( AVAGO_EYE_QVAL_GET(*datap, x, data_row) == 0.0 )
                 printf("H extrapolation failed at %u, %u, qval = %f\n", x, data_row, AVAGO_EYE_QVAL_GET(*datap, x, data_row));
    }
    #endif
}

static void extrapolate_vertical_qvals(
    Avago_serdes_eye_data_t *datap) /**< [in,out] Eye data to act upon. */
{
    int which;

    for( which = 0; which < datap->eye_count; which++ )
    {
        uint left, right, column;

        find_center_ui_edges(datap, 0, which & 1, &left, &right);
        for( column = left; column <= right; column++ )
        {
            uint y;
            Avago_serdes_eye_vbtc_t results;
            Avago_least_sqr_results lower_lsr, upper_lsr;

            get_vertical_least_sqr(datap, which/2, column, &results, &lower_lsr, &upper_lsr);
            for( y = results.bottom_index+1; y < results.top_index; y++ )
            {
                if( AVAGO_EYE_ERRORS_GET(*datap,column,y) == 0 )
                {
                    double x_val = mv_from_index(datap, datap->ed_y_points, datap->ed_y_step, y);
                    double qval_lower = lower_lsr.slope * x_val + lower_lsr.y_intercept;
                    double qval_upper = upper_lsr.slope * x_val + upper_lsr.y_intercept;
                    double qval_v     = MIN(qval_lower, qval_upper);
                    double qval_h     = AVAGO_EYE_QVAL_GET(*datap, column, y);
#if 1
                    double qval       = avago_qfuncinv((avago_qfunc(qval_v) + avago_qfunc(qval_h))/2.0);
#elif 1
                    double qval = MIN(qval_h, qval_v);
#else
                    double qval       = qval_v;
#endif
                    AVAGO_EYE_QVAL_SET(*datap, column, y, qval);
                }
            }
        }
    }
    /**< Save eye center Q value: */
    {
        int i;
        int combined_lsb_count = 0, combined_btc_count = 0;

        datap->ed_combined_btc_ber = datap->ed_combined_lsb_ber = 0.0;

        for( i = 0; i < datap->eye_count; i++ )
        {
            if( datap->ed_hbtc[i].data_row < datap->ed_y_points )
            {
                int center_x_index = get_eye_middle_x_index(datap, i & 1);
                float tmp_qval = AVAGO_EYE_QVAL_GET(*datap, center_x_index, datap->ed_hbtc[i].data_row);
                double ber = avago_qfunc(tmp_qval);

                datap->ed_combined_btc_ber += ber;
                combined_btc_count ++;

                if( (datap->eye_count == 6 && (i == 2 || i == 3)) ||
                    (datap->eye_count == 3 && i == 1) )
                {
                    datap->ed_combined_btc_ber += ber;
                    combined_btc_count ++;
                }
                else
                {
                    datap->ed_combined_lsb_ber += ber;
                    combined_lsb_count ++;
                }

            }
        }
        if( combined_btc_count > 0 ) datap->ed_combined_btc_ber /= combined_btc_count;
        if( combined_lsb_count > 0 ) datap->ed_combined_lsb_ber /= combined_lsb_count;
    }
    datap->ed_combined_btc_qval = avago_qfuncinv(datap->ed_combined_btc_ber);
    datap->ed_combined_lsb_qval = avago_qfuncinv(datap->ed_combined_lsb_ber);
    if( datap->ed_combined_btc_qval > AVAGO_Q_CEILING )
        datap->ed_combined_btc_qval = AVAGO_Q_CEILING;
    if( datap->ed_combined_lsb_qval > AVAGO_Q_CEILING )
        datap->ed_combined_lsb_qval = AVAGO_Q_CEILING;
}

static void serdes_eye_calc_qval(
    Aapl_t *aapl,                   /**< [in] */
    Avago_serdes_eye_data_t *datap) /**< [in,out] Eye data to act upon. */
{
    uint x, y;

    for( x = 0; x < datap->ed_x_points; x++ )
        for( y = 0; y < datap->ed_y_points; y++ )
            calc_qval_bit(datap, x, y);

    extrapolate_horizontal_qvals(datap);
    extrapolate_vertical_qvals(datap);

    if( (aapl->debug & 0xf) != AVAGO_DEBUG3 )
        return;

    for( y = datap->ed_y_points; y > 0;  )
    {
        y--;
        for( x = 0; x < datap->ed_x_points; x++ )
        {
            if( x == 0 )
                aapl_log_printf(aapl, AVAGO_DEBUG3, 0, 0, "%2u: %4.1f", y, AVAGO_EYE_QVAL_GET(*datap, x, y));
            else if( x == datap->ed_x_points / 2 )
                aapl_log_printf(aapl, AVAGO_DEBUG3, 0, 0, ",|%4.1f|", AVAGO_EYE_QVAL_GET(*datap, x, y));
            else
                aapl_log_printf(aapl, AVAGO_DEBUG3, 0, 0, ",%4.1f", AVAGO_EYE_QVAL_GET(*datap, x, y));
        }
        aapl_log_printf(aapl, AVAGO_INFO, 0, 0, "\n");
    }
}

/** @brief   Updates the bits to dwell for a given eye point.
 ** @details Want to dwell enough to push errors above threshold without
 **          wasting time getting it much above it.
 **          Also caps total dwell at max_dwell bits.
 **/
static BOOL update_dwell(Eye_state_t *esp, int x, uint y)
{
    bigint bits   = get_bits_column(esp->datap, x)[y];
    bigint errors = get_errs_column(esp->datap, x)[y];

    bigint new_dwell = esp->curr_dwell;
    if( new_dwell > bits )
        new_dwell = bits;
    if( errors <= esp->threshold / 100 )
        new_dwell *= 200;
    else if( errors <= esp->threshold / 20 )
        new_dwell *= 40;
    else if( errors <= esp->threshold / 5 )
        new_dwell *= 10;
    else if( errors <= esp->threshold * 2 / 3 )
        new_dwell *= 2;

    new_dwell = MAX(new_dwell, esp->datap->ed_min_dwell_bits);
    new_dwell = MIN(new_dwell, esp->datap->ed_max_dwell_bits - bits);
    new_dwell = ((new_dwell+19) / 20) * 20;


    if( esp->sbm_eye_gather )
        new_dwell = MIN(new_dwell, AVAGO_EYE_SBM_DWELL_MAX_BITS);
    else
        new_dwell = MIN(new_dwell, AVAGO_EYE_ONE_DWELL_MAX_BITS);

    if( new_dwell == 0 )
    {
        esp->curr_dwell = 0;
        return TRUE;
    }
    if( eye_set_error_timer(esp, new_dwell) < 0 )
        return FALSE;
    aapl_log_printf(esp->aapl, AVAGO_DEBUG3, __func__, __LINE__, "update_dwell: x,y = %3d,%3u, errors,bits = %s,%s, new dwell = %s\n",
        x,y,
        aapl_bigint_to_str(errors),
        aapl_bigint_to_str(bits),
        aapl_bigint_to_str(esp->curr_dwell));
    return TRUE;
}

static BOOL sbm_eye_set_options(Eye_state_t *esp)
{
    Aapl_t *aapl = esp->aapl;
    uint addr = esp->addr;
    uint sbm_addr = avago_make_sbus_master_addr(addr);
    int options = 2;
    int return_code = aapl->return_code;

    if( !esp->sbm_eye_gather )
        return TRUE;

    if( aapl_get_ip_type(aapl, addr) == AVAGO_SERDES )
    {
        options = (esp->datap->ed_cmp_mode == AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN) ? 1 : 0;
    }

    if( aapl_get_interrupt_rev(aapl, addr, 0x25) == 2 )
    {
        options |= 0x0010;
        if( aapl_get_sdrev(aapl, addr) == AAPL_SDREV_PON )
            options |= 0x0018;
        if( (options & 2) == 0 && aapl_get_process_id(aapl, addr) == AVAGO_PROCESS_E )
            options |= (1<<6);
    }

    if( esp->enable_not_errors )
        options |= (1<<5);

    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_OPTIONS    | (0x7ff & options));

    return return_code == aapl->return_code;
}

/** @brief Converts FW floating point error count into integer. */
static uint error_float_to_int(uint e)
{
    if( e == 0xffff ) return 4000000000U;
    if( e & 0xe000 )
        e = (0x1000 | (e & 0x0fff)) << (((e >> 12) & 0x0f) - 1);
    else
        e &= 0x1fff;
    return e;
}

/** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
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
    uint last_read = 0, rep_count = 0;

    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Points = %u, current_dwell = %s\n", points, aapl_bigint_to_str(esp->curr_dwell));
    avago_sbus_wr(aapl, sbc_addr, 0x11, read_index);
    avago_sbus_wr(aapl, sbc_addr, 0x12, 0);
    avago_spico_int(aapl, sbm_addr, SBM_INT, int_data);

    for( index = 0; index < stop_index;     )
    {
        unsigned char reg_addrs[] = { 0x12, 0x13, 0x16 };
        uint avail = 0, err_reg[3];
        uint loop_count = 0;
        const uint max_loop_count = 1000;
        uint errs[4];

        avago_sbus_wr(aapl, sbc_addr, 0x11, read_index);
        while( loop_count++ < max_loop_count )
        {
            avago_sbus_rd_array(aapl, sbc_addr, 3, reg_addrs, err_reg);
            avail = err_reg[0];
            if( avail >= read_index )
                break;
            if( loop_count >= 300 )
                ms_sleep(1);
        }
        if( loop_count > 1 && aapl->debug & 0x100 ) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "loop_count = %u\n", loop_count);
        if( loop_count >= max_loop_count )
        {
            aapl_fail(aapl, __func__,__LINE__,"Timeout waiting for SBM eye data.\n");
            return FALSE;
        }

        if( (aapl->debug & 0x100) && (aapl->debug & 0xf) > AVAGO_DEBUG2 )
        {
            uint av = avail * 4;
            BOOL do_log = FALSE;
            if( last_read == av - index )
            {
                do_log = av >= stop_index;
                rep_count++;
            }
            else
            {
                do_log = rep_count > 0;
            }
            if( do_log )
                aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "int_data = %x, read %2u entries x %3u = %3u\n", int_data, last_read, rep_count, last_read * rep_count);
            if( last_read != av - index ) rep_count = 1;
            last_read = av - index;
        }
        esp->timeout_count += err_reg[1]>>16 == 0xffff;
        if( bits ) bits[index] += esp->curr_dwell;
        errs[0] = error_float_to_int(err_reg[1] >> 16);
        errors[index] += errs[0];
        index += step;
        if( index < stop_index )
        {
            esp->timeout_count += (err_reg[1] & 0xffff) == 0xffff;
            if( bits ) bits[index] += esp->curr_dwell;
            errs[1] = error_float_to_int(err_reg[1]);
            errors[index] += errs[1];
            index += step;
            if( index < stop_index )
            {
                esp->timeout_count += err_reg[2]>>16 == 0xffff;
                if( bits ) bits[index] += esp->curr_dwell;
                errs[2] = error_float_to_int(err_reg[2] >> 16);
                errors[index] += errs[2];
                index += step;
                if( index < stop_index )
                {
                    esp->timeout_count += (err_reg[2] & 0xffff) == 0xffff;
                    if( bits ) bits[index] += esp->curr_dwell;
                    errs[3] = error_float_to_int(err_reg[2]);
                    errors[index] += errs[3];
                    index += step;
                }
            }
        }

        while( avail*4*step > index && index < stop_index )
        {
            if( bits ) bits[index] += esp->curr_dwell;
            errors[index] += errs[index%4];
            index += step;
        }

        read_index = avail + 1;
    }
    return return_code == aapl->return_code;
}


static int sbm_adjust_dac(Eye_state_t *esp, int dac)
{
    if( aapl_get_ip_type(esp->aapl, esp->addr) == AVAGO_SERDES )
    {
        if( !aapl_check_firmware_rev(esp->aapl, esp->addr, 0, 0, FALSE, 1, 0x1065) )
            dac -= 2;
    }
    return dac;
}
/** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL sbm_set_dac_start(Eye_state_t *esp, const char *func, int line, int dac)
{
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);
    dac = sbm_adjust_dac(esp, dac);
    return avago_spico_int_check(esp->aapl, func, line, sbm_addr, SBM_INT, EYE_SET_START  | (dac & 0x7ff));
}

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
    uint fw_build = aapl_get_firmware_build(aapl, addr);
    bigint xx;
    if( !esp->sbm_eye_gather )
        return TRUE;

    AAPL_LOG_PRINT2(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SerDes FW: 0x%04X_%04X  SBM FW: 0x%04X_%04X\n",
        aapl_get_firmware_rev(aapl,addr),
        fw_build,
        aapl_get_firmware_rev(aapl,sbm_addr),
        aapl_get_firmware_build(aapl,sbm_addr));

    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_ADDR       | (0x0ff & addr));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_RESOLUTION | (0x7ff & esp->phase_mult));
    sbm_eye_set_options(esp);

    sbm_set_dac_start(esp, __func__, __LINE__, 0);
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | (1 & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP   | (1 & 0x7ff));
    eye_set_compare_mode(esp, AVAGO_SERDES_RX_CMP_MODE_XOR);
    sbm_eye_gather_data(esp, EYE_GATHER_MISSION, &xx, &xx, 1, 1);
    esp->datap->ed_x_sbm_center = (short)avago_spico_int(aapl, sbm_addr, SBM_INT, EYE_READ_CENTER);
    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBM center: %hd\n", esp->datap->ed_x_sbm_center);

#   define AAPL_CENTER_PHASE_BUFLEN 40
    if( esp->datap->ed_phase_center_log ) aapl_free(aapl,esp->datap->ed_phase_center_log,"ed_phase_center_log");
    esp->datap->ed_phase_center_log = (char *)aapl_malloc(aapl, AAPL_CENTER_PHASE_BUFLEN, "sbm phase center");
    if( esp->datap->ed_phase_center_log )
        snprintf(esp->datap->ed_phase_center_log, AAPL_CENTER_PHASE_BUFLEN, "SBM center at phase %d", esp->datap->ed_x_sbm_center);

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

    if( aapl_get_async_cancel_flag(aapl) ) return FALSE;

    if( column < 0 )
    {
        y_points  = esp->datap->ed_y_mission_points;
        y_step  = esp->datap->ed_y_mission_step;
        y_start = esp->datap->ed_y_mission_min;
    }
    else
    {
        y_points  = esp->datap->ed_y_points;
        y_step  = esp->datap->ed_y_step;
        y_start  = esp->datap->ed_y_min;
    }
    y_start -= (esp->datap->ed_y_resolution - 1 ) / 2;
    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Points = %u; Start = %d, Step = %u, Column = %d\n", y_points, y_start, y_step, column);

    sbm_set_dac_start(esp, __func__, __LINE__, y_start);
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | (y_points & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP   | (y_step   & 0x7ff));
    return return_code == aapl->return_code;
}

/** @brief Configures SBM for a gather of a single point.
 **        Note: The row and column are specified later.
 **/
static BOOL sbm_eye_setup_point(Eye_state_t *esp)
{
    if( esp->sbm_eye_gather )
    {
        Aapl_t *aapl = esp->aapl;
        uint sbm_addr = avago_make_sbus_master_addr(esp->addr);
        aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "\n");
        return !aapl_get_async_cancel_flag(esp->aapl)
            && avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | 1);
    }
    return TRUE;
}

static int get_phase_for_x_index(Eye_state_t *esp, int x_index, int which)
{
    Avago_serdes_eye_data_t *datap = esp->datap;

    if( gather_separate_even_odd(datap) && x_index >= (int)datap->ed_x_points / 2 )
        x_index -= datap->ed_x_points / 2;

    return datap->ed_x_center[which] + (x_index - datap->ed_x_UI * datap->ed_x_resolution / 2) * datap->ed_x_step;
}

static int get_dac_for_y_index(const Avago_serdes_eye_data_t *datap, int y_index, BOOL mission)
{
    if( mission )
        return datap->ed_y_mission_min + y_index * datap->ed_y_mission_step;
    else
        return datap->ed_y_min + y_index * datap->ed_y_step;
}

static BOOL sbm_eye_gather_column(
    Eye_state_t *esp,
    int x_index,
    uint y_begin,
    uint y_end)
{
    BOOL result;
    uint int_data;
    bigint *bits = (bigint *)get_bits_column(esp->datap, x_index) + y_begin;
    bigint *errs = (bigint *)get_errs_column(esp->datap, x_index) + y_begin;

    if( x_index < 0 )
    {
        int_data = EYE_GATHER_MISSION;
    }
    else
    {
        int sbm_phase = get_phase_for_x_index(esp, x_index, 0) - esp->datap->ed_x_sbm_center;
        int_data = EYE_GATHER_COLUMN | (sbm_phase & 0x7ff);
    }
    aapl_log_printf(esp->aapl, AVAGO_DEBUG2, __func__, __LINE__, "Column = %d, points = %u, int_data = 0x%x\n", x_index, y_end - y_begin, int_data);
    result = sbm_eye_gather_data(esp, int_data, bits, errs, 1, y_end - y_begin);
    if (esp->datap->ed_gather_mean && esp->datap->ed_mean_direction == 1)
    {
        uint i, count, total;

        total = y_end - y_begin;
        count = total/2;
        for (i = 0; i < count; i++)
        {
            bigint temp;
            temp = bits[i]; bits[i] = bits[total-1-i]; bits[total-1-i] = temp;
            temp = errs[i]; errs[i] = errs[total-1-i]; errs[total-1-i] = temp;
        }
    }
    return result;
}

static BOOL sbm_eye_gather_nrz(Eye_state_t *esp)
{
    BOOL status = sbm_eye_setup_column(esp, 0);
    uint i;
    uint sbm_addr = 0;
    int options = 0;

    if( esp->datap->ed_gather_mean )
    {
        int value;
        bigint thresh;
        sbm_addr = avago_make_sbus_master_addr(esp->addr);
        options = avago_spico_int(esp->aapl, sbm_addr, SBM_INT, EYE_READ_OPTIONS);

        if (esp->datap->ed_mean_direction > 0)
        {
            options &= (0x0003 << 9);
            options |= (esp->datap->ed_mean_direction << 9);
        }

        avago_spico_int_check(esp->aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_OPTIONS | (0x7ff & (options | 0x0100)));

#if 0
        thresh = (esp->datap->ed_min_dwell_bits) / 4;

        if( aapl_get_ip_type(esp->aapl, esp->addr) == AVAGO_M4 )
        {
            if( avago_serdes_get_tx_line_encoding(esp->aapl, esp->addr) )
            {
                thresh = (esp->datap->ed_min_dwell_bits) / 16;
            }
        }
#endif

        thresh = (esp->datap->ed_min_dwell_bits) / 16;

        if (esp->datap->ed_mean_threshold > 0)
            thresh = esp->datap->ed_mean_threshold;

        aapl_log_printf(esp->aapl,AVAGO_INFO,0,0,"Mean Eye Threshold: %s\n", aapl_bigint_to_str(thresh));

        value = thresh & 0x000000ff;
        avago_spico_int_check(esp->aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_THRESH  | ((0<<8) | value));
        value = (thresh & 0x0000ff00) >>  8;
        avago_spico_int_check(esp->aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_THRESH  | ((1<<8) | value));
        value = (thresh & 0x00ff0000) >> 16;
        avago_spico_int_check(esp->aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_THRESH  | ((2<<8) | value));
        value = (thresh & 0xff000000) >> 24;
        avago_spico_int_check(esp->aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_THRESH  | ((3<<8) | value));
    }

    for( i = 0; status && i < esp->datap->ed_x_points; i++ )
    {
        status &= sbm_eye_gather_column(esp, i, 0, esp->datap->ed_y_points);
        if( aapl_get_async_cancel_flag(esp->aapl) ) return FALSE;
    }

    if( esp->datap->ed_gather_mean ) {
        avago_spico_int_check(esp->aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_OPTIONS | (0x7ff & options));
    }

    return status;
}

/** @brief   Gather column using configured dwell, data_qual and cmp_mode.
 ** @details Works OK on SBM/direct, Mission/Test
 **          NOTE: Does not do prev0/prev1 gathers.
 **          Set dwell, data_qual and cmp_mode before calling.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL gather_column_x(
    Eye_state_t *esp,
    BOOL mission,                        /**< Mission/phase clock */
    int phase,                           /**< Phase location of column */
    int dac_start,                       /**< First absolute DAC value for error reading */
    int dac_step,                        /**< Increment */
    int dac_end,                         /**< Just past last DAC value */
    bigint *errs,                        /**< Where to record error counts */
    bigint *bits)                        /**< Where to record bit counts */
{
    Aapl_t *aapl = esp->aapl;
    BOOL status = FALSE;

    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__,__LINE__, "mission %s; phase %d; dac {%d..%d..%d}, sbm_phase = %d, sbm_center = %d\n",
        aapl_bool_to_str(mission), phase, dac_start, dac_end, dac_step, phase, esp->datap->ed_x_sbm_center);


    {
        int col_len = (dac_end - dac_start) / dac_step;
        int sbm_phase = phase - esp->datap->ed_x_sbm_center;
        uint int_data = (mission ? EYE_GATHER_MISSION : (EYE_GATHER_COLUMN | (sbm_phase & 0x7ff)));
        uint sbm_addr = avago_make_sbus_master_addr(esp->addr);
        dac_start -= (esp->datap->ed_y_resolution - 1) / 2;
        sbm_set_dac_start(esp, __func__, __LINE__, dac_start);
        avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | (0x7ff & col_len));
        avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP   | (0x7ff & dac_step));
        sbm_eye_set_options(esp);
        status = sbm_eye_gather_data(esp, int_data, bits, errs, 1, col_len);
    }
    return status;
}

 /** @brief   Updates the test channel delay. */
 /** @details Caches value to avoid no-op writes. */
static void eye_set_delay(Eye_state_t *esp, int index, int delay)
{
    if( index == 11 )
    {
        if( delay == esp->datap->delay[7] )
            return;
        esp->datap->delay[7] = delay;
    }
    else if( index == 12 )
    {
        if( delay == esp->datap->delay[6] )
            return;
        esp->datap->delay[6] = delay;
    }
    else
        return;
    avago_serdes_hal_set(esp->aapl, esp->addr, AVAGO_HAL_RXCLK_SELECT, index, delay);
    avago_serdes_hal_func(esp->aapl, esp->addr, AVAGO_HAL_RXCLK_VERNIER_APPLY);
}


static uint find_m4_eye_center_offset(Eye_state_t *esp, int which)
{
    return ((short *)&esp->datap->inputs)[which];
}

static uint find_tune_row(Eye_state_t *esp, int which)
{
    int ret = find_m4_eye_center_offset(esp, which);
    int row = aapl_iround((double)ret / esp->datap->ed_y_step) + (esp->datap->ed_y_points-1) / 2;
    aapl_log_printf(esp->aapl, AVAGO_DEBUG2, __func__, __LINE__, "vertical eye_center[%d] = %4d, y index = %4d\n",which,ret,row);
    return row;
}



/** @brief   Gathers eye column.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_gather_column_x(
    Eye_state_t *esp,
    int phase,
    int which,
    int x_index,
    int y_begin,
    int y_end)
{
    BOOL status = TRUE;
    Gather_info_t gather_info;
    BOOL mission = x_index < 0;
    Avago_serdes_eye_data_t *datap = esp->datap;
    int i, gi_index;
    int dac_start = 0, dac_end = 0;
    int dac_step  = mission ? datap->ed_y_mission_step : datap->ed_y_step;
    bigint *bits = (bigint *)get_bits_column(datap, x_index);
    bigint *errs = (bigint *)get_errs_column(datap, x_index);

    init_gather_info(esp, which, &gather_info);

    for( i = 0; i < gather_info.entries; i++ )
    {
        while( (dac_start = get_dac_for_y_index(datap, y_begin, mission)) + gather_info.v_offset[i] < 0 )
            y_begin++;
        while( (dac_end = get_dac_for_y_index(datap, y_end-1, mission)) + gather_info.v_offset[i] >= (int)datap->ed_y_resolution )
            y_end--;
    }
    dac_end = get_dac_for_y_index(datap, y_end, mission);
    bits += y_begin;
    errs += y_begin;

    esp->gather_reverse = !esp->gather_reverse;
    for( gi_index = 0; gi_index < gather_info.entries && status; gi_index++ )
    {
        int i = esp->gather_reverse ? gather_info.entries - 1 - gi_index : gi_index;

        eye_select(esp, gather_info.eye[i]);

        if( gather_info.h_index[i] >= 0 )
            eye_set_delay(esp, gather_info.h_index[i], gather_info.h_delay[i]);

        status &= gather_column_x(esp, mission, phase, dac_start + gather_info.v_offset[i], dac_step, dac_end + gather_info.v_offset[i], errs, bits);
        bits = 0;
    }
    return status;
}

static void eye_get_pam4_y_levels(Eye_state_t *esp, BOOL gather_odd, int *y_level)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int odd = gather_odd?1:0;
    uint lower_center_index = datap->ed_hbtc[0+odd].data_row;
    uint mid_center_index   = datap->ed_hbtc[2+odd].data_row;
    uint upper_center_index = datap->ed_hbtc[4+odd].data_row;

    y_level[0] = 0;
    y_level[1] = MIN(datap->ed_y_points, (lower_center_index + mid_center_index) / 2);
    y_level[2] = MIN(datap->ed_y_points, (upper_center_index + mid_center_index) / 2);
    y_level[3] = datap->ed_y_points;
}

/** @brief   Gathers PAM4 non-mission column direct or through SBM.
 ** @details Used for default data qual full, height and size eye gathers.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_gather_pam4_column(Eye_state_t *esp, int x_index)
{
    int return_code = aapl_get_return_code(esp->aapl);
    Avago_serdes_eye_data_t *datap = esp->datap;
    BOOL status = TRUE;

    if( x_index < 0 )
    {
        status &= eye_gather_column_x(esp, 0, 0, -1, 0                       ,datap->ed_y_resolution/2  );
        status &= eye_gather_column_x(esp, 0, 1, -2, 0                       ,datap->ed_y_resolution/2  );
        status &= eye_gather_column_x(esp, 0, 2, -3, datap->ed_y_resolution/4,datap->ed_y_resolution*3/4);
        status &= eye_gather_column_x(esp, 0, 3, -4, datap->ed_y_resolution/4,datap->ed_y_resolution*3/4);
        status &= eye_gather_column_x(esp, 0, 4, -5, datap->ed_y_resolution/2,datap->ed_y_resolution    );
        status &= eye_gather_column_x(esp, 0, 5, -6, datap->ed_y_resolution/2,datap->ed_y_resolution    );
    }
    else
    {
        int e_index = x_index;
        int o_index = x_index + datap->ed_x_points / 2;

        int which;
        int phase[6];
        int y_level_e[4];
        int y_level_o[4];

        eye_get_pam4_y_levels(esp, FALSE, y_level_e);
        eye_get_pam4_y_levels(esp, TRUE,  y_level_o);

        for( which = 0; which < 6; which ++ )
            phase[which] = get_phase_for_x_index(esp, x_index, which);

        status &= eye_gather_column_x(esp, phase[0], 0, e_index, y_level_e[0], y_level_e[1]);
        status &= eye_gather_column_x(esp, phase[1], 1, o_index, y_level_o[0], y_level_o[1]);
        status &= eye_gather_column_x(esp, phase[2], 2, e_index, y_level_e[1], y_level_e[2]);
        status &= eye_gather_column_x(esp, phase[3], 3, o_index, y_level_o[1], y_level_o[2]);
        status &= eye_gather_column_x(esp, phase[4], 4, e_index, y_level_e[2], y_level_e[3]);
        status &= eye_gather_column_x(esp, phase[5], 5, o_index, y_level_o[2], y_level_o[3]);
    }
    return status && return_code == esp->aapl->return_code;
}

/** @brief   Gathers mission and all test PAM4 columns direct or through SBM.
 ** @details Use for default data qual full eye gather.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_gather_pam4(Eye_state_t *esp)
{
    BOOL status = eye_set_error_timer(esp, esp->curr_dwell) == 0;
    int x_points = esp->datap->ed_x_UI * esp->datap->ed_x_resolution + 1;
    int x_index;

    for( x_index = -1; x_index < x_points && status; x_index++ )
        status &= eye_gather_pam4_column(esp, x_index);

    return status;
}

/** @brief   Gathers NRZ column of data.
 ** @details Pass -1 to select the mission column.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_gather_nrz_column(Eye_state_t *esp, int x_index)
{
    uint points = (x_index < 0) ? esp->datap->ed_y_resolution : esp->datap->ed_y_points;
    int phase = get_phase_for_x_index(esp, x_index, 0);

    return eye_gather_column_x(esp, phase, 0, x_index, 0, points);
}

/** @brief   Gathers mission and all test NRZ columns direct or through SBM.
 ** @details Use for all non-PAM4 full eye gathers.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_gather_nrz(Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int x_index;
    BOOL status = TRUE;

    if( datap->ed_gather_mean )
        return sbm_eye_gather_nrz(esp);

    for( x_index = -1; x_index < (int)datap->ed_x_points; x_index++ )
        status &= eye_gather_nrz_column(esp, x_index);

    return status;
}

/** @brief   Gathers full eye.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL gather_full_eye(Eye_state_t *esp)
{
    if( esp->default_gather && avago_serdes_get_rx_line_encoding(esp->aapl, esp->addr) )
        return eye_gather_pam4(esp);

    return eye_gather_nrz(esp);
}

/** @brief   Performs initial pass eye height gather on center column.
 ** @details Gathers mission column.  If SIZE_VDUAL mode is selected, also gathers center test column.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL gather_eye_height(Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    BOOL status;

    if( esp->default_gather && avago_serdes_get_rx_line_encoding(esp->aapl, esp->addr) )
    {
        status = eye_gather_pam4_column(esp, -1);

        if( datap->ed_eye_type == AVAGO_EYE_SIZE_VDUAL && status )
        {
            int x_mid = get_eye_middle_x_index(datap, FALSE);
            status = eye_gather_pam4_column(esp, x_mid);
        }
        return status;
    }

    status = eye_gather_nrz_column(esp, -1);

    if( datap->ed_eye_type == AVAGO_EYE_SIZE_VDUAL && status )
    {
        int x_mid = datap->ed_x_points / 2;
        status = eye_gather_nrz_column(esp, x_mid);
    }
    return status;
}

/** @brief Configures SBM for a row eye gather. */
static BOOL sbm_eye_setup_row(Eye_state_t *esp, int which)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    Aapl_t *aapl = esp->aapl;
    int return_code = aapl->return_code;
    uint sbm_addr = avago_make_sbus_master_addr(esp->addr);

    uint x_points  = datap->ed_x_points;
    uint x_step  = datap->ed_x_step;
    int  x_start = get_phase_for_x_index(esp, 0, which) - datap->ed_x_sbm_center;

    aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "Columns: start = %d; total = %u; step = %u\n", x_start, x_points, x_step);

    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_START  | (x_start  & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS | (x_points & 0x7ff));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP   | (x_step   & 0x7ff));
    return return_code == aapl->return_code;
}

/** @brief   Gathers eye data for a row.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL gather_row_x(
    Eye_state_t *esp,
    int which,          /**< Which eye, used for center adjustments. */
    int dac,            /**< Absolute DAC value for row gathering. */
    bigint *errs,       /**< Where to record error counts */
    bigint *bits,       /**< Where to record bit counts */
    int array_step)     /**< array entries between elements */
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int points = datap->ed_x_points;
    int int_data;

    if( gather_separate_even_odd(datap) )
        points /= 2;


    dac -= (datap->ed_y_resolution - 1) / 2;
    int_data = EYE_GATHER_ROW | (sbm_adjust_dac(esp,dac) & 0x7ff);

    return sbm_eye_gather_data(esp, int_data, bits, errs, array_step, points);
}

/** @brief Gathers row at data array index for specified eye. */
static BOOL eye_gather_row(Eye_state_t *esp, int which, uint y_index)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int i;
    Gather_info_t gather_info;
    BOOL status = TRUE;
    int base_dac = get_dac_for_y_index(datap,y_index,FALSE);
    int row_points = datap->ed_x_UI * datap->ed_x_resolution + 1;
    int row_start = ((which & 1) && gather_separate_even_odd(datap)) ? row_points : 0;
    bigint *errs = (bigint *)&get_errs_column(datap, row_start)[y_index];
    bigint *bits = (bigint *)&get_bits_column(datap, row_start)[y_index];

    init_gather_info(esp, which, &gather_info);

    if( esp->sbm_eye_gather )
        status &= sbm_eye_setup_row(esp, which);

    for( i = 0; i < gather_info.entries && status; i++ )
    {
        int dac = base_dac + gather_info.v_offset[i];

        eye_select(esp, gather_info.eye[i]);

        if( gather_info.h_index[i] >= 0 )
            eye_set_delay(esp, gather_info.h_index[i], gather_info.h_delay[i]);

        status &= gather_row_x(esp, which, dac, errs, bits, datap->ed_y_points);
        bits = 0;
    }
    return status;
}

/** @brief   Performs initial pass eye width gather on HBTC row.
 ** @details Gathers the three eye center rows in PAM4 mode.
 ** @return  On success, returns TRUE.
 ** @return  On error, decrements aapl->return_code and returns FALSE.
 **/
static BOOL gather_eye_width(Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int which;
    BOOL status = TRUE;
    for( which = 0; which < datap->eye_count; which++ )
        status &= eye_gather_row(esp, which, datap->ed_hbtc[which].data_row);
    return status;
}


static void update_qval_and_gradient_for_point(Eye_state_t *esp, int column, uint y)
{
    Avago_serdes_eye_data_t *datap = esp->datap;

    calc_qval_bit(datap, column, y);

    calc_gradient_bit(datap, column, y);
    calc_gradient_bit(datap, column, y+1);
    calc_gradient_bit(datap, column+1, y);
}

/** @brief  Performs gather at the indicated point.
 ** Does not store results.
 ** @return On success, returns measured error count for point.
 ** @return On failure, decrements aapl->return_code and returns -1.
 **/
static int sbm_eye_get_point(
    Eye_state_t *esp, /**< Eye state info */
    BOOL mission,     /**< TRUE if mission column (sbm_phase ignored). */
    int sbm_phase,    /**< Column from which to gather (relative to eye-center). */
    int sbm_dac)      /**< Row from which to gather (relative to eye-center). */
{
    uint int_data;
    bigint bits = 0;
    bigint errors = 0;
    if( mission )
    {
        int_data = EYE_GATHER_MISSION;
        if( sbm_set_dac_start(esp, __func__, __LINE__, sbm_dac)
            && sbm_eye_gather_data(esp, int_data, &bits, &errors, 1, 1) )
            return (int)errors;
    }
    else
    {
        int_data = EYE_GATHER_COLUMN | (sbm_phase & 0x7ff);
        if( sbm_set_dac_start(esp, __func__, __LINE__, sbm_dac)
            && sbm_eye_gather_data(esp, int_data, &bits, &errors, 1, 1) )
            return (int)errors;
    }
    return -1;
}

/** @brief   Performs dynamic dwell at a point and saves results.
 ** @details Note: The caller decides which points to dwell upon.
 ** @return  Returns TRUE if dynamic dwell done successfully.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell_bit(
    Eye_state_t *esp,
    int phase,
    int x_index,
    uint y_index,
    Gather_info_t *gather_info)
{
    BOOL status = TRUE;
    BOOL update = FALSE;
    Avago_serdes_eye_data_t *datap = esp->datap;
    bigint *bits = (bigint *)get_bits_column(datap, x_index);
    bigint *errs = (bigint *)get_errs_column(datap, x_index);
    int threshold = esp->threshold;
    int sbm_phase = phase - esp->datap->ed_x_sbm_center;
    int base_dac = get_dac_for_y_index(datap, y_index, x_index < 0);


    if( esp->configp->ec_fast_dynamic == 2 ) esp->threshold = 1000;


    while( errs[y_index] <= esp->threshold &&
           errs[y_index] >= 0 &&
           bits[y_index] < datap->ed_max_dwell_bits )
    {
        int gi_index, errors = 0;

        if( aapl_get_async_cancel_flag(esp->aapl) ) { status = FALSE; break; }

        if( ! update_dwell(esp, x_index, y_index) ) { status = FALSE; break; }

        esp->gather_reverse = !esp->gather_reverse;
        for( gi_index = 0; gi_index < gather_info->entries && status; gi_index++ )
        {
            int i = esp->gather_reverse ? gather_info->entries - 1 - gi_index : gi_index;
            int dac = base_dac + gather_info->v_offset[i];

            eye_select(esp, gather_info->eye[i]);

            if( gather_info->h_index[i] >= 0 )
                eye_set_delay(esp, gather_info->h_index[i], gather_info->h_delay[i]);

                errors += sbm_eye_get_point(esp, x_index < 0, sbm_phase, dac -= (datap->ed_y_resolution-1)/2);

            if( errors != 0 && esp->aapl->debug >= AVAGO_DEBUG4 )
                aapl_log_printf(esp->aapl, AVAGO_DEBUG4, 0, 0, "%d: i=%d: [%d,%d (%d,%d)] dwell = %s; %d errors from eye %d\n", __LINE__, i, x_index, y_index, sbm_phase, dac, aapl_bigint_to_str(esp->curr_dwell), errors, gather_info->eye[i]);
        }
        errs[y_index] += errors;
        bits[y_index] += esp->curr_dwell;

        update = TRUE;

        aapl_log_printf(esp->aapl, AVAGO_DEBUG3, __func__, __LINE__, "dynamic: errors = %s, bits = %s\n",
            aapl_bigint_to_str(errs[y_index]),
            aapl_bigint_to_str(bits[y_index]));
    }
    esp->threshold = threshold;

    if( update )
        update_qval_and_gradient_for_point(esp, x_index, y_index);

    return status;
}

/** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell_column(
    Eye_state_t *esp,
    int which,
    int x_index,
    int y_begin,
    int y_end)
{
    int neighbor_threshold = esp->configp->ec_fast_dynamic ? esp->threshold : 0;
    int y_index;
    bigint *errs = (bigint *)get_errs_column(esp->datap, x_index);
    bigint *bits = (bigint *)get_bits_column(esp->datap, x_index);
    Gather_info_t gather_info;
    int phase = get_phase_for_x_index(esp, x_index, which);

    init_gather_info(esp, which, &gather_info);

    aapl_log_printf(esp->aapl, AVAGO_DEBUG2, __func__, __LINE__, "x_index = %d, y_range = [%u..%u], neighbor_threshold = %d\n",x_index,y_begin,y_end, neighbor_threshold);

    for( y_index = y_begin; y_index < y_end-1; y_index++ )
    {
        if( errs[y_index] > neighbor_threshold )
        {
            if( !eye_dynamic_dwell_bit(esp, phase, x_index, y_index+1, &gather_info) )
                return FALSE;
        }
        else if( bits[y_index] > 0 )
        {
            aapl_log_printf(esp->aapl, AVAGO_DEBUG2, __func__, __LINE__, "STOP SCANNING column %d at %d\n", x_index, y_index);
            break;
        }
    }

    for( y_index = y_end-1; y_index > y_begin; y_index-- )
    {
        if( errs[y_index] > neighbor_threshold )
        {
            if( !eye_dynamic_dwell_bit(esp, phase, x_index, y_index-1, &gather_info) )
                return FALSE;
        }
        else if( bits[y_index] > 0 )
        {
            aapl_log_printf(esp->aapl, AVAGO_DEBUG2, __func__, __LINE__, "STOP SCANNING column %d at %d\n", x_index, y_index);
            break;
        }
    }
    return TRUE;
}

/** @brief   Perform dynamic dwell on given row of eye.
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell_row(Eye_state_t *esp, int which, uint y_index)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int neighbor_threshold = esp->configp->ec_fast_dynamic ? esp->threshold : 0;
    int x_index;
    int x_mid = get_eye_middle_x_index(datap, which & 1);
    int x_left  = MAX(x_mid - datap->ed_x_resolution / 2, 0);
    int x_right = MIN(x_mid + datap->ed_x_resolution / 2, datap->ed_x_points-1);
    int x_shift = 0;
    Gather_info_t gather_info;

    if( y_index >= datap->ed_y_points )
        return TRUE;

    init_gather_info(esp, which, &gather_info);

    aapl_log_printf(esp->aapl,AVAGO_DEBUG2,__func__,__LINE__,"which = %d, x_range = [%d..%d], x_shift = %d, y_index = %d\n", which, x_left, x_right, x_shift, y_index);

    for( x_index = x_left+1; x_index <= x_right; x_index++ )
    {
        if( AVAGO_EYE_ERRORS_GET(*datap, x_index-1, y_index) > neighbor_threshold )
        {
            int phase = get_phase_for_x_index(esp, x_index, which);
            if( !eye_dynamic_dwell_bit(esp, phase, x_index, y_index, &gather_info) )
                return FALSE;
        }
        else
            break;
    }

    for( x_index = x_right-1; x_index > x_left; x_index-- )
    {
        if( AVAGO_EYE_ERRORS_GET(*datap, x_index+1, y_index) > neighbor_threshold )
        {
            int phase = get_phase_for_x_index(esp, x_index, which);
            if( !eye_dynamic_dwell_bit(esp, phase, x_index, y_index, &gather_info) )
                return FALSE;
        }
        else
            break;
    }

    return TRUE;
}

/** @brief   Performs dynamic dwell on BTC points.
 ** @details Works for all hardware and gather types.
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell_btc(
    Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    BOOL status = TRUE;

    if( datap->ed_eye_type != AVAGO_EYE_WIDTH )
    {

        if( datap->eye_count == 6 )
        {
            status &= eye_dynamic_dwell_column(esp,5,-6,datap->ed_y_resolution/2,datap->ed_y_resolution);
            status &= eye_dynamic_dwell_column(esp,4,-5,datap->ed_y_resolution/2,datap->ed_y_resolution);
            status &= eye_dynamic_dwell_column(esp,3,-4,datap->ed_y_resolution/4,datap->ed_y_resolution*3/4);
            status &= eye_dynamic_dwell_column(esp,2,-3,datap->ed_y_resolution/4,datap->ed_y_resolution*3/4);
            status &= eye_dynamic_dwell_column(esp,1,-2,0                       ,datap->ed_y_resolution/2);
            status &= eye_dynamic_dwell_column(esp,0,-1,0                       ,datap->ed_y_resolution/2);
        }
        else
        {
            status &= eye_dynamic_dwell_column(esp, 0, -1, 0, datap->ed_y_resolution);
        }
    }

    if( datap->ed_eye_type != AVAGO_EYE_HEIGHT )
    {
        int which;

        for( which = 0; which < datap->eye_count; which++ )
            status &= eye_dynamic_dwell_row(esp, which, datap->ed_hbtc[which].data_row);
    }

    return status;
}

/** @brief   Performs dynamic dwell on requested range of points.
 ** @details Works for all hardware and gather types.
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell_range(
    Eye_state_t *esp,
    int which,
    uint y_begin,
    uint y_end)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    int neighbor_threshold = esp->configp->ec_fast_dynamic ? esp->threshold : 0;
    uint x_index;
    Gather_info_t gather_info;

    init_gather_info(esp, which, &gather_info);

    if( which != gather_info.which )
        return TRUE;

    for( x_index = 0; x_index < datap->ed_x_points; x_index++ )
    {
        uint y_index;
        int phase = get_phase_for_x_index(esp, x_index, which);
        for( y_index = y_begin; y_index < y_end; y_index++ )
        {
            if( (x_index != 0 && AVAGO_EYE_ERRORS_GET(*datap, x_index-1, y_index) > neighbor_threshold) ||
                (y_index != 0 && AVAGO_EYE_ERRORS_GET(*datap, x_index, y_index-1) > neighbor_threshold) )
            {
                if( ! eye_dynamic_dwell_bit(esp, phase, x_index, y_index, &gather_info) )
                    return FALSE;
            }
        }
    }
    for( x_index = datap->ed_x_points; x_index > 0;    )
    {
        uint y_index;
        int phase = get_phase_for_x_index(esp, x_index, which);
        BOOL right_edge = (x_index == datap->ed_x_points);
        x_index--;
        for( y_index = y_end; y_index > y_begin;     )
        {
            BOOL bottom_edge = (y_index == datap->ed_y_points);
            y_index--;
            if( (!right_edge  && AVAGO_EYE_ERRORS_GET(*datap, x_index+1, y_index) > neighbor_threshold) ||
                (!bottom_edge && AVAGO_EYE_ERRORS_GET(*datap, x_index, y_index+1) > neighbor_threshold) )
            {
                if( ! eye_dynamic_dwell_bit(esp, phase, x_index, y_index, &gather_info) )
                    return FALSE;
            }
        }
    }
    return TRUE;
}

/** @brief   Performs dynamic dwell on full eye.
 ** @details Useful for more accurate full eye bathtub calcs without
 **          performance cost of full dynamic dwell.
 ** @details Works for all hardware and gather types.
 **
 ** Processes the eye to perform additional dwells on bits where:
 **  * the error count is less than or equal to the error_threshold, and
 **  * where a neighboring cell has some errors (> 0 for fast_dynamic==0,
 **    > threshold for fast_dynamic == 1 or 2), and
 **  * the current bit has > 0 dwells already.
 **
 ** The goal is to increase the resolution of the BER on the edges
 **    of the eye by doing additional dwells until the center edge
 **    of the eye has zero errors even after max_dwell bits dwells.
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell_all(
    Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    BOOL status = TRUE;


    if( esp->default_gather && avago_serdes_get_rx_line_encoding(esp->aapl, esp->addr) )
    {
        int y_level[4];

        eye_get_pam4_y_levels(esp, FALSE, y_level);
        status &= eye_dynamic_dwell_range(esp, 0, y_level[0], y_level[1]);
        status &= eye_dynamic_dwell_range(esp, 1, y_level[1], y_level[2]);
        status &= eye_dynamic_dwell_range(esp, 2, y_level[2], y_level[3]);
    }
    else
    {
        status &= eye_dynamic_dwell_range(esp, 0, 0, datap->ed_y_points);
    }

    return status;
}

/** @brief   Performs requested dynamic dwell.
 ** @details Works for all hardware and gather types.
 ** @return  On success, returns TRUE.
 ** @return  On failure, decrements aapl->return_code and returns FALSE.
 **/
static BOOL eye_dynamic_dwell(
    Eye_state_t *esp)
{
    BOOL status = TRUE;

    if( esp->datap->ed_min_dwell_bits < esp->datap->ed_max_dwell_bits )
    {
        status &= sbm_eye_setup_point(esp);

        status &= eye_dynamic_dwell_btc(esp);

        if( esp->configp->ec_fast_dynamic < 2 )
            status &= eye_dynamic_dwell_all(esp);
    }
    return status;
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

static int get_Vmean(const Avago_serdes_eye_data_t *datap, int column, int y_mid, float *top, float *bottom)
{
    const bigint *bits = get_bits_column(datap, column);
    const bigint *errs = get_errs_column(datap, column);
    int points = column < 0 ? datap->ed_y_mission_points : datap->ed_y_points;
    int step   = column < 0 ? datap->ed_y_mission_step   : datap->ed_y_step;
    int threshold = datap->ed_error_threshold;
    int y;
    Avago_least_sqr_point point, prev = {0.0, 0.0};

    for( y = y_mid; y < points; y++ )
    {
        if( bits[y] < 0 ) continue;
        if( bits[y] == 0 ) break;

        if( errs[y] > threshold )
        {
            point.x = mv_from_index(datap, points, step, y);
            point.y = avago_qfuncinv(avago_calc_BER(errs[y],bits[y],datap->ed_dc_balance));

            if( y > y_mid && point.y < 0 && prev.y >= 0 )
            {
                *top = (float)avago_interpolate(&prev,&point);
                break;
            }
            *top = point.x;
            prev.x = point.x;
            prev.y = point.y;
        }
    }

    for( y = y_mid; y >= 0; y-- )
    {
        if( bits[y] < 0 ) continue;
        if( bits[y] == 0 ) break;

        if( errs[y] > threshold )
        {
            point.x = mv_from_index(datap, points, step, y);
            point.y = avago_qfuncinv(avago_calc_BER(errs[y],bits[y],datap->ed_dc_balance));

            if( y < y_mid && point.y < 0 && prev.y >= 0 )
            {
                *bottom = (float)avago_interpolate(&prev,&point);
                break;
            }
            *bottom = point.x;
            prev.x = point.x;
            prev.y = point.y;
        }
    }

    if( *top > 0.0 && *bottom < 0.0 )
    {
        return (int)(*top - *bottom);
    }
    return 0;
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


/** @brief   Calculates best-fit extrapolation for the HBTC (horizontal bathtub curve).
 ** @details Uses the selected row of eye data and trans_density
 **          to perform a standard set of error rate extrapolations.
 ** @return  Saves relevant results into the Avago_serdes_eye_hbtc_t structure.
 ** @see     avago_serdes_eye_vbtc_extrapolate().
 **/
void avago_serdes_eye_hbtc_extrapolate(
    const Avago_serdes_eye_data_t *datap,   /**< [in] Populated eye data. */
    BOOL odd,                               /**< [in] Which eye to analyze. */
    uint data_row,                          /**< [in] Row index in eye data to analyze. */
    float trans_density,                    /**< [in] Transition density to use for calculations. */
    Avago_serdes_eye_hbtc_t *results)       /**< [out] Where results are written. */
{
    Avago_least_sqr_results left, right;

    memset(results,0,sizeof(*results));

    results->data_row = data_row;
    results->total_rows = datap->ed_y_points;
    results->trans_density = trans_density;
    results->data_millivolts = (uint)mv_from_index(datap, datap->ed_y_points, datap->ed_y_step, data_row);
    results->points = datap->ed_x_points;

    if( data_row >= datap->ed_y_points || datap->ed_eye_type == AVAGO_EYE_HEIGHT )
        return;

    get_horizontal_least_sqr(datap, data_row, odd, results->trans_density, results, &left, &right);
    get_horizontal_means(    datap, data_row, odd, results->trans_density, results);

    if( results->left_points < FIT || results->right_points < FIT )
    {
        results->left_points = results->right_points = 0;
        return;
    }


    results->left_slope      = (float)left.slope * 1000;
    results->left_intercept  = (float)left.y_intercept;
    results->left_R_squared  = (float)left.Rsqr;
    results->left_rj         = (float)calc_rj(&left);

    if( left.slope != 0.0 )
        results->left_x_intercept = -left.y_intercept / left.slope;
    if( right.slope != 0.0 )
        results->right_x_intercept = -right.y_intercept / right.slope;
    results->dj = fabs(1000 - (results->right_x_intercept - results->left_x_intercept));

    results->right_slope     = (float)right.slope * 1000;
    results->right_intercept = (float)right.y_intercept;
    results->right_R_squared = (float)right.Rsqr;
    results->right_rj        = (float)calc_rj(&right);
    results->snr             = (float)(results->right_intercept * results->left_slope - results->left_intercept * results->right_slope) / (results->left_slope - results->right_slope);
    if( results->snr < 0 )
        results->snr = -results->snr;


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
}

/** @brief Write the HBTC data to a string.
 ** @return A character string containing the formatted HBTC results.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_hbtc_format(
    const Avago_serdes_eye_hbtc_t *hbtcp) /**< Populated Avago_serdes_eye_hbtc_t pointer. */
{
    size_t buf_len = 1000;
    char *buf = (char *)AAPL_MALLOC(buf_len);
    char *end = buf + buf_len;
    char *ptr = buf;
    double td = hbtcp->trans_density;
    uint mid_row = ((int)hbtcp->total_rows-1) / 2;
    const char *eye_type = hbtcp->points/2 < hbtcp->left_index ? "odd " : hbtcp->points/2 > hbtcp->right_index ? "even " : "";
    if( buf == NULL )
        return buf;

    ptr += snprintf(ptr, end-ptr, "\n");
    ptr += snprintf(ptr, end-ptr, "# Horizontal Bathtub Curve for %seye at %+d mV (%+d rows) from center:\n", eye_type, hbtcp->data_millivolts, hbtcp->data_row - mid_row);
    if( hbtcp->left_points == 0 || hbtcp->right_points == 0 )
    {
        if( hbtcp->data_row < AAPL_MAX_DAC_RANGE )
            return strncat(ptr,"\nNOTE: Insufficient data to generate horizontal bathtub information.\n", end-ptr), buf;
        AAPL_FREE(buf);
        return NULL;
    }

    if( hbtcp->left_R_squared < 0.95 || hbtcp->right_R_squared < 0.95 ||
        hbtcp->left_slope <= 0.0 || hbtcp->right_slope >= 0.0 )
        ptr += snprintf(ptr, end-ptr, "#\n# WARNING: This projection is based on measurements with poor correlation.\n#\n");

    ptr += snprintf(ptr, end-ptr, "BER/%.3g = Q at eye width of   0 mUI: %4.2e, %5.2f\n", td, hbtcp->horz_ber_0mUI, hbtcp->width_0mUI);
    ptr += snprintf(ptr, end-ptr, "BER/%.3g = Q at eye width of 100 mUI: %4.2e, %5.2f\n", td, hbtcp->horz_ber_100mUI, hbtcp->width_100mUI);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-06 BER/%.3g = Q(%4.2f): %4d mUI\n", td, q06, hbtcp->horz_eye_1e06);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-10 BER/%.3g = Q(%4.2f): %4d mUI\n", td, q10, hbtcp->horz_eye_1e10);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-12 BER/%.3g = Q(%4.2f): %4d mUI\n", td, q12, hbtcp->horz_eye_1e12);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-15 BER/%.3g = Q(%4.2f): %4d mUI\n", td, q15, hbtcp->horz_eye_1e15);
    ptr += snprintf(ptr, end-ptr, "Eye width at 1e-17 BER/%.3g = Q(%4.2f): %4d mUI\n", td, q17, hbtcp->horz_eye_1e17);
    ptr += snprintf(ptr, end-ptr, "X-intercept left/right:   %7.1f,    %5.1f  mUI\n", hbtcp->left_x_intercept, hbtcp->right_x_intercept);
    ptr += snprintf(ptr, end-ptr, "Mean left/right:          %7.1f,    %5.1f  mUI (at Q==0)\n", hbtcp->left_mean, hbtcp->right_mean);
    ptr += snprintf(ptr, end-ptr, "Est RJrms left/right:     %7.1f,    %5.1f  mUI\n",  hbtcp->left_rj, hbtcp->right_rj);
    ptr += snprintf(ptr, end-ptr, "Est DJpp:                 %7.1f            mUI\n", hbtcp->dj);
    ptr += snprintf(ptr, end-ptr, "Est signal noise ratio:   %8.2f\n", hbtcp->snr);
    ptr += snprintf(ptr, end-ptr, "Transition density:       %11.5f\n", hbtcp->trans_density);
    ptr += snprintf(ptr, end-ptr, "R-squared fit left/right: %9.3f,    %5.3f\n", hbtcp->left_R_squared, hbtcp->right_R_squared);
    ptr += snprintf(ptr, end-ptr, "No. points left/right:    %5u, %8u\n",hbtcp->left_points, hbtcp->right_points);
    ptr += snprintf(ptr, end-ptr, "Indexes left/right:       %5u, %8u\n",hbtcp->left_index,hbtcp->right_index);
    return buf;
}

#if AAPL_ENABLE_FILE_IO
/** @brief Write the formatted HBTC data to a file using the
 **        serdes_eye_hbtc_format() output.
 **/
void avago_serdes_eye_hbtc_write(
    FILE *file,                           /**< [in] Where to write. */
    const Avago_serdes_eye_hbtc_t *hbtcp) /**< [in] Data to format and print. */
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


/** @brief Write the HBTC data to a string.
 ** @return A character string containing the formatted HBTC results.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_btc_format(
    const Avago_serdes_eye_data_t *datap) /**< [in] Populated eye data. */
{
    size_t buf_len = 450;
    char *buf = (char *)AAPL_MALLOC(buf_len);
    char *end = buf + buf_len;
    char *ptr = buf;
    if( buf == NULL )
        return buf;

    ptr += snprintf(ptr, end-ptr, "\n");
    if( datap->eye_count == 6 )
    {
        ptr += snprintf(ptr, end-ptr, "Level 3 even/odd means: %6.0f %6.0f mV\n", datap->level_vmean[0][3], datap->level_vmean[1][3]);
        ptr += snprintf(ptr, end-ptr, "Level 2 even/odd means: %6.0f %6.0f mV\n", datap->level_vmean[0][2], datap->level_vmean[1][2]);
        ptr += snprintf(ptr, end-ptr, "Level 1 even/odd means: %6.0f %6.0f mV\n", datap->level_vmean[0][1], datap->level_vmean[1][1]);
        ptr += snprintf(ptr, end-ptr, "Level 0 even/odd means: %6.0f %6.0f mV\n", datap->level_vmean[0][0], datap->level_vmean[1][0]);
        ptr += snprintf(ptr, end-ptr, "Level 3 even/odd DN:    %6.2f %6.2f mV\n", datap->level_dn[0][3], datap->level_dn[1][3]);
        ptr += snprintf(ptr, end-ptr, "Level 2 even/odd DN:    %6.2f %6.2f mV\n", datap->level_dn[0][2], datap->level_dn[1][2]);
        ptr += snprintf(ptr, end-ptr, "Level 1 even/odd DN:    %6.2f %6.2f mV\n", datap->level_dn[0][1], datap->level_dn[1][1]);
        ptr += snprintf(ptr, end-ptr, "Level 0 even/odd DN:    %6.2f %6.2f mV\n", datap->level_dn[0][0], datap->level_dn[1][0]);
        ptr += snprintf(ptr, end-ptr, "Level even/odd Comp:    %6.2f %6.2f dB\n", datap->level03_comp[0],datap->level03_comp[1]);
    }
    else if( datap->eye_count == 3 )
    {
        ptr += snprintf(ptr, end-ptr, "Level 3 mean: %5.0f mV\n", datap->level_vmean[0][3]);
        ptr += snprintf(ptr, end-ptr, "Level 2 mean: %5.0f mV\n", datap->level_vmean[0][2]);
        ptr += snprintf(ptr, end-ptr, "Level 1 mean: %5.0f mV\n", datap->level_vmean[0][1]);
        ptr += snprintf(ptr, end-ptr, "Level 0 mean: %5.0f mV\n", datap->level_vmean[0][0]);
        ptr += snprintf(ptr, end-ptr, "Level 3 DN:   %5.2f mV\n", datap->level_dn[0][3]);
        ptr += snprintf(ptr, end-ptr, "Level 2 DN:   %5.2f mV\n", datap->level_dn[0][2]);
        ptr += snprintf(ptr, end-ptr, "Level 1 DN:   %5.2f mV\n", datap->level_dn[0][1]);
        ptr += snprintf(ptr, end-ptr, "Level 0 DN:   %5.2f mV\n", datap->level_dn[0][0]);
        ptr += snprintf(ptr, end-ptr, "Level Comp:   %5.2f dB\n", datap->level03_comp[0]);
    }
    else
    {
        ptr += snprintf(ptr, end-ptr, "Level 1 mean: %5.0f mV\n", datap->level_vmean[0][1]);
        ptr += snprintf(ptr, end-ptr, "Level 0 mean: %5.0f mV\n", datap->level_vmean[0][0]);
        ptr += snprintf(ptr, end-ptr, "Level 1 DN:   %5.2f mV\n", datap->level_dn[0][1]);
        ptr += snprintf(ptr, end-ptr, "Level 0 DN:   %5.2f mV\n", datap->level_dn[0][0]);
    }


    ptr += snprintf(ptr, end-ptr, "Combined BTC BER/Q:  %4.2e, %5.2f\n", datap->ed_combined_btc_ber, datap->ed_combined_btc_qval);
    if( datap->ed_combined_lsb_ber != 0.0 )
        ptr += snprintf(ptr, end-ptr, "Combined LSB BER/Q:  %4.2e, %5.2f\n", datap->ed_combined_lsb_ber, datap->ed_combined_lsb_qval);

    return buf;
}

#if AAPL_ENABLE_FILE_IO
/** @brief Write the formatted BTC data to a file using the
 **        serdes_eye_btc_format() output.
 **/
void avago_serdes_eye_btc_write(
    FILE *file,                           /**< [in] Where to write. */
    const Avago_serdes_eye_data_t *datap) /**< [in] Populated eye data. */
{
    char *btc_string = avago_serdes_eye_btc_format(datap);
    if( btc_string )
    {
        fputs("\n",file);
        fputs(btc_string,file);
        AAPL_FREE(btc_string);
    }
}
#endif

/** @brief Write the formatted BTC data metric to the log using the
 **        serdes_eye_btc_format() output.
 **/
void avago_serdes_eye_btc_log_print(
    Aapl_t *aapl,                         /**< [in] */
    Aapl_log_type_t level,                /**< [in] Specify logging type. */
    const char *caller,                   /**< [in] Typically __func__, may be 0. */
    int line,                             /**< [in] Typically __LINE__, may be 0. */
    const Avago_serdes_eye_data_t *datap) /**< [in] Populated eye data. */
{
    char *btc_string = avago_serdes_eye_btc_format(datap);
    if( btc_string )
    {
        aapl_log_add(aapl, level, btc_string, caller, line);
        AAPL_FREE(btc_string);
    }
}

/** @brief   Calculate best-fit extrapolation for the VBTC (vertical bathtub curve).
 ** @details Uses the selected row of eye data, as well as datap->ed_dc_balance,
 **          to perform a standard set of error rate extrapolations.
 ** @see     avago_serdes_eye_hbtc_extrapolate().
 ** @return  Saves relevant results into the Avago_serdes_eye_vbtc_t structure.
 **/
void avago_serdes_eye_vbtc_extrapolate(
    const Avago_serdes_eye_data_t *datap, /**< [in] Populated eye data. */
    int which,                            /**< [in] Which PAM4 eye to analyze [0..5] */
    int column,                           /**< [in] Column index in eye data to analyze. */
    Avago_serdes_eye_vbtc_t *results)     /**< [out] Where results are written. */
{
    Avago_least_sqr_results lower_lsr, upper_lsr;
    int data_column = column;

    memset(results,0,sizeof(*results));

    if( (which & 1) && column >= 0 )
        data_column += datap->ed_x_points / 2;

    get_vertical_least_sqr(datap, which/2, data_column, results, &lower_lsr, &upper_lsr);

    results->data_column = column;
    results->total_columns = column < 0 ? 0 : datap->ed_x_UI * datap->ed_x_resolution + 1;
    results->eye_count = datap->eye_count;
    results->which = which;

    results->points = MIN(results->bottom_points, results->top_points);

    if( results->bottom_points < FIT || results->top_points < FIT )
    {
        results->bottom_points = results->top_points = 0;
        return;
    }

    results->Vmean = get_Vmean(datap, data_column, results->bottom_index + 1, &results->top_vmean, &results->bottom_vmean);
    results->dc_balance = datap->ed_dc_balance;
    results->avdd = datap->ed_avdd;

    results->top_rn           = (float)calc_rj(&upper_lsr);
    results->top_slope        = (float)1.0 / upper_lsr.slope;
    results->top_intercept    = (float)upper_lsr.y_intercept;
    results->top_vsig         = (float)-upper_lsr.y_intercept / upper_lsr.slope;
    results->top_R_squared    = (float)upper_lsr.Rsqr;

    results->bottom_rn        = (float)calc_rj(&lower_lsr);
    results->bottom_slope     = (float)1.0 / lower_lsr.slope;
    results->bottom_intercept = (float)lower_lsr.y_intercept;
    results->bottom_vsig      = (float)-lower_lsr.y_intercept / lower_lsr.slope;
    results->bottom_R_squared = (float)lower_lsr.Rsqr;
    results->snr              = (float)(results->top_intercept * results->top_slope - results->bottom_intercept * results->bottom_slope) / (results->top_slope - results->bottom_slope);
    if( results->snr < 0 )
        results->snr = -results->snr;

    {

    double proj_diff = upper_lsr.y_intercept * lower_lsr.slope - lower_lsr.y_intercept * upper_lsr.slope;
    double slope_diff = upper_lsr.slope - lower_lsr.slope;
    int sign = slope_diff > 0 ? +1 : -1;
    double y_0mV = 0.0 - proj_diff / slope_diff;
    double y_25mV = 0.0 - (proj_diff - (sign * 25) * lower_lsr.slope * upper_lsr.slope) / slope_diff;
    if( y_0mV > AVAGO_Q_CEILING )
        y_0mV = AVAGO_Q_CEILING;
    if( y_25mV > AVAGO_Q_CEILING )
        y_25mV = AVAGO_Q_CEILING;
    results->vert_ber_0mV = avago_qfunc(y_0mV);
    results->vert_ber_25mV = avago_qfunc(y_25mV);
    results->height_0mV  = (float)y_0mV;
    results->height_25mV = (float)y_25mV;


    results->vert_eye_1e03 = (int)(sign * ((upper_lsr.y_intercept - q03) / upper_lsr.slope - (lower_lsr.y_intercept - q03) / lower_lsr.slope));
    results->vert_eye_1e04 = (int)(sign * ((upper_lsr.y_intercept - q04) / upper_lsr.slope - (lower_lsr.y_intercept - q04) / lower_lsr.slope));
    results->vert_eye_1e05 = (int)(sign * ((upper_lsr.y_intercept - q05) / upper_lsr.slope - (lower_lsr.y_intercept - q05) / lower_lsr.slope));
    results->vert_eye_1e06 = (int)(sign * ((upper_lsr.y_intercept - q06) / upper_lsr.slope - (lower_lsr.y_intercept - q06) / lower_lsr.slope));
    results->vert_eye_1e10 = (int)(sign * ((upper_lsr.y_intercept - q10) / upper_lsr.slope - (lower_lsr.y_intercept - q10) / lower_lsr.slope));
    results->vert_eye_1e12 = (int)(sign * ((upper_lsr.y_intercept - q12) / upper_lsr.slope - (lower_lsr.y_intercept - q12) / lower_lsr.slope));
    results->vert_eye_1e15 = (int)(sign * ((upper_lsr.y_intercept - q15) / upper_lsr.slope - (lower_lsr.y_intercept - q15) / lower_lsr.slope));
    results->vert_eye_1e17 = (int)(sign * ((upper_lsr.y_intercept - q17) / upper_lsr.slope - (lower_lsr.y_intercept - q17) / lower_lsr.slope));
    }
}

/** @brief Perform a standard set of error rate calculations using the horizontal
 **         center row for each eye.
 **/
static void hbtc_extrapolate(Avago_serdes_eye_data_t *datap)
{
    int which;
    for( which = 0; which < datap->eye_count; which++ )
    {
        float trans_density = datap->ed_trans_density;
        if( (datap->eye_count == 6 && (which == 2 || which == 3)) ||
            (datap->eye_count == 3 && which == 1) )
        {
            trans_density *= 4.0 / 3.0;
        }
        avago_serdes_eye_hbtc_extrapolate(datap, which&1, datap->ed_hbtc[which].data_row, trans_density, &datap->ed_hbtc[which]);
    }
}

/** @brief Perform a standard set of error rate calculations using the mission
 **         data column of the eye data.
 **/

static void vbtc_extrapolate_mission(Avago_serdes_eye_data_t *datap)
{
    int which;
    for( which = 0; which < datap->eye_count; which++ )
        avago_serdes_eye_vbtc_extrapolate(datap, which, -1-which, &datap->ed_vbtc[which]);

    if( datap->eye_count == 6 )
    {
        int i;
        for( i = 0; i < 2; i++ )
        {
            datap->level_vmean[i][3] =  datap->ed_vbtc[4+i].top_vmean;
            datap->level_vmean[i][2] = (datap->ed_vbtc[2+i].top_vmean + datap->ed_vbtc[4+i].bottom_vmean) / 2.0;
            datap->level_vmean[i][1] = (datap->ed_vbtc[0+i].top_vmean + datap->ed_vbtc[2+i].bottom_vmean) / 2.0;
            datap->level_vmean[i][0] =                                  datap->ed_vbtc[0+i].bottom_vmean;

            datap->level_dn[i][3] = fabs(datap->ed_vbtc[4+i].top_vmean   - datap->ed_vbtc[4+i].top_vsig) * 2.0;
            datap->level_dn[i][2] = fabs(datap->ed_vbtc[4+i].bottom_vsig - datap->ed_vbtc[2+i].top_vsig);
            datap->level_dn[i][1] = fabs(datap->ed_vbtc[2+i].bottom_vsig - datap->ed_vbtc[0+i].top_vsig);
            datap->level_dn[i][0] = fabs(datap->ed_vbtc[0+i].bottom_vsig - datap->ed_vbtc[0+i].bottom_vmean) * 2.0;

            if( datap->level_vmean[i][3] > datap->level_vmean[i][0] )
                datap->level03_comp[i] = 20 * log10(3.0 * (datap->level_vmean[i][2] - datap->level_vmean[i][1]) / (datap->level_vmean[i][3] - datap->level_vmean[i][0]));
        }
    }
#if 1
    else if( datap->eye_count == 3 )
    {
        datap->level_vmean[0][3] =  datap->ed_vbtc[2].top_vmean;
        datap->level_vmean[0][2] = (datap->ed_vbtc[1].top_vmean + datap->ed_vbtc[2].bottom_vmean) / 2.0;
        datap->level_vmean[0][1] = (datap->ed_vbtc[0].top_vmean + datap->ed_vbtc[1].bottom_vmean) / 2.0;
        datap->level_vmean[0][0] =                                datap->ed_vbtc[0].bottom_vmean;

        datap->level_dn[0][3] = fabs(datap->ed_vbtc[2].top_vmean   - datap->ed_vbtc[2].top_vsig) * 2.0;
        datap->level_dn[0][2] = fabs(datap->ed_vbtc[2].bottom_vsig - datap->ed_vbtc[1].top_vsig);
        datap->level_dn[0][1] = fabs(datap->ed_vbtc[1].bottom_vsig - datap->ed_vbtc[0].top_vsig);
        datap->level_dn[0][0] = fabs(datap->ed_vbtc[0].bottom_vsig - datap->ed_vbtc[0].bottom_vmean) * 2.0;

        if( datap->level_vmean[0][3] > datap->level_vmean[0][0] )
            datap->level03_comp[0] = 20 * log10(3.0 * (datap->level_vmean[0][2] - datap->level_vmean[0][1]) / (datap->level_vmean[0][3] - datap->level_vmean[0][0]));
    }
#endif
    else
    {
        datap->level_vmean[0][1] = datap->ed_vbtc[0].top_vmean;
        datap->level_vmean[0][0] = datap->ed_vbtc[0].bottom_vmean;
        datap->level_dn[0][1] = 2.0 * fabs(datap->ed_vbtc[0].top_vmean - datap->ed_vbtc[0].top_vsig);
        datap->level_dn[0][0] = 2.0 * fabs(datap->ed_vbtc[0].bottom_vsig - datap->ed_vbtc[0].bottom_vmean);
    }
}


/** @brief Write the VBTC data to a string.
 ** @return A character string containing the formatted VBTC results.
 **         The caller should AAPL_FREE the returned string.
 **/

char *avago_serdes_eye_vbtc_format(const Avago_serdes_eye_vbtc_t *vbtcp) /**< Populated VBTC structure pointer */
{
    size_t buf_len = 1000;
    char *buf = (char *)AAPL_MALLOC(buf_len);
    char *end = buf + buf_len;
    char *ptr = buf;
    double db = vbtcp->dc_balance;
    const char *even_odd = vbtcp->eye_count > 3 ? (vbtcp->which & 1) ? " odd" : " even" : "";
    int eye_base = vbtcp->which / (vbtcp->eye_count > 3 ? 2 : 1);
    if( buf == NULL )
        return buf;

    ptr += snprintf(ptr, end-ptr, "\n");
    if( vbtcp->data_column < 0 )
        ptr += snprintf(ptr, end-ptr, "# Vertical Bathtub Curve (mission data channel; %d..%d%s eye):\n", eye_base, eye_base+1, even_odd);
    else
        ptr += snprintf(ptr, end-ptr, "# Vertical Bathtub Curve (phase center %+d; %d..%d%s eye):\n", vbtcp->data_column - vbtcp->total_columns / 2, eye_base, eye_base+1, even_odd);
    if( vbtcp->top_points == 0 || vbtcp->bottom_points == 0 )
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
    ptr += snprintf(ptr, end-ptr, "Eye height (Vmean) at %g BER=Q(%4.2f): %4d mV\n",db,0.0,vbtcp->Vmean);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-06 BER/%g = Q(%4.2f): %4d mV\n",db,q06,vbtcp->vert_eye_1e06);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-10 BER/%g = Q(%4.2f): %4d mV\n",db,q10,vbtcp->vert_eye_1e10);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-12 BER/%g = Q(%4.2f): %4d mV\n",db,q12,vbtcp->vert_eye_1e12);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-15 BER/%g = Q(%4.2f): %4d mV\n",db,q15,vbtcp->vert_eye_1e15);
    ptr += snprintf(ptr, end-ptr, "Eye height at 1e-17 BER/%g = Q(%4.2f): %4d mV\n",db,q17,vbtcp->vert_eye_1e17);
    ptr += snprintf(ptr, end-ptr, "Vsig bottom/top:            %6.1f,  %6.1f  mV\n", vbtcp->bottom_vsig, vbtcp->top_vsig);
    ptr += snprintf(ptr, end-ptr, "Vmean bottom/top:           %6.1f,  %6.1f  mV\n", vbtcp->bottom_vmean, vbtcp->top_vmean);
    ptr += snprintf(ptr, end-ptr, "Est RNrms bottom/top:       %6.1f,  %6.1f  mV\n", vbtcp->bottom_rn, vbtcp->top_rn);
    ptr += snprintf(ptr, end-ptr, "Voltage range:              %7.2f           V\n", vbtcp->avdd);
    ptr += snprintf(ptr, end-ptr, "Est signal noise ratio:     %7.2f\n", vbtcp->snr);
    ptr += snprintf(ptr, end-ptr, "DC balance:                 %9.4f\n", vbtcp->dc_balance);
    ptr += snprintf(ptr, end-ptr, "R-squared fit bottom/top:   %8.3f,%8.3f\n", vbtcp->bottom_R_squared, vbtcp->top_R_squared);
    ptr += snprintf(ptr, end-ptr, "No. points bottom/top:      %4u, %7u\n",vbtcp->bottom_points, vbtcp->top_points);
    ptr += snprintf(ptr, end-ptr, "Indexes bottom/top:         %4u, %7u\n",vbtcp->bottom_index,vbtcp->top_index);
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
    uint column_points = column < 0 ? datap->ed_y_mission_points : datap->ed_y_points;
    uint column_step = column < 0 ? datap->ed_y_mission_step : datap->ed_y_step;
    uint y_point;
    for( y_point = 0; y_point < column_points; ++y_point )
    {
        bigint e = errors[y_point];
        if( e <= datap->ed_error_threshold && e >= 0 && bits[y_point] > 0 )
            height++;
    }
    datap->ed_height = height * column_step;

    datap->ed_height_mV = (1000 * datap->ed_height + dac_resolution/2) / dac_resolution;
    vbtc_extrapolate_mission(datap);

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__,"height = %u, height_mV = %u\n", datap->ed_height, datap->ed_height_mV);
    if( (aapl->debug & 0xf) >= AVAGO_DEBUG2 )
    {
        avago_serdes_eye_vbtc_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, &datap->ed_vbtc[0]);
        if( datap->ed_vbtc[1].top_points > 0 && datap->ed_vbtc[1].bottom_points > 0 )
            avago_serdes_eye_vbtc_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, &datap->ed_vbtc[1]);
        if( datap->ed_vbtc[2].top_points > 0 && datap->ed_vbtc[2].bottom_points > 0 )
            avago_serdes_eye_vbtc_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, &datap->ed_vbtc[2]);
    }
}


static void calc_width(Aapl_t *aapl, Avago_serdes_eye_data_t *datap)
{
    int pi_resolution = datap->ed_x_resolution * datap->ed_x_step;
    int width = 0, w = 0, out = 0;
    uint y_mid = (datap->ed_y_points-1) / 2;
    uint x_point;
    for( x_point = 0; x_point < datap->ed_x_points; ++x_point )
    {
        bigint e = AVAGO_EYE_ERRORS_GET(*datap, x_point, y_mid);
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

    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__,"width = %u, width_mUI = %u\n", datap->ed_width, datap->ed_width_mUI);
    if( (aapl->debug & 0xf) >= AVAGO_DEBUG2 )
    {
        avago_serdes_eye_hbtc_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, &datap->ed_hbtc[0]);
        if( datap->ed_hbtc[1].data_row < datap->ed_y_points )
            avago_serdes_eye_hbtc_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, &datap->ed_hbtc[1]);
        if( datap->ed_hbtc[2].data_row < datap->ed_y_points )
            avago_serdes_eye_hbtc_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, &datap->ed_hbtc[2]);
    }
}


static void adjust_x_scale(Eye_state_t *esp)
{
    Aapl_t *aapl = esp->aapl;
    uint    addr = esp->addr;

    int left = 0, right = 0, inside = 0;
    uint x, x_res = esp->phase_mult * 64;
    int margin = 0;


    if( esp->phase_mult * 64 == esp->datap->ed_x_resolution )
        return;

    aapl_log_printf(esp->aapl,AVAGO_DEBUG2,__func__,__LINE__,"SBus %s, BEFORE: x_resolution=%d\n",
            aapl_addr_to_str(addr), esp->datap->ed_x_resolution);

    if( !eye_set_compare_mode(esp, AVAGO_SERDES_RX_CMP_MODE_XOR)
     || eye_set_error_timer(esp, AVAGO_EYE_MIN_DWELL_BITS) < 0 )
    {
        return;
    }

    sbm_eye_setup_point(esp);

    for( x = 0; x <= x_res && !aapl_get_async_cancel_flag(esp->aapl); x++ )
    {
        int errors;
        errors = sbm_eye_get_point(esp, FALSE, x - x_res/2, 0);
        if( errors >= (int)esp->datap->ed_error_threshold )
        {
            if( inside == 0 )
                left++;
            else
                right++;
        }
        else if( inside == 0 )
        {
            x = x_res - left - 2;
            inside++;
        }
    }
    aapl_log_printf(aapl, AVAGO_DEBUG3, __func__,__LINE__,"left,inside,right = %d,%d,%d\n",left,inside,right);
    margin = MIN(left,right);
    while( esp->datap->ed_x_resolution < x_res )
    {
        aapl_log_printf(aapl, AVAGO_DEBUG4, __func__,__LINE__, "resolution,margin = %u,%d\n",x_res,margin);
        if( margin < 6 )
            break;
        x_res /= 2;
        margin /= 2;
    }
    set_x_resolution(esp, x_res);

    aapl_log_printf(esp->aapl,AVAGO_DEBUG2,__func__,__LINE__,"SBus %s, AFTER: x_resolution=%d\n",
            aapl_addr_to_str(addr), esp->datap->ed_x_resolution);
}

static void find_y_edges(Eye_state_t *esp, int *upper, int *lower)
{
    {
        int res = esp->datap->ed_y_resolution;
        if( sbm_eye_setup_point(esp) )
        {
            int upper_center_dac = res/2;
            int lower_center_dac = res/2;
            if( avago_serdes_get_rx_line_encoding(esp->aapl, esp->addr) )
            {
                upper_center_dac = find_m4_eye_center_offset(esp, 4) + 255;
                lower_center_dac = find_m4_eye_center_offset(esp, 0) + 255;

                eye_select(esp, 4);
                *upper  = (int)find_edge(esp, upper_center_dac, res, esp->threshold);
                eye_select(esp, 0);
                *lower  = (int)find_edge(esp, lower_center_dac,   0, esp->threshold);
            }
            else
            {
                *upper  = (int)find_edge(esp, upper_center_dac, res, esp->threshold);
                *lower  = (int)find_edge(esp, lower_center_dac,   0, esp->threshold);
            }
        }
        else
            *upper = *lower = 0;
    }
    aapl_log_printf(esp->aapl, AVAGO_DEBUG4, __func__, __LINE__, "SBus %s, adjusted: upper=%d, lower=%d\n",
            aapl_addr_to_str(esp->addr), *upper, *lower);
}

static void adjust_y_scale(Eye_state_t *esp)
{
    int dac_top = 255, dac_bot = 0;
    uint dac_range = esp->datap->ed_y_resolution;
    uint dac_mid = dac_range / 2;
    uint max_range = dac_range - 1;
    uint y_points;
    int dac_half_span;

    if( eye_set_error_timer(esp, AVAGO_EYE_MIN_DWELL_BITS) < 0 )
        return;

    aapl_log_printf(esp->aapl,AVAGO_DEBUG2,__func__,__LINE__,"BEFORE: y_points=%d, y_step=%d\n",esp->datap->ed_y_points,esp->datap->ed_y_step);

    find_y_edges(esp, &dac_top, &dac_bot);

    dac_half_span = dac_top - dac_mid > dac_mid - dac_bot ? (dac_top-dac_mid) : (dac_mid-dac_bot);
    while( TRUE )
    {
        y_points = (dac_half_span / esp->datap->ed_y_step + FIT + FIT) * 2 + 1;


        if( esp->datap->ed_y_step == 1 || (y_points-1) * esp->datap->ed_y_step < max_range )
            break;
        esp->datap->ed_y_step--;
    }
    if( y_points > max_range )
        y_points = max_range;
    set_y_points(esp->datap, y_points);

    aapl_log_printf(esp->aapl,AVAGO_DEBUG2,__func__,__LINE__,"AFTER:  y_points=%d (%d..%d), y_step=%d\n",
            esp->datap->ed_y_points,
            dac_mid-esp->datap->ed_y_points/2*esp->datap->ed_y_step,
            dac_mid+esp->datap->ed_y_points/2*esp->datap->ed_y_step,
            esp->datap->ed_y_step);

}



/** @brief  Verifies valid parameters are passed in and SerDes is in state to gather an eye.
 ** @return Returns 0 on success, < 0 on failure.
 **/
static int verify_eye_parameters(
    Aapl_t *aapl,                             /**< [in] Pointer to Aapl_t structure. */
    uint addr,                                /**< [in] SBus slice address. */
    const Avago_serdes_eye_config_t *configp) /**< [in] Configuration parameters for how to gather the eye. */
{
    int ret = aapl_get_return_code(aapl);
    if( ret < 0 )
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "found aapl->return_code negative (%d) implying a prior error; value cleared\n",ret);

    if( configp->ec_gather_mean && (configp->ec_mean_direction > 0) && configp->ec_no_sbm )
        return aapl_fail(aapl, __func__, __LINE__,
            "SBus %s, Mean eye measurement with direction requires a SBus Master support\n",
            aapl_addr_to_str(addr));

    if( !(   aapl_check_process(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F)
          && aapl_check_ip_type(aapl, addr, __func__, __LINE__, TRUE, 3, AVAGO_SERDES, AVAGO_M4, AVAGO_P1)) )
    {
        return -1;
    }

    if( !aapl_check_firmware_rev(aapl, addr, __func__, __LINE__, FALSE, 1, 0x1049) )
    {
        uint build_id = aapl_get_firmware_build(aapl, addr);
        if( 0 == (build_id & 0x0040) )
            return aapl_fail(aapl, __func__, __LINE__,
                "SBus %s, Eye measurement requires a _xx4x build in pre-0x1049 firmware, current is 0x%04X_%04X\n",
                aapl_addr_to_str(addr), aapl_get_firmware_rev(aapl, addr), build_id);
    }

    if( configp->ec_cmp_mode == AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN
        && aapl_get_ip_type(aapl, addr) == AVAGO_M4
        && avago_serdes_get_rx_line_encoding(aapl, addr) )
    {
        aapl_log_printf(aapl, AVAGO_WARNING, __func__,__LINE__, "TEST_PATGEN compare mode is not supported for all PAM4 data path configurations.\n");
    }

    if( configp->ec_eye_type > AVAGO_EYE_HEIGHT_DVOS )
    {
        return aapl_fail(aapl, __func__, __LINE__,
            "Avago_serdes_eye_config_t->ec_eye_type value (%d) is out-of-range.\n",
            configp->ec_eye_type);
    }
    {
        Avago_serdes_rx_clocks_t clocks;
        avago_serdes_rx_clock_read(aapl, addr, &clocks);
        if( clocks.data == AVAGO_SERDES_RX_CLOCK_R || clocks.edge == AVAGO_SERDES_RX_CLOCK_R || clocks.dfe == AVAGO_SERDES_RX_CLOCK_R )
        {
            if( configp->ec_eye_type != AVAGO_EYE_HEIGHT )
                return aapl_fail(aapl, __func__,__LINE__,"Can only capture eye height when rclk is used for data or edge detection.\n");

            if( !configp->ec_no_sbm )
                return aapl_fail(aapl, __func__,__LINE__,"Cannot use SBM acceleration when rclk is used for data or edge detection.\n");
        }
        if( aapl_get_ip_type(aapl,addr) == AVAGO_M4 && aapl_check_firmware_rev(aapl,addr, __func__, __LINE__, FALSE, 1, 0x1071) && avago_serdes_get_rx_input_loopback(aapl, addr) )
            return aapl_fail(aapl, __func__,__LINE__,"Cannot capture eye on CM4 in ILB mode with firmware >= 0x1071.\n");
    }
    aapl_log_printf(aapl, AVAGO_DEBUG3, __func__,__LINE__,"returning success\n");
    return 0;
}

/** @brief Sets ed_x_min and ed_x_max for the eye center. */
static void set_eye_center(Eye_state_t *esp)
{
    Avago_serdes_eye_data_t *datap = esp->datap;
    Aapl_t *aapl = esp->aapl;
    uint    addr = esp->addr;
    int i, eye_center = 0;

    if( esp->configp->ec_eye_type == AVAGO_EYE_HEIGHT )
        return;


    for( i = 0; i < datap->eye_count; i++ )
        datap->ed_x_center[i] = eye_center + datap->ed_x_sbm_center + datap->ed_x_shift;
    for( i = datap->eye_count; i < AAPL_ARRAY_LENGTH(datap->ed_x_center); i++ )
        datap->ed_x_center[i] = 0;


    set_x_center(datap, eye_center + datap->ed_x_shift);
    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__,__LINE__,"eye_center = %d\n", (datap->ed_x_min + datap->ed_x_max) / 2);
}

/** return 0 on success, < 0 on failure. */
static int initialize_for_eye_gather(
    Aapl_t *aapl,                             /**< [in] Pointer to Aapl_t structure. */
    uint addr,                                /**< [in] SBus slice address. */
    Eye_state_t *esp,                         /**< [in,out] Eye gathering state structure. */
    const Avago_serdes_eye_config_t *configp, /**< [in] Configuration parameters for how to gather the eye. */
    Avago_serdes_eye_data_t *datap)           /**< [out] Where to save the gathered eye data. */
{
    uint dfe_resume_status = 0;
    if( avago_serdes_dfe_pause(aapl, addr, &dfe_resume_status) == -1 && avago_serdes_dfe_wait(aapl, addr) == 0 )
        return aapl_fail(aapl,__func__,__LINE__,"EYE coordination with running DFE failed.\n");

    if( !init_eye_state(esp, aapl, addr, configp, datap) )
        return aapl_fail(aapl, __func__, __LINE__, "Error initializing hardware: returning %d\n",aapl->return_code);

    esp->dfe_resume_status = dfe_resume_status;

    if( 0 != eye_set_error_timer(esp, AVAGO_EYE_DEF_DWELL_BITS) )
        return -1;

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Centering in: SBus %s, x_UI=%u, x_points=%u, x_step=%u, x_res=%d, x_min=%d; x_center=%d, y_points=%u, y_step=%u, y_min=%d; y_center=%d\n",
            aapl_addr_to_str(addr), datap->ed_x_UI, datap->ed_x_points, datap->ed_x_step, datap->ed_x_resolution, datap->ed_x_min, (datap->ed_x_min+datap->ed_x_max)/2,
            datap->ed_y_points, datap->ed_y_step, datap->ed_y_min, datap->ed_y_center_point);

    sbm_eye_setup_serdes(esp);
    set_eye_center(esp);
    sbm_eye_set_options(esp);

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Centering out:SBus %s, x_UI=%u, x_points=%u, x_step=%u, x_res=%d, x_min=%d; x_center=%d, y_points=%u, y_step=%u, y_min=%d; y_center=%d\n",
            aapl_addr_to_str(addr), datap->ed_x_UI, datap->ed_x_points, datap->ed_x_step, datap->ed_x_resolution, datap->ed_x_min, (datap->ed_x_min+datap->ed_x_max)/2,
            datap->ed_y_points, datap->ed_y_step, datap->ed_y_min, datap->ed_y_center_point);

    eye_set_compare_mode(esp, datap->ed_cmp_mode);

    if( configp->ec_y_auto_scale && configp->ec_eye_type != AVAGO_EYE_WIDTH )
        adjust_y_scale(esp);
    if( configp->ec_x_auto_scale && configp->ec_eye_type != AVAGO_EYE_HEIGHT )
        adjust_x_scale(esp);

    eye_set_compare_mode(esp, datap->ed_cmp_mode);
    sbm_eye_set_options(esp);

    if( datap->eye_count == 6 )
    {
        int i;
        for( i = 0; i < datap->eye_count; i++ )
            datap->ed_hbtc[i].data_row = find_tune_row(esp,i);
        datap->ed_x_points = datap->ed_x_points * 2;
    }
    else
        datap->ed_hbtc[0].data_row = (datap->ed_y_points-1) / 2;

    if( allocate_eye_arrays(aapl, datap) < 0 )
        return -1;

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "AutoScale out:SBus %s, x_UI=%u, x_points=%u, x_step=%u, x_res=%d, x_min=%d; x_center=%d, y_points=%u, y_step=%u, y_min=%d; y_center=%d\n",
            aapl_addr_to_str(addr), datap->ed_x_UI, datap->ed_x_points, datap->ed_x_step, datap->ed_x_resolution, datap->ed_x_min, (datap->ed_x_min+datap->ed_x_max)/2,
            datap->ed_y_points, datap->ed_y_step, datap->ed_y_min, datap->ed_y_center_point);

    if( aapl->return_code < 0 )
        return -1;

    return 0;
}

static int force_mean_eye_points(Avago_serdes_eye_data_t *datap)
{
#if defined(MEAN_EYE_FORCE_GATHER) || defined(MEAN_EYE_FORCE_READ)
    if( datap->ed_x_points > 1 )
    {
        uint x;
        for( x = 0; x < datap->ed_x_points; ++x )
        {
            uint y;
            uint y1;
            bigint last_diff;

            const bigint *errs = get_errs_column(datap, x);
            const bigint *bits = get_bits_column(datap, x);

            bigint thresh = bits[0] / 16;

            y1 = 0;
            last_diff = errs[0] - thresh;
            for( y = 1; y < datap->ed_y_points; ++y ) {
                BOOL sign_change = FALSE;
                bigint this_diff;

                this_diff = errs[y] - thresh;
                if (this_diff > 0 && last_diff < 0) sign_change = TRUE;
                if (this_diff < 0 && last_diff > 0) sign_change = TRUE;

                if (sign_change) {
                    for( ; y1 < (y-1); ++y1 ) {
                            AVAGO_EYE_ERRORS_SET(*datap,x,y1,0);
                    }
                    y1 += 2;
                }
                last_diff = this_diff;
            }

            for(  ; y1 < datap->ed_y_points; ++y1 ) {
                AVAGO_EYE_ERRORS_SET(*datap,x,y1,0);
            }
        }
    }
#endif
    return 0;
}

/** @brief Copy from mission[which] to x_mid,ystart..y_end. */
static void copy_mission_column_to_data(Avago_serdes_eye_data_t *datap, int which, int x_mid, int y_start, int y_end)
{
    int y;
    for( y = y_start; y < y_end; y++ )
    {
        uint dac = get_dac_for_y_index(datap, y, FALSE);
        uint y_mission = (dac - datap->ed_y_mission_min) / datap->ed_y_mission_step;
        bigint my_errs = AVAGO_EYE_ERRORS_GET(*datap,x_mid,y);
        bigint my_bits = AVAGO_EYE_BITS_GET(  *datap,x_mid,y);
        bigint mission_errs = datap->ed_mission_errors[which][y_mission];
        bigint mission_bits = datap->ed_mission_bits  [which][y_mission];
        bigint merged_errs, merged_bits;
        if( my_bits == 0 )
        {
            merged_errs = mission_errs;
            merged_bits = mission_bits;
        }
        else if( my_bits == mission_bits )
        {
            merged_errs = MIN(my_errs, mission_errs);
            merged_bits = my_bits;
        }
        else
        {
            double my_ber = avago_calc_BER(my_errs, my_bits, 0.5);
            double mission_ber = avago_calc_BER(mission_errs, mission_bits, 0.5);
            if( my_ber <= mission_ber )
            {
                merged_errs = my_errs;
                merged_bits = my_bits;
            }
            else
            {
                merged_errs = mission_errs;
                merged_bits = mission_bits;
            }
        }
        AVAGO_EYE_ERRORS_SET(*datap,x_mid,y,merged_errs);
        AVAGO_EYE_BITS_SET(  *datap,x_mid,y,merged_bits);
    }
}

static void copy_mission_to_data(Avago_serdes_eye_data_t *datap)
{
    if( datap->ed_eye_type == AVAGO_EYE_SIZE || datap->ed_eye_type == AVAGO_EYE_HEIGHT )
    {
        int x_mide = get_eye_middle_x_index(datap, FALSE);

        copy_mission_column_to_data(datap, 0, x_mide, 0, datap->ed_y_points);

        if( datap->eye_count == 6 )
        {
            int x_mido = get_eye_middle_x_index(datap, TRUE);
            int y_mid  = (datap->ed_y_points-1) / 2 + 1;

            copy_mission_column_to_data(datap, 1, x_mido, 0, y_mid);

            copy_mission_column_to_data(datap, 4, x_mide, y_mid, datap->ed_y_points);
            copy_mission_column_to_data(datap, 5, x_mido, y_mid, datap->ed_y_points);

            copy_mission_column_to_data(datap, 2, x_mide, y_mid/2, datap->ed_y_points * 3 / 4);
            copy_mission_column_to_data(datap, 3, x_mido, y_mid/2, datap->ed_y_points * 3 / 4);
        }
    }
}

/** @brief   Gathers eye diagram measurements from a SerDes slice.
 ** @details See Avago_serdes_eye_config_t and Avago_serdes_eye_data_t for
 **          descriptions of configuration and return data values.
 **          Before returning, restores key SerDes values to original states.
 ** @return Returns 0 on success.
 ** @return Returns 1 if eye gather is canceled asynchronously.
 ** @return Returns -1 and decrements aapl->return_code on error.
 **/
int avago_serdes_eye_get(
    Aapl_t *aapl,                             /**< [in] Pointer to Aapl_t structure. */
    uint addr,                                /**< [in] SBus slice address. */
    const Avago_serdes_eye_config_t *configp, /**< [in] Configuration parameters for how to gather the eye. */
    Avago_serdes_eye_data_t *datap)           /**< [out] Where to save the gathered eye data. */
{
    Eye_state_t es;
    Eye_state_t *esp = &es;

    if( aapl_get_async_cancel_flag(aapl) )
        return 1;

    if( 0 != verify_eye_parameters(aapl, addr, configp) )
        return -1;

    if( aapl_get_async_cancel_flag(aapl) )
        return 1;


    {
        BOOL tx_ready = 0, rx_ready = 0;
        if( avago_serdes_get_tx_rx_ready(aapl, addr, &tx_ready, &rx_ready) != 0 || !rx_ready )
            return aapl_fail(aapl, __func__, __LINE__,
                "SBus %s, Eye measurement requires that the Rx be enabled and ready.\n", aapl_addr_to_str(addr));
    }

    if( 0 != initialize_for_eye_gather(aapl, addr, esp, configp, datap) )
        return -1;

    if( aapl_get_async_cancel_flag(aapl) )
        goto SEG_Reset;


    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "original cmp_mode = %s, phase_mult = %d, dac_min/step/points = %u,%u,%u\n",
                    aapl_cmp_mode_to_str(esp->orig_cmp_mode), esp->phase_mult, datap->ed_y_min, datap->ed_y_step, datap->ed_y_points);



    if( eye_set_error_timer(&es, es.datap->ed_min_dwell_bits) < 0 )
        goto SEG_Reset;




    if( configp->ec_eye_type == AVAGO_EYE_FULL )
    {
        if( !gather_full_eye(esp) )
            goto SEG_Reset;
    }
    else
    {
        if( configp->ec_eye_type != AVAGO_EYE_HEIGHT && !gather_eye_width(esp) )
            goto SEG_Reset;

        if( configp->ec_eye_type != AVAGO_EYE_WIDTH && !gather_eye_height(esp) )
            goto SEG_Reset;
    }

    eye_dynamic_dwell(esp);

    copy_mission_to_data(datap);

    if ( configp->ec_gather_mean )
        force_mean_eye_points(datap);

    serdes_eye_calc_gradient(esp->datap);
    serdes_eye_calc_qval(esp->aapl,esp->datap);

    calc_width(esp->aapl, datap);
    if( configp->ec_eye_type != AVAGO_EYE_WIDTH ) calc_height(esp->aapl, datap, -1);

    avago_serdes_eye_plot_log_print(aapl, AVAGO_DEBUG2, __func__, __LINE__, datap);

    if( esp->timeout_count > 0 )
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "SBus %s, %u timeouts detected during eye gather.\n", aapl_addr_to_str(addr), esp->timeout_count);

goto SEG_Exit;

SEG_Reset:
    if( aapl_get_async_cancel_flag(aapl) )
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__,"SBus %s, Eye exit due to cancel request.\n", aapl_addr_to_str(addr));
    else
        aapl_fail(aapl, __func__, __LINE__,"SBus %s, Eye abnormal exit.\n",aapl_addr_to_str(addr));

SEG_Exit:
    restore_serdes_state(esp);
    return aapl_get_async_cancel_flag(aapl) ? 1 : aapl->return_code < 0 ? -1 : 0;

}

/** @brief  Displays a num line with numeric labels every 5th character. */
static char *print_num_header(char *ptr, const Avago_serdes_eye_data_t *datap)
{
    ptr += sprintf(ptr, "UI/%-3d ", datap->ed_x_resolution);
    if(      datap->ed_x_points == 1 ) ptr += sprintf(ptr, "0");
    else if( datap->ed_x_points == 2 ) ptr += sprintf(ptr, "00");
    else
    {
        int max_eye = datap->eye_count == 6 || datap->eye_count == 2 ? 2 : 1;
        int eye;
        int x_center = datap->ed_x_UI * datap->ed_x_resolution / 2;
        for( eye = 0; eye < max_eye; eye++ )
        {
            int i;
            int skip = (x_center-2)%5;
            for( i = 0; i < skip; i++ )              ptr += sprintf(ptr, " ");
            for( i = -(x_center-2)/5; i < -1; i++  ) ptr += sprintf(ptr, "%4d ", i*5);
                                                     ptr += sprintf(ptr, " -5    0    5 ");
            for( i = 2; i <= (x_center-1)/5; i++  )  ptr += sprintf(ptr, "%5d", i*5);
            if( max_eye == 2 && eye == 0 )
            {
                skip = (x_center-1) % 5;
                for( i = 0; i < skip; i++ ) ptr += sprintf(ptr, " ");
            }
        }
    }
    ptr += sprintf(ptr, "\n");
    return ptr;
}

/** @brief  Displays a tic line with vertical bars every 5th character. */
static char *print_tic_header(char *ptr, const Avago_serdes_eye_data_t *datap)
{
    int max_eye = datap->eye_count == 6 || datap->eye_count == 2 ? 2 : 1;
    int eye;
    int x_center = datap->ed_x_UI * datap->ed_x_resolution / 2;
    ptr += sprintf(ptr, "       ");
    for( eye = 0; eye < max_eye; eye++ )
    {
        int i;
        for( i = -x_center; i <= x_center; i++ )
        {
            if( i % 5 == 0 ) ptr += sprintf(ptr,"|");
            else             ptr += sprintf(ptr,"-");
        }
    }
    ptr += sprintf(ptr, "\n");
    return ptr;
}

#define        ROW_DELIM ':'
#define CENTER_ROW_DELIM '='

/** @brief  Create a simple ascii text eye.
 ** @return A string containing the eye or NULL upon allocation error.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_plot_format(
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to display */
{
    const uint threshold1 = datap->ed_error_threshold;
    const uint threshold2 = threshold1 * 10;
    const uint threshold3 = threshold2 * 10;
    const uint threshold4 = threshold3 * 10;
    uint x_points = gather_separate_even_odd(datap) ? datap->ed_x_points/2 : datap->ed_x_points;
    uint y = datap->ed_y_points;
    uint upper_threshold = MIN(datap->ed_y_points, (datap->ed_hbtc[2].data_row + datap->ed_hbtc[4].data_row) / 2);
    uint lower_threshold = MIN(datap->ed_y_points, (datap->ed_hbtc[0].data_row + datap->ed_hbtc[2].data_row) / 2);
    uint alloc_size = (datap->ed_x_points+15)*(datap->ed_y_points+4) + 80;
    char *buf = (char *)AAPL_MALLOC(alloc_size);
    char *ptr = buf;
    if( !buf ) return 0;

    ptr += sprintf(ptr,"\nEye Plot");
    if( datap->eye_count == 6 ) ptr += sprintf(ptr," (even on the left, odd on the right)");
    *ptr++ = '\n';

    if( !datap->ed_errorsp || !datap->ed_bitsp )
        return *buf = '\0',buf;

    ptr = print_num_header(ptr, datap);
    ptr = print_tic_header(ptr, datap);

    while( y-- > 0 )
    {
        BOOL print_line = FALSE;
        uint x;
        int y_odd = y;
        int y_even = y;
        int even_row, odd_row;
        BOOL center_row = FALSE;
        BOOL row_delim = ROW_DELIM;

#if 1
        if( y >= upper_threshold )
            y_odd = y + datap->ed_hbtc[5].data_row - datap->ed_hbtc[4].data_row;
        else if( y >= lower_threshold )
            y_odd = y + datap->ed_hbtc[3].data_row - datap->ed_hbtc[2].data_row;
        else
            y_odd = y + datap->ed_hbtc[1].data_row - datap->ed_hbtc[0].data_row;

        if( y_odd >= (int)datap->ed_y_points ) y_odd = datap->ed_y_points - 1;
        else if( y_odd < 0 ) y_odd = 0;
#endif
        even_row = get_dac_for_y_index(datap, y_even, FALSE) - datap->ed_y_center_point;
        odd_row = get_dac_for_y_index(datap, y_odd, FALSE) - datap->ed_y_center_point;

        for( x = 0; x < datap->ed_x_points; x++ )
        {
            int e_o = x < x_points ? 0 : 1;
            uint y_index = e_o ? y_odd : y_even;
            bigint bits = get_bits_column(datap, (int)x)[y_index];
            if( bits > 0 )
            {
                print_line = TRUE;
                break;
            }
        }
        if( !print_line ) continue;

        for( x = 0; x < datap->ed_x_points; x++ )
        {
            int e_o = x < x_points ? 0 : 1;
            uint y_index = e_o ? y_odd : y_even;
            bigint bits = get_bits_column(datap, (int)x)[y_index];
            bigint errs = get_errs_column(datap, (int)x)[y_index];

            if( x == 0 || x == x_points )
            {
                int e_o = x == 0 ? 0 : 1;
                if( datap->ed_hbtc[0+e_o].data_row == y_index ||
                    datap->ed_hbtc[2+e_o].data_row == y_index ||
                    datap->ed_hbtc[4+e_o].data_row == y_index ||
                   (datap->ed_hbtc[1    ].data_row == y_index && datap->eye_count == 3) )
                {
                    center_row = TRUE;
                    row_delim = CENTER_ROW_DELIM;
                }
                if( x == 0 )
                    ptr += sprintf(ptr,"%4d %c ", even_row, row_delim);
            }

            if( bits <= 0 )
                ptr[x] = '-';
            else if( errs == 0 )
            {
                char row_char, col_char;
                if( x == x_points / 2 || x == x_points + x_points / 2 )
                     { row_char = '+'; col_char = '!'; }
                else { row_char = '-'; col_char = ' '; }

                ptr[x] = center_row ? row_char : col_char;
            }
            else if( errs <= threshold1 )
                ptr[x] = '.';
            else if( errs <= threshold2 )
                ptr[x] = '+';
            else if( errs <= threshold3 )
                ptr[x] = '*';
            else if( x == x_points / 2 || x == x_points + x_points / 2 )
                ptr[x] = '|';
            else if( datap->ed_hbtc[0+e_o].data_row == y_index )
                ptr[x] = '=';
            else if( datap->ed_hbtc[2+e_o].data_row == y_index && y_index != 0)
                ptr[x] = '=';
            else if( datap->ed_hbtc[4+e_o].data_row == y_index && y_index != 0)
                ptr[x] = '=';
            else if( errs <= threshold4 )
                ptr[x] = '@';
            else
                ptr[x] = '#';
        }
        ptr += datap->ed_x_points;
        if( x_points != datap->ed_x_points ) ptr += sprintf(ptr," %c %4d", row_delim, odd_row);
        *ptr++ = '\n';
    }
    ptr = print_tic_header(ptr, datap);
    ptr = print_num_header(ptr, datap);
    *ptr = '\0';
    return buf;
}

/** @brief  Create a simple text gradient eye.
 ** @return A string containing the eye or NULL upon allocation error.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_gradient_plot_format(
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to display */
{
    const float threshold1 = 0.0001;
    const float threshold2 = 0.0040;
    const float threshold3 = 0.0140;
    const float threshold4 = 0.0300;
    const float threshold5 = 0.1000;
    uint x_points = gather_separate_even_odd(datap) ? datap->ed_x_points/2 : datap->ed_x_points;
    uint y = datap->ed_y_points;
    uint upper_threshold = MIN(datap->ed_y_points, (datap->ed_hbtc[2].data_row + datap->ed_hbtc[4].data_row) / 2);
    uint lower_threshold = MIN(datap->ed_y_points, (datap->ed_hbtc[0].data_row + datap->ed_hbtc[2].data_row) / 2);
    uint alloc_size = (datap->ed_x_points+15)*(datap->ed_y_points+4) + 80;
    char *buf = (char *)AAPL_MALLOC(alloc_size);
    char *ptr = buf;
    if( !buf ) return 0;

    ptr += sprintf(ptr,"\nEye Gradient Plot");
    if( datap->eye_count == 6 ) ptr += sprintf(ptr," (even on the left, odd on the right)");
    *ptr++ = '\n';

    if( !datap->ed_errorsp || !datap->ed_bitsp )
        return *buf = '\0',buf;

    ptr = print_num_header(ptr, datap);
    ptr = print_tic_header(ptr, datap);

    while( y-- > 1 )
    {
        uint x;
        int y_odd = y;
        int y_even = y;
        int even_row, odd_row;
        BOOL center_row = FALSE;
        char row_delim = ROW_DELIM;

#if 1
        if( y >= upper_threshold )
            y_odd = y + datap->ed_hbtc[5].data_row - datap->ed_hbtc[4].data_row;
        else if( y >= lower_threshold )
            y_odd = y + datap->ed_hbtc[3].data_row - datap->ed_hbtc[2].data_row;
        else
            y_odd = y + datap->ed_hbtc[1].data_row - datap->ed_hbtc[0].data_row;

        if( y_odd >= (int)datap->ed_y_points ) y_odd = datap->ed_y_points - 1;
        else if( y_odd < 0 ) y_odd = 0;
#endif
        even_row = get_dac_for_y_index(datap, y_even, FALSE) - datap->ed_y_center_point;
        odd_row = get_dac_for_y_index(datap, y_odd, FALSE) - datap->ed_y_center_point;

        for( x = 0; x < datap->ed_x_points; x++ )
        {
            int e_o = x < x_points ? 0 : 1;
            uint y_index = e_o ? y_odd : y_even;
            bigint bits = AVAGO_EYE_BITS_GET(*datap,x,y_index);
            float grad = AVAGO_EYE_GRAD_GET(*datap,x,y_index);

            if( x == 0 || x == x_points )
            {
                int e_o = x == 0 ? 0 : 1;
                if( datap->ed_hbtc[0+e_o].data_row == y_index ||
                    datap->ed_hbtc[2+e_o].data_row == y_index ||
                    datap->ed_hbtc[4+e_o].data_row == y_index ||
                   (datap->ed_hbtc[1    ].data_row == y_index && datap->eye_count == 3) )
                {
                    center_row = TRUE;
                    row_delim = CENTER_ROW_DELIM;
                }
                if( x == 0 )
                    ptr += sprintf(ptr,"%4d %c ", even_row, row_delim);
            }

            if( bits <= 0 )
                ptr[x] = '-';
            else if( grad < threshold1 )
            {
                char row_char, col_char;
                if( x == x_points / 2 || x == x_points + x_points / 2 )
                     { row_char = '+'; col_char = '!'; }
                else { row_char = '-'; col_char = ' '; }

                ptr[x] = center_row ? row_char : col_char;
            }
            else if( grad < threshold2 )
                ptr[x] = '.';
            else if( grad < threshold3 )
                ptr[x] = ':';
            else if( grad < threshold4 )
                ptr[x] = '+';
            else if( x == x_points / 2 || x == x_points + x_points / 2 )
                ptr[x] = '|';
            else if( datap->ed_hbtc[2+e_o].data_row == y_index && y_index != 0 )
                ptr[x] = '=';
            else if( datap->ed_hbtc[4+e_o].data_row == y_index && y_index != 0 )
                ptr[x] = '=';
            else if( datap->ed_hbtc[0+e_o].data_row == y_index )
                ptr[x] = '=';
            else if( grad < threshold5 )
                ptr[x] = '*';
            else
                ptr[x] = '#';
        }
        ptr += datap->ed_x_points;
        if( x_points != datap->ed_x_points ) ptr += sprintf(ptr," %c %4d", row_delim, odd_row);
        *ptr++ = '\n';
    }
    ptr = print_tic_header(ptr, datap);
    ptr = print_num_header(ptr, datap);
    *ptr = '\0';
    return buf;
}


/** @brief  Create a simple text qval contour eye.
 ** @return A string containing the eye or NULL upon allocation error.
 **         The caller should AAPL_FREE the returned string.
 **/
char *avago_serdes_eye_contour_plot_format(
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to display */
{
#if AAPL_ALLOW_ANSI_COLORS
    const char *color = "\x1B[1m";
    const char *end_color = "\x1B[0m";
#else
    const char *color = "";
    const char *end_color = "";
#endif
    uint y = datap->ed_y_points;
    uint x_points = gather_separate_even_odd(datap) ? datap->ed_x_points/2 : datap->ed_x_points;
    uint upper_threshold = MIN(datap->ed_y_points, (datap->ed_hbtc[2].data_row + datap->ed_hbtc[4].data_row) / 2);
    uint lower_threshold = MIN(datap->ed_y_points, (datap->ed_hbtc[0].data_row + datap->ed_hbtc[2].data_row) / 2);
    uint alloc_size = (datap->ed_x_points+31)*(datap->ed_y_points+4) + 80;
    char *buf = (char *)AAPL_MALLOC(alloc_size);
    char *ptr = buf;
    if( !buf ) return 0;

    ptr += sprintf(ptr,"\nEye Q-value Contour Plot");
    if( datap->eye_count == 6 ) ptr += sprintf(ptr," (even on the left, odd on the right)");
    *ptr++ = '\n';

    if( !datap->ed_errorsp || !datap->ed_bitsp )
        return *buf = '\0',buf;

    ptr = print_num_header(ptr, datap);
    ptr = print_tic_header(ptr, datap);

    ptr += sprintf(ptr,"%s",end_color);
    while( y-- > 0 )
    {
        uint x;
        int y_odd = y;
        int y_even = y;
        int even_row, odd_row;
        BOOL center_row = FALSE;
        char row_delim = ROW_DELIM;

#if 1
        if( y >= upper_threshold )
            y_odd = y + datap->ed_hbtc[5].data_row - datap->ed_hbtc[4].data_row;
        else if( y >= lower_threshold )
            y_odd = y + datap->ed_hbtc[3].data_row - datap->ed_hbtc[2].data_row;
        else
            y_odd = y + datap->ed_hbtc[1].data_row - datap->ed_hbtc[0].data_row;

        if( y_odd >= (int)datap->ed_y_points ) y_odd = datap->ed_y_points - 1;
        else if( y_odd < 0 ) y_odd = 0;
#endif
        even_row = get_dac_for_y_index(datap, y_even, FALSE) - datap->ed_y_center_point;
        odd_row = get_dac_for_y_index(datap, y_odd, FALSE) - datap->ed_y_center_point;

        for( x = 0; x < datap->ed_x_points; x++ )
        {
            int e_o = x < x_points ? 0 : 1;
            uint y_index = e_o ? y_odd : y_even;
            float qval = AVAGO_EYE_QVAL_GET(*datap,x,y_index);
            BOOL center_column = x_points / 2 == x || x_points + x_points / 2 == x;
            BOOL color_column;

            if( x == 0 || x == x_points )
            {
                int e_o = x == 0 ? 0 : 1;
                if( center_row )
                {
                    ptr += sprintf(ptr,"%s",end_color);
                    center_row = FALSE;
                }
                if( datap->ed_hbtc[0+e_o].data_row == y_index ||
                    datap->ed_hbtc[2+e_o].data_row == y_index ||
                    datap->ed_hbtc[4+e_o].data_row == y_index ||
                   (datap->ed_hbtc[1    ].data_row == y_index && datap->eye_count == 3) )
                {
                    ptr += sprintf(ptr,"%s",color);
                    center_row = TRUE;
                    row_delim = CENTER_ROW_DELIM;
                }
                if( x == 0 )
                    ptr += sprintf(ptr,"%4d %c ", even_row, row_delim);
            }
            color_column = center_column && !center_row;

            if( color_column ) ptr += sprintf(ptr,"%s",color);
            if( qval >= 10.0 )
            {
                if(      center_column                         ) *ptr++ = '|';
                else if( datap->ed_hbtc[0].data_row == y_index ) *ptr++ = '-';
                else                                             *ptr++ = ' ';
            }
#if AAPL_ALLOW_ANSI_COLORS
            else if( qval >= 1.0 )
                *ptr++ = '0' + (int)qval % 10;
#else
            else if( qval >= 1.0 )
            {
                char c = '0' + (int)qval % 10;
                if(      !(c & 1) && center_column                         ) *ptr++ = '|';
                else if( !(c & 1) && datap->ed_hbtc[0].data_row == y_index ) *ptr++ = '-';
                else                                                         *ptr++ = c;
            }
            else if( center_column )
                *ptr++ = '|';
            else if( datap->ed_hbtc[2+e_o].data_row == y_index )
                *ptr++ = '=';
            else if( datap->ed_hbtc[4+e_o].data_row == y_index )
                *ptr++ = '=';
            else if( datap->ed_hbtc[0+e_o].data_row == y_index )
                *ptr++ = '=';
#endif
            else
                *ptr++ = '0';
            if( color_column ) ptr += sprintf(ptr,"%s",end_color);
        }
        if( x_points != datap->ed_x_points ) ptr += sprintf(ptr," %c %4d", row_delim, odd_row);
        if( center_row                     ) ptr += sprintf(ptr,"%s",end_color);
        *ptr++ = '\n';
    }
    ptr = print_tic_header(ptr, datap);
    ptr = print_num_header(ptr, datap);
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
    if(( (aapl->debug & 0xf) >= (uint)level ) || (level >= AVAGO_MEM_LOG ))
    {
        char *eye_text = avago_serdes_eye_plot_format(datap);
        if( eye_text )
        {
            aapl_log_add(aapl, level, eye_text, caller, line);
            AAPL_FREE(eye_text);
        }
    }
}

#if AAPL_ENABLE_FILE_IO

/** @brief Write a simple ascii text eye to a file. */
void avago_serdes_eye_plot_write(
    FILE *file,                             /**< Where to print the eye */
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to print */
{
    char *eye_text = avago_serdes_eye_plot_format(datap);
    if( eye_text )
    {
        fputs(eye_text,file);
        AAPL_FREE(eye_text);
    }
}

/** @brief Write a simple text gradient eye to a file. */
void avago_serdes_eye_gradient_plot_write(
    FILE *file,                             /**< Where to print the eye */
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to print */
{
    char *eye_text = avago_serdes_eye_gradient_plot_format(datap);
    if( eye_text )
    {
        fputs(eye_text,file);
        AAPL_FREE(eye_text);
    }
}

/** @brief Write a simple text gradient eye to a file. */
void avago_serdes_eye_contour_plot_write(
    FILE *file,                             /**< Where to print the eye */
    const Avago_serdes_eye_data_t *datap)   /**< Eye data to print */
{
    char *eye_text = avago_serdes_eye_contour_plot_format(datap);
    if( eye_text )
    {
        fputs(eye_text,file);
        AAPL_FREE(eye_text);
    }
}


static void write_phase_data(FILE *file, const Avago_serdes_eye_data_t *datap)
{
    if( datap->ed_phase_table )
    {
        uint i;
        fprintf(file, "phase_data: %d,1,%.2f", datap->ed_phase_table_len, datap->ed_phase_center);
        for( i = 0; i < datap->ed_phase_table_len; i++ )
            fprintf(file, ", %.2f", datap->ed_phase_table[i]);
        fprintf(file, "\n");
        fprintf(file, "phase_inl: %u", datap->ed_x_points);
        for( i = 0; i < datap->ed_x_points; i++ )
            fprintf(file, ", %.2f", mui_from_index(datap, i));
        fprintf(file, "\n");
    }
}
static int read_float(const char *str, float *arg)
{
    const char *ptr;
    if( 1 == sscanf(str,"%9f",arg) && (ptr = strchr(str,',')) != 0 )
        return ptr-str+1;
    return strlen(str);
}
static uint read_uint(const char *str, uint *arg)
{
    const char *ptr;
    if( 1 == sscanf(str,"%9u",arg) && (ptr = strchr(str,',')) != 0 )
        return ptr-str+1;
    return strlen(str);
}
static BOOL parse_phase_data(Aapl_t *aapl, Avago_serdes_eye_data_t *datap, const char *str)
{
    uint i = 0;
    uint extra_items;
    const char *ptr;
    str += read_uint(str, &datap->ed_phase_table_len);
    str += read_uint(str, &extra_items);

    str += read_float(str, &datap->ed_phase_center);
    extra_items -= 1;
    while( extra_items-- > 0 && (ptr = strchr(str,',')) != 0 ) str = ptr + 1;

    datap->ed_phase_table = (float *)aapl_realloc(aapl, datap->ed_phase_table, datap->ed_phase_table_len * sizeof(datap->ed_phase_table[0]), "phase_table");
    if( datap->ed_phase_table )
    {
        int len;
        while( i < datap->ed_phase_table_len && (len = read_float(str, &datap->ed_phase_table[i])) > 0 )
        {
            str += len;
            i++;
        }
    }
    return i == datap->ed_phase_table_len;
}


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
    fprintf(file,"AAPL_version:   " AAPL_VERSION ", compiled %s %s\n",__DATE__,__TIME__);
    fprintf(file,"capture_date:   %s\n", time_str);
    if( datap->ed_comment )
        fprintf(file,"user_comment:   %s\n",datap->ed_comment);
    fprintf(file,"\n");
    if( datap->ed_hardware_log )
        fprintf(file,"%s\n", datap->ed_hardware_log);

    fprintf(file,"eye_type:       %s\n", aapl_eye_type_to_str(datap->ed_eye_type));
    fprintf(file,"compare_mode:   %s\n", aapl_cmp_mode_to_str(datap->ed_cmp_mode));
    fprintf(file,"\n");

    if( datap->eye_count > 0 )
        fprintf(file,"eye_count:        %3d\n", datap->eye_count);
    fprintf(file,"x.UI:             %3d\n",datap->ed_x_UI);
    fprintf(file,"x.resolution:     %3d  # Steps per UI\n",datap->ed_x_resolution);
    fprintf(file,"x.points:         %3d  # Data array dimension\n",datap->ed_x_points);
    fprintf(file,"x.min:            %3d\n",datap->ed_x_min);
    fprintf(file,"x.max:            %3u\n",datap->ed_x_max);
    fprintf(file,"x.step:           %3d\n",datap->ed_x_step);
    fprintf(file,"x.sbm_center:     %3d\n",datap->ed_x_sbm_center);
    fprintf(file,"x.adj_center:     %3d  # Relative to sbm_center; before any manual shift\n",(datap->ed_x_min + datap->ed_x_max) / 2 - datap->ed_x_shift);
    fprintf(file,"x.center:         %3d", datap->ed_x_center[0]);
    if( datap->ed_hbtc[1].data_row < datap->ed_y_points )
    {
        int i;
        for( i = 1; i < datap->eye_count; i++ )
            fprintf(file,", %3d", datap->ed_x_center[i]);
        fprintf(file, " # Eye center phase (le, lo, me, mo, ue, uo)\n");
    }
    else
    fprintf(file, " # Eye center phase\n");
    fprintf(file,"x.shift:          %3d  # Manual adjustment\n",datap->ed_x_shift);
    fprintf(file,"x.width:          %3d\n",datap->ed_width);
    fprintf(file,"x.width_mUI:      %3d\n",datap->ed_width_mUI);
    fprintf(file,"\n");

    fprintf(file,"y.resolution:     %3d  # DAC range\n",datap->ed_y_resolution);
    fprintf(file,"y.points:         %3d  # Data array dimension\n",datap->ed_y_points);
    fprintf(file,"y.step:           %3d\n",datap->ed_y_step);
    fprintf(file,"y.min:            %3d  # DAC for y=0\n",datap->ed_y_min);
    fprintf(file,"y.mission_points: %3d\n",datap->ed_y_mission_points);
    fprintf(file,"y.mission_step:   %3d\n",datap->ed_y_mission_step);
    fprintf(file,"y.mission_min:    %3d  # DAC for y=0\n",datap->ed_y_mission_min);
    fprintf(file,"y.center_row:     %3d", datap->ed_hbtc[0].data_row);
    if( datap->ed_hbtc[1].data_row < datap->ed_y_points )
    {
        int i;
        for( i = 1; i < datap->eye_count; i++ )
            fprintf(file,", %3d", datap->ed_hbtc[i].data_row);
        fprintf(file," # eye center y indices (le, lo, me, mo, ue, uo)\n");
    }
    else
    fprintf(file," # eye center y index\n");
    fprintf(file,"y.center:         %3d  # DAC middle\n", get_dac_for_y_index(datap, (datap->ed_y_points-1) / 2, FALSE));
    fprintf(file,"y.height:         %3d\n",datap->ed_height);
    fprintf(file,"y.height_mV:      %3d\n",datap->ed_height_mV);
    fprintf(file,"\n");

    fprintf(file,"dc_balance:         %g\n", datap->ed_dc_balance);
    fprintf(file,"trans_density:      %g\n", datap->ed_trans_density);
    fprintf(file,"avdd:               %-.2f     # V\n", datap->ed_avdd);
    fprintf(file,"dac_scale:          %g  # mV/step\n", datap->ed_dac_scale);
    fprintf(file,"\n");
    fprintf(file,"error_threshold: %8d\n",  datap->ed_error_threshold);
    fprintf(file,"min_dwell_bits:  %8g\n",  datap->ed_min_dwell_bits*1.0);
    fprintf(file,"max_dwell_bits:  %8g\n",  datap->ed_max_dwell_bits*1.0);
    fprintf(file,"fast_dynamic:    %8d\n",  datap->ed_fast_dynamic);
    if( datap->ed_phase_center_log )
        fprintf(file,"\ncenter_data:  %s\n\n", datap->ed_phase_center_log);
    write_phase_data(file, datap);
    fprintf(file,"\n");

    fprintf(file,"# Phase index, DAC index, Errors, Bits\n");
    if( datap->ed_y_mission_points > 1 )
    {
        int x;
        if( datap->eye_count == 6 )
            fprintf(file,"# Mission data (-6=uo, -5=ue, -4=mo, -3=me, -2=lo, -1=le\n");
        else
            fprintf(file,"# Mission data:\n");
        for( x = -datap->eye_count; x < 0; x++ )
        {
            const bigint *errs = get_errs_column(datap, x);
            const bigint *bits = get_bits_column(datap, x);
            uint y;
            for( y = 0; y < datap->ed_y_mission_points; y++ )
                if( bits[y] != 0 )
                {
                    fprintf(file,"%3d, %3u, %6s, %13s", x, y, aapl_bigint_to_str(errs[y]), aapl_bigint_to_str(bits[y]));
                    fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y));
                    if( y > 0 ) fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y-1) - avago_serdes_eye_qval_get(0,datap,x,y));
                    fprintf(file,"\n");
                }
        }
    }
    if( datap->ed_x_points >= 1 )
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
#ifdef MEAN_EYE_FORCE_WRITE
                    if ( datap->ed_gather_mean && errs[y] == 0 ) continue;
#endif
                    fprintf(file,"%3u, %3u, %6s, %13s", x, y, aapl_bigint_to_str(errs[y]), aapl_bigint_to_str(bits[y]));
                    fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y));
                    if( y > 0 ) fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x,y-1) - avago_serdes_eye_qval_get(0,datap,x,y));
                    if( x > 0 ) fprintf(file," %9f", avago_serdes_eye_qval_get(0,datap,x-1,y) - avago_serdes_eye_qval_get(0,datap,x,y));
                    fprintf(file,"\n");
                }
        }
    }

    {
        int i;
        for( i = 0; i < datap->eye_count; i++ )
        {
            int which = datap->eye_count == 6 ? (i%2) + 2 * (2 - i/2) : datap->eye_count-1-i;
            avago_serdes_eye_vbtc_write(file, &datap->ed_vbtc[which]);
        }
        for( i = 0; i < datap->eye_count; i++ )
        {
            int which = datap->eye_count == 6 ? (i%2) + 2 * (2 - i/2) : datap->eye_count-1-i;
            avago_serdes_eye_hbtc_write(file, &datap->ed_hbtc[which]);
        }
        avago_serdes_eye_btc_write(file, datap);
    }

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
 ** @see avago_serdes_eye_data_read_file().
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
    fprintf(stderr,"Error opening file \"%s\" for writing: %s.\n", file_name, strerror(errno));
    return -1;
}

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
    return (int) aapl_strtol(str,0,0);
}

static bigint getbigint(const char *str)
{
#ifdef _MSC_VER
    return (bigint) _strtoi64(str,0,0);
#else
    return (bigint) strtoll(str,0,0);
#endif
}

/** @brief   Reads a name and value from buf.
 ** @details Buf contains a name value pair separated by one or more white
 **          space, colon and equal sign characters.
 **          Locates and nul terminates the name, and
 **          stores any integer value into *value.
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
    *value = aapl_strtol(*value_string,&ptr,0);
    buf += strcspn(buf,"\r\n");
    while( buf > *value_string && (buf[-1] == ' ' || buf[-1] == '\t') )
        buf--;
    *buf = '\0';

    if( **name == '#' ) return 0;
    return 2;
}

/** @brief Parse string for an array of integers, extracting and storing up to count integers into array.
 ** @return Return the number of integers stored.
 **/
static int read_int_array(const char *string, int count, int *array)
{
    const char *seps = ", ";
    int i;
    for( i = 0; i < count; i++ )
    {
        char *ptr;
        string += strspn(string,seps);
        array[i] = strtol(string,&ptr,0);
        if( ptr == string ) break;
        string = ptr;
    }
    return i;
}

/** @brief   Loads phase data from a file.
 ** @details Does not require AAPL connection to any hardware.
 ** @return  Returns 0 on success, non-zero on error, and logs specific problem.
 **/
int avago_serdes_eye_data_read_phase(
    Aapl_t *aapl,                   /**< Pointer to Aapl_t structure. */
    const char *filename,           /**< Name of file containing phase data */
    Avago_serdes_eye_data_t *datap) /**< Where to save phase data */
{
    int ret = -1;
    char *buf = aapl_read_file(aapl, filename);
    if( buf )
    {
        char *ptr = strstr(buf,"phase_data:");
        if( ptr )
        {
            ret = parse_phase_data(aapl, datap, ptr + 11);
#if 0
            printf("center=%f, table=", datap->ed_phase_center);
            for( uint i = 0; i < datap->ed_phase_table_len; i++ )
                printf(",%6.2f", datap->ed_phase_table[i]);
            printf("\n");
#endif
        }
        else
            ret = aapl_fail(aapl, __func__, __LINE__, "Can't find \"phase_data:\" in file \"%s\"\n", filename);

        aapl_free(aapl, buf, "phase_data");
    }
    else
        ret = aapl_fail(aapl, __func__, __LINE__, "Can't open \"%s\": %s\n", filename, strerror(errno));
    return ret;
}

/** @brief   Loads eye data from a file.
 ** @details Does not require AAPL connection to any hardware.
 ** @return  Returns 0 on success, non-zero on error, and logs specific problem.
 ** @see     avago_serdes_eye_data_write_file().
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
    char *ptr = datap->ed_hardware_log = (char *)aapl_malloc(aapl,300,__func__);
    float avdd = datap->ed_avdd;

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "%s\n",filename);

    if( !file )
        return aapl_fail(aapl, __func__, __LINE__, "ERROR opening file %s\n",filename);

    if( ptr == 0 )
    {
        fclose(file);
        return -1;
    }
    *ptr = '\0';

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
    datap->eye_count = 1;


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

            if( count == 0 && str_val && 0 == strncmp(str_val,"Phase", 5) && 0!=strstr(str_val+6,"index") )
            {
                allocate_eye_arrays(aapl, datap);
                in_header = FALSE;
            }
            if( count != 2 ) continue;


            if     ( EQS(name,"eye_count"       ) ) datap->eye_count = (uint)value;
            else if( EQS(name,"x.width"         ) ) datap->ed_width = (uint)value;
            else if( EQS(name,"y.height"        ) ) datap->ed_height = (uint)value;

            else if( EQS(name,"x.width_mUI"     ) ) datap->ed_width_mUI = (uint)value;
            else if( EQS(name,"y.height_mV"     ) ) datap->ed_height_mV = (uint)value;

            else if( EQS(name,"x.UI"            ) ) datap->ed_x_UI = (uint)value;
            else if( EQS(name,"x.points"        ) ) datap->ed_x_points = MIN((uint)value, 8193U);
            else if( EQS(name,"x.step"          ) ) datap->ed_x_step = (uint)value;
            else if( EQS(name,"x.resolution"    ) ) datap->ed_x_resolution = (uint)value;

            else if( EQS(name,"x.min"           ) ) datap->ed_x_min = (int)value;
            else if( EQS(name,"x.max"           ) ) datap->ed_x_max = (int)value;
            else if( EQS(name,"x.shift"         ) ) datap->ed_x_shift = (int)value;
            else if( EQS(name,"x.sbm_center"    ) ) datap->ed_x_sbm_center = (int)value;
            else if( EQS(name,"x.center2-3"     ) ) datap->ed_x_center[2] = (int)value;
            else if( EQS(name,"x.center1-2"     ) ) datap->ed_x_center[1] = (int)value;
            else if( EQS(name,"x.center0-1"     ) ) datap->ed_x_center[0] = (int)value;
            else if( EQS(name,"x.center"        ) ){ int i, values[6], n = read_int_array(str_val, 6, values);
                                                     for( i = 0; i < n; i++ )
                                                        datap->ed_x_center[i] = values[i];
                                                   }

            else if( EQS(name,"y.resolution"    ) ) datap->ed_y_resolution = (uint)value;
            else if( EQS(name,"y.center_row"    ) ){ int i, values[6], n = read_int_array(str_val, 6, values);
                                                     for( i = 0; i < n; i++ )
                                                        datap->ed_hbtc[i].data_row = values[i];
                                                   }
            else if( EQS(name,"y.center2-3"     ) ){datap->ed_hbtc[2].data_row = (uint)value; if( value != -1 ) datap->eye_count = 3; }
            else if( EQS(name,"y.center1-2"     ) ) datap->ed_hbtc[1].data_row = (uint)value;
            else if( EQS(name,"y.center0-1"     ) ) datap->ed_hbtc[0].data_row = (uint)value;
            else if( EQS(name,"y.points"        ) ) datap->ed_y_points = MIN((uint)value, AAPL_MAX_DAC_RANGE);
            else if( EQS(name,"y.step"          ) ) datap->ed_y_step = (uint)value;
            else if( EQS(name,"y.min"           ) ) datap->ed_y_min = (uint)value;
            else if( EQS(name,"y.mission_points") ) datap->ed_y_mission_points = MIN((uint)value, (uint)AAPL_ARRAY_LENGTH(datap->ed_mission_errors[0]));
            else if( EQS(name,"y.mission_step"  ) ) datap->ed_y_mission_step = (uint)value;
            else if( EQS(name,"y.mission_min"   ) ) datap->ed_y_mission_min = (uint)value;

            else if( EQS(name,"SBus_address"    ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"JTAG_ID"         ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"Process_ID"      ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"SBus_master"     ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);
            else if( EQS(name,"SerDes"          ) ) ptr += sprintf(ptr,"%s:%*s%s\n",name,(int)(15-strlen(name))," ",str_val);

            else if( EQS(name,"center_data"     ) ) datap->ed_phase_center_log = aapl_strdup(str_val);
            else if( EQS(name,"phase_data"      ) ) parse_phase_data(aapl, datap, str_val);
            else if( EQS(name,"user_comment"    ) ) datap->ed_comment          = aapl_strdup(str_val);

            else if( EQS(name,"eye_type"        ) ) aapl_str_to_eye_type (str_val,&datap->ed_eye_type);
            else if( EQS(name,"compare_mode"    ) ) aapl_str_to_cmp_mode (str_val,&datap->ed_cmp_mode);
            else if( EQS(name,"fast_dynamic"    ) ) datap->ed_fast_dynamic     = getint(str_val);
            else if( EQS(name,"error_threshold" ) ) datap->ed_error_threshold = (uint)value;

            else if( EQS(name,"dc_balance"      ) ) sscanf(str_val, "%20f",&datap->ed_dc_balance);
            else if( EQS(name,"trans_density"   ) ) sscanf(str_val, "%20f",&datap->ed_trans_density);
            else if( EQS(name,"avdd"            ) ) sscanf(str_val, "%20f",&datap->ed_avdd);
            else if( EQS(name,"dac_scale"       ) ) sscanf(str_val, "%20lf",&datap->ed_dac_scale);
            else if( EQS(name,"min_dwell_bits"  ) ) sscanf(str_val, "%20g",&dval),datap->ed_min_dwell_bits = (bigint)dval;
            else if( EQS(name,"max_dwell_bits"  ) ) sscanf(str_val, "%20g",&dval),datap->ed_max_dwell_bits = (bigint)dval;
        }
        else
        {
            char *argv[20];
            int argc = split(line, " ,\t", argv);
            if( argv[0][0] == '#' && EQS(argv[1],"BATHTUB") )
                break;
            if( argv[0][0] == '#' && EQS(argv[1],"Horizontal") )
                break;
            if( argv[0][0] == '#' && EQS(argv[1],"Vertical") )
                break;
            if( argc >= 3 && argv[0][0] != '#' )
            {
                 int x = MIN((int)datap->ed_x_points-1,MAX(-AAPL_ARRAY_LENGTH(datap->ed_mission_errors),getint(argv[0])));
                uint y = MIN((uint)getint(argv[1]),datap->ed_y_resolution-1);
                bigint *errorsp = (bigint *)&get_errs_column(datap, x)[y];
                bigint *bitsp   = (bigint *)&get_bits_column(datap, x)[y];
                bigint errs = getbigint(argv[2]);
                bigint bits;

                if( errs < 0 )       bits = 0;
                else if( argc >= 4 ) bits = getbigint(argv[3]);
                else                 bits = datap->ed_max_dwell_bits;

                if( x >= -datap->eye_count && x < (int)datap->ed_x_points && ((x >= 0 && y < datap->ed_y_points) || y < datap->ed_y_resolution) )
                {
                    *errorsp = errs;
                    *bitsp   = bits;
                }
                else
                {
                    aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,"Warning: Data index out of range at [%d,%u]\n",x,y);
                }
            }
        }
    }
    datap->ed_y_center_point = get_dac_for_y_index(datap, (datap->ed_y_points - 1) / 2, FALSE);

    if( datap->ed_avdd      == 0.0 ) datap->ed_avdd = 1.0;
    if( datap->ed_dac_scale == 0.0 ) datap->ed_dac_scale = 1000.0 * datap->ed_avdd / datap->ed_y_resolution;
    if( avdd > 0.0 )
    {
        datap->ed_dac_scale *= avdd / datap->ed_avdd;
        datap->ed_avdd = avdd;
    }


    if( datap->ed_y_mission_points == 0 ) datap->ed_y_mission_points = datap->ed_y_points;
    if( datap->ed_y_mission_step   == 0 ) datap->ed_y_mission_step   = datap->ed_y_step;
    if( datap->ed_y_mission_points == 0 ) datap->ed_y_mission_min    = datap->ed_y_min;
    copy_mission_to_data(datap);

    if ( datap->ed_gather_mean )
        force_mean_eye_points(datap);

    serdes_eye_calc_gradient(datap);
    serdes_eye_calc_qval(aapl,datap);
    vbtc_extrapolate_mission(datap);
    hbtc_extrapolate(datap);

    fclose(file);
    if( aapl->debug >= 4 ) { uint x; for( x = 0; x < datap->ed_x_points; x++ ) { aapl_log_printf(aapl, AVAGO_DEBUG4, __func__, __LINE__, "mUI[%u] = %f\n", x, mui_from_index(datap,x)); } }
    return aapl->return_code;
}
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
    if( x_point >= -AAPL_ARRAY_LENGTH(datap->ed_mission_errors) && x_point < 0 && y_point < AAPL_ARRAY_LENGTH(datap->ed_mission_errors[0]) )
    {
        bigint errors = get_errs_column(datap, x_point)[y_point];
        bigint bits   = get_bits_column(datap, x_point)[y_point];
        double BER = avago_calc_BER(errors, bits, datap->ed_dc_balance);
        return (float)avago_qfuncinv(BER);
    }

    if( aapl && !serdes_eye_range_check(aapl,datap,x_point,y_point,"ed_qvalp") )
        return -100;
    return AVAGO_EYE_QVAL_GET(*datap, x_point, y_point);
}

/** @cond INTERNAL */

int sbm_eye_gather(
    Aapl_t *aapl,
    uint addr,
    bigint dwell,
    int eye_start,
    uint eye_points,
    uint eye_step,
    uint eye_gather,
    uint options)
{
    uint sbm_addr = avago_make_sbus_master_addr(addr);
    bigint bits[512];
    bigint errs[512];
    Eye_state_t es;
    Eye_state_t *esp = &es;
    uint i;
    int row, col;

    Avago_serdes_eye_config_t *configp = avago_serdes_eye_config_construct(aapl);
    Avago_serdes_eye_data_t   *datap   = avago_serdes_eye_data_construct(aapl);
    memset(bits,0,sizeof(bits));
    memset(errs,0,sizeof(errs));

    aapl_log_printf(aapl,AVAGO_INFO,0,0,"EYE_GATHER(SBus %s; dwell %s; %d..%u..%u; 0x%x\n", aapl_addr_to_str(addr), aapl_bigint_to_str(dwell), eye_start, eye_points, eye_step, eye_gather);

    init_eye_state(esp, aapl, addr, configp, datap);

    eye_points = MIN(eye_points,512);
    eye_set_error_timer(esp, dwell);

    if( 0 == (options & 1) )
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_ADDR       | (0x0ff & addr));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_RESOLUTION | (0x7ff & avago_serdes_get_phase_multiplier(aapl, addr)));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_START      | (0x7ff & eye_start));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_POINTS     | (0x7ff & eye_points));
    avago_spico_int_check(aapl, __func__, __LINE__, sbm_addr, SBM_INT, EYE_SET_STEP       | (0x7ff & eye_step));
    sbm_eye_set_options(esp);
    sbm_eye_gather_data(esp, eye_gather, bits, errs, 1, eye_points);

    aapl_log_printf(aapl,AVAGO_INFO,0,0,"SBM Phase center: %d\n", (short)avago_spico_int(aapl, sbm_addr, SBM_INT, EYE_READ_CENTER));
    aapl_log_printf(aapl,AVAGO_INFO,0,0,"Phase             %d\n", (short)avago_spico_int(esp->aapl, sbm_addr, SBM_INT, EYE_READ_PHASE));
    for( i = 0; i < eye_points; i++ )
    {
        if( (eye_gather&0xf000) == 0xa000 )
        {
            row = eye_gather & 0x7ff;
            col = i * eye_step + eye_start;
            if( row & 0x400 )
                row = (short)(row | 0xf800);
        }
        else if( (eye_gather&0xf000) == 0xb000 )
        {
            row = i * eye_step + eye_start;
            col = eye_gather & 0x7ff;
            if( col & 0x400 )
                col = (short)(col | 0xf800);
        }
        else
        {
            row = i;
            col = -1;
        }
        aapl_log_printf(aapl,AVAGO_INFO,0,0,"BER[%4d,%4d] = %10s / %7s\n", col, row, aapl_bigint_to_str(errs[i]), aapl_bigint_to_str(bits[i]));
    }
    return 0;
}

/** @endcond */

/** @} */

#endif
