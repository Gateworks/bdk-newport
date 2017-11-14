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
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>

int _getpid_r(struct _reent *reent)
{
    return 1;
}

int _isatty_r(struct _reent *reent, int file)
{
    return 1;
}

int _kill_r(struct _reent *reent, int pid, int sig)
{
    reent->_errno = EINVAL;
    return -1;
}

int _rename_r(struct _reent *reent, const char *old, const char *new)
{
    reent->_errno = EMLINK;
    return -1;
}

caddr_t _sbrk_r(struct _reent *reent, ptrdiff_t incr)
{
    static caddr_t next = NULL;
    static caddr_t end;

    if (next == NULL)
    {
        extern uint64_t bdk_fs_romfs_get_end(void);
        unsigned int l2_size = bdk_l2c_get_cache_size_bytes(bdk_numa_master());
        /* Heap starts after the _end symbol and goes until the end of
            the L2 cache */
        uint64_t start_paddr = bdk_fs_romfs_get_end();
        /* Align beginning of heap on 64KB boundary */
        start_paddr = (start_paddr + 65535) & -65536;
        next = bdk_phys_to_ptr(start_paddr);
        end = bdk_phys_to_ptr(bdk_numa_get_address(bdk_numa_master(), l2_size));
    }

    /* See of DRAM was setup and we can use more memory */
    uint64_t dram_mbytes = bdk_dram_get_size_mbytes(bdk_numa_master());
    if (dram_mbytes)
    {
        uint64_t dram_top = dram_mbytes << 20;
        end = bdk_phys_to_ptr(bdk_numa_get_address(bdk_numa_master(), dram_top));
    }
    else if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* FIXME: The diagnostics binary won't fit in L2 of CN81XX. In asim,
           lie about the amount of memory for testing. */
        end = bdk_phys_to_ptr(bdk_numa_get_address(bdk_numa_master(), 16 << 20));
    }
    else if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* FIXME: Networking won't fit in L2 of CN83XX. In asim, lie about
           the amount of memory for testing. */
        end = bdk_phys_to_ptr(bdk_numa_get_address(bdk_numa_master(), 64 << 20));
    }

    caddr_t result = next;

    if ((incr < 0) || (next + incr > end))
        result = (void*)-1;
    else
        next += incr;
    return result;
}

clock_t _times_r(struct _reent *reent, struct tms *buf)
{
    return -1;
}

int _gettimeofday_r(struct _reent *reent, struct timeval *tv, void *tz)
{
    uint64_t rate = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    uint64_t count = bdk_clock_get_count(BDK_CLOCK_TIME);
    tv->tv_sec = count / rate;
    tv->tv_usec = (count / (rate / 1000000)) % 1000000;
    return 0;
}

void _exit(int status)
{
    printf("_exit() was called\n");
    bdk_thread_destroy();
}

