#include <itzy/math.h>
#include <stdio.h>

void prnt_v(iz_v2 v) { printf("%i %i\n", v.x, v.y); }

int main(void) {
  iz_v2 a = {38, 57};
  iz_v2 b = {4, 12};

  prnt_v(iz_v2_add(a, b));

  return 0;
}
