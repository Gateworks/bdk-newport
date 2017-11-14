#ifndef BDK_AQR_DRIVER_H
#define BDK_AQR_DRIVER_H
typedef enum
{
  /*! This indicates that no loopback mode is selected.*/
 BDK_AQ_FWMLC_No_LB,
  /*! This selects the system loopback test mode within the system
      interface. Traffic from the system will be redirected towards
      the system.*/
 BDK_AQ_FWMLC_SysIntf_SysLB,
  /*! This selects the system loopback test mode within the system
      interface. Traffic from the system will be redirected towards
      the system, and also will be passed through towards the
      network.*/
 BDK_AQ_FWMLC_SysIntf_SysLB_Passthrough,
  /*! This selects the network loopback test mode within the system
      interface. Traffic from the network will be redirected towards
      the network.*/
 BDK_AQ_FWMLC_SysIntf_NetLB,
  /*! This selects the network loopback test mode within the system
      interface. Traffic from the network will be redirected towards
      the network, and also will be passed through towards the
      system.*/
 BDK_AQ_FWMLC_SysIntf_NetLB_Passthrough,
  /*! This selects the network loopback test mode within the system
      interface. Traffic from the network will be redirected towards
      the network, and also will be passed through towards the system.
      The redirected traffic will be non-destructively merged with
      traffic from the system.*/
 BDK_AQ_FWMLC_SysIntf_NetLB_PassthroughMerge,
  /*! This selects the system loopback test mode within the network
      interface. Traffic from the system will be redirected towards
      the system.*/
 BDK_AQ_FWMLC_NetIntf_SysLB, /* Works */
  /*! This selects the system loopback test mode within the network
      interface. Traffic from the system will be redirected towards
      the system, and also will be passed through towards the
      network.*/
 BDK_AQ_FWMLC_NetIntf_SysLB_Passthrough,
  /*! This selects the system loopback test mode within the network
      interface. Traffic from the system will be redirected towards
      the system. A loopback plug must be inserted in the MDI port.*/
 BDK_AQ_FWMLC_NetIntf_SysLB_Plug,
  /*! This selects the network loopback test mode within the network
      interface. Traffic from the network will be redirected towards
      the network.*/
 BDK_AQ_FWMLC_NetIntf_NetLB,
  /*! This selects the network loopback test mode within the network
      interface. Traffic from the network will be redirected towards
      the network, and also will be passed through towards the
      system.*/
 BDK_AQ_FWMLC_NetIntf_NetLB_Passthrough,
  /*! This selects the system loopback test mode within the cross-
      connect (between the network and system interfaces). Traffic
      from the system will be redirected towards the system.*/
 BDK_AQ_FWMLC_CrossConnect_SysLB,
  /*! This selects the network loopback test mode within the cross-
      connect (between the network and system interfaces). Traffic
      from the network will be redirected towards the network.*/
 BDK_AQ_FWMLC_CrossConnect_NetLB,
  /*! Unrecognized mode- do not use.*/
 BDK_AQ_FWMLC_Other
} fwlbk_lbk_t;

/*! This enumeration is used to select a packet generation data rate
    for an Aquantia PHY.*/
typedef enum
{
  /*! This indicates that a loopback will be automatically chosen,
      based on the currently active system/network interface.*/
 BDK_AQ_FWMLRate_Auto,
  /*! This indicates that a loopback in the 10G data path will be
      set.*/
 BDK_AQ_FWMLRate_10G,
  /*! This indicates that a loopback in the 5G data path will be
      set.*/
 BDK_AQ_FWMLRate_5G,
  /*! This indicates that a loopback in the 2.5G data path will be
      set.*/
 BDK_AQ_FWMLRate_2_5G,
  /*! This indicates that a loopback in the 1G data path will be
      set.*/
 BDK_AQ_FWMLRate_1G,
  /*! This indicates that a loopback in the 100M data path will be
      set.*/
 BDK_AQ_FWMLRate_100M,
  /*! Unrecognized mode- do not use.*/
 BDK_AQ_FWMLRate_Other
} fwlbk_rate_t;


extern int bdk_aqr_set_fwlbk(bdk_node_t node, int mdio_bus, int mdio_phy, int lbk, int neg_rate);

extern int bdk_aqr_get_linkstat(bdk_node_t node, int mdio_bus, int mdio_phy, int *rxUp, int *txReady, int *sysDataRate, int *net_connected);

extern int bdk_aqr_restart_an(bdk_node_t node, int mdio_bus, int mdio_phy);

extern int bdk_aqr_get_status(bdk_node_t node, int mdio_bus, int mdio_phy);

extern int bdk_aqr_connstat(bdk_node_t node, int mdio_bus, int mdio_phy);
extern int bdk_aqr_counters(bdk_node_t node, int mdio_bus, int mdio_phy);

extern int bdk_aqr_set_fwlbk(bdk_node_t node, int mdio_bus, int mdio_phy, int lbk, int neg_rate);
extern int bdk_aqr_get_fwlbk(bdk_node_t node, int mdio_bus, int mdio_phy);

extern int bdk_aqr_set_active(bdk_node_t node, int mdio_bus, int mdio_phy);

extern int bdk_aqr_reset(bdk_node_t node, int mdio_bus, int mdio_phy,int hardreset);
/* Writes an image to phy flash */
extern int __bdk_aqr_write_ext_image(bdk_node_t node, int mdio_bus, int mdio_phy, const uint8_t *img, const uint32_t img_len);
/* Loads an image */
extern int __bdk_aqr_load_ext_image(bdk_node_t node, int mdio_bus, int mdio_phy, const uint8_t *img, const uint32_t img_len);

#endif
