/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

static void init_early(void)
{
    BDK_TRACE(INIT, "EBB9504: Called %s\n", __FUNCTION__);
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "EBB9504: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    int node = bdk_numa_master();

    BDK_TRACE(INIT, "EBB9504: Called %s\n", __FUNCTION__);

    /* EBB9504 only swizzled for CN95E */
    if (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN95XXE)
    {
        bdk_config_set_int(0x0123, BDK_CONFIG_NETWORK_LANE_ORDER, node, 0); /* QLM7 */
        bdk_config_set_int(0x2301, BDK_CONFIG_NETWORK_LANE_ORDER, node, 1); /* DLM4 */
        bdk_config_set_int(0x0123, BDK_CONFIG_NETWORK_LANE_ORDER, node, 2); /* QLM6 */
    }

    /* This structure defines how we should determine if a module is plugged
       in. If the associated SMI bus and address respond with the proper PHY
       identifier, then add the modules DEVICES line */
    struct query_item
    {
        int smi;            /* SMI/MDIO bus to use, >= 16 is special for EBB */
        int address;        /* SMI/MDIO address to query */
        int dev;            /* SMI/MDIO device to query (-1 for clause 22) */
        int reg;            /* SMI/MDIO register to query */
        int phy_id;         /* Expected PHY ID info */
        uint16_t phy_id_msk;  /* Mask of valid bits in PHY ID register */
        const char *device; /* Device line to add */
    };

    /* List of modules to check for, swizzled for CN95e */
    static const struct query_item query_list_cn95e[] = {
        /* Slot 0, package QLM0, die QLM3, PCIe only */
        { /* Slot 1, package QLM1, die QLM7 */
            .smi = 1, /* SMI1, not switched */
            .address = 4,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot1,type=PHY-VSC8574,smi=1,addr=4,qlm=7,qlm_lane=3",
        },
        { /* Slot 1, package QLM1, die QLM7 */
            .smi = 1, /* SMI1, not switched */
            .address = 4,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot1,type=PHY-88X5113,smi=1,addr=4,qlm=7,qlm_lane=3",
        },
        { /* Slot 2, package QLM2, die QLM6 */
            .smi = 17, /* SMI0, switch B */
            .address = 8,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot2,type=PHY-VSC8574,smi=17,addr=8,qlm=6,qlm_lane=3",
        },
        { /* Slot 2, package QLM2, die QLM6 */
            .smi = 17, /* SMI0, switch B */
            .address = 8,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot2,type=PHY-88X5113,smi=17,addr=8,qlm=6,qlm_lane=3",
        },
        { /* Slot 3, package DLM3, die DLM4 */
            .smi = 16, /* SMI0, switch A */
            .address = 12,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot3,type=PHY-VSC8574,smi=16,addr=12,qlm=4,qlm_lane=1",
        },
        { /* Slot 3, package DLM3, die DLM4 */
            .smi = 16, /* SMI0, switch A */
            .address = 12,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot3,type=PHY-88X5113,smi=16,addr=12,qlm=4,qlm_lane=3",
        },
        { /* End of list */
            .smi = -1,
        }
    };

    /* List of modules to check for CNF95XX */
    static const struct query_item query_list_cnf95[] = {
        /* Slot 0, package QLM0, die QLM0, PCIe only */
        { /* Slot 1, package QLM1, die QLM1 */
            .smi = 1, /* SMI1, not switched */
            .address = 4,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot1,type=PHY-VSC8574,smi=1,addr=4,qlm=1,qlm_lane=0",
        },
        { /* Slot 1, package QLM1, die QLM1 */
            .smi = 1, /* SMI1, not switched */
            .address = 4,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot1,type=PHY-88X5113,smi=1,addr=4,qlm=1,qlm_lane=0",
        },
        { /* Slot 2, package QLM2, die QLM2 */
            .smi = 17, /* SMI0, switch B */
            .address = 8,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot2,type=PHY-VSC8574,smi=17,addr=8,qlm=2,qlm_lane=0",
        },
        { /* Slot 2, package QLM2, die QLM2 */
            .smi = 17, /* SMI0, switch B */
            .address = 8,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot2,type=PHY-88X5113,smi=17,addr=8,qlm=2,qlm_lane=0",
        },
        { /* Slot 3, package DLM3, die DLM3 */
            .smi = 16, /* SMI0, switch A */
            .address = 12,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot3,type=PHY-VSC8574,smi=16,addr=12,qlm=3,qlm_lane=0",
        },
        { /* Slot 3, package DLM3, die DLM3 */
            .smi = 16, /* SMI0, switch A */
            .address = 12,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot3,type=PHY-88X5113,smi=16,addr=12,qlm=3,qlm_lane=0",
        },
        { /* End of list */
            .smi = -1,
        }
    };

    /* Get the currect DEVICES list */
    bool need_update = false;
    int devices_size = 0;
    void *devices = (void*)bdk_config_get_blob(&devices_size, BDK_CONFIG_DEVICES);
    if (devices)
    {
        void *tmp = malloc(devices_size);
        if (!tmp)
        {
            bdk_error("EBB9504: Failed to allocate memory for devices\n");
            return;
        }
        memcpy(tmp, devices, devices_size);
        devices = tmp;
    }
    else
        devices_size = 0;

    const struct query_item *query_list = (bdk_is_altpkg(OCTEONTX_CN96XX) == OCTEONTX_ALT_CN95XXE) ? query_list_cn95e : query_list_cnf95;

    /* Add modules to the DEVICES list */
    int i = 0;
    while (query_list[i].smi >= 0)
    {
        int status;
        if (query_list[i].dev == -1)
            status = bdk_mdio_read(node, query_list[i].smi, query_list[i].address, query_list[i].reg);
        else
            status = bdk_mdio_45_read(node, query_list[i].smi, query_list[i].address, query_list[i].dev, query_list[i].reg);

        status &= query_list[i].phy_id_msk;

        if (status == query_list[i].phy_id)
        {
            BDK_TRACE(INIT, "EBB9504: Found %s\n", query_list[i].device);
            int len = strlen(query_list[i].device) + 1; /* Include \0 */
            void *tmp = realloc(devices, devices_size + len);
            if (tmp)
            {
                devices = tmp;
                memcpy(devices + devices_size, query_list[i].device, len);
                devices_size += len;
                need_update = true;
            }
            else
                bdk_error("EBB9504: Failed to allocate memory for device %s\n", query_list[i].device);
        }
        i++;
    }
    /* Set the new DEVICES list */
    if (need_update)
    {
        BDK_TRACE(INIT, "EBB9504: Updating DEVICES\n");
        bdk_config_set_blob(devices_size, devices, BDK_CONFIG_DEVICES);
    }
    if (devices)
        free(devices);
}

static const bdk_boot_callbacks_t ebb9504 = {
    .board_name = "EBB9504",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(ebb9504);

