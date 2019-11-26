/* Copyright 2014, Kenneth MacKay. Licensed under the BSD 2-clause license. */

//#include "util.h"
#include <bdk.h>
#include "uECC.h"

#if __STDC_VERSION__ >= 199901L
    #define RESTRICT restrict
#else
    #define RESTRICT
#endif

#if defined(__SIZEOF_INT128__) || ((__clang_major__ * 100 + __clang_minor__) >= 302)
    #define SUPPORTS_INT128 1
#else
    #define SUPPORTS_INT128 0
#endif

#if (uECC_WORD_SIZE == 8)

typedef uint64_t uECC_word_t;
#if SUPPORTS_INT128
typedef unsigned __int128 uECC_dword_t;
#endif
typedef unsigned wordcount_t;
typedef int swordcount_t;
typedef int bitcount_t;
typedef int cmpresult_t;

#define HIGH_BIT_SET 0x8000000000000000ull
#define uECC_WORD_BITS 64
#define uECC_WORD_BITS_SHIFT 6
#define uECC_WORD_BITS_MASK 0x03F

#define uECC_WORDS_1 3
#define uECC_WORDS_2 3
#define uECC_WORDS_3 4
#define uECC_WORDS_4 4

#define uECC_N_WORDS_1 3
#define uECC_N_WORDS_2 3
#define uECC_N_WORDS_3 4
#define uECC_N_WORDS_4 4

#define Curve_P_1 {0xFFFFFFFF7FFFFFFFull, 0xFFFFFFFFFFFFFFFFull, 0x00000000FFFFFFFFull}
#define Curve_P_2 {0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFEull, 0xFFFFFFFFFFFFFFFFull}
#define Curve_P_3 {0xFFFFFFFFFFFFFFFFull, 0x00000000FFFFFFFFull, 0x0000000000000000ull, 0xFFFFFFFF00000001ull}
#define Curve_P_4 {0xFFFFFFFEFFFFFC2Full, 0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFFull}

#define Curve_B_1 {0x81D4D4ADC565FA45ull, 0x54BD7A8B65ACF89Full, 0x000000001C97BEFCull}
#define Curve_B_2 {0xFEB8DEECC146B9B1ull, 0x0FA7E9AB72243049ull, 0x64210519E59C80E7ull}
#define Curve_B_3 {0x3BCE3C3E27D2604Bull, 0x651D06B0CC53B0F6ull, 0xB3EBBD55769886BCull, 0x5AC635D8AA3A93E7ull}
#define Curve_B_4 {0x0000000000000007ull, 0x0000000000000000ull, 0x0000000000000000ull, 0x0000000000000000ull}

#define Curve_G_1 { \
    {0x68C38BB913CBFC82ull, 0x8EF5732846646989ull, 0x000000004A96B568ull}, \
    {0x042351377AC5FB32ull, 0x3168947D59DCC912ull, 0x0000000023A62855ull}}

#define Curve_G_2 { \
    {0xF4FF0AFD82FF1012ull, 0x7CBF20EB43A18800ull, 0x188DA80EB03090F6ull}, \
    {0x73F977A11E794811ull, 0x631011ED6B24CDD5ull, 0x07192B95FFC8DA78ull}}

#define Curve_G_3 { \
    {0xF4A13945D898C296ull, 0x77037D812DEB33A0ull, 0xF8BCE6E563A440F2ull, 0x6B17D1F2E12C4247ull}, \
    {0xCBB6406837BF51F5ull, 0x2BCE33576B315ECEull, 0x8EE7EB4A7C0F9E16ull, 0x4FE342E2FE1A7F9Bull}}

#define Curve_G_4 { \
    {0x59F2815B16F81798, 0x029BFCDB2DCE28D9, 0x55A06295CE870B07, 0x79BE667EF9DCBBAC}, \
    {0x9C47D08FFB10D4B8, 0xFD17B448A6855419, 0x5DA4FBFC0E1108A8, 0x483ADA7726A3C465}}

#define Curve_N_1 {0xF927AED3CA752257ull, 0x000000000001F4C8ull, 0x0000000100000000ull}
#define Curve_N_2 {0x146BC9B1B4D22831ull, 0xFFFFFFFF99DEF836ull, 0xFFFFFFFFFFFFFFFFull}
#define Curve_N_3 {0xF3B9CAC2FC632551ull, 0xBCE6FAADA7179E84ull, 0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFF00000000ull}
#define Curve_N_4 {0xBFD25E8CD0364141, 0xBAAEDCE6AF48A03B, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF}

#endif /* (uECC_WORD_SIZE == 8) */

#define uECC_WORDS uECC_CONCAT(uECC_WORDS_, uECC_CURVE)
#define uECC_N_WORDS uECC_CONCAT(uECC_N_WORDS_, uECC_CURVE)

typedef struct EccPoint
{
    uECC_word_t x[uECC_WORDS];
    uECC_word_t y[uECC_WORDS];
} EccPoint;

static uECC_word_t curve_p[uECC_WORDS] = uECC_CONCAT(Curve_P_, uECC_CURVE);
static EccPoint curve_G = uECC_CONCAT(Curve_G_, uECC_CURVE);
static uECC_word_t curve_n[uECC_N_WORDS] = uECC_CONCAT(Curve_N_, uECC_CURVE);

static void vli_clear(uECC_word_t *p_vli);
static uECC_word_t vli_isZero(const uECC_word_t *p_vli);
static uECC_word_t vli_testBit(const uECC_word_t *p_vli, bitcount_t p_bit);
static bitcount_t vli_numBits(const uECC_word_t *p_vli, wordcount_t p_maxWords);
static void vli_set(uECC_word_t *p_dest, const uECC_word_t *p_src);
static cmpresult_t vli_cmp(uECC_word_t *p_left, uECC_word_t *p_right);
static void vli_rshift1(uECC_word_t *p_vli);
static uECC_word_t vli_add(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right);
static uECC_word_t vli_sub(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right);
static void vli_mult(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right);
static void vli_modAdd(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right, uECC_word_t *p_mod);
static void vli_modSub(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right, uECC_word_t *p_mod);
static void vli_mmod_fast(uECC_word_t *RESTRICT p_result, uECC_word_t *RESTRICT p_product);
static void vli_modMult_fast(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right);
static void vli_modInv(uECC_word_t *p_result, uECC_word_t *p_input, uECC_word_t *p_mod);
#if uECC_SQUARE_FUNC
static void vli_square(uECC_word_t *p_result, uECC_word_t *p_left);
static void vli_modSquare_fast(uECC_word_t *p_result, uECC_word_t *p_left);
#endif

#ifdef __GNUC__ /* Only support GCC inline asm for now */
    #if (uECC_ASM && (uECC_PLATFORM == uECC_avr))
        #include "asm_avr.inc"
    #endif

    #if (uECC_ASM && (uECC_PLATFORM == uECC_arm || uECC_PLATFORM == uECC_arm_thumb || uECC_PLATFORM == uECC_arm_thumb2))
        #include "asm_arm.inc"
    #endif
#endif

static void vli_clear(uECC_word_t *p_vli)
{
    wordcount_t i;
    for(i = 0; i < uECC_WORDS; ++i)
    {
        p_vli[i] = 0;
    }
}

/* Returns 1 if p_vli == 0, 0 otherwise. */
static uECC_word_t vli_isZero(const uECC_word_t *p_vli)
{
    wordcount_t i;
    for(i = 0; i < uECC_WORDS; ++i)
    {
        if(p_vli[i])
        {
            return 0;
        }
    }
    return 1;
}

/* Returns nonzero if bit p_bit of p_vli is set. */
static uECC_word_t vli_testBit(const uECC_word_t *p_vli, bitcount_t p_bit)
{
    return (p_vli[p_bit >> uECC_WORD_BITS_SHIFT] & ((uECC_word_t)1 << (p_bit & uECC_WORD_BITS_MASK)));
}

/* Counts the number of words in p_vli. */
static wordcount_t vli_numDigits(const uECC_word_t *p_vli, wordcount_t p_maxWords)
{
    swordcount_t i;
    /* Search from the end until we find a non-zero digit.
       We do it in reverse because we expect that most digits will be nonzero. */
    for(i = p_maxWords-1; i >= 0 && p_vli[i] == 0; --i)
    {
    }

    return (i + 1);
}

/* Counts the number of bits required to represent p_vli. */
static bitcount_t vli_numBits(const uECC_word_t *p_vli, wordcount_t p_maxWords)
{
    uECC_word_t i;
    uECC_word_t l_digit;

    wordcount_t l_numDigits = vli_numDigits(p_vli, p_maxWords);
    if(l_numDigits == 0)
    {
        return 0;
    }

    l_digit = p_vli[l_numDigits - 1];
    for(i = 0; l_digit; ++i)
    {
        l_digit >>= 1;
    }

    return (((bitcount_t)(l_numDigits - 1) << uECC_WORD_BITS_SHIFT) + i);
}

/* Sets p_dest = p_src. */
static void vli_set(uECC_word_t *p_dest, const uECC_word_t *p_src)
{
    wordcount_t i;
    for(i=0; i<uECC_WORDS; ++i)
    {
        p_dest[i] = p_src[i];
    }
}

/* Returns sign of p_left - p_right. */
static cmpresult_t vli_cmp(uECC_word_t *p_left, uECC_word_t *p_right)
{
    swordcount_t i;
    for(i = uECC_WORDS-1; i >= 0; --i)
    {
        if(p_left[i] > p_right[i])
        {
            return 1;
        }
        else if(p_left[i] < p_right[i])
        {
            return -1;
        }
    }
    return 0;
}

/* Computes p_vli = p_vli >> 1. */
static void vli_rshift1(uECC_word_t *p_vli)
{
    uECC_word_t *l_end = p_vli;
    uECC_word_t l_carry = 0;

    p_vli += uECC_WORDS;
    while(p_vli-- > l_end)
    {
        uECC_word_t l_temp = *p_vli;
        *p_vli = (l_temp >> 1) | l_carry;
        l_carry = l_temp << (uECC_WORD_BITS - 1);
    }
}

/* Computes p_result = p_left + p_right, returning carry. Can modify in place. */
static uECC_word_t vli_add(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right)
{
    uECC_word_t l_carry = 0;
    wordcount_t i;
    for(i = 0; i < uECC_WORDS; ++i)
    {
        uECC_word_t l_sum = p_left[i] + p_right[i] + l_carry;
        if(l_sum != p_left[i])
        {
            l_carry = (l_sum < p_left[i]);
        }
        p_result[i] = l_sum;
    }
    return l_carry;
}

/* Computes p_result = p_left - p_right, returning borrow. Can modify in place. */
static uECC_word_t vli_sub(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right)
{
    uECC_word_t l_borrow = 0;
    wordcount_t i;
    for(i = 0; i < uECC_WORDS; ++i)
    {
        uECC_word_t l_diff = p_left[i] - p_right[i] - l_borrow;
        if(l_diff != p_left[i])
        {
            l_borrow = (l_diff > p_left[i]);
        }
        p_result[i] = l_diff;
    }
    return l_borrow;
}

static void muladd(uECC_word_t a, uECC_word_t b, uECC_word_t *r0, uECC_word_t *r1, uECC_word_t *r2)
{
#if uECC_WORD_SIZE == 8 && !SUPPORTS_INT128
    uint64_t a0 = a & 0xffffffffull;
    uint64_t a1 = a >> 32;
    uint64_t b0 = b & 0xffffffffull;
    uint64_t b1 = b >> 32;

    uint64_t i0 = a0 * b0;
    uint64_t i1 = a0 * b1;
    uint64_t i2 = a1 * b0;
    uint64_t i3 = a1 * b1;

    uint64_t p0, p1;

    i2 += (i0 >> 32);
    i2 += i1;
    if(i2 < i1)
    { // overflow
        i3 += 0x100000000ull;
    }

    p0 = (i0 & 0xffffffffull) | (i2 << 32);
    p1 = i3 + (i2 >> 32);

    *r0 += p0;
    *r1 += (p1 + (*r0 < p0));
    *r2 += ((*r1 < p1) || (*r1 == p1 && *r0 < p0));
#else
    uECC_dword_t p = (uECC_dword_t)a * b;
    uECC_dword_t r01 = ((uECC_dword_t)(*r1) << uECC_WORD_BITS) | *r0;
    r01 += p;
    *r2 += (r01 < p);
    *r1 = r01 >> uECC_WORD_BITS;
    *r0 = (uECC_word_t)r01;
#endif
}

static void vli_mult(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right)
{
    uECC_word_t r0 = 0;
    uECC_word_t r1 = 0;
    uECC_word_t r2 = 0;

    wordcount_t i, k;

    /* Compute each digit of p_result in sequence, maintaining the carries. */
    for(k = 0; k < uECC_WORDS; ++k)
    {
        for(i = 0; i <= k; ++i)
        {
            muladd(p_left[i], p_right[k-i], &r0, &r1, &r2);
        }
        p_result[k] = r0;
        r0 = r1;
        r1 = r2;
        r2 = 0;
    }
    for(k = uECC_WORDS; k < uECC_WORDS*2 - 1; ++k)
    {
        for(i = (k + 1) - uECC_WORDS; i<uECC_WORDS; ++i)
        {
            muladd(p_left[i], p_right[k-i], &r0, &r1, &r2);
        }
        p_result[k] = r0;
        r0 = r1;
        r1 = r2;
        r2 = 0;
    }

    p_result[uECC_WORDS*2 - 1] = r0;
}

#if uECC_SQUARE_FUNC

static void mul2add(uECC_word_t a, uECC_word_t b, uECC_word_t *r0, uECC_word_t *r1, uECC_word_t *r2)
{
#if uECC_WORD_SIZE == 8 && !SUPPORTS_INT128
    uint64_t a0 = a & 0xffffffffull;
    uint64_t a1 = a >> 32;
    uint64_t b0 = b & 0xffffffffull;
    uint64_t b1 = b >> 32;

    uint64_t i0 = a0 * b0;
    uint64_t i1 = a0 * b1;
    uint64_t i2 = a1 * b0;
    uint64_t i3 = a1 * b1;

    uint64_t p0, p1;

    i2 += (i0 >> 32);
    i2 += i1;
    if(i2 < i1)
    { // overflow
        i3 += 0x100000000ull;
    }

    p0 = (i0 & 0xffffffffull) | (i2 << 32);
    p1 = i3 + (i2 >> 32);

    *r2 += (p1 >> 63);
    p1 = (p1 << 1) | (p0 >> 63);
    p0 <<= 1;

    *r0 += p0;
    *r1 += (p1 + (*r0 < p0));
    *r2 += ((*r1 < p1) || (*r1 == p1 && *r0 < p0));
#else
    uECC_dword_t p = (uECC_dword_t)a * b;
    uECC_dword_t r01 = ((uECC_dword_t)(*r1) << uECC_WORD_BITS) | *r0;
    *r2 += (p >> (uECC_WORD_BITS * 2 - 1));
    p *= 2;
    r01 += p;
    *r2 += (r01 < p);
    *r1 = r01 >> uECC_WORD_BITS;
    *r0 = (uECC_word_t)r01;
#endif
}

static void vli_square(uECC_word_t *p_result, uECC_word_t *p_left)
{
    uECC_word_t r0 = 0;
    uECC_word_t r1 = 0;
    uECC_word_t r2 = 0;

    wordcount_t i, k;

    for(k = 0; k < uECC_WORDS*2 - 1; ++k)
    {
        uECC_word_t l_min = (k < uECC_WORDS ? 0 : (k + 1) - uECC_WORDS);
        for(i = l_min; i<=k && i<=k-i; ++i)
        {
            if(i < k-i)
            {
                mul2add(p_left[i], p_left[k-i], &r0, &r1, &r2);
            }
            else
            {
                muladd(p_left[i], p_left[k-i], &r0, &r1, &r2);
            }
        }
        p_result[k] = r0;
        r0 = r1;
        r1 = r2;
        r2 = 0;
    }

    p_result[uECC_WORDS*2 - 1] = r0;
}

#else /* uECC_SQUARE_FUNC */

#define vli_square(result, left, size) vli_mult((result), (left), (left), (size))

#endif /* uECC_SQUARE_FUNC */


/* Computes p_result = (p_left + p_right) % p_mod.
   Assumes that p_left < p_mod and p_right < p_mod, p_result != p_mod. */
static void vli_modAdd(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right, uECC_word_t *p_mod)
{
    uECC_word_t l_carry = vli_add(p_result, p_left, p_right);
    if(l_carry || vli_cmp(p_result, p_mod) >= 0)
    { /* p_result > p_mod (p_result = p_mod + remainder), so subtract p_mod to get remainder. */
        vli_sub(p_result, p_result, p_mod);
    }
}

/* Computes p_result = (p_left - p_right) % p_mod.
   Assumes that p_left < p_mod and p_right < p_mod, p_result != p_mod. */
static void vli_modSub(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right, uECC_word_t *p_mod)
{
    uECC_word_t l_borrow = vli_sub(p_result, p_left, p_right);
    if(l_borrow)
    { /* In this case, p_result == -diff == (max int) - diff.
         Since -x % d == d - x, we can get the correct result from p_result + p_mod (with overflow). */
        vli_add(p_result, p_result, p_mod);
    }
}

    #define vli_modSub_fast(result, left, right) vli_modSub((result), (left), (right), curve_p)



/* Computes p_result = p_product % curve_p
   from http://www.nsa.gov/ia/_files/nist-routines.pdf */

static void vli_mmod_fast(uint64_t *RESTRICT p_result, uint64_t *RESTRICT p_product)
{
    uint64_t l_tmp[uECC_WORDS];
    int l_carry;

    /* t */
    vli_set(p_result, p_product);

    /* s1 */
    l_tmp[0] = 0;
    l_tmp[1] = p_product[5] & 0xffffffff00000000ull;
    l_tmp[2] = p_product[6];
    l_tmp[3] = p_product[7];
    l_carry = vli_add(l_tmp, l_tmp, l_tmp);
    l_carry += vli_add(p_result, p_result, l_tmp);

    /* s2 */
    l_tmp[1] = p_product[6] << 32;
    l_tmp[2] = (p_product[6] >> 32) | (p_product[7] << 32);
    l_tmp[3] = p_product[7] >> 32;
    l_carry += vli_add(l_tmp, l_tmp, l_tmp);
    l_carry += vli_add(p_result, p_result, l_tmp);

    /* s3 */
    l_tmp[0] = p_product[4];
    l_tmp[1] = p_product[5] & 0xffffffff;
    l_tmp[2] = 0;
    l_tmp[3] = p_product[7];
    l_carry += vli_add(p_result, p_result, l_tmp);

    /* s4 */
    l_tmp[0] = (p_product[4] >> 32) | (p_product[5] << 32);
    l_tmp[1] = (p_product[5] >> 32) | (p_product[6] & 0xffffffff00000000ull);
    l_tmp[2] = p_product[7];
    l_tmp[3] = (p_product[6] >> 32) | (p_product[4] << 32);
    l_carry += vli_add(p_result, p_result, l_tmp);

    /* d1 */
    l_tmp[0] = (p_product[5] >> 32) | (p_product[6] << 32);
    l_tmp[1] = (p_product[6] >> 32);
    l_tmp[2] = 0;
    l_tmp[3] = (p_product[4] & 0xffffffff) | (p_product[5] << 32);
    l_carry -= vli_sub(p_result, p_result, l_tmp);

    /* d2 */
    l_tmp[0] = p_product[6];
    l_tmp[1] = p_product[7];
    l_tmp[2] = 0;
    l_tmp[3] = (p_product[4] >> 32) | (p_product[5] & 0xffffffff00000000ull);
    l_carry -= vli_sub(p_result, p_result, l_tmp);

    /* d3 */
    l_tmp[0] = (p_product[6] >> 32) | (p_product[7] << 32);
    l_tmp[1] = (p_product[7] >> 32) | (p_product[4] << 32);
    l_tmp[2] = (p_product[4] >> 32) | (p_product[5] << 32);
    l_tmp[3] = (p_product[6] << 32);
    l_carry -= vli_sub(p_result, p_result, l_tmp);

    /* d4 */
    l_tmp[0] = p_product[7];
    l_tmp[1] = p_product[4] & 0xffffffff00000000ull;
    l_tmp[2] = p_product[5];
    l_tmp[3] = p_product[6] & 0xffffffff00000000ull;
    l_carry -= vli_sub(p_result, p_result, l_tmp);

    if(l_carry < 0)
    {
        do
        {
            l_carry += vli_add(p_result, p_result, curve_p);
        } while(l_carry < 0);
    }
    else
    {
        while(l_carry || vli_cmp(curve_p, p_result) != 1)
        {
            l_carry -= vli_sub(p_result, p_result, curve_p);
        }
    }
}

/* Computes p_result = (p_left * p_right) % curve_p. */
static void vli_modMult_fast(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right)
{
    uECC_word_t l_product[2 * uECC_WORDS];
    vli_mult(l_product, p_left, p_right);
    vli_mmod_fast(p_result, l_product);
}

#if uECC_SQUARE_FUNC

/* Computes p_result = p_left^2 % curve_p. */
static void vli_modSquare_fast(uECC_word_t *p_result, uECC_word_t *p_left)
{
    uECC_word_t l_product[2 * uECC_WORDS];
    vli_square(l_product, p_left);
    vli_mmod_fast(p_result, l_product);
}

#else /* uECC_SQUARE_FUNC */

#define vli_modSquare_fast(result, left) vli_modMult_fast((result), (left), (left))

#endif /* uECC_SQUARE_FUNC */


#define EVEN(vli) (!(vli[0] & 1))
/* Computes p_result = (1 / p_input) % p_mod. All VLIs are the same size.
   See "From Euclid's GCD to Montgomery Multiplication to the Great Divide"
   https://labs.oracle.com/techrep/2001/smli_tr-2001-95.pdf */
static void vli_modInv(uECC_word_t *p_result, uECC_word_t *p_input, uECC_word_t *p_mod)
{
    uECC_word_t a[uECC_WORDS], b[uECC_WORDS], u[uECC_WORDS], v[uECC_WORDS];
    uECC_word_t l_carry;
    cmpresult_t l_cmpResult;

    if(vli_isZero(p_input))
    {
        vli_clear(p_result);
        return;
    }

    vli_set(a, p_input);
    vli_set(b, p_mod);
    vli_clear(u);
    u[0] = 1;
    vli_clear(v);
    while((l_cmpResult = vli_cmp(a, b)) != 0)
    {
        l_carry = 0;
        if(EVEN(a))
        {
            vli_rshift1(a);
            if(!EVEN(u))
            {
                l_carry = vli_add(u, u, p_mod);
            }
            vli_rshift1(u);
            if(l_carry)
            {
                u[uECC_WORDS-1] |= HIGH_BIT_SET;
            }
        }
        else if(EVEN(b))
        {
            vli_rshift1(b);
            if(!EVEN(v))
            {
                l_carry = vli_add(v, v, p_mod);
            }
            vli_rshift1(v);
            if(l_carry)
            {
                v[uECC_WORDS-1] |= HIGH_BIT_SET;
            }
        }
        else if(l_cmpResult > 0)
        {
            vli_sub(a, a, b);
            vli_rshift1(a);
            if(vli_cmp(u, v) < 0)
            {
                vli_add(u, u, p_mod);
            }
            vli_sub(u, u, v);
            if(!EVEN(u))
            {
                l_carry = vli_add(u, u, p_mod);
            }
            vli_rshift1(u);
            if(l_carry)
            {
                u[uECC_WORDS-1] |= HIGH_BIT_SET;
            }
        }
        else
        {
            vli_sub(b, b, a);
            vli_rshift1(b);
            if(vli_cmp(v, u) < 0)
            {
                vli_add(v, v, p_mod);
            }
            vli_sub(v, v, u);
            if(!EVEN(v))
            {
                l_carry = vli_add(v, v, p_mod);
            }
            vli_rshift1(v);
            if(l_carry)
            {
                v[uECC_WORDS-1] |= HIGH_BIT_SET;
            }
        }
    }

    vli_set(p_result, u);
}

/* ------ Point operations ------ */


/* Point multiplication algorithm using Montgomery's ladder with co-Z coordinates.
From http://eprint.iacr.org/2011/338.pdf
*/

/* Double in place */

static void EccPoint_double_jacobian(uECC_word_t * RESTRICT X1, uECC_word_t * RESTRICT Y1, uECC_word_t * RESTRICT Z1)
{
    /* t1 = X, t2 = Y, t3 = Z */
    uECC_word_t t4[uECC_WORDS];
    uECC_word_t t5[uECC_WORDS];

    if(vli_isZero(Z1))
    {
        return;
    }

    vli_modSquare_fast(t4, Y1);   /* t4 = y1^2 */
    vli_modMult_fast(t5, X1, t4); /* t5 = x1*y1^2 = A */
    vli_modSquare_fast(t4, t4);   /* t4 = y1^4 */
    vli_modMult_fast(Y1, Y1, Z1); /* t2 = y1*z1 = z3 */
    vli_modSquare_fast(Z1, Z1);   /* t3 = z1^2 */

    vli_modAdd(X1, X1, Z1, curve_p); /* t1 = x1 + z1^2 */
    vli_modAdd(Z1, Z1, Z1, curve_p); /* t3 = 2*z1^2 */
    vli_modSub_fast(Z1, X1, Z1); /* t3 = x1 - z1^2 */
    vli_modMult_fast(X1, X1, Z1);    /* t1 = x1^2 - z1^4 */

    vli_modAdd(Z1, X1, X1, curve_p); /* t3 = 2*(x1^2 - z1^4) */
    vli_modAdd(X1, X1, Z1, curve_p); /* t1 = 3*(x1^2 - z1^4) */
    if(vli_testBit(X1, 0))
    {
        uECC_word_t l_carry = vli_add(X1, X1, curve_p);
        vli_rshift1(X1);
        X1[uECC_WORDS-1] |= l_carry << (uECC_WORD_BITS - 1);
    }
    else
    {
        vli_rshift1(X1);
    }
    /* t1 = 3/2*(x1^2 - z1^4) = B */

    vli_modSquare_fast(Z1, X1);      /* t3 = B^2 */
    vli_modSub_fast(Z1, Z1, t5); /* t3 = B^2 - A */
    vli_modSub_fast(Z1, Z1, t5); /* t3 = B^2 - 2A = x3 */
    vli_modSub_fast(t5, t5, Z1); /* t5 = A - x3 */
    vli_modMult_fast(X1, X1, t5);    /* t1 = B * (A - x3) */
    vli_modSub_fast(t4, X1, t4); /* t4 = B * (A - x3) - y1^4 = y3 */

    vli_set(X1, Z1);
    vli_set(Z1, Y1);
    vli_set(Y1, t4);
}

/* Modify (x1, y1) => (x1 * z^2, y1 * z^3) */
static void apply_z(uECC_word_t * RESTRICT X1, uECC_word_t * RESTRICT Y1, uECC_word_t * RESTRICT Z)
{
    uECC_word_t t1[uECC_WORDS];

    vli_modSquare_fast(t1, Z);    /* z^2 */
    vli_modMult_fast(X1, X1, t1); /* x1 * z^2 */
    vli_modMult_fast(t1, t1, Z);  /* z^3 */
    vli_modMult_fast(Y1, Y1, t1); /* y1 * z^3 */
}

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
   Output P' = (x1', y1', Z3), P + Q = (x3, y3, Z3)
   or P => P', Q => P + Q
*/
static void XYcZ_add(uECC_word_t * RESTRICT X1, uECC_word_t * RESTRICT Y1, uECC_word_t * RESTRICT X2, uECC_word_t * RESTRICT Y2)
{
    /* t1 = X1, t2 = Y1, t3 = X2, t4 = Y2 */
    uECC_word_t t5[uECC_WORDS];

    vli_modSub_fast(t5, X2, X1); /* t5 = x2 - x1 */
    vli_modSquare_fast(t5, t5);      /* t5 = (x2 - x1)^2 = A */
    vli_modMult_fast(X1, X1, t5);    /* t1 = x1*A = B */
    vli_modMult_fast(X2, X2, t5);    /* t3 = x2*A = C */
    vli_modSub_fast(Y2, Y2, Y1); /* t4 = y2 - y1 */
    vli_modSquare_fast(t5, Y2);      /* t5 = (y2 - y1)^2 = D */

    vli_modSub_fast(t5, t5, X1); /* t5 = D - B */
    vli_modSub_fast(t5, t5, X2); /* t5 = D - B - C = x3 */
    vli_modSub_fast(X2, X2, X1); /* t3 = C - B */
    vli_modMult_fast(Y1, Y1, X2);    /* t2 = y1*(C - B) */
    vli_modSub_fast(X2, X1, t5); /* t3 = B - x3 */
    vli_modMult_fast(Y2, Y2, X2);    /* t4 = (y2 - y1)*(B - x3) */
    vli_modSub_fast(Y2, Y2, Y1); /* t4 = y3 */

    vli_set(X2, t5);
}

/* -------- ECDSA code -------- */


#define vli_modInv_n vli_modInv
#define vli_modAdd_n vli_modAdd

static void vli2_rshift1(uECC_word_t *p_vli)
{
    vli_rshift1(p_vli);
    p_vli[uECC_WORDS-1] |= p_vli[uECC_WORDS] << (uECC_WORD_BITS - 1);
    vli_rshift1(p_vli + uECC_WORDS);
}

static uECC_word_t vli2_sub(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right)
{
    uECC_word_t l_borrow = 0;
    wordcount_t i;
    for(i=0; i<uECC_WORDS*2; ++i)
    {
        uECC_word_t l_diff = p_left[i] - p_right[i] - l_borrow;
        if(l_diff != p_left[i])
        {
            l_borrow = (l_diff > p_left[i]);
        }
        p_result[i] = l_diff;
    }
    return l_borrow;
}

/* Computes p_result = (p_left * p_right) % curve_n. */
static void vli_modMult_n(uECC_word_t *p_result, uECC_word_t *p_left, uECC_word_t *p_right)
{
    uECC_word_t l_product[2 * uECC_WORDS];
    uECC_word_t l_modMultiple[2 * uECC_WORDS];
    uECC_word_t l_tmp[2 * uECC_WORDS];
    uECC_word_t *v[2] = {l_tmp, l_product};

    vli_mult(l_product, p_left, p_right);
    vli_set(l_modMultiple + uECC_WORDS, curve_n); /* works if curve_n has its highest bit set */
    vli_clear(l_modMultiple);

    bitcount_t i;
    uECC_word_t l_index = 1;
    for(i=0; i<=uECC_BYTES * 8; ++i)
    {
        uECC_word_t l_borrow = vli2_sub(v[1-l_index], v[l_index], l_modMultiple);
        l_index = !(l_index ^ l_borrow); /* Swap the index if there was no borrow */
        vli2_rshift1(l_modMultiple);
    }

    vli_set(p_result, v[l_index]);
}


static bitcount_t smax(bitcount_t a, bitcount_t b)
{
    return (a > b ? a : b);
}

static void keymem_copy(void *dest, const void *src, int length)
{
    const volatile uint64_t *s = src;
    uint64_t *d = dest;
    while (length > 0)
    {
        *d++ = *s++;
        length -= sizeof(uint64_t);
    }
}

int uECC_verify(const uint8_t p_publicKey[uECC_BYTES*2], const uint8_t p_hash[uECC_BYTES], const uint8_t p_signature[uECC_BYTES*2])
{
    uECC_word_t u1[uECC_N_WORDS], u2[uECC_N_WORDS];
    uECC_word_t z[uECC_N_WORDS];
    EccPoint l_public, l_sum;
    uECC_word_t rx[uECC_WORDS];
    uECC_word_t ry[uECC_WORDS];
    uECC_word_t tx[uECC_WORDS];
    uECC_word_t ty[uECC_WORDS];
    uECC_word_t tz[uECC_WORDS];

    uECC_word_t r[uECC_N_WORDS], s[uECC_N_WORDS];

    keymem_copy(l_public.x, p_publicKey, uECC_BYTES);
    keymem_copy(l_public.y, p_publicKey + uECC_BYTES, uECC_BYTES);
    keymem_copy(r, p_signature, uECC_BYTES);
    keymem_copy(s, p_signature + uECC_BYTES, uECC_BYTES);

    if(vli_isZero(r) || vli_isZero(s))
    { /* r, s must not be 0. */
        return 0;
    }

#if (uECC_CURVE != uECC_secp160r1)
    if(vli_cmp(curve_n, r) != 1 || vli_cmp(curve_n, s) != 1)
    { /* r, s must be < n. */
        return 0;
    }
#endif

    /* Calculate u1 and u2. */
    vli_modInv_n(z, s, curve_n); /* Z = s^-1 */
    keymem_copy(u1, p_hash, uECC_BYTES);
    /* SHA256 is stored as a big endian series of bytes. ECC expects a
       little endian array of native 64bit numbers */
    uint64_t tmp = bdk_be64_to_cpu(u1[0]);
    u1[0] = bdk_be64_to_cpu(u1[3]);
    u1[3] = tmp;
    tmp = bdk_be64_to_cpu(u1[1]);
    u1[1] = bdk_be64_to_cpu(u1[2]);
    u1[2] = tmp;
    vli_modMult_n(u1, u1, z); /* u1 = e/s */
    vli_modMult_n(u2, r, z); /* u2 = r/s */

    /* Calculate l_sum = G + Q. */
    vli_set(l_sum.x, l_public.x);
    vli_set(l_sum.y, l_public.y);
    vli_set(tx, curve_G.x);
    vli_set(ty, curve_G.y);
    vli_modSub_fast(z, l_sum.x, tx); /* Z = x2 - x1 */
    XYcZ_add(tx, ty, l_sum.x, l_sum.y);
    vli_modInv(z, z, curve_p); /* Z = 1/Z */
    apply_z(l_sum.x, l_sum.y, z);

    /* Use Shamir's trick to calculate u1*G + u2*Q */
    EccPoint *l_points[4] = {0, &curve_G, &l_public, &l_sum};
    bitcount_t l_numBits = smax(vli_numBits(u1, uECC_N_WORDS), vli_numBits(u2, uECC_N_WORDS));

    EccPoint *l_point = l_points[(!!vli_testBit(u1, l_numBits-1)) | ((!!vli_testBit(u2, l_numBits-1)) << 1)];
    vli_set(rx, l_point->x);
    vli_set(ry, l_point->y);
    vli_clear(z);
    z[0] = 1;

    bitcount_t i;
    for(i = l_numBits - 2; i >= 0; --i)
    {
        EccPoint_double_jacobian(rx, ry, z);

        uECC_word_t l_index = (!!vli_testBit(u1, i)) | ((!!vli_testBit(u2, i)) << 1);
        l_point = l_points[l_index];
        if(l_point)
        {
            vli_set(tx, l_point->x);
            vli_set(ty, l_point->y);
            apply_z(tx, ty, z);
            vli_modSub_fast(tz, rx, tx); /* Z = x2 - x1 */
            XYcZ_add(tx, ty, rx, ry);
            vli_modMult_fast(z, z, tz);
        }
    }

    vli_modInv(z, z, curve_p); /* Z = 1/Z */
    apply_z(rx, ry, z);

    /* v = x1 (mod n) */
#if (uECC_CURVE != uECC_secp160r1)
    if(vli_cmp(curve_n, rx) != 1)
    {
        vli_sub(rx, rx, curve_n);
    }
#endif

    /* Accept only if v == r. */
    return (vli_cmp(rx, r) == 0);
}
