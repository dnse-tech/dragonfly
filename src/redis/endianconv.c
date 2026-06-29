/* endianconv.c - Byte-order reversal helpers used by the vendored Redis data
 * structures (intset, ziplist, listpack, ...).
 *
 * On little-endian hosts every intrevNNifbe()/memrevNNifbe() macro in
 * endianconv.h expands to a no-op, so this translation unit is never
 * referenced there. On big-endian hosts (e.g. s390x) those macros call the
 * functions below, so the file must be compiled and linked.
 *
 * Copyright (c) 2011-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved. Distributed under the BSD license shared with the rest
 * of the vendored Redis sources (see endianconv.h header for the full text).
 */

#include <stdint.h>

#include "endianconv.h"

/* Toggle the 16 bit unsigned integer pointed by *p from little endian to
 * big endian */
void memrev16(void *p) {
  unsigned char *x = p, t;

  t = x[0];
  x[0] = x[1];
  x[1] = t;
}

/* Toggle the 32 bit unsigned integer pointed by *p from little endian to
 * big endian */
void memrev32(void *p) {
  unsigned char *x = p, t;

  t = x[0];
  x[0] = x[3];
  x[3] = t;
  t = x[1];
  x[1] = x[2];
  x[2] = t;
}

/* Note: memrev64() and intrev64() are intentionally NOT defined here; the
 * vendored redis_aux.c already provides them. This file only fills in the
 * 16/32-bit variants that intset.c and friends reference on big-endian hosts. */

uint16_t intrev16(uint16_t v) {
  memrev16(&v);
  return v;
}

uint32_t intrev32(uint32_t v) {
  memrev32(&v);
  return v;
}
