#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct TableNode {
    void *key;
    void *val;
};

struct HashTable {
    struct TableNode** bucket;
    unsigned long int len;
    unsigned long int max_len;
    unsigned long int bucket_len;
    unsigned long int max_collisions;
};

// unsigned long int hash(void* key) {

// }

// constraints : num <= 1B;

unsigned long int max_val(unsigned long int a, unsigned long int b) {
    if ( a > b ) {
        return a;
    }
    return b;
}

unsigned long int nearest_prime(unsigned long int num) {

    unsigned char* primes = (unsigned char*)malloc(num * sizeof(unsigned char));
    
    for (unsigned long int i = 0; i < num; i++) {
        primes[i] = 1;
    }

    for (unsigned long int i = 2; i * i <= num; i++) {
        if (primes[i] == 1) {
            for (unsigned long int j = i * i; j <= num; j += i) {
                primes[j] = 0;
            }
        }
    }

    unsigned long int prime;
    for (unsigned long int i = num - 1; i >= 0; i--) {
        if (primes[i] == 1) {
            prime = i;
            break;
        }
    }
    free(primes);
    return prime;
}

struct HashTable* HashTable(unsigned long int table_len) {

    if (table_len < 1) {
        return NULL;
    }

    unsigned long int bucket_len = (3 * table_len) / 2;
    bucket_len = nearest_prime(bucket_len);

    struct HashTable* hash_table = malloc(sizeof(struct HashTable));
    hash_table -> bucket = malloc(sizeof(struct TableNode*) * bucket_len);
    for (unsigned long int i = 0; i < bucket_len; i++) {
        hash_table -> bucket[i] = NULL;
    }

    hash_table -> len = 0;
    hash_table -> max_len = table_len;
    hash_table -> bucket_len = bucket_len;
    hash_table -> max_collisions = 0;

    return hash_table;
    
}

struct TableNode* get_pair(void* key, void* val) {
    struct TableNode* pair = malloc(sizeof(struct TableNode));
    pair -> key = key;
    pair -> val = val;
    return pair;
}

unsigned long int probe(unsigned long int bucket_slot, unsigned long int collisions) {
    return bucket_slot + (collisions * collisions);
}

bool check(struct HashTable* hash_table, void* key, unsigned long int hash) {
    unsigned long int bucket_slot = hash % hash_table -> bucket_len;
    unsigned long int collisions = 0;
    unsigned long int max_collisions = hash_table -> max_collisions;
    while ((hash_table -> bucket[bucket_slot] -> key != key) && (collisions <= max_collisions)) {
        collisions += 1;
        bucket_slot = probe(bucket_slot, collisions);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }

    bool val;
    if (collisions <= max_collisions) {
        val = true;
    } else {
        val = false;
    }

    return val;
}

bool insert(struct HashTable* hash_table, void* key, void* val, unsigned long int hash) {
    
    if (hash_table -> len == hash_table -> max_len && (check(hash_table, key, hash) == false)) {
        return false;
    }

    unsigned long int bucket_slot = hash % hash_table -> bucket_len;
    struct TableNode* pair_slot = hash_table -> bucket[bucket_slot];

    unsigned long int collisions = 0;

    while (hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key != key) {
        collisions += 1;
        bucket_slot = probe(bucket_slot, collisions);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }

    if (hash_table -> bucket[bucket_slot] == NULL) {
        hash_table -> bucket[bucket_slot] = get_pair(key, val);
        hash_table -> len += 1;
    } else {
        hash_table -> bucket[bucket_slot] -> val = val;
    }

    hash_table -> max_collisions = max_val(hash_table -> max_collisions, collisions);
    return true;

}

void* get(struct HashTable* hash_table, void* key, unsigned long int hash) {
    unsigned long int bucket_slot = hash % hash_table -> bucket_len;
    unsigned long int collisions = 0;
    unsigned long int max_collisions = hash_table -> max_collisions;
    while ((hash_table -> bucket[bucket_slot] -> key != key) && (collisions <= max_collisions)) {
        collisions += 1;
        bucket_slot = probe(bucket_slot, collisions);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }

    void* val;
    if (collisions <= max_collisions) {
        val = hash_table -> bucket[bucket_slot] -> val;
    } else {
        val = NULL;
    }

    return val;
}

void print_hashtable(struct HashTable* hash_table) {
    for (unsigned long int i = 0; i < hash_table -> bucket_len; i++) {
        if (hash_table -> bucket[i] != NULL) {
            printf("bucket[%ld] = { %s : %s }\n", i, (char *)hash_table -> bucket[i] -> key, (char *)hash_table -> bucket[i] -> val);
        }
    }
}

unsigned long int simple_hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int keyLen = strlen(key);

    for (; i < keyLen; ++i) {
        value = value * 37 + key[i];
    }

    return value;
}

int main() {

    struct HashTable* hashmap = HashTable(4);

    printf("%ld \n", hashmap -> bucket_len);

    insert(hashmap, "(", ")", simple_hash("("));
    insert(hashmap, "a", "b", simple_hash("a"));
    insert(hashmap, "s", "d", simple_hash("s"));
    insert(hashmap, "a", "v", simple_hash("a"));

    print_hashtable(hashmap);

    printf("%ld \n", hashmap -> max_collisions);
    printf("%s \n", (char *)get(hashmap, "a", simple_hash("a")));
    printf("%s \n", (char *)get(hashmap, "(", simple_hash("(")));
    insert(hashmap, "(", "{", simple_hash("("));
    print_hashtable(hashmap);
    printf("%s \n", (char *)get(hashmap, "a", simple_hash("a")));

    return 0;
}



