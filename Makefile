CC = gcc
CFLAGS = -Wall -Wextra
OUT_DIR = output

all: hashmap LRUcache

hashmap: | $(OUT_DIR)
	$(CC) $(CFLAGS) hash_map.c -o $(OUT_DIR)/hash_map
	./$(OUT_DIR)/hash_map

LRUcache: | $(OUT_DIR)
	$(CC) $(CFLAGS) LRU_cache.c -o $(OUT_DIR)/LRU_cache
	./$(OUT_DIR)/LRU_cache

$(OUT_DIR):
	mkdir -p $(OUT_DIR)