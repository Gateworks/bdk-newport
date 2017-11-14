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
#include <fcntl.h>

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_FATFS);

/* This is a BDK wrapper around FatFs for accessing files in a FAT filesystem. */

static void *fatfs_open(const char *name, int flags)
{
    BYTE mode = 0;
    FIL *fp = (FIL *) malloc(sizeof(FIL));
    if (!fp)
        return NULL;

    switch (flags & 3)
    {
        case O_RDONLY: mode = FA_READ;            break;
        case O_WRONLY: mode =           FA_WRITE; break;
        case O_RDWR:   mode = FA_READ | FA_WRITE; break;
        default:
            bdk_warn("FatFs: Unsupported flag %04x. Using default read/write.\n", flags);
            mode = FA_READ | FA_WRITE;
            break;
    }
    if (flags & O_CREAT)
    {
        mode |= FA_CREATE_ALWAYS;
    }

    FRESULT rc = f_open(fp, name, mode);
    return rc ? NULL : (void*) fp;
}

static int fatfs_close(__bdk_fs_file_t *handle)
{
    FIL *fp = handle->fs_state;
    if (!fp)
    {
        return 0;
    }

    FRESULT rc = f_close(fp);
    free(fp);
    return rc ? -1 : 0;
}

static int fatfs_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    UINT count;
    FIL *fp = handle->fs_state;
    if (!fp)
    {
        return 0;
    }

    FRESULT rc = f_read(fp, buffer, length, &count);
    return rc ? -1 : (int) count;
}

static int fatfs_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    UINT count;
    FIL *fp = handle->fs_state;
    if (!fp)
    {
        return 0;
    }

    FRESULT rc = f_write(fp, buffer, length, &count);
    return rc ? -1 : (int) count;
}

static int fatfs_unlink(const char *name)
{
    return f_unlink(name);
}

/* Forward declaration for fatfs_list */
static int  fatfs_list(const char *path,__bdk_fs_list_callback callback, void *callback_state);

static const __bdk_fs_ops_t bdk_fs_fatfs_ops =
{
    .stat = NULL,
    .unlink = fatfs_unlink,
    .open = fatfs_open,
    .close = fatfs_close,
    .read = fatfs_read,
    .write = fatfs_write,
    .list = fatfs_list,
};

static const char* const volstr[] = {_VOLUME_STRS};
_Static_assert( _VOLUMES == (sizeof(volstr)/sizeof(volstr[0])), "Mismatch between _VOLUMES and _VOLUME_STRS");

static FATFS *fatfs_ctl[_VOLUMES]; /* FATFS handles for all defined volumes */
#define _FATFSCTL_SIZE (sizeof(*fatfs_ctl[0]))
static uint32_t mountmask = 0;
int __bdk_fs_fatfs_init(void)
{

    /* Go through all defined volumes and lazy-mount them. Lazy mounting will
     * always succeed. The volume will be hard-mounted later when the volume
     * will be first accessed via another operation. Any errors will be
     * generated at that point.
     */

    for (int i = 0; i < _VOLUMES; i++)
    {
        char volume_id[16];
        if ((i < DRV_USB0) || (i > DRV_USB2)) {
	    if (NULL != (fatfs_ctl[i] = calloc(1,_FATFSCTL_SIZE))) {
                snprintf(volume_id, sizeof(volume_id), "%s:", volstr[i]);
                f_mount(fatfs_ctl[i], volume_id, 0);
                mountmask |= (1<<i);
            }
        }
    }

    /* Initialize the FATFS disk IO layer. */
    if (-1 == fatfs_diskio_init())
    {
        bdk_warn("FatFs: Could not initialize disk IO layer.\n");
    }

    return bdk_fs_register("/fatfs/", &bdk_fs_fatfs_ops);
}

void __bdk_fs_fatfs_usbnotify(int drvIndex, int available)
{ /* Poor mans automounter
  ** It is called by usb proper when mass storage devices change
  ** availability or media
  */
    int pdrv = drvIndex + DRV_USB0;
    if (pdrv > DRV_USB2) return; /* There are more indexes then usb drives
                                    ... fatfs can digest */
    char volume_id[16];
    snprintf(volume_id, sizeof(volume_id), "%s:", volstr[pdrv]);
    if (available) {
	if (NULL == fatfs_ctl[pdrv])
            fatfs_ctl[pdrv] = calloc(1,_FATFSCTL_SIZE);
	if (fatfs_ctl[pdrv] ) {
            // Mass storage device became available
            // - reset its interface to blockio
            // - do lazy mount
            disk_usbnotify(drvIndex, available);
            f_mount(fatfs_ctl[pdrv], volume_id, 0);
            mountmask |= (1<<pdrv);
	}
    } else {
        // device is no longer there
        // - unmount
        // - reset blockio underneath
	if (fatfs_ctl[pdrv] ) {
            f_mount(NULL, volume_id,1);
            mountmask &= ~(1<<pdrv);
            free(fatfs_ctl[pdrv]);
            fatfs_ctl[pdrv] = NULL;
        }
	disk_usbnotify(drvIndex, available);

    }
    printf("\n/fatfs/%s %savailable\n", volume_id, (available) ? "" : "un");
}


static int  fatfs_list(const char *path,__bdk_fs_list_callback callback, void *callback_state)
{
    if (NULL == callback) return -1;
    if (1 >= strlen(path)) {
        // List volumes
        uint32_t tmask = 1;
        for(int i = 0; i < _VOLUMES;tmask <<=1, i++) {
            if (!(mountmask & tmask) && (fatfs_ctl[i] == NULL)) continue;
            char volume_id[16];
            snprintf(volume_id, sizeof(volume_id), "%s:%c", volstr[i],
                     !(mountmask & tmask) ||  (fatfs_ctl[i] == NULL)  ? '?' : ' ');
            volume_id[sizeof(volume_id)-1] = '\0';
            callback(volume_id,callback_state);
        }
        return 0;
    } else {
        DIR dir;
        FILINFO fno;
        char *buf;
/* Temp buffer is used to:
** - build temporary path name for fstat and opendir
** - to form output lines to be printed or passed to external formatter
** Conveniently all and any path manipulation happens before output.
*/
#define _OUTBUF_SIZE 256
#if _USE_LFN
        // Allocate two work areas in one chunk
        // _OUTBUF_SIZE of it is used for output buffer
        // _MAX_LFN bytes at the end is used to retrieve long file names from libfatfs
        buf = malloc(_OUTBUF_SIZE + _MAX_LFN+1);
        fno.lfname = &buf[_OUTBUF_SIZE];
        fno.lfsize = _MAX_LFN+1;
#else
       buf = malloc(_OUTBUF_SIZE);
#endif
       if (NULL == buf) return -1;

       // Next snippet does two things as both require looking at path
       // - Root directory has no fstat. Its name ends either with ":" or ":/"
       // - In addition we need to strip trailing slash, opendir does not handle it for non-root directories
        bool mustbedir = false;
        int lpath = strlen(path);
        memcpy(buf,path,lpath+1);
        if (path[lpath-1] == '/') {
            lpath--;
            buf[lpath] = '\0'; // strip trailing slash from the path
            mustbedir = true;
        }
        if  (path[lpath-1] != ':') {
            if (FR_OK != f_stat(buf,&fno)) {
                free(buf);
                return -1;
            }
        } else {
            fno.fattrib = AM_DIR; // f_stat for root directory would fail
                                  // ignore result and fake directory attribute
        }

        if (fno.fattrib & AM_DIR) {
            // Directory - list names, append trailing slash to subdirectory names
            if (FR_OK == f_opendir(&dir,buf)) {
                while(FR_OK == f_readdir(&dir,&fno)) {
                    if (0 == fno.fname[0]) break;
                    int l;
#if _USE_LFN
                    if (fno.lfname[0] ) {
                        l = strlen(fno.lfname);
                        memcpy(buf, fno.lfname,l);
                    } else {
                        l = strlen(fno.fname);
                        memcpy(buf, fno.fname,l);
                    }
#else
                    l = strlen(fno.fname);
                    memcpy(buf, fno.fname,l);
#endif
                    if (fno.fattrib & AM_DIR) {
                        buf[l] = '/';
                        l++;
                    }
                    buf[l] = '\0';
                    callback(buf,callback_state);
                }
                f_closedir(&dir);
            }
        } else if (!mustbedir) {
            // Single file - output size and details
            snprintf(buf,_OUTBUF_SIZE,
                     "%s Size:%u Time:%u/%02u/%02u, %02u:%02u Attributes: -%c%c%c%c",
                     path,
                     (unsigned int) fno.fsize,
                     (fno.fdate >> 9) + 1980, fno.fdate >> 5 & 15, fno.fdate & 31,
                     fno.ftime >> 11, fno.ftime >> 5 & 63,
                     /*(fno.fattrib & AM_DIR) ? 'D' : '-',*/
                     (fno.fattrib & AM_RDO) ? 'R' : '-',
                     (fno.fattrib & AM_HID) ? 'H' : '-',
                     (fno.fattrib & AM_SYS) ? 'S' : '-',
                     (fno.fattrib & AM_ARC) ? 'A' : '-');

            callback(buf,callback_state);
        }
        free(buf);
#undef _OUTBUF_SIZE
    }
    return 0;
}
