/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Infastructure to allow standard C file IO to various file systems.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup stdio Standard IO related functions
 * @{
 */

struct stat;

/**
 * This structure represents non-device files which have free form names
 */
typedef struct
{
    void *fs_state;
    const struct __bdk_fs_ops_s *ops;
    const char *filename;
    uint64_t location;
} __bdk_fs_file_t;

/**
 * This structure are the operations that can be performed on non-device files
 */
typedef void(*__bdk_fs_list_callback)(const char *name, void *state);
typedef struct __bdk_fs_ops_s
{
    int (*unlink)(const char *name);
    void *(*open)(const char *name, int flags);
    int (*close)(__bdk_fs_file_t *handle);
    int (*read)(__bdk_fs_file_t *handle, void *buffer, int length);
    int (*write)(__bdk_fs_file_t *handle, const void *buffer, int length);
    int (*list)(const char *path, __bdk_fs_list_callback callback, void *callback_state);
} __bdk_fs_ops_t;

/**
 * This represents state for device files that represent hardware
 */
typedef struct
{
    const char *filename;
    uint64_t location;
    bdk_node_t dev_node;
    int dev_index;
} __bdk_fs_dev_t;

/**
 * These are the operations that can be performed on device files
 */
typedef struct
{
    int (*open)(__bdk_fs_dev_t *dev, int flags);
    int (*close)(__bdk_fs_dev_t *dev);
    int (*read)(__bdk_fs_dev_t *dev, void *buffer, int length);
    int (*write)(__bdk_fs_dev_t *dev, const void *buffer, int length);
    int block_size;
} __bdk_fs_dev_ops_t;

/**
 * Used to track dynamically allocated device. Note that only one device
 * is created for all nodes. For example, there will be 16 SATA devices on CN88XX
 * regardless of the number of nodes. Used internally by bdk-fs-dev.c.
 */
typedef struct __bdk_dev_fs
{
    struct __bdk_dev_fs *next;
    const __bdk_fs_dev_ops_t *ops;
    char dev_name[16];
    int dev_index;
} __bdk_dev_fs_t;

int __bdk_fs_init_early(void);
int __bdk_fs_init_late(void);
int bdk_fs_register(const char *prefix, const __bdk_fs_ops_t *ops);
int bdk_fs_register_dev(const char *dev_base, int dev_index, const __bdk_fs_dev_ops_t *ops);
int bdk_fs_unregister_dev(const char *dev_base, int dev_index);
int bdk_jump_address(uint64_t paddress, uint64_t arg0, uint64_t arg1);
int __bdk_fs_check_break(void);
int bdk_console_connect_fd(int fd);
int bdk_console_open_file(const char *filename);
int bdk_fs_list(const char *path, __bdk_fs_list_callback callback, void *callback_state);

/* Prototypes for the init functions for all file systems */
extern int __bdk_fs_base64_init(void) BDK_WEAK;
extern int __bdk_fs_boot_init(void) BDK_WEAK;
extern int __bdk_fs_fatfs_init(void) BDK_WEAK;
extern void __bdk_fs_fatfs_usbnotify(int drvIndex, int available) BDK_WEAK;
extern int __bdk_fs_mem_init(void) BDK_WEAK;
extern int __bdk_fs_mmc_init(void) BDK_WEAK;
extern int __bdk_fs_mpi_init(void) BDK_WEAK;
extern int __bdk_fs_pbus_init(void) BDK_WEAK;
extern int __bdk_fs_pcie_init(void) BDK_WEAK;
extern int __bdk_fs_ram_init(void) BDK_WEAK;
extern int __bdk_fs_rom_init(void) BDK_WEAK;
extern int __bdk_fs_sata_init(void) BDK_WEAK;
extern int __bdk_fs_xmodem_init(void) BDK_WEAK;
/** @} */
