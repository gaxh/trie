all : trie.test trie.utf8.test

trie.test : trie_generic.h trie_test.cpp
	g++ trie_test.cpp -o $@ -O2 -g -Wall

trie.utf8.test : trie_generic.h trie_utf8.h utf8_helper.h utf8_helper.cpp trie_utf8.cpp trie_utf8_test.cpp
	g++ trie_utf8_test.cpp trie_utf8.cpp utf8_helper.cpp -o $@ -O2 -g -Wall

clean:
	rm -f trie.test
	rm -f trie.utf8.test
