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

static void __bdk_output(const char *prefix, const char *format, va_list args)
{
#ifndef BDK_BUILD_HOST
    static bdk_rlock_t rlock = {0,0};
    bdk_rlock_lock(&rlock);
#endif
    if (prefix)
    {
        fputs(prefix, stderr);
        vfprintf(stderr, format, args);
        fflush(stderr);
    }
    else
    {
        vfprintf(stdout, format, args); /* printf goes to stdout */
        fflush(stdout);
    }
#ifndef BDK_BUILD_HOST
    bdk_rlock_unlock(&rlock);
#endif
}

void bdk_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    __bdk_output("FATAL: ", format, args);
    va_end(args);
    __bdk_die();
}

void bdk_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    __bdk_output("\nERROR: ", format, args);
    va_end(args);
}

void bdk_warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    __bdk_output("WARNING: ", format, args);
    va_end(args);
}

int printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    __bdk_output(NULL, format, args);
    va_end(args);
    return 0;
}

void __bdk_die(void)
{
#ifndef BDK_BUILD_HOST
    BDK_MB;
    while (1)
        asm volatile ("wfi" ::: "memory");
#else
    abort();
#endif
}
