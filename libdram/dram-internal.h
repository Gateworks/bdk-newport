#ifndef __DRAM_INTERNAL_H__
#define __DRAM_INTERNAL_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * This header defines all internal API for libdram. None
 * of these functions should be called by users of the library.
 * This is the only header that DRAM files should include
 * from the libdram directory
 */

// forward typedef some structs to get out of "header loop hell"...
struct impedence_values_s;
typedef struct impedence_values_s impedence_values_t;
struct dram_init_data_s;
typedef struct dram_init_data_s dram_init_data_t;
struct ddr_overrides_s;
typedef struct ddr_overrides_s ddr_overrides_t;
struct dram_overrides_s;
typedef struct dram_overrides_s dram_overrides_t;

#include "libdram.h"
#include "lib_octeon_shared.h"
#include "dram-print.h"
#include "dram-util.h"
#include "dram-csr.h"
#include "dram-env.h"
#include "dram-gpio.h"
#include "dram-spd.h"
#include "dram-l2c.h"

#include "dram-init-ddr3.h"

typedef enum {
    DDR3_DRAM = 3,
    DDR4_DRAM = 4,
} ddr_type_t;


#undef DRAM_CSR_WRITE_INLINE

#define ALLOW_BY_RANK_INIT 1
#define ENABLE_BY_RANK_INIT_DEFAULT 1

#define ENABLE_WRITE_DESKEW_DEFAULT 0

// define how many HW RL samples per rank to take
// multiple samples will allow looking for the best sample score
// (see dram-init-ddr3.c)
#define RLEVEL_SAMPLES_DEFAULT 3

typedef struct {
    int delay;
    int loop_total;
    int loop_count;
    int best;
    uint64_t bm;
    int bmerrs;
    int sqerrs;
    int bestsq;
} rlevel_byte_data_t;

typedef struct {
    uint64_t bm;
    uint8_t mstart;
    uint8_t width;
    int errs;
} rlevel_bitmask_t;

#define SET_DDR_DLL_CTL3(field, expr)                   \
    do {                                                \
        if (bdk_is_model(OCTEONTX_CN8XXX))              \
            ddr_dll_ctl3.cn8.field = (expr);            \
        else                                            \
            ddr_dll_ctl3.cn9.field = (expr);       \
    } while (0)

#define GET_DDR_DLL_CTL3(field)                         \
    (bdk_is_model(OCTEONTX_CN8XXX) ? ddr_dll_ctl3.cn8.field : ddr_dll_ctl3.cn9.field)

#define RLEVEL_NONSEQUENTIAL_DELAY_ERROR        50
#define RLEVEL_ADJACENT_DELAY_ERROR             30

#define TWO_LMC_MASK  0x03
#define FOUR_LMC_MASK 0x0f
#define ONE_DIMM_MASK 0x01
#define TWO_DIMM_MASK 0x03

extern int initialize_ddr_clock(bdk_node_t node,
    const ddr_configuration_t *ddr_configuration, uint32_t cpu_hertz,
    uint32_t ddr_hertz, uint32_t ddr_ref_hertz, int ddr_interface_num,
    uint32_t ddr_interface_mask);

// "mode" arg
#define DBTRAIN_TEST 0
#define DBTRAIN_DBI  1
#define DBTRAIN_LFSR 2

extern int test_dram_byte_hw_rank(bdk_node_t node, int lmc, int rank,
                                  int mode, uint64_t *xor_data);

extern int run_best_hw_patterns_rank(bdk_node_t node, int lmc, int rank,
                                     int mode, uint64_t *xor_data);

extern int get_dimm_part_number(char *buffer, bdk_node_t node,
                                const dimm_config_t *dimm_config);

extern uint32_t get_dimm_serial_number(bdk_node_t node,
                                       const dimm_config_t *dimm_config);

extern int octeon_ddr_initialize(bdk_node_t node, uint32_t cpu_hertz,
    uint32_t ddr_hertz, uint32_t ddr_ref_hertz, uint32_t ddr_interface_mask,
    const ddr_configuration_t *ddr_configuration, uint32_t *measured_ddr_hertz,
    int board_type, int board_rev_maj, int board_rev_min);

void dbi_switchover_interface(int node, int lmc,
                              dram_init_data_t *init_data,
                              dram_overrides_t *overrides);

extern uint64_t divide_nint(uint64_t dividend, uint64_t divisor);

static inline int get_ddr_type(bdk_node_t node, const dimm_config_t *dimm_config)
{
    int spd_ddr_type;

#define DEVICE_TYPE DDR4_SPD_KEY_BYTE_DEVICE_TYPE
    spd_ddr_type = read_spd(node, dimm_config, DEVICE_TYPE);

    debug_print("%s:%d spd_ddr_type=0x%02x\n", __FUNCTION__, __LINE__, spd_ddr_type);

    /* we return only DDR4 or 0 */
   return (spd_ddr_type == 0x0C) ? DDR4_DRAM : 0;
}

static inline int get_dimm_ecc(bdk_node_t node, const dimm_config_t *dimm_config)
{
#define BUS_WIDTH   DDR4_SPD_MODULE_MEMORY_BUS_WIDTH

    return !!(read_spd(node, dimm_config, BUS_WIDTH) & 8);
}

static inline int get_dimm_module_type(bdk_node_t node, const dimm_config_t *dimm_config)
{
#define MODULE_TYPE DDR4_SPD_KEY_BYTE_MODULE_TYPE

    return (read_spd(node, dimm_config, MODULE_TYPE) & 0x0F);
}

extern int common_ddr4_fixups(dram_config_t *cfg, uint32_t default_udimm_speed);

#define DEFAULT_BEST_RANK_SCORE  9999999
#define MAX_RANK_SCORE_LIMIT     99 // is this OK?

extern unsigned short load_dll_offset(bdk_node_t node, int ddr_interface_num,
			       int dll_offset_mode, int byte_offset, int byte);
extern void change_dll_offset_enable(bdk_node_t node, int ddr_interface_num, int change);

extern void Get_DLL90_Settings(bdk_node_t node, int ddr_interface_num, int* settings);

extern int perform_dll_offset_tuning(bdk_node_t node, int dll_offset_mode, int do_tune);
extern int perform_HW_dll_offset_tuning(bdk_node_t node, int dll_offset_mode, int bytelane);
extern void hw_assist_test_dll_offset(bdk_node_t node, int dll_offset_mode, int lmc, int bytelane);
extern int run_dram_tuning_threads(bdk_node_t node, int num_lmcs, uint64_t bytemask);

extern int perform_margin_write_voltage(bdk_node_t node);
extern int perform_margin_read_voltage(bdk_node_t node);

extern int use_margin_settings;

extern void ddr4_mpr_read(bdk_node_t node, int ddr_interface_num, int rank,
			  int page, int location, uint64_t *mpr_data);

// DESKEW unlock experiment; leave code disabled for now
//
// Set ALLOW to 1 compiles it in.
// Activate it by setting envvar "ddr_deskew_unlock" to:
//   0 = disabled
//   1 = unlock deskew just before software write-leveling
//   2 = unlock deskew at the end of normal eachn LMC init
//   3 = unlock deskew just after potential tuning operation
//
#define ALLOW_DESKEW_UNLOCK 0 // 0 == facility not compiled

typedef struct {
    int16_t nibrng_errs; // mask of bytelanes with nibble range errors
    int16_t saturated;   // number of bits saturated
    int16_t unlocked;    // number of bits unlocked
    int16_t limits;      // number of bytelanes with a value beyond limits
    int16_t sat_hi;      // mask of bytelanes saturated high
    int16_t sat_lo;      // mask of bytelanes saturated low
    int16_t val_hi;      // mask of bytelanes with high value
    int16_t val_lo;      // mask of bytelanes with low value
} deskew_counts_t;

typedef struct {
    int bytes[9];
} dac_data_t;

extern dac_data_t final_dac_settings[4]; // by LMC

/////

#define LMC_RESET_ASSERT    0
#define LMC_RESET_DEASSERT  1

extern void do_lmc_ddr_reset(bdk_node_t node, int ddr_interface_num, int reset);
extern void perform_lmc_reset(bdk_node_t node, int ddr_interface_num);

extern void ddr4_mrw(bdk_node_t node, int ddr_interface_num, int rank,
                     int mr_wr_addr, int mr_wr_sel, int mr_wr_bg1);

// return (x8) for CN8XXX, else return (x9)
extern int CN8_OR_CN9(int x8, int x9);

// for MODEREG_PARAMS1
extern unsigned int EXTR_WR(uint64_t u, int x);
extern void INSRT_WR(uint64_t *up, int x, int v);
extern unsigned int EXTR_NOM(uint64_t u, int x);
extern void INSRT_NOM(uint64_t *up, int x, int v);
extern unsigned int EXTR_DIC(uint64_t u, int x);
extern void INSRT_DIC(uint64_t *up, int x, int v);

// for MODEREG_PARAMS1 but these should only be used on CN8XXX
extern void INSRT_PASR(uint64_t *up, int x, int v);
extern void INSRT_ASR(uint64_t *up, int x, int v);
extern void INSRT_SRT(uint64_t *up, int x, int v);

// for MODEREG_PARAMS2
extern unsigned int EXTR_PARK(uint64_t u, int x);
extern void INSRT_PARK(uint64_t *up, int x, int v);

extern void update_wlevel_rank_struct(bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank,
                                      int byte, int delay);
extern int get_wlevel_rank_struct(bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank, int byte);
extern int get_rlevel_rank_struct(bdk_lmcx_rlevel_rankx_t *lmc_rlevel_rank, int byte);

extern void set_mpr_mode (bdk_node_t node, int lmc, int rank_mask,  int mpr);

extern void bdk_wait_usec_noyield(uint64_t usec);

extern int set_rdimm_mode(bdk_node_t node, int ddr_interface_num, int enable);
extern int set_lrdimm_mode(bdk_node_t node, int ddr_interface_num, int enable);

void Display_MPR_Page(bdk_node_t node, int rank_mask, int ddr_interface_num, int page);

/////////////////////
//
// LRDIM-related, in dram-lrdimm-init.c
//

extern int lrdimm_db_reset(bdk_node_t node, int lmc,
                           dram_init_data_t *init_data);
extern int lrdimm_db_setup(bdk_node_t node, int lmc,
                           dram_init_data_t *init_data,
                           dram_overrides_t *overrides);

extern int lrdimm_db_zqcal_long(bdk_node_t node, int lmc);

extern int lrdimm_process_spd(bdk_node_t node, int lmc,
                              const dimm_config_t *dimm_config);

extern int lrdimm_setup_modereg_params1(bdk_node_t node, int lmc,
                                        dram_init_data_t *init_data,
                                        uint64_t *params1_p);
extern int lrdimm_setup_modereg_params2(bdk_node_t node, int lmc,
                                        dram_init_data_t *init_data,
                                        uint64_t *params2_p);

extern int get_lrdimm_vref(bdk_node_t node, int lmc, int rank);

extern int lrdimm_db_pre_wl(bdk_node_t node, int lmc,
                            dram_init_data_t *init_data);

extern int lrdimm_db_mrep_dwl_train(bdk_node_t node, int lmc,
                                    dram_init_data_t *init_data, int mode);

extern int lrdimm_db_mrd_mwd_train(bdk_node_t node, int lmc,
                                   dram_init_data_t *init_data, int mode);

// Training modes
#define NORM_MODE 0
#define MREP_MODE 1
#define DWL_MODE  4
#define HWL_MODE  5
#define MRD_MODE  6
#define MWD_MODE  7
#define HIW_MODE  8

typedef struct {
    uint8_t dram_vrefdq[4];   // by rank
    uint8_t dram_range[4];    // by rank
    uint8_t db_vrefdq;
    uint8_t db_range;
    uint8_t mdq_drive[3];     // by speed bin
    uint8_t mdq_rtt[3];       // by speed bin
    uint8_t dram_drive[3];    // by speed bin
    uint8_t dram_wr[3];       // by speed bin
    uint8_t dram_nom[3];      // by speed bin
    uint8_t dram_park[3][2];  // by speed bin then by rank
    uint8_t db_dq_dfe;
    uint8_t orig_dic[4];      // by rank
} lrdimm_spd_data_t;
extern lrdimm_spd_data_t lrdimm_spd_data;

/////////////////////////

extern void Setup_ECC_Error_Reporting(bdk_node_t node, int ddr_interface_num, int enable);

// allow explicit test for LMC_INT errors
extern void check_cn8xxx_lmc(bdk_node_t, int, int);
extern void bdk_check_parity_errors_cn9xxx_lmc(bdk_node_t, int);

// generic DRAM parity support

extern void inject_parity_error(bdk_node_t, int, int);
extern void check_inject_parity_error(bdk_node_t, int);

extern void
Setup_EXT_CONFIG_for_parity_mode(bdk_node_t node, int ddr_interface_num, 
                                 dram_init_data_t *init_data,
                                 dram_overrides_t *overrides,
                                 bdk_lmcx_ext_config_t *ext_config);

extern int Set_Parity_Mode(bdk_node_t, int, dram_init_data_t *, dram_overrides_t *, int);
extern void Change_Parity_Generation(bdk_node_t node, int lmc, 
                                     dram_init_data_t *init_data,
                                     dram_overrides_t *overrides,
                                     int gen_par);

//////////////////

extern unsigned int EXTR_DQS0_ADJ(uint64_t u, int x);
extern void INSRT_DQS0_ADJ(uint64_t *up, int x, int v);
extern unsigned int EXTR_DQS1_ADJ(uint64_t u, int x);
extern void INSRT_DQS1_ADJ(uint64_t *up, int x, int v);

//FIXMELATER FIXMELATER: make sure this works when enabled...
// Force 2X refresh capability
// Setting the define symbol to 1 only enables the capability.
// Setting envvar "ddr_force_2x_refresh" to 1 activates it.
#define ALLOW_FORCE_2X_REFRESH 0

// these are used during read-leveling
// xlate PACKED index to UNPACKED index to use with rlevel_byte
#define XPU(i,e) (((i) < 4)?(i):((i)<8)?(i)+(e):4)
// xlate UNPACKED index to PACKED index to use with rlevel_bitmask
//#define XUP(i,e) (((i) < 4)?(i):((i)>4)?(i)-(e):8) // does not work right if non-ECC
#define XUP(i,e) (((i) < 4)?(i):(e)?(((i)>4)?(i)-1:8):(i))

//#define BDK_SYS_CVMCACHE_INV_L2 "#0,c11,c1,#1"          // L2 Cache Invalidate
//#define BDK_CACHE_INV_L2(address) { asm volatile ("sys " BDK_SYS_CVMCACHE_INV_L2 ", %0" : : "r" (address)); }

extern uint64_t global_scramble_cfg0[4];
extern uint64_t global_scramble_cfg1[4];
extern uint64_t global_scramble_cfg2[4];

#endif /* __DRAM_INTERNAL_H__ */
