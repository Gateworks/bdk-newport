/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "dram-internal.h"

const char* lookup_env_parameter(const char *format, ...)
{
    const char *s;
    unsigned long value;
    va_list args;
    char buffer[64];

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer)-1, format, args);
    buffer[sizeof(buffer)-1] = '\0';
    va_end(args);

    if ((s = getenv(buffer)) != NULL)
    {
        value = strtoul(s, NULL, 0);
        error_print("Parameter found in environment: %s = \"%s\" 0x%lx (%ld)\n",
		    buffer, s, value, value);
    }
    return s;
}

const char* lookup_env_parameter_ull(const char *format, ...)
{
    const char *s;
    unsigned long long value;
    va_list args;
    char buffer[64];

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer)-1, format, args);
    buffer[sizeof(buffer)-1] = '\0';
    va_end(args);

    if ((s = getenv(buffer)) != NULL)
    {
        value = strtoull(s, NULL, 0);
        error_print("Parameter found in environment: %s = 0x%016llx\n",
		    buffer, value);
    }
    return s;
}

