/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

static void init_early(void)
{
    BDK_TRACE(INIT, "EBB9604: Called %s\n", __FUNCTION__);
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "EBB9604: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    int node = bdk_numa_master();

    BDK_TRACE(INIT, "EBB9604: Called %s\n", __FUNCTION__);

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

    /* List of modules to check for */
    static const struct query_item query_list[] = {
        { /* Slot 3 */
            .smi = 16,
            .address = 12,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot3,type=PHY-VSC8574,smi=0,addr=12,qlm=3,qlm_lane=3",
        },
        { /* Slot 3 */
            .smi = 16,
            .address = 12,
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot3,type=PHY-88X5113,smi=0,addr=12,qlm=3,qlm_lane=3",
        },
         { /* Slot 4 */
            .smi = 17,
            .address = 16,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot4,type=PHY-VSC8574,smi=17,addr=16,qlm=4,qlm_lane=3",
        },
        { /* Slot 4 */
            .smi = 17,
            .address = 0, /* 16 & 0xF, no address bit 5 on 100G card */
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot4,type=PHY-88X5113,smi=17,addr=0,qlm=4,qlm_lane=3",
        },
        { /* Slot 5 */
            .smi = 18,
            .address = 20,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot5,type=PHY-VSC8574,smi=18,addr=20,qlm=5,qlm_lane=1",
        },
        { /* Slot 5 */
            .smi = 18,
            .address = 4, /* 20 & 0xF, no address bit 5 on 100G card */
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot5,type=PHY-88X5113,smi=17,addr=0,qlm=4,qlm_lane=3",
        },
        { /* Slot 6 */
            .smi = 27,
            .address = 24,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot6,type=PHY-VSC8574,smi=27,addr=24,qlm=6,qlm_lane=3",
        },
        { /* Slot 6 */
            .smi = 27,
            .address = 8, /* 24 & 0xF, no address bit 5 on 100G card */
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot6,type=PHY-88X5113,smi=27,addr=8,qlm=6,qlm_lane=3",
        },
        { /* Slot 7 */
            .smi = 28,
            .address = 28,
            .dev = -1,
            .reg = 2,
            .phy_id = 0x0007,
            .phy_id_msk = 0xffff,
            .device = "fly-qsgmii-slot7,type=PHY-VSC8574,smi=28,addr=28,qlm=7,qlm_lane=3",
        },
        { /* Slot 7 */
            .smi = 28,
            .address = 12, /* 28 & 0xF, no address bit 5 on 100G card */
            .dev = 1,
            .reg = 0x1003,
            .phy_id = 0x0b40,
            .phy_id_msk = 0xfff0,
            .device = "fly-100g-slot7,type=PHY-88X5113,smi=28,addr=12,qlm=7,qlm_lane=3",
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
            bdk_error("EBB9604: Failed to allocate memory for devices\n");
            return;
        }
        memcpy(tmp, devices, devices_size);
        devices = tmp;
    }
    else
        devices_size = 0;

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
            BDK_TRACE(INIT, "EBB9604: Found %s\n", query_list[i].device);
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
                bdk_error("EBB9604: Failed to allocate memory for device %s\n", query_list[i].device);
        }
        i++;
    }
    /* Set the new DEVICES list */
    if (need_update)
    {
        BDK_TRACE(INIT, "EBB9604: Updating DEVICES\n");
        bdk_config_set_blob(devices_size, devices, BDK_CONFIG_DEVICES);
    }
    if (devices)
        free(devices);
}

static const bdk_boot_callbacks_t ebb9604 = {
    .board_name = "EBB9604",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(ebb9604);

