/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * Functions for access the environment for DRAM tweaking.
 * Intenral use only.
 */


extern const char *lookup_env_parameter(const char *format, ...) __attribute__ ((format(printf, 1, 2)));
extern const char *lookup_env_parameter_ull(const char *format, ...) __attribute__ ((format(printf, 1, 2)));

