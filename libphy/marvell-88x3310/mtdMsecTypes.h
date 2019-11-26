/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* \file mtdMsecTypes.h
*
* DESCRIPTION:
*       Definitions for MacSec control functions
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/
#ifndef __mtdMsecTypes_h
#define __mtdMsecTypes_h
#include "mtdApiTypes.h"

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*! \brief Structure for MAC Configuration
*/
typedef struct
{
  int mac_type; /** SMC, WMC */
  int speed; /** MTD_GMII, MTD_XGMII */
  int max_frame_sz; /** max frame size */
} MTD_MAC_T;

/*! \brief Structure for ETM Configuration
*/
typedef struct
{
  MTD_U16 etype;
  int act_e;
  int act_i; 
  int rc_idx_e;
  int rc_idx_i;
} MTD_ETM_T;

/*! \brief Per Port MAC Control Variables
 */
typedef struct {
  int mac_type;     /*/< Indicates System or Wire side MAC (0 -> SYS, 1 -> WRE) */
  MTD_U16 port_en;      /*/< Enable Port (0 -> Packet reception is disabled, 1 -> port is enabled) */
  int speed;        /*/< Indcates port operation speed (3 -> 10G, 2 -> 1000 Mbps, 1 -> 100 Mbps, 0 -> 10 Mbps) */
  int mibcnt_en;    /*/< Enable MIB counters update for this port */
  int lpbk_en;      /*/< Enable Port in loopback mode */
  int max_frame_sz; /*/< Maximum Receive Packet Size - MRU (Default value is 0x5F2) */
  int tx_fc_en;
  int rx_fc_en;
  int aneg_fc_en;
  int aneg_en;
} MTD_MAC_CTRL;

/*! \brief Per Port Match Enable Variables
 */
typedef struct {
  int en_def;   /*/< Enable default match (search will always hit this entry if no previous entry matched) */
  int en_mc;    /*/< Enable Muticast match */
  int en_da;    /*/< Enable MAC DA match */
  int en_sa;    /*/< Enable MAC SA match */
  int en_vlan;  /*/< Enable VLAN match */
  int en_et;    /*/< Enable Ethertype match */
  int en_an;   /*/< Enable AN (Valid only for Ingress path) */
  int en_sci; /*/< Enable SCI match (Valid only for Ingress path) */
} MTD_MATCH_EN;

/*! \brief Per Port Match Fields
 */
typedef struct {
  MTD_U64 da;      /*/< MAC DA */
  MTD_U64 sa;      /*/< MAC SA */
  MTD_U16 vlan;    /*/< VLAN */
  MTD_U16 et;      /*/< Ethertype */
  MTD_U64 sci;     /*/< SCI (Valid only for Ingress path */
  MTD_U8  tci;      /*/< TCI (Valid only for Ingress path) */
  MTD_U8  tci_msk; /*/< TCI Mask (Valid only for Ingress path) */
} MTD_MATCH_FLD;

/*! \brief Variables to set action for an entry within a port
 */
typedef struct {
  int set_idx; /*/< Index to the Rewrite Constructor Instruction Template */
  int drop;    /*/< Drop this Packet */
  int redir;   /*/< For Egress, redirect the packet to ingress path (NDL). For Ingress, redirect the packet to alternate destination. */
  int auth_en; /*/< Encapsulate and authenticate this packet. */
  int enc_en;  /*/< Encrypt this packet. auth_en must also be set when this bit is set. (Valid only for egress path). */
  int enc_start_adj; /*/< 8-bit signed number added to enc start pointer */
  int retain_hdr;
  MTD_U8 tci;
} MTD_ACT_FLD;

/*! \brief Structure to set lookup entry table within a port
 */
typedef struct {
  MTD_MATCH_EN  *lk_match_en;  /*/< Per Port Match Enables */
  MTD_MATCH_FLD *lk_match_fld; /*/< Per Port Match Fields */
} MTD_LKUP_T;

/*! \brief Structure to set Context entry table within a port
 *
 * Sets the variables required to program Egress Context table, Egress/Ingress Key and Hash key tables
 *
 */
typedef struct {
  MTD_U64 sci;       /*/< SCI (Valid only for Egress path) */
  MTD_U32 pn;        /*/< Initial Packet Number (Valid only for Egress path) */
  MTD_U8  tci;       /*/< TCI (Valid only for Egress path) */
  MTD_U8  key  [16]; /*/< 128 bit Encrytion/Decryption Key (key[15] -> key[7:0], key[0] -> key[127:120]) */
  MTD_U8  hkey [16]; /*/< 128 bit Encrytion/Decryption Hash Key (hkey[15] -> hkey[7:0], hkey[0] -> hkey[127:120]) */
} MTD_CTX_T;

/*! \brief Structure to set Redirect Header
 */
typedef struct {
  MTD_U64 da;     /*/< Redirect DA */
  MTD_U16 et;     /*/< Redirect Ether Type */
  MTD_U64 sa [4]; /*/< Redirect SA for Port 0,1,2 and 3 */
} MTD_REDIR_HDR_T;

/*! \brief Structure to set all the MACSec Common Configuration variables
 */
typedef struct {
  MTD_U8  trail_sz;    /*/< Trail Size must be program to 0     */
  MTD_U16 def_vlan;   /*/< Default VLAN used for lookups on packets which do not arrive with an 802.1Q tag */
  MTD_U64 mc_high;    /*/< Multicast match register [47:0], Lower 4 bits should be ignored */
  MTD_U16 mc_low_msk; /*/< Muticast match mask register */
} MTD_CMN_CFG_T;

/*! \brief Structure to set per port Egress Configuration
 */
typedef struct {
    MTD_U8 miss_act;  /*/ < 0 - bypass, 1 - drop, 2 - redir */
    MTD_U8 pn_ro;     /*/ < when PN is saturated, roll over when set */
    MTD_U8 clr_rd;  /*/ < clear on read */
    MTD_U8 bypass_msec; /*/ <bypass MACsec when set */
} MTD_EGR_GEN_T;

/*! \brief Structure to set per port Redirect vector
 */
typedef struct {
  int redir_untagged;  /*/< If set, redirect packets due to untagged or no_tag classification. */
  int redir_badtag;    /*/< If set, redirect packets due to bad_tag classification. */
  int redir_unk_sci;   /*/< If set, redirect packets due to unknown_sci or no_sci classification. */
  int redir_unused_sa; /*/< If set, redirect packets due to unused_sa or not_using_sa classification. */
  int redir_unchecked; /*/< If set, redirect packets due to unchecked classification. */
  int redir_delayed;   /*/< If set, redirect packets due to delayed or late classification. */
  int redir_invalid;   /*/< If set, redirect packets due to invalid or not_valid classification. */
} MTD_REDIR_T;

/*! \brief Structure to set per port SCI parameters for Final SCI calculation on Ingress path
 */
typedef struct {
  MTD_U64 implicit_sci; /*/< Implicit SCI */
  MTD_U16 scb_port;     /*/< SCB Port */
  MTD_U16 def_port;     /*/< Default Port */
} MTD_SCI_T;

/*! \brief Structure to set per port Replay parameters on Ingress path
 */
typedef struct {
  int  validate_frames; /*/< Values for validate_frames are disabled=1, check=2, strict=3 */
  int  replay_protect;  /*/< Enables replay checking */
  int  replay_drop;     /*/< If set, enables dropping of packets which fail replay protection*/
  int  replay_window;   /*/< Replay window register */
  int  sliding_window;  /*/< Sliding window protection */
} MTD_RPY_T;

/*! \brief Structure to set per port Ingress General parameters
*/
typedef struct {
  int aa_disable;    /*/< authentiation adjust checking disable */
  int badtag_rej;    /*/< reject packet if it is bypassed due to badtag */
  int pad_en;        /*/< pad non-rejected packets up to 64B */
  int byp_ctl_sl;    /*/< bypass packet if SL field does not correspond to packet len */
  int byp_ctl_v;    /*/< bypass packet if V bit is set */
  int byp_ctl_sc;    /*/< bypass packet if SC bit and either ES or SCB bits are set */
  int byp_ctl_ec;    /*/< bypass packet if DC bits are not 00 or 11 */
  int sectag_flag;    /*/< select which flag bit indicates that a SEC tag was present in pkt */
} MTD_IGR_GEN_T;

/*! \brief Structure to set per port Ingress Check Action parameters
*/
typedef struct {
  int bad_tag;        /*/< action field for bad_tag pkt after ingress check */
  int notag;        /*/< action field for notag pkt after ingress check */
  int untagged;        /*/< action field for untagged pkt after ingress check */
  int notusingsa;    /*/< action field for notusingsa pkt after ingress check */
  int unusedsa;        /*/< action field for unusedsa pkt after ingress check */
  int nosci;        /*/< action field for nosci pkt after ingress check */
  int unknownsci;    /*/< action field for unknownsci pkt after ingress check */
  int late;            /*/< action field for late pkt after ingress check */
  int notvalid;        /*/< action field for notvalid pkt after ingress check */
  int invalid;        /*/< action field for invalid pkt after ingress check */
  int delayed;        /*/< action field for delayed pkt after ingress check */
  int unchecked;    /*/< action field for unchecked pkt after ingress check */
  int ok;            /*/< action field for ok pkt after ingress check */
} MTD_IGR_CHK_ACT_T;


/*! \brief Structure to set per port FIPS Configuration
 */
typedef struct {
  MTD_U8 fips_vec [16]; /*/< 128 bit FIPS vector Injection (vec[15] -> vec[7:0], vec[0] -> vec[127:120]) */
  MTD_U8 key      [16]; /*/< 128 bit Encrytion/Decryption Key or Hash Key (key[15] -> key[7:0], key[0] -> key[127:120]) */
  MTD_U8 egr_igr;       /*/< If 1, Egress port, else ingress */
  MTD_U8 eng_type;      /*/< If 1, AES engine, else GHASH engine */
} MTD_FIPS_CFG_T;

/*! \brief Structure to set MACsec interrupt mask and get interrupt information
 */
typedef struct {
    MTD_U8 smac_intr; /*/< MTD_SMAC interrupt */
    MTD_U8 wmac_intr; /*/< MTD_WMAC interrupt */
    MTD_U8 msec_tx_stats_full; /*/< MACsec egress statistics counter full */
    MTD_U8 msec_rx_stats_full; /*/< MACsec ingress statistics counter full */
    MTD_U8 msec_tx_stats_almost_full; /*/< MACsec egress statistics counter almost full */
    MTD_U8 msec_rx_stats_almost_full; /*/< MACsec ingress statistics counter almost full */
    MTD_U16 msec_tx_mem_rd_err; /*/< MACsec egress memory error */
    MTD_U16 msec_rx_mem_rd_err; /*/< MACsec ingress memory error */
    MTD_U16 slc_intr_set; /*/< MACsec slice interrupt set */
} MTD_MSEC_INT_T;

#define MTD_MACSEC_BYPASS        1
#define MTD_MACSEC_EN           0
#define MTD_ST_FW                1
#define MTD_CT_TH                0
#define MTD_SMAC                1
#define MTD_WMAC                2
#define MTD_GMII                0
#define MTD_XGMII                1
 
#define MTD_SI_ELU            0x0000
#define MTD_SI_ECT_FR        0x0400
#define MTD_SI_EGR_PCAM        0x0800
#define MTD_SI_ECT_BK        0x0B80

#define MTD_SI_EGR_PKT_SZ    0x0C00
#define MTD_SI_EGR_GEN        0x0C02
#define MTD_SI_EGR_RC0        0x0C04
#define MTD_SI_EGR_RC1        0x0C06
#define MTD_SI_EGR_THR        0x0C08
#define MTD_SI_EGR_PMSK     0x0C10
#define MTD_SI_EGR_INT        0x0C22
#define MTD_SI_EGR_INT_MSK    0x0C26

#define MTD_SI_ILU            0x1000
#define MTD_SI_ICT_FR        0x1400
#define MTD_SI_IGR_PCAM        0x1800
#define MTD_SI_IGR_RC_DATA    0x1B00
#define MTD_SI_IGR_NXT_PN    0x1B80
#define MTD_SI_IGR_PKT_SZ    0x1C00
#define MTD_SI_IGR_SCB        0x1C02
#define MTD_SI_IGR_SCI_LO    0x1C04
#define MTD_SI_IGR_SCI_HI    0x1C06
#define MTD_SI_IGR_CHK_CTL    0x1C08
#define MTD_SI_IGR_GEN        0x1C0A
#define MTD_SI_IGR_RPY_WND    0x1C0C
#define MTD_SI_IGR_PMSK     0x1C10
#define MTD_SI_IGR_INT        0x1C26
#define MTD_SI_IGR_INT_MSK  0x1C2A
#define MTD_SI_IGR_BYPIDX    0x1C2E
#define MTD_SI_IGR_CHK_ACT    0x1C40
#define MTD_ETM_REG            0x1C42


#define MTD_SLC_CFG_GEN             0x8000
#define MTD_SLC_STATUS                0x8002
#define MTD_SLC_INT_SET                0x8004
#define MTD_SLC_INT_SET_MSK            0x8006
#define MTD_SLC_PORT_MAC_SA0        0x8008
#define MTD_SLC_PORT_MAC_SA1        0x800A
#define MTD_SLC_CNT_1MS_CFG            0x800C
#define MTD_SLC_CFG_PAUSE_CTL        0x800E
#define MTD_SLC_EDB_THRESH            0x8010
#define MTD_SLC_IDB_THRESH            0x8012
#define MTD_SLC_D_BUF_USAGE            0x8014
#define MTD_SLC_EDB_CFG_REG            0x8016
#define MTD_SLC_IDB_CFG_REG            0x8018

#define MTD_WMAC_MUX_DROP_CNT        0x8024
#define MTD_SMAC_MUX_DROP_CNT        0x8026
#define MTD_IBD_DROP_CNT            0x8028
#define MTD_EBD_DROP_CNT            0x802A
#define MTD_IGR_REDIR_CNT            0x802C
#define MTD_MEM_SBD_CNT                0x802E

#define MTD_SLC_CFG_ENCAP_DA0        0x803A
#define MTD_SLC_CFG_ENCAP_DA_ET        0x803C
#define MTD_SLC_CFG_MSEC_ET            0x8046
#define MTD_SLC_CFG_VLAN_ET            0x8048
#define MTD_SLC_MSIRAM_CTL0            0x8062
#define MTD_SLC_MSIRAM_CTL1            0x8064
#define MTD_SLC_MSIRAM_STATUS0        0x8066
#define MTD_SLC_MSIRAM_STATUS1        0x8068
#define MTD_FIPS_CTL                0x806A
#define MTD_FIPS_VEC_IN0            0x806C
#define MTD_FIPS_VEC_IN1            0x806E
#define MTD_FIPS_VEC_IN2            0x8070
#define MTD_FIPS_VEC_IN3            0x8072
#define MTD_FIPS_KEY_IN0            0x8074
#define MTD_FIPS_KEY_IN1            0x8076
#define MTD_FIPS_KEY_IN2            0x8078
#define MTD_FIPS_KEY_IN3            0x807A
#define MTD_FIPS_VEC_OUT_EAES0        0x807C
#define MTD_FIPS_VEC_OUT_EAES1        0x807E
#define MTD_FIPS_VEC_OUT_EAES2        0x8080
#define MTD_FIPS_VEC_OUT_EAES3        0x8082
#define MTD_FIPS_VEC_OUT_EGHASH0    0x8084
#define MTD_FIPS_VEC_OUT_EGHASH1    0x8086
#define MTD_FIPS_VEC_OUT_EGHASH2    0x8088
#define MTD_FIPS_VEC_OUT_EGHASH3    0x808A
#define MTD_FIPS_VEC_OUT_IAES0        0x808C
#define MTD_FIPS_VEC_OUT_IAES1        0x808E
#define MTD_FIPS_VEC_OUT_IAES2        0x8090
#define MTD_FIPS_VEC_OUT_IAES3        0x8092
#define MTD_FIPS_VEC_OUT_IGHASH0    0x8094
#define MTD_FIPS_VEC_OUT_IGHASH1    0x8096
#define MTD_FIPS_VEC_OUT_IGHASH2    0x8098
#define MTD_FIPS_VEC_OUT_IGHASH3    0x809A
#define MTD_LOW_POWER_MODE0            0x809C
#define MTD_LOW_POWER_MODE1            0x809E
#define MTD_LOW_POWER_MODE2            0x80A0

#define MTD_SLC_CFG_QOS_FC        0x80A2
#define MTD_SLC_CFG_QOS_ETYPE    0x80A4
#define MTD_IMB_CTL                0x80A6
#define MTD_IMB_DATA            0x80A8
#define MTD_IRD_PKT_DROP_CNT    0x80AA

#define MTD_MSEC_LINK_RESET_CFG    0x80B0
#define MTD_MAC_SPEED_STATUS    0x80B6
#define MTD_SRT_PKT_DROP_CFG    0x80B8
#define MTD_EGR_FC_PKT_DROP_CFG    0x80BA
#define MTD_IGR_FC_PKT_DROP_CFG    0x80BC
#define MTD_SMC_SP_DROP_CNT        0x80BE
#define MTD_WMC_SP_DROP_CNT        0x80C0
#define MTD_SMC_FP_DROP_CNT        0x80C2
#define MTD_WMC_FP_DROP_CNT        0x80C4
#define MTD_SMC_FC_DROP_CNT        0x80C6
#define MTD_WMC_FC_DROP_CNT        0x80C8

#define  MTD_SMAC_REG            0x8C00
#define  MTD_WMAC_REG            0x8E00
#define  MTD_MAC_CTL1            0x2
#define  MTD_MAC_CTL2            0x4
#define  MTD_AUTO_NEG            0x6
#define  MTD_MAC_STATUS            0x8
#define  MTD_MAC_INT_GMII        0x10
#define  MTD_MAC_INT_MSK_GMII    0x12
#define  MTD_MAC_INT            0x10
#define  MTD_MAC_INT_MSK        0x12
#define  MTD_MAC_INT_XGMII        0x0A
#define  MTD_MAC_INT_MSK_XGMII    0x0C

#define  MTD_MSEC_SPEED_MII_10M    0
#define  MTD_MSEC_SPEED_MII_100M   1
#define  MTD_MSEC_SPEED_GMII_1G    2
#define  MTD_MSEC_SPEED_XGMII_10G  3
#define  MTD_MSEC_SPEED_XGMII_2P5G 4
#define  MTD_MSEC_SPEED_XGMII_5G   5

#define  MTD_EGR_SEC_STAT        0x0E00
#define  MTD_IGR_SEC_STAT        0x2000
#define  MTD_SMAC_RX_STAT        0x9000
#define  MTD_SMAC_TX_STAT        0x9080
#define  MTD_WMAC_RX_STAT        0x9100
#define  MTD_WMAC_TX_STAT        0x9300

#define MTD_EGR_SEC_STAT_TOT    122  /* 116 124 128 */  /*   0xE00 0xFE8  */
#define MTD_IGR_SEC_STAT_TOT    184  /* 192 */  /*   0x2000 0x22C0 */
#define  MTD_SMAC_STAT_TOT        14   /* 13 */   /*   0x9000 0x9030 ; 0x9080 0x90B0 */
#define  MTD_WMAC_STAT_TOT        55   /* 55 */   /*   0x9100 0x91D8 ; 0x9300 0x93D8 */

typedef enum
{
    MTD_EGR_SEC_STAT_PKT_PROT = 0xE00,
    MTD_EGR_SEC_STAT_PKT_ENC = 0xE80,
    MTD_EGR_SEC_STAT_CTX_HIT = 0xF00,
    MTD_EGR_SEC_STAT_OCT_PROT =0xF80,
    MTD_EGR_SEC_STAT_OCT_ENC  =0xF84,
    MTD_EGR_SEC_STAT_OCT_SENT= 0xF88,
    MTD_EGR_SEC_STAT_CTX_MISS =0xF8C,
    MTD_EGR_SEC_STAT_CTX_MISS_OCT = 0xF90,
    MTD_EGR_SEC_STAT_NDL    =  0xF94,
    MTD_EGR_SEC_STAT_DROP     = 0xF98,
    MTD_EGR_SEC_STAT_HIT_BAD = 0xF9C,
    MTD_EGR_SEC_STAT_ETM_HIT = 0xFA0,
    MTD_EGR_SEC_STAT_ETM_MISS_GOOD = 0xFE0,
    MTD_EGR_SEC_STAT_ETM_MISS_BAD = 0xFE4
} MTD_MSEC_EGR_STAT_E;

typedef enum
{
    MTD_IGR_SEC_STAT_HIT    = 0x2000,
    MTD_IGR_SEC_STAT_OK    = 0x2080,
    MTD_IGR_SEC_STAT_SCI_HIT = 0x2100,
    MTD_IGR_SEC_STAT_LATE    = 0x2180,
    MTD_IGR_SEC_STAT_NOTVALID    = 0x2200,
    MTD_IGR_SEC_STAT_OCT_VAL    = 0x2280,
    MTD_IGR_SEC_STAT_OCT_DEC    = 0x2284,
    MTD_IGR_SEC_STAT_UNTAG        = 0x2288,
    MTD_IGR_SEC_STAT_NOTAG        = 0x228C,
    MTD_IGR_SEC_STAT_BADTAG    = 0x2290,
    MTD_IGR_SEC_STAT_UNKWN_SCI    = 0x2294,
    MTD_IGR_SEC_STAT_NO_SCI    = 0x2298,
    MTD_IGR_SEC_STAT_UNU_SA    = 0x229C,
    MTD_IGR_SEC_STAT_NOTU_SA    = 0x22A0,
    MTD_IGR_SEC_STAT_OCT_TOT    = 0x22A4,
    MTD_IGR_SEC_STAT_MISS        = 0x22A8,
    MTD_IGR_SEC_STAT_MISS_OCT    = 0x22AC,
    MTD_IGR_SEC_STAT_REDIR        = 0x22B0,
    MTD_IGR_SEC_STAT_DROP        = 0x22B4,
    MTD_IGR_SEC_STAT_ETM_MISS_GOOD = 0x22B8,
    MTD_IGR_SEC_STAT_ETM_MISS_BAD    = 0x22BC,
    MTD_IGR_SEC_STAT_ETM_HIT        = 0x22C0
} MTD_MSEC_IGR_STAT_E;

typedef enum
{
    MTD_SMAC_RX_GOOD_OCTETS    = 0x9000,
    MTD_SMAC_RX_ERROR_OCTETS = 0x9004,
    MTD_SMAC_RX_JABBER = 0x9008,
    MTD_SMAC_RX_FRAGMENTS = 0x900C,
    MTD_SMAC_RX_UNDERSIZE = 0x9010,
    MTD_SMAC_RX_OVERSIZE = 0x9014,
    MTD_SMAC_RX_ERROR = 0x9018,
    MTD_SMAC_RX_CRC_ERROR = 0x901C,
    MTD_SMAC_RX_OVERRUN    = 0x9020,
    MTD_SMAC_RX_GOOD_PKTS = 0x9024,
    MTD_SMAC_RX_FC_PKT = 0x9028,
    MTD_SMAC_RX_BROADCAST_PKTS = 0x902C,
    MTD_SMAC_RX_MULTICAST_PKTS = 0x9030
}  MTD_SMAC_RX_STAT_E;

typedef enum
{
    MTD_SMAC_TX_GOOD_OCTETS    = 0x9080,
    MTD_SMAC_TX_ERROR_OCTETS = 0x9084,
    MTD_SMAC_TX_JABBER = 0x9088,
    MTD_SMAC_TX_FRAGMENTS = 0x908C,
    MTD_SMAC_TX_UNDERSIZE = 0x9090,
    MTD_SMAC_TX_OVERSIZE = 0x9094,
    MTD_SMAC_TX_UNDERRUN = 0x909C,
    MTD_SMAC_TX_GOOD_PKTS = 0x90A4,
    MTD_SMAC_TX_FC_PKT = 0x90A8,
    MTD_SMAC_TX_BROADCAST_PKTS = 0x90AC,
    MTD_SMAC_TX_MULTICAST_PKTS = 0x90B0
}  MTD_SMAC_TX_STAT_E;

typedef enum
{
    MTD_RX_PKTS_VL0 = 0x9100,
    MTD_RX_PKTS_VL1 = 0x9104,
    MTD_RX_PKTS_VL2 = 0x9108,
    MTD_RX_PKTS_VL3 = 0x910C,
    MTD_RX_PKTS_VL4 = 0x9110,
    MTD_RX_PKTS_VL5 = 0x9114,
    MTD_RX_PKTS_VL6 = 0x9118,
    MTD_RX_PKTS_VL7 = 0x911C,
    MTD_DROPPED_PKTS_VL0 = 0x9120,
    MTD_DROPPED_PKTS_VL1 = 0x9124,
    MTD_DROPPED_PKTS_VL2 = 0x9128,
    MTD_DROPPED_PKTS_VL3 = 0x912C,
    MTD_DROPPED_PKTS_VL4 = 0x9130,
    MTD_DROPPED_PKTS_VL5 = 0x9134,
    MTD_DROPPED_PKTS_VL6 = 0x9138,
    MTD_DROPPED_PKTS_VL7 = 0x913C,
    MTD_RX_OCTS_VL0 = 0x9140,
    MTD_RX_OCTS_VL1 = 0x9144,
    MTD_RX_OCTS_VL2 = 0x9148,
    MTD_RX_OCTS_VL3 = 0x914C,
    MTD_RX_OCTS_VL4 = 0x9150,
    MTD_RX_OCTS_VL5 = 0x9154,
    MTD_RX_OCTS_VL6 = 0x9158,
    MTD_RX_OCTS_VL7 = 0x915C,
    MTD_RX_OVERSZ_PKTS_VL0 = 0x9160,
    MTD_RX_OVERSZ_PKTS_VL1 = 0x9164,
    MTD_RX_OVERSZ_PKTS_VL2 = 0x9168,
    MTD_RX_OVERSZ_PKTS_VL3 = 0x916C,
    MTD_RX_OVERSZ_PKTS_VL4 = 0x9170,
    MTD_RX_OVERSZ_PKTS_VL5 = 0x9174,
    MTD_RX_OVERSZ_PKTS_VL6 = 0x9178,
    MTD_RX_OVERSZ_PKTS_VL7 = 0x917C,
    MTD_RX_PKTS_ALL = 0x9180,
    MTD_DROPPED_PKTS_ALL = 0x9184,
    MTD_RX_OCTS_ALL = 0x9188,
    MTD_RX_JABBER = 0x918C,
    MTD_RX_FRAGMENTS = 0x9190,
    MTD_RX_UNDERSZ = 0x9194,
    MTD_RX_ERROR = 0x9198,
    MTD_RX_CRC_ERR = 0x919C,
    MTD_RX_FC_PKTS = 0x91A0,
    MTD_RX_BROADCAST_PKTS = 0x91A4,
    MTD_RX_MULTICAST_PKTS = 0x91A8,
    MTD_RX_PKTS_64_OCTS = 0x91AC,
    MTD_RX_PKTS_66_127_OCTS = 0x91B0,
    MTD_RX_PKTS_128_255_OCTS = 0x91B4,
    MTD_RX_PKTS_256_511_OCTS = 0x91B8,
    MTD_RX_PKTS_512_1023_OCTS = 0x91BC,
    MTD_RX_PKTS_1024_1518_OCTS = 0x91C0,
    MTD_RX_PKTS_1519_1522_OCTS = 0x91C4,
    MTD_RX_PKTS_1523_1548_OCTS = 0x91C8,
    MTD_RX_PKTS_1549_2000_OCTS = 0x91CC,
    MTD_RX_PKTS_2001_2500_OCTS = 0x91D0,
    MTD_RX_PKTS_2501_MTU_OCTS = 0x91D4,
    MTD_RX_PKTS_1549_MTU_OCTS = 0x91D8,
}  MTD_WMAC_RX_STATS_E;

typedef enum
{
    MTD_TX_PKTS_VL0 = 0x9300,
    MTD_TX_PKTS_VL1 = 0x9304,
    MTD_TX_PKTS_VL2 = 0x9308,
    MTD_TX_PKTS_VL3 = 0x930C,
    MTD_TX_PKTS_VL4 = 0x9310,
    MTD_TX_PKTS_VL5 = 0x9314,
    MTD_TX_PKTS_VL6 = 0x9318,
    MTD_TX_PKTS_VL7 = 0x931C,
    MTD_TX_DROPPED_PKTS_VL0 = 0x9320,
    MTD_TX_DROPPED_PKTS_VL1 = 0x9324,
    MTD_TX_DROPPED_PKTS_VL2 = 0x9328,
    MTD_TX_DROPPED_PKTS_VL3 = 0x932C,
    MTD_TX_DROPPED_PKTS_VL4 = 0x9330,
    MTD_TX_DROPPED_PKTS_VL5 = 0x9334,
    MTD_TX_DROPPED_PKTS_VL6 = 0x9338,
    MTD_TX_DROPPED_PKTS_VL7 = 0x933C,
    MTD_TX_OCTS_VL0 = 0x9340,
    MTD_TX_OCTS_VL1 = 0x9344,
    MTD_TX_OCTS_VL2 = 0x9348,
    MTD_TX_OCTS_VL3 = 0x934C,
    MTD_TX_OCTS_VL4 = 0x9350,
    MTD_TX_OCTS_VL5 = 0x9354,
    MTD_TX_OCTS_VL6 = 0x9358,
    MTD_TX_OCTS_VL7 = 0x935C,
    MTD_TX_OVERSZ_PKTS_VL0 = 0x9360,
    MTD_TX_OVERSZ_PKTS_VL1 = 0x9364,
    MTD_TX_OVERSZ_PKTS_VL2 = 0x9368,
    MTD_TX_OVERSZ_PKTS_VL3 = 0x936C,
    MTD_TX_OVERSZ_PKTS_VL4 = 0x9370,
    MTD_TX_OVERSZ_PKTS_VL5 = 0x9374,
    MTD_TX_OVERSZ_PKTS_VL6 = 0x9378,
    MTD_TX_OVERSZ_PKTS_VL7 = 0x937C,
    MTD_TX_PKTS_ALL = 0x9380,
    MTD_TX_DROPPED_PKTS_ALL = 0x9384,
    MTD_TX_OCTS_ALL = 0x9388,
    MTD_TX_JABBER = 0x938C,
    MTD_TX_FRAGMENTS = 0x9390,
    MTD_TX_UNDERSZ = 0x9394,
    MTD_TX_ERROR = 0x9398,
    MTD_TX_CRC_ERR = 0x939C,
    MTD_TX_FC_PKTS = 0x93A0,
    MTD_TX_BROADCAST_PKTS = 0x93A4,
    MTD_TX_MULTICAST_PKTS = 0x93A8,
    MTD_TX_PKTS_64_OCTS = 0x93AC,
    MTD_TX_PKTS_66_127_OCTS = 0x93B0,
    MTD_TX_PKTS_128_255_OCTS = 0x93B4,
    MTD_TX_PKTS_256_511_OCTS = 0x93B8,
    MTD_TX_PKTS_512_1023_OCTS = 0x93BC,
    MTD_TX_PKTS_1024_1518_OCTS = 0x93C0,
    MTD_TX_PKTS_1519_1522_OCTS = 0x93C4,
    MTD_TX_PKTS_1523_1548_OCTS = 0x93C8,
    MTD_TX_PKTS_1549_2000_OCTS = 0x93CC,
    MTD_TX_PKTS_2001_2500_OCTS = 0x93D0,
    MTD_TX_PKTS_2501_MTU_OCTS = 0x93D4,
    MTD_TX_PKTS_1549_MTU_OCTS = 0x93D8,
}  MTD_WMAC_TX_STATS_E;

/* ~~~~~~~~~~ Parser defines  ~~~~~~~~~ */
#define  MTD_ENV_PR_CAM_SZ        32
#define  MTD_ENV_PR_ACT_TBL_SZ    32
#define  MTD_ENV_PR_PTR_TBL_SZ    8 
#define  MTD_ENV_PR_DATA_VEC_SZ   32 
#define  MTD_ENV_PR_OUT_VEC_SZ    40 
#define  MTD_ENV_PR_CAM_WD        72
#define  MTD_ENV_PR_PTR_VEC_WD    8 
#define  MTD_ENV_PR_DATA_VEC_WD   32*8 
#define  MTD_ENV_PR_OUT_VEC_WD    320 
#define  MTD_ENV_PR_ACT_VEC_WD    44
/* ~~~~~~~~~~ EPR off/ptrs/flags defines   ~~~~~~~~~~ */
#define  MTD_ENV_EPR_DA_OFF       0
#define  MTD_ENV_EPR_SA_OFF       6
#define  MTD_ENV_EPR_COT_OFF      12
#define  MTD_ENV_EPR_VLAN_OFF     14
#define  MTD_ENV_EPR_ETH_OFF      18
#define  MTD_ENV_EPR_PHDR_OFF     20
#define  MTD_ENV_EPR_SEC_OFF      24

#define  MTD_ENV_EPR_MACSEC_SVPTR 0
#define  MTD_ENV_EPR_COT_SVPTR    1

#define  MTD_ENV_EPR_MACSEC_PTR   1
#define  MTD_ENV_EPR_COT_PTR      2
#define  MTD_ENV_EPR_SECTAG_PTR   3

#define  MTD_ENV_EPR_1Q_FLAG      1
#define  MTD_ENV_EPR_SEC_FLAG     2
#define  MTD_ENV_EPR_MATCH_FLAG   7
/* ~~~~~~~~~~ IPR off/ptrs/flags defines   ~~~~~~~~~~ */
#define  MTD_ENV_IPR_DA_OFF       0
#define  MTD_ENV_IPR_SA_OFF       6
#define  MTD_ENV_IPR_ETH_OFF      12
#define  MTD_ENV_IPR_PHDR_OFF     14
#define  MTD_ENV_IPR_MACSEC_OFF   16
#define  MTD_ENV_IPR_MACSEC_SVPTR 0
#define  MTD_ENV_IPR_MACSEC_PTR   1
#define  MTD_ENV_IPR_AE_FLAG      1
#define  MTD_ENV_IPR_MATCH_FLAG   7

#define  MTD_EGR_RW_IDX_BYP            0
#define  MTD_EGR_RW_IDX_RMV_HDR        1
#define  MTD_EGR_RW_IDX_RMV_HDR_SEC 2
#define  MTD_EGR_RW_IDX_INS_SEC        3
#define  MTD_IGR_RW_IDX_BYP            0
#define  MTD_IGR_RW_IDX_RMV_SEC        1
#define  MTD_IGR_RW_IDX_RMV_8B_SEC    2
/*! \defgroup UtilityDefines Macros to do bit manipulation 
 *@{
 */
/* Bit Manipulation related Macros */
#define MTD_MSEC_BIT(x)           ((MTD_U32)0x00000001 << (x))
#define mtd_msec_bit_get(p,x)     (((p) &  (MTD_MSEC_BIT(x))) >> (x))
#define mtd_msec_bit_set(p,x)     ((p) |=  (MTD_MSEC_BIT(x)))
#define mtd_msec_bit_clear(p,x)   ((p) &= ~(MTD_MSEC_BIT(x)))
#define mtd_msec_bit_flip(p,x)    ((p) ^=  (MTD_MSEC_BIT(x)))
#define mtd_msec_bit_write(p,c,x) (c ? mtd_msec_bit_set(p,x) : mtd_msec_bit_clear(p,x))
/*@}*/

/* For 1-step PTP */
/* Supporse Global PTP register is 0xb000 */
  #define MTD_VN_GLOBAL_PTP    0x8000   /* 0xB000 < PTP Global  */
  #define MTD_VN_TAI_CFG       0xBC00 /*/< TAI configuration  */
  #define MTD_VN_EG_PTP        0xA000 /*/< PTP configuration for Egress  */
  #define MTD_VN_IG_PTP        0xA800 /*/< PTP configuration for Ingress  */
/* */
typedef enum
{
    MTD_MACSEC_POWER_MODE_POWEROFF        = 0,
    MTD_MACSEC_POWER_MODE_RESET           = 1,
    MTD_MACSEC_POWER_MODE_SLEEP           = 2,
    MTD_MACSEC_POWER_MODE_ACTIVE           = 3,
} MTD_MACSEC_POWER_MODE;

/* # valid type can be "SFI", "XFI", "RXAUI" */
typedef enum  {
  MTD_MSEC_PCS_TYPE_SFI     = 0x0,
  MTD_MSEC_PCS_TYPE_XFI     = 0x1,
  MTD_MSEC_PCS_TYPE_RXAUI   = 0x2,  
  MTD_MSEC_PCS_TYPE_SFI_1G  = 0x3,
  MTD_MSEC_PCS_TYPE_XFI_1G  = 0x4,
} MTD_MSEC_PCS_TYPE;

typedef enum {
  MTD_MAC_MII_10    = 0x0,
  MTD_MAC_MII_100    = 0x1,
  MTD_MAC_GMII        = 0x2,
  MTD_MAC_XGMII        = 0x3,
  MTD_MAC_XGMII_2P5G     = 0x4,
  MTD_MAC_XGMII_5G        = 0x5,
} MTD_MAC_SPEED;

#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* __mtdMsecTypes_h */
