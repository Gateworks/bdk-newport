/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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

void __bdk_trace_printf(const char *format, ...)
{
#ifndef BDK_BUILD_HOST
    const uint64_t USECS_IN_SEC = 1000000;
    const uint64_t USECS_IN_MIN = 60 * USECS_IN_SEC;
    const uint64_t USECS_IN_HOUR = 60 * USECS_IN_MIN;
    const uint64_t USECS_IN_DAY = 24 * USECS_IN_HOUR;

    uint64_t clock_time = bdk_clock_get_count(BDK_CLOCK_TIME);
    uint64_t clock_rate = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    uint64_t usecs = clock_time / (clock_rate / USECS_IN_SEC);

    uint64_t days = usecs / USECS_IN_DAY;
    usecs %= USECS_IN_DAY;
    uint64_t hours = usecs / USECS_IN_HOUR;
    usecs %= USECS_IN_HOUR;
    uint64_t mins = usecs / USECS_IN_MIN;
    usecs %= USECS_IN_MIN;
    uint64_t secs = usecs / USECS_IN_SEC;
    usecs %= USECS_IN_SEC;
    printf("%lud%02luh%02lum%02lu.%06lus: ", days, hours, mins, secs, usecs);
#endif
    va_list args;
    va_start(args, format);
    __bdk_output(NULL, format, args);
    va_end(args);
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
