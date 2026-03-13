#include "LRU_cache.h"

int main() {

    LRU_cache* cache = initialize_LRU_cache(2);
    if (!cache) {
        printf("Memory allocation failed\n");
        return 1;
    }

    if (put_cache(cache, "1", "1") != 0) {
        printf("Put failed\n");
        return 1;
    }

    print_LRU_cache(cache);

    if (put_cache(cache, "2", "2") != 0) {
        printf("Put failed\n");
        return 1;
    }

    print_LRU_cache(cache);

    if (put_cache(cache, "3", "3") != 0) {
        printf("Put failed\n");
        return 1;
    }

    print_LRU_cache(cache);

    if (put_cache(cache, "4", "4") != 0) {
        printf("Put failed\n");
        return 1;
    }

    print_LRU_cache(cache);

    if (put_cache(cache, "3", "3") != 0) {
        printf("Put failed\n");
        return 1;
    }

    print_LRU_cache(cache);

    return 0;
}