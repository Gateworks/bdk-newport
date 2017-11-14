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
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-fusf.h"

/**
 * Read a byte of fuse data
 * @param byte_addr   address to read
 *
 * @return fuse value: 0 or 1
 */
static uint8_t bdk_fuse_read_byte(bdk_node_t node, int byte_addr)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
    {
        bdk_mio_fus_rcmd_t read_cmd;

        /* In CN8XXX fuses take a byte address, not a 128 bit bank */
        read_cmd.u = 0;
        read_cmd.s.addr = byte_addr;
        read_cmd.s.addr_hi = byte_addr >> 8;
        read_cmd.s.pend = 1;
        BDK_CSR_WRITE(node, BDK_MIO_FUS_RCMD, read_cmd.u);
        do
        {
            read_cmd.u = BDK_CSR_READ(node, BDK_MIO_FUS_RCMD);
        } while (read_cmd.s.pend);
        return read_cmd.s.dat;
    }
    else
    {
        /* Use the cached fuse access */
        uint64_t dat = BDK_CSR_READ(node, BDK_FUS_CACHEX(byte_addr >> 3));
        dat >>= (byte_addr & 7) << 3;
        return dat & 0xff;
    }
}


/**
 * Read a single fuse bit
 *
 * @param fuse   Fuse number (0-1024)
 *
 * @return fuse value: 0 or 1
 */
int bdk_fuse_read(bdk_node_t node, int fuse)
{
    return((bdk_fuse_read_byte(node, fuse >> 3) >> (fuse & 0x7)) & 1);
}

/**
 * Read a range of fuses
 *
 * @param node   Node to read from
 * @param fuse   Fuse number
 * @param width  Number of fuses to read, max of 64
 *
 * @return Fuse value
 */
uint64_t bdk_fuse_read_range(bdk_node_t node, int fuse, int width)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        bdk_fatal("bdk_fuse_read_range not implemented for CN8XXX\n");

    int first = fuse >> 6;
    int last = (fuse + width - 1) >> 6;
    uint64_t dat = BDK_CSR_READ(node, BDK_FUS_CACHEX(first));
    dat >>= fuse & 63;
    if (first != last)
    {
        uint64_t dat2 = BDK_CSR_READ(node, BDK_FUS_CACHEX(last));
        dat2 <<= 64 - (fuse & 63);
        dat |= dat2;
    }
    return dat & bdk_build_mask(width);
}

/**
 * Soft blow a fuse. Soft blown fuses keep there new value over soft resets, but
 * not power cycles.
 *
 * @param node   Node to blow
 * @param fuse   Fuse to blow
 *
 * @return Zero on success, negative on failure
 */
int bdk_fuse_soft_blow(bdk_node_t node, int fuse)
{
    /* Select the fuse bank. there are 128 fuses per bank */
    BDK_CSR_WRITE(node, BDK_MIO_FUS_WADR, fuse / 128);

    /* Select the fuse to program in the bank */
    int index = fuse & 127;
    if (index < 64)
    {
        BDK_CSR_WRITE(node, BDK_MIO_FUS_BNK_DATX(0), 1ull << index);
        BDK_CSR_WRITE(node, BDK_MIO_FUS_BNK_DATX(1), 0);
    }
    else
    {
        BDK_CSR_WRITE(node, BDK_MIO_FUS_BNK_DATX(0), 0);
        BDK_CSR_WRITE(node, BDK_MIO_FUS_BNK_DATX(1), 1ull << (index - 64));
    }

    /* Set to do a soft blow */
    BDK_CSR_DEFINE(fus_prog, BDK_MIO_FUS_PROG);
    fus_prog.u = 0;
    fus_prog.s.sft = 1;
    BDK_CSR_WRITE(node, BDK_MIO_FUS_PROG, fus_prog.u);

    /* Do the actual program */
    fus_prog.s.prog = 1;
    BDK_CSR_WRITE(node, BDK_MIO_FUS_PROG, fus_prog.u);

    /* Wait for the program to complete. We don't use timeouts because this
       code can run without the GTI timer */
    do
    {
        fus_prog.u = BDK_CSR_READ(node, BDK_MIO_FUS_PROG);
    } while (fus_prog.s.prog);

    /* Read the fuse to make sure it was really soft blown */
    if (bdk_fuse_read(node, fuse) == 0)
    {
        bdk_error("N%d: Soft blowing fuse %d failed\n", node, fuse);
        return -1;
    }
    return 0;
}

/**
 * Read a single fuse bit from the field set (FUSF)
 *
 * @param fuse   Fuse number (0-1024)
 *
 * @return fuse value: 0 or 1
 */
int bdk_fuse_field_read(bdk_node_t node, int fuse)
{
    bdk_fusf_rcmd_t read_cmd;

    read_cmd.u = 0;
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
    {
        /* In CN8XXX fuses take a byte address, not a 128 bit bank */
        read_cmd.cn8.addr = fuse >> 3;
        read_cmd.cn8.addr_hi = fuse >> 9;
    }
    else
    {
        /* In CN9XXX fuses take a 128 bit bank, not a byte address */
        read_cmd.cn9.addr = fuse >> 7;
    }
    read_cmd.s.pend = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_RCMD, read_cmd.u);
    do
    {
        read_cmd.u = BDK_CSR_READ(node, BDK_FUSF_RCMD);
    } while (read_cmd.s.pend);

    int index = fuse & 0x7f;
    uint64_t dat = BDK_CSR_READ(node, BDK_FUSF_BNK_DATX(index >> 6));
    return (dat >> (index & 0x3f)) & 1;
}

/**
 * Soft blow a fuse in the field set (FUSF). Soft blown fuses
 * keep there new value over soft resets, but not power cycles.
 *
 * @param node   Node to blow
 * @param fuse   Fuse to blow
 *
 * @return Zero on success, negative on failure
 */
int bdk_fuse_field_soft_blow(bdk_node_t node, int fuse)
{
    /* Select the fuse bank. there are 128 fuses per bank */
    BDK_CSR_WRITE(node, BDK_FUSF_WADR, fuse / 128);

    /* Select the fuse to program in the bank */
    int index = fuse & 127;
    if (index < 64)
    {
        BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(0), 1ull << index);
        BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(1), 0);
    }
    else
    {
        BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(0), 0);
        BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(1), 1ull << (index - 64));
    }

    /* Set to do a soft blow */
    BDK_CSR_DEFINE(fus_prog, BDK_FUSF_PROG);
    fus_prog.u = 0;
    fus_prog.s.sft = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, fus_prog.u);

    /* Do the actual program */
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        fus_prog.cn81xx.prog = 1;
    else
        fus_prog.cn9.prog = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, fus_prog.u);

    /* Wait for the program to complete. We don't use timeouts because this
       code can run without the GTI timer */
    int prog;
    do
    {
        fus_prog.u = BDK_CSR_READ(node, BDK_FUSF_PROG);
        if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
            prog = fus_prog.cn81xx.prog;
        else
            prog = fus_prog.cn9.prog;
    } while (prog);

    /* Read the fuse to make sure it was really soft blown */
    if (bdk_fuse_field_read(node, fuse) == 0)
    {
        bdk_error("N%d: Soft blowing field fuse %d failed\n", node, fuse);
        return -1;
    }
    return 0;
}

/**
 * Hard blow fuses in the field set (FUSF). Up to 128 fuses in a bank
 * are blown at the same time
 *
 * @param node       Node to blow
 * @param start_fuse First fuses to blow. Must be on a 128 bit boundary.
 *                   This fuse is blown to match the LSB of fuse 0.
 * @param fuses0     First 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses0 maps to start_fuse. MSB of fuses0 maps to
 *                   (start_fuse + 63).
 * @param fuses1     Second 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses1 maps to (start_fuse + 64). MSB of fuses1
 *                   maps to (start_fuse + 127).
 *
 * @return Zero on success, negative on failure
 */
static int field_hard_blow_cn8(bdk_node_t node, int start_fuse, uint64_t fuses0, uint64_t fuses1)
{
    if ((start_fuse & 127) != 0)
    {
        bdk_error("FUSF: Start fuse must be on a 128 bit boundary\n");
        return -1;
    }

    /* Select the fuse bank. there are 128 fuses per bank */
    BDK_CSR_WRITE(node, BDK_FUSF_WADR, start_fuse / 128);

    /* Select the fuse to program in the bank */
    BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(0), fuses0);
    BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(1), fuses1);

    /* Enable the external programming voltage */
    BDK_CSR_DEFINE(fus_prog, BDK_FUSF_PROG);
    fus_prog.u = 0;
    fus_prog.cn81xx.volt_en = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, fus_prog.u);

    /* Wait for the voltage input to be recognized */
    if (BDK_CSR_WAIT_FOR_CHIP_FIELD(node, BDK_FUSF_PROG, cn81xx, prog_pin, ==, 1, 10000))
    {
        /* Timeout waiting for voltage, disable it and fail */
        BDK_CSR_WRITE(node, BDK_FUSF_PROG, 0);
        bdk_error("FUSF: Programming voltage not detected\n");
        return -1;
    }

    /* Program the fuses */
    fus_prog.cn81xx.prog = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, fus_prog.u);

    /* Wait for the program to complete */
    if (BDK_CSR_WAIT_FOR_CHIP_FIELD(node, BDK_FUSF_PROG, cn81xx, prog, ==, 0, 100000))
    {
        /* Timeout waiting for program, disable power and fail */
        BDK_CSR_WRITE(node, BDK_FUSF_PROG, 0);
        bdk_error("FUSF: Timout programming fuse\n");
        return -1;
    }

    /* Disable the external programming voltage */
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, 0);

    /* Wait for the voltage input to be removed */
    if (BDK_CSR_WAIT_FOR_CHIP_FIELD(node, BDK_FUSF_PROG, cn81xx, prog_pin, ==, 0, 10000))
    {
        bdk_warn("FUSF: Programming voltage not removed after program\n");
    }

    /* Read the fuses back to check programming */
    bdk_fusf_rcmd_t read_cmd;
    read_cmd.u = 0;
    read_cmd.cn8.efuse = 1;
    /* In CN8XXX fuses take a byte address, not a 128 bit bank */
    read_cmd.cn8.addr = start_fuse >> 3;
    read_cmd.cn8.addr_hi = start_fuse >> 9;
    read_cmd.s.pend = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_RCMD, read_cmd.u);
    do
    {
        read_cmd.u = BDK_CSR_READ(node, BDK_FUSF_RCMD);
    } while (read_cmd.s.pend);

    uint64_t dat0 = BDK_CSR_READ(node, BDK_FUSF_BNK_DATX(0));
    uint64_t dat1 = BDK_CSR_READ(node, BDK_FUSF_BNK_DATX(1));

    /* Make sure all fuses that were suppose to blow are blown */
    if (((dat0 & fuses0) != fuses0) || ((dat1 & fuses1) != fuses1))
    {
        bdk_error("FUSF: Mismatch after program (program 0x%lx 0x%lx, read 0x%lx 0x%lx)\n",
            fuses0, fuses1, dat0, dat1);
        return -1;
    }

    /* Warn if more fuses are blown than requested. This probably
       means some fuses were blown before we started */
    if ((dat0 != fuses0) || (dat1 != fuses1))
    {
        bdk_warn("FUSF: Some extra fuses were already blown (program 0x%lx 0x%lx, read 0x%lx 0x%lx)\n",
            fuses0, fuses1, dat0, dat1);
        return -1;
    }

    return 0;
}

/**
 * Hard blow fuses in the field set (FUSF). Up to 128 fuses in a bank
 * are blown at the same time
 *
 * @param node       Node to blow
 * @param start_fuse First fuses to blow. Must be on a 128 bit boundary.
 *                   This fuse is blown to match the LSB of fuse 0.
 * @param fuses0     First 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses0 maps to start_fuse. MSB of fuses0 maps to
 *                   (start_fuse + 63).
 * @param fuses1     Second 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses1 maps to (start_fuse + 64). MSB of fuses1
 *                   maps to (start_fuse + 127).
 *
 * @return Zero on success, negative on failure
 */
static int field_hard_blow_cn9(bdk_node_t node, int start_fuse, uint64_t fuses0, uint64_t fuses1)
{
    if ((start_fuse & 127) != 0)
    {
        bdk_error("FUSF: Start fuse must be on a 128 bit boundary\n");
        return -1;
    }

    /* Select the fuse to program in the bank */
    BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(0), fuses0);
    BDK_CSR_WRITE(node, BDK_FUSF_BNK_DATX(1), fuses1);

    /* Enable the external programming voltage */
    BDK_CSR_DEFINE(fus_prog, BDK_FUSF_PROG);
    fus_prog.u = 0;
    fus_prog.cn9.volt_en = 1;
    fus_prog.cn9.addr = start_fuse >> 7;
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, fus_prog.u);

    /* Wait for the voltage input to be recognized */
    if (BDK_CSR_WAIT_FOR_CHIP_FIELD(node, BDK_FUSF_PROG, cn9, voltage, ==, 1, 10000))
    {
        /* Timeout waiting for voltage, disable it and fail */
        BDK_CSR_WRITE(node, BDK_FUSF_PROG, 0);
        bdk_error("FUSF: Programming voltage not detected\n");
        return -1;
    }

    /* Program the fuses */
    fus_prog.cn9.prog = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, fus_prog.u);

    /* Wait for the program to complete */
    if (BDK_CSR_WAIT_FOR_CHIP_FIELD(node, BDK_FUSF_PROG, cn9, prog, ==, 0, 100000))
    {
        /* Timeout waiting for program, disable power and fail */
        BDK_CSR_WRITE(node, BDK_FUSF_PROG, 0);
        bdk_error("FUSF: Timout programming fuse\n");
        return -1;
    }

    /* Disable the external programming voltage */
    BDK_CSR_WRITE(node, BDK_FUSF_PROG, 0);

    /* Wait for the voltage input to be removed */
    if (BDK_CSR_WAIT_FOR_CHIP_FIELD(node, BDK_FUSF_PROG, cn9, voltage, ==, 0, 10000))
    {
        bdk_warn("FUSF: Programming voltage not removed after program\n");
    }

    /* Read the fuses back to check programming */
    bdk_fusf_rcmd_t read_cmd;
    read_cmd.u = 0;
    read_cmd.cn9.efuse = 1;
    /* In CN9XXX fuses take a 128 bit bank, not a byte address */
    read_cmd.cn9.addr = start_fuse >> 7;
    read_cmd.s.pend = 1;
    BDK_CSR_WRITE(node, BDK_FUSF_RCMD, read_cmd.u);
    do
    {
        read_cmd.u = BDK_CSR_READ(node, BDK_FUSF_RCMD);
    } while (read_cmd.s.pend);

    uint64_t dat0 = BDK_CSR_READ(node, BDK_FUSF_BNK_DATX(0));
    uint64_t dat1 = BDK_CSR_READ(node, BDK_FUSF_BNK_DATX(1));

    /* Make sure all fuses that were suppose to blow are blown */
    if (((dat0 & fuses0) != fuses0) || ((dat1 & fuses1) != fuses1))
    {
        bdk_error("FUSF: Mismatch after program (program 0x%lx 0x%lx, read 0x%lx 0x%lx)\n",
            fuses0, fuses1, dat0, dat1);
        return -1;
    }

    /* Warn if more fuses are blown than requested. This probably
       means some fuses were blown before we started */
    if ((dat0 != fuses0) || (dat1 != fuses1))
    {
        bdk_warn("FUSF: Some extra fuses were already blown (program 0x%lx 0x%lx, read 0x%lx 0x%lx)\n",
            fuses0, fuses1, dat0, dat1);
        return -1;
    }

    return 0;
}

/**
 * Hard blow fuses in the field set (FUSF). Up to 128 fuses in a bank
 * are blown at the same time
 *
 * @param node       Node to blow
 * @param start_fuse First fuses to blow. Must be on a 128 bit boundary.
 *                   This fuse is blown to match the LSB of fuse 0.
 * @param fuses0     First 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses0 maps to start_fuse. MSB of fuses0 maps to
 *                   (start_fuse + 63).
 * @param fuses1     Second 64 fuse values. Bits with a 1 are blown. LSB
 *                   of fuses1 maps to (start_fuse + 64). MSB of fuses1
 *                   maps to (start_fuse + 127).
 *
 * @return Zero on success, negative on failure
 */
int bdk_fuse_field_hard_blow(bdk_node_t node, int start_fuse, uint64_t fuses0, uint64_t fuses1)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return field_hard_blow_cn8(node, start_fuse, fuses0, fuses1);
    else
        return field_hard_blow_cn9(node, start_fuse, fuses0, fuses1);
}
