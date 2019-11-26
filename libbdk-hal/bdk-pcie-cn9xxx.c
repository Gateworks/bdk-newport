/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gic.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-pcierc.h"
#include "libbdk-arch/bdk-csrs-pcieep.h"
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "libcavm-gsern/cavm-gsern-api.h"
#include "libcavm-gsern/cavm-gsern-settings.h"
#include "libcavm-gsern/cavm-gsern-init.h"

/* The SDK expects the prefetch memory regions to have an offset such that
   offset 0 creates PCIe address 0x10_0000_0000. This constant represents
   this offset */
static const uint64_t PREFETCH_OFFSET = 0x1000000000;

/* This is transmit override presets for Rev 1 9XXX which has the incorrect
   values. Set this to zero for No Tap override. This is for Errata 36412 -
   PCIE Glitch */
static const bool TX_OVERRIDE_PRESETS = true;

/* 02-22-2019 */
/* Errata 36412: Temporary Fix to Force Rx Detect On so that Tap Override
   Applied. This is necessary so that high leakage parts can train to GEN1.
   This effectively eliminates the glitch from the transmitter output */
static const bool TX_OVERRIDE_FORCE_RX_DETECT = true;

/* Use this to select different tx preset modes. This is ONLY used with errata
   36412 */
typedef enum
{
    TAP_OVERRIDE_PRESET_0_GEN2_6DB,             /* Index 0 in table is preset 0: gen2 6db */
    TAP_OVERRIDE_PRESET_1_GEN1_GEN2_35DB,       /* Index 1 in table is preset 1: gen2 3.5 db or gen1 */
} tap_override_preset_gen12_mode_t;

/* Default Tx Preset Tap Override */
/* This is if nothing in the device tree */
#define DEFAULT_TX_PRESET_TAP_OVERRIDE_VALUE 7

/* Always 11 presets */
#define GEN3_MAX_TX_PRESETS 11

/* How to wait for speed changes */
#define PCIE_SPEED_CHANGE_WAIT_USEC 25000

typedef struct
{
    uint8_t muxpost;
    uint8_t cpostb;
    uint8_t cposta;
    uint8_t enpost;
    uint8_t muxmain;
    uint8_t cmaind;
    uint8_t enmain;
    uint8_t muxpre;
    uint8_t cpreb;
    uint8_t cprea;
    uint8_t enpre;
} tx_tap_drv_override_t;

/* Compose a table of PCIE preset values, two GEN */

/* This has full scale preset values. This table is from Keith Peterson,
   modified from the original table from Scott MclHenny */
static const tx_tap_drv_override_t tx_tap_drv_override_gen123[11] =
{
    { 0x0, 0x5, 0x5, 0x3, 0xF, 0x5, 0xF, 0x2, 0x5, 0x0, 0x2 }, /* Preset 0 ALSO GEN2 6DB */
    { 0x0, 0x0, 0x7, 0x1, 0xF, 0x7, 0xF, 0x2, 0x7, 0x0, 0x2 }, /* Preset 1 ALSO GEN1 and GEN2 3.5 */
    { 0x0, 0x4, 0x4, 0x3, 0xF, 0x6, 0xF, 0x2, 0x6, 0x0, 0x2 }, /* Preset 2 */
    { 0x2, 0x5, 0x5, 0x3, 0xF, 0x5, 0xF, 0x2, 0x5, 0x0, 0x2 }, /* Preset 3 */
    { 0x2, 0x7, 0x0, 0x2, 0xF, 0x7, 0xF, 0x2, 0x7, 0x0, 0x2 }, /* Preset 4 */
    { 0x2, 0x5, 0x0, 0x2, 0xF, 0x6, 0xF, 0x2, 0x5, 0x4, 0x3 }, /* Preset 5 */
    { 0x2, 0x5, 0x0, 0x2, 0xF, 0x5, 0xF, 0x2, 0x5, 0x5, 0x3 }, /* Preset 6 */
    { 0x2, 0x4, 0x3, 0x3, 0xF, 0x4, 0xF, 0x0, 0x4, 0x4, 0x3 }, /* Preset 7 */
    { 0x0, 0x0, 0x5, 0x1, 0xF, 0x5, 0xF, 0x2, 0x5, 0x5, 0x3 }, /* Preset 8 */
    { 0x0, 0x0, 0x0, 0x0, 0xF, 0x7, 0xF, 0x2, 0x7, 0x7, 0x3 }, /* Preset 9 */
    { 0x0, 0x7, 0x7, 0x3, 0xF, 0x7, 0xF, 0x0, 0x0, 0x0, 0x0 }, /* Preset 10 */
};


/*
 * Check for errata condition for GSER 36412.   Clear the TX_OVERRIDE_PRESETS
 * to disable the workaround.  The override was being checked in a number of places
 * and it was simpler to have a single function.  This errata is ONLY for
 * T96 1.0 chips.
 *
 */
static bool __bdk_is_needed_gsern_pcie_errata_36412_workaround()
{
    if (TX_OVERRIDE_PRESETS && bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
    {
        return true;
    }

    return false;
}

/**
 * Return the number of possible PCIe ports on a node. The actual number
 * of configured ports may be less and may also be disjoint.
 *
 * @param node   Node to query
 *
 * @return Number of PCIe ports that are possible
 */
static int pcie_get_num_ports(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 4;
    else if (bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
        return 1;
    else if (bdk_is_model(OCTEONTX_LOKI))
        return 1;
    else if (bdk_is_model(OCTEONTX_CN98XX))
        return 5;
    else
        return 0;
}

/**
 * Return the Core physical base address for PCIe MEM access. Memory is
 * read/written as an offset from this address.
 *
 * @param node      Node to use in a Numa setup
 * @param pcie_port PCIe port the memory is on
 * @param mem_type  Type of memory
 *
 * @return 64bit physical address for read/write
 */
static uint64_t pcie_get_base_address(bdk_node_t node, int pcie_port, bdk_pcie_mem_t mem_type)
{
    /* We're using the Normal PEM outboud regions (legacy). This are 39l
        bits, but bits [38:31] are used to choose which
        PEMX_REG_NORMX_ACC. As described in the setup
        of PEMX_REG_NORMX_ACC, we use 6 of these bits for address
        extension */
    BDK_CSR_INIT(const_acc, node, BDK_PEMX_CONST_ACC(pcie_port));
    int region_bits = bdk_pop(const_acc.s.num_norm - 1);
    int addr_extension = region_bits - 2; /* Two bits used for type of access */
    int total_bits = addr_extension + const_acc.s.bits_norm;
    uint64_t pem_did = 0x10 + pcie_port; /* Bit 43 set per HRM */
    uint64_t address = (1ull << 47) | (pem_did << 39);
    address |= (uint64_t)mem_type << total_bits;
    return bdk_numa_get_address(node, address);
}

/**
 * Size of the Mem address region returned at address
 * bdk_pcie_get_base_address()
 *
 * @param node      Node to use in a Numa setup
 * @param pcie_port PCIe port the IO is for
 * @param mem_type  Type of memory
 *
 * @return Size of the Mem window
 */
static uint64_t pcie_get_base_size(bdk_node_t node, int pcie_port, bdk_pcie_mem_t mem_type)
{
    /* We're using the Normal PEM outboud regions (legacy). This are 39
        bits, but bits [38:31] are used to choose which
        PEMX_REG_NORMX_ACC. As described in the setup
        of PEMX_REG_NORMX_ACC, we use 6 of these bits for address
        extension */
    BDK_CSR_INIT(const_acc, node, BDK_PEMX_CONST_ACC(pcie_port));
    int region_bits = bdk_pop(const_acc.s.num_norm - 1);
    int addr_extension = region_bits - 2; /* Two bits used for type of access */
    int total_bits = addr_extension + const_acc.s.bits_norm;
    return 1ull << total_bits;
}

/**
 * Initialize the RC config space CSRs
 *
 * @param pcie_port PCIe port to initialize
 */
static void __bdk_pcie_rc_initialize_config_space(bdk_node_t node, int pcie_port)
{
    /* T96 different retry timer, uses a ref clock basis */
    /* Allow for 300 milliseconds */

    /* However, there is an issue in T96 if using BOTH the retry timer */
    /* value and SW does retries on CFG_READS, this is not recommended */
    /* A better way is to program the retry value to 0, and let SW do */
    /* retries on reads, when data is 0xFFFFFFFF */
    /* This is from Brendan/Pam on cfg reads.  There are some additional*/
    /* experiments necessary to isolate the exact cause of hang. There */
    /* are about 5 boards that exhibit a hang when waiting for CFG READ */
    /* data after link up.   By setting the CFG_RTY value to 0, only the*/
    /* SW will be issue retry's on the read  (CFG_RETRY) */
    /* See the cfg_read32_retry function */

    /*  This is number of milliseconds based on 656 usec per bit value */
    /*
    int cfg_retry = (300 * 1000) / 656;

    BDK_CSR_MODIFY(c, node, BDK_PEMX_CTL_STATUS2(pcie_port),
        c.s.cfg_rtry = cfg_retry);
 */

    /* Max Payload Size (PCIE*_CFG030[MPS]) */
    /* Max Read Request Size (PCIE*_CFG030[MRRS]) */
    /* Relaxed-order, no-snoop enables (PCIE*_CFG030[RO_EN,NS_EN] */
    /* Error Message Enables (PCIE*_CFG030[CE_EN,NFE_EN,FE_EN,UR_EN]) */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_DEV_CTL(pcie_port),
        c.s.mps = 0; /* Support 128 byte MPS */
        c.s.mrrs = 0x5; /* Support 4KB MRRS */
        c.s.ro_en = 1; /* Enable relaxed order processing. This will allow devices to affect read response ordering */
        c.s.ns_en = 1; /* Enable no snoop processing. Not used */
        c.s.ce_en = 1; /* Correctable error reporting enable. */
        c.s.nfe_en = 1; /* Non-fatal error reporting enable. */
        c.s.fe_en = 1; /* Fatal error reporting enable. */
        c.s.ur_en = 1); /* Unsupported request reporting enable. */

    /* Configure the PCIe slot number if specified */
    int slot_num = bdk_config_get_int(BDK_CONFIG_PCIE_PHYSICAL_SLOT, node, pcie_port);
    if (slot_num != -1)
    {
        BDK_CSR_MODIFY(c, node, BDK_PCIERCX_E_CAP_LIST(pcie_port),
            c.s.si = 1); /* Slot Implemented*/
        BDK_CSR_MODIFY(c, node, BDK_PCIERCX_SLOT_CAP(pcie_port),
            c.s.ps_num = slot_num);
    }

    /* Disable ECRC Generation as not all card support it. The OS can enable it
       later if desired (PCIE*_CFG070[GE,CE]) */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_ADV_ERR_CAP_CNTRL(pcie_port),
        c.s.ge = 0; /* ECRC generation disable. */
        c.s.ce = 0); /* ECRC check disable. */

    /* Access Enables (PCIE*_CFG001[MSAE,ME]) */
        /* ME and MSAE should always be set. */
    /* Interrupt Disable (PCIE*_CFG001[I_DIS]) */
    /* System Error Message Enable (PCIE*_CFG001[SEE]) */
        BDK_CSR_MODIFY(c, node, BDK_PCIERCX_CMD(pcie_port),
        c.s.msae = 1; /* Memory space enable. */
        c.s.me = 1; /* Bus master enable. */
        c.s.i_dis = 1; /* INTx assertion disable. */
        c.s.see = 1); /* SERR# enable */

    /* Advanced Error Recovery Message Enables */
    /* (PCIE*_CFG066,PCIE*_CFG067,PCIE*_CFG069) */
    BDK_CSR_WRITE(node, BDK_PCIERCX_UCOR_ERR_MSK(pcie_port), 0);
    /* Use BDK_PCIERCX_CFG067 hardware default */
    BDK_CSR_WRITE(node, BDK_PCIERCX_COR_ERR_MSK(pcie_port), 0);

    /* Active State Power Management (PCIE*_CFG032[ASLPC]) */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_LINK_CTL(pcie_port),
        c.s.aslpc = 0); /* Active state Link PM control. */

    /* Link Width Mode (PCIERCn_CFG452[LME]) - Set during bdk_pcie_rc_initialize_link() */
    /* Primary Bus Number (PCIERCn_CFG006[PBNUM]) */
    int bus = 1;
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_BNUM(pcie_port),
        c.s.pbnum = 0;
        c.s.sbnum = bus;
        c.s.subbnum = 255);

    /* Memory-mapped I/O BAR (PCIERCn_CFG008) */
    uint64_t mem_base = bdk_pcie_get_base_address(node, pcie_port, BDK_PCIE_MEM_NORMAL);
    uint64_t mem_limit = mem_base + bdk_pcie_get_base_size(node, pcie_port, BDK_PCIE_MEM_NORMAL) - 1;
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_MEM(pcie_port),
        c.s.mb_addr = mem_base >> 16;
        c.s.ml_addr = mem_limit >> 16);

    /* Prefetchable BAR (PCIERCn_CFG009,PCIERCn_CFG010,PCIERCn_CFG011) */
    uint64_t prefetch_base = bdk_pcie_get_base_address(node, pcie_port, BDK_PCIE_MEM_PREFETCH);
    uint64_t prefetch_limit = prefetch_base + bdk_pcie_get_base_size(node, pcie_port, BDK_PCIE_MEM_PREFETCH) - 1;
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_PMEM(pcie_port),
        c.s.lmem_base = prefetch_base >> 16;
        c.s.lmem_limit = prefetch_limit >> 16);
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_PRE_BASE(pcie_port),
        c.s.umem_base = prefetch_base >> 32);
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_PRE_LIMIT(pcie_port),
        c.s.umem_limit = prefetch_limit >> 32);

    /* System Error Interrupt Enables (PCIERCn_CFG035[SECEE,SEFEE,SENFEE]) */
    /* PME Interrupt Enables (PCIERCn_CFG035[PMEIE]) */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_ROOT_CTL_CAP(pcie_port),
        c.s.secee = 1; /* System error on correctable error enable. */
        c.s.sefee = 1; /* System error on fatal error enable. */
        c.s.senfee = 1; /* System error on non-fatal error enable. */
        c.s.pmeie = 1); /* PME interrupt enable. */

    /* Advanced Error Recovery Interrupt Enables */
    /* (PCIERCn_CFG075[CERE,NFERE,FERE]) */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_ROOT_ERR_CMD(pcie_port),
        c.s.cere = 1; /* Correctable error reporting enable. */
        c.s.nfere = 1; /* Non-fatal error reporting enable. */
        c.s.fere = 1); /* Fatal error reporting enable. */

    /* Get the QLM mode to we know our max width and speed */
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    int qlm_lanes = bdk_qlm_get_lanes(node, qlm);
    int qlm_mode = bdk_qlm_get_mode(node, qlm, 0);
    int qlm_speed = bdk_qlm_get_gbaud_mhz(node, qlm, 0);

    BDK_CSR_INIT(port_ctl, node, BDK_PCIERCX_PORT_CTL(pcie_port));
    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int lme = port_ctl.s.lme;
    int mlw = link_cap.s.mlw;
    int mls;

    if (qlm_speed >= 16000)
        mls = 4;
    else if (qlm_speed >= 8000)
        mls = 3;
    else if (qlm_speed >= 5000)
        mls = 2;
    else
        mls = 1;

    /* Allow override of hardware max link width */
    int max_width = bdk_config_get_int(BDK_CONFIG_PCIE_WIDTH, node, pcie_port);
    if (max_width == -1)
        max_width = 1 << (qlm_mode - BDK_QLM_MODE_PCIE_X1);

    /* Because of Lane Swizzling, the Link Mode Enables need to be set to the
       minimum QLM width, which is 2 for DLM and 4 for QLM. This fixes the
       issue of device tree setting the width to 1 or 2. In addition to LME
       change here, the pipe width in PEMX_CFG also set */

    /* MLW encoding: 0x1=1 lane, 0x2=2 lanes, 0x4=4 lanes, 0x8=8 lanes,  0x10=16 lanes */
    /* LME encoding: 0x1=x1, 0x3=2 lanes, 0x7=4, 0xF=8, 0x1F=16, 0x3F=32 (not supported) */

    switch (max_width)
    {
        /* LME Special case set to QLM width because lane swizzle */
        case 1:
            lme = (qlm_lanes == 2) ? 0x3 : 0x7;
            mlw = 1;
            break;
        /* LME Special case set to QLM width because lane swizzle */
        case 2:
            lme = (qlm_lanes == 2) ? 0x3 : 0x7;
            mlw = 2;
            break;
        case 4:
            lme = 7;
            mlw = 4;
            break;
        case 8:
            lme = 0xf;
            mlw = 8;
            break;
        case 16:
            lme = 0x1f;
            mlw = 16;
            break;
        default:
            /* No change */
            break;
    }

    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(pcie_port));

    BDK_TRACE(PCIE, "N%d.PCIe%d: PEM_CFG.LANES= %d LME=0x%x MLW= 0x%x\n",
        node, pcie_port, pemx_cfg.cn9.lanes, lme, mlw);

    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_PORT_CTL(pcie_port),
        c.s.lme = lme);
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_LINK_CAP(pcie_port),
        c.s.mls = mls;
        c.s.mlw = mlw);
    /* Set the target link speed */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_LINK_CTL2(pcie_port),
        c.s.tls = __bdk_is_needed_gsern_pcie_errata_36412_workaround() ? 1 : mls);

    /* Allow user to change PCIERCX_GEN3_EQ_CTL.PRV */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_GEN3_EQ_CTL(pcie_port),
        c.s.prv = bdk_config_get_int(BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR, node, pcie_port));

    /* GEN4 uses the same register, but PHY_GEN3_CTL.RSS must be set to select shadow */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_PHY_GEN3_CTL(pcie_port),
         c.s.rss = 1);

    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_GEN3_EQ_CTL(pcie_port),
        c.s.prv = bdk_config_get_int(BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR, node, pcie_port));

    /* Restore RSS back to 0 when done with GEN4 PRV value */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_PHY_GEN3_CTL(pcie_port),
         c.s.rss = 0);

    /* Change PCIERCX_LNK_CTL2.SDE for PCIe Gen2 deemphasis control*/
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_LINK_CTL2(pcie_port),
        c.s.sde = bdk_config_get_int(BDK_CONFIG_PCIE_GEN2_DEEMPHASIS, node, pcie_port));

    /* Enable Egress Atomic Operations */
    /* This is fetch add,CAS and Swap */
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_DEV_CTL2(pcie_port),
        c.s.atom_op = 1;
        c.s.atom_op_eb = 0);
}

/**
 * Get the PCIe LTSSM state for the given port. The LTSSM is accessed from
 * the PEM diagnostic status register. This is 9X specific code.
 *
 * @param node      Node to query
 * @param pcie_port PEM to query
 *
 * @return LTSSM state
 */
static int __bdk_pcie_rc_get_ltssm_state(bdk_node_t node, int pcie_port)
{
    BDK_CSR_INIT(diag_status, node, BDK_PEMX_DIAG_STATUS(pcie_port));
    return diag_status.cn9.ltssm;
}

/**
 * Get the PCIe LTSSM state for the given port
 *
 * @param node      Node to query
 * @param pcie_port PEM to query
 *
 * @return LTSSM state
 */
static const char *ltssm_string(int ltssm)
{
    switch (ltssm)
    {
        case 0x00: return "DETECT_QUIET";
        case 0x01: return "DETECT_ACT";
        case 0x02: return "POLL_ACTIVE";
        case 0x03: return "POLL_COMPLIANCE";
        case 0x04: return "POLL_CONFIG";
        case 0x05: return "PRE_DETECT_QUIET";
        case 0x06: return "DETECT_WAIT";
        case 0x07: return "CFG_LINKWD_START";
        case 0x08: return "CFG_LINKWD_ACEPT";
        case 0x09: return "CFG_LANENUM_WAIT";
        case 0x0A: return "CFG_LANENUM_ACEPT";
        case 0x0B: return "CFG_COMPLETE";
        case 0x0C: return "CFG_IDLE";
        case 0x0D: return "RCVRY_LOCK";
        case 0x0E: return "RCVRY_SPEED";
        case 0x0F: return "RCVRY_RCVRCFG";
        case 0x10: return "RCVRY_IDLE";
        case 0x11: return "L0";
        case 0x12: return "L0S";
        case 0x13: return "L123_SEND_EIDLE";
        case 0x14: return "L1_IDLE";
        case 0x15: return "L2_IDLE";
        case 0x16: return "L2_WAKE";
        case 0x17: return "DISABLED_ENTRY";
        case 0x18: return "DISABLED_IDLE";
        case 0x19: return "DISABLED";
        case 0x1A: return "LPBK_ENTRY";
        case 0x1B: return "LPBK_ACTIVE";
        case 0x1C: return "LPBK_EXIT";
        case 0x1D: return "LPBK_EXIT_TIMEOUT";
        case 0x1E: return "HOT_RESET_ENTRY";
        case 0x1F: return "HOT_RESET";
        case 0x20: return "RCVRY_EQ0";
        case 0x21: return "RCVRY_EQ1";
        case 0x22: return "RCVRY_EQ2";
        case 0x23: return "RCVRY_EQ3";
        default:   return "Unknown";
    }
}

/**
 * During PCIe link initialization we need to make config request to the attached
 * device to verify its speed and width. These config access happen very early
 * after the device is taken out of reset, so may fail for some amount of time.
 * This function automatically retries these config accesses. The normal builtin
 * hardware retry isn't enough for this very early access.
 *
 * @param node      Note to read from
 * @param pcie_port PCIe port to read from
 * @param bus       PCIe bus number
 * @param dev       PCIe device
 * @param func      PCIe function on the device
 * @param reg       Register to read
 *
 * @return Config register value, or all ones on failure
 */
static uint32_t cfg_read32_retry(bdk_node_t node, int pcie_port, int bus, int dev, int func, int reg)
{
    /* Read the PCI config register until we get a valid value. Some cards
       require time after link up to return data. Wait at most 3 seconds */
    uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) * 3;
    uint32_t val;
    do
    {
        /* Read PCI capability pointer */
        val = bdk_pcie_config_read32(node, pcie_port, bus, dev, func, reg);
        /* Check the read succeeded */
        if (val != 0xffffffff)
            return val;
        /* Failed, wait a little and try again */
        bdk_wait_usec(10000);
    } while (bdk_clock_get_count(BDK_CLOCK_TIME) < timeout);

    BDK_TRACE(PCIE, "N%d.PCIe%d: Config read failed, can't communicate with device\n",
        node, pcie_port);
    return 0xffffffff;
}


/**
 * Override GEN2 Tap Values. This is a temporary module to prove taps
 * overwritten Not sure if these values get written when only forcing
 * GEN2 values I would set if our max speed is GEN2
 *
 * ERRATA: 36412 GSER IDLE GLITCH
 *
 * @param node
 * @param pcie_port PCIe port to initialize
 * @param preset_mode GEN1,GEN2, or GEN3 P0 thru P11 indec
 *
 * @return
 */
static void __bdk_gsern_pcie_rc_gen2_preset_override(bdk_node_t node, int pcie_port,int preset_mode)
{
    static char *text[] = {
        "PRESET_0/GEN2-6DB",
        "PRESET_1/GEN1/GEN2-3.5DB",
        "PRESET_2",
        "PRESET_3",
        "PRESET_4",
        "PRESET_5",
        "PRESET_6",
        "PRESET_7",
        "PRESET_8",
        "PRESET_9",
        "PRESET_10"
    };

    /* Assumption Here is that the PEM is out of reset */
    /* Which may not always be true */
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);

    if (qlm < 0)
        return;

    /* Determine which table to use (based on preset for gen1,2,3 or 4 */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Errata 36412 Override Preset Mode %d(%s)\n",
        node, pcie_port,preset_mode,text[preset_mode]);

    const tx_tap_drv_override_t *tbl_ptr = &tx_tap_drv_override_gen123[preset_mode];

    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int pcie_lanes = link_cap.s.mlw;
    while (pcie_lanes > 0)
    {
         /* Preset table includes GEN1,GEN2, so add 2 to get correct table index */

         /* NOTE: Do not set the en_tx_bs values in this register, set them      */
         /* In the GSERNX_LANEX_PCIE_TXBIAS_BCFG                                 */
         /* We only want to override the de-emphasis values                      */
         BDK_CSR_MODIFY(c,node,BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm,4),
           c.s.muxpost   = tbl_ptr->muxpost;
           c.s.cpostb    = tbl_ptr->cpostb;
           c.s.cposta    = tbl_ptr->cposta;
           c.s.enpost    = tbl_ptr->enpost;
           c.s.muxmain   = tbl_ptr->muxmain;
           c.s.cmaind    = tbl_ptr->cmaind;
           c.s.enmain    = tbl_ptr->enmain;
           c.s.muxpre    = tbl_ptr->muxpre;
           c.s.cpreb     = tbl_ptr->cpreb;
           c.s.cprea     = tbl_ptr->cprea;
           c.s.enpre     = tbl_ptr->enpre;
           c.s.en_tx_drv = 1);
         BDK_CSR_READ(node, BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm,0));

         int qlm_lanes = bdk_qlm_get_lanes(node, qlm);
         pcie_lanes -= qlm_lanes;
         qlm++;
    }
}


/**
 * Turn off the transmitter override so that the receiver rx detect can work again.
 * This is necessary BEFORE the link is enabled, since the overrides block transmitter
 * requests from the MAC.
 *
 * ERRATA: 36412 GSER IDLE GLITCH
 *
 * @param node
 * @param pcie_port PCIe port to initialize
 *
 * @return
 */
static void __bdk_gsern_pcie_rc_gen2_preset_override_off(bdk_node_t node, int pcie_port)
{
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int pcie_lanes = link_cap.s.mlw;
    while (pcie_lanes > 0)
    {
        BDK_TRACE(PCIE, "N%d.PCIe%d: QLM%d GEN2 Override Transmit Override Off\n",
            node, pcie_port, qlm);
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm, 4),
            c.s.en_tx_drv = 0x0);
        int qlm_lanes = bdk_qlm_get_lanes(node, qlm);
        pcie_lanes -= qlm_lanes;
        qlm++;
    }
}

/**
 * Set the rx detect trigger on serdes lane. This is a single shot write to
 * initiate a rx detect pulse. This is errata 36412 issue, when we want to issue a
 * single rx detect pulse, write the trigger.  The rx detect logic, already
 * programmed, will indicate reflection of the pulse in the serdes transmitter
 * status registers, which are checked in separate function.
 *
 * @param node
 * @param pcie_port PCIe port to issue trigger
 *
 * @return 0 if valid qlm
 */
static int __bdk_gsern_pcie_rc_check_rx_detect_trigger(bdk_node_t node, int pcie_port)
{
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    if (qlm < 0)
        return -1;

    /* This is typically 1, 2, 4, 8, or 16 */
    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int pcie_lanes = link_cap.s.mlw;


    /* These are RO bits and can change. Once the link comes up, it appears that these bits go to 0 */
    int qlm_lane = 0;
    int qlm_lanes = bdk_qlm_get_lanes(node, qlm);

    /* Always need to check at least the width of the QLM */
    /* Because of the lane swizzle */
    /* QLM_LANES will always be 2 or 4 */
    /* PCIE Lanes will always be 1,2,4,8 or 16 */
    int lanes_to_check = (pcie_lanes < qlm_lanes)  ? qlm_lanes : pcie_lanes;

    BDK_TRACE(PCIE, "N%d.PCIe%d: Trigger Rx Detect Trigger PCIE Lanes %d Serdes Lanes %d\n",
        node, pcie_port, pcie_lanes, lanes_to_check);

    for (int lane = 0; lane < lanes_to_check; lane++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, qlm_lane),
            c.s.trigger = 0x1);
        BDK_CSR_READ(node, BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, qlm_lane));

        qlm_lane++;
        if (qlm_lane >= qlm_lanes)
        {
            qlm++;
            qlm_lane = 0;
            qlm_lanes = bdk_qlm_get_lanes(node, qlm);
        }
    }

    return 0;
}

/**
 * Check for Rx Detect Status Completion. THis is related to errata 36412. After a
 * trigger pulse is sent, read the serdes tx status register for detection
 * completion and detection.
 *
 * Added a mechanism to force a "valid lane" in the device tree. If a port override
 * is enabled, then the valid lane indicator is set. This is for some
 * modules which we want to override.
 *
 * @param node
 * @param pcie_port PCIe port to check
 *
 * @return Return a mask where each bit set is a valid lane
 */
static uint64_t __bdk_gsern_pcie_rc_check_rx_detect_check(bdk_node_t node, int pcie_port)
{
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    if (qlm < 0)
        return 0;

    /* Check for forcing an rx detect on a lane(s) */
    /* If this is set to 1 in device tree, then all */
    /* lanes for that port width are enabled */
    int force_rx_detect_override = bdk_config_get_int(BDK_CONFIG_PCIE_RC_OVERRIDE_DETECT, node, pcie_port);

    /* This is typically 1, 2, 4, 8, or 16 */
    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int pcie_lanes = link_cap.s.mlw;

    uint64_t valid_lanes = 0;

    /* These are RO bits and can change. Once the link comes up, it appears that these bits go to 0 */
    int qlm_lane = 0;
    int qlm_lanes = bdk_qlm_get_lanes(node, qlm);

    /* Always need to check at least the width of the QLM */
    /* Because of the lane swizzle */
    /* QLM_LANES will always be 2 or 4 */
    /* PCIE Lanes will always be 1,2,4,8 or 16 */
    int lanes_to_check = (pcie_lanes < qlm_lanes) ? qlm_lanes : pcie_lanes;

    BDK_TRACE(PCIE, "N%d.PCIe%d: Check Rx Detect Trigger PCIE Lanes %d Serdes Lanes %d\n",
        node, pcie_port, pcie_lanes, lanes_to_check);

    for (int lane = 0; lane < lanes_to_check; lane++)
    {
        BDK_CSR_INIT(rx_detect_status, node, BDK_GSERNX_LANEX_TX_BSTS(qlm, qlm_lane));
        BDK_TRACE(PCIE, "N%d.PCIe%d: QLM %d Lane %d Rx Detect Complete=%1d DETP=%1d DETN=%1d\n",
            node, pcie_port, qlm, qlm_lane,
            rx_detect_status.s.rxdetcomplete,
            rx_detect_status.s.rxdetp,
            rx_detect_status.s.rxdetn);

        /* Record valid lanes, make sure detect complete */
        bool valid = rx_detect_status.s.rxdetcomplete &
            (rx_detect_status.s.rxdetp | rx_detect_status.s.rxdetn);

        /* If detect on any lane, record it */
        if (valid || force_rx_detect_override)
            valid_lanes |= 1ull << lane;

        qlm_lane++;
        if (qlm_lane >= qlm_lanes)
        {
            qlm++;
            qlm_lane = 0;
            qlm_lanes = bdk_qlm_get_lanes(node, qlm);
        }
    }

    return valid_lanes;
}

/**
 * Override the rx detect for the number of lanes specified. This overrides the
 * rx detect for the lanes specified in valid so that the MAC will enable link
 * training with that lane.
 *
 * @param node
 * @param pcie_port PCIe port to override rx detect
 * @param valid_lanes
 *                  Bit mask of valid PCIe lanes
 *
 * @return
 */
static int __bdk_gsern_pcie_rc_initialize_override_rx_detect(bdk_node_t node, int pcie_port, uint64_t valid_lanes)
{
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    if (qlm < 0)
        return -1;

    /* This is typically 1, 2, 4, 8, or 16 */
    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int pcie_lanes = link_cap.s.mlw;

    /* We want to set the detect "ON" for the lanes specified */
    /* lane valid bits already set */
    int qlm_lane = 0;
    int qlm_lanes = bdk_qlm_get_lanes(node, qlm);

    /* Always need to check at least the width of the QLM */
    /* Because of the lane swizzle */
    /* QLM_LANES will always be 2 or 4 */
    /* PCIE Lanes will always be 1,2,4,8 or 16 */
    int lanes_to_check = (pcie_lanes < qlm_lanes) ? qlm_lanes : pcie_lanes;

    BDK_TRACE(PCIE, "N%d.PCIe%d: Override Rx Detect Trigger PCIE Lanes %d Serdes Lanes %d\n",
        node, pcie_port, pcie_lanes, lanes_to_check);

    for (int lane = 0; lane < lanes_to_check; lane++)
    {
        if (valid_lanes & (1ull << lane))
        {
            BDK_TRACE(PCIE, "N%d.PCIe%d: Qlm %d Lane %d Force Rx Detect\n",
                node, pcie_port, qlm, qlm_lane);
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, qlm_lane),
                c.s.ovrride_det = 1;
                c.s.ovrride_det_en = 1);
            BDK_CSR_READ(node, BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, qlm_lane));
        }

        qlm_lane++;
        if (qlm_lane >= qlm_lanes)
        {
            qlm++;
            qlm_lane = 0;
            qlm_lanes = bdk_qlm_get_lanes(node, qlm);
        }
    }
    return 0;
}

/**
 * 1) Apply workaround for TSI 721 part. This is an PCIe to SRIO Bridge part. There
 *    is an errata on the part to clear bit ISSC bit in phy link configuration register
 *    offset 0x530 to 0. This workaround clears bit 14, which allows the device to
 *    make a speed change to GEN2.
 *
 * 2) Disable electrical idle detect on IDT part when, so that Inferred electrical
 *    idle is performed during the speed change.
 *
 * @param node      Node the PEM is on
 * @param pcie_port PCIe port to check
 * @param bus       secondary bus that device on
 * @param dev       secondary device that device on
 * @param func      secondary function that device on
 */
static void __bdk_tsi_721_errata_gen2(bdk_node_t node, int pcie_port, int bus, int dev, int func)
{
    #define TSI_721_ERRATA_SERDES_CONFIG_OFFSET          0x510
    #define TSI_721_ERRATA_PHY_LINK_CFG_ISSC_OFFSET      0x530
    #define TSI_721_ERRATA_PHY_LINK_CFG_ISSC_BIT         (1<<14)
    #define TSI_721_ERRATA_SERDES_CONFIG_EID_DISABLE     (1<<9)

    /* Read offset 0x530 (Phy Link Configuration 0 Register) */
    uint32_t data = cfg_read32_retry(node, pcie_port, bus, dev, func, TSI_721_ERRATA_PHY_LINK_CFG_ISSC_OFFSET);

    /* Clear Bit 14 to allow GEN2 speed change */
    data &= ~TSI_721_ERRATA_PHY_LINK_CFG_ISSC_BIT;
    bdk_pcie_config_write32(node, pcie_port, bus, dev, func, TSI_721_ERRATA_PHY_LINK_CFG_ISSC_OFFSET,data);

    /* If pass 1 T96: electrical idle disable on SRIO part */
    if (__bdk_is_needed_gsern_pcie_errata_36412_workaround())
    {
        /* Read offset 0x510 (Serdes Configuration Register) */
        data = cfg_read32_retry(node, pcie_port, bus, dev, func, TSI_721_ERRATA_SERDES_CONFIG_OFFSET);

        /* Disable electrical SRIO IDLE detect for T96 Pass 1 */
        data |= TSI_721_ERRATA_SERDES_CONFIG_EID_DISABLE;
        bdk_pcie_config_write32(node, pcie_port, bus, dev, func, TSI_721_ERRATA_SERDES_CONFIG_OFFSET, data);
    }
}

/**
 * This is checking for device errata the may be required on some device
 * that do not play nicely with the T96. This is used for the following devices:
 *
 *      SRIO Bridge Device Vendor Id = 0x80ab111d
 *          - Disable Electrical Idle Detect so Board links GEN2
 *          - Enable GEN2 speed change.
 *
 * @param node      Node the PEM is on
 * @param pcie_port PCIe port to check
 * @param bus       secondary bus that device on
 * @param dev_vendor_id
 *                  device vendor id
 */
static void __bdk_9xxx_pcie_device_errata_check(bdk_node_t node, int pcie_port, int bus, uint32_t dev_vendor_id)
{
    const int dev = 0;
    const int func = 0;
    const uint32_t DEVICE_VENDOR_ID_TSI_721 = 0x80ab111d;

    if (dev_vendor_id == DEVICE_VENDOR_ID_TSI_721)
    {
        BDK_TRACE(PCIE, "N%d.PCIe%d: TSI721 Errata For GEN2\n", node, pcie_port);
        __bdk_tsi_721_errata_gen2(node, pcie_port, bus, dev, func);
    }
}

/**
 * Initialize a host mode PCIe link. This function assumes the PEM has already
 * been taken out of reset and configure. It brings up the link and checks that
 * the negotiated speed and width is correct for the configured PEM and the
 * device plugged into it. Note that the return code will signal a retry needed
 * for some link failures. The caller is responsible for PEM reset and retry.
 *
 * @param node      Node the PEM is on
 * @param pcie_port PCIe port to initialize link on
 *
 * @return Zero on success
 *         Negative on failures where retries are not needed
 *         Positive if a retry is needed to fix a failure
 */
static int __bdk_pcie_rc_initialize_link(bdk_node_t node, int pcie_port, int *neg_gen)
{
    int tx_tap_override_preset_vector = bdk_config_get_int(BDK_CONFIG_PCIE_TX_PRESET_OVERRIDE_VECTOR, node, pcie_port);
    int gen2_deemphasis = bdk_config_get_int(BDK_CONFIG_PCIE_GEN2_DEEMPHASIS, node, pcie_port);
    int force_rx_detect_override = bdk_config_get_int(BDK_CONFIG_PCIE_RC_OVERRIDE_DETECT, node, pcie_port);

    /* Number of LTSSM transitions to record, must be a power of 2 */
    #define LTSSM_HISTORY_SIZE 64
    uint8_t ltssm_history[LTSSM_HISTORY_SIZE];
    int ltssm_history_loc;
    bool do_retry_speed = false;
    int gen3_tx_preset_value = DEFAULT_TX_PRESET_TAP_OVERRIDE_VALUE;
    int gen3_tx_starting_preset = 0;
    int gen3_found_preset_to_use;

    /* Simulation doesn't support PCIe host */
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    /* Turn off any transmitter overrides, This is so that receiver
       detect works before we override. Errata 36412: GSER IDLE Glitch */
    if (__bdk_is_needed_gsern_pcie_errata_36412_workaround())
        __bdk_gsern_pcie_rc_gen2_preset_override_off(node, pcie_port);

    /* 02-22-2019 */
    /* Force Rx Detect RC mode */
    /* Errata 36412 */
    /* This is simply allowing override to be applied sooner */
    /* We still need to train to GEN1, so that we can adjust the */
    /* equalization, since that is necessary with this workaround */

    /* Check for forcing an rx detect on a lane(s), this is for PCIe modules that are */
    /* not compliant, and we want to force rx detect. This has to be executed for any */
    /* case, with or without the errata.   Specifically, the Titan module which does */
    /* detect properly. */

    if ((TX_OVERRIDE_FORCE_RX_DETECT && __bdk_is_needed_gsern_pcie_errata_36412_workaround())
        || force_rx_detect_override)
    {
        BDK_TRACE(PCIE, "N%d.PCIe%d: Force RC Rx Detect\n", node,pcie_port);

        /* Repeat the detect for up to 100 ms */
        /* Allow sufficient time for the remote target termination */
        /* We should detect something rather quickly if card plugged in */
        uint64_t valid_lanes = 0;
        int timeout = 10;
        do
        {
            /* Force Rx Detect Cycle */
            __bdk_gsern_pcie_rc_check_rx_detect_trigger(node, pcie_port);

            /* Find Out Which Lanes Available */
            valid_lanes = __bdk_gsern_pcie_rc_check_rx_detect_check(node, pcie_port);

            /* If nothing detected, wait 10 milliseconds and try again */
            if (!valid_lanes)
                    bdk_wait_usec(10000);

        } while (--timeout && !valid_lanes);

        /* If we detected a device, then enable rx detect override for lanes */
        /* These are the lanes that will be enabled so the MAC links up */
        /* If the detect fails on this QLM, nothing is plugged in */
        if (valid_lanes)
        {
            /* Enabled Rx Detect Override on Detected Lanes */
            __bdk_gsern_pcie_rc_initialize_override_rx_detect(node, pcie_port, valid_lanes);

            /* Now apply Tx Tap Override to eliminate glitch, before link enabled */
            /* This is critical that this be done before link enabled, otherwise */
            /* Will not stand a chance of link coming up at GEN1, because eye closed*/
            /* We are doing software controlled rx receiver detect operation */
            __bdk_gsern_pcie_rc_gen2_preset_override(node, pcie_port, TAP_OVERRIDE_PRESET_1_GEN1_GEN2_35DB);
        }
        else
        {
            BDK_TRACE(PCIE, "N%d.PCIe%d: No Programmed Receive Detect\n", node, pcie_port);
            /* If the software rx detect fails, always falls back on Hw detect */
            /* But we risk the effect of errata 36412 glitch until tap override */
        }
    }

    /* Determine the maximum link speed and width */
    BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));
    int max_gen = link_cap.s.mls; /* Max speed of PEM from config (1-3) */
    int max_width = link_cap.s.mlw; /* Max lane width of PEM (1-8) */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Link supports up to %d lanes, speed gen%d\n",
        node, pcie_port, max_width, max_gen);

    /* Record starting LTSSM state for debug */
    memset(ltssm_history, -1, sizeof(ltssm_history));
    ltssm_history[0] = __bdk_pcie_rc_get_ltssm_state(node, pcie_port);
    ltssm_history_loc = 0;

    /* Bring up the link */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Enabling the link\n", node, pcie_port);
    BDK_CSR_MODIFY(c, node, BDK_PEMX_CTL_STATUS(pcie_port), c.cn9.lnk_enb = 1);

retry_speed:
    /* Clear RC Correctable Error Status Register */
    BDK_CSR_WRITE(node, BDK_PCIERCX_COR_ERR_STAT(pcie_port), -1);

    /* Wait for the link to come up and link training to be complete */
    uint64_t clock_rate = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    uint64_t hold_time = clock_rate / 5; /* 200ms */
    uint64_t bounce_allow_time = clock_rate / 100; /* 10ms */
    uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + clock_rate; /* Timeout = 1s */
    uint64_t good_time = 0; /* Records when the link first went good */
    BDK_CSR_DEFINE(link_ctl, BDK_PCIERCX_LINK_CTL(pcie_port));
    bool link_up;
    bool is_loop_done;

    do
    {
        /* Record LTSSM state for debug */
        int ltssm_state = __bdk_pcie_rc_get_ltssm_state(node, pcie_port);
        if (ltssm_history[ltssm_history_loc] != ltssm_state)
        {
            ltssm_history_loc = (ltssm_history_loc + 1) & (LTSSM_HISTORY_SIZE - 1);
            ltssm_history[ltssm_history_loc] = ltssm_state;
        }
        /* Read link state */
        link_ctl.u = BDK_CSR_READ(node, BDK_PCIERCX_LINK_CTL(pcie_port));

        /* Check if the link is up */
        uint64_t current_time = bdk_clock_get_count(BDK_CLOCK_TIME);
        link_up = (link_ctl.s.dlla && !link_ctl.s.lt);

        if (link_up)
        {
            /* Is this the first link up? */
            if (!good_time)
            {
                /* Mark the time when the link transitioned to good */
                good_time = current_time;

                /* If the link is up immediately select GEN1 */
                /* So we don't get errors during link training */
                /* We will change it later */
                /* We don't want 100 ms of glitch stuff */
                /* Which will cause errors */
                if (__bdk_is_needed_gsern_pcie_errata_36412_workaround() && !do_retry_speed && !TX_OVERRIDE_FORCE_RX_DETECT)
                {
                    BDK_TRACE(PCIE, "N%d.PCIe%d: Errata 3612: Immediate Force GEN1\n", node, pcie_port);
                    __bdk_gsern_pcie_rc_gen2_preset_override(node, pcie_port,TAP_OVERRIDE_PRESET_1_GEN1_GEN2_35DB);
                }
            }
            else
            {
                /* Check for a link error */
                BDK_CSR_INIT(cor_err_stat, node, BDK_PCIERCX_COR_ERR_STAT(pcie_port));
                if (cor_err_stat.s.res)
                {
                    /* Ignore errors before we've been stable for bounce_allow_time */
                    if (good_time + bounce_allow_time <= current_time)
                    {
                        BDK_TRACE(PCIE, "N%d.PCIe%d: Link errors after link up\n", node, pcie_port);
                        return 1; /* Link error, signal a retry */
                    }
                    else
                    {
                        /* Clear RC Correctable Error Status Register */
                        BDK_CSR_WRITE(node, BDK_PCIERCX_COR_ERR_STAT(pcie_port), -1);
                        BDK_TRACE(PCIE, "N%d.PCIe%d: Ignored error during settling time\n", node, pcie_port);
                    }
                }
            }
        }
        else if (good_time)
        {
            if (good_time + bounce_allow_time <= current_time)
            {
                /* Link Bounce condition, check for errata to change presets */
                /* For the errata, we check for different tx presets to use */
                /* and then issue a speed change so that training occurs again */
                /* And we only do this for GEN3/4 for this errata */

                /* As long as we need a speed change */
                /* Try the next value (up to 11 presets */
                /* If it bounces during GEN3/4, try diff preset */
                if (__bdk_is_needed_gsern_pcie_errata_36412_workaround() && (link_ctl.s.ls >= 3))
                {
                    /* Check if we exceeded number of presets. Basically we get a link bounce */
                    /* On every attempt, so we return 1, to force a fundamental reset retry */
                    if (gen3_tx_starting_preset >= GEN3_MAX_TX_PRESETS)
                    {
                        gen3_tx_starting_preset = 0;
                        /* Force a HARD retry */
                        BDK_TRACE(PCIE, "N%d.PCIe%d: GEN3 Link Bounce Tx Presets Exhausted, Hard Retry\n",node,pcie_port);
                        return 1;
                    }

                    /* If the GEN3 link is already up */
                    /* Initial preset already selected */
                    /* We want to try the next value */
                    gen3_tx_preset_value = DEFAULT_TX_PRESET_TAP_OVERRIDE_VALUE;
                    gen3_found_preset_to_use = 0;
                    for (int j = gen3_tx_starting_preset; j < GEN3_MAX_TX_PRESETS; j++)
                    {
                        if ((1 << j) & tx_tap_override_preset_vector)
                        {
                            gen3_tx_preset_value =  j;
                            gen3_found_preset_to_use = 1;
                            BDK_TRACE(PCIE, "N%d.PCIe%d: Link Bounce Gen3 Tx Preset Start= %d Value=%d From Vector = 0x%x\n",
                                node, pcie_port, gen3_tx_starting_preset, gen3_tx_preset_value, tx_tap_override_preset_vector);

                            /* Save position for next preset */
                            gen3_tx_starting_preset = j + 1;
                            break;
                        }
                    }
                    if (!gen3_found_preset_to_use)
                    {
                        BDK_TRACE(PCIE, "N%d.PCIe%d: Link Bounce, Could not Find Preset to Use, retry initialization\n",
                            node, pcie_port);
                        /* If we get here and there is not recovery, then need to force exit , to retry */
                        return 1;
                    }

                    BDK_TRACE(PCIE, "N%d.PCIe%d: Link Bounce Detected, Next Starting Tx Preset %d Preset Value=%d\n",
                        node, pcie_port, gen3_tx_starting_preset, gen3_tx_preset_value);

                    /* The tap override table includes gen1/2 , which is why we add 2 */
                    __bdk_gsern_pcie_rc_gen2_preset_override(node, pcie_port, gen3_tx_preset_value);

                     /* We didn't get the maximum speed. Request a speed change */
                     BDK_TRACE(PCIE, "N%d.PCIe%d: Link Bounce Speed Change Tx Preset Change, Errata 36412\n",
                         node, pcie_port);

                     BDK_CSR_MODIFY(c, node, BDK_PCIERCX_GEN2_PORT(pcie_port),
                         c.s.dsc = 1);

                     bdk_wait_usec(PCIE_SPEED_CHANGE_WAIT_USEC);

                     /* And check the link again */
                     goto retry_speed;
                }
                /* We allow bounces for bounce_allow_time after the link is good.
                    Once this time passes any bounce requires a retry */
                BDK_TRACE(PCIE, "N%d.PCIe%d: Link bounce detected\n", node, pcie_port);

                return 1; /* Link bounce, signal a retry */
            }
            else
            {
                BDK_TRACE(PCIE, "N%d.PCIe%d: Ignored bounce during settling time\n", node, pcie_port);
            }
        }

        /* Determine if we've hit the timeout */
        is_loop_done = (current_time >= timeout);
        /* Determine if we've had a good link for the required hold time */
        is_loop_done |= link_up && (good_time + hold_time <= current_time);

    } while (!is_loop_done);

    /* Trace the LTSSM state */
    BDK_TRACE(PCIE, "N%d.PCIe%d: LTSSM History\n", node, pcie_port);
    for (int i = 0; i < LTSSM_HISTORY_SIZE; i++)
    {
         ltssm_history_loc = (ltssm_history_loc + 1) & (LTSSM_HISTORY_SIZE - 1);
         if (ltssm_history[ltssm_history_loc] != 0xff)
             BDK_TRACE(PCIE, "N%d.PCIe%d:     %s\n",
                 node, pcie_port, ltssm_string(ltssm_history[ltssm_history_loc]));
    }

    if (!link_up)
    {
        int ltssm_state = __bdk_pcie_rc_get_ltssm_state(node, pcie_port);
        BDK_TRACE(PCIE, "N%d.PCIe%d: Link down, Data link layer %s(DLLA=%d), Link training %s(LT=%d), LTSSM %s\n",
            node, pcie_port,
            link_ctl.s.dlla ? "active" : "down", link_ctl.s.dlla,
            link_ctl.s.lt ? "active" : "complete", link_ctl.s.lt,
            ltssm_string(ltssm_state));
        return 1; /* Link down, signal a retry */
    }

    /* Report the negotiated link speed and width */
    *neg_gen = link_ctl.s.ls; /* Current speed of PEM (1-3) */
    int neg_width = link_ctl.s.nlw; /* Current lane width of PEM (1-8) */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Link negotiated %d lanes, speed gen%d\n",
        node, pcie_port, neg_width, *neg_gen);

    /* Determine PCIe bus number the directly attached device uses */
    BDK_CSR_INIT(pciercx_bnum, node, BDK_PCIERCX_BNUM(pcie_port));
    int bus = pciercx_bnum.s.sbnum;

    int dev_gen = 1; /* Device max speed (1-3) */
    int dev_width = 1; /* Device max lane width (1-16) */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Reading device max speed and width\n",
         node, pcie_port);

    /* Read device vendor ID first                      */
    uint32_t dev_vendor_id = cfg_read32_retry(node, pcie_port, bus, 0, 0, 0x00);
    BDK_TRACE(PCIE, "N%d.PCIe%d: Read Device Vendor Id=0x%08x\n", node, pcie_port, dev_vendor_id);

    /* Read PCI capability pointer */
    uint32_t cap = cfg_read32_retry(node, pcie_port, bus, 0, 0, 0x34);

    /* Check if we were able to read capabilities pointer */
    if (cap == 0xffffffff)
        return 1; /* Signal retry needed */

    /* Read device max speed and width */
    int cap_next = cap & 0xff;
    while (cap_next)
    {
        cap = cfg_read32_retry(node, pcie_port, bus, 0, 0, cap_next);
        if (cap == 0xffffffff)
            return 1; /* Signal retry needed */

        /* Is this a PCIe capability (0x10)? */
        if ((cap & 0xff) == 0x10)
        {
            BDK_TRACE(PCIE, "N%d.PCIe%d: Found PCIe capability at offset 0x%x\n",
                node, pcie_port, cap_next);
            /* Offset 0xc contains the max link info */
            cap = cfg_read32_retry(node, pcie_port, bus, 0, 0, cap_next + 0xc);
            if (cap == 0xffffffff)
                return 1; /* Signal retry needed */
            dev_gen = cap & 0xf; /* Max speed of PEM from config (1-3) */
            dev_width = (cap >> 4) & 0x3f; /* Max lane width of PEM (1-16) */
            BDK_TRACE(PCIE, "N%d.PCIe%d: Device supports %d lanes, speed gen%d\n",
                node, pcie_port, dev_width, dev_gen);
            break;
        }
        /* Move to next capability */
        cap_next = (cap >> 8) & 0xff;
    }

    /* Desired link speed and width is either limited by the device or our PEM
       configuration. Choose the most restrictive limit */
    int desired_gen = (dev_gen < max_gen) ? dev_gen : max_gen;
    int desired_width = (dev_width < max_width) ? dev_width : max_width;

    /* We need a change if we don't match the desired speed or width. Note that
       we allow better than expected in case the device lied about its
       capabilities */
    bool need_speed_change = (*neg_gen < desired_gen);
    bool need_lane_change = (neg_width < desired_width);

    /* This is for the case in which we are a GEN1 card, but we want override */
    /* Some of the low leakage parts have a terrible eye */
    bool need_gen1_override = (__bdk_is_needed_gsern_pcie_errata_36412_workaround() &&
            (*neg_gen == 1) && (desired_gen == 1));

    /* This is for the case in which we are a GEN2 card or desired speed=- gen2, such as after retry, but we want override */
    /* Some of the low leakage parts have a terrible eye */
    bool need_gen2_override = (__bdk_is_needed_gsern_pcie_errata_36412_workaround() &&
            (*neg_gen == 2) && (desired_gen == 2));

    /* So this is not a speed change, just an override to improve eye */
    /* We are not retrying, but need to set the DRV bit if we are at best gen */
    /* We dont always get a speed change */
    if (need_gen1_override || need_gen2_override)
    {
        BDK_TRACE(PCIE, "N%d.PCIe%d: Setting Tx Override Errata 36412\n",
            node, pcie_port);

        /* Select GEN1 or GEN2, depending on requested override, fixed GEN1 bug */
        /* Also check for GEN2 de-emphasis request if in device tree            */
        __bdk_gsern_pcie_rc_gen2_preset_override(node, pcie_port,
            need_gen2_override ? (gen2_deemphasis ? TAP_OVERRIDE_PRESET_1_GEN1_GEN2_35DB :
                    TAP_OVERRIDE_PRESET_0_GEN2_6DB ) : TAP_OVERRIDE_PRESET_1_GEN1_GEN2_35DB);
    }

    /* Device Dependent Errata Check, such as SRIO TSI 721 */
    __bdk_9xxx_pcie_device_errata_check(node, pcie_port, bus, dev_vendor_id);

    /* Check if the speed is correct first, followed by width check */
    if (need_speed_change)
    {
        /* If we are trying to override the tx presets, and come up at GEN1
           speed, and the target is GEN2, we will need a speed change, so
           this is where it comes. Only if requested GEN2 from target, do
           we do a speed change */
        if (__bdk_is_needed_gsern_pcie_errata_36412_workaround())
        {
            BDK_TRACE(PCIE, "N%d.PCIe%d: Setting Tx Override For Desired GEN%d\n",
                node, pcie_port, desired_gen);

            /* Change Target Link Speed in Link Ctrl 2 to match device advertised speed */
            BDK_CSR_MODIFY(c, node, BDK_PCIERCX_LINK_CTL2(pcie_port),
                c.s.tls = desired_gen);

            /* This sets the transmit override, which blocks RX detect
               transmitter. This can only be done after link is up, and
               also blocks anything that MAC wants to do, so its very
               specific to GEN2/3/4 only */
            if ((desired_gen == 4) || (desired_gen == 3))
            {
                /* Check if we have tried all speed changes. */
                /* Start at beginning if so. We normally only get a */
                /* a single speed change. */
                /* Unless the speed change fails, in which we come */
                /* theu here and try a different one. similar to a link*/
                /* bounce, but the link may not have bounced */
                /* Again, all of this because of glitch stuff */
                if (gen3_tx_starting_preset >= GEN3_MAX_TX_PRESETS)
                    gen3_tx_starting_preset = 0;

                /* find tx preset to use, there are 11 presets */
                /* Use a different preset on each retry */
                /* If no vector selected in device tree, use 4 */
                /* If we do not get to gen3/3 use different val */
                gen3_tx_preset_value = DEFAULT_TX_PRESET_TAP_OVERRIDE_VALUE;
                gen3_found_preset_to_use = 0;
                for (int j = gen3_tx_starting_preset; j < GEN3_MAX_TX_PRESETS; j++)
                {
                    if ((1 << j) & tx_tap_override_preset_vector)
                    {
                        gen3_tx_preset_value = j;
                        gen3_found_preset_to_use = 1;
                        BDK_TRACE(PCIE, "N%d.PCIe%d: Need Speed Change Gen3 Tx Preset Start= %d Value=%d From Vector = 0x%x\n",
                            node, pcie_port, gen3_tx_starting_preset, gen3_tx_preset_value, tx_tap_override_preset_vector);

                        /* Save position for next preset */
                        gen3_tx_starting_preset = j + 1;
                        break;
                    }
                }

                if (!gen3_found_preset_to_use)
                {
                    BDK_TRACE(PCIE, "N%d.PCIe%d: Speed Change, Could not Find Preset to Use, Use %d\n",
                        node, pcie_port, gen3_tx_preset_value);
                }

                /* The tap override table includes gen1/2 */
                __bdk_gsern_pcie_rc_gen2_preset_override(node, pcie_port, gen3_tx_preset_value);
            }
            else if (desired_gen == 2)
            {
                __bdk_gsern_pcie_rc_gen2_preset_override (node, pcie_port,gen2_deemphasis ? TAP_OVERRIDE_PRESET_1_GEN1_GEN2_35DB :
                        TAP_OVERRIDE_PRESET_0_GEN2_6DB );
            }

        }
        if (do_retry_speed)
        {
            BDK_TRACE(PCIE, "N%d.PCIe%d: Link speed (gen%d) less that supported (gen%d)\n",
                node, pcie_port, *neg_gen, desired_gen);
            return 1; /* Link at width, but speed low. Request a retry */
        }
        else
        {
            /* We didn't get the maximum speed. Request a speed change */
            BDK_TRACE(PCIE, "N%d.PCIe%d: Link speed (gen%d) less that supported (gen%d), requesting a speed change\n",
                node, pcie_port, *neg_gen, desired_gen);

            BDK_CSR_MODIFY(c, node, BDK_PCIERCX_GEN2_PORT(pcie_port),
                c.s.dsc = 1);

            /* Speed change should happen pretty quick, but we need to make sure */
            /* L0 with the speed change */
            /* Issue a wait for serdes speed change, should not take more than 24 ms */
            /* If running a tight LTSSM capture loop, suggest commenting this out */
            /* If we don't wait long enough, we will get a link up, but it may be gen2 */
            /* If there is repeated equalization, it could take longer than 24 ms */
            bdk_wait_usec (PCIE_SPEED_CHANGE_WAIT_USEC);

            do_retry_speed = true;
            goto retry_speed;
        }
    }
    else if (need_lane_change)
    {
        /* We didn't get the maximum number of lanes */
        BDK_TRACE(PCIE, "N%d.PCIe%d: Link width (%d) less that supported (%d)\n",
            node, pcie_port, neg_width, desired_width);
        return 2; /* Link wrong width, signal a retry */
    }
    else
    {
        BDK_TRACE(PCIE, "N%d.PCIe%d: Link at best speed and width\n", node, pcie_port);
        /* For gen3 links check if we are getting errors over the link */
        if (*neg_gen == 3)
        {
            /* Read RC Correctable Error Status Register */
            BDK_CSR_INIT(cor_err_stat, node, BDK_PCIERCX_COR_ERR_STAT(pcie_port));
            if (cor_err_stat.s.res)
            {
                BDK_TRACE(PCIE, "N%d.PCIe%d: Link reporting error status\n", node, pcie_port);
                return 1; /* Getting receiver errors, request a retry */
            }
        }

        /* Dismiss Correctable Errors */
        /* In the device/control/status register */
        BDK_CSR_MODIFY(c, node, BDK_PCIERCX_DEV_CTL(pcie_port),
            c.s.ce_d = 1;
            c.s.nfe_d = 1;
            c.s.fe_d = 1;
            c.s.ur_d = 1);

        /* And the correctable error status register */
        BDK_CSR_MODIFY(c, node, BDK_PCIERCX_COR_ERR_STAT(pcie_port),
            c.s.btlps  = 1;
            c.s.bdllps = 1;
            c.s.rnrs  = 1;
            c.s.rtts = 1;
            c.s.anfes = 1;
            c.s.cies = 1;
            c.s.chlo = 1);

        return 0; /* Link at correct speed and width */
    }
}

/**
 * Setup the PCIe memory mapped address regions to allow access to PCIe by the
 * cores using addresses returned by bdk_pcie_get_base_address().
 *
 * @param node      Node to configure
 * @param pcie_port PCIe port to configure
 */
static void __bdk_pcie_address_initialize(bdk_node_t node, int pcie_port)
{
    BDK_CSR_INIT(const_acc, node, BDK_PEMX_CONST_ACC(pcie_port));
    /* There are PEMX_CONST_ACC[NUM_NORM] regions per address block. We
        need four regions per PCIe port to support config, IO, normal,
        and prefetchable regions. The extra bits in the region number
        are used for address extension */
    int region_bits = bdk_pop(const_acc.s.num_norm - 1);
    int addr_extension = region_bits - 2; /* Two bits used for type of access */
    for (bdk_pcie_mem_t mem_region = BDK_PCIE_MEM_CONFIG; mem_region <= BDK_PCIE_MEM_IO; mem_region++)
    {
        /* Use top two bits for PCIe port, next two bits for memory region */
        int region = mem_region << addr_extension;
        /* Figure out the hardware setting for each region */
        int ctype = 3;
        int nmerge = 1;
        int ordering = 0;
        switch (mem_region)
        {
            case BDK_PCIE_MEM_CONFIG: /* Config space */
                ctype = 1;      /* Config space */
                nmerge = 1;     /* No merging allowed */
                ordering = 0;   /* NO "relaxed ordering" or "no snoop" */
                break;
            case BDK_PCIE_MEM_NORMAL: /* Memory, not prefetchable */
                ctype = 0;      /* Memory space */
                nmerge = 1;     /* No merging allowed */
                ordering = 0;   /* NO "relaxed ordering" or "no snoop" */
                break;
            case BDK_PCIE_MEM_PREFETCH: /* Memory, prefetchable */
                ctype = 0;      /* Memory space */
                nmerge = 1;     /* No merging allowed */
                ordering = 1;   /* Yes "relaxed ordering" and "no snoop" */
                break;
            case BDK_PCIE_MEM_IO: /* IO */
                ctype = 2;      /* I/O space */
                nmerge = 1;     /* No merging allowed */
                ordering = 0;   /* NO "relaxed ordering" or "no snoop" */
                break;
        }
        /* Use the lower order bits to work as an address extension, allowing
           each PCIe port to map a total of TOTAL_BITS bits */
        for (int r = region; r < region + const_acc.s.num_norm / 4; r++)
        {
            uint64_t address = 0;
            /* Address only applies to memory space */
            if (mem_region == BDK_PCIE_MEM_NORMAL)
            {
                /* Normal starts at bus address 0 */
                address = r - region;
            } else if (mem_region == BDK_PCIE_MEM_PREFETCH)
            {
                /* Prefetch starts at bus address PREFETCH_OFFSET. The 31 bit
                   shift is because of the width of the access region. Yes 31
                   bits, not 32 of previous chips */
                address = r - region + (PREFETCH_OFFSET >> 31);
            }
            BDK_CSR_MODIFY(c, node, BDK_PEMX_REG_NORMX_ACC(pcie_port, r),
                c.s.ctype = ctype;
                c.s.zero = 0;
                c.s.wnmerge = nmerge;
                c.s.rnmerge = nmerge;
                c.s.wtype = ordering;
                c.s.rtype = ordering;
                c.s.ba = address);
        }
    }

    /* Setup MAC control */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_NCBI_CTL(pcie_port),
        c.s.wait_com = (bdk_config_get_int(BDK_CONFIG_PCIE_ORDERING) == 1));
}

/**
 * Perform a complete PCIe RC reset. This is documented in the HRM as issuing a
 * fundamental reset
 *
 * @param node      Node to reset
 * @param pcie_port PCIe port to reset
 *
 * @return Zero on success, negative on failure
 */
static int __bdk_pcie_rc_reset(bdk_node_t node, int pcie_port)
{
    /* Find which QLM/DLM is associated with this PCIe port */
    int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
    if (qlm < 0)
        return -1;

    BDK_TRACE(PCIE, "N%d.PCIe%d: Performing PCIe fundamental reset\n", node, pcie_port);

    /* Turn on PEM clocks */
    /* This has to be first */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_CLK_EN(pcie_port),
          c.cn9.pceclk_gate = 0;
          c.cn9.pemc_csclk_gate = 0);
    BDK_CSR_READ(node, BDK_PEMX_CLK_EN(pcie_port));

    /* Host software may want to issue a fundamental reset to the PCIe bus.
       Software should perform the following steps:
       1.  Write PEM(0..1)_ON[PEMON] = 0. */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_ON(pcie_port),
        c.s.pemon = 0);
    BDK_CSR_READ(node, BDK_PEMX_ON(pcie_port));

    /* 2.  Write RST_SOFT_PRST(0..3)[SOFT_PRST] = 1.
        - This reassertion of [SOFT_PRST] causes the chip to drive PERSTn_L
            low (if RST_CTL(0..3)[RST_DRV] = 1). */
    /* 3.  Read RST_SOFT_PRST(0..3). This ensures the PCIe bus is now in reset.
        - Note that PCIERCn_CFGn registers cannot be accessed when
        RST_SOFT_PRST(0..3)[SOFT_PRST] = 1. */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
    {
        BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(pcie_port),
            c.s.soft_prst = 1);
        BDK_CSR_READ(node, BDK_RST_SOFT_PRSTX(pcie_port));
    }
    else
    {
        BDK_CSR_MODIFY(c, node, BDK_PEMX_RST_SOFT_PERST(pcie_port),
            c.s.soft_perst = 1);
        BDK_CSR_READ(node, BDK_PEMX_RST_SOFT_PERST(pcie_port));
    }
    /* 4.  Write GSER(0..8)_PHY_CTL[PHY_RESET] = 1.
        - This puts the PHY in reset. */

    /* 6.  Wait 2 ms or more before taking the PCIe port out of reset. */
    bdk_wait_usec(2000);

    /* To take PCIe port out of reset, perform the following steps: */
    /* 1.  Write PEM(0..1)_ON[PEMON] = 1. */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_ON(pcie_port),
        c.s.aclr = 1; /* Auto clear on chip reset */
        c.s.pemon = 1);

    BDK_CSR_READ(node, BDK_PEMX_ON(pcie_port));

    return 0;
}

/**
 * Before PCIe link can be brought up a number of steps must be performed to
 * reset the PEM, take the PEM out of reset, initialize the PEM, initialize
 * RC config space, and initialize the address regions. These steps must be
 * performed every time the PEM is reset, which may be repeated if the PCIe link
 * doesn't come up at the desired speed and width.
 *
 * @param node      Node to initialize
 * @param pcie_port PCIe port to initialize
 *
 * @return Zero on success, negative on failure
 */
static int __bdk_pcie_rc_pre_link_init(bdk_node_t node, int pcie_port)
{

    /* Make sure the PEM and GSER do a full reset before starting PCIe */
    if (__bdk_pcie_rc_reset(node, pcie_port))
    {
        bdk_error("N%d.PCIe%d: Reset failed.\n", node, pcie_port);
        return -1;
    }

    /* Bring the PCIe out of reset */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Taking port out of reset\n", node, pcie_port);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
    {
        BDK_CSR_WRITE(node, BDK_RST_SOFT_PRSTX(pcie_port), 0);
        BDK_CSR_READ(node, BDK_RST_SOFT_PRSTX(pcie_port));
        /* Check and make sure PCIe came out of reset. If it doesn't the board
            probably hasn't wired the clocks up and the interface should be
            skipped */
        BDK_TRACE(PCIE, "N%d.PCIe%d: Waiting for reset to complete\n", node, pcie_port);
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_RST_CTLX(pcie_port), rst_done, ==, 1, 10000))
        {
            if (!bdk_is_platform(BDK_PLATFORM_ASIM))
            {
                printf("N%d.PCIe%d: Stuck in reset, skipping.\n", node, pcie_port);
                return -1;
            }
        }
    }
    else
    {
        BDK_CSR_WRITE(node, BDK_PEMX_RST_SOFT_PERST(pcie_port), 0);
        BDK_CSR_READ(node, BDK_PEMX_RST_SOFT_PERST(pcie_port));
    }

    /* After PERST de-assertion, wait 10 milliseconds for any BIST
       to complete, and target cleanup */
    bdk_wait_usec (10000);

    BDK_TRACE(PCIE, "N%d.PCIe%d: Checking the PEM is out of reset\n", node, pcie_port);
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_ON(pcie_port), pemoor, ==, 1, 100000))
    {
        printf("N%d.PCIe%d: PEM in reset, skipping.\n", node, pcie_port);
        return -1;
    }

    /* Errata (PEM-34726) 2018-07-25 A0-A0 CatB PCIe inbound write merging doesn't work */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
    {
        BDK_CSR_MODIFY(c, node, BDK_PEMX_IB_MERGE_TIMER_CTL(pcie_port),
            c.s.wmerge_dis = 1);
    }

    /* Initialize the config space CSRs */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Setting up internal config space\n", node, pcie_port);
    __bdk_pcie_rc_initialize_config_space(node, pcie_port);

    /* Enable gen2 speed selection */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Enabling dynamic speed changes\n", node, pcie_port);
    BDK_CSR_MODIFY(c, node, BDK_PCIERCX_GEN2_PORT(pcie_port),
        c.s.dsc = 1);

    /* Setup the windows to allow access to this PCIe from the core */
    BDK_TRACE(PCIE, "N%d.PCIe%d: Initializing Address Regions\n", node, pcie_port);
    __bdk_pcie_address_initialize(node, pcie_port);
    return 0;
}

/**
 * Check if the PCIe port is already initialized and up for use in host(RC) mode.
 *
 * @param node      Node to use in a Numa setup. Can be an exact ID or a special
 *                  value.
 * @param pcie_port PCIe port to initialize
 *
 * @return Zero if not initialized, negative if not available, positive is the width of
 *         the link
 */
static int pcie_is_rc_initialized(bdk_node_t node, int pcie_port)
{
    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(pcie_port));
    if (!pemx_cfg.cn9.hostmd)
    {
        printf("N%d.PCIe%d: Port in endpoint mode.\n", node, pcie_port);
        return -1;
    }
    /* Read link state */
    BDK_CSR_INIT(link_ctl, node, BDK_PCIERCX_LINK_CTL(pcie_port));

    /* Check if the link is up */
    bool link_up = (link_ctl.s.dlla && !link_ctl.s.lt);
    if (!link_up)
        return false;
    return link_ctl.s.nlw; /* Link width */
}

/**
 * Initialize a PCIe port for use in host(RC) mode. It doesn't
 * enumerate the bus.
 *
 * @param pcie_port PCIe port to initialize
 *
 * @return Zero on success
 */
static int pcie_rc_initialize(bdk_node_t node, int pcie_port)
{
    const int MAX_RETRIES = 2 ; /* Total of 3 attempts: First + 2 retries */
    int retry_count = 0;
    int result = -1;

    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(pcie_port));
    if (!pemx_cfg.cn9.hostmd)
    {
        printf("N%d.PCIe%d: Port in endpoint mode.\n", node, pcie_port);
        return -1;
    }

    int last_negotiated_gen_speed = 0;
    while (retry_count <= MAX_RETRIES)
    {
        if (retry_count)
            BDK_TRACE(PCIE, "N%d.PCIe%d: Starting link retry %d\n", node, pcie_port, retry_count);
        /* Perform init that must be done after PEM reset, but before link */
        if (__bdk_pcie_rc_pre_link_init(node, pcie_port))
            return -1;
        /* Drop speed to gen2 or lower on last retry */
        if (retry_count == MAX_RETRIES && (MAX_RETRIES > 0))
        {
            BDK_CSR_INIT(link_cap, node, BDK_PCIERCX_LINK_CAP(pcie_port));

            /* Drop speed to gen2 if link bouncing
                Result =-1  PEM in reset
                Result = 0: link speed and width ok no retry needed
                Result = 1: Link errors or speed change needed
                Result = 2: lane width error
                Do not drop link speed if width incorrect */

            /* Negotiate to most recent negotiated speed, which did not have errors */
            if ((link_cap.s.mls > 2) && (result != 2))
            {
                BDK_TRACE(PCIE, "N%d.PCIe%d: Dropping speed to gen%d\n",
                    node, pcie_port, last_negotiated_gen_speed);
                link_cap.s.mls = last_negotiated_gen_speed ? last_negotiated_gen_speed : 1;
                BDK_CSR_WRITE(node, BDK_PCIERCX_LINK_CAP(pcie_port), link_cap.u);
                /* Set the target link speed */
                BDK_CSR_MODIFY(c, node, BDK_PCIERCX_LINK_CTL2(pcie_port),
                    c.s.tls = last_negotiated_gen_speed ? last_negotiated_gen_speed :1);
            }
        }
        /* Bring the link up */
        result = __bdk_pcie_rc_initialize_link(node, pcie_port, &last_negotiated_gen_speed);
        if (result == 0)
        {
            BDK_TRACE(PCIE, "N%d.PCIe%d: Link does not need a retry\n", node, pcie_port);
            break;
        }
        else if (result > 0)
        {
            if (retry_count >= MAX_RETRIES)
            {
                BDK_TRACE(PCIE, "N%d.PCIe%d: Link requested a retry, but hit the max retries\n", node, pcie_port);
                /* If the link is down, report failure */
                BDK_CSR_INIT(link_ctl, node, BDK_PCIERCX_LINK_CTL(pcie_port));
                bool link_up = (link_ctl.s.dlla && !link_ctl.s.lt);
                if (!link_up)
                    result = -1;
            }
            else
                BDK_TRACE(PCIE, "N%d.PCIe%d: Link requested a retry\n", node, pcie_port);
        }
        if (result < 0)
        {
            int ltssm_state = __bdk_pcie_rc_get_ltssm_state(node, pcie_port);
            printf("N%d.PCIe%d: Link timeout, probably the slot is empty (LTSSM %s)\n",
                node, pcie_port, ltssm_string(ltssm_state));
            return -1;
        }
        retry_count++;
    }

    /* Setup the EBUS control bits per CSR recomendation */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_EBUS_CTL(pcie_port),
        c.s.pf_bar0_sel = 1;
        c.s.atomic_dis = 1;
        c.s.vdm_dis = 1);

    BDK_TRACE(PCIE, "N%d.PCIe%d: Setting up internal BARs\n", node, pcie_port);
    /* Disable BAR0, the IO special BAR */
    BDK_CSR_WRITE(node, BDK_PEMX_P2N_BAR0_START(pcie_port), -1);
    /* BAR2 Starting at address 0 */
    BDK_CSR_WRITE(node, BDK_PEMX_P2N_BAR2_START(pcie_port), 0);
    /* Disable BAR4, the indexed memory region BAR */
    BDK_CSR_WRITE(node, BDK_PEMX_P2N_BAR4_START(pcie_port), -1);
    /* Setup BAR attributes */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_BAR_CTL(pcie_port),
        c.cn9.bar4_enb = 0; /* BAR4 is disabled (Index memory bar) */
        c.cn9.bar0_enb = 0; /* BAR0 is disabled (SDP register bar) */
        c.cn9.bar2_cbit = 0; /* Disable the BAR2_cbit */
        c.cn9.bar2_siz = 0x21; /* Size of BAR2, 8TB */
        c.s.bar2_enb = 0; /* Disabled while we make changes (Large memory BAR2) */
        c.s.bar2_cax = 0); /* Cache in L2 */
    bdk_wait_usec(1000); /* Wait 1ms before enabling, per HRM */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_BAR_CTL(pcie_port),
        c.s.bar2_enb = 1); /* Enable large memory BAR2 */

    /* Display the link status */
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        printf("N%d.PCIe%d: Simulation, can't report link speed\n", node, pcie_port);
    }
    else
    {
        BDK_CSR_INIT(link_ctl, node, BDK_PCIERCX_LINK_CTL(pcie_port));
        printf("N%d.PCIe%d: Link active, %d lanes, speed gen%d\n",
            node, pcie_port, link_ctl.s.nlw, link_ctl.s.ls);
    }

    return 0;
}


/**
 * Shutdown a PCIe port and put it in reset
 *
 * @param pcie_port PCIe port to shutdown
 *
 * @return Zero on success
 */
static int pcie_rc_shutdown(bdk_node_t node, int pcie_port)
{
    /* Check that the controller is out of reset */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
    {
        BDK_CSR_INIT(rst_ctlx, node, BDK_RST_CTLX(pcie_port));
        if (!rst_ctlx.s.rst_done)
            goto skip_idle_wait;
    }

    /* Check if link is up */
    BDK_CSR_INIT(pciercx_link_ctl, node, BDK_PCIERCX_LINK_CTL(pcie_port));
    if ((pciercx_link_ctl.s.dlla == 0) || (pciercx_link_ctl.s.lt == 1))
        goto skip_idle_wait;
#if 0 // FIXME
    /* Wait for all pending operations to complete */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PEMX_CPL_LUT_VALID(pcie_port), tag, ==, 0, 2000))
        printf("N%d.PCIe%d: Shutdown timeout\n", node, pcie_port);
#endif
skip_idle_wait:
    /* Bring down the link */
    BDK_CSR_MODIFY(c, node, BDK_PEMX_CTL_STATUS(pcie_port), c.cn9.lnk_enb = 0);
    /* Force reset */
    __bdk_pcie_rc_reset(node, pcie_port);
    return 0;
}

/**
 * This is initiating a re-calibration sequence for lane PLL.
 *
 * The purpose of this function is because of some platforms in
 * which the CAL_READY bit of the GSERNX_LANEX_INIT_BSTS register is
 * not set yet during EP initialization.  This was noticed on FIO and
 * some platforms (supermicro) in which the reference clock from the host was not
 * available immediately at EP execution.  This function is called
 * from BDP EP initialization only for PCIE attached QLMS.
 *
 * Reference Errata: 36827 for 96XX A0, B0 parts (non-rambus)
 * Impact: Primarily LIO3 boards that operate in EP mode.
 *
 * @param node
 * @param qlm
 */
static void bdk_pcie_ep_9xxx_lane_pll_recalibrate(bdk_node_t node, int qlm)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1))
    {
        int qlm_lanes = bdk_qlm_get_lanes(node, qlm);

        for (int lane = 0; lane < qlm_lanes; lane++)
        {
            BDK_TRACE(PCIE, "QLM %d Lane %d PLL Calibrate\n", qlm, lane);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
                c.s.tx_div_rst = 1);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
                c.s.reset = 1);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
                c.s.vco_cal_reset = 1);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
                c.s.vco_cal_reset = 0);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
                c.s.cal_en = 0);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
                c.s.cal_en = 1);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
                c.s.reset = 0);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
                c.s.tx_div_rst = 0);
        }
    }
}

/**
 * This is initiating a re-calibration sequence for common PLL.
 *
 * The purpose of this function is because of some platforms in
 * which the CAL_READY bit of the GSERNX_LANEX_INIT_BSTS register is
 * not set yet during EP initialization.  This was noticed on FIO and
 * some platforms (Supermicro) in which the reference clock from the host
 * was not available immediately at EP execution.  This function is called
 * from BDP EP initialization only for PCIE attached QLMS.
 *
 * Reference Errata: 36827 for 96XX A0, B0 parts (non-rambus)
 * Impact: Primarily LIO3 boards that operate in EP mode.
 *
 * @param node
 * @param qlm
 */
static void bdk_pcie_ep_9xxx_common_pll_recalibrate(bdk_node_t node, int qlm)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1))
    {
        BDK_TRACE (PCIE,"QLM %d Common PLL Calibrate\n",qlm);

        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
            c.s.reset = 1);

        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
            c.s.vco_cal_reset = 1);

        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
            c.s.vco_cal_reset = 0);

        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
            c.s.cal_en = 0);

        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
            c.s.cal_en = 1);

        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
            c.s.reset = 0);
    }
}

/**
 * This is initiating a calibration check sequence for common PLL.
 * This is really only for EP mode
 *
 * The purpose of this function is because of some platforms in
 * which the CAL_READY bit of the GSERNX_LANEX_INIT_BSTS register is
 * not set yet during EP script initialization.  This was noticed on FIO and
 * some platforms (supermicro) in which the reference clock from the host was not
 * available immediately at EP execution.  This function is called
 * from BDP EP initialization only for PCIE attached QLMS.
 *
 * Since the PCIe can consume up to 4 QLMS, the PEM configuration is
 * used to get strap information. This function is only called when in
 * EP mode, by the BDK PCIE initialization in bdk_boot_pcie.
 *
 * Reference Errata: 36827 for 96XX A0, B0 parts (non-rambus)
 * Impact: Primarily LIO3 boards that operate in EP mode.
 *
 * @param node
 * @param pcie_port
 */
void bdk_pcie_ep_9xxx_cal_ready_errata_36827(bdk_node_t node, int pcie_port)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CN96XX_PASS1_1))
    {
        bdk_gsernx_lanex_init_bsts_t init_bsts;

        int qlm = bdk_qlm_get(node, BDK_IF_PCIE, pcie_port, 0);
        if (qlm < 0)
            return;

        int qlm_lanes = bdk_qlm_get_lanes(node, qlm);
        int pcie_lanes = 4;
        bool qlm_needs_calibrate = false;

        /* Get the number of lanes */
        /* Must be the PEM configuration */
        bdk_pemx_cfg_t pemx_cfg;

        pemx_cfg.u = BDK_CSR_READ(node, BDK_PEMX_CFG(pcie_port));
        if (pemx_cfg.cn9.lanes == 1)
            pcie_lanes = 4;
        else if (pemx_cfg.cn9.lanes == 2)
            pcie_lanes = 8;
        else if (pemx_cfg.cn9.lanes == 3)
            pcie_lanes = 16;

        BDK_TRACE (PCIE,"Port %d Link Width %d\n",pcie_port,pcie_lanes);

        while (pcie_lanes > 0)
        {
            qlm_lanes = bdk_qlm_get_lanes(node, qlm);
            qlm_needs_calibrate = false;

            /* All lanes must be ready , if not, should re-calibrate    */
            for (int lane=0;lane < qlm_lanes; lane++)
            {
                init_bsts.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane));
                if (!init_bsts.s.cal_ready)
                {
                    /* If any lane not calibrated, calibrate qlm    */
                    BDK_TRACE(PCIE, "Port %d QLM %d Lane %d CAL_READY NOT SET\n", pcie_port, qlm, lane);
                    qlm_needs_calibrate = true;
                }
            }

            /* Calibrate the QLM if any of the lanes out    */
            if (qlm_needs_calibrate)
            {
                BDK_TRACE(PCIE, "Port %d QLM %d Calibration\n", pcie_port, qlm);
                bdk_pcie_ep_9xxx_common_pll_recalibrate(node, qlm);
                bdk_pcie_ep_9xxx_lane_pll_recalibrate(node, qlm);
                bdk_wait_usec(100);
                qlm_needs_calibrate = false;
            }
            else
            {
                BDK_TRACE (PCIE,"Port %d QLM %d CAL_READY SET\n",pcie_port,qlm);
            }

            pcie_lanes -= qlm_lanes;
            qlm++;
        }
    }
}

/**
 * Build a PCIe config space request address for a device
 *
 * @param pcie_port PCIe port to access
 * @param bus       Sub bus
 * @param dev       Device ID
 * @param fn        Device sub function
 * @param reg       Register to access
 *
 * @return 64bit IO address
 */
static uint64_t pcie_build_config_addr(bdk_node_t node, int pcie_port, int bus, int dev, int fn, int reg)
{
    int num_pems = bdk_pcie_get_num_ports(node);
    int ecam;

    if (pcie_port < num_pems)
        ecam = pcie_port + bdk_ecam_get_num(node);
    else if (pcie_port >= 100)
        ecam = pcie_port - 100;
    else
        return 0;

    bdk_device_t device;
    memset(&device, 0, sizeof(device));
    device.node = node;
    device.ecam = ecam;
    device.bus = bus;
    device.dev = dev;
    device.func = fn;
    return __bdk_ecam_build_address(&device, reg);
}

const __bdk_pcie_ops_t pcie_ops_cn9xxx = {
    .get_num_ports = pcie_get_num_ports,
    .is_rc_initialized = pcie_is_rc_initialized,
    .rc_initialize = pcie_rc_initialize,
    .rc_shutdown = pcie_rc_shutdown,
    .get_base_address = pcie_get_base_address,
    .get_base_size = pcie_get_base_size,
    .build_config_addr = pcie_build_config_addr,
};

