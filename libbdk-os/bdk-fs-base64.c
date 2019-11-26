/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_BASE64);

#define CHARS_PER_LINE 76 /* Show 76 encoded chars per line */
#define BYTES_PER_LINE (CHARS_PER_LINE * 3 / 4)

typedef struct
{
    bool is_write;
    int total;
    int len; /* Bytes in buffer (0-3), or -1 for read done */
    char buffer[3];
} base64_state_t;

static const char BASE64_SET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

/**
 * Send bytes in a base64 encode 4 char string
 *
 * @param buf    Buffer to encode
 * @param len    Number of bytes (1-3)
 *
 * @return Number of bytes (1-3)
 */
static int base64_send(const char *buf, int len)
{
    char c[4];

    c[0] = BASE64_SET[0x3f & (buf[0] >> 2)];

    if (len > 1)
        c[1] = BASE64_SET[0x3f & ((buf[0] << 4) | (buf[1] >> 4))];
    else
        c[1] = BASE64_SET[0x3f & (buf[0] << 4)];

    if (len > 2)
        c[2] = BASE64_SET[0x3f & ((buf[1] << 2) | (buf[2] >> 6))];
    else if (len > 1)
        c[2] = BASE64_SET[0x3f & (buf[1] << 2)];
    else
        c[2] = BASE64_SET[64];

    if (len > 2)
        c[3] = BASE64_SET[0x3f & buf[2]];
    else
        c[3] = BASE64_SET[64];

    fwrite(c, 1, 4, stdout);
    return len;
}

/**
 * Open a base64 encoded file for read/write
 *
 * @param name   Name of /base64
 * @param flags  read/write flags
 *
 * @return Non null on success, null on failure
 */
static void *base64_open(const char *name, int flags)
{
    bool is_write = false;
    if ((flags&3) == O_RDONLY)
    {
        printf("Upload a BASE64 encoded file\n");
        printf("Send ^C to abort\n");
    }
    else if ((flags&3) == O_WRONLY)
    {
        printf("\n*** Begin BASE64 encoded file ***\n");
        is_write = true;
    }
    else
    {
        bdk_error("Can't open BASE64 as read+write\n");
        return NULL;
    }

    base64_state_t *state = calloc(1, sizeof(base64_state_t));
    if (state)
        state->is_write = is_write;
    return state;
}

/**
 * Close a base64 encoded file
 *
 * @param handle File to close
 *
 * @return Zero on success, negative on failure
 */
static int base64_close(__bdk_fs_file_t *handle)
{
    base64_state_t *state = handle->fs_state;
    if (!state)
        return 0;
    if (state->is_write)
    {
        /* Send any leftover data */
        if (state->len)
            state->total += base64_send(state->buffer, state->len);
        if ((state->total % BYTES_PER_LINE) != 0)
            putchar('\n');
        printf("*** End BASE64 encoded file (%d bytes) ***\n\n", state->total);
    }
    else
    {
        /* Check for leftover data */
        if (state->len > 0)
            bdk_error("BASE64 receive got too much data\n");
        printf("BASE64 transferred %d bytes\n", state->total);
    }

    int length = state->total;
    free(state);
    handle->fs_state = NULL;
    return (length) ? 0 : -1;
}

/**
 * Read from a base64 encoded file
 *
 * @param handle File to read
 * @param buffer Buffer to fill
 * @param length Size of read
 *
 * @return Number of bytes read, negative on failure
 */
static int base64_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    int bytes_read = 0;
    base64_state_t *state = handle->fs_state;

    if (!state)
        return 0;
    if (state->is_write)
        return -1;
    if (state->len < 0) /* Reached end of valid BASE64 data in last call */
        return 0;

    while (length)
    {
        /* Check if we need 4 more base64 encoded chars. We require
           the '=' padding */
        if (state->len == 0)
        {
            int b64[4];
            int len = 0;
            int skips = 0;
            while (len < 4)
            {
                int c = bdk_readline_getkey(100000);
                if (c < 0)
                {
                    /* No data available, waiting  */
                    continue;
                }
                const char *ptr = strchr(BASE64_SET, c);
                if (ptr)
                {
                    b64[len++] = ptr - BASE64_SET; /* Valid data */
                    skips = 0;
                }
                else if ((c == ' ') || (c == '\n') || (c == '\r'))
                {
                    skips++;
                    if ((len || state->total) && (skips > 2))
                    {
                        state->len = -1;
                        return bytes_read; /* End input */
                    }
                    continue; /* Skip extra whitespace */
                }
                else
                {
                    state->len = -1;
                    return bytes_read; /* Bad input */
                }
            }
            /* Convert 4 chars to 3 bytes */
            if (b64[2] == 64)
            {
                state->len = 1;
                b64[2] = 0;
            }
            else if (b64[3] == 64)
            {
                state->len = 2;
                b64[3] = 0;
            }
            else
                state->len = 3;
            state->buffer[0] = (b64[0] << 2) | (b64[1] >> 4);
            state->buffer[1] = (b64[1] << 4) | (b64[2] >> 2);
            state->buffer[2] = (b64[2] << 6) | b64[3];
        }
        /* Copy bytes from state->buf as we have room */
        int bytes = state->len;
        if (bytes > length)
            bytes = length;
        memcpy(buffer, state->buffer, bytes);
        state->len -= bytes;
        if (state->len)
            memcpy(state->buffer, state->buffer + bytes, state->len);
        buffer += bytes;
        length -= bytes;
        bytes_read += bytes;
        state->total += bytes;
    }
    return bytes_read;
}

/**
 * Write to a base64 encoded file
 *
 * @param handle File to write
 * @param buffer Buffer to write
 * @param length Length of the write
 *
 * @return Number of bytes written, negative on failure
 */
static int base64_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    base64_state_t *state = handle->fs_state;
    const void *ptr = buffer;
    int bytes_written = 0;

    if (!state)
        return -1;
    if (!state->is_write)
        return -1;

    while (length)
    {
        int needed_bytes = 3 - state->len;
        if (needed_bytes > length)
            needed_bytes = length;
        memcpy(state->buffer + state->len, ptr, needed_bytes);
        state->len += needed_bytes;
        ptr += needed_bytes;
        length -= needed_bytes;
        bytes_written += needed_bytes;

        if (state->len == 3)
        {
            state->total += base64_send(state->buffer, state->len);
            state->len = 0;
            if ((state->total % BYTES_PER_LINE) == 0)
                putchar('\n');
        }
    }

    return bytes_written;
}

/**
 * Base64 file OPs
 */
static const __bdk_fs_ops_t bdk_fs_base64_ops =
{
    .open = base64_open,
    .close = base64_close,
    .read = base64_read,
    .write = base64_write,
    .list = NULL,
};

/**
 * Init for Base64
 *
 * @return Zero on success, negative on failure
 */
int __bdk_fs_base64_init(void)
{
    return bdk_fs_register("/base64", &bdk_fs_base64_ops);
}