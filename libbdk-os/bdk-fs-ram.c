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

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_RAM);

typedef struct ram_file
{
    const char *name;
    unsigned int length;
    void *data;
    struct ram_file *next;
} ram_file_t;

static ram_file_t *head;


static void *ram_open(const char *name, int flags)
{
    /* Find the file */
    ram_file_t *fptr = head;
    while (fptr)
    {
        if (strcmp(name, fptr->name) == 0)
            break;
        fptr = fptr->next;
    }

    /* Files openned for write have a possible flags */
    if ((flags&3) != O_RDONLY)
    {
        /* Delete the old file if O_TRUNC */
        if ((flags & O_TRUNC) && fptr)
        {
            free(fptr->data);
            fptr->data = NULL;
            fptr->length = 0;
        }

        /* Create a new file if O_CREAT */
        if ((flags & O_CREAT) && !fptr)
        {
            fptr = calloc(1, sizeof(ram_file_t));
            if (!fptr)
                return NULL;
            fptr->name = strdup(name);
            fptr->next = head;
            head = fptr;
        }
    }

    return fptr;
}


static int ram_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    const ram_file_t *fptr = handle->fs_state;
    unsigned int pos = handle->location;

    if (pos > fptr->length)
        return -1;
    else if (pos == fptr->length)
        return 0;

    if (pos + length > fptr->length)
        length = fptr->length - pos;

    memcpy(buffer, fptr->data + pos, length);
    return length;
}


static int ram_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    ram_file_t *fptr = handle->fs_state;
    unsigned int pos = handle->location;

    if (pos + length > fptr->length)
    {
        void *data = realloc(fptr->data, pos + length);
        if (data == NULL)
            return -1;
        fptr->data = data;
        fptr->length = pos + length;
    }
    memcpy(fptr->data + pos, buffer, length);
    return length;
}


static int ram_unlink(const char *name)
{
    /* Find the file and keep track of the previous one in the linked list */
    ram_file_t *fprev = NULL;
    ram_file_t *fptr = head;
    while (fptr)
    {
        if (strcmp(name, fptr->name) == 0)
            break;
        fprev = fptr;
        fptr = fptr->next;
    }

    /* File wasn't found */
    if (!fptr)
        return -1;

    /* Remove the file from the linked list */
    if (fprev)
        fprev->next = fptr->next;
    else
        head = fptr->next;

    /* Free the file's memory */
    free(fptr->data);
    free((void*)fptr->name);
    free(fptr);

    return 0;
}

static int ram_list(const char *path, __bdk_fs_list_callback callback, void *callback_state)
{
    if (NULL == callback) return -1;
    ram_file_t *fptr = head;
    while (fptr)
    {
        callback(fptr->name,callback_state);
        fptr = fptr->next;
    }
    return 0;
}

static const __bdk_fs_ops_t bdk_fs_ram_ops =
{
    .stat = NULL,
    .unlink = ram_unlink,
    .open = ram_open,
    .close = NULL,
    .read = ram_read,
    .write = ram_write,
    .list = ram_list,
};

int __bdk_fs_ram_init(void)
{
    return bdk_fs_register("/ram/", &bdk_fs_ram_ops);
}
