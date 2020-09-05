#include <itzy/debug.h>
#include <itzy/sys.h>
#include <string.h>
#include <stdio.h>

int main(void) {
  char        tmp[128] = {0};
  const char* msg      = "Hello World.\n";
  int         msglen   = strlen(msg);

  itzy_strnify(tmp, 128, msg, msglen);

  itzy_buffer buffer = itzy_buff_create(64);
  itzy_buff_add_s(&buffer, tmp);
  itzy_buff_rewind(&buffer);

  memset(tmp, 0, sizeof(char) * 128);

  itzy_buff_get_s(&buffer, tmp);
  int length = itzy_destrnify(tmp, 128, tmp, 128);
  memset(tmp + length, 0, sizeof(char) * (128 - length));

  printf("%s\n", tmp);
  itzy_buff_destroy(&buffer);

  return 0;
}
