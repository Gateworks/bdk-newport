/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"
#include "bdk-dram-init.h"

#define QR_X4_DDP 1
static int cs_mode = 0; // default to not QR_X4_DDP

static int training_mode = NORM_MODE;
static char *training_mode_strings[10] =
    { "NORM", "MREP", "???", "???", "DWL", "HWL", "MRD", "MWD", "HIW", "???" };
static char *training_mode_string = "NORM";

// this is SW-only convention
static int current_training_mode = NORM_MODE;

// default to only use bcw_write (1)
static int bcw_write_mode  = 1;

// default to necessary delay in bcw_write for correct operation (250 is not enough)
static int bcw_write_delay = 25; // in usecs; was: 300

// default to use for PBA mask byte bits
static int write_pba_mask = 0x03;  // default to 11b

// var: stop_train_early
// indicates if we should stop training if we see a good value or continue to end
// once working, this should almost always be set
static int stop_train_early = 0;

#define bmask(b) ((1 << (b)) - 1)
#define domask(b,v) ((unsigned)((v) & bmask(b)))

static unsigned munge3(int b1, int v1, int b2, int v2, int b3, int v3)
{
    unsigned new_data;
    new_data  = (domask(b1,v1) << (b2 + b3));
    new_data |= (domask(b2,v2) << (0  + b3));
    new_data |= (domask(b3,v3) << (0  +  0));
    return new_data;
}
static unsigned munge2(int b1, int v1, int b2, int v2)
{
    unsigned new_data;
    new_data  = (domask(b1,v1) << (b2));
    new_data |= (domask(b2,v2) << (0));
    return new_data;
}

void bdk_wait_usec_noyield(uint64_t usec)
{
    uint64_t done = bdk_clock_get_count(BDK_CLOCK_TIME) +
        usec * bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;
    do
    {
        //bdk_thread_yield();
    } while (bdk_clock_get_count(BDK_CLOCK_TIME) < done);
}

void do_phy_reset(bdk_node_t node, int lmc)
{
    bdk_lmcx_phy_ctl_t phy_ctl;

    phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(lmc));
    phy_ctl.s.phy_reset = 1;
    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(lmc), phy_ctl.u);
}

static void
ddr4_mrw_lrdimm(bdk_node_t node, int lmc, int rank,
                int mrreg, int data, int side,
                int pda_mask, int pba_en, int pba_space)
{
    bdk_lmcx_mr_mpr_ctl_t lmc_mr_mpr_ctl;
    int pda_enable = ((pda_mask != 0) && (pba_en == 0));

    // FIXME: check for any LMC errors so far
    if (bdk_is_model(OCTEONTX_CN8XXX))
        check_cn8xxx_lmc(node, lmc, 0);

    VB_PRT(VBL_DEV, "N%d.LMC%d: LRDIMM:  ddr4_mrw_lrdimm: rank %1d mrreg %2d data 0x%05x side %1d, pda_mask 0x%x pba_enable %d pba_space %d\n",
           node, lmc, rank, mrreg, data, side, pda_mask, pba_en, pba_space);

    // fetch CSR to preserve fields not explicitly set below
    // The CSR read preserves the following:
    //    lmc_mr_mpr_ctl.s.mpr_sample_dq_enable
    lmc_mr_mpr_ctl.u = BDK_CSR_READ(node, BDK_LMCX_MR_MPR_CTL(lmc)); // was 0

    // The following CSR fields are currently unused, so zero them out.
    lmc_mr_mpr_ctl.s.mpr_whole_byte_enable = 0;
    lmc_mr_mpr_ctl.s.mpr_byte_select = 0;
    lmc_mr_mpr_ctl.s.mpr_bit_select = 0;

    // Almost all the other CSR fields are provided by the parameter list...

    lmc_mr_mpr_ctl.s.mr_wr_pba_enable = pba_en;
    lmc_mr_mpr_ctl.s.pba_func_space   = pba_space;
    lmc_mr_mpr_ctl.s.pda_early_dqx    = (pba_en) ? 1 : 0;  // FIXME?

    // Not using MRW sequence to do PPR, so turn this off.
    lmc_mr_mpr_ctl.s.mr_wr_secure_key_ena = 0;

    // setup pda if asked
    lmc_mr_mpr_ctl.s.mr_wr_pda_enable = pda_enable;
    lmc_mr_mpr_ctl.s.mr_wr_pda_mask   = pda_mask;

    // setup the rank/register to be programmed
    lmc_mr_mpr_ctl.s.mr_wr_rank = rank;
    lmc_mr_mpr_ctl.s.mr_wr_sel  = mrreg;
    lmc_mr_mpr_ctl.s.mr_wr_addr = data;
    lmc_mr_mpr_ctl.s.mr_wr_bg1 = side;
    lmc_mr_mpr_ctl.s.mr_wr_use_default_value = 0;

    // FIXME? should these be zeroed each time?
    lmc_mr_mpr_ctl.s.mpr_wr  = 0;
    lmc_mr_mpr_ctl.s.mpr_loc = 0;

    DRAM_CSR_WRITE(node, BDK_LMCX_MR_MPR_CTL(lmc), lmc_mr_mpr_ctl.u);
    BDK_CSR_READ(node, BDK_LMCX_MR_MPR_CTL(lmc));

    VB_PRT(VBL_DEV, "N%d.LMC%d: LRDIMM:   Set MR_MPR_CTL: 0x%016lx\n",
           node, lmc, lmc_mr_mpr_ctl.u);

    // setup sequence to run and set init_start, then go
    // delay while we wait to finish
    perform_octeontx_ddr_sequence(node, (1 << rank), lmc, 0x8); /* Mode Register Write */
    bdk_wait_usec_noyield(100); // FIXME???

    // FIXME: extra delay
    bdk_wait_usec_noyield(bcw_write_delay);

    // FIXME: check for any LMC errors so far
    if (bdk_is_model(OCTEONTX_CN8XXX))
        check_cn8xxx_lmc(node, lmc, 0);
}

/////////////////////////////////////////////////
//
//  LRDIMM SPD related code and data

lrdimm_spd_data_t lrdimm_spd_data;

static short ddr4_mdq_drive_ohms[8] = { 40, 34, 48, 0, 0, 60, 0, 0 };

// decode and possibly print the LRDIMM SPD entries
int
lrdimm_process_spd(bdk_node_t node, int lmc, const dimm_config_t *dimm_config)
{
    int rank, speed;
    int temp;
    int spd_mfgr_id = read_spd(node, dimm_config, DDR4_SPD_REGISTER_MANUFACTURER_ID_LSB) |
        (read_spd(node, dimm_config, DDR4_SPD_REGISTER_MANUFACTURER_ID_MSB) << 8);
    int spd_buffer_rev = read_spd(node, dimm_config, DDR4_SPD_BUFFER_REVISION_NUMBER);
    lrdimm_spd_data_t *data = &lrdimm_spd_data;
    const char *speed_string[3] = { "LOW", "MED", "HIGH" };
    const char *s;

    ddr_print("DDR4: LRDIMM Buffer Manufacturer ID 0x%x Revision 0x%x\n",
              spd_mfgr_id, spd_buffer_rev);

    for (rank = 0; rank < 4; rank++) {
        data->dram_vrefdq[rank] =
            read_spd(node, dimm_config, DDR4_SPD_DRAM_VREFDQ_PKG_RANK_0 + rank) & 0x3F;
    }
    ddr_print("DDR4: LRDIMM DRAM_VREFDQ_PKG_RANK[0:3]: 0x%02x 0x%02x 0x%02x 0x%02x\n",
              data->dram_vrefdq[0], data->dram_vrefdq[1],
              data->dram_vrefdq[2], data->dram_vrefdq[3]);

    data->db_vrefdq = read_spd(node, dimm_config, DDR4_SPD_DB_VREFDQ_FOR_DRAM_INTERFACE) & 0x3F;
    ddr_print("DDR4: LRDIMM DB_VREFDQ_FOR_DRAM_INTERFACE: 0x%02x\n",
              data->db_vrefdq);

    for (speed = 0; speed < 3; speed++) {
        temp = read_spd(node, dimm_config, DDR4_SPD_DB_MDQ_DRIVE_AND_RTT_LOW_SPEED + speed);
        data->mdq_drive[speed] = (temp >> 4) & 7;
        data->mdq_rtt[speed]   = (temp >> 0) & 7;
        ddr_print("DDR4: LRDIMM DB_MDQ_DRIVE_AND_RTT_%s_SPEED:  DRIVE %2d, RTT %3d\n",
                  speed_string[speed], ddr4_mdq_drive_ohms[data->mdq_drive[speed]],
                  ddr4_impedence_values.rtt_nom_ohms[data->mdq_rtt[speed]]);
    }

    temp = read_spd(node, dimm_config, DDR4_SPD_DRAM_DRIVE_STRENGTHS);
    data->dram_drive[0] = (temp >> 0) & 3;
    data->dram_drive[1] = (temp >> 2) & 3;
    data->dram_drive[2] = (temp >> 4) & 3;
    ddr_print("DDR4: LRDIMM DRAM_DRIVE_STRENGTHS: LOW %2d, MED %2d, HIGH %2d\n",
              ddr4_impedence_values.dic_ohms[data->dram_drive[0]],
              ddr4_impedence_values.dic_ohms[data->dram_drive[1]],
              ddr4_impedence_values.dic_ohms[data->dram_drive[2]]);

    for (speed = 0; speed < 3; speed++) {
        temp = read_spd(node, dimm_config, DDR4_SPD_DRAM_WR_NOM_LOW_SPEED + speed);
        data->dram_nom[speed] = (temp >> 0) & 7;
        data->dram_wr[speed]  = (temp >> 3) & 7;
        ddr_print("DDR4: LRDIMM DRAM_WR_NOM_%s_SPEED:  RTT_WR %3d, RTT_NOM %3d\n",
                  speed_string[speed],
                  ddr4_impedence_values.rtt_wr_ohms[data->dram_wr[speed]],
                  ddr4_impedence_values.rtt_nom_ohms[data->dram_nom[speed]]);
    }

    for (speed = 0; speed < 3; speed++) {
        temp = read_spd(node, dimm_config, DDR4_SPD_DRAM_PARK_LOW_SPEED + speed);
        data->dram_park[speed][0] = (temp >> 0) & 7; // ranks 0,1
        data->dram_park[speed][1] = (temp >> 3) & 7; // ranks 2,3
        ddr_print("DDR4: LRDIMM DRAM_PARK_%s_SPEED:  PARK_1x %3d, PARK_0x %3d\n",
                  speed_string[speed],
                  ddr4_impedence_values.rtt_nom_ohms[data->dram_park[speed][1]],
                  ddr4_impedence_values.rtt_nom_ohms[data->dram_park[speed][0]]);
    }

    temp = read_spd(node, dimm_config, DDR4_SPD_DRAM_VREFDQ_RANGES);
    for (rank = 0; rank < 4; rank++)
        data->dram_range[rank] = (temp >> rank) & 1;
    data->db_range = (temp >> 4) & 1;
    ddr_print("DDR4: LRDIMM DRAM_VREFDQ_RANGES [0:3]: %d %d %d %d, DB %d\n",
              data->dram_range[0], data->dram_range[1],
              data->dram_range[2], data->dram_range[3],
              data->db_range);

    temp = read_spd(node, dimm_config, DDR4_SPD_DB_DQ_DFE);
    data->db_dq_dfe = (temp >> 0) & 3;
    ddr_print("DDR4: LRDIMM DB_DQ_DFE: %3d\n", data->db_dq_dfe);

    // process any overrides...
    if ((s = lookup_env_parameter_ull("ddr_db_vrefdq")) != NULL) {
        int value = strtoull(s, NULL, 0);
        data->db_vrefdq = value & 0x3F;
        data->db_range = !!(value & 0x40);
        ddr_print("DDR4: LRDIMM: override DB_VREFDQ to 0x%x/%d\n",
                  data->db_vrefdq, data->db_range + 1);
    }

    return 0;
}

int
get_lrdimm_vref(bdk_node_t node, int lmc, int rank)
{
    return lrdimm_spd_data.dram_vrefdq[rank] | (lrdimm_spd_data.dram_range[rank] << 6);
}

int
lrdimm_setup_modereg_params1(bdk_node_t node, int lmc,
                             dram_init_data_t *init_data,
                             uint64_t *params1_p)
{
    uint64_t modereg_params1 = *params1_p;
    lrdimm_spd_data_t *spp = &lrdimm_spd_data;
    int rank_mask = init_data->refs.rank_mask;
    int rank, speed_bin;
    uint64_t nom, wr, dic;
    BDK_CSR_INIT(modereg_params0, node, BDK_LMCX_MODEREG_PARAMS0(lmc));

    speed_bin = modereg_params0.s.cwl >> 1; // <=1866->0, <=2400->1, <=3200->2

    for (rank = 0; rank < 4; rank++) {
        if (! (rank_mask & (1 << rank)))
            continue;

        // do NOM
        nom = spp->dram_nom[speed_bin];
        INSRT_NOM(&modereg_params1, rank, nom);

        // do WR
        wr = spp->dram_wr[speed_bin];
        INSRT_WR(&modereg_params1, rank, wr);

        // do DIC, but save original first...
        spp->orig_dic[rank] = EXTR_DIC(modereg_params1, rank);

        dic = spp->dram_drive[speed_bin];
        INSRT_DIC(&modereg_params1, rank, dic);

        ddr_print("N%d.LMC%d: LRDIMM override MODEREG_PARAMS1: rank %1d: nom %ld, wr %ld, dic %ld\n",
                  node, lmc, rank, nom, wr, dic);
    }

    *params1_p = modereg_params1;

    return 0;
}

int
lrdimm_setup_modereg_params2(bdk_node_t node, int lmc,
                             dram_init_data_t *init_data,
                             uint64_t *params2_p)
{
    uint64_t modereg_params2 = *params2_p;
    lrdimm_spd_data_t *spp = &lrdimm_spd_data;
    int rank_mask = init_data->refs.rank_mask;
    int rank, speed_bin;
    uint64_t park;
    BDK_CSR_INIT(modereg_params0, node, BDK_LMCX_MODEREG_PARAMS0(lmc));

    speed_bin = modereg_params0.s.cwl >> 1; // <=1866->0, <=2400->1, <=3200->2

    for (rank = 0; rank < 4; rank++) {
        if (! (rank_mask & (1 << rank)))
            continue;

        // do PARK
        park = spp->dram_park[speed_bin][(rank >> 1) & 1];
        INSRT_PARK(&modereg_params2, rank, park);

        ddr_print("N%d.LMC%d: LRDIMM override MODEREG_PARAMS2: rank %1d: park %ld\n",
                  node, lmc, rank, park);
    }

    *params2_p = modereg_params2;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// PORTED FUNCTIONS AND ROUTINES

// func: rank2dimm
//  convert from a rank 0..3 to a dimm 0 or possibly 1
static int rank2dimm(int rank)
// function bit [1:0] rank2dimm(bit [1:0] _rank);
{
    //if(p_sequencer.cfg.cs_mode == QR_X4_DDP)
    //  rank2dimm = 0;  // only one dimm in Quad-Rank
    //else
    //  rank2dimm = (_rank>=2) ? 2 : 0; //for dual-rank, rank2=dimm1

    if (cs_mode == QR_X4_DDP)
        return 0; // only one dimm in Quad-Rank
    else
        return (rank >= 2) ? 2 : 0; // for dual-rank, rank2=dimm1
}

// func: rankondimm
//   given a monolithic rank (0-3) figure out what rank this is on the particular dimm
static int rankondimm(int rank)
// function bit[1:0] rankondimm(bit [1:0] _rank);
{
    //if(p_sequencer.cfg.cs_mode == QR_X4_DDP)
    //  rankondimm = _rank; // quad-rank, pass through directly
    //else
    //  //dual-rank, ranks 2-3 correspond with rank0-1 on dimm1
    //  if(_rank >= 2) rankondimm = _rank - 2;
    //  else           rankondimm = _rank;

    if (cs_mode == QR_X4_DDP)
        // quad-rank, pass through directly
        return rank;
    else
        // dual-rank, ranks 2-3 correspond with rank0-1 on dimm1
        return (rank >= 2) ? rank - 2 : rank;
}

// func: rcw_cmd_write
// write to the RCD command register (RC06), to start a bcw_read/write
static int
rcw_cmd_write(bdk_node_t node, int lmc, int rank, int write)
// virtual task rcw_cmd_write(bit[1:0] _rank, bit _write)
{
    //bit [1:0] dimm = rank2dimm(_rank);
    int dimm = rank2dimm(rank);
    // data == (init_data + 18'h64 + _write);
    unsigned new_data = (/*init_data*/0x00000 + 0x00064 + write);

    VB_PRT(VBL_DEV, "N%d.LMC%d: LRDIMM rcw_cmd_write: rank %d, write %d\n",
           node, lmc, rank, write);

    // with {rank == dimm; mrreg == 3'h7; data == (init_data + 18'h64 + _write);
    //       pda_mask == 18'h0; pba_en == 1'b0; }

    ddr4_mrw_lrdimm(node, lmc, /*rank*/dimm, /*mrreg*/7, /*data*/new_data,
                    /*side*/0, /*pda_mask*/0, /*pba_en*/0, /*pba_space*/0);

    return 0;
}

// func: ext_rcw_write
// invokes the MRW sequence to the RCD and extended register with the given data
static int
ext_rcw_write(bdk_node_t node, int lmc, int rank, int reg, int data)
// virtual task ext_rcw_write(bit[1:0] _rank, bit[3:0] _reg, [7:0] _data);
{
    //bit [1:0] dimm = rank2dimm(_rank);
    int dimm = rank2dimm(rank);
    // data == {6'h0, _reg, _data};
    unsigned new_data = munge3( 6,0x00, 4,reg, 8,data);

    VB_PRT(VBL_DEV, "N%d.LMC%d: LRDIMM ext_rcw_write: rank %d, reg %d, data 0x%x\n",
           node, lmc, rank, reg, data);

    // with {rank == dimm; mrreg == 3'h7; data == {6'h0, _reg, _data};
    //       pda_mask == 18'h0; pba_en == 1'b0; }

    ddr4_mrw_lrdimm(node, lmc, /*rank*/dimm, /*mrreg*/7, /*data*/new_data,
                    /*side*/0, /*pda_mask*/0, /*pba_en*/0, /*pba_space*/0);

    return 0;
}

// func: bcw_write
// does a bcw write to the given dimm, function space and register with specified data
static int
bcw_write(bdk_node_t node, int lmc, int rank, int space, int reg, int data, int ext)
// virtual task bcw_write(bit[1:0] _rank, bit[2:0] _space, bit[3:0] _reg, bit[7:0] _data, bit _ext_reg=1);
{
    //bit[1:0] dimm = rank2dimm(_rank);
    int dimm = rank2dimm(rank);

    VB_PRT(VBL_TME, "N%d.LMC%d: LRDIMM: bcw_write: rank %1d, space %1d, reg %2d, data 0x%02x, ext %1d\n",
           node, lmc, rank, space, reg, data, ext);

    //if(_ext_reg == 0 && _space != 0)
    //    `cn_err(("DBTRAIN: Attempt to write a 4-bit register (address 0x%x) in function space %1d,"
    //             " 4-bit regs only present in space 0", _reg, _space))
    if ((ext == 0) && (space != 0)) {
        error_print("N%d.LMC%d: LRDIMM: Attempt to write a 4-bit register (address 0x%x) in function space %d,"
                    " 4-bit regs are only present in space 0\n", node, lmc, reg, space);
        return -1;
    }

    if (space == 0) {
        unsigned new_data;

        // if we are going to function space 0, we can directly write by setting A12
        // with { rank == dimm; mrreg == 3'h7;
        //        if(_ext_reg) data == {6'h1, _reg, _data}; else data == {10'h10, _reg, _data[3:0]};
        //        pda_mask == 18'h0; pba_en == 1'b0; }

        new_data = (ext) ? munge3( 6,0x01, 4,reg, 8,data) : munge3(10,0x10, 4,reg, 4,data);
        ddr4_mrw_lrdimm(node, lmc, /*rank*/dimm, /*mrreg*/7, /*data*/new_data,
                        /*side*/0, /*pda_mask*/0, /*pba_en*/0, /*pba_space*/0);

    } else {

        // going to function space 1-7, two methods
        // 1) set function space in DB (via F0BC7x) and send in RCW with A12=1
        // 2) set function space and data in RCD, then write RC06 to generate BCW
        if (bcw_write_mode) {
            // recursive, but this will hit in the above if and will terminate
            // bcw_write(_rank, 0, 7, _space);
            bcw_write(node, lmc, rank, /*space*/0, /*mrreg*/7, space, /*ext*/1);
            // space is 0 here, even though we are going elsewhere, previous command directs
            // bcw_write(_rank, 0, _reg, _data);
            bcw_write(node, lmc, rank, /*space*/0, /*mrreg*/reg, data, /*ext*/1);
        } else {
            // if we are going to function space 1-7,
            //  we need to set data and address in RCS then execute command
            // ext_rcw_write(_rank, 4, {_space, 1'b1, _reg});
            // ext_rcw_write(_rank, 6, _data);
            // rcw_cmd_write(_rank, 1);
            ext_rcw_write(node, lmc, rank, 4, /*{_space, 1'b1, _reg}*/munge3(3,space, 1,1, 4,reg));
            ext_rcw_write(node, lmc, rank, 6, data);
            rcw_cmd_write(node, lmc, rank, 1);
        }
    }

    return 0;
}

// func: bcw_write_small
// write the 4-bit BCW registers
// always writes to space #0
static int
bcw_write_small(bdk_node_t node, int lmc, int rank, int reg, int data)
// virtual task bcw_write_small(bit[1:0] _rank, bit[3:0] _reg, [3:0] _data);
{
    VB_PRT(VBL_TME, "N%d.LMC%d: LRDIMM: bcw_write_small: rank %d, reg %d, data 0x%x\n",
           node, lmc, rank, reg, data);

    // bcw_write(_rank, 0, _reg, {4'b0, _data}, 0);
    bcw_write(node, lmc, rank, /*space*/0, /*reg*/7, 0, /*ext*/1); // set space==0
    return bcw_write(node, lmc, rank, /*space*/0, reg, data & 0x0F, /*ext*/0);
}

// func: set_func_space
// sets the function space on the data buffer
static int
set_function_space(bdk_node_t node, int lmc, int rank, int space)
//virtual task set_func_space(bit[1:0] _rank, bit[2:0] _space);
{
    VB_PRT(VBL_TME, "N%d.LMC%d: LRDIMM: set_function_space: rank %d, space %d\n",
           node, lmc, rank, space);

#if 0
    // this writes to current space, but F[0:7]BC7x is accessible across all spaces
    bcw_write(node, lmc, rank, /*space*/0, /*reg*/7, space, /*ext*/1);
#else
    int dimm = rank2dimm(rank);
    int new_data = munge3( 6,0x01, 4,7, 8,space);
    ddr4_mrw_lrdimm(node, lmc, /*rank*/dimm, /*mrreg*/7, /*data*/new_data,
                        /*side*/0, /*pda_mask*/0, /*pba_en*/0, /*pba_space*/0);
#endif
    return 0;
}

// func: bcw_write_pba
// does a bcw write to the given dimm, function space and register with specified data
static int
bcw_write_pba(bdk_node_t node, int lmc, int rank, int space, int reg, int data, int mask, int ext)
// virtual task bcw_write_pba(bit[1:0] _rank, bit[2:0] _space, bit[3:0] _reg, bit[7:0] _data,
//     bit[17:0] _mask, bit _ext_reg=1);
{
    //bit[1:0] dimm = rank2dimm(_rank);
    int dimm = rank2dimm(rank);
    unsigned new_data;

    VB_PRT(VBL_TME, "N%d.LMC%d: LRDIMM: bcw_write_pba: rank %d, space %2d, reg %2d, data 0x%02x, mask 0x%05x, ext %d\n",
           node, lmc, rank, space, reg, data, mask, ext);

    // if(_ext_reg == 0 && _space != 0)
    //    `cn_err(("DBTRAIN: Attempt to write a 4-bit register (address 0x%x) in function space %1d,"
    //             "4-bit regs only present in space 0", _reg, _space))
    if ((ext == 0) && (space != 0)) {
        error_print("N%d.LMC%d: LRDIMM: Attempt to write a 4-bit register (address 0x%x) in function space %d,"
                    " 4-bit regs are only present in space 0\n", node, lmc, reg, space);
        return -1;
    }

    // with { rank == dimm; mrreg == 3'h7;
    //        if(_ext_reg) data == {6'h1, _reg, _data}; else data == {10'h10, _reg, _data[3:0]};
    //        pda_mask == _mask; pba_en == 1'b1; pba_space == _space; side == 0; }

    new_data = (ext) ? munge3(6,0x01, 4,reg, 8,data) : munge3(10,0x10, 4,reg, 4,data);
    ddr4_mrw_lrdimm(node, lmc, /*rank*/dimm, /*mrreg*/7, /*data*/new_data,
                    /*side*/0, /*pda_mask*/mask, /*pba_en*/1, /*pba_space*/space);
    return 0;
}

// func: db_set_training_mode
// sets the training mode passed in by writing BC0C
static int
db_set_training_mode(bdk_node_t node, int lmc, int rank, int mode)
// virtual task db_set_training_mode(bit[1:0] _rank, bit[3:0] _mode);
{
    VB_PRT(VBL_FAE, "N%d.LMC%d: LRDIMM: set_training_mode: rank %d, mode %d\n",
           node, lmc, rank, mode);

    // check for invalid
    //if(_mode == 2 || _mode == 3 || _mode[3] == 1)
    //    `cn_err(("DBTRAIN: Reserved training mode selected %h for Data Buffer", _mode))
    if ((mode == 2) || (mode == 3) || (mode >= 8)) {
        error_print("DBTRAIN: Reserved training mode (%d) selected for Data Buffer\n", mode);
        return -1;
    }

    training_mode = mode; // set global
    if (mode != NORM_MODE)
        training_mode_string = training_mode_strings[training_mode];

    // then write DB
    // bcw_write_small(_rank, 12, _mode);
    bcw_write_small(node, lmc, rank, 12, mode);

    return 0;
}


// func: dram_mpr_mode
// write to the DRAM to put us in MPR mode
static int
dram_mpr_mode(bdk_node_t node, int lmc, int rank, int on)
// virtual task dram_mpr_mode(bit[1:0] _rank, int _on);
{
    static int cur_ref_interval = 0; // FIXME? init to OFF?

    VB_PRT(VBL_FAE, "N%d.LMC%d: LRDIMM: dram_mpr_mode: rank %d, on %d\n",
           node, lmc, rank, on);

    // zqcal is not allowed in MPR Mode, so turn off refresh
    if (on)
        cur_ref_interval = set_zqcs_interval(node, lmc, 0);

#if 0
    unsigned data_to_write;
    BDK_CSR_INIT(params3, node, BDK_LMCX_MODEREG_PARAMS3(lmc));
    data_to_write  = 0;
    data_to_write |= ((params3.s.mpr_fmt    & 3) << 11);
    data_to_write |= ((params3.s.wr_cmd_lat & 3) <<  9);
    data_to_write |= ((params3.s.fgrm       & 7) <<  6);
    data_to_write |= ((params3.s.temp_sense & 1) <<  5);
    data_to_write |= ((params3.s.pda        & 1) <<  4);
    data_to_write |= ((params3.s.gd         & 1) <<  3);
    data_to_write |= ((on                   & 1) <<  2);

    // with { rank == _rank; mrreg == 3'h3; data == data_to_write; pda_mask == 18'h0; pba_en == 1'b0; }
    ddr4_mrw_lrdimm(node, lmc, /*rank*/rank, /*mrreg*/3, /*data*/data_to_write,
                    /*side*/0, /*pda_mask*/0, /*pba_en*/0, /*pba_space*/0);
#else
    set_mpr_mode(node, lmc, (1 << rank), on);
#endif

    // turn refresh/zqcal back on after we are out of MPR Mode
    if (! on) {
        (void) set_zqcs_interval(node, lmc, 2);
        bdk_wait_usec(600); // FIXME?
        (void) set_zqcs_interval(node, lmc, cur_ref_interval);
    }

    return 0;
}

// func: dram_wl_mode
// write to the DRAM to put us in write-leveling mode
static int
dram_wl_mode(bdk_node_t node, int lmc, int rank, int on)
// virtual task dram_wl_mode(bit[1:0] _rank, int _on);
{
    static int cur_ref_interval = 0; // FIXME? init to OFF?
    unsigned data_to_write;
    BDK_CSR_INIT(params0, node, BDK_LMCX_MODEREG_PARAMS0(lmc));

    VB_PRT(VBL_FAE, "N%d.LMC%d: LRDIMM: dram_wl_mode: rank %d, on %d\n",
           node, lmc, rank, on);

    // refresh is not allowed in WL Mode, so turn off
    if (on)
        cur_ref_interval = set_zqcs_interval(node, lmc, 0);

    //data_to_write = (_on & 1'b1) << 7 |
    //2'b00 /* RFU */ << 5 |
    //p_sequencer.cfg.csr_model.MODEREG_PARAMS0.AL.value[1:0] << 3 |
    //2'b00 << 1 /* DIC - just ignore*/ |
    //p_sequencer.cfg.csr_model.MODEREG_PARAMS0.DLL.value[0];

    // FIXME - really should set values for DIC and RTT_NOM
    int al = (bdk_is_model(OCTEONTX_CN8XXX)) ? params0.cn8.al : params0.cn9.al;
    data_to_write  = 0;
    data_to_write |= ((on                   & 1) <<  7);
    data_to_write |= ((0                    & 3) <<  5); // RFU
    data_to_write |= ((al                   & 3) <<  3);
    data_to_write |= ((0                    & 3) <<  1); // DIC - just ignore
    data_to_write |= ((params0.s.dll        & 1) <<  0);

    // with { rank == _rank; mrreg == 3'h1; data == data_to_write; pda_mask == 18'h0; pba_en == 1'b0; }
    ddr4_mrw_lrdimm(node, lmc, /*rank*/rank, /*mrreg*/1, /*data*/data_to_write,
                    /*side*/0, /*pda_mask*/0, /*pba_en*/0, /*pba_space*/0);

    // turn refresh back on after we are out of WL Mode
    if (! on) {
        (void) set_zqcs_interval(node, lmc, 2);
        bdk_wait_usec(600); // FIXME?
        (void) set_zqcs_interval(node, lmc, cur_ref_interval);
    }

    return 0;
}

// func: db_ranks_present
// sets the device rank presence control word BC07
static int
db_ranks_present(bdk_node_t node, int lmc, int rank_mask, int dimm_count)
{
    /***
      bit [7:0] data;
      bit       dimm;

      for (int rank=0; rank<4; rank+=2) begin
         if(rankmask[rank] == 0) continue;

         // dimm_params arrays are indexed 0 and 1 so convert rank number to dimm
         dimm = (rank2dimm(rank) == 2) ? 1 : 0;

         // bc07 - Package rank 0-3 disable
         data = 1;  // rank 0 always present
         if(p_sequencer.cfg.csr_model.CONFIG.RANK_ENA.get()) begin
            data |= 4'b10;
            if(p_sequencer.cfg.two_dimm_en && p_sequencer.cfg.cs_mode == QR_X4_DDP)
              data |= 4'b1100;
         end else begin
            if(p_sequencer.cfg.two_dimm_en && p_sequencer.cfg.cs_mode == QR_X4_DDP)
              data |= 4'b100;
         end
         data = ~data;  // we are writing a disable mask here
         bcw_write_small(rank, 7, data);
      end
   endtask
    ***/

    int dimm, rank, data;

    VB_PRT(VBL_FAE, "N%d.LMC%d: LRDIMM: ranks_set: rank_mask 0x%02x, dimm_count %d\n",
           node, lmc, rank_mask, dimm_count);

#if 1
    for (dimm = 0; dimm < dimm_count; dimm++) {
        rank = dimm << 1; // 0 or 2
        rank_mask >>= rank; // possible 4-bits for single DIMM
        if (cs_mode == QR_X4_DDP)
            data = rank_mask & 0x0F;
        else
            data = rank_mask & 0x03;

        // write to BC07
        data = ~data & 0x0F ;  // we are writing a 4-bit disable mask here
        bcw_write_small(node, lmc, rank, 7, data);
    }
#else
    // just write the ~mask to BC07
    data = ~rank_mask & 0x0F ;  // we are writing a 4-bit disable mask here
    bcw_write_small(node, lmc, rank, 7, data);

#endif
    return 0;
}

/////////////////////////////
/****** ENTRY POINTS *******/

// DB Reset: does NOT match VERIF code
int
lrdimm_db_reset(bdk_node_t node, int lmc, 
                dram_init_data_t *init_data)
{
    int dimm;
    bdk_lmcx_dimmx_params_t lmc_dimmx_params;
    bdk_lmcx_dimm_ctl_t lmc_dimm_ctl;
    int rank_mask =             init_data->refs.rank_mask;
    int dimm_count =            init_data->refs.dimm_count;

    ddr_print("N%d.LMC%d: LRDIMM: db_reset: rank_mask 0x%x\n",
              node, lmc, rank_mask);

    /***
        Configuration Step #6
        Issue DB Reset to the databuffers

        Write RC06 = 0x1
        The act of writing the RC06 in the DDR4 register will issue a reset
        to the databuffer through the BCOM side band bus.

        RC06 should not be re-written to 0x0 to clear the control word,
        as this control word is a “one-shot” type register that will issue
        the user’s selected command only once based on the contents of the
        RC06 changing. In fact, RC06=0x0 will issue a soft reset to the DDR4
        register.
     ***/

    for (dimm = 0; dimm < dimm_count; dimm++) {
        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm));
        lmc_dimmx_params.s.rc6 = 0x01; // DB reset
        ddr_print("N%d.LMC%d: LRDIMM: DIMM%d Register Control Word RC06: %x\n",
                  node, lmc, dimm, lmc_dimmx_params.s.rc6);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm), lmc_dimmx_params.u);
    }

    // set mask for write only to RC06
    lmc_dimm_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));
    lmc_dimm_ctl.s.dimm0_wmask = (1 << 6);
    lmc_dimm_ctl.s.dimm1_wmask = (dimm_count > 1) ? (1 << 6) : 0;
    ddr_print("N%d.LMC%d: LRDIMM: DIMM_CTL: 0x%016lx\n",
              node, lmc, lmc_dimm_ctl.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(lmc), lmc_dimm_ctl.u);

    /* Don't write any extended registers */
    DRAM_CSR_WRITE(node, BDK_LMCX_DDR4_DIMM_CTL(lmc), 0);

    BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));

    perform_octeontx_ddr_sequence(node, rank_mask, lmc, 0x7); /* Init RCW */

    for (dimm = 0; dimm < dimm_count; dimm++) {
        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm));
        lmc_dimmx_params.s.rc6 = 0x02; // DRAM reset
        ddr_print("N%d.LMC%d: LRDIMM: DIMM%d Register Control Word RC06: %x\n",
                  node, lmc, dimm, lmc_dimmx_params.s.rc6);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm), lmc_dimmx_params.u);
    }
    BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));

    perform_octeontx_ddr_sequence(node, rank_mask, lmc, 0x7); /* Init RCW */

    for (dimm = 0; dimm < dimm_count; dimm++) {
        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm));
        lmc_dimmx_params.s.rc6 = 0x03; // Clear DRAM reset
        ddr_print("N%d.LMC%d: LRDIMM: DIMM%d Register Control Word RC06: %x\n",
                  node, lmc, dimm, lmc_dimmx_params.s.rc6);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm), lmc_dimmx_params.u);
    }
    BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));

    perform_octeontx_ddr_sequence(node, rank_mask, lmc, 0x7); /* Init RCW */

    ddr_print("N%d.LMC%d: LRDIMM: db_reset: Finished!\n", node, lmc);

    return 0;
}

// DB Setup: somewhat matches VERIF code
int
lrdimm_db_setup(bdk_node_t node, int lmc,
                dram_init_data_t *init_data,
                dram_overrides_t *overrides)
{
    int rank, dimm, data, speed_bin;
    bdk_lmcx_dimmx_params_t lmc_dimmx_params;
    bdk_lmcx_dimmx_ddr4_params0_t lmc_dimmx_ddr4_params0;
    lrdimm_spd_data_t *spp = &lrdimm_spd_data;
    int num_ranks =             init_data->refs.num_ranks;
    int rank_mask =             init_data->refs.rank_mask;
    int dimm_count =            init_data->refs.dimm_count;

    const char *s;
    BDK_CSR_INIT(modereg_params1, node, BDK_LMCX_MODEREG_PARAMS1(lmc));
    BDK_CSR_INIT(modereg_params2, node, BDK_LMCX_MODEREG_PARAMS2(lmc));

    ddr_print("N%d.LMC%d: LRDIMM: db_setup: rank_mask 0x%02x, num_ranks %d\n",
              node, lmc, rank_mask, num_ranks);

    if ((s = lookup_env_parameter_ull("bcw_write_mode")) != NULL) {
        bcw_write_mode = !!strtoull(s, NULL, 0);
    }
    if ((s = lookup_env_parameter_ull("bcw_write_delay")) != NULL) {
        bcw_write_delay = strtoull(s, NULL, 0);
    }
    if ((s = lookup_env_parameter_ull("write_pba_mask")) != NULL) {
        write_pba_mask = strtoull(s, NULL, 0) & 0x03;
    }

    // set the global for easy access...
    cs_mode = ((num_ranks == 4) && (dimm_count == 1)) ? QR_X4_DDP : 0;

    set_function_space(node, lmc, 0, /*space*/0);

    db_ranks_present(node, lmc, rank_mask, dimm_count);

    /***
        Configuration Step #9
        Send All BCW JEDEC register commands to program the databuffers
        properly using broadcast mode.

        Func Space 0
        F0BC00:0x01
        F0BC01:0x00
        F0BC02:0x04
        F0BC03:0x01
        F0BC04:0x05
        F0BC05:0x01
        F0BC07:0x00
        F0BC08:0x00
        F0BC09:0x00
        F0BC0A:0x00
        F0BC0B:0x00
        F0BC0C:0x00
        F0BC0D:0x00
        F0BC0E:0x00
        F0BC0F:0x00

        Func Space 6
        F6BC4x:0x00
        Func Space 5
        F5BC6x:0x19
        Func Space 0
        Func Space 6
        F6BC4x:0x00
        Func Space 5
        F5BC5x:0x14
        Func Space 0

     ***/

    for (rank = 0; rank < 4; rank += 2) {

        // rank does not exist
        if ((rank_mask & (1 << rank)) == 0)
            continue;

        // no second dimm to init in Quad-Rank mode
        // if(rank>2 && p_sequencer.cfg.cs_mode == QR_X4_DDP) continue;
        if ((rank >= 2) && (cs_mode == QR_X4_DDP))
            continue;

        set_function_space(node, lmc, rank, 0); // set space 0

        // dimm_params arrays are indexed 0 and 1 so convert rank number to dimm
        dimm = (rank2dimm(rank) == 2) ? 1 : 0;
        ddr_print("N%d.LMC%d: LRDIMM: db_setup: DIMM %d\n", node, lmc, dimm);

        // fetch the current DIMMX_PARAMS CSR
        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm));

        // bc0a - operating speed - mirrors RCD
        // data = p_sequencer.cfg.csr_model.DIMM_PARAMS[dimm].RC10.get();
        data = lmc_dimmx_params.s.rc10;
        bcw_write_small(node, lmc, rank, /*reg*/10, data);

        // bc0e - parity - mirrors RCD
        // data = p_sequencer.cfg.csr_model.DIMM_PARAMS[dimm].RC14.get();
#if 0
        data = lmc_dimmx_params.s.rc14 & 1; // FIXME: parity could come from RC14
#else
        data = 0; // FIXME: should have an independent "source" for this, *NOT* the RCD!!!
#endif
        bcw_write_small(node, lmc, rank, /*reg*/14, data);

        // fetch the current DIMMX_DDR4_PARAMS0 CSR
        lmc_dimmx_ddr4_params0.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_DDR4_PARAMS0(lmc, dimm));

        // f0bc6x - fine grain speed - mirrors RCS
        // data = p_sequencer.cfg.csr_model.DIMM_DDR4_PARAMS0[dimm].RC3X.get();
        // bcw_write(rank, 0, 6, data);
        data = lmc_dimmx_ddr4_params0.s.rc3x;
        bcw_write(node, lmc, rank, /*space*/0, /*reg*/6, data, /*ext*/1);

        // these are the remaining registers in Config Step #9
        /***
          From Andrew:

          BC04: DRAM Interface MDQ RTT Control Word
          BC05: DRAM Interface MDQ Driver Control Word
          F5BC5x: Host Interface Vref Control Word (Range 1 or 2 is programmed in F6BC4x bit 1).
          F5BC6x: DRAM Interface Vref Control Word (Range 1 or 2 is programmed in F6BC4x bit 2).
        *****/
        speed_bin = /*speed bin*/lmc_dimmx_params.s.rc10 >> 1; // <=1866->0, <=2400->1, <=3200->2

        data = EXTR_NOM(modereg_params1.u, rank); // was FIXME: NOM == 0 for 1R-1S DIMM
        ddr_print("N%d.LMC%d: LRDIMM set BC00: rank %1d: NOM %d\n",
                  node, lmc, rank, data);
        bcw_write_small(node, lmc, rank, /*reg*/0, data); // BC00: Host Interface DQ RTT_NOM Control

        // map SPD to BCW:    0,1,2,3,4,5,6,7
        uint8_t map_wr[8] = { 0,2,4,7,6,0,0,0 };
        data = EXTR_WR(modereg_params1.u, rank);
        data = map_wr[data]; // FIXME: was 4; WR == 80 for 1R-1S DIMM
        ddr_print("N%d.LMC%d: LRDIMM set BC01: rank %1d: WR %d\n",
                  node, lmc, rank, data);
        bcw_write_small(node, lmc, rank, /*reg*/1, data); // BC01: Host Interface DQ RTT_WR Control

        data = EXTR_PARK(modereg_params2.u, rank); // FIXME: was 1; PARK == 60 for 1R-1S DIMM
        ddr_print("N%d.LMC%d: LRDIMM set BC02: rank %1d: PARK %d\n",
                  node, lmc, rank, data);
        bcw_write_small(node, lmc, rank, /*reg*/2, data); // BC02: Host Interface DQ RTT_PARK Control

        data = spp->orig_dic[rank] + 1; // FIXME??? map from SPD [01] to BCW [12]
        ddr_print("N%d.LMC%d: LRDIMM set BC03: rank %1d: DIC %d\n",
                  node, lmc, rank, data);
        bcw_write_small(node, lmc, rank, /*reg*/3, data); // BC03: Host Interface DQ Driver Control Word

        data = spp->mdq_rtt[speed_bin];
        ddr_print("N%d.LMC%d: LRDIMM set BC04: rank %1d: RTT %d\n",
                  node, lmc, rank, data);
        bcw_write_small(node, lmc, rank, /*reg*/4, data); // BC04: DRAM Interface MDQ RTT Control Word

        data = spp->mdq_drive[speed_bin];
        ddr_print("N%d.LMC%d: LRDIMM set BC05: rank %1d: DRV %d\n",
                  node, lmc, rank, data);
        bcw_write_small(node, lmc, rank, /*reg*/5, data); // BC05: DRAM Interface MDQ Driver Control Word

        //bcw_write_small(node, lmc, rank, /*reg*/6, data); // BC06: Command Space Control Word
        //bcw_write_small(node, lmc, rank, /*reg*/7, data); // BC07: Rank Presence Control Word

        data = 0;
        bcw_write_small(node, lmc, rank, /*reg*/8, data); // BC08: Rank Selection Control Word
        bcw_write_small(node, lmc, rank, /*reg*/9, data); // BC09: Power Saving Settings Control Word

        bcw_write_small(node, lmc, rank, /*reg*/11, data); // BC0B: Op. Voltage and Host Side Output Slew Rate Control Word
        bcw_write_small(node, lmc, rank, /*reg*/12, data); // BC0C: Buffer Training Mode Control Word
        bcw_write_small(node, lmc, rank, /*reg*/13, data); // BC0D: LDQ Operation Control Word

        //bcw_write_small(node, lmc, rank, /*reg*/15, data); // BC0F: Error Status Word /RO

        if (dimm_count == 1) {
            // compute VREF as if single 1-rank DIMM
            data = __compute_vref_value(node, lmc, rank, /*dimm_count*/1, /*rank_count*/1,
                                        &ddr4_impedence_values, /*is_stacked_die*/0,
                                        /*dram__connection*/0);
        } else {
            // compute VREF as if two 1-rank DIMMs
            data = __compute_vref_value(node, lmc, rank, /*dimm_count*/2, /*rank_count*/1,
                                        &ddr4_impedence_values, /*is_stacked_die*/0,
                                        /*dram__connection*/0);
        }
        ddr_print("N%d.LMC%d: LRDIMM set Host VREF: rank %1d: range %d vref 0x%x\n",
                  node, lmc, rank, ((data >> 6) & 1) + 1, data & 0x3F);
        // F5BC5x: Host Interface Vref Control Word
        bcw_write(node, lmc, rank, /*space*/5, /*reg*/5, data & 0x3F, /*ext*/1);

        // set ranges for VREFDQ entries
        data = (data >> 5) & 2; // leave HOST range in bit 1
        data |= (spp->db_range << 2); // OR in DB side range to bit 2
        // F6BC4x: Buffer Training Configuration Control Word (VREF ranges)
        bcw_write(node, lmc, rank, /*space*/6, /*reg*/4, data, /*ext*/1);

        data = spp->db_vrefdq;
        ddr_print("N%d.LMC%d: LRDIMM set DRAM VREF: rank %1d: vref 0x%x\n",
                  node, lmc, rank, data & 0x3F);
        // F5BC6x: DRAM Interface Vref Control Word
        bcw_write(node, lmc, rank, /*space*/5, /*reg*/6, data, /*ext*/1);

    } /* for (rank = 0; rank < 4; rank += 2) */

    for (rank = 0; rank < 4; rank += 1) {
        // rank does not exist
        if ((rank_mask & (1 << rank)) == 0)
            continue;
        // set VREF directly from LRDIMM SPD entries
        ddr_print("N%d.LMC%d: LRDIMM set MR6 VREF: rank %1d: vref 0x%x, range %d\n",
                  node, lmc, rank, spp->dram_vrefdq[rank], spp->dram_range[rank] + 1);
        set_vref(node, lmc, rank, spp->dram_range[rank], spp->dram_vrefdq[rank]);
    } /* for (rank = 0; rank < 4; rank += 1) */

    for (rank = 0; rank < 4; rank += 2) {

        // rank does not exist
        if ((rank_mask & (1 << rank)) == 0)
            continue;

        set_function_space(node, lmc, rank, 0); // set space 0
    }

    /***

        NOTE: this is done in the DRAM-init mainline by "Init RCW"

        Configuration Step #10
        Send MRS command to DRAMs on all ranks for example:

        Writing MRS Values For Rank0
        MRS CSn(0xe),Reg(0x3),Dat(0x0)
        MRS CSn(0xe),Reg(0x5),Dat(0x40)
        MRS CSn(0xe),Reg(0x4),Dat(0x0)
        MRS CSn(0xe),Reg(0x2),Dat(0x410)
        MRS CSn(0xe),Reg(0x1),Dat(0x401)
        MRS CSn(0xe),Reg(0x0),Dat(0x73c)

        Writing MRS Values For Rank1
        MRS CSn(0xd),Reg(0x3),Dat(0x0)
        MRS CSn(0xd),Reg(0x5),Dat(0x40)
        MRS CSn(0xd),Reg(0x4),Dat(0x0)
        MRS CSn(0xd),Reg(0x2),Dat(0x410)
        MRS CSn(0xd),Reg(0x1),Dat(0x401)
        MRS CSn(0xd),Reg(0x0),Dat(0x73c

        Configuration Step #11
        Send ZQCal command to all ranks of the DRAMs and the Databuffer

        Send ZQCal Long to Rank0 DRAMs
        Send ZQCal long to Rank1 DRAMs
    ***/

    /***
        NOTE: this will be done in the DRAM-LRDIMM code by "db_zqcal_long"

        Configuration Step #12
        Program BCW to send ZQCal Long command to all databuffers in broadcast mode.

        BCW Func Space 0
        BCW F0BC06:0x1

        The act of writing the Databuffer F0BC06=0x1 will instruct the databuffers to perform
        a ZQCal long command. This BC06 control word is a one-hot state machine type register,
        in that it does not need to be cleared or written to any other value. In fact, if the
        user were to write this register to 0x0, everything will be reset inside the device,
        so this is not desired

     ***/

    /***
        NOTE: this will be done in the DRAM-init mainline by "change_rdimm_mpr_pattern"

        Configuration Step #13
        Program DRAM MPR with specific data pattern that matches the LRDIMM DRAM to DB DQ bit swizzle
        Do this MPR programming for each rank of DRAMs. For example:

        Load DRAM MPR Load of 0x55 on rank 0
        MRS CSn(0xe),Reg(0x3),Dat(0x4)
        MRS CSn(0xe),Reg(0x3),Dat(0x0)
        MRS CSn(0xe),Reg(0x3),Dat(0x4)
        MRS CSn(0xe),Reg(0x3),Dat(0x0)

        Load DRAM MPR Load of 0x55 on rank 1
        MRS CSn(0xd),Reg(0x3),Dat(0x4)
        MRS CSn(0xd),Reg(0x3),Dat(0x0)
        MRS CSn(0xd),Reg(0x3),Dat(0x4)
        MRS CSn(0xd),Reg(0x3),Dat(0x0)
    ***/

    ddr_print("N%d.LMC%d: LRDIMM: db_setup: Finished!\n", node, lmc);

    return 0;
}

int
lrdimm_db_zqcal_long(bdk_node_t node, int lmc)
{
    // broadcast ZQCal Long to the DBs
    set_function_space(node, lmc, 0, 0); // set space 0
    bcw_write_small(node, lmc, 0, /*reg*/6, 1); // set BC06 = 1
    return 0;
}

int
lrdimm_db_pre_wl(bdk_node_t node, int lmc, dram_init_data_t *init_data)
{
    bdk_lmcx_wlevel_ctl_t   wlevel_ctl;
    bdk_lmcx_wlevel_rankx_t wlevel_rank;
    int rank_mask = init_data->refs.rank_mask;
    int rank;

    ddr_print("N%d.LMC%d: LRDIMM: db_pre_wl: rank_mask 0x%x\n", node, lmc, rank_mask);

    wlevel_ctl.u = 0/*BDK_CSR_READ(node, BDK_LMCX_WLEVEL_CTL(lmc))*/;
    wlevel_ctl.s.or_dis  = 1;
    wlevel_ctl.s.bitmask = 0x0F;
    wlevel_ctl.s.rtt_nom = ddr4_rttnom_40ohm - 1; // FIXME? use default for DDR4

    for (rank = 0; rank < 4; rank++) {

        if (! (rank_mask & (1 << rank)))
            continue;

#if 0
        // FIXME: read/print the current contents BEFORE we do the sequence...
        wlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(lmc, rank));
        display_WL(node, lmc, wlevel_rank, rank);
#endif

        DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(lmc, rank), 0); /* Clear write-level delays */

        // do all the byte-lanes at the same time
        wlevel_ctl.s.lanemask = 0x1ff/*ddr_interface_bytemask*/; // FIXME?

        DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_CTL(lmc), wlevel_ctl.u);
        BDK_CSR_READ(node, BDK_LMCX_WLEVEL_CTL(lmc));

        /* Read and write values back in order to update the
           status field. This insures that we read the updated
           values after write-leveling has completed. */
        DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(lmc, rank),
                       BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(lmc, rank)));

        perform_octeontx_ddr_sequence(node, (1 << rank), lmc, 6); /* write-leveling */

        if (!bdk_is_platform(BDK_PLATFORM_ASIM) &&
            BDK_CSR_WAIT_FOR_FIELD(node, BDK_LMCX_WLEVEL_RANKX(lmc, rank),
                                   status, ==, 3, 1000000))
        {
            error_print("ERROR: Timeout waiting for WLEVEL\n");
        }

        wlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(lmc, rank));

        display_WL(node, lmc, wlevel_rank, rank);

    } /* for (rank = 0; rank < 4; rank++) */

    return 0;
}

// FIXME??? must dimension as largest usage!!!
static int final_setting[/*parts*/18];
static uint8_t db_results[/*parts*/18][/*settings*/64*5]; // FIXME: max this to be able to handle MRD

// func: init_db_results
// create and initialize results arrays
static int
init_db_results(int parts, int settings)
// virtual function void init_db_results(int parts, int settings);
{
    int i, j;

    /***
      if(db_results.size() > 0) db_results.delete();
      db_results = new[parts];
      foreach(db_results[parts]) db_results[parts] = new[settings];
      if(final_setting.size() > 0) final_setting.delete();
      final_setting = new[parts];
      foreach(db_results[i,j]) db_results[i][j] = 2'b10;
      foreach(final_setting[i]) final_setting[i] = '1;
    ***/
    for (i = 0; i < parts; i++) {
        final_setting[i] = -1;
        for (j = 0; j < settings; j++) {
            db_results[i][j] = 2;
        }
    }
    return 0;
}

// func: process_results
// read MPR_DATA registers and put data into results array
//  works in two modes, byte or bit, in byte mode we check all bits for 1,
//    in bit mode, we directly put data into array - FIXME - is this needed anymore??
static int
process_results(bdk_node_t node, int lmc, int rank, int idx, int byte_mode, int ignore_falling)
// virtual task process_results(bit[1:0] rank, int idx, bit byte_mode, bit ignore_falling=0);
{
    //bit [191:0] reg_data;
    uint64_t reg_data[3];
    unsigned tmp_data;
    int part;

    // these vary depending on how bits and part size
    int width = /*p_sequencer.cfg.chip_width*/4; // FIXME: get this elsewhere?
    unsigned part_mask = (1 << width) - 1;

    if (! byte_mode) {
        error_print("N%d.LMC%d: LRDIMM: process_results: BIT_MODE unsupported\n", node, lmc);
        return -1;
    }

    //p_sequencer.cfg.csr_model.MPR_DATA0.read(status, reg_data[63:0]);
    //p_sequencer.cfg.csr_model.MPR_DATA1.read(status, reg_data[127:64]);
    //p_sequencer.cfg.csr_model.MPR_DATA2.read(status, reg_data[143:128]);
    reg_data[0] = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA0(lmc));
    reg_data[1] = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA1(lmc));
    reg_data[2] = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA2(lmc));

    VB_PRT(VBL_FAE, "N%d.LMC%d.R%d: LRDIMM: MPR_DATA for setting %2d: [143:0] 0x%04lx.%016lx.%016lx\n",
           node, lmc, rank, idx, reg_data[2], reg_data[1], reg_data[0]);

#define SHIFT_REG_DATA(s) (reg_data[(s)/64] >> ((s) % 64))

    // iterate over parts and collect data
    for (part = 0; part < /*p_sequencer.cfg.get_num_parts()*/18; part++) {
        int offset = part * width;

        if (ignore_falling) {
            // results are 64b in low, 8 bits in mid for ecc
            tmp_data = SHIFT_REG_DATA(offset) & part_mask;
            VB_PRT(VBL_DEV2, "DBTRAIN: lower: 0x%02lx, tmp: 0x%02x\n",
                   (SHIFT_REG_DATA(offset) & part_mask), tmp_data);

        } else {
            // data comes as 2 72b bursts, 4 bits for each part + 8 ECC in upper reg
            unsigned lower = (SHIFT_REG_DATA(offset) & part_mask);
            unsigned upper = (SHIFT_REG_DATA(72+offset) & part_mask);
            tmp_data = lower & upper;
            VB_PRT(VBL_DEV2, "DBTRAIN: lower: 0x%02x, upper 0x%02x, tmp: 0x%02x\n",
                   lower, upper, tmp_data);
        }

        if (byte_mode) {

            // now check that all 4 bits are 1's for a pass
            db_results[part][idx] = !!(tmp_data == part_mask);

            VB_PRT(VBL_DEV2, "DBTRAIN: byte data for rank %1d, part %2d, idx %2d, 0x%02x/0x%02x (db %1d)\n",
                      rank, part, idx, tmp_data, part_mask, db_results[part][idx]);

        } else { /* if (byte_mode) */
#if 0
            // FIXME: this is bogus, needs fixing if ever to work.
            // in bit mode, simply push data right into array
            for (int i = 0; i < width; i++)
                db_results[(part*width)+i][idx] = tmp_data;

            VB_PRT(VBL_NORM, "DBTRAIN: bit data for rank %1d, part %2d, idx %2d, 0x%02x\n",
                   rank, part, idx, tmp_data);
#endif
        }

      } /* for (part = 0; part < /p_sequencer.cfg.get_num_parts()/18; part++) */

    // for byte mode, iterate over parts and print only 1 line per index
    if (byte_mode) {
        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: LRDIMM: byte data for idx %3d [8:0]: ",
               node, lmc, rank, idx);
        for (part = 17; part >= 0; part-=2) { // reverse order
            VB_PRT(VBL_DEV, "%1d%1d ", db_results[part][idx], db_results[part-1][idx]);
        }
        VB_PRT(VBL_DEV, "\n");
    }

    return 0;
}

// func: print_results
// print out the results table
static int
print_results(bdk_node_t node, int lmc, int rank, int stop_idx, char *label)
// virtual function void print_results(int _stop_idx=-1, string label);
{

    int length = (stop_idx == -1) ? /*db_results[0].size()*/63 : stop_idx;
    int part, setting;

    ddr_print("\n               %s Results \n", label);

    // FIXME: copied from process_results() to give a summary here...
    // for byte mode, iterate over parts and print only 1 line per index
    for (setting = 0; setting <= length; setting++) {
        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s data for idx %3d [17:0]: ",
                  node, lmc, rank, label, setting);
        for (part = 17; part >= 0; part--) { // reverse order
            ddr_print("%c", (db_results[part][setting])?'1':'.');
        }
        ddr_print("\n");
    }
    ddr_print("\n");

    return 0;
}

// func: check_results
// looks at the db_results array, consolidates feedback into the results array,
// then checks to see if the results for all bits/bytes are set and returns 1 if so
// rank: which rank we are checking
// valid_idx: search the array up to this setting
// result_type (default 0): 0 = middle of string of 1's, 1= 0->1 transition, 2 = 1->0 transition
// silent (default 0): if set, do not error if search returns 0 (so can be called in middle of training)
static int
check_results(bdk_node_t node, int lmc, int rank, int valid_idx, int result_type, int silent)
// virtual function bit check_results(int rank, int _valid_idx, int _result_type=0, bit _silent=0);
{
    int part, setting, i;
    int ret = 1; // default to good

    // iterate over parts (first idx)
    for (part = 0; part < /*db_results.size()*/18; part++) {

        int rise_best = -1, fall_best = -1, best_run_length = -1;
        int currently_high = 0;
        int rising_edges[64], falling_edges[64]; // by setting
        int rising_count = 0, falling_count = 0;
        int falling_popped;
        int rising_first, rising_last;

        //memset(rising_edges,  0, sizeof(rising_edges));
        //memset(falling_edges, 0, sizeof(falling_edges));

        // if we have already found a good setting, skip
        if (final_setting[part] != -1)
            continue;

        VB_PRT(VBL_DEV2, "DBTRAIN: check_results: part %2d\n", part);

        // iterate over settings
        for (setting = 0; setting <= valid_idx; setting++) {

            // search for good pattern based on _result_type
            VB_PRT(VBL_DEV2, "DBTRAIN: check_results: part %2d, setting %2d, result %1x\n",
                      part, setting, db_results[part][setting]);

            // look at all of the settings for rising and falling edges
            // no edges on 0, need to look at last one for that
            if (setting > 0) {
                // check for difference between last one and this one
                if (currently_high == 1 && db_results[part][setting] == 0) {
                    VB_PRT(VBL_DEV2, "Found a falling edge at setting  %2d\n", setting);
                    //falling_edges.push_back(setting);
                    falling_edges[falling_count] = setting;
                    falling_count++;
                }
                if (currently_high == 0 && db_results[part][setting] == 1) {
                    VB_PRT(VBL_DEV2, "Found a rising edge at setting   %2d\n", setting);
                    //rising_edges.push_back(setting);
                    rising_edges[rising_count] = setting;
                    rising_count++;
                }
                // check for a wrapped edge where last != 0
                if (setting == valid_idx) {
                    if (db_results[part][setting] == 1 && db_results[part][0] == 0) {
                        VB_PRT(VBL_DEV2, "Found a falling edge at setting  0 (wrap)\n");
                        //falling_edges.push_front(0);
                        for (i = falling_count; i > 0; i--) falling_edges[i] = falling_edges[i-1];
                        falling_edges[0] = 0;
                        falling_count++;
                    }
                    if (db_results[part][setting] == 0 && db_results[part][0] == 1) {
                        VB_PRT(VBL_DEV2, "Found a rising edge at setting   0 (wrap)\n");
                        //rising_edges.push_front(0);
                        for (i = rising_count; i > 0; i--) rising_edges[i] = rising_edges[i-1];
                        rising_edges[0] = 0;
                        rising_count++;
                    }
                }
            }

            // update state of this setting so we can check against next
            currently_high = db_results[part][setting];

        } /* for (setting = 0; setting <= valid_idx; setting++) */


        // little sanity check here
        if (falling_count != rising_count) {
            ddr_print("N%d.LMC%d.R%d: LRDIMM: %s: CHECK: Unequal number of rising %d and falling %d edges for part %d\n",
                      node, lmc, rank, training_mode_string, rising_count, falling_count, part);
            ret = 0;
            continue;
        }
        if (falling_count == 0) {
            ddr_print("N%d.LMC%d.R%d: LRDIMM: %s: CHECK: NO edges for part %d\n",
                      node, lmc, rank, training_mode_string, part);
            ret = 0;
            continue;
        }

        // now pull edges out and look for the longest pulse of ones
        //  (as there is sometimes noise for 1-2 settings)
        //while (falling_edges.size() > 0)
        falling_popped = 0;
        rising_first = 0;
        rising_last = rising_count - 1;
        while (falling_popped < falling_count)
        {
            int rise, fall;
            //fall = falling_edges.pop_front();
            fall = falling_edges[falling_popped];
            falling_popped++;

            if (rising_edges[rising_first] > fall) {
                // we have a set of ones that wraps around, falling edge is valid,
                //  but rising is at end of rising queue
                //rise = rising_edges.pop_back();
                rise = rising_edges[rising_last];
                rising_last--;

                VB_PRT(VBL_DEV2, "Found new run, rise %2d, fall %2d run %2d\n",
                          rise, fall, (valid_idx-rise)+fall);
                if (((valid_idx - rise) + fall) > best_run_length) {
                    // record new best
                    best_run_length = (valid_idx - rise) + fall;
                    rise_best = rise;
                    fall_best = fall;
                    VB_PRT(VBL_DEV2, "Found new best run, rise %2d, fall %2d run %2d\n",
                              rise, fall, best_run_length);
                }
            } else {
                //rise = rising_edges.pop_front();
                rise = rising_edges[rising_first];
                rising_first++;

                VB_PRT(VBL_DEV2, "Found new run, rise %2d, fall %2d run %2d\n",
                          rise, fall, (fall-rise));
                if ((fall - rise) > best_run_length) {
                    // record new best
                    best_run_length = fall - rise;
                    rise_best = rise;
                    fall_best = fall;
                    VB_PRT(VBL_DEV2, "Found new best run, rise %2d, fall %2d\n", rise, fall);
                }
            }
        }

        // finally record best based on what we are looking for
        if (rise_best == -1) {
            // ignore parts 16 & 17 when ECC is off
            if (!silent && (part < /*p_sequencer.cfg.get_num_parts()*/18)) // FIXME: parts
                error_print("N%d.LMC%d.R%d: LRDIMM: %s: CHECK: never found a good setting for part %2d\n",
                            node, lmc, rank, training_mode_string, part);
            final_setting[part] = -1;
        } else if (result_type == 0) {

            // calculate mid-point of 1's
            // see if we have a wrapped set of 1's
            if (fall_best < rise_best)
                final_setting[part] = ((rise_best + (valid_idx + fall_best)) / 2) % valid_idx;
            else
                final_setting[part] = (fall_best + rise_best) / 2;

            // check for case where we have a single valid setting at valid_idx,
            //  above formula will come up with 0, and we want _valid_idx
            if ((rise_best == valid_idx) && fall_best == 0)
                final_setting[part] = rise_best;
            VB_PRT(VBL_TME, "N%d.LMC%d.R%d: LRDIMM: %s: RT0: found a good setting for part %2d: 0x%02x\n",
                   node, lmc, rank, training_mode_string, part, final_setting[part]);

        } else if (result_type == 1) {
            final_setting[part] = rise_best;
            VB_PRT(VBL_TME, "N%d.LMC%d.R%d: LRDIMM: %s: RT1: found a good setting for part %2d: 0x%02x\n",
                   node, lmc, rank, training_mode_string, part, final_setting[part]);

        } else if (result_type == 2) {
            final_setting[part] = fall_best;
            VB_PRT(VBL_TME, "N%d.LMC%d.R%d: LRDIMM: %s: RT2: found a good setting for part %2d: 0x%02x\n",
                   node, lmc, rank, training_mode_string, part, final_setting[part]);
        }
    } /* for (part = 0; part < //db_results.size()//18; part++) */

    for (part = 0; part < /*db_results.size()*/18; part++) {
        if (final_setting[part] == -1) {
            VB_PRT(VBL_TME, "N%d.LMC%d.R%d: LRDIMM: check_results, part %2d still has not found good setting\n",
                   node, lmc, rank, part);
            ret = 0;
        }
    }

    VB_PRT(VBL_TME, "N%d.LMC%d.R%d: LRDIMM: check_results, %s parts have good setting, ending training\n",
           node, lmc, rank, ret ? "ALL" : "NOT all");

    return ret;
}

typedef struct {
    int value;
    int count;
    unsigned mask;
} hash_elem_t;

#define MAX_HASH_ENTRIES 9
hash_elem_t hash[MAX_HASH_ENTRIES]; // need max elems to match diff incoming values
int hashes_count; // should be empty at first

static int
get_hash_count(int part, int value)
{
    int entry;

    if (hashes_count > 0) { // there are some already
        for (entry = 0; entry < hashes_count; entry++)
            if (hash[entry].value == value) // found it
                goto update_entry;
    }
    // empty or no match, make a new one
    entry = hashes_count;
    hashes_count++;
    hash[entry].value = value;

    // update the entry fields
 update_entry:
    hash[entry].count++;
    hash[entry].mask |= (write_pba_mask << (part * 2)); // scale part to make a PBA mask

    return hash[entry].count; // return how many now
}

// func: program_db_train_setting
// given a particular DB register, programs the DBs based on an array of values
// will program the most frequent value via broadcast write and the others via
// PBA.

static int
program_db_train_setting(bdk_node_t node, int lmc, int rank,
                         int space, int reg, int *data)
//task program_db_train_setting(bit[1:0] _rank, bit[2:0] _space, bit[3:0] _reg, bit[7:0] _data[9]);
{
    //int count_hash [int][$];
    //int max_count;
    //bit [7:0] common_value;
    int part, part_count;
    int common_value = -1;
    int max_count = 0;
    int h, v;
    int pba_writes = 0;

    memset(hash, 0, sizeof(hash));
    hashes_count = 0;

    // arrange hash so we have a list of parts with each value to program
    for (part = 0; part < 9; part++) {
        // push part number to the back of the queue for this value
        //count_hash[_data[i]].push_back(i);

        part_count = get_hash_count(part, data[part]);
        VB_PRT(VBL_DEV2, "adding part %d to hash value %d\n", part, data[part]);

        // if we have a new max, save it
        if (part_count > max_count) {
            max_count = part_count;
            common_value = data[part];
            VB_PRT(VBL_DEV2, "updating max_count to %d of value %d\n",
                      max_count, common_value);
        }
    }

    // write the most common value as a broadcast write to all DBs
    //  as this is much faster than PBA
    //bcw_write(_rank, _space, _reg, common_value);
    set_function_space(node, lmc, rank, space);
    bcw_write(node, lmc, rank, 0, reg, common_value, 1);

    VB_PRT(VBL_DEV2, "common value %d, size is %d\n",
              common_value, max_count);

    // MANDATORY: set to function space 0 before PBA writes
    set_function_space(node, lmc, rank, 0);

    // iterate over the hash of values to program other parts
    //  that do not have the common value
    for (h = 0; h < hashes_count; h++) {
        v = hash[h].value;
        if (v != common_value) {
            VB_PRT(VBL_DEV2, "value %d mask is 0x%x, size is %d\n",
                   v, hash[h].mask, hash[h].count);
            bcw_write_pba(node, lmc, rank, space, reg, v, hash[h].mask, 1);
            pba_writes += 1;
        }
    }

    // PBA write should set function space 0 AND take us out of PBA mode,
    // but we do this anyway: set to function space 0 after PBA writes
    set_function_space(node, lmc, rank, 0);

    return 0;
}

// func: db_mrep_train and db_dwl_train
// runs the MREP or DWL training sequence for this
//  somewhat matches VERIF code
int
lrdimm_db_mrep_dwl_train(bdk_node_t node, int lmc,
                         dram_init_data_t *init_data, int mode)
{
    int rank_mask =             init_data->refs.rank_mask;
    int dimm_count =            init_data->refs.dimm_count;

    int rank, set, part, i, results, override;
    int final_data_high[18/2], final_data_low[18/2];
    bdk_lmcx_dbtrain_ctl_t dbtrain_ctl;
    int read_dq_count = 0x20; // FIXME? default to 32
    const char *s;
    char *mode_str = (mode == MREP_MODE) ? "MREP":"DWL";
    char *mode_str_l = (mode == MREP_MODE) ? "mrep":"dwl";
    int base = (mode == MREP_MODE) ? 2: 10; // base BC reg
    int trans = (mode == MREP_MODE) ? 2: 1; // transition type
    int mrep_hoffset = 0;
    int mrep_loffset = 0;

    current_training_mode = mode; // now set

    if (mode == MREP_MODE) {
        if ((s = lookup_env_parameter_ull("mrep_read_dq_count")) != NULL) {
            read_dq_count = strtoull(s, NULL, 0);
        }
    } else {
        if ((s = lookup_env_parameter_ull("dwl_read_dq_count")) != NULL) {
            read_dq_count = strtoull(s, NULL, 0);
        }
    }

    ddr_print("N%d.LMC%d: LRDIMM: db_%s_train: rank_mask 0x%02x, read_dq_count %d\n",
              node, lmc, mode_str, rank_mask, read_dq_count);

    // allow MPR to capture anything in MPR register
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_MR_MPR_CTL(lmc),
                    c.s.mpr_sample_dq_enable = 1);

    for (rank = 0; rank < 4; rank++) {

        if (! (rank_mask & (1 << rank)))
            continue;

        mrep_loffset = 0;
        mrep_hoffset = 0;
        if (mode == MREP_MODE) {
            if ((s = lookup_env_parameter("mrep%d_loffset", rank)) != NULL) {
                mrep_loffset = strtoul(s, NULL, 0);
            }
            if ((s = lookup_env_parameter("mrep%d_hoffset", rank)) != NULL) {
                mrep_hoffset = strtoul(s, NULL, 0);
            }
        }

        set_function_space(node, lmc, rank, /*space*/0);

        // NOTE: the order of these steps comes from the IDT Training Sample doc
        if (mode == MREP_MODE) {
            dram_mpr_mode(node, lmc, rank, /*ON*/1); // put DRAM in MPR mode
            set_function_space(node, lmc, rank, /*space*/0);
            db_ranks_present(node, lmc, (1 << rank), dimm_count); // only current rank is "present"?
        } else {
            dram_wl_mode(node, lmc, rank, /*ON*/1); // put DRAM in WL mode
        }

        set_function_space(node, lmc, rank, /*space*/0);
        db_set_training_mode(node, lmc, rank, mode);  // put DB in approp mode

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s training started...\n",
                  node, lmc, rank, mode_str);

        // MREP/DWL is done based on dqs in 1/64th of a clock
        init_db_results(18, 64);

        set_function_space(node, lmc, rank, /*space*/0);

        // DWL mode: tell DB which rank to level
        if (mode == DWL_MODE)
            bcw_write_small(node, lmc, rank, 8, rankondimm(rank));

        // now setup dbtrain register
        dbtrain_ctl.u = 0;

        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            dbtrain_ctl.cn83xx.prank          = rank;
            dbtrain_ctl.cn83xx.cmd_count_ext  = (mode == MREP_MODE) ? 3 : 0;
            dbtrain_ctl.cn83xx.read_cmd_count = (mode == MREP_MODE) ? 0x1E : 0;
            dbtrain_ctl.cn83xx.read_dq_count  = read_dq_count; // FIXME? max it out?
        }
        else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
            dbtrain_ctl.cn9.prank1         = rank;
            dbtrain_ctl.cn9.prank2         = rank;
            dbtrain_ctl.cn9.read_cmd_count = (mode == MREP_MODE) ? 0x7E : 0;
            dbtrain_ctl.cn9.read_dq_count  = read_dq_count; // FIXME? max it out?
        }

        DRAM_CSR_WRITE(node, BDK_LMCX_DBTRAIN_CTL(lmc), dbtrain_ctl.u);
        //BDK_CSR_READ(node, BDK_LMCX_DBTRAIN_CTL(lmc));

        VB_PRT(VBL_TME, "N%d.LMC%d.R%d: LRDIMM: Set DBTRAIN_CTL: 0x%016lx\n",
               node, lmc, rank, dbtrain_ctl.u);

        // select function space for BCW writes inside the loop
        set_function_space(node, lmc, rank, rankondimm(rank)); // set space for rank

        for (set = 0; set < 64; set++) {
            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: LRDIMM: %s iteration, setting %2d\n",
                   node, lmc, rank, mode_str, set);

            // set new values into DBs
            // these should be written indirectly to the function space set above
            bcw_write(node, lmc, rank, /*space*/0, /*mrreg*/base,   set, 1);
            bcw_write(node, lmc, rank, /*space*/0, /*mrreg*/base+1, set, 1);

            // kick off RW_TRAINING sequence
	    perform_octeontx_ddr_sequence(node, (1 << rank), lmc, 14);
            //bdk_wait_usec(500); // FIXME?? let it settle...

            do_phy_reset(node, lmc);

            // read settings out of mpr_data registers and put into array
            process_results(node, lmc, rank, set, /*byte_mode*/1, /*ignore_falling*/0);

            // check and see if we can break out of loop
            if (stop_train_early &&
                check_results(node, lmc, rank, set, /*transition*/trans, 1/*silent*/))
            {
                break;
            }
        } /* for (set = 0; set < 64; set++) */

        set_function_space(node, lmc, rank, /*space*/0);

        db_set_training_mode(node, lmc, rank, NORM_MODE);

        set_function_space(node, lmc, rank, /*space*/0);

        // set back into normal operating mode
        if (mode == MREP_MODE)
            dram_mpr_mode(node, lmc, rank, /*OFF*/0); // take out of MPR mode
        else
            dram_wl_mode(node, lmc, rank, /*OFF*/0); // take out of WL mode

        // make sure we found a good setting
        print_results(node, lmc, rank, 63, mode_str);

        results = check_results(node, lmc, rank, 63, /*transition*/trans, 0/*silent*/);

        // write good settings into DB
        // need to transform from single list of all parts to high and low nibble arrays
        for (part = 0; part < 18; part += 2) {
            final_data_low[part/2]  = (final_setting[part]   + mrep_loffset);
            if (final_data_low[part/2] > 0x3F) final_data_low[part/2] = 0x3F;
            if (final_data_low[part/2] < 0) final_data_low[part/2] = 0;
            final_data_high[part/2] = (final_setting[part+1] + mrep_hoffset);
            if (final_data_high[part/2] > 0x3F) final_data_high[part/2] = 0x3F;
            if (final_data_high[part/2] < 0) final_data_high[part/2] = 0;
        }

        // allow override of final settings, but ONLY if bad results
        override = 0;

        if (!results) {
            if ((s = lookup_env_parameter("ddr%d_%s%d_flo", lmc, mode_str_l, rank)) != NULL) {
                uint64_t flo = strtoull(s, NULL, 0);
                for (i = 0; i < 8; i++) {
                    final_data_low[i] = (flo >> (i * 8)) & 0xFF;
                }
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_fle", lmc, mode_str_l, rank)) != NULL) {
                final_data_low[8] = strtoull(s, NULL, 0) & 0xFF;
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_fhi", lmc, mode_str_l, rank)) != NULL) {
                uint64_t fhi = strtoull(s, NULL, 0);
                for (i = 0; i < 8; i++) {
                    final_data_high[i] = (fhi >> (i * 8)) & 0xFF;
                }
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_fhe", lmc, mode_str_l, rank)) != NULL) {
                final_data_high[8] = strtoull(s, NULL, 0) & 0xFF;
                override = 1;
            }
        }

        // check values
        if (!results && !override) {
            ddr_print("N%d.LMC%d.R%d: LRDIMM: db_%s_train: Aborted!\n",
                      node, lmc, rank, mode_str);
            return 0;
        }

        if (override) {
            ddr_print("N%d.LMC%d.R%d: LRDIMM: db_%s_train: OVERRIDDEN!\n",
                      node, lmc, rank, mode_str);
        }

        // now program the settings...
        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s Programming for lower nibble, phase [8:0] ",
                  node, lmc, rank, mode_str);
        for (i = 8; i >= 0; i--) ddr_print("0x%02x ", final_data_low[i]); ddr_print("\n");

        program_db_train_setting(node, lmc, rank, rankondimm(rank), base,   final_data_low);

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s Programming for upper nibble, phase [8:0] ",
                  node, lmc, rank, mode_str);
        for (i = 8; i >= 0; i--) ddr_print("0x%02x ", final_data_high[i]); ddr_print("\n");

        program_db_train_setting(node, lmc, rank, rankondimm(rank), base+1, final_data_high);

        set_function_space(node, lmc, rank, /*space*/0);
        db_ranks_present(node, lmc, 0, dimm_count); // FIXME: disable all
        db_ranks_present(node, lmc, rank_mask, dimm_count); // FIXME: enable present

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s training done.\n",
                  node, lmc, rank, mode_str);

#if 1
        if (mode == MREP_MODE) {
            BDK_CSR_INIT(ext_config, node, BDK_LMCX_EXT_CONFIG(lmc));
            ddr_print("N%d.LMC%d.R%d: LRDIMM: %s: EXT_CONFIG 0x%016lx\n",
                      node, lmc, rank, mode_str, ext_config.u);
        }
#endif

    } /* for (rank = 0; rank < 4; rank++) */

    // do NOT allow MPR to capture anything in MPR register
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_MR_MPR_CTL(lmc),
                    c.s.mpr_sample_dq_enable = 0);

    ddr_print("N%d.LMC%d: LRDIMM: db_%s_train: Finished!\n",
              node, lmc, mode_str);

    current_training_mode = NORM_MODE; // now reset to NORMAL

    return 1;
}

// func: byte_map_5
// maps an index 0-4 into the encoded register setting as defined in the DB spec
static int
byte_map_5(int setting)
//virtual function bit[3:0] byte_map_5(int setting);
{
    // register as as follows:
    // 0->0 cycles
    // 1->+1 cycles
    // 2->+2 cycles
    // 5->-1 cycles
    // 6->-2 cycles
#if 1
    uint8_t byteSettingMap[5] = {6,5,0,1,2};
#else
    uint8_t byteSettingMap[5] = {2,1,0,5,6};
#endif

    // byte setting register has upper and lower nibble settings together in the
    // upper and lower nibble of the 8 bit register
    return byteSettingMap[setting];

} // endfunction : byte_map_5

#if 0
// FIXME? not needed yet/ever?

// func: byte_unmap_5
// maps an  encoded register setting as defined in the DB spec to an index 0-4
static int
byte_unmap_5(int setting)
//virtual function bit[3:0] byte_unmap_5(int setting);
{
    // register as as follows:
    // 0->0 cycles
    // 1->+1 cycles
    // 2->+2 cycles
    // 5->-1 cycles
    // 6->-2 cycles
    uint8_t byteSettingMap[7] = {2,3,4,15,15,1,0};

    // byte setting register has upper and lower nibble settings together in the
    // upper and lower nibble of the 8 bit register
    return byteSettingMap[setting];

} // endfunction : byte_unmap_5
#endif

// func: bit_map_32
// maps an index 0-31 to the encoded register setting for the -15 to +15 regs in DB spec
static int
bit_map_32(int setting)
//virtual function bit[7:0] bit_map_32(int setting);
{
    // register settings are:
    // -15->31
    // -14->30
    // -1->17
    // 0->0
    // 1->+1
    // 15->+15
    uint8_t bitSettingMap[31] = {31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,0,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15};
    return bitSettingMap[setting];

} // endfunction : bit_map_32

// func: db_mrd_train and db_mwd_train
// runs the MRD or MWD training sequence for this
int
lrdimm_db_mrd_mwd_train(bdk_node_t node, int lmc,
                        dram_init_data_t *init_data, int mode)
{
    int rank_mask =             init_data->refs.rank_mask;
    int dimm_count =            init_data->refs.dimm_count;

    int rank, set, byte_set, part, i, results, override;
    //int final_data_high[18/2], final_data_low[18/2];
    bdk_lmcx_dbtrain_ctl_t dbtrain_ctl;
    int read_dq_count = (mode == MRD_MODE) ? 55 : 32; // FIXME: what should this be, really?
    const char *s;
    int done_training = 0; // use to break out of double loop
    unsigned new_data;

    //int bit_length = train_dq_phase ? `DBTRAIN_MRD_BIT_LENGTH : 1;
    int bit_length = /*DBTRAIN_MRD_BIT_LENGTH*/31; // FIXME? is 31 correct?

    char *mode_str = (mode == MRD_MODE) ? "MRD":"MWD";
    char *mode_str_l = (mode == MRD_MODE) ? "mrd":"mwd";

    int full = (mode == MRD_MODE) ? 12 : 13; // full-cycle base BCx register
    int sub = (mode == MRD_MODE) ? 4 : 8; // sub-cycle base BCx register

    //int tccd_setting = p_sequencer.cfg.csr_model.MODEREG_PARAMS3.TCCD_L.get();
    BDK_CSR_INIT(params3, node, BDK_LMCX_MODEREG_PARAMS3(lmc));
    int tccd_setting = params3.s.tccd_l;

    current_training_mode = mode; // now set

    // set TCCD to meet TCCD_CMP
    //p_sequencer.cfg.csr_model.MODEREG_PARAMS3.TCCD_L.set(4);
    params3.s.tccd_l = 4;
    // FIXME? do we need to write this now? original code does NOT...
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS3(lmc), params3.u);

    ddr_print("N%d.LMC%d: LRDIMM: db_%s_train: rank_mask 0x%02x\n",
              node, lmc, mode_str, rank_mask);

    if (mode == MRD_MODE) {
        if ((s = lookup_env_parameter_ull("mrd_read_dq_count")) != NULL) {
            read_dq_count = strtoull(s, NULL, 0);
        }
    } else {
        if ((s = lookup_env_parameter_ull("mwd_read_dq_count")) != NULL) {
            read_dq_count = strtoull(s, NULL, 0);
        }
    }

    // allow MPR to capture anything in MPR register
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_MR_MPR_CTL(lmc),
                    c.s.mpr_sample_dq_enable = 1);

    for (rank = 0; rank < 4; rank++) {

        //bit [7:0] full_cycle[`DQS_BITS], partial_cycle_high[`DQS_BITS], partial_cycle_low[`DQS_BITS];
        int full_cycle[18/2], partial_cycle_high[18/2], partial_cycle_low[18/2];

        if (! (rank_mask & (1 << rank)))
            continue;

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s training started...\n",
                  node, lmc, rank, mode_str);

        if (mode == MRD_MODE) {
            set_function_space(node, lmc, rank, /*space*/0);
            dram_mpr_mode(node, lmc, rank, /*ON*/1); // put DRAM in MPR mode
        }

        // MRD is done in 0-1/2clk in 1/64th of a clock (over 5 full-cycle settings)
        init_db_results(18, bit_length * /*`DBTRAIN_REG_SET_LENGTH*/5);

#if 0
        // FIXME: try these after the pattern setup
        //set_function_space(node, lmc, rank, /*space*/0);
        db_ranks_present(node, lmc, (1 << rank), dimm_count); // only current rank is "present"?

        // MWD mode: tell DB which rank to level
        if (mode == MWD_MODE) {
            //set_function_space(node, lmc, rank, /*space*/0);
            bcw_write_small(node, lmc, rank, 8, rank);
        }
#endif
        // FIXME - setup pattern to match data in MPR registers
        if (mode == MRD_MODE) {

            // from the original code
            set_function_space(node, lmc, rank, /*space*/5);
            bcw_write(node, lmc, rank, 0, 0, 0x00, 1);
            bcw_write(node, lmc, rank, 0, 1, 0xff, 1);
            bcw_write(node, lmc, rank, 0, 2, 0x00, 1);
            bcw_write(node, lmc, rank, 0, 3, 0xff, 1);

            set_function_space(node, lmc, rank, /*space*/6);
            bcw_write(node, lmc, rank, 0, 0, 0x00, 1);
            bcw_write(node, lmc, rank, 0, 1, 0xff, 1);
            bcw_write(node, lmc, rank, 0, 2, 0x00, 1);
            bcw_write(node, lmc, rank, 0, 3, 0xff, 1);
        }
#if 0
        else { // FIXME: Mike's original code for MWD
            set_function_space(node, lmc, rank, /*space*/5);
            bcw_write(node, lmc, rank, 0, 0, 0x01, 1);
            bcw_write(node, lmc, rank, 0, 1, 0x23, 1);
            bcw_write(node, lmc, rank, 0, 2, 0x45, 1);
            bcw_write(node, lmc, rank, 0, 3, 0x67, 1);
            set_function_space(node, lmc, rank, /*space*/6);
            bcw_write(node, lmc, rank, 0, 0, 0x89, 1);
            bcw_write(node, lmc, rank, 0, 1, 0xab, 1);
            bcw_write(node, lmc, rank, 0, 2, 0xcd, 1);
            bcw_write(node, lmc, rank, 0, 3, 0xef, 1);
        }
#endif
        // F6BC4x - set to send back bit by bit status
        bcw_write(node, lmc, rank, 6, 4, 0x01, 1);
#if 1
        // FIXME: try these after the pattern setup
        //set_function_space(node, lmc, rank, /*space*/0);
        db_ranks_present(node, lmc, (1 << rank), dimm_count); // only current rank is "present"?

        // MWD mode: tell DB which rank to level
        if (mode == MWD_MODE) {
            //set_function_space(node, lmc, rank, /*space*/0);
            bcw_write_small(node, lmc, rank, 8, rankondimm(rank)); // FIXME?
        }
#endif

#if 1
        // FIXME: moved here after setup of F[56]BC[0:3] above
        // NOTE: was before that setup in the original code...
        //set_function_space(node, lmc, rank, /*space*/0);
        db_set_training_mode(node, lmc, rank, mode);  // put DB in approp mode
#endif

        // now setup dbtrain register
        dbtrain_ctl.u = 0;

        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            dbtrain_ctl.cn83xx.prank          = rank;
            dbtrain_ctl.cn83xx.activate       = (mode == MWD_MODE);
            dbtrain_ctl.cn83xx.write_ena      = (mode == MWD_MODE);
            dbtrain_ctl.cn83xx.read_cmd_count = 1; // FIXME? was 1...
            dbtrain_ctl.cn83xx.read_dq_count  = read_dq_count; // FIXME? max it out?
            dbtrain_ctl.cn83xx.tccd_sel       = 1;
            dbtrain_ctl.cn83xx.db_sel         = (mode == MRD_MODE) ? !!rank2dimm(rank) : 0;
        }
        else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
            dbtrain_ctl.cn9.prank1         = rank;
            dbtrain_ctl.cn9.prank2         = rank;
            dbtrain_ctl.cn9.activate       = (mode == MWD_MODE);
            dbtrain_ctl.cn9.write_ena      = (mode == MWD_MODE);
            dbtrain_ctl.cn9.read_cmd_count = 1; // FIXME? was 1...
            dbtrain_ctl.cn9.read_dq_count  = read_dq_count; // FIXME? max it out?
            dbtrain_ctl.cn9.tccd_sel       = 1;
            dbtrain_ctl.cn9.db_sel         = (mode == MRD_MODE) ? !!rank2dimm(rank) : 0;
        }

        if (mode == MRD_MODE) {
            DRAM_CSR_WRITE(node, BDK_LMCX_DBTRAIN_CTL(lmc), dbtrain_ctl.u);
            //BDK_CSR_READ(node, BDK_LMCX_DBTRAIN_CTL(lmc));
            VB_PRT(VBL_TME, "N%d.LMC%d: LRDIMM: Set DBTRAIN_CTL: 0x%016lx\n",
                   node, lmc, dbtrain_ctl.u);
        }

        for (byte_set = 0; byte_set < /*`DBTRAIN_REG_SET_LENGTH*/5; byte_set++) {

            if (mode == MWD_MODE) {

                // IDT doc says change the address
                int ba_bits = (byte_set & 3);
                int bg_bits = (byte_set >> 2) & 1;
                if (bdk_is_model(OCTEONTX_CN8XXX)) {
                    dbtrain_ctl.cn83xx.ba = ba_bits;
                    dbtrain_ctl.cn83xx.bg = bg_bits;
                }
                else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
                    dbtrain_ctl.cn9.ba = ba_bits;
                    dbtrain_ctl.cn9.bg = bg_bits;
                }

                VB_PRT(VBL_TME, "N%d.LMC%d: LRDIMM: Set DBTRAIN_CTL: 0x%016lx\n",
                       node, lmc, dbtrain_ctl.u);

                // from IDT document: program with different settings for each byte_set
                // rotate through: 2B, AC, 56
                set_function_space(node, lmc, rank, /*space*/5);
                bcw_write(node, lmc, rank, 0, 0, (0x00ff00UL >> ((byte_set % 3)*8) & 0xFF), 1);
                bcw_write(node, lmc, rank, 0, 1, (0x0000ffUL >> ((byte_set % 3)*8) & 0xFF), 1);
                bcw_write(node, lmc, rank, 0, 2, (0xffff00UL >> ((byte_set % 3)*8) & 0xFF), 1);
                bcw_write(node, lmc, rank, 0, 3, (0x0000ffUL >> ((byte_set % 3)*8) & 0xFF), 1);
                set_function_space(node, lmc, rank, /*space*/6);
                bcw_write(node, lmc, rank, 0, 0, (0xffff00UL >> ((byte_set % 3)*8) & 0xFF), 1);
                bcw_write(node, lmc, rank, 0, 1, (0x00ffffUL >> ((byte_set % 3)*8) & 0xFF), 1);
                bcw_write(node, lmc, rank, 0, 2, (0xff00ffUL >> ((byte_set % 3)*8) & 0xFF), 1);
                bcw_write(node, lmc, rank, 0, 3, (0xff0000UL >> ((byte_set % 3)*8) & 0xFF), 1);
            }

            set_function_space(node, lmc, rank, /*space*/0);

            // setup full-cycle delay
            new_data = munge2(4,byte_map_5(byte_set), 4,byte_map_5(byte_set));

            if (cs_mode == QR_X4_DDP) {
                // upper ranks are in different register, so this gets a little weird
                bcw_write(node, lmc, rank, (rank & 1), (full + (rank & 2)), new_data, 1);
            } else {
                bcw_write(node, lmc, rank, rankondimm(rank), full, new_data, 1);
            }

            // set function space approp. for rank
            set_function_space(node, lmc, rank, /*space*/rankondimm(rank));

            for (set = 0; set < bit_length; set++) {

                if (mode == MWD_MODE) {
                    // IDT doc says change the address
                    if (bdk_is_model(OCTEONTX_CN8XXX))
                        dbtrain_ctl.cn83xx.row_a = set;
                    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
                        dbtrain_ctl.cn9.row_a = set;

                    DRAM_CSR_WRITE(node, BDK_LMCX_DBTRAIN_CTL(lmc), dbtrain_ctl.u);
                    //BDK_CSR_READ(node, BDK_LMCX_DBTRAIN_CTL(lmc));
                }

                // set sub-cycle values into DBs (use space from above)
                bcw_write(node, lmc, rank, /*space*/0, sub, bit_map_32(set), 1);
                bcw_write(node, lmc, rank, /*space*/0, sub+1, bit_map_32(set), 1);

                VB_PRT(VBL_DEV, "N%d.LMC%d: LRDIMM: %s iteration, rank %1d, full 0x%02x, sub %2d\n",
                       node, lmc, mode_str, rank, new_data, bit_map_32(set));

                // kick off sequence
                perform_octeontx_ddr_sequence(node, (1 << rank), lmc, 14);
                bdk_wait_usec(500); // FIXME?? let it settle...

                do_phy_reset(node, lmc);

                // read settings out of MPR_data registers and put into array
                process_results(node, lmc, rank, (byte_set*bit_length)+set, 1, /*ignore_falling*/0);

                // check and see if we can break out of loop
                if (stop_train_early &&
                    check_results(node, lmc, rank, (byte_set*bit_length)+set, 0/*pulse of ones*/, 1/*silent*/))
                {
                    done_training = 1;
                    break;
                }
            } // set

            if (done_training)
                break;  // break out of this loop as well

        } // byte_set

        // revert to normal training mode
        set_function_space(node, lmc, rank, /*space*/0);
        db_set_training_mode(node, lmc, rank, NORM_MODE);

        // set back into normal operating mode
        if (mode == MRD_MODE) {
            set_function_space(node, lmc, rank, /*space*/0);
            dram_mpr_mode(node, lmc, rank, 0); // take out of MPR mode
        }

        // make sure we found a good setting
        print_results(node, lmc, rank, bit_length * /*`DBTRAIN_REG_SET_LENGTH*/5 - 1, mode_str);

        results = check_results(node, lmc, rank, bit_length * /*`DBTRAIN_REG_SET_LENGTH*/5 - 1, 0, 0/*silent*/);

        // need to transform from single list of all parts to high and low nibble arrays
        for (part = 0; part < 18; part+=2) {
            full_cycle[part/2] = 0;
            partial_cycle_low[part/2] = 0;
            partial_cycle_high[part/2] = 0;

            if (final_setting[part] >= 0) {
                full_cycle[part/2]  = byte_map_5(final_setting[part] / bit_length) & 0x0F;
                partial_cycle_low[part/2] = bit_map_32(final_setting[part] % bit_length);
            }

            if (final_setting[part+1] >= 0) {
                full_cycle[part/2] |= (byte_map_5(final_setting[part+1] / bit_length) & 0x0F) << 4;
                partial_cycle_high[part/2] = bit_map_32(final_setting[part+1] % bit_length);
            }
        }

        // allow override of final settings, but ONLY if bad results
        override = 0;

        if (!results) {
            if ((s = lookup_env_parameter("ddr%d_%s%d_plo", lmc, mode_str_l, rank)) != NULL) {
                uint64_t plo = strtoull(s, NULL, 0);
                for (i = 0; i < 8; i++) {
                    partial_cycle_low[i] = (plo >> (i * 8)) & 0xFF;
                }
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_ple", lmc, mode_str_l, rank)) != NULL) {
                partial_cycle_low[8] = strtoull(s, NULL, 0) & 0xFF;
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_phi", lmc, mode_str_l, rank)) != NULL) {
                uint64_t phi = strtoull(s, NULL, 0);
                for (i = 0; i < 8; i++) {
                    partial_cycle_high[i] = (phi >> (i * 8)) & 0xFF;
                }
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_phe", lmc, mode_str_l, rank)) != NULL) {
                partial_cycle_high[8] = strtoull(s, NULL, 0) & 0xFF;
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_ful", lmc, mode_str_l, rank)) != NULL) {
                uint64_t ful = strtoull(s, NULL, 0);
                for (i = 0; i < 8; i++) {
                    full_cycle[i] = (ful >> (i * 8)) & 0xFF;
                }
                override = 1;
            }
            if ((s = lookup_env_parameter("ddr%d_%s%d_fue", lmc, mode_str_l, rank)) != NULL) {
                full_cycle[8] = strtoull(s, NULL, 0) & 0xFF;
                override = 1;
            }
        }

        if (!results && !override) {
            ddr_print("N%d.LMC%d.R%d: LRDIMM: db_%s_train: Aborted!\n",
                      node, lmc, rank, mode_str);
            return 0;
        }

        if (override) {
            ddr_print("N%d.LMC%d.R%d: LRDIMM: db_%s_train: OVERRIDDEN!\n",
                      node, lmc, rank, mode_str);
        }

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s Programming for full_cycle [8:0]: ",
                  node, lmc, rank, mode_str);
        for (i = 8; i >= 0; --i) ddr_print("0x%02x ", full_cycle[i]); ddr_print("\n");

        // full-cycle
        if (cs_mode == QR_X4_DDP) {
            // upper ranks are in different register, so this gets a little weird
            program_db_train_setting(node, lmc, rank, (rank & 1), (full + (rank & 2)), full_cycle);
        } else {
            program_db_train_setting(node, lmc, rank, rankondimm(rank), full, full_cycle);
        }

        // partial cycle
        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s Programming for lower nibble, partial_cycle [8:0]: ",
                  node, lmc, rank, mode_str);
        for (i = 8; i >= 0; --i) ddr_print("0x%02x ", partial_cycle_low[i]); ddr_print("\n");

        program_db_train_setting(node, lmc, rank, rankondimm(rank), sub,   partial_cycle_low);

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s Programming for upper nibble, partial_cycle [8:0]: ",
                  node, lmc, rank, mode_str);
        for (i = 8; i >= 0; --i) ddr_print("0x%02x ", partial_cycle_high[i]); ddr_print("\n");

        program_db_train_setting(node, lmc, rank, rankondimm(rank), sub+1, partial_cycle_high);

        set_function_space(node, lmc, rank, /*space*/0);
        db_ranks_present(node, lmc, 0, dimm_count); // FIXME: disable all
        db_ranks_present(node, lmc, rank_mask, dimm_count); // FIXME: enable present

        ddr_print("N%d.LMC%d.R%d: LRDIMM: %s training done.\n",
                  node, lmc, rank, mode_str);

    } // rank

    // do NOT allow MPR to capture anything in MPR register
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_MR_MPR_CTL(lmc),
                    c.s.mpr_sample_dq_enable = 0);

    // set TCCD back to normal
    //p_sequencer.cfg.csr_model.MODEREG_PARAMS3.TCCD_L.set(tccd_setting);
    params3.s.tccd_l = tccd_setting;
    // FIXME? do we need to write this now? original code does NOT...
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS3(lmc), params3.u);

    ddr_print("N%d.LMC%d: LRDIMM: db_%s_train: Finished!\n",
              node, lmc, mode_str);

    current_training_mode = NORM_MODE; // now reset to NORMAL

    return 1;

} // endtask : db_mrd_train and db_mwd_train

