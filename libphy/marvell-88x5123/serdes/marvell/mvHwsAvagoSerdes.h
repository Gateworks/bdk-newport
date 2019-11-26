/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************
This file is a placeholder of AVAGO defined file.
********************************************************************/

#ifndef MV_HWS_AVAGO_SERDES_H
#define MV_HWS_AVAGO_SERDES_H


/* Global variables */
#define aapl_default_server                         mvMcd_aapl_default_server
#define aapl_default_port                           mvMcd_aapl_default_port
#define cmd                                         mvMcd_cmd
#define q03                                         mvMcd_q03
#define q04                                         mvMcd_q04
#define q05                                         mvMcd_q05
#define q06                                         mvMcd_q06
#define q10                                         mvMcd_q10
#define q12                                         mvMcd_q12
#define q15                                         mvMcd_q15
#define q17                                         mvMcd_q17

/* function definitions */
/* AAPL/Serdes Initialization */
#define aapl_construct                              mvMcd_aapl_construct
#define aapl_destruct                               mvMcd_aapl_destruct
#define aapl_init                                   mvMcd_aapl_init
#define avago_addr_init                             mvMcd_avago_addr_init
#define avago_addr_init_broadcast                   mvMcd_avago_addr_init_broadcast
#define avago_serdes_init                           mvMcd_avago_serdes_init
#define avago_serdes_init_config                    mvMcd_avago_serdes_init_config
#define avago_serdes_init_config_construct          mvMcd_avago_serdes_init_config_construct
#define avago_serdes_init_config_destruct           mvMcd_avago_serdes_init_config_destruct
#define avago_serdes_init_quick                     mvMcd_avago_serdes_init_quick

/* AAPL information */
#define aapl_get_ip_info                            mvMcd_aapl_get_ip_info
#define aapl_get_return_code                        mvMcd_aapl_get_return_code
#define aapl_get_firmware_rev                       mvMcd_aapl_get_firmware_rev
#define aapl_get_firmware_build                     mvMcd_aapl_get_firmware_build
#define aapl_get_chips                              mvMcd_aapl_get_chips
#define aapl_get_max_sbus_addr                      mvMcd_aapl_get_max_sbus_addr
#define aapl_get_jtag_idcode                        mvMcd_aapl_get_jtag_idcode
#define aapl_get_chip_name                          mvMcd_aapl_get_chip_name
#define aapl_get_chip_rev_str                       mvMcd_aapl_get_chip_rev_str
#define aapl_get_lsb_rev                            mvMcd_aapl_get_lsb_rev
#define aapl_get_ip_rev                             mvMcd_aapl_get_ip_rev
#define aapl_set_ip_type                            mvMcd_aapl_set_ip_type
#define aapl_get_ip_type                            mvMcd_aapl_get_ip_type
#define aapl_bind_set                               mvMcd_aapl_bind_set
#define aapl_bind_get                               mvMcd_aapl_bind_get
#define aapl_get_process_id                         mvMcd_aapl_get_process_id
#define aapl_get_process_id_str                     mvMcd_aapl_get_process_id_str
#define aapl_get_spico_running_flag                 mvMcd_aapl_get_spico_running_flag
#define aapl_set_spico_running_flag                 mvMcd_aapl_set_spico_running_flag
#define aapl_check_broadcast_address_full           mvMcd_aapl_check_broadcast_address_full
#define aapl_check_firmware_rev_full                mvMcd_aapl_check_firmware_rev_full
#define aapl_check_firmware_build                   mvMcd_aapl_check_firmware_build
#define aapl_check_ip_type_full                     mvMcd_aapl_check_ip_type_full
#define aapl_check_ip_type_exists                   mvMcd_aapl_check_ip_type_exists
#define aapl_check_process_full                     mvMcd_aapl_check_process_full
#define aapl_recv                                   mvMcd_aapl_recv
#define aapl_check_capabilities                     mvMcd_aapl_check_capabilities

/* Aacs */
#define avago_aacs_process_cmd                      mvMcd_avago_aacs_process_cmd
#define avago_aacs_server                           mvMcd_avago_aacs_server
#define avago_aacs_open                             mvMcd_avago_aacs_open
#define avago_aacs_close                            mvMcd_avago_aacs_close
#define avago_aacs_flush                            mvMcd_avago_aacs_flush
#define avago_aacs_send_command                     mvMcd_avago_aacs_send_command
#define avago_aacs_send_command_options             mvMcd_avago_aacs_send_command_options

/* Serdes information */
#define avago_get_tap_gen                           mvMcd_avago_get_tap_gen

/* Chip information */
#define avago_chip_id                               mvMcd_avago_chip_id

/* Reset the chip */
#define avago_system_chip_setup                     mvMcd_avago_system_chip_setup

/* async_cancel flag */
#define aapl_set_async_cancel_flag                  mvMcd_aapl_set_async_cancel_flag
#define aapl_get_async_cancel_flag                  mvMcd_aapl_get_async_cancel_flag

/* Sbus */
#define avago_sbus                                  mvMcd_avago_sbus
#define avago_sbus_open                             mvMcd_avago_sbus_open
#define avago_sbus_close                            mvMcd_avago_sbus_close
#define avago_sbus_rd_array                         mvMcd_avago_sbus_rd_array
#define avago_sbus_rd                               mvMcd_avago_sbus_rd
#define avago_sbus_wr                               mvMcd_avago_sbus_wr
#define avago_sbus_wr_flush                         mvMcd_avago_sbus_wr_flush
#define avago_sbus_rmw                              mvMcd_avago_sbus_rmw
#define avago_sbus_reset                            mvMcd_avago_sbus_reset
#define avago_sbm_get_temperature                   mvMcd_avago_sbm_get_temperature
#define user_supplied_sbus_function                 mvMcd_user_supplied_sbus_function

/* Spico */
#define avago_spico_int                             mvMcd_avago_spico_int
#define avago_spico_resume                          mvMcd_avago_spico_resume
#define avago_spico_reset                           mvMcd_avago_spico_reset
#define serdes_spico_halt_fix                       mvMcd_serdes_spico_halt_fix
#define avago_spico_halt                            mvMcd_avago_spico_halt
#define avago_spico_running                         mvMcd_avago_spico_running
#define avago_spico_status                          mvMcd_avago_spico_status
#define spico_int_array_nobatch                     mvMcd_spico_int_array_nobatch
#define spico_int_array_batch                       mvMcd_spico_int_array_batch
#define avago_spico_int_array                       mvMcd_avago_spico_int_array
#define avago_sbm_spico_int                         mvMcd_avago_sbm_spico_int
#define avago_spico_int_check_full                  mvMcd_avago_spico_int_check_full
#define avago_spico_int                             mvMcd_avago_spico_int
#define spico_int_02_retry                          mvMcd_spico_int_02_retry
#define avago_spico_broadcast_int                   mvMcd_avago_spico_broadcast_int
#define avago_spico_broadcast_int_w_mask            mvMcd_avago_spico_broadcast_int_w_mask
#define avago_serdes_set_error_timer                mvMcd_avago_serdes_set_error_timer

/* Load/Upload file */
#define avago_spico_upload                          mvMcd_avago_spico_upload
#define avago_spico_upload_swap_image               mvMcd_avago_spico_upload_swap_image
#define spico_burst_upload                          mvMcd_spico_burst_upload
#define avago_spico_upload_file                     mvMcd_avago_spico_upload_file
#define spico_upload_image                          mvMcd_spico_upload_image
#define avago_spico_wait_for_upload                 mvMcd_avago_spico_wait_for_upload
#define avago_firmware_upload                       mvMcd_avago_firmware_upload
#define avago_firmware_get_rev                      mvMcd_avago_firmware_get_rev
#define avago_firmware_get_build_id                 mvMcd_avago_firmware_get_build_id
#define avago_firmware_upload_file                  mvMcd_avago_firmware_upload_file
#define avago_load_rom_from_file                    mvMcd_avago_load_rom_from_file
#define avago_find_swap_file                        mvMcd_avago_find_swap_file
#define aapl_sbm_rom_has_sdi                        mvMcd_aapl_sbm_rom_has_sdi
#define merge_sdi_files                             mvMcd_merge_sdi_files
#define avago_twi_wait_for_complete                 mvMcd_avago_twi_wait_for_complete
#define aapl_read_file                              mvMcd_aapl_read_file

/* LSB revision */
#define avago_serdes_get_lsb_rev                    mvMcd_avago_serdes_get_lsb_rev

/* CRC */
#define avago_spico_crc                             mvMcd_avago_spico_crc
#define aapl_crc_one_byte                           mvMcd_aapl_crc_one_byte
#define aapl_crc_rom                                mvMcd_aapl_crc_rom
#define aapl_verify_rom_crc                         mvMcd_aapl_verify_rom_crc

/* Connection/Communication */
#define aapl_connect                                mvMcd_aapl_connect
#define aapl_close_connection                       mvMcd_aapl_close_connection
#define aapl_connection_status                      mvMcd_aapl_connection_status
#define aapl_is_i2c_communication_method            mvMcd_aapl_is_i2c_communication_method
#define aapl_is_mdio_communication_method           mvMcd_aapl_is_mdio_communication_method
#define aapl_is_sbus_communication_method           mvMcd_aapl_is_sbus_communication_method
#define aapl_is_aacs_communication_method           mvMcd_aapl_is_aacs_communication_method
#define aapl_is_user_communication_method           mvMcd_aapl_is_user_communication_method
#define aapl_is_system_communication_method         mvMcd_aapl_is_system_communication_method

/* Address */
#define avago_struct_to_addr                        mvMcd_avago_struct_to_addr
#define avago_addr_to_struct                        mvMcd_avago_addr_to_struct
#define avago_make_sbus_controller_addr             mvMcd_avago_make_sbus_controller_addr
#define avago_make_sbus_master_addr                 mvMcd_avago_make_sbus_master_addr
#define avago_make_sbus_controller_addr             mvMcd_avago_make_sbus_controller_addr
#define avago_make_serdes_broadcast_addr            mvMcd_avago_make_serdes_broadcast_addr
#define aapl_broadcast_first                        mvMcd_aapl_broadcast_first
#define aapl_broadcast_next                         mvMcd_aapl_broadcast_next
#define aapl_addr_to_str                            mvMcd_aapl_addr_to_str
#define aapl_str_to_addr                            mvMcd_aapl_str_to_addr
#define avago_make_addr3                            mvMcd_avago_make_addr3

/* RX Signal */
#define avago_serdes_initialize_signal_ok           mvMcd_avago_serdes_initialize_signal_ok
#define avago_serdes_get_signal_ok                  mvMcd_avago_serdes_get_signal_ok
#define avago_serdes_get_signal_ok_threshold        mvMcd_avago_serdes_get_signal_ok_threshold
#define avago_serdes_get_signal_ok_live             mvMcd_avago_serdes_get_signal_ok_live
#define avago_serdes_get_signal_ok_enable           mvMcd_avago_serdes_get_signal_ok_enable
#define avago_serdes_get_electrical_idle            mvMcd_avago_serdes_get_electrical_idle
#define avago_serdes_slip_bits                      mvMcd_avago_serdes_slip_bits
#define avago_serdes_get_rx_line_encoding           mvMcd_avago_serdes_get_rx_line_encoding
#define avago_serdes_get_rx_register_clock          mvMcd_avago_serdes_get_rx_register_clock
#define avago_serdes_get_rx_cmp_mode                mvMcd_avago_serdes_get_rx_cmp_mode
#define avago_serdes_set_rx_cmp_mode                mvMcd_avago_serdes_set_rx_cmp_mode

/* TX Signal */
#define avago_serdes_tx_eq_init                     mvMcd_avago_serdes_tx_eq_init
#define avago_serdes_set_tx_eq                      mvMcd_avago_serdes_set_tx_eq
#define avago_serdes_get_tx_eq                      mvMcd_avago_serdes_get_tx_eq
#define avago_serdes_set_tx_output_enable           mvMcd_avago_serdes_set_tx_output_enable
#define avago_serdes_get_tx_output_enable           mvMcd_avago_serdes_get_tx_output_enable

/* TX/RX Signals */
#define avago_serdes_get_tx_rx_ready                mvMcd_avago_serdes_get_tx_rx_ready
#define avago_serdes_set_tx_rx_enable               mvMcd_avago_serdes_set_tx_rx_enable
#define avago_serdes_set_tx_rx_width                mvMcd_avago_serdes_set_tx_rx_width
#define avago_serdes_get_tx_rx_width                mvMcd_avago_serdes_get_tx_rx_width
#define avago_serdes_set_tx_rx_width_pam            mvMcd_avago_serdes_set_tx_rx_width_pam

/* divider */
#define divider_lookup28nm                          mvMcd_divider_lookup28nm

/* RX PLL frequency */
#define avago_serdes_get_frequency_lock             mvMcd_avago_serdes_get_frequency_lock

/* RX/TX phase */
#define avago_serdes_slip_rx_phase                  mvMcd_avago_serdes_slip_rx_phase
#define avago_serdes_slip_tx_phase                  mvMcd_avago_serdes_slip_tx_phase
#define avago_serdes_get_phase_multiplier           mvMcd_avago_serdes_get_phase_multiplier
#define avago_serdes_power_down_phase_interpolator  mvMcd_avago_serdes_power_down_phase_interpolator

/* TX PLL clock source */
#define avago_serdes_get_tx_pll_clk_src             mvMcd_avago_serdes_get_tx_pll_clk_src
#define avago_serdes_set_tx_pll_clk_src             mvMcd_avago_serdes_set_tx_pll_clk_src

/* Tuning */
#define avago_serdes_tune_init                      mvMcd_avago_serdes_tune_init
#define avago_serdes_tune                           mvMcd_avago_serdes_tune

/* PMD */
#define avago_serdes_pmd_init                       mvMcd_avago_serdes_pmd_init
#define avago_serdes_pmd_train                      mvMcd_avago_serdes_pmd_train
#define avago_serdes_pmd_status                     mvMcd_avago_serdes_pmd_status
#define avago_serdes_pmd_config_construct           mvMcd_avago_serdes_pmd_config_construct
#define avago_serdes_pmd_config_destruct            mvMcd_avago_serdes_pmd_config_destruct
#define avago_serdes_pmd_debug_construct            mvMcd_avago_serdes_pmd_debug_construct
#define avago_serdes_pmd_debug_destruct             mvMcd_avago_serdes_pmd_debug_destruct
#define avago_serdes_pmd_debug                      mvMcd_avago_serdes_pmd_debug
#define avago_serdes_pmd_debug_print                mvMcd_avago_serdes_pmd_debug_print

/* DFE */
#define avago_serdes_dfe_running                    mvMcd_avago_serdes_dfe_running
#define avago_serdes_dfe_wait                       mvMcd_avago_serdes_dfe_wait
#define avago_serdes_dfe_pause                      mvMcd_avago_serdes_dfe_pause
#define avago_serdes_dfe_resume                     mvMcd_avago_serdes_dfe_resume

/* Polarity - RX/TX invert */
#define avago_serdes_get_tx_invert                  mvMcd_avago_serdes_get_tx_invert
#define avago_serdes_set_tx_invert                  mvMcd_avago_serdes_set_tx_invert
#define avago_serdes_get_rx_invert                  mvMcd_avago_serdes_get_rx_invert
#define avago_serdes_set_rx_invert                  mvMcd_avago_serdes_set_rx_invert

/* RX/TX Error Injection */
#define avago_serdes_tx_inject_error                mvMcd_avago_serdes_tx_inject_error
#define avago_serdes_rx_inject_error                mvMcd_avago_serdes_rx_inject_error

/* Eye */
#define avago_serdes_eye_config_construct           mvMcd_avago_serdes_eye_config_construct
#define avago_serdes_eye_config_destruct            mvMcd_avago_serdes_eye_config_destruct
#define avago_serdes_eye_data_construct             mvMcd_avago_serdes_eye_data_construct
#define avago_serdes_eye_data_destruct              mvMcd_avago_serdes_eye_data_destruct
#define avago_serdes_eye_vbtc_format                mvMcd_avago_serdes_eye_vbtc_format
#define avago_serdes_eye_hbtc_format                mvMcd_avago_serdes_eye_hbtc_format
#define avago_serdes_eye_hbtc_extrapolate           mvMcd_avago_serdes_eye_hbtc_extrapolate
#define avago_serdes_eye_vbtc_extrapolate           mvMcd_avago_serdes_eye_vbtc_extrapolate
#define avago_serdes_eye_hbtc_log_print             mvMcd_avago_serdes_eye_hbtc_log_print
#define avago_serdes_eye_vbtc_log_print             mvMcd_avago_serdes_eye_vbtc_log_print
#define avago_serdes_eye_hbtc_write                 mvMcd_avago_serdes_eye_hbtc_write
#define avago_serdes_eye_vbtc_write                 mvMcd_avago_serdes_eye_vbtc_write
#define avago_serdes_eye_get_simple_metric          mvMcd_avago_serdes_eye_get_simple_metric
#define avago_serdes_eye_plot_format                mvMcd_avago_serdes_eye_plot_format
#define avago_serdes_eye_gradient_plot_format       mvMcd_avago_serdes_eye_gradient_plot_format
#define avago_serdes_eye_plot_log_print             mvMcd_avago_serdes_eye_plot_log_print
#define avago_serdes_eye_plot_write                 mvMcd_avago_serdes_eye_plot_write
#define avago_serdes_eye_gradient_plot_write        mvMcd_avago_serdes_eye_gradient_plot_write
#define avago_serdes_eye_data_write                 mvMcd_avago_serdes_eye_data_write
#define avago_serdes_eye_data_write_file            mvMcd_avago_serdes_eye_data_write_file
#define avago_serdes_eye_data_read_file             mvMcd_avago_serdes_eye_data_read_file
#define avago_serdes_eye_bits_get                   mvMcd_avago_serdes_eye_bits_get
#define avago_serdes_eye_grad_get                   mvMcd_avago_serdes_eye_grad_get
#define avago_serdes_eye_qval_get                   mvMcd_avago_serdes_eye_qval_get
#define avago_serdes_eye_errors_get                 mvMcd_avago_serdes_eye_errors_get
#define avago_serdes_eye_get                        mvMcd_avago_serdes_eye_get
#define aapl_eye_type_to_str                        mvMcd_aapl_eye_type_to_str
#define aapl_str_to_eye_type                        mvMcd_aapl_str_to_eye_type
#define allocate_eye_arrays                         mvMcd_allocate_eye_arrays

/* Diagnostic */
#define avago_diag_sbus_rw_test                     mvMcd_avago_diag_sbus_rw_test
#define avago_spico_ram_bist                        mvMcd_avago_spico_ram_bist
#define avago_serdes_get_dac_range                  mvMcd_avago_serdes_get_dac_range

/* RX termination */
#define avago_serdes_get_rx_term                    mvMcd_avago_serdes_get_rx_term
#define avago_serdes_set_rx_term                    mvMcd_avago_serdes_set_rx_term

/* RX Loopback */
#define avago_serdes_get_rx_input_loopback          mvMcd_avago_serdes_get_rx_input_loopback
#define avago_serdes_set_rx_input_loopback          mvMcd_avago_serdes_set_rx_input_loopback

/* PRBS Generator */
#define avago_serdes_set_tx_data_sel                mvMcd_avago_serdes_set_tx_data_sel
#define avago_serdes_get_tx_data_sel                mvMcd_avago_serdes_get_tx_data_sel
#define avago_serdes_set_tx_user_data               mvMcd_avago_serdes_set_tx_user_data
#define avago_serdes_get_tx_user_data               mvMcd_avago_serdes_get_tx_user_data
#define avago_serdes_set_rx_cmp_data                mvMcd_avago_serdes_set_rx_cmp_data
#define avago_serdes_get_rx_cmp_data                mvMcd_avago_serdes_get_rx_cmp_data
#define avago_serdes_get_errors                     mvMcd_avago_serdes_get_errors
#define avago_serdes_set_tx_rx_width                mvMcd_avago_serdes_set_tx_rx_width
#define avago_serdes_error_reset                    mvMcd_avago_serdes_error_reset

/* Memory/Address Rd/Wr */
#define avago_serdes_mem_rd                         mvMcd_avago_serdes_mem_rd
#define avago_serdes_mem_wr                         mvMcd_avago_serdes_mem_wr
#define avago_serdes_mem_rmw                        mvMcd_avago_serdes_mem_rmw
#define serdes_get_int01_bits                       mvMcd_serdes_get_int01_bits
#define serdes_get_int30_bits                       mvMcd_serdes_get_int30_bits
#define avago_hardware_info_format                  mvMcd_avago_hardware_info_format

/* Management Data In/Out */
#define avago_mdio                                  mvMcd_avago_mdio
#define avago_mdio_open                             mvMcd_avago_mdio_open
#define avago_mdio_close                            mvMcd_avago_mdio_close
#define avago_mdio_wr                               mvMcd_avago_mdio_wr
#define avago_mdio_rd                               mvMcd_avago_mdio_rd
#define avago_mdio_sbus                             mvMcd_avago_mdio_sbus
#define aapl_gpio_mdio_write                        mvMcd_aapl_gpio_mdio_write
#define aapl_gpio_mdio_read                         mvMcd_aapl_gpio_mdio_read
#define aapl_gpio_mdio_start                        mvMcd_aapl_gpio_mdio_start
#define aapl_gpio_mdio_send_bit                     mvMcd_aapl_gpio_mdio_send_bit
#define aapl_gpio_mdio_get_bit                      mvMcd_aapl_gpio_mdio_get_bit
#define avago_gpio_mdio_open                        mvMcd_avago_gpio_mdio_open
#define avago_gpio_mdio_close                       mvMcd_avago_gpio_mdio_close
#define aapl_gpio_mdio_function                     mvMcd_aapl_gpio_mdio_function
#define aapl_gpio_gpio_init                         mvMcd_aapl_gpio_gpio_init

/* I2C */
#define avago_i2c_sbus                              mvMcd_avago_i2c_sbus
#define avago_i2c_open                              mvMcd_avago_i2c_open
#define avago_i2c_close                             mvMcd_avago_i2c_close
#define avago_i2c_read                              mvMcd_avago_i2c_read
#define avago_i2c_write                             mvMcd_avago_i2c_write

/* Log/Message */
#define appl_log_user                               mvMcd_appl_log_user
#define aapl_log_get                                mvMcd_aapl_log_get
#define aapl_log_clear                              mvMcd_aapl_log_clear
#define aapl_log_add                                mvMcd_aapl_log_add
#define aapl_log_printf_full                        mvMcd_aapl_log_printf_full
#define aapl_log_type_to_str                        mvMcd_aapl_log_type_to_str
#define aapl_buf_add                                mvMcd_aapl_buf_add
#define aapl_fail_full                              mvMcd_aapl_fail_full
#define aapl_user_supplied_log_func_ptr             mvMcd_aapl_user_supplied_log_func_ptr

/* Log String */
#define name_to_index                               mvMcd_name_to_index
#define value_to_index                              mvMcd_value_to_index
#define aapl_comm_method_to_str                     mvMcd_aapl_comm_method_to_str
#define aapl_str_to_comm_method                     mvMcd_aapl_str_to_comm_method
#define aapl_pll_clk_to_str                         mvMcd_aapl_pll_clk_to_str
#define aapl_str_to_pll_clk                         mvMcd_aapl_str_to_pll_clk
#define aapl_process_id_to_str                      mvMcd_aapl_process_id_to_str
#define aapl_mem_type_to_str                        mvMcd_aapl_mem_type_to_str
#define aapl_str_to_mem_type                        mvMcd_aapl_str_to_mem_type
#define aapl_bigint_to_str                          mvMcd_aapl_bigint_to_str
#define aapl_bool_to_str                            mvMcd_aapl_bool_to_str
#define aapl_onoff_to_str                           mvMcd_aapl_onoff_to_str
#define aapl_data_sel_to_str                        mvMcd_aapl_data_sel_to_str
#define aapl_str_to_data_sel                        mvMcd_aapl_str_to_data_sel
#define aapl_cmp_data_to_str                        mvMcd_aapl_cmp_data_to_str
#define aapl_str_to_cmp_data                        mvMcd_aapl_str_to_cmp_data
#define aapl_cmp_mode_to_str                        mvMcd_aapl_cmp_mode_to_str
#define aapl_str_to_cmp_mode                        mvMcd_aapl_str_to_cmp_mode
#define aapl_enable_to_str                          mvMcd_aapl_enable_to_str
#define aapl_term_to_str                            mvMcd_aapl_term_to_str
#define aapl_str_to_term                            mvMcd_aapl_str_to_term
#define aapl_dfe_tune_mode_to_str                   mvMcd_aapl_dfe_tune_mode_to_str
#define aapl_str_to_dfe_tune_mode                   mvMcd_aapl_str_to_dfe_tune_mode
#define aapl_strncasecmp                            mvMcd_aapl_strncasecmp
#define aapl_strcasecmp                             mvMcd_aapl_strcasecmp
#define aapl_strdup                                 mvMcd_aapl_strdup
#define aapl_str_rep                                mvMcd_aapl_str_rep
#define aapl_strtok_r                               mvMcd_aapl_strtok_r
#define aapl_tcp_strerr                             mvMcd_aapl_tcp_strerr

/* Jtag */
#define avago_jtag                                  mvMcd_avago_jtag
#define avago_jtag_rd                               mvMcd_avago_jtag_rd
#define avago_jtag_set_bit                          mvMcd_avago_jtag_set_bit

/* Sleep */
#define ms_sleep                                    mvMcd_ms_sleep

/* miscellaneous - service functions */
#define avago_serdes_width_to_bits                  mvMcd_avago_serdes_width_to_bits
#define avago_serdes_bits_to_width                  mvMcd_avago_serdes_bits_to_width
#define aapl_hex_2_bin                              mvMcd_aapl_hex_2_bin
#define aapl_local_strftime                         mvMcd_aapl_local_strftime
#define avago_calc_BER                              mvMcd_avago_calc_BER
#define avago_qfunc                                 mvMcd_avago_qfunc
#define avago_qfuncinv                              mvMcd_avago_qfuncinv
#define avago_qfuncinv_half                         mvMcd_avago_qfuncinv_half
#define avago_least_sqr                             mvMcd_avago_least_sqr
#define avago_interpolate                           mvMcd_avago_interpolate
#define aapl_iround                                 mvMcd_aapl_iround

#endif /* defined MV_HWS_AVAGO_SERDES_H */
