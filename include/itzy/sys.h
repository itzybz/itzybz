#ifndef ITZY_SYS_H
#define ITZY_SYS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SEC_TO_NS   1e-9
#define SEC_TO_MCS  1e-6
#define SEC_TO_MS   1e-6
#define SEC_TO_MIN  60
#define SEC_TO_HOUR 3600

#define MS_TO_NS   1e-6
#define MS_TO_MCS  1e-3
#define MS_TO_SEC  1e3
#define MS_TO_MIN  MS_TO_SEC * 60
#define MS_TO_HOUR MS_TO_MIN * 60

#define MCS_TO_NS   1e-3
#define MCS_TO_MS   1e3
#define MCS_TO_SEC  1e6
#define MCS_TO_MIN  MCS_TO_SEC * 60
#define MCS_TO_HOUR MCS_TO_MIN * 60

#define NS_TO_MCS  1e3
#define NS_TO_MS   1e6
#define NS_TO_SEC  1e9
#define NS_TO_MIN  NS_TO_SEC * 60
#define NS_TO_HOUR NS_TO_MIN * 60

/* String based data input/output*/
typedef struct {
  char *   data, *cursor;
  uint32_t length, capacity;
} itzy_buffer;

typedef struct {
  /* keys - an array of the key strings
     values - an array of the value strings
     count - the number of strings (length of each array individually) */
  const char** keys;
  const char** values;
  uint32_t     count;
} itzy_table;

/* Convert integer to String
 * value - the value to convert to string
 * string - the storage for the string
 * base - the base to set the value to
 * returns: pointer to the string */
char* itzy_itoa(int32_t value, char* string, int8_t base);

/* Convert a string to parsable string
 * dst - the destination to store the string
 * dst_capacity - the max amount of characters stored
 * src - the source string
 * str_length - the length of the source string
 * returns: length of string */
uint32_t itzy_strnify(char* dst, uint32_t dst_capacity, const char* src,
                      uint32_t str_length);

/* Convert a string back to regular non-strnified style
 * dst - the destination to store the string
 * dst_capacity - the max amount of characters stored
 * src - the source string
 * str_length - the length of the source string
 * returns: length of string */
uint32_t itzy_destrnify(char* dst, uint32_t dst_capacity, const char* src,
                        uint32_t str_length);

/* Create string buffer with a size of capacity
 * capacity - the capacity of the buffer in characters
 * returns: formatted itzy_buffer struct */
itzy_buffer itzy_buff_create(uint32_t capacity);

/* Create a string buffer matching already existing data
 * data - the data to mirror
 * returns: formatted itzy_buffer struct */
itzy_buffer itzy_buff_read(const char* data);

/* Destroy a string buffer and all of its contents
 * buff - the buffer to destroy */
void itzy_buff_destroy(itzy_buffer* buffer);

/* Rewind a string buffer's cursor
 * buff - the buffer to affect */
void itzy_buff_rewind(itzy_buffer* buffer);

/* Move a buffer's cursor to index
 * buff - the buffer to affect
 * index - the index to move to */
void itzy_buff_move_to(itzy_buffer* buffer, uint32_t index);

/* Add a string to a string buffer
 * buff - the buffer to add a string to
 * string - the string to add
 * returns: success = 1, fail = 0 */
uint8_t itzy_buff_add_s(itzy_buffer* buffer, const char* string);

/* Add an integer to a string buffer
 * buff - the buffer to add an integer to
 * value - the integer value to add
 * returns: success = 1, fail = 0 */
uint8_t itzy_buff_add_i(itzy_buffer* buffer, int value);

/* Add a float to a string buffer
 * buff - the buffer to add a float to
 * value - the float value to add
 * returns: success = 1, fail = 0 */
uint8_t itzy_buff_add_f(itzy_buffer* buffer, float value);

/* Get a float value from a string buffer at cursor point
 * buff - the string buffer to check
 * return: the float value */
float itzy_buff_get_f(itzy_buffer* buffer);

/* Get an integer value from a string buffer at cursor point
 * buff - the string buffer to check
 * return: the integer value */
int itzy_buff_get_i(itzy_buffer* buffer);

/* Get a string value from a string buffer at cursor point
 * buff - the string buffer to check
 * dst - the destination to place the string
 * return: the string value */
char* itzy_buff_get_s(itzy_buffer* buffer, char* dst);

#ifdef __cplusplus
}
#endif
#endif
