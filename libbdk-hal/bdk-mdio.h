/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the SMI/MDIO hardware, including support for both IEEE 802.3
 * clause 22 and clause 45 operations.
 *
 * <hr>$Revision: 51350 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/**
 * PHY register 0 from the 802.3 spec
 */
#define BDK_MDIO_PHY_REG_CONTROL 0
typedef union
{
    uint16_t u16;
    struct
    {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint16_t reset : 1;
        uint16_t loopback : 1;
        uint16_t speed_lsb : 1;
        uint16_t autoneg_enable : 1;
        uint16_t power_down : 1;
        uint16_t isolate : 1;
        uint16_t restart_autoneg : 1;
        uint16_t duplex : 1;
        uint16_t collision_test : 1;
        uint16_t speed_msb : 1;
        uint16_t unidirectional_enable : 1;
        uint16_t reserved_0_4 : 5;
#else
        uint16_t reserved_0_4 : 5;
        uint16_t unidirectional_enable : 1;
        uint16_t speed_msb : 1;
        uint16_t collision_test : 1;
        uint16_t duplex : 1;
        uint16_t restart_autoneg : 1;
        uint16_t isolate : 1;
        uint16_t power_down : 1;
        uint16_t autoneg_enable : 1;
        uint16_t speed_lsb : 1;
        uint16_t loopback : 1;
        uint16_t reset : 1;
#endif
    } s;
} bdk_mdio_phy_reg_control_t;

#define BDK_MDIO_PHY_REG_ID1 2
#define BDK_MDIO_PHY_REG_ID2 3

/**
 * Perform an MII read. This function is used to read PHY
 * registers controlling auto negotiation.
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param location Register location to read
 *
 * @return Result from the read or -1 on failure
 */
extern int bdk_mdio_read(bdk_node_t node, int bus_id, int phy_id, int location);

/**
 * Perform an MII write. This function is used to write PHY
 * registers controlling auto negotiation.
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param location Register location to write
 * @param val      Value to write
 *
 * @return -1 on error
 *         0 on success
 */
extern int bdk_mdio_write(bdk_node_t node, int bus_id, int phy_id, int location, int val);

/**
 * Perform an IEEE 802.3 clause 45 MII read. This function is used to read PHY
 * registers controlling auto negotiation.
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param device   MDIO Manageable Device (MMD) id
 * @param location Register location to read
 *
 * @return Result from the read or -1 on failure
 */

extern int bdk_mdio_45_read(bdk_node_t node, int bus_id, int phy_id, int device, int location);

/**
 * Perform an IEEE 802.3 clause 45 MII write. This function is used to write PHY
 * registers controlling auto negotiation.
 *
 * @param node     Node to use in a Numa setup. Can be an exact ID or a special
 *                 value.
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param device   MDIO Manageable Device (MMD) id
 * @param location Register location to write
 * @param val      Value to write
 *
 * @return -1 on error
 *         0 on success
 */
extern int bdk_mdio_45_write(bdk_node_t node, int bus_id, int phy_id, int device, int location,
                                     int val);

/** @} */
