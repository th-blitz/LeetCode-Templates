#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


unsigned long int max_val(unsigned long int, unsigned long int);
unsigned long int nearest_prime(unsigned long int);

struct HashTable* HashTable(unsigned long int, void*, void*);
struct TableNode* get_key_value_pair(void* , void*);
unsigned long int probe_bucket_slot(unsigned long int, unsigned long int, unsigned long int);
bool check_key_hashtable_(struct HashTable*, void*);
bool insert_key_val_hashtable(struct HashTable*, void*, void*);
void* get_val_hashtable(struct HashTable*, void* );
void clear_hashtable(struct HashTable*);
void free_hashtable(struct HashTable*);
bool remove_key_val_hashtable(struct HashTable*, void*);


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
    unsigned long int pseudo_random_num;
    unsigned long int (*hash)(void* key);
    bool (*insert)(struct HashTable* self, void* key, void* val);
    bool (*remove)(struct HashTable* self, void* key);
    bool (*search)(struct HashTable* self, void* key);
    void* (*get)(struct HashTable* self, void* key);
    void (*clear)(struct HashTable* self);
    void (*free)(struct HashTable* self);
    void (*print)(struct HashTable* self);
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
    
    unsigned char* primes = (unsigned char*)malloc((num + 1) * sizeof(unsigned char));
    
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

struct HashTable* HashTable(unsigned long int table_len, void* hash_func, void* print_func) {

    if (table_len < 1) {
        return NULL;
    }

    unsigned long int bucket_len = (13 * table_len) / 10;
    bucket_len = nearest_prime(bucket_len);
    if (bucket_len <= table_len)
        bucket_len = nearest_prime(2 * table_len);

    struct HashTable* hash_table = malloc(sizeof(struct HashTable));
    hash_table -> bucket = malloc(sizeof(struct TableNode*) * bucket_len);
    for (unsigned long int i = 0; i < bucket_len; i++) {
        hash_table -> bucket[i] = NULL;
    }

    hash_table -> len = 0;
    hash_table -> max_len = table_len;
    hash_table -> bucket_len = bucket_len;
    hash_table -> max_collisions = 0;
    
    hash_table -> hash = hash_func;
    hash_table -> print = print_func;

    hash_table -> insert = insert_key_val_hashtable;
    hash_table -> remove = remove_key_val_hashtable;
    hash_table -> search = check_key_hashtable_;
    hash_table -> get = get_val_hashtable;
    hash_table -> clear = clear_hashtable;
    hash_table -> free = free_hashtable;

    srand(793702983892 + time(0));
    hash_table -> pseudo_random_num = rand() % 9;

    return hash_table;
    
}

struct TableNode* get_key_value_pair(void* key, void* val) {
    struct TableNode* pair = malloc(sizeof(struct TableNode));
    pair -> key = key;
    pair -> val = val;
    return pair;
}

unsigned long int probe_bucket_slot(unsigned long int bucket_slot, unsigned long int collisions, unsigned long int rand) {
    return bucket_slot + (collisions * collisions) + rand;
}

bool insert_key_val_hashtable(struct HashTable* hash_table, void* key, void* val) {
    
    unsigned long int hash = hash_table -> hash(key);
    
    if (hash_table -> len == hash_table -> max_len) {
        bool check = check_key_hashtable_(hash_table, key);
        if (check == false) {
            return false;
        }
    }
    unsigned long int bucket_slot = hash % hash_table -> bucket_len;

    unsigned long int collisions = 0;

    while (hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key != key) {
        collisions += 1;
        bucket_slot = probe_bucket_slot(bucket_slot, collisions, hash_table -> pseudo_random_num);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }

    if (hash_table -> bucket[bucket_slot] == NULL) {
        hash_table -> bucket[bucket_slot] = get_key_value_pair(key, val);
        hash_table -> len += 1;
    } else {
        hash_table -> bucket[bucket_slot] -> val = val;
    }

    hash_table -> max_collisions = max_val(hash_table -> max_collisions, collisions);
    return true;

}

bool remove_key_val_hashtable(struct HashTable* hash_table, void* key) {

    if (hash_table -> len == 0) {
        return false;
    }

    unsigned long int hash = hash_table -> hash(key);
    unsigned long int bucket_slot = hash % hash_table -> bucket_len;
    unsigned long int collisions = 0;
    unsigned long int max_collisions = hash_table -> max_collisions;
    while ((hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key != key) && (collisions <= max_collisions)) {
        collisions += 1;
        bucket_slot = probe_bucket_slot(bucket_slot, collisions, hash_table -> pseudo_random_num);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }
    bool val = false;
    if (collisions <= max_collisions && hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key == key) {
        free(hash_table -> bucket[bucket_slot]);
        hash_table -> bucket[bucket_slot] = NULL;
        hash_table -> len -= 1;
        val = true;
    }
    return val;
}

bool check_key_hashtable_(struct HashTable* hash_table, void* key) {
    
    unsigned long int hash = hash_table -> hash(key);
    unsigned long int bucket_slot = hash % hash_table -> bucket_len;
    unsigned long int collisions = 0;
    unsigned long int max_collisions = hash_table -> max_collisions;
    while ((hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key != key) && (collisions <= max_collisions)) {
        collisions += 1;
        bucket_slot = probe_bucket_slot(bucket_slot, collisions, hash_table -> pseudo_random_num);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }
    bool val = false;
    if (collisions <= max_collisions && hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key == key) {
        val = true;
    }
    return val;
}

void* get_val_hashtable(struct HashTable* hash_table, void* key) {
    
    unsigned long int hash = hash_table -> hash(key);
    unsigned long int bucket_slot = hash % hash_table -> bucket_len;
    unsigned long int collisions = 0;
    unsigned long int max_collisions = hash_table -> max_collisions;
    while ((hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key != key) && (collisions <= max_collisions)) {
        collisions += 1;
        bucket_slot = probe_bucket_slot(bucket_slot, collisions, hash_table -> pseudo_random_num);
        bucket_slot = bucket_slot % hash_table -> bucket_len;
    }

    void* val = NULL;
    if (collisions <= max_collisions && hash_table -> bucket[bucket_slot] != NULL && hash_table -> bucket[bucket_slot] -> key == key) {
        val = hash_table -> bucket[bucket_slot] -> val;
    }

    return val;
}

void clear_hashtable(struct HashTable* hash_table) {
    for (unsigned long int i = 0; i < hash_table -> bucket_len; i++) {
        if (hash_table -> bucket[i] != NULL) {
            free(hash_table -> bucket[i]);
            hash_table -> bucket[i] = NULL;
        }
    }
    hash_table -> len = 0;
    hash_table -> max_collisions = 0;
}

void free_hashtable(struct HashTable* hash_table) {
    clear_hashtable(hash_table);
    free(hash_table -> bucket);
    free(hash_table);
}


// user defiend functions print and hash;
void print_hashtable(struct HashTable* hash_table) {
    for (unsigned long int i = 0; i < hash_table -> bucket_len; i++) {
        if (hash_table -> bucket[i] != NULL) {
            printf("bucket[%ld] = { %s : %s }\n", i, (char *)hash_table -> bucket[i] -> key, (char *)hash_table -> bucket[i] -> val);
        }
    }
}

// http://www.cse.yorku.ca/~oz/hash.html ( hash functions like djb2 and sdbm )

unsigned long int hash_sdbm(void *strr) {
        
        unsigned long int hash = 0;
        int c;
        char* str = strr;

        while (c = *str++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
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

void print_hashtable_stats(struct HashTable* hashmap) {
    printf("- hashmap : len %ld, max_len %ld, bucket_len %ld, max_collisions %ld , pseudo_rand %ld \n\n", 
        hashmap -> len, hashmap -> max_len, hashmap -> bucket_len, hashmap -> max_collisions, 
        hashmap -> pseudo_random_num
    );
}

void run_tests() {

    unsigned long int initial_time = time(0);
    struct HashTable* hashmap = HashTable(1000, hash_sdbm, print_hashtable);
    printf("time 0 : %ld \n", time(0) - initial_time);
    print_hashtable_stats(hashmap);

    char* key1 = "emp name";
    char* key2 = "emp age";
    char* key3 = "emp gender";
    char* key4 = "emp position";
    char* key5 = "AAA";
    char* key6 = "BBB";
    char* key7 = "CCC";
    char* key8 = "DDD";

    char* val1 = "thblitxx";
    char* val2 = "22 ";
    char* val3 = "male";
    char* val4 = "jobless ";
    char* val5 = "aaa";
    char* val6 = "bbb";
    char* val7 = "ccc";
    char* val8 = "ddd";

    hashmap -> insert(hashmap, key1, val1);
    hashmap -> insert(hashmap, key2, val2);
    hashmap -> insert(hashmap, key3, val3);
    hashmap -> insert(hashmap, key4, val4);
    
    hashmap -> print(hashmap);
    print_hashtable_stats(hashmap); 

    
    hashmap -> insert(hashmap, key5, val5);
    hashmap -> insert(hashmap, key6, val6);
    hashmap -> insert(hashmap, key7, val7);
    hashmap -> insert(hashmap, key8, val8);

    hashmap -> print(hashmap);
    print_hashtable_stats(hashmap);

    printf("search %s : %d \n", key6, hashmap -> search(hashmap, key6));
    printf("serach %s : %d \n", "ZZZ",hashmap -> search(hashmap, "ZZZ"));

    printf("get %s : %s \n", key6, (char *)hashmap -> get(hashmap, key6));
    printf("get %s : %s \n", "ZZZ", (char *)hashmap -> get(hashmap, "ZZZ"));

    hashmap -> insert(hashmap, key5, val6);
    hashmap -> insert(hashmap, key8, val7);

    hashmap -> print(hashmap);
    print_hashtable_stats(hashmap);

    hashmap -> clear(hashmap);

    hashmap -> print(hashmap);
    print_hashtable_stats(hashmap);

     
    hashmap -> insert(hashmap, key5, val5);
    hashmap -> insert(hashmap, key6, val6);
    hashmap -> insert(hashmap, key7, val7);
    hashmap -> insert(hashmap, key8, val8);

    hashmap -> print(hashmap);
    print_hashtable_stats(hashmap);

    hashmap -> remove(hashmap, key7);
    hashmap -> remove(hashmap, key8);
    hashmap -> remove(hashmap, "hello there");

    hashmap -> print(hashmap);
    print_hashtable_stats(hashmap);

    hashmap -> free(hashmap);
}

int main() {

    run_tests();

    return 0;
}



