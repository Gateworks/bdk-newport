#ifndef _GSC_H_
#define _GSC_H_

#include <bdk.h>

/* i2c slave addresses */
#define GSC_SC_ADDR		0x20
#define GSC_RTC_ADDR		0x68
#define GSC_HWMON_ADDR		0x29
#define GSC_EEPROM_ADDR		0x51

/* MAX6642 temperature sensor */
#define MAX6642_SLAVE		0x4a
#define MAX6642_R_TEMP_LOCAL	0x00
#define MAX6642_R_TEMP_REMOTE	0x01
#define MAX6642_R_STATUS	0x02
#define MAX6642_R_CONFIG	0x03
#define MAX6642_R_LIMIT_LOCAL	0x05
#define MAX6642_R_LIMIT_REMOTE	0x07
#define MAX6642_W_CONFIG	0x09
#define MAX6642_W_LIMIT_LOCAL	0x0b
#define MAX6642_W_LIMIT_REMOTE	0x0d
#define MAX6642_R_TEMP_LOCAL_E	0x10
#define MAX6642_R_TEMP_REMOTE_E	0x11

#define i2c_read_byte(n, b, a, r)				\
	(uint8_t) bdk_twsix_read_ia(n, b, a, r, 1, 1)
#define i2c_write_byte(n, b, a, r, v) 				\
	bdk_twsix_write_ia(n, b, a, r, 1, 1, (uint64_t) v)	\

struct newport_board_info;
struct newport_board_config;

int gsc_init(bdk_node_t node);
int gsc_read_eeprom(bdk_node_t node);
int gsc_eeprom_update(bdk_node_t node);
int gsc_program(bdk_node_t node);
int gsc_watchdog_config(bdk_node_t node, int timeout);
int gsc_sleep(bdk_node_t node, unsigned long secs);
int gsc_boot_wd_disable(bdk_node_t node, bool leave_enabled);
int gsc_hwmon_reg(bdk_node_t node, int reg);
int gsc_board_temp(bdk_node_t node);
const char *gsc_get_dtb_name(bdk_node_t node, int level);
const char *gsc_get_rst_cause(bdk_node_t node);
void menu_gsc(bdk_menu_t *parent, char key, void *arg);
void hexdump(unsigned char *buf, int size);
struct newport_board_config *gsc_get_board_config(void);
struct newport_board_info *gsc_get_board_info(void);
int gsc_get_board_model(void);
int gsc_get_fwver(void);

#endif
