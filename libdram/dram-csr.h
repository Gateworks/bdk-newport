/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * Functions and macros for libdram access to CSR. These build
 * on the normal BDK functions to allow logging of CSRs based on
 * the libdram verbosity level. Internal use only.
 */

/**
 * Write a CSR, possibly logging it based on the verbosity
 * level. You should use DRAM_CSR_WRITE() as a convientent
 * wrapper.
 *
 * @param node
 * @param csr_name
 * @param type
 * @param busnum
 * @param size
 * @param address
 * @param value
 */
#ifdef DRAM_CSR_WRITE_INLINE
static inline void dram_csr_write(bdk_node_t node, const char *csr_name, bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value) __attribute__((always_inline));
static inline void dram_csr_write(bdk_node_t node, const char *csr_name, bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value)
{
    VB_PRT(VBL_CSRS, "N%d: DDR Config %s[%016lx] => %016lx\n", node, csr_name, address, value);
    bdk_csr_write(node, type, busnum, size, address, value);
}
#else
extern void dram_csr_write(bdk_node_t node, const char *csr_name, bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value);
#endif

/**
 * Macro to write a CSR, logging if necessary
 */
#define DRAM_CSR_WRITE(node, csr, value) \
    dram_csr_write(node, basename_##csr, bustype_##csr, busnum_##csr, sizeof(typedef_##csr), csr, value)

/**
 * Macro to make a read, modify, and write sequence easy. The "code_block"
 * should be replaced with a C code block or a comma separated list of
 * "name.s.field = value", without the quotes.
 */
#define DRAM_CSR_MODIFY(name, node, csr, code_block) do { \
        typedef_##csr name = {.u = bdk_csr_read(node, bustype_##csr, busnum_##csr, sizeof(typedef_##csr), csr)}; \
        code_block; \
        dram_csr_write(node, basename_##csr, bustype_##csr, busnum_##csr, sizeof(typedef_##csr), csr, name.u); \
    } while (0)

