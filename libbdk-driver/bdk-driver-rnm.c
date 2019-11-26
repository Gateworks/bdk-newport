/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-rnm.h"

BDK_REQUIRE_DEFINE(RNM);

/**
 * Reads 8 bits of random data from Random number generator
 *
 * @return random data
 */
uint8_t bdk_rng_get_random8(void)
{

    return bdk_read64_uint8(bdk_numa_get_address(bdk_numa_local(), BDK_RNM_RANDOM));
}

/**
 * Reads 16 bits of random data from Random number generator
 *
 * @return random data
 */
uint16_t bdk_rng_get_random16(void)
{
    return bdk_read64_uint16(bdk_numa_get_address(bdk_numa_local(), BDK_RNM_RANDOM));
}

/**
 * Reads 32 bits of random data from Random number generator
 *
 * @return random data
 */
uint32_t bdk_rng_get_random32(void)
{
    return bdk_read64_uint32(bdk_numa_get_address(bdk_numa_local(), BDK_RNM_RANDOM));
}

/**
 * Reads 64 bits of random data from Random number generator
 *
 * @return random data
 */
uint64_t bdk_rng_get_random64(void)
{
    return bdk_read64_uint64(bdk_numa_get_address(bdk_numa_local(), BDK_RNM_RANDOM));
}

/**
 * The RNM probe function
 *
 * @param device RNM to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    bdk_device_rename(device, "N%d.RNM%d", device->node, device->instance);
    return 0;
}

/**
 * RNM init() function
 *
 * @param device RNM to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    BDK_BAR_MODIFY(c, device, BDK_RNM_CTL_STATUS,
        c.s.ent_en = 1;
        c.s.rng_en = 1);
    /* Read back after enable so we know it is done. Needed on t88 pass 2.0 emulator */
    BDK_BAR_READ(device, BDK_RNM_CTL_STATUS);
    /* Errata (RNM-22528) First consecutive reads to RNM_RANDOM return same
       value. Before using the random entropy, read RNM_RANDOM at least once
       and discard the data */
    bdk_rng_get_random64();
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        BDK_CSR_INIT(rnm_const, device->node, BDK_RNM_CONST);
        if (rnm_const.s.zucs != 0xf)
        {
            BDK_CSR_DEFINE(zuc_lfsr, BDK_RNM_ZUCX_INIT_LFSRX(0,0));
            BDK_CSR_DEFINE(zuc_nlf, BDK_RNM_ZUCX_INIT_NLFX(0,0));
            zuc_lfsr.u = 0;
            zuc_nlf.u = 0;
            int i;
            for(i=0; i < 16; i++)
            {
                zuc_lfsr.s.lfsr = bdk_rng_get_random32();
                BDK_CSR_WRITE(device->node, BDK_RNM_ZUCX_INIT_LFSRX(0,i), zuc_lfsr.u);
            }
            for(i=0; i < 2; i++)
            {
                zuc_nlf.s.r_state = bdk_rng_get_random32();
                BDK_CSR_WRITE(device->node, BDK_RNM_ZUCX_INIT_NLFX(0,i), zuc_nlf.u);
            }
            BDK_BAR_MODIFY(c, device, BDK_RNM_CTL_STATUS,
                           c.cn9.zuc_en = 1);
        }
    }
    return 0;
}

bdk_driver_t __bdk_driver_rnm = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_RNM),
    .name = "RNM",
    .probe = probe,
    .init = init,
};
