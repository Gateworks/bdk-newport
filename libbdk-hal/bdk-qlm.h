/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Function and structure definitions for QLM manipulation
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

typedef enum
{
    BDK_QLM_MODE_DISABLED,  /* QLM is disabled (all chips) */

    /* PCIe modes  */

    BDK_QLM_MODE_PCIE_X1,  /* 1 PCIe, 1 lane. Other lanes unused */
    BDK_QLM_MODE_PCIE_X2,  /* 1 PCIe, 2 lanes */
    BDK_QLM_MODE_PCIE_X4,  /* 1 PCIe, 4 lanes */
    BDK_QLM_MODE_PCIE_X8,  /* 1 PCIe, 8 lanes */
    BDK_QLM_MODE_PCIE_X16,  /* 1 PCIe, 16 lanes (CN96XX) */

    /* SATA modes  */

    BDK_QLM_MODE_SATA,          /* SATA, each lane independent */

    /* BGX / CGX modes */

    BDK_QLM_MODE_SGMII,         /* SGMII, each lane independent */
    BDK_QLM_MODE_1G_X,          /* 1000BASE-X, each lane independent */
    BDK_QLM_MODE_QSGMII,        /* QSGMII is 4 SGMII on one lane */
    BDK_QLM_MODE_XAUI,          /* XAUI or DXAUI, 4 lanes, use gbaud to tell difference */
    BDK_QLM_MODE_RXAUI,         /* RXAUI, 2 lanes each */
    BDK_QLM_MODE_XFI,           /* XFI, 1 lane each */
    BDK_QLM_MODE_SFI,           /* SFI, 1 lane each (CN9XXX) */
    BDK_QLM_MODE_XLAUI,         /* XLAUI chip to chip, 4 lanes each */
    BDK_QLM_MODE_XLAUI_C2M,     /* XLAUI chip to module, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_10G_KR,        /* 10GBASE-KR, 1 lane each */
    BDK_QLM_MODE_40G_CR4,       /* 40GBASE-CR4, 4 lanes each */
    BDK_QLM_MODE_40G_KR4,       /* 40GBASE-KR4, 4 lanes each */
    BDK_QLM_MODE_20GAUI_C2C,    /* 20GAUI chip to chip, 1 lane each (CN9XXX) */
    BDK_QLM_MODE_25GAUI_C2C,    /* 25GAUI chip to chip, 1 lane each (CN9XXX) */
    BDK_QLM_MODE_25GAUI_C2M,    /* 25GAUI chip to module, 1 lane each (CN9XXX) */
    BDK_QLM_MODE_25G_CR,        /* 25GBASE-CR, 1 lane each (CN9XXX) */
    BDK_QLM_MODE_25G_KR,        /* 25GBASE-KR, 1 lane each (CN9XXX) */
    BDK_QLM_MODE_25GAUI_2_C2C,  /* 25GAUI-2 chip to chip, 2 lanes each (CN9XXX) */
    BDK_QLM_MODE_40GAUI_2_C2C,  /* 40GAUI-2 chip to chip, 2 lanes each (CN9XXX) */
    BDK_QLM_MODE_50GAUI_2_C2C,  /* 50GAUI-2 chip to chip, 2 lanes each (CN9XXX) */
    BDK_QLM_MODE_50GAUI_2_C2M,  /* 50GAUI-2 chip to module, 2 lanes each (CN9XXX) */
    BDK_QLM_MODE_50G_CR2,       /* 50GBASE-CR2, 2 lanes each (CN9XXX) */
    BDK_QLM_MODE_50G_KR2,       /* 50GBASE-KR2, 2 lanes each (CN9XXX) */
    BDK_QLM_MODE_50GAUI_4_C2C,  /* 50GAUI-2 chip to chip, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_80GAUI_4_C2C,  /* 80GAUI-2 chip to chip, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_CAUI_4_C2C,    /* CAUI-4 chip to chip, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_CAUI_4_C2M,    /* CAUI-4 chip to module, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_100G_CR4,      /* 100GBASE-CR4, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_100G_KR4,      /* 100GBASE-KR4, 4 lanes each (CN9XXX) */
    BDK_QLM_MODE_USXGMII_4X1,   /* USXGMII, 4 over 1 lane, 10M, 100M, 1G, 2.5G, 5G (CN9XXX) */
    BDK_QLM_MODE_USXGMII_2X1,   /* USXGMII, 2 over 1 lane, 10M, 100M, 1G, 2.5G, 5G, 10G (CN9XXX) */
    BDK_QLM_MODE_USXGMII_1X1,   /* USXGMII, 1 over 1 lane, 10M, 100M, 1G, 2.5G, 5G, 10G, 20G (CN9XXX) */

    BDK_QLM_MODE_LAST,
} bdk_qlm_modes_t;

typedef enum
{
    BDK_QLM_CLK_COMMON_0,
    BDK_QLM_CLK_COMMON_1,
    BDK_QLM_CLK_EXTERNAL,
    BDK_QLM_CLK_COMMON_2, /* Must be after EXTERNAL as device trees have hard coded values */
    BDK_QLM_CLK_LAST,
} bdk_qlm_clock_t;

typedef enum
{
    BDK_QLM_MODE_FLAG_NONE = 0,     /* No flags */
    BDK_QLM_MODE_FLAG_ENDPOINT = 1, /* PCIe in EP instead of RC */
} bdk_qlm_mode_flags_t;

typedef enum
{
    BDK_QLM_LOOP_DISABLED,  /* No loopback */
    BDK_QLM_LOOP_SHALLOW,   /* Loop external data RX->TX (Not supported on CN8XXX) */
    BDK_QLM_LOOP_NEAR_END,  /* Loop internal data TX->RX in analog domain (Not supported on CN8XXX) */
    BDK_QLM_LOOP_CORE,      /* Loop internal data TX->RX in digital domain */
} bdk_qlm_loop_t;

typedef enum
{
    BDK_QLM_DIRECTION_TX = 1,
    BDK_QLM_DIRECTION_RX = 2,
    BDK_QLM_DIRECTION_BOTH = 3,
} bdk_qlm_direction_t;

/**
 * Types of QLM margining supported
 */
typedef enum
{
    BDK_QLM_MARGIN_VERTICAL,
    BDK_QLM_MARGIN_HORIZONTAL,
} bdk_qlm_margin_t;

/**
 * Eye diagram captures are stored in the following structure
 */
typedef struct
{
    int width;              /* Width in the x direction (time) */
    int height;             /* Height in the y direction (voltage) */
    uint32_t data[64][128]; /* Error count at location, saturates as max */
} bdk_qlm_eye_t;

/**
 * The following structure is used to describe the possible modes for a QLM/DLM.
 * Each chip defines an array of these per QLM/DLM to describe what modes the
 * user is allowed to select.
 */
typedef struct
{
    bdk_qlm_modes_t         mode  : 8;      /* Mode of the QLM */
    bdk_qlm_mode_flags_t    flags : 4;      /* Any flags */
    bdk_qlm_clock_t         ref_clk : 4;    /* Recommended reference clock */
    uint16_t                speed;          /* Baud rate in MHz */
} bdk_qlm_mode_desc_t;

/**
 * How to do the various QLM operations changes greatly
 * between chips. Each chip has its specific operations
 * stored in the structure below. The correct structure
 * is chosen based on the chip we're running on.
 */
typedef struct
{
    uint32_t chip_model;
    void (*init)(bdk_node_t node);
    int (*get_num)(bdk_node_t node);
    int (*get_lanes)(bdk_node_t node, int qlm);
    bdk_qlm_modes_t (*get_mode)(bdk_node_t node, int qlm, int lane);
    int (*set_mode)(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags);
    int (*get_gbaud_mhz)(bdk_node_t node, int qlm, int lane);
    int (*measure_refclock)(bdk_node_t node, int qlm);
    int (*get_qlm_num)(bdk_node_t node, bdk_if_t iftype, int interface, int index);
    int (*reset)(bdk_node_t node, int qlm);
    int (*enable_prbs)(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir);
    int (*disable_prbs)(bdk_node_t node, int qlm);
    uint64_t (*get_prbs_errors)(bdk_node_t node, int qlm, int lane, int clear);
    void (*inject_prbs_error)(bdk_node_t node, int qlm, int lane);
    int (*enable_loop)(bdk_node_t node, int qlm, bdk_qlm_loop_t loop);
    int (*auto_config)(bdk_node_t node);
    int (*tune_lane_tx)(bdk_node_t node, int qlm, int lane, int tx_swing, int tx_pre, int tx_post, int tx_gain, int tx_vboost);
    int (*get_tune_lane_tx)(bdk_node_t node, int qlm, int lane, int *tx_swing, int *tx_pre, int *tx_post, int *tx_gain, int *tx_vboost);
    int (*rx_equalization)(bdk_node_t node, int qlm, int lane);
    int (*eye_capture)(bdk_node_t node, int qlm, int qlm_lane, int show_data, bdk_qlm_eye_t *eye);
    void (*display_settings)(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx);
    const bdk_qlm_mode_desc_t *(*get_mode_desc)(bdk_node_t node, int qlm);
    int (*qlm_to_network)(bdk_node_t node, int qlm, bool *is_split, bool *is_upper);
} bdk_qlm_ops_t;

/**
 * Initialize the QLM layer
 */
extern void bdk_qlm_init(bdk_node_t node) BDK_WEAK;

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
extern int bdk_qlm_get_num(bdk_node_t node);

/**
 * Return the number of lanes in a QLM. QLMs normally contain
 * 4 lanes, except for chips which only have half of a QLM.
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param qlm    QLM to get lanes number for
 *
 * @return Number of lanes on the QLM
 */
extern int bdk_qlm_get_lanes(bdk_node_t node, int qlm);

/**
 * Convert a mode into a configuration variable string value
 *
 * @param mode   Mode to convert
 *
 * @return configuration value string
 */
extern const char *bdk_qlm_mode_to_cfg_str(bdk_qlm_modes_t mode);

/**
 * Convert a mode into a human understandable string
 *
 * @param mode   Mode to convert
 *
 * @return Easy to read string
 */
extern const char *bdk_qlm_mode_tostring(bdk_qlm_modes_t mode);

/**
 * Convert a configuration variable value string into a mode
 *
 * @param val  Configuration variable value
 *
 * @return mode
 */
extern bdk_qlm_modes_t bdk_qlm_cfg_string_to_mode(const char *val);

/**
 * Get the mode of a QLM as a human readable string
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return String mode
 */
extern bdk_qlm_modes_t bdk_qlm_get_mode(bdk_node_t node, int qlm, int lane);

/**
 * For chips that don't use pin strapping, this function programs
 * the QLM lane to the specified mode
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param lane     Lane inside the QLM
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 * @param flags    Flags to specify mode specific options
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_set_mode(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags);

/**
 * Set the QLM's clock source.
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param clk      Clock source for QLM
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_set_clock(bdk_node_t node, int qlm, bdk_qlm_clock_t clk);

/**
 * Get the speed (Gbaud) of the QLM in Mhz.
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return Speed in Mhz
 */
extern int bdk_qlm_get_gbaud_mhz(bdk_node_t node, int qlm, int lane);

/**
 * Measure the reference clock of a QLM
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
extern int bdk_qlm_measure_clock(bdk_node_t node, int qlm);

/**
 * Lookup the hardware QLM number for a given interface type and
 * index. If the associated interface doesn't map to a QLM,
 * returns -1.
 *
 * @param node      Node to use in a Numa setup
 * @param iftype    Interface type
 * @param interface Interface index number
 * @param index     Port on the interface. Most chips use the
 *                  same mode for all ports, but there are
 *                  exceptions. For example, BGX2 on CN83XX
 *                  spans two DLMs.
 *
 * @return QLM number or -1 on failure
 */
extern int bdk_qlm_get(bdk_node_t node, bdk_if_t iftype, int interface, int index);

/**
 * Reset a QLM to its initial state
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_reset(bdk_node_t node, int qlm);

/**
 * Enable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param prbs   PRBS mode (31, etc)
 * @param dir    Directions to enable. This is so you can enable TX and later
 *               enable RX after TX has run for a time
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_enable_prbs(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir);

/**
 * Disable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_disable_prbs(bdk_node_t node, int qlm);

/**
 * Return the number of PRBS errors since PRBS started running
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 * @param clear  Clear the counter after returning its value
 *
 * @return Number of errors
 */
extern uint64_t bdk_qlm_get_prbs_errors(bdk_node_t node, int qlm, int lane, int clear);

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
extern void bdk_qlm_inject_prbs_error(bdk_node_t node, int qlm, int lane);

/**
 * Enable shallow loopback on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param loop   Type of loopback. Not all QLMs support all modes
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_enable_loop(bdk_node_t node, int qlm, bdk_qlm_loop_t loop);

/**
 * Configure the TX tuning parameters for a QLM lane. The tuning parameters can
 * be specified as -1 to maintain their current value
 *
 * @param node     Node to configure
 * @param qlm      QLM to configure
 * @param lane     Lane to configure
 * @param tx_swing Transmit swing, also called cMain (coef 0)
 * @param tx_pre   Pre cursor emphasis (Coef -1)
 * @param tx_post  Post cursor emphasis (Coef +1)
 * @param tx_gain_bias
 *                 For CN8XXX, this is transmit gain. For CN9XXX, this is transmit bias
 * @param tx_vboost_unused
 *                 For CN8XXX, this is transmit voltage boost. For CN9XXX, this is unused
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_tune_lane_tx(bdk_node_t node, int qlm, int lane, int tx_swing, int tx_pre, int tx_post, int tx_gain_bias, int tx_vboost_unused);

/**
 * Get the TX tuning parameters for a QLM lane
 *
 * @param node     Node to configure
 * @param qlm      QLM to configure
 * @param lane     Lane to configure
 * @param tx_swing Transmit swing, also called cMain (coef 0)
 * @param tx_pre   Pre cursor emphasis (Coef -1)
 * @param tx_post  Post cursor emphasis (Coef +1)
 * @param tx_gain_bias
 *                 For CN8XXX, this is transmit gain. For CN9XXX, this is transmit bias
 * @param tx_vboost_unused
 *                 For CN8XXX, this is transmit voltage boost. For CN9XXX, this is unused
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_get_tune_lane_tx(bdk_node_t node, int qlm, int lane, int *tx_swing, int *tx_pre, int *tx_post, int *tx_gain_bias, int *tx_vboost_unused);

/**
 * Perform RX equalization on a QLM
 *
 * @param node   Node the QLM is on
 * @param qlm    QLM to perform RX equalization on
 * @param lane   Lane to use, or -1 for all lanes
 *
 * @return Zero on success, negative if any lane failed RX equalization
 */
extern int bdk_qlm_rx_equalization(bdk_node_t node, int qlm, int lane);

/**
 * Capture an eye diagram for the given QLM lane. The output data is written
 * to "eye".
 *
 * @param node      Node to use in numa setup
 * @param qlm       QLM to use
 * @param qlm_lane  Which lane
 * @param show_data Set to non-zero to have the eye capture dump the raw eye data as
 *                  it is captured
 * @param eye       Output eye data
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_eye_capture(bdk_node_t node, int qlm, int qlm_lane, int show_data, bdk_qlm_eye_t *eye);

/**
 * Display an eye diagram for the given QLM lane. The eye data can be in "eye", or
 * captured during the call if "eye" is NULL.
 *
 * @param node     Node to use in numa setup
 * @param qlm      QLM to use
 * @param qlm_lane Which lane
 * @param format   Display format. 0 = table, 1 = Color ASCII, 2 = Color + raw
 * @param eye      Eye data to display, or NULL if the data should be captured.
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_eye_display(bdk_node_t node, int qlm, int qlm_lane, int format, const bdk_qlm_eye_t *eye);

/**
 * Call the board specific method of determining the required QLM configuration
 * and automatically settign up the QLMs to match. For example, on the EBB8800
 * this function queries the MCU for the current setup.
 *
 * @param node   Node to configure
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_auto_config(bdk_node_t node);

/**
 * Get the current RX margining parameter
 *
 * @param node     Node to read margin value from
 * @param qlm      QLM to read from
 * @param qlm_lane Lane to read
 * @param margin_type
 *                 Type of margining parameter to read
 *
 * @return Current margining parameter value
 */
extern int64_t bdk_qlm_margin_rx_get(bdk_node_t node, int qlm, int qlm_lane, bdk_qlm_margin_t margin_type);

/**
 * Get the current RX margining parameter minimum value
 *
 * @param node     Node to read margin value from
 * @param qlm      QLM to read from
 * @param qlm_lane Lane to read
 * @param margin_type
 *                 Type of margining parameter to read
 *
 * @return Current margining parameter minimum value
 */
extern int64_t bdk_qlm_margin_rx_get_min(bdk_node_t node, int qlm, int qlm_lane, bdk_qlm_margin_t margin_type);

/**
 * Get the current RX margining parameter maximum value
 *
 * @param node     Node to read margin value from
 * @param qlm      QLM to read from
 * @param qlm_lane Lane to read
 * @param margin_type
 *                 Type of margining parameter to read
 *
 * @return Current margining parameter maximum value
 */
extern int64_t bdk_qlm_margin_rx_get_max(bdk_node_t node, int qlm, int qlm_lane, bdk_qlm_margin_t margin_type);

/**
 * Set the current RX margining parameter value
 *
 * @param node     Node to set margin value on
 * @param qlm      QLM to set
 * @param qlm_lane Lane to set
 * @param margin_type
 *                 Type of margining parameter to set
 * @param value    Value of margining parameter
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_margin_rx_set(bdk_node_t node, int qlm, int qlm_lane, bdk_qlm_margin_t margin_type, int value);

/**
 * Restore the supplied RX margining parameter value as if it was never set. This
 * disables any overrides in the SERDES need to perform margining
 *
 * @param node     Node to restore margin value on
 * @param qlm      QLM to restore
 * @param qlm_lane Lane to restore
 * @param margin_type
 *                 Type of margining parameter to restore
 * @param value    Value of margining parameter
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_margin_rx_restore(bdk_node_t node, int qlm, int qlm_lane, bdk_qlm_margin_t margin_type, int value);

/**
 * Display the current settings of a QLM lane
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to display
 * @param qlm_lane Lane to use
 * @param show_tx  Display TX parameters
 * @param show_rx  Display RX parameters
 */
extern void bdk_qlm_display_settings(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx);

/**
 * Get a supported mode for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM mode
 */
extern bdk_qlm_modes_t bdk_qlm_get_mode_desc_mode(bdk_node_t node, int qlm, int index);

/**
 * Get a supported flags for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM flags
 */
extern bdk_qlm_mode_flags_t bdk_qlm_get_mode_desc_flags(bdk_node_t node, int qlm, int index);

/**
 * Get a supported ref clock for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM ref clock
 */
extern bdk_qlm_clock_t bdk_qlm_get_mode_desc_ref_clk(bdk_node_t node, int qlm, int index);

/**
 * Get a supported speed for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM speed
 */
extern uint16_t bdk_qlm_get_mode_desc_speed(bdk_node_t node, int qlm, int index);

/**
 * Return the BGX/CGX interface number that corresponds to the supplied DLM/QLM.
 * This function returns the same result regardless of board configuration. If a
 * single BGX/CGX can be used by multiple DLM/QLM, all of those DLM/QLM will
 * return the same interface. The current active configuration is ignored.
 *
 * @param node     Node to lookup
 * @param qlm      DLM/QLM to lookup
 * @param is_split Set to true if the BGX/CGX is split across two DLMs
 * @param is_upper Set to true if the requested DLM is the upper half of a BGX/CGX
 *
 * @return BGX/CGX number, or -1 if the DLM/QLM can't be used with networking
 */
extern int bdk_qlm_to_network(bdk_node_t node, int qlm, bool *is_split, bool *is_upper);

/** @} */
