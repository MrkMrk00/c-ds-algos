#include <math.h>
#include "map.h"

hashmap_t *hashmap_init(size_t initial_count)
{
    size_t size;
    hashmap_t *map;
    void *data;

    size = sizeof(void*) * initial_count;

    data = malloc(size);
    map = malloc(sizeof(hashmap_t));

    *map = (hashmap_t) {
	.size = size,
	.data = data,
    };

    return map;
}

bool hashmap_free(hashmap_t *map)
{
    if (NULL == map || NULL == map->data) {
	return false;
    }
    
    if (map->data != NULL) {
	free(map->data);
    }

    free(map);

    return true;
}

size_t hashmap_hash_code(hashmap_t *map, char *key, size_t key_len, uint8_t *err) 
{
    size_t i, result;

    if (map == NULL) {
	*err = MAP_ERR_MAP_NULL;
	return 0;
    }

    if (key_len < 1) {
	*err = MAP_ERR_WRONG_KEY;
	return 0;
    }
    
    result = 0;
    for (i = 0; i < key_len; i++) {
	result += key[i] * pow(MAP_MAGIC_CONST, key_len - i);
    }
    
    err = MAP_NO_ERR;
    return (result % MAP_MAX_COUNT(map));
}

bool hashmap_set(hashmap_t *map, char *key, size_t key_len, void *value)
{
    size_t hash;
    uint8_t err = 0;

    if (NULL == map || key_len < 1) {
	return false;
    }

    hash = hashmap_hash_code(map, key, key_len, &err);
    if (err != 0) {
	return false;
    }

    map->data[hash] = value;

    return true;
}

void *hashmap_get(hashmap_t *map, char *key, size_t key_len)
{
    size_t hash;
    uint8_t err;

    hash = hashmap_hash_code(map, key, key_len, &err);
    if (err != 0) {
	return NULL;
    }

    return map->data[hash];
}

