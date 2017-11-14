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

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_ROM);

/* ROM files are stored sequencially after the end of the image, starting
    at the _end symbol. Each ROM file starts with six bytes "ROM-FS",
    a two byte filename length, a four byte file length, the bytes for
    the filename, and the file's data. The filename is not \0 terminated */

static const void *find_file(const char *name)
{
    extern void _end();
    const char *ptr = (const char *)&_end;
    int name_length = strlen(name);
    while (memcmp(ptr, "ROM-FS", 6) == 0)
    {
        uint16_t fname_length = bdk_le16_to_cpu(*(uint16_t*)(ptr+6));
        uint32_t fdata_length = bdk_le32_to_cpu(*(uint32_t*)(ptr+8));
        const char *fname_ptr = ptr+12;
        const char *fdata_ptr = fname_ptr + fname_length;
        if ((name_length == fname_length) &&
            (strncasecmp(name, fname_ptr, name_length) == 0))
            return ptr;
        ptr = fdata_ptr + fdata_length;
    }
    return NULL;
}

uint64_t bdk_fs_romfs_get_end(void)
{
    extern void _end();
    const char *ptr = (const char *)&_end;
    while (memcmp(ptr, "ROM-FS", 6) == 0)
    {
        uint16_t fname_length = bdk_le16_to_cpu(*(uint16_t*)(ptr+6));
        uint32_t fdata_length = bdk_le32_to_cpu(*(uint32_t*)(ptr+8));
        const char *fname_ptr = ptr+12;
        const char *fdata_ptr = fname_ptr + fname_length;
        ptr = fdata_ptr + fdata_length;
    }
    return bdk_ptr_to_phys((char*)ptr);
}

static void *rom_open(const char *name, int flags)
{
    return (void*)find_file(name);
}

static int rom_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    unsigned int pos = handle->location;
    const char *fptr = handle->fs_state;
    uint16_t fname_length = bdk_le16_to_cpu(*(uint16_t*)(fptr+6));
    uint32_t fdata_length = bdk_le32_to_cpu(*(uint32_t*)(fptr+8));
    const char *fname_ptr = fptr+12;
    const char *fdata_ptr = fname_ptr + fname_length;

    if (pos > fdata_length)
        return -1;
    else if (pos == fdata_length)
        return 0;

    int count = length;
    if (pos + count > fdata_length)
        count = fdata_length - pos;

    memcpy(buffer, fdata_ptr + pos, count);
    return count;
}

static int rom_list(const char *path, __bdk_fs_list_callback callback, void *callback_state)
{
   extern void _end();
   const char *ptr = (const char *)&_end;
   if (NULL == callback) return -1;
#define _BUF_LEN 512
   char *buf = malloc(_BUF_LEN);
   if (NULL == buf) return -1;
   while (memcmp(ptr, "ROM-FS", 6) == 0)
   {
       uint16_t fname_length = bdk_le16_to_cpu(*(uint16_t*)(ptr+6));
       uint32_t fdata_length = bdk_le32_to_cpu(*(uint32_t*)(ptr+8));
       const char *fname_ptr = ptr+12;
       snprintf(buf,_BUF_LEN, "%.*s",fname_length,fname_ptr);
       buf[_BUF_LEN-1] = '\0';
       callback(buf,callback_state);
       const char *fdata_ptr = fname_ptr + fname_length;
       ptr = fdata_ptr + fdata_length;
   }
   free(buf);
   return 0;
}

static const __bdk_fs_ops_t bdk_fs_rom_ops =
{
    .stat = NULL,
    .unlink = NULL,
    .open = rom_open,
    .close = NULL,
    .read = rom_read,
    .write = NULL,
    .list = rom_list,
};

int __bdk_fs_rom_init(void)
{
    return bdk_fs_register("/rom/", &bdk_fs_rom_ops);
}
