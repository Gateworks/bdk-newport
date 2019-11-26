/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ecam.h"
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-pem.h"

/**
 * Build an ECAM config space request address for a device
 *
 * @param device Device being accessed
 * @param reg    Register to access
 *
 * @return 64bit IO address
 */
uint64_t __bdk_ecam_build_address(const bdk_device_t *device, int reg)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        /* Build the address */
        union bdk_ecam_cfg_addr_s address;
        address.u = BDK_ECAM_BAR_E_ECAMX_PF_BAR2_CN8(device->ecam);
        address.s.node = device->node;
        address.s.bus = device->bus;
        address.s.func = device->dev << 3 | device->func;
        address.s.addr = reg;
        return address.u;
    }
    else
    {
        /* Build the address. The architects decided to make it different
           from CN8XXX for no obvious reason */
        union bdk_ecam_cfg_addr_s address;
        address.u = BDK_ECAM_BAR_E_ECAMX_PF_BAR2_CN9(0);
        address.s.node = device->node;
        address.s.dmn = device->ecam;
        address.s.bus = device->bus;
        address.s.func = device->dev << 3 | device->func;
        address.s.addr = reg;
        return address.u;
    }
}

/**
 * Read from an ECAM
 *
 * @param device Device to read from
 * @param reg    Register to read
 *
 * @return Result of the read of -1 on failure
 */
uint32_t bdk_ecam_read32(const bdk_device_t *device, int reg)
{
    uint64_t address = __bdk_ecam_build_address(device, reg);
    uint32_t result;
    if (address)
        result = bdk_le32_to_cpu(bdk_read64_uint32(address));
    else
        result = 0xffffffff;

    return result;
}

/**
 * Write to an ECAM register
 *
 * @param device Device to write to
 * @param reg    Register to write
 * @param value  Value to write
 */
void bdk_ecam_write32(const bdk_device_t *device, int reg, uint32_t value)
{
    uint64_t address = __bdk_ecam_build_address(device, reg);
    if (address)
        bdk_write64_uint32(address, bdk_cpu_to_le32(value));
}

