#include "hash_map.h"

struct LRU_cache {
    int      capacity;
    int      num_elements;
    Node*    head_node;
    HashMap* hash_map;
};
typedef struct LRU_cache LRU_cache;

LRU_cache* initialize_LRU_cache(int capacity) {
    LRU_cache* cache = (LRU_cache*)malloc(sizeof(LRU_cache));
    if (!cache)
        return NULL;
    cache->hash_map = initialize_HashMap(capacity);
    if (!cache->hash_map)
        return NULL;
    cache->capacity = capacity;

    return cache;
}

void print_LRU_cache(LRU_cache* cache) {
    Node* tmp = cache->head_node;
    printf("\n----- LRU CACHE -----\n");
    while (tmp != NULL) {
        printf("(key=%s, value=%s)\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    printf("---------------------\n");
}

Node* get_Node(LRU_cache* cache, char* key) {
    return search(cache->hash_map, key);
}

int put_cache(LRU_cache* cache, char* key, char* value) {
    if (put(cache->hash_map, key, value) != 0)
        return 1;

    Node* node = (Node*)malloc(sizeof(Node));
    if (!node)
        return 1;
    node->key   = key;
    node->value = value;
    node->next  = NULL;
    node->prev  = NULL;

    if (cache->head_node == NULL) {
        cache->head_node = node;
    } else {
        Node* tail = cache->head_node;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = node;
        node->prev = tail;
    }

    cache->num_elements++;

    if (cache->num_elements > cache->capacity) {
        Node* remove_node      = cache->head_node;
        cache->head_node       = cache->head_node->next;
        cache->head_node->prev = NULL;
        remove_node->next      = NULL;
        free(remove_node);
        if (remove_Node(cache->hash_map, key) != 0)
            return 1;
    }

    return 0;
}