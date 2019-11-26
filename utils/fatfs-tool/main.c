/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include <ff.h>
#include <diskio_img_file.h>

#include "cmd.h"
#include "main.h"

/******************************************************************************/

int fatfs_tool_debug = 0;

int verbose = 1;

unsigned long long aes_key[2] = { 0, 0 };

/******************************************************************************/

static void usage()
{
	printf(
		"USAGE: fatfs-tool [-q] [-d] [-m] -i <image_file> command [args]...\n"
		"        -q     	  - Be quiet\n"
		"        -d     	  - Enable debug messages\n"
		"        -i <image_file>  - Image file to use\n"
		"        -e <aes_key>     - Encrypt files as they are copied with AES (32 hex digits)\n"
		"        command	  - Command to execute\n"
		"\n"
		"        Available commands:\n"
		"        cp    src... target_dir   - copy files into filesystem target\n"
		"        ls    target_dir          - list the files in a directory\n"
		"        mkdir target_dir          - Create new directory in target\n"
		"        extract src... target_dir - Extract files from filesystem image to directory\n"
		"        mkfs   		   - Create new FAT filesystem in target\n"
		"       			     WARNING: This will erase all existing data in target file\n"
		);
	exit(-1);
}

int main(int argc, char **argv)
{
	int rc = -1;
	int  ch;
	char *img_name = NULL;
	while (EOF != (ch = getopt(argc, argv, "qdi:e:")))
	{
		switch (ch)
		{
		case 'q':
			verbose = 0;
			break;
		case 'd':
			fatfs_tool_debug = 1;
			break;
		case 'i':
			img_name = optarg;
			break;
		case 'e':
		{
			int count = sscanf(optarg, "%016llx%016llx", &aes_key[0], &aes_key[1]);
			if ((count != 2) || (strlen(optarg) != 32))
				usage();
                        aes_key[0] = __builtin_bswap64(aes_key[0]);
                        aes_key[1] = __builtin_bswap64(aes_key[1]);
			break;
		}
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (!img_name) /* bail if no image has been specified */
	{
		usage();
	}

	if (!*argv) /* bail if no command has been specified */
	{
		usage();
	}

	/* Set the image filename */
	CHAT("Using disk image file '%s'\n", img_name);
	diskio_img_file_set_filename(img_name);

	/* Mount the filesystem image */
	FRESULT res;
	FATFS fatfs;
	res = f_mount(&fatfs, "DISK_IMG", 0);
	if (res)
	{
		printf("ERROR: Could not mount FAT filesystem image %s: res:%d\n",
				img_name, res);
		goto out;
	}

	/* run the command that is left on the command line. */
	rc = run_command(argc, argv, &fatfs);

	if (rc == 0)
		CHAT("Done.\n");
out:
	diskio_img_file_close();
	return (rc) ? 1 : 0;
}
