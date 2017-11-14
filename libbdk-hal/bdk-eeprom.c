#include <bdk.h>

BDK_REQUIRE_DEFINE(EEPROM);

//int64_t bdk_twsix_read_ia(bdk_node_t node, int twsi_id, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes)


//int bdk_twsix_write_ia(bdk_node_t node, int twsi_id, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data)

/*
// 0c - 0x02
// 0d - 0x0a
// 04 - 0x85 -> 0b0100_0101
// 03 - 0x01 -> 0x02
//unsigned char ddr4_spd[64] = {

// #0 - 40
//0x23,0x11,0x0C,0x02,0x45,0x21,0x00,0x08,0x00,0x60,0x00,0x03,0x02,0x0A,0x80,0x00,
//0x00,0x00,0x07,0x0D,0xF8,0x7F,0x00,0x00,0x6E,0x6E,0x6E,0x11,0x00,0x6E,0xF0,0x0A,
//0x20,0x08,0x00,0x05,0x00,0xA8,0x1B,0x28,0x28,

// #117 - 127
//0x00,0x9C,0xB5,0x00,0x00,0x00,0x00,0xE7,0xD6,0x57,0x26,

// #130 - 131
//0x23,0x05,

// #133 - 138
//0x80,0xB3,0x30,0x00,0x00,0x00,

// #325, #329
//0x00, 0x00,
//};
        //DDR-CONFIG-SPD-DATA.DIMM%d.LMC%d.N%d
        DDR-CONFIG-SPD-DATA.DIMM0.LMC0.N0 = [23 11 0C 02 45 21 00 08 00 60 00 03 02 0A 80 00
         00 00 07 0D F8 7F 00 00 6E 6E 6E 11 00 6E F0 0A
         20 08 00 05 00 A8 1B 28 28
         00 9C B5 00 00 00 00 E7 D6 57 26
         23 05
         80 B3 30 00 00 00
         00 00 00 00];

*/
struct group{
	int addr;
	unsigned char cnt;
};


unsigned char spddata[256] = {0x23, 0x11, 0x0C, 0x02, 0x45, 0x21, 0x00, 0x08, 0x00, 0x60, 0x00, 0x03, 0x02, 0x0A, 0x80, 0x00,
                0x00, 0x00, 0x07, 0x0D, 0xF8, 0x7F, 0x00, 0x00, 0x6E, 0x6E, 0x6E, 0x11, 0x00, 0x6E, 0xF0, 0x0A,
                0x20, 0x08, 0x00, 0x05, 0x00, 0xA8, 0x1B, 0x28, 0x28,
                0x00, 0x9C, 0xB5, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xD6, 0x57, 0x26,
                0x23, 0x05,
                0x80, 0xB3, 0x30, 0x00, 0x00, 0x00,
                /*0x00, 0x00, 0x00, 0x00*/};

struct group spd_group[10] = { {0, 41}, {117, 11}, {130, 2}, {133, 6}, /*{325, 4},*/ {0, 0}};

static uint16_t ddr3_crc16(uint8_t *ptr, int count)
{
    /* From DDR3 spd specification */
    int crc, i;
    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (int)*ptr++ << 8;
        for (i = 0; i < 8; ++i)
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
    }
    return crc & 0xFFFF;
}



int bdk_spd_eeprom_dump(int twsi_id_spd, uint8_t dev_addr_spd){
	bdk_node_t node = 0;
	int twsi_id = twsi_id_spd;
	uint8_t dev_addr = dev_addr_spd;
	//uint16_t internal_addr =0;
	int num_bytes = 1;
	int ia_width_bytes = 1;

	uint8_t eeprom[512] = {0};

	int j=0, p=0;
	int64_t data;

	int start;
	int len = 0;
	uint16_t n;

	int start_gap;
	int len_gap;

	while(spd_group[j].cnt !=0){
		start = spd_group[j].addr;
		len   = spd_group[j].cnt; 

		p = start;
		for(n=start; n < start + len; n++){
			data = bdk_twsix_read_ia(node, twsi_id, dev_addr, n, num_bytes, ia_width_bytes);
			//data = (uint64_t)spddata[p++];
			if(data < 0){
				printf("spd read error\n");
				return data;
			}else{
				eeprom[p] = (uint8_t)data;
			}
			p++;
		}

		start_gap = start + len;
		len_gap = spd_group[j+1].addr - start_gap;

		
		for(n=start_gap; n < start_gap + len_gap; n++){
			data = bdk_twsix_read_ia(node, twsi_id, dev_addr, n, num_bytes, ia_width_bytes);
			//data = (uint64_t)spddata[p++];
			if(data < 0){
				printf("spd read error\n");
				return data;
			}else{
				eeprom[n] = (uint8_t)data;
			}
			//eeprom[n] = 0x00;
		}
		j++;
	}

	printf("EEPROM contents:\n");
	for(int i=0; i < 256; i++){
		if(i % 16 == 0){
			printf("%02X: ", i);
		}
		printf("%02x ", eeprom[i]);
		if((i+1) % 16 == 0){
			printf("\n");
		}
	}
	return 0;
}
			
		

int bdk_spd_eeprom_prog(int twsi_id_spd, uint8_t dev_addr_spd){
	bdk_node_t node = 0;
	int twsi_id = twsi_id_spd;
	uint8_t dev_addr = dev_addr_spd;
	//uint16_t internal_addr =0;
	int num_bytes = 1;
	int ia_width_bytes = 1;

	uint8_t eeprom[512] = {0};

	uint8_t data;
	int ret = 0;
	int p=0;
	int start;
	int len = 0;
	uint16_t n,j=0;
	int start_gap;
	int len_gap;



	while(spd_group[j].cnt !=0){
		start = spd_group[j].addr;
		len   = spd_group[j].cnt; 

		for(n=start; n < start + len; n++){
			data = spddata[p++];
			ret = bdk_twsix_write_ia(node, twsi_id, dev_addr, n, num_bytes, ia_width_bytes, (uint64_t)data);
			//data = n;
			if(ret < 0){
				printf("spd write error\n");
				return ret;
			}else{
				eeprom[n] = data;
				//eeprom[n] = (uint8_t)data;
			}
		}

		start_gap = start + len;
		len_gap = spd_group[j+1].addr - start_gap;

		
		for(n=start_gap; n < start_gap + len_gap; n++){
			eeprom[n] = 0xFF;
			ret = bdk_twsix_write_ia(node, twsi_id, dev_addr, n, num_bytes, ia_width_bytes, eeprom[n]);
			if(ret < 0){
				printf("spd gap write error\n");
				return ret;
			}else{
				//eeprom[n] = (uint8_t)data;
			}

		}
		j++;
	}

	uint16_t crc_comp = ddr3_crc16(eeprom, 126);

	eeprom[126] = (uint8_t)(crc_comp & 0xFF);
	eeprom[127] = (uint8_t)((crc_comp >> 8) & 0xFF);
	for(n=126; n < 128; n++){
			ret = bdk_twsix_write_ia(node, twsi_id, dev_addr, n, num_bytes, ia_width_bytes, eeprom[n]);
			if(ret < 0){
				printf("spd CRC write error\n");
				return ret;
			}else{
				//eeprom[n] = spddata[n];
			}

	}


	printf("EEPROM contents:\n");
	for(int i=0; i < 256; i++){
		if(i % 16 == 0){
			printf("%02X: ", i);
		}
		printf("%02x ", eeprom[i]);
		if((i+1) % 16 == 0){
			printf("\n");
		}
	}
	return 0;
}








