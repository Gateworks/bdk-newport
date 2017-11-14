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

static int volatile write_needed = 0;
static char write_buffer[4096];
static int volatile write_count = 0;
static bdk_spinlock_t write_lock;

/**
 * The actual writing to flash is done in a separate thread so Xmodem doesn't
 * stall during slow erase cycles.
 *
 * @param unused Unused param
 * @param handle File handle for writing
 */
static void write_thread(int unused, void *handle)
{
    FILE *outf = (FILE*)handle;
    while (write_needed || write_count)
    {
        /* Wait for data */
        if (!write_count)
        {
            bdk_thread_yield();
            continue;
        }
        bdk_spinlock_lock(&write_lock);
        /* Write the data */
        int w_count = fwrite(write_buffer, 1, write_count, outf);
        fflush(outf);
        if (w_count != write_count)
        {
            bdk_error("Write error\n");
            bdk_spinlock_unlock(&write_lock);
            break;
        }
        /* Tell the reader the buffer is empty */
        write_count = 0;
        bdk_spinlock_unlock(&write_lock);
    }
    fclose(outf);
}

/**
 * Receive a file through Xmodem and write it to an internal file.
 *
 * @param dest_file File to write to
 * @param offset    Offset into the file to write
 *
 * @return Zero on success, negative on failure
 */
int bdk_xmodem_upload(const char *dest_file, uint64_t offset)
{
    BDK_REQUIRE(FS_XMODEM);
    /* Open the output file */
    FILE *outf = fopen(dest_file, "w");
    if (!outf)
    {
        bdk_error("Failed to open %s\n", dest_file);
        return -1;
    }
    /* Seek the correct location */
    fseek(outf, offset, SEEK_SET);

    /* Create a thread that does the write so Xmodem doesn't stall
       during slow flash accesses */
    write_count = 0;
    write_needed = 1;
    BDK_WMB;
    bdk_thread_create(bdk_numa_local(), 0, write_thread, 0, (void*)outf, 0);
    /* Let the thread start */
    bdk_thread_yield();

    /* Open xmodem for reading the file */
    FILE *inf = fopen("/xmodem", "r");
    if (!inf)
    {
        bdk_error("Failed to open /xmodem\n");
        BDK_WMB;
        write_needed = 0;
        BDK_WMB;
        return -1;
    }

    /* Loop until the file is done */
    while (!feof(inf))
    {
        char buffer[sizeof(write_buffer)];
        /* Read a block */
        int count = fread(buffer, 1, sizeof(buffer), inf);
        if (count > 0)
        {
            /* Wait for the write buffer to be empty */
            while (write_count)
                bdk_thread_yield();
            /* Put the data in the write buffer */
            bdk_spinlock_lock(&write_lock);
            memcpy(write_buffer, buffer, count);
            BDK_WMB;
            write_count = count;
            bdk_spinlock_unlock(&write_lock);
        }
    }
    fclose(inf);
    printf("\nXmodem complete\n");
    /* Wait for the write thread to finish */
    BDK_WMB;
    write_needed = 0;
    BDK_WMB;
    while (write_count)
        bdk_thread_yield();
    return 0;
}

