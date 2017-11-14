/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <stdio.h>
#include <errno.h>

#define MAX_FILE_HANDLES 16
#define MAX_MOUNT_POINTS 12

/**
 * Structure used for mount points. This maps filenames into
 * the proper file system operations
 */
typedef struct
{
    const char *prefix;
    const __bdk_fs_ops_t *ops;
} bdk_fs_mount_t;

extern const __bdk_fs_ops_t bdk_fs_console_ops;
extern const __bdk_fs_ops_t bdk_fs_dev_ops;
extern __bdk_dev_fs_t bdk_fs_dev_uart0;
extern __bdk_dev_fs_t bdk_fs_dev_uart1;

static bdk_fs_mount_t mount_points[MAX_MOUNT_POINTS] = {
    {"/console", &bdk_fs_console_ops},
    {"/dev/", &bdk_fs_dev_ops},
    {NULL, NULL}
};

/* Node number will be fixed in __bdk_fs_init_early */
static char dev_uart0[] = "/dev/n0.uart0";
static char dev_uart1[] = "/dev/n0.uart1";

/**
 * The open file handle table. Handle 0-2 are open to start with
 * connected to uart 0. They can be closed later if needed.
 */
static __bdk_fs_file_t file_handle[MAX_FILE_HANDLES] = {
    [0] = { .fs_state = NULL, .ops = &bdk_fs_console_ops, .filename = "/console" },
    [1] = { .fs_state = NULL, .ops = &bdk_fs_console_ops, .filename = "/console" },
    [2] = { .fs_state = NULL, .ops = &bdk_fs_console_ops, .filename = "/console" },
    [3] = { .fs_state = &bdk_fs_dev_uart0, .ops = &bdk_fs_dev_ops, .filename = dev_uart0 },
    [4] = { .fs_state = &bdk_fs_dev_uart1, .ops = &bdk_fs_dev_ops, .filename = dev_uart1 },
};

/**
 * Called early in init to setup the filesystem core
 *
 * @return Zero on success, negative on failure
 */
int __bdk_fs_init_early(void)
{
    bdk_node_t node = bdk_numa_local();
    dev_uart0[6] = '0' + node;
    dev_uart1[6] = '0' + node;
    return 0;
}

/**
 * Called late in init to setup all the filesystems
 *
 * @return Zero on success, negative on failure
 */
int __bdk_fs_init_late(void)
{
    int result = 0;
    /* Init all filesystems where their init function was linked in */
    if (__bdk_fs_boot_init)
        result |= __bdk_fs_boot_init();
    if (__bdk_fs_mem_init)
        result |= __bdk_fs_mem_init();
    if (__bdk_fs_mmc_init)
        result |= __bdk_fs_mmc_init();
    if (__bdk_fs_mpi_init)
        result |= __bdk_fs_mpi_init();
    if (__bdk_fs_pbus_init)
        result |= __bdk_fs_pbus_init();
    if (__bdk_fs_pcie_init)
        result |= __bdk_fs_pcie_init();
    if (__bdk_fs_ram_init)
        result |= __bdk_fs_ram_init();
    if (__bdk_fs_rom_init)
        result |= __bdk_fs_rom_init();
    if (__bdk_fs_sata_init)
        result |= __bdk_fs_sata_init();
    if (__bdk_fs_xmodem_init)
        result |= __bdk_fs_xmodem_init();
    if (__bdk_fs_fatfs_init)
        result |= __bdk_fs_fatfs_init();
    return result;
}

/**
 * Dynamically register a new filesystem mount point. This is so
 * dependencies on stdout don't pull in all possible filesystems.
 *
 * @param prefix Prefix for mount
 * @param ops    File operations
 *
 * @return Zero on success, negative on failure
 */
int bdk_fs_register(const char *prefix, const __bdk_fs_ops_t *ops)
{
    /* Find the first empty mount point */
    int i = 0;
    while (mount_points[i].prefix)
        i++;

    /* Fail if all spots are full. Note that we must keep the last
        one as NULL to mark the end */
    if (i >= MAX_MOUNT_POINTS - 1)
    {
        bdk_error("bdk_fs_register: Too many mount points\n");
        return -1;
    }

    /* Add the new mount point */
    mount_points[i].prefix = prefix;
    mount_points[i].ops = ops;
    mount_points[i+1].prefix = NULL;
    mount_points[i+1].ops = NULL;
    return 0;
}


/**
 * Get the mount point for the given filename
 *
 * @param name   File to find mount point for
 *
 * @return Mount point index, or -1 on failure
 */
static int get_mount(const char *name)
{
    int index = 0;

    while (mount_points[index].prefix)
    {
        int len = strlen(mount_points[index].prefix);
        if (strncmp(mount_points[index].prefix, name, len) == 0)
            return index;
        index++;
    }

    return -1;
}


/**
 * Get the open file descriptor for a file handle
 *
 * @param handle File handle to get
 *
 * @return File descriptor or NULL on failure
 */
static __bdk_fs_file_t *get_file(int handle)
{
    if ((handle<0) || (handle>=MAX_FILE_HANDLES))
        return NULL;
    if (file_handle[handle].ops == NULL)
        return NULL;
    return &file_handle[handle];
}


/**
 * Perform stat()
 *
 * @param name   File to stat
 * @param st     Result of the stat
 *
 * @return Zero on success
 */
int _stat_r(struct _reent *reent, const char *name, struct stat *st)
{
    int mount = get_mount(name);
    if ((mount != -1) && mount_points[mount].ops->stat)
    {
        name += strlen(mount_points[mount].prefix);
        return mount_points[mount].ops->stat(name, st);
    }
    else
    {
        reent->_errno = ENOENT;
        return -1;
    }
}


/**
 * Unlink / Delete a file
 *
 * @param name   File to delete
 *
 * @return Zero on success
 */
int _unlink_r(struct _reent *reent, const char *name)
{
    int mount = get_mount(name);
    if ((mount != -1) && mount_points[mount].ops->unlink)
    {
        name += strlen(mount_points[mount].prefix);
        return mount_points[mount].ops->unlink(name);
    }
    else
    {
        reent->_errno = ENOENT;
        return -1;
    }
}


/**
 * Open a file
 *
 * @param name   File to open
 * @param flags  Read / write flags
 * @param mode   Unused attributes
 *
 * @return File handle, or -1 on failure
 */
int _open_r(struct _reent *reent, const char *name, int flags, int mode)
{
    int handle;
    int mount = get_mount(name);
    if (mount == -1)
    {
        reent->_errno = ENOENT;
        return -1;
    }

    /* Find a free file handle */
    for (handle=0; handle<MAX_FILE_HANDLES; handle++)
        if (file_handle[handle].ops == NULL)
            break;
    if (handle == MAX_FILE_HANDLES)
    {
        reent->_errno = EMFILE;
        return -1;
    }

    /* Assign the file handle details */
    file_handle[handle].ops = mount_points[mount].ops;
    file_handle[handle].filename = strdup(name);
    file_handle[handle].location = 0;
    file_handle[handle].fs_state = NULL;

    /* Fail if the strdup of the filename failed */
    if (file_handle[handle].filename == NULL)
    {
        file_handle[handle].ops = NULL;
        reent->_errno = ENOMEM;
        return -1;
    }

    /* Call the FS open if it was supplied */
    if (mount_points[mount].ops->open)
    {
        name += strlen(mount_points[mount].prefix);
        reent->_errno = ENOENT;
        file_handle[handle].fs_state = mount_points[mount].ops->open(name, flags);
        if (file_handle[handle].fs_state == NULL)
        {
            file_handle[handle].ops = NULL;
            free((void*)file_handle[handle].filename);
            return -1;
        }
    }
    return handle;
}


/**
 * Close a file handle
 *
 * @param handle File handle to close
 *
 * @return Zero on success
 */
int _close_r(struct _reent *reent, int handle)
{
    int result = 0;
    __bdk_fs_file_t *file = get_file(handle);
    if (!file)
    {
        reent->_errno = EBADF;
        return -1;
    }

    if (file->ops->close)
        result = file->ops->close(file);

    if (result == 0)
    {
        if (file->filename)
            free((void*)file->filename);
        memset(file, 0, sizeof(*file));
    }

    return result;
}


/**
 * Seek to a specific file location
 *
 * @param handle File handle
 * @param offset New location
 * @param whence Basis for the new location
 *
 * @return The new location in the file
 */
off_t _lseek_r(struct _reent *reent, int handle, off_t offset, int whence)
{
    __bdk_fs_file_t *file = get_file(handle);
    if (!file)
    {
        reent->_errno = ENOENT;
        return -1;
    }

    switch (whence)
    {
        case SEEK_SET:
            file->location = offset;
            break;
        case SEEK_CUR:
            file->location += offset;
            break;
        case SEEK_END:
            bdk_fatal("SEEK_END not supported by the BDK filesystem\n");
            break;
    }
    return file->location;
}


/**
 * Read from a file handle
 *
 * @param handle File to read
 * @param buffer Buffer receiving the data
 * @param length Length of the read
 *
 * @return Number of bytes read, can be zero. Negative is a failure
 */
int _read_r(struct _reent *reent, int handle, void *buffer, int length)
{
    __bdk_fs_file_t *file = get_file(handle);
    if (file && file->ops->read)
    {
        int result = file->ops->read(file, buffer, length);
        if (result > 0)
            file->location += result;
        return result;
    }
    else
    {
        reent->_errno = EBADF;
        return -1;
    }
}


/**
 * Write to a file handle
 *
 * @param handle File to write
 * @param buffer Data to write
 * @param length Length of the data
 *
 * @return Number of bytes written. Negative on failure
 */
int _write_r(struct _reent *reent, int handle, const void *buffer, int length)
{
    __bdk_fs_file_t *file = get_file(handle);
    if (file && file->ops->write)
    {
        int result = file->ops->write(file, buffer, length);
        if (result > 0)
            file->location += result;
        return result;
    }
    else
    {
        reent->_errno = EBADF;
        return -1;
    }
}


/**
 * Stat an open file
 *
 * @param handle File handle
 * @param st     Status results
 *
 * @return Zero on success
 */
int _fstat_r(struct _reent *reent, int handle, struct stat *st)
{
    __bdk_fs_file_t *file = get_file(handle);
    if (file && file->ops->stat)
        return file->ops->stat(file->filename, st);
    else
    {
        reent->_errno = EBADF;
        return -1;
    }
}


/**
 * Jump the PC to a physical address. No checking is performed.
 *
 * @param paddress Physical address to jump to
 * @param arg0     Value to place in X0 before the jump
 * @param arg1     Value to place in X1 before the jump
 *
 * @return Zero on success, negative on failure. Note that call most likely
 *         will never return.
 */
int bdk_jump_address(uint64_t paddress, uint64_t arg0, uint64_t arg1)
{
    int (*ptr)(uint64_t arg0, uint64_t arg1) = bdk_phys_to_ptr(paddress);
    if (ptr == NULL)
        return -1;
    return ptr(arg0, arg1);
}

/*
 * default output formatter for file list
 */
static void default_list_formatter(const char *outbuf, void *dummy) {
    puts(outbuf);
}
/**
 * List files or filesystems
 * @param path pointer to the path string
 * @param callback address of formatter If no formatter is specified default_list_formatter is used.
 * @param callback_state pointer to formatter context, passed back to it
 *
 * @return Zero on success, non-zero on failure.
 */

int bdk_fs_list(const char *path, __bdk_fs_list_callback callback, void *callback_state)
{
    if (NULL == path) return -1;
    __bdk_fs_list_callback list_item_output = (callback) ? callback : default_list_formatter;

    int rc;
    if (1 >= strlen(path)) {
        /* root directory listing */
        if (('\0' == *path) || ('/' == *path)) {
            for(unsigned ndx=0; ndx< MAX_MOUNT_POINTS; ndx++) {
                if  (mount_points[ndx].prefix) {
                    list_item_output(mount_points[ndx].prefix, callback_state);
                }
            }
            return 0;
        }
        return -1;
    } else {
        const char *usedpath = path;
        char *buf = NULL;

        int mount = get_mount(path);
        if (mount < 0) {
            // try once more adding leading and trailing slashes
            int len = strlen(path);
            buf = malloc(len+3);
            if (NULL == buf) return -1;
            bool tryagain = false;
            int i=0;
            if (path[0] != '/') {
                buf[0] = '/';
                i++;tryagain = true;
            }
            memcpy(&buf[i],path,len);
            if (('/' != path[len-1]) && (NULL == strchr(path+1, '/'))) {
                        buf[i+len] = '/';
                        i++;
                        tryagain = true;
                    }
            if (tryagain) {
                usedpath = buf;
                buf[len+i] = '\0';
                mount = get_mount(buf);
            }
        }
        if ((mount >= 0) && mount_points[mount].ops->list){
            usedpath += strlen(mount_points[mount].prefix);
            // TODO Should we insert callback to add fs name here?
            rc = mount_points[mount].ops->list(usedpath, list_item_output, callback_state);
        } else
            rc = -1;
        if (buf) free(buf);
    }

    return rc;
}
