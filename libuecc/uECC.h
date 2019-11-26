/* Copyright 2014, Kenneth MacKay. Licensed under the BSD 2-clause license. */

#ifndef _MICRO_ECC_H_
#define _MICRO_ECC_H_

#include <stdint.h>

/* Platform selection options.
If uECC_PLATFORM is not defined, the code will try to guess it based on compiler macros.
Possible values for uECC_PLATFORM are defined below: */
#define uECC_arch_other 0
#define uECC_x86        1
#define uECC_x86_64     2
#define uECC_arm        3
#define uECC_arm_thumb  4
#define uECC_avr        5

#define uECC_PLATFORM uECC_arm


/* If desired, you can define uECC_WORD_SIZE as appropriate for your platform (1, 4, or 8 bytes).
If uECC_WORD_SIZE is not explicitly defined then it will be automatically set based on your platform. */

#define uECC_WORD_SIZE 8

/* Inline assembly options.
uECC_asm_none  - Use standard C99 only.
uECC_asm_small - Use GCC inline assembly for the target platform (if available), optimized for minimum size.
uECC_asm_fast  - Use GCC inline assembly optimized for maximum speed. */
#define uECC_asm_none  0
#define uECC_asm_small 1
#define uECC_asm_fast  2

#define uECC_ASM uECC_asm_none

/* Curve selection options. */
#define uECC_secp160r1 1
#define uECC_secp192r1 2
#define uECC_secp256r1 3
#define uECC_secp256k1 4

#define uECC_CURVE  uECC_secp256r1


/* uECC_SQUARE_FUNC - If enabled (defined as nonzero), this will cause a specific function to be used for (scalar) squaring
    instead of the generic multiplication function. This will make things faster by about 8% but increases the code size. */
#define uECC_SQUARE_FUNC 0

#define uECC_CONCAT1(a, b) a##b
#define uECC_CONCAT(a, b) uECC_CONCAT1(a, b)

#define uECC_size_1 20 /* secp160r1 */
#define uECC_size_2 24 /* secp192r1 */
#define uECC_size_3 32 /* secp256r1 */
#define uECC_size_4 32 /* secp256k1 */

#define uECC_BYTES uECC_CONCAT(uECC_size_, uECC_CURVE)

#ifdef __cplusplus
extern "C"
{
#endif

/* uECC_verify() function.
Verify an ECDSA signature.

Usage: Compute the hash of the signed data using the same hash as the signer and
pass it to this function along with the signer's public key and the signature values (r and s).

Inputs:
    p_publicKey - The signer's public key
    p_hash      - The hash of the signed data.
    p_signature - The signature value.

Returns 1 if the signature is valid, 0 if it is invalid.
*/
int uECC_verify(const uint8_t p_publicKey[uECC_BYTES*2], const uint8_t p_hash[uECC_BYTES], const uint8_t p_signature[uECC_BYTES*2]);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* _MICRO_ECC_H_ */
