/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <ff.h>

#include "main.h"

extern void bdk_aes128cbc_encrypt(const void *key, void *data, int size, void *iv);

/*
 * Helper functions
 */
static const char *get_basename(const char *filename)
{
	const char *p = filename;

	while (*p++) ; /* find end of line */
	while (*--p != '/' && p != filename) ; /* walk back until '/' or beginning */

	return p == filename && *p != '/' ? p : ++p;
}

static int copy_file(const char *filename, const char *target_dir)
{
	int  rc = -1;
	FILE *sfp;
	FIL  tfp;
	FRESULT res;

	unsigned long long aes_iv[2] = { 0, 0 };
	char fullpath[256];
	char buf[1024];
	int  n;
	UINT count;

	sfp = fopen(filename, "rb");
	if (!sfp)
		goto out;

	/* Get the file's base name */
	const char *base = get_basename(filename);

	snprintf(fullpath, sizeof(fullpath), "%s/%s", target_dir, base);

	res = f_open(&tfp, fullpath, FA_WRITE | FA_CREATE_ALWAYS);
	if (res)
		goto out;

	rc = 0;
	while (0 != (n = fread(buf, 1, sizeof(buf), sfp)))
	{
		if (aes_key[0] | aes_key[1])
		{
			n = (n + 15) & -16;
			bdk_aes128cbc_encrypt(aes_key, buf, n, aes_iv);
		}
		rc = f_write(&tfp, buf, n, &count);
		if (rc || (count != n))
		{
			rc = -1;
			break;
		}
	}

	f_close(&tfp);
out:
	if (sfp)
		fclose(sfp);
	return rc;
}

static int extract_file(const char *filename, const char *target_dir)
{
	int  rc = -1;
	FILE *sfp;
	FIL  tfp;
	FRESULT res;

	char fullpath[256];
	char buf[1024];
	int  n;
	UINT count;

	res = f_open(&tfp, filename, FA_READ);
	if (res)
		goto out;

	/* Get the file's base name */
	const char *base = get_basename(filename);

	snprintf(fullpath, sizeof(fullpath), "%s/%s", target_dir, base);

	sfp = fopen(fullpath, "wb");
	if (!sfp)
		goto out2;

	rc = 0;
	while (FR_OK == (res = f_read(&tfp, buf, sizeof(buf), &count)) && count != 0)
	{
		n = fwrite(buf, 1, count, sfp);
		if (count != n)
		{
			rc = -1;
			break;
		}
	}

	fclose(sfp);
out2:
	f_close(&tfp);
out:
	return rc;
}

static int dir_exists(const char *path)
{
	DIR dp;
	FRESULT res = f_opendir(&dp, path);
	if (res)
		return 0;

	f_closedir(&dp);
	return 1;
}

/*
 * Commands
 */
static int cmd_mkfs(int argc, char **argv, FATFS *fatfs)
{
	argv++; /* skip to first argument */

	if (*argv)
	{
		printf("WARNING: Ignoring arguments for mkfs:");
		while (*argv)
		{
			printf(" %s", *argv);
			argv++;
		}
		printf("\n");
	}

	CHAT("Creating FAT filesystem - ");
	FRESULT res = f_mkfs("DISK_IMG",	/* dummy, not used right now */
						 1,				/* SFD */
						 1);			/* 1 sector allocation size */

	if (res)
	{
		printf("fatfs-tool mkfs: ERROR (%d)\n", res);
		return -1;
	}
	CHAT("OK\n");
	return 0;
}

static int cmd_mkdir(int argc, char **argv, FATFS *fatfs)
{
	argv++; /* skip to first argument */

	while (*argv)
	{
		CHAT("Creating directory %s\n", *argv);

		FRESULT res = f_mkdir(*argv);
		if (res)
		{
			printf("fatfs-tool mkdir: ERROR (%d)\n", res);
			return -1;
		}
		else
			CHAT("OK\n");

		argv++;
	}
	return 0;
}

static int cmd_cp(int argc, char **argv, FATFS *fatfs)
{
	CHAT("Copy files:\n");

	if (argc < 3)
	{
		printf("cp: not enough arguments\n");
		return -1;
	}

	const char *target_dir = argv[argc -1];

	if (!dir_exists(target_dir))
	{
		printf("cp: Target directory %s does not exist. Aborting.\n", target_dir);
		return -1;
	}

	int is_root = *target_dir == '/' && !*(target_dir +1);

	argv++; /* skip to first argument */

	while (argc > 2)
	{
		const char *base_name  = get_basename(*argv);
		CHAT(" * %s -> %s%s%s ", *argv, target_dir, is_root ? "" : "/", base_name);

		if (0 != copy_file(*argv, target_dir))
		{
			printf("fatfs-tool cp: ERROR\n");
			return -1;
		}
		else
		{
			CHAT("OK\n");
		}

		argv++;
		argc--;
	}
	return 0;
}

static int sys_dir_exists(const char *path)
{
	struct stat fstat;

	int ret = stat(path, &fstat);

	return (ret == -1) ? 0 : S_ISDIR(fstat.st_mode);
}

static int cmd_extract(int argc, char **argv, FATFS *fatfs)
{
	CHAT("Extract files:\n");

	if (argc < 3)
	{
		printf("extract: not enough arguments\n");
		return -1;
	}

	const char *target_dir = argv[argc -1];

	if (!sys_dir_exists(target_dir))
	{
		printf("extract: Target directory %s does not exist or is not a directory. Aborting.\n", target_dir);
		return -1;
	}

	argv++; /* skip to first argument */

	while (argc > 2)
	{
		const char *base_name  = get_basename(*argv);
		CHAT(" * %s -> %s/%s ", *argv, target_dir, base_name);

		if (0 != extract_file(*argv, target_dir))
		{
			printf("fatfs-tool extract: ERROR\n");
			return -1;
		}
		else
		{
			CHAT("OK\n");
		}

		argv++;
		argc--;
	}
	return 0;
}

static int cmd_ls(int argc, char **argv, FATFS *fatfs)
{
	CHAT("List files:\n");
	char *path;

	if (1 == argc)
		path = "0:"; /* no arg, use default path */
	else
		path = argv[1];

	if (!dir_exists(path))
	{
		printf("ls: Target directory %s does not exist. Aborting.\n", path);
		return -1;
	}

	DIR dir;
	FILINFO info;
#if _USE_LFN
	char lfn[_MAX_LFN + 1] = {0};
	info.lfname = lfn;
	info.lfsize = sizeof(lfn);
#endif
	FRESULT res = f_findfirst(&dir, &info, path, "*");
	while (FR_OK == res && info.fname[0])
	{
		char *dirstr = info.fattrib & AM_DIR ? "/" : "";
		char *pd = path[strlen(path)-1] == '/' ? "" : "/";
#if _USE_LFN
		printf("%s%s%s%s", path, pd, info.fname, dirstr);
		if (info.lfname[0])
			printf("    (%s%s%s%s)", path, pd, info.lfname, dirstr);
		printf("\n");
#else
		printf("%s%s%s%s\n", path, pd, info.fname, dirstr);
#endif
		res = f_findnext(&dir, &info);
	}

	f_closedir(&dir);
	DWORD free_clusters;
	res = f_getfree(path, &free_clusters, &fatfs);
	if (res == FR_OK)
	{
		printf("\nFree clusters: %ld (%ld blocks)\n",
			free_clusters, free_clusters * fatfs->csize);
	}
	return 0;
}

/*
 * Main handler
 */
static struct cmd_d
{
	const char	*cmd;
	int			(*f)(int argc, char **argv, FATFS *fatfs);
}
cmd_list[] =
{
	{ "mkfs",	cmd_mkfs },
	{ "mkdir",	cmd_mkdir },
	{ "cp",		cmd_cp },
	{ "ls",		cmd_ls },
	{ "extract",	cmd_extract },
	{ NULL,		NULL },
};

int run_command(int argc, char **argv, FATFS *fatfs)
{
	struct cmd_d *cmd = cmd_list;

	while (cmd->cmd)
	{
		if (0 == strcmp(*argv, cmd->cmd))
		{
			if (cmd->f)
				return (*cmd->f)(argc, argv, fatfs);
			return -1;
		}

		cmd++;
	}

	if (!cmd->cmd)
	{
		printf("ERROR: Illegal command '%s'\n", *argv);
		return -1; /* command not found */
	}

	return 0;
}
