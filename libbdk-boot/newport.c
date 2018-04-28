#include <bdk.h>
#include <ctype.h>
#include <errno.h>
#include <newport.h>
#include <fw_env.h>
#include <libbdk-arch/bdk-csrs-gpio.h>
#include <libdram/dram-internal.h>
#include <libfdt/libfdt.h>

#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-gic.h"
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-ocx.h"
#include "libbdk-arch/bdk-csrs-pcierc.h"
#include "libbdk-arch/bdk-csrs-vrm.h"

#include "hwconfig.h"


/* PHY registers */
#define REG_BMCR	0x0
#define REG_PHYCR	0x10
#define REG_PHYSTS	0x11
#define REG_LEDCR1	0x18
#define REG_LEDCR2	0x19
#define REG_LEDCR3	0x1a

/* Extended registers */
#define REG_RGMIICTL	0x0032
#define REG_RGMIIDCTL	0x0086
#define REG_SGMIICTL1	0x00d3
#define REG_STRAP_STS1	0x006e
#define REG_STRAP_STS2	0x006f
#define REG_IO_MUX_CFG	0x0170

/* indirect register access */
#define REG_REGCR	13
#define REG_ADDAR	14

static int if_phy_ti_read(bdk_node_t node, int bus, int addr, int reg)
{
	bdk_mdio_write(node, bus, addr, REG_REGCR, 0x001f);
	bdk_mdio_write(node, bus, addr, REG_ADDAR, reg);
	bdk_mdio_write(node, bus, addr, REG_REGCR, 0x401f);
	return bdk_mdio_read(node, bus, addr, REG_ADDAR);
}

static void if_phy_ti_write(bdk_node_t node, int bus, int addr, int reg,
			    int val)
{
	bdk_mdio_write(node, bus, addr, REG_REGCR, 0x001f);
	bdk_mdio_write(node, bus, addr, REG_ADDAR, reg);
	bdk_mdio_write(node, bus, addr, REG_REGCR, 0x401f);
	bdk_mdio_write(node, bus, addr, REG_ADDAR, val);
}

static int ti_phy_setup(bdk_node_t node, int qlm, int bus, int addr)
{
	int reg, id2;

	/* Check if the PHY is TI PHY we expect */
	id2 = bdk_mdio_read(node, bus, addr, BDK_MDIO_PHY_REG_ID2);

	/* DP83867 */
	if (id2 != 0xa231)
		return -1;

	printf("MDIO%d   : DP83867 (%s)\n", bus,
		(qlm == -1) ? "RGMII" : "SGMII");

	/* LED configuration */
	reg = 0;
	reg |= 0x5 << 4; /* LED1(Amber;Speed)   : 1000BT link */
	reg |= 0xb << 8; /* LED2(Green;Link/Act): blink for TX/RX activity */
	bdk_mdio_write(node, bus, addr, REG_LEDCR1, reg);

	/* RGMII PHY */
	if (qlm == -1) {
		/* Enable CLKOUT */
		reg = if_phy_ti_read(node, bus, addr, REG_IO_MUX_CFG);
		reg &= ~0x1f00;
		reg |= 0x0b00; /* chD tx clock*/
		if_phy_ti_write(node, bus, addr, REG_IO_MUX_CFG, reg);

#if 0 // use this if don't want to change uboot/kernel
      // but will break if kernel phy driver enabled
		/* disable PHY TX delay, enable PHY RX delay
		 * as the default for the CN80XX is to enable RX delay
		 * and disable TX delay
		 */
		reg = if_phy_ti_read(node, bus, addr, REG_RGMIICTL);
		reg &= ~0x2; // clear RGMII_TX_CLK_DELAY
		if_phy_ti_write(node, bus, addr, REG_RGMIICTL, reg);
#endif
	}

	/* SGMII PHY */
	else if (qlm == 1) {
	}

	return 0;
}

static const char*
parse_hwconfig_skt(bdk_node_t node, int i, char *hwconfig,
		   struct newport_board_config *cfg)
{
	struct qlm_config *qlm;
	size_t sz, c;
	const char *p;
	const char *opt;
	static char mode[16];

	/* adjust board qlm config based on hwconfig socket options */
	opt = cfg->skt[i].socket_name;
	p = hwconfig_arg_f(opt, &sz, hwconfig);
	if (!p)
		return cfg->skt[i].def_mode;

	qlm = &cfg->qlm[cfg->skt[i].qlm];
	for (c = 0; (c < sz) && (c < sizeof(mode)); c++)
		mode[c] = toupper((unsigned char)p[c]);
	mode[sz] = 0;
	debug("%s: %s:QLM%d:%s\n", __func__, opt,
	      cfg->skt[i].qlm, mode);
	if (strcmp(mode, cfg->skt[i].opt_mode) == 0) {
		/* configure optional mode */
		if (strcmp(mode, "USB3") == 0) {
			qlm->mode = BDK_QLM_MODE_DISABLED;
			if (cfg->gpio_usb3sel != -1)
				gpio_output(cfg->gpio_usb3sel, 1);
		} else if (strcmp(mode, "SATA") == 0) {
			qlm->mode = BDK_QLM_MODE_SATA_2X1;
			qlm->freq = 6000;
			if (cfg->gpio_satasel != -1)
				gpio_output(cfg->gpio_satasel, 1);
		}
	} else if (strncmp(mode, "DISABLE", 7) == 0) {
		qlm->mode = BDK_QLM_MODE_DISABLED;
		return "DISABLED";
	} else if (strcmp(mode, cfg->skt[i].def_mode)) {
		printf("%s: invalid mode '%s'\n", opt, mode);
		qlm->mode = BDK_QLM_MODE_DISABLED;
		return "DISABLED";
	}

	return mode;
}

static int newport_qlm_config(bdk_node_t node, char *hwconfig,
			      bool quiet)
{
	struct newport_board_info *info = gsc_get_board_info();
	struct newport_board_config *cfg = gsc_get_board_config();
	struct qlm_config *qlm;
	int i;

	/* override mode from EEPROM config */
	for (i = 0; i < 4; i++) {
		qlm = &cfg->qlm[i];
		switch(info->qlm[i]) {
			case QLM_MODE_DISABLED:	/* QLM is disabled */
				qlm->mode = BDK_QLM_MODE_DISABLED;
				break;
			case QLM_MODE_PCIE_1X1:	/* 1 PCIe, 1 lane */
				qlm->mode = BDK_QLM_MODE_PCIE_1X1;
				break;
			case QLM_MODE_PCIE_1X2:	/* 1 PCIe, 2 lanes */
				qlm->mode = BDK_QLM_MODE_PCIE_1X2;
				break;
			case QLM_MODE_PCIE_1X4:	/* 1 PCIe, 4 lanes */
				qlm->mode = BDK_QLM_MODE_PCIE_1X4;
				break;
			case QLM_MODE_SATA_2X1:	/* SATA */
				qlm->mode = BDK_QLM_MODE_SATA_2X1;
				break;
			case QLM_MODE_SGMII_1X1: /* SGMII, 1 lane */
				qlm->mode = BDK_QLM_MODE_SGMII_1X1;
				break;
			case QLM_MODE_SGMII_2X1: /* SGMII */
				qlm->mode = BDK_QLM_MODE_SGMII_2X1;
				break;
			case QLM_MODE_XFI_1X1:	/* 1 XFI, 1 lane */
				qlm->mode = BDK_QLM_MODE_XFI_1X1;
				break;
			case QLM_MODE_XFI_2X1:	/* 2 XFI, 1 lane each */
				qlm->mode = BDK_QLM_MODE_XFI_2X1;
				break;
			case QLM_MODE_10G_KR_1X1: /* 1 10GBASE-KR, 1 lane */
				qlm->mode = BDK_QLM_MODE_10G_KR_1X1;
				break;
			case QLM_MODE_QSGMII_4X1: /* QSGMII, 4x SGMII */
				qlm->mode = BDK_QLM_MODE_QSGMII_4X1;
				break;
		}
	}

	/* get QLM configs */
	if (cfg->gpio_usb3sel != -1)
		gpio_output(cfg->gpio_usb3sel, 0);
	if (cfg->gpio_satasel != -1)
		gpio_output(cfg->gpio_satasel, 0);
	for (i = 0; (i < 4) && cfg->skt[i].socket_name; i++) {
		const char *s = parse_hwconfig_skt(node, i, hwconfig, cfg);
		if (!quiet)
			printf("%-8s: %s\n", cfg->skt[i].socket_name, s);
	}
	/* configure */
	for (i = 0; i < 4; i++) {
		bdk_qlm_set_clock(node, i, cfg->qlm[i].clk);
		bdk_qlm_set_mode(node, i, cfg->qlm[i].mode,
				 cfg->qlm[i].freq, 0);
		if (!quiet) {
			printf("QLM%d    : %s@%dMHz\n", i,
			       bdk_qlm_mode_to_cfg_str(cfg->qlm[i].mode),
			       cfg->qlm[i].freq);
		}
	}
	return 0;
}

static int newport_serial_config(bdk_node_t node, char *hwconfig)
{
	struct newport_board_config *cfg = gsc_get_board_config();
	char s[16];
	const char *p;
	size_t sz, c;
	bool rs485 = 0;
	bool rs485_hd = 0;
	bool rs485_term = 0;
	bool rs232 = 1;
	bool rs232_dtr = 0;

	if (hwconfig_f("serial", hwconfig)) {
		p = hwconfig_subarg_f("serial", "mode", &sz, hwconfig);
		if (p) {
			for (c = 0; (c < sz) && (c < sizeof(s)); c++)
				s[c] = toupper((unsigned char)p[c]);
			s[sz] = 0;
			if (strncmp(s, "RS485_HD", 8) == 0) {
				rs232 = false;
				rs485 = true;
				rs485_hd = true;
			} else if (strncmp(s, "RS485_FD", 8) == 0) {
				rs232 = false;
				rs485 = true;
				rs485_hd = false;
			} else if (strncmp(s, "RS232_DTR", 9) == 0) {
				rs232 = true;
				rs232_dtr = true;
			} else if (strncmp(s, "RS232", 5) == 0) {
				rs232 = true;
				rs232_dtr = false;
			} else
				printf("Serial  : invalid mode '%s'\n", s);
		}
	}

	/* setup UART2 pinsel */
	if (rs485 || rs232) {
		debug("pinsel UART2\n");
		gpio_pinsel(6, BDK_GPIO_PIN_SEL_E_UARTX_SIN_CN8(2));
		gpio_pinsel(11, BDK_GPIO_PIN_SEL_E_UARTX_SOUT_CN8(2));
	}

	if (rs232) {
		if (rs232_dtr)
			printf("Serial  : 1x RS232 with flow control\n");
		else if (!rs232_dtr) {
			debug("pinsel UART3\n");
			/* setup UART3 pinsel */
			gpio_pinsel(7, BDK_GPIO_PIN_SEL_E_UARTX_SIN_CN8(3));
			gpio_pinsel(12, BDK_GPIO_PIN_SEL_E_UARTX_SOUT_CN8(3));
			printf("Serial  : 2x RS232 without flow control\n");
		}
	}

	else if (rs485) {
		p = hwconfig_subarg_f("serial", "term", &sz, hwconfig);
		if (p) {
			for (c = 0; (c < sz) && (c < sizeof(s)); c++)
				s[c] = toupper((unsigned char)p[c]);
			s[sz] = 0;
			if (strncmp(s, "YES", 3) == 0)
				rs485_term = 1;
			else if (strncmp(s, "NO", 3) == 0)
				rs485_term = 0;
			else
				printf("Serial  : invalid opt 'term=%s'\n", s);
		}

		printf("Serial  : 1x RS485 %s-duplex with%s "
		       "on-board termination\n",
		       rs485_hd ? "half" : "full",
		       rs485_term ? "" : "out");
	}

	/* serial gpio configuration */
	if (cfg->gpio_uart_rs485 != -1)
		gpio_output(cfg->gpio_uart_rs485, rs485);
	if (cfg->gpio_uart_term != -1)
		gpio_output(cfg->gpio_uart_term, rs485_term);
	if (cfg->gpio_uart_hd != -1)
		gpio_output(cfg->gpio_uart_hd, rs485_hd);

	return 0;
}

/* GPIO configuration:
 *  - power-on pin-sel is GPIO
 *  - power-on default is high-z input
 */
static int newport_gpio_config(bdk_node_t node, char *hwconfig)
{
	const char *rev = bdk_config_get_str(BDK_CONFIG_BOARD_REVISION);

	debug("%s hwconfig=%s\n", __func__, hwconfig);
	if (!rev)
		rev = "A";
	switch(gsc_get_board_model()) {
	case GW630x:
		switch(*rev) {
		case 'A':
			debug("GW630x revA\n");
			gpio_output(14, 1); /* GBE_RST# */
			gpio_output(16, 1); /* PCIE_WDIS# */
			gpio_output(19, 1); /* CPU_LEDG# */
			gpio_output(20, 0); /* CPU_LEDR# */
			gpio_output(24, 1); /* HUB_RST# */
			break;
		case 'B':
			debug("GW630x revB+\n");
			gpio_output(13, 1); /* CPU_LEDG# */
			gpio_output(14, 0); /* CPU_LEDG# */
			gpio_output(18, 1); /* HUB_RST# */
			gpio_output(31, 1); /* GBE_RST# */
			gpio_output(28, 0); /* MEZZ_PWRDIS */
			gpio_input(29);     /* MEZZ_IRQ# */
			break;
		}
		break;
	}

	return 0;
}

int newport_chip_details(bdk_node_t node)
{
	struct newport_board_config *cfg = gsc_get_board_config();
	BDK_CSR_INIT(gicd_iidr, node, BDK_GICD_IIDR);
	BDK_CSR_INIT(rst_boot, node, BDK_RST_BOOT);
	BDK_CSR_INIT(gpio_strap, node, BDK_GPIO_STRAP);
	const char *boot_method_str = "Unknown";
	int trust_mode = rst_boot.s.trusted_mode;
	int boot_method = bdk_extract(gpio_strap.u, 0, 4);
	int alt_pkg;
	int major_pass;
	int minor_pass;

	BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
	alt_pkg = (mio_fus_dat2.s.chip_id >> 6) & 1;
	major_pass = ((mio_fus_dat2.s.chip_id >> 3) & 7) + 1;
	minor_pass = mio_fus_dat2.s.chip_id & 7;
	const char *package_str = (alt_pkg) ? " (alt pkg)" : "";
	/* The contents of PC when this image started */
	extern uint64_t __bdk_init_reg_pc;
	const char *secure_image = "";
	if (node == bdk_numa_master()) {
		if (__bdk_init_reg_pc == 0x150000)
			secure_image = ", Secure Boot";
		else if (__bdk_init_reg_pc == 0x120000)
			secure_image = ", Non-secure Boot";
	}

	printf("SoC     : %s %dKB %lu/%luMHz ",
	       bdk_model_get_sku(node),
	       bdk_l2c_get_cache_size_bytes(node) >> 10,
	       bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000,
	       bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / 1000000);
	printf("0x%x Pass %d.%d%s ", gicd_iidr.s.productid,
	       major_pass, minor_pass, package_str);
	printf("\n");

	/* MMC devices */
	for (int i = 0; i < cfg->mmc_devs; i++) {
		int64_t sz = bdk_mmc_initialize(node, i); // sz is wrong
		bool sd = bdk_mmc_card_is_sd(node, i);
		if (sz > 0)
			printf("MMC%d    : %s\n", i, sd ? "microSD" : "eMMC");
		else
			printf("MMC%d    : not detected\n", i);
	}

	/* Boot device */
	switch ( boot_method )
	{
		case BDK_RST_BOOT_METHOD_E_CCPI0:
		case BDK_RST_BOOT_METHOD_E_CCPI1:
		case BDK_RST_BOOT_METHOD_E_CCPI2:
		case BDK_RST_BOOT_METHOD_E_REMOTE_CN8:
		case BDK_RST_BOOT_METHOD_E_PCIE0:
			break;
		case BDK_RST_BOOT_METHOD_E_EMMC_LS:
		case BDK_RST_BOOT_METHOD_E_EMMC_SS:
			boot_method_str = bdk_mmc_card_is_sd(node, 0) ?
				"microSD" : "eMMC";
			break;
		case BDK_RST_BOOT_METHOD_E_SPI24:
		case BDK_RST_BOOT_METHOD_E_SPI32:
			boot_method_str = "SPI";
			break;
	}
	printf("Boot    : %s %strusted %s\n", boot_method_str,
	       (trust_mode) ? "" : "non-", secure_image);


	return 0;
}

static int newport_dram_config(bdk_node_t node)
{
	struct newport_board_info *info = gsc_get_board_info();
	int spd_size;
	uint8_t *spd_data = (uint8_t *)bdk_config_get_blob(&spd_size,
					BDK_CONFIG_DDR_SPD_DATA, 0, 0, node);

	debug("%s model=%s\n", __func__, info->model);
	if (spd_data && spd_size) {
		if (strncmp(info->model, "GW6300", 6) == 0) {
			/* SDRAM Density / Banks: 2 bank groups, 4 banks 4Gb */
			spd_data[4] = 0x44;
			/* Addressing: 256Mbx16 15 Row x 10 Column */
			spd_data[5] = 0x19;
		} else if (strncmp(info->model, "GW6304", 6) == 0) {
			/* SDRAM Density / Banks: 2 bank groups, 4 banks 8Gb */
			spd_data[4] = 0x45;
			/* Addressing: 512Mbx16 16 Row x 10 Column */
			spd_data[5] = 0x21;
		}
		bdk_config_set_blob(spd_size, spd_data,
				    BDK_CONFIG_DDR_SPD_DATA);
	} else {
		printf("DRAM:  missing configuration\n");
		return -1;
	}

	return 0;
}

void phy_reset(bdk_node_t node, struct newport_board_config *cfg)
{
	if (cfg->gpio_phyrst == -1)
		return;
	bdk_gpio_initialize(node, cfg->gpio_phyrst, 1, cfg->gpio_phyrst_pol);
	bdk_wait_usec(1000);
	bdk_gpio_initialize(node, cfg->gpio_phyrst, 1, !cfg->gpio_phyrst_pol);
	bdk_wait_usec(1000);
}

static int newport_phy_setup(bdk_node_t node)
{
	int bgx, addr;
	int detected = 0;
	int id1;

	/* 81xx has only 2 BGX (BGX0-BGX1); BGX2 is RGMII */
	for (bgx = 2; bgx >= 0; bgx--) {
		int mdio_bus, mdio_addr;

		addr = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, node, bgx, 0);
		if (addr == -1)
			continue;

		mdio_bus = (addr >> 8) & 0xff;
		mdio_addr = addr & 0xff;
		if ((addr & BDK_IF_PHY_TYPE_MASK) == BDK_IF_PHY_MDIO) {
			int qlm = -1;

			/* qlm */
			if (bgx < 2) {
				qlm = bdk_qlm_get(node, BDK_IF_BGX, bgx, 0);
				if (qlm == -1)
					continue;
			}

			/* PHY id */
			id1 = bdk_mdio_read(node, mdio_bus, addr,
					    BDK_MDIO_PHY_REG_ID1);
			if (id1 == 0x2000) { /* TI */
				ti_phy_setup(node, qlm, mdio_bus, mdio_addr);
				detected++;
			}
			else
				printf("MDIO%d: error: %04x\n", mdio_bus, id1);
		}
	}
	return detected;
}

/* newport_config:
 *  - read EEPROM and identify board
 */
int newport_config(void)
{
	struct newport_board_config *cfg;
	int i, board_model;
	char *hwconfig = NULL;
	bool quiet = false;
	bdk_node_t node = bdk_numa_local();

	board_model = gsc_read_eeprom(node);
	if (board_model == GW_UNKNOWN)
		return -1;
	cfg = gsc_get_board_config();

	/* read U-Boot env */
	if (!fw_env_open(NULL)) {
		hwconfig = fw_getenv("quiet");
		if (hwconfig)
			quiet = atoi(hwconfig) ? true : false;
		hwconfig = fw_getenv("hwconfig");
		fw_env_close(NULL);
	} else
		printf("failed opening U-Boot env\n");

	bdk_watchdog_poke();
	/* display chip details */
	if (!quiet)
		newport_chip_details(bdk_numa_master());

	/* Config DRAM */
	bdk_boot_status(BDK_BOOT_STATUS_INIT_NODE0_DRAM);
	newport_dram_config(bdk_numa_master());
	bdk_boot_dram(node, 0 /*clock override*/);
	bdk_boot_status(BDK_BOOT_STATUS_INIT_NODE0_DRAM_COMPLETE);

	/* Config CCPI */
	bdk_boot_status(BDK_BOOT_STATUS_INIT_CCPI);
	bdk_boot_ccpi();
	bdk_boot_status(BDK_BOOT_STATUS_INIT_CCPI_COMPLETE);

	/* Config QLM's */
	bdk_boot_status(BDK_BOOT_STATUS_INIT_QLM);
	newport_qlm_config(node, hwconfig, quiet);
	bdk_boot_status(BDK_BOOT_STATUS_INIT_QLM_COMPLETE);

	bdk_boot_bgx();
	bdk_boot_usb();
	bdk_watchdog_poke();

	/* Config GPIO */
	newport_gpio_config(node, hwconfig);
	newport_serial_config(node, hwconfig);

	/* Config PEMs */
	for (int p = 0; p < bdk_pcie_get_num_ports(node); p++) {
		int qlm = bdk_qlm_get(node, BDK_IF_PCIE, p, 0);
		BDK_CSR_DEFINE(pciercx_cfg032, BDK_PCIERCX_CFG032(p));
		/* Only init PCIe that are attached to QLMs */
		if (qlm != -1) {
			printf("PEM%d    : QLM%d ", p, qlm);
			switch(bdk_pcie_rc_initialize(node, p)) {
			case -2:
				printf("Link Timeout\n");
				break;
			case 0:
				pciercx_cfg032.u = BDK_CSR_READ(node,
							BDK_PCIERCX_CFG032(p));
				printf("Link Gen%d\n", pciercx_cfg032.s.ls);
				break;
			default:
				printf("unkown\n");
				break;
			}
		}
	}

	/* Config PHYs */
	bdk_boot_mdio(); /* handle MDIO-WRITE's from board dts */
	for (i = 0; i < 5; i++) {
		phy_reset(node, cfg);
		if (2 == newport_phy_setup(node))
			break;
		printf("MDIO retry %d/%d\n", i+1, 5);
		bdk_wait_usec(500000);
	}

	return 0;
}

enum mmc_type {
	MMC_EMMC,
	MMC_MICROSD,
};

void setup_mmc(void *fdt, int off, enum mmc_type type, int chipsel)
{
	fdt_setprop_u32(fdt, off, "reg", chipsel);
	switch(type) {
	case MMC_MICROSD:
		/* microSD */
		fdt_setprop_u32(fdt, off, "bus-width", 4);
		fdt_setprop(fdt, off, "cap-sd-highspeed", NULL, 0);
		fdt_setprop(fdt, off, "no-mmc", NULL, 0);
		break;
	case MMC_EMMC:
		/* setup eMMC */
		fdt_setprop_u32(fdt, off, "bus-width", 8);
		fdt_setprop(fdt, off, "mmc-ddr-3_3v", NULL, 0);
		fdt_setprop(fdt, off, "cap-mmc-highspeed", NULL, 0);
		fdt_setprop(fdt, off, "no-sd", NULL, 0);
		break;
	}
}

static void fixup_mmc(void *fdt)
{
	int off, sd;
	bdk_node_t node = bdk_numa_local();
	int64_t sz;

	/*
	 * Swap dt nodes for emmc/microsd slot such that:
	 *  dev 0 and mmcblk0 are always primary device
	 *  dev 1 and mmcblk1 are always secondary device
	 */
	/* first slot */
	off = fdt_node_offset_by_compatible(fdt, -1, "mmc-slot");
	if (off <= 0)
		return;
	sd = bdk_mmc_card_is_sd(node, 0);
	sz = bdk_mmc_initialize(node, 0);
	if (sd)
		setup_mmc(fdt, off, MMC_MICROSD, 0);
	else
		setup_mmc(fdt, off, MMC_EMMC, 0);
	/* second slot */
	off = fdt_node_offset_by_compatible(fdt, -1, "mmc-slot");
	off = fdt_node_offset_by_compatible(fdt, off, "mmc-slot");
	if (off <= 0)
		return;
	sd = bdk_mmc_card_is_sd(node, 1);
	sz = bdk_mmc_initialize(node, 1);
	if (sz > 0) {
		if (sd)
			setup_mmc(fdt, off, MMC_MICROSD, 1);
		else
			setup_mmc(fdt, off, MMC_EMMC, 1);
	} else
		fdt_del_node(fdt, off);
}

static int set_gpio(void *fdt, const char *path, int gpio)
{
	const uint32_t *mem;
	uint32_t new_mem[3];
	int off, len;
	const char* prop = "gpios";

	off = fdt_path_offset(fdt, path);
	if (off <= 0)
		return -1;
	mem = fdt_getprop(fdt, off, prop, &len);
	if (mem && (len == sizeof(uint32_t) * 3)) {
		new_mem[0] = mem[0];
		new_mem[1] = cpu_to_fdt32(gpio);
		new_mem[2] = mem[2];
		return fdt_setprop_inplace(fdt, off, prop, new_mem,
					   sizeof(new_mem));
	}
	return -2;
}

static void fixup_leds(void *fdt)
{
	struct newport_board_config *cfg = gsc_get_board_config();

	set_gpio(fdt, "/leds/user1", cfg->gpio_ledgrn);
	set_gpio(fdt, "/leds/user2", cfg->gpio_ledred);
}

static const char *
fdt_get_string(void *fdt, int offset, const char *prop, const char *def)
{
	int len;
	const char *val;

	val = fdt_getprop(fdt, offset, prop, &len);
	if (val)
		return val;
	return def;
}

static int
fdt_get_int(void *fdt, int offset, const char *prop, int def)
{
	int len;
	const uint32_t *val;

	val = fdt_getprop(fdt, offset, prop, &len);
	if (val && (len == sizeof(uint32_t)))
		return fdt32_to_cpu(*val);
	return def;
}

static int
show_hwmon(void *fdt)
{
	int len, off, reg, val;
	int offset;
	const char *label, *type;
	bdk_node_t node = bdk_numa_local();

	/* GSC firmware v51 required */
        if (gsc_get_fwver() < 51)
		return -1;

	off = fdt_node_offset_by_compatible(fdt, -1, "gw,gsc-hwmon");
	if (off <= 0)
		return -1;

	/* iterate over hwmon nodes */
	off = fdt_first_subnode(fdt, off);
	while (off >= 0) {
		type = fdt_get_string(fdt, off, "type", NULL);
		reg = fdt_get_int(fdt, off, "reg", -1);
		offset = fdt_get_int(fdt, off, "gw,voltage-offset", 0);
		label = fdt_get_string(fdt, off, "label", NULL);
		val = gsc_hwmon_reg(node, label, reg);

		if (label && !strcasecmp(type, "gw,hwmon-temperature")) {
			if (val > 0x8000)
				val -= 0xffff;
			printf("%-8s: %d.%dC\n", label, val / 10, val % 10);
		}

		else if (label && !strcasecmp(type, "gw,hwmon-voltage")) {
			if (val != 0xffff) {
				printf("%-8s: %d.%03dV\n", label,
					val / 1000, val % 1000);
			}
		}

		else if (label && !strcasecmp(type, "gw,hwmon-voltage-raw")) {
			/* scale based on ref volt and resolution */
			val *= 2500;
			val /= 1<<12;

			/* apply pre-scaler voltage divider */
			const uint32_t *div;
			int r[2];
			div  = fdt_getprop(fdt, off, "gw,voltage-divider",
					   &len);
			if (div && (len == sizeof(uint32_t) * 2)) {
				r[0] = fdt32_to_cpu(div[0]);
				r[1] = fdt32_to_cpu(div[1]);
				if (r[0] && r[1]) {
					val *= (r[0] + r[1]);
					val /= r[1];
				}
			}

			/* adjust by offset */
			val += offset;

			printf("%-8s: %d.%03dV\n", label,
				val / 1000, val % 1000);
		}

		off = fdt_next_subnode(fdt, off);
	}
	return 0;
}

int newport_devtree_fixups(void *fdt)
{
	const char *str;

	/* hwmon inputs */
	show_hwmon(fdt);

	/* board serial number */
	str = bdk_config_get_str(BDK_CONFIG_BOARD_SERIAL);
	fdt_setprop(fdt, 0, "system-serial", str, strlen(str) + 1);

	/* board model */
	str = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
	fdt_setprop(fdt, 0, "board", str, strlen(str) + 1);

	/* MMC slot definitions */
	fixup_mmc(fdt);

	/* LED gpios */
	fixup_leds(fdt);

	return 0;
}
