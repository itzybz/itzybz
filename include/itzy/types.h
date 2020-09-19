#ifndef ITZY_TYPES_H
#define ITZY_TYPES_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef char  s8;
typedef short s16;
typedef int   s32;

#define ITZY_VEC_SIZE u16

// TODO change if we need alpha or if padding goes to 32 bit anyway
typedef union {
  struct {
    u8 r, g, b;
  };
} iz_color;

typedef union {
  struct {
    ITZY_VEC_SIZE x, y;
  };
  struct {
    ITZY_VEC_SIZE width, height;
  };
  struct {
    ITZY_VEC_SIZE s, t;
  };
} iz_v2;

typedef union {
  struct {
    ITZY_VEC_SIZE x, y, z;
  };
  struct {
    ITZY_VEC_SIZE r, g, b;
  };
} iz_v3;

typedef union {
  struct {
    ITZY_VEC_SIZE x, y, z, w;
  };
  struct {
    ITZY_VEC_SIZE min_x, min_y, max_x, max_y;
  };
} iz_v4;

#endif
