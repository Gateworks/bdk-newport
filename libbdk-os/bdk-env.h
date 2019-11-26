/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#ifndef __BDK_ENV_H__
#define __BDK_ENV_H__
/**
 * @file bdk-env.h
 *
 * Functions for reading and writing environment variables.
 *
 * @{
 */

/**
 * Set or delete an environment variable
 *
 * @param name      Name of the variable
 * @param value     Value of the variable (NULL == delete the variable)
 *
 * @return
 */
extern void bdk_setenv(const char *name, const char *value);

/**
 * Print the list of environment variables
 *
 * @return
 */
extern void bdk_showenv(void);

/** @} */
#endif /* __BDK_ENV_H__ */
