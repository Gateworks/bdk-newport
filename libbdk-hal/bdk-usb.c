/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-usbdrd.h"
#include "libbdk-arch/bdk-csrs-usbh.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(USB);

/**
 * Write to DWC3 indirect debug control register
 *
 * @param node     Node to write to
 * @param usb_port USB port to write to
 * @param val      32bit value to write
 */
static void write_cr_dbg_cfg(bdk_node_t node, int usb_port, uint64_t val)
{
    BDK_CSR_WRITE(node, BDK_USBDRDX_UCTL_PORTX_CR_DBG_CFG(usb_port, 0), val);
}

/**
 * Poll the DWC3 internal status until the ACK bit matches a desired value. Return
 * the final status.
 *
 * @param node     Node to query
 * @param usb_port USB port to query
 * @param desired_ack
 *                 Desired ACK bit state
 *
 * @return Final status with ACK at correct state
 */
static bdk_usbdrdx_uctl_portx_cr_dbg_status_t get_cr_dbg_status(bdk_node_t node, int usb_port, int desired_ack)
{
    const int TIMEOUT = 1000000; /* 1 sec */
    bdk_usbdrdx_uctl_portx_cr_dbg_status_t status;
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_USBDRDX_UCTL_PORTX_CR_DBG_STATUS(usb_port, 0), ack, ==, desired_ack, TIMEOUT))
    {
        BDK_TRACE(USB_XHCI, "N%d.USB%d: Timeout waiting for indirect ACK\n", node, usb_port);
        status.u = -1;
    }
    else
        status.u = BDK_CSR_READ(node, BDK_USBDRDX_UCTL_PORTX_CR_DBG_STATUS(usb_port, 0));
    return status;
}

/**
 * Perform an indirect read of an internal register inside the DWC3 usb block
 *
 * @param node     Node to read
 * @param usb_port USB port to read
 * @param addr     Indirect register address
 *
 * @return Value of the indirect register
 */
static uint32_t dwc3_uphy_indirect_read(bdk_node_t node, int usb_port, uint32_t addr)
{
    bdk_usbdrdx_uctl_portx_cr_dbg_cfg_t dbg_cfg;
    bdk_usbdrdx_uctl_portx_cr_dbg_status_t status;

    /* See the CSR description for USBHX_UCTL_PORTX_CR_DBG_CFG, which describes
       the steps implemented by this function */

    dbg_cfg.u = 0;
    dbg_cfg.s.data_in = addr;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    dbg_cfg.s.cap_addr = 1;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    status = get_cr_dbg_status(node, usb_port, 1);
    if (status.u == (uint64_t)-1)
        return 0xffffffff;

    write_cr_dbg_cfg(node, usb_port, 0);
    get_cr_dbg_status(node, usb_port, 0);

    dbg_cfg.u = 0;
    dbg_cfg.s.read = 1;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    status = get_cr_dbg_status(node, usb_port, 1);

    write_cr_dbg_cfg(node, usb_port, 0);
    get_cr_dbg_status(node, usb_port, 0);

    return status.s.data_out;
}

/**
 * Perform an indirect write of an internal register inside the DWC3 usb block
 *
 * @param node     Node to write
 * @param usb_port USB port to write
 * @param addr     Indirect register address
 * @param value    Value for write
 */
static void dwc3_uphy_indirect_write(bdk_node_t node, int usb_port, uint32_t addr, uint16_t value)
{
    bdk_usbdrdx_uctl_portx_cr_dbg_cfg_t dbg_cfg;

    /* See the CSR description for USBHX_UCTL_PORTX_CR_DBG_CFG, which describes
       the steps implemented by this function */

    dbg_cfg.u = 0;
    dbg_cfg.s.data_in = addr;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    dbg_cfg.s.cap_addr = 1;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    get_cr_dbg_status(node, usb_port, 1);

    write_cr_dbg_cfg(node, usb_port, 0);
    get_cr_dbg_status(node, usb_port, 0);

    dbg_cfg.u = 0;
    dbg_cfg.s.data_in = value;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    dbg_cfg.s.cap_data = 1;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    get_cr_dbg_status(node, usb_port, 1);

    write_cr_dbg_cfg(node, usb_port, 0);
    get_cr_dbg_status(node, usb_port, 0);

    dbg_cfg.u = 0;
    dbg_cfg.s.write = 1;
    write_cr_dbg_cfg(node, usb_port, dbg_cfg.u);

    get_cr_dbg_status(node, usb_port, 1);

    write_cr_dbg_cfg(node, usb_port, 0);
    get_cr_dbg_status(node, usb_port, 0);
}

/**
 * Errata USB-29206 - The USB HS PLL in all 28nm devices has a
 * design issue that may cause the VCO to lock up on
 * initialization.  The Synopsys VCO is designed with an even
 * number of stages and no kick-start circuit, which makes us
 * believe that there is no question a latched up
 * (non-oscillating) state is possible. The workaround is to
 * check the PLL lock bit, which is just based on a counter and
 * will not set if the VCO is not oscillating, and if it's not
 * set do a power down/power up cycle on the PLL, which tests
 * have proven is much more likely to guarantee the VCO will
 * start oscillating.  Part of the problem appears to be that
 * the normal init sequence holds the VCO in reset during the
 * power up sequence, whereas the plain power up/down sequence
 * does not, so the voltage changing may be helping the circuit
 * to oscillate.
 *
 * @param node     Node to check
 * @param usb_port USB port to check
 *
 * @return Zero on success, negative on failure
 */
static int dwc3_uphy_check_pll(bdk_node_t node, int usb_port)
{
    /* Internal indirect register that reports if the phy PLL has lock.  This will
       be 1 if lock, 0 if no lock */
    const int DWC3_INT_IND_PLL_LOCK_REG = 0x200b;
    /* Internal indirect UPHY register that controls the power to the UPHY PLL */
    const int DWC3_INT_IND_UPHY_PLL_PU = 0x2012;
    /* Write enable bit for DWC3_INT_IND_PLL_POWER_CTL */
    const int DWC3_INT_IND_UPHY_PLL_PU_WE = 0x20;
    /* Power enable bit for DWC3_INT_IND_PLL_POWER_CTL */
    const int DWC3_INT_IND_UPHY_PLL_PU_POWER_EN = 0x02;

    uint32_t pll_locked = dwc3_uphy_indirect_read(node, usb_port, DWC3_INT_IND_PLL_LOCK_REG);
    int retry_count = 0;
    while (!pll_locked)
    {
        if (retry_count >= 3)
        {
            bdk_error("N%d.USB%d: USB2 PLL failed to lock\n", node, usb_port);
            return -1;
        }

        retry_count++;
        BDK_TRACE(USB_XHCI, "N%d.USB%d: USB2 PLL didn't lock, retry %d\n", node, usb_port, retry_count);

        /* Turn on write enable for PLL power control */
        uint32_t pwr_val = dwc3_uphy_indirect_read(node, usb_port, DWC3_INT_IND_UPHY_PLL_PU);
        pwr_val |= DWC3_INT_IND_UPHY_PLL_PU_WE;
        dwc3_uphy_indirect_write(node, usb_port, DWC3_INT_IND_UPHY_PLL_PU, pwr_val);

        /* Power down the PLL */
        pwr_val &= ~DWC3_INT_IND_UPHY_PLL_PU_POWER_EN;
        dwc3_uphy_indirect_write(node, usb_port, DWC3_INT_IND_UPHY_PLL_PU, pwr_val);
        bdk_wait_usec(1000);

        /* Power on the PLL */
        pwr_val |= DWC3_INT_IND_UPHY_PLL_PU_POWER_EN;
        dwc3_uphy_indirect_write(node, usb_port, DWC3_INT_IND_UPHY_PLL_PU, pwr_val);
        bdk_wait_usec(1000);

        /* Check for PLL Lock again */
        pll_locked = dwc3_uphy_indirect_read(node, usb_port, DWC3_INT_IND_PLL_LOCK_REG);
    }
    return 0;
}

/**
 * Initialize the clocks for USB such that it is ready for a generic XHCI driver
 *
 * @param node       Node to init
 * @param usb_port   Port to initialize
 * @param clock_type Type of clock connected to the usb port
 *
 * @return Zero on success, negative on failure
 */

int bdk_usb_initialize(bdk_node_t node, int usb_port, bdk_usb_clock_t clock_type)
{
    /* Asim's USB model is broken */
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return -1;

    if (BDK_IS_REQUIRED(USB_XHCI))
    {
        // XHCI polling needs to be off
        if (0 < bdk_usb_togglePoll(node, usb_port, DO_QUERY))
        {
            // If xhci polling was active turn it off
            bdk_usb_togglePoll(node, usb_port, DO_TOGGLE);
        }
    }

    /* Perform the following steps to initiate a cold reset. */

    /* 1.  Wait for all voltages to reach a stable state.  Ensure the
        reference clock is up and stable.
        a.  If 3.3V is up first, 0.85V must be soon after (within tens of ms). */

    /* 2.  Wait for IOI reset to deassert. */

    /* 3.  If Over Current indication and/or Port Power Control features
        are desired, program the GPIO CSRs appropriately.
        a.  For Over Current Indication, select a GPIO for the input and
            program GPIO_USBH_CTL[SEL].
        b. For Port Power Control, set one of
            GPIO_BIT_CFG(0..19)[OUTPUT_SEL] = USBH_VBUS_CTRL. */

    /* 4.  Assert all resets:
        a.  UPHY reset: USBDRD(0..1)_UCTL_CTL[UPHY_RST] = 1
        b. UAHC reset: USBDRD(0..1)_UCTL_CTL[UAHC_RST] = 1
        c. UCTL reset: USBDRD(0..1)_UCTL_CTL[UCTL_RST] = 1 */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.uphy_rst = 1;
        c.s.uahc_rst = 1;
        c.s.uctl_rst = 1);

    /* 5.  Configure the controller clock:
        a.  Reset the clock dividers: USBDRD(0..1)_UCTL_CTL[H_CLKDIV_RST] = 1.
        b. Select the controller clock frequency
            USBDRD(0..1)_UCTL_CTL[H_CLKDIV] = desired value.
            USBDRD(0..1)_UCTL_CTL[H_CLKDIV_EN] = 1 to enable the controller
                clock.
            Read USBDRD(0..1)_UCTL_CTL to ensure the values take effect.
        c.  Deassert the controller clock divider reset: USB-
            DRD(0..1)_UCTL_CTL[H_CLKDIV_RST] = 0. */
    uint64_t sclk_rate = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    uint64_t divider = (sclk_rate + 300000000-1) / 300000000;
    /*
    ** According to HRM Rules are:
    ** - clock must be below 300MHz
    ** USB3 full-rate requires 150 MHz or better
    ** USB3 requires 125 MHz
    ** USB2 full rate requires 90 MHz
    ** USB2 requires 62.5 MHz
    */
    if (divider <= 1)
        divider = 0;
    else if (divider <= 2)
        divider = 1;
    else if (divider <= 4)
        divider = 2;
    else if (divider <= 6)
        divider = 3;
    else if (divider <= 8)
        divider = 4;
    else if (divider <= 16)
        divider = 5;
    else if (divider <= 24)
        divider = 6;
    else
        divider = 7;
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.h_clkdiv_rst = 1);
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.h_clkdiv_sel = divider;
        c.s.h_clk_en = 1);
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.h_clkdiv_rst = 0);
    if (bdk_trace_enables & (1ull << BDK_TRACE_ENABLE_USB_XHCI)) {
        static bool printit[2] = {true,true};
        if (printit[usb_port]) {
            uint64_t fr_div;
            if (divider < 5) fr_div = divider * 2;
            else fr_div = 8 * (divider - 3);
            uint64_t freq = (typeof(freq)) (sclk_rate / fr_div);
            char *token;
            if (freq < 62500000ULL) token = "???Low";
            else if (freq < 90000000ULL) token = "USB2";
            else if (freq < 125000000ULL) token = "USB2 Full";
            else if (freq < 150000000ULL) token = "USB3";
            else token = "USB3 Full";
            printf("Freq %lld - %s\n",
                   (unsigned long long)freq, token);
            printit[usb_port] = false;
        }
    }
    /* 6.  Configure the strap signals in USBDRD(0..1)_UCTL_CTL.
        a.  Reference clock configuration (see Table 31.2): USB-
            DRD(0..1)_UCTL_CTL[REF_CLK_FSEL, MPLL_MULTIPLIER,
            REF_CLK_SEL, REF_CLK_DIV2].
        b. Configure and enable spread-spectrum for SuperSpeed:
            USBDRD(0..1)_UCTL_CTL[SSC_RANGE, SSC_EN, SSC_REF_CLK_SEL].
        c. Enable USBDRD(0..1)_UCTL_CTL[REF_SSP_EN].
        d. Configure PHY ports:
            USBDRD(0..1)_UCTL_CTL[USB*_PORT_PERM_ATTACH, USB*_PORT_DISABLE]. */
    {
        int ref_clk_src = 0;
        int ref_clk_fsel = 0x27;
        if (bdk_is_model(OCTEONTX_CN83XX)) {
            if (BDK_USB_CLOCK_SS_PAD_HS_PAD != clock_type) {
                bdk_error("Node %d usb_port %d: usb clock type %d is invalid\n", node, usb_port, clock_type);
                return -1;
            }
        }
        else if (bdk_is_model(OCTEONTX_CN81XX)) {
            switch (clock_type)
            {
            default:
                bdk_error("Node %d usb_port %d: usb clock type %d is invalid\n", node, usb_port, clock_type);
                return -1;
            case BDK_USB_CLOCK_SS_PAD_HS_PAD : ref_clk_src = 2; break;
            case BDK_USB_CLOCK_SS_REF0_HS_REF0 : ref_clk_src = 0; break;  /* Superspeed and high speed use DLM/QLM ref clock 0 */
            case BDK_USB_CLOCK_SS_REF1_HS_REF1 : ref_clk_src = 1; break;  /* Superspeed and high speed use DLM/QLM ref clock 1 */
            case BDK_USB_CLOCK_SS_PAD_HS_PLL : ref_clk_src = 6; ref_clk_fsel = 0x7; break;    /* Superspeed uses PAD clock, high speed uses PLL ref clock */
            case BDK_USB_CLOCK_SS_REF0_HS_PLL : ref_clk_src = 4; ref_clk_fsel = 0x7; break;    /* Superspeed uses DLM/QLM ref clock 0, high speed uses PLL ref clock */
            case BDK_USB_CLOCK_SS_REF1_HS_PLL: ref_clk_src = 5; ref_clk_fsel =0x7; break;   /* Superspeed uses DLM/QLM ref clock 1, high speed uses PLL ref clock */
            }
        }
        int mpll_mplier = bdk_is_model(OCTEONTX_CN8XXX) ? 0x19 : 0x0;
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
            c.s.ref_clk_fsel = ref_clk_fsel;
            c.s.mpll_multiplier = mpll_mplier;
            c.s.ref_clk_sel = ref_clk_src;
            c.s.ref_clk_div2 = 0);
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
            c.s.ssc_en = 1;
            c.s.ssc_ref_clk_sel = 0);
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
            c.s.ref_ssp_en = 1);
    }
    /* Hardware default is for ports to be enabled and not perm attach. Don't
        change it */

    /* 7.  The PHY resets in lowest-power mode. Power up the per-port PHY
       logic by enabling the following:
        a.  USBDRD(0..1)_UCTL_CTL [HS_POWER_EN] if high-speed/full-speed/low-
            speed functionality needed.
        b. USBDRD(0..1)_UCTL_CTL [SS_POWER_EN] if SuperSpeed functionality
            needed. */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.hs_power_en = 1;
        c.s.ss_power_en = 1);

    /* 8.  Wait 10 controller-clock cycles from step 5. for controller clock
        to start and async FIFO to properly reset. */
    bdk_wait_usec(1);

    /* 9.  Deassert UCTL and UAHC resets:
        a.  USBDRD(0..1)_UCTL_CTL[UCTL_RST] = 0
        b. USBDRD(0..1)_UCTL_CTL[UAHC_RST] = 0
        c. [optional] For port-power control:
        - Set one of GPIO_BIT_CFG(0..47)[PIN_SEL] =  USB0_VBUS_CTRLor USB1_VBUS_CTRL.
        - Set USBDRD(0..1)_UCTL_HOST_CFG[PPC_EN] = 1 and USBDRD(0..1)_UCTL_HOST_CFG[PPC_ACTIVE_HIGH_EN] = 1.
        - Wait for the external power management chip to power the VBUS.ional port-power control.
        ]
        d. You will have to wait 10 controller-clock cycles before accessing
            any controller-clock-only registers. */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.uctl_rst = 0);
    bdk_wait_usec(1);

    int usb_gpio = bdk_config_get_int(BDK_CONFIG_USB_PWR_GPIO, node, usb_port);
    int usb_polarity = bdk_config_get_int(BDK_CONFIG_USB_PWR_GPIO_POLARITY, node, usb_port);
    if (-1 != usb_gpio) {
        int gsrc = BDK_GPIO_PIN_SEL_E_USBX_VBUS_CTRL(usb_port);
        BDK_CSR_MODIFY(c,node,BDK_GPIO_BIT_CFGX(usb_gpio),
            c.s.pin_sel = gsrc;
            c.s.pin_xor = (usb_polarity) ? 0 : 1;
            c.s.tx_oe = 1);

        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_HOST_CFG(usb_port),
            c.s.ppc_en = 1;
            c.s.ppc_active_high_en = 1);
        bdk_wait_usec(100000);
    }

    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.uahc_rst = 0);

    bdk_wait_usec(100000);
    bdk_wait_usec(1);

    /* 10. Enable conditional coprocessor clock of UCTL by writing USB-
        DRD(0..1)_UCTL_CTL[CSCLK_EN] = 1. */
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        /* CN9XXX make coprocessor clock automatic */
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
            c.cn83xx.csclk_en = 1);
    }

    /* 11. Set USBDRD(0..1)_UCTL_CTL[DRD_MODE] to 1 for device mode, 0 for
        host mode. */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.drd_mode = 0);

    /* 12. Soft reset the UPHY and UAHC logic via the UAHC controls:
        a.  USBDRD(0..1)_UAHC_GUSB2PHYCFG(0)[PHYSOFTRST] = 1
        b. USBDRD(0..1)_UAHC_GUSB3PIPECTL(0)[PHYSOFTRST] = 1
        c. USBDRD(0..1)_UAHC_GCTL[CORESOFTRESET] = 1 */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GUSB2PHYCFGX(usb_port, 0),
        c.s.physoftrst = 1);
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GUSB3PIPECTLX(usb_port, 0),
        c.s.physoftrst = 1);
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GCTL(usb_port),
        c.s.coresoftreset = 1);

    /* 13. Program USBDRD(0..1)_UAHC_GCTL[PRTCAPDIR] to 0x2 for device mode
        or 0x1 for host mode. */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GCTL(usb_port),
        c.s.prtcapdir = 1);

    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        /* Workaround for Errata USB-36459 - pclock does not run long enough
           after uphy reset */
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_PORTX_CFG_SS(usb_port,0),
            c.s.lane0_ext_pclk_req = 1);
    }

    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CN96XX_PASS3_0))
    {
        /* Workaround for Errata USB-36852 and USB-37155 - premature shutoff of
           conditional clock */
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
            c.cn9.csclk_force = 1;);
    }

    /* 14. Wait 10us after step 13. for the PHY to complete its reset. */
    bdk_wait_usec(10);

    /* 15. Deassert UPHY reset: USBDRD(0..1)_UCTL_CTL[UPHY_RST] = 0. */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_CTL(usb_port),
        c.s.uphy_rst = 0);

    /* 16. Wait for at least 45us after step 15. for UPHY to output
        stable PHYCLOCK. */
    bdk_wait_usec(45);

    /* Workround Errata USB-29206 */
    if (bdk_is_model(OCTEONTX_CN8XXX) && dwc3_uphy_check_pll(node, usb_port))
        return -1;

    /* 17. Initialize any other strap signals necessary and make sure they
       propagate by reading back the last register written.
        a.  UCTL
            USBDRD(0..1)_UCTL_PORT0_CFG_*[*_TUNE]
            USBDRD(0..1)_UCTL_PORT0_CFG_*[PCS_*]
            USBDRD(0..1)_UCTL_PORT0_CFG_*[LANE0_TX_TERM_OFFSET]
            USBDRD(0..1)_UCTL_PORT0_CFG_*[TX_VBOOST_LVL]
            USBDRD(0..1)_UCTL__PORT0_CFG_*[LOS_BIAS]
            USBDRD(0..1)_UCTL_HOST_CFG
            USBDRD(0..1)_UCTL_SHIM_CFG
        b.  UAHC: only the following UAHC registers are accessible during
            CoreSoftReset.
            USBDRD(0..1)_UAHC_GCTL
            USBDRD(0..1)_UAHC_GUCTL
            USBDRD(0..1)_UAHC_GSTS
            USBDRD(0..1)_UAHC_GUID
            USBDRD(0..1)_UAHC_GUSB2PHYCFG(0)
            USBDRD(0..1)_UAHC_GUSB3PIPECTL(0) */
    /* Restore the correct defaults for 14nm. CSR mistakenly used defaults
       from 28nm */
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_PORTX_CFG_HS(usb_port, 0),
            c.s.comp_dis_tune = 3;  /* 14nm default */
            /* c.s.tx_preemp_amp_tune = 0; */ /* RTL advised to leave this alone */
            c.s.otgtune = 5;        /* 14nm default */
            c.s.tx_vref_tune = 0x9; /* eye tuning */
            c.s.tx_rise_tune = 3;   /* eye tuning */ );
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UCTL_PORTX_CFG_SS(usb_port, 0),
            c.s.los_bias = 2;             /* 14nm default */
            c.s.pcs_tx_deemph_3p5db = 23; /* 14nm default */
            c.s.pcs_tx_deemph_6db = 33;   /* 14nm default */
            c.s.pcs_tx_swing_full = 120;  /* 14nm default */ );
    }

    /* 18. Release soft reset the UPHY and UAHC logic via the UAHC controls:
        a.  USBDRD(0..1)_UAHC_GUSB2PHYCFG(0)[PHYSOFTRST] = 0
        b. USBDRD(0..1)_UAHC_GUSB3PIPECTL(0)[PHYSOFTRST] = 0
        c. USBDRD(0..1)_UAHC_GCTL[CORESOFTRESET] = 0 */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GUSB2PHYCFGX(usb_port, 0),
        c.s.physoftrst = 0);
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GUSB3PIPECTLX(usb_port, 0),
        c.s.physoftrst = 0);
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_GCTL(usb_port),
        c.s.coresoftreset = 0);

    /* 19. Configure the remaining UAHC_G* registers as needed, including
       any that were not configured in step 17.-b. */

    /* 20. Initialize the USB controller:
        a. To initialize the UAHC as a USB host controller, the application
            should perform the steps described in the xHCI specification
            (UAHC_X* registers). The xHCI sequence starts with poll for a 0 in
            USBDRD(0..1)_UAHC_USBSTS[CNR].
        b. To initialize the UAHC as a device, the application should TBD. The
            device initiation sequence starts with a device soft reset by
            setting USBDRD(0..1)_UAHC_DCTL[CSFTRST] = 1 and wait for a read
            operation to return 0. */

    return 0;
}

static int usb2_test_mode(bdk_node_t node, int usb_port, int usb2_mode)
{
    /* Set Run/Stop bit in USBCMD to zero */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_USBCMD(usb_port),
        c.s.r_s = 0);

    /* Wait for HCHalted in USBSTS to transition to 1 */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_USBDRDX_UAHC_USBSTS(usb_port), hch, ==, 1, 100000))
    {
        bdk_error("USB%d: Timeout waiting for controller halt\n", usb_port);
        return -1;
    }

    /* Set the Port Test Control field in PORTPMSC to the desired test */
    BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_PORTPMSC_20X(usb_port, 0),
        c.s.port_test_control = usb2_mode);

    /* For force enable, turn Run/Stop back on */
    if (usb2_mode == 5)
    {
        BDK_CSR_MODIFY(c, node, BDK_USBDRDX_UAHC_USBCMD(usb_port),
            c.s.r_s = 1);
    }
    return 0;
}

/**
 * Put the USB port into a specific testing mode
 *
 * @param node      Node to use
 * @param usb_port  Port to use
 * @param test_mode USB test mode
 *
 * @return Zero on success, negative on failure
 */
int bdk_usb_test_mode(bdk_node_t node, int usb_port, bdk_usb_test_t test_mode)
{
    switch (test_mode)
    {
        case BDK_USB_TEST_USB2_DISABLE:
            return usb2_test_mode(node, usb_port, 0);
        case BDK_USB_TEST_USB2_J_STATE:
            return usb2_test_mode(node, usb_port, 1);
        case BDK_USB_TEST_USB2_K_STATE:
            return usb2_test_mode(node, usb_port, 2);
        case BDK_USB_TEST_USB2_SE0_NAK:
            return usb2_test_mode(node, usb_port, 3);
        case BDK_USB_TEST_USB2_PACKET:
            return usb2_test_mode(node, usb_port, 4);
        case BDK_USB_TEST_USB2_FORCE_ENABLE:
            return usb2_test_mode(node, usb_port, 5);
        case BDK_USB_XHCI_INIT:
            if (BDK_IS_REQUIRED(USB_XHCI))
                return bdk_usb_HCInit(node, usb_port);
            break;
        case BDK_USB_XHCI_LIST_ADDRESSES:
            if (BDK_IS_REQUIRED(USB_XHCI))
                return bdk_usb_HCList(node, usb_port);
            break;
        case BDK_USB_XHCI_POLL_STATUS:
            if (BDK_IS_REQUIRED(USB_XHCI))
                return bdk_usb_HCPoll(node, usb_port,1);
            break;
        case BDK_USB_XHCI_TOGGLE_POLLING:
            if (BDK_IS_REQUIRED(USB_XHCI))
            {
                bdk_usb_togglePoll(node, usb_port, DO_TOGGLE);
                return 0;
            }
            break;
        case BDK_USB_TEST_USB2_LAST:
            break;
    }
    bdk_error("USB%d: Illegal test mode\n", test_mode);
    return -1;
}

/**
 * Convert a USB test enumeration into a string for display to the user
 *
 * @param node      Node to use
 * @param usb_port  Port to use
 * @param test_mode Mode to convert
 *
 * @return String name of test
 */
const char* bdk_usb_get_test_mode_string(bdk_node_t node, int usb_port, bdk_usb_test_t test_mode)
{
    static char pollState[64];
    switch (test_mode)
    {
        case BDK_USB_TEST_USB2_DISABLE:
            return "Disable testing";
        case BDK_USB_TEST_USB2_J_STATE:
            return "USB 2.0 J_STATE test";
        case BDK_USB_TEST_USB2_K_STATE:
            return "USB 2.0 K_STATE test";
        case BDK_USB_TEST_USB2_SE0_NAK:
            return "USB 2.0 SE0_NAK test";
        case BDK_USB_TEST_USB2_PACKET:
            return "USB 2.0 PACKET test";
        case BDK_USB_TEST_USB2_FORCE_ENABLE:
            return "USB 2.0 FORCE_ENABLE test";
        case BDK_USB_XHCI_INIT:
            return "Initialize host controller";
        case BDK_USB_XHCI_LIST_ADDRESSES:
            return "Show USB host controller state";
        case BDK_USB_XHCI_POLL_STATUS:
            return "USB hxci poll root hub status";
    	case BDK_USB_XHCI_TOGGLE_POLLING:
            if (BDK_IS_REQUIRED(USB_XHCI))
            {
                int i = bdk_usb_togglePoll(node, usb_port, DO_QUERY);
                if (i >= 0)
                {
                    snprintf(pollState, sizeof(pollState),
                        "Toggle USB Polling (currently %s)", i ? "On" : "Off");
                } else
                    return "Toggle USB Polling (NA)";
                return pollState;
            }
            return NULL;
        case BDK_USB_TEST_USB2_LAST:
            break;
    }
    return NULL;
}

