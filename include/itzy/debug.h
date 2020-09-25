#ifndef ITZY_DEBUG_H
#define ITZY_DEBUG_H

#if defined(_cplusplus)
extern "C" {
#endif

#include <stdio.h>

#ifndef ITZY_FUNC_DBG
#ifdef ITZY_DEBUG
#define ITZY_FUNC_DBG(fmt, ...) \
  printf("%s: ", __func__);     \
  printf(fmt, ##__VA_ARGS__);
#else
#define ITZY_FUNC_DBG(fmt, ...)
#endif
#endif

#if defined(_cplusplus)
}
#endif
#endif