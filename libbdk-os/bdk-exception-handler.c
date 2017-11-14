/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-ap.h"

#define ENABLE_DECODE 0

typedef struct
{
    uint64_t gpr[32]; /* SP is x31 */
    __uint128_t fpr[32];
} except_regs_t;

#if ENABLE_DECODE
static const char *EC_STRING[64] = {
    [0x0] = "UNKNOWN",
    [0x1] = "WFE_WFI",
    [0x3] = "MCR_CP15",
    [0x4] = "MCRR_CP15",
    [0x5] = "MCR_CP14",
    [0x6] = "LDC_CP15",
    [0x7] = "ACCESS_SIMD_FP",
    [0x8] = "MRC_CP10",
    [0xc] = "MCRR_CP14",
    [0xe] = "ILLEGAL_INSTR_STATE",
    [0x11] = "SVC_AARCH32",
    [0x12] = "HVC_AARCH32",
    [0x13] = "SMC_AARCH32",
    [0x15] = "SVC_AARCH64",
    [0x16] = "HVC_AARCH64",
    [0x17] = "SMC_AARCH64",
    [0x18] = "MSR_AARCH64",
    [0x20] = "INSTR_ABORT_LOWER_EL",
    [0x21] = "INSTR_ABORT_CURRENT_EL",
    [0x22] = "PC_ALIGNMENT",
    [0x24] = "DATA_ABORT_LOWER_EL",
    [0x25] = "DATA_ABORT_CURRENT_EL",
    [0x26] = "STACK_ALIGNMENT",
    [0x28] = "FLOATING_POINT_AARCH32",
    [0x2c] = "FLOATING_POINT_AARCH64",
    [0x2f] = "SERROR",
    [0x30] = "DEBUG_BP_LOWER_EL",
    [0x31] = "DEBUG_BP_CURRENT_EL",
    [0x32] = "DEBUG_STEP_LOWER_EL",
    [0x33] = "DEBUG_STEP_CURRENT_EL",
    [0x34] = "DEBUG_WP_LOWER_EL",
    [0x35] = "DEBUG_WP_CURRENT_EL",
    [0x38] = "DEBUG_BKPT",
    [0x3a] = "DEBUG_A32_VECTOR",
    [0x3c] = "DEBUG_BRK",
};

static const char *FCS_STRING[64] = {
    [0x00] = "ADDRESS_SIZE_L0",
    [0x01] = "ADDRESS_SIZE_L1",
    [0x02] = "ADDRESS_SIZE_L2",
    [0x03] = "ADDRESS_SIZE_L3",
    [0x04] = "TRANSLATION_L0",
    [0x05] = "TRANSLATION_L1",
    [0x06] = "TRANSLATION_L2",
    [0x07] = "TRANSLATION_L3",
    [0x08] = "ACCESS_FLAG_L0",
    [0x09] = "ACCESS_FLAG_L1",
    [0x0a] = "ACCESS_FLAG_L2",
    [0x0b] = "ACCESS_FLAG_L3",
    [0x0c] = "PERMISSION_L0",
    [0x0d] = "PERMISSION_L1",
    [0x0e] = "PERMISSION_L2",
    [0x0f] = "PERMISSION_L3",
    [0x10] = "EXTERNAL_ABORT",
    [0x11] = "ASYNC_EXTERNAL_ABORT",
    [0x14] = "WALK_ABORT_L0",
    [0x15] = "WALK_ABORT_L1",
    [0x16] = "WALK_ABORT_L2",
    [0x17] = "WALK_ABORT_L3",
    [0x18] = "MEMORY_PARITY",
    [0x1c] = "WALK_PARITY_L0",
    [0x1d] = "WALK_PARITY_L1",
    [0x1e] = "WALK_PARITY_L2",
    [0x1f] = "WALK_PARITY_L3",
    [0x21] = "ALIGNMENT",
    [0x22] = "DEBUG_EVENT",
    [0x30] = "TLB_CONFLICT",
    [0x34] = "LOCKDOWN",
    [0x35] = "IMP_DEFIEND_1",
    [0x3a] = "IMP_DEFINED_2",
    [0x3d] = "SECTION_DOMAIN",
    [0x3e] = "PAGE_DOMAIN",
};
#endif

void __bdk_exception_handler(except_regs_t *exc)
{
    const char *BANNER = "**********************************************************************************\r\n";
    uint64_t pc;
    BDK_MRS(ELR_EL3, pc);
    bdk_ap_esr_elx_t esr;
    BDK_MRS(ESR_EL3, esr.u);
    bdk_ap_far_elx_t far;
    BDK_MRS(FAR_EL3, far.u);
    uint64_t thread_id;
    BDK_MRS(TPIDR_EL3, thread_id);

    bdk_dbg_uart_str(BANNER);

    bdk_dbg_uart_str("Node ");
    bdk_dbg_uart_char(bdk_numa_local() + '0');
    bdk_dbg_uart_str(", Core ");
    int core = bdk_get_core_num();
    bdk_dbg_uart_char(core / 10 + '0');
    bdk_dbg_uart_char(core % 10 + '0');
    bdk_dbg_uart_str(": Unhandled Exception\r\n");

    bdk_dbg_uart_str("ESR EC=");
    bdk_dbg_uart_hex(esr.s.ec);
    bdk_dbg_uart_char('(');
#if ENABLE_DECODE
    bdk_dbg_uart_str(EC_STRING[esr.s.ec] ? EC_STRING[esr.s.ec] : "Unknown");
#endif
    bdk_dbg_uart_str(") ISS=");
    bdk_dbg_uart_hex(esr.s.iss);
    if ((esr.s.ec == 0x24) || (esr.s.ec == 0x25))
    {
        bdk_dbg_uart_char('(');
        if (esr.s.iss & (1<<24)) bdk_dbg_uart_str(" VALID");
        if (esr.s.iss & (1<<21)) bdk_dbg_uart_str(" SIGN_EXTEND");
        if (esr.s.iss & (1<<15)) bdk_dbg_uart_str(" 64BIT");
        if (esr.s.iss & (1<<14)) bdk_dbg_uart_str(" ACQUIRE");
        if (esr.s.iss & (1<<9)) bdk_dbg_uart_str(" EXTERNAL");
        if (esr.s.iss & (1<<8)) bdk_dbg_uart_str(" CACHE");
        if (esr.s.iss & (1<<7)) bdk_dbg_uart_str(" S1PTW");
        if (esr.s.iss & (1<<6)) bdk_dbg_uart_str(" WRITE");
#if ENABLE_DECODE
        if (FCS_STRING[esr.s.iss & 0x3f])
        {
            bdk_dbg_uart_char(' ');
            bdk_dbg_uart_str(FCS_STRING[esr.s.iss & 0x3f]);
        }
#endif
        bdk_dbg_uart_char(')');
    }
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str(BANNER);

    bdk_dbg_uart_str("pc : ");
    bdk_dbg_uart_hex(pc);
    bdk_dbg_uart_str("    esr: ");
    bdk_dbg_uart_hex(esr.u);
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str("far: ");
    bdk_dbg_uart_hex(far.u);
    bdk_dbg_uart_str(" thread: ");
    bdk_dbg_uart_hex(thread_id);
    bdk_dbg_uart_str("\r\n");

    for (int reg=0; reg<16; reg++)
    {
        bdk_dbg_uart_char('x');
        bdk_dbg_uart_char(reg / 10 + '0');
        bdk_dbg_uart_char(reg % 10 + '0');
        bdk_dbg_uart_str(": ");
        bdk_dbg_uart_hex(exc->gpr[reg]);
        bdk_dbg_uart_str("    x");
        bdk_dbg_uart_char((reg+16) / 10 + '0');
        bdk_dbg_uart_char((reg+16) % 10 + '0');
        bdk_dbg_uart_str(": ");
        bdk_dbg_uart_hex(exc->gpr[reg+16]);
        bdk_dbg_uart_str("\r\n");
    }
    bdk_dbg_uart_str("\r\n");

    for (int reg=0; reg<16; reg++)
    {
        bdk_dbg_uart_char('q');
        bdk_dbg_uart_char(reg / 10 + '0');
        bdk_dbg_uart_char(reg % 10 + '0');
        bdk_dbg_uart_str(": ");
        bdk_dbg_uart_hex((uint64_t)(exc->fpr[reg] >> 64));
        bdk_dbg_uart_char('_');
        bdk_dbg_uart_hex((uint64_t)exc->fpr[reg]);
        bdk_dbg_uart_str("  q");
        bdk_dbg_uart_char((reg+16) / 10 + '0');
        bdk_dbg_uart_char((reg+16) % 10 + '0');
        bdk_dbg_uart_str(": ");
        bdk_dbg_uart_hex((uint64_t)(exc->fpr[reg+16] >> 64));
        bdk_dbg_uart_char('_');
        bdk_dbg_uart_hex((uint64_t)exc->fpr[reg+16]);
        bdk_dbg_uart_str("\r\n");
    }
    bdk_dbg_uart_str("\r\n");

    uint64_t *stack = (uint64_t *)exc->gpr[31];
    for (int i = 0; i < 16; i++)
    {
        bdk_dbg_uart_str("stack[");
        bdk_dbg_uart_hex((uint64_t)stack);
        bdk_dbg_uart_str("] = ");
        bdk_dbg_uart_hex(*stack);
        bdk_dbg_uart_str("\r\n");
        stack++;
    }
    bdk_dbg_uart_str(BANNER);
    __bdk_die();
}
