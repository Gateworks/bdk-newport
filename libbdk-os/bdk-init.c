/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include <unistd.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-ccs.h"
#include "libbdk-arch/bdk-csrs-ccu.h"
#include "libbdk-arch/bdk-csrs-gti.h"
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-mio_boot.h"
#include "libbdk-arch/bdk-csrs-rom.h"
#include "libbdk-arch/bdk-csrs-uaa.h"

uint64_t __bdk_init_reg_x0; /* The contents of X0 when this image started */
uint64_t __bdk_init_reg_x1; /* The contents of X1 when this image started */
uint64_t __bdk_init_reg_pc; /* The contents of PC when this image started */
static int64_t __bdk_alive_coremask[BDK_NUMA_MAX_NODES];

/**
 * Set the baud rate on a UART
 *
 * @param uart     uart to set
 * @param baudrate Baud rate (9600, 19200, 115200, etc)
 * @param use_flow_control
 *                 Non zero if hardware flow control should be enabled
 */
void bdk_set_baudrate(bdk_node_t node, int uart, int baudrate, int use_flow_control)
{
    /* 1.2.1 Initialization Sequence (Power-On/Hard/Cold Reset) */
    /* 1. Wait for IOI reset (srst_n) to deassert. */
    /* 2. Assert all resets:
        a. UAA reset: UCTL_CTL[UAA_RST] = 1
        b. UCTL reset: UCTL_CTL[UCTL_RST] = 1  */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart),
        c.s.uaa_rst = 1;
        c.s.uctl_rst = 1);

    /* 3. Configure the HCLK:
        a. Reset the clock dividers: UCTL_CTL[H_CLKDIV_RST] = 1.
        b. Select the HCLK frequency
            i. UCTL_CTL[H_CLKDIV] = desired value,
            ii. UCTL_CTL[H_CLKDIV_EN] = 1 to enable the HCLK.
            iii. Readback UCTL_CTL to ensure the values take effect.
        c. Deassert the HCLK clock divider reset: UCTL_CTL[H_CLKDIV_RST] = 0. */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart),
        c.s.h_clkdiv_sel = 3; /* Run at SCLK / 6, matches emulator */
        c.s.h_clk_byp_sel = 0;
        c.s.h_clk_en = 1);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart),
        c.s.h_clkdiv_rst = 0);

    /* 4. Wait 20 HCLK cycles from step 3 for HCLK to start and async fifo
       to properly reset. */
    bdk_wait(200); /* Overkill */

    /* 5. Deassert UCTL and UAHC resets:
        a. UCTL_CTL[UCTL_RST] = 0
        b. Wait 10 HCLK cycles.
        c. UCTL_CTL[UAHC_RST] = 0
        d. You will have to wait 10 HCLK cycles before accessing any
            HCLK-only registers. */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart), c.s.uctl_rst = 0);
    bdk_wait(100); /* Overkill */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart), c.s.uaa_rst = 0);
    bdk_wait(100); /* Overkill */

    /* 6. Enable conditional SCLK of UCTL by writing UCTL_CTL[CSCLK_EN] = 1. */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart), c.s.csclk_en = 1);

    /* 7. Initialize the integer and fractional baud rate divider registers
        UARTIBRD and UARTFBRD as follows:
        a. Baud Rate Divisor = UARTCLK/(16xBaud Rate) = BRDI + BRDF
        b. The fractional register BRDF, m is calculated as integer(BRDF x 64 + 0.5)
        Example calculation:
            If the required baud rate is 230400 and hclk = 4MHz then:
                Baud Rate Divisor = (4x10^6)/(16x230400) = 1.085
                This means BRDI = 1 and BRDF = 0.085.
                Therefore, fractional part, BRDF = integer((0.085x64)+0.5) = 5
                Generated baud rate divider = 1+5/64 = 1.078 */
    uint64_t base_clock_rate;
    if (bdk_is_model(OCTEONTX_CN8XXX)) /* CN8XXX uses SCLK */
        base_clock_rate = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    else /* CN9XXX uses 100Mhz main reference */
        base_clock_rate = bdk_clock_get_rate(node, BDK_CLOCK_MAIN_REF);
    uint64_t divisor_x_64 = base_clock_rate / (baudrate * 16 * 6 / 64);
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        /* The hardware emulator currently fixes the uart at a fixed rate */
        divisor_x_64 = 64;
    }
    BDK_CSR_MODIFY(c, node, BDK_UAAX_IBRD(uart),
        c.s.baud_divint = divisor_x_64 >> 6);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_FBRD(uart),
        c.s.baud_divfrac = divisor_x_64 & 0x3f);

    /* 8. Program the line control register UAA(0..1)_LCR_H and the control
       register UAA(0..1)_CR */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_LCR_H(uart),
        c.s.sps = 0; /* No parity */
        c.s.wlen = 3; /* 8 bits */
        c.s.fen = 1; /* FIFOs enabled */
        c.s.stp2 = 0; /* Use one stop bit, not two */
        c.s.eps = 0; /* No parity */
        c.s.pen = 0; /* No parity */
        c.s.brk = 0); /* Don't send a break */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_CR(uart),
        c.s.ctsen = use_flow_control;
        c.s.rtsen = use_flow_control;
        c.s.out1 = 1; /* Drive data carrier detect */
        c.s.rts = 0; /* Don't override RTS */
        c.s.dtr = 0; /* Don't override DTR */
        c.s.rxe = 1; /* Enable receive */
        c.s.txe = 1; /* Enable transmit */
        c.s.lbe = 0; /* Disable loopback */
        c.s.uarten = 1); /* Enable uart */
}

/**
 * First C code run when a BDK application starts. It is called by bdk-start.S.
 *
 * @param image_crc A CRC32 of the entire image before any variables might have been updated by C.
 *                  This should match the CRC32 in the image header.
 * @param reg_x0    The contents of the X0 register when the image started. In images loaded after
 *                  the boot stub, this contains a "environment" string containing "BOARD=xxx". The
 *                  use of this is deprecated as it has been replaced with a expandable device tree
 *                  in X1.
 * @param reg_x1    The contents of the X1 register when the image started. For all images after the
 *                  boot stub, this contains a physical address of a device tree in memory. This
 *                  should be used by all images to identify and configure the board we are running
 *                  on.
 * @param reg_pc    This is the PC the code started at before relocation. This is useful for
 *                  the first stage to determine if it from trusted or non-trusted code.
 */
void __bdk_init(uint32_t image_crc, uint64_t reg_x0, uint64_t reg_x1, uint64_t reg_pc) __attribute((noreturn));
void __bdk_init(uint32_t image_crc, uint64_t reg_x0, uint64_t reg_x1, uint64_t reg_pc)
{
    extern void __bdk_exception_current_el_sync_sp0();
    BDK_MSR(VBAR_EL3, __bdk_exception_current_el_sync_sp0);
    BDK_MSR(VBAR_EL2, __bdk_exception_current_el_sync_sp0);
    BDK_MSR(VBAR_EL1, __bdk_exception_current_el_sync_sp0);

    /* Use OcteonTX specific function to change memory to normal instead
       of device attributes. DCVA47=1 makes unmapped addresses behave as
       non-shared memory (not inner or outer shared in ARM speak) */
    bdk_ap_cvmmemctl0_el1_t cvmmemctl0_el1;
    BDK_MRS(s3_0_c11_c0_4, cvmmemctl0_el1.u);
    cvmmemctl0_el1.s.dcva47 = 1;
    BDK_MSR(s3_0_c11_c0_4, cvmmemctl0_el1.u);


    /* Setup running with no mmu */
    bdk_ap_sctlr_el3_t sctlr_el3;
    BDK_MRS(SCTLR_EL3, sctlr_el3.u);
    sctlr_el3.s.wxn = 0; /* No write perm changes */
    sctlr_el3.s.i = 1;  /* Enable Icache */
    sctlr_el3.s.sa = 1; /* Enable stack alignment checking */
    sctlr_el3.s.cc = 1; /* Enable Dcache */
    sctlr_el3.s.aa = 0; /* Allow unaligned accesses */
    sctlr_el3.s.m = 0; /* Disable MMU */
    BDK_MSR(SCTLR_EL3, sctlr_el3.u);

    bdk_node_t node = bdk_numa_local();
    bdk_numa_set_exists(node);

#if 0 // NEWPORT
    /* Default color, Reset scroll region and goto bottom */
    static const char BANNER_1[] = "\33[0m\33[1;r\33[100;1H"
                                   "\n\n\nOcteonTX SOC\n";
    static const char BANNER_2[] = "Locking L2 cache\n";
    static const char BANNER_CRC_RIGHT[] = "PASS: CRC32 verification\n";
    static const char BANNER_CRC_WRONG[] = "FAIL: CRC32 verification\n";
    static const char BANNER_3[] = "Transferring to thread scheduler\n";
#endif

    BDK_MSR(TPIDR_EL3, 0);

    if (bdk_is_boot_core())
    {
        /* Initialize the platform */
        __bdk_platform_init();

        /* Make sure the global watchdog is disabled, requested by the SDK team */
        BDK_CSR_MODIFY(c, node, BDK_GTI_WCX_WCS(0), c.s.en = 0);
        BDK_CSR_MODIFY(c, node, BDK_GTI_WCX_WCS(1), c.s.en = 0);

        /* Enable the timer */
        BDK_MSR(CNTFRQ_EL0, BDK_GTI_RATE); /* Needed for Asim */
        bdk_clock_setup(node);

        /* Only setup the uarts if they haven't been already setup */
        BDK_CSR_INIT(uctl_ctl0, node, BDK_UAAX_UCTL_CTL(0));
        if (!uctl_ctl0.s.h_clk_en)
            bdk_set_baudrate(node, 0, BDK_UART_BAUDRATE, 0);
        BDK_CSR_INIT(uctl_ctl1, node, BDK_UAAX_UCTL_CTL(1));
        if (!uctl_ctl1.s.h_clk_en)
            bdk_set_baudrate(node, 1, BDK_UART_BAUDRATE, 0);

        __bdk_fs_init_early();
#if 0 // NEWPORT
        if (BDK_SHOW_BOOT_BANNERS)
            write(1, BANNER_1, sizeof(BANNER_1)-1);
#endif

        /* Only lock L2 if DRAM isn't initialized */
        if (!__bdk_is_dram_enabled(node))
        {
#if 0 // NEWPORT
            if (BDK_TRACE_ENABLE_INIT)
                write(1, BANNER_2, sizeof(BANNER_2)-1);
#endif
            /* Lock the work cache area */
            uint64_t top_of_cache = bdk_dram_get_top_of_cache();
            bdk_l2c_lock_mem_region(node, bdk_numa_get_address(node, 0), top_of_cache);
            /* The locked region isn't considered dirty by L2. Do read
               read/write of each cache line to force each to be dirty. This
               is needed across the whole line to make sure the L2 dirty bits
               are all up to date */
            volatile uint64_t *ptr = bdk_phys_to_ptr(bdk_numa_get_address(node, 8));
            /* The above pointer got address 8 to avoid NULL pointer checking
               in bdk_phys_to_ptr(). Correct it here */
            ptr--;
            uint64_t *end = bdk_phys_to_ptr(bdk_numa_get_address(node, top_of_cache));
            while (ptr < end)
            {
                *ptr = *ptr;
                ptr++;
            }
            if (bdk_is_model(OCTEONTX_CN8XXX))
            {
                /* The above locking will cause L2 to load zeros without DRAM setup.
                    This will cause L2C_TADX_INT[rddislmc], which we suppress below */
                BDK_CSR_DEFINE(l2c_tadx_int, BDK_L2C_TADX_INT_W1C(0));
                l2c_tadx_int.u = 0;
                l2c_tadx_int.s.wrdislmc = 1;
                l2c_tadx_int.s.rddislmc = 1;
                l2c_tadx_int.s.rdnxm = 1;

                BDK_CSR_WRITE(node, BDK_L2C_TADX_INT_W1C(0), l2c_tadx_int.u);
                if (bdk_is_model(OCTEONTX_CN83XX))
                {
                    BDK_CSR_WRITE(node, BDK_L2C_TADX_INT_W1C(1), l2c_tadx_int.u);
                    BDK_CSR_WRITE(node, BDK_L2C_TADX_INT_W1C(2), l2c_tadx_int.u);
                    BDK_CSR_WRITE(node, BDK_L2C_TADX_INT_W1C(3), l2c_tadx_int.u);
                }
            }
            else
            {
                /* The above locking will cause CCU to load zeros
                    without DRAM setup. This will cause
                    CCUX_TADX_INT_W1C[rdnxm], which we suppress below */
                BDK_CSR_DEFINE(tadx_int_w1c, BDK_CCUX_TADX_INT_W1C(0,0));
                tadx_int_w1c.u = 0;
                tadx_int_w1c.s.rdnxm = 1;

                BDK_CSR_INIT(ccs_const, node, BDK_CCS_CONST);
                for (int cluster = 0; cluster < ccs_const.s.clu; cluster++)
                    for (int tad = 0; tad < ccs_const.s.tadclu; tad++)
                        BDK_CSR_WRITE(node, BDK_CCUX_TADX_INT_W1C(cluster, tad), tadx_int_w1c.u);
            }
        }

        /* Validate the image CRC */
        extern void _start();
#if 0 // NEWPORT
        uint32_t *ptr_crc32 = (uint32_t *)(_start + 16);
        uint32_t correct_crc = bdk_le32_to_cpu(*ptr_crc32);
        if (correct_crc == image_crc)
            write(1, BANNER_CRC_RIGHT, sizeof(BANNER_CRC_RIGHT) - 1);
        else
            write(1, BANNER_CRC_WRONG, sizeof(BANNER_CRC_WRONG) - 1);

        if (BDK_TRACE_ENABLE_INIT)
            write(1, BANNER_3, sizeof(BANNER_3)-1);
#endif
        bdk_thread_initialize();
    }

    /* Enable the core timer */
    BDK_MSR(CNTFRQ_EL0, BDK_GTI_RATE); /* Needed for Asim */
    bdk_ap_cntps_ctl_el1_t cntps_ctl_el1;
    cntps_ctl_el1.u = 0;
    cntps_ctl_el1.s.imask = 1;
    cntps_ctl_el1.s.enable = 1;
    BDK_MSR(CNTPS_CTL_EL1, cntps_ctl_el1.u);

    /* Setup an exception stack in case we crash */
    int EX_STACK_SIZE = 16384;
    void *exception_stack = malloc(EX_STACK_SIZE);
    extern void __bdk_init_exception_stack(void *ptr);
    __bdk_init_exception_stack(exception_stack + EX_STACK_SIZE);

    bdk_atomic_add64(&__bdk_alive_coremask[node], bdk_core_to_mask());

    /* Record our input registers for use later */
    __bdk_init_reg_x0 = reg_x0;
    __bdk_init_reg_x1 = reg_x1;
    __bdk_init_reg_pc = reg_pc;
    bdk_thread_first(__bdk_init_main, 0, NULL, 0);
}

/**
 * Call this function to take secondary cores out of reset and have
 * them start running threads
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param coremask Cores to start. Zero is a shortcut for all.
 *
 * @return Zero on success, negative on failure.
 */
int bdk_init_cores(bdk_node_t node, uint64_t coremask)
{
    extern void __bdk_start_cores();
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        /* Write the address of the main entry point */
        BDK_TRACE(INIT, "N%d: Setting address for boot jump\n", node);
        BDK_CSR_WRITE(node, BDK_MIO_BOOT_AP_JUMP, (uint64_t)__bdk_start_cores);
    }
    else
    {
        BDK_TRACE(INIT, "N%d: Setting ROM boot code\n", node);
        /* Assembly for ROM memory:
            1f 71 08 d5     ic  ialluis
            a0 00 00 58     ldr x0, #20
            c1 00 00 58     ldr x1, #24
            00 b0 18 d5     msr S3_0_C11_C0_0, x0
            df 3f 03 d5     isb
            20 00 1f d6     br  x1
            1f 20 03 d5     nop # Replaced with AP_CVMCTL_EL1 value
            1f 20 03 d5     nop
            1f 20 03 d5     nop # Repalced with branch_addr
            1f 20 03 d5     nop
            Memory is little endain, so 64 bit constants have the first
            instruction in the low word */
        bdk_ap_cvmctl_el1_t ap_cvmctl_el1;
        BDK_MRS(s3_0_c11_c0_0, ap_cvmctl_el1.u);
        BDK_CSR_WRITE(node, BDK_ROM_MEMX(0), 0x580000a0d508711f);
        BDK_CSR_WRITE(node, BDK_ROM_MEMX(1), 0xd518b000580000c1);
        BDK_CSR_WRITE(node, BDK_ROM_MEMX(2), 0xd61f0020d5033fdf);
        BDK_CSR_WRITE(node, BDK_ROM_MEMX(3), ap_cvmctl_el1.u);
        BDK_CSR_WRITE(node, BDK_ROM_MEMX(4), (uint64_t)__bdk_start_cores);
    }

    /* Choose all cores by default */
    if (coremask == 0)
        coremask = -1;

    /* Limit to the cores that aren't already running */
    coremask &= ~__bdk_alive_coremask[node];

    /* Limit to the cores that are specified in configuration menu */
    uint64_t config_coremask = bdk_config_get_int(BDK_CONFIG_COREMASK);
    if (config_coremask)
        coremask &= config_coremask;

    /* Limit to the cores that exist */
    coremask &= (1ull<<bdk_get_num_cores(node)) - 1;

    uint64_t reset = BDK_CSR_READ(node, BDK_RST_PP_RESET);
    BDK_TRACE(INIT, "N%d: Cores currently in reset: 0x%lx\n", node, reset);
    uint64_t need_reset_off = reset & coremask;
    if (need_reset_off)
    {
        BDK_TRACE(INIT, "N%d: Taking cores out of reset (0x%lx)\n", node, need_reset_off);
        BDK_CSR_WRITE(node, BDK_RST_PP_RESET, reset & ~need_reset_off);
        /* Wait for cores to finish coming out of reset */
        bdk_wait_usec(1);
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_RST_PP_PENDING, pend, ==, 0, 100000))
            bdk_error("Timeout waiting for reset pending to clear");
    }

    BDK_TRACE(INIT, "N%d: Wait up to 1s for the cores to boot\n", node);
    uint64_t timeout = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) + bdk_clock_get_count(BDK_CLOCK_TIME);
    while ((bdk_clock_get_count(BDK_CLOCK_TIME) < timeout) && ((bdk_atomic_get64(&__bdk_alive_coremask[node]) & coremask) != coremask))
    {
        /* Tight spin, no thread schedules */
    }

    if ((bdk_atomic_get64(&__bdk_alive_coremask[node]) & coremask) != coremask)
    {
        bdk_error("Node %d: Some cores failed to start. Alive mask 0x%lx, requested 0x%lx\n",
            node, __bdk_alive_coremask[node], coremask);
        return -1;
    }
    BDK_TRACE(INIT, "N%d: All cores booted\n", node);
    return 0;
}

/**
 * Put cores back in reset and power them down
 *
 * @param node     Node to update
 * @param coremask Each bit will be a core put in reset. Cores already in reset are unaffected
 *
 * @return Zero on success, negative on failure
 */
int bdk_reset_cores(bdk_node_t node, uint64_t coremask)
{
    extern void __bdk_reset_thread(int arg1, void *arg2);

    /* Limit to the cores that exist */
    coremask &= (1ull<<bdk_get_num_cores(node)) - 1;

    /* Update which cores are in reset */
    uint64_t reset = BDK_CSR_READ(node, BDK_RST_PP_RESET);
    BDK_TRACE(INIT, "N%d: Cores currently in reset: 0x%lx\n", node, reset);
    coremask &= ~reset;
    BDK_TRACE(INIT, "N%d: Cores to put into reset: 0x%lx\n", node, coremask);

    /* Check if everything is already done */
    if (coremask == 0)
        return 0;

    int num_cores = bdk_get_num_cores(node);
    for (int core = 0; core < num_cores; core++)
    {
        uint64_t my_mask = 1ull << core;
        /* Skip cores not in mask */
        if ((coremask & my_mask) == 0)
            continue;
        BDK_TRACE(INIT, "N%d: Telling core %d to go into reset\n", node, core);
        if (bdk_thread_create(node, my_mask, __bdk_reset_thread, 0, NULL, 0))
        {
            bdk_error("Failed to create thread for putting core in reset");
            continue;
        }
        /* Clear the core in the alive mask */
        bdk_atomic_fetch_and_bclr64_nosync((uint64_t*)&__bdk_alive_coremask[node], my_mask);
    }

    BDK_TRACE(INIT, "N%d: Waiting for all reset bits to be set\n", node);
    uint64_t timeout = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) + bdk_clock_get_count(BDK_CLOCK_TIME);
    while (bdk_clock_get_count(BDK_CLOCK_TIME) < timeout)
    {
        reset = BDK_CSR_READ(node, BDK_RST_PP_RESET);
        if ((reset & coremask) == coremask)
            break;
        bdk_thread_yield();
    }

    BDK_TRACE(INIT, "N%d: Cores now in reset: 0x%lx\n", node, reset);

    return ((reset & coremask) == coremask) ? 0 : -1;
}

/**
 * Call this function to take secondary nodes and cores out of
 * reset and have them start running threads
 *
 * @param skip_cores If non-zero, cores are not started. Only the nodes are setup
 * @param ccpi_sw_gbaud
 *                   If CCPI is in software mode, this is the speed the CCPI QLMs will be configured
 *                   for
 *
 * @return Zero on success, negative on failure.
 */
int bdk_init_nodes(int skip_cores, int ccpi_sw_gbaud)
{
    int result = 0;

    /* Start cores on all node unless it was disabled */
    if (!skip_cores)
    {
        for (bdk_node_t node=0; node<BDK_NUMA_MAX_NODES; node++)
        {
            if (bdk_numa_exists(node))
                result |= bdk_init_cores(node, 0);
        }
    }
    return result;
}

/**
 * Get the coremask of the cores actively running the BDK. Doesn't count cores
 * that aren't booted.
 *
 * @param node   Node to coremask the count for
 *
 * @return 64bit bitmask
 */
uint64_t bdk_get_running_coremask(bdk_node_t node)
{
    return __bdk_alive_coremask[node];
}

/**
 * Return the number of cores actively running in the BDK for the given node.
 * Not an inline so it can be called from LUA.
 *
 * @param node   Node to get the core count for
 *
 * @return Number of cores running. Doesn't count cores that aren't booted
 */
int bdk_get_num_running_cores(bdk_node_t node)
{
    return __builtin_popcountl(bdk_get_running_coremask(node));
}

