/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <fcntl.h>

extern const __bdk_fs_dev_ops_t bdk_fs_uart_ops;

/* The uarts are treated special. These need to work very early, so statically
   add them to the device list. Do uart1 first as uart0 must point to it */
__bdk_dev_fs_t bdk_fs_dev_uart1 = {
    .next = NULL,
    .ops = &bdk_fs_uart_ops,
    .dev_name = "uart1",
    .dev_index = 1,
};

/* Allocate uart0 pointing to uart1 */
__bdk_dev_fs_t bdk_fs_dev_uart0 = {
    .next = &bdk_fs_dev_uart1,
    .ops = &bdk_fs_uart_ops,
    .dev_name = "uart0",
    .dev_index = 0,
};

/* Linked list of all device. Uart0 is the head and uart1 is the tail */
static __bdk_dev_fs_t *dev_head = &bdk_fs_dev_uart0;
static __bdk_dev_fs_t *dev_tail = &bdk_fs_dev_uart1;
static bdk_rlock_t dev_lock = {0,0};
/**
 * Register a hardware device for use as a IO file. Devices are treated differently
 * than other files as they are per node. Device names are of the format "n0.dev0".
 * "n0" is the node number of the device, "dev" is the dev_base prefix given in
 * this function call.
 *
 * @param dev_base  Name of the base device. Examples "sata", "uart", "pcie"
 * @param dev_index Device index tying this device to a hardware block. This becomes the last number
 *                  in the name.
 * @param ops       File operations for this device
 *
 * @return Zero on success, negative on failure
 */
int bdk_fs_register_dev(const char *dev_base, int dev_index, const __bdk_fs_dev_ops_t *ops)
{
    /* Allocate a structure to track this device */
    __bdk_dev_fs_t *dev = calloc(1, sizeof(__bdk_dev_fs_t));
    if (!dev)
    {
        bdk_error("Failed to allocate list entry for device %s%d\n", dev_base, dev_index);
        return -1;
    }
    bdk_rlock_lock(&dev_lock);
    /* Fill the structure */
    dev->next = NULL;
    dev->ops = ops;
    snprintf(dev->dev_name, sizeof(dev->dev_name), "%s%d", dev_base, dev_index);
    dev->dev_name[sizeof(dev->dev_name)-1] = 0;
    dev->dev_index = dev_index;

    /* Add it to the dev_head list */
    if (dev_tail)
        dev_tail->next = dev;
    else
        dev_head = dev;
    dev_tail = dev;
    bdk_rlock_unlock(&dev_lock);
    return 0;
}

/**
 * UnRegister a hardware device for use as a IO file. Devices are treated differently
 * than other files as they are per node. Device names are of the format "n0.dev0".
 * "n0" is the node number of the device, "dev" is the dev_base prefix given in
 * this function call.
 *
 * @param dev_base  Name of the base device. Examples "sata", "uart", "pcie"
 * @param dev_index Device index tying this device to a hardware block. This becomes the last number
 *                  in the name.
 *
 * @return Zero on success, negative on failure
 */
int bdk_fs_unregister_dev(const char *dev_base, int dev_index)
{
    __bdk_dev_fs_t *dev, *pdev;
    char dname[sizeof(dev->dev_name)];
    if (NULL == dev_tail) return -1;
    snprintf(dname,sizeof(dname), "%s%d",dev_base,dev_index);
    dname[sizeof(dname)-1] = '\0';
    bdk_rlock_lock(&dev_lock);
    dev = dev_head;
    pdev = NULL;
    while(dev) {
        if (0 == strcmp(dname,dev->dev_name)) {
            if (NULL == pdev) {
                if (dev == dev_tail) {
                    dev_head = dev_tail = NULL;
                } else {
                    dev_head = dev->next;
                }
            } else {
                pdev->next = dev->next;
                if (NULL == pdev->next) dev_tail = pdev;
            }
            bdk_rlock_unlock(&dev_lock);
            free(dev);
            return 0;
        }
        pdev = dev;
        dev = dev->next;
    }
    bdk_rlock_unlock(&dev_lock);
    return -1;
}

/**
 * Extract the node number from the device name. Names are "n0.dev0"
 *
 * @param name   Name to extract from
 *
 * @return Node number, or -1 on failure
 */
static int dev_get_node(const char *name)
{
    /* Skip any path prefix */
    if (name[0] == '/')
    {
        name++;
        while (name[0] != '/')
            name++;
        name++;
    }
    if (name[0] != 'n')
        return -1;
    if ((name[1] < '0') || (name[1] > '3'))
        return -1;
    if (name[2] != '.')
        return -1;
    int node = name[1] - '0';
    if (!bdk_numa_exists(node))
        return -1;
    return node;
}

/**
 * Lookup a device by name. Note that the leading node number is ignored in
 * the match checking.
 *
 * @param name   Name to search for. Format "N0.DEV0"
 *
 * @return Device structure or NULL
 */
static __bdk_dev_fs_t *dev_find(const char *name)
{
    const char *name_no_node = name + 3;
    char tmp[32];
    __bdk_dev_fs_t *dev;

    /* Truncate name at next / as MPI uses sub names */
    const char *sub_name = strchr(name_no_node, '/');
    if (sub_name)
    {
        unsigned int length = sub_name - name_no_node;
        if (length >= sizeof(tmp))
            length = sizeof(tmp)-1;
        memcpy(tmp, name_no_node, length);
        tmp[length] = 0;
        name_no_node = tmp;
    }
    bdk_rlock_lock(&dev_lock);
    dev = dev_head;
    while (dev)
    {
        if (strcmp(name_no_node, dev->dev_name) == 0) {
            bdk_rlock_unlock(&dev_lock);
            return dev;
        }
        dev = dev->next;
    }
    bdk_rlock_unlock(&dev_lock);
    return NULL;
}

/**
 * Call open for the device if it is implemented. If there is no open, then
 * return good status. Not all devices care when they are opened / closed.
 *
 * @param name   Device name to open
 * @param flags  Flags of the open
 *
 * @return State pointer of success, NULL on failure
 */
static void *dev_open(const char *name, int flags)
{
    int node = dev_get_node(name);
    if (node < 0)
        return NULL;
    __bdk_dev_fs_t *dev = dev_find(name);
    if (!dev)
        return NULL;

    __bdk_fs_dev_t state;
    state.filename = name;
    state.location = 0;
    state.dev_node = node;
    state.dev_index = dev->dev_index;

    if (dev->ops->open && dev->ops->open(&state, flags))
        return NULL;
    return dev;
}

/**
 * Called to close the file. May do nothing for some device
 *
 * @param handle File handle to close
 *
 * @return Zero on success, negative on failure
 */
static int dev_close(__bdk_fs_file_t *handle)
{
    const __bdk_dev_fs_t *dev = handle->fs_state;
    bdk_rlock_lock(&dev_lock);
    const __bdk_dev_fs_t * tdev = dev_head;
    while (tdev)
    {
        if (tdev == dev) {
            break;
        }
        tdev = tdev->next;
    }
    bdk_rlock_unlock(&dev_lock);
    if (NULL == tdev) return 0; // Device no longer exists
    int node = dev_get_node(handle->filename);
    if (node < 0)
        return 0;

    __bdk_fs_dev_t state;
    state.filename = handle->filename;
    state.location = handle->location;
    state.dev_node = node;
    state.dev_index = dev->dev_index;

    if (dev->ops->close)
        return dev->ops->close(&state);
    else
        return 0;
}

/**
 * Read data from a device
 *
 * @param handle File handle
 * @param buffer Buffer to fill
 * @param length NUmber of bytes to fill
 *
 * @return Bytes read, negative on error, zero on no more data
 */
static int dev_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    const __bdk_dev_fs_t *dev = handle->fs_state;
    int node = dev_get_node(handle->filename);
    if (node < 0)
        return -1;
    if (!dev->ops->read)
        return -1;

    __bdk_fs_dev_t state;
    state.filename = handle->filename;
    state.location = handle->location;
    state.dev_node = node;
    state.dev_index = dev->dev_index;

    /* Check the alignment of the call  */
    int block_size = dev->ops->block_size;
    int block_mask = block_size - 1;
    bool start_aligned = (state.location & block_mask) == 0;
    bool len_aligned = (length & block_mask) == 0;
    bool aligned = start_aligned && len_aligned;

    if ((block_size <= 1) || aligned)
        return dev->ops->read(&state, buffer, length);

    char tmp[block_size];
    state.location &= -block_size;
    int status = dev->ops->read(&state, tmp, block_size);
    if (status != block_size)
        return -1;
    /* The caller may not be aligned, so drop data that he doesn't want */
    int offset = handle->location & block_mask;
    /* Limit the return length to one block */
    if (length > block_size - offset)
        length = block_size - offset;
    memcpy(buffer, tmp + offset, length);
    /* Return length may be much smaller than they originally wanted */
    return length;
}

static int dev_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    const __bdk_dev_fs_t *dev = handle->fs_state;
    int node = dev_get_node(handle->filename);
    if (node < 0)
        return -1;
    if (!dev->ops->write)
        return -1;

    __bdk_fs_dev_t state;
    state.filename = handle->filename;
    state.location = handle->location;
    state.dev_node = node;
    state.dev_index = dev->dev_index;

    /* Check the alignment of the call  */
    int block_size = dev->ops->block_size;
    int block_mask = block_size - 1;
    bool start_aligned = (state.location & block_mask) == 0;
    bool len_aligned = (length & block_mask) == 0;
    bool aligned = start_aligned && len_aligned;

    if ((block_size <= 1) || aligned)
        return dev->ops->write(&state, buffer, length);

    uint64_t loc = handle->location;
    int write_count = 0;
    while (length)
    {
        state.location = loc;
        /* Do a partial write if the update doesn't start on a block
           boundary or the length is shorter than a block */
        int partial = (loc & block_mask) || (length < block_size);
        int len;
        if (partial) /* Partial block, do a read/modify/write */
        {
            /* Align on a block boundary */
            int offset = loc & block_mask;
            char tmp[block_size];
            state.location &= -block_size;
            if (dev->ops->read(&state, tmp, block_size) != block_size)
                break;
            len = block_size - offset;
            if (len > length)
                len = length;
            memcpy(tmp + offset, buffer, len);
            int w = dev->ops->write(&state, tmp, block_size);
            if (w != block_size)
            {
                if (w > 0)
                    write_count += w;
                break;
            }
        }
        else
        {
            len = length & -block_size;
            int w = dev->ops->write(&state, buffer, len);
            if (w != len)
            {
                if (w > 0)
                    write_count += w;
                break;
            }
        }
        buffer += len;
        length -= len;
        loc += len;
        write_count += len;
    }
    state.location = handle->location;
    return write_count;
}

static int dev_list(const char *path,__bdk_fs_list_callback callback, void *callback_state)
{
    if (NULL == callback) return -1;
    if (1 >= strlen(path)) {
        __bdk_dev_fs_t *dev;
        if (dev_head != dev_tail) {
            dev = dev_head;
            do {
                char buf[20];
                snprintf(buf,sizeof(buf),"n0.%s", dev->dev_name);
                callback(buf,callback_state);
                dev = dev->next;
            } while (dev);
        }
        return 0;
    }
    // Are there subpath?
    return -1;
}

const __bdk_fs_ops_t bdk_fs_dev_ops =
{
    .unlink = NULL,
    .open = dev_open,
    .close = dev_close,
    .read = dev_read,
    .write = dev_write,
    .list = dev_list,
};
