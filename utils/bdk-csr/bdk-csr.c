#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <bdk.h>

#define BDK_NODE_0 0

static inline uint64_t bdk_build_mask(uint64_t bits)
{
    if (bits == 64)
        return -1;
    else
        return ~((~0x0ull) << bits);
}

static uint64_t read64(const char *str)
{
    unsigned long long val = 0;
    /* Only try decimal for short input */
    if (strlen(str) < 7)
    {
        errno = 0;
        int count = sscanf(str, "%lli", &val);
        if (!errno && (count == 1))
            return val;
    }
    errno = 0;
    int count = sscanf(str, "%llx", &val);
    if (!errno && (count == 1))
        return val;
    printf("ERROR converting %s to a number\n", str);
    return -1;
}

int main(int argc, const char **argv)
{
    if (argc < 2)
        goto usage;
    if (argc > 3)
        goto usage;

    uint64_t name_num = 0;
    uint64_t value_num = 0;

    const char *name = argv[1];
    if ((name[0] >= '0') && (name[0] <= '9'))
        name_num = read64(argv[1]);

    if (argc >= 3)
        value_num = read64(argv[2]);

    if (name_num)
    {
        int status = bdk_csr_decode_by_address(name_num, value_num);
        if (status)
        {
            printf("Unable to find register %s\n", name);
            return 1;
        }
    }
    else
    {
        int status = bdk_csr_decode(name, value_num);
        if (status)
        {
            printf("Unable to find register %s\n", name);
            return 1;
        }
    }
    return 0;

usage:
    printf("Usage: bdk-csr NAME/ADDRESS [VALUE]\n");
    return 1;
}

uint32_t thunder_remote_get_model(void)
{
    return OCTEONTX_CN96XX_PASS1_0;
}

uint64_t thunder_remote_read_csr(bdk_node_t node, bdk_csr_type_t type, int busnum, int size, uint64_t address)
{
    return -1;
}

void thunder_remote_write_csr(bdk_node_t node, bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value)
{
}

