#include <bdk.h>
#include <ctype.h>
#include <gsc.h>
#include <newport.h>

#define ARRAY_SIZE(arr) (int)(sizeof(arr) / sizeof((arr)[0]))
#define MINMAX(n, percent)	((n)*(100-percent)/100), ((n)*(100+percent)/100)

struct newport_board_info board_info;

void
hexdump(unsigned char *buf, int size)
{
	int i = 0;
	char ascii[20];

	ascii[0] = 0;
	for (i = 0; i < size; i++) {
		if (0 == (i % 16)) {
			if (ascii[0]) {
				ascii[16] = 0;
				printf("  |%s|\n", ascii);
				ascii[0] = 0;
			}
			printf("%08x ", i);
		}
		if (0 == (i % 8))
			printf(" ");
		printf("%02x ", buf[i]);
		ascii[i % 16] = (buf[i] < ' ' || buf[i] > 127) ? '.' : buf[i];
		ascii[(i % 16)+1] = 0;
	}
        for (; i % 16; i++) {
                if (0 == (i % 8))
                        printf(" ");
                printf("   ");
        }
	printf("  |%-16s|\n", ascii);
}

/* System Controller registers */
enum {
	GSC_SC_CTRL0		= 0,
	GSC_SC_CTRL1		= 1,
	GSC_SC_STATUS		= 10,
	GSC_SC_FWCRC		= 12,
	GSC_SC_FWVER		= 14,
};

/* System Controller Control1 bits */
enum {
	GSC_SC_CTRL1_WDTIME	= 4, /* 1 = 60s timeout, 0 = 30s timeout */
	GSC_SC_CTRL1_WDEN	= 5, /* 1 = enable, 0 = disable */
	GSC_SC_CTRL1_BOOT_CHK   = 6, /* 1 = enable alt boot check */
	GSC_SC_CTRL1_WDDIS	= 7, /* 1 = disable boot watchdog */
};

/* System Controller Interrupt bits */
enum {
	GSC_SC_IRQ_PB		= 0, /* Pushbutton switch */
	GSC_SC_IRQ_SECURE	= 1, /* Secure Key erase operation complete */
	GSC_SC_IRQ_EEPROM_WP	= 2, /* EEPROM write violation */
	GSC_SC_IRQ_GPIO		= 4, /* GPIO change */
	GSC_SC_IRQ_TAMPER	= 5, /* Tamper detect */
	GSC_SC_IRQ_WATCHDOG	= 6, /* Watchdog trip */
	GSC_SC_IRQ_PBLONG	= 7, /* Pushbutton long hold */
};

static int
i2c_read(bdk_node_t node, int bus, int addr, int reg, uint8_t *buf, int sz)
{
	int64_t data;
	int i;

	for (i = 0; i < sz; i++) {
		/* NB: can only read 1-4 bytes a call so we just use 1 */
		data = bdk_twsix_read_ia(node, bus, addr, reg + i, 1, 1);
		if (data == -1)
			return -1;
		buf[i] = (uint8_t) data;
	}
	return 0;
}

static int
i2c_write(bdk_node_t node, int bus, uint8_t addr, int reg, unsigned char *buf,
	  int sz)
{
	int i;
	int err;

	for (i = 0; i < sz; i++) {
		/* note: can only write 1-8 bytes a call so we just use 1 */
		err = bdk_twsix_write_ia(node, bus, addr, reg + i, 1, 1,
					 (uint64_t) *(buf + i));
		if (err)
			return err;
	}
	return 0;
}

/* read EEPROM, check for validity, and return baseboard type */
int
gsc_read_eeprom(bdk_node_t node, struct newport_board_info *info)
{
	int i;
	int chksum;
	int type;
	unsigned char *buf = (unsigned char *)info;

	/* read eeprom config section */
	memset(info, 0, sizeof(*info));
	if (i2c_read(node, 0, GSC_EEPROM_ADDR, 0x00, buf, sizeof(*info))) {
		bdk_error("EEPROM: Failed to read EEPROM\n");
		return GW_UNKNOWN;
	}

	/* sanity checks */
	if (info->model[0] != 'G' || info->model[1] != 'W') {
		bdk_error("EEPROM: Invalid Model in EEPROM\n");
		hexdump(buf, sizeof(*info));
		return GW_UNKNOWN;
	}

	/* validate checksum */
	for (chksum = 0, i = 0; i < (int)sizeof(*info)-2; i++)
		chksum += buf[i];
	if ((info->chksum[0] != chksum>>8) ||
	    (info->chksum[1] != (chksum&0xff))) {
		bdk_error("EEPROM: Failed EEPROM checksum\n");
		hexdump(buf, sizeof(*info));
		return GW_UNKNOWN;
	}

	switch (info->model[3]) {
	case '3':
		type = GW630x;
		break;
	default:
		type = GW_UNKNOWN;
		bdk_error("EEPROM: Failed model identification\n");
		hexdump(buf, sizeof(*info));
	}
	return type;
}

/* write EEPROM with proper checksum */
int
gsc_eeprom_update(bdk_node_t node)
{
	int i;
	int chksum;
	uint64_t mac;
	struct newport_board_info *info = &board_info;
	unsigned char *buf = (unsigned char *)info;

	/* update info from fdt */
	strncpy(info->model, bdk_config_get_str(BDK_CONFIG_BOARD_MODEL),
		sizeof(info->model));
	info->serial = atoi(bdk_config_get_str(BDK_CONFIG_BOARD_SERIAL));
	mac = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS);
	for (i = 0; i < 6; i++)
		info->mac[5-i] = (mac >> (i*8)) & 0xff;
	/* update checksum */
	for (chksum = 0, i = 0; i < (int)sizeof(*info)-2; i++)
		chksum += buf[i];
	info->chksum[0] = chksum >> 8;
	info->chksum[1] = chksum & 0xff;

	if (i2c_write(node, 0, GSC_EEPROM_ADDR, 0x00, buf, sizeof(*info))) {
		bdk_error("EEPROM: Failed to write EEPROM\n");
		return -1;
	}

	return 0;
}

/* Hardware Monitor registers */
struct hwmon {
	uint8_t reg;
	const char *name;
	uint32_t low;
	uint32_t high;
};

static struct hwmon hwmon_regs[] = {
	{ 0x00, "temp", 0, 9000 },
	{ 0x02, "vin", 8000, 60000 },
	{ 0x05, "3p3", MINMAX(3300, 10) },
	{ 0x08, "bat", 0, 3300 },
	{ 0x0b, "5p0", MINMAX(5000, 10) },
	{ 0x0e, "core", MINMAX(860, 10) },
	{ 0x11, "cpu1", MINMAX(900, 10) },
	{ 0x14, "cpu2", 0, 0xffffff },
	{ 0x17, "dram", MINMAX(1200, 10) },
	{ 0x1a, "ext_bat", 0, 0xffffff },
	{ 0x1d, "io1", MINMAX(2500, 10) },
	{ 0x20, "io2", MINMAX(1000, 10) },
	{ 0x23, "pcie", MINMAX(1500, 10) },
	{ 0x26, "io3", MINMAX(1800, 10) },
	{ 0x29, "io4", 0, 5000 },
	{ 0, 0, 0, 0 },
};

static struct hwmon hwmon_regs_gw630x[] = {
	{ 0x00, "temp", 0, 9000 },
	{ 0x02, "vin", 8000, 60000 },
	{ 0x05, "3p3", MINMAX(3300, 10) },
	{ 0x0b, "5p0", MINMAX(5000, 10) },
	{ 0x11, "0p9", MINMAX(900, 10) },
	{ 0x0e, "core", MINMAX(860, 10) },
	{ 0x17, "1p2", MINMAX(1200, 10) },
	{ 0x1d, "2p5", MINMAX(2500, 10) },
	{ 0x20, "1p0", MINMAX(1000, 10) },
	{ 0x23, "1p5", MINMAX(1500, 10) },
	{ 0x26, "1p8", MINMAX(1800, 10) },
	{ 0x29, "anl", 0, 5000 },
	{ 0, 0, 0, 0 },
};

int
gsc_hwmon_info(bdk_node_t node, int model)
{
	uint8_t buf[3];
	uint32_t val;
	struct hwmon *r;

	switch (model) {
	case GW630x:
		r = hwmon_regs_gw630x;
		break;
	default:
		r = hwmon_regs;
		break;
	}

	for (; r->name; r++) {
		printf("%-8s: ", r->name);
		memset(buf, 0, sizeof(buf));
		if (i2c_read(node, 0, GSC_HWMON_ADDR, r->reg, buf,
		    3))
		{
			printf("fRD\n");
			continue;
		}
		if (r->reg == 0) {
			val = buf[0] | buf[1]<<8;
			if (val > 0x8000)
				val -= 0xffff;
		} else
			val = buf[0] | (buf[1]<<8) | (buf[2]<<16);
		if (val == 0xffffff)
			printf("invalid\n");
		else if (val < r->low)
			printf("%d - Failed Low: %d\n", val, r->low);
		else if (val > r->high)
			printf("%d - Failed High: %d\n", val, r->high);
		else {
			if (r->reg == 0)
				printf("%d.%dC\n", val / 10, val % 10);
			else
				printf("%d.%03dV\n", val / 1000, val % 1000);
		}
	}
	return 0;
}

int
gsc_init(bdk_node_t node)
{
	struct newport_board_info *info = &board_info;
	unsigned char buf[16];
	char serial_str[8];
	char revision_str[8] = { 0 };
	char rev_pcb = 'A'; /* PCB revision */
	int  rev_bom = 0; /* BOM revision */
	int i;

	/*
	 * On a board with a missing/depleted backup battery for GSC, the
	 * board may be ready to probe the GSC before its firmware is
	 * running.  We will wait here indefinately for the GSC/EEPROM.
	 */
	for (i = 2000; i > 0; i--) {
		if (!i2c_read(node, 0, GSC_SC_ADDR, 0, buf, 16))
			break;
		bdk_wait_usec(1000);
	}
	if (!i) {
		bdk_error("Failed probing GSC\n");
		return -1;
	}

	/* Default color, Reset scroll region and goto bottom */
	printf("\33[0m\33[1;r\33[100;1H\n\n\n");
	printf("Gateworks Newport SPL (%s)\n\n", bdk_version_string());
	printf("GSC     : v%d", buf[GSC_SC_FWVER]);
	printf(" 0x%04x", buf[GSC_SC_FWCRC] | buf[GSC_SC_FWCRC+1]<<8);
	printf(" WDT:%sabled", (buf[GSC_SC_CTRL1] & (1<<GSC_SC_CTRL1_WDEN))
		? "en" : "dis");
	if (buf[GSC_SC_STATUS] & (1 << GSC_SC_IRQ_WATCHDOG)) {
		printf(" WDT_RESET");
	}
	if (!i2c_read(node, 0, GSC_HWMON_ADDR, 0, buf, 2)) {
		int ui = buf[0] | buf[1]<<8;
		if (ui > 0x8000)
			ui -= 0xffff;
		printf(" board temp:%dC", ui / 10);
	}
	printf("\n");

	/* Display RTC */
	if (!i2c_read(node, 0, GSC_RTC_ADDR, 0, buf, 6)) {
		printf("RTC     : %d\n",
			buf[0] | buf[1]<<8 | buf[2]<<16 | buf[3]<<24);
	}

	int model = gsc_read_eeprom(node, info);
	if (GW_UNKNOWN == model)
		return -2;

	printf("Model   : %s\n", info->model);
	printf("MFGDate : %02x-%02x-%02x%02x\n",
		info->mfgdate[0], info->mfgdate[1],
		info->mfgdate[2], info->mfgdate[3]);
	printf("Serial  : %d\n", info->serial);

	/* store board/serial */
	bdk_config_set_str(info->model, BDK_CONFIG_BOARD_MODEL);
	sprintf(serial_str, "%d", info->serial);
	bdk_config_set_str(serial_str, BDK_CONFIG_BOARD_SERIAL);

	/* store MAC addr */
	int macno = (info->macno == 0xff) ? 2 : info->macno;
	bdk_config_set_int(macno, BDK_CONFIG_MAC_ADDRESS_NUM);
	uint64_t mac = 0;
	for (i = 5; i >= 0; i--)
		mac |= (uint64_t)info->mac[i] << ((5-i)*8);
	bdk_config_set_int(mac, BDK_CONFIG_MAC_ADDRESS);

	/* determine BOM revision from model */
	for (i = strlen(info->model) - 1; i > 0; i--) {
		if (info->model[i] == '-')
			break;
		if (info->model[i] >= '1' && info->model[i] <= '9') {
			rev_bom = info->model[i] - '0';
			break;
		}
	}

	/* determine PCB revision from model */
	for (i = strlen(info->model) - 1; i > 0; i--) {
		if (info->model[i] == '-')
			break;
		if (info->model[i] >= 'A') {
			rev_pcb = info->model[i];
			break;
		}
	}
	if (rev_bom)
		sprintf(revision_str, "%c.%d", rev_pcb, rev_bom);
	else
		sprintf(revision_str, "%c", rev_pcb);
	bdk_config_set_str(revision_str, BDK_CONFIG_BOARD_REVISION);

	return 0;
}

/*
 * dtb based on model:
 *   try full first        (ie gw6300-b.1)
 *   try pcb level next    (ie gw6300-b)
 *   try base model next   (ie gw6300)
 *   try generic base next (ie gw630x)
 *   try generic base last (ie gw63xx)
 */
const char *
gsc_get_dtb_name(bdk_node_t node, int level)
{
	static char file[64];
	char base[32];
	char rev_pcb = 'a'; /* PCB revision */
	int  rev_bom = 0; /* BOM revision */
	char *p;
	int i;

	/* determine base model from model */
	const char *model = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
	for (i = 0;i < (int)strlen(model) && i < ((int)sizeof(base) - 1);i++) {
		char c = model[i];
		base[i] = (c >= 'A' && c <= 'Z') ? (c+32) : c;
	}
	base[i+1] = 0;
	p = strchr(base, '-');
	if (p)
		*p = 0;

	/* determine BOM revision from model */
	for (i = strlen(model); i > 0; i--) {
		if (model[i] == '-')
			break;
		if (model[i] >= '1' && model[i] <= '9') {
			rev_bom = model[i] - '0';
			break;
		}
	}

	/* determine PCB revision from model */
	for (i = sizeof(model) - 1; i > 0; i--) {
		if (model[i] == '-')
			break;
		if (model[i] >= 'A' && model[i] <= 'Z') {
			rev_pcb = model[i] + 32;
			break;
		}
	}

	switch (level) {
	case 0: /* full model first (ie GW6300-A.1) */
		if (rev_bom)
			sprintf(file, "%s-%c.%d", base, rev_pcb, rev_bom);
		else
			sprintf(file, "%s-%c", base, rev_pcb);
		break;
	case 1: /* look for model and pcb rev (ie GW6300-A) */
		sprintf(file, "%s-%c", base, rev_pcb);
		break;
	case 2: /* look for base model (ie GW6300) */
		sprintf(file, "%s", base);
		break;
	case 3: /* look for generic model (ie gw630x) */
		base[5] = 'x';
		sprintf(file, "%s", base);
		break;
	case 4: /* look for more generic model (ie gw63xx) */
		base[4] = 'x';
		sprintf(file, "%s", base);
		break;
	case 5: /* look for more generic model (ie gw6xxx) */
		base[3] = 'x';
		sprintf(file, "%s", base);
		break;
	default: /* give it up */
		return NULL;
	}
	return file;
}

int
gsc_sleep(bdk_node_t node, unsigned long secs)
{
	unsigned char reg;

	printf("GSC Sleeping for %ld seconds\n", secs);

	reg = (secs >> 24) & 0xff;
	if (i2c_write(node, 0, GSC_SC_ADDR, 9, &reg, 1))
		goto error;
	reg = (secs >> 16) & 0xff;
	if (i2c_write(node, 0, GSC_SC_ADDR, 8, &reg, 1))
		goto error;
	reg = (secs >> 8) & 0xff;
	if (i2c_write(node, 0, GSC_SC_ADDR, 7, &reg, 1))
		goto error;
	reg = secs & 0xff;
	if (i2c_write(node, 0, GSC_SC_ADDR, 6, &reg, 1))
		goto error;
	if (i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
		goto error;
	reg |= (1 << 2);
	if (i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
		goto error;
	reg &= ~(1 << 2);
	reg |= 0x3;
	if (i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
		goto error;

	return 0;

error:
	printf("i2c error\n");
	return -1;
}

int
gsc_boot_wd_disable(bdk_node_t node, bool leave_enabled)
{
	uint8_t reg;

	//printf("%s GSC boot watchdog\n", leave_enabled ?
	//	"Clearing" : "Disabling");
	if (!i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1)) {
		reg |= (1 << GSC_SC_CTRL1_WDDIS);
		reg &= ~(1 << GSC_SC_CTRL1_BOOT_CHK);
		if (leave_enabled)
			reg |= (1 << GSC_SC_CTRL1_BOOT_CHK);
		if (!i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
			return 0;
	}
	printf("Error: could not write to GSC Watchdog\n");
	return -1;
}

int
gsc_watchdog_config(bdk_node_t node, int timeout)
{
	unsigned char reg;

	if (timeout) {
		if (i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
			return -1;
		reg &= ~((1 << GSC_SC_CTRL1_WDEN) | (1 << GSC_SC_CTRL1_WDTIME));
		if (timeout == 60)
			reg |= (1 << GSC_SC_CTRL1_WDTIME);
		else
			timeout = 30;
		reg |= (1 << GSC_SC_CTRL1_WDEN);
		if (i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
			return -1;
		printf("GSC Watchdog enabled with timeout=%d seconds\n",
		       timeout);
	} else {
		if (i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
			return -1;
		reg &= ~((1 << GSC_SC_CTRL1_WDEN) | (1 << GSC_SC_CTRL1_WDTIME));
		if (i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_CTRL1, &reg, 1))
			return -1;
		printf("GSC Watchdog disabled\n");
	}
	return 0;
}

static int
parse_args(const char *str, char **argv, int maxargs)
{
	int argc = 0;
	char *p;
	char line[64];
	char *rest = line;

	if (str) {
		strncpy(line, str, sizeof(line));
		while ((p = strtok_r(rest, " ", &rest)) && argc < maxargs)
			argv[argc++] = p;
		argv[argc] = 0;
	}

	return argc;
}

static void
cmd_usage(void)
{
	printf("gsc sleep [seconds] - sleep num of secs (defaults to 2)\n");
	printf("gsc wd [enable|disable] [timeout] - configure watchdog\n");
	printf("gsc hwmon\n");
	printf("exit|quit - exit menu\n\n");
}

int
gsc_program(bdk_node_t node)
{
	const char *r[5];
	int chksum;
	char *n;
	int addr = 0;
	int i, j;
	struct newport_board_info *info = &board_info;
	unsigned char *buf = (unsigned char *)info;

	printf("***\n");
	printf("*** GATEWORKS MANUFACTURING MODE\n");
	printf("***\n");

	/* input 5 lines */
	for (i = 0; i < 5; i++)
		r[i] = bdk_readline(" > ", NULL, 0);
	/* parse them */
	for (i = 0; i < 5; i++) {
		n = (char *)r[i];
		addr = strtol(n, &n, 16);
		for (j = 0; j < 16 && n; j++) {
			buf[addr] = strtol(n, &n, 16);
			addr++;
		}
	}

	/* validate checksum */
	for (chksum = 0, i = 0; i < (int)sizeof(*info)-2; i++)
		chksum += buf[i];
	if ((info->chksum[0] != chksum>>8) ||
	    (info->chksum[1] != (chksum&0xff))) {
		bdk_error("EEPROM: Failed EEPROM checksum\n");
		return -2;
	}

	/* write */
	if (i2c_write(node, 0, GSC_EEPROM_ADDR, 0x00, buf, sizeof(*info))) {
		bdk_error("EEPROM: Failed to write EEPROM\n");
		return -1;
	}

	return 0;
}

void
menu_gsc(bdk_menu_t *parent, char key, void *arg)
{
	bdk_node_t node = bdk_numa_master();
	struct newport_board_info *info = &board_info;
	int argc;
	char *args[10];
	char line[64];

	if (key == 'P') {
		gsc_program(node);
		bdk_wait_usec(2000000);
		gsc_hwmon_info(node, gsc_read_eeprom(node, info));
		return;
	}

	cmd_usage();
	line[0] = 0;
	while (1) {
		char **argv = args;
		const char *r;

		r = bdk_readline("GSC > ", NULL, 0);
		if (r && *r)
			strncpy(line, r, sizeof(line));
		argc = parse_args(line, args, sizeof(args)/sizeof(char*));
		if (!argc)
			return;
		else if (strcasecmp(argv[0], "exit") == 0)
			return;
		else if (strcasecmp(argv[0], "quit") == 0)
			return;
		/* ignore cmd */
		argc--;
		argv++;
		if (argc < 1)
			cmd_usage();
		else if (strcasecmp(argv[0], "hwmon") == 0) {
			gsc_hwmon_info(node, gsc_read_eeprom(node, info));
		} else if (strcasecmp(argv[0], "sleep") == 0) {
			unsigned long secs = 2;
			if (argc == 2)
				secs = strtoull(argv[1], 0, 0);
			gsc_sleep(node, secs);
		} else if (strcasecmp(argv[0], "wd") == 0) {
			if (argc < 2) {
				uint8_t sc_ctrl;
				if (!i2c_read(node, 0, GSC_SC_ADDR,
					      GSC_SC_CTRL1, &sc_ctrl, 1))
				{
					printf("GSC Watchdog %sabled\n",
					(sc_ctrl & (1<<GSC_SC_CTRL1_WDEN)) ?
						"en" : "dis");
				}
			} else if (strcasecmp(argv[1], "enable") == 0) {
				int timeout = 30;
				if (argc == 3)
					timeout = strtoull(argv[2], 0, 0);
				gsc_watchdog_config(node, timeout);
			} else if (strcasecmp(argv[1], "disable") == 0)
				gsc_watchdog_config(node, 0);
			else
				cmd_usage();
		} else
			cmd_usage();
	}
}
