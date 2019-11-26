/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-dtx.h"
#include "libbdk-arch/bdk-csrs-ecam.h"
#include "libbdk-arch/bdk-csrs-mrml.h"
#include "libbdk-arch/bdk-csrs-pccbr.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-rvu.h"
#include "libbdk-arch/bdk-csrs-sso.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(ECAM);


/**
 * Some devices on the internal ECAMs need to be hidden. This function checks the
 * device and updates it as we scan the ECAMs.
 *
 * @param device    Device to check
 * @param device_id The device ID returned by the hardware
 *
 * @return New device ID after correction
 */
static uint32_t ecam_check_need_hide(bdk_device_t *device, uint32_t device_id)
{
    /* Errata ECAM-36251: Hiding doesn't work on CN96XX pass 1.x */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X))
        return device_id;

    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        switch (device_id)
        {
            case BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SATA5): /* SATA device */
                break; // FIXME: Should fall through when SATA disabled
            case BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SGP): /* SGP device */
                BDK_TRACE(ECAM, "Hiding device %d:%d:%d.%d\n",
                    device->ecam, device->bus, device->dev, device->func);
                if ((device->ecam == 0) && (device->bus == 1))
                {
                    int ari = device->dev * 8 + device->func;
                    BDK_CSR_MODIFY(c, device->node, BDK_ECAMX_DOMX_RSLX_PERMIT(0, device->ecam, ari),
                        c.s.kill = 1);
                }
                else
                {
                    BDK_CSR_MODIFY(c, device->node, BDK_ECAMX_DOMX_DEVX_PERMIT(0, device->ecam, device->dev),
                        c.s.kill = 1);
                }
                return -1;
        }
    }
    return device_id;
}

/**
 * Walk an ECAM finding all internal devices. Each internal
 * device is then added to the list of device maintained by
 * bdk-device.
 *
 * @param node   Node to walk
 * @param ecam   Ecam to walk
 * @param bus    Zero on first call. Will be non-zero when sub buses are walked
 */
static void ecam_walk_internal_bus(bdk_node_t node, int ecam, int bus)
{
    /* Create a fake bdk-device to pass around until we create the
       real device */
    bdk_device_t device;
    memset(&device, 0, sizeof(device));
    device.node = node;
    device.ecam = ecam;
    device.bus = bus;

    /* Scan all possible device IDs on the bus */
    for (int dev = 0; dev < 32; dev++)
    {
        /* Update the current scan location */
        device.dev = dev;
        device.func = 0;

        uint32_t device_id = bdk_ecam_read32(&device, BDK_PCCPF_XXX_ID);
        device_id = ecam_check_need_hide(&device, device_id);

        /* Only add devices that exist. Our internal devices can have function
           zero missing. The all ones we get back matches the multi-function
           check, but not a bridge. This means the later code works fine */
        if (device_id != (uint32_t)-1)
            bdk_device_add_ecam(device.node, device.ecam, device.bus, device.dev, device.func);

        /* Check for Multi function and Bridge devices */
        BDK_CSR_DEFINE(clsize, BDK_PCCPF_XXX_CLSIZE);
        clsize.u = bdk_ecam_read32(&device, BDK_PCCPF_XXX_CLSIZE);
        int ismultifunction = (clsize.s.hdrtype & 0x80);
        int isbridge = (clsize.s.hdrtype & 0x7f) == 1;

        if (ismultifunction)
        {
            /* Scan for other functions on multifunction devices */
            for (int func = 1; func < 8; func++)
            {
                /* Check if we're past all functions */
                device.func = func;
                uint32_t device_id = bdk_ecam_read32(&device, BDK_PCCPF_XXX_ID);
                device_id = ecam_check_need_hide(&device, device_id);
                if (device_id != (uint32_t)-1)
                    bdk_device_add_ecam(device.node, device.ecam, device.bus, device.dev, device.func);
            }
            device.func = 0;
        }
        if (isbridge)
        {
            /* Internal bus numbers are hard coded. Read the bus ID */
            bdk_pccbr_xxx_bus_t bus;
            bus.u = bdk_ecam_read32(&device, BDK_PCCBR_XXX_BUS);
            /* Asim used to have a bug where bus number were zero, report errors
               for those */
            if (bus.s.sbnum == 0)
            {
                bdk_error("N%d:E%d:%d:%d.%d: Secondary bus number is zero\n",
                    device.node, device.ecam, device.bus, device.dev, device.func);
            }
            /* Real PCIe external device use high bus numbers, so skip them */
            else if (bus.s.sbnum < 16)
            {
                ecam_walk_internal_bus(node, ecam, bus.s.sbnum);
            }
        }
    }
}

/**
 * Turn a ECAM bus into a ARI chain by finding all devices and linking them
 *
 * @param node   Node to create the chain on
 * @param ecam   ECAM to create the chain on
 * @param bus    Bus number to use
 */
static void ecam_create_ari_chain(bdk_node_t node, int ecam, int bus)
{
    /* Create a fake bdk-device to pass around until we create the
       real device */
    bdk_device_t device;
    memset(&device, 0, sizeof(device));
    device.node = node;
    device.ecam = ecam;
    device.bus = bus;
    device.dev = 0;
    device.func = 0;

    /* This is time consuming. If the ARI chain is already non-zero,
       assume a previous boot stage already executed this function */
    BDK_CSR_DEFINE(ctl, BDK_PCCPF_XXX_VSEC_CTL);
    ctl.u = bdk_ecam_read32(&device, BDK_PCCPF_XXX_VSEC_CTL);
    if (ctl.s.nxtfn_ns)
        return;

    /* Search for functions and link them into a chain */
    int last_ari = -1; /* ARI is the old PCIe dev and function combined */
    BDK_TRACE(ECAM, "Creating RSL ARI chain for ecam %d, bus %d\n", device.ecam, device.bus);
    for (int ari = 0; ari < 256; ari++)
    {
        device.dev = ari >> 3;
        device.func = ari & 7;

        /* Only visit existing device */
        uint32_t device_id = bdk_ecam_read32(&device, BDK_PCCPF_XXX_ID);
        if (device_id == (uint32_t)-1)
            continue;

        if (last_ari != -1)
        {
            device.dev = last_ari >> 3;
            device.func = last_ari & 7;

            BDK_TRACE(ECAM, "    Found ARI %d, connect to %d\n", ari, last_ari);
            ctl.u = bdk_ecam_read32(&device, BDK_PCCPF_XXX_VSEC_CTL);
            ctl.s.nxtfn_ns = ari;
            bdk_ecam_write32(&device, BDK_PCCPF_XXX_VSEC_CTL, ctl.u);

            BDK_CSR_DEFINE(sctl, BDK_PCCPF_XXX_VSEC_SCTL);
            sctl.u = bdk_ecam_read32(&device, BDK_PCCPF_XXX_VSEC_SCTL);
            sctl.s.nxtfn_s = ari;
            bdk_ecam_write32(&device, BDK_PCCPF_XXX_VSEC_SCTL, sctl.u);
        }
        else
            BDK_TRACE(ECAM, "    Found first ARI %d\n", ari);
        last_ari = ari;
    }
}

/**
 * Return the number of internal ECAMS on a node.
 *
 * @param node   Node to query
 *
 * @return Number of ECAMs available
 */
int bdk_ecam_get_num(bdk_node_t node)
{
    static int internal_domains = 0;

    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        /* Check if we've already counted the internal domains */
        if (internal_domains)
            return internal_domains;
        /* Find out how many domains are possible  */
        BDK_CSR_INIT(ecam_const, node, BDK_ECAMX_CONST(0));
        /* Loop through domains until we've counted all internal.
           Internal domains are always first and have both PRES and
           PERMIT */
        for (int i = 0; i < ecam_const.s.domains; i++)
        {
            BDK_CSR_INIT(dom_const, node, BDK_ECAMX_DOMX_CONST(0, i));
            if (!dom_const.s.pres || !dom_const.s.permit)
                break;
            internal_domains++;
        }
        return internal_domains;
    }
    else
    {
        BDK_CSR_INIT(ecam_const, node, BDK_ECAMX_CONST(0));
        if (ecam_const.s.ecams == 0)
        {
            bdk_error("N%d.ECAM: Number of ecams incorrect in ECAMX_CONST\n", node);
            return 1;
        }
        return ecam_const.s.ecams;
    }
}

/**
 * Initialize RVU functions for use by the BDK. This doesn't setup the hardware
 * behind RVU, juse allows register access to it. The BDK uses a static RVU
 * configuration where everything is accessible from RVU PF0.
 *
 * @param node   Node to initialize
 *
 * @return Zero on success, negative on failure
 */
static int __bdk_ecam_rvu_init(bdk_node_t node)
{
    /* CN96XX HRM says this register must be enabled before scan, but
       doesn't say why */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_CSR_MODIFY(c, node, BDK_DTX_LMCX_BCST_RSP(0),
            c.s.ena = 1);
        /* Program MRML_CMD_TO[tovalue] to be 100SCLK + 100RCLK in
           SCLK cycles */
        BDK_CSR_MODIFY(c, node, BDK_MRML_CMD_TO,
            c.s.tovalue = 100ull + 100ull * bdk_clock_get_rate(node, BDK_CLOCK_SCLK) /
            bdk_clock_get_rate(node, BDK_CLOCK_RCLK));
    }

    const int rvu_pf = 0;
    /* Enable PF access to all blocks */
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_CPTX_CFG(rvu_pf, 0),
        c.s.num_lfs = 1); // FIXME: How many LFs?
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_INT_CFG(rvu_pf),
        c.s.msix_offset = 0);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_MSIX_CFG(rvu_pf),
        c.s.pf_msixt_offset = 0;
        c.s.pf_msixt_sizem1 = 0;
        c.s.vf_msixt_offset = 0;
        c.s.vf_msixt_sizem1 = 0);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_NIXX_CFG(rvu_pf, 0),
        c.s.has_lf = 1);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_NPA_CFG(rvu_pf),
        c.s.has_lf = 1);
    BDK_CSR_INIT(sso_const, node, BDK_SSO_AF_CONST);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_SSO_CFG(rvu_pf),
        c.s.num_lfs = sso_const.s.grp);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_HWVFX_SSO_CFG(rvu_pf),
        c.s.num_lfs = sso_const.s.grp);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_SSOW_CFG(rvu_pf),
        c.s.num_lfs = sso_const.s.hws);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_HWVFX_SSOW_CFG(rvu_pf),
        c.s.num_lfs = sso_const.s.hws);
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_TIM_CFG(rvu_pf),
        c.s.num_lfs = 1); // FIXME: How many LFs?
    /* Enable RVU with full access */
    BDK_CSR_MODIFY(c, node, BDK_RVU_PRIV_PFX_CFG(rvu_pf),
        c.s.me_flr_ena = 1;
        c.s.af_ena = 1;
        c.s.ena = 1;
        c.s.nvf = 0;
        c.s.first_hwvf = 0);
    return 0;
}

/**
 * Scan all ECAMs for devices and add them to bdk-device
 *
 * @param node   Node to scan
 *
 * @return Zero on success, negative on failure
 */
int bdk_ecam_scan_all(bdk_node_t node)
{
    /* RVU must be setup before we scan the bus otherwise it doesn't
       show up */
    if (bdk_is_model(OCTEONTX_CN9XXX))
        __bdk_ecam_rvu_init(node);

    int num_ecams = bdk_ecam_get_num(node);
    for (int ecam = 0; ecam < num_ecams; ecam++)
        ecam_walk_internal_bus(node, ecam, 0);

    /* Create MRML ARI chain */
    ecam_create_ari_chain(node, 0, 1);

    bdk_device_init();

    return 0;
}

