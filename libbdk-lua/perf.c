/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-l2c_cbc.h"
// Module for interfacing with performance counters

/* L2 has two logical groups of counters that are of interest:
    1) CBC Bus utilization counters in:
        L2C_CBCX_XMCX_PFC(row, col)
        L2C_CBCX_XMDX_PFC(row, col)
        L2C_CBCX_RSCX_PFC(row, col)
        L2C_CBCX_RSDX_PFC(row, col)
        L2C_CBCX_IOCX_PFC(row, 0)
        L2C_CBCX_IORX_PFC(row, 0)
        L2C_CBCX_INVX_PFC(row, 0-1)
    2) TAD statistics from BDK_L2C_TADX_PFCX(tad, counter). There are
        fewer counters than interesting statistics, so we need to change
        counter setups over time to get all stats.
    The Lua output table format:
    {
        "cmb" = {
            "cmb0" = {
                "xmc(add) %" = (percent utilization)
                "xmd(store) %" = (percent utilization)
                "rsc(commit) %" = (percent utilization)
                "rsd(fill) %" = (percent utilization)
                "num invalidates" = (percent utilization)
            }
            "cmb1" = {...}
            "cmb2" = {...}
            ...
            "cmbX" = {...} # X=9 for CN88XX
        }
        "io" = {
            "io0" = {
                "ioc(IO req) %" = (percent utilization)
                "ior(IO resp) %" = (percent utilization)
            }
            "io1" = {...}
            "io2" = {...}
            "io3" = {...}
        }
        tad = {
            "tad0" = {
                "tag_hit(num/s)" = (number)
                "tag_miss(num/s)" = (number)
                "tag_noalloc(num/s)" = (number)
                "victim(num/s)" = (number)
                "sc_fail(num/s)" = (number)
                "sc_pass(num/s)" = (number)
                "lfb_occupancy %" = (percent utilization)
                "lfb_wait_lfb %" = (percent utilization)
                "lfb_wait_vab %" = (percent utilization)
                "quad0_index_bus %" = (percent utilization)
                "quad0_read_bus %" = (percent utilization)
                "quad0_banks_inuse %" = (percent utilization)
                "quad0_wdat_inuse %" = (percent utilization)
                (repeat quad1-qaud3)
            }
            "tad1" = {...}
            "tad2" = {...}
            ...
            "tad7" = {...}
        }
    }
*/


static void get_table(lua_State* L, const char *name)
{
    lua_getfield(L, -1, name);
    if (!lua_istable(L, -1))
    {
        /* Pop the non-table value we just got */
        lua_pop(L, 1);
        /* Create a new table for use by name */
        lua_newtable(L);
        /* Attach the table to the name */
        lua_setfield(L, -2, name);
        /* Get the table again */
        lua_getfield(L, -1, name);
    }
}

static void l2_perf_cmb(lua_State* L, bdk_node_t node)
{
    /* These define the array bounds for L2C_CBCX_*X_PFC */
    const int  L2_BUS_ROWS = bdk_is_model(OCTEONTX_CN83XX) ? 2 : 1;
    const int L2_BUS_COLS = bdk_is_model(OCTEONTX_CN81XX) ? 2 : 3;
    const int L2_NUM_IOB = bdk_is_model(OCTEONTX_CN81XX) ? 1 : 2;

    /* This is the time of the last update for each counter */
    static uint64_t last_start;

    uint64_t current_rclk = bdk_clock_get_count(BDK_CLOCK_RCLK);
    uint64_t delta_rclk = current_rclk - last_start;
    uint64_t delta_rclk_percent = delta_rclk / 100;
    if (delta_rclk_percent == 0)
        delta_rclk_percent = 1;
    last_start = current_rclk;

    for (int row = 0; row < L2_BUS_ROWS; row++)
    {
        for (int col = 0; col < L2_BUS_COLS; col++)
        {
            int cmb_num = col * L2_BUS_ROWS + row;
            if (cmb_num > 9)
                continue;
            char bus_name[8];
            if (cmb_num < 8)
                snprintf(bus_name, sizeof(bus_name), "cmb%d", cmb_num);
            else
                snprintf(bus_name, sizeof(bus_name), "iobn%d", cmb_num - 8);
            get_table(L, bus_name);

            /* Counts the number of cycles the XMC(Add bus) was busy. So the
                percentage used is simply 100 * count / RCLK */
            lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_XMCX_PFC(row, col)) / delta_rclk_percent);
            BDK_CSR_WRITE(node, BDK_L2C_CBCX_XMCX_PFC(row, col), 0);
            lua_setfield(L, -2, "xmc(add) %");
            /* Counts the number of cycles the XMD(Store bus) was busy. So the
                percentage used is simply 100 * count / RCLK */
            lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_XMDX_PFC(row,col)) / delta_rclk_percent);
            BDK_CSR_WRITE(node, BDK_L2C_CBCX_XMDX_PFC(row,col), 0);
            lua_setfield(L, -2, "xmd(store) %");
            /* Counts the number of cycles the RSC(Commit bus) was busy. So the
                percentage used is simply 100 * count / RCLK */
            lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_RSCX_PFC(row,col)) / delta_rclk_percent);
            BDK_CSR_WRITE(node, BDK_L2C_CBCX_RSCX_PFC(row,col), 0);
            lua_setfield(L, -2, "rsc(commit) %");
            /* Counts the number of cycles the RSD(Fill bus) was busy. So the
                percentage used is simply 100 * count / RCLK */
            lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_RSDX_PFC(row,col)) / delta_rclk_percent);
            BDK_CSR_WRITE(node, BDK_L2C_CBCX_RSDX_PFC(row,col), 0);
            lua_setfield(L, -2, "rsd(fill) %");
            /* It's not obvious, but column 2 (CMB 8-9) correspond to IOB, which
               doesn't have invalidates */
            if (col < L2_NUM_IOB)
            {
                /* Number of invalidates */
                lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_INVX_PFC(row,col)));
                BDK_CSR_WRITE(node, BDK_L2C_CBCX_INVX_PFC(row,col), 0);
                lua_setfield(L, -2, "num invalidates");
            }
            /* Pop the current CMB table as were done */
            lua_pop(L, 1);
        }
    }
}

static void l2_perf_io(lua_State* L, bdk_node_t node)
{
    const int L2_NUM_IO = bdk_is_model(OCTEONTX_CN83XX) ? 2 : 1;

    /* This is the time of the last update for each counter */
    static uint64_t last_start;

    uint64_t current_rclk = bdk_clock_get_count(BDK_CLOCK_RCLK);
    uint64_t delta_rclk = current_rclk - last_start;
    uint64_t delta_rclk_percent = delta_rclk / 100;
    if (delta_rclk_percent == 0)
        delta_rclk_percent = 1;
    last_start = current_rclk;

    for (int io = 0; io < L2_NUM_IO; io++)
    {
        char io_name[8];
        snprintf(io_name, sizeof(io_name), "io%d", io);
        get_table(L, io_name);

        /* Counts the number of cycles the IOC(IO request bus) was busy.
            So the percentage used is simply 100 * count / RCLK */
        lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_IOCX_PFC(io, 0)) / delta_rclk_percent);
        BDK_CSR_WRITE(node, BDK_L2C_CBCX_IOCX_PFC(io, 0), 0);
        lua_setfield(L, -2, "ioc(IO req) %");
        /* Counts the number of cycles the IOR(IO response bus) was busy.
            So the percentage used is simply 100 * count / RCLK */
        lua_pushnumber(L, BDK_CSR_READ(node, BDK_L2C_CBCX_IORX_PFC(io, 0)) / delta_rclk_percent);
        BDK_CSR_WRITE(node, BDK_L2C_CBCX_IORX_PFC(io, 0), 0);
        lua_setfield(L, -2, "ior(IO resp) %");
        /* Pop the current IO table as were done */
        lua_pop(L, 1);
    }
}

static void l2_perf_tad(lua_State* L, bdk_node_t node)
{
    /* These define TAD counter ranges */
    const int MAX_TADS = bdk_is_model(OCTEONTX_CN83XX) ? 4 : 1;
    const int NUM_TAD_COUNTERS = 4;

    /* We cycle through 6 counter sets. 0-3 are each quad, and 4,5 are
        handpicked values */
    static int tad_count_set = 0;
    /* This is the start time of the setup for current count_set */
    static uint64_t last_start[BDK_NUMA_MAX_NODES][8][4];

    uint64_t rclk_rate = bdk_clock_get_rate(node, BDK_CLOCK_RCLK);
    uint64_t current_rclk = bdk_clock_get_count(BDK_CLOCK_RCLK);

    for (int tad = 0; tad < MAX_TADS; tad++)
    {
        char tad_name[8];
        snprintf(tad_name, sizeof(tad_name), "tad%d", tad);
        get_table(L, tad_name);

        /* Read the current performance counter settings */
        BDK_CSR_INIT(tadx_prf, node, BDK_L2C_TADX_PRF(tad));

        /* Cycle through counters adding them to our L2's table */
        for (int counter=0; counter<NUM_TAD_COUNTERS; counter++)
        {
            /* Calculate time since last update */
            uint64_t delta_rclk = current_rclk - last_start[node][tad][counter];
            if (delta_rclk == 0)
                delta_rclk = 1;
            uint64_t delta_rclk_percent = delta_rclk / 100;
            if (delta_rclk_percent == 0)
                delta_rclk_percent = 1;
            last_start[node][tad][counter] = current_rclk;

            /* Read the appropriate counter */
            uint64_t value = BDK_CSR_READ(node, BDK_L2C_TADX_PFCX(tad, counter));

            /* Figure out what to do based on the counter type */
            int count_type = (tadx_prf.u >> (counter*8)) & 0xff;
            const char *name = NULL;
            switch (count_type)
            {
                case 0x00: /* Nothing (disabled) */
                    break;
                case 0x01: /* L2 Tag Hit */
                    name = "tag_hit(num/s)";
                    /* Value is a simple count, not a utilization. Scale to
                        be cout/sec */
                    value = value * rclk_rate / delta_rclk;
                    break;
                case 0x02: /* L2 Tag Miss */
                    name = "tag_miss(num/s)";
                    /* Value is a simple count, not a utilization. Scale to
                        be cout/sec */
                    value = value * rclk_rate / delta_rclk;
                    break;
                case 0x03: /* L2 Tag NoAlloc (forced no-allocate) */
                    name = "tag_noalloc(num/s)";
                    /* Value is a simple count, not a utilization. Scale to
                        be cout/sec */
                    value = value * rclk_rate / delta_rclk;
                    break;
                case 0x04: /* L2 Victim */
                    name = "victim(num/s)";
                    /* Value is a simple count, not a utilization. Scale to
                        be cout/sec */
                    value = value * rclk_rate / delta_rclk;
                    break;
                case 0x05: /* SC Fail */
                    name = "sc_fail(num/s)";
                    /* Value is a simple count, not a utilization. Scale to
                        be cout/sec */
                    value = value * rclk_rate / delta_rclk;
                    break;
                case 0x06: /* SC Pass */
                    name = "sc_pass(num/s)";
                    /* Value is a simple count, not a utilization. Scale to
                        be cout/sec */
                    value = value * rclk_rate / delta_rclk;
                    break;
                case 0x07: /* LFB Occupancy (each cycle adds \# of LFBs valid) */
                    name = "lfb_occupancy %";
                    /* There are 16 LFBs, so utilization percentage is
                        100 * count / (RCLK*16) */
                    value /= delta_rclk_percent*16;
                    break;
                case 0x08: /* LFB Wait LFB (each cycle adds \# LFBs waiting for other LFBs) */
                    name = "lfb_wait_lfb %";
                    /* There are 16 LFBs, so utilization percentage is
                        100 * count / (RCLK*16) */
                    value /= delta_rclk_percent*16;
                    break;
                case 0x09: /* LFB Wait VAB (each cycle adds \# LFBs waiting for VAB) */
                    name = "lfb_wait_vab %";
                    /* There are 16 LFBs, so utilization percentage is
                        100 * count / (RCLK*16) */
                    value /= delta_rclk_percent*16;
                    break;
                case 0x80: /* Quad 0 index bus inuse */
                    name = "quad0_index_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0x81: /* Quad 0 read data bus inuse */
                    name = "quad0_read_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0x82: /* Quad 0 \# banks inuse (0-4/cycle) */
                    name = "quad0_banks_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0x83: /* Quad 0 wdat flops inuse (0-4/cycle) */
                    name = "quad0_wdat_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0x90: /* Quad 1 index bus inuse */
                    name = "quad1_index_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0x91: /* Quad 1 read data bus inuse */
                    name = "quad1_read_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0x92: /* Quad 1 \# banks inuse (0-4/cycle) */
                    name = "quad1_banks_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0x93: /* Quad 1 wdat flops inuse (0-4/cycle) */
                    name = "quad1_wdat_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0xA0: /* Quad 2 index bus inuse */
                    name = "quad2_index_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0xA1: /* Quad 2 read data bus inuse */
                    name = "quad2_read_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0xA2: /* Quad 2 \# banks inuse (0-4/cycle) */
                    name = "quad2_banks_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0xA3: /* Quad 2 wdat flops inuse (0-4/cycle) */
                    name = "quad2_wdat_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0xB0: /* Quad 3 index bus inuse */
                    name = "quad3_index_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0xB1: /* Quad 3 read data bus inuse */
                    name = "quad3_read_bus %";
                    /* Count is number of cycle bus in use, so utilization
                        percentage is 100 * count / RCLK */
                    value /= delta_rclk_percent;
                    break;
                case 0xB2: /* Quad 3 \# banks inuse (0-4/cycle) */
                    name = "quad3_banks_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
                case 0xB3: /* Quad 3 wdat flops inuse (0-4/cycle) */
                    name = "quad3_wdat_inuse %";
                    /* Count is number of banks bus in use per cycle (there are
                        4 banks), so utilization percentage is 100 * count /
                        (RCLK*4) */
                    value /= delta_rclk_percent*4;
                    break;
            }
            /* Add the counter to our output table */
            if (name)
            {
                lua_pushnumber(L, value);
                lua_setfield(L, -2, name);
            }
        }

        /* Pop the current TAD table as were done */
        lua_pop(L, 1);

        /* Set counter types for next update */
        switch (tad_count_set)
        {
            case 0:
            case 1:
            case 2:
            case 3:
                tadx_prf.s.cnt0sel = 0x80 + tad_count_set * 0x10; /* Quad X index bus inuse */
                tadx_prf.s.cnt1sel = 0x81 + tad_count_set * 0x10; /* Quad X read data bus inuse */
                tadx_prf.s.cnt2sel = 0x82 + tad_count_set * 0x10; /* Quad X # banks inuse (0-4/cycle) */
                tadx_prf.s.cnt3sel = 0x83 + tad_count_set * 0x10; /* Quad X wdat flops inuse (0-4/cycle) */
                break;
            case 4:
                tadx_prf.s.cnt0sel = 0x01; /* L2 Tag Hit */
                tadx_prf.s.cnt1sel = 0x02; /* L2 Tag Miss */
                tadx_prf.s.cnt2sel = 0x03; /* L2 Tag NoAlloc (forced no-allocate) */
                tadx_prf.s.cnt3sel = 0x04; /* L2 Victim */
                break;
            case 5:
                tadx_prf.s.cnt0sel = 0x05; /* SC Fail */
                tadx_prf.s.cnt1sel = 0x06; /* SC Pass */
                tadx_prf.s.cnt2sel = 0x07; /* LFB Occupancy (each cycle adds \# of LFBs valid) */
                tadx_prf.s.cnt3sel = 0x08; /* LFB Wait LFB (each cycle adds \# LFBs waiting for other LFBs) */
                //0x09; /* LFB Wait VAB (each cycle adds \# LFBs waiting for VAB) */
                break;
        }
        BDK_CSR_WRITE(node, BDK_L2C_TADX_PRF(tad), 0);
        BDK_CSR_WRITE(node, BDK_L2C_TADX_PFCX(tad, 0), 0);
        BDK_CSR_WRITE(node, BDK_L2C_TADX_PFCX(tad, 1), 0);
        BDK_CSR_WRITE(node, BDK_L2C_TADX_PFCX(tad, 2), 0);
        BDK_CSR_WRITE(node, BDK_L2C_TADX_PFCX(tad, 3), 0);
        BDK_CSR_WRITE(node, BDK_L2C_TADX_PRF(tad), tadx_prf.u);
    }

    /* Next update will use a different set of counters */
    tad_count_set++;
    if (tad_count_set > 5)
        tad_count_set = 0;
}

static int l2_perf(lua_State* L)
{
    bdk_node_t node = bdk_numa_local();

    /* All results will be in a table */
    if (lua_istable(L, 1))
        lua_pushvalue(L, 1);
    else
        lua_newtable(L);

    get_table(L, "cmb");
    l2_perf_cmb(L, node);
    lua_pop(L, 1);

    get_table(L, "io");
    l2_perf_io(L, node);
    lua_pop(L, 1);

    get_table(L, "tad");
    l2_perf_tad(L, node);
    lua_pop(L, 1);
    return 1;
}

void register_octeontx_perf(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, l2_perf);
    lua_setfield(L, -2, "get_l2");
    lua_setfield(L, -2, "perf");
}

