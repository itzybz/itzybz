#include <itzy/sys.h>
#include <itzy/debug.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* String reversal */
static char* itzy_reverse(char* string, uint32_t length) {
  uint32_t start = 0;
  uint32_t end   = length - 1;

  char tmp_a, tmp_b;

  while (start < end) {
    tmp_a = string[start];
    tmp_b = string[end];

    string[end]   = tmp_a;
    string[start] = tmp_b;

    ++start;
    --end;
  }

  return string;
}

/* Convert int to character */
char* itzy_itoa(int32_t value, char* string, int8_t base) {
  uint32_t i        = 0;
  uint8_t  negative = 0;

  if (value == 0) {
    string[i] = '0';
    ++i;
    string[i] = '\0';
    return string;
  }

  if (value < 0 && base == 10) {
    negative = 1;
    value    = -value;
  }

  while (value != 0) {
    int remainder = value % base;
    string[i]     = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    ++i;
    value = value / base;
  }

  if (negative) {
    string[i] = '-';
    ++i;
  }

  string[i] = '\0';
  itzy_reverse(string, i);

  return string;
}

void itzy_table_free(itzy_table table) {
  if (table.keys)
    free(table.keys);
  if (table.values)
    free(table.values);
}

static char* itzy_cleaned_str(const char* str, uint32_t* size, char* str_end) {
  if (!str) {
    ITZY_FUNC_DBG("Unable to clean null string.\n");
    return 0;
  }

  uint32_t str_size = 0;

  if (str_end) {
    while (isspace(*str) && str < str_end)
      str++;
  } else {
    while (isspace(*str))
      str++;
  }

  if (str == 0)
    return 0;

  const char* start = str;
  if (str_end) {
    while (!isspace(*str) && str < str_end) {
      ++str_size;
      str++;
    }
  } else {
    while (!*str) {
      if (!isspace(*str)) {
        ++str_size;
        str++;
      } else {
        break;
      }
    }
  }

  char* new_str = (char*)malloc(sizeof(char) * (str_size + 1));
  strncpy(new_str, start, str_size);
  new_str[str_size] = '\0';

  if (size)
    *size = str_size;

  return new_str;
}

static void itzy_kv_get(char* src, char** key, char** value,
                        uint32_t* key_length, uint32_t* value_length) {
  char* split = strstr(src, "=");

  uint32_t _key_len, _value_len;
  *key   = itzy_cleaned_str(src, &_key_len, split);
  *value = itzy_cleaned_str(split + 1, &_value_len, 0);

  if (key_length) {
    *key_length = _key_len;
  }

  if (value_length) {
    *value_length = _value_len;
  }
}

itzy_table itzy_table_get(unsigned char* data) {
  char* data_ptr = (char*)data;
  char* line     = strtok(data_ptr, "\n");

  const char** keys          = (const char**)malloc(sizeof(char*) * 16);
  const char** values        = (const char**)malloc(sizeof(char*) * 16);
  uint32_t     line_capacity = 16;
  uint32_t     line_count    = 0;

  while (line != NULL) {
    char *key, *value;

    uint32_t key_length   = 0;
    uint32_t value_length = 0;

    if (line_count == line_capacity) {
      keys   = realloc(keys, sizeof(char*) * (line_capacity + 8));
      values = realloc(values, sizeof(char*) * (line_capacity + 8));
      line_capacity += 8;
    }

    itzy_kv_get(line, &key, &value, &key_length, &value_length);

    keys[line_count]   = key;
    values[line_count] = value;

    ++line_count;
    line = strtok(NULL, "\n");
  }

  return (itzy_table){keys, values, line_count};
}

uint8_t itzy_table_write(itzy_table* table, char* filepath) {
  FILE* f = fopen(filepath, "wb");
  if (!f) {
    return 0;
  }

  char   str_buff[128];
  int8_t str_size = 0;

  for (uint32_t i = 0; i < table->count; ++i) {
    str_size =
        snprintf(str_buff, 128, "%s = %s\n", table->keys[i], table->values[i]);
    uint32_t written = fwrite(str_buff, str_size, sizeof(char), f);
    if (written == 0) {
      fclose(f);
      return 0;
    }
    memset(str_buff, 0, sizeof(char) * str_size);
  }

  fwrite("\0", 1, sizeof(char), f);

  fclose(f);
  return 1;
}

uint8_t itzy_table_write_mem(itzy_table* table, unsigned char* dst,
                             uint32_t dst_length, uint32_t* write_length) {
  uint32_t size = 0;
  char     str_buff[128];
  uint8_t  str_size;

  for (uint32_t i = 0; i < table->count; ++i) {
    str_size =
        snprintf(str_buff, 128, "%s = %s\n", table->keys[i], table->values[i]);

    if (size + str_size > dst_length - 2) {
      return 0;
    }

    memcpy(&dst[size], str_buff, sizeof(char) * str_size);
    memset(str_buff, 0, sizeof(char) * str_size);
    size += str_size;
  }

  char* end = (char*)&dst[size];
  *end      = '\0';

  if (write_length) {
    *write_length = size;
  }

  return 1;
}

uint32_t itzy_strnify(char* dst, uint32_t dst_capacity, const char* src,
                      uint32_t str_length) {
  uint32_t index = 0;

  if (str_length == 0)
    str_length = strlen(src);

  for (uint32_t i = 0; i < str_length; ++i) {
    if (index >= dst_capacity - 1) {
      break;
    }

    if (isspace(*src)) {
      if (index + 3 >= dst_capacity) {
        break;
      }

      strcat(dst, "%20");
      index += 3;
      dst += 3;
    } else {
      *dst = *src;
      ++index;
      ++dst;
    }
    ++src;
  }

  dst[index] = 0;

  return index;
}

uint32_t itzy_destrnify(char* dst, uint32_t dst_capacity, const char* src,
                        uint32_t str_length) {
  uint32_t index = 0, length = 0;

  if (str_length == 0)
    str_length = strlen(src);

  while (*src && index < str_length && length < dst_capacity) {
    if (strstr(src, "%20") == src) {
      *dst = ' ';
      ++dst;
      src += 3;
      index += 3;
    } else {
      *dst = *src;
      ++dst;
      ++src;
      ++index;
    }

    ++length;
  }

  dst[length] = 0;

  return length;
}

itzy_buffer itzy_buff_create(uint32_t capacity) {
  char* data = (char*)malloc(sizeof(char) * capacity);
  memset(data, 0, sizeof(char) * capacity);

  return (itzy_buffer){
      .data     = data,
      .cursor   = data,
      .length   = 0,
      .capacity = capacity,
  };
}

itzy_buffer itzy_buff_read(const char* data) {
  if (!data)
    return (itzy_buffer){0};

  uint32_t length = strlen(data);

  itzy_buffer buff = itzy_buff_create(length + 1);
  strcpy(buff.data, data);
  buff.length = length;

  return buff;
}

void itzy_buff_destroy(itzy_buffer* buffer) { free(buffer->data); }

void itzy_buff_rewind(itzy_buffer* buffer) { buffer->cursor = buffer->data; }

static void itzy_buff_to_space(itzy_buffer* buffer) {
  while (*buffer->cursor) {
    if (isspace(*buffer->cursor)) {
      if (buffer->cursor + 1) {
        ++buffer->cursor;
      }

      return;
    }
    ++buffer->cursor;
  }
}

void itzy_buff_move_to(itzy_buffer* buffer, uint32_t index) {
  buffer->cursor = &buffer->data[index];
}

uint8_t itzy_buff_add_s(itzy_buffer* buffer, const char* string) {
  if (buffer->length == buffer->capacity) {
    return 0;
  }

  uint32_t len = strlen(string);

  if (buffer->capacity - buffer->length < len) {
    return 0;
  }

  uint32_t length = snprintf(buffer->cursor, buffer->capacity - buffer->length,
                             "%s ", string);

  // Move cursor forward
  buffer->cursor += length;
  buffer->length += length;

  return 1;
}

uint8_t itzy_buff_add_i(itzy_buffer* buffer, int value) {
  if (buffer->length == buffer->capacity) {
    return 0;
  }

  uint32_t length =
      snprintf(buffer->cursor, buffer->capacity - buffer->length, "%i ", value);

  // Move cursor forward
  buffer->cursor += length;
  buffer->length += length;

  return 1;
}

uint8_t itzy_buff_add_f(itzy_buffer* buffer, float value) {
  if (buffer->length == buffer->capacity) {
    return 0;
  }

  uint32_t length =
      snprintf(buffer->cursor, buffer->capacity - buffer->length, "%f ", value);

  // Move cursor forward
  buffer->cursor += length;
  buffer->length += length;

  return 1;
}

float itzy_buff_get_f(itzy_buffer* buffer) {
  if (buffer->length == 0)
    return 0;

  float value;
  if (!sscanf(buffer->cursor, "%f ", &value)) {
    return -1.f;
  }

  itzy_buff_to_space(buffer);

  return value;
}

int itzy_buff_get_i(itzy_buffer* buffer) {
  if (buffer->length == 0)
    return 0;

  int value;
  if (!sscanf(buffer->cursor, "%i ", &value)) {
    return -1;
  }

  itzy_buff_to_space(buffer);

  return value;
}

char* itzy_buff_get_s(itzy_buffer* buffer, char* dst) {
  if (buffer->length == 0)
    return 0;

  if (!sscanf(buffer->cursor, "%s ", dst)) {
    return 0;
  }

  itzy_buff_to_space(buffer);

  return dst;
}

