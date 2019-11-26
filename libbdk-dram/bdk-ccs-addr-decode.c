//Convert PA to LMC addr given just the PA

#include <bdk.h>

#include "libbdk-arch/bdk-csrs-ccs.h"
#include "libbdk-arch/bdk-csrs-lmc.h"

#include "bdk-ccs-addr-decode.h"

#define DEBUG_BDK_TRACE 0
#if DEBUG_BDK_TRACE
    #define debug_BDK_TRACE(bit, format, ...) BDK_TRACE(bit, format, ##__VA_ARGS__)
#else
    #define debug_BDK_TRACE(bit, format, ...) do {} while (0)
#endif

/* Hash Distribution Selector for Decode */
//                                  0  1  2  3  4  5  6  7  8  9 10 11
uint8_t bdk_lmc_quarter_selector[12] = {0, 0, 3, 0, 1, 1, 2, 1, 3, 2, 3, 2};
uint8_t bdk_lmc_phys_mask_selector[12] = {
    0x2, //0  - LMC1
    0x1, //1  - LMC0
    0x1, //2  - LMC0
    0x4, //3  - LMC2
    0x2, //4  - LMC1
    0x4, //5  - LMC2
    0x2, //6  - LMC1
    0x1, //7  - LMC0
    0x2, //8  - LMC1
    0x4, //9  - LMC2
    0x4, //10 - LMC2
    0x1, //11 - LMC0
};

/**
 * Perform a Reduction XOR operation and return result
 *
 * @param number    number to do reduction XOR on
 *
 * @return          0 if number of bits is even
 *                  1 if number of bits is odd
 */
int __rxor(uint64_t number)
{
    return bdk_dpop(number) & 1; //64 bit popcount
}

/**
 * Calculate what offset the LMC address given has from other
 * LMCs
 *
 * @param node      The node the address originated on
 * @param address   A full LMC address
 * @param lmc_num   The LMC the address originated from
 * @param add       Binary indicator to add or subtract the LMC offset
 *
 * @return An address offset by the memory on other LMCs
 */
uint64_t __bdk_ccs_offset_address(bdk_node_t node, int lmc_num, uint64_t address,  int add)
{
    //No offset. This address does not need to be changed
    if(lmc_num == 0)
        return address;
    else
    {
        uint64_t total_mem = 0;
        uint64_t mem_per_rank;
        uint64_t mem_on_channel;
        int lmc, num_ranks;

        //Calculate the amount of memory on channels before this one
        for (lmc = 0; lmc < lmc_num; lmc++)
        {
            BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(lmc));
            mem_per_rank = 1ULL << (28 + lmc_config.s.pbank_lsb - lmc_config.s.rank_ena);
            num_ranks = bdk_pop(lmc_config.s.init_status);
            mem_on_channel = mem_per_rank * num_ranks;
            total_mem += mem_on_channel;
        }

        //Add the memory to the address given
        if (add) {
            return address + total_mem;
        } else {
            //subtract the memory from the address given
            if (total_mem > address)
            {
                printf("ERROR this lmc addr does not need to be offset\n");
                return address;
            }
            return address - total_mem;
        }
    }
}

/**
 * Convert a Physical Address from the Cores into an LMC address
 *
 * @param node			Node the Phyisical Address came from
 * @param ccs_data		Data structure holding information on how to reconstruct the
 *						LMC address.
 *
 * @return 	on success	LMC address corresponding to the physical address provided
 *			on failure 	-1
 */

uint64_t bdk_ccs_convert_pa_to_lmc_algorithm(bdk_node_t node, bdk_ccs_addr_conversion_data_t *ccs_data)
{
    uint64_t _ccu_addr =        ccs_data->addr;
    int _md_lr_bit =            ccs_data->ASC_MD_LR_BIT;
    uint64_t _md_lr_en =        ccs_data->ASC_MD_LR_EN;
    int unsigned _lmc_mode =    ccs_data->ASC_LMC_MODE;
    int unsigned _lmc_msk =     ccs_data->ASC_LMC_MASK;

    uint64_t no_lr_addr;
    uint64_t pre_offset;
    uint64_t pre_addr;
    int lmc_mod6_hash;
    uint64_t no_lr_hash_addr;
    int md_right;
    int no_lr_mod6;
    int lmcquarter;
    int i;
    int lmc_mod6_hash_bits[NUM_MCS];
    uint64_t _mcs_en[NUM_MCS];

    debug_BDK_TRACE(CCS_DECODE, "Starting PA to LMC Conversion Algorithm\n");
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "_ccu_addr", _ccu_addr);

    for (i = 0; i < NUM_MCS; i++) {
        _mcs_en[i] = (ccs_data->ASC_MCS_EN[i]) >> 8;
    }

    //regenerate ADDR if L2C Index Aliasing enabled
    pre_addr = _ccu_addr;

    md_right = __rxor((_md_lr_en << 7) & pre_addr);
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre_addr", pre_addr);
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "_md_lr_en & pre_addr", (_md_lr_en << 7) & pre_addr);
    debug_BDK_TRACE(CCS_DECODE, "%-40s: %d\n", "md_right", md_right);

    if (_md_lr_bit == 0)
        no_lr_addr = pre_addr >> 8;
    else {
        uint64_t left_bits = (pre_addr >> (_md_lr_bit + 7)) << _md_lr_bit;
        uint64_t right_bits = pre_addr & (((1ULL << _md_lr_bit) -1) << 7);

        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "left_bits", left_bits);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "right_bits", right_bits);

        no_lr_addr = left_bits | right_bits;
    }

    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "no_lr_addr", no_lr_addr);

    for (i=0; i < NUM_MCS; i++) {
        debug_BDK_TRACE(CCS_DECODE, "MCS(%d): 0x%016lx no_lr_addr: 0x%016lx anded: 0x%016lx\n",
                  i, _mcs_en[i], no_lr_addr, _mcs_en[i] & no_lr_addr);

        lmc_mod6_hash_bits[i] = __rxor(_mcs_en[i] & no_lr_addr);
    }

    debug_BDK_TRACE(CCS_DECODE, "%-40s: [%d%d%d%d]\n", "lmc_mod6_hash_bits",
              lmc_mod6_hash_bits[3], lmc_mod6_hash_bits[2], lmc_mod6_hash_bits[1], lmc_mod6_hash_bits[0]);

    lmc_mod6_hash = 0;
    for (i=0; i<NUM_MCS; i++)
        lmc_mod6_hash |= (lmc_mod6_hash_bits[i] & 0x1) << i;
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "lmc_mod6_hash", lmc_mod6_hash);

    no_lr_hash_addr = (no_lr_addr & 0xFFFFFFFF0) | lmc_mod6_hash;
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "no_lr_hash_addr", no_lr_hash_addr);

    switch (_lmc_mode) {
    case BDK_CCS_LMC_MODE_E_FLAT_1:
        // entire region in single LMC
        pre_offset = (no_lr_hash_addr << 1) | md_right;
        pre_offset &= 0x7FFFFFFFF;
        //save AREM and phys_lmc_mask for later use
        ccs_data->ASC_REM = 0;
        ccs_data->phys_lmc_mask = _lmc_msk;

        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre_offset", pre_offset);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "phys_lmc_mask", ccs_data->phys_lmc_mask);
        break;

    case BDK_CCS_LMC_MODE_E_STRIPE_2:
        pre_offset = no_lr_hash_addr;
        ccs_data->ASC_REM = md_right;

        // region split evenly between 2 LMCs
        if (_lmc_msk == 0x3) { //LMC0 & LMC1
                                                //  LMC0  LMC1
            ccs_data->phys_lmc_mask = (md_right) ? 0x1 : 0x2;
        }
        else if (_lmc_msk == 0x5) { //LMC0 & LMC2
                                                //  LMC0  LMC2
            ccs_data->phys_lmc_mask = (md_right) ? 0x1 : 0x4;
        }
        else if (_lmc_msk == 0x6) { //LMC1 & LMC2
                                                //  LMC2  LMC1
            ccs_data->phys_lmc_mask = (md_right) ? 0x4 : 0x2;
        }
        else {
            BDK_TRACE(CCS_DECODE, "Error LMC Mask: %d not supported for STRIPE_2\n", _lmc_msk);
            return -1;
        }

        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre_offset", pre_offset);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "phys_lmc_mask", ccs_data->phys_lmc_mask);
        break;

    case BDK_CCS_LMC_MODE_E_STRIPE_3:
        no_lr_mod6 = no_lr_hash_addr % 6;
        no_lr_mod6 = no_lr_mod6 << 1 | md_right;
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "no_lr_mod6", no_lr_mod6);
        ccs_data->ASC_REM = no_lr_mod6;

        //reuse no_lr_mod6 to determine what lmc quarter and physical channel to use
        if ((no_lr_mod6 < 12) && (no_lr_mod6 >= 0))
        {
            lmcquarter = bdk_lmc_quarter_selector[no_lr_mod6];
            ccs_data->phys_lmc_mask = bdk_lmc_phys_mask_selector[no_lr_mod6];
        }
        else
        {
            //Something's wrong
            BDK_TRACE(CCS_DECODE, "Error: Address Does Not Convert into LMC addr correctly\n");
            return -1;
        }

        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "lmcquarter", lmcquarter);

        //no_lr_hash_addr is shifted left by 2 bits and then divided by 3
        //before being ored with lmcquarter
        pre_offset = ((no_lr_hash_addr/6) << 2) | lmcquarter;

        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre_offset", pre_offset);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "phys_lmc_mask", ccs_data->phys_lmc_mask);
        break;

    default:
        BDK_TRACE(CCS_DECODE, "Error LMC MODE Not Supported\n");
        return -1;
    }

    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "addr", pre_offset);
    return pre_offset;
}

/**
 * Unhash the physical address without the left right bit
 *
 * @param node				Node the address originates from
 * @param _pa_no_lr_hash	Hashed address without the left right bit
 * @param ccs_adr_mcs		BDK_CCS_ADR_MCSX data
 *
 * @return on Success		Unhashed LMC address without the left right bit
 *         on Failure		-1
 */

uint64_t __bdk_ccs_reverse_lmc_hash(bdk_node_t node, uint64_t _pa_no_lr_hash, uint64_t *ccs_adr_mcs)
{
    uint64_t pa_no_lr;
    uint64_t adr_mcs[4];
    int lmc_hash, i;
    int low_addr;
    int num_good_bits = 0;
    int upper_lmc_hash_parity[4];
    int lower_lmc_hash_parity;

    pa_no_lr = _pa_no_lr_hash & ~(0xfff);
    lmc_hash = (_pa_no_lr_hash >> 8) & 0xf;

    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre pa_no_lr", pa_no_lr);
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "lmc_hash", lmc_hash);

    for (i = 0; i < 4; i++) {
        adr_mcs[i] = ccs_adr_mcs[i];
        upper_lmc_hash_parity[i] = __rxor((adr_mcs[i] >> 12) & (pa_no_lr >> 12));
    }
    debug_BDK_TRACE(CCS_DECODE, "%-40s: [%d%d%d%d]\n", "upper_lmc_hash_parity",
              upper_lmc_hash_parity[0], upper_lmc_hash_parity[1], upper_lmc_hash_parity[2],
              upper_lmc_hash_parity[3]);

    // Loop all possible address values in bits [3:0] and check to see if exactly one matches.
    for (low_addr = 0; low_addr < 16; low_addr++) {
        num_good_bits = 0;
        for (i = 0; i < 4; i++) {
            lower_lmc_hash_parity = __rxor(((adr_mcs[i] >> 8) & 0xf) & low_addr);
            if ((lower_lmc_hash_parity ^ upper_lmc_hash_parity[i]) == ((lmc_hash >> i) & 0x1) )
                num_good_bits++;
        }
        if (num_good_bits == 4)
            break;
    }

    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "low_addr", low_addr);

    if (num_good_bits == 4)
        return pa_no_lr | (low_addr << 8);
    else
        return -1;
}

/**
 * Convert an LMC address into a Physical Address used coreside
 *
 * @param node		Node the Address Comes From
 * @param ccs_data 	Data used to decode the LMC Address
 *
 * @return  on success	Physical address coressponding to the LMC address
 *          on failure	-1
 */
uint64_t bdk_ccs_convert_lmc_to_pa_algorithm(bdk_node_t node, bdk_ccs_addr_conversion_data_t *ccs_data)
{
    uint64_t pre_offset     = ccs_data->addr;
    int region              = ccs_data->ASC_REGION;
    int ASC_MD_LR_BIT       = ccs_data->ASC_MD_LR_BIT;
    uint64_t ASC_MD_LR_EN   = ccs_data->ASC_MD_LR_EN;
    int ASC_LMC_MASK        = ccs_data->ASC_LMC_MASK;
    int ASC_LMC_MODE        = ccs_data->ASC_LMC_MODE;
    int phys_lmc_mask       = ccs_data->phys_lmc_mask;

    uint64_t pa_no_lr;
    uint64_t pa_no_lr_hash = 0;
    uint64_t pa;
    uint64_t gen_addr;
    uint64_t left_mask;
    uint64_t right_mask;

    int lrbit;
    int MD_mirror = 0;
    int MD_right = 0;
    int MD_right_calculated;
    int lmcquarter;
    int pa_no_lr_hash_mod6;

    debug_BDK_TRACE(CCS_DECODE, "Starting LMC to PA Conversion Algorithm\n");
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre_offset", pre_offset);

    //check if lmcmask and ASC LMC MASK intersect if not this region isn't mapped to this ASC
    if ((phys_lmc_mask & ASC_LMC_MASK) == 0) {
        BDK_TRACE(CCS_DECODE, "LMC mask 0x%x Does not Fit into ASC %d LMC_MASK 0x%x\n",
                  phys_lmc_mask, region, ASC_LMC_MASK);
        return -1;
    }

    switch(ASC_LMC_MODE) {

    case BDK_CCS_LMC_MODE_E_FLAT_1:
        MD_right = pre_offset & 0x1;
        //right shift by 1 to get bits 34:1
        //and left shift by 8 to move bits to [41:8]
        pa_no_lr_hash = (pre_offset >> 1);
        pa_no_lr_hash <<= 8;
        pa_no_lr_hash &= ((1ULL << 41) - 1); //Drop pa_no_lr_hash[42]

        debug_BDK_TRACE(CCS_DECODE, "%-40s: %d\n", "MD_right", MD_right);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pa_no_lr_hash", pa_no_lr_hash);
        break;

    case BDK_CCS_LMC_MODE_E_STRIPE_2:
        pa_no_lr_hash = (pre_offset << 8);
        //if phys_lmc_mask is LMC0 MD_right is 1 if it is LMC1 MD_right is 0
        if (ASC_LMC_MASK == 0x3)                    //LMC01
            MD_right = phys_lmc_mask & 0x1 ? 1 : 0;
        //if phys_lmc_mask is LMC0 MD_right is 1 if it is LMC2 MD_right is 0
        else if (ASC_LMC_MASK == 0x5)               //LMC02
            MD_right = phys_lmc_mask & 0x1 ? 1 : 0;
        //if phys_lmc_mask is LMC2 MD_right is 1 if it is LMC1 MD_right is 0
        else if (ASC_LMC_MASK == 0x6)               //LMC12
            MD_right = phys_lmc_mask & 0x4 ? 1 : 0;

        debug_BDK_TRACE(CCS_DECODE, "%-40s: %d\n", "MD_right", MD_right);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pa_no_lr_hash", pa_no_lr_hash);
        break;

    case BDK_CCS_LMC_MODE_E_STRIPE_3:
        lmcquarter = pre_offset & 0x3;
        pa_no_lr_hash_mod6 = 0;

        //Determine pa_no_lr_hash_mod6 and MD_right based upon which
        //LMC the addr came from and the LMC quarter
        if (phys_lmc_mask == 0x1) {     //LMC0
            MD_right = 1;
            if (lmcquarter == 0x0)
                pa_no_lr_hash_mod6 = 0;
            else if (lmcquarter == 0x1)
                pa_no_lr_hash_mod6 = 0x3;
            else if (lmcquarter == 0x2)
                pa_no_lr_hash_mod6 = 0x5;
            else if (lmcquarter == 0x3) {
                pa_no_lr_hash_mod6 = 0x1;
                MD_right = 0;
            } else {
                BDK_TRACE(CCS_DECODE, "ERROR: Unsupported lmc, lmcquarter: %x %x\n", phys_lmc_mask, lmcquarter);
                return -1;
            }
        }
        else if (phys_lmc_mask == 0x2) {  //LMC1
            MD_right = 0;
            if (lmcquarter == 0x0)
                pa_no_lr_hash_mod6 = 0;
            else if (lmcquarter == 0x1)
                pa_no_lr_hash_mod6 = 0x2;
            else if (lmcquarter == 0x2)
                pa_no_lr_hash_mod6 = 0x3;
            else if (lmcquarter == 0x3)
                pa_no_lr_hash_mod6 = 0x4;
            else {
                BDK_TRACE(CCS_DECODE, "ERROR: Unsupported lmc, lmcquarter: %x %x\n", phys_lmc_mask, lmcquarter);
                return -1;
            }
        }
        else if (phys_lmc_mask == 0x4) {  //LMC2
            MD_right = 1;
            if (lmcquarter == 0x0)
                pa_no_lr_hash_mod6 = 0x1;
            else if (lmcquarter == 0x1)
                pa_no_lr_hash_mod6 = 0x2;
            else if (lmcquarter == 0x2)
                pa_no_lr_hash_mod6 = 0x4;
            else if (lmcquarter == 0x3) {
                pa_no_lr_hash_mod6 = 0x5;
                MD_right = 0;
            } else {
                BDK_TRACE(CCS_DECODE, "ERROR: Unsupported lmc, lmcquarter: %x %x\n", phys_lmc_mask, lmcquarter);
                return -1;
            }
        }

        pa_no_lr_hash = (((pre_offset >> 2) * 6) + pa_no_lr_hash_mod6) << 8;

        debug_BDK_TRACE(CCS_DECODE, "%-40s: %d\n", "lmcquarter", lmcquarter);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%x\n", "pa_no_lr_hash_mod6", pa_no_lr_hash_mod6);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: %d\n", "MD_right", MD_right);
        debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pa_no_lr_hash", pa_no_lr_hash);

        break;

    default:
        BDK_TRACE(CCS_DECODE, "Unsupported lmc_mode: %x\n", ASC_LMC_MODE);
        return -1;
    }

    pa_no_lr = __bdk_ccs_reverse_lmc_hash(node, pa_no_lr_hash, ccs_data->ASC_MCS_EN);
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pa_no_lr", pa_no_lr);
    if (pa_no_lr == (uint64_t)-1)
	{
        BDK_TRACE(CCS_DECODE, "No Valid LMC Hash Combinations Work for lmc%0d address: %0lx.\n", phys_lmc_mask, pre_offset);
        return -1;
    }

    //left mask
    left_mask = ((1ULL << (42 - (ASC_MD_LR_BIT + 7))) - 1) << (ASC_MD_LR_BIT + 8);

    //right mask
    right_mask = (1ULL << (ASC_MD_LR_BIT + 8)) - 1;

    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%lx\n", "left_mask", left_mask);
    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%lx\n", "right_mask", right_mask);

    //pa_no_lr is currently bits 42:0 but bits 7:0 are left as 0
    pa = (pa_no_lr & left_mask) | ((pa_no_lr & right_mask) >> 1);

    debug_BDK_TRACE(CCS_DECODE, "%-40s: 0x%016lx\n", "pre_pa", pa);

    MD_right_calculated = __rxor((ASC_MD_LR_EN << 7) & pa) ^ MD_mirror;

    if (MD_right == MD_right_calculated)
        lrbit = 0;
    else
        lrbit = 1;

    gen_addr = (pa | lrbit << (ASC_MD_LR_BIT + 7));

    debug_BDK_TRACE(CCS_DECODE, "Generated Addr: 0x%016lx\n", gen_addr);
    return gen_addr;
}

static int prep_done = 0;
static bdk_ccs_addr_conversion_data_t  ccs_data;

static int __bdk_ccs_do_prep(bdk_node_t node)
{
    int i, region;

    if (!prep_done) {

        //memset(&ccs_data, 0, sizeof(bdk_ccs_addr_conversion_data_t));

        BDK_CSR_INIT(adr_ctl, node, BDK_CCS_ADR_CTL);
        ccs_data.ASC_MD_LR_BIT =   adr_ctl.s.md_lr_bit;
        ccs_data.ASC_MD_LR_EN =    adr_ctl.s.md_lr_en;

        for (i = 0; i < 4; i++)
            ccs_data.ASC_MCS_EN[i] = BDK_CSR_READ(node, BDK_CCS_ADR_MCSX(i));

        // extract the ASC region info
        BDK_CSR_INIT(ccs_const, node, BDK_CCS_CONST);
        int max_regions = ccs_const.s.asc;

        int idx = 0;
        for (region = 0; region < max_regions; region++) {

            //Check if the ASC Region is Enabled or not
            BDK_CSR_INIT(region_attr, node, BDK_CCS_ASC_REGIONX_ATTR(region));
            if ((region_attr.s.s_en == 0) && (region_attr.s.ns_en == 0))
                continue; //Region is disabled, go to the next

            // record the region's info
            ccs_data.regions_lmc_mode[idx] = region_attr.s.lmc_mode;
            ccs_data.regions_lmc_mask[idx] = region_attr.s.lmc_mask;
            BDK_CSR_INIT(start,  node, BDK_CCS_ASC_REGIONX_START(region));
            BDK_CSR_INIT(end,    node, BDK_CCS_ASC_REGIONX_END(region));
            BDK_CSR_INIT(offset, node, BDK_CCS_ASC_REGIONX_OFFSET(region));
            ccs_data.regions_start[idx]  = start.u;
            ccs_data.regions_end[idx]    = end.u;
            ccs_data.regions_offset[idx] = offset.u;

            idx++; // count it
        }
        ccs_data.num_regions = idx;

        prep_done = 1;
    }
    return 0;
}


#if 0
// FIXME: disabled pending debug
/**
 * Convert a Core Physical Address into an LMC number
 *
 * @param node			Node the Address Came from
 * @param addr			Physical Address
 *
 * @return 	on success	An LMC number
 * 		on failure	-1
 */
int bdk_quick_and_dirty_lmc_finder(bdk_node_t node, uint64_t addr)
{
    int md_right;
    uint8_t lmc_mode, lmc_mask;
    uint8_t hash_bits;
    uint64_t no_lr_hash_addr;
    uint8_t no_lr_mod6;
    int lmc, region, ret = 0;

    __bdk_ccs_do_prep(node);

    //set known variables
    addr &= ((1ULL << 43) - 1);

    for (region = 0; region < ccs_data.num_regions; region++)
    {
        //check if Addr fits within ASC Region ranges
        if (addr >= ccs_data.regions_start[region] && addr < ccs_data.regions_end[region])
        {
            lmc_mode = ccs_data.regions_lmc_mode[region];
            lmc_mask = ccs_data.regions_lmc_mask[region];
            break;
        }
    }
    if (region >= ccs_data.num_regions) {
        bdk_error("N%d: QD: ASC region not found for address 0x%016lX\n", node, addr);
        return -1;
    }
            
    addr -= ccs_data.regions_offset[region];
    md_right = __rxor((ccs_data.ASC_MD_LR_EN << 7) & addr);

    switch (lmc_mode) {
        case 0:
            lmc = 0; //only one
            while (!(lmc_mask & (1 << lmc)))
                lmc++;
            ret = lmc;
            break;
        case 2:
            if (lmc_mask == 0x3)
                ret = !md_right;
            else if (lmc_mask == 0x5)
                ret = (!md_right) * 2;
            else if (lmc_mask == 0x6)
                ret = md_right + 1;
            break;
        case 3:
            hash_bits = ((addr >> 8) & 0xe) |  (bdk_dpop(0x481249 & (addr >> 8)) & 1);
            no_lr_hash_addr = ((addr >> 8) & 0xFFFFFFFF0) | hash_bits;
            no_lr_mod6 = (no_lr_hash_addr % 6) << 1 | md_right;
            //                                    0  1  2  3  4  5  6  7  8  9 10 11
            uint8_t bdk_dirty_lmc_selector[12] = {1, 0, 0, 2, 1, 2, 1, 0, 1, 2, 2, 0};
            ret = bdk_dirty_lmc_selector[no_lr_mod6];
            break;
    }
    return ret;
}
#endif

/**
 * Convert a Core Physical Address into an LMC address
 *
 * @param node			Node the Address Came from
 * @param addr			Physical Address
 *
 * @return 	on success	A full LMC address pointing to the top of the cache
 *                      line where the error occurred
 * 			on failure	-1
 */
uint64_t bdk_ccs_convert_pa_to_lmc(bdk_node_t node, uint64_t addr)
{
    int region;
    uint64_t lmc_addr;
    uint64_t final_addr;
    int found_good_addr = 0;

    debug_BDK_TRACE(CCS_DECODE, "Starting PA to LMC Conversion\n");

    __bdk_ccs_do_prep(node);

    //set known variables
    ccs_data.addr = addr & ((1ULL << 43) - 1);

    for (region = 0; region < ccs_data.num_regions; region++)
    {
        //check if Addr fits within ASC Region ranges
        if ((addr >= ccs_data.regions_start[region]) && (addr < ccs_data.regions_end[region]))
        {
            //set region
            ccs_data.ASC_REGION = region;
            ccs_data.ASC_LMC_MODE  = ccs_data.regions_lmc_mode[region];
            ccs_data.ASC_LMC_MASK  = ccs_data.regions_lmc_mask[region];

            //Subtract offset from lmc address to get raw value
            ccs_data.ASC_OFFSET = ccs_data.regions_offset[region];
            ccs_data.addr = addr - ccs_data.ASC_OFFSET;

            debug_BDK_TRACE(CCS_DECODE, "Checking ASC:%d \n", region);
            debug_BDK_TRACE(CCS_DECODE, "Address:        0x%016lx\n", addr);
            debug_BDK_TRACE(CCS_DECODE, "ASC_MD_LR_BIT:  %d\n", ccs_data.ASC_MD_LR_BIT);
            debug_BDK_TRACE(CCS_DECODE, "ASC_MD_LR_EN:   0x%lx\n", ccs_data.ASC_MD_LR_EN);
            debug_BDK_TRACE(CCS_DECODE, "ASC_LMC_MASK:   %d\n", ccs_data.ASC_LMC_MASK);
            debug_BDK_TRACE(CCS_DECODE, "ASC_LMC_MODE:   %d\n", ccs_data.ASC_LMC_MODE);
            debug_BDK_TRACE(CCS_DECODE, "ASC_OFFSET:     0x%lx\n", ccs_data.ASC_OFFSET);

            //Convert address
            lmc_addr = bdk_ccs_convert_pa_to_lmc_algorithm(node, &ccs_data);

            //check if conversion failed
            if (lmc_addr == (uint64_t)-1) {
                BDK_TRACE(CCS_DECODE, "Address Conversion Failed for this region and channel\n");
                continue;
            } else {
                //check for Aliasing
                debug_BDK_TRACE(CCS_DECODE, "Generated LMC Addr:   0x%016lx\n", lmc_addr);

                final_addr = lmc_addr;
                found_good_addr = 1;
                break;
            }
        } /* if (addr >= start.u && addr < end.u) */
    } /* for (region = 0; region < ccs_const.s.asc; region++) */

    if (found_good_addr == 1) {
        debug_BDK_TRACE(CCS_DECODE, "Address Found!\n");
        //Calculate address offset to add for additional mem channels
        int lmc_num = 0;

        //Find out the LMC num from the LMC mask
        while (!(ccs_data.phys_lmc_mask & (1 << lmc_num)))
            lmc_num++;

        final_addr *= BDK_CACHE_LINE_SIZE;
        debug_BDK_TRACE(CCS_DECODE, "Pre Final LMC Addr:  0x%016lx LMC: %d\n\n", final_addr, lmc_num);
        final_addr = __bdk_ccs_get_lmc_addr(node, final_addr, lmc_num);
        debug_BDK_TRACE(CCS_DECODE, "Final LMC Addr:      0x%016lx\n\n", final_addr);
        return final_addr;

    } else {
        BDK_TRACE(CCS_DECODE, "Unable to Find a Physical Address that Maps to 0x%016lx in Current ASC Config.\n", addr);
        printf("CCS Decode - PA to LMC returned -1\n");
        return (uint64_t)-1;
    }
    BDK_TRACE(CCS_DECODE, "ERROR LMC address offset miscalculated!\n");
    return (uint64_t)-1;
}

/**
 * Convert a memory address from a LMC address in CN9XXX to
 * a physical address
 *
 * @param node          Node the Address came from
 * @param _lmc_addr     Full LMC Address including cache line bits
 *
 * @return 	on success	A physical address corresponding with the lmc address given
 * 			on failure	-1
 */
uint64_t bdk_ccs_convert_lmc_to_pa(bdk_node_t node, uint64_t _lmc_addr)
{
    int region;
    uint64_t phys_addr;
    uint64_t internal_lmc_addr;
    int found_good_addr = 0;
    uint64_t final_phys_addr = 0;
    int lmc;

    debug_BDK_TRACE(CCS_DECODE, "Starting LMC to PA Conversion\n");

    __bdk_ccs_do_prep(node);

    debug_BDK_TRACE(CCS_DECODE, "Original LMC ADDR: 0x%016lx\n", _lmc_addr);

    lmc = __bdk_ccs_find_lmc(node, _lmc_addr);
    internal_lmc_addr = __bdk_ccs_get_dram_addr(_lmc_addr);
    ccs_data.phys_lmc_mask = 0x1 << lmc;

    debug_BDK_TRACE(CCS_DECODE, "ADDR: 0x%016lx LMC origin: %d\n", internal_lmc_addr, lmc);

    for (region = 0; region < ccs_data.num_regions; region++)
    {
        // every counted region is enabled
        debug_BDK_TRACE(CCS_DECODE, "ASC%d: Checking Conversion from LMC to PA\n", region);

        ccs_data.ASC_REGION = region;
        ccs_data.ASC_LMC_MASK = ccs_data.regions_lmc_mask[region];
        ccs_data.ASC_LMC_MODE = ccs_data.regions_lmc_mode[region];

        ccs_data.addr = internal_lmc_addr/BDK_CACHE_LINE_SIZE;

        phys_addr = bdk_ccs_convert_lmc_to_pa_algorithm(node, &ccs_data);
        if (phys_addr == (uint64_t)-1) {
            BDK_TRACE(CCS_DECODE, "ASC%d: Failed to Convert LMC to Phys Addr\n", region);
            continue;
        } else {
            uint64_t scaled_offset = ccs_data.regions_offset[region];
            if (scaled_offset != 0) {
                switch (ccs_data.ASC_LMC_MODE) {
                case 0: /* BDK_CCS_LMC_MODE_E_FLAT_1 */
                    scaled_offset <<= 24; // 16 MB units
                    break; 
                case 2: /* BDK_CCS_LMC_MODE_E_STRIPE_2 */
                    scaled_offset <<= 25 ; // 32 MB units
                    break; 
                case 3: /* BDK_CCS_LMC_MODE_E_STRIPE_3 */
                    scaled_offset *= 3;
                    scaled_offset <<= 24; // 48 MB units
                    break; 
                }
            }
            final_phys_addr = (phys_addr - scaled_offset) & ((1ULL << 42) - 1);
            found_good_addr++;
            debug_BDK_TRACE(CCS_DECODE, "ASC%d: Found Phys Addr: 0x%016lx\n", region, final_phys_addr);
            break; // FIXME? no further checking now for overlap/etc...
        }
    }

    if (found_good_addr == 1)
        return bdk_numa_get_address(node, final_phys_addr);
    else {
        if (found_good_addr > 1)
            BDK_TRACE(CCS_DECODE, "ERROR FOUND ALIASING!\n");
        else
            BDK_TRACE(CCS_DECODE, "ERROR UNABLE TO FIND PHYS ADDR!\n");
        printf("CCS Decode - LMC to PA returned -1\n");
        return -1;
    }
}
