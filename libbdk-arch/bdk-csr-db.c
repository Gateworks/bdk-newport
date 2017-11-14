/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>

extern const __bdk_csr_db_map_t __bdk_csr_db[];
extern const __bdk_csr_db_type_t __bdk_csr_db_csr[];
extern const uint16_t __bdk_csr_db_fieldList[];
extern const __bdk_csr_db_field_t __bdk_csr_db_field[];
extern const int __bdk_csr_db_range[];
extern const char __bdk_csr_db_string[];
extern const uint64_t __bdk_csr_db_number[];

/* This will point to one of the "data" arrays listed in __bdk_csr_db. The
    numbers index __bdk_csr_db_csr[] to find the CSR. The last one is zero,
    which has a null CSR at __bdk_csr_db_csr[0] */
static const int16_t *csr_list = NULL;

/**
 * Check if a supplied value is in a CSR range
 *
 * @param rangeid Range ID to check against
 * @param value   Value to check range on
 * @param next    If supplied, this is filled with the next valid value in the range. If the
 *                current value is the last one, then this is set to -1. If value
 *                is invalid, then this will be set to -1.
 *
 * @return Zero if the supplied value is valid. Negative if it is not
 */
static int __bdk_csr_check_range(int rangeid, int value, int *next)
{
    /* Ranges are stored as a length followed by min/max pairs. Length is always
        a multiple of 2 */
    int range_len = __bdk_csr_db_range[rangeid];
    int i = rangeid+1;
    while (range_len)
    {
        range_len -= 2;
        if ((value >= __bdk_csr_db_range[i]) && (value <= __bdk_csr_db_range[i+1]))
        {
            if (next)
            {
                if (value + 1 <= __bdk_csr_db_range[i+1])
                    *next = value + 1;
                else if (range_len)
                    *next = __bdk_csr_db_range[i+2];
                else
                    *next = -1;
            }
            return 0;
        }
        i += 2;
    }
    if (next)
        *next = -1;
    return -1;

}


/**
 * Given a name, find the CSR associated with it.
 *
 * @param name   Name to find. It can contain extra range info in parenthesis
 * @param offset Filled with the argument in parenthesis from the name
 * @param block  Filled with the argument in parenthesis from the name
 *
 * @return Index into csr_list table, or -1 on failure
 */
int __bdk_csr_lookup_index(const char *name, int params[])
{
    if (!csr_list)
    {
        /* Search the CSR DB for a csr map for this chip */
        const __bdk_csr_db_map_t *map = __bdk_csr_db;
        while (map->model && !CAVIUM_IS_MODEL(map->model))
            map++;
        if (map->model == 0)
        {
            bdk_error("CSR lookup can't find this chip\n");
            return -1;
        }
        csr_list = map->data;
    }

    /* Return the first DB entry if no name was supplied */
    if (name == NULL)
        return 0;

    /* Extract the CSR index info from the name */
    char *compare = strdup(name);
    char *ptr = strchr(compare, '(');
    int arg_count;
    if (ptr)
    {
        arg_count = sscanf(ptr+1, " %d, %d, %d, %d", &params[0], &params[1], &params[2], &params[3]);
        *ptr = 0;
    }
    else
        arg_count = 0;
    for (int i=arg_count; i<BDK_CSR_DB_MAX_PARAM; i++)
        params[i] = -1;

    /* Search the DB for this CSR */
    int index=0;
    const __bdk_csr_db_type_t *db = &__bdk_csr_db_csr[csr_list[index]];
    while (db->width)
    {
        if (strcasecmp(compare, __bdk_csr_db_string + db->name_index*2) == 0)
            break;
        index++;
        db = &__bdk_csr_db_csr[csr_list[index]];
    }
    free(compare);

    /* Fail if we reached the end of the list without finding it */
    if (db->width == 0)
        return -1;

    /* Fail if range in invalid */
    for (int i=0; i<BDK_CSR_DB_MAX_PARAM; i++)
    {
        if (__bdk_csr_check_range(db->range[i], params[i], NULL))
        {
            //bdk_error("CSR lookup with invalid offset\n");
            return -1;
        }
    }

    return index;
}


/**
 * Given a name, find the CSR associated with it.
 *
 * @param name   Name to find. It can contain extra range info in parenthesis
 * @param offset Filled with the argument in parenthesis from the name
 * @param block  Filled with the argument in parenthesis from the name
 *
 * @return Non NULL on success
 */
static const __bdk_csr_db_type_t *__bdk_csr_lookup(const char *name, int params[])
{
    int db_index = __bdk_csr_lookup_index(name, params);
    /* Fail if we can't find the CSR */
    if (db_index == -1)
    {
        bdk_error("CSR lookup can't find this CSR\n");
        return NULL;
    }
    return &__bdk_csr_db_csr[csr_list[db_index]];
}


/**
 * Figure out the address of a CSR given its DB entry and range arguments
 *
 * @param db     DB entry for CSR
 * @param offset Offset inside block
 * @param block  Block index
 *
 * @return Address of CSR
 */
static uint64_t __bdk_csr_lookup_address(const __bdk_csr_db_type_t *db, int params[])
{
    uint64_t address = __bdk_csr_db_number[db->base_index];
    for (int i=0; i<BDK_CSR_DB_MAX_PARAM; i++)
    {
        if (params[i] != -1)
            address += __bdk_csr_db_number[db->param_inc[i]] * params[i];
    }
    return address;
}


/**
 * Decode a CSR in a human readable format
 *
 * @param name   Name of CSR to decode
 * @param value  Value to decode
 *
 * @return Zero on success, negative on failure
 */
int bdk_csr_decode(const char *name, uint64_t value)
{
    int params[BDK_CSR_DB_MAX_PARAM] = {-1, -1, -1, -1};
    const __bdk_csr_db_type_t *db = __bdk_csr_lookup(name, params);
    int num_fields;

    /* Fail if we can't find the CSR */
    if (!db)
        return -1;

    /* Print the official CSR name */
    printf("%s", __bdk_csr_db_string + db->name_index*2);
    if (params[0] != -1)
    {
        printf("(%d", params[0]);
        for (int i=1; i<BDK_CSR_DB_MAX_PARAM; i++)
        {
            if (params[i] != -1)
                printf(",%d", params[i]);
            else
                break;
        }
        printf(")");
    }

    /* Print the address and value */
    printf("[0x%016llx] = 0x%016llx\n", (unsigned long long)__bdk_csr_lookup_address(db, params), (unsigned long long)value);

    num_fields = __bdk_csr_db_fieldList[db->field_index];
    while (num_fields--)
    {
        int field = __bdk_csr_db_fieldList[db->field_index + 1 + num_fields];
        const char *field_name = __bdk_csr_db_string + __bdk_csr_db_field[field].name_index*2;
        int start_bit = __bdk_csr_db_field[field].start_bit;
        int stop_bit = __bdk_csr_db_field[field].stop_bit;
        int size_bits = stop_bit - start_bit + 1;
        uint64_t v = (value >> start_bit);
        if(size_bits < 64)
            v = v & ~((~0x0ull) << size_bits);
        if (size_bits == 1)
            printf("  [   %2d] %-20s = %10llu (0x%llx)\n", start_bit, field_name,
                (unsigned long long)v, (unsigned long long)v);
        else
            printf("  [%2d:%2d] %-20s = %10llu (0x%llx)\n", stop_bit, start_bit, field_name,
                (unsigned long long)v, (unsigned long long)v);
    }
    return 0;
}


/**
 * Lookup a field by knowning its CSR and start_bit. By starting
 * at zero, you can walk all fields.
 *
 * @param csr_name   CSR to lookup field for
 * @param field_start_bit
 *                   Starting bit of field
 * @param field_name Constant character pointer to receive the address of the field name.
 *
 * @return Width of the field, or negative on failure.
 */
int bdk_csr_field(const char *csr_name, int field_start_bit, const char **field_name)
{
    int params[BDK_CSR_DB_MAX_PARAM] = {-1, -1, -1, -1};
    const __bdk_csr_db_type_t *db = __bdk_csr_lookup(csr_name, params);
    int num_fields;
    int i;

    /* Fail if we can't find the CSR */
    if (!db)
        return -1;

    num_fields = __bdk_csr_db_fieldList[db->field_index];
    i = db->field_index + 1;
    while (num_fields--)
    {
        int field = __bdk_csr_db_fieldList[i++];
        int start_bit = __bdk_csr_db_field[field].start_bit;
        if (start_bit == field_start_bit)
        {
            int stop_bit = __bdk_csr_db_field[field].stop_bit;
            *field_name = __bdk_csr_db_string + __bdk_csr_db_field[field].name_index*2;
            return stop_bit - start_bit + 1;
        }
    }
    return -1;
}


/**
 * Do a CSR read based on the string name of a CSR
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param name   Name of CSR to read
 *
 * @return Zero on failure or the CSR value
 */
uint64_t bdk_csr_read_by_name(bdk_node_t node, const char *name)
{
    int params[BDK_CSR_DB_MAX_PARAM] = {-1, -1, -1, -1};
    const __bdk_csr_db_type_t *db = __bdk_csr_lookup(name, params);
    if (!db)
        return 0;

#ifndef BDK_BUILD_HOST
    return bdk_csr_read(node, db->type, params[0], db->width,
        __bdk_csr_lookup_address(db, params));
#else
    extern uint64_t thunder_remote_read_csr(bdk_node_t node, bdk_csr_type_t type, int busnum, int size, uint64_t address);
    return thunder_remote_read_csr(node, db->type, params[0], db->width,
        __bdk_csr_lookup_address(db, params));
#endif
}


/**
 * Do a CSR write based on the string name of a CSR
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param name   Name of the CSR to write
 * @param value  Value to write
 *
 * @return Zero on success, negative on failure
 */
int bdk_csr_write_by_name(bdk_node_t node, const char *name, uint64_t value)
{
    int params[BDK_CSR_DB_MAX_PARAM] = {-1, -1, -1, -1};
    const __bdk_csr_db_type_t *db = __bdk_csr_lookup(name, params);
    if (!db)
        return -1;
#ifndef BDK_BUILD_HOST
    bdk_csr_write(node, db->type, params[0], db->width,
        __bdk_csr_lookup_address(db, params), value);
#else
    extern void thunder_remote_write_csr(bdk_node_t node, bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value);
    thunder_remote_write_csr(node, db->type, params[0], db->width,
        __bdk_csr_lookup_address(db, params), value);
#endif
    return 0;
}


/**
 * Get a CSR name. This is menat to be used to iterate through all
 * possible CSR names.
 *
 * @param last_name Get the CSR following this name. Supply NULL for the first CSR
 * @param buffer    Buffer to fill with the CSR name
 *
 * @return Zero on success, negative on list end or failure
 */
int bdk_csr_get_name(const char *last_name, char *buffer)
{
    int params[BDK_CSR_DB_MAX_PARAM] = {-1, -1, -1, -1};
    const __bdk_csr_db_type_t *db;

    /* Find our current DB spot */
    int db_index = __bdk_csr_lookup_index(last_name, params);
    if (db_index == -1)
        return -1;
    db = &__bdk_csr_db_csr[csr_list[db_index]];

    /* We we are continuing we need to process the range data and figure out what is next */
    if (last_name)
    {
        int need_next_csr = 1;
        for (int p=BDK_CSR_DB_MAX_PARAM-1; p>=0; p--)
        {
            /* Skip unused params */
            if (params[p] == -1)
                continue;
            int next = -1;
            /* Make sure the current param is valid */
            if (__bdk_csr_check_range(db->range[p], params[p], &next))
                return -1;
            /* Special check alert. CN88XX TNS block has two registers that
               read/write the packet memory. These have huge address ranges, so
               only return index 0 for these */
            {
                const char *name = __bdk_csr_db_string + db->name_index * 2;
                if (strncmp(name, "TNS_PM_", 7) == 0)
                    next = -1;
            }
            /* If there isn't a next, we may need to increment the next param */
            if (next == -1)
            {
                /* This param goes back to the lowest index */
                params[p] = __bdk_csr_db_range[db->range[p]+1];
                if (p>0)
                    continue;
                else
                {
                    need_next_csr = 1;
                    break;
                }
            }
            else
            {
                params[p] = next;
                need_next_csr = 0;
                break;
            }
        }
        if (need_next_csr)
        {
            /* End of params, so skip to next CSR */
            db = &__bdk_csr_db_csr[csr_list[++db_index]];
            for (int i=0; i<BDK_CSR_DB_MAX_PARAM; i++)
                params[i] = __bdk_csr_db_range[db->range[i]+1];
        }
    }
    else
    {
        /* Fill in params for the first DB entry */
        for (int i=0; i<BDK_CSR_DB_MAX_PARAM; i++)
            params[i] = __bdk_csr_db_range[db->range[i]+1];
    }

    /* End of list, return failure */
    if (db->width == 0)
        return -1;

    /* Fill in the next name */
    if (buffer)
    {
        buffer += sprintf(buffer, "%s", __bdk_csr_db_string + db->name_index*2);
        if (params[0] != -1)
        {
            buffer += sprintf(buffer, "(%d", params[0]);
            for (int i=1; i<BDK_CSR_DB_MAX_PARAM; i++)
            {
                if (params[i] != -1)
                    buffer += sprintf(buffer, ",%d", params[i]);
                else
                    break;
            }
            buffer += sprintf(buffer, ")");
        }
    }

    return 0;
}

/**
 * Returns a list of CSRs in the format required by bdk_readline tab completion.
 * This allows bdk_readline to automatically support tab completion for lines
 * starting with "csr".
 *
 * @return CSR table or NULL if CSRs aren't available
 */
struct bdk_readline_tab* __bdk_csr_get_tab_complete()
{
    static bdk_readline_tab_t *tab = NULL;
    if (tab)
        return tab;

    /* Make sure csr_list is initialized and get our first index */
    int index = __bdk_csr_lookup_index(NULL, NULL);
    const __bdk_csr_db_type_t *db = &__bdk_csr_db_csr[csr_list[index]];
    /* Count the number of CSRs */
    int csr_count = 0;
    while (db->width)
    {
        csr_count++;
        index++;
        db = &__bdk_csr_db_csr[csr_list[index]];
    }
    /* Allocate a tab complete table */
    tab = malloc((csr_count + 1) * sizeof(bdk_readline_tab_t));
    if (!tab)
        return NULL;
    /* Fill the table with base names */
    for (index = 0; index < csr_count; index++)
    {
        db = &__bdk_csr_db_csr[csr_list[index]];
        tab[index].str = __bdk_csr_db_string + db->name_index * 2;
        tab[index].next = NULL;
    }
    /* Mark the end of the table */
    tab[csr_count].str = NULL;
    tab[csr_count].next = NULL;

    return tab;
}
