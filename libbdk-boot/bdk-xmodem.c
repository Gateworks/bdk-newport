/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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

