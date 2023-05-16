#include "allocator.h"

#include <assert.h>
#include <string.h>

void *mallocator_alloc(const struct mallocator *allocator, size_t size) {
    assert(mallocator_valid(allocator));
    return allocator->alloc(size);
}

void *mallocator_realloc(const struct mallocator *allocator, void *block, size_t new_size) {
    assert(mallocator_valid(allocator));
    return allocator->realloc(block, new_size);
}

void mallocator_free(const struct mallocator *allocator, void *block) {
    assert(mallocator_valid(allocator));
    allocator->free(block);
}

bool mallocator_valid(const struct mallocator *allocator) {
    return allocator
        && allocator->alloc
        && allocator->realloc
        && allocator->free;
}