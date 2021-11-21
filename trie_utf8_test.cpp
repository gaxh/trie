#include "trie_utf8.h"
#include "stdio.h"
#include "string.h"

const char *pattern[] = {
    "操蛋",
    "日",
    "你妈",
    "艹",
    "他妈",
    NULL
};

const char *check[] = {
    "正常",
    "日",
    "日你妈",
    "我艹他妈的",
    "他妈了个操蛋",
    "A日B他他妈2",
    "",
    NULL
};

int main() {
    
    TrieUtf8 trie;

    for(int i = 0; ; ++i) {
        const char *p = pattern[i];

        if(!p) {
            break;
        }

        trie.AddKeyword(p, strlen(p));
    }

    for(int i = 0; ; ++i) {
        const char *c = check[i];

        if(!c) {
            break;
        }

        char check_buffer[1024];

        snprintf(check_buffer, sizeof(check_buffer), "%s", c);

        size_t new_length = 0;
        size_t result = trie.CheckAndReplace(check_buffer, strlen(check_buffer), &new_length, '*');

        check_buffer[new_length] = '\0';

        printf("check %s result: %s (%zd)\n", c, check_buffer, result);
    }

    return 0;
}

