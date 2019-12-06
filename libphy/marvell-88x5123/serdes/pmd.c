/* AAPL CORE Revision: 2.1.0 */

/* Copyright 2014 Avago Technologies. All rights reserved.                   */
/*                                                                           */
/* This file is part of the AAPL CORE library.                               */
/*                                                                           */
/* AAPL CORE is free software: you can redistribute it and/or modify it      */
/* under the terms of the GNU Lesser General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* AAPL CORE is distributed in the hope that it will be useful,              */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with AAPL CORE.  If not, see http://www.gnu.org/licenses.           */

/* Support for AAPL (ASIC and ASSP Programming Layer) generic handling of */
/* SerDes (Serializer/Deserializer) slices on ASIC SBus rings. */
#include <stdio.h>
#include <string.h>

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

/** Doxygen File Header */
/** @file */
/** @brief Functions for PMD training. */

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*============================================================================= */
/* SERDES PMD CONFIG CONSTRUCTOR */
/* */
/** @brief   Creates an Avago_serdes_pmd_config_t struct */
/** @details mallocs and initializes the memory for a Avago_serdes_pmd_config_t */
/**          and returns a pointer to that memory location. */
/** @return  The initialized structure, or 0 on allocation error. */
Avago_serdes_pmd_config_t *avago_serdes_pmd_config_construct(
    Aapl_t *aapl)   /**< [in] Pointer to Aapl_t structure. */
{
    Avago_serdes_pmd_config_t * pmd_config;
    int bytes = sizeof(Avago_serdes_pmd_config_t);

    if (! (pmd_config = (Avago_serdes_pmd_config_t *) aapl_malloc(aapl, bytes, "Avago_serdes_pmd_config_t struct"))) return(NULL);
    memset(pmd_config, 0, sizeof(*pmd_config));

    pmd_config->train_mode = AVAGO_PMD_TRAIN;
    pmd_config->clause     = AVAGO_PMD_CL72;

    return(pmd_config);
}
/*============================================================================= */
/* SERDES PMD CONFIG DESTRUCTOR */
/* */
/** @brief   Destroys the provided Avago_serdes_pmd_config_t struct. */
/** @details Frees resources associated with the pmd configuration structure. */
/** @return  void */
void avago_serdes_pmd_config_destruct(
    Aapl_t *aapl,                           /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_pmd_config_t *pmd_config)  /**< [in] Pointer to structure to free */
{
    aapl_free(aapl, pmd_config, __func__);
}
#endif /* MV_HWS_REDUCED_BUILD */

/* BC3 TBD !!!! following keys not defined in CPSS appDemo compilation - must fix */
#if !defined(ALDRIN_DEV_SUPPORT) && !defined(BOBK_DEV_SUPPORT) && !defined(BV_DEV_SUPPORT) && !defined(BC3_DEV_SUPPORT) && !defined(PIPE_DEV_SUPPORT) && !defined(ALDRIN2_DEV_SUPPORT)
static void serdes_pmd_cl91_lane_config(
    Aapl_t *aapl,
    uint sbus_addr,
    Avago_serdes_pmd_config_t *mode)
{
    uint seed = mode->prbs_seed & 0x3FF;
    uint lane = mode->lane;

    if (lane > 3) {
#ifndef MV_HWS_REDUCED_BUILD
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "PMD lane %d is beyond valid range of 0-3 for SBus %s.  Configuring as PMD lane 0.\n",lane,aapl_addr_to_str(sbus_addr));
#endif 
        lane = 0;
    }

    if (seed == 0) {
        switch(lane) {
        case 3 : {seed = 0x7b6 /*b111_1011_0110*/; break;}
        case 2 : {seed = 0x72d /*b111_0010_1101*/; break;}
        case 1 : {seed = 0x645 /*b110_0100_0101*/; break;}
        case 0 :
        default: {seed = 0x57e /*b101_0111_1110*/; break;}
        }
    }
    avago_spico_int(aapl,sbus_addr,0x3D,0x3000|lane);
    avago_spico_int(aapl,sbus_addr,0x3D,0x4000|seed);
    avago_spico_int(aapl,sbus_addr,0x3D,0x2000|0x01);
}

static void serdes_pmd_cl84_lane_config(
    Aapl_t *aapl,
    uint sbus_addr,
    Avago_serdes_pmd_config_t *mode)
{
    uint seed = mode->prbs_seed & 0x3FF;
    uint lane = mode->lane;

    if (lane > 3) {
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "PMD lane %d is beyond valid range of 0-3 for SBus %s.  Configuring as PMD lane 0.\n",lane,aapl_addr_to_str(sbus_addr));
        lane = 0;
    }

    if (seed == 0)
        seed = lane + 2;

    avago_spico_int(aapl,sbus_addr,0x3D,0x3000|0x04);
    avago_spico_int(aapl,sbus_addr,0x3D,0x4000|seed);
    avago_spico_int(aapl,sbus_addr,0x3D,0x2000|0x03);
}

static void serdes_pmd_16gfc_lane_config(
    Aapl_t *aapl,
    uint sbus_addr,
    Avago_serdes_pmd_config_t * mode)
{
    uint int_data = 0;
    if (mode->TT_FECreq) int_data |= 0x01;
    if (mode->TT_TF    ) int_data |= 0x02;
    if (mode->TT_FECcap) int_data |= 0x04;

    avago_spico_int(aapl,sbus_addr,0x3D,0x1000|int_data);
}
#endif /* !defined(ALDRIN_DEV_SUPPORT) && !defined(BOBK_DEV_SUPPORT) && !defined(BV_DEV_SUPPORT) */

/* ported from aapl 2.2.3 for PMD Training Status  */
/** @brief  Returns PMD training status.
** @return Returns 1 if training completed successfully.
** @return Returns 2 if training is in progress.
** @return Returns 0 if training ran and failed.
** @return Returns -1 if training hasn't been initiated.
**/
int avago_serdes_pmd_status(Aapl_t *aapl, uint addr)
{
#if 0 /* Ported from aapl 2.2.3 */
    int reg_serdes_status = (aapl_get_sdrev(aapl,addr) == AAPL_SDREV_P1) ? 0xef : 0x27;
#else
    int reg_serdes_status = 0x27;
#endif
    int status = avago_serdes_mem_rd(aapl, addr, AVAGO_LSB, reg_serdes_status);
    if( status & (1 << 1) ) return 2;
    if( (status & 7) == 4 ) return 1;
    if( status & (1 << 0) ) return 0;
    return -1;
}

/*============================================================================= */
/* SERDES PMD TUNE */
/*============================================================================= */
/** @brief Initialize struct with default values */
EXT void avago_serdes_pmd_init(Aapl_t *aapl, Avago_serdes_pmd_config_t *pmd_config)
{
    memset(pmd_config, 0, sizeof(Avago_serdes_pmd_config_t));

    pmd_config->train_mode = AVAGO_PMD_TRAIN;
    pmd_config->clause     = AVAGO_PMD_CL72;
}

/** @brief  Launches and halts PMD link training procedure */
/** @return void */
void avago_serdes_pmd_train(
    Aapl_t *aapl,                       /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_pmd_config_t *mode_control) /**< [in] Pointer to control structure. */
{
    uint sbus_addr = mode_control->sbus_addr;
#if !defined(ALDRIN_DEV_SUPPORT) && !defined(BOBK_DEV_SUPPORT) && !defined(BV_DEV_SUPPORT) && !defined(BC3_DEV_SUPPORT) && !defined(PIPE_DEV_SUPPORT) && !defined(ALDRIN2_DEV_SUPPORT)
    uint sbus_tx   = mode_control->sbus_addr;
#endif /* !defined(ALDRIN_DEV_SUPPORT) && !defined(BOBK_DEV_SUPPORT) && !defined(BV_DEV_SUPPORT) */
    uint int_data = 0;
#ifndef MV_HWS_REDUCED_BUILD
    if (!aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, TRUE, 1, AVAGO_SERDES)) return;
    if (!aapl_check_process(aapl, sbus_addr, __func__, __LINE__, TRUE, 2, AVAGO_PROCESS_B, AVAGO_PROCESS_F)) return;
#endif
    if (mode_control->disable_timeout)  int_data |= 0x0010;

    switch(mode_control->train_mode)
    {
    case AVAGO_PMD_BYPASS  : {int_data |= 0x01; break;}
    case AVAGO_PMD_TRAIN   : {int_data |= 0x02; break;}
    case AVAGO_PMD_RESTART : {int_data |= 0x00; break;}
    default                : {int_data |= 0x00; break;}
    }

    if (mode_control->train_mode != AVAGO_PMD_RESTART)
    {
        uint i;
        avago_spico_int_check(aapl, __func__, __LINE__, sbus_addr, 0x04, 0);

        i = 0;
        /* Assuming we check it before running Tx-Training,
           anyway still give a window time for checking that Serdes signal is active */
        while( (i < 10000) && ((avago_serdes_mem_rd(aapl, sbus_addr, AVAGO_LSB, 0x027) & 0x0010)==0) )
            i++;

        if (i >= 10000)
        {
            aapl_fail(aapl, __func__, __LINE__, "serdes_pmd_train RESTART command sent before initiating training timed out for sbus_addr %04x.  Training aborted.\n", sbus_addr);

            return;
        }

#if !defined(ALDRIN_DEV_SUPPORT) && !defined(BOBK_DEV_SUPPORT) && !defined(BV_DEV_SUPPORT) && !defined(BC3_DEV_SUPPORT) && !defined(PIPE_DEV_SUPPORT) && !defined(ALDRIN2_DEV_SUPPORT)
        if (aapl_get_lsb_rev(aapl,sbus_addr) >= 4)
        {
            if (mode_control->clause == AVAGO_PMD_CL92)
                serdes_pmd_cl91_lane_config(aapl,sbus_tx,mode_control);
            if (mode_control->clause == AVAGO_PMD_CL84)
                serdes_pmd_cl84_lane_config(aapl,sbus_tx,mode_control);
        }
        if (mode_control->clause == AVAGO_PMD_FC16G)
            serdes_pmd_16gfc_lane_config(aapl,sbus_addr,mode_control);
#endif /* !defined(ALDRIN_DEV_SUPPORT) && !defined(BOBK_DEV_SUPPORT) && !defined(BV_DEV_SUPPORT) */
    }

    avago_spico_int_check(aapl, __func__, __LINE__, sbus_addr, 0x04, int_data);
}


#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/** @brief Creates a Avago_serdes_pmd_request_t struct
 ** @param aapl aapl struct
 ** @details mallocs the memory for a Avago_serdes_pmd_request_t and returns a pointer
 ** to that memory location.  The following non-zero default values are set for
 ** the returned struct.  tune_mode=AVAGO_PMD_TRAIN,
 ** @return  The initialized structure, or 0 on allocation error.
 **/
static Avago_serdes_pmd_request_t *pmd_tap_requests_construct(
    Aapl_t *aapl)   /**< [in] Pointer to Aapl_t structure. */
{
  Avago_serdes_pmd_request_t *pmd_config;
  int bytes = sizeof(Avago_serdes_pmd_request_t);

  if (! (pmd_config = (Avago_serdes_pmd_request_t *) aapl_malloc(aapl, bytes, "Avago_serdes_pmd_request_t struct"))) return(NULL);
  memset(pmd_config, 0, sizeof(*pmd_config));

  return(pmd_config);
}

/** @brief Creates a Avago_serdes_pmd_tap_stats_t struct
 ** @param aapl aapl struct
 ** @return Avago_serdes_pmd_tap_stats_t struct
 ** @details mallocs the memory for a Avago_serdes_pmd_tap_stats_t and returns a pointer
 ** to that memory location.  The following non-zero default values are set for
 ** the returned struct.  tune_mode=AVAGO_PMD_TRAIN,
 **/
static Avago_serdes_pmd_tap_stats_t *pmd_tap_stats_construct(Aapl_t *aapl)
{
  Avago_serdes_pmd_tap_stats_t * pmd_config;
  int bytes = sizeof(Avago_serdes_pmd_tap_stats_t);
  int i;

  if (! (pmd_config = (Avago_serdes_pmd_tap_stats_t *) aapl_malloc(aapl, bytes, "Avago_serdes_pmd_tap_stats_t struct"))) return(NULL);

  memset(pmd_config, 0, sizeof(*pmd_config));
  for(i=0; i<3; i++)
    pmd_config->tap[i] = pmd_tap_requests_construct(aapl);

  return(pmd_config);
}

/** @brief   Creates a PMD debug structure.
 ** @details Allocates and initializes memory for a PMD debug structure.
 ** @return  The initialized structure, or 0 on allocation error.
 **/
Avago_serdes_pmd_debug_t *avago_serdes_pmd_debug_construct(
    Aapl_t *aapl)   /**< [in] Pointer to Aapl_t structure. */
{
  Avago_serdes_pmd_debug_t * pmd_config;
  int bytes = sizeof(Avago_serdes_pmd_debug_t);

  if (! (pmd_config = (Avago_serdes_pmd_debug_t *) aapl_malloc(aapl, bytes, "Avago_serdes_pmd_debug_t struct"))) return(NULL);
  memset(pmd_config, 0, sizeof(*pmd_config));

  pmd_config->lcl  = pmd_tap_stats_construct(aapl);
  pmd_config->remote = pmd_tap_stats_construct(aapl);

  return(pmd_config);
}

/** @brief   Destroys the provided Avago_serdes_pmd_debug_t struct.
 ** @details Frees the memory pointed to by the provided Avago_serdes_pmd_debug_t struct.
 ** @return  void
 **/
void avago_serdes_pmd_debug_destruct(
    Aapl_t *aapl,                           /**< [in] Pointer to Aapl_t structure. */
    Avago_serdes_pmd_debug_t *pmd_config)   /**< [in] Structure to free. */
{
  int i;
  for(i=0; i<3; i++) {
    aapl_free(aapl, pmd_config->lcl->tap[i],__func__);
    aapl_free(aapl, pmd_config->remote->tap[i],__func__);
  }
  aapl_free(aapl, pmd_config->lcl, __func__);
  aapl_free(aapl, pmd_config->remote,__func__);
  aapl_free(aapl, pmd_config, __func__);
}



/** @brief  Queries debug statistics from a PMD training process
 ** @details Gathers up the PMD training debug information from the provided slice.
 ** @return void
 **/
void avago_serdes_pmd_debug(
    Aapl_t *aapl,                           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,                         /**< [in] SBus address of SerDes. */
    Avago_serdes_pmd_debug_t *pmd_debug)    /**< [in] Struct to populate with debug information. */
{
    int i;
    for(i=0; i<3; i++)
    {
        pmd_debug->remote->tap[i]->inc = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x08);
        pmd_debug->remote->tap[i]->dec = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x09);
        pmd_debug->remote->tap[i]->min = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x0c);
        pmd_debug->remote->tap[i]->max = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x0d);
        pmd_debug->lcl->tap[i]->inc  = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x0a);
        pmd_debug->lcl->tap[i]->dec  = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x0b);
        pmd_debug->lcl->tap[i]->min  = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x0e);
        pmd_debug->lcl->tap[i]->max  = avago_spico_int(aapl,sbus_addr,0x3d,0xd000|(i<<8)|0x0f);
    }
    pmd_debug->remote->initialize = avago_spico_int(aapl,sbus_addr,0x3d,0xd004);
    pmd_debug->remote->preset     = avago_spico_int(aapl,sbus_addr,0x3d,0xd005);
    pmd_debug->lcl->preset     = avago_spico_int(aapl,sbus_addr,0x3d,0xd006);
    pmd_debug->rx_metric          = avago_spico_int(aapl,sbus_addr,0x3d,0xd003);
    pmd_debug->last_local_request = avago_spico_int(aapl,sbus_addr,0x3d,0xd002);
    for(i=0; i<8; i++)
        *(pmd_debug->last_remote_request+i) = avago_spico_int(aapl,sbus_addr,0x3d,0xd300|i);

    if (pmd_debug->reset)
        avago_spico_int(aapl,sbus_addr,0x3d,0xd000);
}

static void pmd_tap_req(uint request, uint tap, char *str)
{
    if (request & 0x2000)
        strcpy(str,(tap > 0) ? " " : "PRESET");
    else if (request & 0x1000)
        strcpy(str,(tap > 0) ? " " : "INITIALIZE");
    else
        switch( (request >> (tap*2)) & 0x3 )
        {
        case 0  : {strcpy(str,"HOLD"); break;}
        case 1  : {strcpy(str,"INC");  break;}
        case 2  : {strcpy(str,"DEC");  break;}
        default : {strcpy(str,"RSVD"); break;}
        }
}

/** @brief  Format and print PMD debug info
 ** @param  aapl  appl struct
 ** @param  pmd_debug Struct to print
 ** @return void
 ** @details Print debug information in useful format
 **/
void avago_serdes_pmd_debug_print(Aapl_t *aapl, Avago_serdes_pmd_debug_t * pmd_debug)
{
  int i,j;
  char rem[3][12];
  char loc[3][12];

  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"Rx Eq Metric: %d (0x%04x)\n",pmd_debug->rx_metric,pmd_debug->rx_metric);
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"+------+----------------------+----------------------+\n","");
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %20s | %20s |\n"," ","Remote Tx Requests","Local Tx Requests");
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6s %6s %6s | %6s %6s %6s |\n","REQ","PRE","CURSOR","POST","PRE","CURSOR","POST");
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"+------+----------------------+----------------------+\n","");
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6d %6s %6s | %6d %6s %6s |\n",
      "PRE",
      pmd_debug->remote->preset, " ", " ",
      pmd_debug->lcl->preset, " ", " ");
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6d %6s %6s | %6d %6s %6s |\n",
      "INIT",
      pmd_debug->remote->initialize, " ", " ",
      pmd_debug->lcl->initialize, " ", " ");
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6d %6d %6d | %6d %6d %6d |\n",
      "INC",
      pmd_debug->remote->tap[0]->inc,
      pmd_debug->remote->tap[1]->inc,
      pmd_debug->remote->tap[2]->inc,
      pmd_debug->lcl->tap[0]->inc,
      pmd_debug->lcl->tap[1]->inc,
      pmd_debug->lcl->tap[2]->inc);
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6d %6d %6d | %6d %6d %6d |\n",
      "DEC",
      pmd_debug->remote->tap[0]->dec,
      pmd_debug->remote->tap[1]->dec,
      pmd_debug->remote->tap[2]->dec,
      pmd_debug->lcl->tap[0]->dec,
      pmd_debug->lcl->tap[1]->dec,
      pmd_debug->lcl->tap[2]->dec);
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6d %6d %6d | %6d %6d %6d |\n",
      "MAX",
      pmd_debug->remote->tap[0]->max,
      pmd_debug->remote->tap[1]->max,
      pmd_debug->remote->tap[2]->max,
      pmd_debug->lcl->tap[0]->max,
      pmd_debug->lcl->tap[1]->max,
      pmd_debug->lcl->tap[2]->max);
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6d %6d %6d | %6d %6d %6d |\n",
      "MIN",
      pmd_debug->remote->tap[0]->min,
      pmd_debug->remote->tap[1]->min,
      pmd_debug->remote->tap[2]->min,
      pmd_debug->lcl->tap[0]->min,
      pmd_debug->lcl->tap[1]->min,
      pmd_debug->lcl->tap[2]->min);
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"+------+----------------------+----------------------+\n","");
  for(i=0; i<8; i++) {
    for(j=0; j<3; j++) {
      pmd_tap_req(pmd_debug->last_remote_request[i],j,rem[j]);
      if (i > 0)
        strcpy(loc[j]," ");
      else
        pmd_tap_req(pmd_debug->last_local_request,j,loc[j]);
    }
    aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"| %4s | %6s %6s %6s | %6s %6s %6s |\n",
        "CMD",
        rem[0],
        rem[1],
        rem[2],
        loc[0],
        loc[1],
        loc[2]);
  }
  aapl_log_printf(aapl,AVAGO_INFO,__func__,1,"+------+----------------------+----------------------+\n","");
}
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */

