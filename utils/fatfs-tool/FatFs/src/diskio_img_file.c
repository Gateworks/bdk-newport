#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "integer.h"
#include "diskio_img_file.h"

#define SECTOR_SIZE		512

static FILE       *img_fp        = NULL;
static const char *img_file_name = NULL;

/*
 * API used by main app
 */
void diskio_img_file_set_filename(const char *img_name)
{
	if (img_file_name)
	{
		DEBUG("WARNING: Filename already set to %s. Ignoring request for %s\n",
				img_file_name, img_name);
	}
	img_file_name = img_name; /* for debug messages later */
}

int diskio_img_file_close()
{
	if (!img_fp)
	{
		printf("WARNING: img_fp NULL in diskio_img_file_close(). Ignoring.\n");
		return 0;
	}

	DEBUG("Closing file %s: img_fp:%p\n", img_file_name, img_fp);
	if (EOF == fclose(img_fp))
	{
		fprintf(stderr, "ERROR: Could not close image file %s (%s)\n", img_file_name, strerror(errno));
		return -1;
	}

	img_fp        = NULL;
	img_file_name = "";
	return 0;
}

/*
 * API used by diskio.c
 */

DSTATUS diskio_img_file_initialize()
{
	DEBUG("INITIALIZE with file %s: img_fp:%p\n", img_file_name, img_fp);
	if (img_fp)
	{
		return RES_OK; /* already open */
	}

	img_fp = fopen(img_file_name, "r+b");
	if (!img_fp)
	{
		fprintf(stderr, "ERROR: Could not open image file %s (%s)\n", img_file_name, strerror(errno));
		return RES_NOTRDY;
	}
	return RES_OK;
}

DRESULT diskio_img_file_read(BYTE *buff, DWORD sector, UINT count)
{
	DWORD pos = sector * SECTOR_SIZE;

	DEBUG("READ: buff:%p - sector:%lu - count:%u\n", buff, sector, count);
	if (0 != fseek(img_fp, pos, SEEK_SET))
	{
		fprintf(stderr, "ERROR: Could not seek sector %lu from file %s (%s)\n",
				sector, img_file_name, strerror(errno));
		return RES_ERROR;
	}

	if (1 != fread(buff, count * SECTOR_SIZE, 1, img_fp))
	{
		fprintf(stderr, "ERROR: Could not read sector %lu from file %s (%s)\n",
				sector, img_file_name, strerror(errno));
		return RES_ERROR;
	}

	return RES_OK;
}

DRESULT diskio_img_file_write(const BYTE *buff, DWORD sector, UINT count)
{
	DWORD pos = sector * SECTOR_SIZE;

	DEBUG("WRITE: buff:%p - sector:%lu - count:%u\n", buff, sector, count);
	if (0 != fseek(img_fp, pos, SEEK_SET))
	{
		fprintf(stderr, "ERROR: Could not seek sector %lu from file %s (%s)\n",
				sector, img_file_name, strerror(errno));
		return RES_ERROR;
	}

	if (1 != fwrite(buff, count * SECTOR_SIZE, 1, img_fp))
	{
		fprintf(stderr, "ERROR: Could not write sector %lu to file %s (%s)\n",
				sector, img_file_name, strerror(errno));
		return RES_ERROR;
	}

	return RES_OK;
}

DRESULT diskio_img_file_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
	DRESULT res = RES_OK;

	DEBUG("IOCTL: pdrv:%d - cmd:%d - buff:%p\n", pdrv, cmd, buff);

	switch (cmd)
	{
		case CTRL_SYNC:
			if (0 != fflush(img_fp))
				res = RES_ERROR;
			break;

		case GET_SECTOR_COUNT:
			if (0 != fseek(img_fp, 0L, SEEK_END))
			{
				res = RES_ERROR;
				break;
			}
			*((DWORD *) buff) = ftell(img_fp) / SECTOR_SIZE;
			break;

		case GET_BLOCK_SIZE:
			*((DWORD *) buff) = 1; /* non flash memory */
			break;

		default:
			printf("WARNING: Unhandled ioctl() command %d in diskio_img_file_ioctl()\n", cmd);
			return RES_PARERR;
	}
	return res;
}
