/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <errno.h>
#include <string.h>

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(ENVIRONMENT);

extern char **environ;

void bdk_setenv(const char *name, const char *value)
{
    if (value)
       setenv(name, value, 1);
    else
       unsetenv(name);
}

void bdk_showenv(void)
{
    if (!environ)
    {
        bdk_error("Environment not allocated\n");
        return;
    }

    char **ptr = environ;
    while (*ptr)
    {
        printf("    %s\n", *ptr);
        ptr++;
    }
}

