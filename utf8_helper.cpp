#include "utf8_helper.h"

#define U(c) utf8_char_to_uint(c)

ssize_t utf8_multibyte_to_uint(const char *input, size_t capacity, size_t first, unsigned *output) {
    unsigned value = 0;
    ssize_t ret = -1;

    if((input[first] & 224) == 192) {
        // 110xxxxx 10xxxxxx
        if(first + 1 < capacity) {
            value = U(input[first]) | (U(input[first+1]) << 8);
            ret = 2;
        }
    } else if((input[first] & 240) == 224) {
        // 1110xxxx 10xxxxxx 10xxxxxx
        if(first + 2 < capacity) {
            value = U(input[first]) | (U(input[first+1]) << 8) | (U(input[first+2]) << 16);
            ret = 3;
        }
    } else if((input[first] & 248) == 240) {
        // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        if(first + 3 < capacity) {
            value = U(input[first]) | (U(input[first+1]) << 8) | (U(input[first+2]) << 16) | (U(input[first+3]) << 24);
            ret = 4;
        }
    } else {
        // single byte case
        if(first < capacity) {
            value = U(input[first]);
            ret = 1;
        }
    }

    *output = value;
    return ret;
}

ssize_t utf8_uint_to_multibyte(unsigned input, char *output, size_t capacity, size_t first) {
    ssize_t ret = -1;

    if(input & 0xff000000) {
        if(first + 3 < capacity) {
            output[first] = (char)input;
            output[first+1] = (char)((input & 0xff00) >> 8);
            output[first+2] = (char)((input & 0xff0000) >> 16);
            output[first+3] = (char)((input & 0xff000000) >> 24);

            ret = 4;
        }
    } else if(input & 0xff0000) {
        if(first + 2 < capacity) {
            output[first] = (char)input;
            output[first+1] = (char)((input & 0xff00) >> 8);
            output[first+2] = (char)((input & 0xff0000) >> 16);

            ret = 3;
        }
    } else if(input & 0xff00) {
        if(first + 1 < capacity) {
            output[first] = (char)input;
            output[first+1] = (char)((input & 0xff00) >> 8);

            ret = 2;
        }
    } else {
        if(first < capacity) {
            output[first] = (char)input;

            ret = 1;
        }
    }

    return ret;
}


