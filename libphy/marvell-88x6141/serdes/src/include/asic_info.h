/* AAPL CORE Revision: 2.6.2
 *
 * Copyright (c) 2014-2017 Avago Technologies. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @file
 ** @brief Declarations of ASIC-specific values used in AAPL.
 */

#ifndef AVAGO_ASIC_INFO_H_
#define AVAGO_ASIC_INFO_H_

typedef struct
{
        uint jtag_idcode;
        const char *name;
        const char *rev;
        Avago_process_id_t process_id;
        uint sbus_rings;
        uint sbus_ring_start;
} Avago_chip_id_t;

/* Only one compilation unit defines this global variable; others just get the
 * definition:
 */

#define avago_chip_id MYD_avago_chip_id
Avago_chip_id_t avago_chip_id[] =
{
    /* NOTE: Add new entries near beginning of list, not at end. */

    {0x1000057f, "\x41\x41\x50\x4c\x5f\x31\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x2000057f, "\x41\x41\x50\x4c\x5f\x32\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 2, 0},
    {0x3000057f, "\x41\x41\x50\x4c\x5f\x33\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 3, 0},
    {0x4000057f, "\x41\x41\x50\x4c\x5f\x34\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 4, 0},
    {0x5000057f, "\x41\x41\x50\x4c\x5f\x35\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 5, 0},
    {0x6000057f, "\x41\x41\x50\x4c\x5f\x36\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 6, 0},
    {0x7000057f, "\x41\x41\x50\x4c\x5f\x37\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 7, 0},
    {0x8000057f, "\x41\x41\x50\x4c\x5f\x38\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 8, 0},
    {0x9000057f, "\x41\x41\x50\x4c\x5f\x39\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 9, 0},
    {0xa000057f, "\x41\x41\x50\x4c\x5f\x31\x30\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 10, 0},
    {0xb000057f, "\x41\x41\x50\x4c\x5f\x31\x31\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 11, 0},
    {0xc000057f, "\x41\x41\x50\x4c\x5f\x31\x32\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 12, 0},
    {0xd000057f, "\x41\x41\x50\x4c\x5f\x31\x33\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 13, 0},
    {0xe000057f, "\x41\x41\x50\x4c\x5f\x31\x34\x5f\x53\x42\x55\x53\x5f\x52\x49\x4e\x47","1", AVAGO_UNKNOWN_PROCESS, 14, 0},

    {0x0912457f, "\x41\x56\x53\x50\x2d\x31\x31\x30\x34",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x0912657f, "\x41\x56\x53\x50\x2d\x31\x31\x30\x34",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x0912657f, "\x41\x56\x53\x50\x2d\x31\x31\x30\x34",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x0954657f, "\x41\x56\x53\x50\x2d\x34\x34\x31\x32\x2f\x38\x38\x30\x31", "1",    AVAGO_PROCESS_F, 1, 0},
    {0x1954657f, "\x41\x56\x53\x50\x2d\x34\x34\x31\x32\x2f\x38\x38\x30\x31", "2",    AVAGO_PROCESS_F, 1, 0},
    {0x096d157f, "\x41\x56\x53\x50\x2d\x34\x34\x31\x32\x2f\x38\x38\x30\x31", "3",    AVAGO_PROCESS_F, 1, 0},
    {0x0968257f, "\x41\x56\x53\x50\x2d\x34\x34\x31\x32\x2f\x38\x38\x30\x31", "4",    AVAGO_PROCESS_F, 1, 0},
    {0x090b957f, "\x41\x56\x53\x50\x2d\x35\x32\x31",                         "1",    AVAGO_PROCESS_F, 1, 0},
    {0x1911357f, "\x41\x56\x53\x50\x2d\x35\x32\x31",                         "1.1",  AVAGO_PROCESS_F, 1, 0},
    {0x0911457f, "\x41\x56\x53\x50\x2d\x35\x32\x31",                         "x",    AVAGO_PROCESS_F, 1, 0},
    {0x099a557f, "\x41\x56\x53\x50\x2d\x35\x34\x31\x30",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x199a557f, "\x41\x56\x53\x50\x2d\x35\x34\x31\x30",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x0990357f, "\x41\x56\x53\x50\x2d\x37\x34\x30\x31",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x0973957f, "\x41\x56\x53\x50\x2d\x37\x34\x31\x32",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x1973957f, "\x41\x56\x53\x50\x2d\x37\x34\x31\x32",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x0973157f, "\x41\x56\x53\x50\x2d\x38\x38\x31\x32",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x1973157f, "\x41\x56\x53\x50\x2d\x38\x38\x31\x32",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x0964257f, "\x41\x56\x53\x50\x2d\x39\x31\x30\x34",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x1964257f, "\x41\x56\x53\x50\x2d\x39\x31\x30\x34",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x2964257f, "\x41\x56\x53\x50\x2d\x39\x31\x30\x34",                     "3",    AVAGO_PROCESS_F, 1, 0},


    {0x0000157f, "\x30\x37\x6e\x6d\x54\x65\x73\x74",                         "1",    AVAGO_PROCESS_E, 1, 0},
    {0x1a08457f, "\x42\x65\x61\x76\x65\x72\x2d\x43\x72\x65\x65\x6b",         "1",    AVAGO_PROCESS_E, 2, 0},
    {0x0a18957f, "\x43\x6f\x6c\x75\x67\x6f",                                 "1",    AVAGO_PROCESS_E, 1, 0},
    {0x0a21657f, "\x44\x46\x45",                                             "1",    AVAGO_PROCESS_E, 1, 0},
    {0x0a0c357f, "\x4d\x63\x43\x68\x69\x70",                                 "1",    AVAGO_PROCESS_E, 1, 0},
    {0x09ca357f, "\x54\x43\x48\x49\x50",                                     "1",    AVAGO_PROCESS_E, 1, 0},

    {0x09d4957f, "\x42\x72\x6f\x61\x64\x6d\x6f\x6f\x72",                     "1",    AVAGO_PROCESS_B, 1, 0},
    {0x09b1657f, "\x46\x65\x72\x6d\x69",                                     "1",    AVAGO_PROCESS_B, 1, 0},
    {0x09c2557f, "\x46\x65\x72\x6d\x69\x42",                                 "1.1",  AVAGO_PROCESS_B, 1, 0},
    {0x49c2557f, "\x46\x65\x72\x6d\x69\x42",                                 "2.0",  AVAGO_PROCESS_B, 1, 0},
    {0x09ce657f, "\x46\x72\x61\x6e\x6b\x6c\x69\x6e",                         "1",    AVAGO_PROCESS_B, 1, 0},
    {0x49ce657f, "\x46\x72\x61\x6e\x6b\x6c\x69\x6e",                         "2.0",  AVAGO_PROCESS_B, 1, 0},
    {0x14211001, "\x48\x65\x72\x74\x7a",                                     "1",    AVAGO_PROCESS_B, 1, 0},
    {0x09b93001, "\x48\x69\x67\x68\x6c\x61\x6e\x64",                         "1",    AVAGO_PROCESS_B, 2, 0},
    {0x19827001, "\x4c\x6f\x72\x65\x6e\x74\x7a",                             "1",    AVAGO_PROCESS_B, 1, 0},
    {0x0000057f, "\x4d\x61\x78\x77\x65\x6c\x6c",                             "1",    AVAGO_PROCESS_B, 1, 0},
    {0x0992957f, "\x53\x69\x6d\x62\x61",                                     "1",    AVAGO_PROCESS_B, 1, 0},
    {0x1992957f, "\x53\x69\x6d\x62\x61",                                     "2",    AVAGO_PROCESS_B, 1, 0},
    {0x0995957f, "\x54\x65\x73\x6c\x61",                                     "1",    AVAGO_PROCESS_B, 1, 0},

    {0x09a1757f, "\x41\x63\x61\x64\x65\x6d\x79",                             "1",    AVAGO_PROCESS_F, 1, 0},
    {0x0985357f, "\x42\x6f\x72\x61\x68\x2d\x50\x65\x61\x6b",                 "1",    AVAGO_PROCESS_F, 1, 0},
    {0x099a757f, "\x42\x75\x63\x6b\x2d\x48\x69\x6c\x6c",                     "1",    AVAGO_PROCESS_F, 1, 0},
    {0x199a757f, "\x42\x75\x63\x6b\x2d\x48\x69\x6c\x6c",                     "2",    AVAGO_PROCESS_F, 1, 0},
    {0x0911657f, "\x44\x65\x6e\x61\x6c\x69",                                 "Bx",   AVAGO_PROCESS_F, 1, 0},
    {0x090b857f, "\x44\x65\x6e\x61\x6c\x69",                                 "B25",  AVAGO_PROCESS_F, 1, 0},
    {0x0912257f, "\x44\x65\x6e\x61\x6c\x69",                                 "B15",  AVAGO_PROCESS_F, 1, 0},
    {0x0901457f, "\x44\x65\x6e\x61\x6c\x69",                                 "1",    AVAGO_PROCESS_F, 1, 0},
    {0x0954957f, "\x4d\x63\x4b\x69\x6e\x6c\x65\x79",                         "XTAL", AVAGO_PROCESS_F, 1, 0},
    {0x0954857f, "\x4d\x63\x4b\x69\x6e\x6c\x65\x79",                         "25",   AVAGO_PROCESS_F, 1, 0},
    {0x0912557f, "\x4d\x63\x4b\x69\x6e\x6c\x65\x79",                         "15",   AVAGO_PROCESS_F, 1, 0},
    {0x0991757f, "\x50\x69\x6b\x65\x73",                                     "1",    AVAGO_PROCESS_F, 1, 0},

    {0x18e5657f, "\x41\x73\x77\x61\x6e",                                     "1",    AVAGO_PROCESS_A, 1, 0},
    {0x18ca657f, "\x43\x61\x6e\x6f\x70\x75\x73",                             "1",    AVAGO_PROCESS_A, 2, 1},
    {0x0000057f, "\x56\x65\x67\x61",                                         "1",    AVAGO_PROCESS_A, 1, 0},

    {0x18a9557f, "\x57\x68\x69\x74\x65",                                     "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x08ca357f, "\x47\x6f\x64\x64\x61\x72\x64",                             "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x1891357f, "\x48\x61\x62\x61\x6e\x65\x72\x6f",                         "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x10000291, "\x54\x61\x62\x61\x73\x63\x6f",                             "90",   AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x086e2291, "\x52\x69\x62\x65\x79\x65",                                 "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x186e2291, "\x52\x69\x62\x65\x79\x65",                                 "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x08d2457f, "\x41\x74\x62\x61\x72\x61",                                 "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x18b3957f, "\x41\x6d\x61\x7a\x6f\x6e",                                 "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x08a7157f, "\x43\x61\x6d\x61\x72\x6f",                                 "1",    AVAGO_UNKNOWN_PROCESS, 1, 0},
    {0x18ca457f, "\x42\x6c\x75\x65",                                         "1",    AVAGO_UNKNOWN_PROCESS, 1, 0}

    /* NOTE: Add new entries at the front of this list, NOT here. */
};

#endif /* AVAGO_ASIC_INFO_H_ */
