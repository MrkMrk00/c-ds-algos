#ifndef _H_MAP
#define _H_MAP

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAP_MAGIC_CONST 31

#define MAP_NO_ERR 		0
#define MAP_ERR_WRONG_KEY 	1
#define MAP_ERR_MAP_NULL 	2

typedef struct {
    size_t size;
    void **data;
} hashmap_t;

#define MAP_MAX_COUNT(map) ((map)->size / sizeof(void*))

hashmap_t *hashmap_init(size_t initial_count);
bool hashmap_free(hashmap_t *map);

size_t hashmap_hash_code(hashmap_t *map, char *key, size_t key_len, uint8_t *err);

bool hashmap_set(hashmap_t *map, char *key, size_t key_len, void *value);

void *hashmap_get(hashmap_t *map, char *key, size_t key_len);

#endif
