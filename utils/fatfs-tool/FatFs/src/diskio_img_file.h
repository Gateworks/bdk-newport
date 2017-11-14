#ifndef _DISKIO_IMG_FILE_H__
#define _DISKIO_IMG_FILE_H__

#include "diskio.h"

#include <stdio.h> /* for printf in DEBUG */

void diskio_img_file_set_filename(const char *img_name);
int  diskio_img_file_close();

DSTATUS diskio_img_file_initialize();
DRESULT diskio_img_file_read(BYTE *buff, DWORD sector, UINT count);
DRESULT diskio_img_file_write(const BYTE *buff, DWORD sector, UINT count);
DRESULT diskio_img_file_ioctl(BYTE pdrv, BYTE cmd, void *buff);

#endif /* _DISKIO_IMG_FILE_H__ */
