#include "trie_utf8.h"
#include <string.h>
#include <vector>
#include "utf8_helper.h"

bool TrieUtf8::AddKeyword(const char *keyword, size_t length) {
    std::vector<unsigned> buffer;
    buffer.reserve(length);

    size_t first = 0;

    while(first < length) {
        unsigned value = 0;
        ssize_t step = utf8_multibyte_to_uint(keyword, length, first, &value);

        if(step <= 0) {
            return false;
        }

        first += step;
        buffer.emplace_back(value);
    }

    m_trie.AddKeyword(buffer.data(), buffer.size());
    return true;
}

ssize_t TrieUtf8::CheckAndReplace(char *data, size_t length, size_t *newlength, char replacement) {
    std::vector<unsigned> buffer;
    buffer.reserve(length);

    size_t first = 0;

    while(first < length) {
        unsigned value = 0;
        ssize_t step = utf8_multibyte_to_uint(data, length, first, &value);

        if(step <= 0) {
            return -1;
        }

        first += step;
        buffer.emplace_back(value);
    }

    size_t check_result = m_trie.CheckAndReplace(buffer.data(), buffer.size(), utf8_char_to_uint(replacement));

    first = 0;

    for(unsigned value: buffer) {
        ssize_t step = utf8_uint_to_multibyte(value, data, length, first);

        if(step <= 0) {
            break;
        }

        first += step;
    }

    *newlength = first;
    return check_result;
}


