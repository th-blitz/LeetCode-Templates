#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    struct Trie* nextNodes[26]; 
    bool end; 
} Trie;


Trie* trieCreate() {
    Trie* root = (Trie*)malloc(sizeof(Trie));
    for (int i = 0; i < 26; i++) {
        root -> nextNodes[i] = NULL;
    }
    root -> end = false;
    return root;
}


Trie* get_node(Trie* node, char character) {
    int index = character - 97;
    Trie* nextNode = node -> nextNodes[index];
    return nextNode;
}


void add_node(Trie* node, char character, Trie* newNode) {
    int index = character - 97;
    node -> nextNodes[index] = newNode;
    return;
}


void insert_recur(Trie* node, int idx, char * word, int wordSize) {
    if (idx == wordSize) {
        node -> end = true;
        return;
    }
    if (get_node(node, word[idx]) == NULL) {
        add_node(node, word[idx], trieCreate());
    }
    return insert_recur(get_node(node, word[idx]), idx + 1, word, wordSize);
}


void trieInsert(Trie* obj, char * word) {
    insert_recur(obj, 0, word, strlen(word));
    return;
}


bool trieSearch_recur(Trie* node, int idx, char * word, int wordSize) {
    if (idx == wordSize) {
        return node -> end;
    }
    if (get_node(node, word[idx]) == NULL) {
        return false;
    }
    return trieSearch_recur(get_node(node, word[idx]), idx + 1, word, wordSize);
}


bool trieSearch(Trie* obj, char * word) {
    return trieSearch_recur(obj, 0, word, strlen(word));
}


bool trieStartsWith_recur(Trie* node, int idx, char * prefix, int prefixSize) {
    if (idx == prefixSize) {
        return true;
    }
    if (get_node(node, prefix[idx]) == NULL) {
        return false;
    }
    return trieStartsWith_recur(get_node(node, prefix[idx]), idx + 1, prefix, prefixSize);
}


bool trieStartsWith(Trie* obj, char * prefix) {
    return trieStartsWith_recur(obj, 0, prefix, strlen(prefix));
}


void trieFree(Trie* obj) {
    if (obj == NULL) {
        return;
    }    
    for (char i = 97; i < 123; i++) {
        trieFree(get_node(obj, i));
    }
    free(obj);
    return;
}


int main() {

    Trie* root = trieCreate();

    char *a = "hellothere";
    char *b = "hellya";
    trieInsert(root, a);
    trieInsert(root, b);

    trieFree(root);

    return 0;
}