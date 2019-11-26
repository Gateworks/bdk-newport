/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include <libfdt.h>
#include "libuecc/uECC.h"
#include "liblzma/LzmaDec.h"
#include "libbdk-arch/bdk-csrs-fusf.h"

typedef struct
{
    uint64_t random[7];     /* Unused, makes signature more secure */
    uint64_t nv_counter;    /* Trust NV counter for this public key, little endian */
    uint64_t pub_key[8];    /* Public EC 256p key, two 256 but little endian numbers */
} bdk_signed_pub_key_t;

static uint64_t bdk_public_signing_key[8];

/**
 * Read data from a signed and possibly encrypted file. As we load the file we
 * need to AES decrypt it and keep a running SHA256. The SHA256 will then be
 * checked against the signature when we're done loading.
 *
 * @param inf     File to read from
 * @param aes_key AES decryption key, or NULL if not using AES
 * @param aes_iv  AES initialization / state vector
 * @param sha256_state
 *                Running state of the SHA256
 * @param buffer  Buffer to read into
 * @param buffer_size
 *                Size of the buffer. The buffer must have room for a full AES block
 *
 * @return Number of bytes read, output of fread()
 */
static int get_more_data(FILE *inf, const void *aes_key, uint64_t aes_iv[2], bdk_sha256_state_t *sha256_state, void *buffer, int buffer_size)
{
    /* Read data from the file */
    int read_size = fread(buffer, 1, buffer_size, inf);
    if (read_size <= 0)
        return read_size;
    /* Perform AES decrypt if necessary  */
    if (aes_key)
        bdk_aes128cbc_decrypt(aes_key, buffer, read_size, aes_iv);
    /* Update the SHA256 of the data */
    if (sha256_state)
        bdk_sha256_update(sha256_state, buffer, read_size);
    return read_size;
}

/**
 * Load the signature for a file
 *
 * @param basefile  Filename we need the signature for. A ".sign" is appended
 * @param signature Location to store the signature
 * @param signature_size
 *                  Size of the signature
 *
 * @return Zero on success, negative on failure
 */
static int load_signature(const void *aes_key, const char *basefile, void *signature, int signature_size)
{
    char filename[strlen(basefile)+ 6];
    strcpy(filename, basefile);
    strcat(filename, ".sign");

    if (signature_size != 64)
    {
        bdk_error("Load: %s: Signature buffer size incorrect\n", filename);
        return -1;
    }

    FILE *inf = fopen(filename, "rb");
    if (!inf)
    {
        bdk_error("Load: %s: Unable to open signature\n", filename);
        return -1;
    }

    uint8_t buffer[128] = { 0, };
    int read_size = fread(buffer, 1, sizeof(buffer), inf);
    fclose(inf);
    if (read_size < 70)
    {
        bdk_error("Load: %s: Signature read too small\n", filename);
        return -1;
    }

    uint64_t aes_iv[2] = {0, 0};
    if (aes_key)
        bdk_aes128cbc_decrypt(aes_key, buffer, read_size, aes_iv);

    /* Signature is a ASN.1 SEQUENCE(0x30) of two INTEGER(0x02). The
       INTEGER are 32 bytes, but may have the MSB set which causes them
       to be negative. In this case ASN.1 adds a zero byte before the
       INTEGER. The total ASN.1 Sequence should be:
        0x30: SEQUENCE start TAG
        0xXX: Length of the sequnce in bytes
        0x02: INTEGER start TAG
        0xXX: Length of the integer in bytes
        0x00: Optional, added if INTEGER MSB is set
           *: Data
        0x02: INTEGER start TAG
        0xXX: Length of the integer in bytes
        0x00: Optional, added if INTEGER MSB is set
           *: Data */
    int buf_loc = 0;
    /* Read SEQUENCE start TAG */
    int sequence = buffer[buf_loc++];
    if (sequence != 0x30)
    {
        bdk_error("Load: %s: Wrong sequence start tag\n", filename);
        return -1;
    }
    /* Read SEQUENCE length */
    int sequence_len = buffer[buf_loc++];
    if ((sequence_len < 44) || (sequence_len > 70))
    {
        bdk_error("Load: %s: Wrong sequence length\n", filename);
        return -1;
    }
    /* Read INTEGER start TAG */
    int int_tag = buffer[buf_loc++];
    if (int_tag != 0x02)
    {
        bdk_error("Load: %s: Wrong integer tag #1\n", filename);
        return -1;
    }
    /* Read INTEGER length. Length is variable based on leading zeros.
       Technically it could be all the way down to 1 byte, but 20 byte
       seems to be a good check to make sure nothing is bad */
    int int_len = buffer[buf_loc++];
    if ((int_len < 20) || (int_len > 33))
    {
        bdk_error("Load: %s: Wrong integer length #1\n", filename);
        return -1;
    }
    /* Squash leading zero */
    if (int_len == 33)
    {
        int zero = buffer[buf_loc++];
        if (zero)
        {
            bdk_error("Load: %s: Leading zero not zero #1\n", filename);
            return -1;
        }
        int_len--;
    }
    /* Read first integer */
    if (int_len < 32)
        memset(signature, 0, 32 - int_len);
    memcpy(signature + 32 - int_len, buffer + buf_loc, int_len);
    buf_loc += int_len;
    /* Read INTEGER start TAG */
    int_tag = buffer[buf_loc++];
    if (int_tag != 0x02)
    {
        bdk_error("Load: %s: Wrong integer tag #2\n", filename);
        return -1;
    }
    /* Read INTEGER length. Length is variable based on leading zeros.
       Technically it could be all the way down to 1 byte, but 20 byte
       seems to be a good check to make sure nothing is bad */
    int_len = buffer[buf_loc++];
    if ((int_len < 20) || (int_len > 33))
    {
        bdk_error("Load: %s: Wrong integer length #2\n", filename);
        return -1;
    }
    /* Squash leading zero */
    if (int_len == 33)
    {
        int zero = buffer[buf_loc++];
        if (zero)
        {
            bdk_error("Load: %s: Leading zero not zero #2\n", filename);
            return -1;
        }
        int_len--;
    }
    /* Read second integer */
    if (int_len < 32)
        memset(signature + 32, 0, 32 - int_len);
    memcpy(signature + 64 - int_len, buffer + buf_loc, int_len);

    /* The signature is two 256 bit numbers in big endian format. The
       ECC library we use expects the numbers in 64bit native endian
       format, with little endian between 64bit words */
    uint64_t *ptr = signature;
    for (int i = 0; i < 2; i++)
    {
        /* First 256 bit number */
        uint64_t tmp = bdk_be64_to_cpu(ptr[i]);
        ptr[i] = bdk_be64_to_cpu(ptr[3 - i]);
        ptr[3 - i] = tmp;
        /* Second 256 bit number */
        tmp = bdk_be64_to_cpu(ptr[4 + i]);
        ptr[4 + i] = bdk_be64_to_cpu(ptr[7 - i]);
        ptr[7 - i] = tmp;
    }
    return 0;
}

/**
 * Verify a signature for a file
 *
 * @param filename  Filename to verify. File was already loaded, so this is just informational
 * @param sha256    SHA256 hash of the file's contents
 * @param signature Signature of the file using ECDSA
 *
 * @return Zero on success, negative on failure
 */
static int verify_signature(const char *filename, void *sha256, const void *signature)
{
    const void *public_key = bdk_public_signing_key;
    if (!bdk_public_signing_key[0])
    {
        uint64_t addr = bdk_config_get_int(BDK_CONFIG_TRUST_ROT_ADDR);
        if (addr)
            public_key = bdk_phys_to_ptr(addr);
    }

    /* Public key is in CSIB format, two little endian numbers. The
       volatile is so the compiler always uses 8 bytes read from key
       memory */
    const volatile uint64_t *p = (void*)public_key;
    BDK_TRACE(INIT,
        "Load: %s: Public Key Qx: (MSB)%016lx %016lx %016lx %016lx(LSB) Qy: (MSB)%016lx %016lx %016lx %016lx(LSB)\n",
        filename, bdk_le64_to_cpu(p[3]), bdk_le64_to_cpu(p[2]),
        bdk_le64_to_cpu(p[1]), bdk_le64_to_cpu(p[0]),
        bdk_le64_to_cpu(p[7]), bdk_le64_to_cpu(p[6]),
        bdk_le64_to_cpu(p[5]), bdk_le64_to_cpu(p[4]));
    p = sha256;
    /* Hash is a byte array, show big endian to fix swapping to match
       Linux's "sha256sum" output */
    BDK_TRACE(INIT, "Load: %s: SHA256 %016lx %016lx %016lx %016lx\n", filename,
        bdk_cpu_to_be64(p[0]), bdk_cpu_to_be64(p[1]),
        bdk_cpu_to_be64(p[2]), bdk_cpu_to_be64(p[3]));
    /* Signature is two little endian numbers */
    p = signature;
    BDK_TRACE(INIT, "Load: %s: Signature Qx: (MSB)%016lx %016lx %016lx %016lx(LSB) Qy: (MSB)%016lx %016lx %016lx %016lx(LSB)\n",
        filename, bdk_le64_to_cpu(p[3]), bdk_le64_to_cpu(p[2]),
        bdk_le64_to_cpu(p[1]), bdk_le64_to_cpu(p[0]),
        bdk_le64_to_cpu(p[7]), bdk_le64_to_cpu(p[6]),
        bdk_le64_to_cpu(p[5]), bdk_le64_to_cpu(p[4]));
    int valid = uECC_verify(public_key, (void*)sha256, signature);
    return (valid == 1) ? 0 : -1;
}

/**
 * Needed to support LZMA memory allocation
 *
 * @param p
 * @param size
 *
 * @return
 */
static void *SzAlloc(void *p, size_t size)
{
    return malloc(size);
}

/**
 * Needed to support LZMA memory free
 *
 * @param p
 * @param size
 *
 * @return
 */
static void SzFree(void *p, void *address)
{
    free(address);
}

/**
 * Uncompress a file using LZMA
 *
 * @param inf        File to load data from
 * @param in_buffer  Input buffer for file reads
 * @param in_buffer_size
 *                   Size of the input buffer. It is assumed the buffer already contains this amount
 *                   of data.
 * @param used_count Number of bytes in the input buffer that were used by the LZMA header. The rest
 *                   of the input buffer contains compressed data.
 * @param out_data   Pointer to write the output data to
 * @param out_size   Size of the output buffer
 * @param aes_key    AES decryption key, or NULL if not using AES
 * @param aes_iv     AES initialization / state vector
 * @param sha256_state
 *                   Running state of the SHA256
 *
 * @return Zero on success, negative on failure
 */
static int unlzma(FILE *inf, void *in_buffer, int in_buffer_size, int used_count,
    void *out_data, int out_size, const void *aes_key, uint64_t aes_iv[2],
    bdk_sha256_state_t *sha256_state)
{
    ISzAlloc alloc = { SzAlloc, SzFree };
    CLzmaDec state;
    LzmaDec_Construct(&state);
    SRes res = LzmaDec_Allocate(&state, in_buffer, LZMA_PROPS_SIZE, &alloc);
    if (res != SZ_OK)
    {
        bdk_error("Load: LZMA failed memory alloc (result=%d)\n", res);
        return -1;
    }

    LzmaDec_Init(&state);
    size_t inLen = in_buffer_size - used_count;
    void *src = in_buffer + used_count;
    size_t srcLen = in_buffer_size - used_count;
    void *dest = out_data;
    size_t destLen = out_size;
    while (1)
    {
        if (inLen == 0)
        {
            inLen = get_more_data(inf, aes_key, aes_iv, sha256_state, in_buffer, in_buffer_size);
            if (inLen <= 0)
            {
                bdk_error("Load: LZMA file read failed\n");
                goto out_lzma;
            }
            src = in_buffer;
            srcLen = inLen;
        }

        ELzmaFinishMode finishMode = LZMA_FINISH_ANY;
        ELzmaStatus status;
        res = LzmaDec_DecodeToBuf(&state, dest, &destLen, src, &srcLen, finishMode, &status);

        if (res != SZ_OK)
            goto out_lzma;

        if ((status == LZMA_STATUS_FINISHED_WITH_MARK) ||
            (status == LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK))
            break;

        inLen -= srcLen;
        src += srcLen;
        srcLen = inLen;
        dest += destLen;
        destLen = out_data + out_size - dest;
    }
    LzmaDec_Free(&state, &alloc);
    return 0;

out_lzma:
    LzmaDec_Free(&state, &alloc);
    return -1;
}

/**
 * Load a file and verify its signature. If the file is encrypted, it is
 * decrypted. If the file is compressed, it is decompressed.
 *
 * @param filename  File to load
 * @param loc       Offset into file for image. This is normally zero for normal files. Device
 *                  files, such as /dev/mem, will use this to locate the image.
 * @param data_type Type of data in the file, enumerated by bdk_signed_data_t. This is required
 *                  so the code can determine the file size before loading the whole file.
 * @param flags     Flags for controlling file loading
 * @param filesize  Set the size of the file if the file is loaded properly. If load fails, set to
 *                  zero.
 *
 * @return Pointer to the data from the file, or NULL on failure
 */
void *bdk_signed_load(const char *filename, uint64_t loc, bdk_signed_data_t data_type, bdk_signed_flags_t flags, uint64_t *filesize)
{
    static void *bssk_ptr = NULL; /* Pointer to BSSK key, saved for speed */

    /* Set the file size to zero in case of failure */
    *filesize = 0;

    /* Variables used for AES and SHA256 */
    uint64_t aes_iv[2] = { 0, 0 };
    bdk_sha256_state_t sha256_info;
    bdk_sha256_state_t *sha256_state;
    const void *aes_key;

    /* Use the trust level to determine the SHA256 and AES needs */
    switch (bdk_trust_get_level())
    {
        case BDK_TRUST_LEVEL_NONE:
            aes_key = NULL;
            sha256_state = NULL;
            break;
        case BDK_TRUST_LEVEL_SIGNED:
            aes_key = NULL;
            sha256_state = &sha256_info;
            break;
        case BDK_TRUST_LEVEL_SIGNED_SSK:
            aes_key = bdk_phys_to_ptr(bdk_numa_get_address(bdk_numa_master(), BDK_FUSF_SSKX(0)));
            sha256_state = &sha256_info;
            break;
        case BDK_TRUST_LEVEL_SIGNED_BSSK:
            if (!bssk_ptr)
            {
                uint64_t addr = bdk_config_get_int(BDK_CONFIG_TRUST_BSSK_ADDR);
                if (!addr)
                {
                    bdk_error("Load: %s: No BSSK\n", filename);
                    return NULL;
                }
                bssk_ptr = bdk_phys_to_ptr(addr);
            }
            aes_key = bssk_ptr;
            sha256_state = &sha256_info;
            break;
        default:
            bdk_error("Load: %s: Unexpected trust level\n", filename);
            return NULL;
    }

    if (flags & BDK_SIGNED_FLAG_NOT_ENCRYPTED)
        aes_key = NULL;
    if (flags & BDK_SIGNED_FLAG_ALLOW_UNSIGNED)
        sha256_state = NULL;

    /* Init the SHA256 state */
    if (sha256_state)
        bdk_sha256_init(sha256_state);

    /* Check if the file should be decompressed or not  */
    bool compressed = (strstr(filename, ".lzma") != NULL);

    /* Open the file */
    FILE *inf = fopen(filename, "rb");
    if (!inf)
    {
        BDK_TRACE(INIT, "Load: %s: File doesn't exist\n", filename);
        return NULL;
    }

    if (loc)
    {
        BDK_TRACE(INIT, "Load: %s: Loading file at offset 0x%lx\n", filename, loc);
        /* Seek to the start location */
        if (fseek(inf, loc, SEEK_SET) != 0)
        {
            bdk_error("Load: %s: Unable to seek to %lu\n", filename, loc);
            fclose(inf);
            return NULL;
        }
    }
    else
    {
        BDK_TRACE(INIT, "Load: %s: Loading file\n", filename);
    }

    /* Read the first block to determine the file size */
    char read_data[512];
    int read_size = get_more_data(inf, aes_key, aes_iv, sha256_state, read_data, sizeof(read_data));
    if (read_size <= 0)
    {
        bdk_error("Load: %s: Read failed\n", filename);
        fclose(inf);
        return NULL;
    }

    long file_size;     /* Total file size after load completes */
    int used_size;      /* Number of bytes from initial read to throw away after header used */
    if (compressed)
    {
        BDK_TRACE(INIT, "Load: %s: File is compressed\n", filename);
        /* File size is in the LZMA header  */
        CLzmaProps p;
        SRes res = LzmaProps_Decode(&p, (void*)read_data, read_size);
        if (res != SZ_OK)
        {
            bdk_error("Load: %s: LZMA header invalid\n", filename);
            fclose(inf);
            return NULL;
        }
        file_size = bdk_le64_to_cpu(*(uint64_t *)(read_data + LZMA_PROPS_SIZE));
        used_size = LZMA_PROPS_SIZE + sizeof(uint64_t);
    }
    else if (data_type == BDK_SIGNED_IMAGE)
    {
        /* File size is in the bdk_image_header_t header */
        const bdk_image_header_t *header = (bdk_image_header_t *)read_data;
        if (!bdk_image_header_is_valid(header))
        {
            fclose(inf);
            BDK_TRACE(INIT, "Load: %s: Image header invalid\n", filename);
            return NULL;
        }
        BDK_TRACE(INIT, "Load: %s: File is a code image\n", filename);
        file_size = header->length;
        used_size = 0;
        if (sha256_state)
        {
            /* Files are always padded to AES keysize chunks */
            file_size = (file_size + 15) & -16;
        }
    }
    else if (data_type == BDK_SIGNED_DTS)
    {
        BDK_TRACE(INIT, "Load: %s: File is a device tree\n", filename);
        /* File size is in the device tree header */
        const struct fdt_header *fdt = (struct fdt_header *)read_data;
        if (fdt_check_header(fdt))
        {
            bdk_error("Load: %s FDT header invalid\n", filename);
            fclose(inf);
            return NULL;
        }
        file_size = fdt_totalsize(fdt);
        used_size = 0;
        if (sha256_state)
        {
            /* Files are always padded to AES keysize chunks */
            file_size = (file_size + 15) & -16;
        }
    }
    else if (data_type == BDK_SIGNED_PUB_KEY)
    {
        file_size = sizeof(bdk_signed_pub_key_t);
        used_size = 0;
    }
    else
    {
        /* Unknown file type, we can't determine the size */
        bdk_error("Load: %s: Unsupported file type\n", filename);
        fclose(inf);
        return NULL;
    }

    if ((file_size <= 0) || (file_size > (1 << 30)))
    {
        bdk_error("Load: %s: Invalid file size %ld\n", filename, file_size);
        fclose(inf);
        return NULL;
    }

    /* Allocate a 4KB aligned block for the file. The 4KB alignment
       is in case this is code. ADRP needs alignment */
    void *data = memalign(4096, file_size);
    if (!data)
    {
        bdk_error("Load: %s: Memory allocation failed\n", filename);
        fclose(inf);
        return NULL;
    }

    /* Read the rest of the data */
    int read_so_far = read_size - used_size;
    if (read_so_far > file_size)
        read_so_far = file_size;
    if (compressed)
    {
        int status = unlzma(inf, read_data, read_size, used_size, data, file_size, aes_key, aes_iv, sha256_state);
        if (status == 0)
            read_size = file_size - read_so_far;
        else
            read_size = -1;
    }
    else
    {
        /* Copy already loaded data */
        memcpy(data, read_data + used_size, read_so_far);
        /* Read the rest of the file */
        if (file_size > read_so_far)
            read_size = get_more_data(inf, aes_key, aes_iv, sha256_state, data + read_so_far, file_size - read_so_far);
        else
            read_size = 0;
    }

    /* Close the file all reads are done */
    fclose(inf);

    /* Make sure the final size is correct */
    if (read_size + read_so_far < file_size)
    {
        bdk_error("Load: %s: Load failed\n", filename);
        free(data);
        return NULL;
    }

    BDK_TRACE(INIT, "Load: %s: File load complete\n", filename);

    /* Skip signature check if we didn't calculate the SHA256 */
    if (sha256_state == NULL)
    {
        *filesize = file_size;
        /* Add image attestation info to configuration item */
        bdk_add_img_attestation_info(filename, loc, NULL, 0);
        return data;
    }

    /* Finish the SHA256 */
    void *hash = bdk_sha256_finish(sha256_state);

    BDK_TRACE(INIT, "Load: %s: Loading signing key signature\n", filename);

    /* Load the signature for this file */
    uint8_t p_signature[uECC_BYTES*2];
    int status = load_signature(aes_key, filename, p_signature, sizeof(p_signature));
    if (status)
    {
        bdk_error("Load: %s: Signature read failed\n", filename);
        free(data);
        return NULL;
    }

    BDK_TRACE(INIT, "Load: %s: Verifying signature\n", filename);

    /* Verify signature */
    status = verify_signature(filename, hash, p_signature);
    if (status)
    {
        bdk_error("Load: %s: Signing verification failed\n", filename);
        free(data);
        return NULL;
    }

    BDK_TRACE(INIT, "Load: %s: Signature good\n", filename);

    /* Add image attestation info to configuration item */
    bdk_add_img_attestation_info(filename, loc, hash, sizeof(sha256_state->s));

    /* Signature good */
    *filesize = file_size;
    return data;
}

/**
 * Load the BDK's public signing key, which is signed by the Root of Trust
 *
 * @return Zero on success, negative on failure
 */
int bdk_signed_load_public(void)
{
    const char *filename = "/fatfs/bdk-sign.pub";

    uint64_t data_size = 0;
    bdk_signed_pub_key_t *data = bdk_signed_load(filename, 0,
        BDK_SIGNED_PUB_KEY, BDK_SIGNED_FLAG_NONE, &data_size);
    if (!data)
        return -1;
    if (data_size != sizeof(bdk_signed_pub_key_t))
    {
        free(data);
        bdk_error("Load: %s: Invalid file size\n", filename);
        return -1;
    }

    BDK_TRACE(INIT, "Load: %s: Checking NV counter\n", filename);

    /* Make sure the NV counter is the correct value. The hardware
       fuses should have already been update for the CSIB NV counter */
    uint64_t hw_nv = bdk_trust_get_nv_counter();
    uint64_t nv = bdk_le64_to_cpu(data->nv_counter);
    if (nv != hw_nv)
    {
        free(data);
        bdk_error("Load: %s: Invalid NV counter\n", filename);
        return -1;
    }
    BDK_TRACE(INIT, "Load: %s: Public key verfied and loaded\n", filename);
    /* Public key is already two little endian numbers  */
    for (int i = 0; i < 8; i++)
        bdk_public_signing_key[i] = bdk_le64_to_cpu(data->pub_key[i]);
    free(data);
    return 0;
}

