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
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-mio_fus.h"

#include "efuse-read.h"

#define MAX_FUSES   4096
#define NUMBER_OF_EFUSE_READS (num_fuses()/8 + (num_fuses()%8 != 0))

#define DECODE_LOTID_CHAR(x)    (x < 10 ? '0' + x : x < 36 ? 'A' + x - 10 : ' ')
int num_fuses(void)
{
    return(3056);
}


/* get single fuse value from array */
int get_fuse(unsigned char *efuse_ptr, int fuse)
{
    if (fuse >= num_fuses())
        return 0;
    return (!!(efuse_ptr[fuse >> 3] & (1 << (fuse & 0x7))));
}
/* Set single fuse value in array to specified value */
int set_fuse(unsigned char *efuse_ptr, int fuse, int val)
{
    if (fuse >= num_fuses())
        return 0;
    efuse_ptr[fuse >> 3] &= ~(1 << (fuse & 0x7));
    efuse_ptr[fuse >> 3] |= ((!!val) << (fuse & 0x7));
    return(get_fuse(efuse_ptr, fuse));
}

    /*

   [9:0]  = fus[9:0]   = Die Y-loc
   [19:10]  = fus[19:10]   = Die X-loc
  [25:20] = fus[25:20] = Wafer ID
  [35:26] = fus[35:26] = Unused
  [40:36] = fus[40:36] = Frequency multiplier with 50Mhz as ref_clk
  [56:41] = fus[56:41] = Bad PP based on ATE testing
                This is required for ATE to system test correlation and will not
                be needed in mass production when we remove system test
  [57]    = fus[57]    = Bad ZIP on ATE testing
                This is required for ATE to system test correlation and will not
                be needed in mass production when we remove system test
  [58]    = fus[58]    = Bad DFA on ATE testing
                This is required for ATE to system test correlation and will not
                be needed in mass production when we remove system test
  [63:59] = fus[63:59] = Unused 
    */
typedef union
{
    uint64_t u64;
    struct mfg_data
    {
#ifdef CPU_BE
        uint64_t    reserved    :   5;
        uint64_t    bad_dfa     :   1;
        uint64_t    bad_zip     :   1;
        uint64_t    bad_pp_mask :  16;
        uint64_t    freq_x_50   :   5;
        uint64_t    unused      :  10;
        uint64_t    wafer_id    :   6;
        uint64_t    xloc        :  10;
        uint64_t    yloc        :  10;
#else
        uint64_t    yloc        :  10;
        uint64_t    xloc        :  10;
        uint64_t    wafer_id    :   6;
        uint64_t    unused      :  10;
        uint64_t    freq_x_50   :   5;
        uint64_t    bad_pp_mask :  16;
        uint64_t    bad_zip     :   1;
        uint64_t    bad_dfa     :   1;
        uint64_t    reserved    :   5;
#endif
    } s;
} mfg_fuse_wafer_id_t;
/*
  fus[511:448] for Lot ID (2nd MFG FUSE BANK)

'0' => 0x0
...
'9' => 0x9
'A' => 0xa
...


[459:448] = fus[459:448] = Reserved for child/split Lot ID (*.00)
[465:460] = fus[465:460] = Last digit of mother lot ID
[471:466] = fus[471:466] = 5th Digit of mother lot ID
[477:472] = fus[477:472] = 4th Digit of mother lot ID
[483:478] = fus[483:478] = 3rd Alphanumeric character of mother lot ID
[489:484] = fus[489:484] = 2nd Alphanumeric character of mother lot ID
[495:490] = fus[495:490] = 1st Letter of mother lot ID 

For 63xx:
 Fuses for Lot ID 						
  fus[651:640] = [11:0] = Reserved for child/split Lot ID (*.00)

  fus[657:652] = [17:12] = Last digit is split/space character of mother
lot ID						
  fus[663:658] = [23:18] = 5th Alphanumeric of mother lot ID

  fus[669:664] = [29:24] = 4th Alphanumeric character of mother lot ID

  fus[675:670] = [35:30] = 3rd Alphanumeric character of mother lot ID

  fus[681:676] = [41:36] = 2nd Alphanumeric character of mother lot ID

  fus[687:682] = [47:42] = 1st Alphanumeric character of mother lot ID


*/
typedef union
{
    uint64_t u64;
    struct mfg_data2
    {
#ifdef CPU_BE
        uint64_t    reserved1    :  10;
        uint64_t    char0        :  6;
        uint64_t    char1        :  6;
        uint64_t    char2        :  6;
        uint64_t    char3        :  6;
        uint64_t    char4        :  6;
        uint64_t    char5        :  6;
        uint64_t    char6        :  6;
        uint64_t    reserved_cs  :  12;
#else
        uint64_t    reserved_cs  :  12;
        uint64_t    char6        :  6;
        uint64_t    char5        :  6;
        uint64_t    char4        :  6;
        uint64_t    char3        :  6;
        uint64_t    char2        :  6;
        uint64_t    char1        :  6;
        uint64_t    char0        :  6;
        uint64_t    reserved1    :  10;
#endif
    } s;
} mfg_fuse_lot_id_t;

/* bit_offset must be byte aligned.*/

uint64_t efuse_extract_64bits(unsigned char *fuse_ptr, int bit_offset)
{
    uint64_t fuse_data  = 0;
    int offset = bit_offset/8;
    int i;
    for (i = offset + 7; i >= offset;i--)
    {
        fuse_data <<= 8;
        fuse_data |= fuse_ptr[i];
    }
    return(fuse_data);
}


void efuse_read_all_o3(unsigned char *efuse_ptr, int cached_read)
{
    int64_t cmd;
    int i;
    uint8_t addr_hi;

    bdk_node_t node = bdk_numa_local();


    /* Read 8 bits at a time */
    for (i=0; i < NUMBER_OF_EFUSE_READS; i++)
    {
        addr_hi = ((i >> 8) & 0x3);
        if (!cached_read)
            BDK_CSR_WRITE(node, BDK_MIO_FUS_RCMD, (1<<12) | (1<<8) | (addr_hi << 9) | i);  // read fuse actual
        else
            BDK_CSR_WRITE(node, BDK_MIO_FUS_RCMD, (1<<12) | (0<<8) | (addr_hi << 9) | i);  // read fuse cache

        //BDK_SYNC;  /* Force IO transaction out */
        while (1)
        {
            cmd = BDK_CSR_READ(node, BDK_MIO_FUS_RCMD);
          //  BDK_SYNC;

            if (cmd & 0x1000)
                ;
            else break;
        }
        efuse_ptr[i] = (cmd>>16) & 0xff;;
    }
}

void dump_fuses(void)
{
    unsigned char efuse_data[MAX_FUSES/8] = {0};
    unsigned char efuse_data_cached[MAX_FUSES/8] = {0};
    int i, j;

    printf("Starting fuse dump\n");
    fflush(NULL);

    efuse_read_all_o3(efuse_data, 0);
    efuse_read_all_o3(efuse_data_cached, 1);


    for (i = 0; i < NUMBER_OF_EFUSE_READS; i+=8)
    {
        printf("Fuse [%4d:%4d] ", (i + 8)*8 - 1, i*8);
        for (j = 7; j >= 0; j--)
        {
            printf("%02x ", efuse_data[i + j]);
        }
        printf("\n");
    }
    printf("\n\n");


    /* Print out list of fuses blown.  Add prefix to each
    ** line to make parsing of output by script a bit easier. */
    int blown_count = 0;
    printf("Fuses blown:\n");
    for (i = 0; i < num_fuses(); i++)
    {
        if (efuse_data[i >> 3] & (1 << (i & 0x7)))
        {
            if ((blown_count & 0x7) == 0x0)
                printf("FB: ");
            printf("%4d ", i);
            if ((blown_count & 0x7) == 0x7)
                printf("\n");
            blown_count++;
        }
    }
    printf("\nFuse blown count: %d fuses\n", blown_count);


//    if (OCTEON_IS_MODEL(OCTEON_CN78XX))
    {
        /* Adjust cached copy to adjust for fuses that have default
         * values of 1.  For these fuses blowing the fuse will result
         * in the power on value being 0.  We adjust for these by
         * flipping the value in the cached fuse data.
         */
        set_fuse(efuse_data_cached, 128, !get_fuse(efuse_data_cached, 128));
        set_fuse(efuse_data_cached, 132, !get_fuse(efuse_data_cached, 132));
        set_fuse(efuse_data_cached, 143, !get_fuse(efuse_data_cached, 143));
    }

    /* Now handle soft blown fuses... */
    blown_count= 0;
    printf("\n\n");
    printf("Fuses soft blown:\n");
    for (i = 0; i < num_fuses(); i++)
    {
        if (!(efuse_data[i >> 3] & (1 << (i & 0x7)))
            && (efuse_data_cached[i >> 3] & (1 << (i & 0x7))))
        {
            /* Skip the revision ID field, as well as the Authentik
            ** secret stuff.  The rev id can be set by different means,
            ** and the Athentik fuses are not readable. */

//                 OCTEON3 todo...
//                if ((i >= 64 && i <= 71) || (i >=960 && i <= 1023))
//                    continue;
            if ((blown_count & 0x7) == 0x0)
                printf("SFB: ");
            printf("%4d ", i);
            if ((blown_count & 0x7) == 0x7)
                printf("\n");
            blown_count++;
        }
    }
    printf("\nFuse soft blown count: %d fuses\n", blown_count);



    uint64_t ate_bad_pp_mask;
    mfg_fuse_lot_id_t lot_id;
    mfg_fuse_wafer_id_t mfg_wafer_id;
    int ate_bad_pp_offset = 32;
    int ate_wafer_id_offset = 704;
    char lot_id_str[10] = {0};
    ate_bad_pp_offset = 896;
    ate_wafer_id_offset = 704;
    lot_id.u64 = efuse_extract_64bits(efuse_data, 640);
    ate_bad_pp_mask = efuse_extract_64bits(efuse_data, ate_bad_pp_offset) & 0xffffffff;
    mfg_wafer_id.u64 = efuse_extract_64bits(efuse_data, ate_wafer_id_offset);

    /* Translate lot ID character encoding */
    lot_id_str[0] = DECODE_LOTID_CHAR(lot_id.s.char0);
    lot_id_str[1] = DECODE_LOTID_CHAR(lot_id.s.char1);
    lot_id_str[2] = DECODE_LOTID_CHAR(lot_id.s.char2);
    lot_id_str[3] = DECODE_LOTID_CHAR(lot_id.s.char3);
    lot_id_str[4] = DECODE_LOTID_CHAR(lot_id.s.char4);
    lot_id_str[5] = DECODE_LOTID_CHAR(lot_id.s.char5);
    lot_id_str[6] = DECODE_LOTID_CHAR(lot_id.s.char6);


    int arch_cores = 0;
    arch_cores = 48;

    ate_bad_pp_mask &= ((1ULL << arch_cores) - 1);


    printf("Manufacturing fuse decode (Octeon III):\n");
    printf("Lot id: %s, wafer id: %2d, x: %2d, y: %2d\n",
          lot_id_str, mfg_wafer_id.s.wafer_id, mfg_wafer_id.s.xloc, mfg_wafer_id.s.yloc);
    printf("bad_pp_mask: %016llx\n", (unsigned long long)ate_bad_pp_mask);
    printf("fuse dump complete\n");
}

