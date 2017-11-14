/*
** $Id: lbitlib.c,v 1.13 2010/11/22 18:06:33 roberto Exp $
** Standard library for bitwise operations
** See Copyright Notice in lua.h
*/

#define lbitlib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


/* number of bits to consider in a number */
#define NBITS	64

#define ALLONES		(~(((~(unsigned long long)0) << (NBITS - 1)) << 1))

/* mask to trim extra bits */
#define trim(x)		((x) & ALLONES)


typedef unsigned long long b_uint;


#define getbitarg(L,arg)	(b_uint)luaL_checknumber(L,arg)
#define pushbit(L, arg)         lua_pushnumber(L, arg)


static b_uint andaux (lua_State *L) {
  int i, n = lua_gettop(L);
  b_uint r = ~(b_uint)0;
  for (i = 1; i <= n; i++)
    r &= getbitarg(L, i);
  return trim(r);
}


static int b_and (lua_State *L) {
  b_uint r = andaux(L);
  pushbit(L, r);
  return 1;
}


static int b_test (lua_State *L) {
  b_uint r = andaux(L);
  lua_pushboolean(L, r != 0);
  return 1;
}


static int b_or (lua_State *L) {
  int i, n = lua_gettop(L);
  b_uint r = 0;
  for (i = 1; i <= n; i++)
    r |= getbitarg(L, i);
  pushbit(L, trim(r));
  return 1;
}


static int b_xor (lua_State *L) {
  int i, n = lua_gettop(L);
  b_uint r = 0;
  for (i = 1; i <= n; i++)
    r ^= getbitarg(L, i);
  pushbit(L, trim(r));
  return 1;
}


static int b_not (lua_State *L) {
  b_uint r = ~getbitarg(L, 1);
  pushbit(L, trim(r));
  return 1;
}


static int b_shift (lua_State *L, b_uint r, int i) {
  if (i < 0) {  /* shift right? */
    i = -i;
    r = trim(r);
    if (i >= NBITS) r = 0;
    else r >>= i;
  }
  else {  /* shift left */
    if (i >= NBITS) r = 0;
    else r <<= i;
    r = trim(r);
  }
  pushbit(L, r);
  return 1;
}


static int b_lshift (lua_State *L) {
  return b_shift(L, getbitarg(L, 1), luaL_checkint(L, 2));
}


static int b_rshift (lua_State *L) {
  return b_shift(L, getbitarg(L, 1), -luaL_checkint(L, 2));
}


static int b_arshift (lua_State *L) {
  b_uint r = getbitarg(L, 1);
  int i = luaL_checkint(L, 2);
  if (i < 0 || !(r & ((b_uint)1 << (NBITS - 1))))
    return b_shift(L, r, -i);
  else {  /* arithmetic shift for 'negative' number */
    if (i >= NBITS) r = ALLONES;
    else
      r = trim((r >> i) | ~(~(b_uint)0 >> i));  /* add signal bit */
    pushbit(L, r);
    return 1;
  }
}


static int b_rot (lua_State *L, int i) {
  b_uint r = getbitarg(L, 1);
  i &= (NBITS - 1);  /* i = i % NBITS */
  r = trim(r);
  r = (r << i) | (r >> (NBITS - i));
  pushbit(L, trim(r));
  return 1;
}


static int b_lrot (lua_State *L) {
  return b_rot(L, luaL_checkint(L, 2));
}


static int b_rrot (lua_State *L) {
  return b_rot(L, -luaL_checkint(L, 2));
}

/**
 * Extract bits out of a number
 * v = bit64.bextract(0x11223344, 8, 15)
 * v = 0x33
 *
 * @param L
 *
 * @return
 */
static int b_extract(lua_State *L) {
    b_uint r = getbitarg(L, 1);
    int start_bit = luaL_checkint(L, 2);
    int stop_bit = luaL_optint(L, 3, start_bit);
    int width = stop_bit - start_bit + 1;

    if (start_bit)
        r >>= start_bit;
    if (width < NBITS)
        r &= (1ull<<width) - 1;
    pushbit(L, trim(r));
    return 1;
}

/**
 * Insert bits into a number
 * v = bit64.binsert(0x11223344, 0x55, 8, 15)
 * v = 0x11225544
 *
 * @param L
 *
 * @return
 */
static int b_insert(lua_State *L) {
    b_uint r = getbitarg(L, 1); /* Original value */
    b_uint n = getbitarg(L, 2); /* Value to insert */
    int start_bit = luaL_checkint(L, 3); /* Start bit for insert */
    int stop_bit = luaL_optint(L, 4, start_bit); /* Stop bit, defaults to start */

    int width = stop_bit - start_bit + 1;
    b_uint mask = ALLONES;
    if (width < NBITS)
        mask = (1ull<<width) - 1;
    if (start_bit)
    {
        mask <<= start_bit;
        n <<= start_bit;
    }
    n &= mask;
    r &= ~mask;
    r |= n;
    pushbit(L, trim(r));
    return 1;
}


static const luaL_Reg bitlib[] = {
  {"arshift", b_arshift},
  {"band", b_and},
  {"bnot", b_not},
  {"bor", b_or},
  {"bxor", b_xor},
  {"lrotate", b_lrot},
  {"lshift", b_lshift},
  {"rrotate", b_rrot},
  {"rshift", b_rshift},
  {"btest", b_test},
  {"bextract", b_extract},
  {"binsert", b_insert},
  {NULL, NULL}
};



LUAMOD_API int luaopen_bit64 (lua_State *L) {
  luaL_newlib(L, bitlib);
  return 1;
}

