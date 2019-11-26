/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Utility functions for handling binary images
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup image Binary image utility functions
 * @{
 */

/**
 * Structure present at the beginning of BDK images
 */
typedef struct
{
    uint32_t    instruction;    /* Raw instruction for skipping header */
    uint32_t    length;         /* Length of the image, includes header */
    uint64_t    magic;          /* Magic string "OCTEONTX" */
    uint32_t    crc32;          /* CRC32 of image + header. These bytes are zero when calculating the CRC */
    uint32_t    reserved1;      /* Zero, reserved for future use */
    char        name[64];       /* ASCII Image name. Must always end in zero */
    char        version[32];    /* ASCII Version. Must always end in zero */
    uint64_t    reserved[17];   /* Zero, reserved for future use */
} BDK_LITTLE_ENDIAN_STRUCT bdk_image_header_t;

/**
 * Validate image header
 *
 * @param header Header to validate
 *
 * @return 1 if header is valid, zero if invalid
 */
extern int bdk_image_header_is_valid(const bdk_image_header_t *header);

/**
 * Verify image at the given address is good
 *
 * @param image  Pointer to the image
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_image_verify(const void *image);

/**
 * Read a image header from a file
 *
 * @param handle File handle to read from
 * @param header Pointer to header structure to fill
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_image_read_header(FILE *handle, bdk_image_header_t *header);

/**
 * Read a image from a file and boot it, replacing the current running BDK image
 *
 * @param filename   File to read the image from
 * @param loc        Offset into file for image. This is normally zero for normal files. Device
 *                   files, such as /dev/mem, will use this to locate the image.
 *
 * @return Negative on failure. On success this function never returns.
 */
extern int bdk_image_boot(const char *filename, uint64_t loc);

/**
 * Append file information to the BDK_CONFIG_ATTESTATION_IMAGE_LIST.
 *
 * @param filename Filename that was loaded
 * @param loc      Offset into the file, generally zero except for direct flash access
 * @param hash     A [SHA256] image hash or NULL if no hash is available
 * @param hash_len Length of image hash (provided for completeness)
 */
extern void bdk_add_img_attestation_info(const char *filename, uint64_t loc, uint8_t *hash, int hash_len);

/** @} */
