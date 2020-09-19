#include <itzy/debug.h>
#include <itzy/sys.h>
#include <string.h>
#include <stdio.h>

#define TEST_MESSAGE "Hello World!\n";

int main(void) {
  // Setup string buffers for serialization
  char        tmp[128] = {0};
  const char* msg      = TEST_MESSAGE;
  int         msglen   = strlen(msg);

  // Make the string decodable
  itzy_strnify(tmp, 128, msg, msglen);

  // Create a serialization buffer
  itzy_buffer buffer = itzy_buff_create(64);

  // Add string to the buffer
  itzy_buff_add_s(&buffer, tmp);

  // Rewind the buffer for reading
  itzy_buff_rewind(&buffer);

  // Set the temporary buffer to empty
  memset(tmp, 0, sizeof(char) * 128);

  // Get the string from the buffer
  itzy_buff_get_s(&buffer, tmp);
  int length = itzy_destrnify(tmp, 128, tmp, 128);
  // Clear out the buffer after the end of the string
  memset(tmp + length, 0, sizeof(char) * (128 - length));

  // Print out the decoded string
  printf("%s\n", tmp);

  // Destroy the serialization buffer
  itzy_buff_destroy(&buffer);

  return 0;
}
