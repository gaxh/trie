#ifndef __TRIE_UTF8_H__
#define __TRIE_UTF8_H__

#include "trie_generic.h"

class TrieUtf8 {
public:
    bool AddKeyword(const char *keyword, size_t length);

    ssize_t CheckAndReplace(char *data, size_t length, size_t *newlength, char replacement);

private:
    TrieGeneric<unsigned> m_trie;
};

#endif
