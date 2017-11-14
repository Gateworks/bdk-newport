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
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_CONSOLE_FILES 8
static int open_files[MAX_CONSOLE_FILES] = {3,4,};
static int last_input;
static char pending_rx[32];
static int pending_rx_count = 0;

/**
 * Add a file to the list of devices that the console polls for input
 *
 * @param filename Filename of the device to poll
 *
 * @return Zero on success, negative on failure
 */
int bdk_console_open_file(const char *filename)
{
    int fd = open(filename, O_RDWR, 0);
    if (fd < 0)
    {
        bdk_error("Failed to open console file %s\n", filename);
        return -1;
    }

    for (int i=0; i<MAX_CONSOLE_FILES; i++)
    {
        if (open_files[i] == 0)
        {
            open_files[i] = fd;
            return i;
        }
    }
    close(fd);
    bdk_error("Too many open console files\n");
    return -1;
}

static void *console_open(const char *name, int flags)
{
    /* This is never called as the C library assumes stdin, stdout, and stderr
        are already open */
    return open_files;
}

static int console_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    static bdk_rlock_t console_lock;
    int fd = open_files[last_input];
    const char *ptr = buffer;
    int len = length;

    while (len)
    {
        /* Send all bytes up until the \n */
        int count = 0;
        while ((count < len) && (ptr[count] != '\n'))
            count++;
        bdk_rlock_lock(&console_lock);
        if (count && (write(fd, ptr, count) < 0))
            goto error;
        /* Send a \r\n if we found a \n */
        if ((count < len) && (ptr[count] == '\n'))
        {
            if (write(fd, "\r\n", 2) < 0)
                goto error;
            count++;
        }
        bdk_rlock_unlock(&console_lock);
        ptr += count;
        len -= count;
    }
    return length;
error:
    close(fd);
    open_files[last_input] = 0;
    last_input = 0;
    bdk_rlock_unlock(&console_lock);
    return length;
}

static int console_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    while (1)
    {
        for (int i=0; i<MAX_CONSOLE_FILES; i++)
        {
            if (!open_files[i])
                continue;
            if (pending_rx_count)
            {
                int len = pending_rx_count;
                if (length < len)
                    len = length;
                memcpy(buffer, pending_rx, len);
                pending_rx_count -= len;
                if (pending_rx_count)
                    memcpy(pending_rx, pending_rx+len, pending_rx_count);
                return len;
            }
            int bytes = read(open_files[i], buffer, length);
            if (bytes > 0)
            {
                last_input = i;
                return bytes;
            }
            else if (bytes < 0)
            {
                /* Close dead devices */
                close(open_files[i]);
                open_files[i] = 0;
                if (i == last_input)
                    last_input = 0;
            }
        }
        bdk_thread_yield();
        if (length == 1)
            break;
    }
    return 0;
}

/**
 * This function is called periodically for Control-C processing
 *
 * @return Non zero if a Control-C is seen
 */
int __bdk_fs_check_break(void)
{
    char c;
    int result = console_read(NULL, &c, 1);
    if (result != 1)
        return 0;

    /* Check for Control-C */
    if (c == 0x3)
    {
        /* Cancel any buffered RX when we receive a Contorl-C */
        pending_rx_count = 0;
        return 1;
    }
    else
    {
        /* Store this character in our internal buffer */
        if (pending_rx_count < (int)sizeof(pending_rx))
            pending_rx[pending_rx_count++] = c;
        return 0;
    }
}

const __bdk_fs_ops_t bdk_fs_console_ops =
{
    .stat = NULL,
    .unlink = NULL,
    .open = console_open,
    .close = NULL,
    .read = console_read,
    .write = console_write,
};

