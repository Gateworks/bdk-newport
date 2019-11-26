/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include <ctype.h>

#define HEADER_MAGIC 0x58544e4f4554434fL

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
 * @param handle File handle to read from
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

    fatfs_diskio_shutdown();

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
        /* Software wants the watchdog running with a 15 second timeout */
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

/**
 * Append file information to the BDK_CONFIG_ATTESTATION_IMAGE_LIST.
 *
 * @param filename Filename that was loaded
 * @param loc      Offset into the file, generally zero except for direct flash access
 * @param hash     A [SHA256] image hash or NULL if no hash is available
 * @param hash_len Length of image hash (provided for completeness)
 */
void bdk_add_img_attestation_info(const char *filename, uint64_t loc, uint8_t *hash, int hash_len)
{
    /* Append "filename@loc:hash" to the Attestation information. */
    int name_len = strlen(filename);
    /* The @loc is dropped if loc is zero. Otherwise show 8 hex digits */
    int loc_len = (loc) ? 9 : 0;
    /* Show the hash in hex, or zero if no hash */
    int h_len = (hash_len) ? 2 * hash_len : 1;
    /* Need a tmp variable for the string to append */
    char tmp[name_len + loc_len + 1 + h_len + 1];
    /* Fill the append string */
    char *pos = tmp;
    strcpy(tmp, filename);
    pos += name_len;
    if (loc)
        pos += sprintf(pos, "@%08lx", loc);
    *pos++ = ':';
    if (hash_len)
    {
        for (int idx = 0; idx < hash_len; idx++)
            pos += sprintf(pos, "%02x", hash[idx]);
    }
    else
        *pos++ = '0';
    *pos++ = 0;
    bdk_config_append_str(tmp, BDK_CONFIG_ATTESTATION_IMAGE_LIST);
}
