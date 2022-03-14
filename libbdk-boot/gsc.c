#include <bdk.h>
#include <ctype.h>
#include <gsc.h>
#include <newport.h>
#include <libbdk-arch/bdk-csrs-gpio.h>

#include "libbdk-arch/bdk-csrs-gic.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-mio_tws.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"

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
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
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
		.gpio_ledblu = -1,
		/* misc */
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
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_SGMII, 1250, BDK_QLM_CLK_COMMON_1 },
			/* Unused */
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
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
		.gpio_ledblu = -1,
		/* misc */
		.gpio_satasel = -1,
		.gpio_usb2sel = -1,
		.gpio_usb3sel = 19,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 0,
		.gpio_mezz_pwrdis = -1,
		.gpio_mezz_irq = -1,
		.mmc_devs = 2,
		.ext_temp = 1,
	},

	/* GW630x */
	{
		.qlm = {
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_SGMII, 1250, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or USB3.0 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
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
		.gpio_ledblu = -1,
		/* misc */
		.gpio_satasel = -1,
		.gpio_usb2sel = -1,
		.gpio_usb3sel = 19,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 0,
		.gpio_mezz_pwrdis = 28,
		.gpio_mezz_irq = 29,
		.mmc_devs = 2,
		.ext_temp = 1,
	},

	/* GW640x */
	{
		.qlm = {
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_QSGMII, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
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
		.gpio_ledblu = -1,
		/* misc */
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

	/* GW650x */
	{
		.qlm = {
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* SGMII 1Gb/s */
			{ BDK_QLM_MODE_QSGMII, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
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
		.gpio_ledblu = -1,
		/* misc */
		.gpio_satasel = -1,
		.gpio_usb2sel = 20,
		.gpio_usb3sel = -1,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 0,
		.gpio_mezz_pwrdis = 28,
		.gpio_mezz_irq = 29,
		.mmc_devs = 2,
		.ext_temp = 1,
	},

	/* GW6903 */
	{
		.qlm = {
			/* PCIe Gen2 */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			{ BDK_QLM_MODE_DISABLED, 0, BDK_QLM_CLK_COMMON_1 },
			/* PCIe Gen2 (default) or SATA */
			{ BDK_QLM_MODE_PCIE_X1, 5000, BDK_QLM_CLK_COMMON_1 },
		},
		.skt = {
			/* qlm, skt, defmode, optmode */
			{ 0, "J7", "PCI", NULL },
			{ 3, "J5", "PCI", "SATA" },
		},
		/* serial */
		.gpio_uart_hd = -1,
		.gpio_uart_term = -1,
		.gpio_uart_rs485 = -1,
		/* LED */
		.gpio_ledred = 5,
		.gpio_ledgrn = 31,
		.gpio_ledblu = 29,
		/* misc */
		.gpio_satasel = -1,
		.gpio_usb2sel = -1,
		.gpio_usb3sel = -1,
		.gpio_phyrst = 23,
		.gpio_phyrst_pol = 1,
		.gpio_mezz_pwrdis = -1,
		.gpio_mezz_irq = -1,
		.mmc_devs = 1,
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

/*
 * GPIO support
 */
static void gpio_setup(int gpio, bool is_output, int output_value,
		       bool active_high, bool tristate)
{
	bdk_node_t node = bdk_numa_local();

	if ((gpio >= 0) && (gpio < 48))
	{
		int gpio_group = gpio >> 6;
		int gpio_index = gpio & 63;
		if (output_value) {
			if (gpio_group)
				BDK_CSR_WRITE(node, BDK_GPIO_TX1_SET,
						1ull << gpio_index);
			else
				BDK_CSR_WRITE(node, BDK_GPIO_TX_SET,
						1ull << gpio_index);
		} else {
			if (gpio_group)
				BDK_CSR_WRITE(node, BDK_GPIO_TX1_CLR,
						1ull << gpio_index);
			else
				BDK_CSR_WRITE(node, BDK_GPIO_TX_CLR,
						1ull << gpio_index);
		}
		BDK_CSR_DEFINE(cfg, BDK_GPIO_BIT_CFGX(gpio));
		cfg.u = 0;
		cfg.s.tx_oe = !!is_output;
		cfg.s.tx_od = tristate;
		BDK_CSR_WRITE(node, BDK_GPIO_BIT_CFGX(gpio), cfg.u);
	}
	else
	{
		bdk_error("%s: illegal gpio%d\n", __func__, gpio);
	}
}

void gpio_output(int gpio, int state)
{
	debug("%s: gpio%d %d\n", __func__, gpio, state);
	gpio_setup(gpio, true, state, false, false);
}

void gpio_input(int gpio)
{
	debug("%s: gpio%d\n", __func__, gpio);
	gpio_setup(gpio, false, 0, false, false);
}

void gpio_pinsel(int gpio, int pin)
{
	bdk_node_t node = bdk_numa_master();

	debug("%s: gpio%d 0x%03x\n", __func__, gpio, pin);
	BDK_CSR_MODIFY(c, node, BDK_GPIO_BIT_CFGX(gpio), c.s.pin_sel = pin);
}
/*
 * I2C support
 */
#define RECOVERY_UDELAY  5
#define RECOVERY_CLK_CNT 9
#define ARBLOST_UDELAY   5000 /* 5ms */

/**
 * Initialize the TWSI blocks. This just sets the clock rate.
 * Many times stuff will work without calling this, but some
 * TWSI devices will fail. This is normally called automatically
 * in bdk-init-main.c.
 *
 * @return Zero on success, negative on failure
 */
int bdk_twsix_initialize(bdk_node_t node)
{
    const int TWSI_BUS_FREQ = 100000;   /* 100 KHz */
    const int TWSI_THP = 24;    	/* TCLK half period (default 24) */
    const int io_clock_hz = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    int N_divider;
    int M_divider;

    /* Set the TWSI clock to a conservative TWSI_BUS_FREQ.  Compute the
	clocks M divider based on the SCLK.
	TWSI freq = (core freq) / (20 x (M+1) x (thp+1) x 2^N)
	M = ((core freq) / (20 x (TWSI freq) x (thp+1) x 2^N)) - 1 */
    for (N_divider = 0; N_divider < 8; N_divider++)
    {
	M_divider = (io_clock_hz / (20 * TWSI_BUS_FREQ * (TWSI_THP + 1) * (1 << N_divider))) - 1;
	if (M_divider < 16)
	    break;
    }

    BDK_CSR_DEFINE(sw_twsi, BDK_MIO_TWSX_SW_TWSI(bus));
    sw_twsi.u = 0;
    sw_twsi.s.v = 1;       /* Clear valid bit */
    sw_twsi.s.op = 0x6;    /* See EOP field */
    sw_twsi.s.r = 0;       /* Select CLKCTL when R = 0 */
    sw_twsi.s.eop_ia = 3;  /* R=0 selects CLKCTL, R=1 selects STAT */
    sw_twsi.s.data = ((M_divider & 0xf) << 3) | ((N_divider & 0x7) << 0);

    int num_busses = 2;
    for (int bus = 0; bus < num_busses; bus++)
    {
	/* Only init non-slave ports */
	BDK_CSR_INIT(state, node, BDK_MIO_TWSX_SW_TWSI(bus));
	if (!state.s.slonly)
	    BDK_CSR_WRITE(node, BDK_MIO_TWSX_SW_TWSI(bus), sw_twsi.u);
    }
    return 0;
}

/**
 * Do a twsi bus recovery in the case when the last transaction
 * on the bus has been left unfinished.
 *
 * @param twsi_id   which TWSI bus to use
 */
static void bdk_twsix_recover_bus(bdk_node_t node, int twsi_id)
{
    /* read TWSX_INT */
    BDK_CSR_INIT(twsx_int, node, BDK_MIO_TWSX_INT(twsi_id));

    for (int i = 0; i < RECOVERY_CLK_CNT * 2; i++)
    {
	if (!twsx_int.s.scl_ovr)
	{
	    /* SCL shouldn't be low here */
	    if (!twsx_int.s.scl)
	    {
		bdk_error("N%d.TWSI%d: SCL is stuck low\n", node, twsi_id);
		return;
	    }

	    /* Break if SDA is high */
	    if (twsx_int.s.sda)
		break;
	}

	twsx_int.s.scl_ovr = !twsx_int.s.scl_ovr;
	BDK_CSR_WRITE(node, BDK_MIO_TWSX_INT(twsi_id), twsx_int.u);
	bdk_wait_usec(RECOVERY_UDELAY);
    }

    /*
     * Generate STOP condition using the register overrides
     * in order to move the higher level controller out of
     * the bad state. This is a workaround for the TWSI hardware.
     */
    twsx_int.s.scl_ovr = 1;
    twsx_int.s.sda_ovr = 1;
    BDK_CSR_WRITE(node, BDK_MIO_TWSX_INT(twsi_id), twsx_int.u);
    bdk_wait_usec(RECOVERY_UDELAY);
    twsx_int.s.scl_ovr = 0;
    BDK_CSR_WRITE(node, BDK_MIO_TWSX_INT(twsi_id), twsx_int.u);
    bdk_wait_usec(RECOVERY_UDELAY);
    twsx_int.s.sda_ovr = 0;
    BDK_CSR_WRITE(node, BDK_MIO_TWSX_INT(twsi_id), twsx_int.u);
}

/**
 * Do a twsi read from a 7 bit device address using an (optional)
 * internal address. Up to 4 bytes can be read at a time.
 *
 * @param twsi_id   which TWSI bus to use
 * @param dev_addr  Device address (7 bit)
 * @param internal_addr
 *      	    Internal address.  Can be 0, 1 or 2 bytes in width
 * @param num_bytes Number of data bytes to read (1-4)
 * @param ia_width_bytes
 *      	    Internal address size in bytes (0, 1, or 2)
 *
 * @return Read data, or -1 on failure
 */
int64_t bdk_twsix_read_ia(bdk_node_t node, int twsi_id, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes)
{
    bdk_mio_twsx_sw_twsi_t sw_twsi_val;
    bdk_mio_twsx_sw_twsi_ext_t twsi_ext;
    int retry_limit = 5;

    if (num_bytes < 1 || num_bytes > 4 || ia_width_bytes < 0 || ia_width_bytes > 2)
	return -1;
retry:
    twsi_ext.u = 0;
    sw_twsi_val.u = 0;
    sw_twsi_val.s.v = 1;
    sw_twsi_val.s.r = 1;
    sw_twsi_val.s.sovr = 1;
    sw_twsi_val.s.size = num_bytes - 1;
    sw_twsi_val.s.addr = dev_addr;

    if (ia_width_bytes > 0)
    {
	sw_twsi_val.s.op = 1;
	sw_twsi_val.s.ia = (internal_addr >> 3) & 0x1f;
	sw_twsi_val.s.eop_ia = internal_addr & 0x7;
	if (ia_width_bytes == 2)
	{
	    sw_twsi_val.s.eia = 1;
	    twsi_ext.s.ia = internal_addr >> 8;
	    BDK_CSR_WRITE(node, BDK_MIO_TWSX_SW_TWSI_EXT(twsi_id), twsi_ext.u);
	}
    }

    BDK_CSR_WRITE(node, BDK_MIO_TWSX_SW_TWSI(twsi_id), sw_twsi_val.u);
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MIO_TWSX_SW_TWSI(twsi_id), v, ==, 0, 10000))
    {
	bdk_warn("N%d.TWSI%d: Timeout waiting for read to complete...start recovering process\n",
		 node, twsi_id);
	/* perform bus recovery */
	bdk_twsix_recover_bus(node, twsi_id);
	if (retry_limit-- > 0)
	    goto retry;

	bdk_error("N%d.TWSI%d: Timeout waiting for operation to complete\n", node, twsi_id);
	return -1;
    }
    sw_twsi_val.u = BDK_CSR_READ(node, BDK_MIO_TWSX_SW_TWSI(twsi_id));
    if (!sw_twsi_val.s.r)
    {
	/* Check the reason for the failure.  We may need to retry to handle multi-master
	** configurations.
	** NAK : 0x38, 0x48
	** Lost arbitration : 0x38, 0x68, 0xB0, 0x78
	** Core busy as slave: 0x80, 0x88, 0xA0, 0xA8, 0xB8, 0xC0, 0xC8
	*/
	if (sw_twsi_val.s.data == 0x38
	    || sw_twsi_val.s.data == 0x68
	    || sw_twsi_val.s.data == 0xB0
	    || sw_twsi_val.s.data == 0x78
	    || sw_twsi_val.s.data == 0x80
	    || sw_twsi_val.s.data == 0x88
	    || sw_twsi_val.s.data == 0xA0
	    || sw_twsi_val.s.data == 0xA8
	    || sw_twsi_val.s.data == 0xB8
	    || sw_twsi_val.s.data == 0x30
	    || sw_twsi_val.s.data == 0x48
	    || sw_twsi_val.s.data == 0xC8)
	{
	    /*
	     * One of the arbitration lost conditions is recognized.
	     * The TWSI hardware has switched to the slave mode and
	     * expects the STOP condition on the bus.
	     * Make a delay before next retry.
	     */
	    bdk_wait_usec(ARBLOST_UDELAY);
	    if (retry_limit-- > 0)
		goto retry;
	}
	/* For all other errors, return an error code */
	bdk_error("N%d.TWSI%d: read failed: 0x%02x\n", node, twsi_id,
		  sw_twsi_val.s.data);
	return -1;
    }

    return (sw_twsi_val.s.data & (0xFFFFFFFF >> (32 - num_bytes*8)));
}


/**
 * Write 1-8 bytes to a TWSI device using an internal address.
 *
 * @param twsi_id   which TWSI interface to use
 * @param dev_addr  TWSI device address (7 bit only)
 * @param internal_addr
 *      	    TWSI internal address (0, 8, or 16 bits)
 * @param num_bytes Number of bytes to write (1-8)
 * @param ia_width_bytes
 *      	    internal address width, in bytes (0, 1, 2)
 * @param data      Data to write.  Data is written MSB first on the twsi bus, and
 *      	    only the lower num_bytes bytes of the argument are valid.  (If
 *      	    a 2 byte write is done, only the low 2 bytes of the argument is
 *      	    used.
 *
 * @return Zero on success, -1 on error
 */
int bdk_twsix_write_ia(bdk_node_t node, int twsi_id, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data)
{
    bdk_mio_twsx_sw_twsi_t sw_twsi_val;
    bdk_mio_twsx_sw_twsi_ext_t twsi_ext;
    int retry_limit = 5;
    int to;

    if (num_bytes < 1 || num_bytes > 8 || ia_width_bytes < 0 || ia_width_bytes > 2)
	return -1;

retry:
    twsi_ext.u = 0;
    sw_twsi_val.u = 0;
    sw_twsi_val.s.v = 1;
    sw_twsi_val.s.sovr = 1;
    sw_twsi_val.s.size = num_bytes - 1;
    sw_twsi_val.s.addr = dev_addr;
    sw_twsi_val.s.data = 0xFFFFFFFF & data;

    if (ia_width_bytes > 0)
    {
	sw_twsi_val.s.op = 1;
	sw_twsi_val.s.ia = (internal_addr >> 3) & 0x1f;
	sw_twsi_val.s.eop_ia = internal_addr & 0x7;
    }
    if (ia_width_bytes == 2)
    {
	sw_twsi_val.s.eia = 1;
	twsi_ext.s.ia = internal_addr >> 8;
    }
    if (num_bytes > 4)
	twsi_ext.s.data = data >> 32;

    BDK_CSR_WRITE(node, BDK_MIO_TWSX_SW_TWSI_EXT(twsi_id), twsi_ext.u);
    BDK_CSR_WRITE(node, BDK_MIO_TWSX_SW_TWSI(twsi_id), sw_twsi_val.u);
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MIO_TWSX_SW_TWSI(twsi_id), v, ==, 0, 10000))
    {
	bdk_warn("N%d.TWSI%d: Timeout waiting for write to complete...start recovering process\n",
		 node, twsi_id);
	/* perform bus recovery */
	bdk_twsix_recover_bus(node, twsi_id);
	if (retry_limit-- > 0)
	    goto retry;

	// After retry but still not success, report error and return
	bdk_error("N%d.TWSI%d: Timeout waiting for operation to complete\n", node, twsi_id);
	return -1;
    }

    /* Poll until reads succeed, or polling times out */
    to = 100;
    while (to-- > 0)
    {
	if (bdk_twsix_read_ia(node, twsi_id, dev_addr, 0, 1, 0) >= 0)
	    break;
    }
    if (to <= 0)
	return -1;

    return 0;
}

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

	/* use model as equivalent DTS if not specified */
	if ((info->equiv_dts[0] == 0) || (info->equiv_dts[0] == 0xff)) {
		strncpy(info->equiv_dts, info->model, sizeof(info->equiv_dts) - 1);
		info->equiv_dts[strlen(info->model)] = 0;
	}
	/* check model first, then equiv if still unknown */
	type = GW_UNKNOWN;
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
	case '5':
		type = GW650x;
		break;
	case '9':
		if (!strncmp("GW6903", info->model, 6))
			type = GW6903;
		break;
	}
	if (type == GW_UNKNOWN) {
		switch (info->equiv_dts[3]) {
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
		case '5':
			type = GW650x;
			break;
		case '9':
			if (!strncmp("GW6903", info->equiv_dts, 6))
				type = GW6903;
			break;
		}
	}
	if (type == GW_UNKNOWN) {
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
	for (i = strlen(info->equiv_dts) - 1; i > 0; i--) {
		if (info->equiv_dts[i] == '-')
			break;
		if (info->equiv_dts[i] >= '1' && info->equiv_dts[i] <= '9') {
			rev_bom = info->equiv_dts[i] - '0';
			break;
		}
	}

	/* determine PCB revision from model */
	for (i = strlen(info->equiv_dts) - 1; i > 0; i--) {
		if (info->equiv_dts[i] == '-')
			break;
		if (info->equiv_dts[i] >= 'A') {
			rev_pcb = info->equiv_dts[i];
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
		switch(rev_pcb) {
		case 'A':
		case 'B':
		case 'C':
			cfg->gpio_phyrst_pol = 1;
			break;
		}
		break;
	case GW630x:
		switch(rev_pcb) {
		case 'A':
			info->qlm[0] = 0xff;
			info->qlm[1] = 0xff;
			info->qlm[2] = 0xff;
			info->qlm[3] = 0xff;
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
			cfg->gpio_phyrst_pol = 1;
			cfg->gpio_satasel = 20;
			cfg->ext_temp = 0;
			break;
		case 'D':
			cfg->gpio_phyrst_pol = 1;
			cfg->gpio_satasel = -1;
			break;
		case 'E':
			cfg->gpio_phyrst_pol = 1;
			break;
		case 'F':
			if (!rev_bom)
				cfg->gpio_phyrst_pol = 1;
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
	case GW650x:
		break;
	case GW6903:
		switch(rev_pcb) {
		case 'A':
			cfg->gpio_ledred = 14;
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
	int tj_max, i;
	unsigned char buf;

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
	buf = 0x10;
	i2c_write(node, 0, MAX6642_SLAVE, MAX6642_W_CONFIG, &buf, 1);
	buf = tj_max;
	i2c_write(node, 0, MAX6642_SLAVE, MAX6642_W_LIMIT_LOCAL, &buf, 1);
	i2c_write(node, 0, MAX6642_SLAVE, MAX6642_W_LIMIT_REMOTE, &buf, 1);

	/* loop over status until clear */
	for (i = 0; i < 20; i++) {
		i2c_read(node, 0, MAX6642_SLAVE, MAX6642_R_STATUS, &buf, 1);
		if (!(buf & 0x50))
			break;
		bdk_wait_usec(500000);
	}

	return 0;
}

/* octeontx_chip_details: display details about cavium SoC */
static void
octeontx_chip_details(bdk_node_t node, struct newport_board_config *cfg)
{
	BDK_CSR_INIT(rst_boot, node, BDK_RST_BOOT);
	BDK_CSR_INIT(gpio_strap, node, BDK_GPIO_STRAP);
	const char *boot_method_str = "Unknown";
	int trust_mode = rst_boot.s.trusted_mode;
	int boot_method = bdk_extract(gpio_strap.u, 0, 4);
	int alt_pkg;
	int major_pass;
	int minor_pass;
	int i;

	BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
	alt_pkg = (mio_fus_dat2.s.chip_id >> 6) & 1;
	major_pass = ((mio_fus_dat2.s.chip_id >> 3) & 7) + 1;
	minor_pass = mio_fus_dat2.s.chip_id & 7;
	const char *package_str = (alt_pkg) ? " (alt pkg)" : "";
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
	BDK_CSR_INIT(gicd_iidr, node, BDK_GICD_IIDR);
	printf("0x%x Pass %d.%d%s ", gicd_iidr.s.productid,
	       major_pass, minor_pass, package_str);
	printf("\n");

	/* Boot devices */
	for (i = cfg->mmc_devs - 1; i >= 0; i--) {
		if (bdk_mmc_initialize(node, i) > 0)
			printf("MMC%d    : %s\n", i,
			       bdk_mmc_card_is_sd(node, i) ? "microSD":"eMMC");
		else
			printf("MMC%d    : not detected\n", i);
	}

	/* Boot device and mode*/
	switch (boot_method)
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
			bdk_config_set_str("EMMC",
					   BDK_CONFIG_BOOT_DEVICE, node);
			break;
		case BDK_RST_BOOT_METHOD_E_SPI24:
		case BDK_RST_BOOT_METHOD_E_SPI32:
			boot_method_str = "SPI";
			bdk_config_set_str("SPI",
					   BDK_CONFIG_BOOT_DEVICE, node);
			break;
	}
	printf("Boot    : %s %strusted%s\n", boot_method_str,
	       (trust_mode) ? "" : "non-", secure_image);
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

	bdk_twsix_initialize(node);

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
		i2c_read(node, 0, MAX6642_SLAVE, MAX6642_R_TEMP_REMOTE,
			&buf[0], 1);
		i2c_read(node, 0, MAX6642_SLAVE, MAX6642_R_LIMIT_REMOTE,
			&buf[1], 1);
		printf("Temp    : Board:%dC/86C CPU:%dC/%dC\n", t / 10,
			buf[0], buf[1]);
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
	/* put PHY's into reset */
	if (cfg->gpio_phyrst != -1)
		gpio_output(cfg->gpio_phyrst, cfg->gpio_phyrst_pol);
	/* Enable front-panel LEDs */
	if (cfg->gpio_ledblu != -1) {
		/* tri-color LED stack individually controlled active low */
		if (cfg->gpio_ledgrn != -1)
			gpio_output(cfg->gpio_ledgrn, 0);
		if (cfg->gpio_ledred != -1)
			gpio_output(cfg->gpio_ledred, 1);
		if (cfg->gpio_ledblu != -1)
			gpio_output(cfg->gpio_ledblu, 1);
	} else {
		/* bi-color LED stack push-pull active high */
		if (cfg->gpio_ledgrn != -1)
			gpio_output(cfg->gpio_ledgrn, 1);
		if (cfg->gpio_ledred != -1)
			gpio_output(cfg->gpio_ledred, 0);
	}
	/* Configure Mezzanine IO */
	if (cfg->gpio_mezz_pwrdis != -1)
		gpio_output(cfg->gpio_mezz_pwrdis, 0);
	if (cfg->gpio_mezz_irq != -1)
		gpio_input(cfg->gpio_mezz_irq);

	octeontx_chip_details(node, cfg);

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
	struct newport_board_info *info = &board_info;
	const char *model = info->equiv_dts;

	/* determine base model from model */
	for (i = 0;i < (int)strlen(model) && i < ((int)sizeof(base) - 1);i++) {
		char c = model[i];
		base[i] = (c >= 'A' && c <= 'Z') ? (c+32) : c;
	}
	base[i+1] = 0;
	p = strchr(base, '-');
	if (p)
		*p = 0;

	/* determine BOM revision from model */
	for (i = strlen(model) - 1; i > 0; i--) {
		if (model[i] == '-')
			break;
		if (model[i] >= '1' && model[i] <= '9') {
			rev_bom = model[i] - '0';
			break;
		}
	}

	/* determine PCB revision from model */
	for (i = strlen(model) - 1; i > 0; i--) {
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
