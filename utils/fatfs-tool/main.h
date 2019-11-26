#ifndef _MAIN_H_
#define _MAIN_H_
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern unsigned long long aes_key[2];
extern int verbose;
#define CHAT(args...) do { if (verbose) printf(args); } while (0)

#endif /* _MAIN_H_ */
