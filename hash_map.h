#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char*        key;
    char*        value;
    struct Node* next;
    struct Node* prev;
};
typedef struct Node Node;

struct Bucket {
    unsigned long hash;
    Node*         nodes;
};
typedef struct Bucket Bucket;

struct HashMap {
    int     num_elements;
    int     capacity;
    Bucket* buckets;
};
typedef struct HashMap HashMap;

HashMap* initialize_HashMap(int capacity) {
    HashMap* hash_map = (HashMap*)malloc(sizeof(HashMap));
    if (!hash_map)
        return NULL;

    hash_map->num_elements = 0;
    hash_map->capacity     = capacity;
    hash_map->buckets      = (Bucket*)calloc(capacity, sizeof(Bucket));
    if (!hash_map->buckets) {
        free(hash_map);
        return NULL;
    }

    return hash_map;
}

unsigned long hash(char* str) {
    unsigned long h = 5381;
    int           c;
    while ((c = *str++))
        h = ((h << 5) + h) + c;
    return h;
}

void resize(HashMap* hash_map, int new_capacity) {
    if (new_capacity < 1)
        return;

    Bucket* new_buckets = (Bucket*)calloc(new_capacity, sizeof(Bucket));
    if (!new_buckets)
        return;

    int     old_capacity = hash_map->capacity;
    Bucket* old_buckets  = hash_map->buckets;

    for (int i = 0; i < old_capacity; i++) {
        Node* node = old_buckets[i].nodes;
        while (node != NULL) {
            Node* next = node->next;

            unsigned long index  = hash(node->key) % new_capacity;
            Bucket*       bucket = &new_buckets[index];

            node->prev = NULL;
            node->next = bucket->nodes;
            if (bucket->nodes)
                bucket->nodes->prev = node;
            bucket->nodes = node;
            bucket->hash  = index;

            node = next;
        }
    }

    free(old_buckets);
    hash_map->buckets  = new_buckets;
    hash_map->capacity = new_capacity;
}

int put_no_resize(HashMap* hash_map, char* key, char* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node)
        return 1;

    node->key   = key;
    node->value = value;
    node->next  = NULL;
    node->prev  = NULL;

    unsigned long index  = hash(key) % hash_map->capacity;
    Bucket*       bucket = &hash_map->buckets[index];

    if (bucket->nodes == NULL) {
        bucket->nodes = node;
        bucket->hash  = index;
    } else {
        Node* tmp        = bucket->nodes;
        Node* tmp_before = tmp;
        bool  found      = false;
        while (tmp != NULL) {
            if (strcmp(tmp->key, key) == 0) {
                tmp->value = value;
                found      = true;
                break;
            }
            tmp_before = tmp;
            tmp        = tmp->next;
        }
        if (!found) {
            tmp_before->next = node;
            node->prev       = tmp_before;
        }
    }

    hash_map->num_elements++;

    return 0;
}

int put(HashMap* hash_map, char* key, char* value) {
    put_no_resize(hash_map, key, value);

    float load_factor = (float)hash_map->num_elements / hash_map->capacity;
    if (load_factor >= 0.75f)
        resize(hash_map, hash_map->capacity * 2);

    return 0;
}

Node* search(HashMap* hash_map, char* key) {
    unsigned long index  = hash(key) % hash_map->capacity;
    Bucket*       bucket = &hash_map->buckets[index];
    Node*         node   = bucket->nodes;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0)
            return node;
        node = node->next;
    }

    return NULL;
}

char* get(HashMap* hash_map, char* key) {
    Node* node = search(hash_map, key);
    return node ? node->value : NULL;
}

int remove_Node_no_resize(HashMap* hash_map, char* key) {
    Node* node = search(hash_map, key);
    if (!node)
        return 1;

    unsigned long index  = hash(key) % hash_map->capacity;
    Bucket*       bucket = &hash_map->buckets[index];

    if (node->prev)
        node->prev->next = node->next;
    else
        bucket->nodes = node->next;

    if (node->next)
        node->next->prev = node->prev;

    free(node);
    hash_map->num_elements--;

    return 0;
}

int remove_Node(HashMap* hash_map, char* key) {
    remove_Node_no_resize(hash_map, key);

    float load_factor = (float)hash_map->num_elements / hash_map->capacity;
    if (load_factor <= 0.25f && hash_map->capacity > 1)
        resize(hash_map, hash_map->capacity / 2);

    return 0;
}

void clean(HashMap* hash_map) {
    for (int i = 0; i < hash_map->capacity; i++) {
        Node* node = hash_map->buckets[i].nodes;
        while (node != NULL) {
            Node* tmp = node;
            node      = node->next;
            free(tmp);
        }
    }
    free(hash_map->buckets);
    free(hash_map);
}

void print_HashMap(HashMap* hash_map) {
    printf("\n----- HASH MAP -----\n");
    for (int i = 0; i < hash_map->capacity; i++) {
        printf("Bucket[%d]: ", i);
        Node* node = hash_map->buckets[i].nodes;
        if (node == NULL) {
            printf("empty\n");
            continue;
        }
        while (node != NULL) {
            printf("(key=%s, value=%s)", node->key, node->value);
            if (node->next)
                printf(" -> ");
            node = node->next;
        }
        printf("\n");
    }
    printf("--------------------\n");
}