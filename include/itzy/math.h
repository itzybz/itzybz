#ifndef ITZY_MATH_H
#define ITZY_MATH_H

#include <itzy/types.h>

#define _max(a, b) ((a) > (b) ? (a) : (b))
#define _min(a, b) ((a) > (b) ? (b) : (a))

#ifdef ITZY_NO_INLINE
#define ITZY_FUNC static
#else
#define ITZY_FUNC static inline
#endif

ITZY_FUNC int iz_v2_cmp(iz_v2 const a, iz_v2 const b) {
  return (a.x == b.x && a.y == b.y);
}

ITZY_FUNC iz_v2 iz_v2_add(iz_v2 const a, iz_v2 const b) {
  return (iz_v2){a.x + b.x, a.y + b.y};
}

ITZY_FUNC iz_v2 iz_v2_sub(iz_v2 const a, iz_v2 const b) {
  return (iz_v2){a.x - b.x, a.y - b.y};
}

ITZY_FUNC iz_v2 iz_v2_mul(iz_v2 const a, iz_v2 const b) {
  return (iz_v2){a.x * b.x, a.y * b.y};
}

ITZY_FUNC iz_v2 iz_v2_div(iz_v2 const a, iz_v2 const b) {
  return (iz_v2){a.x / b.x, a.y / b.y};
}

ITZY_FUNC iz_v2 iz_v2_min(iz_v2 const a, iz_v2 const b) {
  return (iz_v2){_min(a.x, b.x), _min(a.y, b.y)};
}

ITZY_FUNC iz_v2 iz_v2_max(iz_v2 const a, iz_v2 const b) {
  return (iz_v2){_max(a.x, b.x), _max(a.y, b.y)};
}

ITZY_FUNC iz_v2 iz_v2_clamp(iz_v2 const val, iz_v2 const min, iz_v2 const max) {
  return iz_v2_min(iz_v2_max(val, min), max);
}

ITZY_FUNC int iz_v3_cmp(iz_v3 const a, iz_v3 const b) {
  return (a.x == b.x && a.y == b.y && a.z == b.z);
}

ITZY_FUNC iz_v3 iz_v3_add(iz_v3 const a, iz_v3 const b) {
  return (iz_v3){a.x + b.x, a.y + b.y, a.z + b.z};
}

ITZY_FUNC iz_v3 iz_v3_sub(iz_v3 const a, iz_v3 const b) {
  return (iz_v3){a.x - b.x, a.y - b.y, a.z - b.z};
}

ITZY_FUNC iz_v3 iz_v3_mul(iz_v3 const a, iz_v3 const b) {
  return (iz_v3){a.x * b.x, a.y * b.y, a.z * b.z};
}

ITZY_FUNC iz_v3 iz_v3_div(iz_v3 const a, iz_v3 const b) {
  return (iz_v3){a.x / b.x, a.y / b.y, a.z / b.z};
}

ITZY_FUNC iz_v3 iz_v3_min(iz_v3 const a, iz_v3 const b) {
  return (iz_v3){_min(a.x, b.x), _min(a.y, b.y), _min(a.z, b.z)};
}

ITZY_FUNC iz_v3 iz_v3_max(iz_v3 const a, iz_v3 const b) {
  return (iz_v3){_max(a.x, b.x), _max(a.y, b.y), _max(a.z, b.z)};
}

ITZY_FUNC iz_v3 iz_v3_clamp(iz_v3 const val, iz_v3 const min, iz_v3 const max) {
  return iz_v3_min(iz_v3_max(val, min), max);
}

ITZY_FUNC int iz_v4_cmp(iz_v4 const a, iz_v4 const b) {
  return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}

ITZY_FUNC iz_v4 iz_v4_add(iz_v4 const a, iz_v4 const b) {
  return (iz_v4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

ITZY_FUNC iz_v4 iz_v4_sub(iz_v4 const a, iz_v4 const b) {
  return (iz_v4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

ITZY_FUNC iz_v4 iz_v4_mul(iz_v4 const a, iz_v4 const b) {
  return (iz_v4){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

ITZY_FUNC iz_v4 iz_v4_div(iz_v4 const a, iz_v4 const b) {
  return (iz_v4){a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

ITZY_FUNC iz_v4 iz_v4_min(iz_v4 const a, iz_v4 const b) {
  return (iz_v4){_min(a.x, b.x), _min(a.y, b.y), _min(a.z, b.z),
                 _min(a.w, b.w)};
}

ITZY_FUNC iz_v4 iz_v4_max(iz_v4 const a, iz_v4 const b) {
  return (iz_v4){_max(a.x, b.x), _max(a.y, b.y), _max(a.z, b.z),
                 _max(a.w, b.w)};
}

ITZY_FUNC iz_v4 iz_v4_clamp(iz_v4 const val, iz_v4 const min, iz_v4 const max) {
  return iz_v4_min(iz_v4_max(val, min), max);
}

#endif
