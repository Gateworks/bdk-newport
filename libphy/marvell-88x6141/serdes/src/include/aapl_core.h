/* AAPL CORE Revision: 2.6.2
 *
 * Copyright (c) 2014-2017 Avago Technologies. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/** Doxygen File Header
 ** @file
 ** @brief Core AAPL types and function definitions.
 **/

#ifndef AAPL_CORE_H_
#define AAPL_CORE_H_

#define aapl_is_jtag_communication_method MYD_aapl_is_jtag_communication_method
#define aapl_is_sbus_communication_method MYD_aapl_is_sbus_communication_method
#define aapl_is_aacs_communication_method MYD_aapl_is_aacs_communication_method
#define aapl_set_async_cancel_flag        MYD_aapl_set_async_cancel_flag
#define aapl_get_async_cancel_flag        MYD_aapl_get_async_cancel_flag
#define aapl_register_sbus_fn             MYD_aapl_register_sbus_fn
#define aapl_register_jtag_idcode_fn      MYD_aapl_register_jtag_idcode_fn
#define aapl_register_spico_int_fn        MYD_aapl_register_spico_int_fn
#define aapl_connect                      MYD_aapl_connect
#define aapl_close_connection2            MYD_aapl_close_connection2
#define aapl_close_connection             MYD_aapl_close_connection
#define aapl_connection_status            MYD_aapl_connection_status
#define aapl_reconnect                    MYD_aapl_reconnect
#define aapl_construct                    MYD_aapl_construct
#define aapl_destruct                     MYD_aapl_destruct
#define aapl_get_return_code              MYD_aapl_get_return_code
#define aapl_get_chips                    MYD_aapl_get_chips
#define aapl_get_max_sbus_addr            MYD_aapl_get_max_sbus_addr
#define aapl_get_jtag_idcode              MYD_aapl_get_jtag_idcode
#define aapl_get_chip_name                MYD_aapl_get_chip_name
#define aapl_get_chip_rev_str             MYD_aapl_get_chip_rev_str
#define aapl_bind_set                     MYD_aapl_bind_set
#define aapl_bind_get                     MYD_aapl_bind_get
#define aapl_get_process_id               MYD_aapl_get_process_id
#define aapl_set_spico_running_flag       MYD_aapl_set_spico_running_flag
#define aapl_get_process_id_str           MYD_aapl_get_process_id_str
#define avago_jtag                        MYD_avago_jtag
#define avago_jtag_options                MYD_avago_jtag_options
#define aapl_check_broadcast_address      MYD_aapl_check_broadcast_address
#define avago_get_tap_gen                 MYD_avago_get_tap_gen
#define avago_system_chip_setup           MYD_avago_system_chip_setup
#define aapl_set_ip_type                  MYD_aapl_set_ip_type
#define aapl_get_firmware_rev             MYD_aapl_get_firmware_rev
#define aapl_check_firmware_rev           MYD_aapl_check_firmware_rev
#define aapl_get_firmware_build           MYD_aapl_get_firmware_build
#define aapl_check_firmware_build         MYD_aapl_check_firmware_build
#define aapl_get_ip_type                  MYD_aapl_get_ip_type
#define aapl_get_lsb_rev                  MYD_aapl_get_lsb_rev
#define aapl_get_spico_running_flag       MYD_aapl_get_spico_running_flag
#define aapl_check_ip_type                MYD_aapl_check_ip_type
#define aapl_check_ip_type_exists         MYD_aapl_check_ip_type_exists
#define aapl_check_process                MYD_aapl_check_process
#define aapl_get_ip_rev                   MYD_aapl_get_ip_rev
#define aapl_get_sdrev                    MYD_aapl_get_sdrev
#define aapl_get_interrupt_rev            MYD_aapl_get_interrupt_rev
#define aapl_get_ip_info                  MYD_aapl_get_ip_info
#define aapl_default_port                 MYD_aapl_default_port
#define aapl_default_server               MYD_aapl_default_server
#define avago_addr_init                   MYD_avago_addr_init
#define avago_addr_to_struct              MYD_avago_addr_to_struct
#define avago_struct_to_addr              MYD_avago_struct_to_addr
#define avago_make_addr3                  MYD_avago_make_addr3
#define avago_make_addr4                  MYD_avago_make_addr4
#define avago_make_sbus_addr              MYD_avago_make_sbus_addr
#define avago_addr_init_broadcast         MYD_avago_addr_init_broadcast
#define avago_make_sbus_master_addr       MYD_avago_make_sbus_master_addr
#define avago_make_sbus_controller_addr   MYD_avago_make_sbus_controller_addr
#define avago_make_serdes_broadcast_addr  MYD_avago_make_serdes_broadcast_addr
#define avago_make_sbus_lane_addr         MYD_avago_make_sbus_lane_addr
#define aapl_is_octal_p1                  MYD_aapl_is_octal_p1
#define aapl_broadcast_next               MYD_aapl_broadcast_next
#define aapl_broadcast_first              MYD_aapl_broadcast_first
#define aapl_addr_selects_fw_device       MYD_aapl_addr_selects_fw_device
#define ms_sleep                          MYD_ms_sleep
#define aapl_malloc                       MYD_aapl_malloc
#define aapl_realloc                      MYD_aapl_realloc
#define aapl_free                         MYD_aapl_free
#define aapl_strncasecmp                  MYD_aapl_strncasecmp
#define aapl_strcasecmp                   MYD_aapl_strcasecmp
#define aapl_strdup                       MYD_aapl_strdup
#define aapl_str_rep                      MYD_aapl_str_rep
#define aapl_strtok_r                     MYD_aapl_strtok_r
#define aapl_hex_2_bin                    MYD_aapl_hex_2_bin
#define aapl_local_strftime               MYD_aapl_local_strftime
#define aapl_read_file                    MYD_aapl_read_file

/* Macros to suppress error accounting when errors are expected and handled: */
#define AAPL_SUPPRESS_ERRORS_PUSH(aapl) { int return_code = (aapl->suppress_errors++, aapl->return_code)
#define AAPL_SUPPRESS_ERRORS_POP(aapl)        aapl->return_code = return_code; aapl->suppress_errors--; }

/* AAPL debug defines (used to debug specific sections of code using aapl->debug) */
#define AAPL_DEBUG_LOCK 0x10
#define AAPL_DEBUG_MEMORY_NAMES 0x20
#define AAPL_DEBUG_SBUS_RW_TEST 0x40

/* AACS Server capabilities flags: */
#define AACS_SERVER_NO_CAPABILITIES 0x1
#define AACS_SERVER_SPICO_INT       0x2
#define AACS_SERVER_DIAG            0x4
#define AACS_SERVER_SBUS_RESET      0x8
#define AACS_SERVER_NO_CRC          0x10
#define AACS_SERVER_MDIO            0x20
#define AACS_SERVER_PMI             0x40

#define AAPL_3D_ARRAY_ADDR(addr) (addr).chip][(addr).ring][(addr).sbus

/** @brief Aapl_log_type_t is used for the AAPL struct log buffers */
typedef enum
{
    AVAGO_DEBUG0 = 0, AVAGO_DEBUG1, AVAGO_DEBUG2, AVAGO_DEBUG3,
    AVAGO_DEBUG4, AVAGO_DEBUG5, AVAGO_DEBUG6,
    AVAGO_DEBUG7, AVAGO_DEBUG8, AVAGO_DEBUG9,
    AVAGO_MEM_LOG, AVAGO_DATA_CHAR, AVAGO_DATA_CHAR_ADD,
    AVAGO_ERR, AVAGO_WARNING, AVAGO_INFO
} Aapl_log_type_t;


typedef enum
{
    AVAGO_UNKNOWN_PROCESS = 0,
    AVAGO_PROCESS_A,
    AVAGO_PROCESS_B,
    AVAGO_PROCESS_D,
    AVAGO_PROCESS_E,
    AVAGO_PROCESS_F,
    AVAGO_PROCESS_H
} Avago_process_id_t;

typedef enum
{
    AVAGO_UNKNOWN_IP                 = 0x00,
    AVAGO_SERDES                     = 0x01,
    AVAGO_SBUS_CONTROLLER            = 0x02,
    AVAGO_SPICO                      = 0x03,
    AVAGO_QPI                        = 0x04,
    AVAGO_BLACKHAWK                  = 0x05,
    AVAGO_PCS64B66B                  = 0x06,
    AVAGO_AUTO_NEGOTIATION           = 0x07,
    AVAGO_PCS64B66B_FEC              = 0x08,
    AVAGO_PCIE_PCS                   = 0x09,
    AVAGO_CORE_PLL                   = 0x0a,
    AVAGO_PMRO                       = 0x0b,
    AVAGO_DDR_ADDRESS                = 0x0c,
    AVAGO_DDR_DATA                   = 0x0d,
    AVAGO_DDR_TRAIN                  = 0x0e,
    AVAGO_DDR_CTC                    = 0x0f,
    AVAGO_DDR_STOP                   = 0x10,
    AVAGO_THERMAL_SENSOR             = 0x11,
    AVAGO_RMON                       = 0x12,
    AVAGO_LINK_EMULATOR              = 0x13,
    AVAGO_AVSP_CONTROL_LOGIC         = 0x14,
    AVAGO_M4                         = 0x15,
    AVAGO_P1                         = 0x16,
    AVAGO_MLD                        = 0x17,
    AVAGO_RSFEC_BRIDGE               = 0x18,
    AVAGO_CROSSPOINT                 = 0x19,
    AVAGO_MAX                        = 0x1a,
    AVAGO_SBUS2APB                   = 0x1b,
    AVAGO_EFUSE                      = 0x1d,
    AVAGO_RESCAL                     = 0x1e,

    AVAGO_SAPPH_GBX                  = 0x20,
    AVAGO_SAPPH_GBX_TOP              = 0x21,
    AVAGO_OPAL_RSFEC528              = 0x22,
    AVAGO_OPAL_RSFEC528_544          = 0x23,
    AVAGO_OPAL_HOST_ALIGNER          = 0x24,
    AVAGO_OPAL_MOD_ALIGNER           = 0x25,
    AVAGO_OPAL_CONTROL               = 0x26,
    AVAGO_OSC_SSC_PLL                = 0x27,
    AVAGO_GARNET_25GE_INTERFACE      = 0x28,
    AVAGO_SGMII                      = 0x29,
    AVAGO_APC                        = 0x2a,
    AVAGO_MLD_RX2                    = 0x2b,

    AVAGO_LINK_EMULATOR_2            = 0x81,
    AVAGO_SLE_PKT                    = 0x82,
    AVAGO_SLE                        = 0x83,
    AVAGO_PAD_CONTROL                = 0x88,


    AVAGO_RAM_PMRO,
    AVAGO_PANDORA_LSB,

    AVAGO_MAX_RING_ADDRESS           = 0xdf,
    AVAGO_SGMII_BROADCAST            = 0xea,
    AVAGO_OSC_SSC_BROADCAST          = 0xeb,
    AVAGO_MLD_BROADCAST              = 0xec,
    AVAGO_SERDES_P1_BROADCAST        = 0xed,
    AVAGO_SERDES_M4_BROADCAST        = 0xee,
    AVAGO_SERDES_D6_BROADCAST        = 0xff,
    AVAGO_THERMAL_SENSOR_BROADCAST   = 0xef,
    AVAGO_DDR_STOP_BROADCAST         = 0xf0,
    AVAGO_DDR_CTC_BROADCAST          = 0xf1,
    AVAGO_DDR_TRAIN_BROADCAST        = 0xf2,
    AVAGO_APC_BROADCAST              = 0xf2,
    AVAGO_DDR_DATA_BROADCAST         = 0xf3,
    AVAGO_MAX_BROADCAST              = 0xf3,
    AVAGO_DDR_ADDRESS_BROADCAST      = 0xf4,
    AVAGO_RESCAL_ADDRESS_BROADCAST   = 0xf4,
    AVAGO_PMRO_BROADCAST             = 0xf5,
    AVAGO_RESERVED_BROADCAST         = 0xf6,
    AVAGO_PCIE_PCS_BROADCAST         = 0xf7,
    AVAGO_PCS64B66B_BROADCAST        = 0xf8,
    AVAGO_AUTO_NEGOTIATION_BROADCAST = 0xf9,
    AVAGO_BLACKHAWK_BROADCAST        = 0xfb,
    AVAGO_QPI_BROADCAST              = 0xfc,
    AVAGO_MLD_RX2_BROADCAST          = 0xfc,
    AVAGO_SPICO_BROADCAST            = 0xfd,
    AVAGO_SERDES_BROADCAST           = 0xff
} Avago_ip_type_t;

/* When auto-setting Avago_ip_type_t, what is the max value to be read from the SBus address 0xff.
 * Additional Avago_ip_type_t values above what is in the SBus master spec
 *   (ie, special conditions that obtain the ip_type elsewhere) may still be used,
 * but the value listed here is the max that will be read from the SBus.
 */
#define AVAGO_IP_TYPE_MAX 0x2b

#define AVAGO_IP_TYPE_ALT_RANGE_LO 0x81
#define AVAGO_IP_TYPE_ALT_RANGE_HI 0x8a


/* Required to be declared here since it gets used in Aapl_t below */
typedef enum
{
    AVAGO_MDIO_ADDR,
    AVAGO_MDIO_WRITE,
    AVAGO_MDIO_READ,
    AVAGO_MDIO_WAIT
} Avago_mdio_cmd_t;


/** @defgroup Address IP Addressing Functions
 ** @{
 **/

/** @brief Internal hardware address structure.
 ** Not generally end-user accessible.
 ** Each value can be AVAGO_ADDR_BROADCAST to indicate broadcast to all at that level.
 ** Else the valid values are hardware and call dependent.
 **/
typedef struct Avago_addr_t
{
    unsigned char chip;   /**< Device number. */
    unsigned char ring;   /**< Ring on device. */
    unsigned char sbus;   /**< SBus address on ring. */
    unsigned char lane;   /**< Lane at SBus address. */
    uint results;         /**< Place to store return value for list read and interrupt operations. */
    bigint bigint_results;/**< Place to store return value for list read and interrupt operations. */
    uint group_addr;      /**< SBus broadcast group address.  0 if none. */

    struct Avago_addr_t *next; /**< Address of next Avago_addr_t element in linked list. */
} Avago_addr_t;

/** @brief AAPL addressing constants. */
typedef enum
{
    AVAGO_ADDR_BROADCAST      = 0xff,
    AVAGO_ADDR_IGNORE_LANE    = 0xf0,
    AVAGO_ADDR_QUAD_LOW       = 0xf1,
    AVAGO_ADDR_QUAD_HIGH      = 0xf2,
    AVAGO_ADDR_QUAD_ALL       = 0xf3
} Aapl_broadcast_control_t;

#define AVAGO_BROADCAST                (AVAGO_ADDR_BROADCAST)
#define AVAGO_SBUS_MASTER_ADDRESS      (0xfd)
#define AVAGO_SBUS_CONTROLLER_ADDRESS  (0xfe)
#define AVAGO_SERDES_BROADCAST_ADDRESS (0xff)
#define AVAGO_MAKE_SERDES_BROADCAST_ADDRESS(addr) (avago_make_serdes_broacast_addr(addr))

/** @} */



/** @brief AAPL struct used by virtually every function in this API.
 ** @warning Generally the user should not read or modify any elements of this struct.
 ** Use functions provided to get and set information in this structure.
 **/
typedef struct _Aapl_t
{

    uint debug;                               /**< global debug level */
    uint verbose;                             /**< global verbosity level */
    uint suppress_errors;                     /**< Turn aapl_log_add ERR and WARNINGS into DEBUG1 messages */
    uint upgrade_warnings;                    /**< If set, all WARNINGS are upgraded to ERRORS */
    uint diag_on_failure;                     /**< Run avago_diag when SPICO interrupts fail. Each time avago_diag is called this variable is decremented. */
    BOOL ansi_colors;                         /**< Defaults to the value in aapl.h. When 1, colorized output will be used when isatty() is true. When set to 2 colorized output will always be used. */

    int enable_debug_logging;                 /**< When enabled, data sent to DEBUGn will also be added to the AAPL log */
    int enable_stream_logging;                /**< When enabled, INFO and DEBUGn messages are written to AAPL_STREAM (if defined) */
    int enable_stream_err_logging;            /**< When enabled, warnings and errors are written to AAPL_STREAM_ERR (if defined) */
    char *logging_file_path;                  /**< Redirect all INFO and DEBUGn messages to user specified file */
                                              /**< Setting file path to this variable will enable redirecting data to the file. */
                                              /**< This is intended for short term debugging. */

    int log_time_stamps;                      /**< When enabled, time stamps are added to AAPL logs and DEBUGn output */

    int serdes_int_timeout;                   /**< 28nm SerDes SPICO interrupt maximum number of tries */
    int sbus_mdio_timeout;                    /**< sbus-over-mdio SBUS_RESULT polling maximum number of tries */
    uint tck_delay;                           /**< Allows user to slow down bit-banged GPIO JTAG operations */

    Aapl_comm_method_t communication_method;  /**< Method for communicating with Avago devices. */

    uint chips;                               /**< number of die this struct points to */
    uint sbus_rings;                          /**< number of SBus rings this struct points to */

    int max_cmds_buffered;                    /**< Maximum bumber of commands to queue before sending them via TCP over AACS. */
                                              /**< Setting this to 0 disables command buffering */
    int prior_connection;                     /**< Indicates if this AAPL struct has ever connected to an AACS server. */
    int disable_reconnect;                    /**< Don't allow AAPL to reconnect to TCP clients */

    int cmds_buffered;                        /**< number of commands in buf_cmd (which are bufferred AACS commands) */

    uint capabilities;                        /**< Bitmask of the remote AACS Server's capabilities */

    BOOL aacs;                                /**< Is AACS being used for communication? */
    uint tap_gen;                             /**< Avago TAP generation being communicated with */

    uint sbus_commands;                       /**< SBus commands executed */
    uint commands;                            /**< AACS Server commands received */

    uint  (*sbus_fn)             (struct _Aapl_t *aapl, uint addr, unsigned char reg_addr, unsigned char command, uint *sbus_data);
    uint  (*sbus_fn_2)           (struct _Aapl_t *aapl, uint addr, unsigned char reg_addr, unsigned char command, uint *sbus_data, uint flags);
    int   (*comm_open_fn)        (struct _Aapl_t *aapl);
    int   (*comm_close_fn)       (struct _Aapl_t *aapl);
    uint  (*jtag_idcode_fn)      (struct _Aapl_t *aapl, uint device);

    int   (*i2c_write_fn)        (struct _Aapl_t *aapl, unsigned int dev_addr, unsigned int length, unsigned char * buffer);
    int   (*i2c_read_fn)         (struct _Aapl_t *aapl, unsigned int dev_addr, unsigned int length, unsigned char * buffer);

    uint  (*mdio_fn)             (struct _Aapl_t *aapl, Avago_mdio_cmd_t mdio_cmd, uint port_addr, uint dev_addr, uint reg_addr, uint data);

    char *(*jtag_fn)             (struct _Aapl_t *aapl, int opcode, int bits, const char *tdi, BOOL get_tdo);
    BOOL  (*bit_banged_jtag_fn)  (struct _Aapl_t *aapl, BOOL tms, BOOL tdi, BOOL trst_l, BOOL get_tdo);
    uint  (*serdes_int_fn)       (struct _Aapl_t *aapl, uint addr, int int_code, int int_data);
    void  (* log_fn)             (struct _Aapl_t *aapl, Aapl_log_type_t log_sel, const char * buf, size_t new_item_length);
    int   (* log_open_fn)        (struct _Aapl_t *aapl);
    int   (* log_close_fn)       (struct _Aapl_t *aapl);

    int   (*parallel_serdes_int_fn) (struct _Aapl_t *aapl, Avago_addr_t *addr_list, int int_num, int int_data);

    void *client_data;
    volatile int async_cancel;

# ifndef SWIG

#if AAPL_ALLOW_OFFLINE_SBUS
    int *offline_sbus_reg;                    /**< Pointer to offline SBus storage */
#endif
#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
    volatile unsigned *rpi_gpio_access;       /**< memory mapped I/O access on rpi. Used by GPIO JTAG access functions */
    int prev_opcode;
    unsigned char recv_data_valid[AAPL_MAX_CHIPS][AAPL_MAX_RINGS]; /**< Last value of recv_data_valid (used in SBus over JTAG modes) */
    char sbus_reg[128];                       /**< SBus IJTAG register. Gets ORed in whenever an SBus an command is sent (in SBus over JTAG modes) (used globally for all rings and chips) */
    uint curr_chip;                           /**< Current chip that we're communicating with (used for JTAG and BB JTAG functions) */
                                              /**< Set using aapl_set_chip(). */

    char *buf_cmd, *buf_cmd_end;              /**< Pointer to start/end of AACS command buffer */
#endif

    const char *chip_name[AAPL_MAX_CHIPS];  /**< Array of chip name pointers */
    const char *chip_rev[AAPL_MAX_CHIPS];   /**< Array of chip revision pointers */

    char *aacs_server_buffer;               /**< Pointer to aacs_server's internal buffer */
    char *aacs_server;                      /**< Server name (or IP address) used to open the AACS socket */
    int socket;                             /**< Socket used for AACS TCP communications. */
                                            /**< It must be >= 0 after successful open, and < 0 on open failure and after close. */
                                            /**< If open/close don't touch this, AAPL will manage its value. */
    int tcp_port;                           /**< TCP port used to open the AACS socket */

    uint jtag_idcode[AAPL_MAX_CHIPS];       /**< JTAG IDCODE for each chip */
    Avago_process_id_t process_id[AAPL_MAX_CHIPS]; /**< Process Identifier for each chip */

    uint last_mdio_addr[AAPL_MAX_CHIPS];    /**< Last MDIO address used */
    uint mdio_base_port_addr;               /**< MDIO base port address. */
    int  i2c_base_addr;                     /**< I2C base address. */
    unsigned short       ip_rev[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< IP revision for each SBus Rx */
    unsigned short     firm_rev[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< Revision of firmware load, populated if ip_type is SERDES or SPICO */
    unsigned short   firm_build[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< Build of firmware load, populated if ip_type is SERDES or SPICO */
    char          spico_running[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< Indicator of SPICO processor is running. */
    unsigned char       ip_type[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< Avago_ip_type_t identifier for each SBus Rx */
    signed   char       lsb_rev[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< Revision of LSB block, populated if ip_type is SERDES */
    unsigned char max_sbus_addr[AAPL_MAX_CHIPS][AAPL_MAX_RINGS];      /**< max SBus address for each die and SBus ring */
#  if AAPL_ENABLE_FILE_IO
    char         *firmware_file[AAPL_MAX_CHIPS][AAPL_MAX_RINGS][256]; /**< Keeps track of firmware file loaded */
#  endif

    int return_code;        /**< set by most functions to indicate success/fail status */
    int errors;             /**< Incremented each time an error occurs */
    int warnings;           /**< Incremented each time an error occurs */
    int data;               /**< used for functions that return int data */

    char *data_char;        /**< used for functions that return strings */
    char *data_char_end;    /**< to truncate data_char, set data_char_end = data_char; */
    int   data_char_size;   /**< data_char memory management */

    char *log;              /**< memory log, logs commands, info,errors, warnings, and debug statements */
    char *log_end;          /**< to truncate log, set log_end = log; */
    int   log_size;         /**< memory log managment */
    char *last_log;         /**< pointer to start of most recent item stored in the log */
    char *last_err;         /**< pointer to start of most recent warning or error */


#if AAPL_ALLOW_THREADED_SBUS || AAPL_ALLOW_THREAD_SUPPORT
    BOOL destroy_thread;
#endif
#if AAPL_ALLOW_THREAD_SUPPORT && AAPL_ENABLE_HS2
    pthread_t telnet_thread;
#endif
#if AAPL_ALLOW_THREADED_SBUS
    pthread_t sbus_thread;
    uint sbus_sa;
    unsigned char sbus_da;
    unsigned char sbus_cmd;
    volatile uint sbus_data;
    BOOL sbus_recv_data_back;
    volatile    BOOL sbus_execute;
#endif
#if AAPL_ALLOW_THREAD_SUPPORT
    #define AAPL_SPICO_INT_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock.\n"); \
        pthread_mutex_lock(&aapl->spico_int_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete.\n");}
    #define AAPL_SPICO_INT_UNLOCK \
        {pthread_mutex_unlock(&aapl->spico_int_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock.\n");}

    #define AAPL_CLOSE_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock.\n"); \
        pthread_mutex_lock(&aapl->close_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete.\n");}
    #define AAPL_CLOSE_UNLOCK \
        {pthread_mutex_unlock(&aapl->close_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock.\n");}

    #define AAPL_AACS_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock.\n"); \
        pthread_mutex_lock(&aapl->aacs_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete.\n");}
    #define AAPL_AACS_UNLOCK \
        {pthread_mutex_unlock(&aapl->aacs_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock.\n");}

    #define AAPL_SERDES_MEM_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock (%d).\n", mem_lock_count); \
        if (!mem_lock_count) pthread_mutex_lock(&aapl->serdes_mem_mutex); \
        mem_lock_count += 1; \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete (%d).\n", mem_lock_count);}
    #define AAPL_SERDES_MEM_UNLOCK \
        {mem_lock_count --; if (!mem_lock_count) pthread_mutex_unlock(&aapl->serdes_mem_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock (%d).\n", mem_lock_count);}

    #define AAPL_IP_INFO_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock (%d).\n", ip_lock_count); \
        if (!ip_lock_count) pthread_mutex_lock(&aapl->ip_info_mutex); \
        ip_lock_count += 1; \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete (%d).\n", ip_lock_count);}
    #define AAPL_IP_INFO_UNLOCK \
        {ip_lock_count --; if (!ip_lock_count) pthread_mutex_unlock(&aapl->ip_info_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock (%d).\n", ip_lock_count);}

    #define AAPL_SENSOR_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock.\n"); \
        pthread_mutex_lock(&aapl->sensor_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete.\n");}
    #define AAPL_SENSOR_UNLOCK \
        {pthread_mutex_unlock(&aapl->sensor_mutex); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock.\n");}

    #define AAPL_PRINTF_LOCK \
        {pthread_mutex_lock(&aapl->log_printf_mutex);}
    #define AAPL_PRINTF_UNLOCK \
        {pthread_mutex_unlock(&aapl->log_printf_mutex);}

    #define AAPL_SBUS_LOCK \
        {if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Attempting to lock.\n"); \
        pthread_mutex_lock(&aapl->sbus_lock); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Lock complete.\n");}
    #define AAPL_SBUS_UNLOCK \
        {pthread_mutex_unlock(&aapl->sbus_lock); \
        if (aapl->debug & AAPL_DEBUG_LOCK) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Unlock.\n");}

    pthread_mutex_t sbus_execute_mutex;
    pthread_mutex_t aacs_mutex;
    pthread_mutex_t close_mutex;
    pthread_mutex_t spico_int_mutex;
    pthread_mutex_t serdes_mem_mutex;
    pthread_mutex_t ip_info_mutex;
    pthread_mutex_t sensor_mutex;
    pthread_mutex_t log_printf_mutex;
    pthread_mutex_t sbus_lock;
#else
    #define AAPL_SPICO_INT_LOCK
    #define AAPL_SPICO_INT_UNLOCK
    #define AAPL_AACS_LOCK
    #define AAPL_AACS_UNLOCK
    #define AAPL_CLOSE_LOCK
    #define AAPL_CLOSE_UNLOCK
    #define AAPL_SERDES_MEM_LOCK
    #define AAPL_SERDES_MEM_UNLOCK
    #define AAPL_SENSOR_LOCK
    #define AAPL_SENSOR_UNLOCK
    #define AAPL_IP_INFO_LOCK
    #define AAPL_IP_INFO_UNLOCK
    #define AAPL_PRINTF_LOCK
    #define AAPL_PRINTF_UNLOCK
    #define AAPL_SBUS_LOCK
    #define AAPL_SBUS_UNLOCK
#endif

# endif
} Aapl_t;

/* Create a pointer to a new AAPL struct */
EXT Aapl_t *aapl_construct(void);
EXT void    aapl_destruct(Aapl_t *aapl);

/* Address list handling functions: */
EXT void          avago_addr_init(Avago_addr_t *addr_struct);
EXT Avago_addr_t *avago_addr_new(Aapl_t *aapl);
EXT Avago_addr_t *avago_addr_new_from_struct(Aapl_t *aapl, Avago_addr_t *initial_value);
EXT void          avago_addr_delete(Aapl_t *aapl, Avago_addr_t *addr_list);
EXT void          avago_group_expand_broadcast(Aapl_t *aapl, Avago_addr_t *addr_list);
EXT void          avago_group_setup(Aapl_t *aapl, Avago_addr_t *addr_list);
EXT void          avago_group_clear(Aapl_t *aapl, Avago_addr_t *addr_list);
EXT Avago_addr_t *avago_group_get_next(Avago_addr_t *addr_list);
EXT uint          avago_group_get_addr(Avago_addr_t *addr_list);
EXT void          avago_group_debug(Aapl_t *aapl, Aapl_log_type_t debug, const char *func, int line, Avago_addr_t *addr_list);

EXT BOOL avago_addr_to_struct(uint addr, Avago_addr_t *addr_struct);
EXT uint avago_struct_to_addr(Avago_addr_t *addr);

EXT uint avago_addr_init_broadcast(Avago_addr_t *addr_struct);
EXT uint avago_make_addr3(int chip, int ring, int sbus);
EXT uint avago_make_addr4(int chip, int ring, int sbus, int lane);
EXT uint avago_make_sbus_addr(uint addr, int sbus);
EXT uint avago_make_sbus_lane_addr(uint addr, int lane);
EXT uint avago_make_sbus_master_addr(uint addr);
EXT uint avago_make_sbus_controller_addr(uint addr);
EXT uint avago_make_serdes_broadcast_addr(uint addr);

EXT int aapl_get_async_cancel_flag(Aapl_t *aapl);
EXT int aapl_set_async_cancel_flag(Aapl_t *aapl, int new_value);

/* Returns the return code and then sets it to zero. Values less than 0 indicate failure, while 0 indicates no error. */
EXT int         aapl_get_return_code(Aapl_t *aapl);

/* The following functions return information from the Aapl_t struct. addr is used to return specific information for that element. */
EXT uint        aapl_get_chips(Aapl_t *aapl);
EXT uint        aapl_get_max_sbus_addr(Aapl_t *aapl, uint addr);
EXT uint        aapl_get_jtag_idcode(Aapl_t *aapl, uint addr);
EXT const char *aapl_get_chip_name(Aapl_t *aapl, uint addr);
EXT const char *aapl_get_chip_rev_str(Aapl_t *aapl, uint addr);
EXT const char *aapl_get_process_id_str(Aapl_t *aapl, uint addr);
EXT uint        aapl_get_ip_rev(Aapl_t *aapl, uint addr);
EXT uint        aapl_get_lsb_rev(Aapl_t *aapl, uint addr);
EXT int         aapl_get_firmware_rev(Aapl_t *aapl, uint addr);
EXT int         aapl_get_firmware_build(Aapl_t *aapl, uint addr);
/* Functions to access client defined aapl data */
EXT void        aapl_bind_set(Aapl_t *aapl, void *client_data );
EXT void       *aapl_bind_get(Aapl_t *aapl);

EXT Avago_process_id_t     aapl_get_process_id(Aapl_t *aapl, uint addr);
EXT Avago_ip_type_t        aapl_get_ip_type(Aapl_t *aapl, uint addr);
EXT void                   aapl_set_ip_type(Aapl_t *aapl, uint addr);
EXT BOOL aapl_get_spico_running_flag(Aapl_t *aapl, uint addr);
EXT BOOL aapl_set_spico_running_flag(Aapl_t *aapl, uint addr, BOOL running);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
/* Functions to manage chip selection: */
EXT void aapl_set_chip(Aapl_t *aapl, uint chipnum);
EXT void aapl_set_chip_by_addr(Aapl_t *aapl, uint addr);
#endif

/* Query ASIC(s) to fully fill out the AAPL struct. Should be done before using. */
EXT void    aapl_get_ip_info(Aapl_t *aapl, int chip_reset);

/* Send / receive JTAG information. */
typedef enum
{
    AVAGO_SHIFT_DR,
    AVAGO_RTI
} Aapl_jtag_state_t;
EXT char *avago_jtag(        Aapl_t *aapl, int opcode, int length, const char *data);
EXT char *avago_jtag_options(Aapl_t *aapl, int opcode, int length, const char *data, BOOL get_tdo);
EXT char *avago_jtag_rd(     Aapl_t *aapl, int opcode, int length);
EXT char *avago_jtag_rd_len( Aapl_t *aapl, int opcode, int *length);
EXT void  avago_jtag_set_bit(Aapl_t *aapl, int opcode, uint length, uint set_bit, uint value);
EXT void  avago_jtag_scan(   Aapl_t *aapl, int length, int tms, const char * tdi, char * tdo);
EXT void  avago_jtag_scan_options(Aapl_t *aapl, int length, int tms, const char * tdi, char * tdo, Aapl_jtag_state_t state);
EXT void avago_jtag_reset(   Aapl_t *aapl, int chip);

/* checks addr against ip_type or process. Args is the number of arguments passed in for ip_type or process
 * for example: aapl_check_ip_type(aapl, addr, __func__,__LINE__, 2, AVAGO_SERDES, AVAGO_QPI);
 */
EXT BOOL aapl_check_ip_type(       Aapl_t *aapl, uint addr, const char *caller, int line, int error, int args, ...);
EXT BOOL aapl_check_ip_type_exists(Aapl_t *aapl, uint addr, const char *caller, int line, int error, int args, ...);
EXT BOOL aapl_check_process(       Aapl_t *aapl, uint addr, const char *caller, int line, int error, int args, ...);
EXT BOOL aapl_check_firmware_rev(  Aapl_t *aapl, uint addr, const char *caller, int line, int error, int args, ...);
EXT BOOL aapl_check_firmware_build(Aapl_t *aapl, uint addr, const char *caller, int line, int error, int args, ...);
EXT BOOL aapl_check_broadcast_address( Aapl_t *aapl, uint addr, const char *caller, int line, int error_on_match);

EXT void avago_system_chip_setup(Aapl_t *aapl, int reset, int chip);
EXT uint avago_get_tap_gen(Aapl_t *aapl);


/* Setup AAPL's connection to a device.
 * If using an AVAGO_AACS_* communication method, this will setup a TCP connection.
 */
EXT void aapl_connect(Aapl_t *aapl, const char *aacs_server, int tcp_port);
EXT void aapl_close_connection(Aapl_t *aapl);
EXT int  aapl_connection_status(Aapl_t *aapl);

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
EXT BOOL aapl_check_sdrev(Aapl_t *aapl, uint addr, const char *caller, int line, int error, int args, ...);
EXT void aapl_close_connection2(Aapl_t *aapl);
EXT int  aapl_reconnect(Aapl_t *aapl, const char * command);
EXT int  aapl_send(Aapl_t *aapl, char * data, int len, int tcp_port);
#endif

EXT BOOL aapl_is_jtag_communication_method(Aapl_t *aapl);
EXT BOOL aapl_is_i2c_communication_method(Aapl_t *aapl);
EXT BOOL aapl_is_mdio_communication_method(Aapl_t *aapl);
EXT BOOL aapl_is_sbus_communication_method(Aapl_t *aapl);
EXT BOOL aapl_is_aacs_communication_method(Aapl_t *aapl);


#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
#define AAPL_BROADCAST_IGNORE_LANE     (0x01)
#define AAPL_BROADCAST_NO_ITER_LANE    (0x02)
#define AAPL_BROADCAST_LANE            (0x04)
#define AAPL_BROADCAST_NO_ITER_SBUS    (0x08)
EXT BOOL aapl_broadcast_first(Aapl_t *aapl, Avago_addr_t *addr, Avago_addr_t *start, Avago_addr_t *stop, Avago_addr_t *first, uint flags);
EXT BOOL aapl_broadcast_next(Aapl_t *aapl, Avago_addr_t *addr, Avago_addr_t *start, Avago_addr_t *stop, uint flags);
EXT BOOL aapl_addr_selects_fw_device(Aapl_t *aapl, Avago_addr_t *addr_struct, uint addr, BOOL *ignore);
EXT BOOL aapl_is_octal_p1(Aapl_t *aapl, uint addr);

#  if AAPL_ENABLE_FILE_IO
    EXT char *aapl_read_file(Aapl_t *aapl, const char *filename);
#  endif

typedef enum
{
    AAPL_SDREV_UNKNOWN = 0,
    AAPL_SDREV_D6      = 1,
    AAPL_SDREV_16      = 2,
    AAPL_SDREV_P1      = 3,
    AAPL_SDREV_HVD6    = 4,
    AAPL_SDREV_OM4     = 5,
    AAPL_SDREV_CM4     = 6,
    AAPL_SDREV_CM4_16  = 7,
    AAPL_SDREV_PON     = 9,
    AAPL_SDREV_D6_07   =10,
    AAPL_SDREV_XXX
} Aapl_sdrev_t;
EXT int aapl_get_sdrev(Aapl_t *aapl, uint addr);
EXT int aapl_get_interrupt_rev(Aapl_t *aapl, uint addr, int int_num);

#endif

/*//////////////////////////////////////////////////////////////////////
 * AAPL memory functions that log on allocation failure:
 */

//#ifndef aapl_malloc
EXT void *aapl_malloc(Aapl_t *aapl, size_t bytes, const char *description);
EXT void *aapl_realloc(Aapl_t *aapl, void *ptr, size_t bytes, const char *description);
EXT void  aapl_free(Aapl_t *aapl, void *ptr, const char *description);
//#endif


/*//////////////////////////////////////////////////////////////////////
 * AACS Functions and Globals
 */

/* Size of buffer for SBus commands. Largest command could be:
 * sbus 00 00 00 0x00000000
 * NOTE: Currently no comments are sent, so this is the biggest possible command
 */
#define AAPL_SBUS_CMD_LOG_BUF_SIZE (32)


/* Always available, but may be empty: */
EXT const char *avago_aacs_send_command(            Aapl_t *aapl, const char *cmd);
EXT int         avago_aacs_send_command_int(        Aapl_t *aapl, const char *cmd);
EXT const char *avago_aacs_send_command_options(    Aapl_t *aapl, const char *cmd,     int recv_data_back, int strtol);
EXT int         avago_aacs_send_command_options_int(Aapl_t *aapl, const char *command, int recv_data_back);
EXT void        avago_aacs_flush(Aapl_t *aapl);

#if AAPL_ALLOW_AACS

# ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS
    EXT int avago_aacs_open_fn(Aapl_t *aapl);
    EXT int avago_aacs_close_fn(Aapl_t *aapl);
    EXT uint aapl_aacs_sbus_fn(Aapl_t *aapl, uint addr, unsigned char reg_addr, unsigned char command, uint *sbus_data, uint recv_data_back);

    EXT const char *aapl_tcp_strerr(void);
    EXT int aapl_recv(Aapl_t *aapl);
    EXT void aapl_check_capabilities(Aapl_t *aapl);
# endif

#endif

# ifndef SWIG
    EXT const char *aapl_default_server;
    EXT const uint  aapl_default_port;
# endif


EXT void aapl_register_sbus_fn(Aapl_t *aapl,
    uint (* user_sbus_fn)(Aapl_t *, uint addr, unsigned char reg_addr, unsigned char command, uint *sbus_data),
    int (* comm_open_fn)(Aapl_t *),
    int (* comm_close_fn)(Aapl_t *)
);

EXT void aapl_register_mdio_fn(Aapl_t *aapl,
    uint (* mdio_fn)(Aapl_t *, Avago_mdio_cmd_t mdio_cmd, uint port_addr, uint dev_addr, uint reg_addr, uint data),
    int (* comm_open_fn)(Aapl_t *),
    int (* comm_close_fn)(Aapl_t *)
);

EXT void aapl_register_i2c_fn(Aapl_t *aapl,
    int (* i2c_rd_fn)(Aapl_t *, uint dev_addr, uint length, unsigned char * buffer),
    int (* i2c_wr_fn)(Aapl_t *, uint dev_addr, uint length, unsigned char * buffer),
    int (* comm_open_fn)(Aapl_t *),
    int (* comm_close_fn)(Aapl_t *)
);

EXT void aapl_register_jtag_fn(Aapl_t *aapl,
    char *(* jtag_fn)(Aapl_t *, int opcode, int bits, const char *tdi, BOOL get_tdo),
    int (* comm_open_fn)(Aapl_t *),
    int (* comm_close_fn)(Aapl_t *)
);

EXT void aapl_register_bit_banged_jtag_fn(Aapl_t *aapl,
    int (* jtag_fn)(Aapl_t *, BOOL tms, BOOL tdi, BOOL trst_l, BOOL get_tdo),
    int (* comm_open_fn)(Aapl_t *),
    int (* comm_close_fn)(Aapl_t *)
);

EXT void aapl_register_spico_int_fn(Aapl_t *aapl,
    uint  (*serdes_int_fn)     (Aapl_t *aapl, uint addr, int int_code, int int_data)
);

EXT void aapl_register_parallel_serdes_int_fn(Aapl_t *aapl,
     int  (*parallel_serdes_int_fn) (Aapl_t *aapl, Avago_addr_t *addr_list, int int_code, int int_data)
);

EXT void aapl_register_jtag_idcode_fn(Aapl_t *aapl,
    uint (* jtag_idcode_fn)(Aapl_t *, uint device)
);

EXT void aapl_register_user_supplied_functions(Aapl_t *aapl);

EXT void aapl_sigint_check(Aapl_t *aapl);

#endif
