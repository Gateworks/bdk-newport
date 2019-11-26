//Code to convert between LMC Addresses and Physical Addresses on the Chip

//structure to hold address decoding info
#define NUM_MCS 4
typedef struct {
    uint64_t addr;          //uint64_t addr;
    int phys_lmc_mask;      //MASK of LMC
    int num_regions;
    uint64_t regions_start[16], regions_end[16], regions_offset[16];
    uint8_t regions_lmc_mode[16], regions_lmc_mask[16];
    int ASC_REGION;
    int ASC_REM;
    int ASC_MD_LR_BIT;      //Left Right Bit selector
    int ASC_LMC_MASK;		//Mask of Channels enabled
    int ASC_LMC_MODE;		//Mode region is setup as
    uint64_t ASC_MD_LR_EN;	//Bit mask of Address bits used in hash
    uint64_t ASC_OFFSET;	//Address offset
    uint64_t ASC_MCS_EN[NUM_MCS];	//Bit Masks for Hashing
} bdk_ccs_addr_conversion_data_t;

/**
 * Add 2 bits into the LMC address to represent the LMC the address
 * came from. (like the CN8xxx LMC address configuration)
 *
 * @param node  Node the address came from
 * @param addr  an LMC address without LMC bits
 * @param lmc   The LMC the address originated from
 *
 * @return an LMC address with LMC Bits
 */
static inline uint64_t __bdk_ccs_get_lmc_addr(bdk_node_t node, uint64_t addr, int lmc)
{
    return  (((((((1ULL << 36)-1) << 7) & addr) << 2) |
            (0x7f & addr)) | ((lmc & 0x3) << 7)) | ((uint64_t)node << 46);
}

/**
 * Remove the two bits from an interal LMC address that represent the
 * LMC the address is on and return just the DRAM bits
 *
 * @param addr  an LMC address with LMC bits
 *
 * @return an LMC address without LMC Bits
 */
static inline uint64_t __bdk_ccs_get_dram_addr(uint64_t addr)
{
    return  (((((1ULL << 36)-1) << 9) & addr) >> 2) |
            (0x7f & addr);
}

/**
 * Extract the LMC from the address provided
 *
 * @param address   A full LMC address with LMC bits indicating
 *                  which lmc it came from
 *
 * @return the LMC the address originated on
 */
static inline int __bdk_ccs_find_lmc(bdk_node_t node, uint64_t address)
{
    return (address >> 7) & 0x3;
}

extern uint64_t __bdk_ccs_offset_address(bdk_node_t node, int lmc_num, uint64_t address,  int add);

//Algorithm for Converting LMC addresses into Physiscal Address
extern uint64_t bdk_ccs_convert_lmc_to_pa_algorithm(bdk_node_t node, bdk_ccs_addr_conversion_data_t *addr_data);

//Conversion code will cycle through enabled ASC regions, and LMCs, and return A physical addr
extern uint64_t bdk_ccs_convert_lmc_to_pa(bdk_node_t node, uint64_t addr);

//Algorithm for Converting Physiscal Address into LMC addresses
extern uint64_t bdk_ccs_convert_pa_to_lmc_algorithm(bdk_node_t node, bdk_ccs_addr_conversion_data_t *addr_data);

//Conversion Code will cycle through enable ASC regions and return an LMC Address
extern uint64_t bdk_ccs_convert_pa_to_lmc(bdk_node_t node, uint64_t _ccu_addr);

//Conversion Code will cycle through enable ASC regions and return only an LMC number
extern int bdk_quick_and_dirty_lmc_finder(bdk_node_t node, uint64_t addr);
