#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define TABLE_SIZE 8

struct entry {
    char *key;
    char *value;
    struct entry *next;
};

struct hashTable {
    struct entry **entries;
};

unsigned int hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int keyLen = strlen(key);

    for (; i < keyLen; ++i) {
        value = value * 37 + key[i];
    }
    
    value  = value % TABLE_SIZE;
    return value;
}

struct hashTable* hashTable() {

    struct hashTable* hash_table = malloc(sizeof(struct hashTable));

    hash_table -> entries = malloc(sizeof(struct entry*) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        hash_table -> entries[i] = NULL;
    }

    return hash_table;
}

struct entry* hash_pair(const char* key, const char* value) {
    
    struct entry* entry = malloc(sizeof(struct entry));
    entry -> key = malloc(strlen(key) + 1);
    entry -> value = malloc(strlen(key) + 1);

    strcpy(entry -> key, key);
    strcpy(entry -> value, value);

    entry -> next = NULL;

    return entry;
}

void put(struct hashTable* hash_table, const char * key, const char * value) {
    
    unsigned int slot = hash(key);

    struct entry* entry = hash_table -> entries[slot];

    if (entry == NULL) {
        hash_table -> entries[slot] = hash_pair(key, value);
        return;
    }

    struct entry* prev;

    while (entry != NULL) {

        if (strcmp(entry -> key, key) == 0) {
            free(entry -> value);
            entry -> value = malloc(strlen(value) + 1);
            strcpy(entry -> value, value);
            return;
        }

        prev = entry;
        entry = prev -> next;
    }
    prev -> next = hash_pair(key, value);
}

char* get(struct hashTable* hash_table, const char *key) {
    
    unsigned int slot = hash(key);
    struct entry* entry = hash_table -> entries[slot];

    while (entry != NULL) {
        if (strcmp(entry -> key, key) == 0) {
            return entry -> value;
        }
        entry = entry -> next; 
    }

    return NULL;
}

void print_hashmap(struct hashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct entry* entry = hash_table -> entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for (;;) {
            printf("%s = %s ; ", entry -> key, entry -> value);

            if (entry -> next == NULL) {
                break;
            }
            entry = entry -> next;    
        } 
        printf("\n");
    }
}

int main() {

    struct hashTable* hash_map = hashTable();

    put(hash_map, "name", "thblitz");
    put(hash_map, "(", ")");
    put(hash_map, "{", "}");

    print_hashmap(hash_map);

    printf("%s \n", get(hash_map, "("));

    return 0;
}