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

enum vt_led_modes {
	VT_LED_LINK_ACT	= 0,
	VT_LED_LINK1000_ACT,
	VT_LED_LINK100_ACT,
	VT_LED_LINK10_ACT,
	VT_LED_LINK100_1000_ACT,
	VT_LED_LINK10_1000_ACT,
	VT_LED_LINK10_100_ACT,
	VT_LED_LINK100BASEFX_1000BASEX_ACT,
	VT_LED_DUPLEX_COLLISION,
	VT_LED_COLLISION,
	VT_LED_ACT,
	VT_LED_1000BASEFX_1000BASE_X_ACT,
	VT_LED_AUTONEG_FAULT,
	VT_LED_SERIAL,
	VT_LED_OFF,
	VT_LED_ON,
	VT_LED_LINK1000BASEX_ACT,
	VT_LED_LINK100BASEFX_ACT,
	VT_LED_100BASEX_ACT,
	VT_LED_100BASEFX_ACT,
	VT_LED_OFF1,
	VT_LED_ON1,
	VT_LED_FAST_LINK_FAIL,
};

/*
 *  LED2 (Amber)
 *  LED3 (Green)
 *
 * P3 PHY5
 * P2 PHY4 D8-Green (LED3) D7-Amber (LED2)
 */
static int vt_set_port_led(bdk_node_t node, int bus, int addr, int port,
			   int led, int mode)
{
	int reg;

	debug("%s: mdio%d 0x%02x port%d led%d mode=%d\n", __func__,
	      bus, addr, port, led, mode);
	// Select page 1 registers
	bdk_mdio_write(node, bus, addr + port, 0x1f, 1);
	reg = bdk_mdio_read(node, bus, addr + port, 0x13);
	// LED0-3 extended mode: R29[12]
	reg = bdk_insert(reg, mode / 0xf, 12 + led, 1);
	bdk_mdio_write(node, bus, addr + port, 0x13, reg);

	// Select main registers
	bdk_mdio_write(node, bus, addr + port, 0x1f, 0);
	reg = bdk_mdio_read(node, bus, addr + port, 0x1d);
	reg = bdk_insert(reg, mode & 0xf, led * 4, 4);
	bdk_mdio_write(node, bus, addr + port, 0x1d, reg);

	return 0;
}

/* vt_phy_setup - setup VSC8574 PHY */
static int vt_phy_setup(bdk_node_t n, int qlm, int b, int a)
{
	int reg, p;

	debug("%s QLM%d MDIO%d 0x%02x\n", __func__, qlm, b, a);
	reg = bdk_mdio_read(n, b, a, BDK_MDIO_PHY_REG_ID2);

	/* VSC8475-04 */
	if (reg != 0x04a2)
		return -1;

	printf("MDIO%d   : VSC8574 (QSGMII)\n", b);

	/* same as the VSC8475-01 used on sff8104: use that setup */
	bdk_if_phy_vetesse_setup(n, qlm, b, a);

	/* GPIO configuration
	 * GPIO0: IN SFP4_PRES#
	 * GPIO1: IN SFP5_PRES#
	 * GPIO2: IN SFP4_LOS
	 * GPIO3: IN SFP5_LOS
	 * GPIO4: OUT SFP4_TXDIS
	 * GPIO5: OUT SFP5_TXDIS
	 * GPIO6: OUT SFP4_SCL
	 * GPIO7: OUT SFP5_SCL
	 * GPIO8: I/O SFP45_SDA
	 * Drive LED states vs drive low and tristate high
	 */
	// Reg 13G GPIO0-GPIO7 control
	//   GPIO0-5 GPIO GPIO6=PHY2_SCL GPIO7=PHY3_SCL
	bdk_mdio_write(n, b, a, 0x1f, 0x10);
	reg = 0x0fff;
	bdk_mdio_write(n, b, a, 13, reg);
	// Reg 14G GPIO control: GPIO0-5 GPIO GPIO6=PHY2_SCL GPIO7=PHY3_SCL
	reg = bdk_mdio_read(n, b, a, 14);
	reg &= ~0x3; // GPIO8 I2C_SDA
	reg &= ~(1 << 9); // drive LED bus output low
	bdk_mdio_write(n, b, a, 14, reg);
	// Reg 17G: GPIO Pin Config
	reg = bdk_mdio_read(n, b, a, 17);
	reg &= ~0x3fff; // clear bits 13:0
	reg |= 0x01f0; // GPIO0-3 input, GPIO4-8 output
	bdk_mdio_write(n, b, a, 17, reg);
	// Select main registers
	bdk_mdio_write(n, b, a, 0x1f, 0);

	/* Port specific config */
	for (p = 0; p < 4; p++) {
		// set 17e2(0x11) bit 11:10 to invert LED0/LED1
		bdk_mdio_write(n, b, a + p, 0x1f, 2);
		reg = bdk_mdio_read(n, b, a + p, 0x11);
		reg = bdk_insert(reg, 0x3, 10, 2);
		bdk_mdio_write(n, b, a + p, 0x11, reg);
		bdk_mdio_write(n, b, a + p, 0x1f, 0);

		// LED0 (Green) link/activity
		vt_set_port_led(n, b, a, p, 0, VT_LED_LINK_ACT);
		// LED1 (Yellow) speed
		vt_set_port_led(n, b, a, p, 1, VT_LED_LINK1000_ACT);
		reg = bdk_mdio_read(n, b, a + p, 0x1e);
		reg = bdk_insert(reg, 0x1, 1, 1); // disable LED1 activity
		bdk_mdio_write(n, b, a + p, 0x1e, reg);
		// LED2/LED3 off
		vt_set_port_led(n, b, a, p, 2, VT_LED_OFF);
		vt_set_port_led(n, b, a, p, 3, VT_LED_OFF);
	}

	return 0;
}

int
parse_hwconfig_skt(bdk_node_t node, int i, char *hwconfig,
		   struct newport_board_config *cfg, bool quiet)
{
	struct qlm_config *qlm = &cfg->qlm[cfg->skt[i].qlm];
	size_t sz, c;
	const char *p;
	const char *opt;
	char *mode;
	static char arg[16];
	int err;

	opt = cfg->skt[i].socket_name;
	if (!quiet)
		printf("%-8s: ", opt);

	/* get socket option string */
	p = hwconfig_arg_f(opt, &sz, hwconfig);
	if (!p || sz == 0) {
		p = cfg->skt[i].def_mode;
		sz = strlen(p);
	}

	/* upercase and terminate mode str */
	for (c = 0; (c < sz) && (c < sizeof(arg)); c++)
		arg[c] = toupper((unsigned char)p[c]);
	arg[sz] = 0;
	debug("%s: socket=%s QLM%d mode=%s default=%s opts=%s\n", __func__, opt,
	      cfg->skt[i].qlm, arg, cfg->skt[i].def_mode, cfg->skt[i].opt_mode);

	/* adjust board qlm/gpio config based on hwconfig socket options */
	mode = strtok(arg, ",");
	err = 0;
	while (mode) {
		if (strncmp(mode, "DISABLE", 7) == 0) {
			qlm->mode = BDK_QLM_MODE_DISABLED;
			qlm->freq = 0;
			if (!quiet)
				printf("DISABLED ");
			goto out;
		}
		else if (strcmp(mode, cfg->skt[i].def_mode) == 0) {
			if (!quiet)
				printf("%s ", mode);
		}
		else if (strstr(cfg->skt[i].opt_mode, mode)) {
			if (!quiet)
				printf("%s ", mode);
		}
		else {
			qlm->mode = BDK_QLM_MODE_DISABLED;
			qlm->freq = 0;
			if (quiet)
				printf("%-8s: ", opt);
			printf("DISABLED: invalid mode '%s'\n", mode);
			err = 1;
			goto out;
		}

		if (strcmp(mode, "USB3") == 0) {
			qlm->mode = BDK_QLM_MODE_DISABLED;
			qlm->freq = 0;
			if (cfg->gpio_usb3sel != -1)
				gpio_output(cfg->gpio_usb3sel,
					    cfg->gpio_usb3sel_pol ? 0 : 1);
		}
		else if (strcmp(mode, "USB2") == 0) {
			if (cfg->gpio_usb2sel != -1)
				gpio_output(cfg->gpio_usb2sel, 1);
		}
		else if (strcmp(mode, "SATA") == 0) {
			qlm->mode = BDK_QLM_MODE_SATA_2X1;
			qlm->freq = 6000;
			if (cfg->gpio_satasel != -1)
				gpio_output(cfg->gpio_satasel, 1);
		}

		mode = strtok(NULL, ",");
	}

out:
	if (!quiet) {
		/* show available configuration modes */
		if (cfg->skt[i].opt_mode) {
			printf("(hwconfig options:%s,%s)",
				cfg->skt[i].def_mode, cfg->skt[i].opt_mode);
		}
		printf("\n");
	}

	return err;
}

static const char *
socket_name_for_qlm(struct newport_board_config *cfg, int qlm)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (cfg->skt[i].socket_name && cfg->skt[i].qlm == qlm)
			return cfg->skt[i].socket_name;
	}

	return "";
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
				qlm->freq = 0;
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
	if (cfg->gpio_usb2sel != -1)
		gpio_output(cfg->gpio_usb2sel, 0);
	if (cfg->gpio_usb3sel != -1)
		gpio_output(cfg->gpio_usb3sel,
			    cfg->gpio_usb3sel_pol ? 1 : 0);
	if (cfg->gpio_satasel != -1)
		gpio_output(cfg->gpio_satasel, 0);
	for (i = 0; (i < 4) && cfg->skt[i].socket_name; i++)
		parse_hwconfig_skt(node, i, hwconfig, cfg, quiet);
	/* configure */
	for (i = 0; i < 4; i++) {
		bdk_qlm_set_clock(node, i, cfg->qlm[i].clk);
		/* let PCI freq depend on SCLK */
		if (cfg->qlm[i].mode == BDK_QLM_MODE_PCIE_1X1) {
			int sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);

			if (sclk >= 550000000)
				cfg->qlm[i].freq = 8000;
			else if (sclk >= 350000000)
				cfg->qlm[i].freq = 5000;
		}
		bdk_qlm_set_mode(node, i, cfg->qlm[i].mode,
				 cfg->qlm[i].freq, 0);
		if (!quiet) {
			if (cfg->qlm[i].mode == BDK_QLM_MODE_DISABLED)
				printf("QLM%d    : DISABLED\n", i);
			else {
				printf("QLM%d    : %s@%dMHz %s\n", i,
				      bdk_qlm_mode_to_cfg_str(cfg->qlm[i].mode),
				      cfg->qlm[i].freq,
				      socket_name_for_qlm(cfg, i));
			}
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

/* GPIO configuration: handle any gpio's not defined in newport_board_config
 *  - power-on pin-sel is GPIO
 *  - power-on default is high-z input
 */
static int newport_gpio_config(bdk_node_t node, char *hwconfig)
{
/*
	const char *rev = bdk_config_get_str(BDK_CONFIG_BOARD_REVISION);

	debug("%s hwconfig=%s\n", __func__, hwconfig);
	if (!rev)
		rev = "A";
	switch(gsc_get_board_model()) {
	}
*/

	return 0;
}

static int newport_dram_config(bdk_node_t node)
{
	struct newport_board_info *info = gsc_get_board_info();
	int spd_size;
	uint8_t *spd_data = (uint8_t *)bdk_config_get_blob(&spd_size,
					BDK_CONFIG_DDR_SPD_DATA, 0, 0, node);
	int width = 8 << info->sdram_width;
	int size_mb = 16 << info->sdram_size;

	debug("%s: %s model=%d width=%d size_mb=%d\n", __func__, info->model,
	      atoi(info->model + 2), width, size_mb);
	if (!spd_data || !spd_size) {
		printf("DRAM:  missing configuration\n");
		return -1;
	}

	switch (width) {
	case 32:
		switch (size_mb) {
		case 1024:
			/* SDRAM Density / Banks: 2 bank groups, 4 banks 4Gb */
			spd_data[4] = 0x44;
			/* Addressing: 256Mbx16 15 Row x 10 Column */
			spd_data[5] = 0x19;
			break;
		case 2048:
			/* SDRAM Density / Banks: 2 bank groups, 4 banks 8Gb */
			spd_data[4] = 0x45;
			/* Addressing: 512Mbx16 16 Row x 10 Column */
			spd_data[5] = 0x21;
			break;
		case 4096:
			/* SDRAM Density / Banks: 2 bank groups, 4 banks 16Gb */
			spd_data[4] = 0x46;
			/* Addressing: 512Mbx16 17 Row x 10 Column */
			spd_data[5] = 0x29;
			break;
		}
		break;
	}
	bdk_config_set_blob(spd_size, spd_data, BDK_CONFIG_DDR_SPD_DATA);

	/* adjust DRAM clock */
	int def, spd;
	int rclk = bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000;
	def = spd = bdk_config_get_int(BDK_CONFIG_DDR_SPEED, node);
	// based on RCLK
	switch (rclk) {
	case 400: spd = min(spd, 800); break;
	case 700: spd = min(spd, 1333); break;
	case 800: spd = min(spd, 1600); break;
	case 1100: spd = min(spd, 2133); break;
	case 1500: spd = min(spd, 2133); break;
	}
	if (def != spd) {
		debug("DRAM    : adjusting DRAM rate"
		       " from %dMT/s to %dMT/s per %dMHz CPU speed\n",
		       def, spd,
		       (int)bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000);
		bdk_config_set_int(spd, BDK_CONFIG_DDR_SPEED, node);
	}

	return 0;
}

void phy_reset(bdk_node_t node, struct newport_board_config *cfg)
{
	if (cfg->gpio_phyrst == -1)
		return;
	gpio_output(cfg->gpio_phyrst, cfg->gpio_phyrst_pol);
	bdk_wait_usec(1000);
	gpio_output(cfg->gpio_phyrst, !cfg->gpio_phyrst_pol);
	bdk_wait_usec(110000);
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
			id1 = bdk_mdio_read(node, mdio_bus, mdio_addr,
					    BDK_MDIO_PHY_REG_ID1);
			if (id1 == 0x2000) { /* TI */
				ti_phy_setup(node, qlm, mdio_bus, mdio_addr);
				detected++;
			}
			else if (id1 == 0x0007) { /* Vitesse */
				vt_phy_setup(node, qlm, mdio_bus, mdio_addr);
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
	int board_model;
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
	phy_reset(node, cfg);
	newport_phy_setup(node);

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
	int off[2], sd;
	bdk_node_t node = bdk_numa_local();
	int64_t sz;

	/* first slot */
	off[0] = fdt_node_offset_by_compatible(fdt, -1, "mmc-slot");
	if (off[0] <= 0)
		return;
	/* second slot */
	off[1] = fdt_node_offset_by_compatible(fdt, off[0], "mmc-slot");
	if (off[1] <= 0)
		return;

	/*
	 * Swap dt nodes for emmc/microsd slot such that:
	 *  dev 0 and mmcblk0 are always primary device
	 *  dev 1 and mmcblk1 are always secondary device
	 */
	sz = bdk_mmc_initialize(node, 1);
	sd = bdk_mmc_card_is_sd(node, 1);
	if (sz > 0) {
		if (sd)
			setup_mmc(fdt, off[1], MMC_MICROSD, 1);
		else
			setup_mmc(fdt, off[1], MMC_EMMC, 1);
	} else
		fdt_del_node(fdt, off[1]);
	sz = bdk_mmc_initialize(node, 0);
	sd = bdk_mmc_card_is_sd(node, 0);
	if (sd)
		setup_mmc(fdt, off[0], MMC_MICROSD, 0);
	else
		setup_mmc(fdt, off[0], MMC_EMMC, 0);

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

	if (cfg->gpio_ledgrn != -1) {
		set_gpio(fdt, "/leds/green", cfg->gpio_ledgrn);
		set_gpio(fdt, "/leds/user1", cfg->gpio_ledgrn);
	}
	if (cfg->gpio_ledred != -1) {
		set_gpio(fdt, "/leds/red", cfg->gpio_ledred);
		set_gpio(fdt, "/leds/user2", cfg->gpio_ledred);
	}
	if (cfg->gpio_ledblu != -1) {
		set_gpio(fdt, "/leds/blue", cfg->gpio_ledblu);
		set_gpio(fdt, "/leds/user3", cfg->gpio_ledblu);
	}
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
	int len, off, reg, val, mode;
	const char *label;
	bdk_node_t node = bdk_numa_local();

	/* GSC firmware v51 required */
        if (gsc_get_fwver() < 51)
		return -1;

	off = fdt_node_offset_by_compatible(fdt, -1, "gw,gsc-adc");
	if (off <= 0)
		return -1;

	/* iterate over hwmon nodes */
	off = fdt_first_subnode(fdt, off);
	while (off >= 0) {
		mode = fdt_get_int(fdt, off, "gw,mode", -1);
		reg = fdt_get_int(fdt, off, "reg", -1);
		label = fdt_get_string(fdt, off, "label", NULL);
		val = gsc_hwmon_reg(node, reg);

		if (label && (mode == 0)) {
			if (val > 0x8000)
				val -= 0xffff;
			printf("%-8s: %d.%dC\n", label, val / 10,
				abs(val % 10));
		}

		else if (label && (mode == 1)) {
			if (val != 0xffff) {
				printf("%-8s: %d.%03dV\n", label,
					val / 1000, val % 1000);
			}
		}

		else if (label && (mode == 2)) {
			/* scale based on ref volt and resolution */
			val *= 2500;
			val /= 1<<12;

			/* apply pre-scaler voltage divider */
			const uint32_t *div;
			int r[2];
			div  = fdt_getprop(fdt, off, "gw,voltage-divider-ohms",
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
			int offset = fdt_get_int(fdt, off, "gw,voltage-offset-microvolt", 0);
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
	struct newport_board_config *cfg = gsc_get_board_config();
	const char *str;

	/* hwmon inputs */
	show_hwmon(fdt);

	/* board serial number */
	str = bdk_config_get_str(BDK_CONFIG_BOARD_SERIAL);
	fdt_setprop(fdt, 0, "system-serial", str, strlen(str) + 1);

	/* board model */
	str = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
	fdt_setprop(fdt, 0, "board", str, strlen(str) + 1);

	/* max6642 */
	if (!cfg->ext_temp) {
		int off;

		off = fdt_node_offset_by_compatible(fdt, -1, "maxim,max6642");
		if (off > 0)
			fdt_del_node(fdt, off);
	}

	/* MMC slot definitions */
	fixup_mmc(fdt);

	/* LED gpios */
	fixup_leds(fdt);

	return 0;
}
