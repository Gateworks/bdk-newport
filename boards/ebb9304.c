/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

static void init_early(void)
{
    BDK_TRACE(INIT, "EBB9304: Called %s\n", __FUNCTION__);
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "EBB9304: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    int node = bdk_numa_master();

    BDK_TRACE(INIT, "EBB9304: Called %s\n", __FUNCTION__);

    /* This structure defines how we should determine if a module is plugged
       in. If the associated SMI bus and address respond with the proper PHY
       identifier, then add the modules DEVICES line */
    struct query_item
    {
        int smi;            /* SMI/MDIO bus to use, >= 16 is special for EBB */
        int address;        /* SMI/MDIO address to query */
        int phy_id;         /* If register 2 is this value, add the following device line */
        const char *device; /* Device line to add */
    };

    /* List of modules to check for */
    static const struct query_item query_list[] = {
        { /* Slot 3 */
            .smi = 16,
            .address = 12,
            .phy_id = 0x0007,
            .device = "qsgmii-phy,type=PHY-VSC8574,smi=0,addr=12,qlm=3,qlm_lane=3",
        },
        { /* Slot 4 */
            .smi = 17,
            .address = 16,
            .phy_id = 0x0007,
            .device = "qsgmii-phy,type=PHY-VSC8574,smi=17,addr=16,qlm=4,qlm_lane=3",
        },
        { /* Slot 5 */
            .smi = 18,
            .address = 20,
            .phy_id = 0x0007,
            .device = "qsgmii-phy,type=PHY-VSC8574,smi=18,addr=20,qlm=5,qlm_lane=1",
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
        int status = bdk_mdio_read(node, query_list[i].smi, query_list[i].address, BDK_MDIO_PHY_REG_ID1);
        if (status == query_list[i].phy_id)
        {
            BDK_TRACE(INIT, "EBB9304: Found %s\n", query_list[i].device);
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
                bdk_error("EBB9304: Failed to allocate memory for device %s\n", query_list[i].device);
        }
        i++;
    }
    /* Set the new DEVICES list */
    if (need_update)
    {
        BDK_TRACE(INIT, "EBB9304: Updating DEVICES\n");
        bdk_config_set_blob(devices_size, devices, BDK_CONFIG_DEVICES);
    }
    if (devices)
        free(devices);
}

static const bdk_boot_callbacks_t ebb9304 = {
    .board_name = "EBB9304",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(ebb9304);

