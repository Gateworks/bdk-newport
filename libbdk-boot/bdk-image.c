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
#include <malloc.h>
#include <ctype.h>

#define HEADER_MAGIC 0x585245444e554854L

/**
 * Validate image header
 *
 * @param header Header to validate
 *
 * @return 1 if header is valid, zero if invalid
 */
int bdk_image_header_is_valid(const bdk_image_header_t *header)
{
    /* First instruction can't be zero */
    int bad = (header->instruction == 0);
    /* Make sure the length is somewhat sane. 1GB is an arbitrary limit */
    bad |= (header->length <= sizeof(*header)) || (header->length > 1<<30);
    /* Check the magic number */
    bad |= (header->magic != HEADER_MAGIC);
    /* No constraints on CRC */
    /* Reserved space must be zero */
    bad |= (header->reserved1 != 0);
    /* Name must not be empty and must end in a zero */
    bad |= (header->name[0] == 0) || (header->name[63] != 0);
    /* Version must not be empty and must end in a zero */
    bad |= (header->version[0] == 0) || (header->version[31] != 0);
    /* Reserved space must be zero */
    for (int i = 0; i < 17; i++)
        bad |= (header->reserved[i] != 0);
    return !bad;
}

/**
 * Verify image at the given address is good
 *
 * @param image  Pointer to the image
 *
 * @return Zero on success, negative on failure
 */
int bdk_image_verify(const void *image)
{
    const bdk_image_header_t *header = image;
    if (!bdk_image_header_is_valid(image))
        return -1;

    uint32_t crc = bdk_crc32(image, 16, 0);
    uint32_t zero = 0;
    crc = bdk_crc32(&zero, 4, crc);
    crc = bdk_crc32(image + 20, header->length - 20, crc);

    if (crc == header->crc32)
        return 0;
    else
        return -1;
}

/**
 * Read a image header from a file
 *
 * @param handle File handel to read from
 * @param header Pointer to header structure to fill
 *
 * @return Zero on success, negative on failure
 */
int bdk_image_read_header(FILE *handle, bdk_image_header_t *header)
{
    size_t count = fread(header, sizeof(*header), 1, handle);

    /* Check if read failed */
    if (count != 1)
        return -1;

    return !bdk_image_header_is_valid(header);
}

/**
 * Read a image from a file and boot it, replacing the current running BDK image
 *
 * @param filename   File to read the image from
 * @param loc        Offset into file for image. This is normally zero for normal files. Device
 *                   files, such as /dev/mem, will use this to locate the image.
 *
 * @return Negative on failure. On success this function never returns.
 */
int bdk_image_boot(const char *filename, uint64_t loc)
{
    if (loc)
        printf("    Loading image at %s:0x%lx\n", filename, loc);
    else
        printf("    Loading image file '%s'\n", filename);

    uint64_t filesize = 0;
    void *image = bdk_signed_load(filename, loc, BDK_SIGNED_IMAGE,
        BDK_SIGNED_FLAG_NONE, &filesize);
    if (!image)
        goto out;

    if (bdk_image_verify(image))
    {
        bdk_error("Image CRC32 is incorrect\n");
        goto out;
    }

    /* Putting all cores except this one in reset */
    for (bdk_node_t node = 0; node < BDK_NUMA_MAX_NODES; node++)
    {
        if (bdk_numa_exists(node))
        {
            if (node == bdk_numa_local())
                bdk_reset_cores(node, -2);
            else
                bdk_reset_cores(node, -1);
        }
    }

    printf("---\n");
    BDK_MB;

    if (bdk_watchdog_is_running())
    {
        /* Software wants the watchdog running with a 15 second timout */
        bdk_watchdog_set(15000);
    }

    bdk_jump_address(bdk_ptr_to_phys(image), 0, __bdk_config_export_to_mem());
    /* Should never get here */
    bdk_error("Failed to jump to image\n");
out:
    if (image)
        free(image);
    return -1;
}
