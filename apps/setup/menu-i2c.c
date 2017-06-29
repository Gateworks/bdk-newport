#include <bdk.h>

/*
 * I2C Functions similar to the standard memory functions.
 *
 * There are several parameters in many of the commands that bear further
 * explanations:
 *
 * {i2c_chip} is the I2C chip address (the first byte sent on the bus).
 *   Each I2C chip on the bus has a unique address.  On the I2C data bus,
 *   the address is the upper seven bits and the LSB is the "read/write"
 *   bit.  Note that the {i2c_chip} address specified on the command
 *   line is not shifted up: e.g. a typical EEPROM memory chip may have
 *   an I2C address of 0x50, but the data put on the bus will be 0xA0
 *   for write and 0xA1 for read.  This "non shifted" address notation
 *   matches at least half of the data sheets :-/.
 *
 * {addr} is the address (or offset) within the chip.  Small memory
 *   chips have 8 bit addresses.  Large memory chips have 16 bit
 *   addresses.  Other memory chips have 9, 10, or 11 bit addresses.
 *   Many non-memory chips have multiple registers and {addr} is used
 *   as the register index.  Some non-memory chips have only one register
 *   and therefore don't need any {addr} parameter.
 *
 *   The default {addr} parameter is one byte (.1) which works well for
 *   memories and registers with 8 bits of address space.
 *
 *   You can specify the length of the {addr} field with the optional .0,
 *   .1, or .2 modifier (similar to the .b, .w, .l modifier).  If you are
 *   manipulating a single register device which doesn't use an address
 *   field, use "0.0" for the address and the ".0" length field will
 *   suppress the address in the I2C data stream.  This also works for
 *   successive reads using the I2C auto-incrementing memory pointer.
 *
 *   If you are manipulating a large memory with 2-byte addresses, use
 *   the .2 address modifier, e.g. 210.2 addresses location 528 (decimal).
 *
 *   Then there are the unfortunate memory chips that spill the most
 *   significant 1, 2, or 3 bits of address into the chip address byte.
 *   This effectively makes one chip (logically) look like 2, 4, or
 *   8 chips.  This is handled (awkwardly) by #defining
 *   CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW and using the .1 modifier on the
 *   {addr} field (since .1 is the default, it doesn't actually have to
 *   be specified).  Examples: given a memory chip at I2C chip address
 *   0x50, the following would happen...
 *     i2c md 50 0 10   display 16 bytes starting at 0x000
 *                      On the bus: <S> A0 00 <E> <S> A1 <rd> ... <rd>
 *     i2c md 50 100 10 display 16 bytes starting at 0x100
 *                      On the bus: <S> A2 00 <E> <S> A3 <rd> ... <rd>
 *     i2c md 50 210 10 display 16 bytes starting at 0x210
 *                      On the bus: <S> A4 10 <E> <S> A5 <rd> ... <rd>
 *   This is awfully ugly.  It would be nice if someone would think up
 *   a better way of handling this.
 *
 * Adapted from cmd_mem.c which is copyright Wolfgang Denk (wd@denx.de).
 */

#define simple_strtoul strtoull
#define udelay(x) bdk_wait_usec(x)
#define be32_to_cpu __builtin_bswap32
#define cpu_to_be32 __builtin_bswap32
#undef putc
#define putc(x) printf("%c", x)
#undef puts // common puts inserts a CR when it shouldn't
#define puts(x) printf("%s", x)

#define uint	uint8_t
#define ulong	uint32_t
#define uchar	uint8_t

/* Display values from last command.
 * Memory modify remembered values are different from display memory.
 */
static uint	i2c_dp_last_chip;
static uint	i2c_dp_last_addr;
static uint	i2c_dp_last_alen;
static uint	i2c_dp_last_length = 0x10;

static uint	i2c_mm_last_chip;
static uint	i2c_mm_last_addr;
static uint	i2c_mm_last_alen;

static uint	i2c_bus_no = 0;

/* If only one I2C bus is present, the list of devices to ignore when
 * the probe command is issued is represented by a 1D array of addresses.
 * When multiple buses are present, the list is an array of bus-address
 * pairs.  The following macros take care of this */

#define DISP_LINE_LEN	16
#define DEFAULT_ADDR_LEN	1
#define CMD_RET_FAILURE	-1
#define CMD_RET_USAGE -2
#define CMD_FLAG_REPEAT 1

static char i2c_help_text[] =
/*
	"crc32 chip address[.0, .1, .2] count - compute CRC32 checksum\n"
*/
	"i2c dev [dev] - show or set current I2C bus\n"
	"i2c loop chip address[.0, .1, .2] [# of objects] - looping read of device\n"
	"i2c md chip address[.0, .1, .2] [# of objects] - read from I2C device\n"
	"i2c mm chip address[.0, .1, .2] - write to I2C device (auto-incrementing)\n"
	"i2c mw chip address[.0, .1, .2] value [count] - write to I2C device (fill)\n"
	"i2c nm chip address[.0, .1, .2] - write to I2C device (constant address)\n"
	"i2c probe [address] - test for and show device(s) on the I2C bus\n"
	"i2c read chip address[.0, .1, .2] length memaddress - read to memory\n"
	"i2c write memaddress chip address[.0, .1, .2] length [-s] - write memory\n"
	"          to I2C; the -s option selects bulk write in a single transaction\n"
	"i2c speed [speed] - show or set I2C bus speed";

static int
cmd_usage(void)
{
	printf("%s\n", i2c_help_text);
	return CMD_RET_USAGE;
}

static int
cmd_get_data_size(char* arg, int default_size)
{
	/* Check for a size specification .b, .w or .l.
	 */
	int len = strlen(arg);
	if (len > 2 && arg[len-2] == '.') {
		switch (arg[len-1]) {
		case 'b':
			return 1;
		case 'w':
			return 2;
		case 'l':
			return 4;
		case 'q':
			return 8;
		case 's':
			return -2;
		default:
			return -1;
		}
	}
	return default_size;
}

static int
i2c_probe(uint8_t chip)
{
	bdk_node_t node = bdk_numa_master();
#if 0 // i2c probe should be a 'quick write' but that always fails here
printf("%s: chip=0x%02x ret=%d\n", __func__, chip, ret);
	return bdk_twsix_write_ia(node, i2c_bus_no, chip, 0, 0, 0, 0);
#else
	int64_t data;

	data = bdk_twsix_read_ia(node, i2c_bus_no, chip, 0, 1, 1);
//printf("%s: chip=0x%02x data=%ld\n", __func__, chip, data);
	return (data == -1) ? -1 : 0;
#endif
}

static int
i2c_read(uint8_t chip, uint8_t devaddr, int alen, unsigned char *buf, int len)
{
	bdk_node_t node = bdk_numa_master();
	int64_t data;
	int i;

//printf("%s: chip=0x%02x devaddr=0x%02x alen=%d len=%d\n", __func__, chip, devaddr, alen, len);
	// TODO: up to 4 bytes can be written to at a time - were only doing 1
	// TODO: alen 0 ok?
	for (i = 0; i < len; i += (alen) ? alen : 1) {
		data = bdk_twsix_read_ia(node, i2c_bus_no, chip, devaddr + i,
					 1, alen);
		if (data == -1) {
			printf("i2c_read i2c%d@0x%02x 0x%02x failed\n",
				i2c_bus_no, chip, devaddr + i);
			return -1;
		}
		switch (alen) {
		case 0:
			break;
		case 1:
//			printf("i2c%d@0x%02x 0x%02x<<0x%02x\n", i2c_bus_no,
//				chip, devaddr + i, (uint8_t) data);
			*buf = (uint8_t) data;
			break;
		case 2:
//			printf("i2c%d@0x%02x 0x%02x<<0x%04x\n", i2c_bus_no,
//				chip, devaddr + i, (uint16_t) data);
			*buf = (uint16_t) data;
			break;
		}
		buf += alen;
	}
	return 0;
}

static int
i2c_write(uint8_t chip, uint8_t devaddr, int alen, unsigned char *buf, int len)
{
	bdk_node_t node = bdk_numa_master();
	int64_t err;
	int i;

//printf("%s: chip=0x%02x devaddr=0x%02x alen=%d len=%d\n", __func__, chip, devaddr, alen, len);
	// TODO: up to 8 bytes can be written to at a time, were only doing 1
	// TODO: alen 0 ok?
	for (i = 0; i < len; i += (alen) ? alen : 1) {
		err = bdk_twsix_write_ia(node, i2c_bus_no, chip, devaddr + i, 1,
					 alen, (uint64_t) *(buf + i));
		if (err) {
			printf("i2c%d@0x%02x 0x%02x failed: %ld\n",
				i2c_bus_no, chip, devaddr, err);
			return err;
		}
		switch (alen) {
		case 0:
		case 1:
//			printf("i2c%d@0x%02x 0x%02x>>%02x\n", i2c_bus_no, chip,
//				devaddr, (uint8_t)*(buf + i));
			break;
		case 2:
//			printf("i2c%d@0x%02x 0x%02x>>%04x\n", i2c_bus_no, chip,
//				devaddr,(uint16_t)*(buf + i));
			break;
		}
	}
	return 0;
}

/**
 * get_alen() - Small parser helper function to get address length
 *
 * Returns the address length.
 */
static uint get_alen(char *arg, int default_len)
{
	int	j;
	int	alen;

	alen = default_len;
	for (j = 0; j < 8; j++) {
		if (arg[j] == '.') {
			alen = arg[j+1] - '0';
			break;
		} else if (arg[j] == '\0')
			break;
	}
	return alen;
}

enum i2c_err_op {
	I2C_ERR_READ,
	I2C_ERR_WRITE,
};

static int i2c_report_err(int ret, enum i2c_err_op op)
{
	printf("Error %s the chip: %d\n",
	       op == I2C_ERR_READ ? "reading" : "writing", ret);

	return CMD_RET_FAILURE;
}

/**
 * do_i2c_md() - Handle the "i2c md" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 *
 * Syntax:
 *	i2c md {i2c_chip} {addr}{.0, .1, .2} {len}
 */
static int do_i2c_md (int flag, int argc, char * const argv[])
{
	uint	chip;
	uint	addr, length;
	int alen;
	int	j, nbytes, linebytes;
	int ret;

	/* We use the last specified parameters, unless new ones are
	 * entered.
	 */
	chip   = i2c_dp_last_chip;
	addr   = i2c_dp_last_addr;
	alen   = i2c_dp_last_alen;
	length = i2c_dp_last_length;

	if (argc < 3)
		return CMD_RET_USAGE;

	if ((flag & CMD_FLAG_REPEAT) == 0) {
		/*
		 * New command specified.
		 */

		/*
		 * I2C chip address
		 */
		chip = simple_strtoul(argv[1], NULL, 0);

		/*
		 * I2C data address within the chip.  This can be 1 or
		 * 2 bytes long.  Some day it might be 3 bytes long :-).
		 */
		addr = simple_strtoul(argv[2], NULL, 0);
		alen = get_alen(argv[2], DEFAULT_ADDR_LEN);
		if (alen > 3)
			return CMD_RET_USAGE;

		/*
		 * If another parameter, it is the length to display.
		 * Length is the number of objects, not number of bytes.
		 */
		if (argc > 3)
			length = simple_strtoul(argv[3], NULL, 0);
	}

	/*
	 * Print the lines.
	 *
	 * We buffer all read data, so we can make sure data is read only
	 * once.
	 */
	nbytes = length;
	do {
		unsigned char	linebuf[DISP_LINE_LEN];
		unsigned char	*cp;

		linebytes = (nbytes > DISP_LINE_LEN) ? DISP_LINE_LEN : nbytes;

		ret = i2c_read(chip, addr, alen, linebuf, linebytes);
		if (ret)
			return i2c_report_err(ret, I2C_ERR_READ);
		else {
			printf("%04x:", addr);
			cp = linebuf;
			for (j=0; j<linebytes; j++) {
				printf(" %02x", *cp++);
				if (((j - 1) % 8) == 0)
					printf("  ");
				addr++;
			}
			puts ("    ");
			cp = linebuf;
			for (j=0; j<linebytes; j++) {
				if ((*cp < 0x20) || (*cp > 0x7e))
					puts (".");
				else
					printf("%c", *cp);
				cp++;
			}
			putc ('\n');
		}
		nbytes -= linebytes;
	} while (nbytes > 0);

	i2c_dp_last_chip   = chip;
	i2c_dp_last_addr   = addr;
	i2c_dp_last_alen   = alen;
	i2c_dp_last_length = length;

	return 0;
}

/**
 * do_i2c_mw() - Handle the "i2c mw" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 *
 * Syntax:
 *	i2c mw {i2c_chip} {addr}{.0, .1, .2} {data} [{count}]
 */
static int do_i2c_mw (int flag, int argc, char * const argv[])
{
	uint	chip;
	ulong	addr;
	int	alen;
	uchar	byte;
	int	count;
	int ret;

	if ((argc < 4) || (argc > 5))
		return CMD_RET_USAGE;

	/*
	 * Chip is always specified.
	 */
	chip = simple_strtoul(argv[1], NULL, 0);

	/*
	 * Address is always specified.
	 */
	addr = simple_strtoul(argv[2], NULL, 0);
	alen = get_alen(argv[2], DEFAULT_ADDR_LEN);
	if (alen > 3)
		return CMD_RET_USAGE;

	/*
	 * Value to write is always specified.
	 */
	byte = simple_strtoul(argv[3], NULL, 0);

	/*
	 * Optional count
	 */
	if (argc == 5)
		count = simple_strtoul(argv[4], NULL, 0);
	else
		count = 1;

	while (count-- > 0) {
		ret = i2c_write(chip, addr++, alen, &byte, 1);
		if (ret)
			return i2c_report_err(ret, I2C_ERR_WRITE);
		/*
		 * Wait for the write to complete.  The write can take
		 * up to 10mSec (we allow a little more time).
		 */
		udelay(11000);
	}

	return 0;
}

#if 0
/**
 * do_i2c_crc() - Handle the "i2c crc32" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Calculate a CRC on memory
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 *
 * Syntax:
 *	i2c crc32 {i2c_chip} {addr}{.0, .1, .2} {count}
 */
static int do_i2c_crc (int flag, int argc, char * const argv[])
{
	uint	chip;
	ulong	addr;
	int	alen;
	int	count;
	uchar	byte;
	ulong	crc;
	ulong	err;
	int ret = 0;

	if (argc < 4)
		return CMD_RET_USAGE;

	/*
	 * Chip is always specified.
	 */
	chip = simple_strtoul(argv[1], NULL, 0);

	/*
	 * Address is always specified.
	 */
	addr = simple_strtoul(argv[2], NULL, 0);
	alen = get_alen(argv[2], DEFAULT_ADDR_LEN);
	if (alen > 3)
		return CMD_RET_USAGE;

	/*
	 * Count is always specified
	 */
	count = simple_strtoul(argv[3], NULL, 0);

	printf ("CRC32 for %08lx ... %08x ==> ", addr, addr + count - 1);
	/*
	 * CRC a byte at a time.  This is going to be slooow, but hey, the
	 * memories are small and slow too so hopefully nobody notices.
	 */
	crc = 0;
	err = 0;
	while (count-- > 0) {
		ret = i2c_read(chip, addr, alen, &byte, 1);
		if (ret)
			err++;
		crc = crc32 (crc, &byte, 1);
		addr++;
	}
	if (err > 0)
		i2c_report_err(ret, I2C_ERR_READ);
	else
		printf ("0x%08lx\n", crc);

	return 0;
}
#endif

/**
 * mod_i2c_mem() - Handle the "i2c mm" and "i2c nm" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Modify memory.
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 *
 * Syntax:
 *	i2c mm{.b, .w, .l} {i2c_chip} {addr}{.0, .1, .2}
 *	i2c nm{.b, .w, .l} {i2c_chip} {addr}{.0, .1, .2}
 */
static int
mod_i2c_mem(int incrflag, int flag, int argc, char * const argv[])
{
	uint	chip;
	ulong	addr;
	int	alen;
	ulong	data;
	int	size = 1;
	int	nbytes;
	int ret;

	if (argc != 3)
		return CMD_RET_USAGE;

	/*
	 * We use the last specified parameters, unless new ones are
	 * entered.
	 */
	chip = i2c_mm_last_chip;
	addr = i2c_mm_last_addr;
	alen = i2c_mm_last_alen;

	if ((flag & CMD_FLAG_REPEAT) == 0) {
		/*
		 * New command specified.  Check for a size specification.
		 * Defaults to byte if no or incorrect specification.
		 */
		size = cmd_get_data_size(argv[0], 1);

		/*
		 * Chip is always specified.
		 */
		chip = simple_strtoul(argv[1], NULL, 0);

		/*
		 * Address is always specified.
		 */
		addr = simple_strtoul(argv[2], NULL, 0);
		alen = get_alen(argv[2], DEFAULT_ADDR_LEN);
		if (alen > 3)
			return CMD_RET_USAGE;
	}

	/*
	 * Print the address, followed by value.  Then accept input for
	 * the next value.  A non-converted value exits.
	 */
	do {
		printf("0x%08x:", addr);
		ret = i2c_read(chip, addr, alen, (uchar *)&data, size);
		if (ret)
			return i2c_report_err(ret, I2C_ERR_READ);

		data = cpu_to_be32(data);
		if (size == 1)
			printf(" 0x%02x", (data >> 24) & 0x000000FF);
		else if (size == 2)
			printf(" 0x%04x", (data >> 16) & 0x0000FFFF);
		else
			printf(" 0x%08x", data);

		//nbytes = cli_readline(" ? ");
		//if (nbytes == 0)
		const char *p = bdk_readline(" ? ", NULL, 0);
		if (!*p)
		{
			/*
			 * <CR> pressed as only input, don't modify current
			 * location and move to next.
			 */
			if (incrflag)
				addr += size;
			nbytes = size;
		}
		else {
			char *endp;

			//data = simple_strtoul(console_buffer, &endp, 0);
			data = simple_strtoul(p, &endp, 0);
			if (size == 1)
				data = data << 24;
			else if (size == 2)
				data = data << 16;
			data = be32_to_cpu(data);
			//nbytes = endp - console_buffer;
			nbytes = endp - p;
			if (nbytes) {
				ret = i2c_write(chip, addr, alen,
						(uchar *)&data, size);
				if (ret)
					return i2c_report_err(ret,
							      I2C_ERR_WRITE);
				if (incrflag)
					addr += size;
			}
		}
	} while (nbytes);

	i2c_mm_last_chip = chip;
	i2c_mm_last_addr = addr;
	i2c_mm_last_alen = alen;

	return 0;
}

/**
 * do_i2c_probe() - Handle the "i2c probe" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 *
 * Syntax:
 *	i2c probe {addr}
 *
 * Returns zero (success) if one or more I2C devices was found
 */
static int do_i2c_probe (int flag, int argc, char * const argv[])
{
	int j;
	int addr = -1;
	int found = 0;
	int ret;

	if (argc == 2)
		addr = simple_strtoul(argv[1], 0, 0);

	puts ("Valid chip addresses:");
	for (j = 0; j < 128; j++) {
		if ((0 <= addr) && (j != addr))
			continue;

		ret = i2c_probe(j);
		if (ret == 0) {
			printf(" 0x%02X", j);
			found++;
		}
	}
	putc ('\n');

	return (0 == found);
}

/**
 * do_i2c_loop() - Handle the "i2c loop" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 *
 * Syntax:
 *	i2c loop {i2c_chip} {addr}{.0, .1, .2} [{length}] [{delay}]
 *	{length} - Number of bytes to read
 *	{delay}  - A DECIMAL number and defaults to 1000 uSec
 */
static int do_i2c_loop(int flag, int argc, char * const argv[])
{
	uint	chip;
	int alen;
	uint	addr;
	uint	length;
	u_char	bytes[16];
	int	delay;
	int ret;

	if (argc < 3)
		return CMD_RET_USAGE;

	/*
	 * Chip is always specified.
	 */
	chip = simple_strtoul(argv[1], NULL, 0);

	/*
	 * Address is always specified.
	 */
	addr = simple_strtoul(argv[2], NULL, 0);
	alen = get_alen(argv[2], DEFAULT_ADDR_LEN);
	if (alen > 3)
		return CMD_RET_USAGE;

	/*
	 * Length is the number of objects, not number of bytes.
	 */
	length = 1;
	length = simple_strtoul(argv[3], NULL, 0);
	if (length > sizeof(bytes))
		length = sizeof(bytes);

	/*
	 * The delay time (uSec) is optional.
	 */
	delay = 1000;
	if (argc > 3)
		delay = simple_strtoul(argv[4], NULL, 10);
	/*
	 * Run the loop...
	 */
	while (1) {
		ret = i2c_read(chip, addr, alen, bytes, length);
		if (ret)
			i2c_report_err(ret, I2C_ERR_READ);
		udelay(delay);
	}

	/* NOTREACHED */
	return 0;
}

/**
 * do_i2c_bus_num() - Handle the "i2c dev" command-line command
 * @cmdtp:      Command data struct pointer
 * @flag:       Command flag
 * @argc:       Command-line argument count
 * @argv:       Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 */
static int do_i2c_bus_num(int flag, int argc, char * const argv[])
{
	int ret = 0;

	if (argc == 1) {
		printf("Current bus is %d\n", i2c_bus_no);
	} else {
		i2c_bus_no = simple_strtoul(argv[1], NULL, 10);
		printf("Setting bus to %d\n", i2c_bus_no);
	}

	return ret ? CMD_RET_FAILURE : 0;
}

/**
 * do_i2c_mm() - Handle the "i2c mm" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 */
static int do_i2c_mm(int flag, int argc, char * const argv[])
{
	return mod_i2c_mem (1, flag, argc, argv);
}

/**
 * do_i2c_nm() - Handle the "i2c nm" command-line command
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 */
static int do_i2c_nm(int flag, int argc, char * const argv[])
{
	return mod_i2c_mem (0, flag, argc, argv);
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

void
menu_i2c(bdk_menu_t *parent, char key, void *arg)
{
	int argc;
	char *args[10];
	char line[64];

	cmd_usage();
	line[0] = 0;
	while (1) {
		char **argv = args;
		const char *r;

		r = bdk_readline("I2C > ", NULL, 0);
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
		if (argc < 1) {
			cmd_usage();
			continue;
		}
/*
		else if (strcasecmp(argv[0], "crc32") == 0)
			do_i2c_crc(0, argc, argv);
*/
		else if (strcasecmp(argv[0], "loop") == 0)
			do_i2c_loop(0, argc, argv);
		else if (strcasecmp(argv[0], "md") == 0)
			do_i2c_md(0, argc, argv);
		else if (strcasecmp(argv[0], "mm") == 0)
			do_i2c_mm(0, argc, argv);
		else if (strcasecmp(argv[0], "mw") == 0)
			do_i2c_mw(0, argc, argv);
		else if (strcasecmp(argv[0], "nm") == 0)
			do_i2c_nm(0, argc, argv);
		else if (strcasecmp(argv[0], "probe") == 0)
			do_i2c_probe(0, argc, argv);
		else if (strcasecmp(argv[0], "dev") == 0)
			do_i2c_bus_num(0, argc, argv);
		else
			cmd_usage();
	}
}
