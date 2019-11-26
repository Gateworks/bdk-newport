/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <stdint.h>
#include <string.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define SWAP(a) __builtin_bswap32(a)
#else
#  define SWAP(a) (a)
#endif

typedef struct
{
    uint64_t total_length;
    uint32_t s[8];
} bdk_sha256_state_t;

static inline uint32_t ror32(uint32_t a, int n)
{
  return ((a>>n) | (a<<(32-n)));
}

static uint32_t SHA256_K[64]
= {0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u, 0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
   0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u, 0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
   0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu, 0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
   0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u, 0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
   0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u, 0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
   0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u, 0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
   0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u, 0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
   0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u, 0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u };

static uint32_t SHA256_H0[8]
= {0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au, 0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u };

static void SHA256_update(bdk_sha256_state_t *hash_state, const uint32_t *M, char reverse)
{
  uint32_t W[16];
  uint32_t A, B, C, D, E, F, G, H;
  A = hash_state->s[0];
  B = hash_state->s[1];
  C = hash_state->s[2];
  D = hash_state->s[3];
  E = hash_state->s[4];
  F = hash_state->s[5];
  G = hash_state->s[6];
  H = hash_state->s[7];
  for (int t=0; t<64; t++) {
    uint32_t Wtmp;
    if (t<16) {
      Wtmp = SWAP(*M++);
    } else {
      uint32_t Wt2 = W[(t-2) & 0xf];
      uint32_t Wt15 = W[(t-15) & 0xf];
      Wtmp = (ror32(Wt2, 17) ^ ror32(Wt2, 19) ^ (Wt2 >> 10)) + W[(t-7) & 0xf]
	+ (ror32(Wt15, 7) ^ ror32(Wt15, 18) ^ (Wt15 >> 3)) + W[t&0xf];
    }
    W[t&0xf] = Wtmp;
    uint32_t T1 = H + (ror32(E, 6) ^ ror32(E, 11) ^ ror32(E, 25)) + ((E & F) | (~E & G)) + SHA256_K[t] + Wtmp;
    uint32_t T2 = (ror32(A, 2) ^ ror32(A, 13) ^ ror32(A, 22)) + ((A & B) | (A & C) | (B & C));
    H = G;
    G = F;
    F = E;
    E = D + T1;
    D = C;
    C = B;
    B = A;
    A = T1 + T2;
  }
  uint32_t tmp;
  if (reverse) {
    tmp = A + hash_state->s[0];
    hash_state->s[0] = H + hash_state->s[7];
    hash_state->s[7] = tmp;

    tmp = B + hash_state->s[1];
    hash_state->s[1] = G + hash_state->s[6];
    hash_state->s[6] = tmp;

    tmp = C + hash_state->s[2];
    hash_state->s[2] = F + hash_state->s[5];
    hash_state->s[5] = tmp;

    tmp = D + hash_state->s[3];
    hash_state->s[3] = E + hash_state->s[4];
    hash_state->s[4] = tmp;
  } else {
    hash_state->s[0] = A + hash_state->s[0];
    hash_state->s[1] = B + hash_state->s[1];
    hash_state->s[2] = C + hash_state->s[2];
    hash_state->s[3] = D + hash_state->s[3];
    hash_state->s[4] = E + hash_state->s[4];
    hash_state->s[5] = F + hash_state->s[5];
    hash_state->s[6] = G + hash_state->s[6];
    hash_state->s[7] = H + hash_state->s[7];
  }
}

/**
 * Start a new SHA256
 *
 * @param hash_state Hash state to initialize
 */
void bdk_sha256_init(bdk_sha256_state_t *hash_state)
{
    hash_state->total_length = 0;
    for (int i=0; i<8; i++)
        hash_state->s[i] = SHA256_H0[i];
}

/**
 * Update SHA256 for a data block
 *
 * @param hash_state Hash state
 * @param data       Data to hash
 * @param size       Size of the data in bytes
 */
void bdk_sha256_update(bdk_sha256_state_t *hash_state, const void *data, int size)
{
    while (size >= 64)
    {
        SHA256_update(hash_state, data, 0);
        hash_state->total_length += 64;
        data += 64;
        size -= 64;
    }
    if (size)
    {
        hash_state->total_length += size;
        char pad[64] = { 0, };
        memcpy(pad, data, size);
        pad[size] = 0x80;
        if (size < 56)
        {
            uint64_t bit_len = hash_state->total_length * 8;
            *(uint32_t*)(pad + 56) = SWAP(bit_len >> 32);
            *(uint32_t*)(pad + 60) = SWAP(bit_len);
        }
        SHA256_update(hash_state, (void*)pad, 0);
    }
}

/**
 * Finish a SHA256
 *
 * @param hash_state Hash state
 *
 * @return Pointer to the 64 byte SHA256
 */
void *bdk_sha256_finish(bdk_sha256_state_t *hash_state)
{
    int last_block_size = hash_state->total_length & 63;
    if (!last_block_size || (last_block_size >= 56))
    {
        char pad[64] = { 0, };
        if (last_block_size == 0)
            pad[0] = 0x80;
        uint64_t bit_len = hash_state->total_length * 8;
        *(uint32_t*)(pad + 56) = SWAP(bit_len >> 32);
        *(uint32_t*)(pad + 60) = SWAP(bit_len);
        SHA256_update(hash_state, (void*)pad, 0);
    }

    for (int i = 0; i < 8; i++)
        hash_state->s[i] = SWAP(hash_state->s[i]);
    return hash_state->s;
}




#if 0
#include <assert.h>
#include <stdio.h>
int main(int argc, const char *argv[])
{
    assert(argc > 1);
    for (int f = 1; f < argc; f++)
    {
        const char *filename = argv[f];
        FILE *inf = fopen(filename, "rb");
        bdk_sha256_state_t hash;
        bdk_sha256_init(&hash);
        char buffer[512];
        int count;
        int total = 0;
        do
        {
            count = fread(buffer, 1, sizeof(buffer), inf);
            if (count > 0)
            {
                bdk_sha256_update(&hash, buffer, count);
                total += count;
            }
        } while (count > 0);
        fclose(inf);
        uint8_t *sha = bdk_sha256_finish(&hash);
        for (int i = 0; i < 32; i++)
            printf("%02x", 0xff & sha[i]);
        printf("  %s\n", filename);
    }
    return 0;
}
#endif
