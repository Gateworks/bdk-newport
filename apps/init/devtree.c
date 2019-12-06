/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdarg.h>
#include <libfdt.h>
#include <newport.h>
#include "libbdk-arch/bdk-csrs-bgx.h"
#include "libbdk-arch/bdk-csrs-ccs.h"
#include "libbdk-arch/bdk-csrs-cgx.h"
#include "libbdk-arch/bdk-csrs-gic.h"
#include "libbdk-arch/bdk-csrs-pcierc.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-uaa.h"

static const char *QLM_BGX_MODE_MAP[BDK_QLM_MODE_LAST] =
{
    [BDK_QLM_MODE_SGMII]        = "sgmii",
    [BDK_QLM_MODE_1G_X]         = "sgmii",
    [BDK_QLM_MODE_XAUI]         = "xaui",
    [BDK_QLM_MODE_RXAUI]        = "rxaui",
    [BDK_QLM_MODE_XFI]          = "xfi",
    [BDK_QLM_MODE_SFI]          = "xfi",
    [BDK_QLM_MODE_XLAUI]        = "xlaui",
    [BDK_QLM_MODE_XLAUI_C2M]    = "xlaui",
    [BDK_QLM_MODE_10G_KR]       = "xfi-10g-kr",
    [BDK_QLM_MODE_40G_CR4]      = "xlaui-40g-cr",
    [BDK_QLM_MODE_40G_KR4]      = "xlaui-40g-kr",
    [BDK_QLM_MODE_QSGMII]       = "qsgmii",
    [BDK_QLM_MODE_20GAUI_C2C]   = "20gaui",
    [BDK_QLM_MODE_25GAUI_C2C]   = "25gaui",
    [BDK_QLM_MODE_25GAUI_C2M]   = "25gaui",
    [BDK_QLM_MODE_25G_CR]       = "25g-cr",
    [BDK_QLM_MODE_25G_KR]       = "25g-kr",
    [BDK_QLM_MODE_25GAUI_2_C2C] = "25gaui",
    [BDK_QLM_MODE_40GAUI_2_C2C] = "40gaui",
    [BDK_QLM_MODE_50GAUI_2_C2C] = "50gaui",
    [BDK_QLM_MODE_50GAUI_2_C2M] = "50gaui",
    [BDK_QLM_MODE_50G_CR2]      = "50g-cr2",
    [BDK_QLM_MODE_50G_KR2]      = "50g-kr2",
    [BDK_QLM_MODE_50GAUI_4_C2C] = "50gaui",
    [BDK_QLM_MODE_80GAUI_4_C2C] = "80gaui",
    [BDK_QLM_MODE_CAUI_4_C2C]   = "caui",
    [BDK_QLM_MODE_CAUI_4_C2M]   = "caui",
    [BDK_QLM_MODE_100G_CR4]     = "100g-cr4",
    [BDK_QLM_MODE_100G_KR4]     = "100g-kr4",
    [BDK_QLM_MODE_USXGMII_4X1]  = "usxgmii",
    [BDK_QLM_MODE_USXGMII_2X1]  = "usxgmii",
    [BDK_QLM_MODE_USXGMII_1X1]  = "usxgmii",
};

/**
 * Delete a node from a device tree, using printf style arguments to build the
 * node name
 *
 * @param fdt    Tree to delete the node from
 * @param format Printf style format string for the name
 *
 * @return Zero on success, negative on failure. Node that if the node doesn't exist when
 *         called, that is considered a success.
 */
static int devtree_node_del(void *fdt, const char *format, ...) __attribute__ ((format(printf, 2, 3)));
static int devtree_node_del(void *fdt, const char *format, ...)
{
    /* Format the name into a string */
    char name[64];
    va_list args;
    va_start(args, format);
    vsnprintf(name, sizeof(name), format, args);
    va_end(args);
    /* Find the node */
    int status = fdt_path_offset(fdt, name);
    if (status >= 0)
    {
        /* Delete the node without removing its space, so offsets are unaffected */
        status = fdt_nop_node(fdt, status);
        if (status != 0)
        {
            bdk_error("Unable to delete %s in FDT (%d:%s)\n", name, status, fdt_strerror(status));
            return -1;
        }
        BDK_TRACE(FDT_OS, "    Deleted FDT node %s\n", name);
    }
    return 0;
}

/**
 * Find a node with the given property name. Call with a startoffset of -1 on the
 * first call, then keep calling until the return value is -1.
 *
 * @param fdt      Tree to search
 * @param startoffset
 *                 Starting node, which has already been searched. Pass -1 on first call
 * @param propname Name of property to search for
 *
 * @return Node with property name, or -1 when iteration complete
 */
static int devtree_node_offset_by_prop_name(const void *fdt, int startoffset, const char *propname)
{
    int node;

    /* Figure out the starting node */
    if (startoffset == -1)
        node = 0;
    else
        node = fdt_next_node(fdt, startoffset, NULL);

    /* Search until we iterate through all nodes */
    while (node >= 0)
    {
        int proplen = 0;
        const void *propvalue = fdt_getprop(fdt, node, propname, &proplen);
        if (propvalue)
        {
            /* Found the desired prop name, return this node */
            return node;
        }
        /* Not found, proceed to next node */
        node = fdt_next_node(fdt, node, NULL);
    }
    /* Ran out of nodes, return -1 */
    return -1;
}

/**
 * Load a device tree DTB file, allocating new space for it
 *
 * @param filename File to load
 *
 * @return NULL on failure, or a pointer to the device tree
 */
static void *devtree_load(const char *filename)
{
    uint64_t fdt_size = 0;
    void *fdt = bdk_signed_load(filename, 0, BDK_SIGNED_DTS, BDK_SIGNED_FLAG_NONE, &fdt_size);
    if (!fdt)
        return NULL; /* Fails silently so we can search for DTB files */

    /* Make sure the read succeeded */
    if (fdt_size < sizeof(struct fdt_header))
    {
        bdk_error("Unable to read %s\n", filename);
        free(fdt);
        return NULL;
    }

    if (fdt_check_header(fdt))
    {
        bdk_error("Invalid FDT header read from %s\n", filename);
        free(fdt);
        return NULL;
    }

    /* Make sure we read enough data to contain the FDT */
    int correct_size = fdt_totalsize(fdt);
    if ((int)fdt_size < correct_size)
    {
        bdk_error("Unable to read FDT from %s\n", filename);
        free(fdt);
        return NULL;
    }

    /* Check if a CRC32 was added on the end of the FDT */
    if ((int)fdt_size >= correct_size + 4)
    {
        uint32_t crc32 = bdk_crc32(fdt, correct_size, 0);
        uint32_t correct_crc32 = *(uint32_t *)((const char *)fdt + correct_size);
        /* CRC32 is stored in same endianness as FDT */
        correct_crc32 = fdt32_to_cpu(correct_crc32);
        if (crc32 != correct_crc32)
        {
            bdk_error("FDT failed CRC32 verification (%s)\n", filename);
            free(fdt);
            return NULL;
        }
        BDK_TRACE(FDT_OS, "Loaded device tree %s, CRC32 matched\n", filename);
    }
    else
        BDK_TRACE(FDT_OS, "Loaded device tree %s, CRC32 not present\n", filename);

    /* Enlarge the FDT so it has some working room */
    void *bigger = realloc(fdt, fdt_size + 0x10000);
    if (bigger)
    {
        fdt = bigger;
        /* Tell the FDT it has extra space */
        int status = fdt_open_into(fdt, fdt, fdt_size + 0x10000);
        if (status)
        {
            bdk_error("Unable resize FDT (%d:%s)\n", status, fdt_strerror(status));
            free(fdt);
            return NULL;
        }
    }
    return fdt;
}

/**
 * Copy the current BDK config settings into a device tree
 *
 * @param fdt    Tree to receive the new settings
 *
 * @return Zero on success, negative on failure
 */
static int devtree_copy_settings(void *fdt)
{
    /* If the bdk config node exists, delete it, removing all attributes and
       sub nodes */
    if (devtree_node_del(fdt, "/" BDK_DEVICE_TREE_ROOT))
        return -1;

    /* Create a bdk config node */
    int top = fdt_add_subnode(fdt, 0, BDK_DEVICE_TREE_ROOT);
    if (top < 0)
    {
        bdk_error("Unable to create %s node in FDT (%d:%s)\n", BDK_DEVICE_TREE_ROOT, top, fdt_strerror(top));
        return -1;
    }
    BDK_TRACE(FDT_OS, "    Created /%s\n", BDK_DEVICE_TREE_ROOT);

    /* Copy all bdk attributes to the new tree */
    void *bdk_fdt = bdk_config_get_fdt();
    int bdk_top = fdt_path_offset(bdk_fdt, "/" BDK_DEVICE_TREE_ROOT);
    int offset = fdt_first_property_offset(bdk_fdt, bdk_top);
    while (offset >= 0)
    {
        const char *name = NULL;
        int blob_size = 0;
        const char *data = fdt_getprop_by_offset(bdk_fdt, offset, &name, &blob_size);
        fdt_setprop(fdt, top, name, data, blob_size);
        offset = fdt_next_property_offset(bdk_fdt, offset);
    }
    BDK_TRACE(FDT_OS, "    Copied /%s properties\n", BDK_DEVICE_TREE_ROOT);
    return 0;
}

/**
 * The operating system following the BDK needs some changes made to the device
 * tree, making it match the dynamic state of the hardware
 *
 * @param fdt    Device tree to update
 *
 * @return Zero on success, negative on failure
 */
static int devtree_fixups(void *fdt)
{
    /* Extract our MAC address info so we can assign them in the device tree */
    uint64_t next_free_mac_address = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS);
    int num_free_mac_addresses = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS_NUM);
    int num_free_override = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS_NUM_OVERRIDE);
    if (num_free_override != -1)
        num_free_mac_addresses = num_free_override;

    /* Loop through all possible node IDs */
    for (bdk_node_t node = 0; node < BDK_NUMA_MAX_NODES; node++)
    {
        BDK_CSR_DEFINE(ccs_const, BDK_CCS_CONST);
        ccs_const.u = 0;

        /* The /soc name is used a lot, create a string containing it */
        char soc[32];
        if (node == 0)
            snprintf(soc, sizeof(soc), "soc@0");
        else
            snprintf(soc, sizeof(soc), "soc@%x00000000000", node);

        /* 1) Remove unwanted CPUs and L2 caches */
        int num_cpus;
        if (bdk_numa_exists(node))
        {
            if (!bdk_is_model(OCTEONTX_CN8XXX))
                ccs_const.u = BDK_CSR_READ(node, BDK_CCS_CONST);
            /* Figure out the number of CPUs */
            num_cpus = bdk_get_num_cores(node);
            /* We'll need to delete extra cpus below */
        }
        else
        {
            /* Node doesn't exist, so no CPUs */
            num_cpus = 0;
            /* Delete the entire cpu cluster */
            if (devtree_node_del(fdt, "/cpus/cpu-map/cluster%d", node))
                return -1;
            /* Delete the L2 for the node */
            if (devtree_node_del(fdt, "/cpus/l2-cache%d", node))
                return -1;
            /* We still need to delete the CPUs in /cpus/cpu*. This
               is done below */
        }

        /* Loop through node's cpu numbers and delete ones that don't exist */
        for (int cpu = 0; cpu < 64; cpu++)
        {
            if (cpu >= num_cpus)
            {
                /* Delete unused CPUs out of the CPU cluster */
                if (bdk_numa_exists(node) &&
                    devtree_node_del(fdt, "/cpus/cpu-map/cluster%d/core%d", node, cpu))
                        return -1;
                /* Delete unused CPUs out of /cpus/cpu* */
                int cpu_id;
                if (bdk_is_model(OCTEONTX_CN8XXX))
                    cpu_id = (node << 16) | ((cpu & 0xf0) << 4) | (cpu & 0xf);
                else /* Cores are enumerated across clusters first */
                    cpu_id = (node << 16) | ((cpu % ccs_const.s.clu) << 8) | (cpu / ccs_const.s.clu);
                if (devtree_node_del(fdt, "/cpus/cpu@%x", cpu_id))
                    return -1;
            }
        }

        /* 2) Remove unwanted NUMA node entries:
             - /interrupt-controller@801000000000/gic-its@901000020000
             - /soc@100000000000
             - /memory@10000000000
             - /distance-map
             - Set #redistributor-regions to 1 */
        if (!bdk_numa_exists(node))
        {
            uint64_t address = bdk_numa_get_address(node, BDK_GIC_BAR_E_GIC_PF_BAR2);
            /* Delete the ITS interrupt entry */
            if (devtree_node_del(fdt, "/interrupt-controller@801000000000/gic-its@%lx", address))
                return -1;
            /* Delete the SOC entry */
            if (devtree_node_del(fdt, "/%s", soc))
                return -1;
            /* Delete the memory entry */
            if (devtree_node_del(fdt, "/memory@%08lx", bdk_numa_get_address(node, 0)))
                return -1;
            /* Set #redistributor-regions to 1 */
            if (node == 1)
            {
                int fdt_node = fdt_path_offset(fdt, "/interrupt-controller@801000000000");
                if (fdt_node >= 0)
                {
                    if (fdt_setprop_inplace_u32(fdt, fdt_node, "#redistributor-regions", 1))
                    {
                        bdk_error("Unable to set #redistributor-regions in FDT\n");
                        return -1;
                    }
                }
            }
        }

        /* 3) Remove unwanted PEM entries */
        if (bdk_numa_exists(node))
        {
            int num_pems = bdk_pcie_get_num_ports(node);
            for (int pem = 0; pem < num_pems; pem++)
            {
                /* Check that the PEM hardware exists on this chip */
                bool del_pem = (pem >= num_pems);
                /* Check that the PEM is on */
                if (!del_pem)
                {
                    BDK_CSR_INIT(pemx_on, node, BDK_PEMX_ON(pem));
                    del_pem = !pemx_on.s.pemon;
                }
                /* Check that the PEM is not in reset */
                if (!del_pem)
                {
                    if (bdk_is_model(OCTEONTX_CN8XXX) ||
                        bdk_is_model(OCTEONTX_CN96XX_PASS1_X) ||
                        bdk_is_model(OCTEONTX_CNF95XX))
                    {
                        BDK_CSR_INIT(soft_prst, node, BDK_RST_SOFT_PRSTX(pem));
                        del_pem = soft_prst.s.soft_prst;
                    }
                    else
                    {
                        BDK_CSR_INIT(soft_perst, node, BDK_PEMX_RST_SOFT_PERST(pem));
                        del_pem = soft_perst.s.soft_perst;
                    }
                }
                /* Check that the PEM has link */
                if (!del_pem)
                {
                    if (bdk_is_model(OCTEONTX_CN8XXX))
                    {
                        BDK_CSR_INIT(pciercx_cfg032, node, BDK_PCIERCX_CFG032(pem));
                        del_pem = (pciercx_cfg032.s.dlla == 0) || (pciercx_cfg032.s.lt == 1);
                    }
                    else
                    {
                        BDK_CSR_INIT(link_ctl, node, BDK_PCIERCX_LINK_CTL(pem));
                        del_pem = (link_ctl.s.dlla == 0) || (link_ctl.s.lt == 1);
                    }
                }
                /* Delete PEMs that fail any of the above checks */
                if (del_pem)
                {
                    /* Find the FDT node for the PEM, device tree
                       addresses are node relative, so don't use
                       absolute address on the given node. */
                    uint64_t address = bdk_is_model(OCTEONTX_CN8XXX) ?
                                        BDK_PEM_BAR_E_PEMX_PF_BAR0_CN8(pem):
                                        BDK_PEM_BAR_E_PEMX_PF_BAR0_CN9(pem);
                    char pem_name[64];
                    snprintf(pem_name, sizeof(pem_name), "/%s/pci@%lx", soc, address);
                    int fdt_node = fdt_path_offset(fdt, pem_name);
                    if (fdt_node <= 0)
                        continue;
                    /* Get its phandle, used by SMMU */
                    uint32_t pem_phandle = fdt_get_phandle(fdt, fdt_node);
                    /* Delete the PEM */
                    int status = fdt_nop_node(fdt, fdt_node);
                    if (status) {
                        bdk_error("Unable to delete %s in FDT (%d:%s)\n", pem_name, status, fdt_strerror(status));
                        return -1;
                    }
                    /* After deleting the PEM, we need to remove references to
                       it from the SMMUs */
                    const char *propname = "mmu-masters";
                    fdt_node = devtree_node_offset_by_prop_name(fdt, -1, propname);
                    while (fdt_node >= 0)
                    {
                        int next_node = devtree_node_offset_by_prop_name(fdt, fdt_node, propname);
                        const char *fdt_node_name = fdt_get_name(fdt, fdt_node, NULL);
                        /* Get the value of the property */
                        int proplen = 0;
                        const uint32_t *propvalue = fdt_getprop(fdt, fdt_node, propname, &proplen);
                        const uint32_t *propend = propvalue + proplen / sizeof(uint32_t);
                        /* Loop removing references to the PEMs phandle */
                        uint32_t mmu_masters[4][2];
                        int mmu_count = 0;
                        while (propvalue < propend)
                        {
                            if (fdt32_to_cpu(*propvalue) != pem_phandle)
                            {
                                /* Copy */
                                mmu_masters[mmu_count][0] = *propvalue++;
                                mmu_masters[mmu_count][1] = *propvalue++;
                                mmu_count++;
                            }
                            else
                                propvalue += 2; /* Skip */
                        }
                        /* If any were deleted update the property */
                        int new_len = mmu_count * sizeof(int32_t) * 2;
                        if (new_len != proplen)
                        {
                            if (fdt_setprop(fdt, fdt_node, propname, mmu_masters, new_len))
                            {
                                bdk_error("Failed to update property %s[%s]\n",
                                    fdt_node_name, propname);
                                return -1;
                            }
                            else
                            {
                                BDK_TRACE(FDT_OS, "    %s[%s] removed PEM%d\n",
                                    fdt_node_name, propname, pem);
                                /* Changing the property reorders the FDT, so
                                   we need to start at the top of the tree
                                   again */
                                next_node = -1;
                            }
                        }
                        fdt_node = next_node;
                    }
                }
            }
        }

        /* 4) Remove unwanted QLM mode entries.  For each BGX 0, 1 on node0,
          and 2, 3 on node 1, determine the mode.  This will be one of:

           See QLM_BGX_MODE_MAP above

          For each BGX, scan for nodes containing the property named
          "qlm-mode".  This will have property strings of the form "#,mode",
          where # is a BGX number (0..4) and mode is one of the modes listed
          above.  If the BGX number of the "qlm-mode" property matches, do one
          of the following:

          A) If the mode matches the BGX mode, remove the "qlm-mode" property.
          B) If the mode doesn't match the BGX mode, remove the entire node
          containing the "qlm-mode" property

          Note that some "qlm-mode" properties have multiple values of this form:

            qlm-mode = "2,xfi","2,sgmii"; for example.

          In this case the match must be tried against each value.
        5) Populate MAC addresses.  For each child node of the BGX nodes,
          add a property named "local-mac-address" set to the next available
          MAC address obtained from the Manufacturing data.  If no MAC address
          is available, don't add the "local-mac-address" property. */
        if (bdk_numa_exists(node))
        {
            bdk_if_t if_net_type = (bdk_is_model(OCTEONTX_CN8XXX)) ? BDK_IF_BGX : BDK_IF_CGX;
            unsigned int bgx_index, bgx_interface;
            int len;
            int fdt_node, fdt_node_prev;
            for (bgx_interface = 0; bgx_interface < 4; bgx_interface++)
            {
                for (bgx_index = 0; bgx_index < 4; bgx_index++)
                {
                    char key[64];
                    int qlm = bdk_qlm_get(node, if_net_type, bgx_interface, bgx_index);
                    unsigned int qlm_lanes = (qlm == -1) ? 0 : bdk_qlm_get_lanes(node, qlm);
                    int qlm_lane = (bgx_index < qlm_lanes) ? bgx_index : bgx_index - qlm_lanes;
                    bdk_qlm_modes_t qlm_mode = (qlm == -1) ? BDK_QLM_MODE_DISABLED : bdk_qlm_get_mode(node, qlm, qlm_lane);

                    /* BGXX_CMRX_RX_DMAC_CTL is used to mark ports as disabled
                       that would otherwise be enabled */
                    if (qlm_mode != BDK_QLM_MODE_DISABLED)
                    {
                        if (bdk_is_model(OCTEONTX_CN8XXX))
                        {
                            BDK_CSR_INIT(rx_dmac_ctl, node, BDK_BGXX_CMRX_RX_DMAC_CTL(bgx_interface, bgx_index));
                            if (rx_dmac_ctl.u == 0)
                                qlm_mode = BDK_QLM_MODE_DISABLED;
                        }
                        else
                        {
                            BDK_CSR_INIT(rx_dmac_ctl, node, BDK_CGXX_CMRX_RX_DMAC_CTL0(bgx_interface, bgx_index));
                            if (rx_dmac_ctl.u == 0)
                                qlm_mode = BDK_QLM_MODE_DISABLED;
                        }
                    }

                    if (qlm_mode == BDK_QLM_MODE_DISABLED)
                        snprintf(key, sizeof(key), "0x%x%x%x,disabled", node, bgx_interface, bgx_index);
                    else
                        snprintf(key, sizeof(key), "0x%x%x%x,%s", node, bgx_interface, bgx_index, QLM_BGX_MODE_MAP[qlm_mode]);
                    fdt_node = 0;
                    do
                    {
                        fdt_node_prev = fdt_node;
                        fdt_node = fdt_next_node(fdt, fdt_node_prev, NULL);

                        if (fdt_node < 0)
                            break;

                        const char *prop_value_in_tree = fdt_getprop(fdt, fdt_node, "qlm-mode", &len);
                        if (!prop_value_in_tree)
                            continue; /* No qlm-mode property in this node. */

                        if (strncmp(prop_value_in_tree, key, 6) != 0)
                            continue; /* No key prefix match. */

                        const char *node_name = fdt_get_name(fdt, fdt_node, NULL);
                        if (fdt_stringlist_contains(prop_value_in_tree, len, key)) {
                            /* Keep node, remove "qlm-mode" property */
                            BDK_TRACE(FDT_OS, "    Keep %s because \"%s\"\n", node_name, key);
                            fdt_nop_property(fdt, fdt_node, "qlm-mode");
                            /* Linux only access the Phy via MDIO, only used for CN8XXX
                               Remove 'phy-handle' if this option is not available */
                            if (bdk_is_model(OCTEONTX_CN8XXX))
                            {
                                int64_t phy_address = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, node, bgx_interface, bgx_index);
                                switch (qlm_mode)
                                {
                                    case BDK_QLM_MODE_SGMII:
                                    case BDK_QLM_MODE_QSGMII:
                                        if ((phy_address & BDK_IF_PHY_TYPE_MASK) != BDK_IF_PHY_MDIO) {
                                            fdt_nop_property(fdt, fdt_node, "phy-handle");
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                        } else {
                            /* No match, remove node */
                            BDK_TRACE(FDT_OS, "    Remove %s because \"%s\"\n", node_name, key);
                            fdt_nop_node(fdt, fdt_node);
                        }
                        /*  Retry at the same offset as NOP filling may invalidate next nodes. */
                        fdt_node = fdt_node_prev;
                    } while (fdt_node >= 0);
                }
            }
        }

        /* 6) Set refclkuaa clock rate.  For the node "/refclkuaa", set the
          "clock-frequency" property to the value of:
           (115200 * (64 * UAA_IBRD_REG + UAA_FBRD_REG)) / 4 */
        if (bdk_numa_exists(node))
        {
            char refclkuaa[32];
            snprintf(refclkuaa, sizeof(refclkuaa), "/%s/refclkuaa", soc);
            int fdt_node = fdt_path_offset(fdt, refclkuaa);
            if (fdt_node >= 0)
            {
                int divisor;
                BDK_CSR_INIT(uctl_ctl, node, BDK_UAAX_UCTL_CTL(0));

                switch (uctl_ctl.s.h_clkdiv_sel) {
                case 0:
                    divisor = 1;
                    break;
                case 1:
                    divisor = 2;
                    break;
                case 2:
                    divisor = 4;
                    break;
                case 3:
                    divisor = 6;
                    break;
                case 4:
                    divisor = 8;
                    break;
                case 5:
                    divisor = 16;
                    break;
                case 6:
                    divisor = 24;
                    break;
                case 7:
                    divisor = 32;
                    break;
                }
                int uaa_clock = bdk_clock_get_rate(node, bdk_is_model(OCTEONTX_CN8XXX) ? BDK_CLOCK_SCLK : BDK_CLOCK_MAIN_REF) / divisor;

                if (fdt_setprop_inplace_u32(fdt, fdt_node, "clock-frequency", uaa_clock))
                {
                    bdk_error("Unable to edit %s[clock-frequency] in FDT\n", refclkuaa);
                    return -1;
                }
                BDK_TRACE(FDT_OS, "    Set %s[clock-frequency] = 0x%x\n", refclkuaa, uaa_clock);
            }
        }

        /* 7) Set the sclk clock rate.  For the node "/sclk", set the
          "clock-frequency" property to the value to the system SCLK rate (800000000 or so). */
        if (bdk_numa_exists(node))
        {
            char sclk_name[32];
            snprintf(sclk_name, sizeof(sclk_name), "/%s/sclk", soc);
            int rate = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
            int fdt_node = fdt_path_offset(fdt, sclk_name);
            if (fdt_node >= 0)
            {
                if (fdt_setprop_inplace_u32(fdt, fdt_node, "clock-frequency", rate))
                {
                    bdk_error("Unable to edit %s[clock-frequency] in FDT\n", sclk_name);
                    return -1;
                }
                BDK_TRACE(FDT_OS, "    Set %s[clock-frequency] = 0x%x\n", sclk_name, rate);
            }
        }

        /* 8) Patch ECAM property names.  For systems that are *not* either T88
          pass1, nor T88 Pass2-2nd node, find all "compatible" properties with a
          value "cavium,pci-host-thunder-ecam", and change the compatible
          value to "pci-host-ecam-generic". */
        if (true)
        {
            char soc_path[32];
            const char *new_compatible = "pci-host-ecam-generic";
            /* Length includes null terminator */
            const int new_compatible_len = strlen(new_compatible) + 1;
            int depth;
            int fdt_node;

            snprintf(soc_path, sizeof(soc_path), "/%s", soc);
            fdt_node = fdt_path_offset(fdt, soc_path);

            for (depth = 0;
                 (fdt_node >= 0) && (depth >= 0);
                 fdt_node = fdt_next_node(fdt, fdt_node, &depth))
            {
                if (fdt_node_check_compatible(fdt, fdt_node, "cavium,pci-host-thunder-ecam") != 0)
                    continue;

                const char *fdt_node_name = fdt_get_name(fdt, fdt_node, NULL);
                if (fdt_setprop(fdt, fdt_node, "compatible", new_compatible, new_compatible_len))
                {
                    bdk_error("Unable to edit %s[compatible] in FDT\n", fdt_node_name);
                    return -1;
                }
                BDK_TRACE(FDT_OS, "    Changed %s[compatible] to %s\n", fdt_node_name, new_compatible);
            }
        }

        /* 9) Patch memory size.  For the memory node corresponding to each
          NUMA node, set the memory size.  These nodes have the following paths:

            - "/memory@0"
            - "/memory@10000000000"
          These nodes have a "reg" property of the following form:

            reg = <base_63_32 base_31_0 size_63_32 size_31_0>

          The base should be set the the physical address of the non-secure memory.
          The size should be set to the size of the non-secure memory on the corresponding node */
        if (bdk_numa_exists(node))
        {
            char mem[32];
            snprintf(mem, sizeof(mem), "/memory@%lx", bdk_numa_get_address(node, 0));
            int fdt_node = fdt_path_offset(fdt, mem);
            if (fdt_node >= 0)
            {
                int mem_info_len = 0;
                const uint32_t *mem_info = fdt_getprop(fdt, fdt_node, "reg", &mem_info_len);
                if (mem_info && (mem_info_len == sizeof(uint32_t) * 4))
                {
                    uint64_t base = fdt32_to_cpu(mem_info[1]);
                    base |= (uint64_t)fdt32_to_cpu(mem_info[0]) << 32;
                    uint64_t size = bdk_dram_get_size_mbytes(node) << 20;
                    size -= base & 0xfffffffffful; /* Mask out node bits */
                    uint32_t new_mem[4];
                    new_mem[0] = cpu_to_fdt32(base >> 32);    /* High part of memory base */
                    new_mem[1] = cpu_to_fdt32(base);          /* Low part of memory base */
                    new_mem[2] = cpu_to_fdt32(size >> 32);    /* High part of memory size */
                    new_mem[3] = cpu_to_fdt32(size);          /* Low part of memory size */
                    if (fdt_setprop_inplace(fdt, fdt_node, "reg", new_mem, sizeof(new_mem)))
                    {
                        bdk_error("Unable to edit %s[reg] in FDT\n", mem);
                        return -1;
                    }
                    BDK_TRACE(FDT_OS, "    Set %s[reg] = mem size 0x%lx\n", mem, size);
                }
            }
        }
    }

    if (bdk_numa_is_only_one() && devtree_node_del(fdt, "/distance-map"))
        return -1;

    /* All hardware changes are complete in the device tree. Iterate through the
       whole tree fixing any MAC addresses that are left and not already filled
       with a value. Zero MAC addresses in "local-mac-address" will be updated
       or removed */
    const char *propname = "local-mac-address";
    int fdt_node = devtree_node_offset_by_prop_name(fdt, -1, propname);
    while (fdt_node >= 0)
    {
        const char *fdt_node_name = fdt_get_name(fdt, fdt_node, NULL);
        /* See if this node's MAC address needs update */
        const uint8_t *old = fdt_getprop(fdt, fdt_node, propname, NULL);
        if (old)
        {
            /* See if all 6 bytes are zero */
            bool is_non_zero = old[0] || old[1] || old[2] || old[3] || old[4] || old[5];
            if (!is_non_zero)
            {
                /* Found a zero MAC address, either update it or remove it if we
                   are out of MAC addresses */
                if (num_free_mac_addresses)
                {
                    /* Update */
                    uint8_t new_mac_address[6];
                    new_mac_address[0] = (next_free_mac_address >> 40) & 0xff;
                    new_mac_address[1] = (next_free_mac_address >> 32) & 0xff;
                    new_mac_address[2] = (next_free_mac_address >> 24) & 0xff;
                    new_mac_address[3] = (next_free_mac_address >> 16) & 0xff;
                    new_mac_address[4] = (next_free_mac_address >> 8) & 0xff;
                    new_mac_address[5] = (next_free_mac_address >> 0) & 0xff;
                    if (fdt_setprop_inplace(fdt, fdt_node, propname, new_mac_address, 6))
                    {
                        bdk_error("Failed to update property %s[%s]\n",
                            fdt_node_name, propname);
                        return -1;
                    }
                    BDK_TRACE(FDT_OS, "    Set %s[%s] = %02x:%02x:%02x:%02x:%02x:%02x\n",
                        fdt_node_name, propname,
                        new_mac_address[0], new_mac_address[1],
                        new_mac_address[2], new_mac_address[3],
                        new_mac_address[4], new_mac_address[5]);
                    next_free_mac_address++;
                    num_free_mac_addresses--;
                }
                else
                {
                    /* Out of MACs, remove it */
                    if (fdt_nop_property(fdt, fdt_node, propname))
                    {
                        bdk_error("Failed to NOP property %s[%s]\n",
                            fdt_node_name, propname);
                        return -1;
                    }
                    BDK_TRACE(FDT_OS, "    Removed property %s[%s]\n", fdt_node_name, propname);
                }
            }
        }
        fdt_node = devtree_node_offset_by_prop_name(fdt, fdt_node, propname);
    }
    return 0;
}

/**
 * Called to load the operating system device tree and get it ready for following
 * software
 *
 * @param use_atf True if we're booting normally, through ATF
 *
 * @return Zero on success, negative on failure
 */
int devtree_process(int use_atf)
{
    void *fdt = NULL;
#if 0 // NEWPORT
    const char *model = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
    const char *revision = bdk_config_get_str(BDK_CONFIG_BOARD_REVISION);
    char filename[64];

    /* Load BOARD-REVISION-linux.dtb if it is there */
    if (model && revision)
    {
        snprintf(filename, sizeof(filename), "/rom/%s-%s-linux.dtb", model, revision);
        fdt = devtree_load(filename);
    }

    /* Load BOARD-linux.dtb if it is there */
    if (!fdt && model)
    {
        snprintf(filename, sizeof(filename), "/rom/%s-linux.dtb", model);
        fdt = devtree_load(filename);
    }

    /* Load generic-linux.dtb if it is there */
    if (!fdt)
    {
        snprintf(filename, sizeof(filename), "/rom/generic-linux.dtb");
        fdt = devtree_load(filename);
    }

    /* Load BOARD-REVISION-linux.dtb if it is there */
    if (!fdt && model && revision)
    {
        snprintf(filename, sizeof(filename), "/fatfs/dtb/%s-%s-linux.dtb", model, revision);
        fdt = devtree_load(filename);
    }

    /* Load BOARD-linux.dtb if it is there */
    if (!fdt && model)
    {
        snprintf(filename, sizeof(filename), "/fatfs/dtb/%s-linux.dtb", model);
        fdt = devtree_load(filename);
    }

    /* Load generic-linux.dtb if it is there */
    if (!fdt)
    {
        snprintf(filename, sizeof(filename), "/fatfs/dtb/generic-linux.dtb");
        fdt = devtree_load(filename);
    }
#else
	const char *model = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
	char filename[64];
	const char *file;
	bdk_node_t node = bdk_numa_master();
	int i;

	for (i = 0; ; i++) {
		file = gsc_get_dtb_name(node, i);
		if (!file)
			break;
		snprintf(filename, sizeof(filename), "/fatfs/%s-linux.dtb",
			 file);
		fdt = devtree_load(filename);
		if (fdt) {
			break;
		}
	}
#endif // NEWPORT

    /* Warn if we could load a device tree */
    if (!fdt)
    {
        if (use_atf)
        {
            printf("\33[1m"); /* Bold */
            bdk_warn("\n");
            bdk_warn("********************************************************\n");
            bdk_warn("* Operating system device tree not found. Operating\n");
            bdk_warn("* system may not boot properly. DTB file not found for\n");
            bdk_warn("* board \"%s\". ATF will not load.\n", model);
            bdk_warn("********************************************************\n");
            bdk_warn("\n");
            printf("\33[0m"); /* Normal */
        }
        return -1;
    }

    BDK_TRACE(FDT_OS, "Processing FDT for Operating System (%s)\n", filename);

    /* Copy the BDK settings to the new tree */
    if (devtree_copy_settings(fdt))
    {
        free(fdt);
        return -1;
    }

    /* Expand the defaults for missing entries */
    if (bdk_config_expand_defaults(fdt))
    {
        free(fdt);
        return -1;
    }

    /* Perform device tree fixups for Linux */
    if (devtree_fixups(fdt))
    {
        free(fdt);
        return -1;
    }

    /* Perform device tree fixups for board */
    if (newport_devtree_fixups(fdt))
    {
        free(fdt);
        return -1;
    }

    /* Swap the BDK config FDT for this one */
    if (bdk_config_set_fdt(fdt))
    {
        bdk_error("Failed to replace config FDT\n");
        free(fdt);
        return -1;
    }
    BDK_TRACE(FDT_OS, "Using FDT for Operating System\n");

    return 0;
}
