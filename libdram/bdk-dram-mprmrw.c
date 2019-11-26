/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

// MRW/MPR related
#define ENABLE_MRW_VERBOSITY 0
#define ENABLE_MPR_VERBOSITY 0

void
ddr4_mrw(bdk_node_t node, int ddr_interface_num, int rank,
         int mr_wr_addr, int mr_wr_sel, int mr_wr_bg1)
{
    bdk_lmcx_mr_mpr_ctl_t lmc_mr_mpr_ctl;

    lmc_mr_mpr_ctl.u = 0;

    lmc_mr_mpr_ctl.s.mr_wr_addr                 = (mr_wr_addr == -1) ? 0 : mr_wr_addr;
    lmc_mr_mpr_ctl.s.mr_wr_sel                  = mr_wr_sel;
    lmc_mr_mpr_ctl.s.mr_wr_rank                 = rank;
    lmc_mr_mpr_ctl.s.mr_wr_use_default_value    = (mr_wr_addr == -1) ? 1 : 0;
    lmc_mr_mpr_ctl.s.mr_wr_bg1                  = mr_wr_bg1;

    DRAM_CSR_WRITE(node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num), lmc_mr_mpr_ctl.u);

    /* Mode Register Write */
    perform_octeontx_ddr_sequence(node, (1 << rank), ddr_interface_num, 0x8);
}

void
set_mpr_mode(bdk_node_t node, int lmc, int rank_mask, int mpr)
{
    int rankx;

    VB_PRT(VBL_FAE, "N%d.LMC%d: set_mpr_mode: ranks 0x%02x, mpr %d, %s-side(s)\n",
           node, lmc, rank_mask, mpr, "BOTH");

    DRAM_CSR_MODIFY(c, node, BDK_LMCX_MODEREG_PARAMS0(lmc),
		    (c.s.mprloc = 0, c.s.mpr = mpr));

    for (rankx = 0; rankx < 4; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;
        ddr4_mrw(node, lmc, rankx, -1, 3, 0);
    } /* for (rankx = 0; rankx < 4; rankx++) */
}

static void
do_ddr4_mpr_read(bdk_node_t node, int ddr_interface_num,
                 int rank, int page, int location)
{
    bdk_lmcx_mr_mpr_ctl_t lmc_mr_mpr_ctl;

    // Do not fetch CSR, just zero all fields initially
    lmc_mr_mpr_ctl.u = 0;

    lmc_mr_mpr_ctl.s.mr_wr_sel                  = page; /* Page */
    lmc_mr_mpr_ctl.s.mr_wr_rank                 = rank;
    lmc_mr_mpr_ctl.s.mpr_loc                    = location;

    DRAM_CSR_WRITE(node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num), lmc_mr_mpr_ctl.u);

    /* MPR register access sequence */
    perform_octeontx_ddr_sequence(node, (1 << rank), ddr_interface_num, 0x9);
}

void
ddr4_mpr_read(bdk_node_t node, int ddr_interface_num, int rank,
			  int page, int location, uint64_t *mpr_data)
{
    do_ddr4_mpr_read(node, ddr_interface_num, rank, page, location);

    mpr_data[0] = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA0(ddr_interface_num));
    mpr_data[1] = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA1(ddr_interface_num));
    mpr_data[2] = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA2(ddr_interface_num));

    debug_print("MPR Read %016lx.%016lx.%016lx\n", mpr_data[2], mpr_data[1], mpr_data[0]);
}

/* Display MPR values for Page */
void
Display_MPR_Page(bdk_node_t node, int rank_mask, int ddr_interface_num, int page)
{
    int rankx;
    uint64_t mpr_data[3];

    for (rankx = 0; rankx < 4; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;

        ddr_print("N%d.LMC%d.R%d: MPR Page %d loc [0:3]: ",
                  node, ddr_interface_num, rankx, page);

        for (int location = 0; location < 4; location++) {
            ddr4_mpr_read(node, ddr_interface_num, rankx, page, location, mpr_data);
            ddr_print("0x%02lx ", mpr_data[0] & 0xFF);
        }
        ddr_print("\n");

    } /* for (rankx = 0; rankx < 4; rankx++) */
}

/* Display Full MPR values for Page/Location */
void
Display_Full_MPR_Page_Location(bdk_node_t node, int ddr_interface_num,
                               int rank_mask, int page, int location)
{
    int rankx;
    uint64_t mpr_data[3];

    for (rankx = 0; rankx < 4; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;

        ddr4_mpr_read(node, ddr_interface_num, rankx, page, location, mpr_data);

        bdk_error("N%d.LMC%d.R%d: PARITY: MPR Page %d Loc %d: %04lx.%016lx.%016lx\n",
                  node, ddr_interface_num, rankx, page, location,
                  mpr_data[2], mpr_data[1], mpr_data[0]);

    } /* for (rankx = 0; rankx < 4; rankx++) */
}

void ddr4_mpr_write(bdk_node_t node, int ddr_interface_num, int rank,
                    int page, int location, uint8_t mpr_data)
{
    bdk_lmcx_mr_mpr_ctl_t lmc_mr_mpr_ctl;

    lmc_mr_mpr_ctl.u = 0;

    lmc_mr_mpr_ctl.s.mr_wr_addr                 = mpr_data;
    lmc_mr_mpr_ctl.s.mr_wr_sel                  = page; /* Page */
    lmc_mr_mpr_ctl.s.mr_wr_rank                 = rank;
    lmc_mr_mpr_ctl.s.mpr_loc                    = location;
    lmc_mr_mpr_ctl.s.mpr_wr                     = 1; /* Read=0, Write=1 */

    DRAM_CSR_WRITE(node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num), lmc_mr_mpr_ctl.u);

    /* MPR register access sequence */
    perform_octeontx_ddr_sequence(node, (1 << rank), ddr_interface_num, 0x9);
}

void set_vref(bdk_node_t node, int ddr_interface_num, int rank,
	      int range, int value)
{
    bdk_lmcx_mr_mpr_ctl_t lmc_mr_mpr_ctl;
    bdk_lmcx_modereg_params3_t lmc_modereg_params3;
    int mr_wr_addr = 0;

    lmc_mr_mpr_ctl.u = 0;

    lmc_modereg_params3.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS3(ddr_interface_num));

    mr_wr_addr |= lmc_modereg_params3.s.tccd_l<<10; /* A12:A10 tCCD_L */
    mr_wr_addr |= 1<<7;         /* A7 1 = Enable(Training Mode) */
    mr_wr_addr |= range<<6;     /* A6 VrefDQ Training Range */
    mr_wr_addr |= value<<0;     /* A5:A0 VrefDQ Training Value */

    lmc_mr_mpr_ctl.s.mr_wr_addr               = mr_wr_addr;
    lmc_mr_mpr_ctl.s.mr_wr_sel                = 6; /* Write MR6 */
    lmc_mr_mpr_ctl.s.mr_wr_rank               = rank;

    DRAM_CSR_WRITE(node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num), lmc_mr_mpr_ctl.u);

    /* 0x8 = Mode Register Write */
    perform_octeontx_ddr_sequence(node, (1 << rank), ddr_interface_num, 0x8);

    /* It is vendor specific whether Vref_value is captured with A7=1.
       A subsequent MRS might be necessary. */
    perform_octeontx_ddr_sequence(node, (1 << rank), ddr_interface_num, 0x8);
}

static void set_DRAM_output_inversion (bdk_node_t node,
                                       int ddr_interface_num,
                                       int dimm_count,
                                       int rank_mask,
                                       int inversion)
{
    bdk_lmcx_ddr4_dimm_ctl_t lmc_ddr4_dimm_ctl;
    bdk_lmcx_dimmx_params_t lmc_dimmx_params;
    bdk_lmcx_dimm_ctl_t lmc_dimm_ctl;
    int dimm_no;

    lmc_ddr4_dimm_ctl.u = 0;  /* Don't touch extended register control words */
    DRAM_CSR_WRITE(node, BDK_LMCX_DDR4_DIMM_CTL(ddr_interface_num), lmc_ddr4_dimm_ctl.u);

    VB_PRT(VBL_FAE, "All DIMMs: Register Control Word          RC0 : %x\n", (inversion & 1));

    for (dimm_no = 0; dimm_no < dimm_count; ++dimm_no) {
        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(ddr_interface_num, dimm_no));
        lmc_dimmx_params.s.rc0  = (lmc_dimmx_params.s.rc0 & ~1) | (inversion & 1);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(ddr_interface_num, dimm_no), lmc_dimmx_params.u);
    }

    /* LMC0_DIMM_CTL */
    lmc_dimm_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(ddr_interface_num));
    lmc_dimm_ctl.s.dimm0_wmask         = 0x1;
    lmc_dimm_ctl.s.dimm1_wmask         = (dimm_count > 1) ? 0x0001 : 0x0000;

    VB_PRT(VBL_FAE, "%-45s : 0x%016lx\n", "LMC DIMM_CTL", lmc_dimm_ctl.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(ddr_interface_num), lmc_dimm_ctl.u);

    perform_octeontx_ddr_sequence(node, rank_mask, ddr_interface_num, 0x7 ); /* Init RCW */
}

static void
write_mpr_page0_pattern(bdk_node_t node, int rank_mask,
                        int ddr_interface_num, int dimm_count,
                        int pattern, int location_mask)
{
    int rankx;
    int location;
#if ENABLE_MPR_VERBOSITY
    dram_verbosity_t save_dram_verbosity = dram_verbosity;
    dram_verbosity |= (VBL_SEQ | VBL_CSRS);
#endif

    VB_PRT(VBL_FAE, "N%d.LMC%d: write_mpr_page0_pattern: ranks 0x%02x, dimms %d, pattern 0x%x, loc_mask 0x%02x\n",
           node, ddr_interface_num, rank_mask, dimm_count, pattern, location_mask);

    for (rankx = 0; rankx < 4; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;
        for (location = 0; location < 4; ++location) {
            if (!(location_mask & (1 << location)))
                continue;

            ddr4_mpr_write(node, ddr_interface_num, rankx,
                           /* page */ 0, /* location */ location, pattern);
        }
    }

#if ENABLE_MPR_VERBOSITY
    dram_verbosity = save_dram_verbosity;
#endif
}

void change_rdimm_mpr_pattern (bdk_node_t node, int rank_mask,
                               int ddr_interface_num, int dimm_count)
{
    int save_ref_zqcs_int;
    int save_lrdimm_mode;

    // HRM-CN8XXX Section 6.9.8
    // HRM-CN9XXX Section 7.9.7
    /*
      Okay, here is the latest sequence.  This should work for all
      chips and passes (78,88,73,etc).  This sequence should be run
      immediately after DRAM INIT.  The basic idea is to write the
      same pattern into each of the 4 MPR locations in the DRAM, so
      that the same value is returned when doing MPR reads regardless
      of the inversion state.  My advice is to put this into a
      function, change_rdimm_mpr_pattern or something like that, so
      that it can be called multiple times, as I think David wants a
      clock-like pattern for OFFSET training, but does not want a
      clock pattern for Bit-Deskew.  You should then be able to call
      this at any point in the init sequence (after DRAM init) to
      change the pattern to a new value.
      Mike

      A correction: PHY doesn't need any pattern during offset
      training, but needs clock like pattern for internal vref and
      bit-dskew training.  So for that reason, these steps below have
      to be conducted before those trainings to pre-condition
      the pattern.  David

      Note: Step 3, 4, 8 and 9 have to be done through RDIMM
      sequence. If you issue MRW sequence to do RCW write (in o78 pass
      1 at least), LMC will still do two commands because
      CONTROL[RDIMM_ENA] is still set high. We don't want it to have
      any unintentional mode register write so it's best to do what
      Mike is doing here.
      Andrew
    */


    /* 1) Disable refresh (REF_ZQCS_INT = 0) */
    debug_print("1) Disable refresh (REF_ZQCS_INT = 0)\n");

    // HRM-CN9XXX Section 7.9.7.2
    save_ref_zqcs_int = set_zqcs_interval(node, ddr_interface_num, 0);

    /* 2) Put all devices in MPR mode (Run MRW sequence (sequence=8)
       with MODEREG_PARAMS0[MPRLOC]=0,
       MODEREG_PARAMS0[MPR]=1, MR_MPR_CTL[MR_WR_SEL]=3, and
       MR_MPR_CTL[MR_WR_USE_DEFAULT_VALUE]=1) */
    debug_print("2) Put all devices in MPR mode (Run MRW sequence (sequence=8)\n");

    // HRM-CN9XXX Section 7.9.7.3-7
    set_mpr_mode(node, ddr_interface_num, rank_mask, /* mpr */ 1); /* BOTH */

    /* 3) Disable RCD Parity (if previously enabled) - parity does not
       work if inversion disabled */
    debug_print("3) Disable RCD Parity\n");
    // FIXME: implement when RCD parity is implemented!

    /* 4) Disable Inversion in the RCD. */
    /*    a. I did (3&4) via the RDIMM sequence (seq_sel=7), but it
          may be easier to use the MRW sequence (seq_sel=8).  Just set
          MR_MPR_CTL[MR_WR_SEL]=7, MR_MPR_CTL[MR_WR_ADDR][3:0]=data,
          MR_MPR_CTL[MR_WR_ADDR][7:4]=RCD reg */
    debug_print("4) Disable Inversion in the RCD.\n");

    // HRM-CN9XXX Section 7.9.7.8-11
    set_DRAM_output_inversion(node, ddr_interface_num, dimm_count, rank_mask,
                               1 /* 1=disable output inversion*/);

    /* 5) Disable CONTROL[RDIMM_ENA] so that MR sequence goes out
       non-inverted.  */
    debug_print("5) Disable CONTROL[RDIMM_ENA]\n");

    // HRM-CN9XXX Section 7.9.7.12
    set_rdimm_mode(node, ddr_interface_num, 0);
    save_lrdimm_mode = set_lrdimm_mode(node, ddr_interface_num, 0);

    /* 6) Write all 4 MPR registers with the desired pattern (have to
       do this for all enabled ranks) */
    /*    a. MR_MPR_CTL.MPR_WR=1, MR_MPR_CTL.MPR_LOC=0..3,
          MR_MPR_CTL.MR_WR_SEL=0, MR_MPR_CTL.MR_WR_ADDR[7:0]=pattern */
    debug_print("6) Write all 4 MPR page 0 Training Patterns\n");

    // HRM-CN9XXX Section 7.9.7.13-16
    write_mpr_page0_pattern(node, rank_mask, ddr_interface_num,
                            dimm_count, 0x55, 0x8);

    /* 7) Re-enable RDIMM_ENA */
    debug_print("7) Re-enable RDIMM_ENA\n");

    // HRM-CN9XXX Section 7.9.7.17
    set_rdimm_mode(node, ddr_interface_num, 1);
    set_lrdimm_mode(node, ddr_interface_num, save_lrdimm_mode);

    /* 8) Re-enable RDIMM inversion */
    debug_print("8) Re-enable RDIMM inversion\n");

    // HRM-CN9XXX Section 7.9.7.18-21
    set_DRAM_output_inversion(node, ddr_interface_num, dimm_count, rank_mask,
                              0 /* 0=re-enable output inversion*/);

    /* 9) Re-enable RDIMM parity (if desired) */
    debug_print("9) Re-enable RDIMM parity (if desired)\n");
    // FIXME: implement when RCD parity is implemented!

    /* 10)Take B-side devices out of MPR mode (Run MRW sequence
       (sequence=8) with MODEREG_PARAMS0[MPRLOC]=0,
       MODEREG_PARAMS0[MPR]=0, MR_MPR_CTL[MR_WR_SEL]=3, and
       MR_MPR_CTL[MR_WR_USE_DEFAULT_VALUE]=1) */
    debug_print("10)Take B-side devices out of MPR mode\n");

    // HRM-CN9XXX Section 7.9.7.22-26
    set_mpr_mode(node, ddr_interface_num, rank_mask, /* mpr */ 0); /* BOTH */

    /* 11)Re-enable refresh (REF_ZQCS_INT=previous value) */
    debug_print("11)Re-enable refresh (REF_ZQCS_INT=previous value)\n");

    // HRM-CN9XXX Section 7.9.7.27
    (void) set_zqcs_interval(node, ddr_interface_num, save_ref_zqcs_int);
}

