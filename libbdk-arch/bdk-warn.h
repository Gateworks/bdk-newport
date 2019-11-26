/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for reporting errors and warnings.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup stdio Standard IO related functions
 * @{
 */

extern void __bdk_die(void) __attribute__ ((noreturn));
extern void bdk_fatal(const char *format, ...) __attribute__ ((noreturn, format(printf, 1, 2)));
extern void bdk_error(const char *format, ...) __attribute__ ((format(printf, 1, 2)));
extern void bdk_warn(const char *format, ...) __attribute__ ((format(printf, 1, 2)));
extern void __bdk_trace_printf(const char *format, ...) __attribute__ ((format(printf, 1, 2)));
#define bdk_warn_if(expression, format, ...) if (bdk_unlikely(expression)) bdk_warn(format, ##__VA_ARGS__)

/* The following defines control detailed tracing of various parts of the
   BDK. Each one can be enabled(1) or disabled(0) independently. These
   should be disabled unless you are trying to debug something specific */

typedef enum
{
    BDK_TRACE_ENABLE_BGX,               /* BGX networking block */
    BDK_TRACE_ENABLE_DRAM,              /* DRAM initialization */
    BDK_TRACE_ENABLE_DRAM_TEST,         /* DRAM test code */
    BDK_TRACE_ENABLE_INIT,              /* Early initialization, before main() */
    BDK_TRACE_ENABLE_ECAM,              /* ECAM initialization */
    BDK_TRACE_ENABLE_QLM,               /* QLM related debug */
    BDK_TRACE_ENABLE_EMMC,              /* eMMC related debug */
    BDK_TRACE_ENABLE_PCIE,              /* PCIe link init */
    BDK_TRACE_ENABLE_PCIE_CONFIG,       /* PCIe config space reads / writes */
    BDK_TRACE_ENABLE_SATA,              /* SATA/AHCI related debug */
    BDK_TRACE_ENABLE_CCPI,              /* Multi-node related debug */
    BDK_TRACE_ENABLE_FATFS,             /* FatFs related debug */
    BDK_TRACE_ENABLE_MPI,               /* MPI related debug */
    BDK_TRACE_ENABLE_ENV,               /* Environment variables related debug */
    BDK_TRACE_ENABLE_FPA,               /* Free Pool Allocator */
    BDK_TRACE_ENABLE_PKI,               /* Packet Input */
    BDK_TRACE_ENABLE_PKO,               /* Packet Output */
    BDK_TRACE_ENABLE_SSO,               /* SSO */
    BDK_TRACE_ENABLE_DEVICE,            /* ECAM based device framework */
    BDK_TRACE_ENABLE_DEVICE_SCAN,       /* ECAM based device scanning detail */
    BDK_TRACE_ENABLE_NIC,               /* Virtual NIC */
    BDK_TRACE_ENABLE_FDT_OS,            /* Device tree passed to OS */
    BDK_TRACE_ENABLE_USB_XHCI,          /* USB XHCI block */
    BDK_TRACE_ENABLE_CCS_DECODE,        /* Conversion Between LMC and Physical Addressing */
    __BDK_TRACE_ENABLE_LAST,            /* Must always be last value */
} bdk_trace_enable_t;

/* See bdk-config.c to change the trace level for before config files are loaded */
extern uint64_t bdk_trace_enables;

/**
 * Macro for low level tracing of BDK functions. When enabled,
 * these translate to printf() calls. The "area" is a string
 * that is appended to "BDK_TRACE_ENABLE_" to figure out which
 * enable macro to use. The macro expects a ';' after it.
 */
#define BDK_TRACE(area, format, ...) do {                       \
    if (bdk_trace_enables & (1ull << BDK_TRACE_ENABLE_##area))  \
        __bdk_trace_printf(#area ": " format, ##__VA_ARGS__);   \
} while (0)

/** @} */
