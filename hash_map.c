#include "hash_map.h"

int main() {

    HashMap* hash_map = initialize_HashMap(2);
    if (!hash_map) {
        printf("Memory allocation failed\n");
    }

    print_HashMap(hash_map);

    if ((put(hash_map, "John Smith", "521-1234")) != 0) {
        printf("Error in inserting\n");
        return 1;
    }

    print_HashMap(hash_map);

    if ((put(hash_map, "Lisa Smith", "521-8976")) != 0) {
        printf("Error in inserting\n");
        return 1;
    }

    print_HashMap(hash_map);

    if ((put(hash_map, "Sam Doe", "521-5030")) != 0) {
        printf("Error in inserting\n");
        return 1;
    }

    print_HashMap(hash_map);

    if ((put(hash_map, "Sandra Dee", "521-9655")) != 0) {
        printf("Error in inserting\n");
        return 1;
    }

    print_HashMap(hash_map);

    if ((put(hash_map, "Ted Baker", "418-4165")) != 0) {
        printf("Error in inserting\n");
        return 1;
    }

    print_HashMap(hash_map);

    // Looking for phone number of Sandra Dee
    char* phone_number = get(hash_map, "Sandra Dee");
    printf("Found phone number of Sandra Dee: %s", phone_number);

    // Sandra is not funny, we want to remove her phone number
    if (remove_Node(hash_map, "Sandra Dee") != 0) {
        printf("Sandra Dee not found");
    }

    print_HashMap(hash_map);

    // Now a lot of friends are not funny
    if (remove_Node(hash_map, "Lisa Smith") != 0) {
        printf("Lisa Smith not found");
    }

    print_HashMap(hash_map);

    if (remove_Node(hash_map, "Sam Doe") != 0) {
        printf("Sam Doe not found");
    }

    print_HashMap(hash_map);

    clean(hash_map);

    print_HashMap(hash_map);

    return 0;
}