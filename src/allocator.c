#include "allocator.h"

#include <assert.h>
#include <string.h>

mallocator_t mallocator_mk(const struct mallocator_vtable *vtable) {
    assert(mallocator_vtable_valid(vtable));
    return (mallocator_t) { vtable };
}

const struct mallocator_vtable *mallocator_vtable(const mallocator_t *allocator) {
    assert(mallocator_valid(allocator));
    return allocator->vtable;
}

void *mallocator_alloc(mallocator_t *allocator, size_t size) {
    assert(mallocator_valid(allocator));
    return allocator->vtable->alloc(allocator, size);
}

bool mallocator_can_realloc(mallocator_t *allocator) {
    assert(mallocator_valid(allocator));
    return allocator->vtable->realloc;
}

void *mallocator_realloc(mallocator_t *allocator, void *block, size_t new_size) {
    assert(mallocator_valid(allocator) && allocator->vtable->realloc);
    return allocator->vtable->realloc(allocator, block, new_size);
}

bool mallocator_can_free(mallocator_t *allocator) {
    assert(mallocator_valid(allocator));
    return allocator->vtable->free;
}

void mallocator_free(mallocator_t *allocator, void *block) {
    assert(mallocator_valid(allocator) && allocator->vtable->free);
    allocator->vtable->free(allocator, block);
}

bool mallocator_valid(const mallocator_t *allocator) {
    return allocator
        && mallocator_vtable_valid(allocator->vtable);
}

bool mallocator_vtable_valid(const struct mallocator_vtable *vtable) {
    return vtable
        && vtable->alloc;
}