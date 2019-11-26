/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "bdk-qlm-common.h"
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"

enum
{
    MCU_FLAGS_SPREAD_SPECTRUM = 0x4,
    MCU_FLAGS_AUTONEG = 0x10,
    MCU_FLAGS_KR_TRAINING = 0x20,
    MCU_FLAGS_FEC = 0x40,
    MCU_FLAGS_RS_FEC = 0x80,
};

/**
 * Converts a measured reference clock to a likely ideal value. Rounds
 * clock speed to the nearest REF_*Mhz define.
 *
 * @param node   Node to use in numa setup
 * @param qlm    Which QLM
 * @param measured_hz
 *               Measured value
 *
 * @return Value exactly matching a define
 */
int __bdk_qlm_round_refclock(bdk_node_t node, int qlm, int measured_hz)
{
    int ref_clk;
    if ((measured_hz > REF_100MHZ - REF_100MHZ / 10) && (measured_hz < REF_100MHZ + REF_100MHZ / 10))
    {
        ref_clk = REF_100MHZ;
    }
    else if ((measured_hz > REF_125MHZ - REF_125MHZ / 10) && (measured_hz < REF_125MHZ + REF_125MHZ / 10))
    {
        ref_clk = REF_125MHZ;
    }
    else if ((measured_hz > REF_156MHZ - REF_156MHZ / 10) && (measured_hz < REF_156MHZ + REF_156MHZ / 10))
    {
        ref_clk = REF_156MHZ;
    }
    else if (measured_hz < 1000000)
    {
        ref_clk = 0; /* Used for disabled QLMs */
    }
    else
    {
        ref_clk = measured_hz;
        bdk_error("N%d.QLM%d: Unexpected reference clock speed of %d Mhz\n", node, qlm, measured_hz / 1000000);
    }
    return ref_clk;
}

/**
 * TWSI reads from the MCU randomly timeout. Retry a few times on
 * failure to try and recover
 *
 * @param twsi_device
 *                  TWSI bus device
 * @param dev_addr  Device address (7 bit)
 * @param internal_addr
 *                  Internal address.  Can be 0, 1 or 2 bytes in width
 * @param num_bytes Number of data bytes to read (1-4)
 * @param ia_width_bytes
 *                  Internal address size in bytes (0, 1, or 2)
 *
 * @return Read data, or -1 on failure
 */
static int64_t mcu_read(bdk_device_t *twsi_device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes)
{
    int read_tries = 0;
    int64_t result;
    do
    {
        result = bdk_device_twsi_read_ia(twsi_device, dev_addr, internal_addr, num_bytes, ia_width_bytes);
        read_tries++;
        if (result < 0)
        {
            BDK_TRACE(QLM, "Timeout %d reading from MCU\n", read_tries);
            bdk_wait_usec(100000);
        }
    } while ((result < 0) && (read_tries < 3));
    return result;
}

/**
 * Some dies are put in alternate packages that remap the QLM/DLM names. This
 * converts the MCU external name to the internal chip QLM number.
 *
 * @param external_qlm
 *               External QLM/DLM number from MCU
 *
 * @return Internal QLM/DLM number
 */
static int qlm_remap_package(int external_qlm)
{
    int internal_qlm = external_qlm;
    if (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN95XXE) /* CN95XXe */
    {
        const int8_t qlm_map[] = { 3, 7, 6, 4 };
        internal_qlm = qlm_map[external_qlm];
    }
    else if (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN93XXC) /* CN93XXC networking version */
    {
        const int8_t qlm_map[] = { 0, 1, 3, 6, 7 };
        internal_qlm = qlm_map[external_qlm];
    }
    return internal_qlm;
}

/**
 * For EVB and EBB board, query the MCU to determine the QLM setup.
 * Applying any configuration found.
 *
 * @param node   Node to configure
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_mcu_auto_config(bdk_node_t node)
{
    const int MCU_TWSI_BUS = bdk_is_model(OCTEONTX_CN9XXX) ? 2 : 0;
    const int MCU_TWSI_ADDRESS = 0x60;
    int64_t data;

    if (bdk_is_platform(BDK_PLATFORM_EMULATOR) || bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    bdk_device_t *twsi_device = bdk_device_lookup(node, BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), MCU_TWSI_BUS);

    /* Check the two magic number bytes the MCU should return */
    data = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x00, 1, 1);
    if (data != 0xa5)
    {
        printf("QLM Config: MCU not found, skipping auto configuration\n");
        return -1;
    }
    data = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x01, 1, 1);
    if (data != 0x5a)
    {
        bdk_error("QLM Config: MCU magic number incorrect\n");
        return -1;
    }

    /* Read the MCU version */
    int mcu_major = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x02, 1, 1);
    int mcu_minor = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x03, 1, 1);
    BDK_TRACE(QLM, "MCU version %d.%d\n", mcu_major, mcu_minor);
    if ((mcu_major < 2) || ((mcu_major == 2) && (mcu_minor < 30)))
    {
        bdk_error("QLM Config: Unexpected MCU version %d.%d\n", mcu_major, mcu_minor);
        return -1;
    }

    /* Find out how many lanes the MCU thinks are available */
    int lanes = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x16, 1, 1);
    BDK_TRACE(QLM, "MCU says board has %d lanes\n", lanes);
    int correct_lanes = 0;
    if (bdk_is_model(OCTEONTX_CN83XX))
        correct_lanes = 22;
    else if (bdk_is_model(OCTEONTX_CN81XX))
        correct_lanes = 8;
    else if (bdk_is_model(OCTEONTX_CN96XX))
    {
        if (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN95XXE) /* CN95XXe */
            correct_lanes = 14;
        else if (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN93XX) /* CN93XX */
            correct_lanes = 20;
        else if (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN93XXC) /* CN93XXC networking version */
            correct_lanes = 20;
        else
            correct_lanes = 28;
    }
    else if (bdk_is_model(OCTEONTX_CNF95XX))
        correct_lanes = 14;
    if (lanes != correct_lanes)
    {
        bdk_error("QLM Config: Unexpected number of lanes (%d) from MCU\n", lanes);
        return -1;
    }

    int lane = 0;
    int qlm = 0;
    while (lane < lanes)
    {
        int write_status;
        int width;
        int mode;
        int speed;
        int refclk;
        int64_t cfg_flags;
        /* TWSI reads from the MCU randomly timeout. Retry a few times on
           failure to try and recover */
        int read_tries = 0;
        do
        {
            read_tries++;
            if (read_tries > 3)
            {
                bdk_error("QLM Config: Timeouts reading from MCU\n");
                return -1;
            }
            /* Space request out 20ms */
            bdk_wait_usec(20000);
            /* Select the lane we are interested in */
            write_status = bdk_device_twsi_write_ia(twsi_device, MCU_TWSI_ADDRESS, 0x16, 1, 1, lane);
            /* Space request out 20ms */
            bdk_wait_usec(20000);
            /* Get the mode */
            width = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x17, 1, 1);
            mode = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x18, 2, 1);
            speed = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x19, 2, 1);
            refclk = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x1a, 1, 1);
            /* Starting the CN9XXX, the MCU support config flags */
            if (!bdk_is_model(OCTEONTX_CN8XXX))
                cfg_flags = mcu_read(twsi_device, MCU_TWSI_ADDRESS, 0x1c, 4, 1);
            else
                cfg_flags = 0;
        } while ((write_status < 0) || (width < 0) || (mode < 0) || (speed < 0) || (refclk < 0) || (cfg_flags < 0));

        BDK_TRACE(QLM, "MCU lane %d, width %d, mode 0x%x, speed 0x%x, ref 0x%x, flags 0x%lx\n",
            lane, width, mode, speed, refclk, cfg_flags);
        if ((width != 0) && (width != 1) && (width != 2) && (width != 4) && (width != 8) && (width != 16))
        {
            bdk_error("QLM Config: Unexpected interface width (%d) from MCU\n", width);
            return -1;
        }
        /* MCU reports a width of 0 for unconfigured QLMs. It reports a width
           of 1 for some combinations on CN80XX, and two on others. Convert
           either 0 or 1 to the actual width, or 2 for CN80XX. Yuck */
        int qlm_width = bdk_qlm_get_lanes(node, qlm_remap_package(qlm));
        if (width <= qlm_width)
        {
            if (bdk_is_altpkg(OCTEONTX_CN81XX) && (qlm < 2))
                width = 2;
            else
                width = qlm_width;
        }

        const char *qlm_mode;
        int qlm_speed = (speed >> 8) * 1000 + (speed & 0xff) * 1000 / 256;
        bdk_qlm_clock_t qlm_clk;

        /* The top nibble of the refclk is a clock input selector */
        switch (refclk & 0xf0)
        {
            case 0x00: /* Old MCU, before upper nibble was clock selector */
                switch (refclk)
                {
                    case 0x01: /* 156.25 MHz local reference clock */
                        qlm_clk = bdk_is_model(OCTEONTX_CN8XXX) ? BDK_QLM_CLK_COMMON_1 : BDK_QLM_CLK_COMMON_2;
                        break;
                    case 0x00: /* No clock specified */
                    case 0x03: /* 100 MHz local reference clock */
                        qlm_clk = BDK_QLM_CLK_COMMON_0;
                        break;
                    case 0x07: /* Off-board (external) 100 MHz reference clock */
                        qlm_clk = BDK_QLM_CLK_EXTERNAL;
                        break;
                    case 0x0B: /* 100 MHz spread spectrum reference clock */
                        qlm_clk = bdk_is_model(OCTEONTX_CN8XXX) ? BDK_QLM_CLK_EXTERNAL : BDK_QLM_CLK_COMMON_1;
                        break;
                    default:
                        bdk_error("QLM Config: Unexpected refclk (0x%x) from MCU\n", refclk);
                        return -1;
                }
                break;
            case 0x10: /* External reference clock input */
                qlm_clk = BDK_QLM_CLK_EXTERNAL;
                break;
            case 0x20: /* Common clock 0 */
                qlm_clk = BDK_QLM_CLK_COMMON_0;
                break;
            case 0x30: /* Common clock 1 */
                qlm_clk = BDK_QLM_CLK_COMMON_1;
                break;
            case 0x40: /* Common clock 2 */
                qlm_clk = BDK_QLM_CLK_COMMON_2;
                break;
            default:
                bdk_error("QLM Config: Unexpected refclk (0x%x) from MCU\n", refclk);
                return -1;
        }

        switch (mode)
        {
            case 0x0000: /* No Configuration */
                qlm_mode = NULL;
                break;
            case 0x0101: /* PCIe Host */
                qlm_mode = (width == 16) ? "PCIE_X16" :
                           (width == 8) ? "PCIE_X8" :
                           (width == 4) ? "PCIE_X4" :
                           "PCIE_X2";
                break;
            case 0x0102: /* PCIe Endpoint */
                qlm_mode = (width == 16) ? "PCIE_X16-EP" :
                           (width == 8) ? "PCIE_X8-EP" :
                           (width == 4) ? "PCIE_X4-EP" :
                           "PCIE_X2-EP";
                break;
            case 0x1000: /* SGMII */
                qlm_mode = "SGMII";
                /* CN80XX parts on EBBs use phy port 2 for SGMII, while QSGMII
                   uses the correct port. Fix this for DLM1 and DLM3 */
                if (bdk_is_altpkg(OCTEONTX_CN81XX))
                {
                    int bgx = (qlm == 3) ? 1 : 0;
                    uint64_t phy = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, 0, bgx, 2);
                    bdk_config_set_int(phy, BDK_CONFIG_PHY_ADDRESS, 0, bgx, 1);
                }
                if (bdk_is_model(OCTEONTX_CN9XXX) && (qlm_clk != BDK_QLM_CLK_COMMON_2))
                {
                    qlm_clk = BDK_QLM_CLK_COMMON_2;
                    BDK_TRACE(QLM, "MCU specified the incorrect ref clock for SGMII, fixing\n");
                }
                break;
            case 0x1001: /* 1G-X */
                qlm_mode = "1G_X";
                /* CN80XX parts on EBBs use phy port 2 for SGMII, while QSGMII
                   uses the correct port. Fix this for DLM1 and DLM3 */
                if (bdk_is_altpkg(OCTEONTX_CN81XX))
                {
                    int bgx = (qlm == 3) ? 1 : 0;
                    uint64_t phy = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, 0, bgx, 2);
                    bdk_config_set_int(phy, BDK_CONFIG_PHY_ADDRESS, 0, bgx, 1);
                }
                break;
            case 0x1100: /* QSGMII */
                qlm_mode = "QSGMII";
                break;
            case 0x1200: /* USXGMII */
                qlm_mode = "USXGMII_1X1";
                break;
            case 0x2000: /* XAUI */
                qlm_mode = "XAUI";
                break;
            case 0x2100: /* RXAUI */
                qlm_mode = "RXAUI";
                break;
            case 0x2200: /* DXAUI */
                qlm_mode = "XAUI";
                break;
            case 0x4000: /* SATA */
                qlm_mode = "SATA";
                break;
            case 0x5001: /* XFI */
                qlm_mode = "XFI";
                break;
            case 0x5002: /* 10G-KR */
                qlm_mode = "10G_KR";
                break;
            case 0x5003: /* SFI */
                qlm_mode = "SFI";
                break;
            case 0x6001: /* XLAUI */
                qlm_mode = "XLAUI";
                break;
            case 0x6002: /* 40G-KR4 */
                qlm_mode = "40G_KR4";
                break;
            case 0x8001: /* 25G-R C2C */
                qlm_mode = "25GAUI_C2C";
                break;
            case 0x8002: /* 25G-R C2M */
                qlm_mode = "25GAUI_C2M";
                break;
            case 0x8003: /* 25G-R KR */
                qlm_mode = "25G_KR";
                break;
            case 0x8101: /* 50G-R2 C2C */
                qlm_mode = "50GAUI_2_C2C";
                break;
            case 0x8102: /* 50G-R2 C2M */
                qlm_mode = "50GAUI_2_C2M";
                break;
            case 0x8103: /* 50G-R2 KR */
                qlm_mode = "50G_KR2";
                break;
            case 0x8201: /* 100G-R4 C2C */
                qlm_mode = "CAUI_4_C2C";
                break;
            case 0x8202: /* 100G-R4 C2M */
                qlm_mode = "CAUI_4_C2M";
                break;
            case 0x8203: /* 100G-R4 KR */
                qlm_mode = "100G_KR4";
                break;
            case 0x8801: /* 20G-R C2C */
            case 0x8802: /* 20G-R C2M */
                if (cfg_flags & MCU_FLAGS_AUTONEG)
                    bdk_warn("20G currently doesn't support auto negotiation\n");
                qlm_mode = "20GAUI_C2C";
                break;
            case 0x8803: /* 20G-R KR */
                bdk_warn("20G currently doesn't support KR\n");
                qlm_mode = "20GAUI_C2C";
                break;
            case 0x8901: /* 40G-R2 C2C */
            case 0x8902: /* 40G-R2 C2M */
                if (cfg_flags & MCU_FLAGS_AUTONEG)
                    bdk_warn("40G-R2 currently doesn't support auto negotiation\n");
                qlm_mode = "40GAUI_2_C2C";
                break;
            case 0x8903: /* 40G-R2 KR */
                bdk_warn("40G-R2 currently doesn't support KR\n");
                qlm_mode = "40GAUI_2_C2C";
                break;
            case 0x8a01: /* 80G-R4 C2C */
            case 0x8a02: /* 80G-R4 C2M */
                if (cfg_flags & MCU_FLAGS_AUTONEG)
                    bdk_warn("80G-R4 currently doesn't support auto negotiation\n");
                qlm_mode = "80GAUI_4_C2C";
                break;
            case 0x8a03: /* 80G-R4 KR */
                bdk_warn("80G-R4 currently doesn't support KR\n");
                qlm_mode = "80GAUI_4_C2C";
                break;
            case 0x8c01: /* 25G-R2 C2C */
                if (cfg_flags & MCU_FLAGS_AUTONEG)
                    bdk_warn("25G-R2 currently doesn't support auto negotiation\n");
                qlm_mode = "25GAUI_2_C2C";
                break;
            case 0x8d01: /* 50G-R4 C2C */
                if (cfg_flags & MCU_FLAGS_AUTONEG)
                    bdk_warn("50G-R4 currently doesn't support auto negotiation\n");
                qlm_mode = "50GAUI_4_C2C";
                break;
            default:
                bdk_error("QLM Config: Unexpected interface mode (0x%x) from MCU\n", mode);
                qlm_mode = NULL;
                break;
        }

        lane += width;
        do
        {
            int internal_qlm = qlm_remap_package(qlm);
            int num_lanes = bdk_qlm_get_lanes(node, internal_qlm);

            if (qlm_mode)
            {
                BDK_TRACE(QLM, "N%d.QLM%d: Setting mode %s, speed %d, clock %d\n",
                    node, internal_qlm, qlm_mode, qlm_speed, qlm_clk);
                bdk_config_set_str(qlm_mode, BDK_CONFIG_QLM_MODE, node, internal_qlm, 0);
                bdk_config_set_int(qlm_speed, BDK_CONFIG_QLM_FREQ, node, internal_qlm, 0);
                bdk_config_set_int(qlm_clk, BDK_CONFIG_QLM_CLK, node, internal_qlm);

                /* KR flag processing not implemented yet */
                if (cfg_flags & MCU_FLAGS_KR_TRAINING)
                    bdk_warn("N%d.QLM%d: MCU KR Training flag ignored\n", node, internal_qlm);

                /* Check if we need FEC */
                if (cfg_flags & (MCU_FLAGS_RS_FEC | MCU_FLAGS_FEC))
                {
                    bool is_split;
                    bool is_upper;
                    int bgx_cgx = bdk_qlm_to_network(node, internal_qlm, &is_split, &is_upper);
                    if (bgx_cgx != -1)
                    {
                        const char *name_str = (cfg_flags & MCU_FLAGS_RS_FEC) ? "RS-FEC" : "FEC";
                        int fec = (cfg_flags & MCU_FLAGS_RS_FEC) ? BDK_NETPHY_FLAG_RS_FEC : BDK_NETPHY_FLAG_FEC;
                        int first_lmac = is_upper ? 2 : 0;
                        int last_lmac = is_upper ? 3 : num_lanes - 1;
                        for (int lmac = first_lmac; lmac <= last_lmac; lmac++)
                        {
                            BDK_TRACE(QLM, "N%d.QLM%d: Setting CGX%d.LMAC%d to %s\n",
                                node, internal_qlm, bgx_cgx, lmac, name_str);
                            bdk_config_set_int(fec, BDK_CONFIG_NETWORK_FLAGS, node, bgx_cgx, lmac);
                        }
                    }
                }
            }

            if (qlm_mode && (strncmp(qlm_mode, "PCIE_X16", 8) == 0))
            {
                /* PCIe x16 is a special case as the QLM config function
                   actually configures both QLMs in one go */
                qlm += 3;
                width -= 16;
            }
            else if (qlm_mode && (strncmp(qlm_mode, "PCIE_X8", 7) == 0))
            {
                /* PCIe x8 is a special case as the QLM config function
                   actually configures both QLMs in one go */
                qlm++;
                width -= 8;
            }
            else if (qlm_mode && (strncmp(qlm_mode, "PCIE_X4", 7) == 0) && (width > num_lanes))
            {
                /* PCIe x4 is a special case as the QLM config function
                   actually configures both QLMs in one go */
                qlm++;
                width -= 4;
            }
            else if (width >= num_lanes)
            {
                if (num_lanes == 1)
                    width -= 2; /* Special case for CN80XX */
                else
                    width -= num_lanes;
            }
            else
                width = 0;
            qlm++;
        } while (width > 0);
    }
    return 0;
}

/**
 * Build a structure representing the state of a GSER*. This is normally stored in
 * a scratch register inside GSER*.
 *
 * @param mode     Desired mode
 * @param baud_mhz Rate in MHz
 * @param flags    Optional flags
 *
 * @return State to store in scratch
 */
bdk_qlm_state_lane_t __bdk_qlm_build_state(bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    bdk_qlm_state_lane_t state;
    state.u = 0;
    state.s.mode = mode;
    state.s.baud_mhz = baud_mhz;
    state.s.flags = flags;
    state.s.pcie = (mode > BDK_QLM_MODE_DISABLED) && (mode <= BDK_QLM_MODE_PCIE_X16);
    state.s.sata = (mode == BDK_QLM_MODE_SATA);
    state.s.cgx = (mode >= BDK_QLM_MODE_SGMII) && (mode < BDK_QLM_MODE_LAST);
    return state;
}
