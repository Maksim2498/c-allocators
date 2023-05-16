#include "default.h"

#include <stdlib.h>

const struct mallocator_vtable MALLOCATOR_VTABLE_DEFAULT = {
    .alloc   = mallocator_default_alloc,
    .realloc = mallocator_default_realloc,
    .free    = mallocator_default_free
};

const mallocator_t MALLOCATOR_DEFAULT = {
    .vtable = &MALLOCATOR_VTABLE_DEFAULT
};

void *mallocator_default_alloc(mallocator_t *allocator, size_t size) {
    return malloc(size);
}

void *mallocator_default_realloc(mallocator_t *allocator, void *block, size_t new_size) {
    return realloc(block, new_size);
}

void mallocator_default_free(mallocator_t *allocator, void *block) {
    return free(block);
}