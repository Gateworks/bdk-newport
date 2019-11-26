/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to CN9XXX flash script (SCR)
 *
 * @addtogroup hal
 * @{
 */

/**
 * Initialize a new memory script for creation
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_init(void);

/**
 * Calculate the checksum of the current script
 *
 * @return Checksum
 */
extern uint32_t bdk_scr_chksum(void);

/**
 * Read the script from the boot flash
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_read(void);

/**
 * Write the current script to the boot flash
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_write(void);

/**
 * Display the current script
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_display(void);

/**
 * Add a new CSR write to the current script
 *
 * @param type    Type of CSR being written
 * @param busnum  Bus number from CSR
 * @param size    Size of the CSR
 * @param address Address of the CSR
 * @param value   Value to write
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_add_write(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value);

/**
 * Add a script step to poll a CSR for status
 *
 * @param type       Type of CSR being written
 * @param busnum     Bus number from CSR
 * @param size       Size of the CSR
 * @param address    Address of the CSR
 * @param mask       Mask for which bits to look at
 * @param value      Value to compare with
 * @param scr_cmp_type_e
 *                   Compare type
 * @param timeout_ns Timeout in nanoseconds
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_add_poll(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t mask, uint64_t value, int scr_cmp_type_e, int timeout_ns);

/**
 * Add a wait
 *
 * @param timeout_ns Timeout in nanoseconds
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_add_wait(int timeout_ns);

/**
 * Add a script step to poll a CSR for status an exit
 *
 * @param type    Type of CSR being written
 * @param busnum  Bus number from CSR
 * @param size    Size of the CSR
 * @param address Address of the CSR
 * @param mask    Mask for which bits to look at
 * @param value   Value to compare with
 * @param scr_cmp_type_e
 *                Compare type
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_add_cmp_exit(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t mask, uint64_t value, int scr_cmp_type_e);

/**
 * Add a script step to poll a CSR for status and jump to a location. The location
 * can be update with bdk_scr_update_jump()
 *
 * @param type    Type of CSR being written
 * @param busnum  Bus number from CSR
 * @param size    Size of the CSR
 * @param address Address of the CSR
 * @param mask    Mask for which bits to look at
 * @param value   Value to compare with
 * @param scr_cmp_type_e
 *                Compare type
 * @param jump    Jump off set as location into script. Pass 0 if it will be updated later
 *
 * @return Zero or positive on success, negative on failure. The non-negative return value
 *         is the handle to pass to bdk_scr_update_jump()
 */
extern int bdk_scr_add_cmp_jump(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t mask, uint64_t value, int scr_cmp_type_e, int jump);

/**
 * Update the jump location for a existing compare and jump
 *
 * @param handle Handle returned by bdk_scr_add_cmp_jump()
 * @param jump   New jump address
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_update_jump(int handle, int jump);

/**
 * Add a script step to exit the script
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_add_exit(void);

/**
 * Create a default script for use in booting
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_scr_create_default(void);

/** @} */
