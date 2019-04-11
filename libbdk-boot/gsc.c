#include <bdk.h>
#include <ctype.h>
#include <gsc.h>
#include <newport.h>
#include <libbdk-arch/bdk-csrs-gpio.h>

#define ARRAY_SIZE(arr) (int)(sizeof(arr) / sizeof((arr)[0]))
#define MINMAX(n, percent)	((n)*(100-percent)/100), ((n)*(100+percent)/100)

struct newport_board_info board_info;
int board_model = GW_UNKNOWN;

struct newport_board_config board_configs[] = {
	/* GW610x */
	{
		.qlm = {
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
		},
		.skt = {
			/* qlm, skt, defmode, optmode */
			{ 3, "J6", "PCI", "SATA,USB3" },
		},
		/* serial */
		.gpio_uart_hd = -1,
		.gpio_uart_term = -1,
		.gpio_uart_rs485 = -1,
		/* LED */
		.gpio_ledgrn = 31,
		.gpio_ledred = 14,
		/* misc */
		.gpio_usben = -1,
		.gpio_satasel = -1,
		.gpio_usb2sel = -1,
		.gpio_usb3sel = 5,
		.gpio_usb3sel_pol = 1,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 1,
		.gpio_mezz_pwrdis = -1,
		.gpio_mezz_irq = -1,
		.mmc_devs = 2,
		.ext_temp = 1,
	},

	/* GW620x */
	{
		.qlm = {
			/* PCIe Gen2 (default) or USB3.0 */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_SGMII_1X1, 1250, BDK_QLM_CLK_COMMON_1 },
			/* Unused */
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
		},
		.skt = {
			/* qlm, skt, defmode, optmode */
			{ 0, "J6", "PCI", "USB3" },
			{ 3, "J8", "PCI", "SATA" },
		},
		/* serial */
		.gpio_uart_hd = 15,
		.gpio_uart_term = 16,
		.gpio_uart_rs485 = 17,
		/* LED */
		.gpio_ledgrn = 31,
		.gpio_ledred = 14,
		/* misc */
		.gpio_usben = 18,
		.gpio_satasel = -1,
		.gpio_usb2sel = -1,
		.gpio_usb3sel = 19,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 1,
		.gpio_mezz_pwrdis = -1,
		.gpio_mezz_irq = -1,
		.mmc_devs = 2,
		.ext_temp = 1,
	},

	/* GW630x */
	{
		.qlm = {
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_SGMII_1X1, 1250, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or USB3.0 */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
		},
		.skt = {
			/* qlm, skt, defmode, optmode */
			{ 0, "J9", "PCI", NULL },
			{ 3, "J10", "PCI", "SATA" },
			{ 2, "J11", "PCI", "USB3" },
		},
		/* serial */
		.gpio_uart_hd = 15,
		.gpio_uart_term = 16,
		.gpio_uart_rs485 = 17,
		/* LED */
		.gpio_ledgrn = 31,
		.gpio_ledred = 14,
		/* misc */
		.gpio_usben = 18,
		.gpio_satasel = -1,
		.gpio_usb2sel = -1,
		.gpio_usb3sel = 19,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 1,
		.gpio_mezz_pwrdis = 28,
		.gpio_mezz_irq = 29,
		.mmc_devs = 2,
		.ext_temp = 1,
	},

	/* GW640x */
	{
		.qlm = {
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_QSGMII_4X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_1X1, 5000, BDK_QLM_CLK_COMMON_1 },
		},
		.skt = {
			/* qlm, skt, defmode, optmode */
			{ 0, "J9", "PCI", NULL },
			{ 3, "J10", "PCI", "SATA,USB2" },
			{ 2, "J11", "PCI", NULL },
		},
		/* serial */
		.gpio_uart_hd = 15,
		.gpio_uart_term = 16,
		.gpio_uart_rs485 = 17,
		/* LED */
		.gpio_ledgrn = 31,
		.gpio_ledred = 14,
		/* misc */
		.gpio_usben = 18,
		.gpio_satasel = -1,
		.gpio_usb2sel = 20,
		.gpio_usb3sel = -1,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 1,
		.gpio_mezz_pwrdis = 28,
		.gpio_mezz_irq = 29,
		.mmc_devs = 2,
		.ext_temp = 1,
	},
};

struct newport_board_config *gsc_get_board_config(void) {
	if (board_model != GW_UNKNOWN)
		return &board_configs[board_model];
	return NULL;
}

struct newport_board_info *gsc_get_board_info(void) {
	return &board_info;
}

int gsc_get_board_model(void) {
	return board_model;
}

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
	GSC_SC_WP		= 15,
	GSC_SC_RST_CAUSE	= 16,
	GSC_SC_THERM_PROTECT	= 19,
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

/* System Controller WP bits */
enum {
	GSC_SC_WP_ALL		= 0, /* Write Protect All EEPROM regions */
	GSC_SC_WP_BOARDINFO	= 1, /* Write Protect Board Info region */
};
#define GSC_WP_PASSWD		0x58
#define GSC_WP_PASSWD_MASK	0xF8

/* System Controller Reset Cause */
enum {
	GSC_SC_RST_CAUSE_VIN		= 0,
	GSC_SC_RST_CAUSE_PB		= 1,
	GSC_SC_RST_CAUSE_WDT		= 2,
	GSC_SC_RST_CAUSE_CPU		= 3,
	GSC_SC_RST_CAUSE_TEMP_LOCAL	= 4,
	GSC_SC_RST_CAUSE_TEMP_REMOTE	= 5,
	GSC_SC_RST_CAUSE_SLEEP		= 6,
	GSC_SC_RST_CAUSE_BOOT_WDT	= 7,
	GSC_SC_RST_CAUSE_BOOT_WDT_MAN	= 8,
	GSC_SC_RST_CAUSE_SOFT_PWR	= 9,
	GSC_SC_RST_CAUSE_MAX		= 10,
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

/* read EEPROM:
 * - read EEPROM and check for EEPROM validity
 * - init BDK variables (BDK_CONFIG_BOARD_MODEL, BDK_CONFIG_BOARD_SERIAL,
 *   and BDK_CONFIG_BOARD_REVISION)
 * - return baseboard type
 */
int
gsc_read_eeprom(bdk_node_t node)
{
	struct newport_board_info *info = &board_info;
	int i;
	int chksum;
	int type;
	unsigned char *buf = (unsigned char *)info;
	char serial_str[8];
	char revision_str[8] = { 0 };
	char rev_pcb = 'A'; /* PCB revision */
	int  rev_bom = 0; /* BOM revision */
	int retries = 3;

	/* read eeprom config section */
retry:
	memset(info, 0, sizeof(*info));
	if (i2c_read(node, 0, GSC_EEPROM_ADDR, 0x00, buf, sizeof(*info))) {
		bdk_error("EEPROM: Failed to read EEPROM\n");
		return GW_UNKNOWN;
	}

	/* validate checksum */
	for (chksum = 0, i = 0; i < (int)sizeof(*info)-2; i++)
		chksum += buf[i];
	if ((info->chksum[0] != chksum>>8) ||
	    (info->chksum[1] != (chksum&0xff))) {
		bdk_error("EEPROM: Failed EEPROM checksum\n");
		hexdump(buf, sizeof(*info));
		if (retries--)
			goto retry;
		return GW_UNKNOWN;
	}

	/* sanity checks */
	if (info->model[0] != 'G' || info->model[1] != 'W') {
		bdk_error("EEPROM: Invalid Model in EEPROM\n");
		hexdump(buf, sizeof(*info));
		return GW_UNKNOWN;
	}

	switch (info->model[3]) {
	case '1':
		type = GW610x;
		break;
	case '2':
		type = GW620x;
		break;
	case '3':
		type = GW630x;
		break;
	case '4':
		type = GW640x;
		break;
	default:
		type = GW_UNKNOWN;
		bdk_error("EEPROM: Failed model identification\n");
		hexdump(buf, sizeof(*info));
	}

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

	/* board revision specific changes */
	board_model = type;
	struct newport_board_config *cfg = gsc_get_board_config();

	/* modify board info from the default struct based on model/revision */
	switch(type) {
	case GW610x:
		break;
	case GW620x:
		break;
	case GW630x:
		switch(rev_pcb) {
		case 'A':
			info->qlm[0] = 0xff;
			info->qlm[1] = 0xff;
			info->qlm[2] = 0xff;
			info->qlm[3] = 0xff;
			cfg->gpio_usben = 24;
			cfg->gpio_usb3sel = 25;
			cfg->gpio_satasel = -1;
			cfg->gpio_phyrst = 14;
			cfg->gpio_phyrst_pol = 0;
			cfg->gpio_uart_hd = 21;
			cfg->gpio_uart_term = 22;
			cfg->gpio_uart_rs485 = 23;
			cfg->gpio_ledgrn = 19;
			cfg->gpio_ledred = 20;
			cfg->ext_temp = 0;
			break;
		case 'B':
			cfg->gpio_phyrst = 31;
			cfg->gpio_phyrst_pol = 0;
			cfg->gpio_satasel = 20;
			cfg->gpio_ledgrn = 13;
			cfg->ext_temp = 0;
			break;
		case 'C':
			cfg->gpio_satasel = 20;
			cfg->ext_temp = 0;
			break;
		case 'D':
			cfg->gpio_satasel = -1;
			break;
		}
		break;
	case GW640x:
		switch(rev_pcb) {
		case 'A':
			cfg->ext_temp = 0;
			cfg->gpio_satasel = 20;
			cfg->gpio_usb2sel = -1;
			break;
		}
		break;
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

int
gsc_hwmon_reg(bdk_node_t node, int reg)
{
	uint8_t buf[2];

	memset(buf, 0, sizeof(buf));
	if (i2c_read(node, 0, GSC_HWMON_ADDR, reg, buf, sizeof(buf)))
		return -1;
	return buf[0] | buf[1]<<8;
}

const char *
gsc_get_rst_cause(bdk_node_t node)
{
	static char str[64];
	const char *names[] = {
		"VIN",
		"PB",
		"WDT",
		"CPU",
		"TEMP_L",
		"TEMP_R",
		"SLEEP",
		"BOOT_WDT1",
		"BOOT_WDT2",
		"SOFT_PWR",
	};
	unsigned char reg;

	/* GSC v53 adds reset cause register */
	if (gsc_get_fwver() > 52)
		i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_RST_CAUSE, &reg, 1);
	else {
		i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_STATUS, &reg, 1);
		if (reg & (1 << GSC_SC_IRQ_WATCHDOG))
			reg = GSC_SC_RST_CAUSE_WDT;
		else
			reg = GSC_SC_RST_CAUSE_VIN;
	}

	if (reg < ARRAY_SIZE(names))
		sprintf(str, "%s", names[reg]);
	else
		sprintf(str, "0x%02x", reg);

	/* GSC v53 adds thermal protection which we will enable always */
	if (gsc_get_fwver() > 52) {
		i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_THERM_PROTECT, &reg, 1);
		reg |= 1;
		i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_THERM_PROTECT, &reg, 1);
		strcat(str, " Thermal Protection Enabled");
	}

	return str;
}

int
gsc_board_temp(bdk_node_t node)
{
	int reg, ui;

	/* GSC v51+ has board temp at register offset 0 */
	reg = (gsc_get_fwver() > 50) ? 6 : 0;
	ui = gsc_hwmon_reg(node, reg);
	if (ui > 0x8000)
		ui -= 0xffff;
	return ui;
}

/* update MAX6642 remote threshold per CN80XXI-AD-1.0 */
static int init_max6642(bdk_node_t node)
{
	int tj_max, reg, i;

	/*
	 * CN80XX industrial temp max Junction Temp (Tj):
	 *  800MHz: 100C
	 * 1000MHz: 100C
	 * 1200MHz: 100C
	 * 1500MHz: 95C
	 */
	tj_max = 100;
	if ( (bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000) >= 1500)
		tj_max -= 5;

	/* set new limits:
	 *  Note disabling local sense keeps you from ever being able to
	 *  clear the alert if it has tripped so instead we just set the
	 *  local limit to the remote limit so remote will always trip first.
	 */
	i2c_write_byte(node, 0, MAX6642_SLAVE, MAX6642_W_CONFIG, 0x10);
	i2c_write_byte(node, 0, MAX6642_SLAVE, MAX6642_W_LIMIT_LOCAL, tj_max);
	i2c_write_byte(node, 0, MAX6642_SLAVE, MAX6642_W_LIMIT_REMOTE, tj_max);

	/* loop over status until clear */
	for (i = 0; i < 20; i++) {
		reg = i2c_read_byte(node, 0, MAX6642_SLAVE, MAX6642_R_STATUS);
		if (!(reg & 0x50))
			break;
		bdk_wait_usec(500000);
	}

	return 0;
}

/* gsc_init:
 *
 * This is called from early init (boot stub) to determine board model
 * and perform any critical early init including:
 *  - configure early GPIO (ie front panel GRN LED, default states)
 *  - display GSC details banner
 *  - display EEPROM model/mfgdate/serial
 *  - configuring temperature sensor thresholds
 */
int
gsc_init(bdk_node_t node)
{
	struct newport_board_info *info = &board_info;
	struct newport_board_config *cfg;
	unsigned char buf[16];
	int i, t;

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
	printf("%s\n\n", bdk_version_string());
	printf("GSC     : v%d 0x%04x", buf[GSC_SC_FWVER],
		buf[GSC_SC_FWCRC] | buf[GSC_SC_FWCRC+1]<<8);
	printf(" RST:%s", gsc_get_rst_cause(node));
	printf("\n");

	if (GW_UNKNOWN == gsc_read_eeprom(node))
		return -2;

	cfg = gsc_get_board_config();
	/* Display/Configure temperature */
	t = gsc_board_temp(node);
	if (cfg->ext_temp) {
		init_max6642(node);
		printf("Temp    : Board:%dC/86C CPU:%dC/%dC\n", t / 10,
		       i2c_read_byte(node, 0, MAX6642_SLAVE,
				     MAX6642_R_TEMP_REMOTE),
		       i2c_read_byte(node, 0, MAX6642_SLAVE,
				     MAX6642_R_LIMIT_REMOTE));
	}
	else
		printf("Temp    : Board:%dC/86C\n", t / 10);
	printf("Model   : %s\n", info->model);
	printf("MFGDate : %02x-%02x-%02x%02x\n",
		info->mfgdate[0], info->mfgdate[1],
		info->mfgdate[2], info->mfgdate[3]);
	printf("Serial  : %d\n", info->serial);

	/* Display RTC */
	if (!i2c_read(node, 0, GSC_RTC_ADDR, 0, buf, 6)) {
		printf("RTC     : %d\n",
			buf[0] | buf[1]<<8 | buf[2]<<16 | buf[3]<<24);
	}

	/*
	 * Configure early GPIO
	 */
	/* enable USB HUB */
	if (cfg->gpio_usben != -1)
		gpio_output(cfg->gpio_usben, 1);
	/* put PHY's into reset */
	if (cfg->gpio_phyrst != -1)
		gpio_output(cfg->gpio_phyrst, cfg->gpio_phyrst_pol);
	/* Enable front-panel GRN LED */
	if (cfg->gpio_ledgrn != -1)
		gpio_output(cfg->gpio_ledgrn, 1);
	if (cfg->gpio_ledred != -1)
		gpio_output(cfg->gpio_ledred, 0);
	/* Configure Mezzanine IO */
	if (cfg->gpio_mezz_pwrdis != -1)
		gpio_output(cfg->gpio_mezz_pwrdis, 0);
	if (cfg->gpio_mezz_irq != -1)
		gpio_input(cfg->gpio_mezz_irq);

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

int
gsc_get_fwver(void) {
	bdk_node_t node = bdk_numa_master();
	unsigned char fw_ver;

	if (i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_FWVER, &fw_ver, 1))
		return -1;
	return fw_ver;
};

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
	unsigned char reg, wp;

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

	/* get WP */
	if (i2c_read(node, 0, GSC_SC_ADDR, GSC_SC_WP, &reg, 1)) {
		bdk_error("EEPROM: Failed to read GSC_SC_WP\n");
		return -1;
	}
	wp = reg & ~GSC_WP_PASSWD_MASK;

	/* disable WP */
	reg = GSC_WP_PASSWD;
	if (i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_WP, &reg, 1)) {
		bdk_error("EEPROM: Failed to write GSC_SC_WP\n");
		return -1;
	}

	/* write */
	if (i2c_write(node, 0, GSC_EEPROM_ADDR, 0x00, buf, sizeof(*info))) {
		bdk_error("EEPROM: Failed to write EEPROM\n");
		return -1;
	}

	/* re-enable WP */
	reg = wp | GSC_WP_PASSWD;
	if (i2c_write(node, 0, GSC_SC_ADDR, GSC_SC_WP, &reg, 1)) {
		bdk_error("EEPROM: Failed to write GSC_SC_WP\n");
		return -1;
	}

	return 0;
}

void
menu_gsc(bdk_menu_t *parent, char key, void *arg)
{
	bdk_node_t node = bdk_numa_master();
	int argc;
	char *args[10];
	char line[64];

	if (key == 'P') {
		gsc_program(node);
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
		else if (strcasecmp(argv[0], "sleep") == 0) {
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
