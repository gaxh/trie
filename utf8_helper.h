#ifndef __UTF8_HELPER_H__
#define __UTF8_HELPER_H__

#include <stddef.h>
#include <sys/types.h>

ssize_t utf8_multibyte_to_uint(const char *input, size_t capacity, size_t first, unsigned *output);

ssize_t utf8_uint_to_multibyte(unsigned input, char *output, size_t capacity, size_t first);

#define utf8_char_to_uint(c) ((unsigned)(unsigned char)(c))

#endif
